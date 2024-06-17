#pragma once
#include "CObject.h"


struct tMonInfo
{
    float       fSpeed;           // �ӵ�
    float       fHP;              // ü��
    float       fRecgRange;       // ���� ����
    float       fAttRange;        // ���� ����
    float       fAtt;             // ���ݷ�
};


class AI;
class CMonster :
    public CObject
{

private:
    tMonInfo     m_tInfo;            
    AI*          m_pAI;              // AI

    Vec2    m_vCenterPos;       // �߽���
    float   m_fSpeed;           // �ӵ�
    float   m_fMaxDistance;     // �ִ� �̵��Ÿ�
    int     m_iDir;             // 1�̸� ������, -1�̸� ����
    //int     m_iHP;
public:
    bool m_bGoneDead;         // �״� ���� Ȱ�� ����
    float m_fDeadTime;
 

public:
    float GetSpeed() { return m_tInfo.fSpeed; }
    void SetSpeed(float _f) { m_tInfo.fSpeed = _f; }
   /* void SetMoveDistance(float _f) { m_fMaxDistance = _f; }
    void SetCenterPos(Vec2 _vPos) { m_vCenterPos = _vPos; }*/
  
    void SetAI(AI* _AI);

    // �����Ұ��� ������ ���� ũ�⸦ �ٿ���
    const tMonInfo& GetMonInfo() { return m_tInfo; }

private:
    void SetMonInfo(const tMonInfo& _info) { m_tInfo = _info; }
 
public:
    virtual void OnCollisionEnter(CCollider* _pOther);
    virtual void OnCollision(CCollider* _pOther);
    virtual void OnCollisionExit(CCollider* _pOther);
public:
    virtual void update();
    virtual void render(HDC _dc);


    CMonster* Clone() { return new CMonster(*this); }
   
public:
    CMonster();
    ~CMonster();
    friend class CMonFactory;
};

