// TreeTables.cpp : implementation file
//

#include "pch.h"
#include "DBMS.h"
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
	m_hMain = tree.InsertItem(L"Tables", -1, -1, NULL, TVI_FIRST);

	m_hClients = tree.InsertItem(L"Clients", -1, -1, m_hMain, TVI_FIRST);
	m_hOrders = tree.InsertItem(L"Orders", -1, -1, m_hMain, TVI_ROOT);
	m_hTours = tree.InsertItem(L"Tours", -1, -1, m_hMain, TVI_ROOT);

	tree.Expand(m_hMain, TVE_EXPAND);

	//tree.SetCheck(m_hCoord, m_pDoc->m_bCoord);
	//tree.SetCheck(m_hSinus, m_pDoc->m_bSinus);
	//tree.SetCheck(m_hStreaks, m_pDoc->m_bStreaks);
	//tree.SetCheck(m_hStreaks45, m_pDoc->m_bStreaks45);
	//tree.SetCheck(m_hBrush, m_pDoc->m_bBrush);
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

	// TODO:  Добавьте специализированный код создания

	return 0;
}


void CTreeTables::OnLButtonDown(UINT nFlags, CPoint point)
{
	CTreeView::OnLButtonDown(nFlags, point);

	CTreeCtrl& tree = GetTreeCtrl();
	CRect rc;

	tree.GetItemRect(m_hClients, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hClients);

	tree.GetItemRect(m_hOrders, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hOrders);

	tree.GetItemRect(m_hTours, &rc, false);
	if (rc.PtInRect(point))
		tree.SelectItem(m_hTours);

	tree.GetItemRect(m_hMain, &rc, false);
	if (rc.PtInRect(point))
	{
		bool check = tree.GetCheck(m_hMain);
		tree.SetCheck(m_hClients, check);
		tree.SetCheck(m_hOrders, check);
		tree.SetCheck(m_hTours, check);
	}
	else
		tree.SetCheck(m_hMain, false);

	/*m_pDoc->m_bCoord = tree.GetCheck(m_hCoord);
	m_pDoc->m_bSinus = tree.GetCheck(m_hSinus);
	m_pDoc->m_bStreaks = tree.GetCheck(m_hStreaks);
	m_pDoc->m_bStreaks45 = tree.GetCheck(m_hStreaks45);
	m_pDoc->m_bBrush = tree.GetCheck(m_hBrush);

	m_pDoc->m_pView->Invalidate();*/


	CTreeView::OnLButtonDown(nFlags, point);
}
