/* 2152153 ������ �ƿ� */
#include "popstar.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ������������ָ��
  ���������int row : ����
			int col : ����
			char order[] : ���ָ�������
			int stars[][N + 2] : ��������
			char search[][N + 2] : ��ǲ��ҵ�����
  �� �� ֵ��int count : ������������
  ˵    �����ж������ʽ�Ƿ���ȷ���Լ�����λ���Ƿ�Ϊ0����Χ�Ƿ�������ֵͬ
***************************************************************************/
int input_order(int row, int col, char order[], int stars[][N + 2], char search[][N + 2])
{
	const int STR_MAX = 5;
	int value;

	while (1) {
		cout << endl << "������ĸ+������ʽ[����c2]����������꣺";

		cin >> order;

		order[0] += ('A' - 'a') * ('a' <= order[0] && order[0] <= 'z');

		/* ���ж������ʽ�Ƿ���ȷ */
		if ('A' <= order[0] && order[0] <= ('A' + row - 1)
			&& '0' <= order[1] && order[1] <= ('0' + col - 1)
			&& order[2] == '\0') {
			cout << "����Ϊ" << order[0] << "��" << order[1] << "��" << endl;
		}
		else {
			cout << "�����������������" << endl;
			continue;
		}

		/* ���ж��Ƿ�Ϸ� */
		if ((value = stars[order[0] - 'A' + 1][order[1] - '0' + 1]) != 0) {
			/* ��order����Ϊ����ֵ */
			order[0] = order[0] - 'A' + 1;
			order[1] = order[1] - '0' + 1;
			//(--����--)cout << "(" << (int)order[0] << "," << (int)order[1] << ")" << endl;

			/* ����������ֵͬ */
			int count;
			count = count_neighbor(order, value, search, stars);

			/* �ж� */
			if (count == 1)
				cout << "����ľ�������λ�ô���������ֵͬ������������" << endl;
			else {
				cout << endl << "���ҽ�����飺" << endl;
				print_search_array(row, col, search);
				cout << endl << "��ǰ���飨��ͬɫ��ʶ����" << endl;
				print_stars_array(0, row, col, stars, search);
				return count;
			}
		}
		else
			cout << "����ľ�������λ��Ϊ0���Ƿ�λ�ã�������������" << endl;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ��������
  ���������int print_mode : ��ӡģʽ
			int row : ����
			int col : ����
			char order[] : ���ָ�������
			int stars[][N + 2] : ��ǰ��������
			char search[][N + 2] : ��ǲ��ҵ�����
  �� �� ֵ��
  ˵    ����print_modeΪ����ʱ��ʶ����Ϊ0��λ�ã�Ϊż��ʱ��ʶ��ǰ��ͬ����ֵ
***************************************************************************/
void print_stars_array(int print_mode, int row, int col, int stars[][N + 2], char search[][N + 2])
{
	const int WIDTH = 3;
	int i, j;
	int X, Y;

	/* ��ӡ�߿��һ�� */
	cout << setw(WIDTH) << '|';
	for (i = 0; i < col; i++)
		cout << setw(WIDTH) << i;
	cout << endl;

	/* ��ӡ�߿�ڶ��� */
	cout << setfill('-') << setw(WIDTH) << '+';
	cout << setw(WIDTH * col) << '-' << endl;
	cout << setfill(' ');

	/* ��ӡ������ */
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
  �������ƣ�
  ��    �ܣ���ӡ���ҽ������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void print_search_array(int row, int col, char search[M + 2][N + 2])
{
	const int WIDTH = 3;
	int i, j;

	/* ��ӡ�߿��һ�� */
	cout << setw(WIDTH) << '|';
	for (i = 0; i < col; i++)
		cout << setw(WIDTH) << i;
	cout << endl;

	/* ��ӡ�߿�ڶ��� */
	cout << setfill('-') << setw(WIDTH) << '+';
	cout << setw(WIDTH * col) << '-' << endl;
	cout << setfill(' ');

	/* ��ӡ������ */
	for (i = 1; i <= row; i++) {
		cout << (char)('A' + i - 1) << setw(WIDTH - 1) << '|';
		for (j = 1; j <= col; j++) {
			cout << setw(WIDTH) << search[i][j];
		}
		cout << endl;
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ȷ���Ƿ�������ʾ��
  ���������
  �� �� ֵ��
  ˵    �������˵�A-Cʹ��
***************************************************************************/
char remove_or_not(char pos[])
{
	char remove_flag;
	cout << endl << "��ȷ���Ƿ��" << char(pos[0] + 'A' - 1) << char(pos[1] + '0' - 1) << "����Χ����ֵͬ����(Y/N/Q)��";
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
  �������ƣ�
  ��    �ܣ�ģʽA�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_A(int row, int col, int stars[][N + 2])
{
	char search[M + 2][N + 2];
	char pos[200];

	/* ��ӡ��ǰ���� */
	cout << endl << "��ǰ���飺" << endl;
	print_stars_array(1, row, col, stars, search);

	/* ���벢����������� */
	input_order(row, col, pos, stars, search);
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ģʽB�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void mode_B(int& score, int row, int col, int stars[][N + 2])
{
	char search[M + 2][N + 2];

	while (1) {
		char pos[200];
		int count_remove;
		int score_new = 0;

		/* ��ӡ��ǰ���� */
		cout << endl << "��ǰ���飺" << endl;
		print_stars_array(1, row, col, stars, search);

		/* ���벢����������� */
		count_remove = input_order(row, col, pos, stars, search);

		/* �ж��Ƿ����� */
		switch (remove_or_not(pos)) {
			case 'Q':
				return;
				break;
			case 'N':
				cout << endl << "��������ѡ�����꡿" << endl;
				break;
			case 'Y':
				/* ���� */
				do_remove(stars, search);
				cout << endl << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
				print_stars_array(0, row, col, stars, search);

				/* ��¼�÷� */
				score_new = count_remove * count_remove * 5;
				score += score_new;
				cout << endl << "���ε÷֣�" << score_new << " �ܵ÷֣�" << score << endl;

				/* ���� */
				to_be_continued("���س������������������...");
				do_move(row, col, stars, 0, 0);
				cout << endl << "���������飺" << endl;
				print_stars_array(1, row, col, stars, search);

				return;
				break;
			default:
				break;
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ģʽC�ļ��ɺ���
  ���������
  �� �� ֵ��
  ˵    ����
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

		/* ��ӡ��ǰ���� */
		cout << endl << "��ǰ���飺" << endl;
		print_stars_array(1, row, col, stars, search);

		/* �ж���Ϸ�Ƿ���� */
		left = eliminableStars_left_or_not(row, col, stars);
		if (left >= 0) {
			score_prize = (10 - left) * (left < 10) * 180;
			score += score_prize;
			cct_setcolor(COLOR_HYELLOW, COLOR_RED);
			cout << endl << "ʣ��" << left << "��������������ؽ�����" << endl;
			cout << "�����÷֣�" << score_prize << " �����ܵ÷֣�" << score << endl;
			cct_setcolor();
			return;
		}

		/* ���벢����������� */
		count_remove = input_order(row, col, pos, stars, search);

		/* �ж��Ƿ����� */
		switch (remove_or_not(pos)) {
			case 'Q':
				return;
				break;
			case 'N':
				cout << endl << "��������ѡ�����꡿" << endl;
				break;
			case 'Y':
				/* ���� */
				do_remove(stars, search);
				cout << endl << "��ֵͬ�鲢�������(��ͬɫ��ʶ)��" << endl;
				print_stars_array(0, row, col, stars, search);

				/* ��¼�÷� */
				score_new = count_remove * count_remove * 5;
				score += score_new;
				cout << endl << "���ε÷֣�" << score_new << " �ܵ÷֣�" << score << endl;

				/* ���� */
				to_be_continued("���س������������������...");
				do_move(row, col, stars, 0, 0);
				cout << endl << "���������飺" << endl;
				print_stars_array(1, row, col, stars, search);

				cout << endl;
				to_be_continued("�����������������س���������һ�ε�����...");
				break;
			default:
				break;
		}
	}
}