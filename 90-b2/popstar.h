/* 2152153 李欣晨 计科 */
#pragma once

/* 头文件 */
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

/* 定义星星的大小和边框的粗细 */
const int BLOCK_WIDTH = 6, BLOCK_HIGHT = 3;
const int FRAME_WIDTH = 2, FRAME_HIGHT = 1;

/* 定义边框色与星星的状态色 */
const int BG_COLOR = COLOR_HWHITE, FRAME_COLOR = COLOR_BLACK;
const int STAR_COLOR = COLOR_BLACK, CHOSE_COLOR = COLOR_WHITE, CLICK_COLOR = COLOR_HWHITE;

/* 各菜单项函数 */
void mode_A(int row, int col, int stars[][N + 2]);
void mode_B(int& score, int row, int col, int stars[][N + 2]);
void mode_C(int& score, int row, int col, int stars[][N + 2]);
void mode_D(int row, int col, int stars[][N + 2], bool mode);
void mode_E(int row, int col, int stars[][N + 2], bool mode);
void mode_F(int& score, int row, int col, int stars[][N + 2], bool mode);
void mode_G(int& score, int row, int col, int stars[][N + 2], bool mode);

/* 菜单项A-C数组方式实现的各函数 */
int input_order(int row, int col, char order[], int stars[][N + 2], char search[][N + 2]);
void print_search_array(int row, int col, char search[M + 2][N + 2]);
void print_stars_array(int print_mode, int row, int col, int stars[][N + 2], char search[][N + 2]);

/* cmd图形界面方式实现的各函数 */
void show_frame(bool mode, int row, int col);
void show_down_state(bool mode, int row, int state, int tool, int i, int j);
void paint_one_star_xy(int X, int Y, const int bg_color, const int fg_color);
void paint_one_block_xy(int X, int Y, bool mode);
void paint_one_block(bool mode, bool paint_star_or_not, int i, int j, const int bg_color, const int fg_color);
void paint_neibor(bool mode, char search[][N + 2], int stars[][N + 2], int fg_color, int pos[]);
void paint_each_move(int start_pos[], int end_pos[], bool mode, int color);

/* 内部数组/图形方式共用的公共函数 */
void init_search(char search[][N + 2], int X, int Y);
int count_search_only(int row, int col, char search[][N + 2]);
void search_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2]);
int count_neighbor(char pos[], int value, char search[][N + 2], int stars[][N + 2]);
void do_move(int row, int col, int stars[][N + 2], bool flag, bool mode);
void do_remove(int stars[][N + 2], char search[][N + 2]);
int eliminableStars_left_or_not(int row, int col, int stars[][N + 2]);

/* 工具函数 */
void to_be_continued(const char* prompt);