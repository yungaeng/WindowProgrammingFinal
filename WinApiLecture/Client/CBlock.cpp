
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
	// ĳ������ ���¸� ���� ������ �� , �� ���¿� �°� ĳ������ �ִϸ��̼��� ������.
	// ���� ����, �����̴� ����, ���� ����, ��� �� ������ ��ȯ�� �Ϻ��� ������ ��


	// ==06.10 ����== coin2.bmp(��Ŀ� �°� ������ �̹���)�� �����ϵ��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"CoinTex", L"texture\\coin2.bmp");


	// ==06.10 ����==	(��Ŀ� �°� �ִϸ��̼� ����)
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
	// ==06.10 ����== ������ ���ư��� ������ �ִϸ��̼� ����
	GetAnimator()->Play(L"IDEL_1", true);

}

void CBlock::render(HDC _dc)
{
	/*Vec2 vPos = GetPos();
	vPos = CCamera::GetInst()->GetRenderPos(vPos);*/


	// ==06.10 ����== ������ �ƴϸ� CObject���� ���, �����̸� ������Ʈ(�ִϸ��̼�) ���� ���
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
	CObject* pOtherObj = _pOther->GetObj();	// �ε��� ����� object�� �޾ƿ�
	if (pOtherObj->GetName() == L"Missale_Player")
	{
		DeleteObject(this);
	}
}

void CBlock::OnCollisionExit(CCollider* _pOther)
{
}
