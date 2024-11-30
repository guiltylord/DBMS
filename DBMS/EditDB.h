#pragma once
#include "afxdialogex.h"
#include <string>
#include "MainFrm.h"


// EditDB dialog

class EditDB : public CDialog
{
	DECLARE_DYNAMIC(EditDB)

public:
	EditDB(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditDB();
	
	CString id;
	string currTable;
	string query;

	CMainFrame* pFrame;

	void ConfigureWindow();
// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EDIT_DB_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedOk();


protected:
	virtual BOOL OnInitDialog();
	CEdit e_ClientsLastName;
	CEdit e_ClientsName;
	CStatic t_ClientsName;
	CStatic t_ClientsLastName;

	CEdit e_OrdersDate;
	CEdit e_OrdersPeoples;
	CStatic t_OrdersDate;
	CStatic t_OrdersPeoples;
};
