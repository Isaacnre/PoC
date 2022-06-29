#include <iostream>
#include <fstream>
#include <stdio.h>
#include <string.h>


using namespace std;


char input[30]; //输入缓冲区
char temp;	//读取一个字符
int rep = 0; //判断多符号

const char keylist[33][15] = { "main", "for", "do", "while", "break", "continue", "if", "else", "goto", "switch", "case", "default", "return",
                               "char", "double", "enum", "float", "int", "long", "short", "signed", "struct", "union", "unsigned", "void",
                               "auto", "extern", "register", "static", "const", "sizeof", "typedef", "volatile"
                             };
//关键字

FILE *fin;

void init() { //初始化缓冲区为空
	for (int i = 0; i < 20; ++i) {
		input[i] = '\0';
	}
}

int token() {
	init();
	if (rep == 0) { //初次运行
		temp = getc(fin);
	}
	rep = 1; //关掉循环中多读取一次的阀门
	while (temp == ' ' || temp == '\t' || temp == '\n') { //清除中间的空白符
		temp = getc(fin);
	}
	int index = 0;
	/*先进行关键字的搜索判断*/
	if (temp >= 'a' && temp <= 'z' || temp >= 'A' && temp <= 'Z') { //判断为letter或者关键字
		while (temp >= 'a' && temp <= 'z' || temp >= 'A' && temp <= 'Z') {
			input[index] = temp;
			index++;
			temp = getc(fin);
		}
		input[index++] = '\0'; //字符串结尾
		for (int i = 0; i < 33; i++) {
			if (strcmp(input, keylist[i]) == 0) {//判断为关键字
				return i;
			}
		}
		return 33;//判断为letter
	}
	/*进行number的判断*/
	if (temp >= '0' && temp <= '9') {
		while (temp >= '0' && temp <= '9' || temp == '.') {
			input[index++] = temp;
			temp = getc(fin);
		}
		return 34;
	}
	/*其他情况的判断*/
	else {
		input[index++] = temp;
		switch (temp) {
			case '=':
				temp = getc(fin);
				if (temp == '=') {
					input[index++] = temp;
					temp = getc(fin);
					return 44;
				}
				return 35;
			case '+':
				rep = 0;
				return 36;
			case '-':
				rep = 0;
				return 37;
			case '*':
				rep = 0;
				return 38;
			case '/':
				temp = getc(fin);
				if (temp == '*') {
					input[index++] = temp;
					temp = getc(fin);
					while (temp != '*') {
						temp = getc(fin);
						if (temp == '*') {
							input[index++] = temp;
							temp = getc(fin);
							if (temp == '/') {
								input[index++] = temp;
								break;
							}
						}
					}
					rep = 0;
					return 57;
				}
				return 39;
			case '>':
				temp = getc(fin);
				if (temp == '=') {
					input[index++] = temp;
					temp = getc(fin);
					return 42;
				}
				return 40;
			case '<':
				temp = getc(fin);
				if (temp == '=') {
					input[index++] = temp;
					temp = getc(fin);
					return 43;
				}
				return 41;
			case '!':
				temp = getc(fin);
				if (temp == '=') {
					input[index++] = temp;
					temp = getc(fin);
					return 45;
				}
				return 46;
			case ',':
				rep = 0;
				return 47;
			case ':':
				rep = 0;
				return 48;
			case ';':
				rep = 0;
				return 49;
			case '"':
				temp = getc(fin);
				while (temp != '"') {
					input[index++] = temp;
					temp = getc(fin);
				}
				input[index++] = temp;
				rep = 0;
				return 50;
			case '(':
				rep = 0;
				return 51;
			case ')':
				rep = 0;
				return 52;
			case '[':
				rep = 0;
				return 53;
			case ']':
				rep = 0;
				return 54;
			case '{':
				rep = 0;
				return 55;
			case '}':
				rep = 0;
				return 56;
			case '#':
				rep = 0;
				return 58;
			case EOF:
				return 59;
			default:
				rep = 0;
				return -1;
		}
	}
}


int main() {
	fin = fopen("demo.c", "r");
	ofstream fout;
	fout.open("tokens.txt");
	if (!fout.is_open()) {
		cout << "Open outfile failed!" << endl;
	}
	int judge = 0;
	while (true) {
		judge = token();
		if (judge == 59) { //文件结尾
			break;
		}
		if (judge == -1) { //报错
			fout << "ERROR!" << endl;
		} else {
			cout << judge << "," << input << endl;
			fout << judge << "," << input << endl;
		}
	}
	fout.close();
	return 0;
}
