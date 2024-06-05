#pragma once
#include "CObject.h"

enum class PLAYER_STATE
{
    IDLE,
    WALK,
    ATTACK,
    DAMAGED,
    DEAD,
    JUMP,

};

enum class PLAYER_ATTACK_STATE
{
    NOMAL_ATT_1,
    NOMAL_ATT_2,
    NOMAL_ATT_3,

    SKILL_ATT_1,
    SKILL_ATT_2,
    // ...
};



class CTexture;

class CPlayer :
    public CObject
{
private:
  //  CTexture* m_pTex;

    PLAYER_STATE    m_eCurState;
    PLAYER_STATE    m_ePrevState;
    int             m_iDir;         // ���� ����
    int             m_iPrevDir;     // ���� ����
    int             m_iJumpStack;   // ���� ���� Ƚ��

    public:
        virtual void update();
        virtual void render(HDC _dc);
private:
    void CreateMissile();
    void update_state();
    void update_move();
    void update_animation();
    void update_gravity();

    virtual void OnCollisionEnter(CCollider* _pOther);



    // CObject�� clone �������̵� _ ���������
   // CPlayer* Clone() { return new CPlayer(*this); }
    CLONE(CPlayer);
public:
    CPlayer();
    // ���� ���� �ʿ� ������
    // �����Ϸ��� �̷� ������ ��������ڸ� ���� ���̴�
    //CPlayer(const CPlayer& _origin)
    //    :CObject(_origin)   // �θ� �� �����ڿ��� ����
    //    ,m_pTex(_origin.m_pTex)
    //{
    //}
    ~CPlayer();
};

