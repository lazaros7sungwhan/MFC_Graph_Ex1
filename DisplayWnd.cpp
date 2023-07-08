#include "pch.h"
#include "DisplayWnd.h"
#include <math.h>
#include "Concept1.h"

IMPLEMENT_DYNAMIC(DisplayWnd,CWnd)
DisplayWnd::DisplayWnd()
{
	m_grid_move_count = 0;
	m_count_per_grid = 5;
	m_grid_count = 5;
	m_data_index = -1;
	m_data_count = 300;
	m_scroll_index = 0;
	m_max = 100;
	m_min = -100;
	m_current_degree = 0;
}
DisplayWnd::~DisplayWnd()
{
}

BEGIN_MESSAGE_MAP(DisplayWnd, CWnd)
	ON_WM_PAINT()
	ON_WM_CREATE()
	ON_WM_DESTROY()
	ON_WM_TIMER()
END_MESSAGE_MAP()

void DisplayWnd::OnPaint()
{
	CPaintDC dc(this);
	
	CRect r; 
	GetClientRect(r);
	dc.FillSolidRect(r, RGB(255, 255, 255));

	CPen main_grid_pen(PS_DOT, 1, RGB(0, 0, 0)), data_line_pen(PS_SOLID, 2, RGB(255, 0, 0)), sub_grid_pen(PS_SOLID,1,RGB(200,200,200));
	
	double step = r.Width() / m_grid_count;
	double data_step = step / m_count_per_grid;

	CPen* p_old_pen = dc.SelectObject(&sub_grid_pen);

	for (int i = 0; int(i * data_step) < r.Width(); i++)
	{
		dc.MoveTo(int(i * data_step), 0);
		dc.LineTo(int(i * data_step), r.bottom);
	}

	dc.SelectObject(&main_grid_pen);
	for (int i =0; int(i * data_step) < r.Width(); i++)
	{
		dc.MoveTo(int(i*step - data_step)-int(m_grid_count * (step/m_count_per_grid)), 0);
		dc.LineTo(int(i * step - data_step)-int(m_grid_count * (step/m_count_per_grid)), r.bottom);
	}

	if (m_data_index >= 0) {
		dc.SelectObject(&data_line_pen);
		dc.MoveTo(r.right, r.Height() - int(r.Height() * (mp_data[m_data_index] - m_min)) / (m_max - m_min));
		for (int i = 0; i < m_data_index - m_scroll_index + 1; i++)
		{
			dc.LineTo(r.right - int(i * data_step), r.Height() - int(r.Height() * (mp_data[m_data_index - i]-m_min)) / (m_max - m_min));
		}

		/*dc.SelectObject(&data_line_pen);
		dc.MoveTo(r.right, r.Height() - int(r.Height() * (mp_data[m_data_index] - m_min)) / (m_max - m_min));
		for (i = 0; i < m_data_index - m_scroll_index + 1; i++)
		{
			dc.LineTo(r.right - int(i * data_step), r.Height() - int(r.Height() * (mp_data[m_data_index - i] - m_min)) / (m_max - m_min));
		}*/
	}

	dc.SelectObject(p_old_pen);

	data_line_pen.DeleteObject();
	main_grid_pen.DeleteObject();
	sub_grid_pen.DeleteObject();
	
}


int DisplayWnd::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CWnd::OnCreate(lpCreateStruct) == -1) return -1;
	mp_data = new double[m_data_count];
	
	for (int i = 0; i < m_data_count; i++)mp_data[i] = double(0);

	srand((unsigned)time(NULL));
	SetTimer(1, 100, NULL);
	return 0;
}


void DisplayWnd::OnDestroy()
{
	KillTimer(1);
	delete[] mp_data;

	CWnd::OnDestroy();
}
double DisplayWnd::getCurrentData()
{
	if (m_data_index < 0)return double(0);
	return mp_data[m_data_index];
}
void DisplayWnd::OnTimer(UINT_PTR nIDEvent)
{
	if (nIDEvent == 1)
	{
		m_current_degree = (m_current_degree + 20) % 360;
		if (m_data_index < m_data_count - 1) {
			m_data_index++;
			// �����͸� �����ϴ� ������ m_data_count ������ ������ ȭ�鿡�� �����ټ� �ִ� �������� ������
			// m_count_per_grid * m_grid_count���̴�. ���� �� ������ �Ѵ� ���� �����ʹ� ÷���� �������°�
			// �ƴ϶� m_scroll_index ���� �������� �ȴ�.
			if (m_data_index >= m_count_per_grid * m_grid_count + 2) {
				if (m_data_count - m_count_per_grid * m_grid_count > m_scroll_index) m_scroll_index++;
			}
		}
		else {
			// �������� ������ m_data_count - 1���� �ʰ��ϸ� ���� ó���� �ִ� �����͸� ������ �� �ڿ� 
			// �ִ� �����͸� ������ 1���� ���� ��Ų��.
			memcpy(mp_data, mp_data + 1, sizeof(double) * (m_data_count - 1));
		}

		// ������ �����͸� �߻���Ų��. 
		mp_data[m_data_index] = int(tan(m_current_degree * 3.141592 / 180) * ((rand() % 20) + 10)) % 50;
		// �׷����� ��ȭ�� ���� ���Ǽ� �ְ� ���̱� ���� �׸��带 ���� �����Ų��.
		if (m_count_per_grid > 0) m_grid_move_count = (m_grid_move_count + 1) % m_count_per_grid;

		// ���� �׷��� �����츦 �����Ѵ�.
		Invalidate(FALSE);
		// �ð���� ������ �����Ѵ�.
		GetParent()->Invalidate(FALSE);
	}
	else CWnd::OnTimer(nIDEvent);
}

void DisplayWnd::setScaleRange(int param_max, int pram_min)
{
	m_max = param_max;
	m_min = pram_min;
}
