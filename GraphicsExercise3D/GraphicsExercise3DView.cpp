
// GraphicsExercise3DView.cpp : CGraphicsExercise3DView 类的实现
//

#include "stdafx.h"
// SHARED_HANDLERS 可以在实现预览、缩略图和搜索筛选器句柄的
// ATL 项目中进行定义，并允许与该项目共享文档代码。
#ifndef SHARED_HANDLERS
#include "GraphicsExercise3D.h"
#endif

#include "GraphicsExercise3DDoc.h"
#include "GraphicsExercise3DView.h"

#include <math.h>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#ifndef PI
#define PI 3.14159
#endif // !PI

// CGraphicsExercise3DView

IMPLEMENT_DYNCREATE(CGraphicsExercise3DView, CView)

BEGIN_MESSAGE_MAP(CGraphicsExercise3DView, CView)
	// 标准打印命令
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsExercise3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphicsExercise3DView 构造/析构

CGraphicsExercise3DView::CGraphicsExercise3DView()
{
	// TODO: 在此处添加构造代码

	// 设置斜二测视图倾斜角度（弧度制） 
	SetSlantRadian(PI / 4);

	// 设置规模比例
	SetScale(70);

	// 设置坐标系在x、y方向的位移（不改变规模情况下，即移动像素）
	SetTransformOrigin(300, 350);

	// 设置球面半径radius、取样步长stepPhi、stepTheta
	SetPlotSphere(2.0, 0.01, 0.1);
}

CGraphicsExercise3DView::~CGraphicsExercise3DView()
{
}

BOOL CGraphicsExercise3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: 在此处通过修改
	//  CREATESTRUCT cs 来修改窗口类或样式

	return CView::PreCreateWindow(cs);
}


// 设置规模
void CGraphicsExercise3DView::SetScale(int scale)
{
	this->scale = scale;
}

// 设置坐标系原点在x、y方向的位移（不改变规模情况下，即移动像素）
void CGraphicsExercise3DView::SetTransformOrigin(float transformOriginX, float transformOriginY)
{
	this->transformOriginX = transformOriginX;
	this->transformOriginY = transformOriginY;
}

// 设置球面半径radius、取样步长stepPhi、stepTheta
void CGraphicsExercise3DView::SetPlotSphere(float radius, float stepPhi, float stepTheta)
{
	this->radius = radius;
	this->stepPhi = stepPhi;
	this->stepTheta = stepTheta;
}

// 设置斜二测视图的倾斜角（单位弧度）
void CGraphicsExercise3DView::SetSlantRadian(float slant)
{
	this->slant = slant;
}

// 变换规模
float CGraphicsExercise3DView::TransformScale(float num)
{
	return num * scale;
}

// 坐标系X轴方向位移
float CGraphicsExercise3DView::TransformOriginX(float x)
{
	return x + transformOriginX / scale;
}

// 坐标系y轴方向位移
float CGraphicsExercise3DView::TransformOriginY(float y)
{
	return y - transformOriginY / scale;
}

// 变换坐标系X和规模
float CGraphicsExercise3DView::TransformOriginScaleX(float x)
{
	return TransformScale(TransformOriginX(x));
}

// 变换坐标系Y和规模
float CGraphicsExercise3DView::TransformOriginScaleY(float y)
{
	return -TransformScale(TransformOriginY(y));
}


// 使用斜二测视图，把三维坐标点转化为二维平面上的点
void CGraphicsExercise3DView::Transform3Dto2D(float &x, float &y, float z)
{
	x = x - (z * cos(slant)) / 2;
	y = y - (z * sin(slant)) / 2;
}


// CGraphicsExercise2View 绘制

void CGraphicsExercise3DView::OnDraw(CDC* pDC)
{
	CGraphicsExercise3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: 在此处为本机数据添加绘制代码

	float x, y, z;

	// -------------------- 绘制坐标系 -------------------------

	// 坐标x轴
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(radius + 2), TransformOriginScaleY(0));

	// 坐标y轴
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(0), TransformOriginScaleY(radius + 2));

	// 坐标z轴
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));

	// 坐标x轴的箭头
	pDC->MoveTo(TransformOriginScaleX(radius + 1.8), TransformOriginScaleY(0.2));
	pDC->LineTo(TransformOriginScaleX(radius + 2), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(radius + 1.8), TransformOriginScaleY(-0.2));

	// 坐标y轴的箭头
	pDC->MoveTo(TransformOriginScaleX(-0.2), TransformOriginScaleY(radius + 1.8));
	pDC->LineTo(TransformOriginScaleX(0), TransformOriginScaleY(radius + 2));
	pDC->LineTo(TransformOriginScaleX(0.2), TransformOriginScaleY(radius + 1.8));

	// 坐标z轴的箭头
	x = 0, y = 0.2;
	Transform3Dto2D(x, y, radius + 5 - 0.2);
	pDC->MoveTo(TransformOriginScaleX(x), TransformOriginScaleY(y));
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));
	x = 0.2, y = 0;
	Transform3Dto2D(x, y, radius + 5 - 0.2);
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));

	// -------------------- 绘制刻度线 -------------------------

	// 绘制x轴刻度线
	for (float scaleX = 0.2; scaleX < radius + 1; scaleX += 0.2)
	{
		pDC->MoveTo((int)TransformOriginScaleX(scaleX), (int)TransformOriginScaleY(0));
		pDC->LineTo((int)TransformOriginScaleX(scaleX), (int)TransformOriginScaleY(0.1));
	}

	// 绘制y轴刻度线
	for (float scaleY = 0.2; scaleY <= radius + 1; scaleY += 0.2)
	{
		pDC->MoveTo((int)TransformOriginScaleX(0), (int)TransformOriginScaleY(scaleY));
		pDC->LineTo((int)TransformOriginScaleX(0.1), (int)TransformOriginScaleY(scaleY));
	}

	// 绘制z轴刻度线
	for (float x = 0, y = 0, scaleZ = 0.2; scaleZ <= radius + 4; scaleZ += 0.2, x = 0, y = 0)
	{
		Transform3Dto2D(x, y, scaleZ);
		pDC->MoveTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));
		pDC->LineTo((int)TransformOriginScaleX(x + 0.1), (int)TransformOriginScaleY(y));
	}


	// -------------------- 绘制文字 -------------------------

	// 绘制x轴的x
	pDC->TextOutW(TransformOriginScaleX(radius + 1.6), TransformOriginScaleY(-0.2), CString("x"));
	// 绘制y轴的y
	pDC->TextOutW(TransformOriginScaleX(-0.2), TransformOriginScaleY(radius + 1.6), CString("y"));
	// 绘制z轴的z
	x = 0.2, y = 0;
	Transform3Dto2D(x, y, radius + 5 - 0.4);
	pDC->TextOutW(TransformOriginScaleX(x), TransformOriginScaleY(y), CString("z"));

	CString s;
	// 绘制x轴刻度文字
	for (float ScaleTextX = 0.4; ScaleTextX < radius + 1; ScaleTextX += 0.4)
	{
		s.Format(_T("%.1f"), ScaleTextX);
		pDC->TextOutW(TransformOriginScaleX(ScaleTextX - 0.1), TransformOriginScaleY(-0.1), s);
	}

	// 绘制y轴刻度文字
	for (float ScaleTextY = 0.4; ScaleTextY <= radius + 1; ScaleTextY += 0.4)
	{
		s.Format(_T("%.1f"), ScaleTextY);
		pDC->TextOutW(TransformOriginScaleX(-0.4), TransformOriginScaleY(ScaleTextY + 0.1), s);
	}

	// 绘制z轴刻度文字
	for (float ScaleTextZ = 0.6; ScaleTextZ <= radius + 4; ScaleTextZ += 0.6)
	{
		s.Format(_T("%.1f"), ScaleTextZ);
		x = 0, y = 0;
		Transform3Dto2D(x, y, ScaleTextZ);
		pDC->TextOutW(TransformOriginScaleX(x + 0.15), TransformOriginScaleY(y + 0.12), s);
	}

	// 绘制函数图的Title
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->TextOutW(TransformOriginScaleX(x + 3), TransformOriginScaleY(y), CString("x^2 + y^2 + z^2 = r^2"));

	// -------------------- 绘制函数 -------------------------

	// 球面
	float phi, theta;
	for (phi = 0; phi < 2 * PI; phi += stepPhi)
	{
		for (theta = 0; theta < PI; theta += stepTheta)
		{
			x = radius * sin(phi) * cos(theta);
			y = radius * sin(phi) * sin(theta);
			z = radius * cos(phi);

			Transform3Dto2D(x, y, z);

			srand(z);
			pDC->SetPixel(TransformOriginScaleX(x), TransformOriginScaleY(y), RGB(rand() % 255, rand() % 255, rand() % 255));
		}
	}


	//// 三棱锥（测试用）
	//x = 1, y = 0, z = 0;
	//Transform3Dto2D(x, y, z);
	//pDC->MoveTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));

	//x = 0, y = 1, z = 0;
	//Transform3Dto2D(x, y, z);
	//pDC->LineTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));

	//x = 0, y = 0, z = 1;
	//Transform3Dto2D(x, y, z);
	//pDC->LineTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));

	//x = 1, y = 0, z = 0;
	//Transform3Dto2D(x, y, z);
	//pDC->LineTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));

}


// CGraphicsExercise3DView 打印


void CGraphicsExercise3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsExercise3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// 默认准备
	return DoPreparePrinting(pInfo);
}

void CGraphicsExercise3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加额外的打印前进行的初始化过程
}

void CGraphicsExercise3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: 添加打印后进行的清理过程
}

void CGraphicsExercise3DView::OnRButtonUp(UINT /* nFlags */, CPoint point)
{
	ClientToScreen(&point);
	OnContextMenu(this, point);
}

void CGraphicsExercise3DView::OnContextMenu(CWnd* /* pWnd */, CPoint point)
{
#ifndef SHARED_HANDLERS
	theApp.GetContextMenuManager()->ShowPopupMenu(IDR_POPUP_EDIT, point.x, point.y, this, TRUE);
#endif
}


// CGraphicsExercise3DView 诊断

#ifdef _DEBUG
void CGraphicsExercise3DView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsExercise3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsExercise3DDoc* CGraphicsExercise3DView::GetDocument() const // 非调试版本是内联的
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsExercise3DDoc)));
	return (CGraphicsExercise3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsExercise3DView 消息处理程序
