#pragma once

#include "Base.h"

BEGIN(Engine)

class CScene;
class CComponent;

class  CManagement : public CBase
{
	DECLARE_SINGLETON(CManagement)

private:
	explicit CManagement();
	virtual ~CManagement();

public:
	CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

public:
	HRESULT			Set_Scene(CScene* pScene, _bool bChangingStage = false);
	HRESULT			Set_Scene_NotDelete(CScene* pScene);
	CScene*			Get_Scene() { return m_pScene; }

	_int			Update_Management(const _float& fTimeDelta);
	void			LateUpdate_Management();
	void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev);

	void			Add_GameObject(class CGameObject* pObj);
	CGameObject*	Get_GameObject(LAYERID LayerID, const _tchar* pObjTag);
	void			Remove_GameObject(LAYERID layerID, CGameObject* obj);

	// 플레이어를 전역적으로 불러옴.
	class CGameObject*	Get_Player() { return m_pPlayer; }
	void				Set_Player(CGameObject* player);

	void				Start_WorldTimer() { m_bPlayingWorldTimer = true; }
	void				Stop_WorldTimer() { m_bPlayingWorldTimer = false; }
	_float				Get_WorldTime() const { return m_fWorldTime; }
	void				Reset_WorldTime() { m_fWorldTime = 0.f; }
	void				Stop_SlowTime();
	void				Reset_SlowTime(const _float & fTimeDelta);
	void				Set_TimeStopped(_bool state = true) { m_bTimeStopped = state; }
	_bool				Get_TimeStopped() const { return m_bTimeStopped; }

	void				Set_StaticLayerArr_Management(vector<class CLayer*>* layerArr);

	void				Next_Stage();
	void				Set_Ending();

private:
	CScene*			m_pScene = nullptr;
	class CGameObject*	m_pPlayer;

	_float			m_fWorldTime;
	_bool			m_bPlayingWorldTimer;
	_bool			m_bChangeRoom;

	_bool			m_bChangingStage;
	_bool			m_bTimeStopped;

private:
	virtual void	Free(void);
};

END