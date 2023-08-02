// CSaveDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCPainter.h"
#include "CSaveDialog.h"
#include "afxdialogex.h"


// CSaveDialog 대화 상자

IMPLEMENT_DYNAMIC(CSaveDialog, CDialogEx)

CSaveDialog::CSaveDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_SAVE_DIALOG, pParent)
{

}

CSaveDialog::~CSaveDialog()
{
}

void CSaveDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CSaveDialog, CDialogEx)
END_MESSAGE_MAP()


// CSaveDialog 메시지 처리기
