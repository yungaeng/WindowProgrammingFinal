#include "pch.h"
#include "CFlag.h"
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


CFlag::CFlag()
{
	CreateCollider();
	GetCollider()->SetOffsetPos(Vec2(0.f, 0.f));
	GetCollider()->SetScale(Vec2(140.f, 115.f));

	CreateAnimator();
	// ĳ������ ���¸� ���� ������ �� , �� ���¿� �°� ĳ������ �ִϸ��̼��� ������.
	// ���� ����, �����̴� ����, ���� ����, ��� �� ������ ��ȯ�� �Ϻ��� ������ ��


	// ==06.10 ����== coin2.bmp(��Ŀ� �°� ������ �̹���)�� �����ϵ��� ����
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"FlagTex", L"texture\\flag.bmp");

	//��� �ִϸ��̼�
	GetAnimator()->CreateAnimation(
		L"Flag",
		pTex,
		Vec2(0.f, 0.f),
		Vec2(148.f, 150.f),
		Vec2(149.f, 0.f),
		0.1f,
		6);
}

CFlag::~CFlag()
{
} 

void CFlag::update()
{
	GetAnimator()->Play(L"Flag", true);
}

void CFlag::render(HDC _dc)
{
	Component_render(_dc);
}

void CFlag::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();	// �ε��� ����� object�� �޾ƿ�
	if (pOtherObj->GetName() == L"Player")
		ChangeScene(SCENE_TYPE::EnD);
}

void CFlag::OnCollision(CCollider* _pOther)
{
	
}

void CFlag::OnCollisionExit(CCollider* _pOther)
{
}
