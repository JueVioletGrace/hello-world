/* 2152153 李欣晨 计科 */
#include "popstar.h"

/***************************************************************************
  函数名称：
  功    能：输入矩阵坐标指令
  输入参数：int row : 行数
			int col : 列数
			char order[] : 存放指令的数组
			int stars[][N + 2] : 星星数组
			char search[][N + 2] : 标记查找的数组
  返 回 值：int count : 本次消除个数
  说    明：判断输入格式是否正确，以及坐标位置是否为0，周围是否连续相同值
***************************************************************************/
int input_order(int row, int col, char order[], int stars[][N + 2], char search[][N + 2])
{
	const int STR_MAX = 5;
	int value;

	while (1) {
		cout << endl << "请以字母+数字形式[例：c2]输入矩阵坐标：";

		cin >> order;

		order[0] += ('A' - 'a') * ('a' <= order[0] && order[0] <= 'z');

		/* 先判断输入格式是否正确 */
		if ('A' <= order[0] && order[0] <= ('A' + row - 1)
			&& '0' <= order[1] && order[1] <= ('0' + col - 1)
			&& order[2] == '\0') {
			cout << "输入为" << order[0] << "行" << order[1] << "列" << endl;
		}
		else {
			cout << "输入错误，请重新输入" << endl;
			continue;
		}

		/* 再判断是否合法 */
		if ((value = stars[order[0] - 'A' + 1][order[1] - '0' + 1]) != 0) {
			/* 将order处理为坐标值 */
			order[0] = order[0] - 'A' + 1;
			order[1] = order[1] - '0' + 1;
			//(--测试--)cout << "(" << (int)order[0] << "," << (int)order[1] << ")" << endl;

			/* 查找连续相同值 */
			int count;
			count = count_neighbor(order, value, search, stars);

			/* 判断 */
			if (count == 1)
				cout << "输入的矩阵坐标位置处无连续相同值，请重新输入" << endl;
			else {
				cout << endl << "查找结果数组：" << endl;
				print_search_array(row, col, search);
				cout << endl << "当前数组（不同色标识）：" << endl;
				print_stars_array(0, row, col, stars, search);
				return count;
			}
		}
		else
			cout << "输入的矩阵坐标位置为0（非法位置），请重新输入" << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：打印星星数组
  输入参数：int print_mode : 打印模式
			int row : 行数
			int col : 列数
			char order[] : 存放指令的数组
			int stars[][N + 2] : 当前星星数组
			char search[][N + 2] : 标记查找的数组
  返 回 值：
  说    明：print_mode为奇数时标识所有为0的位置，为偶数时标识当前相同连续值
***************************************************************************/
void print_stars_array(int print_mode, int row, int col, int stars[][N + 2], char search[][N + 2])
{
	const int WIDTH = 3;
	int i, j;
	int X, Y;

	/* 打印边框第一行 */
	cout << setw(WIDTH) << '|';
	for (i = 0; i < col; i++)
		cout << setw(WIDTH) << i;
	cout << endl;

	/* 打印边框第二行 */
	cout << setfill('-') << setw(WIDTH) << '+';
	cout << setw(WIDTH * col) << '-' << endl;
	cout << setfill(' ');

	/* 打印其余行 */
	for (i = 1; i <= row; i++) {
		cout << (char)('A' + i - 1) << setw(WIDTH - 1) << '|';
		for (j = 1; j <= col; j++) {
			switch (print_mode % 2) {
				case 0:
					cout << setw(WIDTH - 1) << ' ';
					cct_getxy(X, Y);
					if (search[i][j] == '*') {
						cct_showch(X, Y, stars[i][j] + '0', COLOR_HYELLOW, COLOR_BLACK);
						cct_setcolor();
					}
					else
						cout << stars[i][j];
					break;
				case 1:
					cout << setw(WIDTH - 1) << ' ';
					cct_getxy(X, Y);
					if (stars[i][j] == 0) {
						cct_showch(X, Y, stars[i][j] + '0', COLOR_HYELLOW, COLOR_BLACK);
						cct_setcolor();
					}
					else
						cout << stars[i][j];
					break;
				default:
					break;
			}
		}
		cout << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：打印查找结果数组
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void print_search_array(int row, int col, char search[M + 2][N + 2])
{
	const int WIDTH = 3;
	int i, j;

	/* 打印边框第一行 */
	cout << setw(WIDTH) << '|';
	for (i = 0; i < col; i++)
		cout << setw(WIDTH) << i;
	cout << endl;

	/* 打印边框第二行 */
	cout << setfill('-') << setw(WIDTH) << '+';
	cout << setw(WIDTH * col) << '-' << endl;
	cout << setfill(' ');

	/* 打印其余行 */
	for (i = 1; i <= row; i++) {
		cout << (char)('A' + i - 1) << setw(WIDTH - 1) << '|';
		for (j = 1; j <= col; j++) {
			cout << setw(WIDTH) << search[i][j];
		}
		cout << endl;
	}
}

/***************************************************************************
  函数名称：
  功    能：确认是否消除提示语
  输入参数：
  返 回 值：
  说    明：供菜单A-C使用
***************************************************************************/
char remove_or_not(char pos[])
{
	char remove_flag;
	cout << endl << "请确认是否把" << char(pos[0] + 'A' - 1) << char(pos[1] + '0' - 1) << "及周围的相同值消除(Y/N/Q)：";
	int X, Y;
	cct_getxy(X, Y);
	while (1) {
		remove_flag = _getche();
		remove_flag += ('A' - 'a') * ('a' <= remove_flag && remove_flag <= 'z');
		if (remove_flag == 'Y' || remove_flag == 'N' || remove_flag == 'Q') {
			cout << endl;
			return remove_flag;
		}
		else
			cct_gotoxy(X, Y);
	}
}

/***************************************************************************
  函数名称：
  功    能：模式A的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_A(int row, int col, int stars[][N + 2])
{
	char search[M + 2][N + 2];
	char pos[200];

	/* 打印当前数组 */
	cout << endl << "当前数组：" << endl;
	print_stars_array(1, row, col, stars, search);

	/* 输入并处理矩阵坐标 */
	input_order(row, col, pos, stars, search);
}

/***************************************************************************
  函数名称：
  功    能：模式B的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_B(int& score, int row, int col, int stars[][N + 2])
{
	char search[M + 2][N + 2];

	while (1) {
		char pos[200];
		int count_remove;
		int score_new = 0;

		/* 打印当前数组 */
		cout << endl << "当前数组：" << endl;
		print_stars_array(1, row, col, stars, search);

		/* 输入并处理矩阵坐标 */
		count_remove = input_order(row, col, pos, stars, search);

		/* 判断是否消除 */
		switch (remove_or_not(pos)) {
			case 'Q':
				return;
				break;
			case 'N':
				cout << endl << "【请重新选择坐标】" << endl;
				break;
			case 'Y':
				/* 消除 */
				do_remove(stars, search);
				cout << endl << "相同值归并后的数组(不同色标识)：" << endl;
				print_stars_array(0, row, col, stars, search);

				/* 记录得分 */
				score_new = count_remove * count_remove * 5;
				score += score_new;
				cout << endl << "本次得分：" << score_new << " 总得分：" << score << endl;

				/* 下落 */
				to_be_continued("按回车键进行数组下落操作...");
				do_move(row, col, stars, 0, 0);
				cout << endl << "下落后的数组：" << endl;
				print_stars_array(1, row, col, stars, search);

				return;
				break;
			default:
				break;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：模式C的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_C(int& score, int row, int col, int stars[][N + 2])
{
	char search[M + 2][N + 2];

	while (1) {
		char pos[200];
		int count_remove;
		int score_new = 0;
		int score_prize = 0;
		int left;

		/* 打印当前数组 */
		cout << endl << "当前数组：" << endl;
		print_stars_array(1, row, col, stars, search);

		/* 判断游戏是否结束 */
		left = eliminableStars_left_or_not(row, col, stars);
		if (left >= 0) {
			score_prize = (10 - left) * (left < 10) * 180;
			score += score_prize;
			cct_setcolor(COLOR_HYELLOW, COLOR_RED);
			cout << endl << "剩余" << left << "个不可消除项，本关结束！" << endl;
			cout << "奖励得分：" << score_prize << " 最终总得分：" << score << endl;
			cct_setcolor();
			return;
		}

		/* 输入并处理矩阵坐标 */
		count_remove = input_order(row, col, pos, stars, search);

		/* 判断是否消除 */
		switch (remove_or_not(pos)) {
			case 'Q':
				return;
				break;
			case 'N':
				cout << endl << "【请重新选择坐标】" << endl;
				break;
			case 'Y':
				/* 消除 */
				do_remove(stars, search);
				cout << endl << "相同值归并后的数组(不同色标识)：" << endl;
				print_stars_array(0, row, col, stars, search);

				/* 记录得分 */
				score_new = count_remove * count_remove * 5;
				score += score_new;
				cout << endl << "本次得分：" << score_new << " 总得分：" << score << endl;

				/* 下落 */
				to_be_continued("按回车键进行数组下落操作...");
				do_move(row, col, stars, 0, 0);
				cout << endl << "下落后的数组：" << endl;
				print_stars_array(1, row, col, stars, search);

				cout << endl;
				to_be_continued("本次消除结束，按回车键继续新一次的消除...");
				break;
			default:
				break;
		}
	}
}