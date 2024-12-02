#include "pch.h"
#include "CCore.h"
#include "CScene.h"
#include "CObject.h"
#include "CTile.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CCamera.h"
#include "CBlock.h"



CScene::CScene()
	:m_iTileX(0)
	,m_iTileY(0)
	,m_iBlockX(0)
	,m_iBlockY(0)
	,m_pPlayer(nullptr)
{
}

CScene::~CScene()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; i++)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// m_arrObj[i] �׷� ������ j��° ��ü ����
 			delete m_arrObj[i][j];
		}
	}
	// ���Ͷ��� CScene�� ����̹Ƿ� ������ �Ҹ��ڰ� ȣ��
}


void CScene::start()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			m_arrObj[i][j]->start();
		}
	}
}

void CScene::update()
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			if (!m_arrObj[i][j]->IsDead())
			{
				m_arrObj[i][j]->update();
			}
		}
	}
}

// ������ ������Ʈ
void CScene::finalupdate()
{
	
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		for (size_t j = 0; j < m_arrObj[i].size(); ++j)
		{
			// ���� ��ü�� ���������� ���̳� ������Ʈ - �浹 üũ ����ȭ ��
			m_arrObj[i][j]->finalupdate();
		}
	}
}

void CScene::render(HDC _dc)
{
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		// Ÿ�� �������� ���� ����
		// ���� Ÿ�� ������Ʈ�� ���� ó���� �Ǿ���Ѵٸ� ���ͷ����ͷ� �ٽ� ����ߵ�
		if ((UINT)GROUP_TYPE::TILE == i)
		{
			render_tile(_dc);
			continue;
		}



		vector<CObject*>::iterator iter = m_arrObj[i].begin();
		for (; iter != m_arrObj[i].end();)
		{
			if (!(*iter)->IsDead())
			{
				(*iter)->render(_dc);
				++iter;
			}
			else
			{
				// ��������� ���
				// ���� ���ͷ����Ͱ� ����Ű�� �����͸� �����ϰ� ���� ���ͷ����͸� �޾ƿ�
				iter = m_arrObj[i].erase(iter);
			}
		}
	}
}

void CScene::render_tile(HDC _dc)
{

	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	// ī�޶� ������ �����ִ� ��ǥ�� �˾ƿ���
	Vec2 vCamLook =  CCamera::GetInst()->GetLookAt();


	// ���� ȭ�� �ػ� �˾ƿ���
	Vec2 vRestoultion = CCore::GetInst()->GetResolution();


	// ī�޶� �����ִ� ���� �»�� ��ǥ
	Vec2 vLeftTop = vCamLook - vRestoultion / 2;

	int iTileSize = TILE_SIZE;	// Ÿ�� ������ �˾ƿ���

	// �»���� �ε��� ���ϱ�
	// x��ǥ�� Ÿ�� ������� ������ ��
	// y��ǥ�� Ÿ�� ������� ������ ���� ���� �� ����
	int iLTCol = (int)vLeftTop.x / (int)iTileSize;
	int iLTRow = (int)vLeftTop.y / (int)iTileSize;




	int iClientWidth = (int)(vRestoultion.x / iTileSize + 1);		// �� ȭ�鿡 ���� Ÿ���� ���� ����
	int iClientheight = (int)(vRestoultion.y / iTileSize + 1);	// �� ȭ�鿡 ���� ���� ����

	// ���� �ݺ�Ƚ�� - ȭ�鿡 ������ ���� ����
	for (int iCurRow = iLTRow ; iCurRow < (iLTRow + iClientheight); ++iCurRow)
	{
		// ���� �ݺ�Ƚ�� - ȭ�鿡 ������ ���� ����
		for (int iCurCol = iLTCol; iCurCol < (iLTCol + iClientWidth); ++iCurCol)
		{
			// Ÿ�� ���ο��� ������ �����̰ų�, Ÿ���� �ִ� ���� ������ �Ѿ�� �ȵ� 
			if (iCurCol < 0 || m_iTileX <= (unsigned)iCurCol
				// Ÿ�� ���ο��� ������ �����̰ų�, Ÿ���� �ִ� ���� ������ �Ѿ�� �ȵ�
				|| iCurRow < 0 || m_iTileY <= (unsigned)iCurRow)
			{
				// ���������� �ʴ´�.
				continue;
			}

			int iIdx = (m_iTileX * iCurRow) + iCurCol;		// Ÿ�� ���� * ���� ���� + ���� ���� = �ش� �ε���
			vecTile[iIdx]->render(_dc);
		}
	}


}

// �� �׷��� ��� ������Ʈ �����ϱ�
void CScene::DeleteGroup(GROUP_TYPE _eTarget)
{
	// �ڡڡں��� �ȿ� �ּҸ� �����Ҵ� �Ͽ� ���� ���
	// ���͸� ���� ���� ���� ���� �ּҸ� ���� �����ϰ�, �� ���� ���͸� �����Ѵ�.
	// ���ø����� ���� ���� �Լ� ����
	// ����
	Safe_Delete_Vec<CObject*>(m_arrObj[(UINT)_eTarget]);

	// < > ���� �ڷ����� �־ ������ ������� �Ѵ�!!! �ؿ��� ��ü�� �Լ� ���ø����� �Լ��� �ƴϴ�.
	//Safe_Delete_Vec(m_arrObj[(UINT)_eTarget]);
}

void CScene::DeleteAll()
{
	// ��� �׷� ����
	for (UINT i = 0; i < (UINT)GROUP_TYPE::END; ++i)
	{
		DeleteGroup((GROUP_TYPE)i);
	}
}

void CScene::CreateTile(UINT _iXCount, UINT _iYCount)
{
	DeleteGroup(GROUP_TYPE::TILE);
	m_iTileX = _iXCount;
	m_iTileY = _iYCount;
	CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"Texture\\Tile.bmp");
	for (UINT i = 0; i < _iYCount; ++i)
	{
		for (UINT j = 0; j < _iXCount; ++j)
		{
			CTile* pTile = new CTile();
			pTile->SetPos(Vec2((float)(j * TILE_SIZE), (float)(i * TILE_SIZE)));
			pTile->SetTexture(pTileTex);
			AddObject(pTile, GROUP_TYPE::TILE);
		}
	}
}

void CScene::CreateBlock(int _count)
{
	// �ι����� ������ ��¦ �ǵ帲
	//DeleteGroup(GROUP_TYPE::TILE);
	/*m_iBlockX = _iXCount;
	m_iBlockY = _iYCount;*/
	//CTexture* pTileTex = CResMgr::GetInst()->LoadTexture(L"Tile", L"Texture\\Tile.bmp");
	for (UINT i = 0; i < (UINT)_count; ++i)
	{
			CBlock* pBlock = new CBlock();

			// �ǵ帲
			pBlock->SetScale(Vec2(40.f, 40.f));
			pBlock->SetName(L"Block");
			pBlock->SetPos(Vec2(MakeRandomInt(20,1260),MakeRandomInt(20, 780)));
			//pTile->SetTexture(pTileTex);

			AddObject(pBlock, GROUP_TYPE::BLOCK);
		
	}
}

void CScene::LoadTile(const wstring& _strRelativePath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	// Ŀ�� ������Ʈ
	FILE* pFile = nullptr;
	// 2����Ʈ ���� ���� ���� 
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb"); // L"r" -> read���, ������ġ�� �����ϴ� �� �Ұ����ϴ�.
	// r, w �� rb , wb�� ���� b(���̳ʸ�)�� �������� ������ �ƽ�Ű�ڵ�� ���Ͽ� ������
	// ��� �� ��� ���������, 27 = ESC(Ż�⹮��)�� �����ϱ� ������
	// Ư�� ��Ȳ�� ������ ������ ��Ȳ�� �߻��� �� �ִ�.
	// ���� b�� ���� ���̳ʸ� ������(���� ����) �����ͷ� �����ϰڴٴ� ���� ����.
	// ���� �б� ���� �������� �ϴ� ��ο� ������ ������ ������ - write�� �ٸ�
	
	assert(pFile);
	// Ÿ�� ���� ���� ���� �ҷ�����
	UINT xCount = 0;
	UINT yCount = 0;

	fread(&xCount, sizeof(UINT), 1, pFile);
	fread(&yCount, sizeof(UINT), 1, pFile);

	// �ҷ��� ������ �°� EmptyTile �� �����α�
	CreateTile(xCount, yCount);

	// ������� Ÿ�� ������ �ʿ��� ������ �ҷ����� ��
	const vector<CObject*>& vecTile = GetGroupObject(GROUP_TYPE::TILE);

	for (size_t i = 0; i < vecTile.size(); ++i)
	{
		// ���� Ÿ���� ������ ��Ű��
		((CTile*)vecTile[i])->Load(pFile);
	}

	fclose(pFile);
}
