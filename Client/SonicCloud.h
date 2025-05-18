#pragma once
#include "GameObject.h"

class CSonicCloud : public CGameObject
{
private:
	explicit CSonicCloud(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicCloud();

	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual HRESULT Add_Component() override;

public:
	static CSonicCloud*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
};

