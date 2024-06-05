#pragma once
class CUI;


class CUIMgr
{
	SINGLE(CUIMgr);

private:
	CUI* m_pFocusedUI;

public:
	void update();
	// UI���� ��Ŀ�� �Լ�
	void SetFocusdeUI(CUI* _pUI);

private:
	CUI* GetFocusedUI();
	CUI* GetTargetedUI(CUI* _pParentUI);	// �θ� UI ������ ������ Ÿ���� �� UI�� ã�� ��ȯ�Ѵ�.


};

