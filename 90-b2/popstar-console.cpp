/* 2152153 ������ �ƿ� */
#include "popstar.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ�����߿�
  ���������bool mode : 0�����޷ָ��ߣ�1�����зָ���
			int row : ���ǵ���
			int col : ���ǵ���
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void show_frame(bool mode, int row, int col)
{
	/* ������Ļ��С */
	const int cols = BLOCK_WIDTH * col + 3 + FRAME_WIDTH * (2 + mode * (col - 1));
	const int lines = BLOCK_HIGHT * row + 6 + FRAME_HIGHT * (2 + mode * (row - 1));
	cct_setconsoleborder(cols, lines, cols, lines);

	/* ��ӡ��һ�� */
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

	/* ��ӡ������ */
	int word = 0;
	for (i = 1; i <= lines - 6; i++) {
		/* ��ӡ��ʾ�е���ĸ */
		if ((i + mode * FRAME_HIGHT) % (BLOCK_HIGHT + mode * FRAME_HIGHT) == 0)
			cout << char('A' + word++) << ' ';
		else
			cout << "  ";

		/* ��ӡ�߿�͵�ɫ */
		cct_setcolor(BG_COLOR, FRAME_COLOR);
		switch (mode) {
			case 0:
				if (i == 1) {
					cout << "�X";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH / 2; j++) {
						cout << "�T";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "�[";
				}
				else if (i == lines - 6) {
					cout << "�^";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH / 2; j++) {
						cout << "�T";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "�a";
				}
				else {
					cout << "�U";
					Sleep(SPEED);
					for (j = 0; j < col * BLOCK_WIDTH; j++) {
						cout << " ";
						if (j % BLOCK_WIDTH == 0)
							Sleep(SPEED);
					}
					cout << "�U";
				}
				break;
			case 1:
				if (i == 1) {
					cout << "�X";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						(j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0) ? (cout << "�j") : (cout << "�T");
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "�[";
				}
				else if (i == lines - 6) {
					cout << "�^";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						(j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0) ? (cout << "�m") : (cout << "�T");
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "�a";
				}
				else if ((i - 1) % (BLOCK_HIGHT + FRAME_HIGHT)) {
					cout << "�U";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						if (j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0)
							cout << "�U";
						else
							cout << "  ";
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "�U";
				}
				else {
					cout << "�d";
					Sleep(SPEED);
					for (j = 1; j <= col * (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) - FRAME_WIDTH / 2; j++) {
						if (j % (BLOCK_WIDTH / 2 + FRAME_WIDTH / 2) == 0)
							cout << "�p";
						else
							cout << "�T";
						if (j % (BLOCK_HIGHT + FRAME_WIDTH) == 0)
							Sleep(SPEED);
					}
					cout << "�g";
				}
				break;
		}
		cct_setcolor();

		cout << endl;
	}

	cct_gotoxy(0, 0);
	cout << "��Ļ��ǰ����Ϊ��" << lines << "��" << cols << "��";
	cct_gotoxy(0, lines - 4);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����Ϸ��ʼ�������������ɫ��
  ���������
  �� �� ֵ��
  ˵    ����modeΪ0��ʾ�޷ָ��ߣ�modeΪ1��ʾ�зָ���
***************************************************************************/
void paint_init_stars(bool mode, int row, int col, int stars[][N + 2])
{
	int i, j;
	for (i = 1; i <= row; i++)
		for (j = 1; j <= col; j++)
			paint_one_block(mode, 1, i, j, stars[i][j] + 8, COLOR_BLACK);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ�����Ϸ�״̬��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void show_up_state(int score_new, int score_total, int score_prize)
{
	cct_gotoxy(0, 0);
	if (score_new > 0)
		cout << "���ε÷�:" << score_new;
	else
		cout << "�����÷�:" << score_prize;
	cout << " �ܷ�:" << score_total << "          ";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ�·�״̬��
  ���������bool mode : 0�����޷ָ��ߣ�1�����зָ���
			int row : �������������
			int state : ����������ݲ���1
			int tool : ����������ݲ���2
			int i : ��ǰ��������
			int j : ��ǰ��������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void show_down_state(bool mode, int row, int state, int tool, int i, int j)
{
	int Y;
	Y = BLOCK_HIGHT * row + 6 + FRAME_HIGHT * (2 + mode * (row - 1)) - 4;
	cct_gotoxy(0, Y);
	if (tool == CCT_MOUSE_EVENT) {
		switch (state) {
			case 0:
				cout << "[��ǰ���] λ�÷Ƿ�";
				cout << setw(60) << ' ';
				break;
			case 1:
				cout << "[��ǰ���] " << char(i + 'A' - 1) << "��" << char(j + '0' - 1) << "��";
				cout << setw(50) << ' ';
				break;
			case 2:
				cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
				cout << setw(30) << ' ';
				break;
			default:
				break;
		}
	}
	else if (tool == CCT_KEYBOARD_EVENT) {
		switch (state) {
			case 1:
				cout << "[��ǰ����] " << char(i + 'A' - 1) << "��" << char(j + '0' - 1) << "��";
				cout << setw(50) << ' ';
				break;
			case 2:
				cout << "��ͷ��/����ƶ�ȡ����ǰѡ�񣬻س���/��������ϳ�";
				cout << setw(30) << ' ';
				break;
			default:
				break;
		}
	}
	else if (tool == 2) {
		cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����" << setw(30) << ' ';
	}
	else if (tool == 3) {
		cout << "��ͷ��/����ƶ����س���/�������ѡ�񲢽���" << setw(30) << ' ';
	}
	else if (tool == 4) {
		cout << "ѡ����" << char(i + 'A' - 1) << "��" << char(j + '0' - 1) << "��" << setw(50) << ' ';
	}
	else if (tool == 5) {
		cct_setcolor(0, COLOR_HYELLOW);
		cout << "��Χ����ֵͬ��";
		cct_setcolor();
		cout << "��ͷ��/����ƶ����س���/�������ѡ��Q/�����Ҽ�����" << setw(30) << ' ';
	}
	else if (tool == 6) {
		cout << "�ϳ���ɣ��س���/�����������" << setw(30) << ' ';
	}
	else if (tool == 7) {
		cct_setcolor(0, COLOR_HYELLOW);
		cout << "���κϳɽ�������C/�������������һ�εĺϳ�";
		cct_setcolor();
	}
	else if (tool == -1)
		cout << "                                           ";
	else if (tool == 8) {
		cct_setcolor(COLOR_BLACK, COLOR_HYELLOW);
		cout << "ʣ��";
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����Ƶ������ǻ���������������
  ���������bool mode : 0��ʾ�޷ָ��ߣ�1��ʾ�зָ���
			bool paint_star_or_not : 1��ʾ�������ǣ�0��ʾ��������
			int i : ���������е���
			int j : ���������е���
			const int bg_color : ����ɫ
			const int fg_color : ǰ��ɫ
  �� �� ֵ��
  ˵    �����ú���ֱ�Ӵ������������е������м����ڶ�Ӧλ�ô�ӡ
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
  �������ƣ�
  ��    �ܣ����մ���xy���껭һ������ɫ��
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void paint_one_star_xy(int X, int Y, const int bg_color, const int fg_color)
{
	cct_setcolor(bg_color, fg_color);
	cct_gotoxy(X, Y);
	cout << "�X�T�[";
	cct_gotoxy(X, Y + 1);
	cout << "�U��U";
	cct_gotoxy(X, Y + 2);
	cout << "�^�T�a";
	cct_setcolor();
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ����մ���xy����������������ɫ��
  ���������int X : ����ɫ�����Ͻǵ�x����
			int Y : ����ɫ�����Ͻǵ�y����
			bool mode : 0�����޷ָ���1�����зָ�
  �� �� ֵ��
  ˵    ����
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
						cout << "�U";
					}
					else if ((j - 2) % (BLOCK_HIGHT + FRAME_HIGHT) == 0)
						cout << "�T";
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
  �������ƣ�
  ��    �ܣ����塰��ꡱ����ʼλ�ò���ʾ
  ���������bool mode : modeΪ0��ʾ�޷ָ��ߣ�modeΪ1��ʾ�зָ���
			int row : ���ǵ���
			int stars[][N + 2] : ��ǰ��������
			int pos[] : ��ŵ�ǰѡ��λ�õ�����
  �� �� ֵ��
  ˵    ����ÿ���������������������Ͻǵ�������Ϊ�ƶ�����ʼλ��
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
  �������ƣ�
  ��    �ܣ����ж�����λ���Ƿ�Ϸ���
			�ڽ�����x��y�����Ӧ��ת��Ϊ��������У���ŵ�pos[]��
  ���������
  �� �� ֵ��bool state : 0��ʾλ�÷Ƿ���1��ʾλ�úϷ�
  ˵    ����λ�úϷ�ʱ�Ż�ı�pos[]
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
  �������ƣ�
  ��    �ܣ������ͷ�������ƶ���ӳ����Ϸ������
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ���ȡ�������̵Ĳ���
  ���������int pos[] : ������е�����
			bool mode : modeΪ0��ʾ�޷ָ��ߣ�modeΪ1��ʾ�зָ���
			���������
  �� �� ֵ��int flag :  flagΪ0ʱ��ʾ�˳���С�⣻
						flagΪ1ʱ��ʾѡ�и����ǣ�
						flagΪ2ʱ��ʾ����������ǰѡ�е�����(��Ҫ���ڵȴ��ڶ��ε��)��
  ˵    ����
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
		/* ������ */
		if (ret == CCT_MOUSE_EVENT) {
			old_pos[0] = pos[0];
			old_pos[1] = pos[1];
			old_state = state;

			/* ���ݵ�ǰ��λ���ж�λ���Ƿ�Ƿ� */
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
		}/* ���̲��� */
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
  �������ƣ�
  ��    �ܣ�����ѡ�е���������
  ���������bool mode : 0��ʾ�޷ָ��ߣ�1��ʾ�зָ���
			int row : ���������
			int col : ���������
			char search[][N + 2] : ���ҽ������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�(����/ȡ������)������ͬ������
  ���������bool mode : 0��ʾ�޷ָ��ߣ�1��ʾ�зָ���
			int fg_color : ǰ��ɫ
			������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ����Ƶ������ǵ��ƶ�
  ���������int start_pos[] : �ƶ���ʼ����������
			int end_pos[] : �ƶ���ֹ����������
			bool mode : 0�����޷ָ���1�����зָ�
			int color : ���ǵı���ɫ
  �� �� ֵ��
  ˵    ����ʵ�����ƻ�����
			1.�����˳���������
			2.���Ƶ�˳��������ң��������ϣ�һ��һ����һ��
***************************************************************************/
void paint_each_move(int start_pos[], int end_pos[], bool mode, int color)
{
	const int X_START = (start_pos[1] - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
	const int Y_START = 2 + FRAME_HIGHT + (start_pos[0] - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);
	const int X_END = (end_pos[1] - 1) * (BLOCK_WIDTH + mode * FRAME_WIDTH) + 2 + FRAME_WIDTH;
	const int Y_END = 2 + FRAME_HIGHT + (end_pos[0] - 1) * (BLOCK_HIGHT + mode * FRAME_HIGHT);

	int x, y;
	/* ���� */
	if (X_START == X_END) {
		for (y = Y_START; y < Y_END; y++) {
			paint_one_block_xy(X_START, y, mode);
			paint_one_star_xy(X_START, y + 1, color, STAR_COLOR);
			Sleep(1);
		}
	}  /* ���� */
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
  �������ƣ�
  ��    �ܣ�ÿһ��������������ѡ�����ǵ�����/���Ƶ�һ�β�����ȫ����
  ���������
  �� �� ֵ������0��ʾ�������أ�����1��ʾ����������һ������
  ˵    �����ú���������pos��score��search��stars�ĸ���
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
			/* ����������ֵͬ����ʶ */
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

		/* �ٴεȴ����ȷ������ */
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
  �������ƣ�
  ��    �ܣ��ȴ�ĳ����/���������
  ���������int state : ��ʾ��ͬ�ļ���ָ��
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�ģʽD�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_D(int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* ���Ƴ�ʼ���� */
	show_frame(mode, row, col);
	show_down_state(mode, row, 0, 3, 0, 0);
	paint_init_stars(mode, row, col, stars);

	/* ��һ�ε�� */
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
  �������ƣ�
  ��    �ܣ�ģʽE�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_E(int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* ���Ƴ�ʼ���� */
	show_frame(mode, row, col);
	show_down_state(mode, row, 0, 3, 0, 0);
	paint_init_stars(mode, row, col, stars);

	/* ��һ�ε�� */
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
  �������ƣ�
  ��    �ܣ�ģʽF�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_F(int& score, int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	/* ���Ƴ�ʼ���� */
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
		/* �ȴ����ȷ������ */
		wait_for_continue(1);
		do_move(row, col, stars, true, mode);

		/* ������һ�κϳ� */
		show_down_state(mode, row, 0, 7, pos[0], pos[1]);
		wait_for_continue(2);
	}
	show_down_state(mode, row, 0, -1, pos[0], pos[1]);

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ģʽG�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_G(int& score, int row, int col, int stars[][N + 2], bool mode)
{
	cct_setcursor(CURSOR_INVISIBLE);

	while (1) {
		/* ���Ƴ�ʼ���� */
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
		/* ÿһ�� */
		while (1) {
			score_prize = 0;

			/* �ж���Ϸ�Ƿ���� */
			int left;
			left = eliminableStars_left_or_not(row, col, stars);
			if (left >= 0) {
				score_prize = (10 - left) * (left < 10) * 180;
				score += score_prize;
				show_up_state(0, score, score_prize);
				show_down_state(mode, row, 0, 8, 0, 0);
				cout << left << "��������������ؽ�����";
				cct_setcolor();
				break;
			}

			/* ����ÿһ������ */
			int flag;
			show_init_pos(mode, row, stars, pos, tool);

			flag = each_step(mode, tool, score, row, col, stars, search, pos);

			if (flag == 0) {
				show_down_state(mode, row, 0, -1, pos[0], pos[1]);
				return;
			}

			/* �������䡢���Ƶ� */
			do_move(row, col, stars, true, mode);
			show_down_state(mode, row, 0, 2, pos[0], pos[1]);

			init_search(search, pos[0], pos[1]);
		}
		cct_disable_mouse();
		cout << "�س�������һ��              ";
		while (_getch() != '\r')
			;
	}

	cct_setcursor(CURSOR_VISIBLE_NORMAL);
}