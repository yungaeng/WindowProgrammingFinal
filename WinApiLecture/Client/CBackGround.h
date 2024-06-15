#pragma once
#include "CObject.h"
class CBackGround :
    public CObject
{
private:
    CTexture* m_pTex;





private:
    virtual void start();
    virtual void update();
    virtual void render(HDC _dc);
public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
    CLONE(CBackGround);

public:
    CBackGround();
    ~CBackGround();
};

