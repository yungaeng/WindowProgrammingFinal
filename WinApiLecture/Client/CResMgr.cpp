#include "pch.h"
#include "CResMgr.h"
#include "CPathMgr.h"
#include "CTexture.h"
#include "CSound.h"

CResMgr::CResMgr()
{
}

CResMgr::~CResMgr()
{
	Safe_Delete_Map(m_mapTex);
	Safe_Delete_Map(m_mapSound);
	// ���� ��ȸ�ϸ鼭 ���ҽ����� ������ ��
	/*map<wstring, CTexture*>::iterator iter = m_mapTex.begin();
	for (; iter != m_mapTex.end(); ++iter)
	{
		delete iter->second;
	}*/
}
CTexture* CResMgr::FindTexture(const wstring& _strKey)
{
	// ã�Ҵٸ� �� �ڸ��� ���ͷ����͸� ��ȯ
	map<wstring,CRes*>::iterator iter = m_mapTex.find(_strKey);
	
	// ���� ã�� ���ؼ� m_mapTex�� end���ͷ����Ͱ� ��ȯ�Ǿ��ٸ�,
	if (iter == m_mapTex.end())
	{
		return nullptr;
	}
	
	// ã�Ҵٸ� ���ͷ������� �ι��� ��� (CTexture*) ��ȯ
	return (CTexture*)iter->second;
}

CTexture* CResMgr::LoadTexture(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �ؽ��İ� �̹� �ִ� ���
	CTexture* pTex = FindTexture(_strKey);
	if (nullptr != pTex)
	{
		return pTex;
	}
	// ������ ��� ã�Ƽ�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	// ���ο� �ؽ��� ��������� �� �ؽ��Ŀ� ã�� ��θ� �ε��ؼ� �޾ƿ�
	pTex = new CTexture;
	pTex->Load(strFilePath);
	pTex->SetKey(_strKey);
	pTex->SetRelativePath(_strRelativePath);

	m_mapTex.insert(make_pair(_strKey, pTex));
	return pTex;
}


CSound* CResMgr::LoadSound(const wstring& _strKey, const wstring& _strRelativePath)
{
	// �ؽ��İ� �̹� �ִ� ���
	CSound* pSound = FindSound(_strKey);
	if (nullptr != pSound)
	{
		return pSound;
	}
	// ������ ��� ã�Ƽ�
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativePath;
	// ���ο� �ؽ��� ��������� �� �ؽ��Ŀ� ã�� ��θ� �ε��ؼ� �޾ƿ�
	pSound = new CSound;
	pSound->Load(strFilePath);
	pSound->SetKey(_strKey);
	pSound->SetRelativePath(_strRelativePath);

	m_mapSound.insert(make_pair(_strKey, pSound));
	return pSound;
}

CSound* CResMgr::FindSound(const wstring& _strKey)
{
		// ã�Ҵٸ� �� �ڸ��� ���ͷ����͸� ��ȯ
	map<wstring,CRes*>::iterator iter = m_mapSound.find(_strKey);
	
	// ���� ã�� ���ؼ� m_mapTex�� end���ͷ����Ͱ� ��ȯ�Ǿ��ٸ�,
	if (iter == m_mapSound.end())
	{
		return nullptr;
	}
	
	// ã�Ҵٸ� ���ͷ������� �ι��� ��� (CTexture*) ��ȯ
	return (CSound*)iter->second;
}
