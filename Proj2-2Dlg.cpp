
// Proj2-2Dlg.cpp: 实现文件
//

#include "stdafx.h"
#include "Proj2-2.h"
#include "Proj2-2Dlg.h"
#include "afxdialogex.h"

#include <opencv2/core.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2\imgproc\types_c.h>


#include "WinCVMat.h"
#pragma comment(lib,"WinCVMat4_x64.lib")

#ifdef _DEBUG
#pragma comment(lib,"opencv_world401d.lib")
#else
#pragma comment(lib,"opencv_world401.lib")
#endif


using namespace cv;
using namespace std;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

int situation;

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
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


// CProj22Dlg 对话框



CProj22Dlg::CProj22Dlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_PROJ22_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CProj22Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PIC1, m_ctrlPic1);
	DDX_Control(pDX, IDC_PIC2, m_ctrlPic2);
	DDX_Control(pDX, IDC_SLIDER1, m_ctrlSlider1);
}

BEGIN_MESSAGE_MAP(CProj22Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CProj22Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CProj22Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CProj22Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CProj22Dlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CProj22Dlg::OnBnClickedButton5)
	ON_WM_HSCROLL()
END_MESSAGE_MAP()


// CProj22Dlg 消息处理程序

BOOL CProj22Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_ctrlSlider1.SetRange(0, 1000);//设置滑动范围
	for (int jj = 10; jj <= 1000;)//每10个单位画一刻度
	{
		m_ctrlSlider1.SetTic(jj);
		jj += 10;
	}


	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CProj22Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CProj22Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CProj22Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}





void CProj22Dlg::OnBnClickedButton1()
{
	//长缩小一半
	Mat src;

	src = imread("test02.jpg", 1);
	ShowCVMat(m_ctrlPic1, src, 0, 255, 1);

	//立方插值
	Mat smaller_image(src.rows, src.cols*0.508, src.type());
	resize(src, smaller_image, smaller_image.size(), INTER_CUBIC);

	////双线性插值
	//Mat smaller_image；
	//resize(src, smaller_image, Size(), 0.5, 1);


	ShowCVMat(m_ctrlPic2, smaller_image, 0, 255, 1);


	//// Gaussian金字塔    函数： pyrDown();   P16
	//Mat src, dst, kernel;
	//src = imread("test02.jpg", 1);
	//ShowCVMat(m_ctrlPic1, src, 0, 255, 1);
	////int t1 = m_ctrlCombo1.GetCurSel();
	////if (t2 == 0) pyrUp(src, dst, Size(src.cols * 2, src.rows * 2));
	//pyrDown(src, dst, Size(src.cols / 2, src.rows / 2));
	//imshow("result", dst);
	//waitKey(0);
}





void CProj22Dlg::OnBnClickedButton2()
{
	//宽缩小一半
	Mat src;

	src = imread("test02.jpg", 1);
	ShowCVMat(m_ctrlPic1, src, 0, 255, 1);

	//立方插值
	Mat smaller_image(src.rows*0.5,src.cols,src.type());
	resize(src, smaller_image, smaller_image.size(),INTER_CUBIC);

	ShowCVMat(m_ctrlPic2, smaller_image, 0, 255, 1);


}


void CProj22Dlg::OnBnClickedButton3()
{
	// Affine变换
	Mat src = imread("test02.jpg", 1), dst;
	ShowCVMat(m_ctrlPic1, src, 0, 255, 1);
	Point2f srcTri[3], dstTri[3];
	Mat rot_mat(2, 3, CV_32FC1), rot_mat1(2, 3, CV_32FC1), warp_mat(2, 3,
		CV_32FC1);
	Mat warp_dst, warp_rotate_dst, rotate_dst;
	warp_dst = Mat::zeros(src.rows, src.cols, src.type());
	//int i = m_ctrlSlider1.GetPos();
	//m_ctrlSlider1.SetRange(0, 1000);
	int sz = 1 + 359 * situation / 1000;                      //【10为i】
	/// Set your 3 points to calculate the Affine Transform
	srcTri[0] = Point2f(0, 0);
	srcTri[1] = Point2f(src.cols - 1, 0);
	srcTri[2] = Point2f(0, src.rows - 1);
	srand((unsigned)time(NULL));
	double pro1 = (double)(rand() % 100) / 100;
	double pro2 = (double)(rand() % 100) / 100;
	double pro3 = (double)(rand() % 100) / 100;
	double pro4 = (double)(rand() % 100) / 100;
	double pro5 = (double)(rand() % 100) / 100;
	double pro6 = (double)(rand() % 100) / 100;
	dstTri[0] = Point2f(src.cols* pro1, src.rows* pro2);
	dstTri[1] = Point2f(src.cols* pro3, src.rows* pro4);
	dstTri[2] = Point2f(src.cols* pro5, src.rows* pro6);
	/// Get the Affine Transform
	warp_mat = getAffineTransform(srcTri, dstTri);
	/// Apply the Affine Transform just found to the src image
	warpAffine(src, warp_dst, warp_mat, warp_dst.size());
	/*rotate only*/
	Point center1 = Point(src.cols / 2, src.rows / 2);
	double angle1 = -sz, scale1 = 1;
	/// Get the rotation matrix with the specifications above
	rot_mat1 = getRotationMatrix2D(center1, angle1, scale1);
	/// Rotate the warped image
	warpAffine(src, rotate_dst, rot_mat1, warp_dst.size());
	/** Rotating the image after Warp */
	/// Compute a rotation matrix with respect to the center of the image
	Point center = Point(warp_dst.cols / 2, warp_dst.rows / 2);
	double angle = -sz, scale = 1;
	/// Get the rotation matrix with the specifications above
	rot_mat = getRotationMatrix2D(center, angle, scale);
	/// Rotate the warped image
	warpAffine(warp_dst, warp_rotate_dst, rot_mat, warp_dst.size());
	//int t1 = m_ctrlCombo1.GetCurSel();
	int t1 = 2;
	if (t1 == 0) {
		//m_ctrlSlider1.EnableWindow(FALSE);
		ShowCVMat(m_ctrlPic2, warp_dst, 0, 255, 1);
	}
	else if (t1 == 1) {
		//m_ctrlSlider1.EnableWindow(TRUE);
		ShowCVMat(m_ctrlPic2, rotate_dst, 0, 255, 1);
	}
	else if (t1 == 2) {
		m_ctrlSlider1.EnableWindow(TRUE);
		ShowCVMat(m_ctrlPic2, warp_rotate_dst, 0, 255, 1);
	}
}


void CProj22Dlg::OnBnClickedButton4()
{
	// 膨胀腐蚀
	Mat src, dst;
	//int t1 = m_ctrlCombo1.GetCurSel(), t2 = m_ctrlCombo2.GetCurSel();
	//m_ctrlSlider1.SetRange(0, 1000);
	//int pos1 = m_ctrlSlider1.GetPos();
	int sz = 1 + 16 * situation / 1000;
	src = imread("soble.jpg", 1); // src = imread("lena.jpg", 1);
	ShowCVMat(m_ctrlPic1, src, 0, 255, 1);
	Mat element = getStructuringElement(1, Size(2 * sz + 1, 2 * sz + 1), Point(sz,
		sz));

	int t1 =1;
	if (t1 == 0) erode(src, dst, element);
	else if (t1 == 1) dilate(src, dst, element);
	ShowCVMat(m_ctrlPic2, dst, 0, 255, 1);
}


void CProj22Dlg::OnBnClickedButton5()
{
	// 边缘检测
	Mat src = imread("test03.jpg", 1), src_gray, dst;
	ShowCVMat(m_ctrlPic1, src, 0, 255, 1);
	Mat grad, grad_x, grad_y, abs_grad_x, abs_grad_y;
	int ddepth = CV_16S;
	GaussianBlur(src, src, Size(3, 3), 0, 0, BORDER_DEFAULT);
	Sobel(src, grad_x, ddepth, 1, 0, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_x, abs_grad_x);
	Sobel(src, grad_y, ddepth, 0, 1, 3, 1, 0, BORDER_DEFAULT);
	convertScaleAbs(grad_y, abs_grad_y);
	addWeighted(abs_grad_x, 0.5, abs_grad_y, 0.5, 0, grad);
	//int t1 = m_ctrlCombo1.GetCurSel();
	int t1 = 2;
	if (t1 == 0) ShowCVMat(m_ctrlPic2, grad_x, 0, 255, 1);
	else if (t1 == 1) ShowCVMat(m_ctrlPic2, grad_y, 0, 255, 1);
	else if (t1 == 2) ShowCVMat(m_ctrlPic2, grad, 0, 255, 1);

	imwrite("C:\\Users\\Qu Ray\\Desktop\\hmwork\\Proj2-2\\Proj2-2\\soble.jpg", grad);//保存opencv图片
}


void CProj22Dlg::OnHScroll(UINT nSBCode, UINT nPos, CScrollBar* pScrollBar)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	/*m_ctrlSlider1.SetRange(0, 1000);
	int pos1 = m_ctrlSlider1.GetPos();*/

	UpdateData(TRUE);

	// TODO: 在此添加消息处理程序代码和/或调用默认值
	CSliderCtrl   *pSlidCtrl = (CSliderCtrl*)GetDlgItem(IDC_SLIDER1);
	//m_int 即为当前滑块的值。
	situation = 0.1*pSlidCtrl->GetPos();//取得当前位置值  
	CDialogEx::OnHScroll(nSBCode, nPos, pScrollBar);
	UpdateData(FALSE);
}
