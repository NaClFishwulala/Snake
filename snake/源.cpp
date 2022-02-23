#include <stdio.h>
#include <graphics.h>
#include <conio.h>
#include <time.h>

#define SnakeSize 4
#define SnakeSpeed 10

#define KET_UP 72
#define KET_DOWN 80
#define KET_LEFT 75 
#define KET_RIGHT 77

enum DIR
{
	UP,
	DOWN,
	LEFT,
	RIGHT,
};

struct Snake
{
	int size;
	int dir;
	int speed;
	POINT coord[5000];
}snake;

struct Food
{
	int x;
	int y;
	int size = 5;
	bool flag;
}food;

void GameInit();
void GameDraw();
void SnakeMove();
void KeyControl();
void FoodEat();
void FoodCreat();

int main()
{
	GameInit();
	GameDraw();
	while (1)
	{
		GameDraw();
		SnakeMove();
		KeyControl();
		FoodEat();
		Sleep(40);
	}
	return 0;
}

void GameInit()
{
	//初始化屏幕
	initgraph(640, 480);
	//初始化蛇
	snake.size = SnakeSize;
	snake.speed = SnakeSpeed;
	snake.dir = RIGHT;
	for (int i = 0; i < snake.size; i++)
	{
		snake.coord[i].x = (snake.size-i)*10+20;
		snake.coord[i].y = 10;
	}
	//初始化食物
	srand((unsigned)time(NULL));
	FoodCreat();
	return;
}

void GameDraw()
{
	BeginBatchDraw();
	//画屏幕
	setbkcolor(RGB(0, 255, 0));
	cleardevice();
	//画蛇
	setfillcolor(RED);
	solidcircle(snake.coord[0].x, snake.coord[0].y, 5);
	setfillcolor(WHITE);
	for(int i=1;i<snake.size;i++)
		solidcircle(snake.coord[i].x, snake.coord[i].y, 5);
	//画食物
	if (food.flag)
	{
		setfillcolor(YELLOW);
		solidcircle(food.x, food.y, food.size);
	}

	EndBatchDraw();
	return;
}

void SnakeMove()
{
	for (int i = snake.size-1; i > 0 ; i--)
	{
		snake.coord[i].x = snake.coord[i-1].x;
		snake.coord[i].y = snake.coord[i-1].y;
	}
	switch (snake.dir)
	{
		case RIGHT:
			snake.coord[0].x += SnakeSpeed;
			if (snake.coord[0].x >= 640)
				snake.coord[0].x = 0;
			break;
		case LEFT:
			snake.coord[0].x -= SnakeSpeed;
			if (snake.coord[0].x <= 0)
				snake.coord[0].x = 640;
			break;		
		case UP:		
			snake.coord[0].y -= SnakeSpeed;
			if (snake.coord[0].y <= 0)
				snake.coord[0].y = 480;
			break;		
		case DOWN:		
			snake.coord[0].y += SnakeSpeed;
			if (snake.coord[0].y >= 480)
				snake.coord[0].y = 0;
			break;
		default:
			break;
	}
}

void KeyControl()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case KET_UP:
			if(snake.dir != DOWN)
				snake.dir = UP;
			break;
		case KET_DOWN:
			if (snake.dir != UP)
				snake.dir = DOWN;
			break;
		case KET_LEFT:
			if (snake.dir != RIGHT)
				snake.dir = LEFT;
			break;
		case KET_RIGHT:
			if (snake.dir != LEFT)
				snake.dir = RIGHT;
			break;
		default:
			break;
		}
	}
}

void FoodEat()
{
	if (snake.coord[0].x + food.size >= food.x && snake.coord[0].x - food.size <= food.x
		&& snake.coord[0].y + food.size >= food.y && snake.coord[0].y - food.size <= food.y
		&& food.flag)
	{
		food.flag = false;
		snake.size++;
	}

	if (!food.flag)
		FoodCreat();
}

void FoodCreat()
{
	food.x = rand() % 640;
	food.y = rand() % 480;
	food.flag = true;
}