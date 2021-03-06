// Machine generated IDispatch wrapper class(es) created with ClassWizard
/////////////////////////////////////////////////////////////////////////////
// DOMNode wrapper class

class DOMNode : public COleDispatchDriver
{
public:
	DOMNode() {}		// Calls COleDispatchDriver default constructor
	DOMNode(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMNode(const DOMNode& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
};
/////////////////////////////////////////////////////////////////////////////
// DOMNodeList wrapper class

class DOMNodeList : public COleDispatchDriver
{
public:
	DOMNodeList() {}		// Calls COleDispatchDriver default constructor
	DOMNodeList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMNodeList(const DOMNodeList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH item(long index);
	long GetLength();
};
/////////////////////////////////////////////////////////////////////////////
// DOMNamedNodeMap wrapper class

class DOMNamedNodeMap : public COleDispatchDriver
{
public:
	DOMNamedNodeMap() {}		// Calls COleDispatchDriver default constructor
	DOMNamedNodeMap(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMNamedNodeMap(const DOMNamedNodeMap& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH item(long index);
	long GetLength();
	LPDISPATCH getNamedItem(LPCTSTR name);
	LPDISPATCH setNamedItem(LPDISPATCH node);
	LPDISPATCH removeNamedItem(LPCTSTR name);
};
/////////////////////////////////////////////////////////////////////////////
// _DOMDocument wrapper class

class _DOMDocument : public COleDispatchDriver
{
public:
	_DOMDocument() {}		// Calls COleDispatchDriver default constructor
	_DOMDocument(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_DOMDocument(const _DOMDocument& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	LPDISPATCH createElement(LPCTSTR name);
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data);
	LPDISPATCH createTextNode(LPCTSTR data);
	LPDISPATCH createComment(LPCTSTR data);
	LPDISPATCH createDocumentFragment();
	LPDISPATCH GetDocumentElement();
	LPDISPATCH createAttribute(LPCTSTR name);
	LPDISPATCH createEntityReference(LPCTSTR name);
	LPDISPATCH createCDATASection(LPCTSTR data);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	LPDISPATCH GetDoctype();
	LPDISPATCH GetImplementation();
};
/////////////////////////////////////////////////////////////////////////////
// DOMElement wrapper class

class DOMElement : public COleDispatchDriver
{
public:
	DOMElement() {}		// Calls COleDispatchDriver default constructor
	DOMElement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMElement(const DOMElement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetTagName();
	CString getAttribute(LPCTSTR attrName);
	void setAttribute(LPCTSTR attrName, LPCTSTR attrValue);
	void removeAttribute(LPCTSTR attrName);
	void normalize();
	LPDISPATCH getAttributeNode(LPCTSTR attrName);
	LPDISPATCH setAttributeNode(LPDISPATCH attrNode);
	LPDISPATCH removeAttributeNode(LPDISPATCH attrNode);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	BOOL hasAttribute(LPCTSTR attrName);
};
/////////////////////////////////////////////////////////////////////////////
// DOMAttr wrapper class

class DOMAttr : public COleDispatchDriver
{
public:
	DOMAttr() {}		// Calls COleDispatchDriver default constructor
	DOMAttr(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMAttr(const DOMAttr& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetName();
	CString GetValue();
	void SetValue(LPCTSTR lpszNewValue);
	BOOL GetSpecified();
	LPDISPATCH GetOwnerElement();
};
/////////////////////////////////////////////////////////////////////////////
// DOMProcessingInstruction wrapper class

class DOMProcessingInstruction : public COleDispatchDriver
{
public:
	DOMProcessingInstruction() {}		// Calls COleDispatchDriver default constructor
	DOMProcessingInstruction(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMProcessingInstruction(const DOMProcessingInstruction& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetTarget();
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// DOMText wrapper class

class DOMText : public COleDispatchDriver
{
public:
	DOMText() {}		// Calls COleDispatchDriver default constructor
	DOMText(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMText(const DOMText& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
	LPDISPATCH splitText(long offset);
};
/////////////////////////////////////////////////////////////////////////////
// DOMCharacterData wrapper class

class DOMCharacterData : public COleDispatchDriver
{
public:
	DOMCharacterData() {}		// Calls COleDispatchDriver default constructor
	DOMCharacterData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCharacterData(const DOMCharacterData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
};
/////////////////////////////////////////////////////////////////////////////
// DOMComment wrapper class

class DOMComment : public COleDispatchDriver
{
public:
	DOMComment() {}		// Calls COleDispatchDriver default constructor
	DOMComment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMComment(const DOMComment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
};
/////////////////////////////////////////////////////////////////////////////
// DOMDocumentFragment wrapper class

class DOMDocumentFragment : public COleDispatchDriver
{
public:
	DOMDocumentFragment() {}		// Calls COleDispatchDriver default constructor
	DOMDocumentFragment(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMDocumentFragment(const DOMDocumentFragment& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
};
/////////////////////////////////////////////////////////////////////////////
// DOMEntityReference wrapper class

class DOMEntityReference : public COleDispatchDriver
{
public:
	DOMEntityReference() {}		// Calls COleDispatchDriver default constructor
	DOMEntityReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMEntityReference(const DOMEntityReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
};
/////////////////////////////////////////////////////////////////////////////
// DOMCDATASection wrapper class

class DOMCDATASection : public COleDispatchDriver
{
public:
	DOMCDATASection() {}		// Calls COleDispatchDriver default constructor
	DOMCDATASection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCDATASection(const DOMCDATASection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetData();
	void SetData(LPCTSTR lpszNewValue);
	long GetLength();
	CString substringData(long offset, long count);
	void appendData(LPCTSTR data);
	void insertData(long offset, LPCTSTR data);
	void deleteData(long offset, long count);
	void replaceData(long offset, long count, LPCTSTR data);
	LPDISPATCH splitText(long offset);
};
/////////////////////////////////////////////////////////////////////////////
// DOMDocumentType wrapper class

class DOMDocumentType : public COleDispatchDriver
{
public:
	DOMDocumentType() {}		// Calls COleDispatchDriver default constructor
	DOMDocumentType(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMDocumentType(const DOMDocumentType& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetName();
	LPDISPATCH GetEntities();
	LPDISPATCH GetNotations();
	CString GetElementType(long index);
	VARIANT GetElementTypes();
	BOOL GetHasElementType(LPCTSTR ElementName);
	BOOL GetHasAttribute(LPCTSTR ElementName, LPCTSTR AttributeName);
	CString GetElementAttribute(LPCTSTR ElementName, long index);
	VARIANT GetElementAttributes(LPCTSTR ElementName);
	CString GetPublicId();
	CString GetSystemId();
	long GetAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName);
	CString GetEnumeratedAttributeType(LPCTSTR ElementName, LPCTSTR AttributeName, long index);
	VARIANT GetEnumeratedAttributeTypes(LPCTSTR ElementName, LPCTSTR AttributeName);
	long GetElementContentType(LPCTSTR ElementName);
	long GetAttributeDefaultType(LPCTSTR ElementName, LPCTSTR AttributeName);
	CString GetAttributeDefaultValue(LPCTSTR ElementName, LPCTSTR AttributeName);
	void addElement(LPCTSTR ElementName, LPCTSTR description, BOOL any, BOOL retainWhiteSpace);
	void addElementToInclusions(LPCTSTR ElementNameToAdd, LPCTSTR ElementNameInclusions);
	void addAttribute(LPCTSTR ElementName, LPCTSTR attrName, LPCTSTR helpString, long attrType, long dfltType, LPCTSTR attValueDefault);
	// method 'addEnumeratedAttribute' not emitted because of invalid return type or parameter type
	void addInPlaceControlOverride(LPCTSTR selector, LPCTSTR progID, LPCTSTR scriptPrefix, LPCTSTR userData, BOOL useBmpPrinting);
	CString GetParentElementType(LPCTSTR elementType, long index);
	VARIANT GetParentElementTypes(LPCTSTR elementType);
	BOOL GetHasParentElementType(LPCTSTR elementType, LPCTSTR ParentElementName);
	CString GetChildElementType(LPCTSTR elementType, long index);
	VARIANT GetChildElementTypes(LPCTSTR elementType);
	BOOL GetHasChildElementType(LPCTSTR elementType, LPCTSTR ChildElementName);
};
/////////////////////////////////////////////////////////////////////////////
// DOMImplementation wrapper class

class DOMImplementation : public COleDispatchDriver
{
public:
	DOMImplementation() {}		// Calls COleDispatchDriver default constructor
	DOMImplementation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMImplementation(const DOMImplementation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL hasFeature(LPCTSTR feature, LPCTSTR version);
};
/////////////////////////////////////////////////////////////////////////////
// _Document wrapper class

class _Document : public COleDispatchDriver
{
public:
	_Document() {}		// Calls COleDispatchDriver default constructor
	_Document(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Document(const _Document& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	LPDISPATCH createElement(LPCTSTR name);
	LPDISPATCH createProcessingInstruction(LPCTSTR target, LPCTSTR data);
	LPDISPATCH createTextNode(LPCTSTR data);
	LPDISPATCH createComment(LPCTSTR data);
	LPDISPATCH createDocumentFragment();
	LPDISPATCH GetDocumentElement();
	LPDISPATCH createAttribute(LPCTSTR name);
	LPDISPATCH createEntityReference(LPCTSTR name);
	LPDISPATCH createCDATASection(LPCTSTR data);
	LPDISPATCH getElementsByTagName(LPCTSTR tagName);
	LPDISPATCH GetDoctype();
	LPDISPATCH GetImplementation();
	CString GetName();
	CString GetFullName();
	CString GetTitle();
	void SetTitle(LPCTSTR lpszNewValue);
	BOOL GetSaved();
	void SetSaved(BOOL bNewValue);
	void Save();
	void SaveAs(VARIANT* FileName, BOOL AddToRecentFiles);
	void Close(long SaveChanges);
	BOOL Undo(long Times);
	BOOL Redo(long Times);
	void Activate();
	void ScrollToSelection();
	BOOL GetInCurrentProject();
	CString GetPath();
	CString GetBodyAttribute(LPCTSTR attrName);
	void SetBodyAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue);
	CString GetDocumentTitle();
	void SetDocumentTitle(LPCTSTR lpszNewValue);
	CString UniqueAttributeValue(LPCTSTR AttributeName, LPCTSTR Prefix, VARIANT* number);
	void Validate();
	LPDISPATCH GetRange();
	BOOL GetIsXML();
	BOOL GetIsSGML();
	BOOL GetIsHTML();
	long GetViewType();
	void SetViewType(long nNewValue);
	LPDISPATCH GetCustomDocumentProperties();
	CString GetMacroFile();
	BOOL GetIsValid();
	void Reload();
	void RefreshCssStyle();
	BOOL Layout();
	CString GetLocalPath();
	CString GetLocalFullName();
	BOOL GetIsEntityDeclared(LPCTSTR EntityName);
	void DeleteEntityDeclaration(LPCTSTR EntityName);
	void DeclareTextEntity(LPCTSTR EntityName, LPCTSTR entityContent, long entityType);
	void DeclareExternalEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName);
	void DeclareGraphicEntity(LPCTSTR EntityName, LPCTSTR publicName, LPCTSTR FileName, LPCTSTR notationName, long entityType);
	LPDISPATCH GetChangedNodes();
	void ClearNodeChangedStates(LPDISPATCH inNode, BOOL deep);
	void ClearAllChangedStates();
	BOOL GetNodeState(LPCTSTR stateName, LPDISPATCH inNode);
	void HideInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType);
	void ShowInAttributeInspector(LPCTSTR attrName, LPCTSTR elementType);
	CString GetBrowserURL();
	void SetBrowserURL(LPCTSTR lpszNewValue);
	CString GetBrowserApplication();
	void SetBrowserApplication(LPCTSTR lpszNewValue);
	void PreviewInBrowser(LPCTSTR Browser);
	BOOL GetRulesChecking();
	void SetRulesChecking(BOOL bNewValue);
	void UndoClear();
	CString GetRenderedContent(LPDISPATCH inNode);
	void SetRenderedContent(LPDISPATCH inNode, LPCTSTR renderedContent);
	LPDISPATCH createCharacterReference(long value);
	LPDISPATCH getElementById(LPCTSTR value);
	long GetPreviousViewType();
	CString GetRulesFile();
	BOOL GetDOMEnforceValid();
	void SetDOMEnforceValid(BOOL bNewValue);
	CString GetDisplayStylesFile();
	BOOL AcceptDropFormat(VARIANT* dropFormat, LPCTSTR formatName);
	BOOL GetStructureViewVisible();
	void SetStructureViewVisible(BOOL bNewValue);
	CString CreatePreviewFile();
	LPDISPATCH GetCustomProperties();
	LPDISPATCH GetStyleSheets();
	BOOL GetIsInWellFormedEditingMode();
	LPDISPATCH GetChangedNodesbyKey(LPCTSTR key);
	void ClearNodeChangedStatesbyKey(LPCTSTR key, LPDISPATCH inNode, BOOL deep);
	void ClearAllChangedStatesbyKey(LPCTSTR key);
	BOOL GetNodeStatebyKey(LPCTSTR key, LPCTSTR stateName, LPDISPATCH inNode);
	CString GetAllUsersMacroFile();
	CString GetCurrentUserMacroFile();
	CString GetXml();
	LPDISPATCH GetCustomizations();
	BOOL GetTrackRevisions();
	void SetTrackRevisions(BOOL bNewValue);
	BOOL GetMinimizeTagIcons();
	void SetMinimizeTagIcons(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Range wrapper class

class Range : public COleDispatchDriver
{
public:
	Range() {}		// Calls COleDispatchDriver default constructor
	Range(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Range(const Range& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void TypeText(LPCTSTR Text);
	void Cut();
	void Copy();
	void Paste();
	void Delete();
	void MoveLeft(long MovementType);
	void MoveRight(long MovementType);
	void MoveUp(long MovementType);
	void MoveDown(long MovementType);
	void MoveColumnLeft();
	void MoveColumnRight();
	void MoveRowUp();
	void MoveRowDown();
	void MergeCellLeft();
	void MergeCellRight();
	void MergeCellUp();
	void MergeCellDown();
	void SplitCellColumn();
	void SplitCellRow();
	void InsertRowsAbove(long number);
	void InsertRowsBelow(long number);
	void InsertColumnsLeft(long number);
	void InsertColumnsRight(long number);
	void HomeKey(long unit, long extend);
	void EndKey(long unit, long extend);
	LPDISPATCH GetFont();
	long GetHorizontalAlignment();
	void SetHorizontalAlignment(long nNewValue);
	void GotoNext(long GotoItem);
	void GotoPrevious(long GotoItem);
	void Collapse(long CollapseDirection);
	void PasteString(LPCTSTR String);
	void InsertForm(long FormElement);
	void InsertElement(LPCTSTR ElementName);
	void InsertElementWithRequired(LPCTSTR ElementName);
	CString GetContainerName();
	void SetContainerName(LPCTSTR lpszNewValue);
	void RemoveContainerTags();
	void SplitContainer();
	CString GetContainerAttribute(LPCTSTR attrName);
	void SetContainerAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue);
	void InsertComment();
	void InsertBreak();
	void InsertHorizontalRule();
	void InsertNBSP();
	void JoinElementToPreceding();
	void InsertEntity(LPCTSTR EntityName);
	void Surround(LPCTSTR ElementName);
	void SelectElement();
	void TypingSplit();
	void DeleteColumn();
	void DeleteRow();
	void InsertTable(long NumRows, long NumCols, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing);
	void InsertCaption();
	void Indent();
	void Outdent();
	void InsertImage(LPCTSTR Src, LPCTSTR Alt, LPCTSTR Align, LPCTSTR Width, LPCTSTR Height, LPCTSTR Border);
	CString GetStyle();
	void SetStyle(LPCTSTR lpszNewValue);
	void PageUp();
	void PageDown();
	void ToggleTableCellType();
	CString GetElementName(long AncestorNum);
	CString GetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum);
	void SetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum, LPCTSTR lpszNewValue);
	BOOL GetIsParentElement(LPCTSTR ElementName);
	void ListIndent(VARIANT* ElementName);
	void ListOutdent(VARIANT* ElementName);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetIsInsertionPoint();
	void InsertLink(LPCTSTR Href, LPCTSTR target);
	LPDISPATCH GetContainerNode();
	void SelectBeforeNode(LPDISPATCH node);
	void SelectAfterNode(LPDISPATCH node);
	void SelectNodeContents(LPDISPATCH node);
	void SelectAfterContainer();
	void SelectBeforeContainer();
	void SelectContainerContents();
	LPDISPATCH GetFind();
	void BasicPaste();
	void PasteStringWithInterpret(LPCTSTR String);
	BOOL GetCanInsert(LPCTSTR ElementName);
	BOOL GetCanChange(LPCTSTR ElementName);
	BOOL GetCanSurround(LPCTSTR ElementName);
	BOOL GetCanPaste(LPCTSTR String, BOOL interpret);
	BOOL GetIsValid();
	void MoveToDocumentStart();
	void MoveToDocumentEnd();
	void SelectAll();
	BOOL ExtendTo(LPDISPATCH Selection);
	BOOL GetContains(LPDISPATCH Selection, BOOL IncludeSelOnEdge);
	BOOL GetIsEqual(LPDISPATCH Selection);
	BOOL GetOverlaps(LPDISPATCH Selection);
	BOOL MoveToElement(LPCTSTR ElementName, BOOL Forward);
	BOOL GetCanInsertText();
	void InsertProcessingInstruction();
	LPDISPATCH GetDocument();
	BOOL GetIsAdjacent(LPDISPATCH Selection);
	BOOL GetIsLessThan(LPDISPATCH Selection, BOOL OrEqual);
	BOOL GetIsGreaterThan(LPDISPATCH Selection, BOOL OrEqual);
	BOOL GetHasAttribute(LPCTSTR attrName);
	void InsertCALSTable(long NumRows, long NumCols, LPCTSTR TableElement, BOOL WantTHead, BOOL WantTFoot);
	void InsertWithTemplate(LPCTSTR ElementName);
	void InsertCDATASection();
	void Validate();
	void InsertReplaceableText(LPCTSTR Text);
	void ContractCell(long ContractDirection);
	BOOL GetReadOnlyContainer();
	void SetReadOnlyContainer(BOOL bNewValue);
	BOOL GetReadOnly();
	void Select();
	LPDISPATCH GetDuplicate();
	BOOL Layout();
	BOOL GetCollapsedContainerTags();
	void SetCollapsedContainerTags(BOOL bNewValue);
	BOOL GetCollapsedTags();
	BOOL GetCanDelete();
	BOOL GetCanRemoveContainerTags();
	BOOL GetHiddenContainer();
	void SetHiddenContainer(BOOL bNewValue);
	BOOL GetHidden();
	CString GetContainerStyle();
	void SetContainerStyle(LPCTSTR lpszNewValue);
	BOOL FindInsertLocation(LPCTSTR ElementName, BOOL Forward);
	void DropFile(LPCTSTR FileName);
	BOOL GetSVCollapsedContainer();
	void SetSVCollapsedContainer(BOOL bNewValue);
	void TypeTab(BOOL shift);
	void ToggleInline(LPCTSTR ElementName);
	BOOL GetCanSplitContainer(LPCTSTR ElementName);
	BOOL GetCanJoinElementToPreceding();
	void SplitToElementType(LPCTSTR ElementName);
	CString GetStyleElement();
	void SetStyleElement(LPCTSTR lpszNewValue);
	BOOL GetNonRemovableContainer();
	void SetNonRemovableContainer(BOOL bNewValue);
	BOOL FindPasteLocation(LPCTSTR String, BOOL Forward);
	BOOL GetWritePermittedContainer();
	void SetWritePermittedContainer(BOOL bNewValue);
	void PasteStringAsText(LPCTSTR String);
	BOOL GetInContextOfType(LPCTSTR ContextType);
};
/////////////////////////////////////////////////////////////////////////////
// Selection wrapper class

class Selection : public COleDispatchDriver
{
public:
	Selection() {}		// Calls COleDispatchDriver default constructor
	Selection(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Selection(const Selection& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void TypeText(LPCTSTR Text);
	void Cut();
	void Copy();
	void Paste();
	void Delete();
	void MoveLeft(long MovementType);
	void MoveRight(long MovementType);
	void MoveUp(long MovementType);
	void MoveDown(long MovementType);
	void MoveColumnLeft();
	void MoveColumnRight();
	void MoveRowUp();
	void MoveRowDown();
	void MergeCellLeft();
	void MergeCellRight();
	void MergeCellUp();
	void MergeCellDown();
	void SplitCellColumn();
	void SplitCellRow();
	void InsertRowsAbove(long number);
	void InsertRowsBelow(long number);
	void InsertColumnsLeft(long number);
	void InsertColumnsRight(long number);
	void HomeKey(long unit, long extend);
	void EndKey(long unit, long extend);
	LPDISPATCH GetFont();
	long GetHorizontalAlignment();
	void SetHorizontalAlignment(long nNewValue);
	void GotoNext(long GotoItem);
	void GotoPrevious(long GotoItem);
	void Collapse(long CollapseDirection);
	void PasteString(LPCTSTR String);
	void InsertForm(long FormElement);
	void InsertElement(LPCTSTR ElementName);
	void InsertElementWithRequired(LPCTSTR ElementName);
	CString GetContainerName();
	void SetContainerName(LPCTSTR lpszNewValue);
	void RemoveContainerTags();
	void SplitContainer();
	CString GetContainerAttribute(LPCTSTR attrName);
	void SetContainerAttribute(LPCTSTR attrName, LPCTSTR lpszNewValue);
	void InsertComment();
	void InsertBreak();
	void InsertHorizontalRule();
	void InsertNBSP();
	void JoinElementToPreceding();
	void InsertEntity(LPCTSTR EntityName);
	void Surround(LPCTSTR ElementName);
	void SelectElement();
	void TypingSplit();
	void DeleteColumn();
	void DeleteRow();
	void InsertTable(long NumRows, long NumCols, LPCTSTR BGColor, LPCTSTR TableWidth, LPCTSTR TableWidthUnit, LPCTSTR TableBorder, LPCTSTR CellPadding, LPCTSTR CellSpacing);
	void InsertCaption();
	void Indent();
	void Outdent();
	void InsertImage(LPCTSTR Src, LPCTSTR Alt, LPCTSTR Align, LPCTSTR Width, LPCTSTR Height, LPCTSTR Border);
	CString GetStyle();
	void SetStyle(LPCTSTR lpszNewValue);
	void PageUp();
	void PageDown();
	void ToggleTableCellType();
	CString GetElementName(long AncestorNum);
	CString GetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum);
	void SetElementAttribute(LPCTSTR attrName, LPCTSTR ElementName, long SkipNum, LPCTSTR lpszNewValue);
	BOOL GetIsParentElement(LPCTSTR ElementName);
	void ListIndent(VARIANT* ElementName);
	void ListOutdent(VARIANT* ElementName);
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	BOOL GetIsInsertionPoint();
	void InsertLink(LPCTSTR Href, LPCTSTR target);
	LPDISPATCH GetContainerNode();
	void SelectBeforeNode(LPDISPATCH node);
	void SelectAfterNode(LPDISPATCH node);
	void SelectNodeContents(LPDISPATCH node);
	void SelectAfterContainer();
	void SelectBeforeContainer();
	void SelectContainerContents();
	LPDISPATCH GetFind();
	void BasicPaste();
	void PasteStringWithInterpret(LPCTSTR String);
	BOOL GetCanInsert(LPCTSTR ElementName);
	BOOL GetCanChange(LPCTSTR ElementName);
	BOOL GetCanSurround(LPCTSTR ElementName);
	BOOL GetCanPaste(LPCTSTR String, BOOL interpret);
	BOOL GetIsValid();
	void MoveToDocumentStart();
	void MoveToDocumentEnd();
	void SelectAll();
	BOOL ExtendTo(LPDISPATCH Selection);
	BOOL GetContains(LPDISPATCH Selection, BOOL IncludeSelOnEdge);
	BOOL GetIsEqual(LPDISPATCH Selection);
	BOOL GetOverlaps(LPDISPATCH Selection);
	BOOL MoveToElement(LPCTSTR ElementName, BOOL Forward);
	BOOL GetCanInsertText();
	void InsertProcessingInstruction();
	LPDISPATCH GetDocument();
	BOOL GetIsAdjacent(LPDISPATCH Selection);
	BOOL GetIsLessThan(LPDISPATCH Selection, BOOL OrEqual);
	BOOL GetIsGreaterThan(LPDISPATCH Selection, BOOL OrEqual);
	BOOL GetHasAttribute(LPCTSTR attrName);
	void InsertCALSTable(long NumRows, long NumCols, LPCTSTR TableElement, BOOL WantTHead, BOOL WantTFoot);
	void InsertWithTemplate(LPCTSTR ElementName);
	void InsertCDATASection();
	void Validate();
	void InsertReplaceableText(LPCTSTR Text);
	void ContractCell(long ContractDirection);
	BOOL GetReadOnlyContainer();
	void SetReadOnlyContainer(BOOL bNewValue);
	BOOL GetReadOnly();
	void Select();
	LPDISPATCH GetDuplicate();
	BOOL Layout();
	BOOL GetCollapsedContainerTags();
	void SetCollapsedContainerTags(BOOL bNewValue);
	BOOL GetCollapsedTags();
	BOOL GetCanDelete();
	BOOL GetCanRemoveContainerTags();
	BOOL GetHiddenContainer();
	void SetHiddenContainer(BOOL bNewValue);
	BOOL GetHidden();
	CString GetContainerStyle();
	void SetContainerStyle(LPCTSTR lpszNewValue);
	BOOL FindInsertLocation(LPCTSTR ElementName, BOOL Forward);
	void DropFile(LPCTSTR FileName);
	BOOL GetSVCollapsedContainer();
	void SetSVCollapsedContainer(BOOL bNewValue);
	void TypeTab(BOOL shift);
	void ToggleInline(LPCTSTR ElementName);
	BOOL GetCanSplitContainer(LPCTSTR ElementName);
	BOOL GetCanJoinElementToPreceding();
	void SplitToElementType(LPCTSTR ElementName);
	CString GetStyleElement();
	void SetStyleElement(LPCTSTR lpszNewValue);
	BOOL GetNonRemovableContainer();
	void SetNonRemovableContainer(BOOL bNewValue);
	BOOL FindPasteLocation(LPCTSTR String, BOOL Forward);
	BOOL GetWritePermittedContainer();
	void SetWritePermittedContainer(BOOL bNewValue);
	void PasteStringAsText(LPCTSTR String);
	BOOL GetInContextOfType(LPCTSTR ContextType);
};
/////////////////////////////////////////////////////////////////////////////
// Font wrapper class

class Font : public COleDispatchDriver
{
public:
	Font() {}		// Calls COleDispatchDriver default constructor
	Font(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Font(const Font& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetBold();
	void SetBold(long nNewValue);
	long GetItalic();
	void SetItalic(long nNewValue);
	long GetUnderline();
	void SetUnderline(long nNewValue);
	long GetStrong();
	void SetStrong(long nNewValue);
	long GetEmphasis();
	void SetEmphasis(long nNewValue);
	long GetTeletype();
	void SetTeletype(long nNewValue);
	long GetCitation();
	void SetCitation(long nNewValue);
	CString GetSize();
	void SetSize(LPCTSTR lpszNewValue);
	CString GetColor();
	void SetColor(LPCTSTR lpszNewValue);
	void Grow();
	void Shrink();
};
/////////////////////////////////////////////////////////////////////////////
// Find wrapper class

class Find : public COleDispatchDriver
{
public:
	Find() {}		// Calls COleDispatchDriver default constructor
	Find(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Find(const Find& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL Execute(LPCTSTR FindString, LPCTSTR ReplaceString, LPCTSTR ConstraintString, BOOL MatchCase, BOOL MatchWholeWords, BOOL MatchPatterns, BOOL Forward, BOOL Wrap, long action, BOOL SetFindDialogOptions);
};
/////////////////////////////////////////////////////////////////////////////
// DocumentProperties wrapper class

class DocumentProperties : public COleDispatchDriver
{
public:
	DocumentProperties() {}		// Calls COleDispatchDriver default constructor
	DocumentProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentProperties(const DocumentProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH item(VARIANT* index);
	long GetCount();
	void Add(LPCTSTR name, LPCTSTR value);
};
/////////////////////////////////////////////////////////////////////////////
// DocumentProperty wrapper class

class DocumentProperty : public COleDispatchDriver
{
public:
	DocumentProperty() {}		// Calls COleDispatchDriver default constructor
	DocumentProperty(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentProperty(const DocumentProperty& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetValue();
	void SetValue(LPCTSTR lpszNewValue);
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// DOMCharacterReference wrapper class

class DOMCharacterReference : public COleDispatchDriver
{
public:
	DOMCharacterReference() {}		// Calls COleDispatchDriver default constructor
	DOMCharacterReference(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCharacterReference(const DOMCharacterReference& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
};
/////////////////////////////////////////////////////////////////////////////
// NameVariantProperties wrapper class

class NameVariantProperties : public COleDispatchDriver
{
public:
	NameVariantProperties() {}		// Calls COleDispatchDriver default constructor
	NameVariantProperties(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	NameVariantProperties(const NameVariantProperties& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH item(VARIANT* index);
	long GetCount();
	void Add(LPCTSTR name, const VARIANT& value);
};
/////////////////////////////////////////////////////////////////////////////
// NameVariantProperty wrapper class

class NameVariantProperty : public COleDispatchDriver
{
public:
	NameVariantProperty() {}		// Calls COleDispatchDriver default constructor
	NameVariantProperty(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	NameVariantProperty(const NameVariantProperty& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	VARIANT GetValue();
	void Delete();
};
/////////////////////////////////////////////////////////////////////////////
// StyleSheetList wrapper class

class StyleSheetList : public COleDispatchDriver
{
public:
	StyleSheetList() {}		// Calls COleDispatchDriver default constructor
	StyleSheetList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	StyleSheetList(const StyleSheetList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetLength();
	LPDISPATCH item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleSheet wrapper class

class DOMCSSStyleSheet : public COleDispatchDriver
{
public:
	DOMCSSStyleSheet() {}		// Calls COleDispatchDriver default constructor
	DOMCSSStyleSheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSStyleSheet(const DOMCSSStyleSheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetType();
	BOOL GetDisabled();
	void SetDisabled(BOOL bNewValue);
	LPDISPATCH GetOwnerNode();
	LPDISPATCH GetParentStyleSheet();
	CString GetHref();
	CString GetTitle();
	LPDISPATCH GetMedia();
	LPDISPATCH GetOwnerRule();
	LPDISPATCH GetCssRules();
	long insertRule(LPCTSTR rule, long index);
	void deleteRule(long index);
};
/////////////////////////////////////////////////////////////////////////////
// StyleSheet wrapper class

class StyleSheet : public COleDispatchDriver
{
public:
	StyleSheet() {}		// Calls COleDispatchDriver default constructor
	StyleSheet(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	StyleSheet(const StyleSheet& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetType();
	BOOL GetDisabled();
	void SetDisabled(BOOL bNewValue);
	LPDISPATCH GetOwnerNode();
	LPDISPATCH GetParentStyleSheet();
	CString GetHref();
	CString GetTitle();
	LPDISPATCH GetMedia();
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSRule wrapper class

class DOMCSSRule : public COleDispatchDriver
{
public:
	DOMCSSRule() {}		// Calls COleDispatchDriver default constructor
	DOMCSSRule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSRule(const DOMCSSRule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short GetType();
	CString GetCssText();
	void SetCssText(LPCTSTR lpszNewValue);
	LPDISPATCH GetParentStyleSheet();
	LPDISPATCH GetParentRule();
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSRuleList wrapper class

class DOMCSSRuleList : public COleDispatchDriver
{
public:
	DOMCSSRuleList() {}		// Calls COleDispatchDriver default constructor
	DOMCSSRuleList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSRuleList(const DOMCSSRuleList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetLength();
	LPDISPATCH item(long index);
};
/////////////////////////////////////////////////////////////////////////////
// Customizations wrapper class

class Customizations : public COleDispatchDriver
{
public:
	Customizations() {}		// Calls COleDispatchDriver default constructor
	Customizations(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Customizations(const Customizations& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParagraphs();
	LPDISPATCH GetLists();
	LPDISPATCH GetImages();
	LPDISPATCH GetTogglingElements();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraphs wrapper class

class TreatAsParagraphs : public COleDispatchDriver
{
public:
	TreatAsParagraphs() {}		// Calls COleDispatchDriver default constructor
	TreatAsParagraphs(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsParagraphs(const TreatAsParagraphs& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsParagraph wrapper class

class TreatAsParagraph : public COleDispatchDriver
{
public:
	TreatAsParagraph() {}		// Calls COleDispatchDriver default constructor
	TreatAsParagraph(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsParagraph(const TreatAsParagraph& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetParent();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsLists wrapper class

class TreatAsLists : public COleDispatchDriver
{
public:
	TreatAsLists() {}		// Calls COleDispatchDriver default constructor
	TreatAsLists(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsLists(const TreatAsLists& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsList wrapper class

class TreatAsList : public COleDispatchDriver
{
public:
	TreatAsList() {}		// Calls COleDispatchDriver default constructor
	TreatAsList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsList(const TreatAsList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	long GetType();
	CString GetListHeader();
	CString GetListItem();
	CString GetTerm();
	CString GetDefinition();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsImages wrapper class

class TreatAsImages : public COleDispatchDriver
{
public:
	TreatAsImages() {}		// Calls COleDispatchDriver default constructor
	TreatAsImages(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsImages(const TreatAsImages& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetCount();
};
/////////////////////////////////////////////////////////////////////////////
// TreatAsImage wrapper class

class TreatAsImage : public COleDispatchDriver
{
public:
	TreatAsImage() {}		// Calls COleDispatchDriver default constructor
	TreatAsImage(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TreatAsImage(const TreatAsImage& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetSource();
	CString GetHeight();
	CString GetWidth();
	CString GetAltText();
};
/////////////////////////////////////////////////////////////////////////////
// TogglingElements wrapper class

class TogglingElements : public COleDispatchDriver
{
public:
	TogglingElements() {}		// Calls COleDispatchDriver default constructor
	TogglingElements(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TogglingElements(const TogglingElements& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetItem(long index);
	long GetCount();
	CString GetBold();
	CString GetItalic();
	CString GetUnderline();
};
/////////////////////////////////////////////////////////////////////////////
// TogglingElement wrapper class

class TogglingElement : public COleDispatchDriver
{
public:
	TogglingElement() {}		// Calls COleDispatchDriver default constructor
	TogglingElement(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	TogglingElement(const TogglingElement& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetMacroName();
};
/////////////////////////////////////////////////////////////////////////////
// FX wrapper class

class FX : public COleDispatchDriver
{
public:
	FX() {}		// Calls COleDispatchDriver default constructor
	FX(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	FX(const FX& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL CopyFile(LPCTSTR SrcFile, LPCTSTR DstFile, VARIANT* ForceUpdate);
	BOOL ShowDialog(LPCTSTR dialogName);
	BOOL setAttribute(LPCTSTR ElementName, LPCTSTR AttributeName, LPCTSTR AttributeValue, LPCTSTR Relative);
	BOOL RemoveAll(LPCTSTR ElementName);
	BOOL DTC(LPCTSTR Guid);
	BOOL HTML(VARIANT* HTMLSrc, VARIANT* SrcFile, VARIANT* ElementName, VARIANT* ElementID, VARIANT* location, VARIANT* LeaveSelected);
	BOOL Surround(LPCTSTR Before, LPCTSTR After, VARIANT* LeaveSelected);
	CString GetPath();
	BOOL SelectDropPoint();
};
/////////////////////////////////////////////////////////////////////////////
// _Global wrapper class

class _Global : public COleDispatchDriver
{
public:
	_Global() {}		// Calls COleDispatchDriver default constructor
	_Global(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Global(const _Global& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetDocuments();
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetSelection();
	LPDISPATCH GetResourceManager();
};
/////////////////////////////////////////////////////////////////////////////
// _Application wrapper class

class _Application : public COleDispatchDriver
{
public:
	_Application() {}		// Calls COleDispatchDriver default constructor
	_Application(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_Application(const _Application& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetApplication();
	LPDISPATCH GetDocuments();
	LPDISPATCH GetActiveDocument();
	LPDISPATCH GetSelection();
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	void Quit(long SaveChanges);
	void Help(long HelpType, long ContextID);
	void Run(LPCTSTR MacroName);
	CString GetProjectDirectory();
	LPDISPATCH GetFx();
	CString GetPath();
	CString PathToURL(LPCTSTR Path, VARIANT* Base);
	CString URLToPath(LPCTSTR URL, VARIANT* Base);
	CString UniqueFileName(LPCTSTR Directory, LPCTSTR Prefix, VARIANT* Extension);
	BOOL FileExists(LPCTSTR Path);
	BOOL ReadableFileExists(LPCTSTR Path);
	BOOL WritableFileExists(LPCTSTR Path);
	BOOL WritableDirExists(LPCTSTR Path);
	CString FileToString(LPCTSTR Path);
	void Alert(LPCTSTR Msg, VARIANT* Title);
	BOOL Confirm(LPCTSTR Msg, VARIANT* Title);
	CString Prompt(LPCTSTR Msg, VARIANT* Text, VARIANT* length, VARIANT* MaxLength, VARIANT* Title);
	long MessageBox(LPCTSTR Msg, long Btns, VARIANT* Title);
	long NoticeBox(LPCTSTR Msg, LPCTSTR Btn1, VARIANT* Btn2, VARIANT* Btn3, VARIANT* Title);
	LPDISPATCH GetCommandBars();
	long GetWindowHandle();
	void EnableModeless(BOOL prop);
	void HelpFinder(LPCTSTR HelpFile);
	void HelpContext(LPCTSTR HelpFile, long ContextID);
	void RefreshMacros();
	void RunKeyedMacro(LPCTSTR KeyString);
	LPDISPATCH GetDropPoint();
	void DisableMacro(LPCTSTR MacroName);
	CString GetMacroFile();
	void Beep();
	CString GetAssetsPath();
	void DisablePlainTextView();
	BOOL GetIsDocumentOpen(LPDISPATCH Document);
	BOOL CopyAssetFile(LPCTSTR SrcFile, LPCTSTR DstFile, BOOL ForceUpdate);
	void ShowPage(LPCTSTR URL);
	long GetDisplayAlerts();
	void SetDisplayAlerts(long nNewValue);
	LPDISPATCH GetActiveInPlaceControl();
	LPDISPATCH GetMouseOverNode();
	void SetCursor(long cursorType);
	void SetStatusText(LPCTSTR statusText);
	void AppendMacro(LPCTSTR Label, LPCTSTR MacroName);
	LPDISPATCH GetCustomProperties();
	LPDISPATCH GetNewDocumentType();
	long GetDropFileCount();
	CString GetDropFileName(long index);
	BOOL GetInitComplete();
	LPDISPATCH GetResourceManager();
	void PreventExit(LPCTSTR appName, LPCTSTR msgText);
	void AllowExit(LPCTSTR appName);
	LPUNKNOWN GetDropDataObject();
	BOOL AcceptDropFormat(VARIANT* dropFormat, LPCTSTR formatName);
	void EmptyClipboard();
	long GetMakeFaceId(LPCTSTR groupName, long rowNum, long iconNum);
	void HideViewModeButton(long vtButton);
	void HideMiniContext();
	void HideStructureView();
	void HideStatusBarPane(long pane);
	void SetWorkbookMode(BOOL modeOn);
	void DisableToolbarContextMenu();
	void DisableDocumentContextMenu();
	BOOL GetUnicodeSupported();
	CString GetResolveURL();
	void SetResolveURL(LPCTSTR lpszNewValue);
	LPDISPATCH GetResolveEntityInfo();
	BOOL GetValidationSuccess();
	void SetValidationSuccess(BOOL bNewValue);
	void StopValidation();
	void PushInMacro(LPCTSTR MacroName);
	LPDISPATCH GetStyleElements();
	CString GetStyleElementName();
	CString GetStyleElementType();
	void HideSplashDialog();
	LPDISPATCH GetClipboard();
	CString GetDropText();
	void SetDropText(LPCTSTR lpszNewValue);
	BOOL GetDropClipboardText();
	BOOL GetDropInternalText();
	void MoveDropPoint(LPDISPATCH newDropPoint);
	LPDISPATCH GetDropRange();
	LPDISPATCH GetAttributeInspector();
	void DropNotAllowed();
	void AddChangedNodeKey(LPCTSTR key);
	void RemoveChangedNodeKey(LPCTSTR key);
	CString GetAllUsersMacroFile();
	CString GetCurrentUserMacroFile();
	LPDISPATCH GetCheckData();
	VARIANT CreateFormDlg(LPCTSTR formFileName, VARIANT* DOMNode);
	LPDISPATCH GetElementList();
	CString DataObjectAsText(LPCTSTR formatName, LPUNKNOWN data);
	LPDISPATCH GetActiveContextMenu();
};
/////////////////////////////////////////////////////////////////////////////
// Documents wrapper class

class Documents : public COleDispatchDriver
{
public:
	Documents() {}		// Calls COleDispatchDriver default constructor
	Documents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Documents(const Documents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH item(VARIANT* index);
	long GetCount();
	LPDISPATCH Open(LPCTSTR FileName, long ViewType);
	LPDISPATCH Add(BOOL UseDefaultTemplate);
	void Save();
	void Close();
	LPDISPATCH OpenTemplate(LPCTSTR FileName);
	LPDISPATCH OpenString(LPCTSTR inputString, long ViewType, LPCTSTR FileName, BOOL asTemplate, BOOL IsXML, BOOL wfEdit);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBars wrapper class

class CommandBars : public COleDispatchDriver
{
public:
	CommandBars() {}		// Calls COleDispatchDriver default constructor
	CommandBars(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBars(const CommandBars& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Add(LPCTSTR name, VARIANT* positon);
	LPDISPATCH FindControl(long type, long cmdId, VARIANT* Visible, VARIANT* recursive);
	long GetCount();
	LPDISPATCH GetItem(const VARIANT& index);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBar wrapper class

class CommandBar : public COleDispatchDriver
{
public:
	CommandBar() {}		// Calls COleDispatchDriver default constructor
	CommandBar(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBar(const CommandBar& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Delete();
	void Reset();
	LPDISPATCH FindControl(long type, long cmdId, VARIANT* Visible, VARIANT* recursive);
	BOOL GetBuiltIn();
	LPDISPATCH GetControls();
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	long GetPosition();
	void SetPosition(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	BOOL GetReadOnly();
	void SetReadOnly(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarControl wrapper class

class CommandBarControl : public COleDispatchDriver
{
public:
	CommandBarControl() {}		// Calls COleDispatchDriver default constructor
	CommandBarControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarControl(const CommandBarControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Copy(VARIANT* toBar, VARIANT* Before);
	void Delete();
	void Execute();
	void Move(VARIANT* toBar, VARIANT* Before);
	void Reset();
	BOOL GetBuiltIn();
	long GetId();
	long GetType();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	VARIANT GetDescriptionText();
	void SetDescriptionText(const VARIANT& newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT& newValue);
	long GetState();
	void SetState(long nNewValue);
	VARIANT GetTooltipText();
	void SetTooltipText(const VARIANT& newValue);
	long GetTop();
	void SetTop(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarControls wrapper class

class CommandBarControls : public COleDispatchDriver
{
public:
	CommandBarControls() {}		// Calls COleDispatchDriver default constructor
	CommandBarControls(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarControls(const CommandBarControls& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH Add(long controlType, VARIANT* commandId, VARIANT* Before, VARIANT* param);
	long GetCount();
	LPDISPATCH GetItem(const VARIANT& index);
};
/////////////////////////////////////////////////////////////////////////////
// InPlaceControl wrapper class

class InPlaceControl : public COleDispatchDriver
{
public:
	InPlaceControl() {}		// Calls COleDispatchDriver default constructor
	InPlaceControl(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	InPlaceControl(const InPlaceControl& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetDocument();
	LPDISPATCH GetNode();
	CString GetUserData();
	VARIANT GetControl();
	BOOL GetUserMovedIntoControl();
	BOOL GetUpdateFromDocument();
	VARIANT GetNextEventParam();
	void SetShouldCreate(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// _ResourceManager wrapper class

class _ResourceManager : public COleDispatchDriver
{
public:
	_ResourceManager() {}		// Calls COleDispatchDriver default constructor
	_ResourceManager(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	_ResourceManager(const _ResourceManager& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetAssets();
	LPDISPATCH GetDesktop();
	LPDISPATCH GetFtpNeighborhood();
	LPDISPATCH GetLocalSites();
	void AddTab(LPCTSTR tabName, LPCTSTR Guid);
	void SelectTab(LPCTSTR tabName);
	void RemoveTab(LPCTSTR tabName);
	void RemoveAllTabs();
	LPDISPATCH GetControlInTab(LPCTSTR tabName);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// Assets wrapper class

class Assets : public COleDispatchDriver
{
public:
	Assets() {}		// Calls COleDispatchDriver default constructor
	Assets(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Assets(const Assets& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetWebBrowser();
	void SelectFolder(LPCTSTR Path);
	void Refresh();
};
/////////////////////////////////////////////////////////////////////////////
// ResolveEntityInfo wrapper class

class ResolveEntityInfo : public COleDispatchDriver
{
public:
	ResolveEntityInfo() {}		// Calls COleDispatchDriver default constructor
	ResolveEntityInfo(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ResolveEntityInfo(const ResolveEntityInfo& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	void SetName(LPCTSTR lpszNewValue);
	CString GetPublicId();
	void SetPublicId(LPCTSTR lpszNewValue);
	CString GetSystemId();
	void SetSystemId(LPCTSTR lpszNewValue);
	CString GetBasePath();
	void SetBasePath(LPCTSTR lpszNewValue);
	CString GetFileName();
	void SetFileName(LPCTSTR lpszNewValue);
	BOOL IsDocType();
};
/////////////////////////////////////////////////////////////////////////////
// StyleElements wrapper class

class StyleElements : public COleDispatchDriver
{
public:
	StyleElements() {}		// Calls COleDispatchDriver default constructor
	StyleElements(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	StyleElements(const StyleElements& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	long GetCount();
	CString item(long index);
	long Insert(long index, LPCTSTR name);
};
/////////////////////////////////////////////////////////////////////////////
// Clipboard wrapper class

class Clipboard : public COleDispatchDriver
{
public:
	Clipboard() {}		// Calls COleDispatchDriver default constructor
	Clipboard(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	Clipboard(const Clipboard& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetText();
	void SetText(LPCTSTR lpszNewValue);
	CString FirstFormatName();
	CString NextFormatName();
	LPUNKNOWN GetDataObject();
	void SetEmpty();
	BOOL GetHasText();
	BOOL GetHasFile();
	BOOL GetHasFormat(VARIANT* format);
};
/////////////////////////////////////////////////////////////////////////////
// AttributeInspector wrapper class

class AttributeInspector : public COleDispatchDriver
{
public:
	AttributeInspector() {}		// Calls COleDispatchDriver default constructor
	AttributeInspector(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	AttributeInspector(const AttributeInspector& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetElement();
	CString GetAttributeName();
	CString GetAttributeValueBeforeChange();
	CString GetAttributeValueAfterChange();
	void SetAttributeValueAfterChange(LPCTSTR lpszNewValue);
	void CancelChange();
};
/////////////////////////////////////////////////////////////////////////////
// CheckData wrapper class

class CheckData : public COleDispatchDriver
{
public:
	CheckData() {}		// Calls COleDispatchDriver default constructor
	CheckData(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CheckData(const CheckData& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetElement();
	CString GetAttributeName();
	CString GetValue();
	CString GetValidationMsg();
	void SetValidationMsg(LPCTSTR lpszNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ElementList wrapper class

class ElementList : public COleDispatchDriver
{
public:
	ElementList() {}		// Calls COleDispatchDriver default constructor
	ElementList(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ElementList(const ElementList& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	LPDISPATCH GetItem(VARIANT* index);
	long GetCount();
	LPDISPATCH InsertItem(LPCTSTR name, LPCTSTR description, long index);
	LPDISPATCH InsertSortedItem(LPCTSTR name, LPCTSTR description);
	void RemoveItem(VARIANT* index);
	void RemoveAllItems();
	CString GetTabName();
	void SetTabName(LPCTSTR lpszNewValue);
	CString GetSelectedName();
	BOOL GetIsInsert();
	void SetIsInsert(BOOL bNewValue);
	void SelectTab(LPCTSTR tabName);
	CString GetNameToSelect();
	void SetNameToSelect(LPCTSTR lpszNewValue);
	void AddTab(LPCTSTR tabName);
	void RemoveTab(LPCTSTR tabName);
};
/////////////////////////////////////////////////////////////////////////////
// ElementListItem wrapper class

class ElementListItem : public COleDispatchDriver
{
public:
	ElementListItem() {}		// Calls COleDispatchDriver default constructor
	ElementListItem(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ElementListItem(const ElementListItem& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetName();
	CString GetDescription();
	void SetDescription(LPCTSTR lpszNewValue);
	BOOL GetRequired();
	void SetRequired(BOOL bNewValue);
	long GetUsageCount();
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarPopup wrapper class

class CommandBarPopup : public COleDispatchDriver
{
public:
	CommandBarPopup() {}		// Calls COleDispatchDriver default constructor
	CommandBarPopup(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarPopup(const CommandBarPopup& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Copy(VARIANT* toBar, VARIANT* Before);
	void Delete();
	void Execute();
	void Move(VARIANT* toBar, VARIANT* Before);
	void Reset();
	BOOL GetBuiltIn();
	long GetId();
	long GetType();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	VARIANT GetDescriptionText();
	void SetDescriptionText(const VARIANT& newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT& newValue);
	long GetState();
	void SetState(long nNewValue);
	VARIANT GetTooltipText();
	void SetTooltipText(const VARIANT& newValue);
	long GetTop();
	void SetTop(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	void CopyFace();
	void PasteFace();
	BOOL GetBuiltInFace();
	void SetBuiltInFace(BOOL bNewValue);
	CString GetCaption();
	void SetCaption(LPCTSTR lpszNewValue);
	LPDISPATCH GetControls();
	long GetFaceId();
	void SetFaceId(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// ApplicationEvents wrapper class

class ApplicationEvents : public COleDispatchDriver
{
public:
	ApplicationEvents() {}		// Calls COleDispatchDriver default constructor
	ApplicationEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	ApplicationEvents(const ApplicationEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void SelectionChanged();
	void DocumentChanged();
	void Quit();
};
/////////////////////////////////////////////////////////////////////////////
// DocumentEvents wrapper class

class DocumentEvents : public COleDispatchDriver
{
public:
	DocumentEvents() {}		// Calls COleDispatchDriver default constructor
	DocumentEvents(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DocumentEvents(const DocumentEvents& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void New();
	void Open();
	void Close();
};
/////////////////////////////////////////////////////////////////////////////
// DOMEntity wrapper class

class DOMEntity : public COleDispatchDriver
{
public:
	DOMEntity() {}		// Calls COleDispatchDriver default constructor
	DOMEntity(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMEntity(const DOMEntity& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetPublicId();
	CString GetSystemId();
	CString GetNotationName();
};
/////////////////////////////////////////////////////////////////////////////
// DOMNotation wrapper class

class DOMNotation : public COleDispatchDriver
{
public:
	DOMNotation() {}		// Calls COleDispatchDriver default constructor
	DOMNotation(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMNotation(const DOMNotation& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	LPDISPATCH GetParentNode();
	short GetNodeType();
	CString GetNodeName();
	CString GetNodeValue();
	void SetNodeValue(LPCTSTR lpszNewValue);
	LPDISPATCH GetFirstChild();
	LPDISPATCH GetLastChild();
	LPDISPATCH GetNextSibling();
	LPDISPATCH GetPreviousSibling();
	BOOL hasChildNodes();
	LPDISPATCH replaceChild(LPDISPATCH newChild, LPDISPATCH oldChild);
	LPDISPATCH insertBefore(LPDISPATCH newNode, const VARIANT& refNode);
	LPDISPATCH removeChild(LPDISPATCH child);
	LPDISPATCH appendChild(LPDISPATCH child);
	LPDISPATCH GetOwnerDocument();
	LPDISPATCH GetChildNodes();
	LPDISPATCH GetAttributes();
	LPDISPATCH cloneNode(BOOL deep);
	CString GetPublicId();
	CString GetSystemId();
};
/////////////////////////////////////////////////////////////////////////////
// CommandBarButton wrapper class

class CommandBarButton : public COleDispatchDriver
{
public:
	CommandBarButton() {}		// Calls COleDispatchDriver default constructor
	CommandBarButton(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	CommandBarButton(const CommandBarButton& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	void Copy(VARIANT* toBar, VARIANT* Before);
	void Delete();
	void Execute();
	void Move(VARIANT* toBar, VARIANT* Before);
	void Reset();
	BOOL GetBuiltIn();
	long GetId();
	long GetType();
	BOOL GetBeginGroup();
	void SetBeginGroup(BOOL bNewValue);
	VARIANT GetDescriptionText();
	void SetDescriptionText(const VARIANT& newValue);
	BOOL GetEnabled();
	void SetEnabled(BOOL bNewValue);
	long GetHeight();
	void SetHeight(long nNewValue);
	long GetLeft();
	void SetLeft(long nNewValue);
	VARIANT GetOnAction();
	void SetOnAction(const VARIANT& newValue);
	long GetState();
	void SetState(long nNewValue);
	VARIANT GetTooltipText();
	void SetTooltipText(const VARIANT& newValue);
	long GetTop();
	void SetTop(long nNewValue);
	BOOL GetVisible();
	void SetVisible(BOOL bNewValue);
	long GetWidth();
	void SetWidth(long nNewValue);
	void CopyFace();
	void PasteFace();
	BOOL GetBuiltInFace();
	void SetBuiltInFace(BOOL bNewValue);
	long GetFaceId();
	void SetFaceId(long nNewValue);
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleRule wrapper class

class DOMCSSStyleRule : public COleDispatchDriver
{
public:
	DOMCSSStyleRule() {}		// Calls COleDispatchDriver default constructor
	DOMCSSStyleRule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSStyleRule(const DOMCSSStyleRule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short GetType();
	CString GetCssText();
	void SetCssText(LPCTSTR lpszNewValue);
	LPDISPATCH GetParentStyleSheet();
	LPDISPATCH GetParentRule();
	CString GetSelectorText();
	LPDISPATCH GetStyle();
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSStyleDeclaration wrapper class

class DOMCSSStyleDeclaration : public COleDispatchDriver
{
public:
	DOMCSSStyleDeclaration() {}		// Calls COleDispatchDriver default constructor
	DOMCSSStyleDeclaration(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSStyleDeclaration(const DOMCSSStyleDeclaration& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	CString GetCssText();
	void SetCssText(LPCTSTR lpszNewValue);
	CString getPropertyValue(LPCTSTR name);
	LPDISPATCH getPropertyCSSValue(LPCTSTR name);
	CString removeProperty(LPCTSTR name);
	CString getPropertyPriority(LPCTSTR name);
	void setProperty(LPCTSTR name, LPCTSTR value, LPCTSTR priority);
	long GetLength();
	CString item(long index);
	LPDISPATCH GetParentRule();
};
/////////////////////////////////////////////////////////////////////////////
// DOMCSSUnknownRule wrapper class

class DOMCSSUnknownRule : public COleDispatchDriver
{
public:
	DOMCSSUnknownRule() {}		// Calls COleDispatchDriver default constructor
	DOMCSSUnknownRule(LPDISPATCH pDispatch) : COleDispatchDriver(pDispatch) {}
	DOMCSSUnknownRule(const DOMCSSUnknownRule& dispatchSrc) : COleDispatchDriver(dispatchSrc) {}

// Attributes
public:

// Operations
public:
	short GetType();
	CString GetCssText();
	void SetCssText(LPCTSTR lpszNewValue);
	LPDISPATCH GetParentStyleSheet();
	LPDISPATCH GetParentRule();
};
