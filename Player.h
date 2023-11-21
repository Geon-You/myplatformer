#pragma once
#include "Object.h"

class Player :
    public Object
{
private:
    float speed; // �÷��̾��� �̵��ӵ�
    list<LINE*>* lineListAddress; // ���� ���ӿ��� �Ѱ��ִ� ���� ����Ʈ �ּҸ� �Ѱܹ��� ���
    float time; // ���� ��, ���ӵ� ǥ���� ���� ���
    bool isJump; // ���� ���� ���������� ��Ÿ���� ���� ���
    Object* obstacle; // ���� ���ӿ��� �ڽ� ������ �޾ƿ�

public:
    void SetLineList(list<LINE*>* lineListAddress) { this->lineListAddress = lineListAddress; } // ���� ���ӿ��� ����Ʈ �ּҸ� �������� �޼���
    void SetObstacle(Object* obstacle) { this->obstacle = obstacle; } // ���� ���ӿ��� ��ֹ� ��ü�� �ּҸ� �������� �޼���

public:
    // Object��(��) ���� ��ӵ�
    void Initialize() override;
    void Update() override;
    void Render(HDC hdc) override;
    void Release() override;

private:
    void CheckKey(); // Ű �Է� üũ
    void Jump(); // ���� ���
    void BoxColl(); // �ڽ� �浹 ����
    void LineColl(); // ���� �浹 ����

public:
    Player();
    virtual ~Player();
};

