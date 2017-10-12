
// GraphicsExercise3DView.cpp : CGraphicsExercise3DView ���ʵ��
//

#include "stdafx.h"
// SHARED_HANDLERS ������ʵ��Ԥ��������ͼ������ɸѡ�������
// ATL ��Ŀ�н��ж��壬�����������Ŀ�����ĵ����롣
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
	// ��׼��ӡ����
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CGraphicsExercise3DView::OnFilePrintPreview)
	ON_WM_CONTEXTMENU()
	ON_WM_RBUTTONUP()
END_MESSAGE_MAP()

// CGraphicsExercise3DView ����/����

CGraphicsExercise3DView::CGraphicsExercise3DView()
{
	// TODO: �ڴ˴���ӹ������

	// ����б������ͼ��б�Ƕȣ������ƣ� 
	SetSlantRadian(PI / 4);

	// ���ù�ģ����
	SetScale(70);

	// ��������ϵ��x��y�����λ�ƣ����ı��ģ����£����ƶ����أ�
	SetTransformOrigin(300, 350);

	// ��������뾶radius��ȡ������stepPhi��stepTheta
	SetPlotSphere(2.0, 0.01, 0.1);
}

CGraphicsExercise3DView::~CGraphicsExercise3DView()
{
}

BOOL CGraphicsExercise3DView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: �ڴ˴�ͨ���޸�
	//  CREATESTRUCT cs ���޸Ĵ��������ʽ

	return CView::PreCreateWindow(cs);
}


// ���ù�ģ
void CGraphicsExercise3DView::SetScale(int scale)
{
	this->scale = scale;
}

// ��������ϵԭ����x��y�����λ�ƣ����ı��ģ����£����ƶ����أ�
void CGraphicsExercise3DView::SetTransformOrigin(float transformOriginX, float transformOriginY)
{
	this->transformOriginX = transformOriginX;
	this->transformOriginY = transformOriginY;
}

// ��������뾶radius��ȡ������stepPhi��stepTheta
void CGraphicsExercise3DView::SetPlotSphere(float radius, float stepPhi, float stepTheta)
{
	this->radius = radius;
	this->stepPhi = stepPhi;
	this->stepTheta = stepTheta;
}

// ����б������ͼ����б�ǣ���λ���ȣ�
void CGraphicsExercise3DView::SetSlantRadian(float slant)
{
	this->slant = slant;
}

// �任��ģ
float CGraphicsExercise3DView::TransformScale(float num)
{
	return num * scale;
}

// ����ϵX�᷽��λ��
float CGraphicsExercise3DView::TransformOriginX(float x)
{
	return x + transformOriginX / scale;
}

// ����ϵy�᷽��λ��
float CGraphicsExercise3DView::TransformOriginY(float y)
{
	return y - transformOriginY / scale;
}

// �任����ϵX�͹�ģ
float CGraphicsExercise3DView::TransformOriginScaleX(float x)
{
	return TransformScale(TransformOriginX(x));
}

// �任����ϵY�͹�ģ
float CGraphicsExercise3DView::TransformOriginScaleY(float y)
{
	return -TransformScale(TransformOriginY(y));
}


// ʹ��б������ͼ������ά�����ת��Ϊ��άƽ���ϵĵ�
void CGraphicsExercise3DView::Transform3Dto2D(float &x, float &y, float z)
{
	x = x - (z * cos(slant)) / 2;
	y = y - (z * sin(slant)) / 2;
}


// CGraphicsExercise2View ����

void CGraphicsExercise3DView::OnDraw(CDC* pDC)
{
	CGraphicsExercise3DDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: �ڴ˴�Ϊ����������ӻ��ƴ���

	float x, y, z;

	// -------------------- ��������ϵ -------------------------

	// ����x��
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(radius + 2), TransformOriginScaleY(0));

	// ����y��
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(0), TransformOriginScaleY(radius + 2));

	// ����z��
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->MoveTo(TransformOriginScaleX(0), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));

	// ����x��ļ�ͷ
	pDC->MoveTo(TransformOriginScaleX(radius + 1.8), TransformOriginScaleY(0.2));
	pDC->LineTo(TransformOriginScaleX(radius + 2), TransformOriginScaleY(0));
	pDC->LineTo(TransformOriginScaleX(radius + 1.8), TransformOriginScaleY(-0.2));

	// ����y��ļ�ͷ
	pDC->MoveTo(TransformOriginScaleX(-0.2), TransformOriginScaleY(radius + 1.8));
	pDC->LineTo(TransformOriginScaleX(0), TransformOriginScaleY(radius + 2));
	pDC->LineTo(TransformOriginScaleX(0.2), TransformOriginScaleY(radius + 1.8));

	// ����z��ļ�ͷ
	x = 0, y = 0.2;
	Transform3Dto2D(x, y, radius + 5 - 0.2);
	pDC->MoveTo(TransformOriginScaleX(x), TransformOriginScaleY(y));
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));
	x = 0.2, y = 0;
	Transform3Dto2D(x, y, radius + 5 - 0.2);
	pDC->LineTo(TransformOriginScaleX(x), TransformOriginScaleY(y));

	// -------------------- ���ƿ̶��� -------------------------

	// ����x��̶���
	for (float scaleX = 0.2; scaleX < radius + 1; scaleX += 0.2)
	{
		pDC->MoveTo((int)TransformOriginScaleX(scaleX), (int)TransformOriginScaleY(0));
		pDC->LineTo((int)TransformOriginScaleX(scaleX), (int)TransformOriginScaleY(0.1));
	}

	// ����y��̶���
	for (float scaleY = 0.2; scaleY <= radius + 1; scaleY += 0.2)
	{
		pDC->MoveTo((int)TransformOriginScaleX(0), (int)TransformOriginScaleY(scaleY));
		pDC->LineTo((int)TransformOriginScaleX(0.1), (int)TransformOriginScaleY(scaleY));
	}

	// ����z��̶���
	for (float x = 0, y = 0, scaleZ = 0.2; scaleZ <= radius + 4; scaleZ += 0.2, x = 0, y = 0)
	{
		Transform3Dto2D(x, y, scaleZ);
		pDC->MoveTo((int)TransformOriginScaleX(x), (int)TransformOriginScaleY(y));
		pDC->LineTo((int)TransformOriginScaleX(x + 0.1), (int)TransformOriginScaleY(y));
	}


	// -------------------- �������� -------------------------

	// ����x���x
	pDC->TextOutW(TransformOriginScaleX(radius + 1.6), TransformOriginScaleY(-0.2), CString("x"));
	// ����y���y
	pDC->TextOutW(TransformOriginScaleX(-0.2), TransformOriginScaleY(radius + 1.6), CString("y"));
	// ����z���z
	x = 0.2, y = 0;
	Transform3Dto2D(x, y, radius + 5 - 0.4);
	pDC->TextOutW(TransformOriginScaleX(x), TransformOriginScaleY(y), CString("z"));

	CString s;
	// ����x��̶�����
	for (float ScaleTextX = 0.4; ScaleTextX < radius + 1; ScaleTextX += 0.4)
	{
		s.Format(_T("%.1f"), ScaleTextX);
		pDC->TextOutW(TransformOriginScaleX(ScaleTextX - 0.1), TransformOriginScaleY(-0.1), s);
	}

	// ����y��̶�����
	for (float ScaleTextY = 0.4; ScaleTextY <= radius + 1; ScaleTextY += 0.4)
	{
		s.Format(_T("%.1f"), ScaleTextY);
		pDC->TextOutW(TransformOriginScaleX(-0.4), TransformOriginScaleY(ScaleTextY + 0.1), s);
	}

	// ����z��̶�����
	for (float ScaleTextZ = 0.6; ScaleTextZ <= radius + 4; ScaleTextZ += 0.6)
	{
		s.Format(_T("%.1f"), ScaleTextZ);
		x = 0, y = 0;
		Transform3Dto2D(x, y, ScaleTextZ);
		pDC->TextOutW(TransformOriginScaleX(x + 0.15), TransformOriginScaleY(y + 0.12), s);
	}

	// ���ƺ���ͼ��Title
	x = 0, y = 0;
	Transform3Dto2D(x, y, radius + 5);
	pDC->TextOutW(TransformOriginScaleX(x + 3), TransformOriginScaleY(y), CString("x^2 + y^2 + z^2 = r^2"));

	// -------------------- ���ƺ��� -------------------------

	// ����
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


	//// ����׶�������ã�
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


// CGraphicsExercise3DView ��ӡ


void CGraphicsExercise3DView::OnFilePrintPreview()
{
#ifndef SHARED_HANDLERS
	AFXPrintPreview(this);
#endif
}

BOOL CGraphicsExercise3DView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// Ĭ��׼��
	return DoPreparePrinting(pInfo);
}

void CGraphicsExercise3DView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӷ���Ĵ�ӡǰ���еĳ�ʼ������
}

void CGraphicsExercise3DView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: ��Ӵ�ӡ����е��������
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


// CGraphicsExercise3DView ���

#ifdef _DEBUG
void CGraphicsExercise3DView::AssertValid() const
{
	CView::AssertValid();
}

void CGraphicsExercise3DView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CGraphicsExercise3DDoc* CGraphicsExercise3DView::GetDocument() const // �ǵ��԰汾��������
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CGraphicsExercise3DDoc)));
	return (CGraphicsExercise3DDoc*)m_pDocument;
}
#endif //_DEBUG


// CGraphicsExercise3DView ��Ϣ�������
