// EditDB.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
#include "afxdialogex.h"
#include "EditDB.h"
#include <string>
#include <sstream>


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
	DDX_Control(pDX, CLIENTS_EDIT_LASTNAME, e_ClientsLastName);
	DDX_Control(pDX, CLIENTS_EDIT_FIRSTNAME, e_ClientsName);
	DDX_Control(pDX, CLIENTS_TEXT_FIRSTNAME, t_ClientsName);
	DDX_Control(pDX, CLIENTS_TEXT_LASTNAME, t_ClientsLastName);
	DDX_Control(pDX, ORDERS_EDIT_DATE, e_OrdersDate);
	DDX_Control(pDX, ORDERS_TEXT_DATE, t_OrdersDate);
	DDX_Control(pDX, ORDERS_TEXT_PEOPLES, t_OrdersPeoples);
	DDX_Control(pDX, ORDERS_EDIT_PEOPLES, e_OrdersPeoples);
}


BEGIN_MESSAGE_MAP(EditDB, CDialog)
	ON_BN_CLICKED(IDOK, &EditDB::OnBnClickedOk)
END_MESSAGE_MAP()


// EditDB message handlers


void EditDB::OnEnChangeEdit1()
{
	// TODO:  If this is a RICHEDIT control, the control will not
	// send this notification unless you override the CDialog::OnInitDialog()
	// function and call CRichEditCtrl().SetEventMask()
	// with the ENM_CHANGE flag ORed into the mask.

	// TODO:  Add your control notification handler code here
}


void EditDB::OnBnClickedOk()
{
	UpdateData(TRUE);
	// TODO: Add your control notification handler code here

	CString newNameText;
	e_ClientsName.GetWindowText(newNameText);

	CString newLastNameText;
	e_ClientsLastName.GetWindowText(newLastNameText);

	std::ostringstream oss;
	oss << "UPDATE clients SET Firstname = '"
		<< CT2A(newNameText)
		<< "', Lastname = '"
		<< CT2A(newLastNameText)
		<< "' WHERE Id = "
		<< CT2A(id);


	
	query = oss.str();



	CDialog::OnOK();
}

void EditDB::ConfigureWindow()
{
	auto width = GetSystemMetrics(SM_CXSCREEN);
	auto height = GetSystemMetrics(SM_CYSCREEN);
	
	CRect rc;
	GetClientRect(&rc);
	
	MoveWindow(rc.Width(), rc.Height(), 1000, 300);

	int x1 = 10;
	int y1 = 30;

	int x2 = x1+1;
	int y2 = 10;

	/*auto p = POINT();
	p.x = 10;
	p.y = 10;*/
	if(currTable == "clients") {
		e_ClientsLastName.MoveWindow(x1, y1, 100, 20);
		e_ClientsName.MoveWindow(x1+=150, y1, 100, 20);

		t_ClientsName.MoveWindow(x2, y2, 100, 15);
		t_ClientsLastName.MoveWindow(x2 += 150, y2, 100, 15);

		


		//LastNameEdit.MoveWindow(50, 50, 100, 30);
		e_OrdersDate.ShowWindow(SW_HIDE);
		e_OrdersPeoples.ShowWindow(SW_HIDE);
		t_OrdersDate.ShowWindow(SW_HIDE);
		t_OrdersPeoples.ShowWindow(SW_HIDE);
	}
}

BOOL EditDB::OnInitDialog()
{
	CDialog::OnInitDialog();

	ConfigureWindow();
	// TODO:  Add extra initialization here

	return TRUE;  // return TRUE unless you set the focus to a control
	// EXCEPTION: OCX Property Pages should return FALSE
}
