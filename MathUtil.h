#pragma once
#include "Object.h"

class MathUtil
{
public:
	// static�� ������ ���� �޼���, ���� �޼���� �ν��Ͻ� ���� ����� ����
	// Ŭ���� ��ü�� ���ԵǹǷ�
	// �Ķ���ͷ� ���� 2���� ������Ʈ�� �浹�� ���� 
	static bool OnCollision(Object* a, Object* b)
	{
		// �浹 üũ�� �ϰ��� �ϴ� �� ���� �������� �� ��
		// -> �� �� ������ �Ÿ��� �� ���� �������� ���� ������ �۴ٸ� �浹�ߴٰ� ó��
		int sum = a->GetInfo().sizeX + b->GetInfo().sizeX;

		// �浹�� �����ϰ����ϴ� �� ��ü ������ �Ÿ��� ���Ѵ�.
		// �� ��ü ������ x�������� �Ÿ�
		int distanceX = a->GetInfo().posX - b->GetInfo().posX;
		// �� ��ü ������ y�������� �Ÿ�
		int distanceY = a->GetInfo().posY - b->GetInfo().posY;

		// ���� x, y ���� �Ÿ��� �ϳ��� �����ͷ� ǥ�� (���� �Ÿ��� ����)
		float distance = sqrt(distanceX * distanceX + distanceY * distanceY);

		// �� ���� �������� ���� ���� �����Ÿ����� ũ�ٸ� �浹�ߴٴ� ��
		return sum > distance;
	}
};
