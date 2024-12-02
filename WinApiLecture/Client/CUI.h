#pragma once
#include "CObject.h"

// �� �ſ��� ū UI�ϳ��� �ְ�, �� UI�κ��� �ٸ� UI���� ��ӵǾ� �����Ѵ�.
// ���� �θ� UI�� �ڽ�UI�� �����ϵ��� �Ѵ�.
// ���� 1. ������ ������ �ڿ������� ��������.
// ���� 2. �θ� child ���� ������Ʈ,���̳ξ�����Ʈ,������Ű�� ������ ���ε��� �� �ʿ�..�� ����?

class CTexture;
class CUI :
    public CObject
{
private:
    vector<CUI*>    m_vecChildUI;       // �ڽ� UI���� ������ ����
    CUI*            m_pParentUI;        // �ڽ��� �θ� pUI
    Vec2            m_vFinalPos;        // ������ġ
    CTexture*       m_pTex;             // ������ ������ �ؽ�ó
    bool            m_bCamAffected;     // UI�� ī�޶� ������ �޴� ����
    bool            m_bMouseOn;         // UI���� ���콺�� �ִ���
    bool            m_bLbtnDown;        // UI������ ���� ��ư�� ���� ���� �ִ���
    

public:
    Vec2 GetFinalPos() { return m_vFinalPos; }
    CUI* GetParent() { return m_pParentUI; }    // �ڽ��� �θ� pUI �˾ƿ���
    bool IsMouseOn() { return m_bMouseOn; }
    bool ISLbtnDown() { return m_bLbtnDown; }
    void SetTex(CTexture* _pTex) { m_pTex = _pTex; }

    // �ڽ��� �ڽ� UI �����ϰ� �θ�� ���� �����ϱ�
    void AddChild(CUI* _pUI) { m_vecChildUI.push_back(_pUI); _pUI->m_pParentUI = this; }   
    const vector<CUI*>& GetChildUI() { return m_vecChildUI; }

private:    // �ڽ� ���� ������Ʈ - ���� �Լ�
    virtual void update_child();
    virtual void finalupdate_child();
    virtual void render_child(HDC _dc);

    void MouseOnCheck();
public:     // ���� ���� ������Ʈ - ���� �Լ�
    virtual void finalupdate();
    virtual void update();
    virtual void render(HDC _dc);

public:     // UI Event �Լ�
    virtual void MouseOn();             // �ش� UI�� ���콺�� �ö�� ��� ȣ��
    virtual void MouseLbtnDown();       // ���콺�� �ö�� ��쿡�� ������ �� ȣ��
    virtual void MouseLbtnUp();         // ���콺�� ������ ��
    virtual void MouseLbtnClicked();    // ���콺�� Ŭ���Ǿ��� ��: Down�� Up�� ���� UI������ �߻�..?
    virtual CUI* Clone() = 0;
public:
    // �⺻������ ��� ī�޶� bool�� �޴� �����ڸ� �����Ͽ� �ݵ�� ī�޶� ���� ���� �Է� ����
    CUI(bool _bCamAff);
    CUI(const CUI& _origin);
    virtual ~CUI();

    friend class CUIMgr;
};

