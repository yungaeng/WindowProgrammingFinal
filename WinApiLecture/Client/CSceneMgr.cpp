#include "pch.h"
#include "CSceneMgr.h"
#include "CScene_Start.h"
#include "CScene_Tool.h"
#include "CScene_End.h"
#include "CScene_5_5.h"
#include "CEventMgr.h"


CSceneMgr::CSceneMgr()
	:m_arrScene{}
	,m_pCurScene(nullptr)
{

}

CSceneMgr::~CSceneMgr()
{
	// �� ���� ������ �ǵ� �θ� Ÿ�� �����ͷ� ����Ű�� �־����ϱ�
	// virtual�Ҹ��ڸ� ȣ������ ������ �θ� �Ҹ��ڸ� ȣ��ǰ� ����
	// �ڡڡ� ���� ���� ��ü�� �Ҹ��ڰ� ȣ��� �� �ֵ��� ���� �Ҹ��ڷ� ��������
	for (UINT i = 0; i < (UINT)SCENE_TYPE::END; ++i)
	{
		if(nullptr != m_arrScene[i])
			delete m_arrScene[i];
	}
}

void CSceneMgr::init()
{
	// Scene ����
	m_arrScene[(UINT)SCENE_TYPE::START] = new CScene_Start;
	m_arrScene[(UINT)SCENE_TYPE::START]->SetName(L"Start Scene");



	m_arrScene[(UINT)SCENE_TYPE::TOOL] = new CScene_Tool;
	m_arrScene[(UINT)SCENE_TYPE::TOOL]->SetName(L"Tool Scene");


	// end scene �߰�
	m_arrScene[(UINT)SCENE_TYPE::EnD] = new CScene_End;
	m_arrScene[(UINT)SCENE_TYPE::EnD]->SetName(L"End Scene");


	//m_arrScene[(UINT)SCENE_TYPE::STAGE_01] = new CScene_Stage01;
	//m_arrScene[(UINT)SCENE_TYPE::STAGE_02] = new CScene_Stage02;



	// ���� �� ����
	m_pCurScene = m_arrScene[(UINT)SCENE_TYPE::START];
	m_pCurScene->Enter();
}

// ���� ���� ������Ʈ
void CSceneMgr::update()
{
	m_pCurScene->update();

	m_pCurScene->finalupdate();
}

void CSceneMgr::render(HDC _dc)
{
	m_pCurScene->render(_dc);
}

void CSceneMgr::ChangeScene(SCENE_TYPE _eNext)
{
	// ���� ������ �̺�Ʈ ó���� �� �ߵ� �Ǵ� �ܰ�
	// �� ���� ��� �� �ߵ��Ǿ�� �ϴ� �Լ� Exit() �� �ߵ�
	m_pCurScene->Exit();	// �ش� ���� �ִ� ������Ʈ �׷���� ������Ʈ�� ����

	m_pCurScene = m_arrScene[(UINT)_eNext];		// �� ����

	m_pCurScene->Enter();						// ����� ���� enter����
}


