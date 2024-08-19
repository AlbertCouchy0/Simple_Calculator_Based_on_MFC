
// calculatorDlg.cpp: 实现文件
#include"MyDialog1.h"
#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};
CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}
void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}
BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_CLOSE()
END_MESSAGE_MAP()

// CcalculatorDlg 对话框
CcalculatorDlg::CcalculatorDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CALCULATOR_DIALOG, pParent),mStr(_T(""))
	, result(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}
void CcalculatorDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, mStr);          //编辑框上显示的内容
	DDX_Text(pDX, IDC_EDIT2, result);
}
BEGIN_MESSAGE_MAP(CcalculatorDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_EN_CHANGE(IDC_EDIT1, &CcalculatorDlg::OnEnChangeEdit1)
	ON_BN_CLICKED(IDC_BUTTONabout, &CcalculatorDlg::OnBnClickedButtonabout)
	ON_BN_CLICKED(IDC_BUTTON1, &CcalculatorDlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CcalculatorDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CcalculatorDlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CcalculatorDlg::OnBnClickedButton4)
	ON_BN_CLICKED(IDC_BUTTON5, &CcalculatorDlg::OnBnClickedButton5)
	ON_BN_CLICKED(IDC_BUTTON6, &CcalculatorDlg::OnBnClickedButton6)
	ON_BN_CLICKED(IDC_BUTTON7, &CcalculatorDlg::OnBnClickedButton7)
	ON_BN_CLICKED(IDC_BUTTON8, &CcalculatorDlg::OnBnClickedButton8)
	ON_BN_CLICKED(IDC_BUTTON9, &CcalculatorDlg::OnBnClickedButton9)
	ON_BN_CLICKED(IDC_BUTTON0, &CcalculatorDlg::OnBnClickedButton0)
	ON_BN_CLICKED(IDC_BUTTONe, &CcalculatorDlg::OnBnClickedButtone)
	ON_BN_CLICKED(IDC_BUTTONpai, &CcalculatorDlg::OnBnClickedButtonpai)
	ON_BN_CLICKED(IDC_BUTTONdot, &CcalculatorDlg::OnBnClickedButtondot)
	ON_BN_CLICKED(IDC_BUTTONDEL, &CcalculatorDlg::OnBnClickedButtondel)
	ON_BN_CLICKED(IDC_BUTTONAC, &CcalculatorDlg::OnBnClickedButtonac)
	ON_BN_CLICKED(IDC_BUTTONmultiply, &CcalculatorDlg::OnBnClickedButtonmultiply)
	ON_BN_CLICKED(IDC_BUTTONdivide, &CcalculatorDlg::OnBnClickedButtondivide)
	ON_BN_CLICKED(IDC_BUTTONplus, &CcalculatorDlg::OnBnClickedButtonplus)
	ON_BN_CLICKED(IDC_BUTTONminus, &CcalculatorDlg::OnBnClickedButtonminus)
	ON_BN_CLICKED(IDC_BUTTONANS, &CcalculatorDlg::OnBnClickedButtonans)
	ON_BN_CLICKED(IDC_BUTTONequal, &CcalculatorDlg::OnBnClickedButtonequal)
	ON_BN_CLICKED(IDC_BUTTONsin, &CcalculatorDlg::OnBnClickedButtonsin)
	ON_BN_CLICKED(IDC_BUTTONcos, &CcalculatorDlg::OnBnClickedButtoncos)
	ON_BN_CLICKED(IDC_BUTTONtan, &CcalculatorDlg::OnBnClickedButtontan)
	ON_BN_CLICKED(IDC_BUTTONcot, &CcalculatorDlg::OnBnClickedButtoncot)
	ON_BN_CLICKED(IDC_BUTTONarcsin, &CcalculatorDlg::OnBnClickedButtonarcsin)
	ON_BN_CLICKED(IDC_BUTTONarccos, &CcalculatorDlg::OnBnClickedButtonarccos)
	ON_BN_CLICKED(IDC_BUTTONarctan, &CcalculatorDlg::OnBnClickedButtonarctan)
	ON_BN_CLICKED(IDC_BUTTONreciprocal, &CcalculatorDlg::OnBnClickedButtonreciprocal)
	ON_BN_CLICKED(IDC_BUTTONsquare_root, &CcalculatorDlg::OnBnClickedButtonsquareroot)
	ON_BN_CLICKED(IDC_BUTTONcube_root, &CcalculatorDlg::OnBnClickedButtoncuberoot)
	ON_BN_CLICKED(IDC_BUTTONsquare, &CcalculatorDlg::OnBnClickedButtonsquare)
	ON_BN_CLICKED(IDC_BUTTONcube, &CcalculatorDlg::OnBnClickedButtoncube)
	ON_BN_CLICKED(IDC_BUTTONpower, &CcalculatorDlg::OnBnClickedButtonpower)
	ON_BN_CLICKED(IDC_BUTTONlog, &CcalculatorDlg::OnBnClickedButtonlog)
	ON_BN_CLICKED(IDC_BUTTONlog10, &CcalculatorDlg::OnBnClickedButtonlog10)
	ON_BN_CLICKED(IDC_BUTTONln, &CcalculatorDlg::OnBnClickedButtonln)
	ON_BN_CLICKED(IDC_BUTTONleftparenthese, &CcalculatorDlg::OnBnClickedButtonleftparenthese)
	ON_BN_CLICKED(IDC_BUTTONrightparenthese, &CcalculatorDlg::OnBnClickedButtonrightparenthese)
	ON_COMMAND(IDOK, &CcalculatorDlg::OnIdok)
	ON_COMMAND(IDCANCEL, &CcalculatorDlg::OnIdcancel)
	ON_COMMAND(IDCLOSE, &CcalculatorDlg::OnIdclose)
	ON_WM_CLOSE()
	ON_EN_CHANGE(IDC_EDIT2, &CcalculatorDlg::OnEnChangeEdit2)
	ON_STN_CLICKED(IDC_TITLE, &CcalculatorDlg::OnStnClickedTitle)
//	ON_WM_CTLCOLOR()
ON_WM_CTLCOLOR()
END_MESSAGE_MAP()

// CcalculatorDlg 消息处理程序
BOOL CcalculatorDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	m_static2.SubclassDlgItem(IDC_EDIT2, this);
	m_font2.CreatePointFont(200, _T("黑体"));
	m_static2.SetFont(&m_font2);

	m_static1.SubclassDlgItem(IDC_EDIT1, this);
	m_font1.CreatePointFont(140, _T("黑体"));
	m_static1.SetFont(&m_font1);

	m_static3.SubclassDlgItem(IDC_TITLE, this);
	m_font3.CreatePointFont(240, _T("微软雅黑"));
	m_static3.SetFont(&m_font3);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}
void CcalculatorDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}
// 如果向对话框添加最小化按钮，则需要下面的代码来绘制该图标。 
//  对于使用文档/视图模型的 MFC 应用程序， 这将由框架自动完成。
void CcalculatorDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CPaintDC   dc(this);
		CRect   rect;
		GetClientRect(&rect);                     //获取对话框长宽      
		CDC   dcBmp;                               //定义并创建一个内存设备环境
		dcBmp.CreateCompatibleDC(&dc);             //创建兼容性DC
		CBitmap   bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP1);    //载入资源中图片
		BITMAP   m_bitmap;                         //图片变量               
		bmpBackground.GetBitmap(&m_bitmap);       //将图片载入位图中
		//将位图选入临时内存设备环境
		CBitmap* pbmpOld = dcBmp.SelectObject(&bmpBackground);
		//调用函数显示图片StretchBlt显示形状可变
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcBmp, 0, 0, m_bitmap.bmWidth, m_bitmap.bmHeight, SRCCOPY);
	}
}
//当用户拖动最小化窗口时系统调用此函数取得光标显示。
HCURSOR CcalculatorDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


//自定义函数
//位数
int WeiShu(double num) {
	int result = 0;
	int temp = floor(num);
	num *= 10;
	temp *= 10;
	int xiaoshu = num - temp;
	while (xiaoshu > 0 && xiaoshu < 10 && result <= 12) {
		result++;
		temp = floor(num);
		num *= 10;
		temp *= 10;
		xiaoshu = num - temp;
	}
	return result;
}
//自动调整位数输出
CString strCreate(double result) {
	CString  str;
	switch (WeiShu(result)) {
	case 0: str.Format(_T("%.0f"), result); break;
	case 1: str.Format(_T("%.1f"), result); break;
	case 2: str.Format(_T("%.2f"), result); break;
	case 3: str.Format(_T("%.3f"), result); break;
	case 4: str.Format(_T("%.4f"), result); break;
	case 5: str.Format(_T("%.5f"), result); break;
	case 6: str.Format(_T("%.6f"), result); break;
	case 7: str.Format(_T("%.7f"), result); break;
	case 8: str.Format(_T("%.8f"), result); break;
	case 9: str.Format(_T("%.9f"), result); break;
	case 10: str.Format(_T("%.10f"), result); break;
	case 11: str.Format(_T("%.11f"), result); break;
	default:str.Format(_T("%.12f"), result); break;
	}
	return str;
}
/*
//弹窗
void MyAlert(char* p) {
	INT_PTR  nRes;// 用于保存DoModal函数的返回值 
	MyDialog1 TAN;
	TAN.alert = p;
	nRes =TAN.DoModal();
	if (nRes == IDCANCEL)return;
}*/

void CcalculatorDlg::OnEnChangeEdit1()
{
	UpdateData(TRUE);
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonabout()  //弹出关于窗口
{
	CAboutDlg dlg;
	dlg.DoModal();
}//已删除

void CcalculatorDlg::OnBnClickedButton1()      //按下按钮的消息处理函数
{
	UpdateData(TRUE);
	if (flag)                         //若当前处于刚刚按下=键的状态，则执行AC键的操作，flag归零
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"1";                    //编辑框内文本末尾增加对应的字符串
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton2()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"2";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton3()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"3";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton4()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"4";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton5()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"5";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton6()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"6";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton7()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"7";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton8()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"8";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton9()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"9";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButton0()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"0";
	UpdateData(FALSE);
}
//e的按钮
void CcalculatorDlg::OnBnClickedButtone()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"e";
	UpdateData(FALSE);
}
//Π的按钮
void CcalculatorDlg::OnBnClickedButtonpai()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"π";
	UpdateData(FALSE);
}
//小数点的按钮
void CcalculatorDlg::OnBnClickedButtondot()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L".";
	UpdateData(FALSE);
}

//DEL键：退格操作
void CcalculatorDlg::OnBnClickedButtondel()  
{
	UpdateData(TRUE);
	if (!mStr.IsEmpty())
	{
		size_t length = mStr.GetLength();
		if (mStr[length - 1] == L'(')        //遇到左括号，将左括号左侧对应的函数（sin、tan等）一并清除
		{
			int ncount = mStr.Replace(L"(",L"(");
			ncount -= 1;
			mStr = mStr.Left(mStr.GetLength() - parenthese_left[ncount].function.GetLength() - 1);
			parenthese_left.pop_back();
		}
		else if (mStr[length - 1] == L'g')//将log，ANS作为整体清除
		{
			mStr = mStr.Left(mStr.GetLength() - 3);
		}
		else if (mStr[length - 1] == L'S')
		{
			mStr = mStr.Left(mStr.GetLength() - 3);
		}
		else
		{
			mStr = mStr.Left(mStr.GetLength() - 1);
		}
	}
	if (mStr.IsEmpty())  //清除到空，清空所有
	{
		result = L"";
		parenthese_left.clear();
	}
	if (flag)  
	{
		result = L"";
		flag = false;
	}
	UpdateData(FALSE);
}

//AC键：清空除ans外所有成员
void CcalculatorDlg::OnBnClickedButtonac() 
{
	UpdateData(TRUE);
	mStr = L"";
	result = L"";
	parenthese_left.clear();
	flag = false;
	UpdateData(FALSE);
}

//乘法
void CcalculatorDlg::OnBnClickedButtonmultiply()
{
	UpdateData(TRUE);
	//作为运算符，在窗口处于刚刚按下=键的状态下按下此键，则在算式开头添加ANS，类似卡西欧计算器的设置
	if (flag)          
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"*";
	UpdateData(FALSE);
}
//除法
void CcalculatorDlg::OnBnClickedButtondivide()
{
	UpdateData(TRUE);
	if (flag)           //类似的
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"/";
	UpdateData(FALSE);
}
//加法
void CcalculatorDlg::OnBnClickedButtonplus()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"+";
	UpdateData(FALSE);
}
//减法
void CcalculatorDlg::OnBnClickedButtonminus()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"-";
	UpdateData(FALSE);
}

//ANS键：保留结果
void CcalculatorDlg::OnBnClickedButtonans()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"ANS";
	UpdateData(FALSE);
}

//=键：执行运算
void CcalculatorDlg::OnBnClickedButtonequal()  
{
	UpdateData(TRUE);
	if (!mStr.IsEmpty())  //空字符串不做处理
	{
		if (check())      //先检查
		{
			ans = calculate(mStr, 0, mStr.GetLength(), ans);//再计算
			result = strCreate(ans);
			   //默认的12位输出精度，多了有误差
			flag = true;
		}
	}
	UpdateData(FALSE);
}

//函数区：
void CcalculatorDlg::OnBnClickedButtonsin()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"sin(";         //由于屏幕上多了一个左括号，所以要记录下这个左括号的信息，如左侧的函数、所在位置等；下同
	PARENTHESE_LEFT parenthese_sin;
	parenthese_sin.function = L"sin";
	parenthese_sin.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_sin));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtoncos()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"cos(";
	PARENTHESE_LEFT parenthese_cos;
	parenthese_cos.function = L"cos";
	parenthese_cos.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_cos));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtontan()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"tan(";
	PARENTHESE_LEFT parenthese_tan;
	parenthese_tan.function = L"tan";
	parenthese_tan.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_tan));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtoncot()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"cot(";
	PARENTHESE_LEFT parenthese_cot;
	parenthese_cot.function = L"cot";
	parenthese_cot.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_cot));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonarcsin()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"arcsin(";
	PARENTHESE_LEFT parenthese_arcsin;
	parenthese_arcsin.function = L"arcsin";
	parenthese_arcsin.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_arcsin));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonarccos()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"arccos(";
	PARENTHESE_LEFT parenthese_arccos;
	parenthese_arccos.function = L"arccos";
	parenthese_arccos.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_arccos));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonarctan()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"arctan(";
	PARENTHESE_LEFT parenthese_arctan;
	parenthese_arctan.function = L"arctan";
	parenthese_arctan.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_arctan));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonreciprocal()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";             //都含有^运算符，在这里按照运算符处理
		flag = false;
	}
	mStr += L"^(-1)";
	PARENTHESE_LEFT parenthese_reciprocal;
	parenthese_reciprocal.function = L"";       //^作运算符处理，所以当前（函数信息位空
	parenthese_reciprocal.location = mStr.GetLength() - 4;
	parenthese_left.push_back(std::move(parenthese_reciprocal));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonsquareroot()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"^(1/2)";
	PARENTHESE_LEFT parenthese_squareroot;
	parenthese_squareroot.function = L"";
	parenthese_squareroot.location = mStr.GetLength() - 5;
	parenthese_left.push_back(std::move(parenthese_squareroot));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtoncuberoot()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"^(1/3)";
	PARENTHESE_LEFT parenthese_cuberoot;
	parenthese_cuberoot.function = L"";
	parenthese_cuberoot.location = mStr.GetLength() - 5;
	parenthese_left.push_back(std::move(parenthese_cuberoot));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonsquare()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"^(2)";
	PARENTHESE_LEFT parenthese_square;
	parenthese_square.function = L"";
	parenthese_square.location = mStr.GetLength() - 3;
	parenthese_left.push_back(std::move(parenthese_square));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtoncube()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"^(3)";
	PARENTHESE_LEFT parenthese_cube;
	parenthese_cube.function = L"";
	parenthese_cube.location = mStr.GetLength() - 3;
	parenthese_left.push_back(std::move(parenthese_cube));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonpower()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"^";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonlog()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		mStr += L"ANS";
		flag = false;
	}
	mStr += L"log";
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonlog10()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"lg(";
	PARENTHESE_LEFT parenthese_lg;
	parenthese_lg.function = L"lg";
	parenthese_lg.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_lg));
	UpdateData(FALSE);
}
void CcalculatorDlg::OnBnClickedButtonln()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"ln(";
	PARENTHESE_LEFT parenthese_ln;
	parenthese_ln.function = L"ln";
	parenthese_ln.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese_ln));
	UpdateData(FALSE);
}

//左括号
void CcalculatorDlg::OnBnClickedButtonleftparenthese()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L"(";
	PARENTHESE_LEFT parenthese;
	parenthese.function = L"";
	parenthese.location = mStr.GetLength() - 1;
	parenthese_left.push_back(std::move(parenthese));
	UpdateData(FALSE);
}
//右括号
void CcalculatorDlg::OnBnClickedButtonrightparenthese()
{
	UpdateData(TRUE);
	if (flag)
	{
		CcalculatorDlg::OnBnClickedButtonac();
		flag = false;
	}
	mStr += L")";
	UpdateData(FALSE);
}

void CcalculatorDlg::OnIdok()
{
	//防止按回车键退出程序
	return;
}
void CcalculatorDlg::OnIdcancel()
{
	//防止按Esc键退出程序
	return;
}
void CcalculatorDlg::OnIdclose()
{
	AfxGetMainWnd()->SendMessage(WM_CLOSE);
}
void CcalculatorDlg::OnClose()   //保证点击×正常退出
{
	CDialogEx::OnCancel();
	CDialogEx::OnClose();
}

BOOL CcalculatorDlg::PreTranslateMessage(MSG* pMsg)
{
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_BACK)
	{
		if (GetFocus()->GetDlgCtrlID() == IDC_EDIT1)//按下退格相当于按下DEL键
		{
			CcalculatorDlg::OnBnClickedButtondel();
		}
		return TRUE;
	}
	if (pMsg->message == WM_KEYDOWN && pMsg->wParam == VK_ESCAPE)
		return TRUE;
	return CDialogEx::PreTranslateMessage(pMsg);
}

void CcalculatorDlg::OnEnChangeEdit2()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


void CcalculatorDlg::OnStnClickedTitle()
{
	// TODO: 在此添加控件通知处理程序代码
}



//HBRUSH CcalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
//{
//	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);
//
	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔
//	return hbr;
//}


HBRUSH CcalculatorDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	
	return hbr;
}
