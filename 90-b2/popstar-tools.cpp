/* 2152153 ������ �ƿ� */
#include "popstar.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ�����ָ������λ�ü���Χ��ͬ��
  ���������char pos[] : ָ��������λ��
			int value : ָ������λ�õ�ֵ
			char search[][N + 2] : ���ҽ������
			int stars[][N + 2] : ��ǰ��������
  �� �� ֵ��
  ˵    ����1.pos�е������Ѿ���ָ��ת���ɿ���ֱ�Ӷ�Ӧ�������е�����
			2.�ú������ҽ������search����
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
  �������ƣ�
  ��    �ܣ�����ָ������λ�ü���Χ��ͬ��ļ��ɺ���
  ���������
  �� �� ֵ��int count : ������ֵͬ����
  ˵    ����1.�ú����ڻ����search����
			2.ʹ��ʱ���øú������ɣ��ɸ���search���鲢����������ֵͬ����
***************************************************************************/
int count_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2])
{
	init_search(search, pos[0], pos[1]);
	search_neighbor(pos, value, search, stars);

	/* ����������ֵͬ���� */
	int count = 0, i, j;
	for (i = 0; i < M + 2; i++)
		for (j = 0; j < N + 2; j++)
			if (search[i][j] == '*')
				count++;
	return count;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ִ��stars�����е���������
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�ִ��stars�����е��ƶ�����(�������������)
  ���������int row
			int col
			int stars[][N + 2]
			bool flag : �Ƿ���Ҫ��������ͼ��
			bool mode : 0�����޷ָ���1�����зָ�
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void do_move(int row, int col, int stars[][N + 2], bool flag, bool mode)
{
	int i, j, k, t;

	/* �ȼ������ */
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

	/* �������� */
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
  �������ƣ�
  ��    �ܣ��ж��Ƿ�ʣ���������
  ���������
  �� �� ֵ��-1�����п�������ʣ�ࣻ���޿�������ʣ�࣬�򷵻�ʣ��������
  ˵    ����
***************************************************************************/
int eliminableStars_left_or_not(int row, int col, int stars[][N + 2])
{
	int i, j, m, n;
	int count_total = 0, count_neibor = 0;
	char pos[3], search[M + 2][N + 2];

	for (j = 1; stars[row][j] != 0; j++) {
		for (i = row; stars[i][j] != 0; i--) {
			/* ��ʼ��search���� */
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
  �������ƣ�
  ��    �ܣ��ȴ��س�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continued(const char* prompt)
{
	cout << endl << prompt;

	/* ���Գ��س�������������� */
	while (_getch() != '\r')
		;

	cout << endl;
	return;
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʼ��search����
  ���������char search[][N + 2]
			int X : ѡ�еĵ����
			int Y : ѡ�еĵ����
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�ͳ��search�����еı�� * �ĸ���
  ���������
  �� �� ֵ��
  ˵    ����
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