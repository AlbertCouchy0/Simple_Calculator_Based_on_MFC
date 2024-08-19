
// calculatorDlg.h: 头文件
//

#pragma once
#include<vector>
#include<memory>
#include<cmath>
#include<cstdlib>

//结构体：储存左括号位置、绑定的函数、匹配的右括号的位置
struct PARENTHESE_LEFT
{
	int location;
	CString function;       
	int location_right;
};

// CcalculatorDlg 对话框
class CcalculatorDlg : public CDialogEx
{
// 构造
public:
	CcalculatorDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CALCULATOR_DIALOG };       
#endif
	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

//自定义函数
public:
	bool check();           //检查算式
	friend double calculate(CString str, int start, int lenth, double ans);     //解析算式，算出结果
	afx_msg void OnIdok();
	afx_msg void OnIdcancel();
	afx_msg void OnIdclose();
	afx_msg void OnClose();
	afx_msg void OnEnChangeEdit1();
	afx_msg void OnBnClickedButtonabout();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	afx_msg void OnBnClickedButton6();
	afx_msg void OnBnClickedButton7();
	afx_msg void OnBnClickedButton8();
	afx_msg void OnBnClickedButton9();
	afx_msg void OnBnClickedButton0();
	afx_msg void OnBnClickedButtone();
	afx_msg void OnBnClickedButtonpai();
	afx_msg void OnBnClickedButtondot();
	afx_msg void OnBnClickedButtondel();
	afx_msg void OnBnClickedButtonac();
	afx_msg void OnBnClickedButtonmultiply();
	afx_msg void OnBnClickedButtondivide();
	afx_msg void OnBnClickedButtonplus();
	afx_msg void OnBnClickedButtonminus();
	afx_msg void OnBnClickedButtonans();
	afx_msg void OnBnClickedButtonequal();
	afx_msg void OnBnClickedButtonsin();
	afx_msg void OnBnClickedButtoncos();
	afx_msg void OnBnClickedButtontan();
	afx_msg void OnBnClickedButtoncot();
	afx_msg void OnBnClickedButtonarcsin();
	afx_msg void OnBnClickedButtonarccos();
	afx_msg void OnBnClickedButtonarctan();
	afx_msg void OnBnClickedButtonreciprocal();
	afx_msg void OnBnClickedButtonsquareroot();
	afx_msg void OnBnClickedButtoncuberoot();
	afx_msg void OnBnClickedButtonsquare();
	afx_msg void OnBnClickedButtoncube();
	afx_msg void OnBnClickedButtonpower();
	afx_msg void OnBnClickedButtonlog();
	afx_msg void OnBnClickedButtonlog10();
	afx_msg void OnBnClickedButtonln();
	afx_msg void OnBnClickedButtonleftparenthese();
	afx_msg void OnBnClickedButtonrightparenthese();


	virtual BOOL PreTranslateMessage(MSG* pMsg);
//自定义变量
private:
	CString mStr;         
	CString result;      
	double ans = NAN;     //The nan functions return a quiet NaN value.
	bool flag = false;//记录是否刚刚按下等于按钮
	std::vector<PARENTHESE_LEFT> parenthese_left;    //声明左括号变量
	//添加两个可以控制字体的类变量
	CFont m_font1;
	CStatic m_static1;
	CFont m_font2;
	CStatic m_static2;
	CFont m_font3;
	CStatic m_static3;
public:
	afx_msg void OnEnChangeEdit2();
	afx_msg void OnStnClickedTitle();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
};
