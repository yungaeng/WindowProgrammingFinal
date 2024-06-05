#pragma once
#include "CUI.h"

#include "CScene.h"
#include "CObject.h"

class CScene;
class CScene_Tool;
class CObject;



typedef void(*BTN_FUNC) (DWORD_PTR, DWORD_PTR);


// ��ȯ Ÿ���� void, ���ڵ� void�� ��� �Լ� �����͸� �����ϴ� ���
typedef void(CScene::*SCENE_MEMFUNC)(void);
//CScene���� �����ϸ� CScene�� ��ӹ��� �ڽ� ����Լ������� �Լ��� ������ �� �ִ�.

// ���� ������Ʈ Ÿ������ �ϰ�ʹٸ�
typedef void(CObject::* OBJECT_MEMFUNC)(void);


class CBtnUI :
    public CUI
{
private:
    BTN_FUNC        m_pFunc;
    DWORD_PTR       m_param1;
    DWORD_PTR       m_param2;

    SCENE_MEMFUNC   m_pSceneFunc;       // �� ��ü�� ȣ���� �Լ�
    CScene*         m_pSceneInst;       // ȣ���� ��ų ��ü
public:
    virtual void MouseOn();             // �ش� UI�� ���콺�� �ö�� ��� ȣ��
    virtual void MouseLbtnDown();       // ���콺�� �ö�� ��쿡�� ������ �� ȣ��
    virtual void MouseLbtnUp();         // ���콺�� ������ ��
    virtual void MouseLbtnClicked();

    void SetClickedCallBack(BTN_FUNC _pFunc,DWORD_PTR _param1, DWORD_PTR _param2)
    {
        m_pFunc = _pFunc;
        m_param1 = _param1;
        m_param2 = _param2;
    }
    void SetClickedCallBack(CScene* _pScene, SCENE_MEMFUNC _pSceneFunc);
   

    CLONE(CBtnUI);
public:
    CBtnUI();
    ~CBtnUI();
};

