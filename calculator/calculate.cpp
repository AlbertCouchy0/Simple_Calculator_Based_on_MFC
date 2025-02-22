//������㺯�����ļ�
#include "pch.h"
#include "framework.h"
#include "calculator.h"
#include "calculatorDlg.h"
#include "afxdialogex.h"
#include<iostream>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


//���㣩�ṹ�壺������ʽΪ���ݽṹ�����ݾ��Ǹ�����������������֮��Ĺ�ϵΪ�����
struct NUMBER                    
{                                  //����ʽ����Ϊ��������Ľڵ��¼�˵�ǰ����������ֵ�����������������Լ�������������ȼ�
	double num;
	CString opt;
	int precedence;//���ȼ�
	std::shared_ptr<NUMBER> next;//����Ľڵ㶨��
};

//��һ���������Ӧ������
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

//����������������Ӧ������
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

//��������������Ƿ����
bool CcalculatorDlg::check()    
{
	int left_parenthese = mStr.Replace(L"(", L"(");
	int right_parenthese = mStr.Replace(L")", L")");//��ȡ�������ŷ�������
	if (left_parenthese != right_parenthese)//����������Դ�������������������
	{
		result = L"error!";
		return false;
	}
	for (int i = 0; i < left_parenthese; i++)//�����������
	{
		int pair = 0;
		for (int j = parenthese_left[i].location + 1; j < mStr.GetLength(); j++)
			//����������һλ��ʼ��������pair==-1������������Χ�����ţ���Ϊ�������
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
	CString possible_head = L"1234567890(-+sctaleA��"; //�������ַ�����λ�ͣ��Ҳ���ֵ��ַ�
	CString possible_head2 = L"1234567890(sctaeA��";  //���ұ߲��ܳ��ֵ��ַ�
	if (possible_head.Find(mStr[0]) == -1)//��һ���ַ�����
	{
		result = L"error!";
		return false;
	}
	for (int i = 0; i < left_parenthese; i++)//�����ź��һ���ַ�����
	{
		if (possible_head.Find(mStr[parenthese_left[i].location + 1]) == -1)
		{
			result = L"error!";
			return false;
		}
	}
	CString numbers = L"0123456789";
	CString special = L"e��";
	for (int i = 0; i < left_parenthese; i++)//��������ࡢ�������Ҳ����
	{
		if (parenthese_left[i].location != 0)   //��������λ
		{
			if (numbers.Find(mStr[parenthese_left[i].location - 1]) != -1)//�����Ϊ����
			{
				result = L"error!";
				return false;
			}
			int j = parenthese_left[i].location - parenthese_left[i].function.GetLength() - 1; //��ǰ�����ַ�����ǰ��һλ����sin����sǰһλ
			if (j != -1)   //��һλ������λ
			{
				if (numbers.Find(mStr[j]) != -1 || special.Find(mStr[j]) != -1 || mStr[j] == L'S')  //��һλΪ���֣�����e���У���ANS�е�S
				{
					result = L"error!";
					return false;
				}
			}
		}
		if (parenthese_left[i].location_right != mStr.GetLength() - 1)    //������ĩβ
		{
			if (possible_head2.Find(mStr[parenthese_left[i].location_right + 1]) != -1)//����Ƿ��ַ�
			{
				result = L"error!";
				return false;
			}
			if (mStr[parenthese_left[i].location_right + 1] == L'l' && mStr[parenthese_left[i].location_right + 2] != L'o')//������log
			{
				result = L"error!";
				return false;
			}
		}
	}
	for (int i = 1; i < mStr.GetLength(); i++)//С�������
	{
		if (mStr[i] == L'.')
		{
			if (numbers.Find(mStr[i + 1]) == -1)//.��������
			{
				result = L"error!";
				return false;
			}
			if (numbers.Find(mStr[i - 1]) == -1)//.ǰ��������
			{
				result = L"error!";
				return false;
			}
			if (i == mStr.GetLength() - 1)//.���ַ���ĩβ
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
				if (numbers.Find(mStr[j] == -1) && mStr[j] != L'.')//һ���Ϸ����֣��������±��ƶ������ֺ�
				{
					i = j;
					break;
				}
				if (mStr[j] == L'.')//һ��������������С����
				{
					result = L"error!";
					return false;
				}
			}
		}
	}
	CString operators = L"+-*/^";
	for (int i = 0; i < mStr.GetLength(); i++)//���������
	{
		if (operators.Find(mStr[i]) != -1)
		{
			if (i == mStr.GetLength() - 1)//�����������ĩβ
			{
				result = L"error!";
				return false;
			}
			if ((operators.Find(mStr[i + 1]) != -1) || (mStr[i + 1] == L'l' && mStr[i + 2] == L'o'))//�������д
			{
				result = L"error!";
				return false;
			}
			if (mStr[i + 1] == L')')//�������Ϊ��
			{
				result = L"error!";
				return false;
			}
		}
		if (mStr[i] == L'l' && mStr[i + 1] == L'o')//���������log
		{
			i = i + 2;    //�ƶ���logĩβ
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
	for (int i = 0; i < mStr.GetLength(); i++)//�����ַ�����Ĵ���
	{
		if (mStr[i] == L'A')//ANS
		{
			if (i)    //ANS������λ�������Ƿ�����β���������ֹ�±�Խ��
			{
				if (numbers.Find(mStr[i - 1]) != -1 || mStr[i - 1] == L')')//AǰΪ���ֻ��ߣ���Ϊȱʡ�˺š�ȱ������������
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i - 1]) != -1)//AǰΪe���
				{
					result = L"error!";
					return false;
				}
				if (mStr[i - 1] == L'S')//ANSǰΪANS
				{
					result = L"error!";
					return false;
				}
				i = i + 2;
				if (i == mStr.GetLength() - 1)//ANS��S��ĩβ�����ںϷ����
				{
					return true;
				}
				if (numbers.Find(mStr[i + 1]) != -1 || mStr[i + 1] == L'(')//S��ȱ�������
				{
					result = L"error!";
					return false;
				}
				if (special.Find(mStr[i + 1]) != -1)//S��Ϊe���
				{
					result = L"error!";
					return false;
				}
			}
			else
			{
				i = i + 2;    //SΪ��λ��ֱ�ӷ����󷽵����
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
		if (special.Find(mStr[i]) != -1)  //e���ǰ����жϣ�����
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

//���ģ����ַ��������Ű󶨺������ڶ�������Ϊ���ã��Ա����������ŵ���Ϣ������
void paired(CString str, std::vector<PARENTHESE_LEFT>& parenthese_left_)  
{
	int left_parenthese = str.Replace(L"(", L"(");
	CString left = L"ngst";               //�����������ܵĽ�β������
	for (int i = 0; i < str.GetLength(); i++)      //ͨ��ö�٣������ͣ�ǰ�ĺ�����
	{
		if (str[i] == L'(')
		{
			if (i)//i��λ����λʱ�ſ����к�����
			{
				PARENTHESE_LEFT parenthese_left;
				if (left.Find(str[i - 1]) == -1)//str��i-1��������ǰһλ�Ҳ�����Ӧ����
				{
					parenthese_left.function = L"";
					parenthese_left.location = i;
					parenthese_left_.push_back(std::move(parenthese_left));//���ñ���������Ϣ
					continue;
				}
				else
				{
					//n��β�ĺ���
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
					//g��β�ĺ���
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
					//s��β�ĺ���
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
					//t��β�ĺ���
					if (str[i - 1] == L't')
					{
						parenthese_left.function = L"cot";
						parenthese_left.location = i;
						parenthese_left_.push_back(std::move(parenthese_left));
						continue;
					}
				}
			}
			else//i��ʱλ����λ
			{
				PARENTHESE_LEFT parenthese_left;
				parenthese_left.function = L"";
				parenthese_left.location = i;
				parenthese_left_.push_back(std::move(parenthese_left));
				continue;
			}
		}
	}
	for (int i = 0; i < left_parenthese; i++)//�����������
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

//���壩��Ԫ:���㡪��һ�������ǽ��յ��ַ����������ڶ����ŵĴ������н��е�����
// ��2��3������������Ӵ��Ŀ�ʼ��ͳ���
double calculate(CString str ,int start, int lenth ,double ans)     
{
	double result = NAN;

	CString mStr_ = str.Mid(start, lenth);    //��Ҫ������Ӵ��Ӹ������ȡ������������������֮����Ӵ�
	std::vector<PARENTHESE_LEFT> parenthese_left_;
	paired(mStr_, parenthese_left_);//ʶ�����Ŷ�Ӧ����
	int left_parenthese = mStr_.Replace(L"(", L"(");
	CString numbers = L"1234567890";

	std::shared_ptr<NUMBER> phead = 0;
	std::shared_ptr<NUMBER> pnow = phead;
	std::vector<std::shared_ptr<NUMBER>> all_num;    //�Ƚ�Ҫ��������ʽ�����еĽڵ㱣������
	
	//���ַ����еĽڵ���ȡ������һ�α�������iָʾ��ǰ������������
	for (int i = 0; i < mStr_.GetLength(); i++)    
	{
		//���������ֻ�г�������ǰ���-�Žи��ţ��ڿ�ͷ���һ����Ч��������0-����
		if (i == 0&&mStr_[i] == L'-')           
		{
			NUMBER num_now; 
			num_now.num = 0; 
			num_now.opt = L"-"; 
			num_now.precedence = 1; 
			all_num.push_back(std::make_shared<NUMBER>(num_now));//@������ӵ�������
		}
		//����Ե���������֮����Ӵ���Ϊһ������������������
		if (mStr_[i] == L'(')             
		{
			NUMBER num_now;
			int j = 0;
			for (j = 0; j < left_parenthese; j++)//��õ�ǰ����Ӧ������
			{
				if (parenthese_left_[j].location == i)
				{
					break;
				}
			}
			//������������ȵ���һ�����������Ӵ���ֵ����������ǰ�ĺ������㵱ǰ�����������ֵ
			num_now.num = function(parenthese_left_[j].function, calculate(mStr_, i + 1, parenthese_left_[j].location_right - i - 1, ans));
			i = parenthese_left_[j].location_right + 1;//��ǰ�����±��ƶ����������Ҳ�һλ
			//�����ַ���ĩβ�Ĵ������
			if (i == mStr_.GetLength())  
			{
				num_now.opt = L"";       //ĩβ�����Ϊ�գ����ȼ�Ϊ0
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@������ӵ�������
				break;
			}
			//����ĩβ���鿴��ǰλ�ö�Ӧ���������ʲô������check()���������Ҳ�ֻ�������������д��Ԫ��
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
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@������ӵ�������
			}
		}
		//����һ�����ֵĿ�ͷλ��
		if (numbers.Find(mStr_[i]) != -1) 
		{
			int j = i;
			//Ѱ�ҡ���¼������ֵĽ���λ�ã���λ����һ���������ҷ�С�������Ϊĩβ
			for (j = i; j <= mStr_.GetLength(); j++)  
			{
				if (j == mStr_.GetLength() - 1)       //ĩβ
				{
					j++;
					break;
				}
				if ((numbers.Find(mStr_[j]) == -1) && mStr_[j] != L'.') //�ҵ�һ���������ֺ�С����ĵط����˴���Ϊ����ĩβ
				{
					break;
				}
			}

			NUMBER num_now;
			num_now.num = _wtof(mStr_.Mid(i, j - i));//CStringת��Ϊdouble
			i = j;                       //�����±��ƶ�����ǰ������ĩβ�ĺ�һλ

			if (i == mStr_.GetLength())  //������ʽĩβ�����������
			{
				num_now.opt = L"";
				num_now.precedence = 0;
				all_num.push_back(std::make_shared<NUMBER>(num_now));//@������ӵ�������
				break;
			}
			else
			{
				if (mStr_[i] == L'+')  //��Ӧ�������������
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
		//�����ַ���ANS�������������һ��ֵΪans����
		if (mStr_[i] == L'A')          
		{
			i = i + 3;
			NUMBER num_now;
			num_now.num = ans;
			if (i == mStr_.GetLength()) //��������������
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
		//�����ַ�������������
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
		//�����ַ�������������
		if (mStr_[i] == L'��')
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

	
	phead = all_num[0];     //����������¼����ͷλ��
	pnow = phead;           //phead��¼����ͷ��ַ��pnowΪ��ǰ���������λ��
	for (int i = 0; i < all_num.size(); i++)  //��������
	{
		if (i != all_num.size() - 1)
		{
			pnow->next = all_num[i + 1];  //��ǰ�ڵ�����һ���ڵ㽨����ϵ
			pnow = pnow->next;
		}
		else
		{
			pnow->next = 0;
		}
	}
	
	pnow = phead;
	for (int i = 4; i > 0; i--) //�����ȼ��Ӹߵ��ͣ���������
	{
		pnow = phead;
		while (pnow)
		{
			if (pnow->precedence == i)//��ǰ�������������������ȼ�����i���
			{
				pnow->num = operate(pnow->opt,pnow->num,pnow->next->num);//��ǰ���������һ�����������㣬��������ٵ�ǰ��������
				pnow->opt = pnow->next->opt;  //��ǰ���������Ǻ�һ���������������һ���������������������Ϣ
				pnow->precedence = pnow->next->precedence;
				pnow->next = pnow->next->next;//�൱�ڽ���һ����������������ɾ����pnow��ָ��ǰ����������Ӧ�Կ��ܵ���һ������
			}
			else
			{
				pnow = pnow->next;//��ǰ�������������������ȼ���i����ȣ�������
			}
		}
	}

	result = phead->num;    //ȫ������������ֻʣ����ͷ������ͷ����ֵ��Ϊ��ʽ��������
	return result;
}

