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
SDName: Boss_Majordomo_Executus
SD%Complete: 30
SDComment: Correct spawning and Event NYI
SDCategory: Molten Core
EndScriptData */

#include "ScriptedPch.h"
#include "molten_core.h"

#define SAY_AGGRO           -1409003
#define SAY_SPAWN           -1409004
#define SAY_SLAY            -1409005
#define SAY_SPECIAL         -1409006
#define SAY_DEFEAT          -1409007

#define SAY_SUMMON_MAJ      -1409008
#define SAY_ARRIVAL1_RAG    -1409009
#define SAY_ARRIVAL2_MAJ    -1409010
#define SAY_ARRIVAL3_RAG    -1409011
#define SAY_ARRIVAL5_RAG    -1409012

#define SPAWN_RAG_X         838.51
#define SPAWN_RAG_Y         -829.84
#define SPAWN_RAG_Z         -232.00
#define SPAWN_RAG_O         1.70

#define SPELL_MAGIC_REFLECTION      20619
#define SPELL_DAMAGE_REFLECTION     21075

#define SPELL_BLASTWAVE             20229
#define SPELL_AEGIS                 20620                   //This is self casted whenever we are below 50%
#define SPELL_TELEPORT              20618
#define SPELL_TELEPORT_RAG          20534
#define SPELL_TELEPORT_VISUAL       19484
#define SPELL_SUMMON_RAGNAROS       19774

#define SPELL_ELEMENTAL_FIRE        19773                   // Ragnaros kills Majordomo

#define SPELL_FRENZY                19953                  // not sure

//adds spells
//flamewalker elite
#define SPELL_BLAST_WAVE            20229 
#define SPELL_FIRE_BLAST            20623
//flamewalker healer
#define SPELL_SHADOW_SHOCK          20603
#define SPELL_HEAL_BRETHREN         26565

//#define ENTRY_FLAMEWALKER_HEALER    11663
//#define ENTRY_FLAMEWALKER_ELITE     11664

//#define NPC_MAJORDOMO               12018
#define NPC_FLAMEWAKER_HEALER       11663
#define NPC_FLAMEWAKER_ELITE        11664

Position posNewHome = {830, -814, -229, 5.3};

enum 
{
    INTRO_START,
    INTRO_FINISH
};

struct boss_majordomoAI : public ScriptedAI
{
    boss_majordomoAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = me->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    uint32 MagicReflection_Timer;
    uint32 DamageReflection_Timer;
    uint32 Blastwave_Timer;
    uint32 uiTeleportTimer;
    uint32 uiAddsDeadCounter;
    uint32 uiDefeatTimer;
    uint32 uiIntroPhase;
    uint32 uiIntroTimer;

    bool bDefeat;
    bool bRagTele;
    bool bRagIntro;
    bool bRagIntroStart;

    void Reset()
    {
        MagicReflection_Timer =  30000;                     //Damage reflection first so we alternate
        DamageReflection_Timer = 15000;
        Blastwave_Timer = 10000;
        uiTeleportTimer = urand(20000, 40000);
        uiAddsDeadCounter = 0;
        uiDefeatTimer = 30000;
        uiIntroPhase = 0;
        uiIntroTimer = 15000;

        bRagTele = false;
        bRagIntro = false;
        bRagIntroStart = false;

        if (pInstance && pInstance->GetData(DATA_MAJORDOMO_EVENT) != DONE)
        {
            bDefeat = false;
            pInstance->SetData(DATA_MAJORDOMO_EVENT, NOT_STARTED);
        }
        else
        {
            me->setFaction(35);
            bDefeat = true;
            me->SetHomePosition(posNewHome);
        }
    }

    void KilledUnit(Unit* victim)
    {
        if (rand()%5)
            return;

        DoScriptText(SAY_SLAY, m_creature);
    }

    void DoAction(const int32 param)
    {
        ++uiAddsDeadCounter;
        if (uiAddsDeadCounter == 7)
            DoCast(SPELL_FRENZY);

        if (uiAddsDeadCounter == 8)
        {
            if (pInstance)
                pInstance->SetData(DATA_MAJORDOMO_EVENT, DONE);
            bDefeat = true;
            me->setFaction(35);
            DoScriptText(SAY_DEFEAT, me);
            me->SetReactState(REACT_DEFENSIVE);
            Evade();
        }
    }

    void EnterCombat(Unit *who)
    {
        DoZoneInCombat();
        DoScriptText(SAY_AGGRO, m_creature);
        if (pInstance)
            pInstance->SetData(DATA_MAJORDOMO_EVENT, IN_PROGRESS);
    }

    void JustDied(Unit* killer)
    {
        if (pInstance)
            pInstance->SetData(DATA_MAJORDOMO_EVENT, DONE);
    }

    void Evade()
    {
        _EnterEvadeMode();
        me->GetMotionMaster()->MoveTargetedHome();
        Reset();
    }

    void MoveInLineOfSight(Unit *who)
    {
        if (pInstance && pInstance->GetData(DATA_MAJORDOMO_EVENT) == DONE)
            if (who->GetTypeId() == TYPEID_PLAYER && bRagTele && !bRagIntro)
            {
                DoCast(SPELL_SUMMON_RAGNAROS);
                DoScriptText(SAY_SUMMON_MAJ, me);
                if (Creature* pRagnaros = Creature::GetCreature(*me, pInstance->GetData64(DATA_RAGNAROS)))
                    pRagnaros->AI()->DoAction(INTRO_START);
                bRagIntro = true;
            }
    }



    void Intro(uint32 diff)
    {
        if (uiIntroTimer <= diff)
        {
            switch (uiIntroPhase)
            {
            case 0:
                if (Creature* pRagnaros = Creature::GetCreature(*me, pInstance->GetData64(DATA_RAGNAROS)))
                    pRagnaros->SetPhaseMask(1, true);

                ++uiIntroPhase;
                uiIntroTimer = 7*IN_MILISECONDS;
                break;
            case 1:
                if (Creature* pRagnaros = Creature::GetCreature(*me, pInstance->GetData64(DATA_RAGNAROS)))
                {
                    DoScriptText(SAY_ARRIVAL1_RAG, pRagnaros);
                    pRagnaros->HandleEmoteCommand(EMOTE_STATE_ROAR);
                }
                ++uiIntroPhase;
                uiIntroTimer = 14*IN_MILISECONDS;
                break;
            case 2:
                DoScriptText(SAY_ARRIVAL2_MAJ, me);
                ++uiIntroPhase;
                uiIntroTimer = 8*IN_MILISECONDS;
                break;
            case 3:
                if (Creature* pRagnaros = Creature::GetCreature(*me, pInstance->GetData64(DATA_RAGNAROS)))
                {
                    pRagnaros->HandleEmoteCommand(EMOTE_STATE_ROAR);
                    DoScriptText(SAY_ARRIVAL3_RAG, pRagnaros);
                }
                ++uiIntroPhase;
                uiIntroTimer = 16*IN_MILISECONDS;
                break;
            case 4:
                bRagIntro = false;
                if (Creature* pRagnaros = Creature::GetCreature(*me, pInstance->GetData64(DATA_RAGNAROS)))
                {
                    pRagnaros->AI()->DoAction(INTRO_FINISH);
                    pRagnaros->CastSpell(me, SPELL_ELEMENTAL_FIRE, false);
                }
            }
        } else uiIntroTimer -= diff;
    }


    void UpdateAI(const uint32 diff)
    {
        if (bDefeat)
        {
            if (!bRagTele)
            {
                if (uiDefeatTimer <= diff)
                {
                    me->SetReactState(REACT_AGGRESSIVE);
                    DoCast(me, SPELL_TELEPORT_RAG);
                    bRagTele = true;
                }
                else
                    uiDefeatTimer -= diff;
            }

            if (bRagIntro)
                Intro(diff);
        }

        if (!UpdateVictim())
            return;

        //Cast Ageis if less than 50% hp
        if (m_creature->GetHealth()*100 / m_creature->GetMaxHealth() < 50)
        {
            DoCast(m_creature, SPELL_AEGIS);
        }

        if (uiTeleportTimer <= diff)
        {
            if (Unit *pTarget = me->SelectNearestTarget(100))
                pTarget->CastSpell(pTarget, SPELL_TELEPORT, false);

            DoResetThreat();

            uiTeleportTimer = urand(20000, 40000);
        } else uiTeleportTimer -= diff;

        //MagicReflection_Timer
        if (MagicReflection_Timer <= diff)
        {
    //        DoCast(m_creature, SPELL_MAGIC_REFLECTION);
            me->AddAura(SPELL_MAGIC_REFLECTION, me);

            //60 seconds until we should cast this again
            MagicReflection_Timer = 30000;
        } else MagicReflection_Timer -= diff;

        //DamageReflection_Timer
        if (DamageReflection_Timer <= diff)
        {
       //     DoCast(m_creature, SPELL_DAMAGE_REFLECTION);
            me->AddAura(SPELL_DAMAGE_REFLECTION, me);

            //60 seconds until we should cast this again
            DamageReflection_Timer = 30000;
        } else DamageReflection_Timer -= diff;

        //Blastwave_Timer
        if (Blastwave_Timer <= diff)
        {
            DoCast(SPELL_BLASTWAVE);
            Blastwave_Timer = 10000;
        } else Blastwave_Timer -= diff;

        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_boss_majordomo(Creature* pCreature)
{
    return new boss_majordomoAI (pCreature);
}

struct npc_majordomoAddsAI : public ScriptedAI
{
    npc_majordomoAddsAI(Creature *c) : ScriptedAI(c)
    {
        pInstance = me->GetInstanceData();
    }

    ScriptedInstance* pInstance;

    uint32 uiShieldTimer;
    uint32 DamageReflection_Timer;
    uint32 Blastwave_Timer;
    uint32 uiFireBlastTimer;
    uint32 uiShadowShockTimer;
    uint32 uiHealTimer;

    void Reset()
    {
        uiShieldTimer =  urand(20000, 30000);

        switch (me->GetEntry())
        {
        case NPC_FLAMEWAKER_ELITE:
            Blastwave_Timer = 10000;
            uiFireBlastTimer = 15000;
            break;
        case NPC_FLAMEWAKER_HEALER:
            uiShadowShockTimer = 2000;
            uiHealTimer = urand(15000, 20000);
            break;
        }
    }

    void JustDied(Unit* who)
    {
        if (pInstance)
            if (Creature* pDomo = Creature::GetCreature(*me, pInstance->GetData64(DATA_MAJORDOMO)))
                pDomo->AI()->DoAction(NULL);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiShieldTimer <= diff)
        {
            me->AddAura(RAND(SPELL_MAGIC_REFLECTION, SPELL_DAMAGE_REFLECTION), me);
       //     DoCast(m_creature, RAND(SPELL_MAGIC_REFLECTION, SPELL_DAMAGE_REFLECTION));
            uiShieldTimer = urand(20000, 30000);
        } else uiShieldTimer -= diff;

        switch (me->GetEntry())
        {
        case NPC_FLAMEWAKER_ELITE:
            if (Blastwave_Timer <= diff)
            {
                DoCast(SPELL_BLAST_WAVE);
                Blastwave_Timer = 10000;
            } else Blastwave_Timer -= diff;

            if (uiFireBlastTimer <= diff)
            {
                DoCast(SPELL_FIRE_BLAST);
                uiFireBlastTimer = 15000;
            } else uiFireBlastTimer -= diff;

            break;
        case NPC_FLAMEWAKER_HEALER:
            if (uiShadowShockTimer <= diff)
            {
                if (Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 100, true))
                    DoCast(pTarget, SPELL_SHADOW_SHOCK);
                uiShadowShockTimer = 2000;
            } else uiShadowShockTimer -= diff;

            if (uiHealTimer <= diff)
            {
                if (Unit* pTarget = DoSelectLowestHpFriendly(200))
                    DoCast(pTarget, SPELL_HEAL_BRETHREN);
                uiHealTimer = urand(15000, 20000);
            } else uiHealTimer -= diff;
            break;
        }
        DoMeleeAttackIfReady();
    }
};
CreatureAI* GetAI_npc_majordomoAdds(Creature* pCreature)
{
    return new npc_majordomoAddsAI (pCreature);
}
void AddSC_boss_majordomo()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_majordomo";
    newscript->GetAI = &GetAI_boss_majordomo;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_majordomoAdds";
    newscript->GetAI = &GetAI_npc_majordomoAdds;
    newscript->RegisterSelf();
}