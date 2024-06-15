#include "pch.h"
#include "CScene_End.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CGround.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include"CSceneMgr.h"
#include "CCamera.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"

CScene_End::CScene_End()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_End::~CScene_End()
{
}

void CScene_End::update()
{

}

void CScene_End::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;
	SelectGDI gdi1(_dc,BRUSH_TYPE::HOLLOW);
	SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	m_fCurRadius += m_fForceRadius * 2.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));
		//m_vForcePos;

}

void CScene_End::Enter()
{
	// 해당 신이 시작될 때
	// CObject : CPlayer 추가
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(0.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// 현재 씬에 플레이어 등록
	RegisterPlayer(pObj);

	//// 몬스터 팩토리를 통한 생성
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	// 카메라가 플레이어 따라다니기
	CCamera::GetInst()->SetTarget(pObj);

	
	// 카메라 LookAt 지정
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	// 땅 물체 배치 
	CObject* pGround1 = new CGround;
	pGround1->SetName(L"Ground");
	pGround1->SetPos(Vec2(3500.f, 800.f));
	pGround1->SetScale(Vec2(7000.f, 400.f));
	AddObject(pGround1, GROUP_TYPE::GROUND);


	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);


	start();
}

void CScene_End::Exit()
{
	DeleteAll();

	// 기존 해당 씬에서 지정해 놨던 충돌 그룹을 해제해 놔야 함
	CCollisionMgr::GetInst()->Reset();
}





