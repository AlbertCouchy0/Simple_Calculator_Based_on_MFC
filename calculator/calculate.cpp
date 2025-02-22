//储存计算函数的文件
#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"
#include<iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//（零）结构体：抽象算式为数据结构，数据就是各个运算数，运算数之间的关系为运算符
struct NUMBER                    
{                                  //将算式抽象化为链表，链表的节点记录了当前运算数的数值、运算数后的运算符以及该运算符的优先级
	double num;
	CString opt;
	int precedence;//优先级
	std::shared_ptr<NUMBER> next;//链表的节点定义
};

//（一）运算符对应的运算
double operate(CString function, double num_left, double num_right)  
{
	double result = NAN;
	if (function == L"+")
	{
		result = num_left + num_right;
	}
	if (function == L"-")
	{
		result = num_left - num_right;
	}
	if (function == L"*")
	{
		result = num_left * num_right;
	}
	if (function == L"/")
	{
		result = num_left / num_right;
	}
	if (function == L"^")
	{
		result = pow(num_left, num_right);
	}
	if (function == L"log")
	{
		result = log(num_right) / log(num_left);
	}
	return result;
}

//（二）各个函数对应的运算
double function(CString function, double num) 
{
	double result = NAN;
	if (function == L"sin")
	{
		result = sin(num);
	}
	if (function == L"cos")
	{
		result = cos(num);
	}
	if (function == L"tan")
	{
		result = tan(num);
	}
	if (function == L"cot")
	{
		result = 1 / tan(num);
	}
	if (function == L"arcsin")
	{
		result = asin(num);
	}
	if (function == L"arccos")
	{
		result = acos(num);
	}
	if (function == L"arctan")
	{
		result = atan(num);
	}
	if (function == L"lg")
	{
		result = log10(num);
	}
	if (function == L"ln")
	{
		result = log(num);
	}
	if (function == L"")
	{
		result = num;
	}
	return result;
}

//（三）检查括号是否错误
bool CcalculatorDlg::check()    
{
	int left_parenthese = mStr.Replace(L"(", L"(");
	int right_parenthese = mStr.Replace(L")", L")");//获取左右括号符号数量
	if (left_parenthese != right_parenthese)//左右括号配对错误：左右括号数量不等
	{
		result = L"error!";
		return false;
	}
	for (int i = 0; i < left_parenthese; i++)//左右括号配对
	{
		int pair = 0;
		for (int j = parenthese_left[i].location + 1; j < mStr.GetLength(); j++)
			//从左括号右一位开始检索，当pair==-1，检索到最外围的括号，即为最终配对
		{
			if (mStr[j] == L'(')
			{
				pair++;
			}
			if (mStr[j] == L')')
			{
				pair--;
			}
			if (pair == -1)
			{
				parenthese_left[i].location_right = j;
				break;
			}
		}
	}
	CString possible_head = L"1234567890(-+sctaleAπ"; //可能在字符串首位和（右侧出现的字符
	CString possible_head2 = L"1234567890(sctaeAπ";  //）右边不能出现的字符
	if (possible_head.Find(mStr[0]) == -1)//第一个字符错误
	{
		result = L"error!";
		return false;
	}
	for (int i = 0; i < left_parenthese; i++)//左括号后第一个字符错误
	{
		if (possible_head.Find(mStr[parenthese_left[i].location + 1]) == -1)
		{
			result = L"error!";
			return false;
		}
	}
	CString numbers = L"0123456789";
	CString special = L"eπ";
	for (int i = 0; i < left_parenthese; i++)//左括号左侧、右括号右侧错误
	{
		if (parenthese_left[i].location != 0)   //（不在首位
		{
			if (numbers.Find(mStr[parenthese_left[i].location - 1]) != -1)//（左侧为数字
			{
				result = L"error!";
				return false;
			}
			int j = parenthese_left[i].location - parenthese_left[i].function.GetLength() - 1; //（前函数字符串的前面一位，如sin（中s前一位
			if (j != -1)   //这一位不是首位
			{
				if (numbers.Find(mStr[j]) != -1 || special.Find(mStr[j]) != -1 || mStr[j] == L'S')  //这一位为数字，或者e、π，或ANS中的S
				{
					result = L"error!";
					return false;
				}
			}
		}
		if (parenthese_left[i].location_right != mStr.GetLength() - 1)    //）不在末尾
		{
			if (possible_head2.Find(mStr[parenthese_left[i].location_right + 1]) != -1)//）后非法字符
			{
				result = L"error!";
				return false;
			}
			if (mStr[parenthese_left[i].location_right + 1] == L'l' && mStr[parenthese_left[i].location_right + 2] != L'o')//）后不是log
			{
				result = L"error!";
				return false;
			}
		}
	}
	for (int i = 1; i < mStr.GetLength(); i++)//小数点错误
	{
		if (mStr[i] == L'.')
		{
			if (numbers.Find(mStr[i + 1]) == -1)//.后不是数字
			{
				result = L"error!";
				return false;
			}
			if (numbers.Find(mStr[i - 1]) == -1)//.前不是数字
			{
				result = L"error!";
				return false;
			}
			if (i == mStr.GetLength() - 1)//.在字符串末尾
			{
				result = L"error!";
				return false;
			}
			for (int j = i + 1; j < mStr.GetLength(); j++)
			{
				if (numbers.Find(mStr[j]) != -1)
				{
					continue;
				}
				if (numbers.Find(mStr[j] == -1) && mStr[j] != L'.')//一个合法数字，将遍历下标移动到数字后
				{
					i = j;
					break;
				}
				if (mStr[j] == L'.')//一个数字两个以上小数点
				{
					result = L"error!";
					return false;
				}
			}
		}
	}
	CString operators = L"+-*/^";
	for (int i = 0; i < mStr.GetLength(); i++)//运算符错误
	{
		if (operators.Find(mStr[i]) != -1)
		{
			if (i == mStr.GetLength() - 1)//运算符出现在末尾
			{
				result = L"error!";
				return false;
			}
			if ((operators.Find(mStr[i + 1]) != -1) || (mStr[i + 1] == L'l' && mStr[i + 2] == L'o'))//运算符连写
			{
				result = L"error!";
				return false;
			}
			if (mStr[i + 1] == L')')//运算符后为）
			{
				result = L"error!";
				return false;
			}
		}
		if (mStr[i] == L'l' && mStr[i + 1] == L'o')//特殊运算符log
		{
			i = i + 2;    //移动到log末尾
			if (i == mStr.GetLength() - 1)
			{
				result = L"error!";
				return false;
			}
			if ((operators.Find(mStr[i + 1]) != -1) || (mStr[i + 1] == L'l' && mStr[i + 2] == L'o'))
			{
				result = L"error!";
				return false;
			}
			if (mStr[i + 1] == L')')
			{
				result = L"error!";
				return false;
			}
		}
	}
	for (int i = 0; i < mStr.GetLength(); i++)//特殊字符两侧的错误
	{
		if (mStr[i] == L'A')//ANS
		{
			if (i)    //ANS不在首位；区分是否在首尾的情况，防止下标越界
			{
				if (numbers.Find(mStr[i - 1]) != -1 || mStr[i - 1] == L')')//A前为数字或者），为缺省乘号、缺少运算符的情况
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i - 1]) != -1)//A前为e或π
				{
					result = L"error!";
					return false;
				}
				if (mStr[i - 1] == L'S')//ANS前为ANS
				{
					result = L"error!";
					return false;
				}
				i = i + 2;
				if (i == mStr.GetLength() - 1)//ANS的S在末尾，属于合法情况
				{
					return true;
				}
				if (numbers.Find(mStr[i + 1]) != -1 || mStr[i + 1] == L'(')//S后缺少运算符
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i + 1]) != -1)//S后为e或π
				{
					result = L"error!";
					return false;
				}
			}
			else
			{
				i = i + 2;    //S为首位，直接分析后方的情况
				if (i == mStr.GetLength() - 1)
				{
					return true;
				}
				if (numbers.Find(mStr[i + 1]) != -1 || mStr[i + 1] == L'(')
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i + 1]) != -1)
				{
					result = L"error!";
					return false;
				}
			}
		}
		if (special.Find(mStr[i]) != -1)  //e或π前后的判断，类似
		{
			if (i)
			{
				if (numbers.Find(mStr[i - 1]) != -1 || mStr[i - 1] == L')')
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i - 1]) != -1)
				{
					result = L"error!";
					return false;
				}
				if (i == mStr.GetLength() - 1)
				{
					return true;
				}
				if (numbers.Find(mStr[i + 1]) != -1 || mStr[i + 1] == L'(')
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i + 1]) != -1)
				{
					result = L"error!";
					return false;
				}
			}
			else
			{
				if (i == mStr.GetLength() - 1)
				{
					return true;
				}
				if (numbers.Find(mStr[i + 1]) != -1 || mStr[i + 1] == L'(')
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i + 1]) != -1)
				{
					result = L"error!";
					return false;
				}
			}
		}
	}
	return true;
}

//（四）子字符串的括号绑定函数；第二个参数为引用，以保存所有括号的信息到类外
void paired(CString str, std::vector<PARENTHESE_LEFT>& parenthese_left_)  
{
	int left_parenthese = str.Replace(L"(", L"(");
	CString left = L"ngst";               //各个函数可能的结尾（）！
	for (int i = 0; i < str.GetLength(); i++)      //通过枚举，将（和（前的函数绑定
	{
		if (str[i] == L'(')
		{
			if (i)//i不位于首位时才可能有函数绑定
			{
				PARENTHESE_LEFT parenthese_left;
				if (left.Find(str[i - 1]) == -1)//str【i-1】即括号前一位找不到对应函数
				{
					parenthese_left.function = L"";
					parenthese_left.location = i;
					parenthese_left_.push_back(std::move(parenthese_left));//引用变量储存信息
					continue;
				}
				else
				{
					//n结尾的函数
					if (str[i - 1] == L'n')
					{
						if (str[i - 2] == L'l')
						{
							parenthese_left.function = L"ln";
							parenthese_left.location = i;
							parenthese_left_.push_back(std::move(parenthese_left));
							continue;
						}
						if (str[i - 2] == L'i')
						{
							if (i > 5 && str[i - 5] == L'r')
							{
								parenthese_left.function = L"arcsin";
								parenthese_left.location = i;
								parenthese_left_.push_back(std::move(parenthese_left));
								continue;
							}
							else
							{
								parenthese_left.function = L"sin";
								parenthese_left.location = i;
								parenthese_left_.push_back(std::move(parenthese_left));
								continue;
							}
						}
						if (str[i - 2] == L'a')
						{
							if (i > 5 && str[i - 5] == L'r')
							{
								parenthese_left.function = L"arctan";
								parenthese_left.location = i;
								parenthese_left_.push_back(std::move(parenthese_left));
								continue;
							}
							else
							{
								parenthese_left.function = L"tan";
								parenthese_left.location = i;
								parenthese_left_.push_back(std::move(parenthese_left));
								continue;
							}
						}
					}
					//g结尾的函数
					if (str[i - 1] == L'g')
					{
						if (str[i - 2] == L'l')
						{
							parenthese_left.function = L"lg";
							parenthese_left.location = i;
							parenthese_left_.push_back(std::move(parenthese_left));
							continue;
						}
						else
						{
							parenthese_left.function = L"";
							parenthese_left.location = i;
							parenthese_left_.push_back(std::move(parenthese_left));
							continue;
						}
					}
					//s结尾的函数
					if (str[i - 1] == L's')
					{
						if (i > 5 && str[i - 5] == L'r')
						{
							parenthese_left.function = L"arccos";
							parenthese_left.location = i;
							parenthese_left_.push_back(std::move(parenthese_left));
							continue;
						}
						else
						{
							parenthese_left.function = L"cos";
							parenthese_left.location = i;
							parenthese_left_.push_back(std::move(parenthese_left));
							continue;
						}
					}
					//t结尾的函数
					if (str[i - 1] == L't')
					{
						parenthese_left.function = L"cot";
						parenthese_left.location = i;
						parenthese_left_.push_back(std::move(parenthese_left));
						continue;
					}
				}
			}
			else//i此时位于首位
			{
				PARENTHESE_LEFT parenthese_left;
				parenthese_left.function = L"";
				parenthese_left.location = i;
				parenthese_left_.push_back(std::move(parenthese_left));
				continue;
			}
		}
	}
	for (int i = 0; i < left_parenthese; i++)//左右括号配对
	{
		int pair = 0;
		for (int j = parenthese_left_[i].location + 1; j < str.GetLength(); j++)
		{
			if (str[j] == L'(')
			{
				pair++;
			}
			if (str[j] == L')')
			{
				pair--;
			}
			if (pair == -1)
			{
				parenthese_left_[i].location_right = j;
				break;
			}
		}
	}
}

//（五）友元:计算—第一个参数是接收的字符串，方便在对括号的处理函数中进行迭代；
// 第2、3个参数标记了子串的开始点和长度
double calculate(CString str ,int start, int lenth ,double ans)     
{
	double result = NAN;

	CString mStr_ = str.Mid(start, lenth);    //将要运算的子串从父串里截取出来，例如两个括号之间的子串
	std::vector<PARENTHESE_LEFT> parenthese_left_;
	paired(mStr_, parenthese_left_);//识别括号对应函数
	int left_parenthese = mStr_.Replace(L"(", L"(");
	CString numbers = L"1234567890";

	std::shared_ptr<NUMBER> phead = 0;
	std::shared_ptr<NUMBER> pnow = phead;
	std::vector<std::shared_ptr<NUMBER>> all_num;    //先将要出现在算式链表中的节点保存下来
	
	//将字符串中的节点提取出来（一次遍历）；i指示当前遍历到了哪里
	for (int i = 0; i < mStr_.GetLength(); i++)    
	{
		//负号情况；只有出现在最前面的-才叫负号；在开头添加一个等效的运算数0-即可
		if (i == 0&&mStr_[i] == L'-')           
		{
			NUMBER num_now; 
			num_now.num = 0; 
			num_now.opt = L"-"; 
			num_now.precedence = 1; 
			all_num.push_back(std::make_shared<NUMBER>(num_now));//@将结果加到链表中
		}
		//将配对的左右括号之间的子串视为一个运算数，加入链表
		if (mStr_[i] == L'(')             
		{
			NUMBER num_now;
			int j = 0;
			for (j = 0; j < left_parenthese; j++)//获得当前所对应的括号
			{
				if (parenthese_left_[j].location == i)
				{
					break;
				}
			}
			//计算操作数：先迭代一次自身，计算子串的值；再用括号前的函数计算当前运算数具体的值
			num_now.num = function(parenthese_left_[j].function, calculate(mStr_, i + 1, parenthese_left_[j].location_right - i - 1, ans));
			i = parenthese_left_[j].location_right + 1;//当前遍历下标移动到右括号右侧一位
			//到了字符串末尾的处理程序
			if (i == mStr_.GetLength())  
			{
				num_now.opt = L"";       //末尾运算符为空，优先级为0
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@将结果加到链表中
				break;
			}
			//不在末尾，查看当前位置对应的运算符是什么（经过check()函数，）右侧只能是运算符），写入元素
			else  
			{
				if (mStr_[i] == L'+')
				{
					num_now.opt = L"+";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'-')
				{
					num_now.opt = L"-";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'*')
				{
					num_now.opt = L"*";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'/')
				{
					num_now.opt = L"/";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'^')
				{
					num_now.opt = L"^";
					num_now.precedence = 3;
				}
				if (mStr_[i] == L'l')
				{
					num_now.opt = L"log";
					num_now.precedence = 4;
				}
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@将结果加到链表中
			}
		}
		//发现一个数字的开头位置
		if (numbers.Find(mStr_[i]) != -1) 
		{
			int j = i;
			//寻找、记录这个数字的结束位置，该位置是一个非数字且非小数点或者为末尾
			for (j = i; j <= mStr_.GetLength(); j++)  
			{
				if (j == mStr_.GetLength() - 1)       //末尾
				{
					j++;
					break;
				}
				if ((numbers.Find(mStr_[j]) == -1) && mStr_[j] != L'.') //找到一个不是数字和小数点的地方，此处即为数字末尾
				{
					break;
				}
			}

			NUMBER num_now;
			num_now.num = _wtof(mStr_.Mid(i, j - i));//CString转化为double
			i = j;                       //遍历下标移动到当前运算数末尾的后一位

			if (i == mStr_.GetLength())  //整个算式末尾的情况：类似
			{
				num_now.opt = L"";
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@将结果加到链表中
				break;
			}
			else
			{
				if (mStr_[i] == L'+')  //对应的运算符，类似
				{
					num_now.opt = L"+";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'-')
				{
					num_now.opt = L"-";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'*')
				{
					num_now.opt = L"*";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'/')
				{
					num_now.opt = L"/";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'^')
				{
					num_now.opt = L"^";
					num_now.precedence = 3;
				}
				if (mStr_[i] == L'l')
				{
					num_now.opt = L"log";
					num_now.precedence = 4;
				}
				all_num.push_back(std::make_shared<NUMBER>(num_now));
			}
		}
		//特殊字符：ANS，则链表中添加一个值为ans的数
		if (mStr_[i] == L'A')          
		{
			i = i + 3;
			NUMBER num_now;
			num_now.num = ans;
			if (i == mStr_.GetLength()) //获得运算符，类似
			{
				num_now.opt = L"";
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));
				break;
			}
			else
			{
				if (mStr_[i] == L'+')
				{
					num_now.opt = L"+";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'-')
				{
					num_now.opt = L"-";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'*')
				{
					num_now.opt = L"*";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'/')
				{
					num_now.opt = L"/";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'^')
				{
					num_now.opt = L"^";
					num_now.precedence = 3;
				}
				if (mStr_[i] == L'l')
				{
					num_now.opt = L"log";
					num_now.precedence = 4;
				}
				all_num.push_back(std::make_shared<NUMBER>(num_now));
			}
		}
		//特殊字符，处理方法类似
		if (mStr_[i] == L'e') 
		{
			i = i + 1;
			NUMBER num_now;
			num_now.num = 2.71828182845904523536;
			if (i == mStr_.GetLength())
			{
				num_now.opt = L"";
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));
				break;
			}
			else
			{
				if (mStr_[i] == L'+')
				{
					num_now.opt = L"+";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'-')
				{
					num_now.opt = L"-";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'*')
				{
					num_now.opt = L"*";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'/')
				{
					num_now.opt = L"/";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'^')
				{
					num_now.opt = L"^";
					num_now.precedence = 3;
				}
				if (mStr_[i] == L'l')
				{
					num_now.opt = L"log";
					num_now.precedence = 4;
				}
				all_num.push_back(std::make_shared<NUMBER>(num_now));
			}
		}
		//特殊字符，处理方法类似
		if (mStr_[i] == L'π')
		{
			i = i + 1;
			NUMBER num_now;
			num_now.num = 3.14159265358979323846;
			if (i == mStr_.GetLength())
			{
				num_now.opt = L"";
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));
				break;
			}
			else
			{
				if (mStr_[i] == L'+')
				{
					num_now.opt = L"+";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'-')
				{
					num_now.opt = L"-";
					num_now.precedence = 1;
				}
				if (mStr_[i] == L'*')
				{
					num_now.opt = L"*";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'/')
				{
					num_now.opt = L"/";
					num_now.precedence = 2;
				}
				if (mStr_[i] == L'^')
				{
					num_now.opt = L"^";
					num_now.precedence = 3;
				}
				if (mStr_[i] == L'l')
				{
					num_now.opt = L"log";
					num_now.precedence = 4;
				}
				all_num.push_back(std::make_shared<NUMBER>(num_now));
			}
		}
	}

	
	phead = all_num[0];     //创建链表，记录链表头位置
	pnow = phead;           //phead记录链表头地址，pnow为当前遍历链表的位置
	for (int i = 0; i < all_num.size(); i++)  //创建链表
	{
		if (i != all_num.size() - 1)
		{
			pnow->next = all_num[i + 1];  //当前节点与下一个节点建立联系
			pnow = pnow->next;
		}
		else
		{
			pnow->next = 0;
		}
	}
	
	pnow = phead;
	for (int i = 4; i > 0; i--) //按优先级从高到低，遍历链表
	{
		pnow = phead;
		while (pnow)
		{
			if (pnow->precedence == i)//当前运算数后的运算符的优先级，与i相等
			{
				pnow->num = operate(pnow->opt,pnow->num,pnow->next->num);//当前运算数与后一个运算数运算，结果保存再当前运算数中
				pnow->opt = pnow->next->opt;  //当前运算数覆盖后一个运算数，保存后一个运算数关于运算符的信息
				pnow->precedence = pnow->next->precedence;
				pnow->next = pnow->next->next;//相当于将后一个运算数从链表中删除，pnow仍指向当前运算数，以应对可能的下一次运算
			}
			else
			{
				pnow = pnow->next;//当前运算数后的运算符的优先级与i不相等，向后遍历
			}
		}
	}

	result = phead->num;    //全部遍历后，链表将只剩链表头，链表头的数值即为算式的运算结果
	return result;
}

