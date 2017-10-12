
// GraphicsExercise3DView.h : CGraphicsExercise3DView 类的接口
//

#pragma once


class CGraphicsExercise3DView : public CView
{
protected: // 仅从序列化创建
	CGraphicsExercise3DView();
	DECLARE_DYNCREATE(CGraphicsExercise3DView)

// 特性
public:
	CGraphicsExercise3DDoc* GetDocument() const;

// 操作
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

// 重写
public:
	virtual void OnDraw(CDC* pDC);  // 重写以绘制该视图
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// 实现
public:
	virtual ~CGraphicsExercise3DView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// 生成的消息映射函数
protected:
	afx_msg void OnFilePrintPreview();
	afx_msg void OnRButtonUp(UINT nFlags, CPoint point);
	afx_msg void OnContextMenu(CWnd* pWnd, CPoint point);
	DECLARE_MESSAGE_MAP()

private:
	int scale;
	float radius, stepPhi, stepTheta, slant, transformOriginX, transformOriginY;
};

#ifndef _DEBUG  // GraphicsExercise3DView.cpp 中的调试版本
inline CGraphicsExercise3DDoc* CGraphicsExercise3DView::GetDocument() const
   { return reinterpret_cast<CGraphicsExercise3DDoc*>(m_pDocument); }
#endif

