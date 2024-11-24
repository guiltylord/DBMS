
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


void CDBMSView::OnDraw(CDC* pDC)
{
	TRACE("OnDraw called\n");


	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	CView::OnDraw(pDC);

	CPaintDC dc(this); // device context for painting
	// TODO: Add your message handler code here
	// Do not call CListView::OnPaint() for painting messages



	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.ModifyStyle(0, LVS_REPORT);


	// Insert columns
	if (pDoc->m_bClients)
	{
		listCtrl.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Firstname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Lastname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Email"), LVCFMT_LEFT, 250);
		listCtrl.InsertColumn(4, _T("PhoneNumber"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("DateOfBirth"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(6, _T("PassportNumber"), LVCFMT_LEFT, 150);

		// Add sample data
		listCtrl.InsertItem(0, _T("01"));
		listCtrl.SetItemText(0, 1, _T("John"));
		listCtrl.SetItemText(0, 2, _T("Doe"));
		listCtrl.SetItemText(0, 3, _T("john.doe@example.com"));
		listCtrl.SetItemText(0, 4, _T("123-456-7890"));
		listCtrl.SetItemText(0, 5, _T("1980-01-01"));
		listCtrl.SetItemText(0, 6, _T("A1234567"));
	}

	// TODO: add draw code for native data here
}


void CDBMSView::OnInitialUpdate()
{
	CDBMSDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);

	CListCtrl& listCtrl = GetListCtrl();
	listCtrl.ModifyStyle(0, LVS_REPORT);

	// Insert columns
	if (pDoc->m_bClients)
	{
		CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd(); 
		if (!pFrame)
			return;

		if (!pFrame->OpenTrans())
			return;

		listCtrl.InsertColumn(0, _T("Id"), LVCFMT_LEFT, 35);
		listCtrl.InsertColumn(1, _T("Firstname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(2, _T("Lastname"), LVCFMT_LEFT, 100);
		listCtrl.InsertColumn(3, _T("Email"), LVCFMT_LEFT, 250);
		listCtrl.InsertColumn(4, _T("PhoneNumber"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(5, _T("DateOfBirth"), LVCFMT_LEFT, 150);
		listCtrl.InsertColumn(6, _T("PassportNumber"), LVCFMT_LEFT, 150);
		
		vector<MYSQL_ROW>* data = new vector<MYSQL_ROW>();
		data = pFrame->SelectAllFromTable("clients");

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
	CListView::OnInitialUpdate();
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

