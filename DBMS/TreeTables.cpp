// TreeTables.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
#include "DBMSDoc.h"
#include "DBMSView.h"
#include "TreeTables.h"


// TreeTables
IMPLEMENT_DYNCREATE(CTreeTables, CTreeView)

CTreeTables::CTreeTables()
{
}

CTreeTables::~CTreeTables()
{
}

BEGIN_MESSAGE_MAP(CTreeTables, CTreeView)
	ON_WM_CREATE()
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// TreeTables diagnostics

#ifdef _DEBUG
void CTreeTables::FillTree()
{
	CTreeCtrl& tree = GetTreeCtrl();

	tree.DeleteAllItems();

	m_hClients = tree.InsertItem(L"Clients", -1, -1, NULL, TVI_ROOT);
	m_hOrders = tree.InsertItem(L"Orders", -1, -1, NULL, TVI_ROOT);
	m_hTours = tree.InsertItem(L"Tours", -1, -1, NULL, TVI_ROOT);

	tree.SetCheck(m_hClients, m_pDoc->m_bClients);
	tree.SetCheck(m_hOrders, m_pDoc->m_bOrders);
	tree.SetCheck(m_hTours, m_pDoc->m_bTours);
}


void CTreeTables::AssertValid() const
{
	CTreeView::AssertValid();
}


#ifndef _WIN32_WCE
void CTreeTables::Dump(CDumpContext& dc) const
{
	CTreeView::Dump(dc);
}
#endif
#endif //_DEBUG


// TreeTables message handlers


int CTreeTables::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	lpCreateStruct->style |= TVS_HASLINES
		| TVS_HASBUTTONS
		| TVS_LINESATROOT
		| TVS_SHOWSELALWAYS;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CTreeTables::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;
	auto selTreeItem = tree.GetSelectedItem();
	if (selTreeItem == nullptr) {
		return;
	}
	auto selTable = tree.GetItemText(selTreeItem);
	if (selTable == "Clients") {
		m_pDoc->m_bClients = true;
		m_pDoc->m_pView->currTable = "Clients";
		m_pDoc->m_bOrders = m_pDoc->m_bTours = false;
	}
	
	if (selTable == "Orders") {
		m_pDoc->m_bOrders = true;
		m_pDoc->m_pView->currTable = "Orders";
		m_pDoc->m_bClients = m_pDoc->m_bTours = false;
	}

	if (selTable == "Tours") {
		m_pDoc->m_bTours = true;
		m_pDoc->m_pView->currTable = "Tours";
		m_pDoc->m_bClients = m_pDoc->m_bOrders = false;
	}
	
	ShowNewTable();
}

void CTreeTables::ShowNewTable()
{
	m_pDoc->m_pView->ClearView();
	m_pDoc->m_pView->FillTable();
}

