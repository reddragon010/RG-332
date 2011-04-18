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
#include "ulduar.h"
#include "Spell.h"

// General Vezax Spells
enum VezaxSpells
{
    AURA_OF_DESPAIR                 = 62692,
    SPELL_BERSERK                   = 26662,
    SPELL_MARK_OF_THE_FACELESS      = 63276,
    SPELL_SARONITE_BARRIER          = 63364,
    SPELL_SEARING_FLAMES            = 62661,
    SPELL_SHADOW_CRASH              = 62660,
    SPELL_SURGE_OF_DARKNESS         = 62662,
    SPELL_SARONITE_VAPOR            = 63323,
    SPELL_PROFOUND_OF_DARKNESS      = 63420
};

// General Vezax Says
enum VezaxSays
{
    SAY_UR_Vezax_Aggro01            = -2000010,
    SAY_UR_Vezax_Slay01             = -2000011,
    SAY_UR_Vezax_Slay02             = -2000012,
    SAY_UR_Vezax_Hard               = -2000013, 
    SAY_UR_Vezax_Enrage01           = -2000014,
    SAY_UR_Vezax_Kite               = -2000015,
    SAY_UR_Vezax_Death01            = -2000016,
    EMOTE_SARONIT                   = -2000017
};

// Saronite Vapors
enum VezaxNpcs
{
    MOB_SARONITE_VAPORS             = 33488,
    MOB_SARONITE_DEBUFF             = 194811,
    BOSS_SARONITE_ANIMUS            = 33524
};

enum Achievs
{
    ACHIEV_I_LOVE_THE_SMELL_OF_SARONITE_IN_THE_MORNING    = 3181,     // Defeat General Vezax after defeating the Saronite Animus in 10-player mode.  
    ACHIEV_I_LOVE_THE_SMELL_OF_SARONITE_IN_THE_MORNING_H    = 3188      // Defeat General Vezax after defeating the Saronite Animus in 25-player mode.  
};

// Saronite Vapor Spawn locations
const Position SaronitSummonPos0 = { 1852.780,   81.38, 342.37, 1.658 };
const Position SaronitSummonPos1 = { 1836.196,  119.20, 342.37, 2.304 };
const Position SaronitSummonPos2 = { 1804.516,   94.45, 342.37, 0.102 };
const Position SaronitSummonPos3 = { 1833.187,  149.11, 342.37, 5.526 };

struct boss_generalvezaxAI : public ScriptedAI
{
    boss_generalvezaxAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *m_pInstance;

    bool berserk;
    uint32 Hardmode;
    uint32 Searing_Flames_Timer;
    uint32 SaroniteAnimus_Timer;
    uint32 Aura_check_Timer;
    uint32 Shadow_Crash_Timer;
    uint32 Mark_of_the_Faceless_Timer;
    uint32 Surge_of_Darkness_Timer;
    uint32 Saronite_Barrier_Timer;
    uint32 Saronite_Vapors_Timer;  //Spawn 8x the entire battle
    uint32 Berserk_Timer;

    void Reset()
    {
        Hardmode = 0;
        Searing_Flames_Timer = 10000;
        SaroniteAnimus_Timer = 3000000;
        Aura_check_Timer = 2500;
        Shadow_Crash_Timer = 15000;
        Mark_of_the_Faceless_Timer = 25000;
        Surge_of_Darkness_Timer = 30000;
        Saronite_Barrier_Timer = 35000;
        Saronite_Vapors_Timer = 30000;
        Berserk_Timer = 900000;
        me->ResetLootMode();
       
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, NOT_STARTED);
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(RAND(SAY_UR_Vezax_Slay01, SAY_UR_Vezax_Slay02), me);
    }
    
    void AddSaroniteAnimus()
    {
            me->AddLootMode(LOOT_MODE_HARD_MODE_1);      // Add Hardmode loot
    }

    void JustDied(Unit *victim)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, DONE);
        DoScriptText(SAY_UR_Vezax_Death01, me);
        if (m_pInstance && Hardmode == 1 && TYPE_SARONITE_ANIMUS == DONE)
            m_pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_I_LOVE_THE_SMELL_OF_SARONITE_IN_THE_MORNING, ACHIEV_I_LOVE_THE_SMELL_OF_SARONITE_IN_THE_MORNING_H));

    }

    void Aggro(Unit *pWho)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VEZAX, IN_PROGRESS);
        DoScriptText(SAY_UR_Vezax_Aggro01, me);
    }

    void SpellHit(Unit* caster, const SpellEntry *spell)
    {
        if (!spell)
            return;

        // Make boss interrupt able :O
        switch (spell->Id)
        {
            case 57994:     // windschock
            case 2139:      // gegenzauber
            case 47528:     // gedankenfrost
            case 1766:      // tritt
            case 6552:      // zuschlagen
            case 72:        // schildhieb
            {
                for (uint32 i = CURRENT_FIRST_NON_MELEE_SPELL; i < CURRENT_MAX_SPELL; i++)
                {
                    if (Spell *sCurrent = me->GetCurrentSpell(i))
                    {
                        if (sCurrent->m_spellInfo->Id == SPELL_SURGE_OF_DARKNESS)
                            return;
                    }
                }
                me->CastStop();
                break;
            }
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Aura of Despair
        if (Aura_check_Timer < diff )
        {
            DoCast(me, AURA_OF_DESPAIR);
            Aura_check_Timer = 12000;
        }else Aura_check_Timer -= diff;

        // Vezax Hardmode
        if (SaroniteAnimus_Timer < diff )
        {
            DoCast(me, SPELL_SARONITE_BARRIER);
            me->SummonCreature(BOSS_SARONITE_ANIMUS, me->GetPositionX(), me->GetPositionY(), me->GetPositionZ() + 5, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            AddSaroniteAnimus();
            Hardmode = 1;
        }else SaroniteAnimus_Timer -= diff;
        
        // Searing Flames
        if (Searing_Flames_Timer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_SEARING_FLAMES);
            Searing_Flames_Timer = 16000;
        }else Searing_Flames_Timer -= diff;

        // Shadow Crash
        if (Shadow_Crash_Timer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_SHADOW_CRASH);
            Shadow_Crash_Timer = 30000;
        }else Shadow_Crash_Timer -= diff;

        // Surge of Darkness
        if (Surge_of_Darkness_Timer < diff )
        {
            DoScriptText(SAY_UR_Vezax_Kite, me);
            DoCast(me, SPELL_SURGE_OF_DARKNESS);
            Surge_of_Darkness_Timer = 40000;
        }else Surge_of_Darkness_Timer -= diff;

        // Makr of the Faceless
        if (Mark_of_the_Faceless_Timer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_MARK_OF_THE_FACELESS);
            Mark_of_the_Faceless_Timer = 20000;
        }else Mark_of_the_Faceless_Timer -= diff;

        // Saronite Vapor
        if (Saronite_Vapors_Timer < diff )
        {
            DoScriptText(EMOTE_SARONIT, me);

            switch (urand(0, 3))
            {
            case 0: 
                DoSummon(MOB_SARONITE_VAPORS, SaronitSummonPos0, 1);
                break;
            case 1:
                DoSummon(MOB_SARONITE_VAPORS, SaronitSummonPos1, 1);
                break;
            case 2:
                DoSummon(MOB_SARONITE_VAPORS, SaronitSummonPos2, 1);
                break;
            case 3:
                DoSummon(MOB_SARONITE_VAPORS, SaronitSummonPos3, 1);
                break;
            }
            Saronite_Vapors_Timer = 30000;
        }else Saronite_Vapors_Timer -= diff;

        // Enrage
        if (Berserk_Timer < diff && !berserk)
        {
            me->CastStop();
            DoCast(me, SPELL_BERSERK);
            berserk = true;
        }else Berserk_Timer -= diff;

        DoMeleeAttackIfReady();
    }

};

CreatureAI* GetAI_boss_generalvezax(Creature *pCreature)
{
    return new boss_generalvezaxAI(pCreature);
}

struct mob_saronite_vaporsrAI : public ScriptedAI
{
    mob_saronite_vaporsrAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    void Reset() { }

    void JustDied(Unit *victim)
    {
        if (!victim)
            return;

        // Spawn trigger for the saronite debuff
        me->SummonCreature(MOB_SARONITE_DEBUFF, *me, TEMPSUMMON_TIMED_OR_DEAD_DESPAWN, 16000);
    }

    void UpdateAI(const uint32 diff)
    {
        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_saronite_vaporsr(Creature *pCreature)
{
    return new mob_saronite_vaporsrAI(pCreature);
}

struct mob_saronite_debufferAI : public ScriptedAI
{
    mob_saronite_debufferAI(Creature *pCreature) : ScriptedAI(pCreature)
    {
        Reset();
    }

    uint32 Debuff_Timer;

    void Reset()
    {
        Debuff_Timer = 500;
    }

    void UpdateAI(const uint32 diff)
    {
        // Debuff for Mana
        if (Debuff_Timer < diff)
        {
            DoCast(me, SPELL_SARONITE_VAPOR, true);
            Debuff_Timer = 16000;
        }else Debuff_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_saronite_debuffer(Creature *pCreature)
{
    return new mob_saronite_debufferAI(pCreature);
}

struct boss_saronite_animusAI : public BossAI
{
    boss_saronite_animusAI(Creature *pCreature) : BossAI(pCreature, TYPE_SARONITE_ANIMUS)
    {
        m_pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }
    ScriptedInstance *m_pInstance;
    uint32 ProfoundDarkness_Timer;
    void Reset()
    {
    ProfoundDarkness_Timer = 1000;
    }


    void JustDied(Unit * victim, ScriptedInstance* m_pInstance, Map *m_pMap)
    {
     if (Creature *Vezax = m_pMap->GetCreature(m_pInstance->GetData64(TYPE_VEZAX)))
        Vezax->RemoveAurasDueToSpell(63364);
        if (m_pInstance)
            m_pInstance->SetData(TYPE_SARONITE_ANIMUS, DONE);
    }

    void EnterCombat(Unit* pWho)
    {
        DoScriptText(SAY_UR_Vezax_Hard, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
        // Profound Darkness
        if (ProfoundDarkness_Timer < diff )
        {
            DoCast(me, SPELL_PROFOUND_OF_DARKNESS);
            ProfoundDarkness_Timer = 2000;
        }else ProfoundDarkness_Timer -= diff;
        
        DoMeleeAttackIfReady();

    }
};

CreatureAI* GetAI_boss_saronite_animus(Creature* pCreature)
{
    return new boss_saronite_animusAI(pCreature);
}

void AddSC_boss_vezax()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_generalvezax";
    newscript->GetAI = &GetAI_boss_generalvezax;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_saronite_vaporsr";
    newscript->GetAI = &GetAI_mob_saronite_vaporsr;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_saronite_debuffer";
    newscript->GetAI = &GetAI_mob_saronite_debuffer;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "mob_saronite_animus";
    newscript->GetAI = &GetAI_boss_saronite_animus;
    newscript->RegisterSelf();
}