#include "pch.h"
#include "func.h"
#include "CEventMgr.h"
#include "CResMgr.h"
#include "random"

using std::mt19937;
using std::random_device;
using std::uniform_int_distribution;

void CreateObject(CObject* _pObj, GROUP_TYPE _eGroup)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CREATE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;
	evn.wParam = (DWORD_PTR)_eGroup;	// enum���� 4����Ʈ ����

	CEventMgr::GetInst()->AddEvent(evn);
}

void DeleteObject(CObject* _pObj)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::DELETE_OBJECT;
	evn.lParam = (DWORD_PTR)_pObj;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeScene(SCENE_TYPE _eNext)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::SCENE_CHANGE;
	evn.lParam = (DWORD_PTR)_eNext;

	CEventMgr::GetInst()->AddEvent(evn);
}

void ChangeAIState(AI* _pAI, MON_STATE _eNextState)
{
	tEvent evn = {};
	evn.eEven = EVENT_TYPE::CHANGE_AI_STATE;
	evn.lParam = (DWORD_PTR)_pAI;
	evn.wParam = (DWORD_PTR)_eNextState;

	CEventMgr::GetInst()->AddEvent(evn);
}

void FScanf(char* _pOutBuff, FILE* _pFile)
{
	int i = 0;
	while (true)
	{
		char c = (char)getc(_pFile);
		if (c == '\n')
		{
			_pOutBuff[i++] = '\0';
			break;
		}
		_pOutBuff[i++] = c;
	}
}

void SaveWString(const wstring& _str, FILE* _pFile)
{
	
	const wchar_t* pStrName = _str.c_str();
	size_t iLen = _str.length();

	// ���� ���� ����
	fwrite(&iLen, sizeof(size_t), 1, _pFile);

	// ���ڿ� ����
	fwrite(pStrName, sizeof(wchar_t), iLen, _pFile);
}

void LoadWString(wstring& _str, FILE* _pFile)
{
	size_t iLen = 0;
	// ���Ϸκ��� ���ڿ��� ���̸� �о��
	fread(&iLen, sizeof(size_t), 1, _pFile);

	// �� �̾ pFile�� ���� �����͸� ����Ű�� �ֱ� ������ iLen ��ŭ �о���� ��

	wchar_t szBuff[256] = {};		// ���ڿ��� �޾ƿ� ���� ����

	// �ٷ� _str(wstring)�� ���� �ʴ� ������, _str�� ���� �迭�̱� ������ �󸶳� �Ҵ�Ǿ��ִ��� ��
	// �ٷ� ũ�⸦ �Ѿ�� ���ڿ��� �־��ָ� ���� �߻� ����
	// ���Ϸκ��� ���ڸ� iLen��ŭ ������
	fread(szBuff, sizeof(wchar_t), iLen, _pFile);

	// = operator�� ���� �迭 ����� �����س��� ���̴�.
	_str = szBuff;
}


int MakeRandomInt(int start, int end)
{
	random_device rd;
	mt19937 mt(rd());
	uniform_int_distribution<int> id(start, end);

	return id(mt);
}
