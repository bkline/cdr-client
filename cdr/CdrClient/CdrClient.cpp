/*
 * $Id: CdrClient.cpp,v 1.1.1.1 2005-11-08 21:30:20 bkline Exp $
 *
 * Ensures that the CDR client files are up-to-date, then launches XMetaL
 * with custom CDR DLL.  See documentation of the InitInstance method
 * (the entry point for a dialog-based application) below for an overview
 * of the processing logic.
 *
 * $Log: not supported by cvs2svn $
 */
#include "stdafx.h"
#include "CdrClient.h"
#include "CdrLogin.h"
#include <iostream>
#include <fstream>
#include <winsock.h>
#include <atlenc.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*
 * Wrapper class for CDR client commands.  This program only uses
 * this class for logging on to the CDR, so the complexity of
 * remembering and re-using the session string (obtained by the
 * logon command) for subsequent requests is omitted here.
 *
 * CDR client requests are sent as an XML document with the
 * following structure:
 *
 *   CdrCommandSet
 *     SessionId [optional, not present for the logon command]
 *     CdrCommand [multiple, only one used here]
 *       Cdr[CommandName]
 *         [content of command]
 *
 * The server's response has the following structure:
 *
 *   CdrResponseSet
 *     @Time [date-time]
 *     CdrResponse [optional, multiple, only one returned here]
 *       Cdr[NameOfCommand]Resp [CdrLogonResp here]
 *     Errors [optional]
 *       Err [multiple; only one sent when logon fails]
 */
class CdrSocket {

public:

    /*
     * Connects to the CDR server over the specified port.  Throws
     * an exception if the connection cannot be made.
     */
    CdrSocket(CdrClient* cdrClient,
              const CString& hostString, INTERNET_PORT port = 2019) 
        : connected(false), client(cdrClient) {

        client->log(_T("Creating socket connection to ") + hostString +
                    _T("\n"), 3);
        // Working variables.
        CString             logMessage;
        CStringA            ascii = (CStringA)hostString.GetString();
        CStringA::PCXSTR    host  = ascii.GetString();
        struct sockaddr_in  addr;
        struct hostent *    ph = gethostbyname(host);
        if (!ph)
            throw _T("CdrSocket(): Failure resolving host name ") + hostString;

        // Build the socket address.
        addr.sin_family = ph->h_addrtype;
        memcpy(&addr.sin_addr, ph->h_addr, ph->h_length);
        addr.sin_port = htons(port);

        // Create the socket.
        sock = (SOCKET)socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0)
            throw _T("CdrSocket(): Failure creating socket for") + hostString;

        // Connect to the server.
        if (connect(sock, (struct sockaddr *)&addr, sizeof addr) < 0)
            throw _T("CdrSocket(): Failure connecting to ") + hostString;
        logMessage.Format(_T("Connected to %s over port %d.\n"), hostString, 
                          port);
        client->log(logMessage, 3);
        connected = true;
    }

    /*
     * Conditionally cleans up by closing the socket.
     */
    ~CdrSocket() { 
        if (connected) {
            client->log(_T("Closing socket.\n"), 3);
            closesocket(sock); 
        }
    }

    /*
     * Packs up a CDR client request, sends it to the CDR server,
     * retrieves the server's response, and returns that response
     * to the caller.  Throws a string-based exception if an
     * error is encountered.
     */
    CString sendCommand(const CString& cmd) const {

        // Wrap the command in the command/set elements.
        CString request = _T("<CdrCommandSet><CdrCommand>") + cmd
                        + _T("</CdrCommand></CdrCommandSet>");
        client->log(_T("Sending command ") + request + _T("\n"), 3);

        // Tell the server the size of the coming request buffer.
        CStringA            ascii = (CStringA)request.GetString();
        CStringA::PCXSTR    buf   = ascii.GetString();
        long len = (long)htonl((u_long)request.GetLength());
        if (send(sock, (char *)&len, sizeof len, 0) < 0)
            throw _T("In sendCommand(): Failure sending command length");

        // Submit the command to the server.
        if (send(sock, buf, (int)request.GetLength(), 0) < 0)
            throw _T("In sendCommand(): Failure sending command");

        // Retrieve the server's response.
        return this->read();
    }

private:

    /*
     * Private method for reading the server's response.  Pulls out
     * the first four bytes, which are transmitted in network ("big
     * endian") order and indicate the number of bytes to follow.
     * Allocates a buffer to hold the response, reads the response
     * into the buffer, converts it to a CString object, and returns
     * that object.  Throws a string-based exception if anything
     * goes wrong.
     */
    CString read() const {

        // Find out how many bytes the response contains.  This solves the
        // "how do we know we're done?" problem.
        CString msg;
        char lengthBytes[4];
        if (readn(sizeof lengthBytes, lengthBytes) != sizeof lengthBytes)
            throw _T("Failure reading byte count from server");
        long length;
        memcpy(&length, lengthBytes, sizeof length);
        length = ntohl(length);
        msg.Format(_T("Read length bytes: %ld.\n"), length);
        client->log(msg, 3);

        // Use a local buffer type to ensure memory release even if an
        // exception occurs.
        struct Buf {
            Buf(size_t n) : buf(new char[n + 1]) { memset(buf, 0, n + 1); }
            ~Buf() { delete [] buf; }
            char* buf;
        };
        Buf b(length);
        if (readn(length, b.buf) != length)
            throw _T("Failure reading response from CDR server");

        CString response(b.buf);
        msg.Format(_T("Server response: %s\n"), response);
        client->log(msg, 3);
        return response;
    }

    /*
     * Common private code for reading a specified number of bytes into
     * a supplied buffer.  Used for reading the 4-byte length header,
     * as well as the payload for the server's response.  Returns the
     * number of bytes read, or -1 if an error occurs.
     */
    int readn(int nBytes, char* buf) const {

        // Read until we have all the bytes we've been promised.
        int recd = 0;
        while (recd < nBytes) {
            int n = recv(sock, buf + recd, nBytes - recd, 0);
            CString msg;
            msg.Format(_T("recv requested %d bytes; got %d.\n"),
                       nBytes - recd, n);
            client->log(msg, 4);
            if (n < 0)
                return -1;
            recd += n;
        }
        return recd;
    }

    /*
     * Private static object used to ensure that intialization and
     * cleanup are handled automatically, even if failures cause
     * an unexpectedly early end of the program.
     */
    struct Init {
        Init() {
            if (WSAStartup(0x0101, &wsaData) != 0) {
                AfxMessageBox(_T("Unable to initialize socket library"));
                throw _T("Failure initializing Windows socket library");
            }
        }
        ~Init() { WSACleanup(); }
        WSAData wsaData;
        static Init init;
    };
    SOCKET     sock;
    bool       connected;
    CdrClient* client;
};

// Ensures cleanup at shutdown time.
CdrSocket::Init CdrSocket::Init::init;

/*
 * Local utility functions.
 */
static CComPtr<IXMLDOMNode> getFirstChild(CComPtr<IXMLDOMNode>& node);
static CComPtr<IXMLDOMNode> getNextSibling(CComPtr<IXMLDOMNode>& node);
static CString getNodeName(CComPtr<IXMLDOMNode>& node);
static CString getTextContent(CComPtr<IXMLDOMNode>& element);
static CString getFileTimestamp(const CString& name);
static CString getAttribute(CComPtr<IXMLDOMNode>& elem, const TCHAR* name);
static CString extractErrorString(CComPtr<IXMLDOMNode>& node);
static CString findXmetalProgram();
static void usage();

/*
 * CdrClient class implementation.
 */
BEGIN_MESSAGE_MAP(CdrClient, CWinApp)
	ON_COMMAND(ID_HELP, CWinApp::OnHelp)
END_MESSAGE_MAP()

/*
 * Global object for the application.
 */
CdrClient theApp;

/*
 * CdrClient constructor.
 */
CdrClient::CdrClient() : loaderReplaced(false),
                         serverSettings(NULL),
                         dialog(NULL),
                         logger(NULL) {
    CoInitialize(NULL);
    xmlDomParser.CoCreateInstance(__uuidof(DOMDocument));
}

/*
 * Release our objects for server settings and the connection dialog,
 * and close down the COM mechanism.
 */
CdrClient::~CdrClient() {
    delete serverSettings;
    delete dialog;
    delete logger;
    xmlDomParser = NULL;
    CoUninitialize();
}

/*
 * Since this is a dialog-based application, the InitInstance() method
 * is the main entry point for the program's processing logic.
 *
 *   0. Invoke the base class's version of this method.
 *   1. Read the options from the application's settings file.
 *   2. Parse the command-line arguments.
 *   3. If we aren't already logged into the CDR, do it.
 *   4. Clear out files we don't want to keep.
 *   5. Install any new files from the server and delete obsolete files.
 *   6. If this program was replaced, launch the new version; otherwise
 *      register the CDR DLL and launch XMetaL.
 */
BOOL CdrClient::InitInstance() {

    try {

        // Create object for logging major events.
        logger = new LogFile();

        // Do this to get password mask characters to display as bullets.
        InitCommonControls();

        // 0. Invoke the base class's version of this method.
	    CWinApp::InitInstance();

        // 1. Read the settings from the application's state file.
        serverSettings = new ServerSettings(xmlDomParser);

        // 2. Parse the command-line arguments.
        ParseCommandLine(commandLineOptions);
        logOptions();

        // 3. If we aren't already logged into the CDR, do it.
        if (!createCdrSession())
            return FALSE;

        // 4. Clear out temporary caches and unwanted XMetaL files.
        clearCaches();

        // 5. Install any new files from the server and delete obsolete files.
        refreshFiles();

        // 6. Launch new version of this program, if any; else start XMetal.
        if (loaderReplaced)
            launchRecursively();
        else
            launchClient();
    }

    // Bail out for failures.
    catch (const TCHAR* error) {
        AfxMessageBox(error);
        log(CString(error) + _T("\n"));
    }
    catch (const CString error) {
        AfxMessageBox(error);
        log(error + _T("\n"));
    }
    catch (...) {
        AfxMessageBox(_T("Unexpected failure ... closing"));
        log(_T("Unexpected failure ... closing\n"));
    }

	// We're done; FALSE means don't start the Windows message pump.
	return FALSE;
}

/*
 * Loads information for connection to the CDR servers from the XML
 * configuration file, stored locally to remember the values the
 * user last gave us.
 */
ServerSettings::ServerSettings(CComPtr<IXMLDOMDocument>& xmlDomParser) {

    // Parse the XML settings file.
    if (!xmlDomParser)
        throw _T("XML parser not created");
    VARIANT_BOOL success;
    CComVariant fileName = SETTINGS_FILE;
    if (FAILED(xmlDomParser->load(fileName, &success)) || !success)
        return;

    // Start at the top-level element.
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting elements from settings document");

    // Walk through the nodes extracting the remembered settings.
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("ServerGroup"))
            serverGroups.push_back(ServerGroup(node));
        else if (nodeName == _T("CurrentUser"))
            currentUser = getTextContent(node);
        else if (nodeName == _T("CurrentGroup"))
            currentGroup = getTextContent(node);
        node = getNextSibling(node);
    }
}

/*
 * Creates a new XML document file to remember the current server
 * settings, overwriting an existing file if there is one.  All
 * of the characters will be ASCII (mostly DNS names and strings
 * representing decimal port numbers).
 */
void ServerSettings::serialize(const CString& name) const {
    CStdioFile file;
    CFileException e;
    UINT flags = CFile::modeCreate | CFile::modeWrite | CFile::shareDenyNone;

    BOOL success = file.Open(name, flags);
    if (!success) {
        _TCHAR errmsg[1028];
        int    len = 1024;
        e.GetErrorMessage(errmsg, len);
        throw CString(errmsg);
    }
    file.WriteString(_T("<CDRServerSettings>\n"));
    file.WriteString(_T(" <CurrentUser>"));
    file.WriteString((LPCTSTR)currentUser);
    file.WriteString(_T("</CurrentUser>\n"));
    file.WriteString(_T(" <CurrentGroup>"));
    file.WriteString((LPCTSTR)currentGroup);
    file.WriteString(_T("</CurrentGroup>\n"));
    for (size_t i = 0; i < serverGroups.size(); ++i)
        serverGroups[i].serialize(file);
    file.WriteString(_T("</CDRServerSettings>\n"));
    file.Close();
}

/*
 * Constructs a ServerGroup object from its serialized form in the
 * DOM node from the XML document for remembered server settings.
 */
ServerSettings::ServerGroup::ServerGroup(CComPtr<IXMLDOMNode>& node) {
    groupName = getAttribute(node, _T("Name"));
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("UpdateServer"))
            updateServer = getTextContent(child);
        else if (nodeName == _T("UpdatePort"))
            updatePort = getTextContent(child);
        else if (nodeName == _T("CdrServer"))
            cdrServer = getTextContent(child);
        else if (nodeName == _T("CdrPort"))
            cdrPort = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Write the XML document fragment representing this server settings
 * group.
 */
void ServerSettings::ServerGroup::serialize(CStdioFile& file) const {
    file.WriteString(_T("  <ServerGroup Name=\""));
    file.WriteString((LPCTSTR)groupName);
    file.WriteString(_T("\">\n"));
    file.WriteString(_T("   <UpdateServer>"));
    file.WriteString((LPCTSTR)updateServer);
    file.WriteString(_T("</UpdateServer>\n"));
    file.WriteString(_T("   <UpdatePort>"));
    file.WriteString((LPCTSTR)updatePort);
    file.WriteString(_T("</UpdatePort>\n"));
    file.WriteString(_T("   <CdrServer>"));
    file.WriteString((LPCTSTR)cdrServer);
    file.WriteString(_T("</CdrServer>\n"));
    file.WriteString(_T("   <CdrPort>"));
    file.WriteString((LPCTSTR)cdrPort);
    file.WriteString(_T("</CdrPort>\n"));
    file.WriteString(_T("  </ServerGroup>\n"));
}

/*
 * Looks up the group corresponding to the name specified by the caller.
 * Returns the address of the object for the group.
 */
ServerSettings::ServerGroup* ServerSettings::findGroup(const CString& name) {
    for (size_t i = 0; i < serverGroups.size(); ++i)
        if (serverGroups[i].groupName == name)
            return &serverGroups[i];
    return NULL;
}

/*
 * Sets the initial values for settings which can be specified on the
 * command line.
 */
CdrCommandLineOptions::CdrCommandLineOptions() {
    skipCdrLogin     = false;
    skipDialog       = false;
    skipRefresh      = false;
    skipRecursion    = false;
    recurse          = false;
    serverDebugLevel = 1;
    clientDebugLevel = 1;
    TCHAR* envClient = _tgetenv(_T("CDR_CLIENT_DEBUG_LEVEL"));
    if (envClient) {
        errno = 0;
        int level = (int)_tcstol(envClient, NULL, 10);
        if (!errno)
            clientDebugLevel = level;
    }
    TCHAR* envServer = _tgetenv(_T("CDR_SERVER_DEBUG_LEVEL"));
    if (envServer) {
        errno = 0;
        int level = (int)_tcstol(envServer, NULL, 10);
        if (!errno)
            serverDebugLevel = level;
    }
}

/*
 * Overrides the ParseParam method of the base CCommandLineInfo class.
 * This method is invoked indirectly when we call the MFC function
 * ParseCommandLine with a reference to our CdrCommandLineOptions
 * object.
 */
void CdrCommandLineOptions::ParseParam(const TCHAR* param, 
                                       BOOL flag, BOOL last) {
    CString msg;
    CString previousOption = currentOption;
    currentOption = _T("");
    if (flag) {
        if (!_tcscmp(param,  _T("-skip-login")))
            skipCdrLogin = true;
        else if (!_tcscmp(param, _T("-skip-dialog")))
            skipDialog = true;
        else if (!_tcscmp(param, _T("-skip-refresh")))
            skipRefresh = true;
        else if (!_tcscmp(param, _T("-skip-recursion")))
            skipRecursion = true;
        else if (!_tcscmp(param, _T("-server-debug-level")))
            currentOption = _T("server-debug-level");
        else if (!_tcscmp(param, _T("-debug-level")))
            currentOption = _T("debug-level");
        else if (!_tcscmp(param, _T("-recurse"))) {
            recurse = true;
            _tremove(RECURSIVE_SCRIPT);
        }
        else {
            usage();
        }
    }
    else {
        CString msg;
        msg.Format(_T("param=%s previousOption=%s"), param, previousOption);
        if (previousOption == _T("server-debug-level")) {
            errno = 0;
            int level = _tcstol((LPCTSTR)param, NULL, 10);
            if (!errno)
                serverDebugLevel = level;
            else
                usage();
        }
        else if (previousOption == _T("debug-level")) {
            errno = 0;
            int level = _tcstol((LPCTSTR)param, NULL, 10);
            if (!errno)
                clientDebugLevel = level;
            else
                usage();
        }
    }
}

/*
 * Record the command-line options specified and the client and server 
 * debugging level, if the client debugging level is 2 or higher.
 */
void CdrClient::logOptions() {
    if (commandLineOptions.recurse)
        log(_T("Option --recurse specified.\n"), 2);
    if (commandLineOptions.skipCdrLogin)
        log(_T("Option --skip-login specified.\n"), 2);
    if (commandLineOptions.skipDialog)
        log(_T("Option --skip-dialog specified.\n"), 2);
    if (commandLineOptions.skipRecursion)
        log(_T("Option --skip-recursion specified.\n"), 2);
    if (commandLineOptions.skipRefresh)
        log(_T("Option --skip-refresh specified.\n"), 2);
    CString buf;
    buf.Format(_T("Client logging level: %d.\n"),
               commandLineOptions.clientDebugLevel);
    log(buf, 2);
    buf.Format(_T("Server logging level: %d.\n"),
               commandLineOptions.serverDebugLevel);
    log(buf, 2);
}
/*
 * Tell the user how to invoke the program.  Will be displayed in a
 * dialog window by the InitInstance method where the exception is caught.
 */
void usage() {
    throw _T("Usage: CdrClient [options]           \n\n")
          _T("available options:\n")
          _T("  --recurse\n")
          _T("  --skip-login\n")
          _T("  --skip-dialog\n")
          _T("  --skip-refresh\n")
          _T("  --skip-recursion\n")
          _T("  --debug-level N\n")
          _T("  --server-debug-level N\n");
}

/*
 * If we have been invoked recursively, a login session will already have
 * been created for the user and the ID for the session will have been
 * passed to us as part of the environment strings provided to the process.
 * If not we put up the logon dialog window, in which the user enters
 * her CDR account's credentials (and optionally modifies the values
 * used to connect to the CDR and client refresh servers).  If the user
 * confirms the request to log into the CDR, we create the logon command,
 * submit it to the CDR server, extract the session ID, and set the
 * environment variables which will be passed to the CDR XMetaL custom
 * DLL.  Returns false if the user cancels the logon request, otherwise
 * returns true.  An exception is thrown if the logon is unsuccessful.
 *
 * The XML for the client's request to logon has the following structure:
 *
 *   CdrLogon
 *     UserName [string]
 *     Password [string]
 *
 * All CDR client requests are sent as an XML document wrapped as
 * described above in the comments for the CdrSocket type, which handles
 * packing the individual commands into the CdrCommandSet document.
 *
 * The server's response has the following structure:
 *
 *   CdrLogonResp
 *     SessionId [string]
 *
 * The CdrLogonResp element is wrapped by the document-level element
 * CdrResponseSet, as described above for the CdrSocket type.
 */
bool CdrClient::createCdrSession() {

    // See if we have already been logged in to the CDR.
    TCHAR* envId = _tgetenv(_T("CDRSession"));
    if (envId) {
        sessionId = envId;
        log(_T("Already logged into the CDR with session ") + 
            sessionId + _T("\n"), 1);
        extractServerSettings();
        return true;
    }

    // Put up the login dialog window unless we've been asked not to.
    if (!commandLineOptions.skipDialog) {
        CWaitCursor waitCursor;
        dialog = new CdrLoginDlg(serverSettings);
	    INT_PTR nResponse = dialog->DoModal();
        if (nResponse == IDOK) {

            // Remember any changes to the server settings.
            serverSettings->serialize(SETTINGS_FILE);

	        // Create the logon command.
            CString uidElem;
            CString pwdElem;
	        CString request;
            uidElem.Format(_T("<UserName>%s</UserName>"), dialog->uid);
            pwdElem.Format(_T("<Password>%s</Password>"), dialog->pwd);
            request = _T("<CdrLogon>") + uidElem + pwdElem + _T("</CdrLogon>");

            // Establish a socket connection to the CDR server.
            extractServerSettings();
            CdrSocket cdrSocket(this, cdrServer, cdrPort);

            // Submit the logon request and get our CDR session ID.
            CString serverResponse = cdrSocket.sendCommand(request);
            sessionId = extractSessionId(serverResponse);
            log(_T("Logged into the CDR as ") + dialog->uid +
                _T(" with session ") + sessionId + _T("\n"), 1);

            // Inject some important values into the environment.
            CString portEnviron;
            CString clientDebugEnv;
            CString serverDebugEnv;
            portEnviron.Format(_T("CDR_PORT=%d"), cdrPort);
            clientDebugEnv.Format(_T("CDR_CLIENT_DEBUG_LEVEL=%d"), 
                                  commandLineOptions.clientDebugLevel);
            serverDebugEnv.Format(_T("CDR_SERVER_DEBUG_LEVEL=%d"),
                                  commandLineOptions.serverDebugLevel);
            _tputenv((LPCTSTR)(_T("CDRUser=") + dialog->uid));
            _tputenv((LPCTSTR)(_T("CDRSession=") + sessionId));
            _tputenv((LPCTSTR)(_T("CDR_HOST=") + cdrServer));
            _tputenv((LPCTSTR)portEnviron);
            _tputenv((LPCTSTR)clientDebugEnv);
            _tputenv((LPCTSTR)serverDebugEnv);
            return true;
        }
        else if (nResponse == IDCANCEL) {
            log(_T("User cancelled logon; shutting down ... \n"), 1);
            return false;
        }
    }
    return true;
}

/*
 * Find the currently-selected server group, and extract the server
 * names and ports into private member variables of the CdrClient
 * object.  Invoked by createCdrSession().  
 */
void CdrClient::extractServerSettings() {
    httpPort       = 80;
    cdrPort        = 2019;
    httpServer     = cdrServer 
                   = _T("mahler.nci.nih.gov");
    for (size_t i = 0; i < serverSettings->serverGroups.size(); ++i) {
        ServerSettings::ServerGroup* group = &serverSettings->serverGroups[i];
        if (serverSettings->currentGroup == group->groupName) {
            if (!group->cdrServer.IsEmpty())
                cdrServer = group->cdrServer;
            if (!group->updateServer.IsEmpty())
                httpServer = group->updateServer;
            if (!group->cdrPort.IsEmpty()) {
                long p = _tcstol((LPCTSTR)group->cdrPort, NULL, 10);
                if (p > 0)
                    cdrPort = (INTERNET_PORT)p;
            }
            if (!group->updatePort.IsEmpty()) {
                long p = _tcstol((LPCTSTR)group->updatePort, NULL, 10);
                if (p > 0)
                    httpPort = (INTERNET_PORT)p;
            }
        }
    }
}

/*
 * Parse the XML message from the server in response to our logon
 * request and extract the text content of the SessionId element.
 * An string-based exception is thrown if the server sends back
 * an error message, or we are unable to find the session ID.
 */
CString CdrClient::extractSessionId(const CString& xmlString) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xmlString);
    if (FAILED(xmlDomParser->loadXML(bstrXml, &success))) {
        log(_T("Server response: ") + xmlString + _T("\n"));
        throw _T("Failure parsing CDR Server response");
    }
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem))) {
        log(_T("Server response: ") + xmlString + _T("\n"));
        throw _T("Failure extracting session ID");
    }
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("CdrResponse")) {
            CComPtr<IXMLDOMNode> child = getFirstChild(node);
            while (child) {
                CString nodeName = getNodeName(child);
                if (nodeName == _T("CdrLogonResp")) {
                    CComPtr<IXMLDOMNode> grandchild = getFirstChild(child);
                    while (grandchild) {
                        CString nodeName = getNodeName(grandchild);
                        if (nodeName == _T("SessionId"))
                            return getTextContent(grandchild);
                        else if (nodeName == _T("Errors"))
                            throw extractErrorString(grandchild);
                        grandchild = getNextSibling(grandchild);
                    }
                }
                child = getNextSibling(child);
            }
        }
        node = getNextSibling(node);
    }
    log(_T("Server response: ") + xmlString + _T("\n"));
    throw _T("Unable to find Session ID in server response");
}

/*
 * Helper function invoked by CdrClient::extractSessionId() to pull out
 * the text content of the Err child element of an Errors element
 * returned by the CDR server in response to our logon request.
 */
CString extractErrorString(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("Err"))
            return getTextContent(child);
        child = getNextSibling(child);
    }
    return _T("Unable to find server's explanation of logon failure");
}

/*
 * This method accomplishes two goals.  First, we clear out any cached
 * multimedia documents so we don't fill up the user's disk with unwanted
 * bulk.  Second, we avoid stepping into some nasty XMetaL bugs.  XMetaL
 * does not behave correctly when we install changed DTDs for our document
 * types, even though the file timestamps for the DTDs are more recent
 * than the dates on XMetaL's compiled RLX files for these DTDs.  Sometimes
 * XMetaL ignores our changes; at other times XMetaL simply crashes.  We
 * eliminate these problems by clearing out XMetaL's compiled RLX files
 * for our own document types (but we leave the RLX files for their own
 * document types intact).
 */
void CdrClient::clearCaches() {

    // Files we want to retain (none for media).
    std::set<CString> mediaKeepers;
    std::set<CString> rlxKeepers;
    rlxKeepers.insert(_T("MACROS.RLX"));
    rlxKeepers.insert(_T("TBR.RLX"));
    rlxKeepers.insert(_T("XMETAL.RLX"));
    rlxKeepers.insert(_T("CTM.RLX"));
    rlxKeepers.insert(_T("JOURNALIST.RLX"));
    rlxKeepers.insert(_T("MEETING.RLX"));
    rlxKeepers.insert(_T("OPENRULESET.RLX"));

    log(_T("Clearing out unwanted cached and compiled files.\n"), 1);
    deleteFiles(_T(".\\Cdr\\Media\\*"), mediaKeepers);
    deleteFiles(_T(".\\Rules\\*.rlx"),  rlxKeepers);
}

/*
 * Helper method invoked by clearCaches() with common code to find
 * all files whose pathnames match a string pattern, and delete any
 * which don't appear on a list of exceptions which we're supposed
 * to keep.
 */
void CdrClient::deleteFiles(const CString& pattern,
                            const std::set<CString>& exceptions) {
    CFileFind fileFinder;
    BOOL more = fileFinder.FindFile(pattern);
    while (more) {
        more = fileFinder.FindNextFile();
        CString fileName = fileFinder.GetFileName();
        if (fileName == _T(".") || fileName == _T(".."))
            continue;
        if (exceptions.find(fileName.MakeUpper()) != exceptions.end())
            continue;
        CString filePath = fileFinder.GetFilePath();
        try {
            CFile::Remove(filePath);
        }
        catch (...) {
            log(_T("Failure removing ") + filePath + _T("\n"));
        }
    }
}

/*
 * This is where we do the work for which this program was principally
 * created: make sure all of the files needed by the CDR client are
 * up to date.  This is accomplished by communicating via the network
 * with a server which has a set of the current version of all of
 * these files, as well as a list of all of those files (the "MANIFEST")
 * with pathname and timestamp for each file, as well as a header (called
 * a "TICKET" below) identifying the server on which the manifest was
 * generated, as well as the date and time of this generation.
 *
 * The first time this program connects to the client refresh server,
 * it sends a stub version of the manifest to the server, asking it
 * to send a complete set of the client files.  The server does so
 * and the client installs these files locally.  A copy of the manifest
 * document is included in the set.
 *
 * For subsequent invocations of this program, the client first asks
 * the client refresh server if any changes have been made to the file
 * set since the previous session.  It does this by extracting the
 * header ("TICKET") from the stored manifest document and sending it
 * to the server.  If the server name and timestamp match those in
 * the server's copy of the manifest, the response "ACK" is returned
 * to the client, and no further work needs to be done.
 *
 * In the event that we detect tampering with the local client files
 * (we check to ensure that all of the files in our local copy of the
 * manifest are present, with timestamps which match those in the
 * manifest exactly), then we discard the manifest and get a complete
 * new set, as if this were the first time we had connected to the
 * server.  A possible side effect is that the client might retain
 * a file which has been removed from the complete set of client files,
 * and which the server would have asked to be deleted, had it received
 * the manifest listing that file.  This is extremely unlikely to present
 * a problem.
 *
 * If the server determines that changes have occurred, it returns the
 * response "NAK" and the client sends a copy of its complete manifest
 * file to the server.  The server compares its own copy of the manifest
 * with the copy from the client and builds two lists: one for files which
 * the client currently has but are no longer in the set of files needed
 * by the client, and a second list of files which the client does not
 * yet have, or for which the client's copy differs from that on the
 * server.  If the second list is not empty, the server creates a
 * compressed archive containing the files represented by this list.
 * An XML document ("DELTA") is sent back to the client containing the
 * name of the compressed archive (in the "ZIPFILE" element, which is
 * only created if the file was created), and an optional "DELETE" element
 * with one or more child "FILE" elements.  If the ZIPFILE element
 * is present the client asks the server to send it the file named in
 * the element, and the contents of the archive are installed locally
 * on the client machine.  If there are any files to be removed, they
 * are then deleted.
 *
 * Even in the initial case, in which the client sends a stub version
 * of the manifest, the intermediate DELTA document is returned with
 * the name of the compressed archive file, which the client requests
 * in a separate exchange with the server.
 *
 * For additional information about the structure of the XML responses
 * returned by the server, see the interface documentation for the
 * Manifest and Delta types.
 *
 * In summary, the following sequence of exchanges would take place
 * if the client's files are not completely up to date, and the
 * refresh process is successful:
 *
 *      1. Client sends <TICKET>...</TICKET> document.
 *      2. Server responds with <VALIDATION>NAK</VALIDATION>.
 *      3. Client sends <MANIFEST>...</MANIFEST> document.
 *      4. Server responds with <DELTA>...</DELTA> document.
 *      5. Client sends <ZIPREQ>[name of zipfile]</ZIPREQ>.
 *      6. Server responds with <ZIPFILE>...</ZIPFILE> document.
 */
void CdrClient::refreshFiles() {

    // Don't do anything if we're asked to skip this step (for debugging).
    if (commandLineOptions.skipRefresh)
        return;

    // Start out with stubs for the manifest document and ticket header.
    CString manifestXml = _T("<MANIFEST/>");
    CString ticketXml;

    // Parse the local copy of the manifest, if it exists.
    try {
        Manifest manifest(xmlDomParser);

        // Make sure no one has manually changed any of the client files.
        CString mismatch = manifest.validate(this);
        if (mismatch.IsEmpty()) {
            manifestXml = manifest.manifestXml;
            ticketXml   = manifest.ticketXml;
        }
    }
    
    // Errors are not fatal; log them and use the stub manifest.
    catch (const TCHAR* err) {
        CString msg;
        msg.Format(_T("Failure parsing local manifest: %s\n"), err);
        log(msg);
    }

    // If we found a valid manifest, ask the server if it's current.
    if (ticketXml.IsEmpty())
        log(_T("No local ticket available; refresh forced.\n"), 1);
    else {
        log(_T("Asking server if any files have changed.\n"), 1);
        CString response = sendHttpCommand(ticketXml);
        TicketValidation ticketValidation(xmlDomParser, response);
        if (ticketValidation.response == _T("ACK")) {
            log(_T("Local files are up to date.\n"), 1);
            return;
        }
    }

    // Make sure the user doesn't think we've died if this takes a long time.
    CdrProgressDlg progressDialog;
    progressDialog.Create(progressDialog.IDD, m_pMainWnd);
    progressDialog.Init();
    progressDialog.ShowWindow(SW_SHOWNORMAL);
    progressDialog.Advance();

    // There are changes; find out what they are.  May take some time.
    log(_T("Some files have changed; sending manifest for local files.\n"), 1);
    CString response = sendHttpCommand(manifestXml);
    progressDialog.Advance();
    Delta delta = Delta(xmlDomParser, response);

    // If there are new or changed files, retrieve and unpack them.
    if (!delta.zipFile.IsEmpty())
        getNewFiles(delta.zipFile, progressDialog);
    progressDialog.Advance();

    // If we've been asked to delete any files, do so here.
    std::list<CString>::const_iterator iter = delta.deletes.begin();
    while (iter != delta.deletes.end()) {
        log(_T("Removing ") + *iter + _T(" on instructions from server\n"), 1);
        try {
            CFile::Remove((LPCTSTR)*iter);
        }
        catch (...) {
            log(_T("Unable to remove ") + *iter + _T("\n"));
        }
        ++iter;
    }
    log(_T("Refresh of local files complete.\n"), 1);
}

/*
 * Parse the XML document for a manifest for a client file set,
 * and populate the data members of the object with the values
 * found in the document.  Throws a string-based exception if
 * the document is missing or corrupt.  See the interface documentation
 * for this class for the structure of the manifest XML document.
 */
Manifest::Manifest(CComPtr<IXMLDOMDocument>& xmlDomParser) {

    // Parse the document.
    VARIANT_BOOL success;
    CComVariant fileName = MANIFEST_FILE;
    if (FAILED(xmlDomParser->load(fileName, &success)) || !success)
        if (PathFileExists(MANIFEST_FILE))
            throw _T("Manifest file is corrupt");
        else
            throw _T("User has no local manifest file");

    // Save the string representation of the document in case we need to
    // send it to the server or log it.
    CComBSTR xmlString;
    xmlDomParser->get_xml(&xmlString);
    manifestXml = xmlString;

    // Walk through the children of the document element and extract the
    // ticket header and the list of files.
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting elements from manifest");
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("TICKET")) {
            ticket = Ticket(node);
            CComBSTR xmlString;
            node->get_xml(&xmlString);
            ticketXml = xmlString;
        }
        else if (nodeName == _T("FILELIST")) {
            CComPtr<IXMLDOMNode> child = getFirstChild(node);
            while (child) {
                CString nodeName = getNodeName(child);
                if (nodeName == _T("FILE"))
                    fileList.push_back(File(child));
                child = getNextSibling(child);
            }
        }
        node = getNextSibling(node);
    }
}

/*
 * Extract the pathname and timestamp for a single node in the manifest's
 * fileList vector.
 */
File::File(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("NAME"))
            name = getTextContent(child);
        else if (nodeName == _T("TIMESTAMP"))
            timestamp = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Compares the manifest with the files on the local disk, making sure
 * they're all present and have matching timestamps.  Returns an empty
 * string if there are no discrepancies; otherwise returns a string
 * identifying the first mismatch or missing file detected.  We don't
 * bother checking the script to invoke ourselves recursively, because
 * we delete that file as soon as we are invoked with the --recurse
 * command-line option, in order to prevent infinite recursion.  For
 * a more detailed explanation of how the recursion works (and why
 * and when it is needed), see the comment for the implementation
 * of the CdrClient::launchRecursively() method.
 */
CString Manifest::validate(CdrClient* client) {
    std::vector<File>::const_iterator file = fileList.begin();
    CString skipRecursiveLoader = CString(RECURSIVE_SCRIPT).MakeLower();
    while (file != fileList.end()) {
        CString lowerName = file->name;
        lowerName.MakeLower();
        if (lowerName.Find(skipRecursiveLoader) == -1) {
            CString clientTimestamp;
            try {
                clientTimestamp = getFileTimestamp(file->name);
            }
            catch (const CString err) {
                return err;
            }
            if (clientTimestamp != file->timestamp) {
                CString msg;
                msg.Format(_T("%s: local stamp = %s; server stamp = %s"),
                    file->name, clientTimestamp, file->timestamp);
                client->log(msg + _T("\n"), 1);
                AfxMessageBox(msg);
                return file->name + _T(" mismatch");
            }
        }
        ++file;
    }
    return _T("");
}

/*
 * Finds the local copy of a file on the disk and obtains its
 * data/time stamp for last modification.  Returns a string
 * representing the UTF date/time for the stamp.  Throws a
 * string-based exception if the file cannot be found or the
 * timestamp cannot be obtained.
 */
CString getFileTimestamp(const CString& name) {
    HANDLE h = ::CreateFile((LPCTSTR)name, GENERIC_READ, 0, NULL,
                            OPEN_EXISTING, 0, 0);
    if (!h) {
        CString err;
        err.Format(_T("failure getting timestamp for %s"), name);
        return err;
    }
    FILETIME cre, acc, wri;
    if (!::GetFileTime(h, &cre, &acc, &wri)) {
        CString err;
        err.Format(_T("unable to get timestamp for %s"), name);
        ::CloseHandle(h);
        return err;
    }
    ::CloseHandle(h);
    SYSTEMTIME s;
    if (!::FileTimeToSystemTime(&wri, &s)) {
        CString err;
        err.Format(_T("failure converting filetime to system time for %s"),
                   name);
        return err;
    }
    CString result;
    result.Format(_T("%04d-%02d-%02dT%02d:%02d:%02d"),
                  s.wYear, s.wMonth, s.wDay,
                  s.wHour, s.wMinute, s.wSecond);
    return result;
}

/*
 * Populates this object with the values found in the DOM node for
 * its XML representation.
 */
Ticket::Ticket(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child = getFirstChild(node);
    while (child) {
        CString nodeName = getNodeName(child);
        if (nodeName == _T("APPLICATION"))
            application = getTextContent(child);
        else if (nodeName == _T("TIMESTAMP"))
            timestamp = getTextContent(child);
        else if (nodeName == _T("HOST"))
            host = getTextContent(child);
        else if (nodeName == _T("AUTHOR"))
            author = getTextContent(child);
        child = getNextSibling(child);
    }
}

/*
 * Send an XML document via HTTP to the client refresh server, then
 * retrieve and return the server's response.
 */
CString CdrClient::sendHttpCommand(const CString& cmd) {

    // Build the strings needed for submitting the request.
    CInternetSession session;
    CString          response;
    CString          headers;
    CHttpConnection* conn    = NULL;
    CHttpFile*       file    = NULL;
    const TCHAR*     target  = _T("/cgi-bin/cdr/ClientRefresh.py");
    CStringA         ascii   = (CStringA)cmd.GetString();
    CStringA::PCXSTR bytes   = ascii.GetString();
    DWORD            length  = cmd.GetLength();
    BOOL             success = FALSE;
    try {//_T("Content-Length: %d\n")
        headers.Format(_T("Content-Type: text/xml; charset=utf-8\n")
                       
                       _T("X-Debug-Level: %d\n"), 
                       // length, 
                       commandLineOptions.serverDebugLevel);
        log(_T("HTTP headers:\n%s\n") + headers, 3);

        // Connect the to client refresh server.
        try {
            conn = session.GetHttpConnection(httpServer, httpPort);
            log(_T("Got HTTP connection to ") + httpServer + _T("\n"), 3);
            file = conn->OpenRequest(_T("POST"), target);
            log(_T("POST request opened successfully.\n"), 3);
        }
        catch (...) {
            throw _T("Unable to connect to client update server");
        }

        // This fails occasionally; give the server three chances.
        for (int i = 0; !success && i < 3; ++i) {
            try {
                log(_T("Calling SendRequest().\n"), 3);
                success = file->SendRequest(headers, 0, (void *)bytes, length);
            }
            catch (...) {}
        }
        if (!success)
            throw _T("Failure submitting request to update server");

        // Find out if the mechanics of the exchange were successful.
        DWORD result;
        file->QueryInfoStatusCode(result);
        if (result != HTTP_STATUS_OK) {
            CString err;
            err.Format(_T("HTTP status code from update server: %lu"), 
                       result);
            throw err;
        }

        // Read the response in chunks.
        try {
            CString msg;
            char buf[1024];
            UINT nread = file->Read(buf, sizeof buf);
            msg.Format(_T("Read %u bytes.\n"), nread);
            log(msg, 4);
            while (nread > 0) {
                response += CString(buf, (int)nread);
                nread = file->Read(buf, sizeof buf);
                msg.Format(_T("Read %u bytes.\n"), nread);
                log(msg, 4);
            }
        }

        // Haven't had this ever fail before, but you never know.
        catch (...) {
            throw _T("Failure reading response from update server");
        }
    }
    catch (...) {
        if (conn)
            conn->Close();
        if (file)
            file->Close();
        throw;
    }
    conn->Close();
    file->Close();
    log(_T("HTTP response:\n") + response + _T("\n"), 3);
    return response;
}

/*
 * Constructor for parsing the server response when we ask if our 
 * manifest is up to date.  Throws a string-based exception if
 * we are unable to parse the response's XML document.
 */
TicketValidation::TicketValidation(CComPtr<IXMLDOMDocument>& xmlDomParser, 
                                   const CString& xmlString) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xmlString);
    if (FAILED(xmlDomParser->loadXML(bstrXml, &success)))
        throw _T("Failure parsing ticket validation response");
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlDomParser->get_documentElement(&docElem)))
        throw _T("Failure extracting ticket validation response");
    response = getTextContent((CComPtr<IXMLDOMNode>)docElem);
}

/*
 * Constructor for parsing the server response when we ask it to 
 * compare our copy of the manifest with its copy and determine
 * what the differences are, if any.  Throws a string-based
 * exception if we are unable to parse the response's XML
 * document.
 */
Delta::Delta(CComPtr<IXMLDOMDocument>& xmlParser, const CString& xmlString) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xmlString);
    if (FAILED(xmlParser->loadXML(bstrXml, &success)))
        throw _T("Failure parsing ticket validation response");
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlParser->get_documentElement(&docElem)))
        throw _T("Failure extracting ticket validation response");
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("ZIPFILE"))
            zipFile = getTextContent(node);
        else if (nodeName == _T("DELETE")) {
            CComPtr<IXMLDOMNode> child = getFirstChild(node);
            CString nodeName = getNodeName(child);
            if (nodeName == _T("FILE"))
                deletes.push_back(getTextContent(child));
            child = getNextSibling(child);
        }
        node = getNextSibling(node);
    }
}

/*
 * Ask the server to send us the archive of new and/or changed files.
 * Unpack the set, and then verify that the files match the manifest.
 *
 * Mismatches can happen for a variety of reasons:
 *
 *   (1) Sometimes a new or changed file is added to the set on the
 *       server, and the account under which the client refresh server
 *       is running does not have sufficient permission to read the
 *       file when it tries to add it to the compressed archive.
 *       This condition should be addressed by enhancements to the
 *       software which builds the manifest on the server, to ensure
 *       at manifest build time that the client refresh server can
 *       read all of the files represented on the manifest.  Of
 *       course, this would not completely eliminate this class of
 *       problem, as it is possible for systems administrators to
 *       make changes to permission settings, or for bugs to surface
 *       in the operating system, changing the way permissions are
 *       granted or denied.  We might address this problem by having
 *       a periodic job run to confirm that permissions needed by
 *       the server are intact, with email alerts sent to appropriate
 *       persons whenever this assumption is violated.  It is possible
 *       that moving the client refresh servers from Windows to an
 *       operating system with a less Byzantine authentication /
 *       permission system would dramatically reduce or eliminate
 *       this class of problem.
 *
 *   (2) The copy of a file on the client machine can have settings
 *       which deny the current user permission to overwrite that
 *       file with a new version.  This can happen, for example,
 *       if an administrator logs onto the machine and runs the
 *       CDR client, resulting in files for which only the administrator
 *       has sufficient permissions for removal or replacement.
 *       Or the systems support staff can change the account with which
 *       the user logs onto the machine (e.g., different domain).
 *       There isn't much we can do about this problem, beyond
 *       educating users (or at least, lead users responsible for
 *       troubleshooting failures) about the need to check the
 *       the logs for error messages and ensure that the user has
 *       adequate permissions for changing all of the files
 *       represented in the manifest.
 *
 *   (3) A file can be added to (changed in, deleted from) the set
 *       of current client files without rebuilding the manifest.
 *       One solution might be to have a scheduled job run periodically
 *       to verify that the manifest is in sync with the set of current
 *       files, with email alerts when problems are detected.  A more
 *       elaborate approach would be to set up a mechanism for
 *       managing the client file set (adding new files, removing
 *       or replacing existing files) exclusively through an interface
 *       designed for this purpose.  This would eliminate the window
 *       for failures allowed by the first approach to dealing with
 *       this type of problem.  For example, a web interface might
 *       be used with the file upload feature of CGI for submitting
 *       new or changed files.  The web interface would also allow
 *       for removing files from the client set.  An additional
 *       benefit from this technique would be the ability to capture
 *       information about who installed the most recent version of
 *       a file (or deleted a file), and any reasons for the change.
 *       Another side benefit of the web interface would be easier
 *       upload of files from the user's workstation, which is currently
 *       made more difficult by the inability to map drives locally
 *       to the CDR Servers.
 *
 *       A command-line version of the interface might also be useful,
 *       to allow developers or lead users to install or delete files
 *       from a telnet or ssh connection, where a browser cannot be
 *       used for installing files from the remote server's filesystem.
 *
 *       An even more elaborate, but more reliable approach (and one
 *       providing richer functionality), would be to store the client 
 *       file set in tables of a DBMS.
 *
 *   (4) Transmission errors.  Theoretically possible, but should be
 *       eliminated by the error-correction facilities provided by
 *       TCP/IP, over which the connections communicate.
 *
 *   (5) Operating system bugs in reporting of file timestamps.  The
 *       predecessor of this program was susceptible to the most
 *       notorious of these bugs in Windows, which reported different
 *       values depending on whether the client and server were
 *       on different sides of a daylight-saving time boundary.
 *       This program avoids that bug by storing file timestamps
 *       as a standard ISO representation of the UTC string for
 *       the timestamp, which is unaffected by local time changes,
 *       including those for daylight savings time.  Another problem
 *       in this category is caused by the discrepancy in older
 *       versions of Windows, which returned timestamp values with
 *       insufficient granularity, resulting in discrepancies in
 *       representations of the same timestamp.  This problem is
 *       currently addressed by client requirements for minimum
 *       operating system versions.
 *
 * The zipfile is saved in the current working directory under the
 * name CdrClientFiles.zip.  The output from the command to unpack
 * the files (listing the files which were unpacked) is stored in
 * the a file named unzip.out.  Any error messages from that operation
 * are stored in a file named unzip.err.
 */
void CdrClient::getNewFiles(const CString& zipName, CdrProgressDlg& dialog) {

    // Ask the server for the zipfile.
    CString request  = _T("<ZIPREQ>") + zipName + _T("</ZIPREQ>");
    CString response = sendHttpCommand(request);
    dialog.Advance();

    // Parse the response.
    ZipFile zipFile(xmlDomParser, response);
    dialog.Advance();
    log(_T("Retrieved zipfile ") + zipFile.name + _T("\n"), 1);

    // Save the zipfile to the current working directory.
    FILE* fp = fopen("CdrClientFiles.zip", "wb");
    if (!fp)
        throw _T("Failure opening CdrClientFiles.zip");
    size_t n = fwrite(zipFile.bytes.c_str(), 1, zipFile.bytes.size(), fp);
    if (n != zipFile.bytes.size())
        throw _T("Failure writing CdrClientFiles.zip");
    if (fclose(fp))
        throw _T("Failure closing CdrClientFiles.zip");

    // Unpack the archive.
    log(_T("Unpacking updated files from the server.\n"), 1);
    int rc = system(".\\unzip -o CdrClientFiles.zip >unzip.out 2>unzip.err");
    if (rc == -1)
        throw _T("Failure unpacking new files from server");
    dialog.Advance();

    // Verify that the manifest and files match each other.
    CString mismatch;
    try {
        Manifest manifest(xmlDomParser);
        log(_T("Verifying the new manifest against our local files ...\n"), 1);
        mismatch = manifest.validate(this);
        dialog.Advance();
    }
    catch (...) {
        throw _T("Missing or corrupted manifest");
    }
    if (!mismatch.IsEmpty())
        throw mismatch;

    // If a new version of this program was included, there will be a
    // copy of the script to launch the program again recursively.
    // Make a note so we'll know to invoke the script.
    if (PathFileExists(RECURSIVE_SCRIPT))
        this->loaderReplaced = true;
}

/*
 * Extracts the filename and bytes for the compressed archive containing
 * new and/or modified files.  Decodes the bytes into a non-Unicode string
 * object which is saved as the bytes data member of the object.  Throws
 * a string-based exception if the XML document representing the zipfile
 * cannot be parsed successfully, or if the bytes cannot be decoded from
 * their base 64 representation.
 */
ZipFile::ZipFile(CComPtr<IXMLDOMDocument>& xmlParser, const CString& xml) {
    VARIANT_BOOL success;
    CComBSTR bstrXml(xml);
    if (FAILED(xmlParser->loadXML(bstrXml, &success)))
        throw _T("Failure parsing ZIPFILE response");
    CComPtr<IXMLDOMElement> docElem;
    if (FAILED(xmlParser->get_documentElement(&docElem)))
        throw _T("Failure extracting ZIPFILE element");
    CComPtr<IXMLDOMNode> node = getFirstChild((CComPtr<IXMLDOMNode>)docElem);
    while (node) {
        CString nodeName = getNodeName(node);
        if (nodeName == _T("FNAME"))
            name = getTextContent(node);
        else if (nodeName == _T("DATA")) {
            CString encoding = getAttribute(node, _T("encoding"));
            if (encoding != _T("base64"))
                throw _T("Unsupported encoding for zipfile: ") + encoding;
            CString data = getTextContent(node);
            CStringA bytes = CStringA(data);
            int nBytes = data.GetLength();
            struct SafeBuf {
                SafeBuf(int n) { buf = new char[n]; }
                ~SafeBuf() { delete [] buf; }
                char* buf;
            };
            SafeBuf safeBuf(nBytes);
            BOOL success = Base64Decode((LPCSTR)bytes, data.GetLength(), 
                                        (BYTE*)safeBuf.buf, &nBytes);
            if (!success)
                throw _T("Failure decoding base64 bytes for zipfile");
            this->bytes = std::string((char*)safeBuf.buf, nBytes);
        }
        node = getNextSibling(node);
    }
}

/*
 * Registers the custom DLL we wrote to provide CDR functionality
 * for users of XMetaL and invokes the latest Unicode version of
 * XMetaL.  Throws a string-based exception if the launch does not
 * succeed.
 */
void CdrClient::launchClient() {
    CString msg;
    int rc = system("regsvr32 /s CDR\\Cdr.dll");
    if (rc) {
        msg.Format(_T("Failure registering Cdr.dll: %S"), strerror(errno));
        throw msg;
    }
    CString programName = findXmetalProgram();
    if (programName.IsEmpty())
        throw _T("Unable to find XMetaL program");
    TCHAR* args[2] = { _T("XMetaL") };
    log(_T("Launching ") + programName + _T("\n"), 1);
    int err = (int)_texecve(programName.GetBuffer(), args, NULL);
    msg.Format(_T("Failure launching %s: %S"), programName, strerror(errno));
    throw msg;
}

/*
 * Look in the current working directory for the XMetaL executable
 * program file with the latest version, skipping over versions
 * which use single-byte-character strings (the names of which
 * end in "a.exe").  Returns the name of the program to run,
 * or an empty string if no appropriate file is found.
 */
CString findXmetalProgram() {
    CFileFind fileFinder;
    BOOL more = fileFinder.FindFile(_T(".\\xmetal*.exe"));
    CString xmetalProgram;
    while (more) {
        more = fileFinder.FindNextFile();
        CString fileName = fileFinder.GetFileName();
        CString ucName = fileName.MakeUpper();
        if (ucName.Right(5).Compare(_T("A.EXE"))) {
            if (ucName > xmetalProgram.MakeUpper())
                xmetalProgram = fileName;
        }
    }
    return xmetalProgram;
}

/*
 * Invokes the script to run this program a second time with the
 * --recurse command-line argument.  Throws a string-based exception
 * if the launch does not succeed.
 *
 * Here's how this works.  The set of client files always includes
 * a script named LaunchCdrClientRecursively.cmd, which has a single
 * line calling this program with the --recurse argument.  Whenever
 * this program (CdrClient-versionstamp.exe) is updated, an executable
 * with a new name containing a timestamp representing the date and
 * time this version of the program was compiled (for example,
 * CdrClient20051103-1709.exe).  At the same time, the script
 * LaunchCdrClientRecursively.cmd is edited to invoke this version
 * of the program instead of the previous version.  Since the
 * client's manifest indicates that its version of the recursion
 * script is older than the version now on the server, the server
 * sends this new version of the script to the client, along with
 * the new version of this program.  This program downloads the
 * new client files, notices that the recursion script is present
 * in the set, and invokes the script (using the function below
 * this comment).  The code to parse the command-line arguments
 * deletes the recursion script when it sees the --recurse argument
 * in the current invocation of the program, preventing infinite
 * recursion.  Although the recursion script file has been deleted,
 * the client's copy of the manifest still includes the listing
 * for the script file, so the server doesn't keep sending the
 * missing recursion script over and over.  The code which verifies
 * that the client files are in sync with the manifest is smart
 * enough to know that it shouldn't bother checking the recursion
 * script file, because if it did, the check would almost always
 * fail needlessly.  A bit complicated, but it all works just fine.
 *
 * The reason we need to use different names for the individual
 * versions of this program is that Windows is not capable of
 * allowing the binary file for a program to be replaced while
 * the program is still running.
 */
void CdrClient::launchRecursively() {

    // Don't do this if we're asked not to.
    if (commandLineOptions.skipRecursion)
        return;

    // Avoid infinite recursion.
    if (commandLineOptions.recurse) {
        log(_T("Recursion attempted a second time; bailing out.\n"));
        return;
    }
    
    CString msg;
    msg.Format(_T("Recursively launching %s\n"), RECURSIVE_SCRIPT);
    log(msg, 1);
    TCHAR* args[2] = { RECURSIVE_SCRIPT };
    (void)_texecve(RECURSIVE_SCRIPT, args, NULL);
    msg.Format(_T("Failure launching %s: %d"), RECURSIVE_SCRIPT, 
               strerror(errno));
    throw msg;
}

/*
 * Returns a new CString object for the value of the specified
 * attribute of an element.  This is the first of a series of
 * convenient utility functions which encapsulate frequently
 * used XML DOM processing tasks.
 */
CString getAttribute(CComPtr<IXMLDOMNode>& elem, const TCHAR* name) {
    CComPtr<IXMLDOMNamedNodeMap> attrMap;
    elem->get_attributes(&attrMap);
    CComVariant value;
    CComPtr<IXMLDOMNode> attribute;
    CComBSTR bstrName(name);
    attrMap->getNamedItem(bstrName, &attribute);
    attribute->get_nodeValue(&value);
    return CString(value);
}

/*
 * Returns a pointer to the object for the next DOM node in the
 * chain; used for walking through the children of a DOM node
 * sequentially.
 */
CComPtr<IXMLDOMNode> getNextSibling(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> nextNode;
    node->get_nextSibling(&nextNode);
    return nextNode;
}

/*
 * Wrapper for the DOM node's get_firstChild method.
 */
CComPtr<IXMLDOMNode> getFirstChild(CComPtr<IXMLDOMNode>& node) {
    CComPtr<IXMLDOMNode> child;
    node->get_firstChild(&child);
    return child;
}

/*
 * Returns the name of the current DOM node.
 */
CString getNodeName(CComPtr<IXMLDOMNode>& node) {
    CComBSTR name;
    if (SUCCEEDED(node->get_nodeName(&name)))
        return CString(name);
    throw _T("Failure getting XML node name");
}

/*
 * Extract the text content from a DOM element node and returns it
 * as a new CString object.
 */
CString getTextContent(CComPtr<IXMLDOMNode>& element) {
    CString textContent = _T("");
    CComPtr<IXMLDOMNode> child = getFirstChild(element);
    while (child) {
        DOMNodeType nodeType;
        child->get_nodeType(&nodeType);
        if (nodeType == NODE_TEXT || nodeType == NODE_CDATA_SECTION) {

            COleVariant childTextContent;
            if (SUCCEEDED(child->get_nodeValue(&childTextContent))) {
                textContent += CString(childTextContent.bstrVal);
            }
        }
        child = getNextSibling(child);
    }
    return textContent;
}

/*
 * Opens the log file and writes a heading for this session.  File is
 * opened in append mode, so entries from previous sessions are preserved.
 */
LogFile::LogFile() {
    try {
        time_t now = time(0);
        logFile.open("CdrClient.log", std::ios::app);
        logFile << "===================================================\n";
        logFile << cStringToUtf8(AfxGetAppName()) << " " << ctime(&now);
        logFile << "===================================================\n";
        logFile << std::flush;
    }
    catch (...) {
        AfxMessageBox(_T("Unable to open log file"));
    }
}

/*
 * Converts the caller's string to a UTF-8--encoded string and writes
 * it to the open log file.
 */
void LogFile::write(const CString& what) {
    SYSTEMTIME t;
    ::GetLocalTime(&t);
    char buf[80];
    sprintf(buf, "%02u:%02u:%02u.%03u ", t.wHour, t.wMinute, t.wSecond,
            t.wMilliseconds);
    std::string s = cStringToUtf8(what);
    logFile << buf << s << std::flush;
}

/**
 * Creates UTF-8 version of CString.  Ignores UCS code points beyond 0xFFFF.
 */
std::string LogFile::cStringToUtf8(const CString& str) {

    // Calculate storage requirement.
    size_t i, len = 0;
    size_t strLen = str.GetLength();
    LPCTSTR wchars = static_cast<LPCTSTR>(str);
    for (i = 0; i < strLen; ++i) {
        unsigned short ch = charToUnsignedShort(wchars[i]);
        if (ch < 0x80)
            ++len;
        else if (ch < 0x800)
            len += 2;
        else
            len += 3;
    }

    // Create string.
    std::string utf8(len, ' ');
    size_t j;

    // Populate string.
    for (i = j = 0; i < strLen; ++i)
    {
        unsigned short ch = charToUnsignedShort(*wchars++);
        if (ch < 0x80)
            utf8[j++] = (char)(unsigned char)ch;
        else if (ch < 0x800)
        {
            utf8[j++] = (char)(unsigned char)(0xC0 | ((ch & 0x07C0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
        else
        {
            utf8[j++] = (char)(unsigned char)(0xE0 | ((ch & 0xF000) >> 12));
            utf8[j++] = (char)(unsigned char)(0x80 | ((ch & 0x0FC0) >> 6));
            utf8[j++] = (char)(unsigned char)(0x80 |  (ch & 0x003F));
        }
    }
    return utf8;
}

/*
 * Wrapper for the LogFile object's write() method.
 */
void CdrClient::log(const CString& what, int level) {
    if (level >= commandLineOptions.clientDebugLevel)
        logger->write(what);
}