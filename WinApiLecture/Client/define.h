#pragma once

// SIngleton ��ũ��
#define SINGLE(type) public:\
						static type* GetInst()\
						{\
							static type mgr;\
								return &mgr;\
						}\
						private:\
						type();\
						~type();\

#define fDT CTimeMgr::GetInst()->GetfDT()	// 1�����Ӵ� �ð� �� - float ����
#define	DT	CTimeMgr::GetInst()->GetDT()	// 1�����Ӵ� �ð� �� - double ����
#define CLONE(type) type* Clone() {return new type(*this);}

#define KEY_CHECK(key,state) CKeyMgr::GetInst()->GetKeyState(key) == state
#define KEY_HOLD(key) KEY_CHECK(key,KEY_STATE::HOLD)
#define KEY_TAP(key) KEY_CHECK(key,KEY_STATE::TAP)
#define KEY_AWAY(key) KEY_CHECK(key,KEY_STATE::AWAY)
#define KEY_NONE(key) KEY_CHECK(key,KEY_STATE::NONE)
#define MOUSE_POS CKeyMgr::GetInst()->GetMousePos()

#define PI 3.1415926535f

// Ÿ�� �̹����� �����ϸ� 2�� �¼��� �ϴ� ���� ����.
#define TILE_SIZE 40

enum class GROUP_TYPE
{
	// �׷����� ���� ���� �߿�
	DEFAULT,
	TILE,
	BLOCK,
	GROUND,
	FLAG,	//0613 ��� �߰�

	MONSTER,
	PLAYER,
	PROJ_PLAYER,	// �÷��̾� ����ü
	PROJ_MONSTER,	// ���� ����ü


	COIN,	// ���� Ÿ�� �߰�

	// ���⼭ UI�� ��� ������Ʈ�� ���� �׷������� ���� ����
	UI = 31,
	END = 32,
};

enum class SCENE_TYPE
{
	TOOL,
	START,
	STAGE_01,
	STAGE_02,


	//end scene �߰�
	EnD,

	END,
};

enum class BRUSH_TYPE
{
	HOLLOW,
	BLACK,
	END,
};

enum class PEN_TYPE
{
	RED,
	GREEN,
	BLUE,
	END,
};

enum class EVENT_TYPE
{
	CREATE_OBJECT,
	DELETE_OBJECT,
	SCENE_CHANGE,
	CHANGE_AI_STATE,
	END,
};
enum class MON_STATE
{
	IDLE,
	PATROL,
	TRACE,
	ATT,
	RUN,
	DEAD,

	END,
};

//static CCore* GetInst()
//{
//	// �������� ���� �� �ʱ�ȭ ������ �ѹ��� ����
//	static CCore core;
//
//	return &core;
//}