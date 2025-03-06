
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
	DDX_Control(pDX, IDC_LIST_CONTACTS, listBoxContacts);
	DDX_Control(pDX, IDC_TEXT_SEARCH, textSearch);
}

BEGIN_MESSAGE_MAP(CPhoneAgendaDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(ID_BUTTON_ADD, &CPhoneAgendaDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CPhoneAgendaDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, &CPhoneAgendaDlg::OnBnClickedButtonEdit)
	ON_EN_CHANGE(IDC_TEXT_SEARCH, &CPhoneAgendaDlg::OnEnChangeTextSearch)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CPhoneAgendaDlg::OnBnClickedButtonSave)
END_MESSAGE_MAP()


// CPhoneAgendaDlg message handlers

BOOL CPhoneAgendaDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_HIDE);

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

	CString dsn = _T("test");
	CString user = _T("admin");
	CString password = _T("admin");


	if (dbConn.OpenConnection(dsn, user, password))
	{
		if (!dbConn.CreateContactsTable())
		{
			AfxMessageBox(_T("Could not establish connection to database!"));
		}
	}
	else
	{
		AfxMessageBox(_T("Creating the Contacts table failed!"));
	}

	dbConn.LoadContacts(listContacts);
	UpdateContactList();

	return TRUE; 
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


void CPhoneAgendaDlg::OnBnClickedButtonAdd()
{
	CString firstName, lastName, phone;
	GetDlgItemText(IDC_EDIT_FIRST_NAME, firstName);
	GetDlgItemText(IDC_EDIT_LAST_NAME, lastName);
	GetDlgItemText(IDC_EDIT_PHONE, phone);

	if (firstName.IsEmpty())
	{
		AfxMessageBox(_T("First name cannot be empty."));
		return;
	}

	if (lastName.IsEmpty())
	{
		AfxMessageBox(_T("Last name cannot be empty."));
		return;
	}

	if (phone.GetLength() != 10)
	{
		AfxMessageBox(_T("Phone number must have exactly 10 digits."));
		return;
	}

	if (dbConn.AddContact(firstName, lastName, phone))
	{
		AfxMessageBox(_T("Contact added successfully!"));
		dbConn.LoadContacts(listContacts);
		UpdateContactList();
	}
	else
	{
		AfxMessageBox(_T("Failed to add contact from database."));
	}
	

	SetDlgItemText(IDC_EDIT_FIRST_NAME, _T(""));
	SetDlgItemText(IDC_EDIT_LAST_NAME, _T(""));
	SetDlgItemText(IDC_EDIT_PHONE, _T(""));
}

void CPhoneAgendaDlg::OnBnClickedButtonDelete()
{
	int selIndex = listBoxContacts.GetCurSel();

	if (selIndex != LB_ERR)
	{
		CString selectedContact;
		listBoxContacts.GetText(selIndex, selectedContact);

		int contactID = FindContactID(selectedContact);
		if (contactID != -1)
		{
			if (dbConn.DeleteContact(contactID))
			{
				AfxMessageBox(_T("Contact deleted successfully!"));
				dbConn.LoadContacts(listContacts);
				UpdateContactList();
			}
			else
			{
				AfxMessageBox(_T("Failed to delete contact from database."));
			}
		}
		else
		{
			AfxMessageBox(_T("Could not find the contact in the list."));
		}
	}
}

void CPhoneAgendaDlg::UpdateContactList()
{
	listBoxContacts.ResetContent();

	for (const auto& contact : listContacts)
	{
		listBoxContacts.AddString(contact.ToString());
	}
}

void CPhoneAgendaDlg::OnBnClickedButtonEdit()
{
	int selIndex = listBoxContacts.GetCurSel();

	if (selIndex != LB_ERR)
	{
		CString selectedContact;
		listBoxContacts.GetText(selIndex, selectedContact);

		int delimPosPhone = selectedContact.Find(_T(" - "));
		CString name = selectedContact.Left(delimPosPhone);
		CString phone = selectedContact.Mid(delimPosPhone + 3);
		int delimPosName = name.Find(_T(" "));
		CString firstName = name.Left(delimPosName);
		CString lastName = name.Mid(delimPosName+1);

		SetDlgItemText(IDC_EDIT_FIRST_NAME, firstName);
		SetDlgItemText(IDC_EDIT_LAST_NAME, lastName);
		SetDlgItemText(IDC_EDIT_PHONE, phone);

		selectedContactID = FindContactID(selectedContact);

		GetDlgItem(ID_BUTTON_ADD)->ShowWindow(SW_HIDE);
		GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_SHOW);
		UpdateContactList();
	}
}

void CPhoneAgendaDlg::OnBnClickedButtonSave()
{
	CString firstName, lastName, phone;
	GetDlgItemText(IDC_EDIT_FIRST_NAME, firstName);
	GetDlgItemText(IDC_EDIT_LAST_NAME, lastName);
	GetDlgItemText(IDC_EDIT_PHONE, phone);

	if (firstName.IsEmpty())
	{
		AfxMessageBox(_T("First name cannot be empty."));
		return;
	}
	if (lastName.IsEmpty())
	{
		AfxMessageBox(_T("Last name cannot be empty."));
		return;
	}
	if (phone.GetLength() != 10)
	{
		AfxMessageBox(_T("Phone number must have exactly 10 digits."));
		return;
	}

	if (dbConn.UpdateContact(selectedContactID, firstName, lastName, phone))
	{
		AfxMessageBox(_T("Contact updated successfully!"));
		dbConn.LoadContacts(listContacts);
		UpdateContactList();

		SetDlgItemText(IDC_EDIT_FIRST_NAME, _T(""));
		SetDlgItemText(IDC_EDIT_LAST_NAME, _T(""));
		SetDlgItemText(IDC_EDIT_PHONE, _T(""));

		GetDlgItem(ID_BUTTON_ADD)->ShowWindow(SW_SHOW);
		GetDlgItem(IDC_BUTTON_SAVE)->ShowWindow(SW_HIDE);
	}
	else
	{
		AfxMessageBox(_T("Failed to update contact."));
	}

}

void CPhoneAgendaDlg::OnEnChangeTextSearch()
{
	CString searchText;
	textSearch.GetWindowText(searchText);

	std::vector<Contact> filteredContacts = SearchContacts(searchText);
	listBoxContacts.ResetContent();
	for (const auto& contact : filteredContacts)
	{
		listBoxContacts.AddString(contact.ToString());
	}
}

std::vector<Contact> CPhoneAgendaDlg::SearchContacts(const CString& searchText)
{
	std::vector<Contact> filteredContacts;
	CString lowerSearchQuery = searchText;
	lowerSearchQuery.MakeLower();

	for (const auto& contact : listContacts)
	{
		CString contactString = contact.ToString();
		contactString.MakeLower();

		if (contactString.Find(lowerSearchQuery) != -1) 
		{
			filteredContacts.push_back(contact);
		}
	}

	return filteredContacts;
}

int CPhoneAgendaDlg::FindContactID(const CString& selectedContact)
{
	for (const auto& contact : listContacts)
	{
		if (contact.ToString() == selectedContact)
		{
			return contact.GetID();
		}
	}
	return -1;
}

