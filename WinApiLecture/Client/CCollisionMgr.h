#pragma once

class CCollider;

union COLLIDER_ID
{
	struct {
		UINT Left_id;
		UINT Right_id;
	};
	ULONGLONG ID;
};


class CCollisionMgr
{
	SINGLE(CCollisionMgr)
private:
	// �׷� ������ŭ�� ��� ���� �迭 ����
	UINT				 m_arrCheck[(UINT)GROUP_TYPE::END];	// �׷찣�� �浹 üũ ��Ʈ����
	
	map<ULONGLONG, bool> m_mapColInfo;		// �浹ü ���� ���� ������ �浹 ����
		// first: �� �浹ü���� Ű �� , second: �浹�� �ϰ� �־��°�? �ƴѰ�?
public:
	void update();
	void CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eright);
	// 32 * int(byte)���� �迭�� 0���� (int) * 32����Ʈ��ŭ �ʱ�ȭ 
	void Reset()	{memset(m_arrCheck, 0, sizeof(UINT) * (UINT)GROUP_TYPE::END);}

	// memset() -> ���� ������ �ּҸ� ����Ʈ ������ ä���

private:
	// �ڱ� �ڽ��� �Լ����� ȣ���� �Լ��̹Ƿ� private,
	// �׷찣�� �浹 ������Ʈ
	void CollisionUpdateGroup(GROUP_TYPE _eleft, GROUP_TYPE _eright);
	bool IsCollision(CCollider* _pLeft,CCollider* _pRight);

};

