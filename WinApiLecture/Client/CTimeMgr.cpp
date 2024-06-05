#include "pch.h"
#include "CTimeMgr.h"
#include "CCore.h"


CTimeMgr::CTimeMgr()
	:m_llCurCount{}
	, m_llFrequency{}
	, m_llPrevCount{}
	, m_dDT(0.)
	, m_iCallCount(0)
	, m_iFPS(0)
	,m_dAcc(0.)
{

}


CTimeMgr::~CTimeMgr()
{

}

void CTimeMgr::init()
{
	// ���� ī��Ʈ
	QueryPerformanceCounter(&m_llPrevCount);

	// �ʴ� ī��Ʈ Ƚ�� (�ʴ� ī��Ʈ ���� ��)
	QueryPerformanceFrequency(&m_llFrequency);
}

void CTimeMgr::update()
{
	QueryPerformanceCounter(&m_llCurCount);

	// ���� �������� ī���ð� ���� ������ ī���� ���� ���̸� ���Ѵ�. �̸� �ʴ� ī��Ʈ Ƚ���� ������ -> ������ī��Ʈ�� �ð��� ���´�
	m_dDT = (double)(m_llCurCount.QuadPart - m_llPrevCount.QuadPart) / (double)(m_llFrequency.QuadPart);

	// ���� ������ī��Ʈ �� ���� ������ī��Ʈ������ ���� (���� ����� ����)
	m_llPrevCount = m_llCurCount;

#ifdef _DEBUG
	if (m_dDT > (1. / 60.))
		m_dDT = (1. / 60.);
#endif
}

void CTimeMgr::render()
{

	// ȣ�� Ƚ�� ����
	++m_iCallCount;

	m_dAcc += m_dDT;	// DT ����

	if (m_dAcc >= 1.) // 1�ʿ� �ѹ�(m_dAcc�� ���� �� ���� 1�ʰ� �Ѿ��)
	{
		m_dAcc = 0.;
		m_iFPS = m_iCallCount;
		m_iCallCount = 0;

		wchar_t szBuffer[255] = {};
		swprintf_s(szBuffer, L"FPS : %d, DT : %f", m_iFPS, m_dDT);
		SetWindowText(CCore::GetInst()->GetMainHwnd(), szBuffer);
	}
}
