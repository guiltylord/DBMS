
// MainFrm.h : interface of the CMainFrame class
//
#include "mysql.h"

#include <string>
#include <vector>
using namespace std;



#pragma once

class CMainFrame : public CFrameWnd
{
	
protected: // create from serialization only
	CMainFrame() noexcept;
	DECLARE_DYNCREATE(CMainFrame)

// Attributes
public:
	MYSQL_RES* res, * reslogon, * reslogoff;
// Operations
public:
	bool OpenTrans();
	bool CloseTrans();
	bool SendQuery(string query);
	vector<MYSQL_ROW>* SelectAllFromTable(string table);
// Overrides
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// Implementation
public:
	CSplitterWnd      m_wndSplitter;
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:  // control bar embedded members
	CToolBar          m_wndToolBar;
	CStatusBar        m_wndStatusBar;

	MYSQL* conn;
	MYSQL_ROW row;
// Generated message map functions
protected:
	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);

private:
	const char* HOST = "localhost";
	const char* USER = "root";
	const char* PASSWORD = "mysql";
	const char* DATABASE = "mybase";
};


