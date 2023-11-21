#pragma once
#include "Define.h"

class Object;

class MainGame
{
private:
	HDC hdc; // ���� �� ��ü�� �׸� �� ���� hdc
	Object* player; // �÷��̾� ��ü
	Object* obstacle; // ��ֹ� ��ü
	list<LINE*> lineList; // ���� ��ü���� ���� ����Ʈ

public:
	void Initialize(); // �ʱ�ȭ
	void Update(); // ���� �� ����
	void Render(); // �׸���
	void Release(); // �޸� ����

public:
	MainGame();
	~MainGame();
};

