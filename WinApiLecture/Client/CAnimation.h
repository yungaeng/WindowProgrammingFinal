#pragma once
#include "global.h"


class CAnimator;
class CTexture;

// ������ �� ���� ���
struct tAnimFrm
{
	Vec2	vLT;			// 1. �»��
	Vec2	vSlice;			// 2. �ڸ� ������ ����
	Vec2	vOffset;		// 3. ������ �� offset
	float	fDuration;		// 4. ������ ���ӽð�
};

class CAnimation
{
private:
	wstring				m_strName;	// �ִϸ��̼� �̸�
	CAnimator*			m_pAnimator;// �ڽ��� ����Ű�� �ִϸ�����
	CTexture*			m_pTex;		// Animation�� ����� �ؽ���
	vector<tAnimFrm>	m_vecFrm;	// ��� ������ ���� ����
	int					m_iCurFrm;	// ���� ������
	float				m_fAccTime;	// ���� �ð�
	bool				m_bFinish;	// �� ������ ����Ŭ�� �� ���Ҵ��� ����
private:
	void SetName(const wstring& _strName) { m_strName = _strName; }
	
public:
	const wstring& GetName() { return m_strName; }
	UINT GetMaxFream() { return (UINT)m_vecFrm.size(); }
	bool IsFinish() { return m_bFinish; }
	void SetFrame(int _iFrameIdx)
	{
		m_bFinish = false;
		m_iCurFrm = _iFrameIdx;
		m_fAccTime = 0.f;
	}
	// ���� �������� �ִϸ��̼� �������� ������ �� ������ �����´�.
	// ���۷����� ��ȯ�� ���� ���������ϰ� �ϱ�
	tAnimFrm& GetFrame(int _iIdx) { return m_vecFrm[_iIdx]; }
public:
	void Save(const wstring& _strRelativPath);
	void Load(const wstring& _strRelativPath);
public:
	void update();
	void render(HDC _dc);
	void Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep,float _fDuration, UINT _iFrameCount);

public:
	CAnimation();
	~CAnimation();

	friend class CAnimator;
};

