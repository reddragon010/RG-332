/*
* Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
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

/* Script Data Start
SDName: Boss novos
SDAuthor: Tartalo
SD%Complete: 100
SDComment:
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = 'boss_novos' where entry = '';
*** SQL END ***/
#include "ScriptedPch.h"
#include "drak_tharon_keep.h"

enum Spells
{
    SPELL_ARCANE_BLAST                        = 49198,
    H_SPELL_ARCANE_BLAST                      = 59909,
    SPELL_ARCANE_FIELD                        = 47346,
    SPELL_BLIZZARD                            = 49034,
    H_SPELL_BLIZZARD                          = 59854,
    SPELL_FROSTBOLT                           = 49037,
    H_SPELL_FROSTBOLT                         = 59855,
    SPELL_WRATH_OF_MISERY                     = 50089,
    H_SPELL_WRATH_OF_MISERY                   = 59856,
    SPELL_SUMMON_MINIONS                      = 59910, //Summons an army of Fetid Troll Corpses to assist the caster.
    SPELL_FLASH_OF_DARKNESS                   = 49668,
    H_SPELL_FLASH_OF_DARKNESS                 = 59004,
    SPELL_SHADOW_BOLT                         = 51363,
    H_SPELL_SHADOW_BOLT                       = 59016,
//    Summon_Risen_Shadowcaster                 = 49105,
//    Summon_Crystal_Handler                    = 49179,
};
//not in db
enum Yells
{
    SAY_AGGRO                              = -1600000,
    SAY_KILL                               = -1600001,
    SAY_DEATH                              = -1600002,
    SAY_NECRO_ADD                          = -1600003,
    SAY_REUBBLE_1                          = -1600004,
    SAY_REUBBLE_2                          = -1600005
};
enum Creatures
{
    CREATURE_RISEN_SHADOWCASTER            = 27600,
    CREATURE_FETID_TROLL_CORPSE            = 27598,
    CREATURE_HULKING_CORPSE                = 27597,
    CREATURE_CRYSTAL_HANDLER               = 26627,
    CREATURE_ROTTED_TROLL_CORPSE           = 32786
};
enum CombatPhase
{
    IDLE,
    PHASE_1,
    PHASE_2
};
enum Achievements
{
    ACHIEV_OH_NOVOS                        = 2057
};

static Position AddSpawnPoint = { -379.20, -816.76, 59.70};
static Position CrystalHandlerSpawnPoint = { -326.626343, -709.956604, 27.813314 };
static Position AddDestinyPoint = { -379.314545, -772.577637, 28.58837 };

struct boss_novosAI : public Scripted_NoMovementAI
{
    boss_novosAI(Creature *c) : Scripted_NoMovementAI(c), lSummons(me)
    {
        pInstance = c->GetInstanceData();
        Reset();
    }

    uint32 uiTimer;
    int32 iSummonMinionsTimer;
    int32 iCrystalHandlerTimer;
    int32 iBlizzardTimer;
    int32 iWrathOfMiseryTimer;


    bool bAchiev;
    bool summonMinions;

    SummonList lSummons;

    std::list<uint64> luiCrystals;

    CombatPhase Phase;

    ScriptedInstance* pInstance;

    void Reset()
    {
        Phase = IDLE;
        luiCrystals.clear();
        bAchiev = true;
        summonMinions = true;
        m_creature->CastStop();
        lSummons.DespawnAll();

        if (pInstance)
        {
            pInstance->SetData(DATA_NOVOS_EVENT, NOT_STARTED);
            luiCrystals.push_back(pInstance->GetData64(DATA_NOVOS_CRYSTAL_1));
            luiCrystals.push_back(pInstance->GetData64(DATA_NOVOS_CRYSTAL_2));
            luiCrystals.push_back(pInstance->GetData64(DATA_NOVOS_CRYSTAL_3));
            luiCrystals.push_back(pInstance->GetData64(DATA_NOVOS_CRYSTAL_4));
            for (std::list<uint64>::iterator itr = luiCrystals.begin(); itr != luiCrystals.end(); ++itr)
            {
                if (GameObject* pTemp = pInstance->instance->GetGameObject(*itr))
                    pTemp->SetGoState(GO_STATE_READY);
            }
        }
    }
    
    void EnterCombat(Unit* who)
    {
        Reset();
        DoScriptText(SAY_AGGRO, m_creature);
        Phase = PHASE_1;
        iCrystalHandlerTimer = 30*IN_MILISECONDS;

        uiTimer = 1*IN_MILISECONDS;
        iSummonMinionsTimer = 2*IN_MILISECONDS;
        iBlizzardTimer = urand(15*IN_MILISECONDS, 20*IN_MILISECONDS);
        iWrathOfMiseryTimer = urand(10*IN_MILISECONDS, 15*IN_MILISECONDS);
        DoCast(SPELL_ARCANE_FIELD);
        if (pInstance)
        {
            for (std::list<uint64>::iterator itr = luiCrystals.begin(); itr != luiCrystals.end(); ++itr)
            {
                if (GameObject *pTemp = pInstance->instance->GetGameObject(*itr))
                    pTemp->SetGoState(GO_STATE_ACTIVE);
            }
            pInstance->SetData(DATA_NOVOS_EVENT, IN_PROGRESS);
        }
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateCombatState())
            return;
        switch (Phase)
        {
            case PHASE_1:
                if (uiTimer <= diff)
                {
                    Creature *pSummon = m_creature->SummonCreature(RAND(CREATURE_FETID_TROLL_CORPSE,CREATURE_HULKING_CORPSE,CREATURE_RISEN_SHADOWCASTER), AddSpawnPoint, TEMPSUMMON_CORPSE_TIMED_DESPAWN,20*IN_MILISECONDS);
                    pSummon->GetMotionMaster()->MovePoint(0, AddDestinyPoint);
                    //If spell is casted stops casting arcane field so no spell casting
                    //DoCast(m_creature, SPELL_SUMMON_MINIONS);
                    uiTimer = 3*IN_MILISECONDS;

                } else uiTimer -= diff;
                if (iCrystalHandlerTimer <= diff)

                {
                    //TODO: say
                    DoScriptText(SAY_NECRO_ADD, m_creature);
                    Creature *pCrystalHandler = m_creature->SummonCreature(CREATURE_CRYSTAL_HANDLER, CrystalHandlerSpawnPoint, TEMPSUMMON_CORPSE_TIMED_DESPAWN,20*IN_MILISECONDS);
                    pCrystalHandler->GetMotionMaster()->MovePoint(0, AddDestinyPoint);
                    iCrystalHandlerTimer = urand(20*IN_MILISECONDS,30*IN_MILISECONDS);
                } else iCrystalHandlerTimer -= diff;


                break;
            case PHASE_2:
                if (!me->IsNonMeleeSpellCasted(false))
                {
                    if (iSummonMinionsTimer <= (int32)diff)
                    {
                        if (summonMinions)
                        {
                            DoCast(SPELL_SUMMON_MINIONS);
                            summonMinions = false;
                        }
                        if (!me->IsNonMeleeSpellCasted(false))
                        {
                            for (uint8 i = 0; i <=5; ++i)
                            {
                                if (Creature* creature = me->SummonCreature(CREATURE_ROTTED_TROLL_CORPSE, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ(), TEMPSUMMON_CORPSE_DESPAWN))
                                {
                                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, true))
                                        creature->Attack(pTarget, true);
                                }
                            }
                            summonMinions = true;
                            iSummonMinionsTimer = urand(30*IN_MILISECONDS,40*IN_MILISECONDS);
                        }
                    } else 
                    if (iBlizzardTimer <= (int32)diff)
                    {
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(pTarget, DUNGEON_MODE(SPELL_BLIZZARD, H_SPELL_BLIZZARD));

                        iBlizzardTimer = urand(15*IN_MILISECONDS,20*IN_MILISECONDS);
                    } else 
                    if (iWrathOfMiseryTimer <= (int32)diff)

                    {
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(pTarget, DUNGEON_MODE(SPELL_WRATH_OF_MISERY, H_SPELL_WRATH_OF_MISERY));

                        iWrathOfMiseryTimer = urand(10*IN_MILISECONDS, 15*IN_MILISECONDS);
                    } else 
                    if (!me->IsNonMeleeSpellCasted(false))
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                            DoCast(pTarget, DUNGEON_MODE(SPELL_FROSTBOLT, H_SPELL_FROSTBOLT));
                }
                iSummonMinionsTimer -= diff;
                iBlizzardTimer -= diff;
                iWrathOfMiseryTimer -= diff;
                break;
        }
    }
    
    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, m_creature);
        if (pInstance)
        {
            pInstance->SetData(DATA_NOVOS_EVENT, DONE);

            if (IsHeroic() && bAchiev)
                pInstance->DoCompleteAchievement(ACHIEV_OH_NOVOS);
        }
        lSummons.DespawnAll();
    }

    void KilledUnit(Unit *victim)
    {
        if (victim == m_creature)
            return;
        DoScriptText(SAY_KILL, m_creature);
    }

    void JustSummoned(Creature *summon)
    {
        lSummons.Summon(summon);
    }

    void RemoveCrystal()
    {
        if (!luiCrystals.empty())
        {
            if (pInstance)
                if (GameObject *pTemp = pInstance->instance->GetGameObject(luiCrystals.back()))
                    pTemp->SetGoState(GO_STATE_READY);
            luiCrystals.pop_back();
        }
        if (luiCrystals.empty())
        {
            m_creature->CastStop();
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            Phase = PHASE_2;
            uiTimer = 1*IN_MILISECONDS;

        }
    }

	Unit* GetRandomTarget()
	{
		return SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true);
	}
};

struct mob_crystal_handlerAI : public ScriptedAI
{
    mob_crystal_handlerAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }

    uint32 uiFlashOfDarknessTimer;

    ScriptedInstance *pInstance;

    void EnterCombat(Unit *who)

    {
        uiFlashOfDarknessTimer = 5*IN_MILISECONDS;
    }
    
    void JustDied(Unit* killer)
    {
        if (Creature* pNovos = Unit::GetCreature(*m_creature, pInstance ? pInstance->GetData64(DATA_NOVOS) : 0))
            CAST_AI(boss_novosAI,pNovos->AI())->RemoveCrystal();
    }
    
    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
            
        if (uiFlashOfDarknessTimer <= diff)
        {
            DoCastVictim(DUNGEON_MODE(SPELL_FLASH_OF_DARKNESS, H_SPELL_FLASH_OF_DARKNESS));
            uiFlashOfDarknessTimer = urand(10*IN_MILISECONDS,15*IN_MILISECONDS);
        } else uiFlashOfDarknessTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

struct mob_novos_minionAI : public ScriptedAI
{
    mob_novos_minionAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = c->GetInstanceData();
    }

    ScriptedInstance *pInstance;

    uint32 uiTimer;
    
    void Reset()
    {
        uiTimer = 10*IN_MILISECONDS;
    }
    
    void EnterCombat(Unit *who)
    {
        uiTimer = 1*IN_MILISECONDS;
    }
    
    void MovementInform(uint32 type, uint32 id)
    {
        if(type != POINT_MOTION_TYPE)
            return;
        if (Creature* pNovos = Unit::GetCreature(*m_creature, pInstance ? pInstance->GetData64(DATA_NOVOS) : 0))
        {
            CAST_AI(boss_novosAI, pNovos->AI())->bAchiev = false;
            if (Unit *pTarget = CAST_AI(boss_novosAI, pNovos->AI())->GetRandomTarget())
                AttackStart(pTarget);
        }
    }
    
    void UpdateAI(const uint32 diff)
    {
        if (!UpdateCombatState())
            return;
            
        if (me->GetEntry() == CREATURE_RISEN_SHADOWCASTER)
        {
            if (uiTimer <= diff)
            {
                DoCastVictim(DUNGEON_MODE(SPELL_SHADOW_BOLT, H_SPELL_SHADOW_BOLT));
                uiTimer = urand(5*IN_MILISECONDS,8*IN_MILISECONDS);
            } else uiTimer -= diff;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_novos(Creature* pCreature)
{
    return new boss_novosAI (pCreature);
}

CreatureAI* GetAI_mob_crystal_handler(Creature* pCreature)
{
    return new mob_crystal_handlerAI (pCreature);
}

CreatureAI* GetAI_mob_novos_minion(Creature* pCreature)
{
    return new mob_novos_minionAI (pCreature);
}

void AddSC_boss_novos()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_novos";
    newscript->GetAI = &GetAI_boss_novos;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_crystal_handler";
    newscript->GetAI = &GetAI_mob_crystal_handler;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_novos_minion";
    newscript->GetAI = &GetAI_mob_novos_minion;
    newscript->RegisterSelf();
}
