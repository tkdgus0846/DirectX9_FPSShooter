#include "stdafx.h"
#include "RcTex.h"

CRcTex::CRcTex(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CRcTex::CRcTex(const CRcTex & rhs)
	: CVIBuffer(rhs)
{
	
}

CRcTex::~CRcTex()
{
}

HRESULT CRcTex::Ready_Buffer(VIBUFFER_FLAG bufferFlag)
{
	m_dwFVF = FVF_TEX;
	m_dwVtxSize = sizeof(VTXTEX);
	m_dwVtxCnt = 4;
	m_dwTriCnt = 2;

	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(__super::Ready_Buffer(bufferFlag), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.

	pVertex[0].vPos = { -1.f, 1.f, 0.f };
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPos = { 1.f, 1.f, 0.f };
	pVertex[1].vTexUV = { 1.f, 0.f };

	pVertex[2].vPos = { 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPos = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { 0.f, 1.f };

	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();

	return S_OK;
}

void CRcTex::Edit_VB(_float fX)
{
	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.


	pVertex[0].vPos = { -1.f, 1.f, 0.f };
	pVertex[0].vTexUV = { 0.f, 0.f };

	pVertex[1].vPos = { fX * 2.f - 1.f, 1.f, 0.f };
	pVertex[1].vTexUV = { fX, 0.f };

	pVertex[2].vPos = { fX * 2.f - 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { fX, 1.f };

	pVertex[3].vPos = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { 0.f, 1.f };

	m_pVB->Unlock();


	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();
}

void CRcTex::Edit_V(_float fY)
{
	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.


	pVertex[0].vPos = { -1.f, fY * 2.f - 1.f, 0.f };
	pVertex[0].vTexUV = { 0.f, fY };

	pVertex[1].vPos = { 1.f, fY * 2.f - 1.f, 0.f };
	pVertex[1].vTexUV = { 1.f, fY };

	pVertex[2].vPos = { 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { 1.f, 1.f };

	pVertex[3].vPos = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { 0.f, 1.f };
	//cout << pVertex[0].vTexUV.y << endl;
	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();
}

void CRcTex::Edit_U(_float fX)
{
	VTXTEX*		pVertex = nullptr;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);
	// 버텍스 버퍼 메모리 공간의 접근을 막는 행위, 3번 인자는 버텍스 버퍼에 저장된 버텍스들 중 첫 번째 버텍스의 주소를 반환한다.


	pVertex[0].vPos = { -1.f, 1.f, 0.f };
	pVertex[0].vTexUV = { fX -0.5f, 0.f };

	pVertex[1].vPos = { 1.f, 1.f, 0.f };
	pVertex[1].vTexUV = { fX, 0.f };

	pVertex[2].vPos = { 1.f, -1.f, 0.f };
	pVertex[2].vTexUV = { fX, 1.f };

	pVertex[3].vPos = { -1.f, -1.f, 0.f };
	pVertex[3].vTexUV = { fX - 0.5f, 1.f };

	m_pVB->Unlock();

	INDEX32*		pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	pIndex[0]._0 = 0;
	pIndex[0]._1 = 1;
	pIndex[0]._2 = 2;

	pIndex[1]._0 = 0;
	pIndex[1]._1 = 2;
	pIndex[1]._2 = 3;

	m_pIB->Unlock();
}

CRcTex * CRcTex::Create(LPDIRECT3DDEVICE9 pGraphicDev, VIBUFFER_FLAG bufferFlag)
{
	CRcTex *	pInstance = new CRcTex(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer(bufferFlag)))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}
CComponent * CRcTex::Clone(void)
{
	return new CRcTex(*this);
}

void CRcTex::Free(void)
{
	__super::Free();
}
