/*
 * Copyright (C) 2008 - 2009 Trinity <http://www.trinitycore.org/>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
 */
 
/* ScriptData
SDName: Flame Leviathan
SDAuthor: PrinceCreed
SD%Complete: 65
EndScriptData */

#include "ScriptedPch.h"
#include "ulduar.h"
#include "Vehicle.h"

enum Spells
{
    SPELL_PURSUED                               = 62374,
    SPELL_GATHERING_SPEED                       = 62375,
    SPELL_BATTERING_RAM                         = 62376,
    SPELL_FLAME_VENTS                           = 62396,
    SPELL_MISSILE_BARRAGE                       = 62400,
    SPELL_SYSTEMS_SHUTDOWN                      = 62475,

    SPELL_FLAME_CANNON                          = 62395,
    //SPELL_FLAME_CANNON                        = 64692 trigger the same spell

    SPELL_OVERLOAD_CIRCUIT                      = 62399,
    SPELL_SEARING_FLAME                         = 62402,
    SPELL_BLAZE                                 = 62292,
    SPELL_SMOKE_TRAIL                           = 63575,
    SPELL_ELECTROSHOCK                          = 62522,
    SPELL_STUN                                  = 9032,
   
    // Ulduar Colossus spell
    SPELL_GROUND_SLAM                           = 62625,
};

enum Mobs
{
    MOB_MECHANOLIFT                             = 33214,
    MOB_LIQUID                                  = 33189,
    MOB_CONTAINER                               = 33218,
    MOB_COLOSSUS                                = 33237,//33240,
};

#define ACTION_VEHICLE_RESPAWN                    1
#define INCREASE_COLOSSUS_COUNT                   2

enum Events
{
    EVENT_NONE,
    EVENT_PURSUE,
    EVENT_MISSILE,
    EVENT_VENT,
    EVENT_SPEED,
    EVENT_SUMMON,
    EVENT_SHUTDOWN, // not offylike
};

enum Seats
{
    SEAT_PLAYER                                 = 0,
    SEAT_TURRET                                 = 1,
    SEAT_DEVICE                                 = 2,
};

#define EMOTE_PURSUE          "Flame Leviathan pursues $N."
#define EMOTE_OVERLOAD        "Flame Leviathan's circuits overloaded."
#define EMOTE_REPAIR          "Automatic repair sequence initiated."
#define GOSSIP_ITEM_1         "Summon vehicles!"

enum Yells
{
    SAY_AGGRO                                   = -1603060,
    SAY_SLAY                                    = -1603061,
    SAY_DEATH                                   = -1603062,
    SAY_TARGET_1                                = -1603063,
    SAY_TARGET_2                                = -1603064,
    SAY_TARGET_3                                = -1603065,
    SAY_HARDMODE                                = -1603066,
    SAY_TOWER_NONE                              = -1603067,
    SAY_TOWER_FROST                             = -1603068,
    SAY_TOWER_FLAME                             = -1603069,
    SAY_TOWER_NATURE                            = -1603070,
    SAY_TOWER_STORM                             = -1603071,
    SAY_PLAYER_RIDING                           = -1603072,
    SAY_OVERLOAD_1                              = -1603073,
    SAY_OVERLOAD_2                              = -1603074,
    SAY_OVERLOAD_3                              = -1603075,
};

#define VEHICLE_SIEGE                              33060
#define VEHICLE_CHOPPER                            33062
#define VEHICLE_DEMOLISHER                         33109

const Position PosSiege[5] =
{
{-814.59,-64.54,429.92,5.969},
{-784.37,-33.31,429.92,5.096},
{-808.99,-52.10,429.92,5.668},
{-798.59,-44.00,429.92,5.663},
{-812.83,-77.71,429.92,0.046}
};

const Position PosChopper[5] =
{
{-717.83,-106.56,430.02,0.122},
{-717.83,-114.23,430.44,0.122},
{-717.83,-109.70,430.22,0.122},
{-718.45,-118.24,430.26,0.052},
{-718.45,-123.58,430.41,0.085}
};

const Position PosDemolisher[5] =
{
{-724.12,-176.64,430.03,2.543},
{-766.70,-225.03,430.50,1.710},
{-729.54,-186.26,430.12,1.902},
{-756.01,-219.23,430.50,2.369},
{-798.01,-227.24,429.84,1.446}
};

const Position PosColossus[2] =
{
{367.031, 12.784,409.886,3.263},
{368.768,-46.847,409.886,3.036}
};

struct boss_flame_leviathanAI : public BossAI
{
    boss_flame_leviathanAI(Creature *pCreature) : BossAI(pCreature, BOSS_LEVIATHAN), vehicle(me->GetVehicleKit())
    {
        assert(vehicle);
        pInstance = pCreature->GetInstanceData();
        ColossusCount = 0;
       
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
        me->SetReactState(REACT_PASSIVE);
       
        // Summon Ulduar Colossus
        if (me->isAlive())
            for(uint32 i = 0; i < 2; ++i)
                DoSummon(MOB_COLOSSUS, PosColossus[i], 7000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
        }

    ScriptedInstance* pInstance;
    Vehicle *vehicle;
    uint32 ColossusCount;

    void Reset()
    {
        _Reset();
    }

    void EnterCombat(Unit *who)
    {
        _EnterCombat();
        DoScriptText(SAY_AGGRO, me);
        events.ScheduleEvent(EVENT_PURSUE, 0);
        events.ScheduleEvent(EVENT_MISSILE, 1500);
        events.ScheduleEvent(EVENT_VENT, 20000);
        events.ScheduleEvent(EVENT_SPEED, 2000);
        //events.ScheduleEvent(EVENT_SUMMON, 0);
        events.ScheduleEvent(EVENT_SHUTDOWN, 120000);
        if (Creature *turret = CAST_CRE(vehicle->GetPassenger(7)))
            turret->AI()->DoZoneInCombat();
    }

    void JustDied(Unit *victim)
    {
        DoScriptText(SAY_DEATH, me);
                   
        _JustDied();
    }
   
    void DamageTaken(Unit* pKiller, uint32 &damage)
        {
            if(damage >= me->GetHealth())
            {
                std::list<HostileReference*> ThreatList = me->getThreatManager().getThreatList();
            for (std::list<HostileReference*>::const_iterator itr = ThreatList.begin(); itr != ThreatList.end(); ++itr)
            {
                Unit *pTarget = Unit::GetUnit(*me, (*itr)->getUnitGuid());
           
                if (pTarget->GetTypeId() == TYPEID_PLAYER)
                    continue;
                else me->Kill(pTarget, false);
            }
            }
        }


    void SpellHit(Unit *caster, const SpellEntry *spell)
    {
        if(spell->Id == 62472)
            vehicle->InstallAllAccessories();
        else if(spell->Id == SPELL_ELECTROSHOCK)
            me->InterruptSpell(CURRENT_CHANNELED_SPELL);
    }

    void KilledUnit(Unit* Victim)
    {
        if (!(rand()%5))
            DoScriptText(SAY_SLAY, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        if (me->HasAura(SPELL_SYSTEMS_SHUTDOWN))
        {
            me->SetReactState(REACT_PASSIVE);
            me->CastSpell(me, SPELL_STUN, true);
            return;
        }
                else
        {
            me->SetReactState(REACT_AGGRESSIVE);
            me->RemoveAurasDueToSpell(SPELL_STUN);
        }

        while(uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
            case 0: break;
            case EVENT_PURSUE:
                DoScriptText(RAND(SAY_TARGET_1, SAY_TARGET_2, SAY_TARGET_3), me);
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    DoResetThreat();
                    me->AddAura(SPELL_PURSUED, pTarget);
                    me->AddThreat(pTarget, 5000000.0f);
                    me->MonsterTextEmote(EMOTE_PURSUE, me->getVictim()->GetGUID(), true);
                }
                events.RescheduleEvent(EVENT_PURSUE, 35000);
                break;
            case EVENT_MISSILE:
                DoCastAOE(SPELL_MISSILE_BARRAGE);
                events.RescheduleEvent(EVENT_MISSILE, 1500);
                break;
            case EVENT_VENT:
                DoCastAOE(SPELL_FLAME_VENTS);
                events.RescheduleEvent(EVENT_VENT, 20000);
                break;
            case EVENT_SPEED:
                DoCastAOE(SPELL_GATHERING_SPEED);
                events.RescheduleEvent(EVENT_SPEED, 10000);
                break;
            case EVENT_SUMMON:
                if(summons.size() < 15) // 4seat+1turret+10lift
                    if(Creature *lift = DoSummonFlyer(MOB_MECHANOLIFT, me, rand()%20 + 20, 50, 0))
                        lift->GetMotionMaster()->MoveRandom(100);
                events.RescheduleEvent(EVENT_SUMMON, 2000);
                break;
            case EVENT_SHUTDOWN:
                DoScriptText(RAND(SAY_OVERLOAD_1, SAY_OVERLOAD_2, SAY_OVERLOAD_3), me);
                me->MonsterTextEmote(EMOTE_OVERLOAD, 0, true);
                DoCast(SPELL_SYSTEMS_SHUTDOWN);
                me->RemoveAurasDueToSpell(SPELL_GATHERING_SPEED);
                me->MonsterTextEmote(EMOTE_REPAIR, 0, true);
                events.RescheduleEvent(EVENT_SHUTDOWN, 120000);
                break;
            default:
                events.PopEvent();
                break;
            }
        }
       
        if (me->IsWithinMeleeRange(me->getVictim()))
            DoSpellAttackIfReady(SPELL_BATTERING_RAM);
    }
 
    void DoAction(const int32 action)
    {
        switch (action)
        {
            case INCREASE_COLOSSUS_COUNT:
                ++ColossusCount;
                outstring_log("INCREASE_COLOSSUS_COUNT");
                break;
        }
       
        if (ColossusCount >= 2)
        {
            outstring_log("ColossusCount >= 2");
            // Event starts
            if (pInstance)
                pInstance->SetData(DATA_LEVIATHAN_DOOR, GO_STATE_ACTIVE);
               
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
            me->SetReactState(REACT_AGGRESSIVE);
            me->SetHomePosition(318.74, -13.75, 409.803, 3.12723); // new Home Position
            me->GetMotionMaster()->MoveTargetedHome();
            DoZoneInCombat();
        }
    }
};

//#define BOSS_DEBUG

struct boss_flame_leviathan_seatAI : public PassiveAI
{
    boss_flame_leviathan_seatAI(Creature *c) : PassiveAI(c), vehicle(c->GetVehicleKit())
    {
        assert(vehicle);
#ifdef BOSS_DEBUG
        me->SetReactState(REACT_AGGRESSIVE);
#endif
    }

    Vehicle *vehicle;

#ifdef BOSS_DEBUG
    void MoveInLineOfSight(Unit *who)
    {
        if(who->GetTypeId() == TYPEID_PLAYER && CAST_PLR(who)->isGameMaster()
            && !who->GetVehicle() && vehicle->GetPassenger(SEAT_TURRET))
            who->EnterVehicle(vehicle, SEAT_PLAYER);
    }
#endif

    void PassengerBoarded(Unit *who, int8 seatId, bool apply)
    {
        if(!me->GetVehicle())
            return;

        if(seatId == SEAT_PLAYER)
        {
            if(!apply)
                return;

            if(Creature *turret = CAST_CRE(vehicle->GetPassenger(SEAT_TURRET)))
            {
                turret->setFaction(me->GetVehicleBase()->getFaction());
                turret->SetUInt32Value(UNIT_FIELD_FLAGS, 0); // unselectable
                turret->AI()->AttackStart(who);
            }
            if(Unit *device = vehicle->GetPassenger(SEAT_DEVICE))
            {
                device->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                device->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            }
        }
        else if(seatId == SEAT_TURRET)
        {
            if(apply)
                return;

            if(Unit *device = vehicle->GetPassenger(SEAT_DEVICE))
            {
                device->SetFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
                device->SetUInt32Value(UNIT_FIELD_FLAGS, 0); // unselectable
            }
        }
    }
};

struct boss_flame_leviathan_defense_turretAI : public TurretAI
{
    boss_flame_leviathan_defense_turretAI(Creature *c) : TurretAI(c) {}

    void DamageTaken(Unit *who, uint32 &damage)
    {
        if(!CanAIAttack(who))
            damage = 0;
    }

    bool CanAIAttack(const Unit *who) const
    {
        if (who->GetTypeId() != TYPEID_PLAYER || !who->GetVehicle() || who->GetVehicleBase()->GetEntry() != 33114)
            return false;
        return true;
    }
};

struct boss_flame_leviathan_overload_deviceAI : public PassiveAI
{
    boss_flame_leviathan_overload_deviceAI(Creature *c) : PassiveAI(c) {}

    void DoAction(const int32 param)
    {
        if(param == EVENT_SPELLCLICK)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_SPELLCLICK);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            if(me->GetVehicle())
            {
                if(Unit *player = me->GetVehicle()->GetPassenger(SEAT_PLAYER))
                {
                    player->ExitVehicle();
                    me->GetVehicleBase()->CastSpell(player, SPELL_SMOKE_TRAIL, true);
                    if(Unit *leviathan = me->GetVehicleBase()->GetVehicleBase())
                        player->GetMotionMaster()->MoveKnockbackFrom(leviathan->GetPositionX(), leviathan->GetPositionY(), 30, 30);
                }
            }
        }
    }
};


struct boss_flame_leviathan_safety_containerAI : public PassiveAI
{
    boss_flame_leviathan_safety_containerAI(Creature *c) : PassiveAI(c) {}

    void MovementInform(uint32 type, uint32 id)
    {
        if(id == me->GetEntry())
        {
            if(Creature *liquid = DoSummon(MOB_LIQUID, me, 0))
                liquid->CastSpell(liquid, 62494, true);
            me->DisappearAndDie(); // this will relocate creature to sky
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if(!me->GetVehicle() && me->isSummon() && me->GetMotionMaster()->GetCurrentMovementGeneratorType() != POINT_MOTION_TYPE)
            me->GetMotionMaster()->MoveFall(409.8f, me->GetEntry());
    }
};

struct spell_pool_of_tarAI : public TriggerAI
{
    spell_pool_of_tarAI(Creature *c) : TriggerAI(c)
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void DamageTaken(Unit *who, uint32 &damage)
    {
        damage = 0;
    }

    void SpellHit(Unit* caster, const SpellEntry *spell)
    {
        if(spell->SchoolMask & SPELL_SCHOOL_MASK_FIRE && !me->HasAura(SPELL_BLAZE))
            me->CastSpell(me, SPELL_BLAZE, true);
    }
};

struct keeper_norgannonAI : public ScriptedAI
{
    keeper_norgannonAI(Creature *c) : ScriptedAI(c), summons(me)
    {
        pInstance = c->GetInstanceData();
    }

    ScriptedInstance* pInstance;
    SummonList summons;

    void JustSummoned(Creature *summon)
    {
        summons.Summon(summon);
    }
   
    void DoAction(const int32 action)
    {
        switch (action)
        {
            case ACTION_VEHICLE_RESPAWN:
                summons.DespawnAll();
                for(uint32 i = 0; i < (RAID_MODE(2, 5)); ++i)
                    DoSummon(VEHICLE_SIEGE, PosSiege[i], 3000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                for(uint32 i = 0; i < (RAID_MODE(2, 5)); ++i)
                    DoSummon(VEHICLE_CHOPPER, PosChopper[i], 3000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                for(uint32 i = 0; i < (RAID_MODE(2, 5)); ++i)
                    DoSummon(VEHICLE_DEMOLISHER, PosDemolisher[i], 3000, TEMPSUMMON_CORPSE_TIMED_DESPAWN);
                break;
        }
    }
};

bool GossipHello_keeper_norgannon(Player* pPlayer, Creature* pCreature)
{
    InstanceData *data = pPlayer->GetInstanceData();
    ScriptedInstance *pInstance = (ScriptedInstance *) pCreature->GetInstanceData();
   
    if (data->GetBossState(BOSS_LEVIATHAN) != DONE && pInstance && pPlayer)
    {
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU(13910, pCreature->GetGUID());
    }
    else pPlayer->SEND_GOSSIP_MENU(1, pCreature->GetGUID());

    return true;
}

bool GossipSelect_keeper_norgannon(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    ScriptedInstance* pInstance = pCreature->GetInstanceData();
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            if (pPlayer)
                pPlayer->CLOSE_GOSSIP_MENU();
            if(Creature* Norgannon = Unit::GetCreature(*pCreature, pInstance ? pInstance->GetData64(DATA_NORGANNON) : 0))
                if(Norgannon->isAlive())
                    Norgannon->AI()->DoAction(ACTION_VEHICLE_RESPAWN);
            break;
    }
    return true;
}

struct mob_colossusAI : public ScriptedAI
{
    mob_colossusAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = me->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    int32 uiGroundSlamTimer;

    void Reset()
    {
        uiGroundSlamTimer = 12000;
    }
   
    void JustDied(Unit *victim)
    {
        outstring_log("JustDied");
        if (Creature* pLeviathan = Unit::GetCreature(*me, m_pInstance->GetData64(TYPE_LEVIATHAN)))
        {
            outstring_log("Creature* pLeviathan = Unit::GetCreature(*me, m_pInstance->GetData64(TYPE_LEVIATHAN))");
            if (pLeviathan->AI())
            {
                outstring_log("pLeviathan->AI()");
                pLeviathan->AI()->DoAction(INCREASE_COLOSSUS_COUNT);
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiGroundSlamTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_GROUND_SLAM);
            uiGroundSlamTimer = 12000;
        } else uiGroundSlamTimer -= diff;

        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_boss_flame_leviathan(Creature* pCreature)
{
    return new boss_flame_leviathanAI (pCreature);
}

CreatureAI* GetAI_boss_flame_leviathan_seat(Creature* pCreature)
{
    return new boss_flame_leviathan_seatAI (pCreature);
}

CreatureAI* GetAI_boss_flame_leviathan_defense_turret(Creature* pCreature)
{
    return new boss_flame_leviathan_defense_turretAI (pCreature);
}

CreatureAI* GetAI_boss_flame_leviathan_overload_device(Creature* pCreature)
{
    return new boss_flame_leviathan_overload_deviceAI (pCreature);
}

CreatureAI* GetAI_boss_flame_leviathan_safety_containerAI(Creature* pCreature)
{
    return new boss_flame_leviathan_safety_containerAI(pCreature);
}

CreatureAI* GetAI_spell_pool_of_tar(Creature* pCreature)
{
    return new spell_pool_of_tarAI (pCreature);
}

CreatureAI* GetAI_keeper_norgannon(Creature* pCreature)
{
    return new keeper_norgannonAI (pCreature);
}

CreatureAI* GetAI_mob_colossus(Creature* pCreature)
{
    return new mob_colossusAI(pCreature);
}

void AddSC_boss_flame_leviathan()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_flame_leviathan";
    newscript->GetAI = &GetAI_boss_flame_leviathan;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_flame_leviathan_seat";
    newscript->GetAI = &GetAI_boss_flame_leviathan_seat;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_flame_leviathan_defense_turret";
    newscript->GetAI = &GetAI_boss_flame_leviathan_defense_turret;
    newscript->RegisterSelf();


    newscript = new Script;
    newscript->Name = "boss_flame_leviathan_overload_device";
    newscript->GetAI = &GetAI_boss_flame_leviathan_overload_device;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_flame_leviathan_safety_container";
    newscript->GetAI = &GetAI_boss_flame_leviathan_safety_containerAI;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "spell_pool_of_tar";
    newscript->GetAI = &GetAI_spell_pool_of_tar;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name="npc_keeper_norgannon";
    newscript->pGossipHello =  &GossipHello_keeper_norgannon;
    newscript->pGossipSelect = &GossipSelect_keeper_norgannon;
    newscript->GetAI = &GetAI_keeper_norgannon;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mob_colossus";
    newscript->GetAI = &GetAI_mob_colossus;
    newscript->RegisterSelf();
}
