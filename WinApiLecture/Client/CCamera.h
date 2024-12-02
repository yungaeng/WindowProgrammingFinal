#pragma once

class CObject;

enum class CAM_EFFECT
{
	FADE_IN,
	FADE_OUT,
	NONE,
};


class CCamera
{
	SINGLE(CCamera);
private:
	Vec2		m_vLookAt;		// ���� ī�޶��� �߽� == ȭ���� �߽�, ī�޶� ���� ��ġ
	Vec2		m_vPrevLookAt;	// ī�޶� ���� ���� ������ ��ġ
	Vec2		m_vCurLookAt;	// ���� ��ġ�� ������ġ ������ġ
	CObject*	m_pTargerObj;	// ī�޶� Ÿ�� ������Ʈ
	Vec2		m_vDiff;		// �ػ� �߽���ġ��, ī�޶� Lookat���� ���̰�
	float		m_fTime;		// Ÿ���� ���󰡴µ� �ɸ��� �ð�
	float		m_fSpeed;		// Ÿ���� ���󰡴� �ӵ�
	float		m_fAccTime;		// �����ð�

//	CAM_EFFECT	m_eEffect;

public:
	void SetLookAt(Vec2 _vLook) 
	{
		m_vLookAt = _vLook; 
		float fMoveDist = (m_vLookAt - m_vPrevLookAt).Length();
		m_fSpeed = fMoveDist / m_fTime;
		m_fAccTime = 0.f;
	}
	void SetTarget(CObject* _pTarget) {m_pTargerObj = _pTarget; }

	Vec2 GetLookAt() { return m_vCurLookAt; }
	Vec2 GetRenderPos(Vec2 _vObjPos) { return _vObjPos - m_vDiff; }		// ���� ��ǥ -> ������ ��ǥ ��ȯ
	Vec2 GetRealPos(Vec2 _RenderPos) { return _RenderPos + m_vDiff; }	// ���� ��ǥ ��ȯ



public:
	void update();

private:
		void CalDiff();
};


