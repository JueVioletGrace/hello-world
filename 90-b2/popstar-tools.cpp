/* 2152153 李欣晨 计科 */
#include "popstar.h"

/***************************************************************************
  函数名称：
  功    能：查找指定坐标位置及周围相同项
  输入参数：char pos[] : 指定的坐标位置
			int value : 指定坐标位置的值
			char search[][N + 2] : 查找结果数组
			int stars[][N + 2] : 当前星星数组
  返 回 值：
  说    明：1.pos中的坐标已经将指令转换成可以直接对应数组行列的坐标
			2.该函数会且仅会更新search数组
***************************************************************************/
void search_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2])
{
	char new_pos[4][2] = { '\0' };

	if (stars[pos[0] - 1][pos[1]] == value && search[pos[0] - 1][pos[1]] == '0') {
		new_pos[0][0] = pos[0] - 1;
		new_pos[0][1] = pos[1];
		search[pos[0] - 1][pos[1]] = '*';
		search_neighbor(new_pos[0], value, search, stars);
	}

	if (stars[pos[0] + 1][pos[1]] == value && search[pos[0] + 1][pos[1]] == '0') {
		new_pos[1][0] = pos[0] + 1;
		new_pos[1][1] = pos[1];
		search[pos[0] + 1][pos[1]] = '*';
		search_neighbor(new_pos[1], value, search, stars);
	}

	if (stars[pos[0]][pos[1] - 1] == value && search[pos[0]][pos[1] - 1] == '0') {
		new_pos[2][0] = pos[0];
		new_pos[2][1] = pos[1] - 1;
		search[pos[0]][pos[1] - 1] = '*';
		search_neighbor(new_pos[2], value, search, stars);
	}

	if (stars[pos[0]][pos[1] + 1] == value && search[pos[0]][pos[1] + 1] == '0') {
		new_pos[3][0] = pos[0];
		new_pos[3][1] = pos[1] + 1;
		search[pos[0]][pos[1] + 1] = '*';
		search_neighbor(new_pos[3], value, search, stars);
	}

	return;
}

/***************************************************************************
  函数名称：
  功    能：查找指定坐标位置及周围相同项的集成函数
  输入参数：
  返 回 值：int count : 连续相同值个数
  说    明：1.该函数内会更新search数组
			2.使用时调用该函数即可，可更新search数组并返回连续相同值个数
***************************************************************************/
int count_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2])
{
	init_search(search, pos[0], pos[1]);
	search_neighbor(pos, value, search, stars);

	/* 计算连续相同值个数 */
	int count = 0, i, j;
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			if (search[i][j] == '*')
				count++;
	return count;
}

/***************************************************************************
  函数名称：
  功    能：执行stars数组中的消除操作
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void do_remove(int stars[][N + 2], char search[][N + 2])
{
	int i, j;
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			if (search[i][j] == '*')
				stars[i][j] = 0;
}

/***************************************************************************
  函数名称：
  功    能：执行stars数组中的移动操作(下落和整列左移)
  输入参数：int row
			int col
			int stars[][N + 2]
			bool flag : 是否需要绘制星星图案
			bool mode : 0代表无分隔；1代表有分隔
  返 回 值：
  说    明：
***************************************************************************/
void do_move(int row, int col, int stars[][N + 2], bool flag, bool mode)
{
	int i, j, k, t;

	/* 先检查下落 */
	for (j = 1; j <= col; j++) {
		for (i = row; i >= 1; i--) {
			if (stars[i][j] == 0) {
				for (k = i; k >= 1; k--) {
					if (stars[k][j] != 0) {
						t = stars[i][j];
						stars[i][j] = stars[k][j];
						stars[k][j] = t;
						if (flag) {
							int start_pos[2];
							int end_pos[2];
							start_pos[0] = k;
							start_pos[1] = j;
							end_pos[0] = i;
							end_pos[1] = j;
							paint_each_move(start_pos, end_pos, mode, stars[i][j] + 8);
						}
						break;
					}
				}
				if (k == 0)
					break;
			}
		}
	}

	/* 后检查左移 */
	int count_1 = 0;
	for (j = 1; j <= col; j++) {
		if (stars[row][j] != 0)
			count_1++;
	}
	for (j = 1; j <= count_1; j++) {
		while (stars[row][j] == 0) {
			for (k = j; k <= col; k++)
				if (stars[row][k] != 0) {
					for (i = row; stars[i][k] != 0; i--) {
						stars[i][k - 1] = stars[i][k];
						stars[i][k] = 0;
						if (flag) {
							int start_pos[2];
							int end_pos[2];
							start_pos[0] = i;
							start_pos[1] = k;
							end_pos[0] = i;
							end_pos[1] = k - 1;
							paint_each_move(start_pos, end_pos, mode, stars[i][k - 1] + 8);
						}
					}
				}
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：判断是否剩余可消除项
  输入参数：
  返 回 值：-1代表有可消除项剩余；若无可消除项剩余，则返回剩余星星数
  说    明：
***************************************************************************/
int eliminableStars_left_or_not(int row, int col, int stars[][N + 2])
{
	int i, j, m, n;
	int count_total = 0, count_neibor = 0;
	char pos[3], search[M + 2][N + 2];

	for (j = 1; stars[row][j] != 0; j++) {
		for (i = row; stars[i][j] != 0; i--) {
			/* 初始化search数组 */
			for (m = 0; m < M + 2; m++) {
				for (n = 0; n < N + 2; n++)
					search[m][n] = '0';
			}
			search[i][j] = '*';

			pos[0] = i;
			pos[1] = j;
			count_total++;
			count_neibor += count_neighbor(pos, stars[i][j], search, stars);
		}
	}

	if (count_neibor == count_total) {
		return count_total;
	}
	else
		return -1;
}

/***************************************************************************
  函数名称：
  功    能：等待回车
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continued(const char* prompt)
{
	cout << endl << prompt;

	/* 忽略除回车键外的所有输入 */
	while (_getch() != '\r')
		;

	cout << endl;
	return;
}

/***************************************************************************
  函数名称：
  功    能：初始化search数组
  输入参数：char search[][N + 2]
			int X : 选中的点的行
			int Y : 选中的点的列
  返 回 值：
  说    明：
***************************************************************************/
void init_search(char search[][N + 2], int X, int Y)
{
	int i, j;
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			search[i][j] = '0';
	search[X][Y] = '*';
}

/***************************************************************************
  函数名称：
  功    能：统计search数组中的标记 * 的个数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int count_search_only(int row, int col, char search[][N + 2])
{
	int count_sear = 0;
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			if (search[i][j] == '*')
				count_sear++;
	return count_sear;
}