
// ImgProView.cpp : implementation of the CImgProView class
//

#include "pch.h"
#include "framework.h"
// SHARED_HANDLERS can be defined in an ATL project implementing preview, thumbnail
// and search filter handlers and allows sharing of document code with that project.
#ifndef SHARED_HANDLERS
#include "ImgPro.h"
#endif

#include "ImgProDoc.h"
#include "ImgProView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CImgProView

IMPLEMENT_DYNCREATE(CImgProView, CView)

BEGIN_MESSAGE_MAP(CImgProView, CView)
	// Standard printing commands
	ON_COMMAND(ID_FILE_PRINT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, &CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, &CView::OnFilePrintPreview)
	ON_COMMAND(ID_OPERATION_GRAYSCALE, &CImgProView::OnOperationGrayscale)
	ON_COMMAND(ID_FILE_OPEN, &CImgProView::OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, &CImgProView::OnFileSave)
END_MESSAGE_MAP()

// CImgProView construction/destruction

CImgProView::CImgProView() noexcept
{
	// TODO: add construction code her
	img_src = 0;
	img_save = 0;
}

CImgProView::~CImgProView()
{
	img_src = 0;
	img_save = 0;
	destroyAllWindows();
}

BOOL CImgProView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CImgProView drawing

void CImgProView::OnDraw(CDC* /*pDC*/)
{
	CImgProDoc* pDoc = GetDocument();
	ASSERT_VALID(pDoc);
	if (!pDoc)
		return;

	// TODO: add draw code for native data here
}


// CImgProView printing

BOOL CImgProView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CImgProView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CImgProView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CImgProView diagnostics

#ifdef _DEBUG
void CImgProView::AssertValid() const
{
	CView::AssertValid();
}

void CImgProView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

CImgProDoc* CImgProView::GetDocument() const // non-debug version is inline
{
	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CImgProDoc)));
	return (CImgProDoc*)m_pDocument;
}
#endif //_DEBUG


// CImgProView message handlers


void CImgProView::OnOperationGrayscale()
{
	// TODO: Add your command handler code here
	/*Mat img = imread("D:\\images.png", IMREAD_COLOR);
	namedWindow("Test CV", 1);
	imshow("Test CV", img);*/
   
	//TODO:Convert RGB to grayscale()
	Mat image, newImage;

	image = img_save;
	int width = 400, height = 400;
	resize(image, newImage, Size(width, height));
	Mat lum(newImage.rows, newImage.cols, CV_8UC1, Scalar(0));

	for (int i = 0; i < newImage.rows; i++)
	{
		for (int j = 0; j < newImage.cols; j++)
		{
			int red = newImage.at<Vec3b>(i, j)[2];
			int green = newImage.at<Vec3b>(i, j)[1];
			int blue = newImage.at<Vec3b>(i, j)[0];

			lum.at<uchar>(i, j) = (0.299 * red + 0.587 * green + 0.114 * blue);
		}
	}

	namedWindow("Grayscale", WINDOW_AUTOSIZE);
	imshow("Grayscale", lum);

	waitKey(0);

}


void CImgProView::OnFileOpen()
{
	// TODO: Add your command handler code here

	CFileDialog dlg(TRUE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg; *.gif; *.jpeg; *.png; *.tif) |*.bmp;*.jpg; *.gif; *.jpeg; *.png; *.tif|All Files (*.*)|*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Open an Image");

	if (dlg.DoModal() == IDOK)
	{
		CImgProDoc* pDoc = GetDocument();
		CString path = dlg.GetPathName(); // contain the selected filename
		char* path_image = new char[path.GetLength() + 1];
		wsprintfA(path_image, "%ls", path);
		String windowName = "Source Image";
		img_src = imread(path_image, IMREAD_COLOR);
		img_save = img_src;
		namedWindow(windowName, WINDOW_AUTOSIZE);
		//MessageBox(NULL, (CString)path_image, MB_OK);
		imshow(windowName, img_src);
	}
}


void CImgProView::OnFileSave()
{
	// TODO: Add your command handler code here

	CFileDialog dlg(FALSE, _T("*.bmp"), NULL,
		OFN_FILEMUSTEXIST | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY,
		_T("image files (*.bmp; *.jpg; *.gif; *.jpeg; *.png; *.tif) |*.bmp;*.jpg; *.gif; *.jpeg; *.png; *.tif|All Files (*.*)|*.*||"), NULL);

	dlg.m_ofn.lpstrTitle = _T("Save Image");

	if (dlg.DoModal() == IDOK)
	{
		CString file = dlg.GetPathName();
		char* filename = new char[file.GetLength() + 1];
		wsprintfA(filename, "%ls", file);
		imwrite(filename, img_save);
	}

}
