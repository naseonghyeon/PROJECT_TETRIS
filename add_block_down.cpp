#include<stdio.h>
#include<Windows.h>
#include<time.h>

//********************
// �Լ� ����
//********************
int init(); // ���� ���� �ʱ�ȭ
int total_gameboard(); // �׿��ִ� ����� ȭ�鿡 ǥ��
int goto_xy(int x, int y); // Ŀ���� �ű�� �Լ�
int show_cur_block(int shape, int angle, int x, int y); // ���� ���Ǵ� ����� ����� ������
int make_shape(); // ��� ����� ��ȣ(0~6��)�� �������� ��ȯ

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
}; // ��� ����� ������ �迭
int block_shape, block_angle, block_x, block_y;
int ab_x, ab_y; // ȭ���� ����� ��Ÿ���� ��ǥ�� ���� ��ġ


int main() {
	init();
	while (1) {
		total_gameboard();
		block_shape = make_shape();
		//block_start(block_shape, &block_angle, &block_x, &block_y);
		show_cur_block(block_shape, block_angle, block_x, block_y);
		//move_block(&block_shape, &block_angle, &block_x, &block_y);
		(block_y)++;
		if (block_y == 21)
			break;

		goto_xy(77, 23);
		Sleep(15);
		goto_xy(77, 23);
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
	int shape;

	shape = rand() % 7;

	return shape;
}