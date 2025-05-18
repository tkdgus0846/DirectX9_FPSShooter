#pragma once
#include "UI.h"

class CGunUI : public CUI
{
private:
	explicit CGunUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CGunUI();

public:
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	static CGunUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	

protected:
	virtual void Free(void) override;

};

