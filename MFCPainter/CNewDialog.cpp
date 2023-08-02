// CNewDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCPainter.h"
#include "CNewDialog.h"
#include "afxdialogex.h"


// CNewDialog 대화 상자

IMPLEMENT_DYNAMIC(CNewDialog, CDialogEx)

CNewDialog::CNewDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_NEW_DIALOG, pParent)
{

}

CNewDialog::~CNewDialog()
{
}

void CNewDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CNewDialog, CDialogEx)
END_MESSAGE_MAP()


// CNewDialog 메시지 처리기
