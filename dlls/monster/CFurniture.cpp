#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "schedule.h"
#include "scripted.h"
#include "defaultai.h"

//=========================================================
// Furniture - this is the cool comment I cut-and-pasted
//=========================================================
class CFurniture : public CBaseMonster
{
public:
	void Spawn(void);
	void Die(void);
	int	 Classify(void);
	virtual int	ObjectCaps(void) { return (CBaseMonster::ObjectCaps() & ~FCAP_ACROSS_TRANSITION); }
};


LINK_ENTITY_TO_CLASS(monster_furniture, CFurniture);


//=========================================================
// Furniture is killed
//=========================================================
void CFurniture::Die(void)
{
	SetThink(&CFurniture::SUB_Remove);
	pev->nextthink = gpGlobals->time;
}

//=========================================================
// This used to have something to do with bees flying, but 
// now it only initializes moving furniture in scripted sequences
//=========================================================
void CFurniture::Spawn()
{
	PRECACHE_MODEL((char*)STRING(pev->model));
	SET_MODEL(ENT(pev), STRING(pev->model));

	pev->movetype = MOVETYPE_NONE;
	pev->solid = SOLID_BBOX;
	pev->health = 80000;
	pev->takedamage = DAMAGE_AIM;
	pev->effects = 0;
	pev->yaw_speed = 0;
	pev->sequence = 0;
	pev->frame = 0;

	//	pev->nextthink += 1.0;
	//	SetThink (WalkMonsterDelay);

	ResetSequenceInfo();
	pev->frame = 0;
	MonsterInit();
}

//=========================================================
// ID's Furniture as neutral (noone will attack it, unless
// overridden)
//=========================================================
int CFurniture::Classify(void)
{
	return	m_Classify ? CBaseMonster::Classify() : CLASS_NONE;
}
