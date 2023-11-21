#include "MainGame.h"
#include "Player.h"
#include "MathUtil.h"
#include "Obstacle.h"

void MainGame::Initialize()
{
	srand(GetTickCount64());

	// 전역 윈도우 핸들을 통해 dc를 가져온다
	hdc = GetDC(g_hWnd);

	player = new Player();
	player->Initialize();

	obstacle = new Obstacle();
	obstacle->Initialize();

	// 라인의 위치 구조체
	POINTFLOAT points[4] =
	{
		{ 100, 500 }, // 0번째 인덱스
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
	// 창 해상도만큼 사각형을 새로 그려, 화면이 지워진 것처럼 보이게 함
	Rectangle(hdc, 0, 0, WIN_SIZE_X, WIN_SIZE_Y);
	player->Render(hdc);

	// 라인 시작점 설정
	MoveToEx(hdc, lineList.front()->lPoint.x, lineList.front()->lPoint.y, NULL);

	// 시작점을 기준으로 라인 이어서 그리기
	for (auto iter = lineList.begin(); iter != lineList.end(); ++iter)
	{
		LineTo(hdc, (*iter)->rPoint.x, (*iter)->rPoint.y);
	}

	obstacle->Render(hdc);
}

void MainGame::Release()
{
	// 플레이어 객체가 존재한다면 해제
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

	// 가져왔던 dc를 시스템에 반환 (해제)
	ReleaseDC(g_hWnd, hdc);
}

MainGame::MainGame()
{
}

MainGame::~MainGame()
{
	Release();
}
