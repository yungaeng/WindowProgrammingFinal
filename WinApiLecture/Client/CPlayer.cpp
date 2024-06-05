#include "pch.h"
#include "CPlayer.h"
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
#include "CRigidBody.h"
#include "CGravity.h"


CPlayer::CPlayer()
	//:m_pTex(nullptr)
	:m_eCurState(PLAYER_STATE::IDLE)
	,m_ePrevState(PLAYER_STATE::WALK)
	,m_iDir(1)
	,m_iPrevDir(1)
	,m_iJumpStack(2)
{
	// ��ü �߰�
	CreateRigidBody();


	//// Texture �ε��ϱ�
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\airp.bmp");
	CreateCollider();
	// �浹ü�� offset�� �����Ͽ� ���̳� pos ����� �׸�ŭ �̵����� �����Ŵ
	GetCollider()->SetOffsetPos(Vec2(-2.f, 12.f));

	// �浹ü�� ũ�� ����
	GetCollider()->SetScale(Vec2(25.f, 40.f));



	// �ִϸ����� ������Ʈ ����
	CreateAnimator();
	// ĳ������ ���¸� ���� ������ �� , �� ���¿� �°� ĳ������ �ִϸ��̼��� ������.
	// ���� ����, �����̴� ����, ���� ����, ��� �� ������ ��ȯ�� �Ϻ��� ������ ��
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\link.bmp");
	

	GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_top.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_idle_bottom.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");
	//GetAnimator()->CreateAnimation(
	//	L"IDLE_BOTTOM",
	//	pTex,
	//	Vec2(0.f, 0.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	0.5f,
	//	3);
	//GetAnimator()->CreateAnimation(
	//	L"IDLE_TOP",
	//	pTex,
	//	Vec2(0.f, 0.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	1.f,
	//	1);
	//GetAnimator()->CreateAnimation(
	//	L"WALK_LEFT",
	//	pTex,
	//	Vec2(0.f, 325.f), 
	//	Vec2(60.f, 65.f), 
	//	Vec2(60.f, 0.f),
	//	0.1f,
	//	10);
	//GetAnimator()->CreateAnimation(
	//	L"WALK_RIGHT",
	//	pTex,
	//	Vec2(0.f, 455.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	0.1f,
	//	10);
	//GetAnimator()->CreateAnimation(
	//	L"JUMP_LEFT",
	//	pTex,
	//	Vec2(0.f, 65.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	0.2f,
	//	1);

	//GetAnimator()->CreateAnimation(
	//	L"JUMP_RIGHT",
	//	pTex,
	//	Vec2(0.f, 195.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	0.2f,
	//	1);
	//// Animation �����غ���
	//GetAnimator()->FindAnimation(L"IDLE_TOP")->Save(L"animation\\player_idle_top.anim");
	//GetAnimator()->FindAnimation(L"IDLE_BOTTOM")->Save(L"animation\\player_idle_bottom.anim");
	//GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
	//GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");
	//GetAnimator()->FindAnimation(L"JUMP_RIGHT")->Save(L"animation\\player_jump_right.anim");
	// �߷� ������Ʈ ����
	CreateGravity();
	//GetAnimator()->Play(L"IDLE_BOTTOM", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE_BOTTOM");
	//for(UINT i = 0; i < pAnim->GetMaxFream(); ++i)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f,-20.f);		// 0�� ������

}

CPlayer::~CPlayer()
{
	
}
void CPlayer::update()
{
	
	update_move();

	update_state();

	update_animation();

	// �θ�(CObject)�� ��� ������ m_vPos�� private�̹Ƿ� ���� ������ �Ұ���, GetPos�� ���� ���� ����)
	//Vec2 vPos = GetPos();
	
	//if (KEY_TAP(KEY::SPACE))
	//{

	//	//CreateMissile();
	//}
	
	

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}


	// �θ���Ʈ�� ��� ���� m_vPos�� ������ vPos������ Set
//	SetPos(vPos);

	GetAnimator()->update();


	m_ePrevState = m_eCurState;
	m_iPrevDir = m_iDir;
}

void CPlayer::render(HDC _dc)
{
	//CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"Plane", L"texture\\aaa.bmp");
	//Vec2 vPos = GetPos();
	//vPos = CCamera::GetInst()->GetRenderPos(vPos);

	//float width = (float)pTex->Width();
	//float height = (float)pTex->Height();

	//BLENDFUNCTION bf = {};
	//bf.BlendOp = AC_SRC_OVER;
	//bf.BlendFlags = 0;
	//bf.AlphaFormat = AC_SRC_ALPHA;
	//bf.SourceConstantAlpha = 127;

	///*AlphaBlend(_dc
	//	, vPos.x - width / 2.f
	//	, vPos.y - height / 2.f
	//	,width,height
	//	,pTex->GetDC()
	//	,0,0,width,height
	//	,bf);*/
	// 
	//// �ȼ� ũ�� ��ü�� UINT����, ���߿� ��ġ�� �Է��� �� ������ �Է��� �� �ֵ��� int�� ĳ����
	//int iWidth = (int)pTex->Width();
	//int iHeight = (int)pTex->Height();

	////Vec2 vPos = GetPos();

	//
	///*
	//BitBlt(_dc,
	//	vPos.x - (float)(iWidth / 2)
	//	, vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, m_pTex->GetDC()
	//	, 0, 0, SRCCOPY);*/

	//TransparentBlt(_dc,
	//	vPos.x - (float)(iWidth / 2)
	//	, vPos.y - (float)(iHeight / 2)
	//	, iWidth, iHeight
	//	, pTex->GetDC()
	//	,0,0,iWidth,iHeight
	//	,RGB(255,255,255));
	//

	// ������Ʈ(�浹ü, etc...)�� �ִ� ��� ����
	// �ִϸ��̼��� �ִ� ��� ���� �ؽ��İ� �ƴ� ������ ������ �ִϸ��̼��� ������ ����
	Component_render(_dc);
}

void CPlayer::CreateMissile()
{
	Vec2 vMissalePos = GetPos();
	vMissalePos.y -= GetScale().y / 2.f;

	// Missile Object
	CMissile* pMissale = new CMissile;
	pMissale->SetName(L"Missale_Player");
	pMissale->SetPos(vMissalePos);
	pMissale->SetScale(Vec2(25.f, 25.f));
	pMissale->SetDir(Vec2(0.f, -1.f));

	CreateObject(pMissale, GROUP_TYPE::PROJ_PLAYER);
}

void CPlayer::update_state()
{
	// �����ϰ� ���¸� ���� ��Ű��			else if�� �����ϸ� ��⸦ ������ �� ����
	if (KEY_HOLD(KEY::A))
	{
		m_iDir = -1;
		if(PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if (KEY_HOLD(KEY::D))
	{
		m_iDir = 1;
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}
	if(GetRigidBody())
	{
		if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
	
	if (KEY_TAP(KEY::SPACE))
	{
		m_eCurState = PLAYER_STATE::JUMP;
		if(m_iJumpStack > 0)
		if (GetRigidBody())
		{
			--m_iJumpStack;
			GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -400.f));
		}
	}
}

void CPlayer::update_move()
{


	CRigidBody* pRigid = GetRigidBody();

	//��� �����̰�
	pRigid->AddForce(Vec2(800.f, 0.f));
	pRigid->SetVelocity(Vec2(200.f, pRigid->GetVelocity().y));

	//if (KEY_HOLD(KEY::W))
	//{
	//	pRigid->AddForce(Vec2(0.f, -200.f));
	//}
	//if (KEY_HOLD(KEY::S))
	//{
	//	pRigid->AddForce(Vec2(0.f, 200.f));
	//}
	if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}
	//if (KEY_TAP(KEY::W))
	//{
	//	pRigid->AddVelocity(Vec2(0.f, -100.f));
	//}
	/*if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}*/
	if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}
}

void CPlayer::update_animation()
{
	//��� �ȴ»�������
	GetAnimator()->Play(L"WALK_RIGHT", true);

	// ���°� ������� �ʾҴٸ� ����
	if (m_ePrevState == m_eCurState && m_iPrevDir == m_iDir)
	{
		return;
	}

	switch (m_eCurState)
	{
	case PLAYER_STATE::IDLE:
	{
		//if(m_iDir)
		GetAnimator()->Play(L"IDLE_BOTTOM", true);
	}

	break;
	case PLAYER_STATE::WALK:
	{
		if (m_iDir == 1)
			GetAnimator()->Play(L"WALK_RIGHT", true);
		else
			GetAnimator()->Play(L"WALK_LEFT", true);
	}
	break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DAMAGED:

		break;
	case PLAYER_STATE::DEAD:
		 
		break;
	case PLAYER_STATE::JUMP:
	{
		if (m_iDir == 1)
			GetAnimator()->Play(L"JUMP_RIGHT", true);
		else
			GetAnimator()->Play(L"JUMP_LEFT", true);

	}
	break;
	}
}

//void CPlayer::update_gravity()
//{
//	// �׻� ����Ǵ� �Ʒ��������� 500�� ��
//	GetRigidBody()->AddForce(Vec2(0.f,500.f));
//}

void CPlayer::OnCollisionEnter(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		Vec2 vPos = GetPos();
		Vec2 vOtherPos = pOtherObj->GetPos();
		if (vPos.y < vOtherPos.y)
		{
			m_iJumpStack = 2;
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}
}

//void CPlayer::render()
//{
//	
//}
