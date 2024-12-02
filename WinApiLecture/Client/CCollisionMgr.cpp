#include "pch.h"
#include "CCollisionMgr.h"

#include "CSceneMgr.h"
#include "CScene.h"
#include "CObject.h"
#include "CCollider.h"

CCollisionMgr::CCollisionMgr()
	:m_arrCheck{}
{

}
CCollisionMgr::~CCollisionMgr()
{

}

void CCollisionMgr::update()
{
	// �浹 �˻�
	for (UINT iRow = 0; iRow < (UINT)GROUP_TYPE::END; ++iRow)
	{
		m_arrCheck[iRow];
		// �˻�� iRow ��° ��Ʈ���� �˻縦 �����Ѵ�. (�迭 ����  / ��Ī�̱� ������ �ѹ��� �˻�)
		for (UINT iCol = iRow; iCol < (UINT)GROUP_TYPE::END; ++iCol)
		{
			// iRow���� 32��Ʈ(4����Ʈ UINT)�� iCol��° ��Ʈ�� �ִ� ��Ʈ�� 1�� end(1)�ΰ��
			if (m_arrCheck[iRow] & (1 << iCol))
			{
				// ������� �� �׷��� ������Ʈ�� �����ͼ� �˻縦 ���� - �Ű� �ŸŴ��� include
				CollisionUpdateGroup((GROUP_TYPE)iRow, (GROUP_TYPE)iCol);
			}
		}
	}
}

void CCollisionMgr::CollisionUpdateGroup(GROUP_TYPE _eleft, GROUP_TYPE _eright)
{
	CScene* pCurScene = CSceneMgr::GetInst()->GetCurScene();
	// ���� ��� �׳� �ܼ��� ���������� ��, �޴� ��� ���۷��� ȭ�� ����� ������ ����������.
	// ���� ���� ���� ���۷����� ���� ������ �������� �߰��ȴ�.
	const vector<CObject*>& vecLeft = pCurScene->GetGroupObject(_eleft);
	const vector<CObject*>& vecRight = pCurScene->GetGroupObject(_eright);

	// �ݺ������� �ʱ�ȭ ���� �ʰ� ���⼭ ����
	map<ULONGLONG, bool>::iterator iter;

	// ���� ���� �׷��� �޾ƿ� ���, �ڱ� �ڽŰ��� �浹�� ���ܽ��Ѿ� �Ѵ�.
	for (size_t i = 0; i < vecLeft.size(); ++i)
	{
		// ���� �浹ü�� ���� ���
		if (nullptr == vecLeft[i]->GetCollider())
		{
			continue;	// ��Ƽ���� ���� �׳� �� �ݸ� ������ ������ ���ǰ� ���� �� ���� �ݺ���
		}
		for (size_t j = 0; j < vecRight.size(); ++j)
		{
			// ���� �浹ü�� ���� ���, ���� �ڱ� �ڽŰ��� �浹�� �˻��Ϸ��� ���
			if (nullptr == vecRight[j]->GetCollider()
				|| (vecLeft[i] == vecRight[j]))
			{
				continue;	// ��Ƽ���� ���� �׳� �� �ݸ��� ������ ���� �ݺ��� ����
			}
		
			CCollider* pLeftCol = vecLeft[i]->GetCollider();
			CCollider* pRightCol = vecRight[j]->GetCollider();

			// �������� �浹üũ - �浹ü ���� ���̵� ����
			COLLIDER_ID ID;
			ID.Left_id = pLeftCol->GetID();
			ID.Right_id = pRightCol->GetID();
			// �̷��� �ϼ��� 4 + 4 8����Ʈ ID�� ������ ID�� �ȴ�

			iter = m_mapColInfo.find(ID.ID);

			// �浹 ������ �� ��� ������ ��� (�浹���� �ʾҴ�=false �� ����)
			if (m_mapColInfo.end() == iter)
			{
				m_mapColInfo.insert(make_pair(ID.ID, false));
				iter = m_mapColInfo.find(ID.ID);
			}

			if (IsCollision(pLeftCol, pRightCol))
			{
				// ���� �浹 ���̴�.

				if (iter->second)
				{
					// �������� �浹�ϰ� �־���. ( ������ )

					if (vecLeft[i]->IsDead() || vecRight[j]->IsDead())
					{
						// �� �� �ϳ��� ���� �����̸� �浹�� ��� �������� ������Ѵ�.
						pLeftCol->OnCollisionExit(pRightCol);
						pRightCol->OnCollisionExit(pLeftCol);
						iter->second = false;
					}
					else
					{	// ���� ������ �ƴ϶�� ��� �浹 ���̴�.
						pLeftCol->OnCollision(pRightCol);
						pRightCol->OnCollision(pLeftCol);
					}
				}
				else
				{
					// �������� �浹���� �ʾ����� ���� �浹�ߴ� ( ������ ) �ٵ� ���� �� ������ ���̴�.
					// �׷� ���� �浹 �� �� �ɷ� ���� 
					// �ƴ϶�� ���� �浹�� ������ ���̴�.
					if (!vecLeft[i]->IsDead() && !vecRight[j]->IsDead())
					{			
						pLeftCol->OnCollisionEnter(pRightCol);
						pRightCol->OnCollisionEnter(pLeftCol);
						iter->second = true;
					}
					
				
				}
			}
			else// �浹�ϰ� ���� ���� ���
			{
				if (iter->second)
				{
					// �浹�ϴٰ� �̹��� �浹�� ������. ( ������ )
					pLeftCol->OnCollisionExit(pRightCol);
					pRightCol->OnCollisionExit(pLeftCol);
					iter->second = false;
				}
				
			}
		}
	}
}

bool CCollisionMgr::IsCollision(CCollider* _pLeftCol, CCollider* _pRightCol)
{
	Vec2 vLeftPos = _pLeftCol->GetFinalPos();
	Vec2 vLeftScale = _pLeftCol->GetScale();

	Vec2 vRightPos = _pRightCol->GetFinalPos();
	Vec2 vRightScale = _pRightCol->GetScale();
	
	if (((abs(vRightPos.x - vLeftPos.x)) <= (vLeftScale.x + vRightScale.x) / 2.f)
		&& ((abs(vRightPos.y - vLeftPos.y)) <= (vLeftScale.y + vRightScale.y) / 2.f))
	{
		return true; 
	}
	return false;
}

void CCollisionMgr::CheckGroup(GROUP_TYPE _eLeft, GROUP_TYPE _eright)
{
	// �׷�� �׷찣�� �浹 ���� �� enum���� ���� �׷��� enum�� ������ ��� 
	// ���� �迭 �ʿ��� ǥ�� ����
	// �� ���� ���� �׷� Ÿ���� ������,
	// ū ���� ��(��Ʈ)�� ���

	UINT iRow = (UINT)_eLeft;
	UINT iCol = (UINT)_eright;

	// ���� �� ū ��Ȳ���� �� ���� �ٲ� �ٽ� �ִ´�.
	if (iCol < iRow)
	{
	 iRow = (UINT)_eright;
	 iCol = (UINT)_eLeft;
	}
	// �̹� 1�̾ end������ 1�� ���� ���
	if (m_arrCheck[iRow] & (1 << iCol))
	{
		// �����ؼ� �ִ´�.
		m_arrCheck[iRow] &= ~(1 << iCol);
	}
	else
	{// 1�� iCol��ŭ ��Ʈ ����Ʈ ����Ʈ �ؼ� ���� �־��ش�.
		m_arrCheck[iRow] |= (1 << iCol);
	}
}

