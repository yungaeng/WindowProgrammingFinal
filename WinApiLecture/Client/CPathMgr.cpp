#include "pch.h"
#include "CPathMgr.h"
#include "CCore.h"
CPathMgr::CPathMgr()
	:m_szContentPath{}
{
	init();
}
CPathMgr::~CPathMgr()
{
}

void CPathMgr::init()
{
	// ������� ����� ��ġ�� ���� ���͸��� ������ ����, �װ� �޾ƿ��� ��
	GetCurrentDirectory(255, m_szContentPath);
	// ���� ������ ���� ��,
	// +bin\\content\\
	// ���ڿ� �ٷ� �� ���� ���� ��ȯ �Լ��� ������. (���̺귯���� ����������)
	int iLen = (int)wcslen(m_szContentPath);
	// ũ��ϱ� �ε����� �� ��쿡�� �ϳ� ����� �Ѵ�.
	for (int i = iLen - 1; i >= 0; --i)
	{
		if ('\\' == m_szContentPath[i])
		{
			m_szContentPath[i] = '\0';
			break;
		}
	}
	// �ι����� ������ ���ڿ��� �ٿ��ش�
	wcscat_s(m_szContentPath, 255, L"\\bin\\content\\");

	/* ����� ��Ʃ����� ���� ������Ͽ� ������ ��� ��ΰ� �ٸ� ������ �� (�۾� ���͸�)
	 -> �Ӽ� ������ ���� (�����) - (�۾� ���͸�) */
		SetWindowText(CCore::GetInst()->GetMainHwnd(), m_szContentPath);

}

wstring CPathMgr::GetRelativePath(const wchar_t* _filepath)
{
	wstring strFilePath = _filepath;

	
	size_t iAbsLen = wcslen(m_szContentPath);	// �������� ����
	size_t iFullLen = strFilePath.length();

	// �����κ���, ������ ���� ��ο��� �������� ���̸�ŭ�� �� ���ڿ��� ���´�,
	// �� ������ ���Ŀ� �̾����� ����� ��ŭ���� �����´�.
	wstring strRelativePath = strFilePath.substr(iAbsLen, iFullLen - iAbsLen);

	return strRelativePath;
}
