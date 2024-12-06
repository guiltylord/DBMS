
// DBMSView.cpp : implementation of the CDBMSView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "DBMS.h"
#endif

#include "DBMSDoc.h"
#include "MainFrm.h"
#include "DBMSView.h"
#include "TreeTables.h"

#include "mysql.h"
#include "EditDB.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

class CMainFrame;
// CDBMSView

IMPLEMENT_DYNCREATE(CDBMSView, CListView)

BEGIN_MESSAGE_MAP(CDBMSView, CListView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CListView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CListView::OnFilePrintPreview)
	ON_WM_LBUTTONDBLCLK()
	ON_NOTIFY_REFLECT(NM_DBLCLK, &CDBMSView::OnNMDblclk)
	ON_WM_RBUTTONDOWN()
	ON_COMMAND(ID_ACTIONS_ADDDATA, &CDBMSView::OnActionsAdddata)
END_MESSAGE_MAP()

// CDBMSView construction/destruction

CDBMSView::CDBMSView() noexcept
{
	// TODO: add construction code here

}

CDBMSView::~CDBMSView()
{
}

BOOL CDBMSView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CListView::PreCreateWindow(cs);
}


void CDBMSView::FillTable()
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl& listCtrl = GetListCtrl();	

	if (pDoc->m_bClients) {
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Firstname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Lastname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Email"), LVCFMT_LEFT, 250);
		listCtrl.InsertColumn(4, _T("PhoneNumber"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("DateOfBirth"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(6, _T("PassportNumber"), LVCFMT_LEFT, 150);

		countColumns = 7;

		string tableName = "Clients";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bOrders) {
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Date"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Peoples"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Total price"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(4, _T("Client Lastname"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("Title of tour"), LVCFMT_LEFT, 175);

		countColumns = 6;

		string tableName = "orders";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bTours) {
		listCtrl.InsertColumn(0, _T(""), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Title"), LVCFMT_LEFT, 200);
		listCtrl.InsertColumn(2, _T("Location"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("DateStart"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(4, _T("DateFinish"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(5, _T("Price"), LVCFMT_LEFT, 100);
		
		countColumns = 6;

		string tableName = "tours";
		GetData(tableName, listCtrl);
	}
}

void CDBMSView::ClearView()
{
	CListCtrl& listCtrl = GetListCtrl();

	listCtrl.DeleteAllItems();
	for (int i = 0; i < countColumns; i++)
		listCtrl.DeleteColumn(0);
}

void CDBMSView::GetData(string tableName, CListCtrl& listCtrl)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	if (!pFrame)
		return;

	if (!pFrame->OpenTrans())
		return;

	vector<MYSQL_ROW>* data;

	if (currTable == "Orders") {
		string query = "\
			SELECT\
		o.Id AS OrderId, \
		o.Date AS OrderDate, \
		o.Peoples AS NumberOfPeople,\
		o.Price AS OrderPrice, \
		c.Lastname AS ClientLastname,\
		t.Title AS TourTitle \
			FROM orders o\
			JOIN clients c ON o.ClientId = c.Id\
			JOIN tours t ON o.TourId = t.Id";
		pFrame->SendQuery(query);
		data = pFrame->GetData();
	}
	else {
		string sql = "SELECT * FROM " + tableName;
		pFrame->SendQuery(sql);
		data = pFrame->GetData();
	}

	for (int rowNumb = 0; rowNumb < data->size(); rowNumb++) {
		MYSQL_ROW row = (*data)[rowNumb];
		CString cstrRow = CString(row[0]); //¬Œ“ “”“ «¿œŒÀÕﬂ≈“—ﬂ ¿…ƒ»ÿÕ» 
		listCtrl.InsertItem(rowNumb, cstrRow);
		for (int columnNumb = 1; columnNumb < mysql_num_fields(pFrame->res); columnNumb++) {
			cstrRow = CString(row[columnNumb]);
			
			listCtrl.SetItemText(rowNumb, columnNumb, cstrRow);
		}
	}
}

void CDBMSView::OnDraw(CDC* pDC)
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
}


void CDBMSView::OnInitialUpdate() 
{
	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.ModifyStyle(0, LVS_REPORT);
	//listCtrl.sub
}


// CDBMSView printing

BOOL CDBMSView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CDBMSView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CDBMSView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CDBMSView diagnostics

#ifdef _DEBUG
void CDBMSView::AssertValid() const
{
	CListView::AssertValid();
}

void CDBMSView::Dump(CDumpContext& dc) const
{
	CListView::Dump(dc);
}

CDBMSDoc* CDBMSView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CDBMSDoc)));
	return (CDBMSDoc*)m_pDocument;
}
#endif //_DEBUG

void CDBMSView::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CListCtrl& listCtrl = GetListCtrl();

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		EditDB dlg;

		CString strItemText = listCtrl.GetItemText(pNMItemActivate->iItem, 0);
		dlg.id = strItemText;

		dlg.C1 = listCtrl.GetItemText(pNMItemActivate->iItem, 1);
		dlg.C2 = listCtrl.GetItemText(pNMItemActivate->iItem, 2);
		dlg.C3 = listCtrl.GetItemText(pNMItemActivate->iItem, 3);
		dlg.C4 = listCtrl.GetItemText(pNMItemActivate->iItem, 4);
		dlg.C5 = listCtrl.GetItemText(pNMItemActivate->iItem, 5);
		dlg.C6 = listCtrl.GetItemText(pNMItemActivate->iItem, 6);
		
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

		dlg.currTable = currTable;
		dlg.pFrame = pFrame;
		dlg.typeAccess = EDIT;

		if (dlg.DoModal() == IDOK)
		{
			pFrame->SendQuery(dlg.query);
			ClearView();
			FillTable();
		}
	}
	
	*pResult = 0;
}


void CDBMSView::OnRButtonDown(UINT nFlags, CPoint point)
{
	CListView::OnRButtonDown(nFlags, point);
	
	ClientToScreen(&point);

	CCmdUI state;
	CMenu* pMenu = AfxGetMainWnd()->GetMenu()->GetSubMenu(2);

	state.m_pMenu = pMenu;
	state.m_nIndexMax = pMenu->GetMenuItemCount();
	for (UINT i = 0; i < state.m_nIndexMax; i++)
	{
		state.m_nIndex = i;
		state.m_nID = pMenu->GetMenuItemID(i);
		state.DoUpdate(this, FALSE);
	}

	pMenu->TrackPopupMenu(TPM_LEFTALIGN, point.x, point.y, this);

	//CListView::OnRButtonDown(nFlags, point);
}


void CDBMSView::OnActionsAdddata()
{
	// TODO: Add your command handler code here

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CListCtrl& listCtrl = GetListCtrl();

	EditDB dlg;

	dlg.currTable = currTable;
	dlg.pFrame = pFrame;
	dlg.typeAccess = ADD;


	if (dlg.DoModal() == IDOK)
	{
		pFrame->SendQuery(dlg.query);
		ClearView();
		FillTable();
	}
}
