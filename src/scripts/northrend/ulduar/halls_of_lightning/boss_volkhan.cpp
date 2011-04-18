/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */
 
/* ScriptData
SDName: Boss Volkhan
SD%Complete: 95%
SDComment: 
 
SDCategory: Halls of Lightning
EndScriptData */
 
#include "ScriptedPch.h"
#include "halls_of_lightning.h"
 
enum eEnums
{
    SAY_AGGRO                               = -1602032,
    SAY_SLAY_1                              = -1602033,
    SAY_SLAY_2                              = -1602034,
    SAY_SLAY_3                              = -1602035,
    SAY_DEATH                               = -1602036,
    SAY_STOMP_1                             = -1602037,
    SAY_STOMP_2                             = -1602038,
    SAY_FORGE_1                             = -1602039,
    SAY_FORGE_2                             = -1602040,
    EMOTE_TO_ANVIL                          = -1602041,
    EMOTE_SHATTER                           = -1602042,
 
    SPELL_HEAT_N                            = 52387,
    SPELL_HEAT_H                            = 59528,
    SPELL_SHATTERING_STOMP_N                = 52237,
    SPELL_SHATTERING_STOMP_H                = 59529,
 
    //unclear how "directions" of spells must be. Last, summoning GO, what is it for? Script depend on:
    SPELL_TEMPER                            = 52238,        //TARGET_SCRIPT boss->anvil
    SPELL_TEMPER_DUMMY                      = 52654,        //TARGET_SCRIPT anvil->boss
 
    //SPELL_TEMPER_VISUAL                     = 52661,        //summons GO
 
    SPELL_SUMMON_MOLTEN_GOLEM               = 52405, 
 
    //Molten Golem
    SPELL_BLAST_WAVE                        = 23113, 
    SPELL_IMMOLATION_STRIKE_N               = 52433, 
    SPELL_IMMOLATION_STRIKE_H               = 59530,
    SPELL_SHATTER_N                         = 52429,
    SPELL_SHATTER_H                         = 59527,
 
    NPC_VOLKHAN_ANVIL                       = 28823, 
    NPC_MOLTEN_GOLEM                        = 28695,
    NPC_BRITTLE_GOLEM                       = 28681,
 
    GO_ANVIL                                = 190858,
    POINT_ID_ANVIL                          = 0,
    MAX_GOLEM                               = 2,
    ACHIEVEMENT_SHATTER_RESISTANT           = 2042    
};

static float anvilPoint[] = { 1326.89, -96.47, 56.70, 2.17 };
static float spawnPoint1[] = { 1329.67, -89.06, 56.72, 4.53 };
static float spawnPoint2[] = { 1321.83, -89.06, 56.69, 5.63 };

 
/*######
## Boss Volkhan
######*/
 
 
struct boss_volkhanAI : public BossAI
{
    boss_volkhanAI(Creature *pCreature) : BossAI(pCreature, TYPE_VOLKHAN), spawns(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }
 
    ScriptedInstance* m_pInstance; 

    uint32 m_uiStompTimer;
    uint32 uiShatterTimer;
    uint8 uiHealthMod;
    uint32 uiTemperTimer;
	uint32 uiHeatTimer;
    uint8 uiShatteredGolem; 

    bool bStomp;
    bool bTemp;

    SummonList spawns;
 
    void Reset()
    {
        spawns.DespawnAll();

        m_uiStompTimer = 30 * IN_MILISECONDS;
        uiTemperTimer = 2 * IN_MILISECONDS;
        uiShatterTimer = 3 * IN_MILISECONDS;
		uiHeatTimer = RAND(1,10) * IN_MILISECONDS; // No Source
        uiHealthMod = 4;
        uiShatteredGolem = 0;

        bStomp = false;
        bTemp = false;
    

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLKHAN , NOT_STARTED);                  
     }

    void EnterCombat (Unit* pWho)
    { 
        DoScriptText(SAY_AGGRO,me);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VOLKHAN , IN_PROGRESS);
    }

    void JustDied(Unit* pwho)
    {
        DoScriptText(SAY_DEATH,me);
        spawns.DespawnAll();

        if (m_pInstance)
        {
            if (uiShatteredGolem < 5 && IsHeroic())
            {
                m_pInstance->DoCompleteAchievement(ACHIEVEMENT_SHATTER_RESISTANT);
                m_pInstance->SetData(TYPE_VOLKHAN, DONE);
			}
        }
    }

    void KilledUnit(Unit* pwho)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3),me);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim() || me->hasUnitState(UNIT_STAT_CASTING))
            return;

        if (m_uiStompTimer <= uiDiff)
        {
            DoCast(DUNGEON_MODE(SPELL_SHATTERING_STOMP_N, SPELL_SHATTERING_STOMP_H));

            bStomp = true;
            m_uiStompTimer = 30 * IN_MILISECONDS;
        }
        else
            m_uiStompTimer -= uiDiff;


		if (uiHeatTimer <= uiDiff)
		{
			if (Creature *pCreature = me->FindNearestCreature(NPC_MOLTEN_GOLEM,99))
				me->CastSpell(pCreature,DUNGEON_MODE(SPELL_HEAT_N,SPELL_HEAT_H),true);
			uiHeatTimer = RAND(1,10) * IN_MILISECONDS;
		}
		else
			uiHeatTimer -= uiDiff;                                			

        if (bTemp)
		{
            if (uiTemperTimer <= uiDiff)
            {
                if (Creature *pCreature = me->SummonCreature(NPC_MOLTEN_GOLEM, spawnPoint1[0], spawnPoint1[1], spawnPoint1[2], spawnPoint1[3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300*IN_MILISECONDS))			
				{
					spawns.Summon(pCreature);
					if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                        pCreature->AI()->AttackStart(pTarget);
				}

                if (Creature *pCreature = me->SummonCreature(NPC_MOLTEN_GOLEM, spawnPoint2[0], spawnPoint2[1], spawnPoint2[2], spawnPoint2[3], TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN, 300*IN_MILISECONDS))			
				{
					spawns.Summon(pCreature);
					if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM))
                        pCreature->AI()->AttackStart(pTarget);
				}
                    
                me->SetReactState(REACT_AGGRESSIVE);
                DoStartMovement(me->getVictim());

                bTemp = false;
                uiTemperTimer = 2 * IN_MILISECONDS;
			}
			else uiTemperTimer -= uiDiff;
		}

        if (bStomp)
        {
            if (uiShatterTimer <= uiDiff)
            {
                for (std::list<uint64>::iterator itr = spawns.begin(); itr != spawns.end(); ++itr)
                {
                     Creature *pCreature = Creature::GetCreature(*me, *itr);
                    if (pCreature && pCreature->GetEntry() == NPC_BRITTLE_GOLEM)
					{
						pCreature->CastSpell(pCreature, DUNGEON_MODE(SPELL_SHATTER_N, SPELL_SHATTER_H), false);
						uiShatteredGolem++;
						pCreature->ForcedDespawn(2.5*IN_MILISECONDS);
					}
                }
                bStomp = false;
                uiShatterTimer = 3*IN_MILISECONDS;

            }else uiShatterTimer -= uiDiff;
        }

        if (HealthBelowPct(20 * uiHealthMod))
        {
            DoScriptText(RAND(SAY_FORGE_1, SAY_FORGE_2), me);
            DoScriptText(EMOTE_TO_ANVIL, me);

            --uiHealthMod;
            
            me->SetReactState(REACT_PASSIVE);
            
            me->GetMotionMaster()->MovePoint(POINT_ID_ANVIL, anvilPoint[0], anvilPoint[1], anvilPoint[2]);
			me->SetOrientation(anvilPoint[3]);
        }
        DoMeleeAttackIfReady();
    }

    void MovementInform(uint32 type, uint32 id)
    {
        if(type != POINT_MOTION_TYPE)
            return;

        if (id == POINT_ID_ANVIL)
        {
            DoCast(me, SPELL_TEMPER);

            bTemp = true;
        }
    }
};
 
// Mob Molten Golem AI
 
struct mob_molten_golemAI : public ScriptedAI
{
    mob_molten_golemAI (Creature *pCreature) : ScriptedAI(pCreature) { }
 
    bool m_bIsFrozen;
    uint32 m_uiBlast_Timer;
    uint32 m_uiDeathdelay_Timer;
    uint32 m_uiImmolation_Timer;
    uint32 m_uiShatter_Timer;

    void Reset()
    {
        m_uiBlast_Timer = 20*IN_MILISECONDS;
        m_uiDeathdelay_Timer = 0;
        m_uiImmolation_Timer = 5*IN_MILISECONDS;
        me->setFaction(16);
		me->SetName("Geschmolzener Golem");
    }
 
    void DamageTaken(Unit* pDoneBy, uint32 &uiDamgage)
    {
		if (uiDamgage > me->GetHealth() && (me->GetEntry() == NPC_MOLTEN_GOLEM)) // Freeze me 
        {
            me->SetFlag(UNIT_FIELD_FLAGS,UNIT_FLAG_STUNNED | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE);           
			me->AttackStop();			
			me->UpdateEntry(NPC_BRITTLE_GOLEM);  
            uiDamgage=0;                    
            me->SetHealth(1000);
            me->RemoveAllAuras();

			me->SetReactState(REACT_PASSIVE);
			me->GetMotionMaster()->Clear(false);
			me->GetMotionMaster()->MoveIdle();
			me->ClearAllReactives();
			me->getThreatManager().resetAllAggro();
        }		
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())    
            return;

		if(me->GetEntry() == NPC_MOLTEN_GOLEM)
		{
		    if (IsHeroic())
			{	
				if (m_uiBlast_Timer <= uiDiff)
				{
					DoCast(me, SPELL_BLAST_WAVE); 
					m_uiBlast_Timer = 20*IN_MILISECONDS;
				}
				else
				 m_uiBlast_Timer -= uiDiff;
			}	

		    if (!me->getVictim()->HasAura(DUNGEON_MODE(SPELL_IMMOLATION_STRIKE_N, SPELL_IMMOLATION_STRIKE_H)))
            {
		        if (m_uiImmolation_Timer <= uiDiff)
		        {
				    DoCast(me->getVictim(), DUNGEON_MODE(SPELL_IMMOLATION_STRIKE_N, SPELL_IMMOLATION_STRIKE_H));
				    m_uiImmolation_Timer = 5*IN_MILISECONDS;
		        }
            }
			else
                m_uiImmolation_Timer-= uiDiff;

            DoMeleeAttackIfReady();
		}
		else
		{
			me->SetReactState(REACT_PASSIVE);
			me->GetMotionMaster()->Clear(false);
			me->GetMotionMaster()->MoveIdle();
			me->getThreatManager().resetAllAggro();
		}
 
	}
};
 
CreatureAI* GetAI_boss_volkhan(Creature* pCreature)
{
    return new boss_volkhanAI(pCreature);
}
 
CreatureAI* GetAI_mob_molten_golem(Creature* pCreature)
{
     return new mob_molten_golemAI(pCreature);
}
 
void AddSC_boss_volkhan()
{
    Script *newscript;
 
    newscript = new Script;
    newscript->Name = "boss_volkhan";
    newscript->GetAI = &GetAI_boss_volkhan;
    newscript->RegisterSelf();
 
    newscript = new Script;
    newscript->Name = "mob_molten_golem";
    newscript->GetAI = &GetAI_mob_molten_golem;
    newscript->RegisterSelf();
}