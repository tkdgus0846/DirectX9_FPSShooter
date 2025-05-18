#include "stdafx.h"
#include "Mesh.h"

CMesh::CMesh(LPDIRECT3DDEVICE9 pGraphicDev) : 
	CComponent(pGraphicDev),
	m_pMesh(nullptr)
{
}

CMesh::CMesh(const CMesh & rhs) :
	CComponent(rhs),
	m_pMesh(rhs.m_pMesh),
	m_Mtrls(rhs.m_Mtrls),
	m_Textures(rhs.m_Textures)
{
}

CMesh::~CMesh()
{
}

HRESULT CMesh::Ready_Mesh(const _tchar * pPath)
{
	HRESULT hr = 0;

	ID3DXBuffer* adjBuffer = 0;
	ID3DXBuffer* mtrlBuffer = 0;
	DWORD        numMtrls = 0;

	if (FAILED(D3DXLoadMeshFromX(pPath, D3DXMESH_MANAGED, m_pGraphicDev,
		&adjBuffer, &mtrlBuffer, 0, &numMtrls, &m_pMesh)))
		return E_FAIL;

	if (mtrlBuffer != 0 && numMtrls != 0)
	{
		D3DXMATERIAL* mtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
		
		for (int i = 0; i < numMtrls; i++)
		{
			//MatD3D 속성은 ambient 값을 가지지 않으므로 지금 이를 저장한다.
			mtrls[i].MatD3D.Ambient = mtrls[i].MatD3D.Diffuse;
			m_Mtrls.push_back(mtrls[i].MatD3D);

			if (mtrls[i].pTextureFilename != 0)
			{
				IDirect3DTexture9* tex = 0;
				D3DXCreateTextureFromFileA(m_pGraphicDev,
					mtrls[i].pTextureFilename, &tex);

				m_Textures.push_back(tex);
			}
			else
				m_Textures.push_back(0);
		}
	}

	Safe_Release(mtrlBuffer);

	// Optimize the mesh.
	hr = m_pMesh->OptimizeInplace(
		D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_COMPACT | D3DXMESHOPT_VERTEXCACHE,
		(DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0);

	Safe_Release(adjBuffer);

	if (FAILED(hr))
		return E_FAIL;

	if (!(m_pMesh->GetFVF() & D3DFVF_NORMAL))
	{
		ID3DXMesh* pTempMesh = nullptr;

		m_pMesh->CloneMeshFVF(
			D3DXMESH_MANAGED,
			m_pMesh->GetFVF() | D3DFVF_NORMAL,
			m_pGraphicDev,
			&pTempMesh);

		D3DXComputeNormals(pTempMesh, nullptr);

		Safe_Release(m_pMesh);
		m_pMesh = pTempMesh;
	}

	return S_OK;
}

void Engine::CMesh::Render_Component()
{
	for (int i = 0; i < m_Mtrls.size(); i++)
	{
		m_pGraphicDev->SetMaterial(&m_Mtrls[i]);
		m_pGraphicDev->SetTexture(0, m_Textures[i]);
		m_pMesh->DrawSubset(i);
	}
}

void Engine::CMesh::Free(void)
{
	Safe_Release(m_pMesh);
	m_Mtrls.clear();
	//for_each(m_Textures.begin(), m_Textures.end(), CDeleteObj());
	m_Textures.clear();

	__super::Free();
}

CMesh * CMesh::Create(LPDIRECT3DDEVICE9 pGraphicDev, const _tchar * pPath)
{
	CMesh *	pInstance = new	CMesh(pGraphicDev);

	if (FAILED(pInstance->Ready_Mesh(pPath)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent * CMesh::Clone(void)
{
	return new CMesh(*this);
}




