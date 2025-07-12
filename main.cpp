#include<stdio.h>
#include<easyx.h>
#include<stdlib.h>
#include<time.h>
#include<Windows.h>
#include<mmsystem.h>
#include "main.h"

#define RC 10
#define img 2
#define MineNum 64

#pragma comment(lib,"winmm.lib")

IMAGE imgs[img];
int main()
{
	mciSendString("open music/0.MP3", NULL, 0, NULL);
	mciSendString("open music/1.MP3", NULL, 0, NULL);
	srand((unsigned)time(NULL));
	int map[RC][RC] = { 0 };
	initgraph(640, 640, EX_SHOWCONSOLE);
	init(map);
	while (true)
	{
		ExMessage msg;
		if (peekmessage(&msg, WH_MOUSE))
		{
			switch (msg.message)
			{
			case WM_LBUTTONDOWN:
				mouseMsg(&msg, map);
				break;
			}
		}
		draw(map);
		game();
		if (IsGame == 2)
		{
			printf("Game Ove!");
			closegraph();
			mciSendString("play music/1.MP3", NULL, 0, NULL);
			Sleep(8000);
			break;
		}
		if (IsGame == 0)
		{
			printf("You Win!");
			closegraph();
			mciSendString("play music/0.MP3", NULL, 0, NULL);
			Sleep(11000);
			break;
		}
	}
	return 0;
}
void init(int map[][RC])
{
	for (int i = 0; i < RC; i++)
	{
		for (int k = 0; k < RC; k++)
		{
			map[i][k] = 0;
		}
	}
	int i = rand() % RC;
	int k = rand() % RC;
	map[i][k] = 1;
}
void show(int map[][RC])
{
	for (int i = 0; i < RC; i++)
	{
		for (int k = 0; k < RC; k++)
		{
			printf("(%d,%d) %d ", i, k, map[i][k]);
		}
		printf("\n");
	}
	
	printf("\n");
}
void loadResource()
{
	for (int i = 0; i < img; i++)
	{
		char imgPath[50] = { 0 };
		sprintf_s(imgPath, "images/%d.jpg", i);
		loadimage(&imgs[i], imgPath, MineNum, MineNum);
	}
}
void draw(int map[][RC])
{
	loadResource();
	for (int i = 0; i < RC; i++)
	{
		for (int k = 0; k < RC; k++)
		{
			if (map[k][i] == 0)
			{
				putimage(i * MineNum, k * MineNum, &imgs[0]);
			}
			else if (map[k][i] == 1)
			{
				putimage(i * MineNum, k * MineNum, &imgs[1]);
			}
		}
	}
}
void mouseMsg(ExMessage* msg, int map[][RC])
{
	int r = msg->y / MineNum;
	int c = msg->x / MineNum;
	if (map[r][c] == 1)
	{
		mouse++;
		init(map);
		//show(map);
	}
	else if(map[r][c] == 0)
	{
		PH--;
		//printf("%d\n", PH);
	}
}
void game()
{
	if (PH == 0)
	{
		IsGame = 2;
	}
	else if (mouse == 10)
	{
		IsGame = 0;
	}
}