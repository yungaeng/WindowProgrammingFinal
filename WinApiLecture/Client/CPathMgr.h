#pragma once
class CPathMgr
{
	SINGLE(CPathMgr);

private:
	wchar_t m_szContentPath[256];	// ������ �ִ� ���� 255�� ����
	wchar_t m_szRelativePath[256];
public:
	void init();
	// �Ѽչ����� ���� const
	const wchar_t* GetContentPath() { return m_szContentPath; }

	// ������ �κп��� ����� �κи� ���� �������ִ� �Լ�
	wstring GetRelativePath(const wchar_t* _filepath);

};

