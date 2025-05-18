#pragma once

#include "Base.h"
#include "Include.h"
#include "GameObject.h"

BEGIN(Engine)

class  CRenderer : public CBase
{
	DECLARE_SINGLETON(CRenderer)

private:
	explicit CRenderer();
	virtual ~CRenderer();

public:
	void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
	void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Clear_RenderGroup(void);

	void		Render_Priority(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_NonAlpha(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_Alpha(LPDIRECT3DDEVICE9& pGraphicDev);

	void		Render_Pre_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_After_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_Final_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_Scene_AlphaUI(LPDIRECT3DDEVICE9& pGraphicDev);
	void		Render_UI(LPDIRECT3DDEVICE9& pGraphicDev);

	void		ToggleColorInversionFlag();
	void		ToggleRenderUI() { m_bRenderUI_Switch = m_bRenderUI_Switch == true ? false : true; }
	_bool		GetColorInversion() { return m_bColorInversion; }
	_bool		GetIsRenderUI() { return m_bRenderUI_Switch; }

private:
	list<CGameObject*>		m_RenderGroup[RENDER_END];

private:
	virtual void		Free(void);

private:
	_bool	m_bColorInversion = false;
	_bool	m_bRenderUI_Switch;
};

END