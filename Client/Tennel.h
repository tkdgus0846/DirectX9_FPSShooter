#pragma once
#include "GameObject.h"

BEGIN(Engine)
class CTexture;
class CCollider;
END

class CTile;
class CDoor;
class CTennel : public CGameObject
{
private:
	explicit CTennel(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTennel();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);

private:
	virtual HRESULT Add_Component() override;

public:
	void Set_Position(_int iFrontorBack);
	void Set_Door(CDoor* pRoom) { m_pDoor = pRoom; }
	void Set_Tennel_Texture(STAGEINFO stageInfo);

	STAGEINFO GetStageInfo() const { return m_eStageInfo; }

private:
	Engine::CCollider*		m_pCollider;
	Engine::CTexture*		m_pTextureCom;

	STAGEINFO				m_eStageInfo;
	_bool					m_bInTennel;

	CDoor*		m_pDoor;	// ��ο� ����Ǿ��ִ� ���� ������.

public:
	static CTennel*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};

