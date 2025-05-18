#pragma once

#include "Scene.h"

class CMyEdit : public CScene
{
private:
	explicit CMyEdit(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMyEdit();

public:
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta)override;
	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

private:
	_int				m_iCurRoomIdx;
	_int				m_iPreRoomIdx;

public:
	static CMyEdit*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void		Free(void);
};

