#pragma once
#include "CScene.h"
class CSound;
class CUI;
class CScene_Start :
    public CScene
{
private:

    Vec2    m_vForcePos;
    float   m_fForceRadius;
    float   m_fCurRadius;
    float   m_fForce;
    bool    m_bUseForce;

    vector<CObject*>    m_vecHeart;
    bool                m_bHeartDelete;
    bool                m_bSceneEnd;
    bool                m_bPhase;
    float               m_fEndTime;
    CSound*             m_csBgm;

    CUI*                m_pUI_Reset;
    CUI*                m_pUI_Resume;
    CUI*                m_pUI_End;
    CUI*                m_pUI_Main;
public:
    // �ڡڡ� virtual Ű���尡 ��� �̹� �����Լ������� (��ӿ� ����)
    // ��������� �����Լ����� ǥ���Ѵ�.
    virtual void update();
    virtual void finalupdate();
    virtual void render(HDC _dc);
    virtual void Enter();           // �ش� ���� ���۵� ���� �ʱ��۾�
    virtual void Exit();            // �ش� ���� Ż���� ���� �۾�

public:
    void CreateForce();
    void Resume();

public:
    CScene_Start();
    ~CScene_Start();
};

