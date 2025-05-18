#include "EditCamera.h"
#include "Room.h"
#include "Wall.h"
#include "Tile.h"
#include "RoomMgr.h"
#include "Export_Function.h"
#include "RoomMgr.h"
#include "Floor.h"
#include "TileFactory.h"
#include "MonsterFactory.h"
#include "WallFactory.h"
#include "MapObjectFactory.h"
#include "ImManager.h"
#include "ImInspector.h"
#include "FileSystem.h"
#include "Creature.h"
#include "Tree.h"
#include "TallGrass.h"
#include "SnowTree.h"
#include "SnowSoTree.h"
#include "Slider.h"
#include "SnowMan.h"
#include "Cactus.h"
CEditCamera::CEditCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_fSpeed(0.f)
	, m_bFix(true)
{
	Set_LayerID(LAYER_CAMERA);
	Set_ObjTag(L"Edit_Camera");
	ZeroMemory(&m_tPickInfo, sizeof(ClickInfo));
}

CEditCamera::~CEditCamera()
{
}

HRESULT CEditCamera::Ready_GameObject(void)
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale = { 1.f, 1.f, 1.f };
	m_pTransform->m_vInfo[INFO_POS] = _vec3(15.f, 20.f, 30.f);
	m_pTransform->m_vInfo[INFO_LOOK] = { 0.f, 0.f, 1.f };
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);

	m_fSpeed = 20.f;

	return result;
}

_int CEditCamera::Update_GameObject(const _float & fTimeDelta)
{
	Key_Input(fTimeDelta);

	if (m_bFix)
	{
		Fix_Mouse();
		Mouse_Move(fTimeDelta);
	}

	__super::Update_GameObject(fTimeDelta);

	return OBJ_NOEVENT;
}

void CEditCamera::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CEditCamera::Render_GameObject(void)
{
}

void CEditCamera::CreateMapObject(CImInspector * pWindow)
{
	if (PICK_MAPOBJ != (PICK_TYPE)pWindow->Get_PickType())
		return;

	if (!dynamic_cast<CFloor*>(m_tPickInfo.pGameObj) 
		&& !dynamic_cast<CTile*>(m_tPickInfo.pGameObj))
		return;

	CGameObject* pObj = MAPOBJ_FACTORY->CreateObject(pWindow->Get_CurTag());
	if (!pObj)
		return;

	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);
	_vec3 vPos = CalcMiddlePoint(m_tPickInfo.tri);

	switch (pWindow->Get_Radio())
	{
	case 1:
		vPos.x -= (VTXCNTX - 1) * 0.5f;
		vPos.z += (VTXCNTZ - 1) * 0.5f;
		break;
	case 2:
		vPos.x += (VTXCNTX - 1) * 0.5f;
		vPos.z += (VTXCNTZ - 1) * 0.5f;
		break;
	case 3:
		vPos.x -= (VTXCNTX - 1) * 0.5f;
		vPos.z -= (VTXCNTZ - 1) * 0.5f;
		break;
	case 4:
		vPos.x += (VTXCNTX - 1) * 0.5f;
		vPos.z -= (VTXCNTZ - 1) * 0.5f;
		break;
	default:
		break;
	}

	if (dynamic_cast<CTree*>(pObj) || dynamic_cast<CTallGrass*>(pObj)
		|| dynamic_cast<CSnowSoTree*>(pObj) || dynamic_cast<CSlider*>(pObj)
		|| dynamic_cast<CSnowMan*>(pObj))
	{
		vPos.y += pObj->m_pTransform->Get_Scale().y;
	}
	else if (dynamic_cast<CSnowTree*>(pObj))
	{
		vPos.y += 4.f;
	}
	else if (dynamic_cast<Cactus*>(pObj))
	{
		vPos.y += 4.f;
	}
	

	pObj->m_pTransform->Set_Pos(vPos);
}

void CEditCamera::RotationY_Tile()
{
	CFloorTile* pFloorTile = dynamic_cast<CFloorTile*>(m_tPickInfo.pGameObj);

	if (!pFloorTile)
		return;
	
	pFloorTile->m_pTransform->Rot_Roll(90.f, 1.f);
}

HRESULT CEditCamera::Add_Component()
{
	CCamera* pCamera = dynamic_cast<CCamera*>(Engine::Clone_Proto(L"Camera", this));
	NULL_CHECK_RETURN(pCamera, E_FAIL);
	m_uMapComponent[ID_UPDATE].insert({ L"Edit_Camera", pCamera });
	pCamera->Set_CameraName(L"Edit_Camera");

	CCollider* pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"BodyCollider", this, COL_PLAYER));
	NULL_CHECK_RETURN(pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"BodyCollider", pCollider });
	pCollider->Set_BoundingBox({ 2.f,2.f,2.f });

	return S_OK;
}

void CEditCamera::Key_Input(const _float & fTimeDelta)
{
	if (Engine::Key_Pressing(DIK_W))	m_pTransform->Move_Walk(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_S))	m_pTransform->Move_Walk(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_A))	m_pTransform->Move_Strafe(-m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_D))	m_pTransform->Move_Strafe(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_Q))	m_pTransform->Move_Fly(m_fSpeed, fTimeDelta);
	if (Engine::Key_Pressing(DIK_E))	m_pTransform->Move_Fly(-m_fSpeed, fTimeDelta);

	if (Engine::Key_Down((DIK_C))) Engine::Toggle_ColliderRender();
	if (Engine::Key_Down(DIK_1)) m_bFix = !m_bFix;

	if (Engine::Mouse_Down(DIM_LB))
	{
		if (!SetClickInfo()) return;

		CImInspector* pWindow = dynamic_cast<CImInspector*>(CImManager::GetInstance()->FindByTag(L"Inspector"));
		CreateTile(pWindow);
		CreateWall(pWindow);
		CreateMonster(pWindow);
		CreateMapObject(pWindow);
	}

	if (Engine::Mouse_Down(DIM_RB))
	{
		if (!SetClickInfo()) return;
		DeleteObject();
	}

	if (Engine::Key_Down(DIK_R))
	{
		if (!SetClickInfo()) return;
		RotationY_Tile();
	}
}

void CEditCamera::Mouse_Move(const _float & fTimeDelta)
{
	_long dwMouseMove = 0;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_Y))
		m_pTransform->m_vInfo[INFO_LOOK] += _vec3(0.f, 1.f, 0.f) * _float(-dwMouseMove) * fTimeDelta / 10.f;

	if (dwMouseMove = Engine::Get_DIMouseMove(DIMS_X))
		m_pTransform->Rot_Yaw(_float(dwMouseMove) * 5.f, fTimeDelta);
}

void CEditCamera::Fix_Mouse()
{
	POINT ptMouse{ WINCX >> 1, WINCY >> 1 };

	ClientToScreen(g_hWnd, &ptMouse);
	SetCursorPos(ptMouse.x, ptMouse.y);
}

CEditCamera * CEditCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CEditCamera*		pInstance = new CEditCamera(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CEditCamera::Free()
{
	__super::Free();
}

_bool CEditCamera::Compute_RayCastHitGameObject(const Ray* pRay, ClickInfo& tClickInfo)
{
	CVIBuffer* pVIBuffer = tClickInfo.pGameObj->Get_VIBuffer();
	CTransform* pTransform = tClickInfo.pGameObj->m_pTransform;

	_matrix matWorld = *pTransform->Get_WorldMatrixPointer();

	if (!pVIBuffer)
		return false;

	_bool success = false;
	_float u, v;
	_vec3 ClickedPos;
	_float dist = FLT_MAX;
	_float distTemp = 0.f;
	VTXTEX* vertices = nullptr;
	INDEX32* indices = nullptr;
	_bool tempSuccess;
	Triangle	tmpTri;
	D3DVERTEXBUFFER_DESC vbDescription;
	D3DINDEXBUFFER_DESC inDescription;

	pVIBuffer->GetVertexBuffer()->GetDesc(&vbDescription);
	pVIBuffer->GetIndexBuffer()->GetDesc(&inDescription);

	pVIBuffer->GetVertexBuffer()->Lock(0, 0, (void**)&vertices, 0);
	pVIBuffer->GetIndexBuffer()->Lock(0, 0, (void**)&indices, 0);

	_ulong dwSize = inDescription.Size / sizeof(INDEX32);
	for (_ulong i = 0; i < dwSize; ++i)
	{
		tmpTri.v[0] = vertices[indices[i]._0].vPos;
		tmpTri.v[1] = vertices[indices[i]._1].vPos;
		tmpTri.v[2] = vertices[indices[i]._2].vPos;

		tmpTri.v[0].TransformCoord(&matWorld);
		tmpTri.v[1].TransformCoord(&matWorld);
		tmpTri.v[2].TransformCoord(&matWorld);

		tempSuccess = D3DXIntersectTri(&tmpTri.v[0]
			, &tmpTri.v[1]
			, &tmpTri.v[2]
			, (const D3DXVECTOR3*)(&pRay->vOrigin)
			, (const D3DXVECTOR3*)(&pRay->vDirection)
			, &u, &v, &distTemp);

		_float w = 1.0f - u - v;
		ClickedPos = w * tmpTri.v[0] + u * tmpTri.v[1] + v * tmpTri.v[2];

		if (tempSuccess && (dist > distTemp))
		{
			tClickInfo.fDist = dist = distTemp;
			success = tempSuccess;
			tClickInfo.tri = tmpTri;
			tClickInfo.index = indices[i];
			tClickInfo.ClickedPos = ClickedPos;

		}
	}

	pVIBuffer->GetVertexBuffer()->Unlock();
	pVIBuffer->GetIndexBuffer()->Unlock();

	return success;
}

_bool CEditCamera::SetClickInfo()
{
	_bool result = true;

	_matrix proj;
	proj.PerspectiveFovLH();
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &proj);

	CRoom* pRoom = ROOM_MGR->Get_CurRoom();
	// Variables for Output about InstersectRayRoom Method

	if (!IntersectRayRoom(pRoom, m_tPickInfo)) result = false;

	return result;	
}

_bool CEditCamera::IntersectRayRoom(const CRoom* pRoom, ClickInfo& tClickInfo)
{
	_bool success = false;
	ClickInfo TempClickInfo;
	float fMinDist = FLT_MAX;

	for (_int i = 0; i < pRoom->ObjNum(); ++i)
	{
		TempClickInfo.pGameObj = pRoom->GetObjByIndex(i);
		if (IntersectRayGameObject(TempClickInfo))
		{
			if (fMinDist > TempClickInfo.fDist)
			{
				fMinDist = TempClickInfo.fDist;
				tClickInfo = TempClickInfo;
			}
			success = true;
		}
	}

	return success;
}

_bool CEditCamera::IntersectRayGameObject(ClickInfo& tClickInfo)
{
	Ray ray = CalcRaycast(GetMousePos());
	_bool bSuccess = Compute_RayCastHitGameObject(&ray, tClickInfo);
	return bSuccess;
}

Ray CEditCamera::CalcRaycast(POINT ptMouse)
{
	float px = 0.f;
	float py = 0.f;

	D3DVIEWPORT9 vp;
	m_pGraphicDev->GetViewport(&vp);

	D3DXMATRIX proj;
	m_pGraphicDev->GetTransform(D3DTS_PROJECTION, &proj);

	px = (((2.f * ptMouse.x) / vp.Width) - 1.0f) / proj(0, 0);
	py = (((-2.f * ptMouse.y) / vp.Height) + 1.0f) / proj(1, 1);

	Ray ray;
	ray.vOrigin = D3DXVECTOR3(0.f, 0.f, 0.f);
	ray.vDirection = D3DXVECTOR3(px, py, 1.f);

	_matrix matView;
	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matView);
	D3DXMatrixInverse(&matView, 0, &matView);

	D3DXVec3TransformCoord(&ray.vOrigin, &ray.vOrigin, &matView);
	D3DXVec3TransformNormal(&ray.vDirection, &ray.vDirection, &matView);
	D3DXVec3Normalize(&ray.vDirection, &ray.vDirection);

	return ray;
}


POINT CEditCamera::GetMousePos()
{
	POINT ptMouse{};
	GetCursorPos(&ptMouse);
	ScreenToClient(g_hWnd, &ptMouse);

	return ptMouse;
}

_vec3 CEditCamera::CalcMiddlePoint(Triangle & tri)
{
	_vec3 standard;
	_vec3 a;
	_vec3 b;
	_vec3 A;
	_vec3 B;
	_vec3 result;
	standard = tri.v[0];
	a = tri.v[1];
	b = tri.v[2];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}

	standard = tri.v[1];
	a = tri.v[0];
	b = tri.v[2];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}


	standard = tri.v[2];
	a = tri.v[1];
	b = tri.v[0];
	A = a - standard;
	B = b - standard;

	if (fabs(A.Dot(B)) < 0.1f)
	{
		result = (a + b) / 2.f;
		return result;
	}

	return _vec3();
}


void CEditCamera::CreateMonster(CImInspector * pWindow)
{
	if (PICK_MONSTER != pWindow->Get_PickType())
		return;
	
	if (!dynamic_cast<CFloor*>(m_tPickInfo.pGameObj)
		&& !dynamic_cast<CTile*>(m_tPickInfo.pGameObj))
		return;

	CGameObject* pObj = MONSTER_FACTORY->CreateObject(pWindow->Get_CurTag());
	CCreature* creature = dynamic_cast<CCreature*>(pObj);

	if (creature != nullptr)
		creature->Set_Speed(0.f);
	if (!pObj)
		return;

	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);
	_vec3 vPos = m_tPickInfo.ClickedPos;
	vPos.y += 2.f;

	pObj->m_pTransform->Set_Pos(vPos);
}

void CEditCamera::CreateTile(CImInspector * pWindow)
{
	if (PICK_TILE != pWindow->Get_PickType())
		return;

	if (!dynamic_cast<CFloor*>(m_tPickInfo.pGameObj))
		return;

	// IMGUI 콤보박스 정보 가져옴.
	CImInspector* pInspector = static_cast<CImInspector*>(IM_MGR->FindByTag(L"Inspector"));
	//wstring CurTileItem = TO_WSTR(pInspector->Get_CurTileItem());
	
	// 타일 생성
	CTile* pObj = dynamic_cast<CTile*>(TILE_FACTORY->CreateObject(pWindow->Get_CurTag()));
	if (!pObj) return;
	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);
	
	// 타일 위치 정해주기.
	_vec3 vPos = CalcMiddlePoint(m_tPickInfo.tri);
	
	vPos.y += 0.01f;

	pObj->m_pTransform->Set_Pos(vPos);
}

void CEditCamera::CreateWall(CImInspector * pWindow)
{
	if (PICK_WALL != pWindow->Get_PickType())
		return;

	if (!dynamic_cast<CWall*>(m_tPickInfo.pGameObj))
		return;

	// IMGUI 콤보박스 정보 가져옴.
	CImInspector* pInspector = static_cast<CImInspector*>(IM_MGR->FindByTag(L"Inspector"));
	//wstring CurTileItem = TO_WSTR(pInspector->Get_CurTileItem());

	// 타일 생성
	CTile* pObj = dynamic_cast<CTile*>(WALL_FACTORY->CreateObject(pWindow->Get_CurTag()));
	if (!pObj) return;
	ROOM_MGR->Get_CurRoom()->PushBack_GameObj(pObj);

	// 타일 위치 정해주기.
	_vec3 vPos = CalcMiddlePoint(m_tPickInfo.tri);

	pObj->m_pTransform->m_vInfo[INFO_RIGHT] = m_tPickInfo.pGameObj->m_pTransform->m_vInfo[INFO_RIGHT];
	pObj->m_pTransform->m_vInfo[INFO_LOOK] = m_tPickInfo.pGameObj->m_pTransform->m_vInfo[INFO_LOOK];
	pObj->m_pTransform->m_vInfo[INFO_UP] = m_tPickInfo.pGameObj->m_pTransform->m_vInfo[INFO_UP];
	vPos += pObj->m_pTransform->m_vInfo[INFO_LOOK] * 0.01f;


	pObj->m_pTransform->Set_Pos(vPos);
}

void CEditCamera::DeleteObject()
{
	if (dynamic_cast<CFloor*>(m_tPickInfo.pGameObj))
		return;

	if (dynamic_cast<CWall*>(m_tPickInfo.pGameObj))
		return;

	m_tPickInfo.pGameObj->SetDead();
	ROOM_MGR->Get_CurRoom()->EraseGameObject(m_tPickInfo.pGameObj);
	m_tPickInfo.pGameObj = nullptr;
}