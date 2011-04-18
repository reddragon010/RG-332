/* Script Data Start
SDName: Boss skadi
SDAuthor: LordVanMartin
SD%Complete:
SDComment:
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = 'boss_skadi' where entry = '';
*** SQL END ***/
#include "ScriptedPch.h"
#include "utgarde_pinnacle.h"

//Phase 0 "gauntlet even" Skadi on a flying mount, waves of adds charging to the group periodicaly carrying harpoons
//Phase 1 Kill the Skadi drake mount with harppons launcher
//Phase 2 Kill the Skadi

//Skadi Spells
enum Spells
{
    SPELL_CRUSH                         = 50234,
    H_SPELL_CRUSH                       = 59330,
    SPELL_POISONED_SPEAR                = 50225,
    SPELL_POISONED_SPEAR_DOT            = 50258,
    H_SPELL_POISONED_SPEAR              = 59331,
    H_SPELL_POISONED_SPEAR_DOT          = 59334,
    SPELL_WHIRLWIND                     = 50228,//random target, but not the tank approx. every 20s
    H_SPELL_WHIRLWIND                   = 59322,
    SPELL_FREEZING_CLOUD                = 47579,
    H_SPELL_FREEZING_CLOUD              = 60020,
    SPELL_FREEZING_CLOUD_PERIODIC_LEFT  = 47590, //this triggers eventai freezing cloud
    SPELL_FREEZING_CLOUD_TRIGGERED_LEFT = 47563,
    SPELL_FREEZING_CLOUD_PERIODIC_RIGHT = 47592,
    SPELL_FREEZING_CLOUD_TRIGGERED_RIGHT= 47593,
    

    // casted with base of creature 22515 (World Trigger), so we must make sure
    // to use the close one by the door leading further in to instance.
    SPELL_SUMMON_GAUNTLET_MOBS          = 48630, // tick every 30 sec
    SPELL_SUMMON_GAUNTLET_MOBS_H        = 59275, // tick every 25 sec

    SPELL_GAUNTLET_PERIODIC             = 47546, // what is this? Unknown use/effect, but probably related
    Launch_Harpoon_Trigger              = 48641,
    SPELL_LAUNCH_HARPOON_2              = 51368, //Server-side script

    SPELL_LAUNCH_HARPOON                = 48642,                // this spell hit drake to reduce HP (force triggered from 48641)
    //SPELL_SKADI_TELEPORT                = 61790,
};
//Spawned creatures
enum Creatures
{
    CREATURE_YMIRJAR_WARRIOR            = 26690,
    CREATURE_YMIRJAR_WITCH_DOCTOR       = 26691,
    CREATURE_YMIRJAR_HARPOONER          = 26692,
    CREATURE_SKADI                      = 26693,
    //Flame Breath Trigger (Skadi)        = 28351,
};

//enum
// {
    // DATA_MOUNT                          = 27043
// };


//not in db
//Yell
enum Texts
{
    SAY_AGGRO                           = -1575019,
    SAY_DRAKE_BREATH_1                  = -1575020,
    SAY_DRAKE_BREATH_2                  = -1575021,
    SAY_DRAKE_BREATH_3                  = -1575022,
    SAY_DRAKE_HIT_1                     = -1575023,
    SAY_DRAKE_HIT_2                     = -1575024,
    SAY_KILL_1                          = -1575025,
    SAY_KILL_2                          = -1575026,
    SAY_KILL_3                          = -1575027,
    SAY_DEATH                           = -1575028,
    SAY_DRAKE_DEATH                     = -1575029,
    EMOTE_HARPOON_RANGE                 = -1575030,
};

enum Achievements
{
    ACHIEV_LODI_DODI                    = 1873,
    ACHIEV_MY_GIRL_LOVES_TO_SKADI       = 2156
};

enum CombatPhase
{
    IDLE,
    FLYING,
    SKADI,
	EVADE
};
const Position Pos[9] =
{
    {324, -504, 120, 6.3},      //left front
    {494, -506, 120, 3.05},     //left rear
    {322, -518, 120, 6.2},      //right front
    {492, -517, 120, 3.11},     //right rear
    {526, -546, 120, 3},        //harpoon
    {305, -535, 120, 3},        //front
    {482, -513, 105, 3},        //summon
    {323, -511, 105, 3},        //summon WP
    {385, -540, 120, 3},        //Grauf waits here after Phase Flying
};
enum WaypointIDs
{
    WP0,    //left front
    WP1,    //left rear
    WP2,    //right front
    WP3,    //right rear
    WP4,    //harpoon
    WP5,    //front
    SUM,    //summon
    SWP,    //summon WP
    EWP,    //Grauf waits here after Phase Flying, when he is not in LOS, he will not enter evademode
    HOME,
    
};
enum Event
{
    EVENT_NONE,
    EVENT_TAKEOFF,
    EVENT_FLYING_WP0,
    EVENT_FLYING_WP1,
    EVENT_FLYING_WP2,
    EVENT_FLYING_WP3,    
    EVENT_FLYING_WP4,
    EVENT_FLYING_WP5,
    EVENT_BREATH,
    EVENT_SPAWN,
    EVENT_HARPOON,
    EVENT_LAND,
    EVENT_GROUND,
    EVENT_CRUSH,
    EVENT_SPEAR,
    EVENT_WHIRLWIND,
    EVENT_SUMMON_WARRIOR,
    EVENT_SUMMON_WITCH_DOCTOR,
    EVENT_SUMMON_HARPOONER,
};

#define EMOTE_DEEP_BREATH "Grauf takes a deep breath"

struct boss_skadiAI : public BossAI
{
    boss_skadiAI(Creature *c) : BossAI(c, DATA_SKADI_THE_RUTHLESS)
    {
        pInstance = c->GetInstanceData();
    }

    uint32 uiLodiDodiTimer;
    
    uint32 uiCrushTimer;
    uint32 uiPoisonedSpearTimer;
    uint32 uiWhirlwindTimer;

    CombatPhase Phase;
    
    ScriptedInstance* pInstance;

    void Reset()
    {
        if (!me->isAlive())
            return;

        events.Reset();
        summons.DespawnAll();

        Phase = IDLE;
        uiLodiDodiTimer = 0;// max 3 * MINUTE * IN_MILISECONDS
        
        uiCrushTimer = 8*IN_MILISECONDS;
        uiPoisonedSpearTimer = 10*IN_MILISECONDS;
        uiWhirlwindTimer = 20*IN_MILISECONDS;
     
        if (Creature* pGrauf = Creature::GetCreature(*me, pInstance->GetData64(DATA_GRAUF)))
            pGrauf->SetPhaseMask(1, true);
        
        if (pInstance)
            pInstance->SetData(DATA_SKADI_THE_RUTHLESS_EVENT, NOT_STARTED);
	    me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
	    me->setFaction(35);
        me->SetReactState(REACT_PASSIVE);
        me->AttackStop();
    }

    //void EnterCombat(Unit* who)
    //{
    //    DoScriptText(SAY_AGGRO, me);
    //    
    //    if (Creature* pGrauf = Creature::GetCreature(*me, pInstance->GetData64(DATA_GRAUF)))
    //    {
    //        if (pGrauf->IsVehicle())
    //            me->EnterVehicle(pGrauf);
    //        else
    //            EnterEvadeMode();
    //    }
    //    if (pInstance)
    //        pInstance->SetData(DATA_SKADI_THE_RUTHLESS_EVENT, IN_PROGRESS);
    //}

    void EnterEvadeMode()
    {
        events.Reset();
        summons.DespawnAll();
        _EnterEvadeMode();
        me->GetMotionMaster()->MoveTargetedHome();
        if (Creature* pGrauf = Creature::GetCreature(*me, pInstance->GetData64(DATA_GRAUF)))
        //    if (!pGrauf->IsInEvadeMode())
                pGrauf->AI()->EnterEvadeMode();
        Reset();
    }
	
    void DoAction(const int32 param)
    {
	    DoScriptText(SAY_AGGRO, me);

        if (Creature* pGrauf = Creature::GetCreature(*me, pInstance->GetData64(DATA_GRAUF)))
        {
            if (pGrauf->IsVehicle())
            {
                me->EnterVehicle(pGrauf);
                Phase = FLYING;
                if (pInstance)
                    pInstance->SetData(DATA_SKADI_THE_RUTHLESS_EVENT, IN_PROGRESS);

                DoZoneInCombat();
            }
            else
                EnterEvadeMode();
        }
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell) 
    {
        if ( IsHeroic() && (spell->Id == H_SPELL_POISONED_SPEAR))
            pTarget->CastSpell(pTarget, H_SPELL_POISONED_SPEAR_DOT, false);
        else if 
            ( !IsHeroic() && (spell->Id == H_SPELL_POISONED_SPEAR))
                pTarget->CastSpell(pTarget, SPELL_POISONED_SPEAR_DOT, false);
    }
    
    void DoText(int32 entry)
    {
        DoScriptText(entry, me);
    }


    void UpdateAI(const uint32 diff)
    {
        if (Phase == IDLE)
            return;

        if (Phase == SKADI)
            if (!UpdateVictim())
                return;

        events.Update(diff);
        uiLodiDodiTimer += diff;
        
        if (uint32 eventId = events.GetEvent())
        {
            switch(eventId)
            {
                case EVENT_SUMMON_WARRIOR:
                {
                    Creature* creature = me->SummonCreature(CREATURE_YMIRJAR_WARRIOR, urand(474,484), -1.0*urand(509, 519), 105, 0, TEMPSUMMON_MANUAL_DESPAWN);
                    if (creature)
                    {
                        if (Map *pInstance = me->GetInstanceData()->instance)
                        {

                            std::vector<Unit*> targets;
                            Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    if (((Player*)i->getSource())->isAlive())
                                        targets.push_back(i->getSource());
                                }
                                if (!targets.empty())
                                {
                                    std::vector<Unit*>::const_iterator itr = targets.begin();
                                    advance(itr, rand()%targets.size());
							        creature->AI()->AttackStart(*itr);
                                }
                            }
                        }
                    }
                }
                    events.PopEvent();
                    break;
                case EVENT_SUMMON_WITCH_DOCTOR:
                {
                    Creature* creature = me->SummonCreature(CREATURE_YMIRJAR_WITCH_DOCTOR, urand(474,484), -1.0*urand(509, 519), 105, 0, TEMPSUMMON_MANUAL_DESPAWN);
                    if (creature)
                    {
                        if (Map *pInstance = me->GetInstanceData()->instance)
                        {

                            std::vector<Unit*> targets;
                            Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    if (((Player*)i->getSource())->isAlive())
                                        targets.push_back(i->getSource());
                                }
                                if (!targets.empty())
                                {
                                    std::vector<Unit*>::const_iterator itr = targets.begin();
                                    advance(itr, rand()%targets.size());
                                    creature->SetReactState(REACT_AGGRESSIVE);
							        creature->AI()->AttackStart(*itr);
                                }
                            }
                        }
                    }
                }
                    events.PopEvent(); 
                    break;
                case EVENT_SUMMON_HARPOONER:
                {
                    Creature* creature = me->SummonCreature(CREATURE_YMIRJAR_HARPOONER, urand(474,484), -1.0*urand(509, 519), 105, 0, TEMPSUMMON_MANUAL_DESPAWN);
                    if (creature)
                    {
                        if (Map *pInstance = me->GetInstanceData()->instance)
                        {

                            std::vector<Unit*> targets;
                            Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                            if (!PlayerList.isEmpty())
                            {
                                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                                {
                                    if (((Player*)i->getSource())->isAlive())
                                        targets.push_back(i->getSource());
                                }
                                if (!targets.empty())
                                {
                                    std::vector<Unit*>::const_iterator itr = targets.begin();
                                    advance(itr, rand()%targets.size());
                                    creature->SetReactState(REACT_AGGRESSIVE);
							        creature->AI()->AttackStart(*itr);
                                 }
                            }
                        }
                    }
                }
                    events.PopEvent();
                    break;
                case EVENT_LAND:
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RestoreFaction();
					me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
                    me->ExitVehicle();    
                    DoTeleportTo(Pos[SUM].GetPositionX(), Pos[SUM].GetPositionY(), Pos[SUM].GetPositionZ());
                    DoScriptText(SAY_DRAKE_DEATH, me);
                    events.ScheduleEvent(EVENT_GROUND, 2*IN_MILISECONDS);
                    events.PopEvent();
                    break;
                case EVENT_GROUND:
                {   
                    Phase = SKADI;
                    if (Map *pInstance = me->GetInstanceData()->instance)
                    {
                        std::vector<Unit*> targets;
                        Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                        if (!PlayerList.isEmpty())
                        {
                            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            {
                                if (((Player*)i->getSource())->isAlive())
                                    targets.push_back(i->getSource());
                            }
                            if (!targets.empty())


                            {
                                std::vector<Unit*>::const_iterator itr = targets.begin();
                                advance(itr, rand()%targets.size());
                                me->AI()->AttackStart(*itr);
                                DoStartMovement(*itr);
                            }
					    }
                    }
                    events.ScheduleEvent(EVENT_CRUSH, 8*IN_MILISECONDS);
                    events.ScheduleEvent(EVENT_SPEAR, 10*IN_MILISECONDS);
                    events.ScheduleEvent(EVENT_WHIRLWIND, 2*IN_MILISECONDS);
                }
                    events.PopEvent();
                    break;
                case EVENT_CRUSH:
                    if (!me->HasAura(DUNGEON_MODE(SPELL_WHIRLWIND, H_SPELL_WHIRLWIND)))
                        DoCast(me->getVictim(), DUNGEON_MODE(SPELL_CRUSH, H_SPELL_CRUSH));
                    events.RepeatEvent(urand(8*IN_MILISECONDS, 15*IN_MILISECONDS));
                    break;
                case EVENT_SPEAR:
                {    
                    if (!me->HasAura(DUNGEON_MODE(SPELL_WHIRLWIND, H_SPELL_WHIRLWIND)))
                        if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                        {
                            if (IsHeroic())
                                DoCast(pTarget, H_SPELL_POISONED_SPEAR);
                            else
                            {
                                int32 dmg = urand(4713, 5287);
                                me->CastCustomSpell(pTarget, H_SPELL_POISONED_SPEAR, &dmg, 0, 0, false);
                            }
                        }
                    events.RepeatEvent(urand(12*IN_MILISECONDS, 30*IN_MILISECONDS));
                }
                    break;
                case EVENT_WHIRLWIND:
                {
                    if (!me->HasAura(DUNGEON_MODE(SPELL_WHIRLWIND, H_SPELL_WHIRLWIND)))
                        if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            me->CastSpell(pTarget, DUNGEON_MODE(SPELL_WHIRLWIND, H_SPELL_WHIRLWIND), false);
                    events.RepeatEvent(urand(23*IN_MILISECONDS, 60*IN_MILISECONDS));
                }
                    break;
                default:
                    events.PopEvent();
                    break;
             }
        }
        DoMeleeAttackIfReady();        
    }

    void JustDied(Unit* killer)
    {
        events.Reset();
        summons.DespawnAll();
        DoScriptText(SAY_DEATH, me);

        if (pInstance)
        {
            if (IsHeroic() && uiLodiDodiTimer <= (3 * MINUTE * IN_MILISECONDS))
                pInstance->DoCompleteAchievement(ACHIEV_LODI_DODI);
			pInstance->SetData(DATA_SKADI_THE_RUTHLESS_EVENT, DONE);
        }    
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(RAND(SAY_KILL_1,SAY_KILL_2,SAY_KILL_3), me);
    }
};

CreatureAI* GetAI_boss_skadi(Creature* pCreature)
{
    return new boss_skadiAI (pCreature);
}

struct boss_graufAI : public BossAI
{
    boss_graufAI(Creature *c) : BossAI(c, DATA_GRAUF)
    {
        pInstance = c->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    CombatPhase phase;

    bool bHarpoon;
    bool bCanHarpoon;
    bool bPlayerAlive;

    uint8 uiHarpoonHits;
    uint8 uiMaxSpawn;
    uint8 uiSpawns;
    uint8 uiHarpoonCounter;

    void Reset()
    {
	    events.Reset();
        phase = IDLE;

        uiHarpoonHits = 0;
        uiHarpoonCounter = 0;
        bHarpoon = false;
        bCanHarpoon = false;
        bPlayerAlive = false;

        uiMaxSpawn = DUNGEON_MODE(5, 6);
        uiSpawns = 0;

        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_UNK_9);
		me->SetReactState(REACT_PASSIVE);
    }

    void EnterEvadeMode()
    {
	    events.Reset();
        _EnterEvadeMode();
        me->GetMotionMaster()->MovePoint(HOME, me->GetHomePosition());
    }

    void JustReachedHome()
    {
        _JustReachedHome();
        Creature* pSkadi = Creature::GetCreature(*me, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS));
        if (pSkadi && me->IsVehicle() && me->GetVehicleKit()->GetPassenger(0))
        {
            pSkadi->ExitVehicle();
            pSkadi->AI()->EnterEvadeMode();
        }
        Reset();
    }

    void UpdateAI(const uint32 diff)
    {
        if (phase == IDLE)
        {
            if (me->IsVehicle() && me->GetVehicleKit()->GetPassenger(0))
            {
                events.ScheduleEvent(EVENT_TAKEOFF, 500);
                phase = FLYING;
            }
            else
                return;
        }
		
        if (phase == FLYING)
        {
            if (Map *pInstance = me->GetInstanceData()->instance)
            {
                Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                if (!PlayerList.isEmpty())
                {
                    bPlayerAlive = false;
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                    {
                        if (((Player*)i->getSource())->isAlive() && !((Player*)i->getSource())->isGameMaster())
                        {
                            bPlayerAlive = true;
                            break;
                        }
                    }
                    if (!bPlayerAlive /*&& phase != EVADE && phase != IDLE*/)
                    {
                        phase = EVADE;
                        EnterEvadeMode();
                    }
                }
            }
        }

        if (uiHarpoonHits >= 3)
        {
            events.Reset();
            Creature* pSkadi = Creature::GetCreature(*me, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS));
            if (!pSkadi)
                return;

            boss_skadiAI* pSkadiAI = CAST_AI(boss_skadiAI, pSkadi->AI());
            if (!pSkadiAI)
                return;

            pSkadiAI->events.ScheduleEvent(EVENT_LAND, 0);
            if (IsHeroic() && uiHarpoonCounter <= 1)
                if (pInstance)
                    pInstance->DoCompleteAchievement(ACHIEV_MY_GIRL_LOVES_TO_SKADI);
            uiHarpoonHits = 0;
            me->SetPhaseMask(2, true);
			me->GetMotionMaster()->MovePoint(EWP, Pos[EWP]);
        }

        events.Update(diff);

        if (uint32 eventId = events.GetEvent())
        {
            switch(eventId)
            {
            case EVENT_TAKEOFF:
                me->SetFlying(true);
                me->SetSpeed(MOVE_FLIGHT, 2.0);
                events.ScheduleEvent(EVENT_FLYING_WP0, 0);
                events.ScheduleEvent(EVENT_SPAWN, 3*IN_MILISECONDS);
                events.PopEvent();
                break;
            case EVENT_FLYING_WP0:
                bHarpoon = true;
                me->GetMotionMaster()->MovePoint(WP0, Pos[WP0]);
                events.PopEvent();
                break;
            case EVENT_FLYING_WP1:
                me->GetMotionMaster()->MovePoint(WP1, Pos[WP1]);
                bCanHarpoon = false;
                events.PopEvent();
                events.ScheduleEvent(EVENT_BREATH, 2*IN_MILISECONDS);
                break;
            case EVENT_FLYING_WP2:
                bHarpoon = true;
                me->GetMotionMaster()->MovePoint(WP2, Pos[WP2]);
                events.PopEvent();
                break;
            case EVENT_FLYING_WP3:
                me->GetMotionMaster()->MovePoint(WP3, Pos[WP3]);
                bCanHarpoon = false;
                events.PopEvent();
                events.ScheduleEvent(EVENT_BREATH, 2*IN_MILISECONDS);
                break;
            case EVENT_FLYING_WP4:
                me->GetMotionMaster()->MovePoint(WP4, Pos[WP4]); 
                events.PopEvent();
                break;        
            case EVENT_FLYING_WP5:
                me->GetMotionMaster()->MovePoint(WP5, Pos[WP5]); 
                events.PopEvent();
                break;                                 
            case EVENT_BREATH:
                if (Creature* pSkadi = Creature::GetCreature(*me, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS)))
                    DoScriptText(RAND(SAY_DRAKE_BREATH_1, SAY_DRAKE_BREATH_2, SAY_DRAKE_BREATH_3), pSkadi);
                me->MonsterTextEmote(EMOTE_DEEP_BREATH, 0, true);
                events.PopEvent();
                break;
            case EVENT_SPAWN:
                {    
                    if (uiSpawns++ < uiMaxSpawn)
                    {
                        Creature* pSkadi = Creature::GetCreature(*me, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS));
                        if (pSkadi)
                        {
                            boss_skadiAI* pSkadiAI = CAST_AI(boss_skadiAI, pSkadi->AI());
                            if (pSkadiAI)
                            {
                                switch (urand(0, 2))
                                {
                                    case 0: pSkadiAI->events.ScheduleEvent(EVENT_SUMMON_WARRIOR, urand(200, 1*IN_MILISECONDS)); break;
                                    case 1: pSkadiAI->events.ScheduleEvent(EVENT_SUMMON_WITCH_DOCTOR, urand(200, 1*IN_MILISECONDS)); break;
                                    case 2: pSkadiAI->events.ScheduleEvent(EVENT_SUMMON_HARPOONER, urand(200, 1*IN_MILISECONDS)); break;
                                }
                            }
                        }
                        events.RepeatEvent(1 * IN_MILISECONDS);
                    }
                    else
                    {
                        uiSpawns = 0;
                        events.RepeatEvent(DUNGEON_MODE(30*IN_MILISECONDS, 25*IN_MILISECONDS));
                    }
                }
                break;
            case EVENT_HARPOON:
                bCanHarpoon = true;
                ++uiHarpoonCounter;
                me->MonsterTextEmote(EMOTE_HARPOON_RANGE, 0, true);
                events.PopEvent();
                break;
            default:
                events.PopEvent();
                break;
            }
        }
    }


    void MovementInform(uint32 type, uint32 id)
    {
        if(type != POINT_MOTION_TYPE)
            return;

        switch (id)
        {
        case WP0:
            events.ScheduleEvent(EVENT_FLYING_WP5, 0);
            me->CastStop();
            me->RemoveAurasDueToSpell(SPELL_FREEZING_CLOUD_PERIODIC_LEFT);
            break;
        case WP1:
            events.ScheduleEvent(EVENT_FLYING_WP0, 0);
            DoCast(SPELL_FREEZING_CLOUD_PERIODIC_LEFT);
            break;
        case WP2:
            events.ScheduleEvent(EVENT_FLYING_WP5, 0);
            me->CastStop();
            me->RemoveAurasDueToSpell(SPELL_FREEZING_CLOUD_PERIODIC_RIGHT);
            break;
        case WP3:
            events.ScheduleEvent(EVENT_FLYING_WP2, 0);
            DoCast(SPELL_FREEZING_CLOUD_PERIODIC_RIGHT);
            break;
        case WP4:
            bHarpoon = false;
            events.ScheduleEvent(EVENT_HARPOON, 0);
            events.ScheduleEvent(RAND(EVENT_FLYING_WP1, EVENT_FLYING_WP3), 6*IN_MILISECONDS);
            break;  
        case WP5:
            events.ScheduleEvent(EVENT_FLYING_WP4, 0);
            break;     
        case HOME:
            JustReachedHome();
            break;  
        }       
    }
};

CreatureAI* GetAI_boss_grauf(Creature* pCreature)
{
    return new boss_graufAI (pCreature);
}


bool go_harpoon(Player* pPlayer, GameObject* pGo)
{
    ScriptedInstance* pInstance = pPlayer->GetInstanceData();
    if (!pInstance)
        return false;

    Creature *pGrauf = Creature::GetCreature(*pPlayer, pInstance->GetData64(DATA_GRAUF));
    if (!pGrauf)
        return false;

    boss_graufAI* pGraufAI = CAST_AI(boss_graufAI, pGrauf->AI());
    if (!pGraufAI)
        return false;

    Creature* pSkadi = Creature::GetCreature(*pPlayer, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS));
    if (!pSkadi)
        return false;

    boss_skadiAI* pSkadiAI = CAST_AI(boss_skadiAI, pSkadi->AI());
    if (!pSkadiAI)
        return false;

    if (pGraufAI->bCanHarpoon)
    {
        pGraufAI->uiHarpoonHits++;
        pSkadiAI->DoText(RAND(SAY_DRAKE_HIT_1, SAY_DRAKE_HIT_2));
    }

    return true;
}

bool AreaTrigger_at_skadi(Player* pPlayer, const AreaTriggerEntry *at)
{
    if (pPlayer->isGameMaster())
        return false;

    ScriptedInstance* pInstance = pPlayer->GetInstanceData();
    if (!pInstance || pInstance->IsEncounterInProgress() || pInstance->GetData(DATA_SKADI_THE_RUTHLESS_EVENT) == DONE)
        return false;

    Creature* pSkadi = Creature::GetCreature(*pPlayer, pInstance->GetData64(DATA_SKADI_THE_RUTHLESS));
    if (!pSkadi)
        return false;

    pSkadi->AI()->DoAction(NULL);

    return true;
}
void AddSC_boss_skadi()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_skadi";
    newscript->GetAI = &GetAI_boss_skadi;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_grauf";
    newscript->GetAI = &GetAI_boss_grauf;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name="go_harpoon";
    newscript->pGOHello = &go_harpoon;
    newscript->RegisterSelf();
    
	newscript = new Script;
    newscript->Name = "at_skadi";
    newscript->pAreaTrigger = &AreaTrigger_at_skadi;
    newscript->RegisterSelf();
}
