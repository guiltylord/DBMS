
// MainFrm.cpp : implementation of the CMainFrame class
//

#include "pch.h"
#include "framework.h"
#include "DBMS.h"
#include "DBMSView.h"
#include "DBMSDoc.h"
#include "TreeTables.h"

#include "mysql.h"

#include <string>
#include <sstream>

#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_CREATE()
END_MESSAGE_MAP()

static UINT indicators[] =
{
	ID_SEPARATOR,           // status line indicator
	ID_INDICATOR_CAPS,
	ID_INDICATOR_NUM,
	ID_INDICATOR_SCRL,
};

// CMainFrame construction/destruction

CMainFrame::CMainFrame() noexcept
{
	// TODO: add member initialization code here
}

CMainFrame::~CMainFrame()
{
}

int CMainFrame::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CFrameWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	if (!m_wndToolBar.CreateEx(this, TBSTYLE_FLAT, WS_CHILD | WS_VISIBLE | CBRS_TOP | CBRS_GRIPPER | CBRS_TOOLTIPS | CBRS_FLYBY | CBRS_SIZE_DYNAMIC) ||
		!m_wndToolBar.LoadToolBar(IDR_MAINFRAME))
	{
		TRACE0("Failed to create toolbar\n");
		return -1;      // fail to create
	}

	if (!m_wndStatusBar.Create(this))
	{
		TRACE0("Failed to create status bar\n");
		return -1;      // fail to create
	}
	m_wndStatusBar.SetIndicators(indicators, sizeof(indicators)/sizeof(UINT));

	// TODO: Delete these three lines if you don't want the toolbar to be dockable
	m_wndToolBar.EnableDocking(CBRS_ALIGN_ANY);
	EnableDocking(CBRS_ALIGN_ANY);
	DockControlBar(&m_wndToolBar);


	return 0;
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if( !CFrameWnd::PreCreateWindow(cs) )
		return FALSE;
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return TRUE;
}

// CMainFrame diagnostics

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame message handlers


BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	// TODO: Add your specialized code here and/or call the base class
	m_wndSplitter.CreateStatic(this, 1, 2);

	m_wndSplitter.CreateView(0, 0, RUNTIME_CLASS(CTreeTables), CSize(200, 0), pContext);
	m_wndSplitter.CreateView(0, 1, RUNTIME_CLASS(CDBMSView), CSize(0, 0), pContext);

	SetActiveView((CListView*)m_wndSplitter.GetPane(0, 1));

	CDBMSDoc* pDoc = (CDBMSDoc*)GetActiveDocument();

	pDoc->m_pTree = (CTreeTables*)m_wndSplitter.GetPane(0, 0);
	pDoc->m_pView = (CDBMSView*)m_wndSplitter.GetPane(0, 1);
	return TRUE;
}

bool CMainFrame::OpenTrans()
{
	// �������� ���������� ����������
	conn = mysql_init(NULL);
	if (conn == NULL) {
		// ���� ���������� �� ������� � ������� ��������� �� ������
		fprintf(stderr, "Error: can'tcreate MySQL-descriptor\n");
		return false;
	}
	// ������������ � �������
	if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, NULL, NULL, 0)) {
		// ���� ��� ����������� ���������� ���������� � ��������
		// ���� ������ ������� ��������� �� ������
		fprintf(stderr, "Error: can'tconnecttodatabase %s\n", mysql_error(conn));
		return false;
	}
	this->conn;
	return true;
}

bool CMainFrame::CloseTrans()
{
	try {
		mysql_close(conn);
	}
	catch (...) {
		AfxMessageBox(L"Transaction closing is invalid");
		return false;
	}
	return true;
}

bool CMainFrame::SendQuery(string query)
{
	if (mysql_query(conn, query.c_str()) == 0)
		return true;
	return false;
}

void CMainFrame::SelectAllFromTable(string table)
{
	string sql = "SELECT * FROM " + table;

	vector<MYSQL_ROW>* data = new vector<MYSQL_ROW>();
	int result = mysql_query(conn, table.c_str());
}

vector<MYSQL_ROW>* CMainFrame::GetData()
{

	vector<MYSQL_ROW>* data = new vector<MYSQL_ROW>();

	if (res = mysql_store_result(conn)) {
		while (row = mysql_fetch_row(res)) {
			data->push_back(row);
		}
	}

	return data;
}

CString CMainFrame::GetId(const vector<CString>& vecData, string currTable)
{
	std::ostringstream oss;
	string query;
	if (currTable == "Clients") {
		oss << "SELECT Id FROM clients WHERE Firstname = '"
			<< CT2A(vecData[0])
			<< "' AND Lastname = '" << CT2A(vecData[1])
			<< "' AND Email = '" << CT2A(vecData[2])
			<< "' AND PhoneNumber = '" << CT2A(vecData[3])
			<< "' AND DateOfBirth = '" << CT2A(vecData[4])
			<< "' AND PassportNumber = '" << CT2A(vecData[5]) << "'";
	}

	if (currTable == "Orders") {
		oss << "SELECT Id FROM orders WHERE Date = '"
			<< CT2A(vecData[0])
			<< "' AND Peoples = " << CT2A(vecData[1])
			<< " AND Price = " << CT2A(vecData[2])
			<< " AND ClientId = (SELECT Id FROM clients WHERE Lastname = '" << CT2A(vecData[3]) << "')"
			<< " AND TourId = (SELECT Id FROM tours WHERE Title = '" << CT2A(vecData[4]) << "')";
	}

	if (currTable == "Tours") {
		oss << "SELECT Id FROM tours WHERE Title = '"
			<< CT2A(vecData[0])
			<< "' AND Location = '" << CT2A(vecData[1])
			<< "' AND DateStart = '" << CT2A(vecData[2])
			<< "' AND DateFinish = '" << CT2A(vecData[3])
			<< "' AND Price = " << CT2A(vecData[4]);
	}

	query = oss.str();

	SendQuery(query);
	auto data = GetData();

	MYSQL_ROW row = (*data)[0];
	CString id = CString(row[0]);

	return id;
}
