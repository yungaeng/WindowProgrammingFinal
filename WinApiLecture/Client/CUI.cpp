#include "CUI.h"
#include "CCamera.h"
#include "CKeyMgr.h"
#include "SelectGDI.h"


CUI::CUI(bool _bCamAff)
	:m_pParentUI(nullptr)
	, m_bCamAffected(_bCamAff)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
}

CUI::CUI(const CUI& _origin)
	:CObject(_origin)
	, m_pParentUI(nullptr)
	, m_bCamAffected(_origin.m_bCamAffected)
	, m_bMouseOn(false)
	, m_bLbtnDown(false)
{
	for (size_t i = 0; i < _origin.m_vecChildUI.size(); ++i)
	{
		AddChild(_origin.m_vecChildUI[i]->Clone());
	}
}

CUI::~CUI()
{
	Safe_Delete_Vec(m_vecChildUI);
}





void CUI::update()
{
	// ������ �� ��


	// ���� �ڽ��� ������Ʈ
	// child ui update

	update_child();
}

void CUI::render(HDC _dc)
{
	// ���� ī�޶��� �����ӿ� ���� �����̴� UI��� UI�� �������̵� �޴� �ٸ� UI class�� ����
	// render�� ������Ʈ ��Ű��.
	Vec2 vPos = GetFinalPos();
	Vec2 vScale = GetScale();
	if (m_bCamAffected)
	{
		vPos = CCamera::GetInst()->GetRenderPos(vPos);
	}
	if (m_bLbtnDown)
	{
		SelectGDI select(_dc, PEN_TYPE::GREEN);	Rectangle(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}
	else
	{
		Rectangle(_dc
			, (int)vPos.x
			, (int)vPos.y
			, (int)(vPos.x + vScale.x)
			, (int)(vPos.y + vScale.y));
	}


	// child ui render
	render_child(_dc);

}

void CUI::update_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->update();
	}
}

void CUI::finalupdate()
{
	CObject::finalupdate();

	// UI�� ���� ��ǥ�� ���Ѵ�.
	m_vFinalPos = GetPos();

	// �ڽſ��� �θ� �ִٸ�	FinalPos�� ParentPos �� ���Ѵ�.
	if (GetParent())
	{
		Vec2 vParentPos = GetParent()->GetFinalPos();
		m_vFinalPos += vParentPos;
	}
	// UI Mouse üũ
	MouseOnCheck();

	
	finalupdate_child();
}

void CUI::finalupdate_child()
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->finalupdate();
	}
}

void CUI::render_child(HDC _dc)
{
	for (size_t i = 0; i < m_vecChildUI.size(); ++i)
	{
		m_vecChildUI[i]->render(_dc);
	}
}

void CUI::MouseOnCheck()
{
	Vec2 vMousePos = MOUSE_POS;
	Vec2 vScale = GetScale();

	if (m_bCamAffected)
	{
		// ī�޶��� ������ �޴� UI �� ��� ī�޶�κ��� ���� ��ǥ�� ����޾ƿ�
		vMousePos = CCamera::GetInst()->GetRealPos(vMousePos);
	}
	if ((m_vFinalPos.x <= vMousePos.x && vMousePos.x <= m_vFinalPos.x + vScale.x)	// x�� üũ
		&& (m_vFinalPos.y <= vMousePos.y && vMousePos.y <= m_vFinalPos.y + vScale.y))	// y�� üũ 
	{
		m_bMouseOn = true;
	}
	else 
	{
		m_bMouseOn = false;
	}
}


void CUI::MouseOn()
{
}

void CUI::MouseLbtnDown()
{
}

void CUI::MouseLbtnUp()
{
}

void CUI::MouseLbtnClicked()
{
}

