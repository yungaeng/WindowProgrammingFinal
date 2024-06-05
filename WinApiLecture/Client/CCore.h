#pragma once
// ����
// ����
// �������� ( ������ ���� ��� ) (�������� �ʴ� �̹��� ���)
// 1. �Լ� �ȿ� ����� ��� - �ش� �Լ������� ���� ���� 
// 
// 2. ���� ��򰡿� ����� ��� - �ش� ���� �ȿ����� ���� ����
//	���������� ��쿡�� �ٸ� ���Ͽ� �Ȱ��� �̸��� ���������� ������ ����
// 
// 3. Ŭ���� �ȿ� ����� ���
// ���� ��� ( ������ ���� ��� )
// Ŭ���� �ȿ����� ���� ���� (�ڰ�ü�ȿ� �ִ� ���� �ƴ�!!��)
// ��ü ������ �ȿ� ���Ե��� ����
// ��ü�� ����, ������, �� � ���� ���� ��� ��ü�� ������ ������ ����



// �̱��� ����
// �ش� Ŭ���� ��ü�� ������ 1���� ����
// ���� ��𼭳� ������ �����ؾ���
// extern���� ���� �س����� ���� ���������� ������ ���������ϱ� ������
// ������ ���ѽ�ų ����� ã�ƾ� �Ѵ�.
// 1. ������ ���ܳ��� - ������ �̷��� �ͽ������ε� ������ �Ұ���
// 2. ���� ������ ����Լ��� ��ü�� ����
// 3. ������ ����Լ��� ��ü�� �־�� ���� ���� - ��� (this���� �ֱ� ���ؼ�)
// 4. ���� ��ü�� ��� �Ǵ� ��������Լ��� �����. (static)
//	staticŰ���尡 ���� ��������Լ��� ��ü�� ���̵� ȣ���� �����ϴ�
// 5. �� ��쿡�� this�� ���� ��� ������ �Ұ��� (ȣ���� ��ü�� ���� ������)
// 6. �ڵ��� �� ���� ����Լ��� ��ü�� ���� ȣ���ص� this�� ����
// 7. �Ϲ� ����� �ƴ� ���� ������� ������ �����ϴ�.
//	�� ���� ����Լ��� ���� ������� ������ ������ ��.


// ���� ����� Ȱ���� �̱���
//class CCore
//{
//private:
//	// CCore�� ����Ű�� �����͸� ���� ����� ���� - ������ ������ ����
//	static CCore* g_pInst;
//public:
//	// ���� ��� �Լ�
//	 static CCore* GetInstance()
//	{
//		 // ���� ������ ���� - ������ ������ ����, �Լ��� ������
//		 // ������� ����, ���� ��� ����
//		 // static���� �����߱⿡ �ʱ�ȭ�� �ʱ� 1���� �ߵ�
//		//  ����, ����� ������ �־ ���� ����� �ٲ�
//
//		 // ���� ȣ�� �� ���
//		 if (nullptr == g_pInst)
//		 {
//			 // CCore ��ü ��ü�� ���� �� ������ ����
//			  g_pInst = new CCore;
//		 }
//		return g_pInst;
//	}
//
//	 static void Release()
//	 {
//		 if (nullptr != g_pInst)
//		 {
//			 delete g_pInst;
//			 g_pInst = nullptr;
//		 }
//	 }
//
//	 // �ܺο����� CCore ��ü�� ������ �� ������ ������ private���� ����
//private:
//	CCore();
//	~CCore();
//};
//
//// ���� ����� �ܺο��� �ʱ�ȭ�� �ݵ�� �ʿ��ϴ�.




// ���� ����Լ��� ���� ������ Ȱ���ϴ� �̱���
// 
// ���ϴ´�� ������ �Ұ����� - �������� ����
class CCore
{
//public:
	//static CCore* GetInst()
	//{
	//	// �������� ���� �� �ʱ�ȭ ������ �ѹ��� ����
	//	static CCore core;

	//	return &core;
	//} �Ʒ��� ��ũ�� ����
	SINGLE(CCore);
private:
	HWND m_hWnd;			// ���� ������ �ڵ�
	POINT m_ptResolution;	// ���� ������ �ػ�
	HDC m_hDC;				// ���� �����쿡 Draw �� DC

	HBITMAP m_hBit;
	HDC m_memDC;

	// ���� ����ϴ� GDI Object
	HBRUSH	m_arrBrush[(UINT)BRUSH_TYPE::END];
	HPEN	m_arrPen[(UINT)PEN_TYPE::END];


	HMENU	m_hMenu;	// tool_scene���� ����� �޴�
public :
	int init(HWND _hWnd,POINT _ptResolution);
	void progress();
	
private:
	void Clear();
	void CreateBrushPen();
public:
	void DockMenu();
	void DivideMenu();
	void ChangeWindowSize(Vec2 _vResolution, bool _bMenu);
public:
	HWND GetMainHwnd() { return m_hWnd; }
	HDC GetMainDC() { return m_hDC; }
	POINT GetResolution() { return m_ptResolution; }
	//HMENU GetMenu() { return m_hMenu; }

	HBRUSH GetBrush(BRUSH_TYPE _eType) { return m_arrBrush[(UINT)_eType]; }
	HPEN GetPen(PEN_TYPE _eType) { return m_arrPen[(UINT)_eType]; }
};
