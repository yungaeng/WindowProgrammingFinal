#include "pch.h"
#include "CScene_Tool.h"
#include "CKeyMgr.h"
#include "CTile.h"

#include "CCore.h"
#include "CResMgr.h"
#include "CSceneMgr.h"
#include "CKeyMgr.h"
#include "CPathMgr.h"

#include "CUIMgr.h"
#include "resource.h"
#include "CPanelUI.h"
#include "CBtnUI.h"

CScene_Tool::CScene_Tool()
	:m_pUI(nullptr)

{
}

CScene_Tool::~CScene_Tool()
{
}


void ChangeScene(DWORD_PTR, DWORD_PTR);

void CScene_Tool::Enter()
{
	// �� Scene���� ����� �޴��� �ٿ��ش�.
//	
	CCore::GetInst()->DockMenu();
	

	// Ÿ�� ���� - ���� ��
	CreateTile(5, 5);

	// UI ����� ����
	Vec2 vResolution = CCore::GetInst()->GetResolution();

	CUI* pPanelUI = new CPanelUI;
	pPanelUI->SetName(L"ParentUI");
	pPanelUI->SetScale(Vec2(300.f,150.f));
	pPanelUI->SetPos(Vec2(vResolution.x - pPanelUI->GetScale().x, 0.f));
	


	CBtnUI* pBtnUI = new CBtnUI;
	pBtnUI->SetName(L"ChildUI");
	pBtnUI->SetScale(Vec2(100.f, 40.f));
	pBtnUI->SetPos(Vec2(0.f, 0.f));

	// ��ü�� ����Լ� ������ ����ϱ�......................................
	((CBtnUI*)pBtnUI)->SetClickedCallBack(this,(SCENE_MEMFUNC)&CScene_Tool::SaveTileData);
	pPanelUI->AddChild(pBtnUI);

	AddObject(pPanelUI, GROUP_TYPE::UI);

	// ���纻 UI
	/*CUI* pClonePanel = pPanelUI->Clone();
	pClonePanel->SetPos(pClonePanel->GetPos() + Vec2(-300.f, 0.f));
	// ���� ����Լ� ������ ���� �ڡڡڡڡڡڡ�
	((CBtnUI*)pClonePanel->GetChildUI()[0])->SetClickedCallBack(ChangeScene, 0, 0);
	AddObject(pClonePanel, GROUP_TYPE::UI);

	m_pUI = pClonePanel;*/

	// ī�޶� LookAt ����
	CCamera::GetInst()->SetLookAt(vResolution / 2.f);

}

void CScene_Tool::Exit()
{
	CCore::GetInst()->DivideMenu();
	DeleteAll();
}


void CScene_Tool::update()
{
	CScene::update();
	// �̷� �������̵� ����?
	// + @�� �� �Ŵ�.
	SetTileIdx();

	//if (KEY_TAP(KEY::LSHIFT))
	//{
	////	CUIMgr::GetInst()->SetFocusdeUI(m_pUI);
	//	SaveTileData();
	//
	//}
	if (KEY_TAP(KEY::CTRL))
	{
		LoadTileData();
	}
}

void CScene_Tool::SetTileIdx()
{
	

	if (KEY_TAP(KEY::LBTN))
	{
		Vec2 vMousePos = MOUSE_POS;
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);

		int iTileX = (int)GetTileX();
		int iTileY = (int)GetTileY();

		int iCol = (int)vMousePos.x / TILE_SIZE;		// ���° ������ �ľ� ���� 
		int iRow = (int)vMousePos.y / TILE_SIZE;		// ���° ������ �ľ� ����

		// ���콺 ��ġ.x�� ������ �ƴ� ��� || ���� ������ �Ѿ ���
		// || ���콺 ��ġ.y�� ������ �ƴ� ��� || ���� ������ �Ѿ ��� return
		if (vMousePos.x < 0 || iTileX <= iCol
			||vMousePos.y < 0 || iTileY <= iRow)
		{
			return;
		}
		// �ε����� ���콺 ���� ���� * �ִ� ���� ���� + ���콺 ���� ����
		// �� �ε����� �ٷ� Ŭ���� Ÿ���� �ε���
		UINT iIdx = iRow * iTileX + iCol;

		const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

		// ���콺�� Ŭ���� Ÿ�� ã�� �Ϸ�, �ٿ� ĳ���� (Ÿ���̶�� Ȯ���� �� ����)
		((CTile*)vecTile[iIdx])->AddImgIdx();


	}
}

void CScene_Tool::SaveTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	// ���ͳݿ� ã�ƺ��� ������ ã�Ƽ� �� �� �ִ�.
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;	// ���ͷ� ����� ������ �ε��� 0 = ALL, 1 = Tile
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
	
	// Modal ��� ��Ŀ���� �������� while ���鼭 ��� ����Ǵ� ��
	if (GetSaveFileName(&ofn))
	{
		// �����ư�� ������ true
		// -> szName�� ��θ� �������� �� ��θ� ���ڷ� �־ ��¥ �����ϱ�
	
		SaveTile(szName);
	}
	// ��� ��ư�� ������ false
}

void CScene_Tool::SaveTile(const wstring& _strFilePath)
{

	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	// 2����Ʈ ���� ���� ���� 
	_wfopen_s(&pFile, _strFilePath.c_str(),L"wb"); // L"w" -> write���, ������ġ���� �ҷ����̴� �� �Ұ����ϴ�.

	assert(pFile);
	
	// ������ ���� - Ÿ�� ���� ���� ����
	UINT xCount = GetTileX();
	UINT yCount = GetTileY();

	// ���Ͽ� ������ �����ϴ� ��� : ù���ڷ� ����� �������� �����ּҸ� void �����ͷ� �ް�,
	// ���� ���� 2�� �� �������� ����� �޾� ��� ������ �����Ѵ�. 
	// ���� 3�� �迭�� ��� ������ �����ش�.
	// ���� 4�� ��Ʈ���� ����
	fwrite(&xCount, sizeof(UINT), 1, pFile);
	fwrite(&yCount, sizeof(UINT), 1, pFile);

	// ��� Ÿ�ϵ��� ���������� ������ �����͸� �����ϰ� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		// ���� Ÿ���� ������ �����Ű��
		((CTile*)vecTile[i])->Save(pFile);
	}

	fclose(pFile);
}

void CScene_Tool::LoadTileData()
{
	OPENFILENAME ofn = {};

	wchar_t szName[256] = {};

	// ���ͳݿ� ã�ƺ��� ������ ã�Ƽ� �� �� �ִ�.
	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = CCore::GetInst()->GetMainHwnd();
	ofn.lpstrFile = szName;
	ofn.nMaxFile = sizeof(szName);
	ofn.lpstrFilter = L"ALL\0*.*\0Tile\0*.tile\0";
	ofn.nFilterIndex = 0;	// ���ͷ� ����� ������ �ε��� 0 = ALL, 1 = Tile
	ofn.lpstrFileTitle = nullptr;
	ofn.nMaxFileTitle = 0;

	wstring strTileFolder = CPathMgr::GetInst()->GetContentPath();
	strTileFolder += L"tile";
	ofn.lpstrInitialDir = strTileFolder.c_str();
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	// Modal ��� ��Ŀ���� �������� while ���鼭 ��� ����Ǵ� ��
	if (GetOpenFileName(&ofn))
	{
		// �����ư�� ������ true
		// -> szName�� ��θ� �������� �� ��θ� ���� ��� ��� ���� �־ ��¥ �о����
		wstring strRelativePath = CPathMgr::GetInst()->GetRelativePath(szName);
		LoadTile(strRelativePath);
	}
	// ��� ��ư�� ������ false
}


// ���� �Լ�
void ChangeScene(DWORD_PTR, DWORD_PTR)
{
	ChangeScene(SCENE_TYPE::START);
}





// !!���� Cscene_tool�� ����Լ��� �ƴ� �����Լ��̴�.�ڡڡڡڡڡڡ�
/// ======================
// Tile Count Window Proc
/// ======================
// CALLBACK  - �Լ� ȣ�� �Ծ࿡ ������ �� 
INT_PTR CALLBACK TileCountProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK )
		{
			// ���̾�α׿� �ִ� ������(���� ���ڿ�)�� ���ڷ� ��ȯ�Ͽ� �����´�.
			// OK ��ư�� ���� ����� ó���� �� - hWnd, ID, ? , ���� ��� signed
			UINT iXCount = GetDlgItemInt(hDlg,IDC_EDIT1,nullptr,false);	
			UINT iYCount = GetDlgItemInt(hDlg, IDC_EDIT2, nullptr, false);

		
			// ������ �ִ� Ÿ�� ����...~ ������ ��� �Լ��� �ƴϹǷ� ���� ���� �������� �𸥴�.
			CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
			// �� ����� Tool Scene������ ��� �����ؾ� �Ѵ�.
			// ���� �ٿ�ĳ������ CScene_Tool�� ������ ������ ��쿡�� �����Ѵ�.
			CScene_Tool* pToolScene = dynamic_cast<CScene_Tool*>(pCurScene);
			assert(pToolScene);	// �ٿ� ĳ���� ���� ���� Ȯ�� - nullptr�� ��� �Ʈ ����
			
			// Ÿ�� �׷� ������Ʈ�� ����
			pToolScene->DeleteGroup(GROUP_TYPE::TILE);

			// Ÿ�� ����
			pToolScene->CreateTile(iXCount, iYCount);


			// EndDialog - �ش� �����찡 ������� �˸� - �ι�° ���ڷ� �������ִ� LOWORD(wParam)(INT_PTR)
			// ���� ������ ���̵� ���� �ش� - DilogBox�� ���� ������ ���� ��ư�� ���� �˷��� �� �ִ�.
			// but �׳� ���⼭ ���� ��ư�� ���� �� ���� �ٷ� �ۼ����ش� - �ϰ���
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		else if (LOWORD(wParam) == IDCANCEL)
		{
			// ĵ���� ��� �׳� ����
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}