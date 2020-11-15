// Glossify.cpp : implementation file
//

#include "stdafx.h"
#include "Cdr.h"
#include "Glossify.h"
#include <stack>
#include <windows.h>
#include ".\glossify.h"

// CGlossify dialog

const wchar_t* TAG_NAME = L"GlossaryTermRef";

IMPLEMENT_DYNAMIC(CGlossify, CDialog)
CGlossify::CGlossify(bool dig, const CString dict, CWnd* pParent /*=NULL*/)
: CDialog(CGlossify::IDD, pParent), curChain(0), curNode(0), m_dig(dig),
    dictionary(dict)
{
    _Application app = cdr::get_app();
    doc = app.GetActiveDocument();
    range = doc.GetRange();
    DOMNode docElement = doc.GetDocumentElement();
    docType = docElement.GetNodeName();
    language = L"en";
    if (docType == L"Summary") {
        ::DOMNode c = docElement.GetFirstChild();
        while (c) {
            if (c.GetNodeName() == L"SummaryMetaData") {
                ::DOMNode gc = c.GetFirstChild();
                while (gc) {
                    if (gc.GetNodeName() == L"SummaryLanguage") {
                        CString value = cdr::extract_element_text(gc);
                        // ::AfxMessageBox(value);
                        if (value == L"Spanish")
                            language = L"es";
                        break;
                    }
                    gc = gc.GetNextSibling();
                }
            }
            c = c.GetNextSibling();
        }
    }
}

CGlossify::~CGlossify()
{
}

void CGlossify::DoDataExchange(CDataExchange* pDX)
{
    CDialog::DoDataExchange(pDX);
    DDX_Control(pDX, IDC_EDIT1, m_phrase);
    DDX_Control(pDX, IDC_EDIT2, m_markup);
}


BEGIN_MESSAGE_MAP(CGlossify, CDialog)
    ON_BN_CLICKED(IDOK2, OnSkip)
    ON_BN_CLICKED(IDCANCEL, OnDone)
    ON_BN_CLICKED(IDOK, OnMarkup)
    ON_BN_CLICKED(IDC_GLOSSIFY_SKIP_FIRST, OnBnClickedGlossifySkipFirst)
    ON_BN_CLICKED(IDC_GLOSSIFY_NEXT_SECTION, OnBnClickedGlossifyNextSection)
END_MESSAGE_MAP()


// CGlossify message handlers

void CGlossify::OnSkip()
{
    if (curNode)
        curNode->marked_up = true;
    if (!findNextMatch()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

void CGlossify::OnBnClickedGlossifySkipFirst()
{
    if (!findNextMatch()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

void CGlossify::OnDone()
{
    OnCancel();
}

void CGlossify::OnMarkup()
{
    if (curNode)
        curNode->marked_up = true;
    CString val;
    m_markup.GetWindowText(val);
    int semicolon = val.Find(';');
    if (semicolon != -1)
        val = val.Left(semicolon);
    range.Surround(TAG_NAME);

    range.SetContainerAttribute(L"cdr:href", val);
    if (!findNextMatch()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}

/**
 * Added for JIRA ticket OCECDR-3815. Exercises option
 * to dig through the layers of Insertion and Deletion
 * elements to find what would otherwise be top-level
 * SummarySection elements.
 */
void CGlossify::keepDigging(::DOMNode& node, ::_Document& doc) {
    ::DOMNode c = node.GetFirstChild();
    while (c) {
        CString nodeName = c.GetNodeName();
        if (nodeName == L"SummarySection")
            chains.push_back(WordChain(c, doc));
        else if (nodeName == L"Insertion" ||
                 nodeName == L"Deletion")
            keepDigging(c, doc);
        c = c.GetNextSibling();
    }
}

void CGlossify::findChains(DOMNode& docElem)
{
    _Document doc = cdr::get_app().GetActiveDocument();
    doc.SetFormattingUpdating(FALSE);
    try {
        if (docType == L"Summary") {
            ::DOMNode c = docElem.GetFirstChild();
            while (c) {
                CString nodeName = c.GetNodeName();
                if (nodeName == L"SummarySection")
                    chains.push_back(WordChain(c, doc));
                else if (m_dig) {
                    if (nodeName == L"Insertion" ||
                        nodeName == L"Deletion")
                        keepDigging(c, doc);
                }
                c = c.GetNextSibling();
            }
        }
    }
    catch (...) {}
    doc.SetFormattingUpdating(TRUE);
}

static CString normalizeWord(const CString& s) {
    CString w = s;
    wchar_t* chars = L"'\".,?!:;()[]{}<>\x201C\x201D";
    for (size_t i = 0; chars[i]; ++i)
        w.Remove(chars[i]);
    wchar_t* p = w.GetBuffer(w.GetLength());
    CharUpperBuff(p, w.GetLength());
    w.ReleaseBuffer();
    // MakeUpper is badly broken for Unicode; BAD Microsoft!
    // w.MakeUpper();
    return w;
}

CGlossify::WordChain::WordChain(::DOMNode node, ::_Document doc)
{
    ::Range range = doc.GetRange();
    ::Range end   = doc.GetRange();
    ::Find find = range.GetFind();
    range.SelectBeforeNode(node);
    end.SelectAfterNode(node);
    while (find.Execute(L"[^-\n\r\t ]+", L"", L"",
                        TRUE, FALSE, TRUE, TRUE, FALSE, 0, FALSE))
    {
        if (!range.GetIsLessThan(end, FALSE))
            break;
        CString s = normalizeWord(range.GetText());
        if (!s.IsEmpty()) {
            ::Range r = range.GetDuplicate();
            Word w = Word(r, s);
            words.push_back(w);
        }
    }
    curWord = 0;
}

bool CGlossify::findNextMatch()
{
    // We're done if there are no more word chains to look at.
    if (curChain >= static_cast<int>(chains.size()))
        return false;

    // Try to match the phrases in the document with those in the glossary.
    cdr::GlossaryTree* gt = cdr::get_glossary_tree(language, dictionary);

    // Pick up where we left off in the current word chain from the doc.
    WordChain* chain = &chains[curChain];

    // Remember the path in the glossary tree for the current phrase.
    std::stack<cdr::GlossaryNode*> phrase;

    // Keep looking until we run out of word chains.
    while (chain) {

        // Start at the root of the tree.
        cdr::GlossaryNodeMap* currentNodeMap = &gt->node_map;

        // If we're finished with the current chain, move to the next one.
        int wordsLeft = static_cast<int>(chain->words.size()) - chain->curWord;
        while (wordsLeft < 1) {
            if (++curChain >= static_cast<int>(chains.size()))
                return false;
            chain = &chains[curChain];
            wordsLeft = (int)chain->words.size();
            if (docType == L"Summary")
                gt->clear_flags();
        }

        // Build the longest matching phrase we can from the current position.
        while (static_cast<int>(phrase.size()) < wordsLeft) {
            Word& w = chain->words[chain->curWord + phrase.size()];
            cdr::GlossaryNodeMap::iterator i = currentNodeMap->find(w.w);
            if (i == currentNodeMap->end())
                break;
            phrase.push(i->second);
            currentNodeMap = &i->second->node_map;
        }

        // Look for a match with a complete glossary phrase.
        while (!phrase.empty()) {

            // Last word has a doc ID if this is a complete phrase; skip
            // over it if we've already marked it up for this chain.
            cdr::GlossaryNode* n = phrase.top();
            if (n->doc_id && !n->marked_up) {

                // Position the range object to include the phrase.
                Word& firstWord = chain->words[chain->curWord];
                Word& lastWord  = chain->words[chain->curWord +
                                               phrase.size() - 1];
                range = firstWord.r.GetDuplicate();
                bool glossifiable = true;
                if (!range.ExtendTo(lastWord.r))
                    glossifiable = false;

                // Make sure the phrase can be marked up.
                if (glossifiable && !range.GetCanSurround(TAG_NAME))
                    glossifiable = false;

                // Populate the controls of the dialog box.
                if (glossifiable) {
                    CString cdrId;
                    CString phraseText = range.GetText();
                    int i = phraseText.GetLength();
                    const wchar_t* endPunct = L".;:,";

                    // Back up in front of trailing punctuation.
                    if (i > 0 && _tcschr(endPunct, phraseText[i - 1])) {
                        ::Range endPoint = lastWord.r.GetDuplicate();
                        endPoint.Collapse(0);
                        while (i-- > 0 && _tcschr(endPunct, phraseText[i]))
                            endPoint.MoveLeft(0); // Broken; bug in XMetaL.
                        phraseText.TrimRight(endPunct);
                        range = firstWord.r.GetDuplicate();
                        if (!range.ExtendTo(endPoint))
                            glossifiable = false;
                        else if (!range.GetCanSurround(TAG_NAME))
                            glossifiable = false;
                    }
                    if (glossifiable) {
                        CString name = gt->names[n->doc_id];
                        cdrId.Format(L"CDR%010d; %s", n->doc_id, name);
                        m_phrase.SetWindowText(phraseText);
                        m_markup.SetWindowText(cdrId);
                        range.Select();

                        // Skip past the current phrase.
                        chain->curWord += (int)phrase.size();
                        curNode = n;
                        return true;
                    }
                }
            }

            // Shrink the phrase by one word.
            phrase.pop();
        }

        // Can't use the current word in a glossary phrase; skip past it.
        ++chain->curWord;
    }

    // Make lint happy (but we'll never reach here).
    return false;
}

BOOL CGlossify::OnInitDialog()
{
    CDialog::OnInitDialog();

    DOMNode docElement = doc.GetDocumentElement();
    cdr::get_glossary_tree(language, dictionary)->clear_flags();
    findChains(docElement);

    if (chains.empty()) {
        ::AfxMessageBox(L"No glossifiable sections found");
        OnCancel();
    }
    if (!findNextMatch()) {
        ::AfxMessageBox(L"No glossifiable phrases found");
        OnCancel();
    }
    return TRUE;  // return TRUE unless you set the focus to a control
    // EXCEPTION: OCX Property Pages should return FALSE
}

void CGlossify::OnBnClickedGlossifyNextSection()
{
    // We're done if there are no more word chains to look at.
    if (curChain < static_cast<int>(chains.size()))
        ++curChain;
    if (!findNextMatch()) {
        ::AfxMessageBox(L"No more glossary phrases found");
        OnOK();
    }
}
