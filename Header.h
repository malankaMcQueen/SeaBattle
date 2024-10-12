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

int Input(int min, int max);																// Функция ввода с проверкой
void add_memory(char*** my, char*** any, char*** my2, char*** any2);						// Функция выделения памяти для игровых полей
void pole(char** my, char** any);															// Функция вывода двух игровых полей
void vivod(char** my);																		// Функция вывода одного поля
void newGameTwoPlayer(char** my, char** any, char** my2, char** any2);						// Функция запуска новой игры для двух игроков
void newGameBot(char** my, char** any, char** my2, char** any2);							// Функция запуска новой игры против компьютера
void restartTwoPlayer(char** my, char** any, char** my2, char** any2);						// Функция возобновления существующей игры для двух игроков
void restartGameBot(char** my, char** any, char** my2, char** any2);						// Функция возобновления существующей игры против компьютера
void gameRules();																			// Функция вывода правил игры
void positions(char** my);																	// Функция расстановки кораблей вручную
bool proverka(char** my, int l1, int l2, int n1, int n2, int len);							// Функция проверки правильности расстановки кораблей
void postanovka(char** my, int l1, int l2, int n1, int n2);									// Функция фиксирования корабля в своей клетке
void randomposition(char** any, bool fl);													// Функция рандомной расстановки кораблей
void twoplayers(char** my, char** any, char** my2, char** any2, int player, int a, int b);	// Функция проведения игры для двух игроков 
bool attak(char** pole1, char** pole2, int* k, int player, char** any, int* k2);			// Функция атаки чужого поля
void botplayer(char** my, char** any, char** any2, int player, int a, int b);				// Функция проведения игры против бота
bool attak_bot(char** pol, int* k);															// Функция атаки бота
void obstrelShip(char** pol, int* num, int* let);											// Функция атаки бота, если есть подбитый корабль
bool proverkaHoda(char** pol, int num, int num2);											// Функция проверки правильности хода
void starKill(char** pol, char** pol2, int num, int let);									// Функция расстановки звездочек вокруг убитого корабля
bool proverkaNaKill(char** pol, char** pol2, int num, int let, int* k);						// Функция проверки убит корабль, или подбит
bool check_open_file(FILE* f);																// Функция проверки файла на открытие
void save_game(char** my, char** any, int player, int k1, int k2);							// Функция сохранения игры в файл
void return_game(char** my, char** any, char** my2, char** any2, int* player, int* k1, int* k2);	// Функция возобновления игры
void free_mem(char** my, char** any, char** my2, char** any2);								// Функция очистки памяти