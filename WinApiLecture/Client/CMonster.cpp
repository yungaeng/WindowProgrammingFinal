#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "AI.h"
CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f,0.f))
	,m_tInfo{}
	,m_pAI(nullptr)
	/*,m_fSpeed(100)
	,m_fMaxDistance(50.f)
	,m_iDir(1)
	,m_iHP(5)*/
{
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}


void CMonster::update()
{
	if(nullptr != m_pAI)
		m_pAI->update();
	//return;
	//Vec2 vCurPos = GetPos();

	//// ���� �������� �ð� �� m_fSpeed��ŭ �̵�
	//vCurPos.x += fDT * m_fSpeed * m_iDir;

	//float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	//// �� ��ġ�� ����(m_vCenterPos.x - vCurPos.x)�� ���밪���� ���ؾ� ��
	//// �������� ��ȭ�� ����ؾ��Ѵ� - �ִ� ��ȸ �Ÿ��� ���� �� �Ѿ ��츦 ����ؾ��Ѵ�.
	//if (0 < fDist)	// �ִ� �Ÿ��� �Ѿ� �� ���
	//{
	//	// ���� ����
	//	m_iDir *= -1;
	//	// �ʰ��� �Ÿ��� �ݴ� �������� ������
	//	vCurPos.x += fDist * m_iDir;
	//}

	//SetPos(vCurPos);
}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI; m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();	// �ε��� ����� object�� �޾ƿ�
	//// �ε��� ��� �����ϱ�
	if (pOtherObj->GetName() == L"Missale_Player")
	{
		m_tInfo.fHP -= 25;

		if(m_tInfo.fHP <= 0)
 			DeleteObject(this);
	}
}

void CMonster::OnCollision(CCollider* _pOther)
{
}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}
