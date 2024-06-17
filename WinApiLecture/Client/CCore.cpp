#include "global.h"
#include "CCore.h"
#include "CObject.h"
#include "CTimeMgr.h"
#include "CKeyMgr.h"
#include "CSceneMgr.h"
#include "CPathMgr.h"
#include "CCollisionMgr.h"
#include "CResMgr.h"
#include "CEventMgr.h"
#include "CCamera.h"
#include "CUIMgr.h"
#include "SelectGDI.h"
#include "CSound.h"

#include"resource.h"

// �����Ҵ� ������� �ϸ� ���� �ʱ�ȭ �ʿ�
//CCore* CCore::g_pInst = nullptr;



CCore::CCore()
	:m_hWnd(0)
	,m_ptResolution{}
	,m_hDC(0)
	,m_hBit(0)
	,m_memDC(0)
	,m_arrBrush{}
	,m_arrPen{}
	,m_hMenu(0)
	,m_iCoin(0)
	,m_iHP(5)
{
	
}

CCore::~CCore()
{
	ReleaseDC(this->m_hWnd, this->m_hDC);

	// CreateCompatiableDC�� ���� DC�� DeleteDC����ߵ�, (������ �ڵ�� ���� ���� �ƴ� ��)
	DeleteDC(m_memDC);
	DeleteObject(m_hBit);

	for (int i = 0; i < (UINT)PEN_TYPE::END; ++i)
	{
		DeleteObject(m_arrPen[i]);
	}
	DestroyMenu(m_hMenu);
}


// CCore �ʱ�ȭ �Լ�
int CCore::init(HWND _hWnd, POINT _ptResolution)
{
	// ������ �ڵ� �Է�
	m_hWnd = _hWnd;
	// ������ �ػ� �� �Է�
	m_ptResolution = _ptResolution;

	// �ڡڡڡڡڡڡ� �ػ� ���� 
	// ���� ���ϴ� Ŭ���̾�Ʈ ������ ���� RECT���� rt�� ������ ��
	// ���� ���ϴ� Ŭ���̾�Ʈ�� ���� ����
	ChangeWindowSize(Vec2((float)_ptResolution.x, (float)_ptResolution.y), false);

	// �޴� �� ����
	m_hMenu = LoadMenu(nullptr, MAKEINTRESOURCE(IDC_CLIENT));

	// DC ������
	m_hDC = GetDC(m_hWnd);


	// ���� ���۸� �뵵�� ��Ʈ�ʰ� DC�� �����
	m_hBit = CreateCompatibleBitmap(m_hDC, m_ptResolution.x, m_ptResolution.y);
	m_memDC = CreateCompatibleDC(m_hDC);
	// m_memDC�� �������� m_hBit ����, m_memDC�� ���� ������ ��Ʈ���� 1�ȼ� ��Ʈ�� ��ȯ���� �� ����
	HBITMAP hOldBit = (HBITMAP)SelectObject(m_memDC, m_hBit);
	DeleteObject(hOldBit);
	
	// ���� ����� �� �� �귯�� ����
	CreateBrushPen();


	// �ڡڡ�Manager �ʱ�ȭ
	CTimeMgr::GetInst()->init();
	CKeyMgr::GetInst()->init();
	CSceneMgr::GetInst()->init();
	CPathMgr::GetInst()->init();


	CSoundMgr::GetInst()->init();
	//// �� �� ������Ʈ�� ������ �ɵ�
	//// Sound �ε� �׽�Ʈ�ڡڡڡڡڡ�
	//CResMgr::GetInst()->LoadSound(L"BGM_01", L"sound\\BGM.wav");
	//CSound* pNewSound = CResMgr::GetInst()->FindSound(L"BGM_01");

	////pNewSound->Play();

	//pNewSound->SetPosition(0.f);			// �����, ��� ��ġ ���� ex 50% ����
	//pNewSound->PlayToBGM(true);				// BGM���� Play 
	////pNewSound->SetVolume(60.f);			// 0~100 ���� ���� ����


	// ���� Sound�� ���۴� �� ���̱� ������ �� ���尡 ������� �� �� ���带 �ٽ� �����Ű��
	// ���۰� ������ �ٲ�� ���� ����� ������� �ʴ´�.

	return S_OK;
}



// �޽����� �߻����� ���� �� �۵��ϴ� �Լ� - �׻� �ߵ�
void CCore::progress()
{
	// =============
	// ��Manager update
	// =============
	CTimeMgr::GetInst()->update();
	CKeyMgr::GetInst()->update();
	CCamera::GetInst()->update();

	// =============
	// ��Scene Update
	// =============
	// ��� ���� ������Ʈ
	CSceneMgr::GetInst()->update();

	// �� �浹üũ
	// �� ������Ʈ ���� �浹�Ŵ��� ������Ʈ ������ ����
	CCollisionMgr::GetInst()->update();

	// �� UI �̺�Ʈ üũ
	CUIMgr::GetInst()->update();


	// =============
	// ��Rendering
	// =============
	// ȭ�� clear
	Clear();

	// �ھ��� DC�� ����
	CSceneMgr::GetInst()->render(m_memDC);
	BitBlt(m_hDC, 0, 0, m_ptResolution.x, m_ptResolution.y,
		m_memDC, 0, 0, SRCCOPY);

	CTimeMgr::GetInst()->render();

	// =============
	// �̺�Ʈ ����ó��
	// =============
	CEventMgr::GetInst()->update();

}

void CCore::Clear()
{
	SelectGDI gdi(m_memDC, BRUSH_TYPE::BLACK);
	Rectangle(m_memDC, -1, -1, m_ptResolution.x + 1, m_ptResolution.y + 1);
}

void CCore::CreateBrushPen()
{
	// hollow brush
	m_arrBrush[(UINT)BRUSH_TYPE::HOLLOW] = (HBRUSH)GetStockObject(HOLLOW_BRUSH);
	m_arrBrush[(UINT)BRUSH_TYPE::BLACK] = (HBRUSH)GetStockObject(BLACK_BRUSH);
	//r g b pen
	m_arrPen[(UINT)PEN_TYPE::RED] = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
	m_arrPen[(UINT)PEN_TYPE::GREEN] = CreatePen(PS_SOLID, 1, RGB(0, 255, 0));
	m_arrPen[(UINT)PEN_TYPE::BLUE] = CreatePen(PS_SOLID, 1, RGB(0, 0, 255));


}

void CCore::DockMenu()
{
	SetMenu(m_hWnd,m_hMenu);
	ChangeWindowSize(GetResolution(), true);
}

void CCore::DivideMenu()
{
	SetMenu(m_hWnd, nullptr);
	ChangeWindowSize(GetResolution(), false);


}

void CCore::ChangeWindowSize(Vec2 _vResolution, bool _bMenu)
{
	RECT rt = { 0,0,(long)_vResolution.x,(long)_vResolution.y };

	// �ػ󵵿� �°� ������ ũ�� �����ϴ� �۾�
	AdjustWindowRect(&rt, WS_OVERLAPPEDWINDOW, _bMenu);
	// ���α���
	// rt.right - rt.left;
	// ���α���
	// rt.bottom - rt.top; 
	SetWindowPos(m_hWnd, nullptr, 100, 100, rt.right - rt.left, rt.bottom - rt.top, 0);
	// �� �ػ� ���� 
}


