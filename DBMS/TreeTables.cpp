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
		| TVS_SHOWSELALWAYS
		| TVS_CHECKBOXES;
	if (CTreeView::OnCreate(lpCreateStruct) == -1)
		return -1;

	return 0;
}


void CTreeTables::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;

	tree.GetItemRect(m_hClients, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hClients);
		m_pDoc->m_pView->currTable = "clients";

		tree.SetCheck(m_hOrders, false);
		tree.SetCheck(m_hTours, false);
	}

	tree.GetItemRect(m_hOrders, &rc, false);
	if (rc.PtInRect(point))  {
		tree.SelectItem(m_hOrders);
		m_pDoc->m_pView->currTable = "orders";

		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hTours, false);
	}

	tree.GetItemRect(m_hTours, &rc, false);
	if (rc.PtInRect(point)) {
		tree.SelectItem(m_hTours);
		m_pDoc->m_pView->currTable = "tours";

		tree.SetCheck(m_hClients, false);
		tree.SetCheck(m_hOrders, false);
	}

	if (m_pDoc->m_bClients = tree.GetCheck(m_hClients)) {
		m_pDoc->m_bOrders = m_pDoc->m_bTours = false;

		ShowNewTable();
	}
	if (m_pDoc->m_bOrders = tree.GetCheck(m_hOrders)) {
		m_pDoc->m_bClients = m_pDoc->m_bTours = false;

		ShowNewTable();
	}
	if (m_pDoc->m_bTours = tree.GetCheck(m_hTours)) {
		m_pDoc->m_bClients = m_pDoc->m_bOrders = false;

		ShowNewTable();
	}
}

void CTreeTables::ShowNewTable()
{
	m_pDoc->m_pView->ClearView();
	m_pDoc->m_pView->FillTable();
}
