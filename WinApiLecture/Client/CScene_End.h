#pragma once
#include "CScene.h"

class CScene_End :
    public CScene
{
private:
    Vec2    m_vForcePos;
    float   m_fForceRadius;
    float   m_fCurRadius;
    float   m_fForce;
    bool    m_bUseForce;


public:
    // �ڡڡ� virtual Ű���尡 ��� �̹� �����Լ������� (��ӿ� ����)
    // ��������� �����Լ����� ǥ���Ѵ�.
    virtual void update();
    virtual void render(HDC _dc);
    virtual void Enter();           // �ش� ���� ���۵� ���� �ʱ��۾�
    virtual void Exit();            // �ش� ���� Ż���� ���� �۾�

    CScene_End();
    ~CScene_End();
};

