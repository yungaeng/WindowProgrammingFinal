#pragma once

class CObject;

// �浹ü�� ������ ������Ʈ�� �̵��� �� �� �浹ü�� ���� �̵��Ͽ��� ��
class CCollider
{
	// ���� �˻�
private:
	static UINT g_iNextID;
	// Collider �� �����ϰ� �ִ� ������Ʈ
	CObject*m_pOwner;		

	// ������, ���� ��ġ(������Ʈ)�κ��� ������� ���̰� / �� ���� �̿��Ͽ� �浹ü ������ �̵���Ų��.
	Vec2	m_vOffsetPos;

	// �������� �̿��Ͽ� ����Ͽ� ���� ��ġ ����
	Vec2	m_vFinalPos;

	// �浹ü�� ũ��
	Vec2	m_vScale;

	UINT	m_iID;		// �浹ü�� ������ ID��
	int		m_iCol;

	bool	m_bActive;	// �浹ü Ȱ��ȭ ����


public:
	void SetOffsetPos(Vec2 _vPos) { m_vOffsetPos = _vPos; }
	void SetScale(Vec2 _vScale) { m_vScale = _vScale; }

	Vec2 GetOffsetPos() { return m_vOffsetPos; }
	Vec2 GetScale() { return m_vScale; }
	Vec2 GetFinalPos() { return m_vFinalPos; }

	CObject* GetObj() { return m_pOwner; }
	UINT GetID() { return m_iID; }

public:
	void finalupdate();
	void render(HDC _dc);

public:
	// �浹 ���� �Լ� ���
	void OnCollision(CCollider* _pOther);		// �浹 ���� ��� ȣ��Ǵ� �Լ�
	void OnCollisionEnter(CCollider* _pOther);	// �浹�� �� ������ ��� ȣ��Ǵ� �Լ�
	void OnCollisionExit(CCollider* _pOther);	// �浹���� ��� ��� ȣ��Ǵ� �Լ�


	// ���� ������ ��ü �����ϱ� - �� ������ ���� �⺻ �����ڰ� �Ǽ��ζ� ��������� �� ��
	CCollider& operator = (CCollider& _origin) = delete;

	CCollider();
	// ���� id ������ ���� ��������� ���� ���� ȣ��
	CCollider(const CCollider& _origin);

	~CCollider();


	friend class CObject;
};

