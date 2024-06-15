#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "AI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
#include "CRigidBody.h"
CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f,0.f))
	,m_tInfo{}
	,m_pAI(nullptr)
	,m_bGoneDead(false)
	, m_fDeadTime(0.f)
	,m_fSpeed(100)
	,m_fMaxDistance(75.f)
	,m_iDir(1)
//	,m_iHP(5)
{
	// 06/11 �� �ؽ��� �߰�
	CreateCollider();
	GetCollider()->SetScale(Vec2(100.f, 100.f));


	CreateAnimator();
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\pepper.bmp");

	//CreateRigidBody();


	//	CreateGravity();

	GetAnimator()->CreateAnimation(
		L"Monster",
		pTex,
		Vec2(0.f, 0.f),
		Vec2(200.f, 200.f),
		Vec2(200.f, 0.f),
		0.3f,
		4);
}

CMonster::~CMonster()
{
	if (nullptr != m_pAI)
		delete m_pAI;
}


void CMonster::update()
{
	/*if(nullptr != m_pAI)
		m_pAI->update();*/
	//return;



	Vec2 vCurPos = GetPos();


	if (m_bGoneDead == false)
	{
		// ���� �������� �ð� �� m_fSpeed��ŭ �̵�
		vCurPos.x += fDT * m_fSpeed * m_iDir;

		float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
		// �� ��ġ�� ����(m_vCenterPos.x - vCurPos.x)�� ���밪���� ���ؾ� ��
		// �������� ��ȭ�� ����ؾ��Ѵ� - �ִ� ��ȸ �Ÿ��� ���� �� �Ѿ ��츦 ����ؾ��Ѵ�.
		if (0 < fDist)	// �ִ� �Ÿ��� �Ѿ� �� ���
		{
			// ���� ����
			m_iDir *= -1;
			// �ʰ��� �Ÿ��� �ݴ� �������� ������
			vCurPos.x += fDist * m_iDir;
		}

		SetPos(vCurPos);
	}



	// 06/11 �� �ִϸ��̼�
	if(m_bGoneDead == false)
		GetAnimator()->Play(L"Monster", true);
	else
	{
		// 06/15 �߰� 
		// �״� ������ ���
		if (m_fDeadTime == 0.f)
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -1200.f));

		m_fDeadTime += CTimeMgr::GetInst()->GetfDT();


		if (m_fDeadTime >= 1.f)
		{
			DeleteObject(this);
		}
	}
}

void CMonster::render(HDC _dc)
{
	Component_render(_dc);

	if (m_fDeadTime >= 0.8f && m_fDeadTime <= 1.f)
	{
		CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Effect", L"texture\\effect.bmp");
		Vec2 vPos = GetPos();
		Vec2 vScale = GetCollider()->GetScale();
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
		float width = (float)pTex->Width();
		float height = (float)pTex->Height();

		TransparentBlt(_dc,
			vPos.x - (float)(vScale.x)
			, vPos.y - (float)(vScale.y)
			, vScale.x * 2, vScale.y * 2
			, pTex->GetDC()
			, 0, 0, width, height
			, RGB(255,0,255));
	}
}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI; m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();	// �ε��� ����� object�� �޾ƿ�
	// �ε��� ��� �����ϱ�
	if (pOtherObj->GetName() == L"Player" && m_bGoneDead == false)
	{
		// �߰� �ٶ� : 06.15 �߰� - �÷��̾���� �浹 ��ȣ�ۿ� ����
		// �÷��̾� ��ġ
		Vec2 vPlayerPos = pOtherObj->GetPos();

		// ����(�ڽ�) ��ġ
		Vec2 vMyPos = GetPos();

		// ���� �� �ִ� y��ġ ���� �ּ� �Ÿ� > �� �� ������ ��ȣ�ۿ��� ������ �ʿ�
		float fCanPress = pOtherObj->GetScale().y / 2 + this->GetScale().y;

		// �浹 �� �÷��̾�� ����(�ڽ�)�� y��ġ ���̰� ���� �� �ִ� �Ÿ����� ũ��
		if (abs(vPlayerPos.y - vMyPos.y) >= fCanPress)
		{
			// �ܼ� �����ڵ�
			// DeleteObject(this);
			// �״� �ִϸ��̼� �÷��� ��� Ȱ��ȭ
			m_bGoneDead = true;
			CreateGravity();
		}
	}
}

void CMonster::OnCollision(CCollider* _pOther)
{

}

void CMonster::OnCollisionExit(CCollider* _pOther)
{
}
