#include <iostream>
#include <stack>
#include <string>

using namespace std;

string input; //ʵ��������Ŵ�

/*�����ս����Vt*/
const char Vt[] = {'l', '+', '-', '*', '/', '(', ')', '#'};
/*����������*/
string analysis[5][8] = {"TR", "NULL", "NULL", "NULL", "NULL", "TR", "NULL", "NULL",
                         "NULL", "+TR", "-TR", "NULL", "NULL", "NULL", "$", "$",
                         "FY", "NULL", "NULL", "NULL", "NULL", "FY", "NULL", "NULL",
                         "NULL", "$", "$", "*FY", "/FY", "NULL", "$", "$",
                         "l", "NULL", "NULL", "NULL", "NULL", "(E)", "NULL", "NULL",
                        };//epsilon����$��ʾ��E1��R��ʾ��T1��Y��ʾ

/*�ս��ƥ��*/
int match(char c) {
	if (c > 64 && c < 123) {
		return 0; //l��Ӧ�Ĵ�Сд26����ĸ
	}
	switch (c) {
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
		case '(':
			return 5;
		case ')':
			return 6;
		case '#':
			return 7;
		default:
			return -1;
	}
}

/*ȷ�϶�Ӧ���е�����*/
int address(char c) {
	switch (c) {
		case 'E':
			return 0;
		case 'R':
			return 1;
		case 'T':
			return 2;
		case 'Y':
			return 3;
		case 'F':
			return 4;
		case 'l':
			return 0;
		case '+':
			return 1;
		case '-':
			return 2;
		case '*':
			return 3;
		case '/':
			return 4;
		case '(':
			return 5;
		case ')':
			return 6;
		case '#':
			return 7;
		default:
			return -1;
	}
}

/*LL(1)�����������ܳ���*/
void analyze() {
	stack<char> lls;
	lls.push('#'); //��#ѹ��ջ��
	lls.push('E'); //����ʼEѹ��ջ��
	int j = 0;
	int temp;
	while (true) {
		char c = lls.top();
		temp = 0;
		for (int i = 0; i < 8; i++) {
			if (Vt[i] == c) {
				if (input[j] == '#' && c == '#') { //��ֹ����
					cout << "�����ɹ�" << endl;
					return;
				}
				if (match(input[j]) == address(c)) {
					lls.pop();
					cout << "��" << input[j] << "���ɹ�ƥ��" << endl;
					j++;
					temp = 1;
					break;
				} else {
					cout << "��" << input[j] << "���������﷨����" << endl;
					return;
				}
			}
		}
		if (temp == 1) {
			continue;
		}
		int a = address(c);
		int b = match(input[j]);
		if (b == -1) {
			cout << "��" << input[j] << "���������﷨����" << endl;
			return;
		}
		lls.pop();
		if (analysis[a][b] == "NULL") {
			string res = input.substr(0, j);
			cout << "��" << res << "������ƥ��" << endl;
			return;
		}
		int len = analysis[a][b].length();
		cout << "�ѡ�" << analysis[a][b] << "������ѹ��ջ��" << endl;
		for (int i = len - 1; i >= 0; i--) {
			if (analysis[a][b][i] == '$') {
				continue;
			}
			lls.push(analysis[a][b][i]);
		}
	}
}

int main() {
	cout << "��������Ŵ���" << endl;
	cin >> input;
	input += '#'; //�ַ���βΪ#
	cout << "�������������£�" << endl;
	analyze();
}
