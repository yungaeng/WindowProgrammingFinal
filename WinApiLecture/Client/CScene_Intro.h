#pragma once
#include "CScene.h"
class CUI;

class CScene_Intro :
    public CScene
{
private:
    CUI* m_pUI;

public:
    bool m_bExplain;
    virtual void update();
    virtual void Enter();
    virtual void Exit();


    void Explain();


    // �����ϸ� �̳�Ŭ������ �б�ó���� �ؼ� �������� ������ �� �� �ֵ��� ����

public:
    CScene_Intro();
    ~CScene_Intro();
};


