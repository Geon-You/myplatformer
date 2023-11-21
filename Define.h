#pragma once
#include "framework.h"

#define WIN_SIZE_X 800
#define WIN_SIZE_Y 600

extern HWND g_hWnd;

// Ư�� ��ü�� �׸� ��, ��ġ�� ����� �ʿ�
// �׷� �� �� ���� ��ġ�� ����� �Ź� ���� �����ϱ� �������ϱ�
// ���� ���Ǵ� �����͸� ����ü�� ����� ó��
typedef struct tagInfo
{
	int posX;
	int posY;
	int sizeX;
	int sizeY;
}INFO;

typedef struct tagLine
{
	// ���� ��(���� ��)
	POINTFLOAT lPoint;
	// ������ ��(�� ��)
	POINTFLOAT rPoint;

	tagLine() {}
	tagLine(POINTFLOAT lp, POINTFLOAT rp) : lPoint(lp), rPoint(rp) {}
}LINE;