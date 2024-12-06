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

	CString newC1;
	e_C1.GetWindowText(newC1);

	CString newC2;
	e_C2.GetWindowText(newC2);

	CString newC3;
	e_C3.GetWindowText(newC3);

	CString newC4;
	e_C4.GetWindowText(newC4);

	CString newC5;
	e_C5.GetWindowText(newC5);

	CString newC6;
	e_C6.GetWindowText(newC6);

	std::ostringstream oss;
	if (typeAccess == EDIT) {
		if (currTable == "Clients") {
			oss << "UPDATE clients SET "
				<< "Firstname = '" << CT2A(newC1)
				<< "', Lastname = '" << CT2A(newC2)
				<< "', Email = '" << CT2A(newC3)
				<< "', PhoneNumber = '" << CT2A(newC4)
				<< "', DateOfBirth = '" << CT2A(newC5)
				<< "', PassportNumber = '" << CT2A(newC6)
				<< "' WHERE Id = " << CT2A(id);
		}
		if (currTable == "Orders") {
			oss << "UPDATE orders "
				<< "SET Date = '" << CT2A(newC1) << "', "
				<< "Peoples = " << CT2A(newC2) << ", "
				<< "Price = " << CT2A(newC3) << ", "
				<< "ClientId = (SELECT Id FROM clients WHERE Lastname = '" << CT2A(newC4) << "'), "
				<< "TourId = (SELECT Id FROM tours WHERE Title = '" << CT2A(newC5) << "') "
				<< "WHERE Id = " << CT2A(id);
		}
		if (currTable == "Tours") {
			oss << "UPDATE tours SET "
				<< "Title = '" << CT2A(newC1)
				<< "', Location = '" << CT2A(newC2)
				<< "', DateStart = '" << CT2A(newC3)
				<< "', DateFinish = '" << CT2A(newC4)
				<< "', Price = '" << CT2A(newC5)
				<< "' WHERE Id = " << CT2A(id);
		}
	}

	if (typeAccess == ADD) {
		if(currTable == "Clients") {
			oss << "INSERT INTO Clients(Firstname, Lastname, Email, PhoneNumber, DateOfBirth, PassportNumber) "
				<< "VALUES('" << CT2A(newC1)
				<< "', '" << CT2A(newC2)
				<< "', '" << CT2A(newC3)
				<< "', '" << CT2A(newC4)
				<< "', '" << CT2A(newC5)
				<< "', '" << CT2A(newC6)
				<< "')";
		}
		if(currTable == "Orders") {
			oss << "INSERT INTO orders (Date, Peoples, Price, ClientId, TourId) "
				<< "VALUES ('" << CT2A(newC1) << "', " << CT2A(newC2) << ", " << CT2A(newC3) << ", " 
				<< "(SELECT Id FROM clients WHERE Lastname = '"  << CT2A(newC4) << "'), "
				<< "(SELECT Id FROM tours WHERE Title = '" << CT2A(newC5) << "'))";
		}
		if (currTable == "Tours") {
			oss << "INSERT INTO tours (Title, Location, DateStart, DateFinish, Price) "
				<< "VALUES ('"
				<< CT2A(newC1)
				<< "', '" << CT2A(newC2)
				<< "', '" << CT2A(newC3)
				<< "', '" << CT2A(newC4)
				<< "', " << CT2A(newC5)
				<< ")";
		}
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

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);

		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Date");
		t_C2.SetWindowTextW(L"Peoples");
		t_C3.SetWindowTextW(L"Total price");
		t_C4.SetWindowTextW(L"Client lastname");
		t_C5.SetWindowTextW(L"Title of tour");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
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

		t_C1.MoveWindow(x2, y2, 100, 15);
		t_C2.MoveWindow(x2 += 150, y2, 100, 15);
		t_C3.MoveWindow(x2 += 150, y2, 100, 20);
		t_C4.MoveWindow(x2 += 150, y2, 100, 20);
		t_C5.MoveWindow(x2 += 150, y2, 100, 20);

		t_C6.ShowWindow(SW_HIDE);
		e_C6.ShowWindow(SW_HIDE);

		btn_Cancel.MoveWindow(szWndX - 100, 100, 75, 30);
		btn_OK.MoveWindow(szWndX - 200, 100, 75, 30);

		t_C1.SetWindowTextW(L"Title");
		t_C2.SetWindowTextW(L"Location");
		t_C3.SetWindowTextW(L"DateStart");
		t_C4.SetWindowTextW(L"DateFinish");
		t_C5.SetWindowTextW(L"Price");

		e_C1.SetWindowTextW(C1);
		e_C2.SetWindowTextW(C2);
		e_C3.SetWindowTextW(C3);
		e_C4.SetWindowTextW(C4);
		e_C5.SetWindowTextW(C5);
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


