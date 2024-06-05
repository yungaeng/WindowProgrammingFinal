#include "pch.h"
#include "CEventMgr.h"
#include "CObject.h"
#include "CSceneMgr.h"
#include "CScene.h"
#include "CUIMgr.h"
#include "CState.h"
#include "AI.h"

CEventMgr::CEventMgr()
{

}
CEventMgr::~CEventMgr()
{

}

void CEventMgr::update()
{
	// �̺�Ʈ �Ŵ��� ������Ʈ ������ �� ���庤�Ͱ� ä���� ������ ���� �������� ����� �̺�Ʈ�� ���̴�.
	// ==============================================
	// ���� �����ӿ��� ����� �� Dead Object ���� �����Ѵ�
	// ==============================================
	for (size_t i = 0; i < m_vecDead.size(); ++i)
	{
		delete m_vecDead[i];
	}
	m_vecDead.clear();
	

	// ===================
	//	EVENT ó��
	// ===================
	for (size_t i = 0; i < m_vecEvent.size(); ++i) 
	{
		Excute(m_vecEvent[i]);
	}
	m_vecEvent.clear();
}



// ���� Scene ü���� �̺�Ʈ�� ��ϵǸ�, �� �̺�Ʈ�� ó���� �� ������ �̺�Ʈ�� ���ִ� ������� �����ϱ�
void CEventMgr::Excute(const tEvent& _eve)
{
	switch (_eve.eEven)
	{
	case EVENT_TYPE::CREATE_OBJECT:
	{
		// lParam : Object Address
		// wParam :	GROUP_TYPE
		CObject* pNewObj = (CObject*)_eve.lParam;
		GROUP_TYPE eType = (GROUP_TYPE)_eve.wParam;
		CSceneMgr::GetInst()->GetCurScene()->AddObject(pNewObj, eType);
	}
	
		break;
	case EVENT_TYPE::DELETE_OBJECT:
	{
		// lParam : Object Address
		// 1. Object�� Dead ���·� ����
		// 2. ���� ���� ������Ʈ�� ��Ƶд� m_vecDead��
		CObject* pDeadObj = (CObject*)_eve.lParam;
		pDeadObj->SetDead();
		m_vecDead.push_back(pDeadObj);
	}
		break;
	case EVENT_TYPE::SCENE_CHANGE:
	{
		// lParam : Next SCENE_TYPE
		// Scene ����
		SCENE_TYPE eType = (SCENE_TYPE)_eve.lParam;
		CSceneMgr::GetInst()->ChangeScene(eType);

		// ��Ŀ�� UI����(���� Scene�� UI�� ����Ű�� �ֱ� ����)
		CUIMgr::GetInst()->SetFocusdeUI(nullptr);
	}
	break;
	case EVENT_TYPE::CHANGE_AI_STATE:
	{	
		// lParam : AI*
		// wParam : Next STATE_TYPE
		AI* pAI = (AI*)_eve.lParam;
		MON_STATE eNextState = (MON_STATE)_eve.wParam;

		pAI->ChangeState(eNextState);

	}
		break;
	}
}
