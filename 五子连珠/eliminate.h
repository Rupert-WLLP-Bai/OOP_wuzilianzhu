#pragma once
#include"checkerboard.h"
void eliminate_1(Checkerboard A, int x, int y,int *left,int *right);//����
void eliminate_2(Checkerboard A, int x, int y,int *up,int *down);//����
void eliminate_3(Checkerboard A, int x, int y,int*EN,int*WS);//Ʋ��
void eliminate_4(Checkerboard A, int x, int y,int *WN,int *ES);//����
int eliminate(Checkerboard *A, int x, int y,const char *prompt=nullptr);//�ۺ�,����ֵ��2Ϊ�÷�
int eliminate(Checkerboard* A, const char* prompt);//ȫ����ȥ���