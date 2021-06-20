#include<iostream>
#include<cstdlib>
#include<ctime>
#include <conio.h>
#include<Windows.h>
using namespace std;
int Height, Width, FruitX, FruitY, HeadX, HeadY, Tail_n;
bool Gameover;
enum eDirection{ stop = 0, UP, DOWN, Right, Left };
eDirection Dir;
int Tail_X[40] = { 0 };
int Tail_Y[40] = { 0 };
int score;
void Setup()
{
	Gameover = false;
	Height = Width = 20;
	HeadX = Width / 2;
	HeadY = Height / 2;
	srand(time(NULL));
	FruitX = rand() % (Width - 2) + 1;
	FruitY = rand() % (Height - 2) + 1;
	Tail_n = 0;
	score = 0;
	eDirection Dir = stop;

}
void Draw()
{
	system("cls");
	for (int i = 0; i < Height; i++)
	{
		for (int j = 0; j < Width; j++)
		{
			if (i == 0 || i == Height - 1)cout << "*";
			else if (j == 0 || j == Width - 1)cout << "*";
			else if (i == HeadY && j == HeadX)cout << "O";
			else if (i == FruitY && j == FruitX)cout << "$";
			else
			{
				bool print = false;
				for (int k = 0; k < Tail_n; k++)
				{
					if (i == Tail_Y[k] && j == Tail_X[k])
					{
						cout << "o";
						print = true;
					}

				}
				if (!print)
				{
					cout << " ";
				}
			}
		}
		cout << endl;
	}
}
void input()
{
	if (_kbhit())
	{
		char C = _getch();
		switch (C)
		{
		case 'w':Dir = UP; break;
		case 's':Dir = DOWN; break;
		case 'a':Dir = Left; break;
		case 'd':Dir = Right; break;
		case 'q':system("pause"); break;
		case 'x':Gameover = true;

		}
	}
}
void logic()
{

	int preX, preY;
	int pre2X, pre2Y;
	preX = Tail_X[0];
	preY = Tail_Y[0];
	Tail_X[0] = HeadX;
	Tail_Y[0] = HeadY;
	for (int i = 1; i <= Tail_n; i++)
	{
		pre2X = Tail_X[i];
		pre2Y = Tail_Y[i];
		Tail_X[i] = preX;
		Tail_Y[i] = preY;
		preX = pre2X;
		preY = pre2Y;

	}
	switch (Dir)
	{
	case UP:HeadY--;
		break;
	case DOWN:HeadY++;
		break;
	case Right:HeadX++;
		break;
	case Left:HeadX--;
		break;
	}
}
void Score()
{


	if (HeadX == FruitX && HeadY == FruitY)
	{
		score += 10;
		Tail_n++;
		FruitX = rand() % (Width - 2) + 1;
		FruitY = rand() % (Height - 2) + 1;
	}
	for (int r = 0; r<Tail_n; r++)
	{
		if (Tail_X[r] == HeadX&&Tail_Y[r] == HeadY)
		{
			Gameover = true;
		}
	}
	if (HeadX <= 0 || HeadX >Width || HeadY <= 0 || HeadY > Height)
	{
		Gameover = true;
	}

	cout << "Score==" << score << endl;

}

int main()
{
	Setup();
	while (!Gameover)
	{
		Draw();
		input();
		logic();
		Score();
		Sleep(50);
	}
	system("pause");
}