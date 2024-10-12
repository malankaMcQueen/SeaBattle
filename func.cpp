#include "Header.h"




int Input(int min, int max) {											// Ввод с проверкой в заднных рамках
	int answ;
	while (!(scanf_s("%d", &answ) && (answ == (int)answ) && (answ >= min && answ <= max))) {
		printf("Wrong input.Try again\n");
		while (getchar() != '\n');
	}
	rewind(stdin);
	return answ;
}					

void add_memory(char*** my, char*** any, char*** my2, char*** any2) {			// Функция выделение памяти для игровых полей
	*my = (char**)calloc(10, sizeof(char*));
	*any = (char**)calloc(10, sizeof(char*));
	*my2 = (char**)calloc(10, sizeof(char*));
	*any2 = (char**)calloc(10, sizeof(char*));
	for (int i = 0; i < 10; i++) {
		(*my)[i] = (char*)calloc(10, sizeof(char));
		(*any)[i] = (char*)calloc(10, sizeof(char));
		(*my2)[i] = (char*)calloc(10, sizeof(char));
		(*any2)[i] = (char*)calloc(10, sizeof(char));
		for (int k = 0; k < 10; k++) {											// Заполняю поля пробелами
			(*my)[i][k] = ' ';
			(*any)[i][k] = ' ';
			(*my2)[i][k] = ' ';
			(*any2)[i][k] = ' ';
		}
	}
}

void pole(char** my,char** any) {												// Функция вывода двух игровых полей
	printf("\n\033[01;32m");													// Ставлю зеленый цвет
	printf("  A B C D E F G H I J\t\t\t  A B C D E F G H I J\n");
	printf(" *_|_|_|_|_|_|_|_|_|_*\t\t\t *_|_|_|_|_|_|_|_|_|_*\n");
	for (int i = 0; i < 10; i++) {
		printf("%d|", i);
		for (int k = 0; k < 10; k++){
			if (my[i][k] == '#')												// Если корабль убит, разукрашиваю его красным
				printf("\033[1;31m%c\033[01;32m|", my[i][k]);
			else if (my[i][k] == 'X')											// Если корабль подбит, помечаю его красным
				printf("\033[31m%c\033[01;32m|", my[i][k]);
			else if (my[i][k] == '*')											// Если промах, разукрашиваю голубым
				printf("\033[34m%c\033[01;32m|", my[i][k]);
			else
				printf("%c|", my[i][k]);
	}
		printf("\t\t\t");														// Вывод второго поля
		printf("%d|", i);
		for (int k = 0; k < 10; k++) {
			if (any[i][k] == '#')
				printf("\033[1;31m%c\033[01;32m|", any[i][k]);
			else if (any[i][k] == 'X')
				printf("\033[31m%c\033[01;32m|", any[i][k]);
			else if (any[i][k] == '*')
				printf("\033[34m%c\033[01;32m|", any[i][k]);
			else
				printf("%c|", any[i][k]);
		}
		printf("\n");
		if (i != 9)
		printf(" |-|-|-|-|-|-|-|-|-|-|\t\t\t |-|-|-|-|-|-|-|-|-|-|\n");
		else 
			printf(" *-------------------*\t\t\t *-------------------*\n");
	}
	printf("\n\033[0m");														// Возвращаю цвет на белый
}

void vivod(char** my) {														// Вывод одного поля
	printf("\033[01;32m");
	printf("  A B C D E F G H I J\n");
	printf(" *_|_|_|_|_|_|_|_|_|_*\n");
	for (int i = 0; i < 10; i++) {
		printf("%d|", i);
		for (int k = 0; k < 10; k++) {
			if (my[i][k] == '0')
				printf("\033[01;34m%c\033[01;32m|", my[i][k]);
			else printf("%c|", my[i][k]);
		}
		printf("\n");
		if (i != 9)
			printf(" |-|-|-|-|-|-|-|-|-|-|\n");
		else
			printf(" *-------------------*\n");
	}
	printf("\033[0m");
}

void newGameTwoPlayer(char** my, char** any, char** my2, char** any2) {			// Функция запуска новвой игры для двух игроков
	printf("Я запускаю игру на двух игроков\n");
	pole(my, any);																// Вывод поля
	printf("Игрок 1, выберите способ расстановки кораблей: расстановка вручную - 1; расстановка рандомом - 2\n");
	int a = Input(1, 2);
	if (a == 1)
		positions(my);															// Расстановка кораблей вручную
	else
		randomposition(my, true);												// Расстановка с помощью рандома 
	printf("\nИгрок 2, выберите способ расстановки кораблей: расстановка вручную - 1; расстановка рандомом - 2\n");
	a = Input(1, 2);
	if (a == 1)
		positions(any);
	else
		randomposition(any, true);
	printf("\nНачинаю игру на двух игроков\n");
	twoplayers(my, any, my2, any2, 0, 10, 10);									// Процесс игры двух игроков
}

void newGameBot(char** my, char** any, char** my2, char** any2) {				// Функция запуска новой игры против бота
	printf("Выберите способ расстановки кораблей: расстановка вручную - 1; расстановка рандомом - 2\n");
	int a = Input(1, 2);
	if (a == 1)
		positions(my);
	else
		randomposition(my, true);
	botplayer(my, any, any2, 0, 10, 10);										// Процесс игры против бота
}

void restartTwoPlayer(char** my, char** any, char** my2, char** any2) {			// Возобновление существующей игры для двух игроков
	int player, k1, k2;
	return_game(my, any, my2, any2, &player, &k1, &k2);
	twoplayers(my, any, my2, any2, player, k1, k2);
}

void restartGameBot(char** my, char** any, char** my2, char** any2) {			// Функция возобновления существующей игры против бота
	int player, k1, k2;
	return_game(my, any, my2, any2, &player, &k1, &k2);
	botplayer(my, any, any2, 1, k1, k2);
}

void gameRules() {																// Функция вывода правил игры
	FILE* f;
	char* str = (char*)calloc(255, sizeof(char));
	fopen_s(&f, "RulesOfGame.txt", "r");
	if (!check_open_file(f)) {
		printf("\nОшибка, перезапустите программу.");
		exit(404);
	}
	printf("\n");
	while (fgets(str, 255, f)) {
		printf("%s", str);
	}
	printf("\n\n");
	fclose(f);
}

void positions(char** my) {												// Функция расстановки кораблей вручную
	ships pal;
	int type;
	int a = 10, g;														// а-кол-во кораблей которое нужно расставить
	int l1, l2, n1, n2;													// Параметры в районе которых буду ставить корабли l-буквы, n-цифры
	char* str = (char*)malloc(6 * sizeof(char));
	system("cls");
	vivod(my);															// Вывожу игровое поле
	while (a != 0) {
		do {
			do {
				printf("Вам нужно расставить корабли типов:\n");
				printf("1. Одно палубный-%d\n", pal.one);
				printf("2. 2-х палубный-%d\n", pal.two);
				printf("3. 3-х палубный-%d\n", pal.three);
				printf("4. 4-х палубный-%d\n", pal.four);
				printf("Выберите тип корабля: ");
				g = 0;
				type = Input(1, 4);
				switch (type) {
				case 1: if (pal.one == 0) {
					printf("Данный тип корабля полностью использован\n");
					g = 1;
				} break;
				case 2: if (pal.two == 0) {
					printf("Данный тип корабля полностью использован\n");
					g = 1;
				} break;
				case 3: if (pal.three == 0) {
					printf("Данный тип корабля полностью использован\n");
					g = 1;
				} break;
				case 4: if (pal.four == 0) {
					printf("Данный тип корабля полностью использован\n");
					g = 1;
				} break;
				}
			} while (g);
			printf("Укажите промежуток клеток, куда вы хотите его поставить(пример Е6-Е9): ");
			rewind(stdin);
			fgets(str, 6, stdin);
			l1 = str[0] - 'A';
			l2 = str[3] - 'A';
			n1 = str[1] - '0';
			n2 = str[4] - '0';
		} while (!proverka(my, l1, l2, n1, n2, type));					// Проверяю можно ли поставить корабль на это место
		system("cls");
		postanovka(my, l1, l2, n1, n2);									// Фиксирую корабль в данном месте
		switch (type) {
		case 1: pal.one--; break;
		case 2: pal.two--; break;
		case 3: pal.three--; break;
		case 4: pal.four--; break;
		}
		printf("Корабль успешно поставлен!\n");
		vivod(my);
		a--;
	}
	printf("Корабли успешно расставлены!\n");
	printf("Продолжить игру - 1 / Расставить корабли заново - 2\n");
	g = Input(1, 2);
	if (g == 2) {
		for (int i = 0; i < 10; i++)
			for (int k = 0; k < 10; k++)
				my[i][k] = ' ';
		printf("Расстановка кораблей вручную - 1 / Расстановка с помощью рандома - 2\n");
		g = Input(1, 2);
		if (g == 1)
			positions(my);
		else if (g == 2)
			randomposition(my, true);
	}
	system("cls");
}

bool proverka(char** my, int l1, int l2, int n1, int n2,int len) {					// Функция проверки постановки корабля
	if (l1 < 0 || l1>9 || l2 < 0 || l2>9 || n1 < 0 || n1>9 || n2 < 0 || n2>9) {
		printf("Заданные параметры не подходят:\n ");
		return false;
	}
	if (l1 != l2 && n1 != n2) {
		printf("Заданные параметры не подходят:\n ");
		return false;
	}
	if (l2 - l1 != len - 1 && n2 - n1 != len-1) {
		printf("Заданные параметры не подходят:\n ");
		return false;
	}
	if (len == 1 && (l1 != l2 || n1 != n2)) {
		printf("Заданные параметры не подходят:\n ");
		return false;
	}
	if (l2 == l1) {
		for (int i = n1; i < n2 + 1; i++) {
			if (my[i][l1] != ' ') {
				printf("Заданные параметры не подходят:\n");
				return false;
			}
			if (l1 != 9)
				if (my[i][l1 + 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (l1 != 0)
				if (my[i][l1 - 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (i != 9)
				if (my[i + 1][l1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (i != 0)
				if (my[i - 1][l1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (l1 != 9 && i != 9)
				if (my[i + 1][l1 + 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (l1 != 9 && i != 0)
				if (my[i - 1][l1 + 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (l1 != 0 && i != 9)
				if (my[i + 1][l1 - 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

			if (l1 != 0 && i != 0)
				if (my[i - 1][l1 - 1] != ' ') {
					printf("Заданные параметры не подходят:\n");
					return false;
				}

		}
	}
	if (n2 == n1) {
		for (int i = l1; i < l2 + 1; i++) {
			if (my[n1][i] != ' ') {
				printf("Заданные параметры не подходят\n");
				return false;
			}
			if (i != 9)
				if (my[n1][i + 1] != ' ') {
					printf("Заданные параметры не подходят\n");
					return false;
				}

			if (i != 0)
				if (my[n1][i - 1] != ' ') {
					printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 9)
				if (my[n1 + 1][i] != ' ') {
					printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 0)
				if (my[n1 - 1][i] != ' ') {
					printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 9 && i != 9)
				if (my[n1 + 1][i + 1] != ' ') {
				printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 0 && i != 9)
				if (my[n1 - 1][i + 1] != ' ') {
				printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 9 && i != 0)
				if (my[n1 + 1][i - 1] != ' ') {
				printf("Заданные параметры не подходят\n");
					return false;
				}

			if (n1 != 0 && i != 0)
				if (my[n1 - 1][i - 1] != ' ') {
				printf("Заданные параметры не подходят\n");
					return false;
				}
		}
	}
	return true;
}

void postanovka(char** my, int l1, int l2, int n1, int n2) {			// Функция фиксации корабля в совей клетке
	if (l1 == l2)
		while (n1 != n2+1) {
			my[n1][l1] = '0';
			n1++;
		}
	else {
		while (l1 != l2+1){
			my[n1][l1] = '0';
			l1++;
		}
	}
}

void randomposition(char** any, bool fl) {			// Если fl-1 Рандом для пользователя, Если fl-0 Рандом для бота
	int a = 10;
	int n1,n2,l1,l2,len;
	for (int a = 10; a > 0; a--) {
		if (a == 10)
			len = 4;
		else if (a > 7 && a < 10)
			len = 3;
		else if (a > 4 && a < 8)
			len = 2;
		else if (a > 0 && a < 5)
			len = 1;
		do {
			if (rand() % 2 == 0) {					// Выбираю направление вертикаль или горизонталь (горизонталь)
				n1 = rand() % 10;
				l1 = rand() % (10 - (len - 1));
				n2 = n1;
				l2 = l1 + len - 1;
			}
			else {
				l1 = rand() % 10;
				l2 = l1;
				n1 = rand() % (10 - (len - 1));
				n2 = n1 + len - 1;
			}
		} while (!proverka(any, l1, l2, n1, n2, len));	// Проверяю можно ли поставить корабль в этом место
		system("cls");
		postanovka(any, l1, l2, n1, n2);				// Ставлю корабль
	}
	printf("Корабли успешно расставлены!\n");
	if (fl) {
		printf("Хотите просмотреть расстановку ваших кораблей? 1 - Да / 2 - Нет\n");
		int k = Input(1, 2);
		if (k == 1) {
			vivod(any);
			printf("Продолжить игру - 1 / Расставить корабли заново - 2\n");
			k = Input(1, 2);
			if (k == 2) {
				for (int i = 0; i < 10; i++)
					for (int k = 0; k < 10; k++)
						any[i][k] = ' ';
				printf("Расстановка кораблей вручную - 1 / Расстановка с помощью рандома - 2\n");
				k = Input(1, 2);
				if (k == 1)
					positions(any);
				else if (k == 2)
					randomposition(any, true);
			}
		}
	}
	system("cls");
}

void twoplayers(char** my, char** any, char** my2, char** any2, int player, int a, int b) {	// Функция игры на два игрока
	printf("\nДля того чтобы сохранить прогресс игры введите: '*'");
	do {
		if (player == 0 || player == 1) {						// Если player=0-запуск новой игры/Если player=1-ходит первый игрок/Если player=2- ходит 2 игрок
			pole(my2, any2);									// Вывод двух игровых полей
			printf("Ход первого игрока: ");
			while (attak(any, any2, &b, 1, my, &a)) {			// Если true-есть попадание
				pole(my2, any2);
				if (b == 0)
					break;
				printf("\nХодит первый игрок: ");
			}
			if (b == 0)
				break;
			printf("\nНе попал, ход переходит ко второму игроку\n");
		}
		player = 0;
		pole(my2, any2);
		printf("\nХод второго игрока: ");
		while (attak(my, my2, &a, 2, any, &b)) {
			pole(my2, any2);
			if (a == 0)
				break;
			printf("\nХодит второй игрок: ");
		}
		if (a == 0)
			break;
		printf("\nНе попал, ход переходит к первому игроку\n");
	} while (a != 0 && b != 0);
	if (a == 0) {
		printf("\nПобедил второй игрок!");
	}
	else
		printf("\nПобедил первый игрок!");
	printf("\nКорабли, которые не были убиты помечены зелным");
	pole(my, any);
	printf("\nДо встречи, чемпионы!\n");
}

bool attak(char** pole1, char** pole2, int* k, int player, char** any, int* k2) {	// Функция атаки
	char letter;
	int let;
	int num;
	bool m;
	do {
		rewind(stdin);
		letter = getchar();
		if (letter == '*') {
			save_game(pole1, any, player, *k, *k2);						// Если *-сохранение игры
			printf("\nПродолжить игру - 1 / Закончить игру - 2\n");
			int a = Input(1, 2);
			if (a == 2) {
				exit(1);
			}
			else {
				printf("Ваш ход: ");
				letter = getchar();
			}
		}
		let = letter - 'A';
		scanf_s("%d", &num);
		m = proverkaHoda(pole1, num, let);								// Проверка, можно ли ходить в эту клетку
	} while (!m);
	system("cls");
	printf("Ваш ход: %c%d", letter, num);
	if (pole1[num][let] == ' ') {										// Если клетка была пустой, ставим *
		pole1[num][let] = '*';
		pole2[num][let] = '*';
		return false;
	}
	if (pole1[num][let] == '0') {										// Если в клетке был корабль, ставим Х
		printf("\nEсть попадание!");
		pole1[num][let] = 'X';
		pole2[num][let] = 'X';
		proverkaNaKill(pole1, pole2, num, let, k);
		return true;
	}
}

void botplayer(char** my, char** any, char** any2, int player, int a, int b) {		// Функция игры с ботом
	if (player == 0)
		randomposition(any, false);													// Рандомная расстановка кораблей бота
	pole(my, any2);
	do {
		printf("\nВаш ход: ");
		while (attak(any, any2, &b, 1, my, &a)) {
			pole(my, any2);
			if (b == 0)
				break;
			printf("\nВаш ход: ");
		}
		if (b == 0)
			break;
		printf("\nНе попал, ходит компьютер: ");				
		while (attak_bot(my, &a)) {
			pole(my, any2);
			system("pause");
			system("cls");
			if (a == 0)
				break;
			printf("\nХодит компьютер: ");
		}
		if (a == 0)
			break;
		pole(my, any2);
		printf("\nКомпьютер не попал, Ваш ход: \n");
	} while (a != 0 && b != 0);
	if (a == 0) {
		printf("\nПобедил компьютер!");
	}
	else
		printf("\nПобедил игрок!");
	printf("\nКорабли, которые не были убиты помечены зеленым");
	pole(my, any);
	printf("\nДо встречи, чемпион!");
}

bool attak_bot(char** pol, int* k) {					// Функция атаки бота
	int num, let;
	bool x = false;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (pol[i][j] == 'X') {						// Проверяю есть ли подбитый корабль
				x = true;
				num = i;
				let = j;
			}
	if (x) {										
		obstrelShip(pol, &num, &let);					// Функция обстрела вокруг подбитого корабля
	}
	else {												// Если подбитого корабля нет, делаю рандомный выстрел
		do {
			num = rand() % 10;
			let = rand() % 10;
		} while (pol[num][let] == '*' || pol[num][let] == '#' || pol[num][let] == 'X');
	}
	printf("%c%d", let + 'A', num);
	if (pol[num][let] == ' ') {
		pol[num][let] = '*';
		return false;
	}
	if (pol[num][let] == '0') {
		printf("\nВ наш корабль попали!");
		pol[num][let] = 'X';
		proverkaNaKill(pol, pol, num, let, k);			// Функция проверка убили ли корабль, или подбили
		return true;
	}
}

void obstrelShip(char** pol, int* num, int* let) {							// Функция обстрела подбитого корабля ботом					
	if (*num > 0 && *num < 9) {
		if (pol[*num - 1][*let] == 'X' && pol[*num + 1][*let] != '*') {
			*num = *num + 1;
			return;
		}
		if (pol[*num - 1][*let] == 'X' && pol[*num + 1][*let] == '*') {
			while (pol[--(*num)][*let] != '0');
			return;
		}
		if (pol[*num + 1][*let] == 'X' && pol[*num - 1][*let] != '*') {
			*num = *num - 1;
			return;
		}
		if (pol[*num + 1][*let] == 'X' && pol[*num - 1][*let] == '*') {
			while (pol[++(*num)][*let] != '0');
			return;
		}
	}
	if (*let > 0 && *let < 9) {
		if (pol[*num][*let - 1] == 'X' && pol[*num][*let + 1] != '*') {
			*let = *let + 1;
			return;
		}
		if (pol[*num][*let - 1] == 'X' && pol[*num][*let + 1] == '*') {
			while (pol[*num][--(*let)] != '0');
			return;
		}	if (pol[*num][*let + 1] == 'X' && pol[*num][*let - 1] != '*') {
			*let = *let - 1;
			return;
		}
		if (pol[*num][*let + 1] == 'X' && pol[*num][*let - 1] == '*') {
			while (pol[*num][--(*let)] != '0');
			return;
		}
	}

	// Углы проверяю
	int i;
	if (*let == 0 && *num == 0) {
		if (pol[*num + 1][*let] == 'X') {
			while (pol[++(*num)][*let] != '0');
			return;
		}
		if (pol[*num][*let + 1] == 'X') {
			while (pol[*num][++(*let)] != '0');
			return;
		}
		i = rand() % 2;								// i=1 меняю по num
		if (pol[*num][*let + 1] == '*' || (pol[*num + 1][*let] != '*' && i)) {
			(*num)++;
			return;
		}
		else {
			(*let)++;
			return;
		}
	}
	if (*let == 9 && *num == 0) {
		if (pol[*num + 1][*let] == 'X') {
			while (pol[++(*num)][*let] != '0');
			return;
		}
		if (pol[*num][*let - 1] == 'X') {
			while (pol[*num][--(*let)] != '0');
			return;
		}
		i = rand() % 2;								// i=1 меняю по num
		if (pol[*num][*let - 1] == '*' || (pol[*num + 1][*let] != '*' && i)) {
			(*num)++;
			return;
		}
		else {
			(*let)--;
			return;
		}
	}
	if (*let == 0 && *num == 9) {
		if (pol[*num - 1][*let] == 'X') {
			while (pol[--(*num)][*let] != '0');
			return;
		}
		if (pol[*num][*let + 1] == 'X') {
			while (pol[*num][++(*let)] != '0');
			return;
		}
		i = rand() % 2;								// i=1 меняю по num
		if (pol[*num][*let + 1] == '*' || (pol[*num - 1][*let] != '*' && i)) {
			(*num)--;
			return;
		}
		else {
			(*let)++;
			return;
		}
	}
	if (*let == 9 && *num == 9) {
		if (pol[*num - 1][*let] == 'X') {
			while (pol[--(*num)][*let] != '0');
			return;
		}
		if (pol[*num][*let - 1] == 'X') {
			while (pol[*num][--(*let)] != '0');
			return;
		}
		i = rand() % 2;								// i=1 меняю по num
		if (pol[*num][*let - 1] == '*' || (pol[*num - 1][*let] != '*' && i)) {
			(*num)--;
			return;
		}
		else {
			(*let)--;
			return;
		}
	}

	if (*let == 0) {
		if (pol[*num][*let + 1] == 'X') {
			while (pol[*num][++(*let)] != '0');
			return;
		}
		i = rand() % 3;                              // 1 num+ / 2-num- / 3-let+
		if ((pol[*num + 1][*let] != '*' && i == 1) || (pol[*num - 1][*let] == '*' && pol[*num][*let + 1] == '*')) {
			(*num)++;
			return;
		}
		if ((pol[*num - 1][*let] != '*' && i == 2) || (pol[*num + 1][*let] == '*' && pol[*num][*let + 1] == '*')) {
			(*num)--;
			return;
		}
		if ((pol[*num][*let + 1] != '*' && i == 3) || (pol[*num + 1][*let] == '*' && pol[*num - 1][*let] == '*')) {
			(*let)++;
			return;
		}
	}
	if (*let == 9) {
		if (pol[*num][*let - 1] == 'X') {
			while (pol[*num][--(*let)] != '0');
			return;
		}
		i = rand() % 3;                              // 1 num+ / 2-num- / 3-let-
		if ((pol[*num + 1][*let] != '*' && i == 1) || (pol[*num - 1][*let] == '*' && pol[*num][*let - 1] == '*')) {
			(*num)++;
			return;
		}
		if ((pol[*num - 1][*let] != '*' && i == 2) || (pol[*num + 1][*let] == '*' && pol[*num][*let - 1] == '*')) {
			(*num)--;
			return;
		}
		if ((pol[*num][*let - 1] != '*' && i == 3) || (pol[*num + 1][*let] == '*' && pol[*num - 1][*let] == '*')) {
			(*let)--;
			return;
		}
	}
	if (*num == 9) {
		if (pol[*num - 1][*let] == 'X') {
			while (pol[--(*num)][*let] != '0');
			return;
		}
		i = rand() % 3;                              // 1 num- / 2-let+ / 3-let-
		if ((pol[*num - 1][*let] != '*' && i == 1) || (pol[*num][*let + 1] == '*' && pol[*num][*let - 1] == '*')) {
			(*num)--;
			return;
		}
		if ((pol[*num][*let + 1] != '*' && i == 2) || (pol[*num - 1][*let] == '*' && pol[*num][*let - 1] == '*')) {
			(*let)++;
			return;
		}
		if ((pol[*num][*let - 1] != '*' && i == 3) || (pol[*num - 1][*let] == '*' && pol[*num][*let + 1] == '*')) {
			(*let)--;
			return;
		}
	}
	if (*num == 0) {
		if (pol[*num + 1][*let] == 'X') {
			while (pol[++(*num)][*let] != '0');
			return;
		}
		i = rand() % 3;                              // 1 num+ / 2-let+ / 3-let-
		if ((pol[*num + 1][*let] != '*' && i == 1) || (pol[*num][*let + 1] == '*' && pol[*num][*let - 1] == '*')) {
			(*num)++;
			return;
		}
		if ((pol[*num][*let + 1] != '*' && i == 2) || (pol[*num + 1][*let] == '*' && pol[*num][*let - 1] == '*')) {
			(*let)++;
			return;
		}
		if ((pol[*num][*let - 1] != '*' && i == 3) || (pol[*num + 1][*let] == '*' && pol[*num][*let + 1] == '*')) {
			(*let)--;
			return;
		}
	}
	i = rand() % 2;					// i=1-num+-
	if ((pol[*num][*let + 1] == '*' && pol[*num][*let - 1] == '*') || (i && (pol[*num + 1][*let] != '*' || pol[*num - 1][*let] != '*'))) {
		i = rand() % 2;				// i=1 num+
		if (pol[*num - 1][*let] == '*' || (i && pol[*num + 1][*let] != '*')) {
			(*num)++;
			return;
		}
		else {
			(*num)--;
			return;
		}
	}
	else {
		i = rand() % 2;
		if (pol[*num][*let - 1] == '*' || (i && pol[*num][*let + 1] != '*')) {
			(*let)++;
			return;
		}
		else {
			(*let)--;
			return;
		}
	}
}

bool proverkaHoda(char** pol, int num, int num2) {		// Функция проверки правильности параметра хода
	if (num < 0 || num>9 || num2 < 0 || num2>9) {
		printf("Неправильно заданы параметры хода, попробуйте еще раз: ");
		return false;
	}
	if (pol[num][num2] == ' ' || pol[num][num2] == '0')
		return true;
	printf("Вы уже стреляли в эту клетку, попробуйте еще раз: ");
	return false;
}

void starKill(char** pol, char** pol2, int num, int let) {			// Функция расстановки звездочек, при убийстве корабля
	pol2[num][let] = '#';
	pol[num][let] = '#';
	if (num < 9) {
		if (pol[num + 1][let] == 'X')
			starKill(pol, pol2 ,num + 1, let);						// Рекурсивная расстановка
		else if (pol[num + 1][let] == ' ') {
			pol[num + 1][let] = '*';
			pol2[num + 1][let] = '*';
		}
	}
	if (let < 9) {
		if (pol[num][let + 1] == 'X')
			starKill(pol, pol2, num, let + 1);
		else if (pol[num][let + 1] == ' ') {
			pol[num][let + 1] = '*';
			pol2[num][let + 1] = '*';
		}
	}
	if (let > 0) {
		if (pol[num][let - 1] == 'X')
			starKill(pol, pol2, num, let - 1);
		else if (pol[num][let - 1] == ' ') {
			pol[num][let - 1] = '*';
			pol2[num][let - 1] = '*';
		}
	}
	if (num > 0) {
		if (pol[num - 1][let] == 'X')
			starKill(pol, pol2, num - 1, let);
		else if (pol[num - 1][let] == ' ') {
			pol[num - 1][let] = '*';
			pol2[num - 1][let] = '*';
		}
	}
	if (num < 9 && let < 9) {
		if (pol[num + 1][let + 1] == ' ') {
			pol[num + 1][let + 1] = '*';
			pol2[num + 1][let + 1] = '*';
		}
	}
	if (num > 0 && let > 0) {
		if (pol[num - 1][let - 1] == ' ') {
			pol[num - 1][let - 1] = '*';
			pol2[num - 1][let - 1] = '*';
		}
	}
	if (num > 0 && let < 9) {
		if (pol[num - 1][let + 1] == ' ') {
			pol[num - 1][let + 1] = '*';
			pol2[num - 1][let + 1] = '*';
		}
	}
	if (num < 9 && let > 0) {
		if (pol[num + 1][let - 1] == ' ') {
			pol[num + 1][let - 1] = '*';
			pol2[num + 1][let - 1] = '*';
		}
	}
}

bool proverkaNaKill(char** pol, char** pol2, int num, int let, int* k) {	// Функция проверяющая убит корабль, или подбит
	if (num < 9) {
		if (pol[num + 1][let] == '0')
			return false;
	}
	if (num > 0) {
		if (pol[num - 1][let] == '0')
			return false;
	}
	if (let < 9) {
		if (pol[num][let+1] == '0')
			return false;
	}
	if (let >0) {
		if (pol[num][let - 1] == '0')
			return false;
	}
	for (int i = 1; i < 4; i++) {
		if (num + i < 10) {
			if (pol[num + i][let] == '*' || pol[num + i][let] == ' ')
				break;
			if (pol[num + i][let] == '0')
				return false;
		}
	}
	for (int i = 1; i < 4; i++) {
		if (num - i >= 0) {
			if (pol[num - i][let] == '*' || pol[num - i][let] == ' ')
				break;
			if (pol[num - i][let] == '0')
				return false;
		}
	}
	for (int i = 1; i < 4; i++) {
		if (let + i < 10) {
			if (pol[num][let + i] == '*' || pol[num][let + i] == ' ')
				break;
			if (pol[num][let + i] == '0')
				return false;
		}
	}
	for (int i = 1; i < 4; i++) {
		if (let - i >= 0) {
			if (pol[num][let - i] == '*' || pol[num][let - i] == ' ')
				break;
			if (pol[num][let - i] == '0')
				return false;
		}
	}
	printf("Корабль убит!");
	(*k)--;
	starKill(pol, pol2, num, let);							// Вызываю функцию расстановки звездочек вокруг убитого корабля
	return true;
}

bool check_open_file(FILE* f) {			// Функция проверки открыт ли файл
	if (f == NULL) {
		printf("\nНе удалось найти файл, попробуйте еще раз");
		return false;
	}
	return true;
}

void save_game(char** my, char** any, int player, int k1, int k2) {		// Функция сохранения игры
	FILE* f;
	char* name = (char*)calloc(30, sizeof(char));
	printf("\nВведите имя файла: ");
	rewind(stdin);
	fgets(name, 30, stdin);
	int i;
	for (i = 0; name[i] != '\n'; i++);
	name[i] = '\0';
	fopen_s(&f, name, "wb");
	fwrite(&player, sizeof(int), 1, f);
	if (player == 1) {													// player-индекс игрока, который ходит
		for (int i = 0; i < 10; i++)
			fwrite(any[i], sizeof(char), 10, f);
		fwrite(&k2, sizeof(int), 1, f);
		for (int i = 0; i < 10; i++)
			fwrite(my[i], sizeof(char), 10, f);
		fwrite(&k1, sizeof(int), 1, f);
	}
	else {
		for (int i = 0; i < 10; i++)
			fwrite(my[i], sizeof(char), 10, f);
		fwrite(&k1, sizeof(int), 1, f);
		for (int i = 0; i < 10; i++)
			fwrite(any[i], sizeof(char), 10, f);
		fwrite(&k2, sizeof(int), 1, f);
	}
	fclose(f);
}

void return_game(char** my, char** any, char** my2, char** any2, int* player, int* k1, int* k2) {	// Функция возобновления игры
	FILE* f;
	char* name = (char*)calloc(30, sizeof(char));
	do {
		printf("\nВведите имя файла: ");
		rewind(stdin);
		fgets(name, 30, stdin);
		int i;
		for (i = 0; name[i] != '\n'; i++);
		name[i] = '\0';
		fopen_s(&f, name, "rb");
	} while (!check_open_file(f));
	fread(player, sizeof(int), 1, f);
	for (int i = 0; i < 10; i++)
		fread(my[i], sizeof(char), 10, f);
	fread(k1, sizeof(int), 1, f);
	for (int i = 0; i < 10; i++)
		fread(any[i], sizeof(char), 10, f);
	fread(k2, sizeof(int), 1, f);
	fclose(f);
	for (int i = 0; i < 10; i++) {
		for (int k = 0; k < 10; k++) {
			my2[i][k] = my[i][k];
			if (my2[i][k] == '0')
				my2[i][k] = ' ';
			any2[i][k] = any[i][k];
			if (any2[i][k] == '0')
				any2[i][k] = ' ';
		}
	}
}

void free_mem(char** my, char** any, char** my2, char** any2) {		// Функция очистки памяти
	for (int i = 0; i < 10; i++) {
		free(my[i]);
		free(my2[i]);
		free(any[i]);
		free(any2[i]);
	}
	free(my);
	free(any);
	free(my2);
	free(any2);
}