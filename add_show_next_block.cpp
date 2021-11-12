#include <stdio.h>
#include <Windows.h>
#include <time.h>
#include <conio.h>

#define EXT_KEY	0xffffffe0
#define	KEY_LEFT	75
#define KEY_RIGHT	77
#define KEY_UP	72
#define KEY_DOWN	80
#define KEY_SPACE	32

//********************
// 함수 선언
//********************
int init_board();
int init(); // 각종 변수 초기화
int total_gameboard(); // 쌓여있는 블록을 화면에 표시
int goto_xy(int x, int y); // 커서를 옮기는 함수
int show_cur_block(int shape, int angle, int x, int y); // 현재 사용되는 블록의 모양을 보여줌
int make_shape(); // 블록 모양의 번호(0~6번)를 랜덤으로 반환
int block_start(); // 블록의 처음 시작 좌표 지정
int erase_cur_block(int shape, int angle, int x, int y);
int move_block(int* shape, int* angle, int* x, int* y); // 블록이 밑으로 내려가게 하는 함수
bool check_crush(int shape, int angle, int x, int y); // 블록이 게임보드와 닿았는지 아닌지 확인하는 함수
int merge_block(int shape, int angle, int x, int y);
void input_key();
int remove_line();
void SetColor(int color);
int make_next_shape();
int show_next_block(int shape);
void clear_game();


//********************
// 구조체 선언
//********************
enum{
	BLACK = 0,      /*  0 : 까망 */
	DARK_BLUE,    /*  1 : 어두운 파랑 */
	DARK_GREEN,    /*  2 : 어두운 초록 */
	DARK_SKY_BLUE,  /*  3 : 어두운 하늘 */
	DARK_RED,    /*  4 : 어두운 빨강 */
	DARK_VOILET,  /*  5 : 어두운 보라 */
	DARK_YELLOW,  /*  6 : 어두운 노랑 */
	GRAY,      /*  7 : 회색 */
	DARK_GRAY,    /*  8 : 어두운 회색 */
	BLUE,      /*  9 : 파랑 */
	GREEN,      /* 10 : 초록 */
	SKY_BLUE,    /* 11 : 하늘 */
	RED,      /* 12 : 빨강 */
	VOILET,      /* 13 : 보라 */
	YELLOW,      /* 14 : 노랑 */
	WHITE,      /* 15 : 하양 */
};

//********************
// 변수 선언
//********************
int gameboard[21][14]; // 게임판을 구현한 배열
int blocks[7][4][4][4] = {
	// 기본 모양, 왼쪽으로 1회 회전, 2회 회전, 3회 회전

	// 막대 모양
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

	// 'ㅁ' 모양
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

	// 'ㅓ' 모양
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

	// 'ㄱ' 모양
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

	// 'ㄴ' 모양
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

	// 'Z' 모양
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

	// 'S' 모양
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
}; // 블록 모양을 구현한 배열
int block_shape, block_angle, block_x, block_y, next_shape;
int ab_x, ab_y; // 화면중 블록이 나타나는 좌표의 절대 위치
int key; // 키 입력값을 받음
clock_t startDropT, endT, startGroundT;
int line = 1;


int main(int argc, char* argv[]) {
	init_board();
	init();
	startDropT = clock();
	make_shape();
	block_start();
	while (true) {
		total_gameboard();
		show_cur_block(block_shape, block_angle, block_x, block_y);
		move_block(&block_shape, &block_angle, &block_x, &block_y);
		show_next_block(next_shape);
		input_key();
		
		goto_xy(77, 23);
		Sleep(15);
		goto_xy(77, 23);
	}
	return 0;
}

int init_board() {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 14; j++) {
			if ((j == 0) || (j == 13)) {
				gameboard[i][j] = 1;
			}
			else {
				gameboard[i][j] = 0;
			}
		}
	}

	for (int j = 0; j < 14; j++) {
		gameboard[20][j] = 1;
	}
	return 0;
}

int init() {
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = 0;
	cursorInfo.dwSize = 1;
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &cursorInfo);
	srand((unsigned)time(NULL));

	ab_x = 5;
	ab_y = 1;

	return 0;
}

int total_gameboard() {
	for (int i = 0; i < 21; i++) {
		for (int j = 0; j < 14; j++) {
			if (j == 0 || j == 13 || i == 20)
				SetColor(DARK_BLUE);
			else
				SetColor(DARK_GRAY);
			goto_xy((j * 2) + ab_x, i + ab_y);
			if (gameboard[i][j] == 1)
				printf("■");
			else
				printf("  ");
		}
	}

	SetColor(WHITE);
	goto_xy(35, 10);
	printf("LINES : %d", line);

	SetColor(BLACK);
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

	switch (shape)
	{
	case 0:
		SetColor(RED);
		break;
	case 1:
		SetColor(BLUE);
		break;
	case 2:
		SetColor(SKY_BLUE);
		break;
	case 3:
		SetColor(WHITE);
		break;
	case 4:
		SetColor(YELLOW);
		break;
	case 5:
		SetColor(VOILET);
		break;
	case 6:
		SetColor(GREEN);
		break;
	}

	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {

			if ((j + y) < 0)
				continue;

			if (blocks[shape][angle][j][i] == 1) {
				goto_xy((i + x) * 2 + ab_x, j + y + ab_y);
				printf("■");
			}
		}
	}
	SetColor(BLACK);
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

	block_shape = next_shape;
	make_next_shape();
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
	endT = clock();
	if ((float)(endT - startDropT) >= 800) {
		(*y)++;
		if (check_crush(*shape, *angle, *x, *y) == true) {
			if (*y < 0) {
				return 1;
			}
			(*y)--;
			merge_block(*shape, *angle, *x, *y);
			block_start();
			return 2;
		}
		startDropT = clock();
	}
	return 0;
}

bool check_crush(int shape, int angle, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[shape][angle][j][i] == 1) {
				if (gameboard[j + y][i + x] == 1)
					return true;
			}
		}
	}
	return false;
}

int merge_block(int shape, int angle, int x, int y) {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			if (blocks[shape][angle][j][i] == 1)
				gameboard[j + y][i + x] = 1;
		}
	}
	remove_line();
	total_gameboard();
	return 0;
}

void input_key() {
	int game_check = 0;
	if (_kbhit()) {
		key = _getch();
		switch (key) {
		case KEY_UP:
			if (check_crush(block_shape, (block_angle + 1) % 4, block_x, block_y) == 0) {
				erase_cur_block(block_shape, block_angle, block_x, block_y);
				block_angle = (block_angle + 1) % 4;
				show_cur_block(block_shape, block_angle, block_x, block_y);
			}
			break;
		case KEY_RIGHT:
			if (block_x < 14) {
				erase_cur_block(block_shape, block_angle, block_x, block_y);
				block_x++;
				if (check_crush(block_shape, block_angle, block_x, block_y) == true) {
					block_x--;
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}
			break;
		case KEY_LEFT:
			if (block_x > 1) {
				erase_cur_block(block_shape, block_angle, block_x, block_y);
				block_x--;
				if (check_crush(block_shape, block_angle, block_x, block_y) == true) {
					block_x++;
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}
			break;
		case KEY_DOWN:
			if (block_y < 21) {
				erase_cur_block(block_shape, block_angle, block_x, block_y);
				block_y++;
				if (check_crush(block_shape, block_angle, block_x, block_y) == true) {
					block_y--;
					show_cur_block(block_shape, block_angle, block_x, block_y);
				}
			}
			break;
		case KEY_SPACE:
			while (1) {
				block_y++;
				if (check_crush(block_shape, block_angle, block_x, block_y) == true) {
					block_y--;
					break;
				}
			}
		}
		fflush(stdin);
	}
}

int remove_line() {
	int i, j, k;
	for (i = 0; i < 20; i++) {
		for (j = 1; j < 13; j++) {
			if (gameboard[i][j] == 0)
				break;
		}
		if (j == 13) {
			SetColor(BLUE);
			goto_xy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++) {
				printf("□");
				Sleep(10);
			}
			goto_xy(1 * 2 + ab_x, i + ab_y);
			for (j = 1; j < 13; j++) {
				printf("  ");
				Sleep(10);
			}

			line--;

			for (k = i; k > 0; k--) {
				for (j = 1; j < 13; j++) {
					gameboard[k][j] = gameboard[k - 1][j];
				}
			}
			if (line == 0) {
				clear_game();
			}
		}
	}
	return 0;
}

void SetColor(int color) {
	HANDLE std_output_handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(std_output_handle, color);
}

int make_next_shape() {
	next_shape = rand() % 7;

	return next_shape;
}

int show_next_block(int shape) {
	SetColor(DARK_GREEN);
	for (int i = 1; i < 9; i++) {
		goto_xy(34, i);
		for (int j = 0; j < 7; j++) {
			if (i == 1 || i == 8 || j == 0 || j == 6) {
				printf("■");
			}
			else
				printf("  ");
		}
	}
	show_cur_block(shape, 0, 16, 2);
	return 0;
}

void clear_game() {
	system("cls");

	SetColor(RED);
	goto_xy(15, 8);
	printf("┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓");
	goto_xy(15, 9);
	printf("┃****************************┃");
	goto_xy(15, 10);
	printf("┃*        GAME CLEAR!!      *┃");
	goto_xy(15, 11);
	printf("┃****************************┃");
	goto_xy(15, 12);
	printf("┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛");
	fflush(stdin);
	Sleep(3000);

	exit(1);
}