#include "Player.h"

void Player::Initialize()
{
	info.posX = 100;
	info.posY = 500;

	// 절반 사이즈로 사용 됨
	info.sizeX = 25;
	info.sizeY = 25;

	speed = 5.f;
}

void Player::Update()
{
	CheckKey();

	Jump();

	BoxColl();

	LineColl();
}

void Player::Render(HDC hdc)
{
	Ellipse(hdc, info.posX - info.sizeX, info.posY - info.sizeY,
		info.posX + info.sizeX, info.posY + info.sizeY);
}

void Player::Release()
{
}

void Player::CheckKey()
{
	if (GetAsyncKeyState(VK_LEFT))
	{
		info.posX -= speed;
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		info.posX += speed;
	}

	if (GetAsyncKeyState(VK_SPACE) && !isJump)
	{
		time = 0;
		isJump = true;
	}
}

void Player::Jump()
{
	if (!isJump)
		return;

	time += 0.1f;

	// 방향 * 최대 높이 + 중력가속도(절반으로 줄였음)
	info.posY += -sinf(90.f * 3.141592f / 180.f) * 6.f + (0.98f * time * time * 0.5f);
}

void Player::BoxColl()
{
	// 박스끼리 충돌 시, 겹치는 부분에 대한 정보를 받음
	// -> IntersectRect() 사용
	
	// 플레이어와 장애물의 사각형 영역에 대한 정보를 가져옴
	RECT playerRC = GetRect();
	RECT obstacleRC = obstacle->GetRect();
	// 겹치는 부분에 대한 정보를 받을 RECT를 선언
	RECT collRC;

	if (IntersectRect(&collRC, &playerRC, &obstacleRC))
	{
		// 충돌했을 경우 이 조건문 내부로 들어옴

		// 겹친 부분에 대한 정보 중, 위치는 제거하고 크기만 남김
		SetRect(&collRC, 0, 0, collRC.right - collRC.left, collRC.bottom - collRC.top);

		// 조건식을 통해 어느 방향에서 플레이어가 부딪혔는지 확인
		auto sizeX = collRC.right;
		auto sizeY = collRC.bottom;

		// 겹친 부분의 너비가 겹친 부분의 높이보다 작다면
		if (sizeX < sizeY) // 양 옆에서 부딪힐 경우
		{
			// 겹친 너비만큼 빼주거나 더함
			if (info.posX < obstacle->GetInfo().posX)
			{
				info.posX -= sizeX;
			}
			else
			{
				info.posX += sizeX;

			}
		}
		else // 위 아래에서 부딪힐 경우
		{
			if (info.posY > obstacle->GetInfo().posY)
			{
				info.posY += sizeY;
			}
			else
			{
				info.posY -= sizeY;
			}
		}
	}
}

void Player::LineColl()
{
	// 플레이어가 여러 라인 중, 어느 라인에 있는지 확인
	LINE* currentLine = nullptr;

	for (auto iter = lineListAddress->begin(); iter != lineListAddress->end(); ++iter)
	{
		// 플레이어와 라인의 x 값을 가지고, 현재 라인을 확인
		if (info.posX >= (*iter)->lPoint.x 
			&& info.posX <= (*iter)->rPoint.x)
		{
			// 현재 라인을 갱신
			currentLine = (*iter);
			break;
		}
	}

	// 현재 라인이 없다면 리턴
	if (currentLine == nullptr)
	{
		if (!isJump)
		{
			time += 0.1f;
			info.posY += (0.98f * time * time * 0.5f);
		}

		return;
	}

	// 현재 라인의 너비와 높이를 구함
	float width = currentLine->rPoint.x - currentLine->lPoint.x;
	float height = currentLine->rPoint.y - currentLine->lPoint.y;

	// 새로운 y 지점 = 높이와 너비 비율(미분 계수 즉, 변화량) * (현재 라인의 시작점을 기준으로 한 플레이어의 x 위치) + (라인 초기 위치 y)
	float y = (height / width) * (info.posX - currentLine->lPoint.x) + currentLine->lPoint.y;

	y -= info.sizeY;

	// 점프 상태가 아닐 때, 플레이어 y 위치 보정
	if (!isJump)
	{
		info.posY = y;
	}

	// 플레이어가 점프 후, 라인에 닿았을 때 위에 구한 보정된 y 값으로 덮어쓰고 점프 종료
	if (info.posY >= y)
	{
		time = 0;
		info.posY = y;
		isJump = false;
	}
}

Player::Player()
{
}

Player::~Player()
{
}
