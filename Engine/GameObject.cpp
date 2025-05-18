#include "GameObject.h"
#include "GameObject.h"
#include "stdafx.h"

#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"

// 테스트용 주석

// 여기는 안보셔도 됩니다. 굳이 안봐도 돼요.
bool Compare_Component_Priority(pair<const _tchar*, CComponent*>& a, pair<const _tchar*, CComponent*>& b)
{
	return a.second->m_RenderOrder < b.second->m_RenderOrder; // Value로 정렬
}


CGameObject::CGameObject(LPDIRECT3DDEVICE9 pGraphicDev) : 
	m_pGraphicDev(pGraphicDev),
	m_fViewZ(0.f),
	m_bDead(FALSE),
	m_pOwnerObject(nullptr),
	m_bReleaseFlag(TRUE)
{
	m_pGraphicDev->AddRef();

	m_pTransform = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Transform", this));
	m_uMapComponent[ID_UPDATE].insert({ L"Transform", m_pTransform });
}

CGameObject::~CGameObject()
{
}

CComponent * CGameObject::Get_Component(const _tchar * pComponentTag, COMPONENTID eID)
{
	CComponent*		pComponent = Find_Component(pComponentTag, eID);
	//NULL_CHECK_RETURN(pComponent, nullptr);

	return pComponent;
}

CVIBuffer* CGameObject::Get_VIBuffer()
{
	CVIBuffer* pBuffer = nullptr;
	for (_ulong i = 0; i < ID_END; ++i)
	{
		for (auto& Component : m_uMapComponent[i])
		{
			if (pBuffer = dynamic_cast<CVIBuffer*>(Component.second))
				return pBuffer;
		}
	}
	return nullptr;
}

CTexture * CGameObject::Get_Texture()
{
	CTexture* pTexture = nullptr;
	for (_ulong i = 0; i < ID_END; ++i)
	{
		for (auto& Component : m_uMapComponent[i])
		{
			if (pTexture = dynamic_cast<CTexture*>(Component.second))
			{
				return pTexture;
			}
				
		}
	}
	return pTexture;
}

wstring CGameObject::Get_TextureKey()
{
	CTexture* pTexture = nullptr;
	for (_ulong i = 0; i < ID_END; ++i)
	{
		for (auto& Component : m_uMapComponent[i])
		{
			if (pTexture = dynamic_cast<CTexture*>(Component.second))
			{
				return Component.first;
			}
		}
	}

	// 텍스처 키를 추출하지 못하면 오류 뜸.
	return nullptr;
}

void CGameObject::Remove_Texture(const _tchar * name, COMPONENTID componentID)
{
	Safe_Release(m_uMapComponent[componentID][name]);
}

void CGameObject::Change_Texture(const _tchar * beforeName, const _tchar * afterName, COMPONENTID componentID)
{
	Remove_Texture(beforeName, componentID);

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(afterName, this));
	NULL_CHECK(texture);
	m_uMapComponent[componentID][beforeName] = texture;

	// 여기 아래 부분은 굳이 안봐도 됩니다.
	vector <pair<const _tchar*, CComponent*>> VecRender(m_uMapComponent[ID_RENDER].begin(), m_uMapComponent[ID_RENDER].end());
	vector <pair<const _tchar*, CComponent*>> VecAll(m_uMapComponent[ID_ALL].begin(), m_uMapComponent[ID_ALL].end());

	vector <pair<const _tchar*, CComponent*>> sortVec;

	sortVec.insert(sortVec.begin(), VecRender.begin(), VecRender.end());
	sortVec.insert(sortVec.end(), VecAll.begin(), VecAll.end());

	sort(sortVec.begin(), sortVec.end(), Compare_Component_Priority);

	// 렌더 우선순위를 통해서 렌더될 순서를 정해준다음에 벡터에 넣어주는거,
	// 그러니까 별개임
	m_RenderComponent = sortVec;

}

HRESULT CGameObject::Ready_GameObject(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	// 여기 아래 부분은 굳이 안봐도 됩니다.
	vector <pair<const _tchar*, CComponent*>> VecRender(m_uMapComponent[ID_RENDER].begin(), m_uMapComponent[ID_RENDER].end());
	vector <pair<const _tchar*, CComponent*>> VecAll(m_uMapComponent[ID_ALL].begin(), m_uMapComponent[ID_ALL].end());

	vector <pair<const _tchar*, CComponent*>> sortVec;

	sortVec.insert(sortVec.begin(), VecRender.begin(), VecRender.end());
	sortVec.insert(sortVec.end(), VecAll.begin(), VecAll.end());

	sort(sortVec.begin(), sortVec.end(), Compare_Component_Priority);

	// 렌더 우선순위를 통해서 렌더될 순서를 정해준다음에 벡터에 넣어주는거,
	// 그러니까 별개임
	m_RenderComponent = sortVec;

	return S_OK;
}

_int CGameObject::Update_GameObject(const _float & fTimeDelta)
{
	for (auto iter = m_StaticObjectList.begin(); iter != m_StaticObjectList.end();)
	{
		_int result = (*iter)->Update_GameObject(fTimeDelta);

		if (result == OBJ_DEAD)
		{
			Engine::Remove_Collider(*iter);
			Safe_Release(*iter);
			iter = m_StaticObjectList.erase(iter);
		}
		else
			iter++;
	}

	for (auto& iter : m_uMapComponent[ID_UPDATE])
		iter.second->Update_Component(fTimeDelta);

	for (auto& iter : m_uMapComponent[ID_ALL])
		iter.second->Update_Component(fTimeDelta);

	return 0;
}

void CGameObject::LateUpdate_GameObject(void)
{
	for (auto iter = m_StaticObjectList.begin(); iter != m_StaticObjectList.end(); ++iter)
	{
		(*iter)->LateUpdate_GameObject();
	}

	for (auto& iter : m_uMapComponent[ID_UPDATE])
		iter.second->LateUpdate_Component();

	for (auto& iter : m_uMapComponent[ID_ALL])
		iter.second->LateUpdate_Component();
}

void CGameObject::Render_GameObject(void)
{
	/*for (auto iter = m_StaticObjectList.begin(); iter != m_StaticObjectList.end(); ++iter)
	{
		(*iter)->Render_GameObject();
	}*/

	for (auto& iter : m_RenderComponent)
		iter.second->Render_Component();

	m_pGraphicDev->SetTexture(0, nullptr);
}

void CGameObject::Compute_ViewZ(const _vec3 * pPos)
{
	_matrix		matCamWorld;

	m_pGraphicDev->GetTransform(D3DTS_VIEW, &matCamWorld);
	D3DXMatrixInverse(&matCamWorld, 0, &matCamWorld);
	
	_vec3	vCamPos;
	memcpy(&vCamPos, &matCamWorld.m[3][0], sizeof(_vec3));

	m_fViewZ = D3DXVec3Length(&(vCamPos - *pPos));
}

void CGameObject::Set_Pos(const _vec3 & pos)
{
	m_pTransform->Set_Pos(pos.x, pos.y, pos.z);
}

void CGameObject::Set_Dir(const _vec3 & dir)
{
	m_pTransform->Set_Dir(dir);
}

void CGameObject::Add_Colldier_Info(const _tchar * colName, COLGROUP colGroup)
{
	m_ObjInfo.colNameVec.push_back(colName);
	m_ObjInfo.colGroupVec.push_back(colGroup);
}

void CGameObject::Set_LayerID(LAYERID layerID)
{
	m_ObjInfo.layerID = layerID;
}

void Engine::CGameObject::Set_ObjTag(const _tchar* pObjTag)
{
	m_ObjInfo.pObjTag = pObjTag;
}

//void CGameObject::Remove_Render_Component(const _tchar * pComponentTag)
//{
//	for (auto iter = m_RenderComponent.begin(); iter != m_RenderComponent.end(); ++iter)
//	{
//		if (0 == lstrcmp(pComponentTag, iter->first))
//		{
//			m_RenderComponent.erase(iter);
//			return;
//		}
//	}
//}

void CGameObject::Add_Render_Component()
{
	vector <pair<const _tchar*, CComponent*>> VecRender(m_uMapComponent[ID_RENDER].begin(), m_uMapComponent[ID_RENDER].end());
	vector <pair<const _tchar*, CComponent*>> VecAll(m_uMapComponent[ID_ALL].begin(), m_uMapComponent[ID_ALL].end());

	vector <pair<const _tchar*, CComponent*>> sortVec;

	sortVec.insert(sortVec.begin(), VecRender.begin(), VecRender.end());
	sortVec.insert(sortVec.end(), VecAll.begin(), VecAll.end());

	sort(sortVec.begin(), sortVec.end(), Compare_Component_Priority);

	m_RenderComponent = sortVec;
}

// 죽었을때 자식 리스트에서 빼주기위한 함수
void CGameObject::Remove_InOwnerObject()
{
	if (m_pOwnerObject == nullptr) return;
	
	for (auto& it = m_pOwnerObject->m_StaticObjectList.begin(); it != m_pOwnerObject->m_StaticObjectList.end(); it++)
	{
		if ((*it) == this)
		{
			m_pOwnerObject->m_StaticObjectList.erase(it);
			break;
		}
	}
}

void CGameObject::Set_Flag(_bool state /*= FALSE*/)
{
	m_bReleaseFlag = state;
	for (auto child : m_StaticObjectList)
	{
		child->Set_Flag();
	}
}

CComponent * CGameObject::Find_Component(const _tchar * pComponentTag, COMPONENTID eID)
{
	auto	iter = find_if(m_uMapComponent[eID].begin(), m_uMapComponent[eID].end(), CTag_Finder(pComponentTag));

	if (iter == m_uMapComponent[eID].end())
		return nullptr;

	return iter->second;
}


void CGameObject::Free(void)
{

	/*if (m_bReleaseFlag == true)
		Engine::Remove_Collider(this);*/

	for (auto it = m_StaticObjectList.begin(); it != m_StaticObjectList.end(); it++)
	{
		if (m_bReleaseFlag == true)
			Engine::Remove_Collider(*it); // 자식오브젝트가 있는 경우에 콜리젼 매니저에서 내 콜라이더를 제거
		Safe_Release(*it);
	}
	
	for (size_t i = 0; i < ID_END; ++i)
	{
		for (auto iter = m_uMapComponent[i].begin(); iter != m_uMapComponent[i].end(); iter++)
		{
			Safe_Release((iter->second));
		}	
	}

	Safe_Release(m_pGraphicDev);
}
