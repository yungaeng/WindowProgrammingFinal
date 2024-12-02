
#include "pch.h"
#include "CScene_5_5.h"
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

CScene_5_5::CScene_5_5()
	:m_bUseForce(false)
	, m_fForceRadius(500.f)
	, m_fCurRadius(0.f)
	, m_fForce(500.f)
{
}

CScene_5_5::~CScene_5_5()
{
}


void CScene_5_5::update()
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
					Vec2 vDiff = vecObj[j]->GetPos() - m_vForcePos;
					float fLen = vDiff.Length();
					// ��ü�� ���� �߻��� �������� �Ÿ���, ���� �ݰ溸�� ������ �� ��ü�� �ݰ� �ȿ� �ִ�
					if (fLen < m_fForceRadius)
					{
						// ���� �󸶳� �޴� ���� ���� ����
						float fRatio = 1.f - (fLen / m_fForceRadius);
						// ����� ��
						float fForce = m_fForce * fRatio;		// ����		*	����� ���� ũ��
						vecObj[j]->GetRigidBody()->AddForce(vDiff.Normalize() * fForce);

					}
				}
				vecObj[j]->update();
			}
		}
	}
}

void CScene_5_5::render(HDC _dc)
{
	CScene::render(_dc);

	if (!m_bUseForce)
		return;
	SelectGDI gdi1(_dc, BRUSH_TYPE::HOLLOW);
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

void CScene_5_5::Enter()
{
	// �ش� ���� ���۵� ��
	// CObject : CPlayer �߰�
	CObject* pObj = new CPlayer;
	pObj->SetName(L"Player");
	pObj->SetPos(Vec2(640.f, 384.f));
	pObj->SetScale(Vec2(100.f, 100.f));
	AddObject(pObj, GROUP_TYPE::PLAYER);

	// ���� ���� �÷��̾� ���
	RegisterPlayer(pObj);

	CreateBlock(MakeRandomInt(3, 10));

	// �÷��̾� �ڴٿ�ĳ���� ������� >> �ʹ� ��ϱ� clone�Լ� �����ؼ� ����
	/*CObject* pOtherPlayer = new CPlayer(*(CPlayer*)pObj);
	pOtherPlayer->SetPos(Vec2(740.f, 384.f));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	/*CObject* pOtherPlayer = pObj->Clone();
	pOtherPlayer->SetPos(Vec2(pObj->GetPos().x + 100, pObj->GetPos().y));
	AddObject(pOtherPlayer, GROUP_TYPE::PLAYER);*/

	// ī�޶� �÷��̾� ����ٴϱ�
	//CCamera::GetInst()->SetTarget(pObj);

	//// ���� ��ġ
	//// ���� ���丮�� ���� ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	CMonster* pMon = CMonFactory::CreateMonster(MON_TYPE::NORMAL, vResolution / 2.f - Vec2(0.f, 300.f));
	AddObject(pMon, GROUP_TYPE::MONSTER);

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
	//// �� ��ü ��ġ 
	//CObject* pGround = new CGround;
	//pGround->SetName(L"Ground");
	//pGround->SetPos(Vec2(640.f, 584.f));
	//pGround->SetScale(Vec2(600.f, 60.f));
	//AddObject(pGround, GROUP_TYPE::GROUND);



	// �浹 ����
	// Player �׷�� Monster �׷� ���� �浹 ����
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::MONSTER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);
	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::BLOCK);
//	CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::PLAYER, GROUP_TYPE::GROUND);
	//CCollisionMgr::GetInst()->CheckGroup(GROUP_TYPE::MONSTER, GROUP_TYPE::PROJ_PLAYER);


	// ī�޶� LookAt ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

	start();
}

void CScene_5_5::Exit()
{
	DeleteAll();

	// ���� �ش� ������ ������ ���� �浹 �׷��� ������ ���� ��
	CCollisionMgr::GetInst()->Reset();
}

void CScene_5_5::CreateForce()
{
	m_vForcePos = CCamera::GetInst()->GetRealPos(MOUSE_POS);
}
