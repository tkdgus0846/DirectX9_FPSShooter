#pragma once
#include "GameObject.h"

// This struct that fills in information about something intersect with a ray
typedef struct tagClickInfo
{
	Triangle tri;			// Three vertices of a face
	INDEX32 index;			// Index of a vertex
	CGameObject* pGameObj;	// Address of an clicked object
	float fDist;			// Distance between a camera and an object
	_vec3 ClickedPos;		// Intersection position of a ray
}ClickInfo;

BEGIN(Engine)
class CCamera;
class CTexture;
END
class CImInspector;
class CRoom;

class CEditCamera : public CGameObject
{
private:
	explicit CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	virtual ~CEditCamera();

public:
	virtual HRESULT Ready_GameObject(void) override;
	virtual _int Update_GameObject(const _float& fTimeDelta) override;
	virtual void LateUpdate_GameObject(void) override;
	virtual void Render_GameObject(void) override;

private:
	virtual	HRESULT Add_Component() override;
	void	Key_Input(const _float& fTimeDelta);
	void	Mouse_Move(const _float& fTimeDelta);
	void	Fix_Mouse();

public:
	ClickInfo&	Get_ClickInfo() { return m_tPickInfo; }

	void CreateMonster(CImInspector * pWindow);
	void CreateTile(CImInspector * pWindow);
	void CreateWall(CImInspector * pWindow);
	void CreateMapObject(CImInspector * pWindow);
	void RotationY_Tile();
	void DeleteObject();

private:
	_bool SetClickInfo();
	// Functions that fill in mouse click information
	_bool IntersectRayRoom(const CRoom* pRoom, ClickInfo& tClickInfo);
	_bool IntersectRayGameObject(ClickInfo& tClickInfo);
	_bool Compute_RayCastHitGameObject(const Ray* pRay, ClickInfo& tClickInfo);
	Ray CalcRaycast(POINT ptMouse);
	POINT GetMousePos();

	_vec3 CalcMiddlePoint(Triangle& tri);

private:
	_float				m_fSpeed;
	_bool				m_bFix;
	ClickInfo			m_tPickInfo;

public:
	static CEditCamera*	Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};