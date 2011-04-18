/*
 * Copyright (C) 2008 - 2010 Trinity <http://www.trinitycore.org/>
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
#include "naxxramas.h"

//Stalagg
enum StalaggYells
{
    SAY_STAL_AGGRO          = -1533023, //not used
    SAY_STAL_SLAY           = -1533024, //not used
    SAY_STAL_DEATH          = -1533025  //not used
};

enum StalagSpells
{
    SPELL_POWERSURGE        = 28134,
    H_SPELL_POWERSURGE      = 54529,
    SPELL_MAGNETIC_PULL     = 28338,
    SPELL_STALAGG_TESLA     = 28097
};

//Feugen
enum FeugenYells
{
    SAY_FEUG_AGGRO          = -1533026, //not used
    SAY_FEUG_SLAY           = -1533027, //not used
    SAY_FEUG_DEATH          = -1533028 //not used
};

enum FeugenSpells
{
    SPELL_STATICFIELD       = 28135,
    H_SPELL_STATICFIELD     = 54528,
    SPELL_FEUGEN_TESLA      = 28109
};

// Thaddius DoAction
enum ThaddiusActions
{
    ACTION_FEUGEN_RESET,
    ACTION_FEUGEN_DIED,
    ACTION_STALAGG_RESET,
    ACTION_STALAGG_DIED
};

//generic
#define C_TESLA_COIL            16218           //the coils (emotes "Tesla Coil overloads!")

enum TeslaSpells
{
    SPELL_SHOCK                 = 28099,
    SPELL_STALAGG_CHAIN         = 28096,
    SPELL_STALAGG_TESLA_PASSIVE = 28097,
    SPELL_FEUGEN_TESLA_PASSIVE  = 28109,
    SPELL_FEUGEN_CHAIN          = 28111
};

//Thaddius
enum ThaddiusYells
{
    SAY_GREET               = -1533029, //not used
    SAY_AGGRO_1             = -1533030,
    SAY_AGGRO_2             = -1533031,
    SAY_AGGRO_3             = -1533032,
    SAY_SLAY                = -1533033,
    SAY_ELECT               = -1533034, //not used
    SAY_DEATH               = -1533035,
    SAY_SCREAM1             = -1533036, //not used
    SAY_SCREAM2             = -1533037, //not used
    SAY_SCREAM3             = -1533038, //not used
    SAY_SCREAM4             = -1533039 //not used
};

enum ThaddiusSpells
{
    SPELL_POLARITY_SHIFT        = 28089,
    SPELL_BALL_LIGHTNING        = 28299,
    SPELL_POSITIVE_CHARGE       = 29659,
    SPELL_NEGATIVE_CHARGE       = 29660,
    SPELL_CHAIN_LIGHTNING       = 28167,
    H_SPELL_CHAIN_LIGHTNING     = 54531,
    SPELL_BERSERK               = 27680
//   SPELL_THADIUS_SPAWN       = 28160,
};

enum Events
{
    EVENT_NONE,
    EVENT_SHIFT,
    EVENT_CHAIN,
    EVENT_BERSERK,
};

struct boss_thaddiusAI : public BossAI
{
    boss_thaddiusAI(Creature *c) : BossAI(c, BOSS_THADDIUS)
    {
        // init is a bit tricky because thaddius shall track the life of both adds, but not if there was a wipe
        // and, in particular, if there was a crash after both adds were killed (should not respawn)

        // Moreover, the adds may not yet be spawn. So just track down the status if mob is spawn
        // and each mob will send its status at reset (meaning that it is alive)
        checkFeugenAlive = false;
        if (Creature *pFeugen = m_creature->GetCreature(*m_creature, instance->GetData64(DATA_FEUGEN)))
            checkFeugenAlive = pFeugen->isAlive();

        checkStalaggAlive = false;
        if (Creature *pStalagg = m_creature->GetCreature(*m_creature, instance->GetData64(DATA_STALAGG)))
            checkStalaggAlive = pStalagg->isAlive();

        if (!checkFeugenAlive && !checkStalaggAlive)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
            me->SetReactState(REACT_AGGRESSIVE);
        }
        else
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
            me->SetReactState(REACT_PASSIVE);
        }
    }

    bool checkStalaggAlive;
    bool checkFeugenAlive;
    uint32 uiAddsTimer;

    void KilledUnit(Unit* victim)
    {
        if (!(rand()%5))
            DoScriptText(SAY_SLAY, me);
    }

    void JustDied(Unit* Killer)
    {
        _JustDied();
        DoScriptText(SAY_DEATH, me);
        if (InstanceData *pInstance = me->GetInstanceData())
        {
            pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_POSITIVE_CHARGE);
            pInstance->DoRemoveAurasDueToSpellOnPlayers(SPELL_NEGATIVE_CHARGE);
        }
    }

    void DoAction(const int32 action)
    {
        switch(action)
        {
            case ACTION_FEUGEN_RESET:
                checkFeugenAlive = true;
                break;
            case ACTION_FEUGEN_DIED:
                checkFeugenAlive = false;
                break;
            case ACTION_STALAGG_RESET:
                checkStalaggAlive = true;
                break;
            case ACTION_STALAGG_DIED:
                checkStalaggAlive = false;
                break;
        }

        if (!checkFeugenAlive && !checkStalaggAlive)
        {
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
            // REACT_AGGRESSIVE only reset when he takes damage.
            DoZoneInCombat();
        }
        else
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_STUNNED);
            me->SetReactState(REACT_PASSIVE);
        }
    }

    void EnterCombat(Unit *who)
    {
        _EnterCombat();
        DoScriptText(RAND(SAY_AGGRO_1,SAY_AGGRO_2,SAY_AGGRO_3), me);
        events.ScheduleEvent(EVENT_SHIFT, 30000);
        events.ScheduleEvent(EVENT_CHAIN, urand(10000,20000));
        events.ScheduleEvent(EVENT_BERSERK, 360000);
    }

  void EnterEvadeMode()
  {
      _EnterEvadeMode();
      Reset();
      if (Creature *pStalagg = me->GetCreature(*m_creature, instance->GetData64(DATA_STALAGG)))
      {
          pStalagg->Respawn();
          pStalagg->GetMotionMaster()->MovePoint(0, pStalagg->GetHomePosition());
      }
      if (Creature *pFeugen = me->GetCreature(*m_creature, instance->GetData64(DATA_FEUGEN)))
      {
          pFeugen->Respawn();
          pFeugen->GetMotionMaster()->MovePoint(0, pFeugen->GetHomePosition());
      }
  }
  
    void DamageTaken(Unit *pDoneBy, uint32 &uiDamage)
    {
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (checkFeugenAlive && checkStalaggAlive)
            uiAddsTimer = 0;

        if (checkStalaggAlive != checkFeugenAlive)
        {
            uiAddsTimer += diff;
            if (uiAddsTimer > 5000)
            {
                if (!checkStalaggAlive)
                {
                    if (instance)
                        if (Creature *pStalagg = m_creature->GetCreature(*m_creature, instance->GetData64(DATA_STALAGG)))
                        {
                            pStalagg->Respawn();
                            pStalagg->GetMotionMaster()->MovePoint(0, pStalagg->GetHomePosition());
                        }
                }
                else
                {
                    if (instance)
                        if (Creature *pFeugen = m_creature->GetCreature(*m_creature, instance->GetData64(DATA_FEUGEN)))
                        {
                            pFeugen->Respawn();
                            pFeugen->GetMotionMaster()->MovePoint(0, pFeugen->GetHomePosition());
                        }
                }
            }
        }

        if (!UpdateVictim())
            return;
        
        events.Update(diff);

        if (me->hasUnitState(UNIT_STAT_CASTING))
            return;

        while(uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_SHIFT:
                    DoCastAOE(SPELL_POLARITY_SHIFT);
                    events.ScheduleEvent(EVENT_SHIFT, 30000);
                    return;
                case EVENT_CHAIN:
                    DoCast(me->getVictim(), RAID_MODE(SPELL_CHAIN_LIGHTNING, H_SPELL_CHAIN_LIGHTNING));
                    events.ScheduleEvent(EVENT_CHAIN, urand(10000,20000));
                    return;
                case EVENT_BERSERK:
                    DoCast(me, SPELL_BERSERK);
                    return;
            }
        }

        if (events.GetTimer() > 15000 && !me->IsWithinMeleeRange(me->getVictim()))
            DoCast(me->getVictim(), SPELL_BALL_LIGHTNING);
        else
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_thaddius(Creature* pCreature)
{
    return new boss_thaddiusAI (pCreature);
}

struct mob_stalaggAI : public ScriptedAI
{
    mob_stalaggAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = c->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    uint32 powerSurgeTimer;
    uint32 magneticPullTimer;
	uint32 uiIdleTimer;
    uint32 uiShockTimer;
    uint64 uiTeslaGuid;
    uint32 uiChainTimer;
    bool bChainReset;
    bool bShock;
	bool bSwitch;
    Position homePosition;

    void Reset()
    {
        if (pInstance)
            if (Creature *pThaddius = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_THADDIUS)))
                if (pThaddius->AI())
                    pThaddius->AI()->DoAction(ACTION_STALAGG_RESET);
        powerSurgeTimer = urand(20000,25000);
        magneticPullTimer = 20000;
		uiIdleTimer = 3*IN_MILISECONDS;
		uiShockTimer = 1*IN_MILISECONDS;
        uiChainTimer = 10*IN_MILISECONDS;
        bChainReset = true;
        bShock = false;
		bSwitch = false;
		homePosition = me->GetHomePosition();
    }

    void JustDied(Unit *killer)
    {
        if (pInstance)
            if (Creature *pThaddius = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_THADDIUS)))
                if (pThaddius->AI())
                    pThaddius->AI()->DoAction(ACTION_STALAGG_DIED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bChainReset)
        {
            if (uiChainTimer <= uiDiff)
            {
                if (Creature *pTesla = me->FindNearestCreature(C_TESLA_COIL, 50))
                {
                    uiTeslaGuid = pTesla->GetGUID();
                    pTesla->CastSpell(me, SPELL_STALAGG_CHAIN, false);
                }
                bChainReset = false;
                uiChainTimer = 3*IN_MILISECONDS;
            } else uiChainTimer -= uiDiff;
        }
		
        if (!UpdateVictim())
            return;

        if (magneticPullTimer <= uiDiff)
        {
            if (Creature *pFeugen = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_FEUGEN)))
            {
                Unit* pStalaggVictim = m_creature->getVictim();
                Unit* pFeugenVictim = pFeugen->getVictim();

                if (pFeugenVictim && pStalaggVictim)
                {
                    // magnetic pull is not working. So just jump.

                    // reset aggro to be sure that feugen will not follow the jump
                    float uiTempThreat = pFeugen->getThreatManager().getThreat(pFeugenVictim);
					pFeugen->getThreatManager().modifyThreatPercent(pFeugenVictim, -100);
                    pFeugenVictim->JumpTo(m_creature, 0.3f); 
					pFeugen->AddThreat(pStalaggVictim, uiTempThreat);
					pFeugen->SetReactState(REACT_PASSIVE);

                    uiTempThreat = me->getThreatManager().getThreat(pStalaggVictim);
                    m_creature->getThreatManager().modifyThreatPercent(pStalaggVictim, -100);
                    pStalaggVictim->JumpTo(pFeugen, 0.3f);
					me->AddThreat(pFeugenVictim, uiTempThreat);
					me->SetReactState(REACT_PASSIVE);
					uiIdleTimer = 3*IN_MILISECONDS;
					bSwitch = true;
                }
            }

            magneticPullTimer = 20000;
        }
        else magneticPullTimer -= uiDiff;

        if (powerSurgeTimer <= uiDiff)
        {
            DoCast(m_creature, RAID_MODE(SPELL_POWERSURGE, H_SPELL_POWERSURGE));
            powerSurgeTimer = urand(15000,20000);
        } else powerSurgeTimer -= uiDiff;

		if (bSwitch)
			if (uiIdleTimer <= uiDiff)
			{
				if (Creature *pFeugen = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_FEUGEN)))
					pFeugen->SetReactState(REACT_AGGRESSIVE);
				me->SetReactState(REACT_AGGRESSIVE);
				bSwitch = false;
			} else uiIdleTimer -= uiDiff;

        if (me->GetDistance(homePosition) > 15)
        {
            if (uiShockTimer <= uiDiff)
            {
                if (Creature *pTesla = Creature::GetCreature(*me, uiTeslaGuid))
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                        pTesla->CastSpell(pTarget, SPELL_SHOCK, false);
                uiShockTimer = 1*IN_MILISECONDS;
                bShock = true;
            }else uiShockTimer -= uiDiff;
        } else if (bShock)
        {
            bShock = false;
            bChainReset = true;
        }
    
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_stalagg(Creature* pCreature)
{
    return new mob_stalaggAI(pCreature);
}

struct mob_feugenAI : public ScriptedAI
{
    mob_feugenAI(Creature *c) : ScriptedAI(c) 
    {
        pInstance = c->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    uint32 staticFieldTimer;
    uint32 uiShockTimer;
    uint64 uiTeslaGuid;
    uint32 uiChainTimer;
    bool bChainReset;
    bool bShock;
    Position homePosition;

    void Reset()
    {
        if (pInstance)
            if (Creature *pThaddius = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_THADDIUS)))
                if (pThaddius->AI())
                    pThaddius->AI()->DoAction(ACTION_FEUGEN_RESET);
        staticFieldTimer = 5000;
        uiShockTimer = 1*IN_MILISECONDS;
        uiChainTimer = 10*IN_MILISECONDS;
        bChainReset = true;
        bShock = false;
        homePosition = me->GetHomePosition();
    }

    void JustDied(Unit *killer)
    {
        if (pInstance)
            if (Creature *pThaddius = m_creature->GetCreature(*m_creature, pInstance->GetData64(DATA_THADDIUS)))
                if (pThaddius->AI())
                    pThaddius->AI()->DoAction(ACTION_FEUGEN_DIED);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (bChainReset)
        {
            if (uiChainTimer <= uiDiff)
            {
                if (Creature *pTesla = me->FindNearestCreature(C_TESLA_COIL, 50))
                {
                    uiTeslaGuid = pTesla->GetGUID();
                    pTesla->CastSpell(me, SPELL_FEUGEN_CHAIN, false);
                }
                bChainReset = false;
                uiChainTimer = 3*IN_MILISECONDS;
            } else uiChainTimer -= uiDiff;
        }
		
        if (!UpdateVictim())
            return;

        if (staticFieldTimer <= uiDiff)
        {
            DoCast(m_creature, RAID_MODE(SPELL_STATICFIELD, H_SPELL_STATICFIELD));
            staticFieldTimer = 5000;
        } else staticFieldTimer -= uiDiff;

        if (me->GetDistance(homePosition) > 15)
        {
            if (uiShockTimer <= uiDiff)
            {
                if (Creature *pTesla = Creature::GetCreature(*me, uiTeslaGuid))
                    if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                        pTesla->CastSpell(pTarget, SPELL_SHOCK, false);
                uiShockTimer = 1*IN_MILISECONDS;
                bShock = true;
            }else uiShockTimer -= uiDiff;
        } else if (bShock)
        {
            bShock = false;
            bChainReset = true;
        }
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_feugen(Creature* pCreature)
{
    return new mob_feugenAI(pCreature);
}

void AddSC_boss_thaddius()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_thaddius";
    newscript->GetAI = &GetAI_boss_thaddius;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_stalagg";
    newscript->GetAI = &GetAI_mob_stalagg;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_feugen";
    newscript->GetAI = &GetAI_mob_feugen;
    newscript->RegisterSelf();
}
