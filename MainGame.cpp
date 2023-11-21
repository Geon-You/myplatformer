#include "MainGame.h"
#include "Player.h"
#include "MathUtil.h"
#include "Obstacle.h"

void MainGame::Initialize()
{
	srand(GetTickCount64());

	// ���� ������ �ڵ��� ���� dc�� �����´�
	hdc = GetDC(g_hWnd);

	player = new Player();
	player->Initialize();

	obstacle = new Obstacle();
	obstacle->Initialize();

	// ������ ��ġ ����ü
	POINTFLOAT points[4] =
	{
		{ 100, 500 }, // 0��° �ε���
		{ 300, 500 },
		{ 500, 300 },
		{ 700, 300},
	};

	lineList.push_back(new LINE(points[0], points[1]));
	lineList.push_back(new LINE(points[1], points[2]));
	lineList.push_back(new LINE(points[2], points[3]));

	((Player*)player)->SetLineList(&lineList);
	((Player*)player)->SetObstacle(obstacle);

}

void MainGame::Update()
{
	player->Update();
}

void MainGame::Render()
{
	// â �ػ󵵸�ŭ �簢���� ���� �׷�, ȭ���� ������ ��ó�� ���̰� ��
	Rectangle(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	player->Render(hdc);

	// ���� ������ ����
	MoveToEx(hdc, lineList.front()->lPoint.x, lineList.front()->lPoint.y, NULL);

	// �������� �������� ���� �̾ �׸���
	for (auto iter = lineList.begin(); iter != lineList.end(); ++iter)
	{
		LineTo(hdc, (*iter)->rPoint.x, (*iter)->rPoint.y);
	}

	obstacle->Render(hdc);
}

void MainGame::Release()
{
	// �÷��̾� ��ü�� �����Ѵٸ� ����
	if (player)
	{
		delete player;
		player = nullptr;
	}

	for (auto iter = lineList.begin(); iter != lineList.end(); ++iter)
	{
		if ((*iter))
		{
			delete* iter;
			*iter = nullptr;
		}
	}
	lineList.clear();

	if (obstacle)
	{
		delete obstacle;
		obstacle = nullptr;
	}

	// �����Դ� dc�� �ý��ۿ� ��ȯ (����)
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
