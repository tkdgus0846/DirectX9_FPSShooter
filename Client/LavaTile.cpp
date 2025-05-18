#include "LavaTile.h"
#include "Export_Function.h"
#include "Creature.h"
#include "..\Engine\ParticleMgr.h"
#include "IceBullet.h"
#include "..\Engine\SoundMgr.h"

CLavaTile::CLavaTile(LPDIRECT3DDEVICE9 pGraphicDev) : 
	CFloorTile(pGraphicDev),
	m_fTime(0.f),
	m_fMaxTime(1.f)
{
	Set_ObjTag(Tag());
}

CLavaTile::~CLavaTile()
{
}

CGameObject * CLavaTile::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLavaTile* pInstance = new CLavaTile(pGraphicDev);

	if (FAILED(pInstance->Ready_GameObject()))
	{
		delete pInstance;
		pInstance = nullptr;
	}
	return pInstance;
}

CGameObject * CLavaTile::LoadSaveTarget(LPDIRECT3DDEVICE9 pGraphicDev)
{
	return Create(pGraphicDev);
}

void CLavaTile::SetDead(_bool bDead /*= true*/)
{
	__super::SetDead(bDead);

	STOP_PLAY_SOUND(L"sfxTeeth.wav", SOUND_ENVIRONMENT, 1.f);
}

HRESULT CLavaTile::Add_Component()
{
	HRESULT result = __super::Add_Component();

	CTexture* texture = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"FloorLava", this));
	NULL_CHECK_RETURN(texture, E_FAIL);
	m_uMapComponent[ID_STATIC].insert({ L"FloorLava", texture });
	m_pAnimation->BindAnimation(ANIM_IDLE, texture);

	m_pCollider = dynamic_cast<CCollider*>(Engine::Clone_Proto(L"Collider", L"Collider", this, COL_ENVIRONMENT));
	NULL_CHECK_RETURN(m_pCollider, E_FAIL);
	m_uMapComponent[ID_ALL].insert({ L"Collider", m_pCollider });

	m_pCollider->Set_BoundingBox({ 10.f,2.4f,10.f });


	return result;
}

void CLavaTile::OnCollisionStay(const Collision * collision)
{

	if (dynamic_cast<CIceBullet*>(collision->OtherGameObject) != nullptr)
	{
		SetDead();
		return;
	}


	CCreature* creature = dynamic_cast<CCreature*>(collision->OtherGameObject);
	if (creature && IsBodyCollider(collision))
	{
		_vec3 amountVec = collision->amountVec;
		if (m_pTransform == nullptr) return;

		_float fps60 = Engine::Get_Timer(L"Timer_FPS60");
		const float amount = 20.f;
		switch (collision->CollisionDir)
		{

		case DIR_LEFT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x -= fps60 * amountVec.x * amount;
			break;
		case DIR_RIGHT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].x += fps60 * amountVec.x * amount;
			break;
		case DIR_FRONT:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z += fps60 * amountVec.z * amount;
			break;
		case DIR_BACK:
			collision->OtherGameObject->m_pTransform->m_vInfo[INFO_POS].z -= fps60 * amountVec.z * amount;
			break;
		default:
			break;
		}
	}
}

_int CLavaTile::Update_GameObject(const _float& fTimeDelta)
{
	if (GetDead()) return OBJ_DEAD;

	m_fTime += fTimeDelta;

	if (m_fTime > m_fMaxTime)
	{
		CParticle* particle = CParticleMgr::GetInstance()->Pop(m_pGraphicDev, L"UpSmoke_Particle", 1, m_pTransform->m_vInfo[INFO_POS], { 0.f,1.f,0.f });
		Add_GameObject(particle);

		m_fTime = 0.f;
	}
	

	return __super::Update_GameObject(fTimeDelta);
}
