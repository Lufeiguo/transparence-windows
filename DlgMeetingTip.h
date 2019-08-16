#pragma once
#include "afxwin.h"
#include "WBButton.h"

// CDlgMeetingTip 对话框

class CDlgMeetingTip : public CDialog
{
	DECLARE_DYNAMIC(CDlgMeetingTip)

public:
	CDlgMeetingTip(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CDlgMeetingTip();

// 对话框数据
	enum { IDD = IDD_DIALOG_MEETINGTIP };

private:
	CStatic m_textMeeting;

	int		m_nToolBarWidth;
	int		m_nToolBarHeight;
	int		m_nDlgPos;
public:
	bool	m_bShow;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()

	virtual void OnCancel();
	virtual void OnOK();
	void InitButton();

public:
	virtual BOOL OnInitDialog();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual BOOL DestroyWindow();
	afx_msg void OnTimer(UINT nIDEvent);

	afx_msg void OnNcMouseMove(UINT nHitTest, CPoint point);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg void OnSize(UINT nType, int cx, int cy);

	void ReSetToolBarState(UINT nType, int nFlag);
	void SetKinescopeTimer(bool bKinescope);	// bKinescope: 0 Stop,  1 start
	void SetRecordRemoteTimer();
	void CloseRecordRemoteTimer();
	void ResizeButton();
	
	afx_msg void OnMove(int x, int y);
	void SetMeetingTip();
	void ReSetWindPos();

public:
	void UpdatePos();
	int GetToolDlgPos();
	void SetToolDlgPos(int pos);
};
