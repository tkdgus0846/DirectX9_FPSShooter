#include "stdafx.h"
#include "TextureParticle.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"


CTextureParticle::CTextureParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CParticleSystem(pGraphicDev)	
{
}

CTextureParticle::CTextureParticle(const CTextureParticle & rhs) :
	CParticleSystem(rhs)
{
}

CTextureParticle::~CTextureParticle()
{
}

HRESULT CTextureParticle::Ready_Particle(void)
{
	FAILED_CHECK_RETURN
	(
		m_pGraphicDev->CreateVertexBuffer(
			m_VBSize * sizeof(PTCTEX),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_COL,
			D3DPOOL_DEFAULT,
			&m_VB,
			0),
		E_FAIL
	);

	return S_OK;
}

void CTextureParticle::Render_Particle(void)
{
	if (!m_Particles.empty())
	{
		
		PreRender();
		m_Texture->Render_Texture_Num();
		
		
		m_pGraphicDev->SetFVF(FVF_TEX);
		m_pGraphicDev->SetStreamSource(0, m_VB, 0, sizeof(PTCTEX));

		if (m_VBOffset >= m_VBSize)
			m_VBOffset = 0;

		PTCTEX* v = 0;

		m_VB->Lock(
			m_VBOffset * sizeof(PTCTEX),
			m_VBBatchSize * sizeof(PTCTEX),
			(void**)&v,
			m_VBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		list<Particle>::iterator it;
		for (it = m_Particles.begin(); it != m_Particles.end(); it++)
		{
			if (it->bIsAlive)
			{
				v->vPos = it->vPos;
				v->vTexUV = it->vTexUV;
				//v->dwColor = it->dwColor;
				
				
				v++;
				numParticlesInBatch++;

				if (numParticlesInBatch == m_VBBatchSize)
				{
					m_VB->Unlock();

					
					m_pGraphicDev->DrawPrimitive(
						D3DPT_POINTLIST,
						m_VBOffset,
						m_VBBatchSize);
					m_VBOffset += m_VBBatchSize;

					if (m_VBOffset >= m_VBSize)
						m_VBOffset = 0;

					m_VB->Lock(
						m_VBOffset * sizeof(PTCTEX),
						m_VBBatchSize * sizeof(PTCTEX),
						(void**)&v,
						m_VBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);
					numParticlesInBatch = 0;
				}
			}
		}


		m_VB->Unlock();

		if (numParticlesInBatch)
		{
			
			m_pGraphicDev->DrawPrimitive(
				D3DPT_POINTLIST,
				m_VBOffset,
				numParticlesInBatch);
		}

		m_VBOffset += m_VBBatchSize;

		PostRender();
	}

}

void CTextureParticle::Free(void)
{
	Safe_Release(m_Texture);
	__super::Free();
}
