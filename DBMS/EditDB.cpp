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
	DDX_Control(pDX, EDIT_C1, e_C1);
	DDX_Control(pDX, EDIT_C2, e_C2);
	DDX_Control(pDX, EDIT_C3, e_C3);
	DDX_Control(pDX, EDIT_C4, e_C4);
	DDX_Control(pDX, EDIT_C5, e_C5);
	DDX_Control(pDX, EDIT_C6, e_C6);

	DDX_Control(pDX, TEXT_C1, t_C1);
	DDX_Control(pDX, TEXT_C2, t_C2);
	DDX_Control(pDX, TEXT_C3, t_C3);
	DDX_Control(pDX, TEXT_C4, t_C4);
	DDX_Control(pDX, TEXT_C5, t_C5);
	DDX_Control(pDX, TEXT_C6, t_C6);
	DDX_Control(pDX, IDOK, btn_OK);
	DDX_Control(pDX, IDCANCEL, btn_Cancel);
}

//EDIT_C1
//EDIT_C2
//EDIT_C3
//EDIT_C4
//TEXT_C1
//TEXT_C2
//TEXT_C3
//TEXT_C4

//EDIT_C5
//EDIT_C6

//TEXT_C5
//TEXT_C6

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

	CString newNameText;
	e_C1.GetWindowText(newNameText);

	CString newLastNameText;
	e_C2.GetWindowText(newLastNameText);

	CString newEmailText;
	e_C3.GetWindowText(newEmailText);

	CString newPhoneNumberText;
	e_C4.GetWindowText(newPhoneNumberText);

	CString newDateOfBirthText;
	e_C5.GetWindowText(newDateOfBirthText);

	CString newPassportNumberText;
	e_C6.GetWindowText(newPassportNumberText);

		std::ostringstream oss;
	if (typeAccess==SHOW) {
		oss << "UPDATE clients SET "
			<< "Firstname = '" << CT2A(newNameText)
			<< "', Lastname = '" << CT2A(newLastNameText)
			<< "', Email = '" << CT2A(newEmailText)
			<< "', PhoneNumber = '" << CT2A(newPhoneNumberText)
			<< "', DateOfBirth = '" << CT2A(newDateOfBirthText)
			<< "', PassportNumber = '" << CT2A(newPassportNumberText)
			<< "' WHERE Id = " << CT2A(id);
	}

	if (typeAccess == EDIT) {
		oss << "INSERT INTO Clients(Firstname, Lastname, Email, PhoneNumber, DateOfBirth, PassportNumber) "
			<< "VALUES('" << CT2A(newNameText)
			<< "', '" << CT2A(newLastNameText)
			<< "', '" << CT2A(newEmailText)
			<< "', '" << CT2A(newPhoneNumberText)
			<< "', '" << CT2A(newDateOfBirthText)
			<< "', '" << CT2A(newPassportNumberText)
			<< "')";
	}

	query = oss.str();

	CDialog::OnOK();
}

void EditDB::ConfigureWindow()
{
	auto width = GetSystemMetrics(SM_CXSCREEN);
	auto height = GetSystemMetrics(SM_CYSCREEN);
	
	CRect rc;
	GetClientRect(&rc);
	
	int szWndX;
	int szWndY;

	int x1 = 10;
	int y1 = 30;

	int x2 = x1+1;
	int y2 = 10;

	/*auto p = POINT();
	p.x = 10;
	p.y = 10;*/
	if(currTable == "Clients") {
		szWndX = 900;
		szWndY = 200;

		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);

		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1+=150, y1, 100, 20);
		e_C3.MoveWindow(x1+=150, y1, 100, 20);
		e_C4.MoveWindow(x1+=150, y1, 100, 20);
		e_C5.MoveWindow(x1+=150, y1, 100, 20);
		e_C6.MoveWindow(x1+=150, y1, 100, 20);

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);
		t_C6.MoveWindow(x2 += 150, y2, 100, 20);

		//t_C6.ShowWindow(SW_HIDE);
		//e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);
		
		t_C1.SetWindowTextW(L"Firstname");
		t_C2.SetWindowTextW(L"Lastname");
		t_C3.SetWindowTextW(L"Email");
		t_C4.SetWindowTextW(L"PhoneNumber");
		t_C5.SetWindowTextW(L"DateOfBirth");
		t_C6.SetWindowTextW(L"PassportNumber");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
		e_C6.SetWindowTextW(C6);
		
		//LastNameEdit.MoveWindow(50, 50, 100, 30);
	}

	if (currTable == "Orders") {
		szWndX = 850;
		szWndY = 200;
		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);

		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1 += 150, y1, 100, 20);
		e_C3.MoveWindow(x1 += 150, y1, 100, 20);
		e_C4.MoveWindow(x1 += 150, y1, 100, 20);
		e_C5.MoveWindow(x1 += 150, y1, 200, 20);
		//e_C6.MoveWindow(x1 += 150, y1, 100, 20);

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);
		//t_C6.MoveWindow(x2 += 150, y2, 100, 20);

		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Date");
		t_C2.SetWindowTextW(L"Peoples");
		t_C3.SetWindowTextW(L"Total price");
		t_C4.SetWindowTextW(L"Client lastname");
		t_C5.SetWindowTextW(L"Title of tour");
		//t_C6.SetWindowTextW(L"PassportNumber");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
		//e_C6.SetWindowTextW(C6);

		//LastNameEdit.MoveWindow(50, 50, 100, 30);
	}

	if (currTable == "Tours") {
		szWndX = 750;
		szWndY = 200;

		MoveWindow((width - szWndX) / 2, (height - szWndY) / 2, szWndX, szWndY);
		e_C1.MoveWindow(x1, y1, 100, 20);
		e_C2.MoveWindow(x1 += 150, y1, 100, 20);
		e_C3.MoveWindow(x1 += 150, y1, 100, 20);
		e_C4.MoveWindow(x1 += 150, y1, 100, 20);
		e_C5.MoveWindow(x1 += 150, y1, 100, 20);
		//e_C6.MoveWindow(x1 += 150, y1, 100, 20);

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);
		//t_C6.MoveWindow(x2 += 150, y2, 100, 20);

		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Title");
		t_C2.SetWindowTextW(L"Location");
		t_C3.SetWindowTextW(L"DateStart");
		t_C4.SetWindowTextW(L"DateFinish");
		t_C5.SetWindowTextW(L"Price");
		//t_C6.SetWindowTextW(L"PassportNumber");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
		//e_C6.SetWindowTextW(C6);

		//LastNameEdit.MoveWindow(50, 50, 100, 30);
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


