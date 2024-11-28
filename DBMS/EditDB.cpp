// EditDB.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
#include "afxdialogex.h"
#include "EditDB.h"


// EditDB dialog

IMPLEMENT_DYNAMIC(EditDB, CDialog)

EditDB::EditDB(CWnd* pParent /*=nullptr*/)
	: CDialog(EDIT_DB_DLG, pParent)
{

}

EditDB::~EditDB()
{
}

void EditDB::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditDB, CDialog)
END_MESSAGE_MAP()


// EditDB message handlers
