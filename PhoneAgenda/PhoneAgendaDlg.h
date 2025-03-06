
// PhoneAgendaDlg.h : header file
//

#pragma once
#include <vector>
#include "Contact.h"
#include "DatabaseConnection.h"


// CPhoneAgendaDlg dialog
class CPhoneAgendaDlg : public CDialogEx
{
// Construction
public:
	CPhoneAgendaDlg(CWnd* pParent = nullptr);	// standard constructor

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_PHONEAGENDA_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();

	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonEdit();
	afx_msg void OnEnChangeTextSearch();
	afx_msg void OnBnClickedButtonSave();

	DECLARE_MESSAGE_MAP()

private:
	std::vector<Contact> listContacts;
	CListBox listBoxContacts;
	CEdit textSearch;
	DatabaseConnection dbConn;
	int selectedContactID;

	std::vector<Contact> SearchContacts(const CString& searchText);
	int FindContactID(const CString& selectedContact);
	void UpdateContactList();
	
};
