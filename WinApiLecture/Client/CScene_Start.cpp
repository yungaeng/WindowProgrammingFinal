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

	//ī

	// ī�޶� �߽��� ��ǥ
	float Acctime= 0.f;
	Acctime += fDT;
	
	if(Acctime >=1.f)
	{
		CObject* pBlock = new CBlock;
		pBlock->SetName(L"Coin");
		pBlock->SetPos(Vec2(CCamera::GetInst()->GetLookAt().x + 100.f, 500.f));
		pBlock->SetScale(Vec2(60.f, 60.f));
		CreateObject(pBlock, GROUP_TYPE::BLOCK);
		Acctime = 0.f;
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
	// �� ��ü ��ġ 
	CObject* pGround1 = new CGround;
	pGround1->SetName(L"Ground");
	pGround1->SetPos(Vec2(3500.f, 800.f));
	pGround1->SetScale(Vec2(7000.f, 400.f));
	AddObject(pGround1, GROUP_TYPE::GROUND);

	CObject* pGround2 = new CGround;
	pGround2->SetName(L"Ground");
	pGround2->SetPos(Vec2(8700.f, 800.f));
	pGround2->SetScale(Vec2(3000.f, 400.f));
	AddObject(pGround2, GROUP_TYPE::GROUND);

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

	// ���ε� �߰�
	for (int i = 0; i < 4; ++i)
	{
		CObject* pBlock = new CBlock;
		pBlock->SetName(L"Block");
		pBlock->SetPos(Vec2(3500.f+500.f*i, 600.f-100.f*i));
		pBlock->SetScale(Vec2(100.f, 500.f));
		AddObject(pBlock, GROUP_TYPE::BLOCK);
	}

	// ���� �߰�
	/*for (int i = 0; i < 600; ++i)
	{
		CObject* pBlock = new CBlock;
		pBlock->SetName(L"Coin");
		pBlock->SetPos(Vec2(0.f + 101.f * i, 500.f));
		pBlock->SetScale(Vec2(40.f, 40.f));
		AddObject(pBlock, GROUP_TYPE::COIN);
	}*/

	// �� �߰�
	for (int i = 0; i < 60; ++i)
	{
		CObject* pMonster = new CMonster;
		pMonster->SetName(L"Monster");
		pMonster->SetPos(Vec2(0.f + 1000.f * i, 480.f));
		pMonster->SetScale(Vec2(40.f, 40.f));
		AddObject(pMonster, GROUP_TYPE::MONSTER);
	}

	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BLOCK);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::COIN);
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
