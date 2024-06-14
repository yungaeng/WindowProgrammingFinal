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
	// �������̵� �ϱ� ������ �θ��� upadate �ڵ带 ���� �� ���̴�.
	//CScene::update();
	// �̷� �������̵� ����?
	// + @ ������ �� �ϰڴ�.
	//if (KEY_TAP(KEY::ENTER))
	//{
	//	// ����Ű�� ������ TOOL_SCENE���� �ٲٰڴ�
	//	// �ٵ� �ٷ� ���� �ٲٴ� �� �ƴ϶� �̺�Ʈ�� ����ؼ� ����-���̳ξ���-������ ���� �� �̺�Ʈ ó��
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
					// ��ü�� ���� �߻��� �������� �Ÿ���, ���� �ݰ溸�� ������ �� ��ü�� �ݰ� �ȿ� �ִ�
					if (fLen < m_fForceRadius)
					{
						// ���� �󸶳� �޴� ���� ���� ����
						float fRatio = 1.f - (fLen / m_fForceRadius);
						// ����� ��
						float fForce = m_fForce* fRatio;		// ����		*	����� ���� ũ��
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);
						
					}
				}
				
				vecObj[j]->update();
			}
		}
	}
}

void CScene_Start::render(HDC _dc)
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

	
	TextOutA(_dc, 10, 10, "COIN :", 10);
}

void CScene_Start::Enter()
{
	// �ش� ���� ���۵� ��
	// CObject : CPlayer �߰�
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(0.f,384.f));
	pObj->SetScale(Vec2(100.f,100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// ���� ���� �÷��̾� ���
	RegisterPlayer(pObj);

	// �÷��̾� �ڴٿ�ĳ���� ������� >> �ʹ� ��ϱ� clone�Լ� �����ؼ� ����
	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(pObj->GetPos().x + 100, pObj->GetPos().y));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	// ī�޶� �÷��̾� ����ٴϱ�
	CCamera::GetInst()->SetTarget(pObj);

	//// ���� ��ġ
	//// ���� ���丮�� ���� ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	//CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	//AddObject(pMon, GROUP_TYPE::MONSTER);

	//CreateObject(pMon) �̺�Ʈ ����� ���� enter�� �ƴ� update �� ������Ʈ �����ϱ�


	// ����
	//int iMonCount = 1;
	////float fMoveDistance = 25.f;
	//float fObjScale = 50.f;
	//Vec2 vResolution = CCore::GetInst()->GetResolution();
	////float fTerm = (vResolution.x - ((fMoveDistance + fObjScale/ 2.f) * 2)) / (float)(iMonCount - 1);
	//
	//// State�� ���� AI ����
	//AI* pAI = new AI;
	//pAI->AddState(new CIdleState);
	//pAI->AddState(new CTraceState);

	//CMonster* pMonsterObj = nullptr;
	//// CObject : CMonster �߰�
	//for (int i = 0; i < iMonCount; ++i)
	//{
	//	// CObject : CMonster �߰�
	//	pMonsterObj = new CMonster;
	//	pMonsterObj->SetName(L"Monster");
	//	pMonsterObj->SetPos(vResolution / 2.f - Vec2(0.f,300.f));
	//	pMonsterObj->SetScale(Vec2(fObjScale, fObjScale));
	//	// AI ����
	//	pMonsterObj->SetAI(pAI);
	////	pMonsterObj->SetMoveDistance(fMoveDistance);
	////	pMonsterObj->SetCenterPos(pMonsterObj->GetPos());


	//	AddObject(pMonsterObj, GROUP_TYPE::MONSTER);
	//}
	//LoadTile(L"Tile\\Start.tile");
	// 
	// 

	// �� ��ü ��ġ 
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
	AddObject(pGround21, GROUP_TYPE::GROUND);

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

	// ���� �߰�
	for (int i = 0; i < 180; ++i)
	{
		CObject* pBlock = new CBlock;
		pBlock->SetName(L"Coin");
		pBlock->SetPos(Vec2(1000.f + 100.f * i, 500.f));
		pBlock->SetScale(Vec2(40.f, 40.f));
		AddObject(pBlock, GROUP_TYPE::COIN);
	}

	// �� �߰� 4/2/6/2
	// ���� ���� ���丮�� ���� ����
	// ���� �浹 �� �ִϸ��̼� �� ������ ���� �� ���� ���ּ���
	for (int i = 0; i < 4; ++i)
	{
		CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(2000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 2; ++i)
	{
		CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(8000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 6; ++i)
	{
		CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(11000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);
	}
	for (int i = 0; i < 2; ++i)
	{
		CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(16000.f + 500.f * i, 540.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);
	}
	
	// ��� �߰�
	CObject* pFlag = new CFlag;
	pFlag->SetName(L"Flag");
	pFlag->SetPos(Vec2(20300.f, 540.f));
	pFlag->SetScale(Vec2(400.f, 400.f));
	AddObject(pFlag, GROUP_TYPE::FLAG);

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);

	// ĳ���Ϳ� �浹
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BLOCK);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::COIN);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::FLAG);

	// ���Ϳ� ������ �浹�ϸ� ���� ���� 06/13
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::COIN);

	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);

	// ī�޶� LookAt ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	start();
}

void CScene_Start::Exit()
{
	DeleteAll();

	// ���� �ش� ������ ������ ���� �浹 �׷��� ������ ���� ��
	CCollisionMgr::GetInst()->Reset();
}

void CScene_Start::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
