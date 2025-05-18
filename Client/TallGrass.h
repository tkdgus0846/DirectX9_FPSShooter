#pragma once
#include "MapObj.h"
BEGIN(Engine)
class CRcTex;
END

class CTallGrass :
	public CMapObj
{
protected:
	explicit CTallGrass(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTallGrass();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"TallGrass"; }

	virtual void OnCollisionStay(const class Collision* collision);


	void Burn(_float fTimeDelta);
private:
	_bool			m_bBurn = false;
	Engine::CRcTex* m_pRcTex = nullptr;
	_float			m_fV = 1.f;

protected:
	virtual void Free(void) override;
};

