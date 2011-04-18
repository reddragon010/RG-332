/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
SDName: Boss_Ragnaros
SD%Complete: 75
SDComment: Intro Dialog and event NYI
SDCategory: Molten Core
EndScriptData */

#include "ScriptedPch.h"
#include "molten_core.h"

#define SAY_SUMMON_MAJ              -1409008
#define SAY_ARRIVAL1_RAG            -1409009
#define SAY_ARRIVAL2_MAJ            -1409010
#define SAY_ARRIVAL3_RAG            -1409011
#define SAY_ARRIVAL5_RAG            -1409012


#define SAY_REINFORCEMENTS1         -1409013
#define SAY_REINFORCEMENTS2         -1409014
#define SAY_HAND                    -1409015
#define SAY_WRATH                   -1409016
#define SAY_KILL                    -1409017
#define SAY_MAGMABURST              -1409018

#define SPELL_HANDOFRAGNAROS        19780
#define SPELL_WRATHOFRAGNAROS       20566
#define SPELL_LAVABURST             21158

#define SPELL_MAGMABURST            20565                   //Ranged attack

#define SPELL_SONSOFFLAME_DUMMY     21108                   //Server side effect
#define SPELL_RAGNAROS_SUBMERGE_FADE      21107                   //Stealth aura
#define SPELL_RAGNAROS_SUBMERGE_VISUAL 20567
#define SPELL_RAGEMERGE             20568
#define SPELL_MELTWEAPON            21388
#define SPELL_ELEMENTALFIRE         20564
#define SPELL_ERRUPTION             17731
#define SPELL_HEAL_RAGNAROS         19952
#define SPELL_FRENZY                19953
#define SPELL_ELEMENTAL_FIRE        19773                   //kills majordomo

#define GO_RAGNAROS                 178088                  //casts lavaburst?
#define NPC_SON_OF_FLAME            12143

enum 
{
    INTRO_START,
    INTRO_FINISH
};

#define ADD_1X 848.740356
#define ADD_1Y -816.103455
#define ADD_1Z -229.74327
#define ADD_1O 2.615287

#define ADD_2X 852.560791
#define ADD_2Y -849.861511
#define ADD_2Z -228.560974
#define ADD_2O 2.836073

#define ADD_3X 808.710632
#define ADD_3Y -852.845764
#define ADD_3Z -227.914963
#define ADD_3O 0.964207

#define ADD_4X 786.597107
#define ADD_4Y -821.132874
#define ADD_4Z -226.350128
#define ADD_4O 0.949377

#define ADD_5X 796.219116
#define ADD_5Y -800.948059
#define ADD_5Z -226.010361
#define ADD_5O 0.560603

#define ADD_6X 821.602539
#define ADD_6Y -782.744109
#define ADD_6Z -226.023575
#define ADD_6O 6.157440

#define ADD_7X 844.924744
#define ADD_7Y -769.453735
#define ADD_7Z -225.521698
#define ADD_7O 4.4539958

#define ADD_8X 839.823364
#define ADD_8Y -810.869385
#define ADD_8Z -229.683182
#define ADD_8O 4.693108

struct boss_ragnarosAI : public Scripted_NoMovementAI
{
    boss_ragnarosAI(Creature *c) : Scripted_NoMovementAI(c)
    {
        pInstance = me->GetInstanceData();
        uiRagnarosFaction = me->getFaction();
    }

    ScriptedInstance* pInstance;

    uint32 WrathOfRagnaros_Timer;
    uint32 HandOfRagnaros_Timer;
    uint32 LavaBurst_Timer;
    uint32 uiCheckMagmaBurstTimer;
    uint32 ElementalFire_Timer;
    uint32 Erruption_Timer;
    uint32 uiSubmerge_Timer;
    uint32 Attack_Timer;
    uint32 uiRagnarosFaction;
    uint32 uiMagma;

    bool HasYelledMagmaBurst;
    bool HasSubmergedOnce;
    bool WasBanished;
    bool HasAura;
    bool bMeleeRange;
    bool bIntro;
    bool bIntroStop;

    void Reset()
    {
        WrathOfRagnaros_Timer = 30000;
        HandOfRagnaros_Timer = 25000;
        LavaBurst_Timer = 10000;
        uiCheckMagmaBurstTimer = 5000;
        uiMagma = 0;
        Erruption_Timer = 15000;
        ElementalFire_Timer = 3000;
        uiSubmerge_Timer = 180000;
        Attack_Timer = 90000;
        HasYelledMagmaBurst = false;
        HasSubmergedOnce = false;
        WasBanished = false;
        bMeleeRange = false;
        bIntro = false;
        bIntroStop = false;

        me->RemoveAllAuras();

        DoCast(m_creature, SPELL_MELTWEAPON, true);
        HasAura = true;

        if (pInstance)
            pInstance->SetData(DATA_RAGNAROS_EVENT, NOT_STARTED);
    }

    void KilledUnit(Unit* victim)
    {
        if (rand()%5)
            return;

        DoScriptText(SAY_KILL, m_creature);
    }

    void EnterCombat(Unit* who)
    {
        DoZoneInCombat();
        if (pInstance)
            pInstance->SetData(DATA_RAGNAROS_EVENT, IN_PROGRESS);
    }

    void JustDied(Unit* killer)
    {
        if (pInstance)
            pInstance->SetData(DATA_RAGNAROS_EVENT, DONE);
    }

    void DoAction(const int32 param)
    {
        if (param == INTRO_START)
        {
            me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
            me->SetReactState(REACT_DEFENSIVE);
            me->DeleteThreatList();
            me->CombatStop(true);
        }
        else
            if (param == INTRO_FINISH)
            {
                me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE|UNIT_FLAG_NOT_SELECTABLE);
                me->SetReactState(REACT_AGGRESSIVE);
            }
    }

    void UpdateAI(const uint32 diff)
    {
        if (WasBanished && Attack_Timer <= diff)
        {
            //Become unbanished again
            m_creature->setFaction(uiRagnarosFaction);
            m_creature->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_AGGRESSIVE);
            DoCast(SPELL_RAGEMERGE);
            me->RemoveAurasDueToSpell(SPELL_RAGNAROS_SUBMERGE_VISUAL);
            me->RemoveAurasDueToSpell(SPELL_RAGNAROS_SUBMERGE_FADE);
            me->HandleEmoteCommand(EMOTE_ONESHOT_EMERGE);
            WasBanished = false;
        } else if (WasBanished)
        {
            Attack_Timer -= diff;
            //Do nothing while banished
            return;
        }

        //Return since we have no target
        if (!UpdateVictim())
            return;

        //WrathOfRagnaros_Timer
        if (WrathOfRagnaros_Timer <= diff)
        {
            DoCast(SPELL_WRATHOFRAGNAROS);

            if (urand(0,1))
                DoScriptText(SAY_WRATH, m_creature);

            WrathOfRagnaros_Timer = 30000;
        } else WrathOfRagnaros_Timer -= diff;

        //HandOfRagnaros_Timer 
        //if (HandOfRagnaros_Timer <= diff)
        //{
        //    DoCast(m_creature, SPELL_HANDOFRAGNAROS);

        //    if (urand(0,1))
        //        DoScriptText(SAY_HAND, m_creature);

        //    HandOfRagnaros_Timer = 25000;
        //} else HandOfRagnaros_Timer -= diff;

        //LavaBurst_Timer
        if (LavaBurst_Timer <= diff)
        {
            DoCast(SPELL_LAVABURST);
            LavaBurst_Timer = 10000;
        } else LavaBurst_Timer -= diff;

        //Erruption_Timer
        if (LavaBurst_Timer <= diff)
        {
            DoCast(SPELL_ERRUPTION);
            Erruption_Timer = urand(20000,45000);
        } else Erruption_Timer -= diff;

        //ElementalFire_Timer
        if (ElementalFire_Timer <= diff)
        {
            DoCast(SPELL_ELEMENTALFIRE);
            ElementalFire_Timer = urand(10000,14000);
        } else ElementalFire_Timer -= diff;

        //uiSubmerge_Timer
        if (!WasBanished && uiSubmerge_Timer <= diff)
        {
            //Creature spawning and ragnaros becomming unattackable
            //is not very well supported in the core
            //so added normaly spawning and banish workaround and attack again after 90 secs.
            me->HandleEmoteCommand(EMOTE_ONESHOT_SUBMERGE);
            DoScriptText(RAND(SAY_REINFORCEMENTS1, SAY_REINFORCEMENTS2), m_creature);

            //// summon 10 elementals
            for (uint8 i = 0; i < 9; ++i)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                {
                    if (Creature* pSummoned = m_creature->SummonCreature(NPC_SON_OF_FLAME, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(),0.0f,TEMPSUMMON_TIMED_OR_CORPSE_DESPAWN,900000))
                        pSummoned->AI()->AttackStart(pTarget);
                }
            }

            m_creature->InterruptNonMeleeSpells(false);
            //Root self
            DoCast(SPELL_RAGNAROS_SUBMERGE_VISUAL);
            DoCast(SPELL_RAGNAROS_SUBMERGE_FADE);
            //           DoCast(m_creature, 23973);  //ERROR: CastSpell: unknown spell id 23973
            m_creature->setFaction(35);
            m_creature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE|UNIT_FLAG_NON_ATTACKABLE);
            me->SetReactState(REACT_DEFENSIVE);
            WasBanished = true;
            Attack_Timer = 90000;
            uiSubmerge_Timer = 180000;
        } else uiSubmerge_Timer -= diff;

        if (uiCheckMagmaBurstTimer <= diff)
        {
            bMeleeRange = false;
            if (Map *pInstance = me->GetInstanceData()->instance)
            {
                Map::PlayerList const &PlayerList = pInstance->GetPlayers();

                if (!PlayerList.isEmpty())
                    for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                        if (i->getSource()->isAlive() && me->IsWithinMeleeRange(i->getSource()))
                        {
                            bMeleeRange = true;
                            break;
                        }

                if (!bMeleeRange)
                    if (Unit *ptarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                    {
                        DoCast(ptarget, SPELL_MAGMABURST);
                        if (!(++uiMagma%10))
                            DoScriptText(SAY_MAGMABURST, me);
                    }
            }
            uiCheckMagmaBurstTimer = 1*IN_MILISECONDS;
        } else
            uiCheckMagmaBurstTimer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_ragnaros(Creature* pCreature)
{
    return new boss_ragnarosAI (pCreature);
}

void AddSC_boss_ragnaros()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_ragnaros";
    newscript->GetAI = &GetAI_boss_ragnaros;
    newscript->RegisterSelf();
}