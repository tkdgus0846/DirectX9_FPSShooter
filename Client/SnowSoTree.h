#pragma once
#include "MapObj.h"
class CSnowSoTree :
	public CMapObj
{
protected:
	explicit CSnowSoTree(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSnowSoTree();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject() override;
	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SnowSoTree"; }

	virtual void OnCollisionStay(const class Collision* collision);
};

