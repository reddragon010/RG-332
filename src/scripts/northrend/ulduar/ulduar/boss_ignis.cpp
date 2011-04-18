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

enum Yells
{
    SAY_AGGRO                     = -1610020,
    SAY_SCORCH_1                  = -1610021,
    SAY_SCORCH_2                  = -1610022,
    SAY_SLAG_POT                  = -1610023,
    EMOTE_FLAME_JETS              = -1610024,
    SAY_SUMMON                    = -1610025,
    SAY_SLAY_1                    = -1610026,
    SAY_SLAY_2                    = -1610027,
    SAY_BERSERK                   = -1610028,
    SAY_DEATH                     = -1610029
};

enum Spells
{
    SPELL_FLAME_JETS              = 62680,
    SPELL_FLAME_JETS_H            = 63472,
    SPELL_SCORCH                  = 62546,
    SPELL_SCORCH_H                = 63474,
    BUFF_STRENGHT_OF_CREATOR      = 64473,
    SPELL_BERSERK                 = 47008, // Wrong spellid? Berserk occurs extremly rare on retail.
    SPELL_SLAG_POT                = 62717,
    SPELL_SLAG_POT_H              = 63477,
    SPELL_SLAG_POT_DMG            = 65722,
    SPELL_SLAG_POT_DMG_H          = 65723,
    SPELL_SLAG_POT_HASTE          = 62836,
    SPELL_SLAG_POT_HASTE_H        = 63536,

    // Iron construct
    SPELL_ACTIVATE                = 62488,
    SPELL_HEAT                    = 65667,
    SPELL_MOLTEN                  = 62373,
    SPELL_BRITTLE                 = 67114,
    SPELL_BRITTLE_H               = 62382,
    SPELL_SHATTER                 = 62383,
    SPELL_STONED                  = 62468,

    // Scorch target
    AURA_SCORCH                   = 62548,
    AURA_SCORCH_H                 = 63476
};


enum Achievs
{
    ACHIEV_HOT_POCKET             = 2927,     // Survive being thrown into Ignis the Furnace Master's Slag Pot in 10-player mode. 
    ACHIEV_HOT_POCKET_H           = 2928,     // Survive being thrown into Ignis the Furnace Master's Slag Pot in 25-player mode. 

    ACHIEV_STOKING_THE_FURNACE    = 2930,     // Defeat Ignis the Furnace Master in 4 minutes in 10-player mode. 
    ACHIEV_STOKING_THE_FURNACE_H  = 2929      // Defeat Ignis the Furnace Master in 4 minutes in 25-player mode. 
};

enum Npcs
{
    MOB_IRON_CONSTRUCT            = 33121,
    MOB_SCORCH_TARGET             = 33221
};

// scorch target
struct mob_scorch_targetAI : public ScriptedAI
{
    mob_scorch_targetAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 Death_Timer;

    void Reset()
    {
        Death_Timer = 55000;
        me->SetDisplayId(11686);
        // Seriously, to much flags?
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        DoCast(me, RAID_MODE(AURA_SCORCH, AURA_SCORCH_H));
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (Death_Timer <= diff)
        {
            me->DealDamage(me, me->GetHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
        }else Death_Timer -= diff;
    }
};

CreatureAI* GetAI_mob_scorch_target(Creature* pCreature)
{
    return new mob_scorch_targetAI (pCreature);
}

float WaterposX[2];
float WaterposY[2];
float WaterposZ[2];

// Iron construct
struct mob_iron_constructAI : public ScriptedAI
{
    mob_iron_constructAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 Aura_Check_Timer;
    uint32 BrittleDeath_Timer;

    bool brittle;
    bool molten;

    void Reset()
    {
        brittle = false;
        molten = false;
        Aura_Check_Timer = 1000;
        BrittleDeath_Timer = 10000;
        DoCast(me, SPELL_STONED);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);

        WaterposX[1] = 646.5789; WaterposY[1] = 277.888; WaterposZ[1] = 359.03; // Right
        WaterposX[2] = 526.1715; WaterposY[2] = 276.869; WaterposZ[2] = 360.18; // Left
    }

    void JustDied(Unit* pKiller, Aura *pAura)
    {
        if (Creature* pTemp = me->FindNearestCreature(NPC_IGNIS, 500))
        {
            if (pTemp->isAlive())
                if (pTemp->HasAura(BUFF_STRENGHT_OF_CREATOR))
                {
                     if (Aura *pAura = me->GetAura(BUFF_STRENGHT_OF_CREATOR))
                        pAura->SetStackAmount(pAura->GetStackAmount() +1);
                    else
                        pAura->SetStackAmount(pAura->GetStackAmount() -1);

                }
        }
    }

    void DamageTaken(Unit* done_by, uint32 &damage)
    {
        if (brittle)
            if (damage > RAID_MODE(3000,5000))
            {
                DoCast(me, SPELL_SHATTER);
                BrittleDeath_Timer = 1500;
            }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (!me->HasAura(RAID_MODE(SPELL_BRITTLE,SPELL_BRITTLE_H),0))
            brittle = false;

        if (!me->HasAura(SPELL_MOLTEN,0))
            molten = false;

        if (BrittleDeath_Timer <= diff && brittle)
        {
            me->DisappearAndDie();
        }else BrittleDeath_Timer -= diff;

        if (Aura_Check_Timer <= diff)
        {
            if (Aura* pAura = me->GetAura(SPELL_HEAT,0))
                if (pAura->GetStackAmount() > 19)
                {
                    DoCast(me, SPELL_MOLTEN, true);
                    if (DoGetThreat(me->getVictim()))
                        DoModifyThreatPercent(me->getVictim(),-100); // Drop threat
                    molten = true;
                }

            // Using 1 sec timer to update molten spell
            if (molten && !brittle)
                DoCast(me, SPELL_MOLTEN);

            Aura_Check_Timer = 1000;
        }else Aura_Check_Timer -= diff;

        if (molten)
        {
            me->RemoveAurasDueToSpell(SPELL_HEAT);
            if ((me->GetDistance(WaterposX[1], WaterposY[1], WaterposZ[1]) <= 22)
               || (me->GetDistance(WaterposX[2], WaterposY[2], WaterposZ[2]) <= 22))
            {
                DoCast(me, SPELL_STONED);
                DoCast(me, SPELL_BRITTLE);
                me->RemoveAurasDueToSpell(SPELL_MOLTEN);
                brittle = true;
            }
        }

        if (!brittle)
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_iron_construct(Creature* pCreature)
{
    return new mob_iron_constructAI (pCreature);
}

// Ignis the furnace master
struct boss_ignisAI : public ScriptedAI
{
    boss_ignisAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance *pInstance;

    uint64 uiPotTarget;

    uint32 Flame_Jets_Timer;
    uint32 Slag_Pot_Timer;
    uint32 Slag_Pot_Dmg_Timer;
    uint32 Scorch_Timer;
    uint32 Summon_Timer;
    uint32 KillingTimer;

    uint8  Damagecount;

    void Reset()
    {
        ShowAdds();
        DespawnScorch();
        Flame_Jets_Timer = 20000;
        Scorch_Timer = 16000;
        Summon_Timer = RAID_MODE(30000, 40000);
        Slag_Pot_Timer = 28000;
        Slag_Pot_Dmg_Timer = 50000;
        Damagecount = 0;
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, me);
    }

    void KilledUnit(Unit* pVictim)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
    }

    void JustDied(Unit* pKiller)
    {
        if (pInstance)
            pInstance->SetData(TYPE_IGNIS, DONE);

        DoScriptText(SAY_DEATH, me);
        ShowAdds(false);
        DespawnScorch();

        // Achievement: Strokin' the Furnace
        if (pInstance && KillingTimer > 0)
            pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_STOKING_THE_FURNACE, ACHIEV_STOKING_THE_FURNACE_H));

    }

    void ShowAdds(bool show = true)
    {
        std::list<Creature*> IronConstruct;
        GetCreatureListWithEntryInGrid(IronConstruct, me, MOB_IRON_CONSTRUCT, 700.f);
        for (std::list<Creature*>::iterator itr1 = IronConstruct.begin(); itr1 != IronConstruct.end(); itr1++)
        {
            if (show)
                (*itr1)->SetVisibility(VISIBILITY_ON);
            else
            {
                (*itr1)->DisappearAndDie();

                if ((*itr1))
                    (*itr1)->Respawn();
            }
        }
    }

    void DespawnScorch()
    {
        std::list<Creature*> ScorchTrigger;
        GetCreatureListWithEntryInGrid(ScorchTrigger, me, MOB_SCORCH_TARGET, 700.f);
        for (std::list<Creature*>::iterator itr2 = ScorchTrigger.begin(); itr2 != ScorchTrigger.end(); itr2++)
        {
            (*itr2)->DisappearAndDie();
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Not Blizzlike, anti-exploit to prevent players from pulling bosses to vehicles.
        if (me->GetPositionY() < 150 || me->GetPositionX() < 450)
        {
            me->DisappearAndDie();
        }

        me->RemoveAurasDueToSpell(SPELL_HEAT);


        // KillTimer for the achievement
        if (KillingTimer <= diff)
            KillingTimer = 0;
        else
            KillingTimer -= diff;


        // Flame Jets 
        if (Flame_Jets_Timer <= diff)
        {
            DoScriptText(EMOTE_FLAME_JETS, me);
            DoCast(me, RAID_MODE(SPELL_FLAME_JETS, SPELL_FLAME_JETS_H));
            Flame_Jets_Timer = 20000;
        }else Flame_Jets_Timer -= diff;   


        // Summon Iron Construct
        if (Summon_Timer <= diff)
        {
            DoScriptText(SAY_SUMMON, me);
            if (Creature* TempIron = me->FindNearestCreature(MOB_IRON_CONSTRUCT, 700))
            {
                if (TempIron->isAlive())
                {
                    DoCast(TempIron, SPELL_ACTIVATE);
                    TempIron->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    TempIron->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    TempIron->RemoveAurasDueToSpell(SPELL_STONED);
                    TempIron->AI()->AttackStart(SelectTarget(SELECT_TARGET_RANDOM, 0, 700, true));
                }else return;
            }
            else // If all constructs are dead.
            {
                DoCast(me, SPELL_BERSERK);
                DoScriptText(SAY_BERSERK, me);
            }
            Summon_Timer = RAID_MODE(30000, 40000);

            if (Aura *buffAura = me->GetAura(BUFF_STRENGHT_OF_CREATOR))
                buffAura->SetStackAmount(buffAura->GetStackAmount() + 1);
            else DoCast(me, BUFF_STRENGHT_OF_CREATOR, true);
        }else Summon_Timer -= diff;


        // Scorch
        if (Scorch_Timer <= diff)
        {
            DoScriptText(RAND(SAY_SCORCH_1, SAY_SCORCH_2), me);
            DoCast(me->getVictim(), RAID_MODE(SPELL_SCORCH, SPELL_SCORCH_H));
            me->SummonCreature(MOB_SCORCH_TARGET, me->getVictim()->GetPositionX(), me->getVictim()->GetPositionY(), me->getVictim()->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 50000);
            Scorch_Timer = 28000;
        }else Scorch_Timer -= diff;


        // Slag Pot
        if (Slag_Pot_Timer <= diff)
        {
            DoScriptText(SAY_SLAG_POT, me);
            if (Unit* target = SelectTarget(SELECT_TARGET_RANDOM, 0, 700, true))
            {
                DoCast(target, RAID_MODE(SPELL_SLAG_POT, SPELL_SLAG_POT_H));
                uiPotTarget = target->GetGUID();
                Slag_Pot_Dmg_Timer = 1000;
            }
            Slag_Pot_Timer = 28000;
        }else Slag_Pot_Timer -= diff;
        

        // Slag Pot Damage
        if (Slag_Pot_Dmg_Timer <= diff)
        {
            if (Player* pPotTarget = Unit::GetPlayer(uiPotTarget))
            {
                if (Damagecount < 10)
                {
                    DoCast(pPotTarget, RAID_MODE(SPELL_SLAG_POT_DMG, SPELL_SLAG_POT_DMG_H));
                    Damagecount++;
                    Slag_Pot_Dmg_Timer = 1000;
                }
                else if (Damagecount == 10)
                {
                    DoCast(pPotTarget, RAID_MODE(SPELL_SLAG_POT_DMG, SPELL_SLAG_POT_DMG_H));
                    pPotTarget->CastSpell(pPotTarget, RAID_MODE(SPELL_SLAG_POT_HASTE, SPELL_SLAG_POT_HASTE_H), true);
                    Damagecount = 0;
                    Slag_Pot_Dmg_Timer = 50000;
                }

                // Achievement: Hot Pocket
                if (pPotTarget->isAlive())
                {
                    AchievementEntry const *AchievPot = GetAchievementStore()->LookupEntry(RAID_MODE(ACHIEV_HOT_POCKET, ACHIEV_HOT_POCKET_H));
                    pPotTarget->CompletedAchievement(AchievPot);
                }
            }
        }else Slag_Pot_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_ignis(Creature* pCreature)
{
    return new boss_ignisAI (pCreature);
}

void AddSC_boss_ignis()
{
    Script* newscript;

    newscript = new Script;
    newscript->Name = "mob_scorch_target";
    newscript->GetAI = &GetAI_mob_scorch_target;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_iron_construct";
    newscript->GetAI = &GetAI_mob_iron_construct;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_ignis";
    newscript->GetAI = &GetAI_boss_ignis;
    newscript->RegisterSelf();
}