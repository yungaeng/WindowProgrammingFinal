#include "pch.h"
#include "CScene_Intro.h"
#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CSound.h"
#include "CUIMgr.h"
#include "resource.h"
#include "CPanelUI.h"
#include "CBtnUI.h"
#include "CBackGround.h"


CScene_Intro::CScene_Intro()
	:m_pUI(nullptr)
	, m_bExplain(false)
{
}

void ChangeScene(DWORD_PTR, DWORD_PTR);

CScene_Intro::~CScene_Intro()
{
}


void CScene_Intro::Explain()
{
	if (m_bExplain == false)
	{
		// Sound �ε� �׽�Ʈ�ڡڡڡڡڡ�
		CResMgr::GetInst()->LoadSound(L"Btn_01", L"sound\\BtnSound.wav");
		CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Btn_01");
		pNewSound->Play();
		//pNewSound->SetPosition(0.f);			// �����, ��� ��ġ ���� ex 50% ����
		pNewSound->SetVolume(30.f);				// 0~100 ���� ���� ����

		m_pUI = new CPanelUI;
		m_pUI->SetName(L"Explain");
		m_pUI->SetScale(Vec2(800.f, 600.f));
		m_pUI->SetPos(Vec2(250.f, 100.f));
		m_pUI->SetTex(CResMgr::GetInst()->LoadTexture(L"Explain", L"texture\\Explain2.bmp"));
		AddObject(m_pUI, GROUP_TYPE::UI);


		m_bExplain = true;
	}
	else if (m_bExplain == true)
	{
		DeleteObject(m_pUI);


		m_bExplain = false;
	}
}



void BtnStart(DWORD_PTR a, DWORD_PTR b)
{
	// Sound �ε� �׽�Ʈ�ڡڡڡڡڡ�
	CResMgr::GetInst()->LoadSound(L"Btn_01", L"sound\\BtnSound.wav");
	CSound* pNewSound = CResMgr::GetInst()->FindSound(L"Btn_01");
	pNewSound->Play();
	//pNewSound->SetPosition(0.f);			// �����, ��� ��ġ ���� ex 50% ����
	pNewSound->SetVolume(30.f);				// 0~100 ���� ���� ����
	ChangeScene(SCENE_TYPE::START);

}

void BtnEscape(DWORD_PTR a, DWORD_PTR b)
{

	DestroyWindow(CCore::GetInst()->GetMainHwnd());
}



void CScene_Intro::Enter()
{
	// UI ����� ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	

	CBackGround* pBg = new CBackGround;
	pBg->SetName(L"Cookie_Run_Main");
	pBg->SetScale(vResolution);
	pBg->SetPos(Vec2(0, 0));
	pBg->SetTex(CResMgr::GetInst()->LoadTexture(L"Main_01", L"texture\\Main_Title2.bmp"));
	AddObject(pBg, GROUP_TYPE::BG);
	//CUI* pPanelUI = new CPanelUI;
	//pPanelUI->SetName(L"Cookie_Run_Panel");
	//pPanelUI->SetScale(Vec2(vResolution.x, vResolution.y));
	//pPanelUI->SetPos(Vec2(0.f,0.f));
	////pPanelUI->SetTex(CResMgr::GetInst()->LoadTexture(L"Title", L"texture\\Inversus_Title.bmp"));
	//m_pUI = pPanelUI;

	// ���� ��ư
	CUI* pBtnStartUI = new CBtnUI;
	pBtnStartUI->SetName(L"Start");
	pBtnStartUI->SetScale(Vec2(300.f, 80.f));
	pBtnStartUI->SetPos(Vec2(vResolution.x / 2 - pBtnStartUI->GetScale().x / 2, 500.f));
	pBtnStartUI->SetTex(CResMgr::GetInst()->LoadTexture(L"StartBtn", L"texture\\StartBtn.bmp"));
	((CBtnUI*)pBtnStartUI)->SetClickedCallBack(BtnStart, 0, 0);
	AddObject(pBtnStartUI, GROUP_TYPE::UI);

	// ���� UI
	CBtnUI* pBtnInfoUI = new CBtnUI;
	pBtnInfoUI->SetName(L"Info");
	pBtnInfoUI->SetScale(Vec2(300.f, 80.f));
	pBtnInfoUI->SetPos(Vec2(vResolution.x / 2 - pBtnInfoUI->GetScale().x / 2, 600.f));
	pBtnInfoUI->SetTex(CResMgr::GetInst()->LoadTexture(L"Easy", L"texture\\InfoBtn.bmp"));
	((CBtnUI*)pBtnInfoUI)->SetClickedCallBack(this, (SCENE_MEMFUNC)&CScene_Intro::Explain);
	AddObject(pBtnInfoUI, GROUP_TYPE::UI);

	//// pPanelUI->AddChild(pBtnUI);
	//// ����
	//CUI* pBtnExUI = new CBtnUI;
	//pBtnExUI->SetName(L"Explain");
	//pBtnExUI->SetScale(Vec2(vResolution.x, 50.f));
	//pBtnExUI->SetPos(Vec2(0.f, 675.f));
	////pBtnExUI->SetTex(CResMgr::GetInst()->LoadTexture(L"ExBtn", L"texture\\Btn_Ex.bmp"));
	////((CBtnUI*)pBtnExUI)->SetClickedCallBack(BtnExplain, (DWORD_PTR)vResolution.x, (DWORD_PTR)vResolution.y);

	//CUI* pPanelUI_EX = new CPanelUI;
	//pPanelUI_EX->SetName(L"Inversus");
	//pPanelUI_EX->SetScale(Vec2(vResolution.x, vResolution.y / 3.f));
	//pPanelUI_EX->SetPos(Vec2(vResolution.x - pPanelUI_EX->GetScale().x, 200.f));
	////pPanelUI_EX->SetTex(CResMgr::GetInst()->LoadTexture(L"Explain", L"texture\\Explain.bmp"));
	//pBtnExUI->AddChild(pPanelUI_EX);


	// ����
	CBtnUI* pBtnEscUI = new CBtnUI;
	pBtnEscUI->SetName(L"Escape");
	pBtnEscUI->SetScale(Vec2(300.f, 80.f));
	pBtnEscUI->SetPos(Vec2(vResolution.x / 2 - pBtnInfoUI->GetScale().x / 2, 700.f));
	pBtnEscUI->SetTex(CResMgr::GetInst()->LoadTexture(L"EscBtn", L"texture\\EscBtn.bmp"));
	((CBtnUI*)pBtnEscUI)->SetClickedCallBack(BtnEscape, (DWORD_PTR)vResolution.x, (DWORD_PTR)vResolution.y);


	
	//AddObject(pPanelUI, GROUP_TYPE::UI);
	

	AddObject(pBtnEscUI, GROUP_TYPE::UI);


}
void CScene_Intro::update()
{
	//if (KEY_TAP(KEY::ESC))
	//{
	//	CUIMgr::GetInst()->SetFocusdeUI(m_pUI);
	//}
	// �� Scene�� ������Ʈ���� ������Ʈ
	CScene::update();
	// �̷� �������̵� ����?
	// + @�� �� �Ŵ�.
	if (KEY_TAP(KEY::ESC) && m_bExplain)
	{
		//CUIMgr::GetInst()->SetFocusdeUI(m_pUI);
		Explain();
	}


}

//// ���� �Լ�
//void ChangeScene(DWORD_PTR, DWORD_PTR)
//{
//	ChangeScene(SCENE_TYPE::START);
//}





void CScene_Intro::Exit()
{
	DeleteAll();
	//CCollisionMgr::GetInst()->Reset();

}



