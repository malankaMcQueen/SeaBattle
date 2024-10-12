#include "Header.h"




int Input(int min, int max) {											// ���� � ��������� � ������� ������
	int answ;
	while (!(scanf_s("%d", &answ) && (answ == (int)answ) && (answ >= min && answ <= max))) {
		printf("Wrong input.Try again\n");
		while (getchar() != '\n');
	}
	rewind(stdin);
	return answ;
}					

void add_memory(char*** my, char*** any, char*** my2, char*** any2) {			// ������� ��������� ������ ��� ������� �����
	*my = (char**)calloc(10, sizeof(char*));
	*any = (char**)calloc(10, sizeof(char*));
	*my2 = (char**)calloc(10, sizeof(char*));
	*any2 = (char**)calloc(10, sizeof(char*));
	for (int i = 0; i < 10; i++) {
		(*my)[i] = (char*)calloc(10, sizeof(char));
		(*any)[i] = (char*)calloc(10, sizeof(char));
		(*my2)[i] = (char*)calloc(10, sizeof(char));
		(*any2)[i] = (char*)calloc(10, sizeof(char));
		for (int k = 0; k < 10; k++) {											// �������� ���� ���������
			(*my)[i][k] = ' ';
			(*any)[i][k] = ' ';
			(*my2)[i][k] = ' ';
			(*any2)[i][k] = ' ';
		}
	}
}

void pole(char** my,char** any) {												// ������� ������ ���� ������� �����
	printf("\n\033[01;32m");													// ������ ������� ����
	printf("  A B C D E F G H I J\t\t\t  A B C D E F G H I J\n");
	printf(" *_|_|_|_|_|_|_|_|_|_*\t\t\t *_|_|_|_|_|_|_|_|_|_*\n");
	for (int i = 0; i < 10; i++) {
		printf("%d|", i);
		for (int k = 0; k < 10; k++){
			if (my[i][k] == '#')												// ���� ������� ����, ������������ ��� �������
				printf("\033[1;31m%c\033[01;32m|", my[i][k]);
			else if (my[i][k] == 'X')											// ���� ������� ������, ������� ��� �������
				printf("\033[31m%c\033[01;32m|", my[i][k]);
			else if (my[i][k] == '*')											// ���� ������, ������������ �������
				printf("\033[34m%c\033[01;32m|", my[i][k]);
			else
				printf("%c|", my[i][k]);
	}
		printf("\t\t\t");														// ����� ������� ����
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
	printf("\n\033[0m");														// ��������� ���� �� �����
}

void vivod(char** my) {														// ����� ������ ����
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

void newGameTwoPlayer(char** my, char** any, char** my2, char** any2) {			// ������� ������� ������ ���� ��� ���� �������
	printf("� �������� ���� �� ���� �������\n");
	pole(my, any);																// ����� ����
	printf("����� 1, �������� ������ ����������� ��������: ����������� ������� - 1; ����������� �������� - 2\n");
	int a = Input(1, 2);
	if (a == 1)
		positions(my);															// ����������� �������� �������
	else
		randomposition(my, true);												// ����������� � ������� ������� 
	printf("\n����� 2, �������� ������ ����������� ��������: ����������� ������� - 1; ����������� �������� - 2\n");
	a = Input(1, 2);
	if (a == 1)
		positions(any);
	else
		randomposition(any, true);
	printf("\n������� ���� �� ���� �������\n");
	twoplayers(my, any, my2, any2, 0, 10, 10);									// ������� ���� ���� �������
}

void newGameBot(char** my, char** any, char** my2, char** any2) {				// ������� ������� ����� ���� ������ ����
	printf("�������� ������ ����������� ��������: ����������� ������� - 1; ����������� �������� - 2\n");
	int a = Input(1, 2);
	if (a == 1)
		positions(my);
	else
		randomposition(my, true);
	botplayer(my, any, any2, 0, 10, 10);										// ������� ���� ������ ����
}

void restartTwoPlayer(char** my, char** any, char** my2, char** any2) {			// ������������� ������������ ���� ��� ���� �������
	int player, k1, k2;
	return_game(my, any, my2, any2, &player, &k1, &k2);
	twoplayers(my, any, my2, any2, player, k1, k2);
}

void restartGameBot(char** my, char** any, char** my2, char** any2) {			// ������� ������������� ������������ ���� ������ ����
	int player, k1, k2;
	return_game(my, any, my2, any2, &player, &k1, &k2);
	botplayer(my, any, any2, 1, k1, k2);
}

void gameRules() {																// ������� ������ ������ ����
	FILE* f;
	char* str = (char*)calloc(255, sizeof(char));
	fopen_s(&f, "RulesOfGame.txt", "r");
	if (!check_open_file(f)) {
		printf("\n������, ������������� ���������.");
		exit(404);
	}
	printf("\n");
	while (fgets(str, 255, f)) {
		printf("%s", str);
	}
	printf("\n\n");
	fclose(f);
}

void positions(char** my) {												// ������� ����������� �������� �������
	ships pal;
	int type;
	int a = 10, g;														// �-���-�� �������� ������� ����� ����������
	int l1, l2, n1, n2;													// ��������� � ������ ������� ���� ������� ������� l-�����, n-�����
	char* str = (char*)malloc(6 * sizeof(char));
	system("cls");
	vivod(my);															// ������ ������� ����
	while (a != 0) {
		do {
			do {
				printf("��� ����� ���������� ������� �����:\n");
				printf("1. ���� ��������-%d\n", pal.one);
				printf("2. 2-� ��������-%d\n", pal.two);
				printf("3. 3-� ��������-%d\n", pal.three);
				printf("4. 4-� ��������-%d\n", pal.four);
				printf("�������� ��� �������: ");
				g = 0;
				type = Input(1, 4);
				switch (type) {
				case 1: if (pal.one == 0) {
					printf("������ ��� ������� ��������� �����������\n");
					g = 1;
				} break;
				case 2: if (pal.two == 0) {
					printf("������ ��� ������� ��������� �����������\n");
					g = 1;
				} break;
				case 3: if (pal.three == 0) {
					printf("������ ��� ������� ��������� �����������\n");
					g = 1;
				} break;
				case 4: if (pal.four == 0) {
					printf("������ ��� ������� ��������� �����������\n");
					g = 1;
				} break;
				}
			} while (g);
			printf("������� ���������� ������, ���� �� ������ ��� ���������(������ �6-�9): ");
			rewind(stdin);
			fgets(str, 6, stdin);
			l1 = str[0] - 'A';
			l2 = str[3] - 'A';
			n1 = str[1] - '0';
			n2 = str[4] - '0';
		} while (!proverka(my, l1, l2, n1, n2, type));					// �������� ����� �� ��������� ������� �� ��� �����
		system("cls");
		postanovka(my, l1, l2, n1, n2);									// �������� ������� � ������ �����
		switch (type) {
		case 1: pal.one--; break;
		case 2: pal.two--; break;
		case 3: pal.three--; break;
		case 4: pal.four--; break;
		}
		printf("������� ������� ���������!\n");
		vivod(my);
		a--;
	}
	printf("������� ������� �����������!\n");
	printf("���������� ���� - 1 / ���������� ������� ������ - 2\n");
	g = Input(1, 2);
	if (g == 2) {
		for (int i = 0; i < 10; i++)
			for (int k = 0; k < 10; k++)
				my[i][k] = ' ';
		printf("����������� �������� ������� - 1 / ����������� � ������� ������� - 2\n");
		g = Input(1, 2);
		if (g == 1)
			positions(my);
		else if (g == 2)
			randomposition(my, true);
	}
	system("cls");
}

bool proverka(char** my, int l1, int l2, int n1, int n2,int len) {					// ������� �������� ���������� �������
	if (l1 < 0 || l1>9 || l2 < 0 || l2>9 || n1 < 0 || n1>9 || n2 < 0 || n2>9) {
		printf("�������� ��������� �� ��������:\n ");
		return false;
	}
	if (l1 != l2 && n1 != n2) {
		printf("�������� ��������� �� ��������:\n ");
		return false;
	}
	if (l2 - l1 != len - 1 && n2 - n1 != len-1) {
		printf("�������� ��������� �� ��������:\n ");
		return false;
	}
	if (len == 1 && (l1 != l2 || n1 != n2)) {
		printf("�������� ��������� �� ��������:\n ");
		return false;
	}
	if (l2 == l1) {
		for (int i = n1; i < n2 + 1; i++) {
			if (my[i][l1] != ' ') {
				printf("�������� ��������� �� ��������:\n");
				return false;
			}
			if (l1 != 9)
				if (my[i][l1 + 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (l1 != 0)
				if (my[i][l1 - 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (i != 9)
				if (my[i + 1][l1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (i != 0)
				if (my[i - 1][l1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (l1 != 9 && i != 9)
				if (my[i + 1][l1 + 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (l1 != 9 && i != 0)
				if (my[i - 1][l1 + 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (l1 != 0 && i != 9)
				if (my[i + 1][l1 - 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

			if (l1 != 0 && i != 0)
				if (my[i - 1][l1 - 1] != ' ') {
					printf("�������� ��������� �� ��������:\n");
					return false;
				}

		}
	}
	if (n2 == n1) {
		for (int i = l1; i < l2 + 1; i++) {
			if (my[n1][i] != ' ') {
				printf("�������� ��������� �� ��������\n");
				return false;
			}
			if (i != 9)
				if (my[n1][i + 1] != ' ') {
					printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (i != 0)
				if (my[n1][i - 1] != ' ') {
					printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 9)
				if (my[n1 + 1][i] != ' ') {
					printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 0)
				if (my[n1 - 1][i] != ' ') {
					printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 9 && i != 9)
				if (my[n1 + 1][i + 1] != ' ') {
				printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 0 && i != 9)
				if (my[n1 - 1][i + 1] != ' ') {
				printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 9 && i != 0)
				if (my[n1 + 1][i - 1] != ' ') {
				printf("�������� ��������� �� ��������\n");
					return false;
				}

			if (n1 != 0 && i != 0)
				if (my[n1 - 1][i - 1] != ' ') {
				printf("�������� ��������� �� ��������\n");
					return false;
				}
		}
	}
	return true;
}

void postanovka(char** my, int l1, int l2, int n1, int n2) {			// ������� �������� ������� � ����� ������
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

void randomposition(char** any, bool fl) {			// ���� fl-1 ������ ��� ������������, ���� fl-0 ������ ��� ����
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
			if (rand() % 2 == 0) {					// ������� ����������� ��������� ��� ����������� (�����������)
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
		} while (!proverka(any, l1, l2, n1, n2, len));	// �������� ����� �� ��������� ������� � ���� �����
		system("cls");
		postanovka(any, l1, l2, n1, n2);				// ������ �������
	}
	printf("������� ������� �����������!\n");
	if (fl) {
		printf("������ ����������� ����������� ����� ��������? 1 - �� / 2 - ���\n");
		int k = Input(1, 2);
		if (k == 1) {
			vivod(any);
			printf("���������� ���� - 1 / ���������� ������� ������ - 2\n");
			k = Input(1, 2);
			if (k == 2) {
				for (int i = 0; i < 10; i++)
					for (int k = 0; k < 10; k++)
						any[i][k] = ' ';
				printf("����������� �������� ������� - 1 / ����������� � ������� ������� - 2\n");
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

void twoplayers(char** my, char** any, char** my2, char** any2, int player, int a, int b) {	// ������� ���� �� ��� ������
	printf("\n��� ���� ����� ��������� �������� ���� �������: '*'");
	do {
		if (player == 0 || player == 1) {						// ���� player=0-������ ����� ����/���� player=1-����� ������ �����/���� player=2- ����� 2 �����
			pole(my2, any2);									// ����� ���� ������� �����
			printf("��� ������� ������: ");
			while (attak(any, any2, &b, 1, my, &a)) {			// ���� true-���� ���������
				pole(my2, any2);
				if (b == 0)
					break;
				printf("\n����� ������ �����: ");
			}
			if (b == 0)
				break;
			printf("\n�� �����, ��� ��������� �� ������� ������\n");
		}
		player = 0;
		pole(my2, any2);
		printf("\n��� ������� ������: ");
		while (attak(my, my2, &a, 2, any, &b)) {
			pole(my2, any2);
			if (a == 0)
				break;
			printf("\n����� ������ �����: ");
		}
		if (a == 0)
			break;
		printf("\n�� �����, ��� ��������� � ������� ������\n");
	} while (a != 0 && b != 0);
	if (a == 0) {
		printf("\n������� ������ �����!");
	}
	else
		printf("\n������� ������ �����!");
	printf("\n�������, ������� �� ���� ����� �������� ������");
	pole(my, any);
	printf("\n�� �������, ��������!\n");
}

bool attak(char** pole1, char** pole2, int* k, int player, char** any, int* k2) {	// ������� �����
	char letter;
	int let;
	int num;
	bool m;
	do {
		rewind(stdin);
		letter = getchar();
		if (letter == '*') {
			save_game(pole1, any, player, *k, *k2);						// ���� *-���������� ����
			printf("\n���������� ���� - 1 / ��������� ���� - 2\n");
			int a = Input(1, 2);
			if (a == 2) {
				exit(1);
			}
			else {
				printf("��� ���: ");
				letter = getchar();
			}
		}
		let = letter - 'A';
		scanf_s("%d", &num);
		m = proverkaHoda(pole1, num, let);								// ��������, ����� �� ������ � ��� ������
	} while (!m);
	system("cls");
	printf("��� ���: %c%d", letter, num);
	if (pole1[num][let] == ' ') {										// ���� ������ ���� ������, ������ *
		pole1[num][let] = '*';
		pole2[num][let] = '*';
		return false;
	}
	if (pole1[num][let] == '0') {										// ���� � ������ ��� �������, ������ �
		printf("\nE��� ���������!");
		pole1[num][let] = 'X';
		pole2[num][let] = 'X';
		proverkaNaKill(pole1, pole2, num, let, k);
		return true;
	}
}

void botplayer(char** my, char** any, char** any2, int player, int a, int b) {		// ������� ���� � �����
	if (player == 0)
		randomposition(any, false);													// ��������� ����������� �������� ����
	pole(my, any2);
	do {
		printf("\n��� ���: ");
		while (attak(any, any2, &b, 1, my, &a)) {
			pole(my, any2);
			if (b == 0)
				break;
			printf("\n��� ���: ");
		}
		if (b == 0)
			break;
		printf("\n�� �����, ����� ���������: ");				
		while (attak_bot(my, &a)) {
			pole(my, any2);
			system("pause");
			system("cls");
			if (a == 0)
				break;
			printf("\n����� ���������: ");
		}
		if (a == 0)
			break;
		pole(my, any2);
		printf("\n��������� �� �����, ��� ���: \n");
	} while (a != 0 && b != 0);
	if (a == 0) {
		printf("\n������� ���������!");
	}
	else
		printf("\n������� �����!");
	printf("\n�������, ������� �� ���� ����� �������� �������");
	pole(my, any);
	printf("\n�� �������, �������!");
}

bool attak_bot(char** pol, int* k) {					// ������� ����� ����
	int num, let;
	bool x = false;
	for (int i = 0; i < 10; i++)
		for (int j = 0; j < 10; j++)
			if (pol[i][j] == 'X') {						// �������� ���� �� �������� �������
				x = true;
				num = i;
				let = j;
			}
	if (x) {										
		obstrelShip(pol, &num, &let);					// ������� �������� ������ ��������� �������
	}
	else {												// ���� ��������� ������� ���, ����� ��������� �������
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
		printf("\n� ��� ������� ������!");
		pol[num][let] = 'X';
		proverkaNaKill(pol, pol, num, let, k);			// ������� �������� ����� �� �������, ��� �������
		return true;
	}
}

void obstrelShip(char** pol, int* num, int* let) {							// ������� �������� ��������� ������� �����					
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

	// ���� ��������
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
		i = rand() % 2;								// i=1 ����� �� num
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
		i = rand() % 2;								// i=1 ����� �� num
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
		i = rand() % 2;								// i=1 ����� �� num
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
		i = rand() % 2;								// i=1 ����� �� num
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

bool proverkaHoda(char** pol, int num, int num2) {		// ������� �������� ������������ ��������� ����
	if (num < 0 || num>9 || num2 < 0 || num2>9) {
		printf("����������� ������ ��������� ����, ���������� ��� ���: ");
		return false;
	}
	if (pol[num][num2] == ' ' || pol[num][num2] == '0')
		return true;
	printf("�� ��� �������� � ��� ������, ���������� ��� ���: ");
	return false;
}

void starKill(char** pol, char** pol2, int num, int let) {			// ������� ����������� ���������, ��� �������� �������
	pol2[num][let] = '#';
	pol[num][let] = '#';
	if (num < 9) {
		if (pol[num + 1][let] == 'X')
			starKill(pol, pol2 ,num + 1, let);						// ����������� �����������
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

bool proverkaNaKill(char** pol, char** pol2, int num, int let, int* k) {	// ������� ����������� ���� �������, ��� ������
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
	printf("������� ����!");
	(*k)--;
	starKill(pol, pol2, num, let);							// ������� ������� ����������� ��������� ������ ������� �������
	return true;
}

bool check_open_file(FILE* f) {			// ������� �������� ������ �� ����
	if (f == NULL) {
		printf("\n�� ������� ����� ����, ���������� ��� ���");
		return false;
	}
	return true;
}

void save_game(char** my, char** any, int player, int k1, int k2) {		// ������� ���������� ����
	FILE* f;
	char* name = (char*)calloc(30, sizeof(char));
	printf("\n������� ��� �����: ");
	rewind(stdin);
	fgets(name, 30, stdin);
	int i;
	for (i = 0; name[i] != '\n'; i++);
	name[i] = '\0';
	fopen_s(&f, name, "wb");
	fwrite(&player, sizeof(int), 1, f);
	if (player == 1) {													// player-������ ������, ������� �����
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

void return_game(char** my, char** any, char** my2, char** any2, int* player, int* k1, int* k2) {	// ������� ������������� ����
	FILE* f;
	char* name = (char*)calloc(30, sizeof(char));
	do {
		printf("\n������� ��� �����: ");
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

void free_mem(char** my, char** any, char** my2, char** any2) {		// ������� ������� ������
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