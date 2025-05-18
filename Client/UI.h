#pragma once
#include "GameObject.h"

class CUI : public CGameObject
{
protected:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CUI();
	
	_bool		m_bShow;

public:
	_bool	CanShow() const { return m_bShow; }
	_bool   SetShow(_bool state) { m_bShow; }

protected:
	_matrix matView, matWorld;
	_vec3 m_vScale, m_vPos;

	virtual void	Set_ViewMatrix_UI();
	virtual void	Set_ViewMatrix_UI(_float posX, _float posY);
	virtual void	Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY);

};