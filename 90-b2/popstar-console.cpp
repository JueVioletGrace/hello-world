/* 2152153 李欣晨 计科 */
#include "popstar.h"

/***************************************************************************
  函数名称：
  功    能：打印背景边框
  输入参数：bool mode : 0代表无分隔线；1代表有分隔线
			int row : 星星的行
			int col : 星星的列
  返 回 值：
  说    明：
***************************************************************************/
void show_frame(bool mode, int row, int col)
{
	/* 设置屏幕大小 */
	const int cols = BLOCK_WIDTH * col + 3 + FRAME_WIDTH * (2 + mode * (col - 1));
	const int lines = BLOCK_HIGHT * row + 6 + FRAME_HIGHT * (2 + mode * (row - 1));
	cct_setconsoleborder(cols, lines, cols, lines);

	/* 打印第一行 */
	cout << endl;
	int i, j;
	for (i = 0; i < FRAME_WIDTH + 2; i++) {
		cout << ' ';
	}
	for (i = 0; i < col; i++) {
		cout << setw(BLOCK_WIDTH / 2) << i;
		cout << setw(FRAME_WIDTH * mode + BLOCK_WIDTH / 2) << ' ';
	}
	cout << endl;

	/* 打印后续行 */
	int word = 0;
	for (i = 1; i <= lines - 6; i++) {
		/* 打印表示行的字母 */
		if ((i + mode * FRAME_HIGHT) % (BLOCK_HIGHT + mode * FRAME_HIGHT) == 0)
			cout << char('A' + word++) << ' ';
		else
			cout << "  ";

		/* 打印边框和底色 */
		cct_setcolor(BG_COLOR, FRAME_COLOR);
		switch (mode) {
			case 0:
				if (i == 1) {
					cout << "╔";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH / 2; j++) {
						cout << "═";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "╗";
				}
				else if (i == lines - 6) {
					cout << "╚";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH / 2; j++) {
						cout << "═";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "╝";
				}
				else {
					cout << "║";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH; j++) {
						cout << " ";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "║";
				}
				break;
			case 1:
				if (i == 1) {
					cout << "╔";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						(j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0) ? (cout << "╦") : (cout << "═");
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "╗";
				}
				else if (i == lines - 6) {
					cout << "╚";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						(j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0) ? (cout << "╩") : (cout << "═");
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "╝";
				}
				else if ((i - 1) % (BLOCK_HIGHT + FRAME_HIGHT)) {
					cout << "║";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						if (j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0)
							cout << "║";
						else
							cout << "  ";
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "║";
				}
				else {
					cout << "╠";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						if (j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0)
							cout << "╬";
						else
							cout << "═";
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "╣";
				}
				break;
		}
		cct_setcolor();

		cout << endl;
	}

	cct_gotoxy(0, 0);
	cout << "屏幕当前设置为：" << lines << "行" << cols << "列";
	cct_gotoxy(0, lines - 4);
}

/***************************************************************************
  函数名称：
  功    能：画游戏初始界面的所有星星色块
  输入参数：
  返 回 值：
  说    明：mode为0表示无分割线；mode为1表示有分割线
***************************************************************************/
void paint_init_stars(bool mode, int row, int col, int stars[][N + 2])
{
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			paint_one_block(mode, 1, i, j, stars[i][j] + 8, COLOR_BLACK);
}

/***************************************************************************
  函数名称：
  功    能：显示界面上方状态栏
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void show_up_state(int score_new, int score_total, int score_prize)
{
	cct_gotoxy(0, 0);
	if (score_new > 0)
		cout << "本次得分:" << score_new;
	else
		cout << "奖励得分:" << score_prize;
	cout << " 总分:" << score_total << "          ";
}

/***************************************************************************
  函数名称：
  功    能：显示下方状态栏
  输入参数：bool mode : 0代表无分隔线；1代表有分隔线
			int row : 星星数组的行数
			int state : 调整输出内容参数1
			int tool : 调整输出内容参数2
			int i : 当前所处行数
			int j : 当前所处列数
  返 回 值：
  说    明：
***************************************************************************/
void show_down_state(bool mode, int row, int state, int tool, int i, int j)
{
	int Y;
	Y = BLOCK_HIGHT * row + 6 + FRAME_HIGHT * (2 + mode * (row - 1)) - 4;
	cct_gotoxy(0, Y);
	if (tool == CCT_MOUSE_EVENT) {
		switch (state) {
			case 0:
				cout << "[当前鼠标] 位置非法";
				cout << setw(60) << ' ';
				break;
			case 1:
				cout << "[当前鼠标] " << char(i + 'A' - 1) << "行" << char(j + '0' - 1) << "列";
				cout << setw(50) << ' ';
				break;
			case 2:
				cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
				cout << setw(30) << ' ';
				break;
			default:
				break;
		}
	}
	else if (tool == CCT_KEYBOARD_EVENT) {
		switch (state) {
			case 1:
				cout << "[当前键盘] " << char(i + 'A' - 1) << "行" << char(j + '0' - 1) << "列";
				cout << setw(50) << ' ';
				break;
			case 2:
				cout << "箭头键/鼠标移动取消当前选择，回车键/单击左键合成";
				cout << setw(30) << ' ';
				break;
			default:
				break;
		}
	}
	else if (tool == 2) {
		cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << setw(30) << ' ';
	}
	else if (tool == 3) {
		cout << "箭头键/鼠标移动，回车键/单击左键选择并结束" << setw(30) << ' ';
	}
	else if (tool == 4) {
		cout << "选中了" << char(i + 'A' - 1) << "行" << char(j + '0' - 1) << "列" << setw(50) << ' ';
	}
	else if (tool == 5) {
		cct_setcolor(0, COLOR_HYELLOW);
		cout << "周围无相同值，";
		cct_setcolor();
		cout << "箭头键/鼠标移动，回车键/单击左键选择，Q/单击右键结束" << setw(30) << ' ';
	}
	else if (tool == 6) {
		cout << "合成完成，回车键/单击左键下落" << setw(30) << ' ';
	}
	else if (tool == 7) {
		cct_setcolor(0, COLOR_HYELLOW);
		cout << "本次合成结束，按C/单击左键继续新一次的合成";
		cct_setcolor();
	}
	else if (tool == -1)
		cout << "                                           ";
	else if (tool == 8) {
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "剩余";
	}
}

/***************************************************************************
  函数名称：
  功    能：绘制单个星星或者消除单个星星
  输入参数：bool mode : 0表示无分割线；1表示有分割线
			bool paint_star_or_not : 1表示绘制星星；0表示消除星星
			int i : 星星数组中的行
			int j : 星星数组中的列
			const int bg_color : 背景色
			const int fg_color : 前景色
  返 回 值：
  说    明：该函数直接传入星星数组中的行与列即可在对应位置打印
***************************************************************************/
void paint_one_block(bool mode, bool paint_star_or_not, int i, int j, const int bg_color, const int fg_color)
{
	int x, y;
	x = (j - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
	y = 2 + FRAME_HIGHT + (i - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);

	if (paint_star_or_not)
		paint_one_star_xy(x, y, bg_color, fg_color);
	else
		paint_one_block_xy(x, y, mode);
}

/***************************************************************************
  函数名称：
  功    能：按照窗口xy坐标画一个星星色块
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void paint_one_star_xy(int X, int Y, const int bg_color, const int fg_color)
{
	cct_setcolor(bg_color, fg_color);
	cct_gotoxy(X, Y);
	cout << "╔═╗";
	cct_gotoxy(X, Y + 1);
	cout << "║★║";
	cct_gotoxy(X, Y + 2);
	cout << "╚═╝";
	cct_setcolor();
}

/***************************************************************************
  函数名称：
  功    能：按照窗口xy坐标消除单个星星色块
  输入参数：int X : 星星色块左上角的x坐标
			int Y : 星星色块左上角的y坐标
			bool mode : 0代表无分隔；1代表有分隔
  返 回 值：
  说    明：
***************************************************************************/
void paint_one_block_xy(int X, int Y, bool mode)
{
	cct_setcolor(BG_COLOR, FRAME_COLOR);

	int i, j;
	switch (mode) {
		case 0:
			for (j = Y; j < Y + BLOCK_HIGHT; j++)
				for (i = X; i < X + BLOCK_WIDTH; i++)
					cct_showch(i, j, ' ', BG_COLOR, BG_COLOR);
			break;
		case 1:
			for (j = Y; j < Y + BLOCK_HIGHT; j++) {
				for (i = X - X % 2; i < X + BLOCK_WIDTH;) {
					cct_gotoxy(i, j);
					if ((i - 10) % (BLOCK_WIDTH + FRAME_WIDTH) == 0) {
						cout << "║";
					}
					else if ((j - 2) % (BLOCK_HIGHT + FRAME_HIGHT) == 0)
						cout << "═";
					else {
						cout << "  ";
					}
					i += 2;
				}
			}
			break;
	}

	cct_setcolor();
}

/***************************************************************************
  函数名称：
  功    能：定义“光标”的起始位置并显示
  输入参数：bool mode : mode为0表示无分割线；mode为1表示有分割线
			int row : 星星的行
			int stars[][N + 2] : 当前星星数组
			int pos[] : 存放当前选择位置的数组
  返 回 值：
  说    明：每次消除结束都将界面左上角的星星作为移动的起始位置
***************************************************************************/
void show_init_pos(bool mode, int row, int stars[][N + 2], int pos[], int tool)
{
	int i;
	for (i = row; stars[i][1] != 0; i--)
		;
	pos[0] = i + 1;
	pos[1] = 1;
	if (tool == CCT_KEYBOARD_EVENT) {
		Sleep(10);
		paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, CHOSE_COLOR);
	}
}

/***************************************************************************
  函数名称：
  功    能：①判断鼠标的位置是否合法；
			②将窗口x、y坐标对应地转化为数组的行列，存放到pos[]中
  输入参数：
  返 回 值：bool state : 0表示位置非法；1表示位置合法
  说    明：位置合法时才会改变pos[]
***************************************************************************/
bool trans_tool(int row, int col, int x, int y, bool mode, int pos[], int stars[][N + 2])
{
	bool state = false;
	int i, j;
	int X, Y;
	int temp[2];

	switch (mode) {
		case 0:
			if (2 + FRAME_WIDTH <= x && x < 2 + FRAME_WIDTH + col * BLOCK_WIDTH
				&& 2 + FRAME_HIGHT <= y && y < 2 + FRAME_HIGHT + row * BLOCK_HIGHT)
			{
				state = true;
				temp[1] = (x - 2 - FRAME_WIDTH) / BLOCK_WIDTH + 1;
				temp[0] = (y - 2 - FRAME_HIGHT) / BLOCK_HIGHT + 1;

				if (stars[temp[0]][temp[1]] == 0) {
					state = false;
				}
				else {
					pos[0] = temp[0];
					pos[1] = temp[1];
				}
			}
			break;
		case 1:
			for (i = 1; i <= row; i++) {
				Y = 2 + FRAME_HIGHT + (i - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);
				for (j = 1; j <= col; j++) {
					X = (j - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
					if (X <= x && x < X + BLOCK_WIDTH && Y <= y && y < Y + BLOCK_HIGHT) {
						state = true;
						temp[0] = i;
						temp[1] = j;
						if (stars[temp[0]][temp[1]] == 0) {
							state = false;
						}
						else {
							pos[0] = temp[0];
							pos[1] = temp[1];
						}
						break;
					}
				}
				if (state)
					break;
			}
			break;
	}

	return state;
}

/***************************************************************************
  函数名称：
  功    能：处理箭头键并将移动反映在游戏界面上
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void keyboard_move(bool mode, int keycode2, int pos[], int stars[][N + 2], int row, int col, char search[][N + 2])
{
	paint_neibor(mode, search, stars, COLOR_BLACK, pos);
	int i;

	switch (keycode2) {
		case KB_ARROW_UP:
			if (stars[pos[0] - 1][pos[1]] == 0)
				pos[0] = row;
			else
				pos[0]--;
			break;
		case KB_ARROW_DOWN:
			if (stars[pos[0] + 1][pos[1]] == 0) {
				for (i = row; stars[i][pos[1]] != 0; i--)
					;
				pos[0] = i + 1;
			}
			else
				pos[0]++;
			break;
		case KB_ARROW_LEFT:
			do {
				if (pos[1] == 1) {
					pos[1] = col;
				}
				else {
					pos[1]--;
				}
			} while (stars[pos[0]][pos[1]] == 0);
			break;
		case KB_ARROW_RIGHT:
			do {
				if (pos[1] == col) {
					pos[1] = 1;
				}
				else {
					pos[1]++;
				}
			} while (stars[pos[0]][pos[1]] == 0);
			break;
	}

	show_down_state(mode, row, 1, CCT_KEYBOARD_EVENT, pos[0], pos[1]);
	paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, COLOR_WHITE);
}

/***************************************************************************
  函数名称：
  功    能：读取鼠标与键盘的操作
  输入参数：int pos[] : 存放行列的数组
			bool mode : mode为0表示无分割线；mode为1表示有分割线
			其余参数略
  返 回 值：int flag :  flag为0时表示退出本小题；
						flag为1时表示选中该星星；
						flag为2时表示放弃消除当前选中的星星(主要用于等待第二次点击)。
  说    明：
***************************************************************************/
int mouse_and_keybord(int& tool, int pos[], bool mode, int row, int col, int stars[][N + 2], char search[][N + 2])
{
	int X = 0, Y = 0;
	int ret = 10, maction;
	int keycode1, keycode2;
	int flag;
	int old_pos[2] = { 0 };
	int old_pos2[2] = { 0 };
	int old_state = 10;
	int state = 10;
	int old_ret;

	cct_enable_mouse();

	while (1) {
		old_ret = ret;
		ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		tool = ret;
		/* 鼠标操作 */
		if (ret == CCT_MOUSE_EVENT) {
			old_pos[0] = pos[0];
			old_pos[1] = pos[1];
			old_state = state;

			/* 根据当前的位置判断位置是否非法 */
			state = trans_tool(row, col, X, Y, mode, pos, stars);

			if (maction == MOUSE_ONLY_MOVED) {
				if (count_search_only(row, col, search) <= 1)
					init_search(search, old_pos[0], old_pos[1]);
				if (old_state != state && state == 0 || old_ret == CCT_KEYBOARD_EVENT) {
					paint_neibor(mode, search, stars, COLOR_BLACK, pos);
					show_down_state(mode, row, state, ret, pos[0], pos[1]);
					if (count_search_only(row, col, search) > 1) {
						init_search(search, old_pos[0], old_pos[1]);
						return 2;
					}
				}
				if (state == 1 && ((pos[0] != old_pos[0] || pos[1] != old_pos[1]) || (old_state == 0))) {
					show_down_state(mode, row, state, ret, pos[0], pos[1]);
					paint_neibor(mode, search, stars, STAR_COLOR, pos);
					paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, CHOSE_COLOR);
					if (count_search_only(row, col, search) > 1) {
						init_search(search, old_pos[0], old_pos[1]);
						return 2;
					}
				}
			}
			if (maction == MOUSE_LEFT_BUTTON_CLICK && state) {

				if ((old_pos[0] != pos[0] || old_pos[1] != pos[1]) &&
					(old_ret == CCT_KEYBOARD_EVENT || old_pos2[0] == 0)) {
					char temp[M + 2][N + 2];
					char str_pos[2];
					str_pos[0] = old_pos[0];
					str_pos[1] = old_pos[1];
					init_search(temp, old_pos[0], old_pos[1]);
					search_neighbor(str_pos, stars[old_pos[0]][old_pos[1]], temp, stars);
					paint_neibor(mode, temp, stars, STAR_COLOR, old_pos);
				}
				if ((old_pos[0] != pos[0] || old_pos[1] != pos[1])
					&& old_pos2[0] == 0 && count_search_only(row, col, search) > 1) {
					return -1;
				}
				return 1;
				break;
			}
			else if (maction == MOUSE_RIGHT_BUTTON_CLICK && state) {
				return 0;
				break;
			}
		}/* 键盘操作 */
		else if (ret == CCT_KEYBOARD_EVENT) {
			old_pos2[0] = pos[0];
			old_pos2[1] = pos[1];
			switch (keycode1) {
				case 224:
					switch (keycode2) {
						case KB_ARROW_UP:
						case KB_ARROW_DOWN:
						case KB_ARROW_LEFT:
						case KB_ARROW_RIGHT:
							if (count_search_only(row, col, search) <= 1)
								init_search(search, old_pos2[0], old_pos2[1]);
							keyboard_move(mode, keycode2, pos, stars, row, col, search);
							if (count_search_only(row, col, search) > 1) {
								init_search(search, old_pos2[0], old_pos2[1]);
								return 2;
							}
							break;
						default:
							break;
					}
					break;
				default:
					if (!keycode2)
						if (keycode1 == 'q' || keycode1 == 'Q') {
							return 0;
						}
						else if (keycode1 == '\r') {
							return 1;
						}
					break;
			}
		}
	}

	cct_disable_mouse();
	return flag;
}

/***************************************************************************
  函数名称：
  功    能：消除选中的所有星星
  输入参数：bool mode : 0表示无分割线；1表示有分割线
			int row : 数组的行数
			int col : 数组的列数
			char search[][N + 2] : 查找结果数组
  返 回 值：
  说    明：
***************************************************************************/
void paint_delete(bool mode, int row, int col, char search[][N + 2])
{
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			if (search[i][j] == '*') {
				paint_one_block(mode, 0, i, j, BG_COLOR, BG_COLOR);
				Sleep(5);
			}
}

/***************************************************************************
  函数名称：
  功    能：(反显/取消反显)连续相同的星星
  输入参数：bool mode : 0表示无分割线；1表示有分割线
			int fg_color : 前景色
			其余略
  返 回 值：
  说    明：
***************************************************************************/
void paint_neibor(bool mode, char search[][N + 2], int stars[][N + 2], int fg_color, int pos[])
{
	if (fg_color == CHOSE_COLOR)
		paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, CLICK_COLOR);
	int i, j;
	for (i = 1; i <= M; i++)
		for (j = 1; j <= N; j++)
			if (search[i][j] == '*') {
				if (fg_color != CHOSE_COLOR) {
					paint_one_block(mode, 1, i, j, stars[i][j] + 8, fg_color);
				}
				else {
					if (i == pos[0] && j == pos[1])
						continue;
					paint_one_block(mode, 1, i, j, stars[i][j] + 8, fg_color);
				}
				Sleep(1);
			}
}

/***************************************************************************
  函数名称：
  功    能：绘制单个星星的移动
  输入参数：int start_pos[] : 移动起始数组内行列
			int end_pos[] : 移动终止数组内行列
			bool mode : 0代表无分隔；1代表有分隔
			int color : 星星的背景色
  返 回 值：
  说    明：实现左移或下落
			1.下落的顺序从下往上
			2.左移的顺序从左向右，从下往上，一列一次移一列
***************************************************************************/
void paint_each_move(int start_pos[], int end_pos[], bool mode, int color)
{
	const int X_START = (start_pos[1] - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
	const int Y_START = 2 + FRAME_HIGHT + (start_pos[0] - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);
	const int X_END = (end_pos[1] - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
	const int Y_END = 2 + FRAME_HIGHT + (end_pos[0] - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);

	int x, y;
	/* 下移 */
	if (X_START == X_END) {
		for (y = Y_START; y < Y_END; y++) {
			paint_one_block_xy(X_START, y, mode);
			paint_one_star_xy(X_START, y + 1, color, STAR_COLOR);
			Sleep(1);
		}
	}  /* 左移 */
	else if (Y_START == Y_END) {
		for (x = X_START; x > X_END; x--) {
			paint_one_block_xy(x, Y_START, mode);
			paint_one_star_xy(x - 1, Y_START, color, STAR_COLOR);
			if (x == X_END + 1 || x % 2)
				Sleep(1);
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：每一步的消除，即从选中星星到下落/左移的一次操作的全过程
  输入参数：
  返 回 值：返回0表示结束本关；返回1表示继续进行下一次消除
  说    明：该函数进行了pos、score、search、stars的更新
***************************************************************************/
int each_step(bool mode, int& tool, int& score, int row, int col, int stars[][N + 2], char search[][N + 2], int pos[])
{
	int count_remove;
	int score_new;
	int flag1 = 0, flag2 = 0;

	while (1) {
		score_new = 0;
		count_remove = 0;
		int old_pos[2];

		if (flag2 == -1) {
			flag1 = 1;
		}
		else if (flag2 != -1)
			flag1 = mouse_and_keybord(tool, pos, mode, row, col, stars, search);
		if (flag1 == 1) {
			/* 查找连续相同值并标识 */
			char pos_str[2];
			pos_str[0] = char(pos[0]);
			pos_str[1] = char(pos[1]);
			count_remove = count_neighbor(pos_str, stars[pos[0]][pos[1]], search, stars);
			if (count_remove == 1) {
				show_down_state(mode, row, 0, 5, pos[0], pos[1]);
				continue;
			}
			else {
				paint_neibor(mode, search, stars, CHOSE_COLOR, pos);
				show_down_state(mode, row, 2, 1, pos[0], pos[1]);
			}
		}
		else if (flag1 == 0) {
			show_down_state(mode, row, 0, -1, pos[0], pos[1]);
			return 0;
		}
		else if (flag1 == 2) {
			continue;
		}

		/* 再次等待点击确认消除 */
		old_pos[0] = pos[0];
		old_pos[1] = pos[1];
		flag2 = mouse_and_keybord(tool, pos, mode, row, col, stars, search);
		if (flag2 == 0) {
			show_down_state(mode, row, 0, -1, pos[0], pos[1]);
			return 0;
		}
		else if (flag2 == 1) {
			score_new = count_remove * 5 * count_remove;
			score += score_new;
			show_up_state(score_new, score, 0);
			do_remove(stars, search);
			paint_delete(mode, row, col, search);
			show_down_state(mode, row, 0, 6, pos[0], pos[1]);
			return 1;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：等待某个键/鼠操作继续
  输入参数：int state : 表示不同的继续指令
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_continue(int state)
{
	int ret;
	int X, Y;
	int maction;
	int keycode1;
	int keycode2;

	cct_enable_mouse();

	switch (state) {
		case 1:
			while (1) {
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (ret == CCT_KEYBOARD_EVENT && !keycode2 && keycode1 == '\r')
					break;
			}
			break;
		case 2:
			while (1) {
				ret = cct_read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
				if (ret == CCT_MOUSE_EVENT && maction == MOUSE_LEFT_BUTTON_CLICK)
					break;
				else if (ret == CCT_KEYBOARD_EVENT && !keycode2 && (keycode1 == 'c' || keycode1 == 'C'))
					break;
			}
			break;
		default:
			break;
	}

	cct_disable_mouse();
}

/***************************************************************************
  函数名称：
  功    能：模式D的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_D(int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* 绘制初始界面 */
	show_frame(mode, row, col);
	show_down_state(mode, row, 0, 3, 0, 0);
	paint_init_stars(mode, row, col, stars);

	/* 第一次点击 */
	int pos[2], flag, tool;
	char search[M + 2][N + 2];
	show_init_pos(mode, row, stars, pos, 1);
	flag = mouse_and_keybord(tool, pos, mode, row, col, stars, search);
	if (flag == 1) {
		paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, CLICK_COLOR);
		show_down_state(mode, row, 0, 4, pos[0], pos[1]);
		show_down_state(mode, row, 0, -2, pos[0], pos[1]);
	}
	else if (flag == 0) {
		show_down_state(mode, row, 0, -1, pos[0], pos[1]);
	}

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/***************************************************************************
  函数名称：
  功    能：模式E的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_E(int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* 绘制初始界面 */
	show_frame(mode, row, col);
	show_down_state(mode, row, 0, 3, 0, 0);
	paint_init_stars(mode, row, col, stars);

	/* 第一次点击 */
	int pos[2], flag, tool;
	char search[M + 2][N + 2];
	show_init_pos(mode, row, stars, pos, 1);
	flag = mouse_and_keybord(tool, pos, mode, row, col, stars, search);
	if (flag == 1) {
		paint_one_block(mode, 1, pos[0], pos[1], stars[pos[0]][pos[1]] + 8, CLICK_COLOR);
		show_down_state(mode, row, 0, 4, pos[0], pos[1]);
		show_down_state(mode, row, 0, -2, pos[0], pos[1]);
	}
	else if (flag == 0) {
		show_down_state(mode, row, 0, -1, pos[0], pos[1]);
	}

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/***************************************************************************
  函数名称：
  功    能：模式F的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_F(int& score, int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* 绘制初始界面 */
	show_frame(mode, row, col);
	show_down_state(mode, row, 0, 3, 0, 0);
	paint_init_stars(mode, row, col, stars);

	char search[M + 2][N + 2];
	int flag;
	int tool;
	int pos[2];
	show_init_pos(mode, row, stars, pos, 1);

	flag = each_step(mode, tool, score, row, col, stars, search, pos);

	if (flag) {
		/* 等待点击确认下落 */
		wait_for_continue(1);
		do_move(row, col, stars, true, mode);

		/* 进行下一次合成 */
		show_down_state(mode, row, 0, 7, pos[0], pos[1]);
		wait_for_continue(2);
	}
	show_down_state(mode, row, 0, -1, pos[0], pos[1]);

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/***************************************************************************
  函数名称：
  功    能：模式G的集成函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void mode_G(int& score, int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	while (1) {
		/* 绘制初始界面 */
		cct_cls();
		int i, j;
		for (i = 1; i <= row; i++)
			for (j = 1; j <= col; j++)
				stars[i][j] = rand() % RAND + 1;
		show_frame(mode, row, col);
		show_down_state(mode, row, 0, 3, 0, 0);
		paint_init_stars(mode, row, col, stars);
		score = 0;

		int score_prize;
		char search[M + 2][N + 2];
		int pos[2];
		int tool = 1;
		/* 每一关 */
		while (1) {
			score_prize = 0;

			/* 判断游戏是否结束 */
			int left;
			left = eliminableStars_left_or_not(row, col, stars);
			if (left >= 0) {
				score_prize = (10 - left) * (left < 10) * 180;
				score += score_prize;
				show_up_state(0, score, score_prize);
				show_down_state(mode, row, 0, 8, 0, 0);
				cout << left << "个不可消除项，本关结束！";
				cct_setcolor();
				break;
			}

			/* 进行每一步消除 */
			int flag;
			show_init_pos(mode, row, stars, pos, tool);

			flag = each_step(mode, tool, score, row, col, stars, search, pos);

			if (flag == 0) {
				show_down_state(mode, row, 0, -1, pos[0], pos[1]);
				return;
			}

			/* 进行下落、左移等 */
			do_move(row, col, stars, true, mode);
			show_down_state(mode, row, 0, 2, pos[0], pos[1]);

			init_search(search, pos[0], pos[1]);
		}
		cct_disable_mouse();
		cout << "回车继续下一关              ";
		while (_getch() != '\r')
			;
	}

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}