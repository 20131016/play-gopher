#pragma once
#define RC 10
void init(int map[][RC]);
void show(int map[][RC]);
void loadResource();
void draw(int map[][RC]);
void mouseMsg(ExMessage* msg, int map[][RC]);
void game();
int PH = 3;
int IsGame = 1;
int mouse = 0;