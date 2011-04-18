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

enum
{
    //auriaya
    SPELL_BERSERK = 47008,
    SPELL_GUARDIAN_SWARM = 64396,
    SPELL_SENTINEL_BLAST = 64389,
    SPELL_SENTINEL_BLAST_H = 64678,
    SPELL_SONIC_SCREECH = 64422,
    SPELL_SONIC_SCREECH_H = 64688,
    SPELL_FEAR = 64386,
    //feral defender
    SPELL_FEIGN_DEATH = 57685,
    SPELL_FERAL_ESSENCE = 64455,
    SPELL_FERAL_POUNCE = 64478,
    SPELL_FERAL_POUNCE_H = 64669,
    SPELL_FERAL_RUSH = 64496,
    SPELL_FERAL_RUSH_H = 64674,
    //sanctum sentry
    SPELL_RIP_FLESH = 64375,
    SPELL_RIP_FLESH_H = 64667,
    SPELL_SAVAGE_POUNCE = 64666,
    SPELL_SAVAGE_POUNCE_H = 64374,
    SPELL_STRENGHT_OF_PACK = 64381,
    //seeping feral essence
    AURA_VOID_ZONE = 64458,
    AURA_VOID_ZONE_H = 64676,
    //NPC ids
    MOB_VOID_ZONE = 34098,
    MOB_FERAL_DEFENDER = 34035
};
 
// Seeping Feral Essence
struct mob_seeping_feral_essenceAI : public ScriptedAI
{
    mob_seeping_feral_essenceAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        SetCombatMovement(false);
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = !pCreature->GetMap()->IsHeroic();
    }
 
    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;
 
    uint32 Check_Timer;
 
    void Reset()
    {
        Check_Timer = 5000;
        me->SetDisplayId(11686);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        DoCast(me, m_bIsRegularMode ? AURA_VOID_ZONE : AURA_VOID_ZONE_H);
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!me->getVictim())
        {
            if (Check_Timer < diff)
            {
                if (m_pInstance->GetData(TYPE_AURIAYA) == FAIL || m_pInstance->GetData(TYPE_AURIAYA) == DONE)
                    me->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
                Check_Timer = 5000;
            }else Check_Timer -= diff;
        }
 
        if (Check_Timer < diff)
        {
            if (m_pInstance->GetData(TYPE_AURIAYA) == FAIL || m_pInstance->GetData(TYPE_AURIAYA) == DONE)
                me->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            Check_Timer = 5000;
        }else Check_Timer -= diff;
    }
};
 
CreatureAI* GetAI_mob_seeping_feral_essence(Creature* pCreature)
{
    return new mob_seeping_feral_essenceAI(pCreature);
}
 
// Sanctum Sentry
struct mob_sanctum_sentryAI : public ScriptedAI
{
    mob_sanctum_sentryAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = !pCreature->GetMap()->IsHeroic();
    }
 
    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;
 
    uint32 Rip_Flesh_Timer;
    uint32 Jump_Timer;
    uint32 Check_Timer;
 
    void Reset()
    {
        Rip_Flesh_Timer = 13000;
        Jump_Timer = 0;
        Check_Timer = 500;
    }
 
    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
        {
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_1))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_2))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_3))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_4))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_AURIAYA))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
        }
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
        {
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_AURIAYA))))
            {
                if (pTemp->isAlive())
                {
                    me->GetMotionMaster()->MoveFollow(pTemp,0.0f,0.0f);
                    me->GetMap()->CreatureRelocation(me, pTemp->GetPositionX(), pTemp->GetPositionY(), pTemp->GetPositionZ(), 0.0f);
                }
            }
        }
 
        if (Rip_Flesh_Timer < diff)
        {
            DoCast(me->getVictim(), m_bIsRegularMode ? SPELL_RIP_FLESH : SPELL_RIP_FLESH_H);
            Rip_Flesh_Timer = 10000;
        }else Rip_Flesh_Timer -= diff;
 
        if (Jump_Timer < diff)
        {
            if (!me->IsWithinDistInMap(me->getVictim(), 8) && me->IsWithinDistInMap(me->getVictim(), 25))
                DoCast(me->getVictim(), m_bIsRegularMode ? SPELL_SAVAGE_POUNCE : SPELL_SAVAGE_POUNCE_H);
            Jump_Timer = 1000;
        }else Jump_Timer -= diff;
 
        if (Check_Timer < diff)
        {
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_1))))
                if (pTemp->isAlive())
                    if (pTemp->IsWithinDistInMap(me->getVictim(), 10))
                        if (Aura *pAura = pTemp->GetAura(SPELL_STRENGHT_OF_PACK)) //if (pTemp->HasAura(SPELL_STRENGHT_OF_PACK))
                            pAura->SetStackAmount(pAura->GetStackAmount() + 1, true);
                        else
                            DoCast(me->getVictim(), SPELL_STRENGHT_OF_PACK);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_2))))
                if (pTemp->isAlive())
                    if (pTemp->IsWithinDistInMap(me->getVictim(), 10))
                        if (Aura *pAura = pTemp->GetAura(SPELL_STRENGHT_OF_PACK)) //if (pTemp->HasAura(SPELL_STRENGHT_OF_PACK))
                            pAura->SetStackAmount(pAura->GetStackAmount() + 1, true);
                        else
                            DoCast(me->getVictim(), SPELL_STRENGHT_OF_PACK);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_3))))
                if (pTemp->isAlive())
                    if (pTemp->IsWithinDistInMap(me->getVictim(), 10))
                        if (Aura *pAura = pTemp->GetAura(SPELL_STRENGHT_OF_PACK)) //if (pTemp->HasAura(SPELL_STRENGHT_OF_PACK))
                            pAura->SetStackAmount(pAura->GetStackAmount() + 1, true);
                        else
                            DoCast(me->getVictim(), SPELL_STRENGHT_OF_PACK);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_4))))
                if (pTemp->isAlive())
                    if (pTemp->IsWithinDistInMap(me->getVictim(), 10))
                        if (Aura *pAura = pTemp->GetAura(SPELL_STRENGHT_OF_PACK)) //if (pTemp->HasAura(SPELL_STRENGHT_OF_PACK))
                            pAura->SetStackAmount(pAura->GetStackAmount() + 1, true);
                        else
                            DoCast(me->getVictim(), SPELL_STRENGHT_OF_PACK);
            if (Aura *pAura = me->GetAura(SPELL_STRENGHT_OF_PACK)) // if (me->HasAura(SPELL_STRENGHT_OF_PACK))
            {
                if (pAura->GetStackAmount() == 1)
                    me->RemoveAurasDueToSpell(SPELL_STRENGHT_OF_PACK);
                else
                    pAura->SetStackAmount(pAura->GetStackAmount() - 1, true);
            }
            Check_Timer = 2100;
        }else Check_Timer -= diff;
 
        DoMeleeAttackIfReady();
    }
};
 
CreatureAI* GetAI_mob_sanctum_sentry(Creature* pCreature)
{
    return new mob_sanctum_sentryAI(pCreature);
}
 
// Feral Defender
struct mob_feral_defenderAI : public ScriptedAI
{
    mob_feral_defenderAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        Reset();
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = !pCreature->GetMap()->IsHeroic();
    }
 
    bool m_bIsRegularMode;
    ScriptedInstance* m_pInstance;
 
    uint32 revive_delay;
    uint32 Pounce_Timer;
    uint32 Rush_Start_Timer;
    uint32 Rush_Finish_Timer;
    uint32 Rush_Delay;
    uint32 Revive_Delay;
    uint32 stack_delay;
 
    bool rush;
    bool dead;
    bool rdy;
 
    void Reset()
    {
        stack_delay = 500;
        Pounce_Timer = 5000;
        Rush_Start_Timer = 9000;
        rdy = false;
        rush = false;
        dead = false;
        DoCast(me, SPELL_FERAL_ESSENCE);
    }
 
    void DamageTaken(Unit* pDoneBy, uint32& uiDamage)
    {
        if (uiDamage > me->GetHealth())
        {
            uiDamage = 0;
            me->CastStop();
            me->RemoveArenaAuras(true);
            me->SummonCreature(MOB_VOID_ZONE, 0.0f, 0.0f, 0.0f, 0, TEMPSUMMON_DEAD_DESPAWN, 0);
            DoCast(me, SPELL_FEIGN_DEATH);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);

            if (Aura *pAura = me->GetAura(SPELL_FERAL_ESSENCE))
            {
                if (pAura->GetStackAmount() == 1)
                    me->RemoveAurasDueToSpell(SPELL_FERAL_ESSENCE);
                else
                    pAura->SetStackAmount(pAura->GetStackAmount() - 1);
                Revive_Delay = 45000;
                dead = true;
            }
        }
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
 
        if (Revive_Delay < diff && dead)
        {
            if (Creature *pAuriaya = Unit::GetCreature((*me), m_pInstance->GetData64(TYPE_AURIAYA)))
            {
                if (!pAuriaya->isAlive())
                {
                    me->DisappearAndDie();
                    return;
                }
            }

            me->SetHealth(me->GetMaxHealth());
            me->RemoveAurasDueToSpell(SPELL_FEIGN_DEATH);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
            me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
            dead = false;
        }else Revive_Delay -= diff;

        if (Pounce_Timer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0)){
                DoCast(target, m_bIsRegularMode ? SPELL_FERAL_POUNCE : SPELL_FERAL_POUNCE_H);
                me->AddThreat(target,0.0f);
                me->AI()->AttackStart(target);
            }
            Pounce_Timer = 5000;
        }else Pounce_Timer -= diff;
 
        if (Rush_Start_Timer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0)){
                DoCast(target, m_bIsRegularMode ? SPELL_FERAL_RUSH : SPELL_FERAL_RUSH_H);
                me->AddThreat(target,0.0f);
                me->AI()->AttackStart(target);
            }
            Rush_Start_Timer = 35000;
            Rush_Finish_Timer = 5000;
            Rush_Delay = 500;
        }else Rush_Start_Timer -= diff;
 
        if (Rush_Delay < diff && rush)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,0)){
                DoCast(target, m_bIsRegularMode ? SPELL_FERAL_RUSH : SPELL_FERAL_RUSH_H);
                me->AddThreat(target,0.0f);
                me->AI()->AttackStart(target);
            }
            Rush_Delay = 500;
        }else Rush_Delay -= diff;
 
        if (Rush_Finish_Timer < diff)
            rush = false;
        else Rush_Finish_Timer -= diff;
 
        
 
        if (stack_delay < diff && !rdy)
        {
            DoCast(me, SPELL_FERAL_ESSENCE);
            if (me->GetAura(SPELL_FERAL_ESSENCE, 0)->GetStackAmount() == 8)
                    rdy = true;
            stack_delay = 500;
        }else stack_delay -= diff;

        DoMeleeAttackIfReady();
    }
};
 
CreatureAI* GetAI_mob_feral_defender(Creature* pCreature)
{
    return new mob_feral_defenderAI(pCreature);
}
 
// Auriaya
struct boss_auriayaAI : public ScriptedAI
{
    boss_auriayaAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        m_bIsRegularMode = !pCreature->GetMap()->IsHeroic();
        Reset();
    }
 
    ScriptedInstance* m_pInstance;
    bool m_bIsRegularMode;
 
    uint32 Enrage_Timer;
    uint32 Swarm_Timer;
    uint32 Sonic_Screech_Timer;
    uint32 Sentinel_Blast_Timer;
    uint32 Fear_Timer;
    uint32 Summon_Timer;
 
    bool enrage;
    bool summoned;
 
    void Reset()
    {
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
        Enrage_Timer = 600000;
        Swarm_Timer = 45000;
        Sonic_Screech_Timer = 35000;
        Sentinel_Blast_Timer = 62500;
        Fear_Timer = 60000;
        Summon_Timer = 45000;
        enrage= false;
        summoned = false;
    }
 
    void JustDied(Unit* pKiller)
    {
        //death yell
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_AURIAYA, DONE);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_FERAL_DEFENDER))))
            {
                if (pTemp->isAlive())
                    pTemp->DisappearAndDie();
            }
        }
    }
 
    void Aggro(Unit* pWho)
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_AURIAYA, IN_PROGRESS);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_1))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_2))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_3))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_4))))
                if (pTemp->isAlive())
                    pTemp->SetInCombatWithZone();
        }
        //aggro yell
    }
 
    void JustReachedHome()
    {
        if (m_pInstance)
        {
            m_pInstance->SetData(TYPE_AURIAYA, FAIL);
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_1))))
                if (!pTemp->isAlive())
                    pTemp->Respawn();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_2))))
                if (!pTemp->isAlive())
                    pTemp->Respawn();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_3))))
                if (!pTemp->isAlive())
                    pTemp->Respawn();
            if (Creature* pTemp = ((Creature*)Unit::GetUnit((*me), m_pInstance->GetData64(DATA_SENTRY_4))))
                if (!pTemp->isAlive())
                    pTemp->Respawn();
        }
    }
 
    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
 
        if (Fear_Timer < diff)
        {
            DoCast(me->getVictim(), SPELL_FEAR);
            Fear_Timer = 45000;
            Sentinel_Blast_Timer = 2500;
        }else Fear_Timer -= diff;
 
        if (Sentinel_Blast_Timer < diff)
        {
            DoCast(me->getVictim(), m_bIsRegularMode ? SPELL_SENTINEL_BLAST : SPELL_SENTINEL_BLAST_H);
            Sentinel_Blast_Timer = 45000;
        }else Sentinel_Blast_Timer -= diff;
 
        if (Summon_Timer < diff && !summoned)
        {
            if (Creature* pTemp = me->SummonCreature(MOB_FERAL_DEFENDER, 0.0f, 0.0f, 0.0f, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000))
                if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM,0))
                {
                    pTemp->AddThreat(pTarget,0.0f);
                    pTemp->AI()->AttackStart(pTarget);
                }
            summoned = true;
        }else Summon_Timer -= diff;
 
        if (Sonic_Screech_Timer < diff)
        {
            DoCast(me->getVictim(), m_bIsRegularMode ? SPELL_SONIC_SCREECH : SPELL_SONIC_SCREECH_H);
            Sonic_Screech_Timer = 45000;
        }else Sonic_Screech_Timer -= diff;
 
        if (Swarm_Timer < diff)
        {
            if (Unit* target = SelectUnit(SELECT_TARGET_RANDOM,1))
                DoCast(target, SPELL_GUARDIAN_SWARM);
            Swarm_Timer = 45000;
        }else Swarm_Timer -= diff;
 
        if (Enrage_Timer < diff && !enrage)
        {
            //enrage yell
            me->CastStop();
            DoCast(me, SPELL_BERSERK);
            enrage = true;
        }else Enrage_Timer -= diff;
        
        DoMeleeAttackIfReady();
    }
};
 
CreatureAI* GetAI_boss_auriaya(Creature* pCreature)
{
    return new boss_auriayaAI(pCreature);
}
 
void AddSC_boss_auriaya()
{
    Script* NewScript;
 
    NewScript = new Script;
    NewScript->Name = "boss_auriaya";
    NewScript->GetAI = GetAI_boss_auriaya;
    NewScript->RegisterSelf();
 
    NewScript = new Script;
    NewScript->Name = "mob_seeping_feral_essence";
    NewScript->GetAI = &GetAI_mob_seeping_feral_essence;
    NewScript->RegisterSelf();
 
    NewScript = new Script;
    NewScript->Name = "mob_sanctum_sentry";
    NewScript->GetAI = &GetAI_mob_sanctum_sentry;
    NewScript->RegisterSelf();
 
    NewScript = new Script;
    NewScript->Name = "mob_feral_defender";
    NewScript->GetAI = &GetAI_mob_feral_defender;
    NewScript->RegisterSelf();
}
