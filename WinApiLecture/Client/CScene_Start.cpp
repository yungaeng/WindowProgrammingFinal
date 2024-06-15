#include "pch.h"
#include "CScene_Start.h"
#include "CObject.h"
#include "CPlayer.h"
#include "CMonster.h"
#include "CCore.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CCollisionMgr.h"
#include "CKeyMgr.h"
#include"CSceneMgr.h"
#include "CCamera.h"
#include"AI.h"
#include "CIdleState.h"
#include "CTraceState.h"
#include "CRigidBody.h"
#include "SelectGDI.h"
#include "CTimeMgr.h"
#include "CGround.h"
#include "CBlock.h"
#include "CFlag.h"
#include "CBackGround.h"

CScene_Start::CScene_Start()
	:m_bUseForce(false)
	,m_fForceRadius(500.f)
	,m_fCurRadius(0.f)
	,m_fForce(500.f)
{
}

CScene_Start::~CScene_Start()
{
}


void CScene_Start::update()
{
	// 오버라이딩 하긴 했지만 부모의 upadate 코드를 갖다 쓸 것이다.
	//CScene::update();
	// 이럼 오버라이딩 왜함?
	// + @ 뭔가를 더 하겠다.
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// 엔터키가 눌리면 TOOL_SCENE으로 바꾸겠다
	//	// 근데 바로 씬을 바꾸는 게 아니라 이벤트에 등록해서 업뎃-파이널업뎃-렌더가 끝난 후 이벤트 처리
	//	ChangeScene(SCENE_TYPE::TOOL);
	//	
	//}

	/*if (KEY_TAP(KEY::LBTN))
	{
		Vec2 LookAt = CCamera::GetInst()->GetRealPos(MOUSE_POS);
		CCamera::GetInst()->SetLookAt(LookAt);
	}*/
	if (KEY_HOLD(KEY::LBTN))
	{
		m_bUseForce = true;
		CreateForce();
	}
	else
	{
		m_bUseForce = false;
	}

	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		const vector<CObject*>& vecObj = GetGroupObject((GROUP_TYPE)(i));
		for (size_t j = 0; j < vecObj.size(); ++j)
		{
			if (!vecObj[j]->IsDead())
			{
				if (m_bUseForce && vecObj[j]->GetRigidBody())
				{
					Vec2 vDiff =  vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					// 물체와 힘이 발생한 지점간의 거리가, 힘의 반경보다 작으면 그 물체는 반경 안에 있다
					if (fLen < m_fForceRadius)
					{
						// 힘을 얼마나 받는 지에 대한 비율
						float fRatio = 1.f - (fLen / m_fForceRadius);
						// 적용될 힘
						float fForce = m_fForce* fRatio;		// 방향		*	적용될 힘의 크기
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
						
					}
				}
				// ★★★★★각오브젝트의 업데이트 수행★★★★★
				vecObj[j]->update();
			}
		}
	}
}

void CScene_Start::render(HDC _dc)
{
	CScene::render(_dc);

	//if (!m_bUseForce)
	//	return;
	//SelectGDI gdi1(_dc,BRUSH_TYPE::HOLLOW);
	//SelectGDI gdi2(_dc, PEN_TYPE::GREEN);

	/*m_fCurRadius += m_fForceRadius * 2.f * fDT;
	if (m_fCurRadius > m_fForceRadius)
	{
		m_fCurRadius = 0.f;
	}
	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(m_vForcePos);

	Ellipse(_dc
		, (int)(vRenderPos.x - m_fCurRadius)
		, (int)(vRenderPos.y - m_fCurRadius)
		, (int)(vRenderPos.x + m_fCurRadius)
		, (int)(vRenderPos.y + m_fCurRadius));*/
		//m_vForcePos;

	wchar_t wsCoin[100] = L"coin";
	wsprintfW(wsCoin, L"COIN : %d ", CCore::GetInst()->m_iCoin);
	TextOut(_dc, 10, 10, wsCoin, lstrlenW(wsCoin));
}

void CScene_Start::Enter()
{



	// 해당 신이 시작될 때
	// CObject : 백그라운드 추가
	CObject* pObj1 = new CBackGround;
	pObj1->SetName(L"BG");
	pObj1->SetPos(Vec2(0.f, 384.f));
	pObj1->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj1, GROUP_TYPE::BG);


	// CObject : CPlayer 추가
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(0.f,384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);



	// 현재 씬에 플레이어 등록
	RegisterPlayer(pObj);

	// 플레이어 ★다운캐스팅 복사생성 >> 너무 기니까 clone함수 구현해서 하자
	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(pObj->GetPos().x + 100, pObj->GetPos().y));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	// 카메라가 플레이어 따라다니기
	CCamera::GetInst()->SetTarget(pObj);

	//// 몬스터 배치
	//// 몬스터 팩토리를 통한 생성
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//CreateObject(pMon) 이벤트 등록을 통한 enter가 아닌 update 중 오브젝트 생성하기


	// 수동
	//int iMonCount = 1;
	////float fMoveDistance = 25.f;
	//float fObjScale = 50.f;
	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	////float fTerm = (vResolution.x - ((fMoveDistance + fObjScale/ 2.f) * 2)) / (float)(iMonCount - 1);
	//
	//// State를 가진 AI 생성
	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//pAI->AddState(new CTraceState);

	//CMonster* pMonsterObj = nullptr;
	//// CObject : CMonster 추가
	//for (int i = 0; i < iMonCount; ++i)
	//{
	//	// CObject : CMonster 추가
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetPos(vResolution / 2.f - Vec2(0.f,300.f));
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	// AI 설정
	//	pMonsterObj->SetAI(pAI);
	////	pMonsterObj->SetMoveDistance(fMoveDistance);
	////	pMonsterObj->SetCenterPos(pMonsterObj->GetPos());


	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}
	//LoadTile(L"Tile\\Start.tile");
	// 
	// 

	//// 땅 물체 배치 
	CObject* pGround1 = new CGround;
	pGround1->SetName(L"Ground");
	pGround1->SetPos(Vec2(3500.f, 800.f));
	pGround1->SetScale(Vec2(7000.f, 400.f));
	AddObject(pGround1, GROUP_TYPE::GROUND);

	CObject* pGround11 = new CGround;
	pGround11->SetName(L"Ground");
	pGround11->SetPos(Vec2(4000.f, 340.f));
	pGround11->SetScale(Vec2(700.f, 100.f));
	AddObject(pGround11, GROUP_TYPE::GROUND);

	CObject* pGround2 = new CGround;
	pGround2->SetName(L"Ground");
	pGround2->SetPos(Vec2(8700.f, 800.f));
	pGround2->SetScale(Vec2(3000.f, 400.f));
	AddObject(pGround2, GROUP_TYPE::GROUND);

	CObject* pGround21 = new CGround;
	pGround21->SetName(L"Ground");
	pGround21->SetPos(Vec2(9000.f, 340.f));
	pGround21->SetScale(Vec2(700.f, 100.f));
	AddObject(pGround21, GROUP_TYPE::GROUND);

	CObject* pGround22 = new CGround;
	pGround22->SetName(L"Ground");
	pGround22->SetPos(Vec2(10000.f, 140.f));
	pGround22->SetScale(Vec2(300.f, 100.f));
	AddObject(pGround22, GROUP_TYPE::GROUND);

	CObject* pGround23 = new CGround;
	pGround23->SetName(L"Ground");
	pGround23->SetPos(Vec2(11000.f, 340.f));
	pGround23->SetScale(Vec2(300.f, 100.f));
	AddObject(pGround23, GROUP_TYPE::GROUND);

	CObject* pGround24 = new CGround;
	pGround24->SetName(L"Ground");
	pGround24->SetPos(Vec2(113000.f, 340.f));
	pGround24->SetScale(Vec2(500.f, 100.f));
	AddObject(pGround24, GROUP_TYPE::GROUND);

	CObject* pGround3 = new CGround;
	pGround3->SetName(L"Ground");
	pGround3->SetPos(Vec2(12400.f, 800.f));
	pGround3->SetScale(Vec2(4000.f, 400.f));
	AddObject(pGround3, GROUP_TYPE::GROUND);

	CObject* pGround4 = new CGround;
	pGround4->SetName(L"Ground");
	pGround4->SetPos(Vec2(17600.f, 800.f));
	pGround4->SetScale(Vec2(6000.f, 400.f));
	AddObject(pGround4, GROUP_TYPE::GROUND);

	// 코인 추가
	for (int i = 0; i < 180; ++i)
	{
		CObject* pBlock = new CBlock;
		pBlock->SetName(L"Coin");
		pBlock->SetPos(Vec2(1000.f + 100.f * i, 500.f));
		pBlock->SetScale(Vec2(40.f, 40.f));
		AddObject(pBlock, GROUP_TYPE::COIN);
	}

	// 적 추가 4/2/6/2
	// 추후 몬스터 팩토리로 구현 예정
	// 몬스터 충돌 시 애니메이션 및 움직임 구현 후 변경 해주세요

	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);
	for (int i = 0; i < 4; ++i)
	{
	/*	CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(2000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);*/


		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(2000.f + 500.f * i, 540.f));
		AddObject(pMon, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 2; ++i)
	{
		/*CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(8000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);*/


		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(8000.f + 500.f * i, 540.f));
		AddObject(pMon, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 6; ++i)
	{
	/*	CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(11000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);*/


		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(11000.f + 500.f * i, 540.f));
		AddObject(pMon, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 2; ++i)
	{
		/*CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(16000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);*/


		CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, Vec2(16000.f + 500.f * i, 540.f));
		AddObject(pMon, GROUP_TYPE::MONSTER);
	}
	
	// 깃발 추가
	CObject* pFlag = new CFlag;
	pFlag->SetName(L"Flag");
	pFlag->SetPos(Vec2(20300.f, 540.f));
	pFlag->SetScale(Vec2(400.f, 400.f));
	AddObject(pFlag, GROUP_TYPE::FLAG);

	////테스트용 깃발 추가
	//CObject* pFlag2 = new CFlag;
	//pFlag2->SetName(L"Flag");
	//pFlag2->SetPos(Vec2(300.f, 540.f));
	//pFlag2->SetScale(Vec2(400.f, 400.f));
	//AddObject(pFlag2, GROUP_TYPE::FLAG);


	// 충돌 지정
	// Player 그룹과 Monster 그룹 간의 충돌 지정
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// 캐릭터와 충돌
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BLOCK);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::COIN);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FLAG);

	// 몬스터와 코인이 충돌하면 코인 삭제 06/13
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::COIN);

	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// 카메라 LookAt 지정
	//CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	// 기존 해당 씬에서 지정해 놨던 충돌 그룹을 해제해 놔야 함
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
