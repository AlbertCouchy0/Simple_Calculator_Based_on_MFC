// MyDialog1.cpp: 实现文件
//

#include "pch.h"
#include "calculator.h"
#include "afxdialogex.h"
#include "MyDialog1.h"


// MyDialog1 对话框

IMPLEMENT_DYNAMIC(MyDialog1, CDialogEx)

MyDialog1::MyDialog1(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG1, pParent)
	, alert(_T(""))
{

}

MyDialog1::~MyDialog1()
{
}


void MyDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_TANCHUANG, alert);
}


BEGIN_MESSAGE_MAP(MyDialog1, CDialogEx)
END_MESSAGE_MAP()


// MyDialog1 消息处理程序
