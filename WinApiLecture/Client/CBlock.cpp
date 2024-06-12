
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
#include "CGravity.h"



CBlock::CBlock()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(100.f, 100.f));

	CreateAnimator();
	// 캐릭터의 상태를 먼저 설정한 후 , 그 상태에 맞게 캐릭터의 애니메이션을 정하자.
	// 맞은 상태, 움직이는 상태, 점프 상태, 등등 그 상태의 전환을 완벽히 실행한 뒤


	// ==06.10 수정== coin2.bmp(양식에 맞게 수정한 이미지)를 참조하도록 변경
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"CoinTex", L"texture\\coin2.bmp");


	// ==06.10 수정==	(양식에 맞게 애니메이션 조정)
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
	// ==06.10 수정== 코인이 돌아가는 상태의 애니메이션 선택
	GetAnimator()->Play(L"IDEL_1", true);

}

void CBlock::render(HDC _dc)
{
	/*Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);*/


	// ==06.10 수정== 코인이 아니면 CObject렌더 사용, 코인이면 컴포넌트(애니메이션) 랜더 사용
	if (L"Coin" != GetName())
		CObject::render(_dc);

	else
		Component_render(_dc);
	
}

void CBlock::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (pOtherObj->GetName() == L"Player")
	{
		pOtherObj->GetGravity()->SetGround(true);

		Vec2 vObjPos = _pOther->GetFinalPos();
		Vec2 vObjScale = _pOther->GetScale();

		Vec2 vPos = GetCollider()->GetFinalPos();
		Vec2 vScale = GetCollider()->GetScale();

		// 두 세로 반경의 절반 간의 합 - 두 중심점과의 차이 = 파고든 거리
		float fLen = abs(vObjPos.y - vPos.y);
		float fValue = (vObjScale.y / 2.f + vScale.y / 2.f) - fLen;

		// 파고든 거리만큼 올려줌
		vObjPos = pOtherObj->GetPos();
		vObjPos.y -= (fValue);
		pOtherObj->SetPos(vObjPos);
	}
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
