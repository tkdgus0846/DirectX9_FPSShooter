#pragma once
#include "Scene.h"

class CLoadingScene : public CScene
{
private:
	explicit CLoadingScene(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CLoadingScene();

public:
	// CScene을(를) 통해 상속됨
	virtual HRESULT		Ready_Scene(void) override;
	virtual _int		Update_Scene(const _float& fTimeDelta)override;

	// 로딩 씬에서는 방의 객체들에대한 업데이트를 수행하면 안되기 때문에 정적 레이어들 말고 동적레이어들만 업데이트할수 있게 만든다.
	

	virtual void		LateUpdate_Scene(void)override;
	virtual void		Render_Scene(void) override;

	void				Set_Stage(CScene* stageScene)
	{
		m_pScene = stageScene;
	}

	void				Set_LoadingID(LOADINGID loadingID)
	{
		m_eLoadingID = loadingID;
	}

	

private:
	HRESULT				Ready_Proto(void);

private:
	class CLoading*			m_pLoading;
	CScene*					m_pScene;
	class CMiniGame*		m_pMiniGame;
	_bool					m_bLoadingCreated;
	LOADINGID				m_eLoadingID;

	_float					m_fLoadingTime;

	class CLoadingBackground* m_pLoadingBackground;

public:
	static CLoadingScene*		Create(LPDIRECT3DDEVICE9 pGraphicDev, LOADINGID loadingID, CScene* stageScene = nullptr);

private:
	virtual void		Free(void);
};

