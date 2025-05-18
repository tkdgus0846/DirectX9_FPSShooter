#pragma once
#include "Item.h"

BEGIN(Engine)

class CRcTex;

END

class CHeartItem :
	public CItem
{
private:
	CHeartItem(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CHeartItem();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual void SetDead(_bool bDead = true) override;

private:
	D3DXMATRIX				matWorld, matView;

public:
	static CHeartItem*	Create(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual void OnCollisionEnter(const class Collision* collsion) final;
	virtual void OnCollisionStay(const class Collision* collision) final;

private:
	virtual void Free(void) override;
};