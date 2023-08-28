/* 2152153 ������ �ƿ� */
#include "popstar.h"

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ӡ�˵�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void show_menu()
{
	cct_cls();
	cout << "--------------------------------------------" << endl;
	cout << "A.�������ҳ����������ʶ" << endl;
	cout << "B.���������һ���������ֲ�����ʾ��" << endl;
	cout << "C.���������һ�أ��ֲ�����ʾ��" << endl;
	cout << "D.αͼ�ν����������ѡ��һ��ɫ�飨�޷ָ��ߣ�" << endl;
	cout << "E.αͼ�ν����������ѡ��һ��ɫ�飨�зָ��ߣ�" << endl;
	cout << "F.αͼ�ν������һ���������ֲ��裩" << endl;
	cout << "G.αͼ�ν���������" << endl;
	cout << "Q.�˳�" << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[��ѡ��: ] ";
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�ѡ��˵�ģʽ
  ���������
  �� �� ֵ��
  ˵    ����
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
  �������ƣ�
  ��    �ܣ�ѡ������������������ʼ����������
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void init_para(int* row, int* col, int stars[][N + 2])
{
	while (1) {
		cout << "����������(8-10)��" << endl;
		cin >> *row;
		if (8 <= *row && *row <= 10 && cin.good())
			break;
		else {
			cin.clear();
			cin.ignore(65536, '\n');
		}
	}

	while (1) {
		cout << "����������(8-10)��" << endl;
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
  �������ƣ�
  ��    �ܣ��ȴ�����end���Խ�������
  ���������
  �� �� ֵ��
  ˵    ����������end������ĸʱ�Ż���������޴�Сд
***************************************************************************/
void wait_for_end()
{
	const int STR_N = 200;

	while (1) {
		cout << endl << "��С�������������End����...";
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