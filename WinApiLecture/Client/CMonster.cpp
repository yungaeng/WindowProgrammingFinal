#include "pch.h"
#include "CMonster.h"

#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CCollider.h"
#include "AI.h"
#include "CTexture.h"
#include "CResMgr.h"
#include "CAnimator.h"
CMonster::CMonster()
	:m_vCenterPos(Vec2(0.f,0.f))
	,m_tInfo{}
	,m_pAI(nullptr)
	/*,m_fSpeed(100)
	,m_fMaxDistance(50.f)
	,m_iDir(1)
	,m_iHP(5)*/
{
	// 06/11 적 텍스쳐 추가
	CreateCollider();
	GetCollider()->SetScale(Vec2(40.f, 40.f));

	CreateAnimator();
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"MonsterTex", L"texture\\pepper.bmp");

	GetAnimator()->CreateAnimation(
		L"Monster",
		pTex,
		Vec2(0.f, 0.f),
		Vec2(272.f, 272.f),
		Vec2(272.f, 0.f),
		0.5f,
		4);
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

	//// 진행 방향으로 시간 당 m_fSpeed만큼 이동
	//vCurPos.x += fDT * m_fSpeed * m_iDir;

	//float fDist = abs(m_vCenterPos.x - vCurPos.x) - m_fMaxDistance;
	//// 두 위치의 차이(m_vCenterPos.x - vCurPos.x)는 절대값으로 구해야 함
	//// 프레임의 변화를 고려해야한다 - 최대 배회 거리를 조금 더 넘어설 경우를 고려해야한다.
	//if (0 < fDist)	// 최대 거리를 넘어 선 경우
	//{
	//	// 방향 변경
	//	m_iDir *= -1;
	//	// 초과한 거리를 반대 방향으로 더해줌
	//	vCurPos.x += fDist * m_iDir;
	//}

	//SetPos(vCurPos);

	// 06/11 적 애니메이션
	GetAnimator()->Play(L"Monster", true);
}


void CMonster::SetAI(AI* _AI)
{
	m_pAI = _AI; m_pAI->m_pOwner = this;
}

void CMonster::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();	// 부딪힌 상대의 object를 받아옴
	//// 부딪힌 상대 생각하기
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
