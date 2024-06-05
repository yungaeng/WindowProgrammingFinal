#include "pch.h"
#include "CKeyMgr.h"
#include "CCore.h"


int g_arrVK[(int)KEY::LAST] =
{
	VK_LEFT, // LEFT
	VK_RIGHT, //RIGHT,
	VK_UP, //UP,
	VK_DOWN, //DOWN,
	'Q',
	'W',
	'E',
	'R',
	'T',
	'Y',
	'U',
	'I',
	'O',
	'P',
	'A',
	'S',
	'D',
	'F',
	'F',
	'Z',
	'X',
	'C',
	'V',
	'B',

	VK_MENU,
	VK_CONTROL,
	VK_LSHIFT,
	VK_RETURN,
	VK_SPACE,
	VK_ESCAPE,

	VK_LBUTTON,
	VK_RBUTTON,



	//LAST, // enum�� ��
};

CKeyMgr::CKeyMgr()
{

}
CKeyMgr::~CKeyMgr()
{

}


void CKeyMgr::init()
{
	for (int i = 0; i < (int)KEY::LAST; ++i)
	{
		m_vecKey.push_back( tKeyInfo { KEY_STATE::NONE, false });
	}

	
}

void CKeyMgr::update()
{
	// ������ ��Ŀ�� �˾Ƴ���
	// HWND hMainWnd = CCore::GetInst()->GetMainHwnd();	
	// ���� ��Ŀ�� �Ǿ��ִ� ������ �ڵ鰪(HWND)�� �˷���(���� ��� NULL)
	HWND hWnd = GetFocus();

	// ������ ��Ŀ�� ���� �� Ű �̺�Ʈ ����
	if (nullptr != hWnd)
	{

		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			// Ű�� ���ȴ��� üũ
			if (GetAsyncKeyState(g_arrVK[i]) & 0x8000)
			{

				if (m_vecKey[i].bPrevPush)
				{
					// �������� ���� Ű�� ��� ��� ���� ������ HOLD ����
					m_vecKey[i].eState = KEY_STATE::HOLD;
				}
				else
				{
					// �̹��� ó�� ���� ����̸� TAP ����
					m_vecKey[i].eState = KEY_STATE::TAP;
				}
				m_vecKey[i].bPrevPush = true;
			}

			// Ű�� �������� ���� ���
			else
			{
				if (m_vecKey[i].bPrevPush)
				{
					// ������ �����־��ٸ� ���� �� �� ������ AWAY
					m_vecKey[i].eState = KEY_STATE::AWAY;
				}
				else
				{
					// ��� �� �����־��ٸ� �� ���� ������ NONE
					m_vecKey[i].eState = KEY_STATE::NONE;
				}
				m_vecKey[i].bPrevPush = false;
			}

		}
		// Mouse ��ġ ���
		POINT ptPos = {};
		// ������ ��ü ���콺 ��ġ ��� �Լ� - ������ ��ü ����
		GetCursorPos(&ptPos);
		
		// ���� ���� ���� Ŭ���̾�Ʈ ���α׷� �������� �ٲ���
		ScreenToClient(CCore::GetInst()->GetMainHwnd(), &ptPos);

		m_vCurMousePos = Vec2((float)ptPos.x, (float)ptPos.y);
	}


	// ������ ��Ŀ�� ��������
	else
	{
		for (int i = 0; i < (int)KEY::LAST; ++i)
		{
			m_vecKey[i].bPrevPush = false;
			// ��Ŀ���� ������ ���� TAP �Ǵ� HOLD���ٸ� AWAY�� ���� ����
			if (KEY_STATE::TAP == m_vecKey[i].eState || KEY_STATE::HOLD == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::AWAY;

			}
			else if (KEY_STATE::AWAY == m_vecKey[i].eState)
			{
				m_vecKey[i].eState = KEY_STATE::NONE;

			}
		}
	}
}

