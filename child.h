#pragma once
#include <afxwin.h>
#include "DisplayWnd.h"

class child :
    public CWnd
{
    DECLARE_DYNAMIC(child)

protected:
    COLORREF m_main_grid;
    DisplayWnd m_displayWnd;
    int m_max, m_min; 

    CFont g_default_font;

public:
    child();
    void SetScaleRange(int parm_max, int parm_min);
virtual ~child();


    DECLARE_MESSAGE_MAP(child)
    afx_msg void OnPaint();
    afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
    afx_msg void OnDestroy();
};

