#pragma once
#include "MapObj.h"
class Cactus :
	public CMapObj
{
protected:
	explicit Cactus(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~Cactus();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject() override;
	virtual HRESULT Add_Component() override;
};

