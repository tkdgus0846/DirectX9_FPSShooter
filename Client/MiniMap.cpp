#include "MiniMap.h"
#include "Export_Function.h"
#include "RoomMgr.h"
CMiniMap::CMiniMap(LPDIRECT3DDEVICE9 pGraphicDev)
	: CUI(pGraphicDev)
{
	Set_ObjTag(L"MiniMap");
}

CMiniMap::~CMiniMap()
{
}

HRESULT CMiniMap::Add_Component()
{
	m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex_Dynamic", this));
	NULL_CHECK_RETURN(m_pBufferCom, E_FAIL);

	m_pRcTex = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"RcTex", this));
	NULL_CHECK_RETURN(m_pRcTex, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"RcTex", m_pRcTex });

	CTexture* Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MiniMap_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_uMapComponent[ID_RENDER].insert({ L"MiniMap_Texture", Texture });

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"MapPos_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[MINIMAPPOS] = Texture;

	Texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"ESWN_Texture", this));
	NULL_CHECK_RETURN(Texture, E_FAIL);
	m_arrMap[MINIMAPESWN] = Texture;

	return S_OK;
}

HRESULT CMiniMap::Ready_GameObject(void)
{
	__super::Ready_GameObject();

	return S_OK;
}

_int CMiniMap::Update_GameObject(const _float & fTimeDelta)
{
	Engine::Add_RenderGroup(RENDER_AFTER_ALPHA_UI, this);
	
	__super::Update_GameObject(fTimeDelta);

	return 0;
}

void CMiniMap::LateUpdate_GameObject(void)
{
	__super::LateUpdate_GameObject();
}


void CMiniMap::Render_GameObject(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransform->Get_WorldMatrixPointer());
	for (size_t i = 0; i < MINIMAPEND; i++)
	{
		if (m_arrMap[i] != nullptr)
		{
			switch (i)
			{
			case MINIMAPESWN: {
				ESWN();
				dynamic_cast<CTexture*>(m_arrMap[i])->Render_Texture();
				m_pBufferCom->Render_Component();
				m_pBufferCom->Edit_U(1.f);
				continue;
			}
			case MINIMAPPOS:
				Set_ViewMatrix_UI(320.f, -210.f, 16.f, 16.f, m_PlayerAngle);
				break;
			case MINIMAPBLANKBLACK:
				Set_ViewMatrix_UI();
				break;
			case MINIMAPBLANKGRAY:
				Set_ViewMatrix_UI();
				break;
			}
			dynamic_cast<CTexture*>(m_arrMap[i])->Render_Texture();
			m_pRcTex->Render_Component();
		}
	}

	Set_ViewMatrix_UI();
	__super::Render_GameObject();
}

void CMiniMap::Set_ViewMatrix_UI()
{
	D3DXMatrixIdentity(&matWorld);
	_matrix transmatrix;
	transmatrix.Translation(0.f, 0.f, 1.f);
	matWorld = transmatrix;

	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, 76.f, 92.f, 0.f);
	matTrans.Translation(320.f, -200.f, 1.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CMiniMap::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix matTrans;
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);
	matTrans.Translation(posX, posY, 0.f);
	D3DXMatrixMultiply(&matView, &matView, &matTrans);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CMiniMap::Set_ViewMatrix_UI(_float posX, _float posY, _float scaleX, _float scaleY, _float fAngle)
{
	D3DXMatrixIdentity(&matWorld);
	D3DXMatrixIdentity(&matView);

	_matrix pPlayerWorld = *Engine::Get_Player()->m_pTransform->Get_WorldMatrixPointer();
	D3DXMatrixScaling(&matView, scaleX, scaleY, 0.f);

	_vec3 vecRot;
	D3DXVec3TransformNormal(&vecRot, &vecRot, &pPlayerWorld);
	if (ROOM_MGR->Is_In_Tennel())
	{
		_matrix matRot, matTrans;
		matRot.RotationZ(m_PlayerTunnelAngle);
		matTrans.Translation(posX, posY, 0.f);
		D3DXMatrixMultiply(&matView, &matView, &matRot);
		D3DXMatrixMultiply(&matView, &matView, &matTrans);
	}
	else
	{
		_float fAngleZ = -atan2f(vecRot.x, vecRot.z) + D3DXToRadian(-135.f);
		m_PlayerTunnelAngle = fAngleZ;
		_matrix matRot, matTrans;
		matRot.RotationZ(fAngleZ);
		matTrans.Translation(posX, posY, 0.f);
		D3DXMatrixMultiply(&matView, &matView, &matRot);
		D3DXMatrixMultiply(&matView, &matView, &matTrans);
	}

	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pGraphicDev->SetTransform(D3DTS_VIEW, &matView);
}

void CMiniMap::ESWN()
{
	_matrix pPlayerWorld = *Engine::Get_Player()->m_pTransform->Get_WorldMatrixPointer();
	_vec3 vecRot;
	D3DXVec3TransformNormal(&vecRot, &vecRot, &pPlayerWorld);

	if (ROOM_MGR->Is_In_Tennel())
	{
		m_pBufferCom->Edit_U(-m_ESWNAngle);
	}
	else
	{
		_float fAngleZ = -atan2f(vecRot.x, vecRot.z) / 6.7f + D3DXToRadian(-27.f);;
		//_float fAngleZ = -atan2f(vecRot.x, vecRot.z) + D3DXToRadian(-27.f);;
		m_ESWNAngle = fAngleZ;
		m_pBufferCom->Edit_U(-fAngleZ);
	}

	Set_ViewMatrix_UI(320.f, -130.f, 76.f, 10.f);
}

CMiniMap * CMiniMap::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CMiniMap* pInstance = new CMiniMap(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CMiniMap::Free(void)
{
	Safe_Release(m_pRcTex);
	Safe_Release(m_pBufferCom);

	auto iter = m_arrMap.begin();
	for (; iter < m_arrMap.end(); iter++)
	{
		Safe_Release(*iter);
	}
	__super::Free();
}