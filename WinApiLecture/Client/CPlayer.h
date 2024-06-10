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

enum class PLAYER_JUMP_STATE
{
    JUMP_UP = 10,
    JUMP_AIR,
    JUMP_DOWN,

    DOUBLE_JUMP_UP,
    DOUBLE_JUMP_AIR,
    DOUBLE_JUMP_DOWN,
};


enum class PLAYER_ATTACK_STATE
{
    NOMAL_ATT_1 = 20,
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
    PLAYER_JUMP_STATE       m_eCurJumpState;
    PLAYER_JUMP_STATE       m_ePrevJumpState;
    int             m_iJumpStack;   // 점프 가능 횟수

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



    // CObject의 clone 오버라이딩 _ 복사생성자
   // CPlayer* Clone() { return new CPlayer(*this); }
    CLONE(CPlayer);
public:
    CPlayer();
    // 굳이 만들 필요 없지만
    // 컴파일러는 이런 식으로 복사생성자를 만들 것이다
    //CPlayer(const CPlayer& _origin)
    //    :CObject(_origin)   // 부모 쪽 생성자에서 생성
    //    ,m_pTex(_origin.m_pTex)
    //{
    //}
    ~CPlayer();
};

