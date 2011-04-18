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

#include "ScriptedPch.h"
#include "ulduar.h"

// Any boss
#define SPELL_SUPERCHARGE   61920
#define SPELL_BERSERK       47008   // Hard enrage, don't know the correct ID.

// Steelbreaker
#define SPELL_HIGH_VOLTAGE                    RAID_MODE(61890,63498)
#define SPELL_FUSION_PUNCH                    RAID_MODE(61903,63493)
#define SPELL_STATIC_DISRUPTION               RAID_MODE(44008,63494)
#define SPELL_OVERWHELMING_POWER              RAID_MODE(64637,61888)
#define SPELL_ELECTRICAL_CHARGE               61902

// Runemaster Molgeim
#define SPELL_SHIELD_OF_RUNES                 RAID_MODE(62274,63489)
#define SPELL_RUNE_OF_POWER                   61973
#define SPELL_RUNE_OF_POWER_VISUAL            61974
#define SPELL_RUNE_OF_DEATH                   RAID_MODE(62269, 63490)
#define SPELL_RUNE_OF_SUMMONING               62273
#define SPELL_RUNE_OF_SUMMONING_VISUAL        62019
#define SPELL_RUNE_OF_SUMMONING_SUMMON        62020
#define SPELL_LIGHTNING_BLAST                 RAID_MODE(62054,63491)

// Stormcaller Brundir
#define SPELL_CHAIN_LIGHTNING                 RAID_MODE(61879,63479)
#define SPELL_OVERLOAD                        RAID_MODE(61869,63481)
#define SPELL_LIGHTNING_WHIRL                 RAID_MODE(61915,63483)
#define SPELL_LIGHTNING_TENDRILS              RAID_MODE(61887,63486)
#define SPELL_STORMSHIELD                     64187

enum eEnums
{
    EVENT_ENRAGE,
    // Steelbreaker
    EVENT_FUSION_PUNCH,
    EVENT_STATIC_DISRUPTION,
    EVENT_OVERWHELMING_POWER,
    // Molgeim
    EVENT_RUNE_OF_POWER,
    EVENT_SHIELD_OF_RUNES,
    EVENT_RUNE_OF_DEATH,
    EVENT_RUNE_OF_SUMMONING,
    EVENT_LIGHTNING_BLAST,
    // Brundir
    EVENT_CHAIN_LIGHTNING,
    EVENT_OVERLOAD,
    EVENT_LIGHTNING_WHIRL,
    EVENT_LIGHTNING_TENDRILS,
    EVENT_STORMSHIELD,
    EVENT_FLIGHT,
    EVENT_GROUND,
    EVENT_LAND,
    //rune of power
    EVENT_AURA,

    MAX_EVENT

};

enum Actions
{
    ACTION_STEELBREAKER                         = 0,
    ACTION_MOLGEIM                              = 1,
    ACTION_BRUNDIR                              = 2,
};

// Achievements
#define ACHIEVEMENT_ON_YOUR_SIDE              RAID_MODE(2945, 2946) // TODO
#define ACHIEVEMENT_CANT_WHILE_STUNNED        RAID_MODE(2947, 2948) // TODO
#define ACHIEVEMENT_CHOOSE_STEELBREAKER       RAID_MODE(2941, 2944)
#define ACHIEVEMENT_CHOOSE_MOLGEIM            RAID_MODE(2939, 2942)
#define ACHIEVEMENT_CHOOSE_BRUNDIR            RAID_MODE(2940, 2943)

//if (me->GetPower(POWER_MANA) == me->GetMaxPower(POWER_MANA)) Useful for this Achievement
//    pInstance->DoCompleteAchievement(ACHIEVEMENT_CANT_WHILE_STUNNED);

#define EMOTE_OVERLOAD    "Stormcaller Brundir begins to Overload!"

enum Yells
{
    SAY_STEELBREAKER_AGGRO                      = -1603020,
    SAY_STEELBREAKER_SLAY_1                     = -1603021,
    SAY_STEELBREAKER_SLAY_2                     = -1603022,
    SAY_STEELBREAKER_POWER                      = -1603023,
    SAY_STEELBREAKER_DEATH_1                    = -1603024,
    SAY_STEELBREAKER_DEATH_2                    = -1603025,
    SAY_STEELBREAKER_BERSERK                    = -1603026,

    SAY_MOLGEIM_AGGRO                           = -1603030,
    SAY_MOLGEIM_SLAY_1                          = -1603031,
    SAY_MOLGEIM_SLAY_2                          = -1603032,
    SAY_MOLGEIM_RUNE_DEATH                      = -1603033,
    SAY_MOLGEIM_SUMMON                          = -1603034,
    SAY_MOLGEIM_DEATH_1                         = -1603035,
    SAY_MOLGEIM_DEATH_2                         = -1603036,
    SAY_MOLGEIM_BERSERK                         = -1603037,

    SAY_BRUNDIR_AGGRO                           = -1603040,
    SAY_BRUNDIR_SLAY_1                          = -1603041,
    SAY_BRUNDIR_SLAY_2                          = -1603042,
    SAY_BRUNDIR_SPECIAL                         = -1603043,
    SAY_BRUNDIR_FLIGHT                          = -1603044,
    SAY_BRUNDIR_DEATH_1                         = -1603045,
    SAY_BRUNDIR_DEATH_2                         = -1603046,
    SAY_BRUNDIR_BERSERK                         = -1603047,
};

bool IsEncounterComplete(ScriptedInstance* pInstance, Creature* me)
{
   if (!pInstance || !me)
        return false;

    for (uint8 i = 0; i < 3; ++i)
    {
        uint64 guid = pInstance->GetData64(DATA_STEELBREAKER+i);
        if (!guid)
            return false;

        if (Creature *boss = (Unit::GetCreature((*me), guid)))
        {
            if (boss->isAlive())
                return false;

            continue;
        }
        else
            return false;
    }
    return true;
}

// Avoid killing bosses one to one
void CallBosses(ScriptedInstance *pInstance, uint32 caller, Unit *who) {
   
    for (uint8 i = 0; i < 3; ++i)
    {
        if (caller == DATA_STEELBREAKER+i) continue;
        uint64 guid = pInstance->GetData64(DATA_STEELBREAKER+i);
        if (!guid) return;
        if (Creature* m_boss = pInstance->instance->GetCreature(guid))
        {
            if (m_boss->isAlive())
            {
                m_boss->AddThreat(who, 100.0f);
                m_boss->AI()->AttackStart(who);
            }
        }
    }
}

struct boss_steelbreakerAI : public ScriptedAI
{
    boss_steelbreakerAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }

    void Reset()
    {
        events.Reset();
        phase = 0;
        me->RemoveAllAuras();
        if (pInstance)
            pInstance->SetBossState(TYPE_ASSEMBLY, NOT_STARTED);
           
        // Respawn
        if (Creature* Brundir = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_BRUNDIR) : 0))
            if (Brundir->isDead())
            {
                Brundir->Respawn(true);
                Brundir->GetMotionMaster()->MoveTargetedHome();
            }

        if (Creature* Molgeim = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MOLGEIM) : 0))
            if (Molgeim->isDead())
            {
                Molgeim->Respawn(true);
                Molgeim->GetMotionMaster()->MoveTargetedHome();
            }
    }


    EventMap events;
    ScriptedInstance* pInstance;
    uint32 phase;

    void EnterCombat(Unit *who)
    {
        DoScriptText(SAY_STEELBREAKER_AGGRO, me);
        DoZoneInCombat();
        CallBosses(pInstance, DATA_STEELBREAKER, who);
        DoCast(me, SPELL_HIGH_VOLTAGE);
        phase = 1;
        events.SetPhase(phase);
        events.ScheduleEvent(EVENT_ENRAGE, 900000);
        events.ScheduleEvent(EVENT_FUSION_PUNCH, 15000);
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(RAND(SAY_STEELBREAKER_DEATH_1, SAY_STEELBREAKER_DEATH_2), me);
   
        if (IsEncounterComplete(pInstance, me) && pInstance)
        {
            pInstance->SetBossState(TYPE_ASSEMBLY, DONE);
            pInstance->DoCompleteAchievement(ACHIEVEMENT_CHOOSE_STEELBREAKER);
        }
        else me->SetLootRecipient(0);
           
        if (Creature* Brundir = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_BRUNDIR) : 0))
            if (Brundir->isAlive())
                Brundir->AI()->DoAction(ACTION_BRUNDIR);

        if (Creature* Molgeim = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MOLGEIM) : 0))
            if (Molgeim->isAlive())
                Molgeim->AI()->DoAction(ACTION_MOLGEIM);
    }

    void KilledUnit(Unit *who)
    {
        DoScriptText(RAND(SAY_STEELBREAKER_SLAY_1, SAY_STEELBREAKER_SLAY_2), me);
   
        if (phase == 3)
            DoCast(me, SPELL_ELECTRICAL_CHARGE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ENRAGE:
                    DoScriptText(SAY_STEELBREAKER_BERSERK, me);
                    DoCast(SPELL_BERSERK);
                break;
                case EVENT_FUSION_PUNCH:
                    DoCastVictim(SPELL_FUSION_PUNCH);
                    events.ScheduleEvent(EVENT_FUSION_PUNCH, urand(15000, 20000));
                break;
                case EVENT_STATIC_DISRUPTION:
                {
                    if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_STATIC_DISRUPTION);
                    events.ScheduleEvent(EVENT_STATIC_DISRUPTION, 20000 + (rand()%20)*1000);
                }
                break;
                case EVENT_OVERWHELMING_POWER:
                    DoScriptText(SAY_STEELBREAKER_POWER, me);
                    DoCastVictim(SPELL_OVERWHELMING_POWER);
                    events.ScheduleEvent(EVENT_OVERWHELMING_POWER, RAID_MODE(60000, 35000));
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
   
    void DoAction(const int32 action)
    {
        switch (action)
        {
            case ACTION_STEELBREAKER:
                me->SetHealth(me->GetMaxHealth());
                me->AddAura(SPELL_SUPERCHARGE, me);
                ++phase;
                events.SetPhase(phase);
                if (phase >= 2)
                events.RescheduleEvent(EVENT_STATIC_DISRUPTION, 30000);
                if (phase >= 3)
                events.RescheduleEvent(EVENT_OVERWHELMING_POWER, urand(2000, 5000));
                break;
        }
    }
};

struct boss_runemaster_molgeimAI : public ScriptedAI
{
    boss_runemaster_molgeimAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }

    void Reset()
    {
        if (pInstance)
            pInstance->SetBossState(TYPE_ASSEMBLY, NOT_STARTED);
        events.Reset();
        me->RemoveAllAuras();
        phase = 0;
       
        // Respawn
        if (Creature* Brundir = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_BRUNDIR) : 0))
            if (Brundir->isDead())
            {
                Brundir->Respawn(true);
                Brundir->GetMotionMaster()->MoveTargetedHome();
            }

        if (Creature* Steelbreaker = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_STEELBREAKER) : 0))
            if (Steelbreaker->isDead())
            {            
                Steelbreaker->Respawn(true);
                Steelbreaker->GetMotionMaster()->MoveTargetedHome();
            }
    }

    ScriptedInstance* pInstance;
    EventMap events;
    uint32 phase;

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_MOLGEIM_AGGRO, me);
        DoZoneInCombat();
        CallBosses(pInstance, DATA_MOLGEIM, who);
        phase = 1;
        pInstance->SetBossState(TYPE_ASSEMBLY, IN_PROGRESS);
        events.ScheduleEvent(EVENT_ENRAGE, 900000);
        events.ScheduleEvent(EVENT_SHIELD_OF_RUNES, 30000);
        events.ScheduleEvent(EVENT_RUNE_OF_POWER, 20000);
    }
           
    void JustDied(Unit* Killer)
    {
        DoScriptText(RAND(SAY_MOLGEIM_DEATH_1, SAY_MOLGEIM_DEATH_2), me);
   
        if (IsEncounterComplete(pInstance, me) && pInstance)
        {
            pInstance->SetBossState(TYPE_ASSEMBLY, DONE);
            pInstance->DoCompleteAchievement(ACHIEVEMENT_CHOOSE_MOLGEIM);
        }
        else me->SetLootRecipient(0);
           
        if (Creature* Brundir = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_BRUNDIR) : 0))
            if (Brundir->isAlive())
                Brundir->AI()->DoAction(ACTION_BRUNDIR);

        if (Creature* Steelbreaker = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_STEELBREAKER) : 0))
            if (Steelbreaker->isAlive())
                Steelbreaker->AI()->DoAction(ACTION_STEELBREAKER);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ENRAGE:
                    DoScriptText(SAY_MOLGEIM_BERSERK, me);
                    DoCast(SPELL_BERSERK);
                break;
                case EVENT_RUNE_OF_POWER: // random alive friendly
                {
                    Creature* bosschoosed;
                    uint32 choice = urand(0,2);

                    if (!pInstance) break;
                   
                    bosschoosed = Unit::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER+choice));

                    if (!bosschoosed || !bosschoosed->isAlive()) {
                        choice = ((choice == 2) ? 0 : choice++);
                        bosschoosed = Unit::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER+choice));
                        if (!bosschoosed || !bosschoosed->isAlive()) {
                            choice = ((choice == 2) ? 0 : choice++);
                            bosschoosed = Unit::GetCreature(*me, pInstance->GetData64(DATA_STEELBREAKER+choice));
                        }
                    }

                    if (!bosschoosed || !bosschoosed->isAlive())
                        break;
                   
                    DoCast(bosschoosed, SPELL_RUNE_OF_POWER);
                    events.ScheduleEvent(EVENT_RUNE_OF_POWER, 35000);
                }
                break;
                case EVENT_SHIELD_OF_RUNES:
                    DoCast(me, SPELL_SHIELD_OF_RUNES);
                    events.ScheduleEvent(EVENT_SHIELD_OF_RUNES, urand(60000, 80000));
                break;
                case EVENT_RUNE_OF_DEATH:
                {
                    DoScriptText(SAY_MOLGEIM_RUNE_DEATH, me);
                    if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_RUNE_OF_DEATH);
                    events.ScheduleEvent(EVENT_RUNE_OF_DEATH, 30000);
                }
                break;
                case EVENT_RUNE_OF_SUMMONING:
                {
                    DoScriptText(SAY_MOLGEIM_SUMMON, me);
                    if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_RUNE_OF_SUMMONING);
                    events.ScheduleEvent(EVENT_RUNE_OF_SUMMONING, urand(40000, 50000));
                }
                break;
               
            }
        }


        DoMeleeAttackIfReady();
    }
   
    void KilledUnit(Unit *who)
    {
        DoScriptText(RAND(SAY_MOLGEIM_SLAY_1, SAY_MOLGEIM_SLAY_2), me);
    }
   
    void DoAction(const int32 action)
    {
        switch (action)
        {
            case ACTION_MOLGEIM:
                me->SetHealth(me->GetMaxHealth());
                me->AddAura(SPELL_SUPERCHARGE, me);
                ++phase;
                events.SetPhase(phase);
                events.RescheduleEvent(EVENT_SHIELD_OF_RUNES, 30000);
                events.RescheduleEvent(EVENT_RUNE_OF_POWER, 20000);
                if (phase >= 2)
                    events.RescheduleEvent(EVENT_RUNE_OF_DEATH, 35000);
                if (phase >= 3)
                    events.RescheduleEvent(EVENT_RUNE_OF_SUMMONING, 40000);
                break;
        }
    }
};

struct boss_stormcaller_brundirAI : public ScriptedAI
{
    boss_stormcaller_brundirAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }

    void Reset()
    {
        if (pInstance)
            pInstance->SetBossState(TYPE_ASSEMBLY, NOT_STARTED);
        me->RemoveAllAuras();
        events.Reset();
        phase = 0;
       
        // Respawn
        if (Creature* Molgeim = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MOLGEIM) : 0))
            if (Molgeim->isDead())
            {
                Molgeim->Respawn(true);
                Molgeim->GetMotionMaster()->MoveTargetedHome();
            }

        if (Creature* Steelbreaker = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_STEELBREAKER) : 0))
            if (Steelbreaker->isDead())
            {            
                Steelbreaker->Respawn(true);
                Steelbreaker->GetMotionMaster()->MoveTargetedHome();
            }
    }

    EventMap events;
    ScriptedInstance* pInstance;
    uint32 phase;

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_BRUNDIR_AGGRO, me);
        DoZoneInCombat();
        CallBosses(pInstance, DATA_BRUNDIR, who);
        phase = 1;
        events.ScheduleEvent(EVENT_ENRAGE, 900000);
        events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, 2000);
        events.ScheduleEvent(EVENT_OVERLOAD, urand(60000, 120000));
    }

    void JustDied(Unit* Killer)
    {
        DoScriptText(RAND(SAY_BRUNDIR_DEATH_1, SAY_BRUNDIR_DEATH_2), me);
   
        if (IsEncounterComplete(pInstance, me) && pInstance)
        {
            pInstance->SetBossState(TYPE_ASSEMBLY, DONE);
            pInstance->DoCompleteAchievement(ACHIEVEMENT_CHOOSE_BRUNDIR);            
        }
        else me->SetLootRecipient(0);
           
        if (Creature* Molgeim = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_MOLGEIM) : 0))
            if (Molgeim->isAlive())
                Molgeim->AI()->DoAction(ACTION_MOLGEIM);

        if (Creature* Steelbreaker = Unit::GetCreature(*me, pInstance ? pInstance->GetData64(DATA_STEELBREAKER) : 0))
            if (Steelbreaker->isAlive())
                Steelbreaker->AI()->DoAction(ACTION_STEELBREAKER);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
           
        if (me->hasUnitState(UNIT_STAT_CASTING))
            return;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch (eventId)
            {
                case EVENT_ENRAGE:
                    DoScriptText(SAY_BRUNDIR_BERSERK, me);
                    DoCast(SPELL_BERSERK);
                break;
                case EVENT_CHAIN_LIGHTNING:
                {
                    if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        DoCast(pTarget, SPELL_CHAIN_LIGHTNING);
                    events.ScheduleEvent(EVENT_CHAIN_LIGHTNING, urand(6000, 12000));
                }
                break;
                case EVENT_OVERLOAD:
                    me->MonsterTextEmote(EMOTE_OVERLOAD, 0, true);
                    DoScriptText(SAY_BRUNDIR_SPECIAL, me);
                    DoCast(SPELL_OVERLOAD);
                    events.ScheduleEvent(EVENT_OVERLOAD, urand(60000, 120000));
                break;
                case EVENT_LIGHTNING_WHIRL:
                    DoCast(SPELL_LIGHTNING_WHIRL);
                    events.ScheduleEvent(EVENT_LIGHTNING_WHIRL, urand(15000, 20000));
                break;
                case EVENT_LIGHTNING_TENDRILS:
                    DoScriptText(SAY_BRUNDIR_FLIGHT, me);
                    DoCast(SPELL_LIGHTNING_TENDRILS);
                    me->SetReactState(REACT_PASSIVE);
                    me->AttackStop();
                    DoResetThreat();
                    me->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                    me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 12);
                    events.ScheduleEvent(EVENT_FLIGHT, 2500);
                    events.ScheduleEvent(EVENT_LIGHTNING_TENDRILS, 90000);
                break;
                case EVENT_FLIGHT:
                    me->GetMotionMaster()->MoveConfused();
                    events.CancelEvent(EVENT_FLIGHT);
                    events.ScheduleEvent(EVENT_LAND, 22000);
                break;
                case EVENT_LAND:
                    me->GetMotionMaster()->Clear(true);
                    me->GetMotionMaster()->MovePoint(0, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() - 12);
                    events.CancelEvent(EVENT_LAND);
                    events.ScheduleEvent(EVENT_GROUND, 2500);
                break;
                case EVENT_GROUND:
                    me->RemoveUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                    me->SetReactState(REACT_AGGRESSIVE);
                    me->RemoveAurasDueToSpell(SPELL_LIGHTNING_TENDRILS);
                    events.CancelEvent(EVENT_GROUND);
                break;
            }
        }

        DoMeleeAttackIfReady();
    }
   
    void KilledUnit(Unit *who)
    {
        DoScriptText(RAND(SAY_BRUNDIR_SLAY_1, SAY_BRUNDIR_SLAY_2), me);
    }

    void DoAction(const int32 action)
    {
        switch (action)
        {
            case ACTION_BRUNDIR:
                me->SetHealth(me->GetMaxHealth());
                me->AddAura(SPELL_SUPERCHARGE, me);
                ++phase;
                events.SetPhase(phase);
                events.RescheduleEvent(EVENT_CHAIN_LIGHTNING, urand(6000, 12000));
                events.RescheduleEvent(EVENT_OVERLOAD, 40000);
                if (phase >= 2)
                    events.RescheduleEvent(EVENT_LIGHTNING_WHIRL, urand(15000, 20000));
                if (phase >= 3)
                {
                    DoCast(me, SPELL_STORMSHIELD);
                    events.RescheduleEvent(EVENT_LIGHTNING_TENDRILS, 60000);
                }
                break;
        }
    }
};

/***************
*  mob_lightning_elemental
*****************/

struct mob_lightning_elementalAI : public ScriptedAI {
    mob_lightning_elementalAI(Creature *c) : ScriptedAI(c) {}
   
    Unit* Target;
    uint32 DespawnTimer;
    bool Casted;


    void Reset()
    {
        DespawnTimer = 120000;
        Casted = false;
        me->GetMotionMaster()->MoveRandom(30);
    }

    void UpdateAI(const uint32 diff)
    {
        if (me->IsWithinMeleeRange(me->getVictim()) && !Casted)
        {
            me->CastSpell(me, SPELL_LIGHTNING_BLAST, true);
            DespawnTimer = 500;
            Casted = true;
        }
       
        // To take time for visual SPELL_LIGHTNING_BLAST before despawning
        if (DespawnTimer <= diff)
            me->ForcedDespawn();
        else DespawnTimer -= diff;
    }
};
/***************
*  mob_rune_of_summoning
*****************/
struct mob_rune_of_summoningAI : public ScriptedAI
{
    mob_rune_of_summoningAI(Creature *c) : ScriptedAI(c)
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_DISABLE_MOVE);
        me->SetReactState(REACT_PASSIVE);
    }

    uint32 SummonTimer;
    uint32 DespawnTimer;

    void Reset()
    {
        SummonTimer = 1500;
        DespawnTimer = 12500;
        DoCast(me, SPELL_RUNE_OF_SUMMONING_VISUAL);
    }

    void UpdateAI(const uint32 uiDiff)
    {

        if (SummonTimer <= uiDiff)
        {
            DoCast(me, SPELL_RUNE_OF_SUMMONING_SUMMON);
            SummonTimer = 1500;
        }
        else SummonTimer -= uiDiff;

        if (DespawnTimer <= uiDiff)
            me->ForcedDespawn();
        else DespawnTimer -= uiDiff;
    }
};

/***************
*  mob_rune_of_power
*****************/
struct mob_rune_of_powerAI : public ScriptedAI
{
    mob_rune_of_powerAI(Creature *c) : ScriptedAI(c)  
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
    }
   
    uint32 DespawnTimer;

    void Reset()
    {
        DoCast(me, SPELL_RUNE_OF_POWER_VISUAL, true);
        DespawnTimer = 35000;
    }
   
    void UpdateAI(const uint32 uiDiff)
    {
        if (DespawnTimer <= uiDiff)
            me->ForcedDespawn();
        else DespawnTimer -= uiDiff;
    }
};


CreatureAI* GetAI_boss_steelbreaker(Creature* pCreature)
{
    return new boss_steelbreakerAI (pCreature);
}

CreatureAI* GetAI_boss_runemaster_molgeim(Creature* pCreature)
{
    return new boss_runemaster_molgeimAI (pCreature);
}

CreatureAI* GetAI_boss_stormcaller_brundir(Creature* pCreature)
{
    return new boss_stormcaller_brundirAI (pCreature);
}

CreatureAI* GetAI_mob_lightning_elemental(Creature* pCreature)
{
    return new mob_lightning_elementalAI (pCreature);
}

CreatureAI* GetAI_mob_rune_of_summoning(Creature* pCreature)
{
    return new mob_rune_of_summoningAI (pCreature);
}

CreatureAI* GetAI_mob_rune_of_power(Creature* pCreature)
{
    return new mob_rune_of_powerAI (pCreature);
}

void AddSC_boss_assembly_of_iron()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_steelbreaker";
    newscript->GetAI = &GetAI_boss_steelbreaker;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_runemaster_molgeim";
    newscript->GetAI = &GetAI_boss_runemaster_molgeim;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_stormcaller_brundir";
    newscript->GetAI = &GetAI_boss_stormcaller_brundir;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_lightning_elemental";
    newscript->GetAI = &GetAI_mob_lightning_elemental;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_rune_of_summoning";
    newscript->GetAI = &GetAI_mob_rune_of_summoning;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_rune_of_power";
    newscript->GetAI = &GetAI_mob_rune_of_power;
    newscript->RegisterSelf();

}
