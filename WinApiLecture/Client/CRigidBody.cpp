#include "pch.h"
#include "CRigidBody.h"
#include "CTimeMgr.h"
#include "CObject.h"

CRigidBody::CRigidBody()
	:m_pOwner(nullptr)
	,m_fMass(1.f)
	, m_vMaxVelocity(Vec2(200.f,600.f))
	,m_fFricCoef(100.f)
{
}

CRigidBody::~CRigidBody()
{
}


void CRigidBody::finalupdate()
{
	// ���� ũ��
	float fForce = m_vForce.Length();	

	// ��ü�� ����� ���� 0�̸� �������� ����
	if (0.f != fForce)
	{
		// ���� �������� ����ȭ
		m_vForce.Normalize();

		//���ӵ��� ũ�� = ����ũ��(|f| / m)
		float m_fAccel = fForce / m_fMass;


		//	���� ���� * ���ӵ��� ũ��		 ���ӵ� : f = ma, a = f / m	
		m_vAccel =	m_vForce * m_fAccel; // m_vForce / m_fMass;	
	}

	// �߰� ���ӵ�
	m_vAccel += m_vAccelA;

	// �ӵ� : ���� �ӵ��� ���ӵ� * fDT ��ŭ�� ���� ������Ʈ�Ѵ�.
	m_vVelocity += m_vAccel * fDT;


	if (!m_vVelocity.IsZero())
	{
		Vec2 vFricDir = -m_vVelocity;
		vFricDir.Normalize();
		// �����¿� ���� �ݴ� ���������� ���ӵ� ���� 
		// ���� �ӵ��� �ݴ� ���� ���� ���Ϳ� ��������� ���� ���� �ӵ��� ����
		Vec2 vFriction = vFricDir * m_fFricCoef * fDT;
		if (m_vVelocity.Length() <= vFriction.Length())
		{
			// ���� ���ӵ��� ���� �ӵ����� �� ū ��� �ӵ��� ����
			m_vVelocity = Vec2(0.f, 0.f);
		}
		else
		{
			m_vVelocity += vFriction;
		}
	}

	// �ӵ� ���� �˻�
	if (abs(m_vMaxVelocity.x) < abs(m_vVelocity.x))
	{
		// ���� �ڽ��� x�� �ӷ��� ũ��� x�� �ӵ��� ������ ����ȭ -> x�� �ִ� �ӵ��� ����
		m_vVelocity.x = (m_vVelocity.x / abs(m_vVelocity.x)) * abs(m_vMaxVelocity.x);
	}

	if (abs(m_vMaxVelocity.y) < abs(m_vVelocity.y))
	{
		// ���� �ڽ��� x�� �ӷ��� ũ��� x�� �ӵ��� ������ ����ȭ -> x�� �ִ� �ӵ��� ����
		m_vVelocity.y = (m_vVelocity.y / abs(m_vVelocity.y)) * abs(m_vMaxVelocity.y);
	}

	// �ӵ��� ���� �̵�
	Move();

	// ���� ����� ���� ������ �ޱ� ���� �ڽ��� �̹� �����ӿ� �޾Ҵ� ���� �ʱ�ȭ
	m_vForce = Vec2(0.f, 0.f);

	// �߰� ���ӵ�, ���ӵ� �ʱ�ȭ
	m_vAccel = Vec2(0.f, 0.f);
	m_vAccelA = Vec2(0.f,0.f);
	
}


void CRigidBody::Move()
{
	// �ӷ�
	float fSpeed = m_vVelocity.Length();
	
	if (0.f != fSpeed)
	{
		// �̵� ����
		Vec2 vDir = m_vVelocity;
		// �븻�������ϸ� ������ �Ѽ��ϹǷ� ���������� ����ȭ
		vDir.Normalize();
		Vec2 vPos = m_pOwner->GetPos();
		vPos += m_vVelocity * fDT;

		m_pOwner->SetPos(vPos);
	}

	

}

