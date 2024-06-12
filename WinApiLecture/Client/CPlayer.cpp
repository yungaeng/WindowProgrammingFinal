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
	, m_ePrevState(PLAYER_STATE::WALK)
	, m_eCurJumpState(PLAYER_JUMP_STATE::JUMP_UP)
	, m_ePrevJumpState(PLAYER_JUMP_STATE::JUMP_DOWN)
	, m_iJumpStack(2)
{
	// 강체 추가
	CreateRigidBody();


	//// Texture 로딩하기
	//m_pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\airp.bmp");
	CreateCollider();

	// 충돌체 offset과 충돌체 크기 변경
	// 충돌체의 offset을 수정하여 파이널 pos 적용시 그만큼 이동시켜 적용시킴
	GetCollider()->SetOffsetPos(Vec2(10.f, 0.f));
	// 충돌체의 크기 설정
	GetCollider()->SetScale(Vec2(80.f, 130.f));


	// 애니메이터 컴포넌트 생성
	CreateAnimator();
	// 캐릭터의 상태를 먼저 설정한 후 , 그 상태에 맞게 캐릭터의 애니메이션을 정하자.
	// 맞은 상태, 움직이는 상태, 점프 상태, 등등 그 상태의 전환을 완벽히 실행한 뒤
	CTexture* pTex = CResMgr::GetInst()->LoadTexture(L"PlayerTex", L"texture\\Brave_Cookie.bmp");


	//GetAnimator()->LoadAnimation(L"animation\\player_walk_left.anim");
	// walk error - 비활성화 06/10
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

		// 셀 당 크기 272 x 272
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
		Vec2(5.f, 1365.f),
		Vec2(267.f, 265.f),
		Vec2(272.f, 0.f),
		0.1f,
		1);
	GetAnimator()->CreateAnimation(
		L"JUMP_AIR",
		pTex,
		Vec2(277.f, 1365.f),
		Vec2(267.f, 160.f),
		Vec2(272.f, 0.f),
		0.2f,
		2);

	GetAnimator()->CreateAnimation(
		L"JUMP_DOWN",
		pTex,
		Vec2(820.f, 1475.f),
		Vec2(267.f, 150.f),
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
	// Animation 저장해보기
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


	// 중력 컴포넌트 생성
	CreateGravity();
	//GetAnimator()->Play(L"IDLE_BOTTOM", true);

	//CAnimation* pAnim = GetAnimator()->FindAnimation(L"IDLE_BOTTOM");
	//for(UINT i = 0; i < pAnim->GetMaxFream(); ++i)
	//	pAnim->GetFrame(i).vOffset = Vec2(0.f,-20.f);		// 0번 프레임

}

CPlayer::~CPlayer()
{
	
}
void CPlayer::update()
{
	
	update_move();

	update_state();

	update_animation();

	// 부모(CObject)의 멤버 변수인 m_vPos가 private이므로 직접 변경이 불가능, GetPos를 통해 값을 얻어옴)
	//Vec2 vPos = GetPos();
	
	//if (KEY_TAP(KEY::SPACE))
	//{

	//	//CreateMissile();
	//}
	
	

	if (KEY_TAP(KEY::ENTER))
	{
		SetPos(Vec2(640.f, 384.f));
	}


	// 부모파트의 멤버 변수 m_vPos를 변경한 vPos값으로 Set
//	SetPos(vPos);

	GetAnimator()->update();


	m_ePrevState = m_eCurState;
	m_ePrevJumpState = m_eCurJumpState;
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
	//// 픽셀 크기 자체는 UINT지만, 나중에 위치를 입력할 때 음수로 입력할 수 있도록 int로 캐스팅
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

	// 컴포넌트(충돌체, etc...)가 있는 경우 렌더
	// 애니메이션이 있는 경우 본인 텍스쳐가 아닌 본인이 보유한 애니메이션의 정보를 렌더
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
	//// 복잡하게 상태를 변경 시키기			else if로 구현하면 상쇄를 구현할 수 없음
	//if (KEY_HOLD(KEY::A))
	//{
	if (PLAYER_STATE::JUMP != m_eCurState)
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
		m_eCurState = PLAYER_STATE::JUMP;
		if (m_iJumpStack > 0)
			if (GetRigidBody())
			{
				--m_iJumpStack;
				GetRigidBody()->SetVelocity(Vec2(GetRigidBody()->GetVelocity().x, -500.f));
			}
	}
	// JUMP 상태인 경우 속도에 따라 분류하기
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
}

void CPlayer::update_move()
{


	CRigidBody* pRigid = GetRigidBody();

	//계속 움직이게
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
	// 상태가 변경되지 않았다면 리턴
	if (m_ePrevState == m_eCurState && m_eCurJumpState == m_ePrevJumpState)
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
		 
		break;
	case PLAYER_STATE::JUMP:
	{
		// 일반 점프인 경우
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
		// 더블 점프의 경우
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
//	// 항상 적용되는 아래쪽으로의 500의 힘
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

	if (L"Coin" == pOtherObj->GetName())
	{
		DeleteObject(_pOther->GetObj());
	}
}

//void CPlayer::render()
//{
//	
//}

