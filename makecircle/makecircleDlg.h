
// makecircleDlg.h: 헤더 파일
//
#include <vector> 

#pragma once


// CmakecircleDlg 대화 상자
class CmakecircleDlg : public CDialogEx
{
// 생성입니다.
public:
	CmakecircleDlg(CWnd* pParent = nullptr);	// 표준 생성자입니다.

public:
	void MovePointsRandomly();  // 점을 랜덤 위치로 이동


// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MAKECIRCLE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 지원입니다.


// 구현입니다.
protected:
	HICON m_hIcon;

	int m_radius = 3;            
	int m_thickness = 2;    
	int m_circleThickness = 2;  

	std::vector<CPoint> m_points;  
	CPoint m_dragOffset;     
	int m_dragIndex = -1;    
	bool m_isDragging = false; 
	bool CalculateCircle(const CPoint& A, const CPoint& B, const CPoint& C, CPoint& center, double& radius);



	// 생성된 메시지 맵 함수
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnEnChangeEditthickness();
	afx_msg void OnEnChangeEditradius();
	afx_msg void OnStnClickedStaticradius();
	afx_msg void OnStnClickedStaticthickness();
	afx_msg void OnBnClickedresetbtn();
	afx_msg void OnBnClickedrandombtn();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg void OnStnClickedStaticfirst();
	afx_msg void OnStnClickedStaticsecond();
	afx_msg void OnStnClickedStaticthird();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point); 
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);
};
