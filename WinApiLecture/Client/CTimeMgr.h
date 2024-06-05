#pragma once



class CTimeMgr
{
	SINGLE(CTimeMgr);
private:
	LARGE_INTEGER	m_llCurCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llPrevCount;	// ���� ī��Ʈ
	LARGE_INTEGER	m_llFrequency;	// �ʴ� ī��Ʈ Ƚ��

	double			m_dDT;	// (FPS�� ����=), 1 �����Ӵ� �ð�	(Delta Time), ������ ������ �ð���
	double			m_dAcc;	// 1�� üũ�� ���� �����ð�
	UINT			m_iCallCount;	// �Լ� ȣ�� Ƚ�� 
	UINT			m_iFPS;			// �ʴ� �Լ� ȣ�� Ƚ��



public:
	void init();	// �ʱ�ȭ
	void update();	// �� �����Ӹ��� ������Ʈ
	void render();
public:
	double GetDT() { return m_dDT; }	// 8����Ʈ ����
	float GetfDT() { return (float)m_dDT; }	// 4����Ʈ �÷�

};

