// CLoadDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCPainter.h"
#include "CLoadDialog.h"
#include "afxdialogex.h"


// CLoadDialog 대화 상자

IMPLEMENT_DYNAMIC(CLoadDialog, CDialogEx)

CLoadDialog::CLoadDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LOAD_DIALOG, pParent)
{

}

CLoadDialog::~CLoadDialog()
{
}

void CLoadDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CLoadDialog, CDialogEx)
END_MESSAGE_MAP()


// CLoadDialog 메시지 처리기
