/*
 * Interface file for CDR loader application.  Rewritten 2005 by bkline.
 */

/*
 * Preprocessor directives generated by Visual Studio wizard.
 */
#pragma once
#ifndef __AFXWIN_H__
    #error include 'stdafx.h' before including this file for PCH
#endif
#include "resource.h"

/*
 * Header files added for this program.
 */
#include <atlbase.h>
#include <msxml.h>
#include <vector>
#include <list>
#include <set>
#include <string>
#include <afxinet.h>
#include <fstream>
#include "CdrProgressDlg.h"

/*
 * Fixed names.
 */
#define RELAUNCH_SCRIPT  _T("CdrRunAgain.cmd")
#define MANIFEST_FILE    _T("CdrManifest.xml")
#define SETTINGS_FILE    _T("CdrTiers.xml")
#define PROD_TIER        _T("PROD")
#define STAGE_TIER       _T("STAGE")
#define QA_TIER          _T("QA")
#define DEV_TIER         _T("DEV")
#define CLREFR           _T("/cgi-bin/cdr/ClientRefresh.py")
#define TUNNELING        1

/*
 * Forward references.
 */
class CdrLoginDlg;
class LogFile;
class CdrClient;

/*
 * These are the values used for connecting to the CDR server and the
 * client files refresh server.  There are four groups ("tiers") of
 * these servers (and the values used to connect to them), one each for
 * production, stage, qa, and development.  This object also remembers
 * the currently selected group, as well as the current CDR user ID.
 * There are methods available for finding a group by its name,
 * and for serializing the values held by the object in a persistent
 * XML file on the user's local disk.
 *
 * The structure of the XML document containing these settings
 * looks like this:
 *
 *  CDRServerSettings
 *    CurrentUser [string]
 *    CurrentGroup [string]
 *    ServerGroup [multiple]
 *      @Name
 *      CDRServer [string]
 *      APIServer [string]
 */
struct ServerSettings {
    ServerSettings(CComPtr<IXMLDOMDocument>& xmlDomParser,
                   CdrClient* client);

    /*
     * Each group has a name, as well as values (DNS names for the
     * servers) for connecting to the CDR server and CDR API server
     * in the group.  The group object knows how to generate an XML
     * representation of itself.
     */
    struct ServerGroup {
        ServerGroup(CString name, CString cdr, CString api);
        ServerGroup(CComPtr<IXMLDOMNode>& node);
        CString groupName;
        CString cdrServer;
        CString apiServer;
        void serialize(CStdioFile&) const;
    };
    ServerGroup* findGroup(const CString& name);
    std::vector<ServerGroup> serverGroups;
    CString currentUser;
    CString currentGroup;
    void serialize(const CString& name, CdrClient*) const;
};

/*
 * Run-time settings which can be set on the command line.  This class
 * is derived from the general MFC class for handling command-line
 * parameters.  The following options are supported:
 *
 *   --run-again           This option is used when we are being invoked
 *                         by ourselves, which we must do when we have
 *                         just received a new version of this program
 *
 *   --server-debug-level  Used to control the amount of logging to
 *                         be performed by the server which sends us
 *                         new or updated client files.  The default
 *                         value is 1, which provides minimal logging.
 *                         Expects a decimal value.  Set to 0 to turn
 *                         off all logging except for failures.
 *
 *   --debug-level         Used to control the amount of logging to
 *                         be performed by this program.  The default
 *                         value is 1, similar to that used for
 *                         the server debug level.
 *
 *   --skip-reload         Used to suppress second invocation of
 *                         this program, even when the server sends
 *                         us a new version of the program with a
 *                         script to invoke the program again.
 *                         Used during development for debugging.
 *
 *   --skip-login          Used during development and debugging
 *                         to suppress the login to the CDR server.
 *
 *   --skip-dialog         Used during development/debugging to
 *                         avoid displaying the login dialog and
 *                         the user modification of connection
 *                         values.
 *
 *   --skip-refresh        Don't download any new or changed
 *                         files from the server; don't even
 *                         check to see whether our files are
 *                         up to date.  Used during development
 *                         or to avoid downloading files which
 *                         may have unwanted changes.
 */
class CdrCommandLineOptions : public CCommandLineInfo {
public:
    CdrCommandLineOptions();
    void ParseParam(const TCHAR* param, BOOL flag, BOOL last);
    bool skipCdrLogin;
    bool skipDialog;
    bool skipRefresh;
    bool skipReload;
    bool runAgain;
    int  serverDebugLevel;
    int  clientDebugLevel;
private:
    CString currentOption;
};

/*
 * Main application object.  See documentation in implementation file
 * for explanations of the program's logic and structure.
 */
class CdrClient : public CWinApp {
public:
    CdrClient();
    ~CdrClient();
    void log(const CString& what, int level = 0);

public:
    // Override base class methods.
    virtual BOOL InitInstance();

    // XMetaL version we're running.
    typedef enum { XM45 = 45, XM70 = 70, XM90 = 90 } XMVER;
    XMVER xmver;
    CString sendHttpCommand(const CString& cmd, const TCHAR* target = CLREFR);

private:
    // Implementation.
    void extractServerSettings();
    bool createCdrSession();
    void clearCaches();
    void refreshFiles();
    void runAgain();
    void launchClient();
    void exportEnvironment();
    void logOptions();
    void cleanOutOlderVersions();
    void getNewFiles(const std::string&, CdrProgressDlg&);
    void deleteFiles(const CString&);
    void deleteRlxFiles(const CString&);
    CString cdrServer;
    CString apiServer;
    CString sessionId;
    bool loaderReplaced;
    ServerSettings* serverSettings;
    CComPtr<IXMLDOMDocument> xmlDomParser;
    CdrLoginDlg* dialog;
    CdrCommandLineOptions commandLineOptions;
    LogFile* logger;

    // Generated by Visual Studio wizard.
    DECLARE_MESSAGE_MAP()
};

/*
 * This object represents the header from a manifest document identifying
 * the current set of client files we should have.  We send this to the
 * client refresh server so that it can determined whether any changes
 * have taken place since the last time we checked, without sending the
 * entire manifest file.  Since in most cases, no such changes have
 * occurred, this saves significant time and network bandwidth.  The
 * header records the name of the machine on which the manifest was
 * created, a cumulative checksum for the client files, who ran the
 * program to create it, and what application was used to create it.
 * Only the host name and manifest checksum are used in the determina-
 * tion of whether changes have taken place since the client's copy of
 * the manifest was created.  See comment below for Manifest type
 * for the header's XML structure.
 */
struct Ticket {
    Ticket(CComPtr<IXMLDOMNode>&);
    Ticket() {}
    CString application;
    CString host;
    CString author;
    CString checksum;
};

/*
 * Records the pathname and checksum for one of the files listed in
 * the manifest.
 */
struct File {
    File(CComPtr<IXMLDOMNode>&);
    CString name;
    CString checksum;
    CString getChecksum() const;
    bool skipValidation() const;
};

/*
 * Contains a list of all of the current CDR client files which should
 * be installed on the user's machine, as well as a header ("ticket")
 * used to determine whether the client machine's copy of the manifest
 * is current.  The validate() method walks through the list of
 * files in the manifest to ensure that the correct version of each
 * file is present on the user's disk.
 *
 * The structure for the manifest file looks like this:
 *
 *  Manifest
 *    Ticket
 *      Application [string]
 *      Host [string]
 *      Author [string]
 *      Checksum [string]
 *    FileList
 *      File [multiple]
 *        Name [string]
 *        Checksum [string]
 */
struct Manifest {
    Manifest(CComPtr<IXMLDOMDocument>&);
    Ticket ticket;
    CString ticketXml;
    CString manifestXml;
    std::vector<File> fileList;
    CString validate(CdrClient*);
};

/*
 * Represents the server's response to our request to determine
 * whether our manifest is out of date.  The XML document for
 * the server's response consists of only a single text-content
 * element named Current.
 */
struct TicketValidation {
    TicketValidation(CComPtr<IXMLDOMDocument>&, const CString&);
    CString response;
};

/*
 * Represents the results of the server's comparison of it's own
 * manifest file with the client's copy.  This object will have
 * a list of files that we said we have but are no longer on
 * the server's manifest, and should therefore be deleted, as
 * well as the bytes for a zipfile containing all the new or
 * changed files (if any) the server needs to send us.
 *
 * The server's response has the following structure:
 *
 *  Updates
 *    ZipFile [string, optional]
 *      @encoding [='base64']
 *    Delete [optional]
 *      File [string, multiple]
 */
struct Updates {
    Updates(CComPtr<IXMLDOMDocument>&, const CString&);
    std::string zipBytes;
    std::list<CString> deletes;
};

/*
 * Object used to record logging information at runtime.  Unicode
 * strings are encoded as UTF-8 before being written to the log
 * file.
 */
class LogFile {
public:
    LogFile();
    ~LogFile() { logFile << std::endl; }
    void write(const CString& what);
private:
    std::ofstream logFile;
    static std::string cStringToUtf8(const CString&);
    static inline unsigned short charToUnsignedShort(TCHAR c) {
        #ifdef _UNICODE
            return static_cast<unsigned short>(c);
        #else
            unsigned char uc = static_cast<unsigned char>(c);
            return static_cast<unsigned short>(uc);
        #endif
    }
};

/*
 * Global object for the application.
 */
extern CdrClient theApp;
