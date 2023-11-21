#pragma once
#include "Define.h"

class Object;

class MainGame
{
private:
	HDC hdc; // 게임 내 객체를 그릴 때 사용될 hdc
	Object* player; // 플레이어 객체
	Object* obstacle; // 장애물 객체
	list<LINE*> lineList; // 라인 객체들을 갖는 리스트

public:
	void Initialize(); // 초기화
	void Update(); // 게임 내 연산
	void Render(); // 그리기
	void Release(); // 메모리 해제

public:
	MainGame();
	~MainGame();
};

