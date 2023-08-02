// CEditLTDialog.cpp: 구현 파일
//

#include "pch.h"
#include "MFCPainter.h"
#include "CEditLTDialog.h"
#include "afxdialogex.h"


// CEditLTDialog 대화 상자

IMPLEMENT_DYNAMIC(CEditLTDialog, CDialogEx)

CEditLTDialog::CEditLTDialog(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_LT_DIALOG, pParent)
{

}

CEditLTDialog::~CEditLTDialog()
{
}

void CEditLTDialog::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_LT, m_nEditLT);
}


BEGIN_MESSAGE_MAP(CEditLTDialog, CDialogEx)
END_MESSAGE_MAP()



// CEditLTDialog 메시지 처리기
