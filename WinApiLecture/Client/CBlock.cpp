
#include "pch.h"
#include "CBlock.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"



CBlock::CBlock()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(40.f, 40.f));

	CreateAnimator();
	// 캐릭터의 상태를 먼저 설정한 후 , 그 상태에 맞게 캐릭터의 애니메이션을 정하자.
	// 맞은 상태, 움직이는 상태, 점프 상태, 등등 그 상태의 전환을 완벽히 실행한 뒤
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"CoinTex", L"texture\\coin.bmp");

	GetAnimator()->CreateAnimation(
		L"IDEL_1",
		pTex,
		Vec2(0.f, 0.f),
		Vec2(3200.f, 3200.f),
		Vec2(3200.f, 0.f),
		0.2f,
		3);
	GetAnimator()->CreateAnimation(
	L"IDEL_2",
		pTex,
		Vec2(0.f, 3200.f),
		Vec2(3200.f, 3200.f),
		Vec2(3200.f, 0.f),
		0.2f,
		3);
}

CBlock::~CBlock()
{
}

void CBlock::update()
{
}

void CBlock::render(HDC _dc)
{
	Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);

	CObject::render(_dc);
}

void CBlock::OnCollisionEnter(CCollider* _pOther)
{
}

void CBlock::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();	// 부딪힌 상대의 object를 받아옴
	if (pOtherObj->GetName() == L"Missale_Player")
	{
		DeleteObject(this);
	}
}

void CBlock::OnCollisionExit(CCollider* _pOther)
{
}
