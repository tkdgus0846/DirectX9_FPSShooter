#pragma once
#include "UI.h"
#include "Player.h"

BEGIN(Engine)

class CRcTex;
class CTexture;
class CAnimation;
class CVIBuffer;

END

struct MiniMapCheck
{
	_bool		m_bCheck = false;
	_bool		m_bInRange = false;

	_int		m_iTextureNum = 0;
};

class CMiniMapBack :
	public CUI
{
public:
	explicit CMiniMapBack(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CMiniMapBack();

public:
	virtual HRESULT Add_Component() override;
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

	void		MiniMapReset();

private:
    void Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY);

private:
	STAGEINFO m_curStageInfo;

	D3DXMATRIX  matWorld, matView;

	CRcTex* m_pRcTex;
	CTexture* m_pTexture;

	array<CComponent*, 3 * 3> m_arrMap;
	array<MiniMapCheck, 3 * 3> m_arrMapInfo;

	_float		m_fPosX = 320.f;
	_float		m_fPosY = -200.f;

	_float		m_pPlayerX = 0.f;
	_float		m_pPlayerZ = 0.f;

	_float		m_pPlayerMoveX = 0.1f;
	_float		m_pPlayerMoveZ = 0.1f;

	_float		m_pPlayerTunnelX = 0.f;
	_float		m_pPlayerTunnelY = 0.f;

	_float		m_bLevelUp = false;


	void		MiniMapMove();
	void		MiniMapCheck();
	void		MiniMapInRange();

public:
	static CMiniMapBack*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free(void) override;
};