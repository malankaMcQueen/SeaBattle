#include "Header.h"


int main()
{
	srand(time(NULL));
	setlocale(LC_ALL, "Ru");
	char** my, ** any, ** my2, ** any2;
	int a;
	do {
		add_memory(&my, &any, &my2, &any2);						// ��������� ������ ��� ������� ����
		do {
			printf("���� ����:\n������ ����� ���� �� 2� ������� - 1\n������ ����� ���� ������ ���� - 2\n����������� ������������ ���� �� ���� ������� - 3\n����������� ������������ ���� ������ ���� - 4\n������� ���� - 5\n");
			a = Input(1, 5);
			system("cls");
			switch (a) {
			case 1: newGameTwoPlayer(my, any, my2, any2);		// ������ ����� ���� �� ��� ������
				break;
			case 2:	newGameBot(my, any, my2, any2);				// ������ ����� ���� ������ ����
				break;
			case 3: restartTwoPlayer(my, any, my2, any2);		// ������ ������������ ���� �� ��� ������
				break;
			case 4:	restartGameBot(my, any, my2, any2);			// ������ ������������ ���� ������ ����
				break;
			case 5: gameRules();								// ������� ����
			}
		} while (a == 5);
		free_mem(my, any, my2, any2);							// ������� ������� ������
		printf("\n��������� ����� ���� - 1 / ����� �� ��������� - 2\n");
		a = Input(1, 2);
	} while (a == 1);
	return 0;
}