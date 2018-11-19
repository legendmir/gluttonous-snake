#pragma once
#include<iostream>
#include<windows.h>
#include<conio.h>
#include<time.h>
#include<vector>
#include<stdlib.h>
#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4
#define SNAKE_SIZE 500
#define MAP_LEN 35
#define MAP_WID 30
#define ESC 27
#pragma comment(lib,"winmm.lib")
using namespace std;
int g_buff[MAP_LEN][MAP_WID];
void show_char(SHORT x, SHORT y, char*pstr, WORD color = 0x0A, HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE))
{
	SetConsoleCursorPosition(hStdOut, { 2*x ,y });
	SetConsoleTextAttribute(hStdOut, color);
	cout << pstr;
}
void set_cursor(SHORT x, SHORT y, WORD color = 0x0A, HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE))
{
	SetConsoleCursorPosition(hStdOut, { 2 * x ,y });
	SetConsoleTextAttribute(hStdOut, color);
}
