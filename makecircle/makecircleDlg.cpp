
// makecircleDlg.cpp: 구현 파일
//

#include "pch.h"
#include "framework.h"
#include "makecircle.h"
#include "makecircleDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif
UINT ThreadRandomMove(LPVOID pParam);  


// 응용 프로그램 정보에 사용되는 CAboutDlg 대화 상자입니다.

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

// 구현입니다.
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CmakecircleDlg 대화 상자



CmakecircleDlg::CmakecircleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MAKECIRCLE_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CmakecircleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CmakecircleDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDOK, &CmakecircleDlg::OnBnClickedOk)
	ON_EN_CHANGE(EditThickness, &CmakecircleDlg::OnEnChangeEditthickness)
	ON_EN_CHANGE(EditRadius, &CmakecircleDlg::OnEnChangeEditradius)
	ON_STN_CLICKED(StaticRadius, &CmakecircleDlg::OnStnClickedStaticradius)
	ON_STN_CLICKED(StaticThickness, &CmakecircleDlg::OnStnClickedStaticthickness)
	ON_BN_CLICKED(resetBtn, &CmakecircleDlg::OnBnClickedresetbtn)
	ON_BN_CLICKED(randomBtn, &CmakecircleDlg::OnBnClickedrandombtn)

	ON_WM_LBUTTONDOWN()
	ON_STN_CLICKED(StaticFirst, &CmakecircleDlg::OnStnClickedStaticfirst)
	ON_STN_CLICKED(StaticSecond, &CmakecircleDlg::OnStnClickedStaticsecond)
	ON_STN_CLICKED(StaticThird, &CmakecircleDlg::OnStnClickedStaticthird)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONUP()

END_MESSAGE_MAP()




BOOL CmakecircleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 시스템 메뉴에 "정보..." 메뉴 항목을 추가합니다.

	// IDM_ABOUTBOX는 시스템 명령 범위에 있어야 합니다.
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 이 대화 상자의 아이콘을 설정합니다.  응용 프로그램의 주 창이 대화 상자가 아닐 경우에는
	//  프레임워크가 이 작업을 자동으로 수행합니다.
	SetIcon(m_hIcon, TRUE);			// 큰 아이콘을 설정합니다.
	SetIcon(m_hIcon, FALSE);		// 작은 아이콘을 설정합니다.

	// TODO: 여기에 추가 초기화 작업을 추가합니다.

	return TRUE;  // 포커스를 컨트롤에 설정하지 않으면 TRUE를 반환합니다.
}

void CmakecircleDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 대화 상자에 최소화 단추를 추가할 경우 아이콘을 그리려면
//  아래 코드가 필요합니다.  문서/뷰 모델을 사용하는 MFC 애플리케이션의 경우에는
//  프레임워크에서 이 작업을 자동으로 수행합니다.

void CmakecircleDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); 

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{


		CPaintDC dc(this);


		for (auto pt : m_points)
		{

			for (int y = -m_radius; y <= m_radius; ++y)
			{
				for (int x = -m_radius; x <= m_radius; ++x)
				{
					if (x * x + y * y <= m_radius * m_radius)
					{
						dc.SetPixel(pt.x + x, pt.y + y, RGB(0, 0, 0));  
					}
				}
			}

			CPen pen(PS_SOLID, m_thickness, RGB(0, 0, 0));
			CPen* oldPen = dc.SelectObject(&pen);

			double angleStep = 2.0;
			CPoint prev;

			for (double angle = 0.0; angle <= 360.0; angle += angleStep)
			{
				double rad = angle * 3.14159265 / 180.0;
				int x = pt.x + static_cast<int>(m_radius * cos(rad));
				int y = pt.y + static_cast<int>(m_radius * sin(rad));

				if (angle == 0.0)
				{
					dc.MoveTo(x, y);
					prev = CPoint(x, y);
				}
				else
				{
					dc.LineTo(x, y);
				}
			}

			dc.LineTo(prev);

			dc.SelectObject(oldPen);
		}



		CDialogEx::OnPaint();

		if (m_points.size() == 3)
		{
			CPoint center;
			double radius;

			if (CalculateCircle(m_points[0], m_points[1], m_points[2], center, radius))
			{
				CPen redPen(PS_SOLID, m_circleThickness, RGB(0, 0, 0));
				CPen* oldPen = dc.SelectObject(&redPen);

				double angleStep = 2.0;
				CPoint first;

				for (double angle = 0.0; angle <= 360.0; angle += angleStep)
				{
					double rad = angle * 3.14159265 / 180.0;
					int x = center.x + static_cast<int>(radius * cos(rad));
					int y = center.y + static_cast<int>(radius * sin(rad));

					if (angle == 0.0)
					{
						dc.MoveTo(x, y);
						first = CPoint(x, y);
					}
					else
					{
						dc.LineTo(x, y);
					}
				}

				dc.LineTo(first);
				dc.SelectObject(oldPen);
			}
		}

		CDialogEx::OnPaint();  
	}
	}



// 사용자가 최소화된 창을 끄는 동안에 커서가 표시되도록 시스템에서
//  이 함수를 호출합니다.
HCURSOR CmakecircleDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CmakecircleDlg::OnBnClickedOk()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	CDialogEx::OnOK();
}

void CmakecircleDlg::OnEnChangeEditthickness()
{
	CString txt;
	GetDlgItemText(EditThickness, txt);
	int t = _ttoi(txt);  

	if (t > 0)
	{
		m_circleThickness = t; 
		Invalidate();
	}
	
}


void CmakecircleDlg::OnEnChangeEditradius()
{
	CString rad;
	GetDlgItemText(EditRadius, rad);
	int r = _ttoi(rad);
	if (r > 0) m_radius = r;
	Invalidate();
}


void CmakecircleDlg::OnStnClickedStaticfirst()
{

}

void CmakecircleDlg::OnStnClickedStaticsecond()
{

}

void CmakecircleDlg::OnStnClickedStaticthird()
{

}



void CmakecircleDlg::OnStnClickedStaticradius()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CmakecircleDlg::OnStnClickedStaticthickness()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
}

void CmakecircleDlg::OnBnClickedresetbtn()
{
	
	m_points.clear();

	
	SetDlgItemText(StaticFirst, _T(""));
	SetDlgItemText(StaticSecond, _T(""));
	SetDlgItemText(StaticThird, _T(""));

	
	Invalidate();
}


void CmakecircleDlg::OnBnClickedrandombtn()
{
	
	AfxBeginThread(ThreadRandomMove, this);
}

void CmakecircleDlg::MovePointsRandomly()
{
	CRect rect;
	GetClientRect(&rect);  

	for (int i = 0; i < (int)m_points.size(); ++i)
	{
		int x = rand() % rect.Width();   
		int y = rand() % rect.Height();  

		m_points[i] = CPoint(x, y);      
	}

	Invalidate();  
}


void CmakecircleDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	if (m_points.size() < 3)
	{
		
		CString coord;
		coord.Format(_T("X: %d, Y: %d"), point.x, point.y);

		if (m_points.size() == 0) SetDlgItemText(StaticFirst, coord);
		else if (m_points.size() == 1) SetDlgItemText(StaticSecond, coord);
		else if (m_points.size() == 2) SetDlgItemText(StaticThird, coord);

		
		m_points.push_back(point);

		Invalidate();  
	}

	CDialogEx::OnLButtonDown(nFlags, point);

	
	for (int i = 0; i < (int)m_points.size(); ++i)
	{
		CPoint pt = m_points[i];

		
		int dx = point.x - pt.x;
		int dy = point.y - pt.y;
		double dist = sqrt(dx * dx + dy * dy);

		if (dist <= m_radius)  
		{
			m_isDragging = true;
			m_dragIndex = i;
			m_dragOffset = point - pt;
			break;
		}
	}

}




bool CmakecircleDlg::CalculateCircle(const CPoint& A, const CPoint& B, const CPoint& C, CPoint& center, double& radius)

{
	
	double a = B.x - A.x;
	double b = B.y - A.y;
	double c = C.x - A.x;
	double d = C.y - A.y;
	double e = a * (A.x + B.x) + b * (A.y + B.y);
	double f = c * (A.x + C.x) + d * (A.y + C.y);
	double g = 2.0 * (a * (C.y - B.y) - b * (C.x - B.x));

	if (g == 0.0) return false; 

	double cx = (d * e - b * f) / g;
	double cy = (a * f - c * e) / g;
	center = CPoint(static_cast<int>(cx), static_cast<int>(cy));
	radius = sqrt(pow(center.x - A.x, 2) + pow(center.y - A.y, 2));
	return true;
}


void CmakecircleDlg::OnMouseMove(UINT nFlags, CPoint point)
{
	if (m_isDragging && m_dragIndex >= 0 && m_dragIndex < (int)m_points.size())
	{
		
		m_points[m_dragIndex] = point - m_dragOffset;

		
		CString coord;
		coord.Format(_T("X: %d, Y: %d"), m_points[m_dragIndex].x, m_points[m_dragIndex].y);

		if (m_dragIndex == 0) SetDlgItemText(StaticFirst, coord);
		else if (m_dragIndex == 1) SetDlgItemText(StaticSecond, coord);
		else if (m_dragIndex == 2) SetDlgItemText(StaticThird, coord);

		
		Invalidate();
	}

	CDialogEx::OnMouseMove(nFlags, point);
}

void CmakecircleDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	m_isDragging = false;
	m_dragIndex = -1;

	CDialogEx::OnLButtonUp(nFlags, point);
}
UINT ThreadRandomMove(LPVOID pParam)
{
	CmakecircleDlg* pDlg = (CmakecircleDlg*)pParam;

	for (int i = 0; i < 10; ++i)
	{
		Sleep(500);
		pDlg->MovePointsRandomly();
	}

	return 0;
}