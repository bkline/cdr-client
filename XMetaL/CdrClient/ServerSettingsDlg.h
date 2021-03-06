/*
 * Interface for object used to track and manipulate values for
 * connecting with the CDR servers.
 */
#pragma once
#include "afxwin.h"

// Forward reference.
struct ServerSettings;

/*
 * Object for dialog window used to display and modify the values
 * for connecting with the CDR servers.  CString data members are
 * used to store each of the following:
 *
 *    - DNS name for the CDR admin/login server
 *    - DNS name for the API server
 *
 * There is a set of these two values for each of the following
 * machines:
 *
 *    - the production machine (e.g., cdr[api].cancer.gov
 *    - the staging machine (e.g., cdr[api]-stage.cancer.gov)
 *    - the qa machine (e.g., cdr[api]-qa.cancer.gov)
 *    - the development machine (e.g., cdr[api]-dev.cancer.gov)
 *
 * The original for this file was generated by a Visual Studio MFC
 * wizard.  Don't mess with the macros unless you really know what
 * you're doing.
 */
class ServerSettingsDlg : public CDialog {

	DECLARE_DYNAMIC(ServerSettingsDlg)

public:
	ServerSettingsDlg(ServerSettings*, CWnd* pParent = NULL);
	virtual ~ServerSettingsDlg();

// Dialog Data
	enum { IDD = IDD_SERVER_SETTINGS };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
    CString prodCDRServer;
    CString prodAPIServer;
    CString stageCDRServer;
    CString stageAPIServer;
    CString qaCDRServer;
    CString qaAPIServer;
    CString devCDRServer;
    CString devAPIServer;
    ServerSettings* ss;
    afx_msg void OnBnClickedOk();
    virtual BOOL OnInitDialog();
};
