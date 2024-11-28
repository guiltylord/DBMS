#pragma once
#include "afxdialogex.h"


// EditDB dialog

class EditDB : public CDialog
{
	DECLARE_DYNAMIC(EditDB)

public:
	EditDB(CWnd* pParent = nullptr);   // standard constructor
	virtual ~EditDB();

// Dialog Data
#ifdef AFX_DESIGN_TIME
	enum { IDD = EDIT_DB_DLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
};
