#pragma once
#include "MapObj.h"

class CTree :
	public CMapObj
{
protected:
	explicit CTree(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CTree();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;

	static CGameObject*		Create(LPDIRECT3DDEVICE9 pGraphicDev);
	static const _tchar* Tag() { return L"Tree"; }
};