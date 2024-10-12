#include "Header.h"


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Ru");
	char** my, ** any, ** my2, ** any2;
	int a;
	do {
		add_memory(&my, &any, &my2, &any2);						// Выделение памяти под игровые поля
		do {
			printf("Меню игры:\nНачать новую игру на 2х игроков - 1\nНачать новую игру против бота - 2\nВозобновить существующую игру на двух игроков - 3\nВозобновить существующую игру против бота - 4\nПравила игры - 5\n");
			a = Input(1, 5);
			system("cls");
			switch (a) {
			case 1: newGameTwoPlayer(my, any, my2, any2);		// Запуск новой игры на два игрока
				break;
			case 2:	newGameBot(my, any, my2, any2);				// Запуск новой игры против бота
				break;
			case 3: restartTwoPlayer(my, any, my2, any2);		// Запуск существующей игры на два игрока
				break;
			case 4:	restartGameBot(my, any, my2, any2);			// Запуск существующей игры против бота
				break;
			case 5: gameRules();								// Правила игры
			}
		} while (a == 5);
		free_mem(my, any, my2, any2);							// Функция очистки памяти
		printf("\nЗапустить новую игру - 1 / Выйти из программы - 2\n");
		a = Input(1, 2);
	} while (a == 1);
	return 0;
}