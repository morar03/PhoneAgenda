
// PhoneAgendaDlg.h : header file
//

#pragma once


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
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnLbnSelchangeListContacts();
	afx_msg void OnBnClickedButtonEdit();
};
