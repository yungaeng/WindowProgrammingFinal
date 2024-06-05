#include "pch.h"
#include "CObject.h"

#include "CCollider.h"
#include "CAnimator.h"
#include "CCamera.h"
#include "CRigidBody.h"
#include "CGravity.h"

CObject::CObject()
	:m_vPos{}
	,m_vScale{}
	,m_pCollider(nullptr)
	,m_pAnimator(nullptr)
	,m_pRigidBody(nullptr)
	,m_pGravity(nullptr)
	,m_bAlive(true)

{
	
}

// �ڡڡںθ��� ��Ʈ�� �θ��� �����ڰ� ������Ų��.
CObject::CObject(const CObject& _origin)
	:m_strName(_origin.m_strName)
	, m_vPos(_origin.m_vPos)
	, m_vScale(_origin.m_vScale)
	, m_pCollider(nullptr)
	, m_pAnimator(nullptr)
	, m_pRigidBody(nullptr)
	, m_pGravity(nullptr)
	, m_bAlive(true)
{
	// ���� ������Ʈ�� �ݶ��̴��� ������ ��쿡�� ����
	if (_origin.m_pCollider)
	{
		m_pCollider = new CCollider(*_origin.m_pCollider);
		m_pCollider->m_pOwner = this;
	}
	if (_origin.m_pAnimator)
	{
		m_pAnimator = new CAnimator(*_origin.m_pAnimator);
		m_pAnimator->m_pOwner = this;
	}
	if (_origin.m_pGravity)
	{
		m_pGravity = new CGravity(*_origin.m_pGravity);
		m_pGravity->m_pOwner = this;
	}
	
}

CObject::~CObject() 
{
	if (nullptr != m_pCollider)
	{
		delete m_pCollider;
	}
	if (nullptr != m_pAnimator)
	{
		delete m_pAnimator;
	}
	if (nullptr != m_pRigidBody)
	{
		delete m_pRigidBody;
	}
	if (nullptr != m_pGravity)
	{
		delete m_pGravity;
	}

}




void CObject::finalupdate()
{
	

	// ��ü final update		--> ��ü ������Ʈ �� ��, �÷��̾��� ��ġ�� �����Ű�� ��찡 ����
	if (m_pRigidBody)
		m_pRigidBody->finalupdate();

	// �浹ü final update
	if (m_pCollider)
		m_pCollider->finalupdate();

	// �ִϸ����� final update
	if (m_pAnimator)
		m_pAnimator->finalupdate();
	if (m_pGravity)
		m_pGravity->finalupdate();


}

void CObject::render(HDC _dc)
{
	
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vPos);

	Rectangle(_dc
		, (int)(vRenderPos.x - m_vScale.x / 2)
		, (int)(vRenderPos.y - m_vScale.y / 2)
		, (int)(vRenderPos.x + m_vScale.x / 2)
		, (int)(vRenderPos.y + m_vScale.y / 2));

	Component_render(_dc);
}

void CObject::Component_render(HDC _dc)
{
	
	if (nullptr != m_pAnimator)
	{
		m_pAnimator->render(_dc);
	}

	if (nullptr != m_pCollider)
	{
		m_pCollider->render(_dc);
	}
	if (nullptr != m_pRigidBody)
	{
		//m_pRigidBody->render(_dc);
	}
}


void CObject::CreateCollider()
{
	m_pCollider = new CCollider;
	// �浹ü ������ ������Ʈ�� �ּҸ� �浹ü�� �Է�
	m_pCollider->m_pOwner = this;
}

void CObject::CreateAnimator()
{
	m_pAnimator = new CAnimator;
	m_pAnimator->m_pOwner = this;
}

void CObject::CreateRigidBody()
{
	m_pRigidBody = new CRigidBody;
	m_pRigidBody->m_pOwner = this;
}

void CObject::CreateGravity()
{
	m_pGravity = new CGravity;
	m_pGravity->m_pOwner = this;
}

