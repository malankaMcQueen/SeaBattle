#include <stdio.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>


struct ships {
	int four = 1;
	int three = 2;
	int two = 3;
	int one = 4;
};

int Input(int min, int max);																// ������� ����� � ���������
void add_memory(char*** my, char*** any, char*** my2, char*** any2);						// ������� ��������� ������ ��� ������� �����
void pole(char** my, char** any);															// ������� ������ ���� ������� �����
void vivod(char** my);																		// ������� ������ ������ ����
void newGameTwoPlayer(char** my, char** any, char** my2, char** any2);						// ������� ������� ����� ���� ��� ���� �������
void newGameBot(char** my, char** any, char** my2, char** any2);							// ������� ������� ����� ���� ������ ����������
void restartTwoPlayer(char** my, char** any, char** my2, char** any2);						// ������� ������������� ������������ ���� ��� ���� �������
void restartGameBot(char** my, char** any, char** my2, char** any2);						// ������� ������������� ������������ ���� ������ ����������
void gameRules();																			// ������� ������ ������ ����
void positions(char** my);																	// ������� ����������� �������� �������
bool proverka(char** my, int l1, int l2, int n1, int n2, int len);							// ������� �������� ������������ ����������� ��������
void postanovka(char** my, int l1, int l2, int n1, int n2);									// ������� ������������ ������� � ����� ������
void randomposition(char** any, bool fl);													// ������� ��������� ����������� ��������
void twoplayers(char** my, char** any, char** my2, char** any2, int player, int a, int b);	// ������� ���������� ���� ��� ���� ������� 
bool attak(char** pole1, char** pole2, int* k, int player, char** any, int* k2);			// ������� ����� ������ ����
void botplayer(char** my, char** any, char** any2, int player, int a, int b);				// ������� ���������� ���� ������ ����
bool attak_bot(char** pol, int* k);															// ������� ����� ����
void obstrelShip(char** pol, int* num, int* let);											// ������� ����� ����, ���� ���� �������� �������
bool proverkaHoda(char** pol, int num, int num2);											// ������� �������� ������������ ����
void starKill(char** pol, char** pol2, int num, int let);									// ������� ����������� ��������� ������ ������� �������
bool proverkaNaKill(char** pol, char** pol2, int num, int let, int* k);						// ������� �������� ���� �������, ��� ������
bool check_open_file(FILE* f);																// ������� �������� ����� �� ��������
void save_game(char** my, char** any, int player, int k1, int k2);							// ������� ���������� ���� � ����
void return_game(char** my, char** any, char** my2, char** any2, int* player, int* k1, int* k2);	// ������� ������������� ����
void free_mem(char** my, char** any, char** my2, char** any2);								// ������� ������� ������