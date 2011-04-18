/* Copyright (C) 2008 - 2009 Trinity <http://www.trinitycore.org/>
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

#define SAY_AGGRO           RAND(-1533109,-1533110,-1533111)
#define SAY_SLAY            -1533112
#define SAY_TAUNT           RAND(-1533113,-1533114,-1533115,-1533116,-1533117)
#define SAY_DEATH           -1533118

#define SPELL_SPELL_DISRUPTION  29310
#define SPELL_DECREPIT_FEVER    RAID_MODE(29998,55011)
#define SPELL_PLAGUE_CLOUD      29350

enum Events
{
    EVENT_NONE,
    EVENT_DISRUPT,
    EVENT_FEVER,
    EVENT_ERUPT,
    EVENT_PHASE,
};

enum Phases
{
    PHASE_FIGHT = 1,
    PHASE_DANCE,
};

enum Achievements
{
    ACHIEV_THE_SAFETY_DANCE_10       = 1996,
    ACHIEV_THE_SAFETY_DANCE_25       = 2139
};

struct boss_heiganAI : public BossAI
{
    boss_heiganAI(Creature *c) : BossAI(c, BOSS_HEIGAN) {}

    uint32 eruptSection;
    uint32 uiCheckAchievTimer;
    bool eruptDirection;
    bool bAchievSavety;
    Phases phase;

    void Reset()
    {
        _Reset();
        bAchievSavety = true;
        uiCheckAchievTimer = 1*IN_MILISECONDS;
    }

    void KilledUnit(Unit* Victim)
    {
        bAchievSavety = false;
        if (!(rand()%5))
            DoScriptText(SAY_SLAY, me);
    }

    void JustDied(Unit* Killer)
    {
        _JustDied();
        DoScriptText(SAY_DEATH, me);
		
        if (bAchievSavety)
            if  (ScriptedInstance* pInstance = me->GetInstanceData())
                pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_THE_SAFETY_DANCE_10, ACHIEV_THE_SAFETY_DANCE_25));
    }

    void EnterCombat(Unit *who)
    {
        _EnterCombat();
        DoScriptText(SAY_AGGRO, me);
        EnterPhase(PHASE_FIGHT);
        if (Map *pInstance = me->GetInstanceData()->instance)
        {
            Map::PlayerList const &PlayerList = pInstance->GetPlayers();

            if (!PlayerList.isEmpty())
                for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                {
                    float fX = ((Player*)i->getSource())->GetPositionX();
                    float fY = ((Player*)i->getSource())->GetPositionY();
                    if (fX > 2722.0f && fX < 2824.0f && fY < -3639.0f && fY > -3735.0f)
                        continue;
                    EnterEvadeMode();
                }
		}
    }

    void EnterPhase(Phases newPhase)
    {
        phase = newPhase;
        events.Reset();
        eruptSection = 3;
        if (phase == PHASE_FIGHT)
        {
            events.ScheduleEvent(EVENT_DISRUPT, urand(10000, 25000));
            events.ScheduleEvent(EVENT_FEVER, urand(15000, 20000));
            events.ScheduleEvent(EVENT_PHASE, 90000);
            events.ScheduleEvent(EVENT_ERUPT, 15000);
        }
        else
        {
            float x, y, z, o;
            me->GetHomePosition(x, y, z, o);
            me->NearTeleportTo(x, y, z, o);
            DoCastAOE(SPELL_PLAGUE_CLOUD);
            events.ScheduleEvent(EVENT_PHASE, 45000);
            events.ScheduleEvent(EVENT_ERUPT, 8000);
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim() || !CheckInRoom())
            return;

        if (uiCheckAchievTimer <= diff)
        {
            if (Map *pInstance = me->GetInstanceData()->instance)
            {
                Map::PlayerList const &PlayerList = pInstance->GetPlayers();
                    if (!PlayerList.isEmpty())
                        for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
                            if (i->getSource()->isDead())
                                bAchievSavety = false;
            }
            uiCheckAchievTimer = 1*IN_MILISECONDS;
        } else
            uiCheckAchievTimer -= diff;

        events.Update(diff);

        while (uint32 eventId = events.ExecuteEvent())
        {
            switch(eventId)
            {
                case EVENT_DISRUPT:
                    DoCastAOE(SPELL_SPELL_DISRUPTION);
                    events.ScheduleEvent(EVENT_DISRUPT, urand(5000, 10000));
                    break;
                case EVENT_FEVER:
                    DoCastAOE(SPELL_DECREPIT_FEVER);
                    events.ScheduleEvent(EVENT_FEVER, urand(20000, 25000));
                    break;
                case EVENT_PHASE:
                    // TODO : Add missing texts for both phase switches
                    EnterPhase(phase == PHASE_FIGHT ? PHASE_DANCE : PHASE_FIGHT);
                    break;
                case EVENT_ERUPT:
                    instance->SetData(DATA_HEIGAN_ERUPT, eruptSection);
                    TeleportCheaters();

                    if (eruptSection == 0)
                        eruptDirection = true;
                    else if (eruptSection == 3)
                        eruptDirection = false;

                    eruptDirection ? ++eruptSection : --eruptSection;

                    events.ScheduleEvent(EVENT_ERUPT, phase == PHASE_FIGHT ? 10000 : 3000);
                    break;
            }
        }

        DoMeleeAttackIfReady();
		
	    EnterEvadeIfOutOfCombatArea(diff);
    }
};

CreatureAI* GetAI_boss_heigan(Creature* pCreature)
{
    return new boss_heiganAI (pCreature);
}

void AddSC_boss_heigan()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_heigan";
    newscript->GetAI = &GetAI_boss_heigan;
    newscript->RegisterSelf();
}