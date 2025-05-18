#pragma once
#include "MiniGame.h"

class CSonicGame : public CMiniGame
{
private:
	explicit CSonicGame(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CSonicGame();


public:
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta) override;
	virtual void		Render_Scene(void) override;

	void	Game_Pattern(const _float& fTimeDelta);

	void	Game_Pattern1(const _float& fTimeDelta);
	void	Game_Pattern2(const _float& fTimeDelta);
	void	Game_Pattern3(const _float& fTimeDelta);
	void	Game_Pattern4(const _float& fTimeDelta);

	static CSonicGame*		Create(LPDIRECT3DDEVICE9 pGraphicDev);	

protected:
	virtual void Free(void) override;

private:
	_float			m_fGameSpeed;
	_bool			m_bGameStarted;
	_float			m_fBirdGenCool;
	_float			m_fBirdGenTime;

	_float			m_fSpeedUpTime;
	_float			m_fSpeedUpCool;

	class CSonic*	m_pSonic;
	class CSonicGround* m_pGround;

};

