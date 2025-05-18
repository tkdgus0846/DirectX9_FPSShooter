#include "stdafx.h"
#include "Animation.h"
#include "Texture.h"



CAnimation::CAnimation(LPDIRECT3DDEVICE9 pGraphicDev) :
	CComponent(pGraphicDev),
	m_CurFrame(nullptr),
	m_ePrevState(ANIM_END),
	m_eCurState(ANIM_END)
{
}

CAnimation::CAnimation(const CAnimation & rhs) :
	CComponent(rhs),
	m_CurFrame(rhs.m_CurFrame),
	m_ePrevState(rhs.m_ePrevState),
	m_eCurState(rhs.m_eCurState)
{
	m_RenderOrder = 2;
	m_bFinished = FALSE;
	m_bInversed = FALSE;
	m_bPlaying = TRUE;
}

CAnimation::~CAnimation()
{
}

HRESULT CAnimation::Ready_Animation()
{
	return S_OK;
}

_int CAnimation::Update_Component(const _float& fTimeDelta)
{
	if (m_CurFrame == nullptr) return OBJ_NOEVENT;
	if (m_bPlaying == FALSE) return 0;

	m_CurFrame->fAccTime += fTimeDelta;

	if (m_bInversed == FALSE)
	{
		if (m_CurFrame->fFrameSpeed <= m_CurFrame->fAccTime)
		{
			m_CurFrame->iFrame++;
			m_CurFrame->fAccTime = 0.f;

			if (m_CurFrame->iMaxFrame <= m_CurFrame->iFrame)
			{
				if (m_CurFrame->bRepeat == TRUE)
					m_CurFrame->iFrame = 0;
				else
				{
					m_CurFrame->iFrame = m_CurFrame->iMaxFrame - 1;
					m_bFinished = TRUE;
				}

			}
		}
	}
	else
	{
		if (m_CurFrame->fFrameSpeed <= m_CurFrame->fAccTime)
		{
			if (m_CurFrame->iFrame >= 1)
				m_CurFrame->iFrame--;
			m_CurFrame->fAccTime = 0.f;

			if (0 >= m_CurFrame->iFrame)
			{
				if (m_CurFrame->bRepeat == TRUE)
					m_CurFrame->iFrame = m_CurFrame->iMaxFrame - 1;
				else
				{
					m_CurFrame->iFrame = 0;
					m_bFinished = TRUE;
				}
			}
		}
	}

	return OBJ_NOEVENT;
}

void CAnimation::LateUpdate_Component()
{

}

void CAnimation::Render_Component()
{
	if (m_CurFrame == nullptr) return;

	m_CurFrame->pTexture->Render_Texture(m_CurFrame->iFrame);
}

CAnimation* CAnimation::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CAnimation* pInstance = new CAnimation(pGraphicDev);

	if (FAILED(pInstance->Ready_Animation()))
	{
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

CComponent* CAnimation::Clone(void)
{
	return new CAnimation(*this);
}

void CAnimation::Free(void)
{
	Safe_Delete(m_CurFrame);
	__super::Free();
}

void CAnimation::SelectState(ANIMSTATE state)
{
	if (m_CurFrame == nullptr) m_CurFrame = new AnimFrame();
	if (m_ePrevState == state) return;

	auto iter = m_MapAnimation.find(state);
	if (iter == m_MapAnimation.end()) return;

	m_ePrevState = state;
	m_eCurState = state;


	*m_CurFrame = (m_MapAnimation[m_eCurState]);
}

void CAnimation::BindAnimation(ANIMSTATE state, CTexture* texture, float frameSpeed, bool repeat)
{
	AnimFrame& animFrame = m_MapAnimation[state];
	animFrame.bRepeat = repeat;
	animFrame.fAccTime = 0.f;
	animFrame.fFrameSpeed = frameSpeed;
	animFrame.iFrame = 0;
	animFrame.iMaxFrame = texture->Get_Size();
	animFrame.pTexture = texture;

	SelectState(state);
}

void CAnimation::Play_Animation()
{
	m_bPlaying = TRUE;
}

void CAnimation::Stop_Animation()
{
	m_bPlaying = FALSE;

}
