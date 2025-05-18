#include "stdafx.h"
#include "Tile.h"
#include "Player.h"
#include "Export_Function.h"

CTile::CTile(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	//, m_eTileType(TILE_DEFAULT)
{
	Set_LayerID(LAYER_TRIGGER);
}

CTile::~CTile()
{
}

HRESULT CTile::Ready_GameObject()
{
	HRESULT result = __super::Ready_GameObject();

	m_pTransform->m_vScale *= VTXITV * 0.5f;
	m_pTransform->Rot_Pitch(90.f, 1);
	m_pTransform->Set_MoveType(CTransform::AIRCRAFT);
	
	return result;
}

_int CTile::Update_GameObject(const _float & fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;
	__super::Update_GameObject(fTimeDelta);

	__super::Compute_ViewZ(&m_pTransform->m_vInfo[INFO_POS]);

	Engine::Add_RenderGroup(RENDER_NONALPHA, this);

	return OBJ_NOEVENT;
}

void CTile::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}

void CTile::Render_GameObject(void)
{
	/*m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);*/
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	__super::Render_GameObject();
}

void CTile::CalcColliderSize()
{
	// 타일 콜라이더 크기 조절 분기문(더러움주의)
	if (fabs(this->NormalVectorFromTile().Degree(_vec3::Up())) < 0.1f
		|| fabs(this->NormalVectorFromTile().Degree(-_vec3::Up())) < 0.1f)
		this->GetCollider()->Set_BoundingBox({ 10.f, 1.f, 10.f });
	else if (fabs(this->NormalVectorFromTile().Degree(_vec3::Right())) < 0.1f
		|| fabs(this->NormalVectorFromTile().Degree(-_vec3::Right())) < 0.1f)
		this->GetCollider()->Set_BoundingBox({ 1.f, 10.f, 10.f });
	else
		this->GetCollider()->Set_BoundingBox({ 10.f, 10.f, 1.f });
}

void CTile::OnCollisionStay(const Collision * collision)
{
	
}

_bool CTile::IsBodyCollider(const Collision *& collision)
{
	if (collision->OtherCollider == collision->OtherGameObject->Get_Component(L"BodyCollider", ID_ALL))
	{
		return true;
	}
	return false;
}

_vec3 CTile::NormalVectorFromTile()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Get_Component(L"RcTex", ID_RENDER));
	NULL_CHECK(pBufferCom);
	Triangle tri;

	VTXTEX*		pVertex = nullptr;
	pBufferCom->GetVertexBuffer()->Lock(0, 0, (void**)&pVertex, 0);

	tri.v[0] = pVertex[0].vPos;
	tri.v[1] = pVertex[1].vPos;
	tri.v[2] = pVertex[2].vPos;

	pBufferCom->GetVertexBuffer()->Unlock();

	tri.v[0].TransformCoord(&m_pTransform->m_matWorld);
	tri.v[1].TransformCoord(&m_pTransform->m_matWorld);
	tri.v[2].TransformCoord(&m_pTransform->m_matWorld);

	return tri.Normal();
}

HRESULT CTile::Add_Component()
{
	CRcTex* pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(pBufferCom, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", pBufferCom });

	m_pAnimation = dynamic_cast<CAnimation*>(Engine::Clone_Proto(L"Animation", this));
	NULL_CHECK_RETURN(m_pAnimation, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Animation", m_pAnimation });

	return S_OK;
}

void CTile::Free(void)
{
	__super::Free();
}

void CTile::Serialization(HANDLE hFile, DWORD & dwByte)
{
	_tchar tmp[32];

	lstrcpy(tmp, m_ObjInfo.pObjTag);
	WriteFile(hFile, tmp, sizeof(_tchar) * 32, &dwByte, nullptr);
	m_pTransform->WriteTransformFile(hFile, dwByte);
}

void CTile::Deserialization(HANDLE hFile, DWORD & dwByte)
{
	m_pTransform->ReadTransformFile(hFile, dwByte);
}

//HRESULT CTile::Remove_TextureCom()
//{
//	for (_uint i = 0; i < ID_END; ++i)
//	{
//		for (auto iter = m_uMapComponent[i].begin(); iter != m_uMapComponent[i].end(); ++iter)
//		{
//			//if (0 == lstrcmp(iter->first, m_pTextureName))
//			if (iter->first == m_pTextureName)
//			{
//				Remove_Render_Component(iter->first);
//				m_uMapComponent[i].erase(iter);
//				Safe_Release(m_pTextureCom);
//				m_pTextureName = L"";
//				return S_OK;
//			}
//		}
//	}
//	
//	return E_FAIL;
//}



