#include "FloorTile.h"
#include "Export_Function.h"
#include "RoomMgr.h"


CFloorTile::CFloorTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CTile(pGraphicDev)
{
}

CFloorTile::~CFloorTile()
{
}

Vertex4 CFloorTile::Get_PlaneXZ()
{
	Vertex4 tmp;
	_vec3 vPos = m_pTransform->m_vInfo[INFO_POS];
	_float fRadius = VTXITV;

	tmp._v1.y = vPos.y;
	tmp._v2.y = vPos.y;
	tmp._v3.y = vPos.y;
	tmp._v4.y = vPos.y;

	tmp._v1.x = vPos.x - (fRadius * 0.5f);
	tmp._v3.x = vPos.x - (fRadius * 0.5f);
	tmp._v2.x = vPos.x + (fRadius * 0.5f);
	tmp._v4.x = vPos.x + (fRadius * 0.5f);

	tmp._v1.z = vPos.z + (fRadius * 0.5f);
	tmp._v3.z = vPos.z - (fRadius * 0.5f);
	tmp._v2.z = vPos.z + (fRadius * 0.5f);
	tmp._v4.z = vPos.z - (fRadius * 0.5f);

	return tmp;
}

_bool CFloorTile::IntersectPoint(const _vec3* vPoint)
{
	Vertex4 Plane = Get_PlaneXZ();
	return (Plane._v1.x <= vPoint->x
		&& vPoint->x <= Plane._v2.x
		&& Plane._v3.z <= vPoint->z
		&& Plane._v1.z >= vPoint->z) ? true : false;
}



_int CFloorTile::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);
	Set_Trigger(false);
	//__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	/*Engine::Add_RenderGroup(RENDER_NONALPHA, this);*/

	return OBJ_NOEVENT;
}

void CFloorTile::InteractGameObject(const InteractInfo* tInteractInfo)
{
}

void CFloorTile::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);

	if (GetDead())
	{
		_vec3 pos = m_pTransform->m_vInfo[INFO_POS];

		_int x = round(pos.x);
		_int z = round(pos.z);

		x %= (VTXCNTX - 1) * VTXITV;
		z %= (VTXCNTZ - 1) * VTXITV;
		x /= VTXITV;
		z /= VTXITV;

		ROOM_MGR->Get_CurRoom()->SetNullFloorTile(x, z);
	}
}
