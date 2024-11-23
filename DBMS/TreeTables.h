#pragma once


// TreeTables view
class CDBMSDoc;

class CTreeTables : public CTreeView
{
	DECLARE_DYNCREATE(CTreeTables)

protected:
	CTreeTables();           // protected constructor used by dynamic creation
	virtual ~CTreeTables();

	
public:
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif
	CDBMSDoc* m_pDoc;

	HTREEITEM m_hMain, m_hCoord, m_hSinus, m_hStreaks, m_hStreaks45, m_hBrush;

	void FillTree();
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
};

