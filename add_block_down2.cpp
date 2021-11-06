#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

//********************
// �Լ� ����
//********************
int init(); // ���� ���� �ʱ�ȭ
int total_gameboard(); // �׿��ִ� ������ ȭ�鿡 ǥ��
int goto_xy(int x, int y); // Ŀ���� �ű�� �Լ�
int show_cur_block(int shape, int angle, int x, int y); // ���� ���Ǵ� ������ ����� ������
int make_shape(); // ���� ����� ��ȣ(0~6��)�� �������� ��ȯ
int block_start(); // ������ ó�� ���� ��ǥ ����
int erase_cur_block(int shape, int angle, int x, int y);
int move_block(int* shape, int* angle, int* x, int* y); // ������ ������ �������� �ϴ� �Լ�
bool check_crush(int x, int y); // ������ ���Ӻ���� ��Ҵ��� �ƴ��� Ȯ���ϴ� �Լ�

//********************
// ���� ����
//********************-
int gameboard[21][14]; // �������� ������ �迭
int blocks[7][4][4][4] = {
	// �⺻ ���, �������� 1ȸ ȸ��, 2ȸ ȸ��, 3ȸ ȸ��

	// ���� ���
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,

	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,0,0,0,
	1,0,0,0,

	1,1,1,1,
	0,0,0,0,
	0,0,0,0,
	0,0,0,0,

	// '��' ���
	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,1,0,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	// '��' ���
	0,1,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,

	1,1,1,0,
	0,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,

	// '��' ���
	1,1,0,0,
	0,1,0,0,
	0,1,0,0,
	0,0,0,0,

	1,1,1,0,
	1,0,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,0,0,0,
	1,1,0,0,
	0,0,0,0,

	0,0,1,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,

	// '��' ���
	1,1,0,0,
	1,0,0,0,
	1,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	0,1,0,0,
	1,1,0,0,
	0,0,0,0,

	1,1,1,0,
	0,0,1,0,
	0,0,0,0,
	0,0,0,0,

	// 'Z' ���
	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	1,1,0,0,
	0,1,1,0,
	0,0,0,0,
	0,0,0,0,

	0,1,0,0,
	1,1,0,0,
	1,0,0,0,
	0,0,0,0,

	// 'S' ���
	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0,

	0,1,1,0,
	1,1,0,0,
	0,0,0,0,
	0,0,0,0,

	1,0,0,0,
	1,1,0,0,
	0,1,0,0,
	0,0,0,0
}; // ���� ����� ������ �迭
int block_shape, block_angle, block_x, block_y;
int ab_x, ab_y; // ȭ���� ������ ��Ÿ���� ��ǥ�� ���� ��ġ


int main() {
	init();
	block_start();
	while (1) {
		total_gameboard();
		show_cur_block(block_shape, block_angle, block_x, block_y);
		move_block(&block_shape, &block_angle, &block_x, &block_y);

		goto_xy(77, 23);
		Sleep(15);
		goto_xy(77, 23);
		init();
	}

	return 0;
}

int init() {
	int i, j;

	srand((unsigned)time(NULL));

	for (i = 0; i < 20; i++) {
		for (j = 0; j < 14; j++) {
			if ((j == 0) || (j == 13)) {
				gameboard[i][j] = 1;
			}
			else {
				gameboard[i][j] = 0;
			}
		}
	}

	for (j = 0; j < 14; j++) {
		gameboard[20][j] = 1;
	}

	ab_x = 5;
	ab_y = 1;

	return 0;
}

int total_gameboard() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 14; j++) {
			goto_xy((j * 2) + ab_x, i + ab_y);
			if (gameboard[i][j] == 1)
				printf("��");
			else
				printf("  ");
		}
	}
	goto_xy(77, 23);
	return 0;
}

int goto_xy(int x, int y) {
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.Y = y;
	pos.X = x;
	SetConsoleCursorPosition(hConsole, pos);
	return 0;
}

int show_cur_block(int shape, int angle, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if ((j + y) < 0)
				continue;

			if (blocks[shape][angle][j][i] == 1) {
				goto_xy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("��");
			}
		}
	}
	goto_xy(77, 23);
	return 0;
}

int make_shape() {
	block_shape = rand() % 7;

	return block_shape;
}

int block_start() {
	block_x = 5;
	block_y = -3;
	block_angle = 0;

	make_shape();
	return 0;
}

int erase_cur_block(int shape, int angle, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[shape][angle][j][i] == 1) {
				goto_xy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("  ");
			}
		}
	}
	return 0;
}

int move_block(int* shape, int* angle, int* x, int* y) {
		if (check_crush(*x, *y) == 1) {
			block_start();
			show_cur_block(block_shape, block_angle, block_x, block_y);
			return 2;
		}
		else
			(*y)++;
		return 0;
}

bool check_crush(int x, int y) {
	if (gameboard[y][x] == 1) {
		return true;
	}
	return false;
}