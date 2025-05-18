#include "stdafx.h"
#include "ColorParticle.h"
#include "GameObject.h"
#include "Transform.h"
#include "Export_Function.h"


CColorParticle::CColorParticle(LPDIRECT3DDEVICE9 pGraphicDev) :
	CParticleSystem(pGraphicDev)
{
}

CColorParticle::CColorParticle(const CColorParticle & rhs) :
	CParticleSystem(rhs)
{
}

CColorParticle::~CColorParticle()
{
}

HRESULT CColorParticle::Ready_Particle(void)
{
	FAILED_CHECK_RETURN
	(
		m_pGraphicDev->CreateVertexBuffer(
			m_VBSize * sizeof(PTCCOL),
			D3DUSAGE_DYNAMIC | D3DUSAGE_POINTS | D3DUSAGE_WRITEONLY,
			FVF_COL,
			D3DPOOL_DEFAULT,
			&m_VB,
			0),
		E_FAIL
	);

	return S_OK;
}

void CColorParticle::Render_Particle(void)
{
	if (!m_Particles.empty())
	{
		
		PreRender();
		
		m_pGraphicDev->SetTexture(0, nullptr);
		m_pGraphicDev->SetFVF(FVF_COL);
		m_pGraphicDev->SetStreamSource(0, m_VB, 0, sizeof(PTCCOL));

		if (m_VBOffset >= m_VBSize)
			m_VBOffset = 0;

		PTCCOL* v = 0;

		m_VB->Lock(
			m_VBOffset * sizeof(PTCCOL),
			m_VBBatchSize * sizeof(PTCCOL),
			(void**)&v,
			m_VBOffset ? D3DLOCK_NOOVERWRITE : D3DLOCK_DISCARD);

		DWORD numParticlesInBatch = 0;

		list<Particle>::iterator it;
		for (it = m_Particles.begin(); it != m_Particles.end(); it++)
		{
			if (it->bIsAlive)
			{
				v->vPos = it->vPos;
				v->dwColor = it->dwColor;
				
				
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
						m_VBOffset * sizeof(PTCCOL),
						m_VBBatchSize * sizeof(PTCCOL),
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
