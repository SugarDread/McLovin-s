#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;

bool gameover;
const int WIDTH = 20;
const int HEIGHT = 20;
enum edir {STOP = 0, RIGHT, LEFT, UP, DOWN };
int x, y,
xFood, yFood,
score;
edir dir, lastdir;
int xEnd[100], yEnd[100];
int flag;

void Setup()
{
	gameover = false;
	dir = STOP;
	x = WIDTH / 2 - 1;
	y = HEIGHT/ 2 - 1;
	xFood = rand() % WIDTH;
	yFood = rand() % HEIGHT;
	score = 0;
}

void Draw()
{
	system("cls");
	for (int i = 0; i < WIDTH; i++) cout << "#";
	cout << endl;
	for (int i = 0; i < HEIGHT; i++)
	{
		for (int j = 0; j < WIDTH; j++)
		{
			
			if (j == 0 or j == WIDTH - 1)
			{
				cout << "#";
			}
			else if (i == y and j == x) cout << "@";
			//else if (i == yEnd[] and j == xEnd[]) cout << "@";
			else if (i == yFood and j == xFood) cout << "F";
			else
			{
				flag = 0;
				for (int k = 0; k < score; k++)
				{
					
					if (i == yEnd[k] and j == xEnd[k])
					{
						cout << "@";
						flag++;
					}
				}
				if (flag != 0)
				{
					flag--;
				}
				else
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
	for (int i = 0; i < WIDTH; i++) cout << "#";
	cout << endl;
	cout << "SCORE: " << score << endl;
	/*cout << x << '\t' << y << endl;
	cout << xEnd[0] << "\t" << yEnd[0] << endl;
	cout << xEnd[1] << "\t" << yEnd[1] << endl;
	cout << xEnd[2] << "\t" << yEnd[2] << endl;
	cout << xEnd[3] << "\t" << yEnd[3] << endl;*/

	
}

void Input()
{
	lastdir = dir;
	if (_kbhit())
	{
		switch (_getch())
		{
		case ('a'):
			dir = LEFT;
			break;
		case ('w'):
			dir = UP;
			break;
		case ('d'):
			dir = RIGHT;
			break;
		case ('s'):
			dir = DOWN;
			break;
		case (NULL):
			break;

		}
	}
}

void Logic()
{

	//движение
	switch (dir)
	{
	case RIGHT:
		x++;
		break;
	case LEFT:
		x--;
		break;
	case UP:
		y--;
		break;
	case DOWN:
		y++;
		break;
	}

	//остановка змейки если идет назад
	if (x == xEnd[0] and y == yEnd[0])
	{
		switch (dir)
		{
		case RIGHT:
			x--;
			break;
		case LEFT:
			x++;
			break;
		case UP:
			y++;
			break;
		case DOWN:
			y--;
			break;
		}
		dir = lastdir;
		return;
	}

	//gameover
	for (int i = 1; i < score; i++)
	{
		if (x == xEnd[i] and y == yEnd[i]) gameover = 1;
	}

	//копирование предыдущего элемента, физика тела
	int tempx = xEnd[0], tempy = yEnd[0],
		temp2x, temp2y;
	for (int i = 1; i < score; i++)
	{
		temp2x = xEnd[i];
		temp2y = yEnd[i];
		xEnd[i] = tempx;
		yEnd[i] = tempy;
		tempx = temp2x;
		tempy = temp2y;
	}

	//соприкосновене со стеной
	if (x == WIDTH - 1) x = 1;
	if (x == 0) x = WIDTH - 2;
	if (y == HEIGHT) y = 0;
	if (y == -1) y = HEIGHT - 1;


	//кушать
	if (x == xFood and y == yFood)
	{
		xFood = rand() % (WIDTH - 2) + 1;
		yFood = rand() % (HEIGHT - 2) + 1;
		score++;
	}
	
	//определение координат первому хвосту
	if (score > 0)
	{
		switch (dir)
		{
		case LEFT:
			xEnd[0] = x + 1;
			yEnd[0] = y;
			break;
		case DOWN:
			xEnd[0] = x;
			yEnd[0] = y - 1;
			break;
		case UP:
			xEnd[0] = x;
			yEnd[0] = y + 1;
			break;
		case RIGHT:
			xEnd[0] = x - 1;
			yEnd[0] = y;
			break;
		}
	}

}
int main()
{
	Setup();
	while (!gameover) 
	{
		Draw();
		Input();
		Logic();
		Sleep(60);
	}
	
	return 0;
}