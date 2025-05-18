#pragma once
#include "MapObj.h"
class CSnowTree :
	public CMapObj
{
protected:
	explicit CSnowTree(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSnowTree();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void Render_GameObject() override;
	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"SnowTree"; }

	virtual void OnCollisionStay(const class Collision* collision);
};