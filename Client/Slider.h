#pragma once
#include "MapObj.h"
class CSlider :
	public CMapObj
{
protected:
	explicit CSlider(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSlider();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;
	virtual void OnCollisionEnter(const class Collision* collsion);

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Slider"; }

protected:
	virtual void Free(void) override;
};