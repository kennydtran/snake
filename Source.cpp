#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

bool gameover;
const int height = 20;
const int width = 30;
int x,
y,
fx,
fy,
score;
int tailx[100],
taily[100],
tail; //length of tail

void run();
void board();
void ui();
void movement();
void movementHard();
void gameeasy();

enum direction {
	STOP = 0, UP, DOWN, LEFT, RIGHT
};
direction MOVE;

int main() {
	char selection;
	char quit;
	do {
		cout << "ooooooooooooooooooooooooO" << endl <<
			"          SNAKE          " << endl << "Ooooooooooooooooooooooooo" << endl;
		cout << endl << "Choose a difficulty:" << endl;
		cout << endl << "EASY" << endl << "HARD" << endl;
		
		cin >> selection;
		switch (selection){
		case 'e':
			gameeasy();
			/*do {
				system("CLS");
				run();
				while (!gameover) {
					board();
					ui();
					movement();
				}
				system("CLS");
				cout << "GAME OVER" << endl;
				cout << endl << "Score: " << score << endl << endl << endl;
				cout << "ENTER ANY KEY TO PLAY AGAIN" << endl;
				cout << "ENTER 'M' FOR MAIN MENU" << endl;
				cin >> quit;
				system("CLS");
			} while (quit != 'M' && quit != 'm');
			system("CLS");*/
			break;
		case 'h':
			do {
				system("CLS");
				run();
				while (!gameover) {
					board();
					ui();
					movementHard();
				}
				system("CLS");
				cout << "GAME OVER" << endl;
				cout << endl << "Score: " << score << endl << endl << endl;
				cout << "ENTER ANY KEY TO PLAY AGAIN" << endl;
				cout << "ENTER 'M' FOR MAIN MENU" << endl;
				cin >> quit;
				system("CLS");
			} while (quit != 'M' && quit != 'm');
			system("CLS");
			break;
		default:
			system("CLS");
			cout << "INVALID INPUT" << endl << endl;
		}
		
	} while (selection != 'q' && selection != 'Q');
	system("CLS");
	cout << "Thanks for playing!" << endl << endl << " . . . SHUTTING DOWN . . . ";
	system("pause>nul");
	return 0;
}

void run() {
	gameover = false;
	x = width / 2;
	y = height / 2;
	fx = rand() % width;
	fy = rand() % height;
	MOVE = STOP;
	score = 0;
}

void board() {
	system("CLS");
	//top
	for (int i = 0; i < width; i++) {
		cout << "=";
	} cout << endl;
	//width and height
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			if (j == 0 || j == width - 1) {
				cout << "|";
			}
			else if (i==y && j==x) {
				cout << "O";
			}
			else if (i == fy && j == fx) {
				cout << "&";
			}
			else {
				bool print = false;
				for (int k = 0; k < tail; k++) {
					if (tailx[k] == j && taily[k] == i) {
						cout << "o";
						print = true;
					}
				}
				if (!print)
				cout << " ";
			}
		}cout << endl;
	}
	//bottom
	cout << "|";
	for (int i = 0; i < width - 1; i++) {
		cout << "=";
	} cout << endl;
	cout << endl << "Score: " << score;
}

void ui() {
	//user input
	if (_kbhit()) {
		switch (_getch()) {
		case 'w' :
			MOVE = UP;
			break;
		case 's' :
			MOVE = DOWN;
			break;
		case 'a' :
			MOVE = LEFT;
			break;
		case 'd' :
			MOVE = RIGHT;
			break;
		default:
			break;
		}
	}
}

void movement() {
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++) {
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	//movement
	switch (MOVE) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	//mirror snake
	if (x > width - 2)
		x = 1;
	else if (x < 1)
		x = width - 2;
	else if (y >= height)
		y = 0;
	else if (y < 0)
		y = height - 1;
	for (int i = 0; i < tail; i++) {
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}
	//snake eat fruit
	if (x == fx && y == fy) {
		score++;
		fx = rand() % width;
		fy = rand() % height;
		tail++;
	}
	//fruit hiding in border fix
	if (fx > width - 2)
		fx = 1;
	else if (fx < 1)
		fx = width - 2;
	else if (fy >= height)
		fy = 0;
	else if (fy < 0)
		fy = height - 1;
}

void movementHard() {
	int prevx = tailx[0];
	int prevy = taily[0];
	int prev2x, prev2y;
	tailx[0] = x;
	taily[0] = y;
	for (int i = 1; i < tail; i++) {
		prev2x = tailx[i];
		prev2y = taily[i];
		tailx[i] = prevx;
		taily[i] = prevy;
		prevx = prev2x;
		prevy = prev2y;
	}
	//movement
	switch (MOVE) {
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	default:
		break;
	}
	//hard wall
	if (x == width || x == 0 || y >= height || y < 0) {
		gameover = true;
	}
	for (int i = 0; i < tail; i++) {
		if (tailx[i] == x && taily[i] == y)
			gameover = true;
	}
	//snake eat fruit
	if (x == fx && y == fy) {
		score++;
		fx = rand() % width;
		fy = rand() % height;
		tail++;
	}
	//fruit hiding in border fix
	if (fx > width - 2)
		fx = 1;
	else if (fx < 1)
		fx = width - 2;
	else if (fy >= height)
		fy = 0;
	else if (fy < 0)
		fy = height - 1;
}

void gameeasy() {
	char selection;
	char quit;
	do {
		system("CLS");
		run();
		while (!gameover) {
			board();
			ui();
			movement();
		}
		system("CLS");
		cout << "GAME OVER" << endl;
		cout << endl << "Score: " << score << endl << endl << endl;
		cout << "ENTER ANY KEY TO PLAY AGAIN" << endl;
		cout << "ENTER 'M' FOR MAIN MENU" << endl;
		cin >> quit;
		system("CLS");
	} while (quit != 'M' && quit != 'm');
	system("CLS");
}