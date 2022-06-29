#include <iostream>
#include <stack>
#include <string>

using namespace std;

string input; //实验输入符号串
char num = 65;

/*设置终结符集Vt*/
const char Vt[] = {'l', '+', '-', '*', '/', '(', ')', '#'};
/*分析表如下*/
string analysis[5][8] = {"TR", "NULL", "NULL", "NULL", "NULL", "TR", "NULL", "NULL",
                         "NULL", "+TAR", "-TSR", "NULL", "NULL", "NULL", "$", "$",
                         "FY", "NULL", "NULL", "NULL", "NULL", "FY", "NULL", "NULL",
                         "NULL", "$", "$", "*FMY", "/FDY", "NULL", "$", "$",
                         "lL", "NULL", "NULL", "NULL", "NULL", "(E)", "NULL", "NULL",
                        };//epsilon串用$表示，E1用R表示，T1用Y表示,+用S表示，-用S表示，*用M表示，/用d表示，l用L表示

/*终结符匹配*/
int match(char c) {
	if (c > 64 && c < 123) {
		return 0; //l对应的大小写26个字母
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

/*确认对应表中的行列*/
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


/*LL(1)分析法主功能程序*/
void analyze() {
	stack<char> syn, sem; //SYN[n],SEM[m]
	int temp;
	string v1, v2;
	char inp, put;
	syn.push('#'); //将#压入栈中
	syn.push('E'); //将初始E压入栈中
	int j = 0;
	while (true) {
		char c = syn.top();
		temp = 0;
		for (int i = 0; i < 8; i++) {
			if (Vt[i] == c) {
				if (input[j] == '#' && c == '#') { //终止条件
					cout << "翻译成功" << endl;
					return;
				}
				if (match(input[j]) == address(c)) {
					syn.pop();
					inp = input[j];
					j++;
					temp = 1;
					break;
				} else {
					cout << "“" << input[j] << "”不符合语法规则" << endl;
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
			cout << "“" << input[j] << "”不符合语法规则" << endl;
			return;
		}
		if (analysis[a][b] == "NULL") {
			string res = input.substr(0, j);
			cout << "“" << res << "”错误匹配" << endl;
			return;
		}
		int len = analysis[a][b].length();
		//cout << "把“" << analysis[a][b] << "”逆序压入栈中" << endl;
		for (int i = len - 1; i >= 0; i--) {
			if (analysis[a][b][i] == '$') {
				continue;
			}
			syn.push(analysis[a][b][i]);
		}
	}
}

int main() {
	cout << "请输入符号串：" << endl;
	cin >> input;
	input += '#'; //字符串尾为#
	cout << "四元式格式翻译结果如下：" << endl;
	analyze();
}
