#pragma once
#include "CObject.h"


class CBlock :
    public CObject
{


public:
    virtual void update();
    virtual void render(HDC _dc);
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);


    CLONE(CBlock);
private:
    int CoinNum = 0;
public:
    CBlock();
    ~CBlock();
    // 06/13 얼마나 코인을 먹었니? 알려주는 함수
    int HowManyCoin();
};

