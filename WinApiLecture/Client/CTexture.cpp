#include "pch.h"
#include "CTexture.h"
#include "CCore.h"

CTexture::CTexture()
	:m_hBit(0)
	, m_dc(0)
	, m_bitInfo{}
{
}

CTexture::~CTexture()
{
	DeleteDC(m_dc);
	DeleteObject(m_hBit);
}

void CTexture::Load(const wstring& _strFilePath)
{
	// �ش� ��ο� �����ϴ� �̹��� ������ �޸𸮻� �ø��� ��Ʈ������ ID(H)�� �޾ƿ� ����Ų��.
	m_hBit = (HBITMAP)LoadImage(nullptr,_strFilePath.c_str(),IMAGE_BITMAP,0,0, LR_CREATEDIBSECTION | LR_LOADFROMFILE);
	// �ε��� ����� ���� ���� ���
	assert(m_hBit);

	// ��Ʈ�ʰ� ������ DC	, �ش� ��Ʈ�ʰ� ������ DC �Ҵ� �ޱ�
	m_dc = CreateCompatibleDC(CCore::GetInst()->GetMainDC());

	// ��Ʈ�ʰ� DC ����
	HBITMAP hPrevBit = (HBITMAP)SelectObject(m_dc, m_hBit);
	DeleteObject(hPrevBit);

	// ���� ���� ����
	// ��Ʈ�� : ��Ʈ�� ������ �����ϴ� ����ü(�ڵ�ƴ�)
	GetObject(m_hBit, sizeof(BITMAP), &m_bitInfo);


	
}

