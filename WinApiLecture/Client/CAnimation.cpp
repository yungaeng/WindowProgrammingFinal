#include "pch.h"

#include "CTimeMgr.h"

#include "CAnimation.h"
#include "CAnimator.h"
#include "CTexture.h"
#include "CObject.h"
#include "CCamera.h"
#include "CPathMgr.h"
#include "CResMgr.h"

CAnimation::CAnimation()
	:m_pAnimator(nullptr)
	, m_pTex(nullptr)
	, m_iCurFrm(0)
	, m_fAccTime(0.f)
	, m_bFinish(false)
{
}

CAnimation::~CAnimation()
{
}



void CAnimation::Save(const wstring& _strRelativPath)
{
	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativPath;
	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(),L"wb");
	assert(pFile);

	// Animation�� �̸��� �����Ѵ�. (������ ����ȭ)
	fprintf(pFile, "[Animation Name]\n");
	string strName = string(m_strName.begin(), m_strName.end());
	fprintf(pFile, strName.c_str());
	//SaveWString(m_strName, pFile);
	fprintf(pFile, "\n");

	// Animation�� ����� �ؽ����� Ű�� ����, ����� �ø� ����� ����� ����
	fprintf(pFile, "[Texture Key]\n");
	strName = string(m_pTex->GetKey().begin(), m_pTex->GetKey().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");

	fprintf(pFile, "[Texture Path]\n");
	strName = string(m_pTex->GetRelativePath().begin(), m_pTex->GetRelativePath().end());
	fprintf(pFile, strName.c_str());
	fprintf(pFile, "\n");
	//SaveWString(m_pTex->GetKey(),pFile);
	//SaveWString(m_pTex->GetRelativePath(), pFile);


	// �������� ���� ����
	fprintf(pFile, "[Frame Count]\n");
	fprintf(pFile, "%d\n",(int)m_vecFrm.size());
	//size_t iFrameCount = m_vecFrm.size();
	//fwrite(&iFrameCount, sizeof(size_t), 1, pFile);

	// ������ ������ ������ ����
	for (size_t i = 0; i < m_vecFrm.size(); ++i)
	{
		fprintf(pFile, "[Frame Index]\n");
		fprintf(pFile, "%d\n", (int)i);

		fprintf(pFile, "[Left Top]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vLT.x, (int)m_vecFrm[i].vLT.y);

		fprintf(pFile, "[Slice Size]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vSlice.x, (int)m_vecFrm[i].vSlice.y);

		fprintf(pFile, "[Offset]\n");
		fprintf(pFile, "%d %d\n", (int)m_vecFrm[i].vOffset.x, (int)m_vecFrm[i].vOffset.y);

		fprintf(pFile, "[Duration]\n");
		fprintf(pFile, "%f\n", m_vecFrm[i].fDuration);

		fprintf(pFile, "\n\n");

	}

	

	
	// ��� ������ ���� ����
	// ������ �����ּҷκ��� ���� ������ũ�⸸ŭ�� ���� ��ü ��������� ���Ͽ� ����
	/*fwrite(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);*/


	fclose(pFile);
}

void CAnimation::Load(const wstring& _strRelativPath)
{

	wstring strFilePath = CPathMgr::GetInst()->GetContentPath();
	strFilePath += _strRelativPath;

	FILE* pFile = nullptr;
	_wfopen_s(&pFile, strFilePath.c_str(), L"rb");
	assert(pFile);

	// ���� �Լ� ���� - ���Ͽ��� �����Ұ�
	//// ���ڿ� �о���� �Լ� ,�о�ͼ� �ִϸ��̼��� �̸����� ����
	////LoadWString(m_strName, pFile);
	//

	//
	//wstring strTexKey,strTexPath; // �ؽ�ó�� Ű(���ڿ�) �޾ƿ���
	//LoadWString(strTexKey, pFile);// �ؽ�ó�� ��� ��� �޾ƿ���
	//LoadWString(strTexPath, pFile);
	//// �ؽ�ó�� �����س��� ���α׷� ������� �ϸ� ResMgr�� ����ִ� �ؽ�ó ������ �����
	//// ���� Ű �Ӹ� �ƴ϶� ��α��� �޾Ƴ��� Find�� �ƴ� Load�� ���� �Ϻ��� �޾ƿ´�.
	//m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);// ��ϵ� �ؽ�ó�� ������ �����
	//
	//// ������ ����
	//size_t iFrameCount = 0;
	//fread(&iFrameCount, sizeof(size_t), 1, pFile);
	//
	//// ��� ������ ����		- �ѹ��� ������ �迭 Ȯ�忡 ���̴� �ڿ��� �������� ���� �� ����
	//m_vecFrm.resize(iFrameCount);		// ������ ������ŭ ���� Ȯ��
	//fread(m_vecFrm.data(), sizeof(tAnimFrm), iFrameCount, pFile);


	// ���� ���� ���� ����
	char szBuff[256] = {};
	string str;
	// ���ڿ� �� �پ� �о���� �Լ�

	// 1. �ִϸ��̼� �̸� �о����
	FScanf(szBuff, pFile);	// �׸��� ������
	FScanf(szBuff, pFile);
	str = szBuff;
	m_strName = wstring(str.begin(), str.end());

	// 2. �ؽ�ó Ű
	FScanf(szBuff, pFile);	// �׸��� ������
	FScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexKey = wstring(str.begin(), str.end());

	// 3. �ؽ�ó ��� ���
	FScanf(szBuff, pFile);	// �׸��� ������
	FScanf(szBuff, pFile);
	str = szBuff;
	wstring strTexPath = wstring(str.begin(), str.end());

	m_pTex = CResMgr::GetInst()->LoadTexture(strTexKey, strTexPath);


	// 4. ������ ����
	FScanf(szBuff, pFile);	// �׸��� ������
	int iFrameCount = 0;
	fscanf_s(pFile, "%d", &iFrameCount);
	

	// ������ ������ ������ �ҷ�����
	tAnimFrm frm = {};
	for (int i = 0; i < iFrameCount; ++i)
	{
		POINT pt = {};
		while (true)
		{
			FScanf(szBuff, pFile);	// ��� �о��
			// �� ���ڿ��� ������ 0
			if (!strcmp("[Frame Index]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
			}
			else if (!strcmp("[Left Top]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vLT = pt;
			}
			else if (!strcmp("[Slice Size]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vSlice = pt;
			}
			else if (!strcmp("[Offset]", szBuff))
			{
				fscanf_s(pFile, "%d", &pt.x);
				fscanf_s(pFile, "%d", &pt.y);
				frm.vOffset = pt;
			}
			else if (!strcmp("[Duration]", szBuff))
			{
				fscanf_s(pFile, "%f", &frm.fDuration);
				break;
			}
		}
		m_vecFrm.push_back(frm);
	}
	

	fclose(pFile);
}

void CAnimation::update()
{
	if (m_bFinish)
		return;

	m_fAccTime += fDT;
	if (m_fAccTime > m_vecFrm[m_iCurFrm].fDuration)
	{
		++m_iCurFrm;
		// �Ѿ �ð����� �ٽ� �ʱ�ȭ


		if (m_vecFrm.size() <= m_iCurFrm)
		{
			// ������ ���� ���� ������ ���
			m_iCurFrm = -1; //-1;
			m_bFinish = true;
			m_fAccTime = 0.f;
			return;
		}
		m_fAccTime = m_fAccTime - m_vecFrm[m_iCurFrm].fDuration;
	}
		
}


void CAnimation::render(HDC _dc)
{
	if (m_bFinish)
		return;
	CObject* pObj = m_pAnimator->GetObj();
	Vec2 vPos = pObj->GetPos();
	m_vecFrm[m_iCurFrm].vOffset;		// offset
	vPos += m_vecFrm[m_iCurFrm].vOffset;// Object Position�� Offset��ŭ �߰� �̵���ġ
	//m_vecFrm[m_iCurFrm].vSlice;
	

	// ī�޶� ������ ��ǥ�� ��ȯ
	vPos = CCamera::GetInst()->GetRenderPos(vPos);
	
	TransparentBlt(_dc
		,(int)(vPos.x - m_vecFrm[m_iCurFrm].vSlice.x / 2.f)
		,(int)(vPos.y - m_vecFrm[m_iCurFrm].vSlice.y / 2.f)
		,(int)(m_vecFrm[m_iCurFrm].vSlice.x)
		,(int)(m_vecFrm[m_iCurFrm].vSlice.y)
		,m_pTex->GetDC()
		,(int)(m_vecFrm[m_iCurFrm].vLT.x)
		,(int)(m_vecFrm[m_iCurFrm].vLT.y)
		,(int)(m_vecFrm[m_iCurFrm].vSlice.x)
		,(int)(m_vecFrm[m_iCurFrm].vSlice.y)
		,RGB(255,0,255));
}
void CAnimation::Create(CTexture* _pTex, Vec2 _vLT, Vec2 _vSliceSize, Vec2 _vStep, float fDuration, UINT _iFrameCount)
{
	m_pTex = _pTex;
	tAnimFrm frm = {};
	for (UINT i = 0; i < _iFrameCount; ++i)
	{
		frm.fDuration = fDuration;	// ������ ���ӽð� = �� ����Ŭ
		frm.vSlice = _vSliceSize;	// �ڸ� ��ġ
		frm.vLT = _vLT + _vStep * (float)i;// �̵��� ����

		// ������ ������ m_vecFrm�� pushback
		m_vecFrm.push_back(frm);
	}
}




