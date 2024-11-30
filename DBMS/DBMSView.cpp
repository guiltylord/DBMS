
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
		listCtrl.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Firstname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Lastname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Email"), LVCFMT_LEFT, 250);
		listCtrl.InsertColumn(4, _T("PhoneNumber"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("DateOfBirth"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(6, _T("PassportNumber"), LVCFMT_LEFT, 150);

		countColumns = 7;

		string tableName = "clients";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bOrders) {
		listCtrl.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Date"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Peoples"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Total price"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(4, _T("ClientId"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(5, _T("TourId"), LVCFMT_LEFT, 100);

		countColumns = 6;

		string tableName = "orders";
		GetData(tableName, listCtrl);
	}

	if (pDoc->m_bTours) {
		listCtrl.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 35);
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

	vector<MYSQL_ROW>* data = pFrame->SelectAllFromTable(tableName);

	for (int rowNumb = 0; rowNumb < data->size(); rowNumb++) {
		MYSQL_ROW row = (*data)[rowNumb];
		CString cstrRow = CString(row[0]);
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



//void CDBMSView::OnLButtonDblClk(UINT nFlags, CPoint point)
//{
	//CListView::OnLButtonDblClk(nFlags, point);
	//// TODO: Add your message handler code here and/or call default
	//CListCtrl& listCtrl = GetListCtrl();
	//CString str;

	//LVHITTESTINFO info;
	//info.pt = point;
	//info.flags = LVHT_ONITEMLABEL;

	//if (listCtrl->SubItemHitTest(&info) >= 0)
	//{
	//	int row = info.iItem;
	//	int column = info.iSubItem;

	//	CRect rect;
	//	pTable->GetSubItemRect(row, column, LVIR_LABEL, rect);



	//	m_selectedCellIndex = info.iItem;


	//	switch (m_pTreeView->GetSelectedItem())
	//	{
	//	case drivers_tbl:
	//		break;
	//	case cars_tbl:
	//	{
	//		CCarRowEditorDlg dlg;
	//		dlg.GetVars(pTable->GetItemText(info.iItem, 0), pTable->GetItemText(info.iItem, 1));
	//		dlg.DoModal();

	//		break;
	//	}

	//	case routes_tbl:
	//		break;
	//	}
	//	Invalidate();

	//}
//}







void CDBMSView::OnNMDblclk(NMHDR* pNMHDR, LRESULT* pResult)
{

	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();

	CListCtrl& listCtrl = GetListCtrl();

	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	if (pNMItemActivate->iItem != -1)
	{
		CString strItemText = listCtrl.GetItemText(pNMItemActivate->iItem, 0);
		string str= CT2A(strItemText); //convert to str
		
		EditDB dlg;
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();


		dlg.id = strItemText;
		dlg.currTable = currTable;
		dlg.pFrame = pFrame;

		if (dlg.DoModal() == IDOK)
		{
			pFrame->SendQuery(dlg.query);
			ClearView();
			FillTable();
		}
	}


	*pResult = 0;
}
