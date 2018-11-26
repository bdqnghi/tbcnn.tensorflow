
// TowerOfHanoiDlg.cpp : ���� ����
//

#include "stdafx.h"
#include "TowerOfHanoi.h"
#include "TowerOfHanoiDlg.h"
#include "afxdialogex.h"

#include "hanoi.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ���� ���α׷� ������ ���Ǵ� CAboutDlg ��ȭ �����Դϴ�.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

// �����Դϴ�.
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


// CTowerOfHanoiDlg ��ȭ ����

CTowerOfHanoiDlg::CTowerOfHanoiDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_TOWEROFHANOI_DIALOG, pParent)
	, muiNumPlate(0)
	, mstrDebugPrint(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	// ���ǰ����� ������ �ִ� ��Ʈ���� �ʱⰪ ����.
	mpHanoi = NULL;
	muiNumPlate = 3;	// �ʱⰪ 3.
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


// CTowerOfHanoiDlg �޽��� ó����

BOOL CTowerOfHanoiDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �ý��� �޴��� "����..." �޴� �׸��� �߰��մϴ�.

	// IDM_ABOUTBOX�� �ý��� ��� ������ �־�� �մϴ�.
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

	// �� ��ȭ ������ �������� �����մϴ�.  ���� ���α׷��� �� â�� ��ȭ ���ڰ� �ƴ� ��쿡��
	//  �����ӿ�ũ�� �� �۾��� �ڵ����� �����մϴ�.
	SetIcon(m_hIcon, TRUE);			// ū �������� �����մϴ�.
	SetIcon(m_hIcon, FALSE);		// ���� �������� �����մϴ�.

	// TODO: ���⿡ �߰� �ʱ�ȭ �۾��� �߰��մϴ�.
	mctrSpinNumPlate.SetRange(1, 10);
	mpHanoi = new Hanoi(muiNumPlate, (void *)this);

	return TRUE;  // ��Ŀ���� ��Ʈ�ѿ� �������� ������ TRUE�� ��ȯ�մϴ�.
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

// ��ȭ ���ڿ� �ּ�ȭ ���߸� �߰��� ��� �������� �׸�����
//  �Ʒ� �ڵ尡 �ʿ��մϴ�.  ����/�� ���� ����ϴ� MFC ���� ���α׷��� ��쿡��
//  �����ӿ�ũ���� �� �۾��� �ڵ����� �����մϴ�.

void CTowerOfHanoiDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // �׸��⸦ ���� ����̽� ���ؽ�Ʈ�Դϴ�.

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Ŭ���̾�Ʈ �簢������ �������� ����� ����ϴ�.
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �������� �׸��ϴ�.
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
		UINT index;
		CDC *pDC = mctrPictureHanoi.GetWindowDC();	// ��ȭ���� �ȿ� �ִ� Picture control�� Device Context�� ��´�.
		CRect rect;

		// Picture Control�� ��ü�� �Ͼ������ ���´�.
		GetClientRect(&rect);
		pDC->FillSolidRect(rect, RGB(255, 255, 255));	

		// 3���� Peg�� �׸���.
		mpHanoi->DrawPeg(pDC);

		// Edit control�� ������ ������ Hanoi class�� ���� ������ ������ �ٸ��� �ٽ� �׸���.
		UpdateData(TRUE);
		if (muiNumPlate != mpHanoi->mNumPlates)
		{
			// ������ ������ �ٲ���� ������ ���ǰ����� �ʱ�ȭ�ϰ�, �ؽ�Ʈ ���â�� �����.
			mstrDebugPrint = _T("");
			mpHanoi->InitPlateStatus(muiNumPlate);
		}
		UpdateData(FALSE);

		for (index = 0; index < muiNumPlate; index++)
			mpHanoi->DrawPlate(pDC, index);
		mctrPictureHanoi.ReleaseDC(pDC);
	}
}

// ����ڰ� �ּ�ȭ�� â�� ��� ���ȿ� Ŀ���� ǥ�õǵ��� �ý��ۿ���
//  �� �Լ��� ȣ���մϴ�.
HCURSOR CTowerOfHanoiDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

// ���� ��ư�� ������ �� ����Ǵ� �̺�Ʈ �ݹ� �Լ�
void CTowerOfHanoiDlg::OnBnClickedButtonStart()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	mpHanoi->DoHanoi();
}

// ��ȭ������ DebugPrint�� Edit control�� ��Ʈ���� ǥ���Ѵ�.
void CTowerOfHanoiDlg::DebugPrint(CString msg)
{
	UpdateData(TRUE);
	mstrDebugPrint += msg;
	UpdateData(FALSE);
}

// ��ȭ���ڰ� ���� Picture control�� DC�� �����ϱ� ���� �Լ�.
CDC * CTowerOfHanoiDlg::GetDC(void)
{
	return mctrPictureHanoi.GetWindowDC();
}

void CTowerOfHanoiDlg::OnEnChangeEditNumplate()
{
	// TODO:  RICHEDIT ��Ʈ���� ���, �� ��Ʈ����
	// CDialogEx::OnInitDialog() �Լ��� ������ 
	//�ϰ� ����ũ�� OR �����Ͽ� ������ ENM_CHANGE �÷��׸� �����Ͽ� CRichEditCtrl().SetEventMask()�� ȣ������ ������
	// �� �˸� �޽����� ������ �ʽ��ϴ�.

	// TODO:  ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	// ����Ʈ ��Ʈ���� ����Ȱ��� ������ ������ ����� ���̹Ƿ�,
	// ȭ���� �ٽ� �׷��� ����� ������ ��������Ѵ�.
	Invalidate();	
}
