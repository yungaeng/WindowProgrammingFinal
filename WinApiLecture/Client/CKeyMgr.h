#pragma once


// 1. ������ ����ȭ
// ���� ������ ������ ���� Ű �Է¿� ����, ������ �̺�Ʈ�� ��������.

// 2. Ű �Է� �̺�Ʈ ��ü�� ���� ó��
// tap, hold, away





enum class KEY_STATE
{
	NONE,	// ������ �ʾҰ�, �������� �� ���� ����
	TAP,	// �� ���� ����
	HOLD,	// ������ �ִ� ����
	AWAY,	// �� �� ����
};

enum class KEY
{
	LEFT,
	RIGHT,
	UP,
	DOWN,
	Q,
	W,
	E,
	R,
	T,
	Y,
	U,
	I,
	O,
	P,
	A,
	S,
	D,
	F,
	G,
	Z,
	X,
	C,
	V,
	B,

	ALT,
	CTRL,
	LSHIFT,
	ENTER,
	SPACE,
	ESC,

	LBTN,
	RBTN,


	LAST, // enum�� ��

};
struct tKeyInfo
{
	KEY_STATE	eState;	// � �����ΰ�?B
	bool bPrevPush;			// ���� �����ӿ� ���ȴ��� ����
};

class CKeyMgr
{
	SINGLE(CKeyMgr);

private:

	vector<tKeyInfo>	m_vecKey;
	Vec2				m_vCurMousePos;
public:
	void init();
	void update();


public:
	KEY_STATE GetKeyState(KEY _eKey){return m_vecKey[(int)_eKey].eState;}
	Vec2 GetMousePos() { return m_vCurMousePos; }

};


