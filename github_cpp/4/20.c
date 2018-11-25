



#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "TowerOfHanoi.h"
#include "MainFrm.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif




BEGIN_MESSAGE_MAP(CTowerOfHanoiApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTowerOfHanoiApp::OnAppAbout)
END_MESSAGE_MAP()




CTowerOfHanoiApp::CTowerOfHanoiApp()
{
	
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_ALL_ASPECTS;
#ifdef _MANAGED
	
	
	
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	
	
	SetAppID(_T("TowerOfHanoi.AppID.NoVersion"));

	
	
}



CTowerOfHanoiApp theApp;




BOOL CTowerOfHanoiApp::InitInstance()
{
	
	
	
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	
	
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	
	if (!AfxOleInit())
	{
		AfxMessageBox(IDP_OLE_INIT_FAILED);
		return FALSE;
	}

	AfxEnableControlContainer();

	EnableTaskbarInteraction(FALSE);

	
	

	
	
	
	
	
	
	
	SetRegistryKey(_T("Local AppWizard-Generated Applications"));


	
	
	CMainFrame* pFrame = new CMainFrame;
	if (!pFrame)
		return FALSE;
	m_pMainWnd = pFrame;
	
	pFrame->LoadFrame(IDR_MAINFRAME,
		WS_OVERLAPPEDWINDOW | FWS_ADDTOTITLE, NULL,
		NULL);





	
	pFrame->ShowWindow(SW_SHOW);
	pFrame->UpdateWindow();
	return TRUE;
}

int CTowerOfHanoiApp::ExitInstance()
{
	
	AfxOleTerm(FALSE);

	return CWinApp::ExitInstance();
}






class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


void CTowerOfHanoiApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}





