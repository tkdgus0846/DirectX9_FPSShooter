#pragma once

#include "Management.h"
#include "ProtoMgr.h"
#include "Renderer.h"
#include "CollisionMgr.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "FrustrumNormalTex.h"
#include "RoomTex.h"
#include "FloorTex.h"
#include "WallTex.h"

#include "Snow.h"
#include "Firework.h"

#include "Collider.h"
#include "GameObject.h"
#include "Transform.h"
#include "Texture.h"
#include "Camera.h"
#include "CubeTex.h"
#include "Rigidbody.h"
#include "CameraMgr.h"

#include "Mesh.h"

#include "LightMgr.h"

#include "Root.h"
#include "Sequence.h"
#include "Selector.h"
#include "BlackBoard.h"
#include "Animation.h"
#include "PickingSphere.h"

#include "VortexParticle.h"
#include "NormalBulletParticle.h"
#include "UpSmokeParticle.h"
#include "JumpSmokeParticle.h"
#include "PyramidDestoryParticle.h"

#include "Scene.h"
#include "Layer.h"

BEGIN(Engine)

inline CGameObject*		Get_Player();
inline void				Set_Player(CGameObject* player);

inline CLayer*			Get_Layer(LAYERID LayerID);

inline HRESULT			Create_Management(CManagement** ppManagement);

inline void				Start_WorldTimer();
inline void				Stop_WorldTimer();
inline _float			Get_WorldTime();

inline CComponent*			Get_Component(LAYERID LayerID, const _tchar* pObjTag, const _tchar* pComponentTag, COMPONENTID eID);

inline void				Add_GameObject(class CGameObject* pObj);
inline CGameObject*		Get_GameObject(LAYERID LayerID, const _tchar* pObjTag);

//inline void				Set_StaticLayerArr(vector<CLayer*>* layerArr);

inline void				Remove_GameObject(LAYERID LayerID, CGameObject* obj);

inline HRESULT			Set_Scene(CScene* pScene, _bool bChangingStage = false);

inline _int			Update_Management(const _float& fTimeDelta);
inline void			LateUpdate_Management();
inline void			Render_Management(LPDIRECT3DDEVICE9 pGraphicDev);
inline void			Stop_SlowTime();
inline void			Reset_SlowTime(const _float & fTimeDelta);


inline HRESULT		Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);

inline CComponent*	Clone_Proto(const _tchar* pProtoTag, CGameObject* pGameObject);
// AI 클론용
inline CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, class CBlackBoard* pBlackBoard);

// Collider 클론용
inline CComponent*	Clone_Proto(const _tchar * pProtoTag, const _tchar* colliderName, class CGameObject* pGameObject, COLGROUP eColGroup, const _vec3& boundSize = { 2.f,2.f,2.f });

// Particle 클론용
inline CComponent*	Clone_Proto(const _tchar * pProtoTag, class CGameObject* pGameObject, const _int& particleNums, const _vec3& offset = { 0.f,0.f,0.f }, const _vec3& boundSize = { 2.f,2.f,2.f });


inline void		Add_RenderGroup(RENDERID eID, CGameObject* pGameObject);
inline void		Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void		Clear_RenderGroup(void);

inline void		Add_Collider(COLGROUP eID, CCollider * pCollider);
inline void		Add_Collider(CGameObject* gameObject);

inline void		Check_Collision(COLGROUP eGroup1, COLGROUP eGroup2);
inline void		Toggle_ColliderRender();
inline void		Change_ColGroup(CCollider* collider, COLGROUP changeID);
inline _bool	Collider_GetIsRender();
inline void		Remove_Collider(CCollider* collider, COLGROUP colID);
inline void		Remove_Collider(CGameObject* gameObject);
//inline void		Set_Collider(COLGROUP eGroup, CCollider* pCollider);
//
inline const	CCamera* Get_CurCamera();
inline void		On_Camera(const _tchar* pCamTag);
inline void		Shake_Camera(SHAKE_TYPE eType, const _float& fForce = 1.5f, const _float& fTime = 10.f);

inline HRESULT			Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev, const D3DLIGHT9* pLightInfo, const _uint& iIndex);
inline void						Release_Utility(void);


#include "Export_Utility.inl"

END