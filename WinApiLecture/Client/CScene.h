#pragma once
#include "global.h"
#include "CMonFactory.h"
// ���� #include "CObject.h" �� �ߴٸ�, CObject.h�� ����� �� ���� �������� ���� ���̴�.
// ���漱���� ���� ����� ����� �����ϴ� ���� ����
// ������ �� ��� ���� Ÿ�Կ� ���� ��ü���� ������ ���� ������ ������ Ÿ�����θ� ��밡��
class CObject;

class CScene
{
private:
	// �ڽ� �����͵��� �θ� �����ͷ� �� ����ų �� �ִ�.
	vector<CObject*>	m_arrObj[(UINT)GROUP_TYPE::END];	// ������Ʈ�� ���� �� ������ ���͸� �׷� ������ŭ ����
	wstring				m_strName;	//Scene �̸�

	UINT				m_iTileX;	// Ÿ���� x ����
	UINT				m_iTileY;	// Ÿ���� y ����

	UINT				m_iBlockX;
	UINT				m_iBlockY;

	CObject*			m_pPlayer;	// ���� ���� �÷��̾�
public:
	// �̸� ���� �� ��ȯ �Լ�
	void SetName(const wstring& _strName)	{	m_strName = _strName;	}
	const wstring& GetName() { return m_strName; }
	// x�� Ÿ�ϰ��� ��ȯ
	UINT GetTileX() { return m_iTileX; }	
	// y�� Ÿ�ϰ��� ��ȯ
	UINT GetTileY() { return m_iTileY; }	
	CObject* GetPlayer() { return m_pPlayer; }

	virtual void start();
	virtual void update();
	virtual void finalupdate();
	virtual void render(HDC _dc);
	virtual void render_tile(HDC _dc);

	// ���� ���� �Լ�
	// �ڡڡڼ��� ���� �Լ��� �����ϰ� �ִ� Ŭ������ ���� ��üȭ �� �� �ִ� Ŭ������ �ƴ�,
	// ������ ����� ���ϰ� �����ؾ��� �Լ��� ����� �˸��� ������ ū Ŭ����
	virtual void Enter() = 0;	// �ش� Scene�� ���� �� ȣ��
	virtual void Exit() = 0;	// �ش� Scene�� Ż�� �� ȣ��


public:
	// �ζ������� �����ؼ� protected�� ���� m_arrObj�� �ٷ� �����ϴ� �Ͱ� ������ ���� ����
	void AddObject(CObject* _pObj, GROUP_TYPE _eType)
	{
		m_arrObj[(UINT)_eType].push_back(_pObj);
	}

	void RegisterPlayer(CObject* _pPlayer) { m_pPlayer = _pPlayer; }

	// �׳� ��ȯ�ϸ� �����ؼ� ��ȯ�ϱ� ������ �������� �߰���, ���� ���� ��ü�� �ش�but �����Ұ�const
	const vector<CObject*>& GetGroupObject(GROUP_TYPE _eType){	return m_arrObj[(UINT)_eType];	}

	// UI������Ʈ �׷� ���� ������Ʈ �׷� ��ȯ �Լ�
	vector<CObject*>& GetUIGroup() { return m_arrObj[(UINT)GROUP_TYPE::UI]; }

	void DeleteGroup(GROUP_TYPE _eTarget);
	void DeleteAll();

	void CreateTile(UINT _iXCount, UINT _iYCount);
	void CreateBlock(int _count);
	void LoadTile(const wstring& _strRelativePath);

public:
	CScene();
	virtual ~CScene();
	// �ڡڡ� ����� �������� �ϴ� Ŭ������ ��� �Ҹ��ڿ� �����Լ��� ������ ����ؾ� �Ѵ�.
	// ���� ����ϴ� �ڽ� ��ü ���� �Ҹ��� �ǵ� �θ� Ÿ�� �����ͷ� ����Ű�� �־����ϱ�
	// virtual�Ҹ��ڸ� ȣ������ ������ �θ� �Ҹ��ڸ� ȣ��ǰ� ����
	// �ڡڡ� ���� ���� ��ü�� �Ҹ��ڰ� ȣ��� �� �ֵ��� SCene�� ���� �Ҹ��ڸ� ��������
};

