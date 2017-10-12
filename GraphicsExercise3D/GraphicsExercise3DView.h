
// GraphicsExercise3DView.h : CGraphicsExercise3DView ��Ľӿ�
//

#pragma once


class CGraphicsExercise3DView : public CView
{
protected: // �������л�����
	CGraphicsExercise3DView();
	DECLARE_DYNCREATE(CGraphicsExercise3DView)

// ����
public:
	CGraphicsExercise3DDoc* GetDocument() const;

// ����
public:
	void SetScale(int scale);
	void SetTransformOrigin(float transformOriginX, float transformOriginY);
	void SetPlotSphere(float radius, float stepPhi, float stepTheta);
	void SetSlantRadian(float slant);

	float TransformScale(float num);
	float TransformOriginX(float x);
	float TransformOriginY(float y);
	float TransformOriginScaleX(float x);
	float TransformOriginScaleY(float y);
	void Transform3Dto2D(float &x, float &y, float z);

// ��д
public:
	virtual void OnDraw(CDC* pDC);  // ��д�Ի��Ƹ���ͼ
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// ʵ��
public:
	virtual ~CGraphicsExercise3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// ���ɵ���Ϣӳ�亯��
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	int scale;
	float radius, stepPhi, stepTheta, slant, transformOriginX, transformOriginY;
};

#ifndef _DEBUG  // GraphicsExercise3DView.cpp �еĵ��԰汾
inline CGraphicsExercise3DDoc* CGraphicsExercise3DView::GetDocument() const
   { return reinterpret_cast<CGraphicsExercise3DDoc*>(m_pDocument); }
#endif

