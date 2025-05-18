#pragma once
#include "Enemy.h"

class CNubPilot : public CEnemy
{
private:
	explicit CNubPilot(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CNubPilot();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	_float m_fTime;
	virtual HRESULT Add_Component() override;

public:
	static CNubPilot*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"NubPilot"; }
private:
	virtual void Free(void) override;
};

