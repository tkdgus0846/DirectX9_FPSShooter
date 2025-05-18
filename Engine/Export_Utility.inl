#include "Export_Utility.h"

CGameObject* Get_Player()
{
	return CManagement::GetInstance()->Get_Player();
}

void			Set_Player(CGameObject* player)
{
	CManagement::GetInstance()->Set_Player(player);
}

inline CLayer * Get_Layer(LAYERID LayerID)
{
	return CManagement::GetInstance()->Get_Scene()->Get_Layer(LayerID);
}

HRESULT			Create_Management(CManagement** ppManagement)
{
	CManagement*		pManagement = CManagement::GetInstance();
	NULL_CHECK_RETURN(pManagement, E_FAIL);

	*ppManagement = pManagement;

	return S_OK;
}

void		Start_WorldTimer()
{
	CManagement::GetInstance()->Start_WorldTimer();
}

void		Stop_WorldTimer()
{
	CManagement::GetInstance()->Stop_WorldTimer();
}

_float		Get_WorldTime()
{
	return CManagement::GetInstance()->Get_WorldTime();
}

CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(LayerID, pObjTag, pComponentTag, eID);
}

void Engine::Add_GameObject(class CGameObject* pObj)
{
	CManagement::GetInstance()->Add_GameObject(pObj);
}

CGameObject*		Get_GameObject(LAYERID LayerID, const _tchar* pObjTag)
{
	return CManagement::GetInstance()->Get_GameObject(LayerID, pObjTag);
}

//void Set_StaticLayerArr(vector<CLayer*>* layerArr)
//{
//	CManagement::GetInstance()->Set_StaticLayerArr(layerArr);
//}

void Remove_GameObject(LAYERID LayerID, CGameObject* obj)
{
	CManagement::GetInstance()->Remove_GameObject(LayerID, obj);
}

HRESULT			Set_Scene(CScene* pScene, _bool bChangingStage)
{
	return CManagement::GetInstance()->Set_Scene(pScene, bChangingStage);
}

_int			Update_Management(const _float& fTimeDelta)
{
	return CManagement::GetInstance()->Update_Management(fTimeDelta);
}
void			LateUpdate_Management()
{
	CManagement::GetInstance()->LateUpdate_Management();
}
void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagement::GetInstance()->Render_Management(pGraphicDev);
}

void			Stop_SlowTime()
{
	CManagement::GetInstance()->Stop_SlowTime();
}

void			Reset_SlowTime(const _float & fTimeDelta)
{
	CManagement::GetInstance()->Reset_SlowTime(fTimeDelta);
}

HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent)
{
	return CProtoMgr::GetInstance()->Ready_Proto(pProtoTag, pComponent);
}

CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject)
{
	return CProtoMgr::GetInstance()->Clone_Proto(pProtoTag, pGameObject);
}

// AI 클론용
CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject, CBlackBoard* pBlackBoard)
{
	return CProtoMgr::GetInstance()->Clone_Proto(pProtoTag, pGameObject, pBlackBoard);
}

// Collider 클론용
CComponent*	Clone_Proto(const _tchar * pProtoTag, const _tchar* colliderName, class CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize)
{
	return CProtoMgr::GetInstance()->Clone_Proto(pProtoTag, colliderName, pGameObject, eColGroup, boundSize);
}

// Particle 클론용
CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, const _int& particleNums, const _vec3& origin, const _vec3& boundSize)
{
	return CProtoMgr::GetInstance()->Clone_Proto(pProtoTag, pGameObject, particleNums, origin, boundSize);
}

void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject)
{
	CRenderer::GetInstance()->Add_RenderGroup(eID, pGameObject);
}
void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev)
{
	CRenderer::GetInstance()->Render_GameObject(pGraphicDev);
}
void		Clear_RenderGroup(void)
{
	CRenderer::GetInstance()->Clear_RenderGroup();
}

void		Add_Collider(COLGROUP eID, CCollider * pCollider)
{
	CCollisionMgr::GetInstance()->Add_Collider(eID, pCollider);
}

void		Add_Collider(CGameObject* gameObject)
{
	CCollisionMgr::GetInstance()->Add_Collider(gameObject);
}

void		Check_Collision(COLGROUP eGroup1, COLGROUP eGroup2)
{
	CCollisionMgr::GetInstance()->Check_Collision(eGroup1, eGroup2);
}

void		Toggle_ColliderRender()
{
	CCollisionMgr::GetInstance()->Toggle_ColliderRender();
}

void		Change_ColGroup(CCollider* collider, COLGROUP changeID)
{
	CCollisionMgr::GetInstance()->Change_ColGroup(collider, changeID);
}
_bool		Collider_GetIsRender()
{
	return CCollisionMgr::GetInstance()->GetIsRender();
}

void		Remove_Collider(CCollider* collider, COLGROUP colID)
{
	CCollisionMgr::GetInstance()->Remove_Collider(collider, colID);
}

void		Remove_Collider(CGameObject* gameObject)
{
	CCollisionMgr::GetInstance()->Remove_Collider(gameObject);
}

//void		Set_Collider(COLGROUP eGroup, CCollider* pCollider)
//{
//	CCollisionMgr::GetInstance()->Set_Collider(eGroup, pCollider);
//}

const	CCamera* Get_CurCamera()
{
	CCameraMgr::GetInstance()->Get_CurCamera();
}

void		On_Camera(const _tchar* pCamTag)
{
	CCameraMgr::GetInstance()->On_Camera(pCamTag);
}

void Shake_Camera(SHAKE_TYPE eType, const _float& fForce, const _float& fTime)
{
	CCameraMgr::GetInstance()->On_Shake(eType, fForce, fTime);
}
HRESULT			Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
	return CLightMgr::GetInstance()->Ready_Light(pGraphicDev, pLightInfo, iIndex);
}

void						Release_Utility(void)
{
	CCameraMgr::GetInstance()->DestroyInstance();
	CLightMgr::GetInstance()->DestroyInstance();
	CCollisionMgr::GetInstance()->DestroyInstance();
	CRenderer::GetInstance()->DestroyInstance();
	CProtoMgr::GetInstance()->DestroyInstance();
	CManagement::GetInstance()->DestroyInstance();
}