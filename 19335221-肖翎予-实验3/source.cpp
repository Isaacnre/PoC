#include <iostream>
#include <stack>
#include <string>

using namespace std;

string input; //ʵ��������Ŵ�
char num = 65;

/*�����ս����Vt*/
const char Vt[] = {'l', '+', '-', '*', '/', '(', ')', '#'};
/*����������*/
string analysis[5][8] = {"TR", "NULL", "NULL", "NULL", "NULL", "TR", "NULL", "NULL",
                         "NULL", "+TAR", "-TSR", "NULL", "NULL", "NULL", "$", "$",
                         "FY", "NULL", "NULL", "NULL", "NULL", "FY", "NULL", "NULL",
                         "NULL", "$", "$", "*FMY", "/FDY", "NULL", "$", "$",
                         "lL", "NULL", "NULL", "NULL", "NULL", "(E)", "NULL", "NULL",
                        };//epsilon����$��ʾ��E1��R��ʾ��T1��Y��ʾ,+��S��ʾ��-��S��ʾ��*��M��ʾ��/��d��ʾ��l��L��ʾ

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
	stack<char> syn, sem; //SYN[n],SEM[m]
	int temp;
	string v1, v2;
	char inp, put;
	syn.push('#'); //��#ѹ��ջ��
	syn.push('E'); //����ʼEѹ��ջ��
	int j = 0;
	while (true) {
		char c = syn.top();
		temp = 0;
		for (int i = 0; i < 8; i++) {
			if (Vt[i] == c) {
				if (input[j] == '#' && c == '#') { //��ֹ����
					cout << "����ɹ�" << endl;
					return;
				}
				if (match(input[j]) == address(c)) {
					syn.pop();
					inp = input[j];
					j++;
					temp = 1;
					break;
				} else {
					cout << "��" << input[j] << "���������﷨����" << endl;
					return;
				}
			}
		}
		switch (c)	{
			case 'L': {
				sem.push(inp);
				syn.pop();
				temp = 2;
				break;
			}
			case 'A': {
				v1.assign(1, sem.top());
				sem.pop();
				v2.assign(1, sem.top());
				sem.pop();
				put = num;
				cout << "(+," << v2 << "," << v1 << "," << put << ")" << endl;
				sem.push(put);
				syn.pop();
				num++;
				temp = 2;
				break;
			}
			case 'S': {
				v1.assign(1, sem.top());
				sem.pop();
				v2.assign(1, sem.top());
				sem.pop();
				put = num;
				cout << "(-," << v2 << "," << v1 << "," << put << ")" << endl;
				sem.push(put);
				syn.pop();
				num++;
				temp = 2;
				break;
			}
			case 'M': {
				v1.assign(1, sem.top());
				sem.pop();
				v2.assign(1, sem.top());
				sem.pop();
				put = num;
				cout << "(*," << v2 << "," << v1 << "," << put << ")" << endl;
				sem.push(put);
				syn.pop();
				num++;
				temp = 2;
				break;
			}
			case 'D': {
				v1.assign(1, sem.top());
				sem.pop();
				v2.assign(1, sem.top());
				sem.pop();
				put = num;
				cout << "(/," << v2 << "," << v1 << "," << num << ")" << endl;
				sem.push(num);
				syn.pop();
				num++;
				temp = 2;
				break;
			}
			default:
				break;
		}
		if (temp == 1 || temp == 2) {
			continue;
		}
		int a = address(c);
		int b = match(input[j]);
		syn.pop();
		if (b == -1) {
			cout << "��" << input[j] << "���������﷨����" << endl;
			return;
		}
		if (analysis[a][b] == "NULL") {
			string res = input.substr(0, j);
			cout << "��" << res << "������ƥ��" << endl;
			return;
		}
		int len = analysis[a][b].length();
		//cout << "�ѡ�" << analysis[a][b] << "������ѹ��ջ��" << endl;
		for (int i = len - 1; i >= 0; i--) {
			if (analysis[a][b][i] == '$') {
				continue;
			}
			syn.push(analysis[a][b][i]);
		}
	}
}

int main() {
	cout << "��������Ŵ���" << endl;
	cin >> input;
	input += '#'; //�ַ���βΪ#
	cout << "��Ԫʽ��ʽ���������£�" << endl;
	analyze();
}
