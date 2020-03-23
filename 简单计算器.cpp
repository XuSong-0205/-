#include <iostream>
#include <string>
#include <stack>
using std::cin;
using std::cout;
using std::endl;
using std::stack;
using std::string;

int calculate(const string& str);

int main()
{
	cout << "请输入一个正确的算术表达式 : ";
	string str;
	cin >> str;
	cout << "该表达式计算结果为 : " << calculate(str) << endl;
	cout << "按任意键退出！" << endl;
	cin.get();
	cin.get();
	return 0;
}

int calculate(const string& s)
{
	int num = 0;
	char sign = '+';
	stack<int> sta;

	for (size_t i = 0; i < s.size(); ++i)
	{
		if (isdigit(static_cast<unsigned char>(s.at(i))))
		{
			num = num * 10 + (s.at(i) - '0');
		}

		// 遇到左括号，开始递归计算括号内的值
		if (s.at(i) == '(')
		{
			num = calculate(string(s.begin() + i + 1, s.end()));
			// 右括号以内已计算完毕，忽略
			while (s.at(i) != ')')
			{
				++i;
			}
			i = i >= s.size() - 1 ? i : i + 1;
		}

		if ((!isdigit(static_cast<unsigned char>(s.at(i))) && s.at(i) != ' ') || i == s.size() - 1)
		{
			if (sign == '+')
			{
				sta.push(num);
			}
			else if (sign == '-')
			{
				sta.push(-num);
			}
			else if (sign == '*' || sign == '/')
			{
				const int temp = sign == '*' ? sta.top() * num : sta.top() / num;
				sta.pop();
				sta.push(temp);
			}

			sign = s.at(i);
			num = 0;
		}

		// 遇到右括号，结束括号内计算，将括号内的值计算返回
		if (s.at(i) == ')')
		{
			break;
		}
	}

	int ans = 0;
	while (!sta.empty())
	{
		ans += sta.top();
		sta.pop();
	}

	return ans;
}