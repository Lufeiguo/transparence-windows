// FullScreenToolbarDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "HPMeeting.h"
#include "DlgMeetingTip.h"
#include ".\DlgMeetingTip.h"
#include "Meeting.h"
#include "DlgMember.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

// Add Han Huajie  全屏模式下的工具条
// CDlgMeetingTip 对话框

IMPLEMENT_DYNAMIC(CDlgMeetingTip, CDialog)
CDlgMeetingTip::CDlgMeetingTip(CWnd* pParent /*=NULL*/)
	: CDialog(CDlgMeetingTip::IDD, pParent)
	, m_nToolBarWidth(600)
	, m_nToolBarHeight(60)
	, m_bShow(false)
	, m_nDlgPos(0)
{
}

CDlgMeetingTip::~CDlgMeetingTip()
{
}

void CDlgMeetingTip::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_STATIC_TEXT, m_textMeeting);
}


BEGIN_MESSAGE_MAP(CDlgMeetingTip, CDialog)
	//ON_WM_LBUTTONDOWN()
	ON_WM_NCHITTEST()
	ON_WM_ERASEBKGND()
	ON_WM_TIMER()
	ON_WM_NCMOUSEMOVE()
	ON_WM_MOVE()
	ON_WM_CTLCOLOR()
	ON_WM_SIZE()
END_MESSAGE_MAP()


// CDlgMeetingTip 消息处理程序

void CDlgMeetingTip::OnCancel()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnCancel();
}

void CDlgMeetingTip::OnOK()
{
	// TODO: 在此添加专用代码和/或调用基类

	//CDialog::OnOK();
}

void CDlgMeetingTip::InitButton()
{
}

void CDlgMeetingTip::ResizeButton()
{
}

BOOL CDlgMeetingTip::OnInitDialog()
{
	CDialog::OnInitDialog();
	// TODO:  在此添加额外的初始化

	LONG para = GetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE);

	para |= WS_EX_LAYERED;

	SetWindowLong(this->GetSafeHwnd(), GWL_EXSTYLE, para);
	SetLayeredWindowAttributes(RGB(255,255,255), 180, LWA_COLORKEY);
	SetMeetingTip();
	//SetTimer(3500, 3500, NULL);
	//SetTimer(3501, 1000, NULL);
	m_bShow = false;


	CRect rc;
	rc = CMeeting::Instance()->m_rNotify.GetInitially_TempletRect();

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常: OCX 属性页应返回 FALSE
}

LRESULT CDlgMeetingTip::OnNcHitTest(CPoint point)
{
	int ret = CDialog::OnNcHitTest(point);
	if( HTCAPTION == ret)
		return HTCLIENT;
	return ret;
}

BOOL CDlgMeetingTip::OnEraseBkgnd(CDC* pDC)	
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值

	//return CDialog::OnEraseBkgnd(pDC);

	CPaintDC dc(this);

	RECT rect;

	GetClientRect(&rect);

	dc.FillSolidRect(&rect, RGB(255, 255, 255));

	return TRUE;
}

BOOL CDlgMeetingTip::DestroyWindow()
{
	return CDialog::DestroyWindow();
}

void CDlgMeetingTip::OnTimer(UINT nIDEvent)
{
	
	if (3500 == nIDEvent && IsWindowVisible())
	{
		CRect		rc;
		GetWindowRect(&rc);

		CPoint point;
		CRect rcClient;
		GetCursorPos(&point);
		GetClientRect(&rcClient);
		ScreenToClient(&point);

		if(!rcClient.PtInRect(point))
		{
			if (rc.top>=0)
				SetWindowPos(&wndTopMost, rc.left, rc.top, rc.Width(), 5, SWP_NOMOVE|SWP_SHOWWINDOW|SWP_NOACTIVATE);
			else
				SetWindowPos(&wndTopMost, rc.left, 0, rc.Width(), 5, SWP_SHOWWINDOW|SWP_NOACTIVATE);
		}
	}
	if (3501 == nIDEvent && IsWindowVisible())
	{
		CRect rc_screen(0,0,0,0);
		CRect rc;
		rc = CMeeting::Instance()->m_rNotify.GetInitially_TempletRect();
		CWnd* p = GetParent();
		p->GetWindowRect(&rc_screen);
		TEXTMETRIC tm;
		CWnd* p1 = GetDlgItem(IDC_STATIC_TEXT);
		CDC* pdc = p1->GetDC();
		pdc->GetTextMetrics(&tm);//获取当前文本的信息，高度、宽度等
		CString csMeetingName;
		p1->GetWindowText(csMeetingName);
		CSize sz = this->GetDC()->GetTextExtent(csMeetingName);
		::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,rc.right - sz.cx, rc.bottom - sz.cy*4, m_nToolBarWidth, m_nToolBarHeight,SWP_SHOWWINDOW|SWP_NOACTIVATE);

		CRect rcthis;
		this->GetWindowRect(rcthis);
		::SetWindowPos(p1->GetSafeHwnd(),HWND_TOPMOST,rcthis.right - sz.cx, rcthis.bottom - sz.cy*4, m_nToolBarWidth, m_nToolBarHeight,SWP_SHOWWINDOW|SWP_NOACTIVATE);
	}
	CDialog::OnTimer(nIDEvent);
}

void CDlgMeetingTip::OnNcMouseMove(UINT nHitTest, CPoint point)
{
	CRect	rc;
	GetWindowRect(&rc);

	SetWindowPos(&wndTopMost, rc.left, rc.top, m_nToolBarWidth, m_nToolBarHeight,  SWP_SHOWWINDOW|SWP_NOACTIVATE);

	CDialog::OnNcMouseMove(nHitTest, point);
}

HBRUSH CDlgMeetingTip::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialog::OnCtlColor(pDC, pWnd, nCtlColor);
	if (pWnd->GetDlgCtrlID() == IDC_STATIC_TEXT)
	{
		pDC->SetBkMode(TRANSPARENT); //设置字体背景为透明 
		pDC->SetTextColor(RGB(245,245,245));  //设置字体颜色
		
		// TODO: Return a different brush if the default is not desired
		return (HBRUSH)::GetStockObject(HOLLOW_BRUSH);  // 设置背景色 
	} 
	else 
		return hbr;
}

void CDlgMeetingTip::OnSize(UINT nType, int cx, int cy)
{
	CDialog::OnSize(nType, cx, cy);
	CRgn rgn;
	CRect rc;
	GetWindowRect(&rc);
	rc-=rc.TopLeft();
	rgn.CreateRoundRectRgn(rc.left,rc.top,rc.right,rc.bottom,10,10);
	//rgn.CreateEllipticRgn(rc.left,rc.top,rc.right,rc.bottom);//椭圆
	SetWindowRgn(rgn,TRUE);
}

void CDlgMeetingTip::OnMove(int x, int y)
{
	CDialog::OnMove(x, y);

	return;
	// TODO: 在此处添加消息处理程序代码
	DISPLAY_DEVICE dev = { sizeof(DISPLAY_DEVICE) };
	BOOL bNext = FALSE;
	DEVMODE devmode;
	int index = 0;

	CArray<CRect,CRect> arr;
	while (true)
	{
		bNext = EnumDisplayDevices(NULL, index, &dev, 0);
		if (bNext == FALSE)
		{
			break;
		}
		if (dev.StateFlags & DISPLAY_DEVICE_ATTACHED_TO_DESKTOP ||  dev.StateFlags & DISPLAY_DEVICE_PRIMARY_DEVICE)
		{
			EnumDisplaySettings(dev.DeviceName, ENUM_CURRENT_SETTINGS, &devmode);
			arr.Add(CRect(devmode.dmPosition.x,devmode.dmPosition.y,devmode.dmPosition.x+devmode.dmPelsWidth, devmode.dmPosition.y+devmode.dmPelsHeight));
		}
		index++;
	}
	CRect rect;
	GetWindowRect(&rect);
	BOOL flag=FALSE;
	for(int i=0;i<arr.GetCount();i++)
	{
		if(flag)
		{
			if((arr[i-1].right-rect.left)<rect.Width()/2)
			{
				int y=rect.top;
				if(y>arr[i].bottom-rect.Height())
				{
					y=0;
				}
				m_nDlgPos=i;
				SetWindowPos(&wndTopMost, arr[i].right-rect.Width(), y, rect.Width(),rect.Height(),SWP_NOACTIVATE|SWP_SHOWWINDOW);
			}
			else
			{
				int y=rect.top;
				if(y>arr[i-1].bottom-rect.Height())
				{
					y=0;
				}
				m_nDlgPos=i-1;
				SetWindowPos(&wndTopMost, arr[i-1].right-rect.Width(), y, rect.Width(),rect.Height(),SWP_NOACTIVATE|SWP_SHOWWINDOW);
			}
			break;
		}
		else if(arr[i].PtInRect(rect.TopLeft()))
		{
			if(arr[i].PtInRect(CPoint(rect.right, rect.top)))
			{
				m_nDlgPos=i;
				break;
			}
			else
			{
				flag=TRUE;
			}
		}
	}
	
	GetDlgItem(IDC_STATIC_TEXT)->RedrawWindow();
}

void CDlgMeetingTip::SetMeetingTip()
{
	string strName = CMeeting::Instance()->GetCurRoomName();
	CString csMeetingName = A2U(strName);
	csMeetingName.Format(_T("会议中-%s"), A2U(strName));
	int n = strName.length();
	if (n>20)
	{
		CString strTmp = csMeetingName.Left(20);
		csMeetingName.Format(_T("%s..."), strTmp);

	}
	if (NULL != m_textMeeting.GetSafeHwnd())
	{
		m_textMeeting.SetWindowText(csMeetingName);
		m_textMeeting.RedrawWindow();
	}
}

void CDlgMeetingTip::ReSetWindPos()
{
	CRect rc;
	rc = CMeeting::Instance()->m_rNotify.GetInitially_TempletRect();
	::SetWindowPos(this->GetSafeHwnd(),HWND_TOPMOST,rc.right - m_nToolBarWidth, rc.bottom - m_nToolBarHeight, m_nToolBarWidth, m_nToolBarHeight, SWP_NOACTIVATE);
}

void CDlgMeetingTip::UpdatePos()
{
	ReSetWindPos();
}

int CDlgMeetingTip::GetToolDlgPos()
{
	return m_nDlgPos;
}

void CDlgMeetingTip::SetToolDlgPos(int pos)
{
	m_nDlgPos = pos;
}
