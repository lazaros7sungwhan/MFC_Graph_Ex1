#pragma once
#include <afxwin.h>

class DisplayWnd :
    public CWnd
{
    DECLARE_DYNAMIC(DisplayWnd)
private:
    int m_count_per_grid, m_grid_count, m_data_count, m_scroll_index;
    int m_grid_move_count, m_data_index, m_max, m_min, m_current_degree;
    double* mp_data;


public :
    DisplayWnd();
    double getCurrentData();
    void setScaleRange(int param_max, int pram_min);

public :
    virtual ~DisplayWnd();



    DECLARE_MESSAGE_MAP()
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
    afx_msg void OnTimer(UINT_PTR nIDEvent);
};




