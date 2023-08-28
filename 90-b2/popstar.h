/* 2152153 ������ �ƿ� */
#pragma once

/* ͷ�ļ� */
#include <iostream>
#include <conio.h>
#include <time.h>
#include <windows.h>
#include <iomanip>
#include "cmd_console_tools.h"
using namespace std;

const int M = 10, N = 10;
const int SPEED = 2;
const int RAND = 5;

/* �������ǵĴ�С�ͱ߿�Ĵ�ϸ */
const int BLOCK_WIDTH = 6, BLOCK_HIGHT = 3;
const int FRAME_WIDTH = 2, FRAME_HIGHT = 1;

/* ����߿�ɫ�����ǵ�״̬ɫ */
const int BG_COLOR = COLOR_HWHITE, FRAME_COLOR = COLOR_BLACK;
const int STAR_COLOR = COLOR_BLACK, CHOSE_COLOR = COLOR_WHITE, CLICK_COLOR = COLOR_HWHITE;

/* ���˵���� */
void mode_A(int row, int col, int stars[][N + 2]);
void mode_B(int& score, int row, int col, int stars[][N + 2]);
void mode_C(int& score, int row, int col, int stars[][N + 2]);
void mode_D(int row, int col, int stars[][N + 2], bool mode);
void mode_E(int row, int col, int stars[][N + 2], bool mode);
void mode_F(int& score, int row, int col, int stars[][N + 2], bool mode);
void mode_G(int& score, int row, int col, int stars[][N + 2], bool mode);

/* �˵���A-C���鷽ʽʵ�ֵĸ����� */
int input_order(int row, int col, char order[], int stars[][N + 2], char search[][N + 2]);
void print_search_array(int row, int col, char search[M + 2][N + 2]);
void print_stars_array(int print_mode, int row, int col, int stars[][N + 2], char search[][N + 2]);

/* cmdͼ�ν��淽ʽʵ�ֵĸ����� */
void show_frame(bool mode, int row, int col);
void show_down_state(bool mode, int row, int state, int tool, int i, int j);
void paint_one_star_xy(int X, int Y, const int bg_color, const int fg_color);
void paint_one_block_xy(int X, int Y, bool mode);
void paint_one_block(bool mode, bool paint_star_or_not, int i, int j, const int bg_color, const int fg_color);
void paint_neibor(bool mode, char search[][N + 2], int stars[][N + 2], int fg_color, int pos[]);
void paint_each_move(int start_pos[], int end_pos[], bool mode, int color);

/* �ڲ�����/ͼ�η�ʽ���õĹ������� */
void init_search(char search[][N + 2], int X, int Y);
int count_search_only(int row, int col, char search[][N + 2]);
void search_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2]);
int count_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2]);
void do_move(int row, int col, int stars[][N + 2], bool flag, bool mode);
void do_remove(int stars[][N + 2], char search[][N + 2]);
int eliminableStars_left_or_not(int row, int col, int stars[][N + 2]);

/* ���ߺ��� */
void to_be_continued(const char* prompt);