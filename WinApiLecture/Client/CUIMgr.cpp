#include "pch.h"
#include "CUIMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CUI.h"
#include "CKeyMgr.h"

CUIMgr::CUIMgr()
	:m_pFocusedUI(nullptr)
{

}

CUIMgr::~CUIMgr()
{

}

void CUIMgr::update()
{
	// 1. FocusedUI Ȯ��

	m_pFocusedUI = GetFocusedUI();
	// ��ȯ�޾� �� FocusedUI�� nullptr�̸� ������Ʈ���� UI�� ���� -> ����
	if (!m_pFocusedUI)
		return;

	// 2. FocusedUI ������, �θ� UI���� �ڽ� UI�� �� ���� Ÿ���� �� UI�� �����´�.
	CUI* pTargetUI =  GetTargetedUI(m_pFocusedUI);


	bool bLbtnTap = KEY_TAP(KEY::LBTN);
	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// Ÿ���� �Ǿ��ִ°� �ִٸ�
	if (nullptr != pTargetUI)
	{
		pTargetUI->MouseOn();

		if (bLbtnTap)
		{
			pTargetUI->MouseLbtnDown();
			pTargetUI->m_bLbtnDown = true;
		}
		else if (bLbtnAway)
		{
			pTargetUI->MouseLbtnUp();
			if (pTargetUI->m_bLbtnDown)
			{
				pTargetUI->MouseLbtnClicked();
			}
			// ���� ��ư��  �� ����̴ϱ� ������ üũ�� �ٽ� �����Ѵ�. 
			pTargetUI->m_bLbtnDown = false;
		}
	}
	//// ���� ���� �޾ƿͼ�
	//CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();

	//// �� ���� ������ ������Ʈ�� ��  UI�׷쿡 ���� ������Ʈ���� �޾ƿ´�.
	//const vector<CObject*>& vecUI = pCurScene->GetGroupObject(GROUP_TYPE::UI);


	//

	//	// �ٿ�ĳ���� �ʿ� (������Ʈ Ÿ�� �����ͱ� ������)
	//m_pFocusedUI;
	//	
	//	// Ÿ���� �� ( ������ �ڽ� �������� Ȯ���ؼ� ���콺�� ���� �ö�� �ִ� UI)UI�� �޾�
	// ������ ���� ���� ���Ե� ������Ʈ �׷� �� UI�׷��� �޾ƿͼ� ���� �� üũ�ϴ� ���¿���	
}

void CUIMgr::SetFocusdeUI(CUI* _pUI)
{
	// �̹� ��Ŀ�̵Ǿ� �ִ� ���
	if (m_pFocusedUI == _pUI || nullptr == _pUI)
	{
		m_pFocusedUI = _pUI;
		return;
	}
	
	m_pFocusedUI = _pUI;
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();

	vector<CObject*>::iterator iter = vecUI.begin();	// �ݺ��� ���ͷ�����

	for (; iter != vecUI.end(); ++iter)
	{
		if (m_pFocusedUI == *iter)
		{
			// ��Ŀ���� UI ���� iter�� ã�Ƴ���
			break;
		}
	}


	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(iter);			// Ÿ�����Ͱ� ����Ű�� CUI* ���� ��
	vecUI.push_back(m_pFocusedUI);	// �޾Ƴ��� pFocusedUI�� �ٽ� �� �ڿ� �߰�
	
}

CUI* CUIMgr::GetFocusedUI()
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	vector<CObject*>& vecUI = pCurScene->GetUIGroup();
	bool bLbtnTap = KEY_TAP(KEY::LBTN);


	// ���� ��Ŀ��UI�� �޾Ƶΰ� ����Ǿ����� Ȯ��
	CUI* pFocusedUI = m_pFocusedUI;


	// ���� Ŭ���� �߻����� �ʾҴµ� ��Ŀ���� ��ȯ �� ���� ���� -> ����
	if (!bLbtnTap)
	{
		return pFocusedUI;
	}

	// ���⼭���ʹ� ��� ���ʹ�ư TAP�� �߻��ߴٴ� ����
	vector<CObject*>::iterator Focusiter = vecUI.end();	// Ÿ�ٿ� ���ͷ�����
	vector<CObject*>::iterator iter = vecUI.begin();	// �ݺ��� ���ͷ�����

	for (; iter != vecUI.end(); ++iter)
	{
		if(((CUI*)*iter)->IsMouseOn())
		{
			// Ŭ���� �߻��ߴµ� ���콺�� �� UI ���� ���� �־����� target iterator�� ����
			// - ������ �� �տ��� ������ �� Ŭ���� ���� ��ü�� vecUI�� �� �ڿ� �־����Ƿ�
			// �������� ������ ���� ������
			Focusiter = iter;
		}
	}
	// �̹� Ŭ������ �ƹ��� ���õ� UI�� ���ٸ�?
	if (vecUI.end() == Focusiter)
	{
		return nullptr;
	}
	pFocusedUI = (CUI*)*Focusiter;


	// ���� ������ �� �ڷ� ���� ��ü
	vecUI.erase(Focusiter);			// Ÿ�����Ͱ� ����Ű�� CUI* ���� ��
	vecUI.push_back(pFocusedUI);	// �޾Ƴ��� pFocusedUI�� �ٽ� �� �ڿ� �߰�



	
	return pFocusedUI;
}

CUI* CUIMgr::GetTargetedUI(CUI* _pParentUI)
{

	bool bLbtnAway = KEY_AWAY(KEY::LBTN);

	// static�� ���� ��� ��� �Ҵ�/���� ���ֱ⿡�� �Ҹ� �ʹ� ũ��, static���� ����
	//	 �θ� UI ����, ��� �ڽĵ��� �˻��Ѵ�.
	// - tree�� ����� ���� ��ȸȰ��
	static list<CUI*> queue;	// ����Ʈ ť�� ����� queue ����
	static vector<CUI*> vecNoneTarget;



	// static���� ������ �־����� clear���ְ� �ٽ� ����
	queue.clear();
	vecNoneTarget.clear();	// ������ clear�� �����Ҵ��� ������ �������� �ʴ´�.

	CUI* pTargetUI = nullptr;
	queue.push_back(_pParentUI);


	while (!queue.empty())
	{
		// ť���� ������ �ϳ� ������
		CUI* pUI = queue.front();
		queue.pop_front();

		// ť���� ������ UI �� TargetUI���� Ȯ��
		// Ÿ�� UI �� ��, �� �켱������ ���� ������ �� ���� ������ �ڽ� UI

		// ���� �ö�� ������ �ϴ� TargetUI�� ����
		if (pUI->IsMouseOn())
		{
			if (nullptr != pTargetUI)
			{
				vecNoneTarget.push_back(pTargetUI);
			}
			pTargetUI = pUI;
		}
		else
		{
			vecNoneTarget.push_back(pUI);
		}

		const vector<CUI*>& vecChild = pUI->GetChildUI();
		for (size_t i = 0; i < vecChild.size(); ++i)
		{
			queue.push_back(vecChild[i]);
		}
	} 

	// ���� ��ư�� ���� ������ ó���� targetUI�� �ƴ� UI���� ���� ó���� �����Ѵ�.
	if (bLbtnAway)
	{
		for (size_t i = 0; i < vecNoneTarget.size(); ++i)
		{

			vecNoneTarget[i]->m_bLbtnDown = false;
		}
	}

	
	return pTargetUI;
}
