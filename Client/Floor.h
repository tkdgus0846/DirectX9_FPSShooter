#pragma once

#include "Include.h"
#include "GameObject.h"

class CFloor : public Engine::CGameObject
{
private:
	explicit CFloor(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CFloor();

public:
	HRESULT Ready_GameObject(STAGEINFO stageInfo);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void OnCollisionEnter(const class Collision* collsion);
	virtual void OnCollisionStay(const class Collision* collision);
	virtual void OnCollisionExit(const class Collision* collision);

	void		SetTextureName(const _tchar* name);
private:
	virtual HRESULT Add_Component() override;

public:
	static CFloor*		Create(LPDIRECT3DDEVICE9 pGraphicDev, STAGEINFO stageInfo);

private:
	const _tchar*	m_FloorTextureName;

private:
	virtual void Free(void) override;
};

