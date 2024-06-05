#include "pch.h"
#include "CTile.h"
#include "CTexture.h"


CTile::CTile()
	:m_pTileTex(nullptr)
	,m_iImgIdx(0)
{
	// ����� Ÿ�� ������� �⺻ ����
	SetScale(Vec2(TILE_SIZE, TILE_SIZE));
}

CTile::~CTile()
{
}

void CTile::update()
{
}

void CTile::render(HDC _dc)
{
	// ������ �ؽ��İ� ���� ��� ����� ����
	if (nullptr == m_pTileTex)
		return;
	UINT iWidth = m_pTileTex->Width();	// �ؽ�ó�� ���� ���ؿ���
	UINT iHeight = m_pTileTex->Height();// �ؽ�ó�� ����	���ؿ���

	UINT iMaxCol = iWidth / TILE_SIZE;	// ���ؿ� ���θ� Ÿ�� ������� ������ ���� ���� ���ϱ�
	UINT iMaxRow = iHeight / TILE_SIZE;	// ���ؿ� ���θ� Ÿ�� ������� ������ ���� ���� ���ϱ�
	
	UINT iCurRow = m_iImgIdx / iMaxCol;	// �ε��� / ���� ���� = ���° ��(���η� ��)���� ��Ÿ���� �ε���
	UINT iCurCol = m_iImgIdx % iMaxCol;	// �ε��� % ���� ���� = ���° ��(���η� ��)���� ��Ÿ���� �ε���

	// �̹��� ����(�ִ� ���� ����)�� �Ѿ �ε���
	if (iMaxRow <= iCurRow)
		assert(nullptr);

	Vec2 vRenderPos = CCamera::GetInst()->GetRenderPos(GetPos());
	Vec2 vScale = GetScale();

	BitBlt(
		_dc
		, (int)vRenderPos.x
		, (int)vRenderPos.y,
		(int)vScale.x
		, (int)vScale.y
		, m_pTileTex->GetDC()
		, iCurCol * TILE_SIZE
		, iCurRow * TILE_SIZE
		, SRCCOPY);
	
}

void CTile::Save(FILE* _pFile)
{
	fwrite(&m_iImgIdx, sizeof(int), 1, _pFile);
}

void CTile::Load(FILE* _pFile)
{
	fread(&m_iImgIdx, sizeof(int), 1, _pFile);

}
