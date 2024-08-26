#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>

using namespace std;

enum direction {
	STOP = 0, RIGHT, 
	LEFT, UP, DOWN
};


void Setup(direction &dir, bool &gameover, int &head_x, int &head_y, int &x, int &y, int &food_x, int &food_y, int &score,
	const int HEIGHT, const int WIDTH, int(&field)[20][20])
{
	dir = STOP;
	gameover = 0;
	head_x = HEIGHT / 2;
	head_y = WIDTH / 2;
	field[head_x][head_y] = 1;
	food_x = rand() % WIDTH;
	food_y = rand() % HEIGHT;
	field[food_y][food_x] = -1;
	score = 0;

}

void Draw(int head_y, int head_x, int score, const int WIDTH, const int HEIGHT, int(&field)[20][20])
{
	system("cls");
	for (size_t i = 0; i < WIDTH * 3 + 2; i++)
	{
		cout << "=";
	}
	cout << endl;
	for (size_t i = 0; i < HEIGHT; i++)
	{
		cout << "|";
		for (size_t j = 0; j < WIDTH; j++)
		{
			if (i == head_y and j == head_x) cout << " @ ";
			else if (field[i][j] == -1) cout << " F ";
			else if (!field[i][j]) cout << " . ";
			else if (field[i][j] > 0) cout << " o ";
			
		}
		cout << "|" << endl;
	}

	for (size_t i = 0; i < WIDTH * 3 + 2; i++)
	{
		cout << "=";
	}
	cout << endl;

	cout << "score = " << score << endl;

}

void Input(direction &dir, direction & prev_dir)
{
	prev_dir = dir;
	if (_kbhit())
	{
		switch (_getch())
		{
		case ('a'):
			if (prev_dir != RIGHT) dir = LEFT;
			break;
		case ('w'):
			if (prev_dir != DOWN) dir = UP;
			break;
		case ('d'):
			if (prev_dir != LEFT) dir = RIGHT;
			break;
		case ('s'):
			if (prev_dir != UP) dir = DOWN;
			break;
		}
	}
}

void Logic(int& x, int& y, int& head_x, int& head_y, direction dir, bool& gameover, int& food_x, int& food_y, int& score, 
	const int HEIGHT, const int WIDTH, int(&field)[20][20])
{
	x = head_x;
	y = head_y;

	switch (dir)
	{
	case RIGHT:
		head_x++;
		break;
	case LEFT:
		head_x--;
		break;
	case UP:
		head_y--;
		break;
	case DOWN:
		head_y++;
		break;
	}
		
	//borders
	if (head_x > WIDTH - 1) head_x = 0;
	if (head_x < 0) head_x = WIDTH - 1;
	if (head_y > HEIGHT - 1) head_y = 0;
	if (head_y < 0) head_y = HEIGHT - 1;

	//gameover
	if (field[head_y][head_x] > 0 and dir != STOP) {
		gameover = 1;
		return;
	}

	//food spawning, skipping logic of deleting end 
	if (head_x == food_x and head_y == food_y)
	{

		food_x = rand() % (WIDTH - 1); 
		food_y = rand() % (HEIGHT - 1);
		while (field[food_y][food_x] != 0)
		{
			food_x = rand() % (WIDTH - 1);
			food_y = rand() % (HEIGHT - 1);
		}
		field[food_y][food_x] = -1;
		score++;
		field[head_y][head_x] = 1 + score;
		return;
	}

	//deleting previous position of head (end of snake)
	field[head_y][head_x] = 1 + score;
	field[y][x] = score;
	for (int i = 0; i < score; i++)
	{
		if (y != HEIGHT - 1 and field[y + 1][x] == field[y][x] and field[y + 1][x] > 0)
		{
			field[y + 1][x] = field[y][x] - 1;
			y++;
		}
		else if (y != 0 and field[y - 1][x] == field[y][x] and field[y - 1][x] > 0)
		{
			field[y - 1][x] = field[y][x] - 1;
			y--;
		}
		else if (x != WIDTH - 1 and field[y][x + 1] == field[y][x] and field[y][x + 1] > 0)
		{
			field[y][x + 1] = field[y][x] - 1;
			x++;
		}
		else if (x != 0 and field[y][x - 1] == field[y][x] and field[y][x - 1] > 0)
		{
			field[y][x - 1] = field[y][x] - 1;
			x--;
		}
		else if (x != 0 and field[y][0] == field[y][x] and field[y][0] > 0)
		{
			field[y][0] = field[y][x] - 1;
			x = 0;
		}
		else if (x != WIDTH - 1 and field[y][WIDTH - 1] == field[y][x] and field[y][WIDTH - 1] > 0)
		{
			field[y][WIDTH - 1] = field[y][x] - 1;
			x = WIDTH - 1;
		}
		else if (y != 0 and field[0][x] == field[y][x] and field[0][x] > 0)
		{
			field[0][x] = field[y][x] - 1;
			y = 0;
		}
		else if (y != HEIGHT - 1 and field[HEIGHT - 1][x] == field[y][x] and field[HEIGHT - 1][x] > 0)
		{
			field[HEIGHT - 1][x] = field[y][x] - 1;
			y = HEIGHT - 1;
		}
	}
}

int main()
{
	int x, y, head_x, head_y,
	food_x, food_y, score;
	bool gameover;
	direction dir, prev_dir;
	const int HEIGHT = 20;
	const int WIDTH = 20;
	int field[HEIGHT][WIDTH] = { 0 };
	Setup(dir, gameover, head_x, head_y, x, y, food_x, food_y, score, HEIGHT, WIDTH, field);
	while (!gameover)
	{
		Draw(head_y, head_x, score, WIDTH, HEIGHT, field);
		Input(dir, prev_dir);
		Logic(x, y, head_x, head_y, dir, gameover, food_x, food_y, score, HEIGHT, WIDTH, field);
		Sleep(70);
	}
	return 0;
}


