
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

	// 06.10 - Coin2 이미지 제작, 그 이미지를 텍스처로 사용
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"CoinTex", L"texture\\coin2.bmp");


	// 06.10 - 코인 이미지 애니메이션 생성
	GetAnimator()->CreateAnimation(
		L"IDEL_1",
		pTex,
		Vec2(0.f, 0.f),
		Vec2(101.f, 115.f),
		Vec2(103.5f, 0.f),
		0.2f,
		6);

	GetAnimator()->CreateAnimation(
	L"IDEL_2",
		pTex,
		Vec2(0.f, 3200.f),
		Vec2(3200.f, 3200.f),
		Vec2(3200.f, 0.f),
		0.2f,
		2);
}

CBlock::~CBlock()
{
}

void CBlock::update()
{
	// 06.10 재생할 애니메이션 선택
	GetAnimator()->Play(L"IDEL_1", true);

}

void CBlock::render(HDC _dc)
{
	/*Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);*/

	// 06.10 코인인 경우 애니메이션 렌더하도록 선택
	if (L"Coin" != GetName())
		CObject::render(_dc);

	else
		Component_render(_dc);
	
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
