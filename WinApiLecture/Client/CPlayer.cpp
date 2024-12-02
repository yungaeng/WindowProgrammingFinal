#include "pch.h"
#include "CCore.h"
#include "CPlayer.h"
#include "CKeyMgr.h"
#include "CTimeMgr.h"
#include "CMissile.h"
#include "CSceneMgr.h"
#include "CScene.h"

#include "CPathMgr.h"
#include "CResMgr.h"
#include "CTexture.h"
#include "CSound.h"
#include "CCollider.h"
#include "CAnimator.h"
#include "CAnimation.h"
#include "CRigidBody.h"
#include "CGravity.h"
#include "CMonster.h"


CPlayer::CPlayer()
//:m_pTex(nullptr)
	:m_eCurState(PLAYER_STATE::IDLE)
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_eCurJumpState(PLAYER_JUMP_STATE::JUMP_UP)
	, m_ePrevJumpState(PLAYER_JUMP_STATE::JUMP_DOWN)
	, m_eCurGiantState(PLAYER_GIANT_STATE::GIANT_NOT)
	, m_ePrevGiantState(PLAYER_GIANT_STATE::GIANT_ESCAPE)
	, m_iJumpStack(2)
	,m_fGiantTime(0.f)
	,m_fDeatTime(0.f)
	,m_iHP(5)
	,m_fSlowTime(3)
	,m_bSlow(false)
	,m_bDir(false)
{
	// ��ü �߰�
	CreateRigidBody();


	//// Texture �ε��ϱ�
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\airp.bmp");
	CreateCollider();

	// �浹ü offset�� �浹ü ũ�� ����
	// �浹ü�� offset�� �����Ͽ� ���̳� pos ����� �׸�ŭ �̵����� �����Ŵ
	GetCollider()->SetOffsetPos(Vec2(10.f, 0.f));
	// �浹ü�� ũ�� ����
	GetCollider()->SetScale(Vec2(80.f, 130.f));

	SetScale(Vec2(10.f, 10.f));

	// �ִϸ����� ������Ʈ ����
	CreateAnimator();
	// ĳ������ ���¸� ���� ������ �� , �� ���¿� �°� ĳ������ �ִϸ��̼��� ������.
	// ���� ����, �����̴� ����, ���� ����, ��� �� ������ ��ȯ�� �Ϻ��� ������ ��
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Brave_Cookie.bmp");


	//GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	// walk error - ��Ȱ��ȭ 06/10
	//GetAnimator()->LoadAnimation(L"animation\\player_walk_right.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_idle_top.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_idle_bottom.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_left.anim");
	//GetAnimator()->LoadAnimation(L"animation\\player_jump_right.anim");*/
	//GetAnimator()->CreateAnimation(
	//	L"IDLE_BOTTOM",
	//	pTex,
	//	Vec2(5.f, 550.f),
	//	Vec2(265.f, 265.f),
	//	Vec2(0.f, 270.f),
	//	0.5f,
	//	2);
	//GetAnimator()->CreateAnimation(
	//	L"IDLE_TOP",
	//	pTex,
	//	Vec2(0.f, 0.f),
	//	Vec2(60.f, 65.f),
	//	Vec2(60.f, 0.f),
	//	1.f,
	//	1);
	/*GetAnimator()->CreateAnimation(
		L"WALK_LEFT",
		pTex,
		Vec2(0.f, 325.f),
		Vec2(60.f, 65.f),
		Vec2(60.f, 0.f),
		0.1f,
		10);*/

		// �� �� ũ�� 272 x 272
		// walk state error 06/10
	GetAnimator()->CreateAnimation(
		L"WALK_RIGHT",
		pTex,
		Vec2(5.f, 410.f),
		Vec2(267.f, 133.f),
		Vec2(272.f, 0.f),
		0.1f,
		4);
	/*GetAnimator()->CreateAnimation(
		L"JUMP_LEFT",
		pTex,
		Vec2(0.f, 65.f),
		Vec2(60.f, 65.f),
		Vec2(60.f, 0.f),
		0.2f,
		1);*/
	GetAnimator()->CreateAnimation(
		L"JUMP_UP",
		pTex,
		Vec2(5.f, 1430.f),
		Vec2(260.f, 140.f),
		Vec2(272.f, 0.f),
		0.1f,
		1);
	GetAnimator()->CreateAnimation(
		L"JUMP_AIR",
		pTex,
		Vec2(277.f, 1365.f),
		Vec2(267.f, 130.f),
		Vec2(272.f, 0.f),
		0.2f,
		2);

	GetAnimator()->CreateAnimation(
		L"JUMP_DOWN",
		pTex,
		Vec2(820.f, 1475.f),
		Vec2(267.f, 140.f),
		Vec2(272.f, 0.f),
		0.1f,
		2);
	GetAnimator()->CreateAnimation(
		L"DOUBLE_JUMP_UP",
		pTex,
		Vec2(277.f, 130.f),
		Vec2(267.f, 140.f),
		Vec2(272.f, 0.f),
		0.1f,
		3);
	GetAnimator()->CreateAnimation(
		L"DOUBLE_JUMP_AIR",
		pTex,
		Vec2(1090.f, 140.f),
		Vec2(267.f, 130.f),
		Vec2(272.f, 0.f),
		0.1f,
		1);

	GetAnimator()->CreateAnimation(
		L"Dead",
		pTex,
		Vec2(1362.f, 1220.f),
		Vec2(268.f, 130.f),
		Vec2(272.f, 0.f),
		0.1f,
		5);

	GetAnimator()->CreateAnimation(
		L"Dead_s",
		pTex,
		Vec2(2450.f, 1220.f),
		Vec2(268.f, 130.f),
		Vec2(272.f, 0.f),
		5.f,
		1);

	// Animation �����غ���
//	GetAnimator()->FindAnimation(L"IDLE_TOP")->Save(L"animation\\player_idle_top.anim");
	//GetAnimator()->FindAnimation(L"IDLE_BOTTOM")->Save(L"animation\\player_idle_bottom.anim");
//	GetAnimator()->FindAnimation(L"WALK_LEFT")->Save(L"animation\\player_walk_left.anim");
//	GetAnimator()->FindAnimation(L"WALK_RIGHT")->Save(L"animation\\player_walk_right.anim");
	//GetAnimator()->FindAnimation(L"JUMP_LEFT")->Save(L"animation\\player_jump_left.anim");
	GetAnimator()->FindAnimation(L"JUMP_UP")->Save(L"animation\\player_jump.anim");
	GetAnimator()->FindAnimation(L"JUMP_DOWN")->Save(L"animation\\player_jump_down.anim");
	GetAnimator()->FindAnimation(L"JUMP_AIR")->Save(L"animation\\player_jump_air.anim");
	GetAnimator()->FindAnimation(L"DOUBLE_JUMP_UP")->Save(L"animation\\player_double_jump_up.anim");
	GetAnimator()->FindAnimation(L"DOUBLE_JUMP_AIR")->Save(L"animation\\player_double_jump_air.anim");


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

	if (KEY_TAP(KEY::D))
	{
		if (m_iHP != 0)
		{
			m_iHP = 0;
			m_fDeatTime = 0.f;
		}
		else
			m_iHP = 1;
	}



	// �θ���Ʈ�� ��� ���� m_vPos�� ������ vPos������ Set
//	SetPos(vPos);

	GetAnimator()->update();

	// ���� ���
	m_ePrevState = m_eCurState;
	m_ePrevJumpState = m_eCurJumpState;
	m_ePrevGiantState = m_eCurGiantState;
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
	//// �����ϰ� ���¸� ���� ��Ű��			else if�� �����ϸ� ��⸦ ������ �� ����
	//if (KEY_HOLD(KEY::A))
	//{
	if (m_iHP <= 0)
	{
		m_eCurState = PLAYER_STATE::DEAD;
		return;
	}


	if (PLAYER_STATE::JUMP != m_eCurState && PLAYER_STATE::GIANT != m_eCurState)
		m_eCurState = PLAYER_STATE::WALK;
	/*}
	if (KEY_HOLD(KEY::D))
	{
		if (PLAYER_STATE::JUMP != m_eCurState)
			m_eCurState = PLAYER_STATE::WALK;
	}*/
	/*if(GetRigidBody())
	{
		if (0.f == GetRigidBody()->GetSpeed() && PLAYER_STATE::JUMP != m_eCurState)
		{
			m_eCurState = PLAYER_STATE::IDLE;
		}
	}*/
	if (KEY_TAP(KEY::SPACE))
	{
		if (m_iJumpStack > 0)
			m_eCurState = PLAYER_STATE::JUMP;

	}
	// JUMP ������ ��� �ӵ��� ���� �з��ϱ�
	if (m_eCurState == PLAYER_STATE::JUMP)
	{
		if (m_iJumpStack == 1)
		{
			if (GetRigidBody()->GetVelocity().y < -50.f)
				m_eCurJumpState = PLAYER_JUMP_STATE::JUMP_UP;
			else if (GetRigidBody()->GetVelocity().y >= -50.f
				&& GetRigidBody()->GetVelocity().y <= 300)
				m_eCurJumpState = PLAYER_JUMP_STATE::JUMP_AIR;
			else
				m_eCurJumpState = PLAYER_JUMP_STATE::JUMP_DOWN;
		}
		else if (m_iJumpStack == 0)
		{
			if (GetRigidBody()->GetVelocity().y < -50.f)
				m_eCurJumpState = PLAYER_JUMP_STATE::DOUBLE_JUMP_UP;
			else if (GetRigidBody()->GetVelocity().y >= -50.f
				&& GetRigidBody()->GetVelocity().y <= 300)
				m_eCurJumpState = PLAYER_JUMP_STATE::JUMP_AIR;
			else
				m_eCurJumpState = PLAYER_JUMP_STATE::JUMP_DOWN;
		}
	}


	// GIANT ���� �з��ϱ�
	if (m_eCurGiantState == PLAYER_GIANT_STATE::GIANT_ENTER)
	{
		Vec2 vPos = GetPos();
		Vec2 vScale = GetScale();
		Vec2 vCScale = GetCollider()->GetScale();
			if (m_fGiantTime <= 1.f)
			{
				vPos -= Vec2(0.f, 133.f) * fDT;
				if (vScale.x <= 801.f && vScale.y <= 399.f)
				{
					vScale += Vec2(534.f, 266.f) * fDT;
					vCScale += Vec2(160.f, 260.f) * fDT;
					SetPos(vPos);
					SetScale(vScale);
					GetCollider()->SetScale(vCScale);
				}
			}
			else if (m_fGiantTime > 1.f && m_fGiantTime <4.f)
			{
			//	m_eCurGiantState = PLAYER_GIANT_STATE::GIANT_ENTER;
				GetCollider()->SetScale(Vec2(240.f, 390.f));
			}
			else if (m_fGiantTime >= 4.f && m_fGiantTime < 5.f)
			{
				/*m_eCurGiantState = PLAYER_GIANT_STATE::GIANT_ESCAPE;*/
				vPos += Vec2(0.f, 133.f) * fDT;
				if (vScale.x >= 267.f && vScale.y >= 133.f )
				{
					vScale -= Vec2(534.f, 266.f) * fDT;
					vCScale -= Vec2(160.f, 260.f) * fDT;
					SetPos(vPos);
					SetScale(vScale);
					GetCollider()->SetScale(vCScale);
				}
			}
			else if (m_fGiantTime >= 5.f)
			{
				m_eCurGiantState = PLAYER_GIANT_STATE::GIANT_NOT;
				SetScale(Vec2(267.f, 133.f));
				m_fGiantTime = 0;
				GetCollider()->SetScale(Vec2(80.f,130.f));
			}
			m_fGiantTime += fDT;
	}
}

void CPlayer::update_move()
{
	CRigidBody* pRigid = GetRigidBody();
	// ���� ���� üũ (�ö󰡴� ������ �������� ������)
	if (pRigid->GetVelocity().y >= 0)
		m_bDir = false;
	else if (pRigid->GetVelocity().y < 0)
		m_bDir = true;

	if (m_eCurState == PLAYER_STATE::DEAD)
		return;

	

	// ���ο� üũ
	if (m_bSlow)
	{
		pRigid->SetMaxVelocity(Vec2(150.f, 600.f));
		m_fSlowTime -= fDT;
		if (m_fSlowTime <= 0)
		{
			pRigid->SetMaxVelocity(Vec2(200.f, 600.f));
			m_bSlow = false;
			m_fSlowTime = 3.f;
		}
	}




	//��� �����̰�
	pRigid->AddForce(Vec2(300.f, 0.f));
	pRigid->SetVelocity(Vec2(300.f, pRigid->GetVelocity().y));

	//if (KEY_HOLD(KEY::W))
	//{
	//	pRigid->AddForce(Vec2(0.f, -200.f));
	//}
	//if (KEY_HOLD(KEY::S))
	//{
	//	pRigid->AddForce(Vec2(0.f, 200.f));
	//}
	/*if (KEY_HOLD(KEY::A))
	{
		pRigid->AddForce(Vec2(-200.f, 0.f));
	}
	if (KEY_HOLD(KEY::D))
	{
		pRigid->AddForce(Vec2(200.f, 0.f));
	}*/
	//if (KEY_TAP(KEY::W))
	//{
	//	pRigid->AddVelocity(Vec2(0.f, -100.f));
	//}
	/*if (KEY_TAP(KEY::S))
	{
		pRigid->AddVelocity(Vec2(0.f, 100.f));
	}*/
	/*if (KEY_TAP(KEY::A))
	{
		pRigid->SetVelocity(Vec2(-100.f, pRigid->GetVelocity().y));
	}
	if (KEY_TAP(KEY::D))
	{
		pRigid->SetVelocity(Vec2(100.f, pRigid->GetVelocity().y));
	}*/
	if (KEY_TAP(KEY::SPACE))
	{	
		if (m_iJumpStack > 0)
			if (GetRigidBody())
			{
				// 06/16 ���� �߰�
				CResMgr::GetInst()->LoadSound(L"Jump_01", L"sound\\Jump.wav");
				CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Jump_01");

				pNewSound->Play();

				pNewSound->SetPosition(0.f);			// �����, ��� ��ġ ���� ex 50% ����
				pNewSound->SetVolume(30.f);				// 0~100 ���� ���� ����
				--m_iJumpStack;
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
			}
	}
}

void CPlayer::update_animation()
{
	// ���°� ������� �ʾҴٸ� ����
	if (m_eCurState != PLAYER_STATE::DEAD && m_ePrevState == m_eCurState && m_eCurJumpState == m_ePrevJumpState)
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
		GetAnimator()->Play(L"WALK_RIGHT", true);
	}
	break;
	case PLAYER_STATE::ATTACK:

		break;
	case PLAYER_STATE::DAMAGED:

		break;
	case PLAYER_STATE::DEAD:
		if (m_fDeatTime <= 0.4f)
			GetAnimator()->Play(L"Dead", false);
		else
			GetAnimator()->Play(L"Dead_s", true);
		m_fDeatTime += fDT;
		break;
	case PLAYER_STATE::JUMP:
	{
		// �Ϲ� ������ ���
		if (m_iJumpStack == 1)
		{ 
			switch (m_eCurJumpState)
			{
			case PLAYER_JUMP_STATE::JUMP_UP:
				GetAnimator()->Play(L"JUMP_UP", true);
				break;
			case PLAYER_JUMP_STATE::JUMP_AIR:
				GetAnimator()->Play(L"JUMP_AIR", true);
				break;
			case PLAYER_JUMP_STATE::JUMP_DOWN:
				GetAnimator()->Play(L"JUMP_DOWN", true);
				break;
			default:
				break;
			}
		}
		// ���� ������ ���
		if (m_iJumpStack == 0)
		{
			switch (m_eCurJumpState)
			{
			case PLAYER_JUMP_STATE::DOUBLE_JUMP_UP:
				GetAnimator()->Play(L"DOUBLE_JUMP_UP", true);
				break;
			case PLAYER_JUMP_STATE::JUMP_AIR:
				GetAnimator()->Play(L"DOUBLE_JUMP_AIR", true);
				break;
			case PLAYER_JUMP_STATE::JUMP_DOWN:
				GetAnimator()->Play(L"JUMP_DOWN", true);
				break;
			default:
				break;
			}
		}
		/*else
			GetAnimator()->Play(L"JUMP_LEFT", true);
			*/
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

		if (GetRigidBody()->GetVelocity().y == 0)
		{
			m_iJumpStack = 2;
 			m_eCurState = PLAYER_STATE::WALK;
		}
	}
	if (L"Coin" == pOtherObj->GetName())
	{
		// 06/15 ���� ���� ����
		CCore::GetInst()->m_iCoin += 1;
	}
	// 06 / 16 ���� 
	if (L"Big_Potion" == pOtherObj->GetName())
	{
		m_fGiantTime = 0;
		m_eCurGiantState = PLAYER_GIANT_STATE::GIANT_ENTER;
	}
	if (L"Banana" == pOtherObj->GetName())
	{
		m_bSlow = true;
	}
	if (L"Monster" == pOtherObj->GetName() && m_eCurState != PLAYER_STATE::DEAD)
	{
		// 06/16 ���� �߰�
		CResMgr::GetInst()->LoadSound(L"Attack_01", L"sound\\Mon_attack.wav");
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Attack_01");
		pNewSound->Play();
	}
}

void CPlayer::OnCollision(CCollider* _pOther)
{
	CObject* pOtherObj = _pOther->GetObj();
	if (L"Ground" == pOtherObj->GetName())
	{
		if (GetRigidBody()->GetVelocity().y == 0)
		{
			m_iJumpStack = 2;
		//	m_eCurState = PLAYER_STATE::WALK;
		}
	}
}

