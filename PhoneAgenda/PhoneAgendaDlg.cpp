
// PhoneAgendaDlg.cpp : implementation file
//

#include "pch.h"
#include "framework.h"
#include "PhoneAgenda.h"
#include "PhoneAgendaDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

// Implementation
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


// CPhoneAgendaDlg dialog



CPhoneAgendaDlg::CPhoneAgendaDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PHONEAGENDA_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CPhoneAgendaDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CPhoneAgendaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_ADD, &CPhoneAgendaDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPhoneAgendaDlg::OnBnClickedButtonDelete)
	ON_LBN_SELCHANGE(IDC_LIST_CONTACTS, &CPhoneAgendaDlg::OnLbnSelchangeListContacts)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CPhoneAgendaDlg::OnBnClickedButtonEdit)
END_MESSAGE_MAP()


// CPhoneAgendaDlg message handlers

BOOL CPhoneAgendaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
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

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CPhoneAgendaDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CPhoneAgendaDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CPhoneAgendaDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CPhoneAgendaDlg::OnLbnSelchangeListContacts()
{
	// TODO: Add your control notification handler code here
}

void CPhoneAgendaDlg::OnBnClickedButtonAdd()
{
	CString name, phone;
	GetDlgItemText(IDC_EDIT_NAME, name);
	GetDlgItemText(IDC_EDIT_PHONE, phone);

	CString contact = name + _T(" - ") + phone;

	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CONTACTS);
	pListBox->AddString(contact);

	SetDlgItemText(IDC_EDIT_NAME, _T(""));
	SetDlgItemText(IDC_EDIT_PHONE, _T(""));
}

void CPhoneAgendaDlg::OnBnClickedButtonDelete()
{
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CONTACTS);

	int selIndex = pListBox->GetCurSel();
	if (selIndex != LB_ERR)
	{
		pListBox->DeleteString(selIndex);
	}
}



void CPhoneAgendaDlg::OnBnClickedButtonEdit()
{
	CListBox* pListBox = (CListBox*)GetDlgItem(IDC_LIST_CONTACTS);

	int selIndex = pListBox->GetCurSel();
	if (selIndex != LB_ERR)
	{
		CString contact;
		pListBox->GetText(selIndex, contact);

		int delimPos = contact.Find(_T(" - "));
		CString name = contact.Left(delimPos);
		CString phone = contact.Mid(delimPos + 3);

		SetDlgItemText(IDC_EDIT_NAME, name);
		SetDlgItemText(IDC_EDIT_PHONE, phone);

		pListBox->DeleteString(selIndex);
	}
}
