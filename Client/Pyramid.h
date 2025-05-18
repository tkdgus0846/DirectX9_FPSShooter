#pragma once
#include "MapObj.h"

class CPyramid :
	public CMapObj
{
protected:
	explicit CPyramid(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CPyramid();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	virtual HRESULT Add_Component() override;

protected:
	virtual void Free(void) override;
};