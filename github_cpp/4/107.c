



#include "stdafx.h"
#include "TowerOfHanoi.h"
#include "TowerOfHanoiDlg.h"
#include "afxdialogex.h"

#include "hanoi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();


#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    


protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()




CTowerOfHanoiDlg::CTowerOfHanoiDlg(CWnd* pParent )
	: CDialogEx(IDD_TOWEROFHANOI_DIALOG, pParent)
	, muiNumPlate(0)
	, mstrDebugPrint(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	
	mpHanoi = NULL;
	muiNumPlate = 3;	
}

void CTowerOfHanoiDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC_HANOI, mctrPictureHanoi);
	DDX_Text(pDX, IDC_EDIT_NUMPLATE, muiNumPlate);
	DDV_MinMaxUInt(pDX, muiNumPlate, 1, 10);
	DDX_Text(pDX, IDC_EDIT_DEBUGPRINT, mstrDebugPrint);
	DDX_Control(pDX, IDC_SPIN_NUMPLATE, mctrSpinNumPlate);
}

BEGIN_MESSAGE_MAP(CTowerOfHanoiDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON_START, &CTowerOfHanoiDlg::OnBnClickedButtonStart)
	ON_EN_CHANGE(IDC_EDIT_NUMPLATE, &CTowerOfHanoiDlg::OnEnChangeEditNumplate)
END_MESSAGE_MAP()




BOOL CTowerOfHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	

	
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	
	
	SetIcon(m_hIcon, TRUE);			
	SetIcon(m_hIcon, FALSE);		

	
	mctrSpinNumPlate.SetRange(1, 10);
	mpHanoi = new Hanoi(muiNumPlate, (void *)this);

	return TRUE;  
}

void CTowerOfHanoiDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}





void CTowerOfHanoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		UINT index;
		CDC *pDC = mctrPictureHanoi.GetWindowDC();	
		CRect rect;

		
		GetClientRect(&rect);
		pDC->FillSolidRect(rect, RGB(255, 255, 255));	

		
		mpHanoi->DrawPeg(pDC);

		
		UpdateData(TRUE);
		if (muiNumPlate != mpHanoi->mNumPlates)
		{
			
			mstrDebugPrint = _T("");
			mpHanoi->InitPlateStatus(muiNumPlate);
		}
		UpdateData(FALSE);

		for (index = 0; index < muiNumPlate; index++)
			mpHanoi->DrawPlate(pDC, index);
		mctrPictureHanoi.ReleaseDC(pDC);
	}
}



HCURSOR CTowerOfHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTowerOfHanoiDlg::OnBnClickedButtonStart()
{
	
	mpHanoi->DoHanoi();
}


void CTowerOfHanoiDlg::DebugPrint(CString msg)
{
	UpdateData(TRUE);
	mstrDebugPrint += msg;
	UpdateData(FALSE);
}


CDC * CTowerOfHanoiDlg::GetDC(void)
{
	return mctrPictureHanoi.GetWindowDC();
}

void CTowerOfHanoiDlg::OnEnChangeEditNumplate()
{
	
	
	
	

	
	
	
	Invalidate();	
}
