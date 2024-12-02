#pragma once
#include "CUI.h"
class CPanelUI :
    public CUI
{
private:
    Vec2    m_vDragStart;

public:
    virtual void update();
    virtual void render(HDC _dc);

    virtual void MouseOn();             // �ش� UI�� ���콺�� �ö�� ��� ȣ��
    virtual void MouseLbtnDown();       // ���콺�� �ö�� ��쿡�� ������ �� ȣ��
    virtual void MouseLbtnUp();         // ���콺�� ������ ��
   
    CLONE(CPanelUI);
public:
    CPanelUI();
    ~CPanelUI();
};

