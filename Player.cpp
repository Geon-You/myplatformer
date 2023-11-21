#include "Player.h"

void Player::Initialize()
{
	info.posX = 100;
	info.posY = 500;

	// ���� ������� ��� ��
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

	// ���� * �ִ� ���� + �߷°��ӵ�(�������� �ٿ���)
	info.posY += -sinf(90.f * 3.141592f / 180.f) * 6.f + (0.98f * time * time * 0.5f);
}

void Player::BoxColl()
{
	// �ڽ����� �浹 ��, ��ġ�� �κп� ���� ������ ����
	// -> IntersectRect() ���
	
	// �÷��̾�� ��ֹ��� �簢�� ������ ���� ������ ������
	RECT playerRC = GetRect();
	RECT obstacleRC = obstacle->GetRect();
	// ��ġ�� �κп� ���� ������ ���� RECT�� ����
	RECT collRC;

	if (IntersectRect(&collRC, &playerRC, &obstacleRC))
	{
		// �浹���� ��� �� ���ǹ� ���η� ����

		// ��ģ �κп� ���� ���� ��, ��ġ�� �����ϰ� ũ�⸸ ����
		SetRect(&collRC, 0, 0, collRC.right - collRC.left, collRC.bottom - collRC.top);

		// ���ǽ��� ���� ��� ���⿡�� �÷��̾ �ε������� Ȯ��
		auto sizeX = collRC.right;
		auto sizeY = collRC.bottom;

		// ��ģ �κ��� �ʺ� ��ģ �κ��� ���̺��� �۴ٸ�
		if (sizeX < sizeY) // �� ������ �ε��� ���
		{
			// ��ģ �ʺ�ŭ ���ְų� ����
			if (info.posX < obstacle->GetInfo().posX)
			{
				info.posX -= sizeX;
			}
			else
			{
				info.posX += sizeX;

			}
		}
		else // �� �Ʒ����� �ε��� ���
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
	// �÷��̾ ���� ���� ��, ��� ���ο� �ִ��� Ȯ��
	LINE* currentLine = nullptr;

	for (auto iter = lineListAddress->begin(); iter != lineListAddress->end(); ++iter)
	{
		// �÷��̾�� ������ x ���� ������, ���� ������ Ȯ��
		if (info.posX >= (*iter)->lPoint.x 
			&& info.posX <= (*iter)->rPoint.x)
		{
			// ���� ������ ����
			currentLine = (*iter);
			break;
		}
	}

	// ���� ������ ���ٸ� ����
	if (currentLine == nullptr)
	{
		if (!isJump)
		{
			time += 0.1f;
			info.posY += (0.98f * time * time * 0.5f);
		}

		return;
	}

	// ���� ������ �ʺ�� ���̸� ����
	float width = currentLine->rPoint.x - currentLine->lPoint.x;
	float height = currentLine->rPoint.y - currentLine->lPoint.y;

	// ���ο� y ���� = ���̿� �ʺ� ����(�̺� ��� ��, ��ȭ��) * (���� ������ �������� �������� �� �÷��̾��� x ��ġ) + (���� �ʱ� ��ġ y)
	float y = (height / width) * (info.posX - currentLine->lPoint.x) + currentLine->lPoint.y;

	y -= info.sizeY;

	// ���� ���°� �ƴ� ��, �÷��̾� y ��ġ ����
	if (!isJump)
	{
		info.posY = y;
	}

	// �÷��̾ ���� ��, ���ο� ����� �� ���� ���� ������ y ������ ����� ���� ����
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
