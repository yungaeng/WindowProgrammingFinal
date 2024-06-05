#include "pch.h"
#include "CCamera.h"

#include"CObject.h"
#include"CCore.h"
#include"CKeyMgr.h"
#include"CTimeMgr.h"


CCamera::CCamera()
	:m_pTargerObj(nullptr)
	, m_fTime(0.5f)
	, m_fSpeed(0.f)
	, m_fAccTime(0.5f)
{

}

CCamera::~CCamera()
{

}


void CCamera::update()
{
	// ���� ������ Ÿ�� obj�� �ִٸ�
	if (m_pTargerObj)
	{
		// �� obj�� ���� �����̶�� Ÿ�� ����
		if (m_pTargerObj->IsDead())
			m_pTargerObj = nullptr;
		else
		{
			m_vLookAt = m_pTargerObj->GetPos();
		}
	}

	if (KEY_HOLD(KEY::UP))
		m_vLookAt.y -= 500.f * fDT;
	if (KEY_HOLD(KEY::DOWN))
		m_vLookAt.y += 500.f * fDT;
	if (KEY_HOLD(KEY::LEFT))
		m_vLookAt.x -= 500.f * fDT;
	if (KEY_HOLD(KEY::RIGHT))
		m_vLookAt.x += 500.f * fDT;
	// ȭ�� �߾���ǥ�� ī�޶� �߽� ���̰� ���


	CalDiff();
}

void CCamera::CalDiff()
{
	// ���� LookAt�� ���� Look�� ���̰��� �����ؼ� ������ LookAt���� ���Ѵ�.
	m_fAccTime += fDT;

	if (m_fAccTime >= m_fTime)
	{
		m_vCurLookAt = m_vLookAt;
	}
	else
	{
		Vec2 vLookDir = m_vLookAt - m_vPrevLookAt;		// �������� ���� ����
		if (!vLookDir.IsZero())
		{
			m_vCurLookAt = m_vPrevLookAt + vLookDir.Normalize() * m_fSpeed * fDT;

		}
	
	}
	

	// ���� prevLooAt�� ���� Look�� ���̰��� �����ؼ� ������ CurLookAt�� ���Ѵ�.
	Vec2 vResolution = CCore::GetInst()->GetResolution();
	Vec2 vCenter = vResolution / 2.f;

	// �����߽ɰ� ī�޶� �߽��� ����
	m_vDiff = m_vCurLookAt - vCenter;

	m_vPrevLookAt = m_vCurLookAt;
}
