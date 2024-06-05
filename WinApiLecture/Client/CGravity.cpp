#include "pch.h"
#include "CGravity.h"
#include "CObject.h"
#include "CRigidBody.h"

CGravity::CGravity()
	:m_pOwner(nullptr)
	, m_bGround(false)
{

}

CGravity::~CGravity()
{
	
}

void CGravity::SetGround(bool _b)
{
	m_bGround = _b;
	if (m_bGround)
	{
		// ���� ���� ������ ���ݱ��� ����� y���� �ӵ��� 0���� �Ѵ�
		Vec2 vVel = m_pOwner->GetRigidBody()->GetVelocity();
		m_pOwner->GetRigidBody()->SetVelocity(Vec2((vVel.x), 0.f));
	}
}

void CGravity::finalupdate()
{ 
	m_pOwner->GetRigidBody()->SetAccelAlpha(Vec2(0.f, 800.f));
}

