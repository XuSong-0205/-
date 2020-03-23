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
	cout << "������һ����ȷ���������ʽ : ";
	string str;
	cin >> str;
	cout << "�ñ��ʽ������Ϊ : " << calculate(str) << endl;
	cout << "��������˳���" << endl;
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

		// ���������ţ���ʼ�ݹ���������ڵ�ֵ
		if (s.at(i) == '(')
		{
			num = calculate(string(s.begin() + i + 1, s.end()));
			// �����������Ѽ�����ϣ�����
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

		// ���������ţ����������ڼ��㣬�������ڵ�ֵ���㷵��
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