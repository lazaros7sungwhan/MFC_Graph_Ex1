#include "pch.h"
#include "child.h"
#include "iostream"

IMPLEMENT_DYNAMIC(child, CWnd)
child::child(){
	m_main_grid = RGB(0, 255, 0);
	m_max = 100;
	m_min = -100;
}
child::~child(){}
BEGIN_MESSAGE_MAP(child,CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


int child::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1)
		return -1;

	CRect r; 
	GetClientRect(r);
	m_displayWnd.CreateEx(0, NULL, NULL, WS_CHILD | WS_VISIBLE, CRect(50, r.top + 20, r.right - 50, r.bottom - 25), this, 25000);

	return 0;
}


void child::OnDestroy()
{
	CWnd::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}




void child::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	CRect r, graph_rect;
	GetClientRect(r);
	dc.FillSolidRect(r, RGB(50, 50, 50));

	CPen main_grid_pen(PS_SOLID, 1, m_main_grid);
	CPen* p_old_pen = dc.SelectObject(&main_grid_pen);

	dc.MoveTo(r.right - 50, r.top + 20);
	dc.LineTo(r.right - 50, r.bottom-15);

	dc.MoveTo(50, r.bottom - 25);
	dc.LineTo(r.right - 40, r.bottom - 25);

	CFont* p_Old_font = dc.SelectObject(&g_default_font);
	int old_mode = dc.SetBkMode(TRANSPARENT);
	dc.SetTextColor(RGB(255, 255, 255));

	CString str;
	str.Format(_T("current : %7.2f"), m_displayWnd.getCurrentData());
	dc.TextOutW(10, r.bottom - 20, str);

	m_displayWnd.GetWindowRect(graph_rect);
	ScreenToClient(graph_rect);	
	double step = graph_rect.Height() / 10.0;
	double value_step = (m_max - m_min) / 10.0;
	int font_height = dc.GetTextExtent(_T("A")).cy;
	for (int i = 0; i < 11; i++)
	{
		str.Format(_T("%6.2f"), m_max - value_step * i);
		dc.TextOutW(graph_rect.right + 5, int(graph_rect.top + i * step) - font_height / 2, str);
	}

	dc.SetBkMode(old_mode);
	dc.SelectObject(p_Old_font);
	dc.SelectObject(p_old_pen);
	main_grid_pen.DeleteObject();
}

void child :: SetScaleRange(int parm_max, int parm_min)
{
	m_max = parm_max;
	m_min = parm_min;
	m_displayWnd.setScaleRange(m_max, m_min);
}

