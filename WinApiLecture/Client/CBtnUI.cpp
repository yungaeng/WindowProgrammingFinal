#include "CBtnUI.h"

#include "CScene.h"


CBtnUI::CBtnUI()
	:CUI(false)
	,m_param1(0)
	,m_param2(0)
	,m_pFunc(nullptr)
	,m_pSceneInst(nullptr)
	,m_pSceneFunc(nullptr)
{

}

CBtnUI::~CBtnUI()
{
}



void CBtnUI::MouseOn()
{
}

void CBtnUI::MouseLbtnDown()
{
}

void CBtnUI::MouseLbtnUp()
{
}


void CBtnUI::MouseLbtnClicked()
{
	if (nullptr != m_pFunc)
	{
		m_pFunc(m_param1,m_param2);
	}


	// 
	if (m_pSceneInst && m_pSceneFunc)
	{
		// 객체로 멤버함수 포인터에 적용된 함수 호출하기
		(m_pSceneInst->*m_pSceneFunc)();
	}
}

void CBtnUI::SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc)
{
	m_pSceneInst = _pScene;
	m_pSceneFunc = _pSceneFunc;
}
