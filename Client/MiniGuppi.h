#pragma once
#include "Enemy.h"

class CMiniGuppi : public CEnemy
{
private:
	explicit CMiniGuppi(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiniGuppi();

public:
	virtual HRESULT Ready_GameObject(const _vec3& vPos);
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	_bool m_bIsDamaged;

private:
	virtual HRESULT Add_Component() override;

public:
	static CMiniGuppi*	Create(LPDIRECT3DDEVICE9 pGraphicDev, const _vec3& vPos);
	static CGameObject*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Guppi_Green"; }

private:
	virtual void Free(void) override;
};

