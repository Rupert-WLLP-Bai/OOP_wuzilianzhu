#pragma once
#include"checkerboard.h"
void eliminate_1(Checkerboard A, int x, int y,int *left,int *right);//横向
void eliminate_2(Checkerboard A, int x, int y,int *up,int *down);//竖向
void eliminate_3(Checkerboard A, int x, int y,int*EN,int*WS);//撇向
void eliminate_4(Checkerboard A, int x, int y,int *WN,int *ES);//捺向
int eliminate(Checkerboard *A, int x, int y,const char *prompt=nullptr);//综合,返回值乘2为得分
int eliminate(Checkerboard* A, const char* prompt);//全部消去检查