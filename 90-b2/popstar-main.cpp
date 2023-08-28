/* 2152153 李欣晨 计科 */
#include "popstar.h"

/***************************************************************************
  函数名称：
  功    能：打印菜单
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void show_menu()
{
	cct_cls();
	cout << "--------------------------------------------" << endl;
	cout << "A.命令行找出可消除项并标识" << endl;
	cout << "B.命令行完成一次消除（分步骤显示）" << endl;
	cout << "C.命令行完成一关（分步骤显示）" << endl;
	cout << "D.伪图形界面下用鼠标选择一个色块（无分隔线）" << endl;
	cout << "E.伪图形界面下用鼠标选择一个色块（有分隔线）" << endl;
	cout << "F.伪图形界面完成一次消除（分步骤）" << endl;
	cout << "G.伪图形界面完整版" << endl;
	cout << "Q.退出" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[请选择: ] ";
}

/***************************************************************************
  函数名称：
  功    能：选择菜单模式
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
char chose_mode()
{
	char mode;
	int flag;

	while (1) {
		mode = _getch();
		mode += ('A' - 'a') * (flag = ('a' <= mode && mode <= 'z'));
		if ('A' <= mode && mode <= 'G' || mode == 'Q') {
			cout << (char)(mode + flag * ('a' - 'A'));
			Sleep(200);
			return mode;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：选择行数、列数，并初始化星星数组
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void init_para(int* row, int* col, int stars[][N + 2])
{
	while (1) {
		cout << "请输入行数(8-10)：" << endl;
		cin >> *row;
		if (8 <= *row && *row <= 10 && cin.good())
			break;
		else {
			cin.clear();
			cin.ignore(65536, '\n');
		}
	}

	while (1) {
		cout << "请输入列数(8-10)：" << endl;
		cin >> *col;
		if (8 <= *col && *col <= 10 && cin.good())
			break;
		else {
			cin.clear();
			cin.ignore(65536, '\n');
		}
	}

	int i, j;
	for (i = 1; i <= *row; i++)
		for (j = 1; j <= *col; j++)
			stars[i][j] = rand() % RAND + 1;
}

/***************************************************************************
  函数名称：
  功    能：等待输入end，以结束本题
  输入参数：
  返 回 值：
  说    明：仅输入end三个字母时才会结束，不限大小写
***************************************************************************/
void wait_for_end()
{
	const int STR_N = 200;

	while (1) {
		cout << endl << "本小题结束，请输入End继续...";
		char str[STR_N] = { '\0' };

		cin >> str;

		if ((str[0] == 'e' || str[0] == 'E') && (str[1] == 'n' || str[1] == 'N')
			&& (str[2] == 'd' || str[2] == 'D') && (str[3] == '\0'))
			break;
		else
			cin.ignore(65536, '\n');
	}
}

int main()
{
	srand((unsigned int)(time(0)));
	while (1) {
		char mode;
		int row, col;
		int score = 0;
		int stars[M + 2][N + 2] = { 0 };

		show_menu();
		mode = chose_mode();
		if (mode == 'Q')
			break;

		cct_cls();
		init_para(&row, &col, stars);

		switch (mode) {
			case 'A':
				mode_A(row, col, stars);
				break;
			case 'B':
				mode_B(score, row, col, stars);
				break;
			case 'C':
				mode_C(score, row, col, stars);
				break;
			case 'D':
				mode_D(row, col, stars, 0);
				break;
			case 'E':
				mode_E(row, col, stars, 1);
				break;
			case 'F':
				mode_F(score, row, col, stars, 0);
				break;
			case 'G':
				mode_G(score, row, col, stars, 1);
				break;
			default:
				break;
		}

		wait_for_end();
	}
	return 0;
}