#pragma once
#include "global.h"

class CCollider;
class CAnimator;
class CRigidBody;
class CGravity;

#include "CCamera.h"

// ��ü�� ��ǥ�� ��ġ
// ��� ������Ʈ�� �θ� ��Ʈ, ������ �� ��ü�� �� ���� ����!
// = > ���������Լ��� ������ �߻�Ŭ������ ��ü�Ѵ�.
class CObject
{
private:

	wstring			m_strName;	// Name = ���� ������Ʈ���� üũ
	Vec2			m_vPos;		// ��ǥ ����
	Vec2			m_vScale;	// ũ�� ����

	// �ڡڡ� component
	// �浹 ��ɿ� �ʿ��� ���� ������Ʈ�� �߰�, �����ʹϱ� �ʿ��ϸ� �����Ҵ�, �ƴϸ� null -> ��Ȱ��ȭ
	CCollider*		m_pCollider;
	CAnimator*		m_pAnimator;
	CRigidBody*		m_pRigidBody;
	CGravity*		m_pGravity;
	bool m_bAlive;

public:
	void SetPos(Vec2 _vPos) { this->m_vPos = _vPos; }
	Vec2 GetPos() { return this->m_vPos; } 

	void SetScale(Vec2 _vScale) { this->m_vScale = _vScale; }
	Vec2 GetScale() { return this->m_vScale; }

	void SetName(const wstring& _strName) { m_strName = _strName; }
	wstring& GetName() { return m_strName; }
	
	CCollider* GetCollider() { return m_pCollider; }
	CAnimator* GetAnimator() { return m_pAnimator; }
	CRigidBody* GetRigidBody() { return m_pRigidBody; }
	CGravity* GetGravity() { return m_pGravity; }



	// �浹Ŭ������ �ʿ��� ��ü�� �浹��ü ����(collider)
	void CreateCollider();
	void CreateAnimator();
	void CreateRigidBody();
	void CreateGravity();
	bool IsDead() { return !m_bAlive; }



	// �浹 ���� �Լ� ��� - ������Ʈ�� ó���� �浹
	virtual void OnCollision(CCollider* _pOther) {}		// �浹 ���� ��� ȣ��Ǵ� �Լ�
 	virtual void OnCollisionEnter(CCollider* _pOther) {}	// �浹�� �� ������ ��� ȣ��Ǵ� �Լ�
	virtual void OnCollisionExit(CCollider* _pOther) {}

private:
	void SetDead() { m_bAlive = false; }

public:
	virtual void start() {};		// Scene�� ���۵Ǳ� ������ ȣ��Ǵ� �Լ�
	// �� ������Ʈ�� ��ӹ��� Ŭ�����鸶�� update�� render �ʿ�
	virtual void update() = 0;		// ���������Լ� > �ݵ�� �ڽĿ��� �������̵� �ؾ���

	// �����Լ��� �������̵� ��Ű�� ���� �ƴ�, ������Ʈ�� ������Ʈ�� �Ͽ��� �����ϰ� ��
	virtual void finalupdate();	// final Ű����� �� �̻��� �������̵��� ����
	virtual void render(HDC _dc);

	void Component_render(HDC _dc);

	// ���������Լ��� �ִ� �߻�Ŭ�����̹Ƿ� �̰͵� ���������Լ��� ���� �������̵� ��Ų��
	virtual CObject* Clone() = 0;

public:
	CObject();
	CObject(const CObject& _origin);
	virtual~CObject();

	friend class CEventMgr;
};

// ������Ʈ ��� ����
// �ʹ� ����� ���̰� ��� �׷��� Ȯ�强�� ��������.
// �ʿ��� ��� ������ ��� ���Խ�Ű��, �ʿ��� ��쿡�� Ȱ��ȭ �ǵ��� �Ѵ�.
