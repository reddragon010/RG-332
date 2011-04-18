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

#define SAY_GREET             "Welcome, champions! All of our attempts at grounding her have failed. We could use a hand in bring her down with these harpoon guns."
#define SAY_AGGRO_1           "Give us a moment to prepare to build the turrets."
#define SAY_AGGRO_2           "Be on the lookout! Mole machines will be surfacing soon with those nasty Iron dwarves aboard!"
#define SAY_AGGRO_3           "Ready to move out, keep those dwarves off of our backs!"
#define SAY_GROUND_PHASE      "Move! Quickly! She won?t remain grounded for long."
#define SAY_TURRETS           "Fires out! Let's rebuild those turrets!"

#define GOSSIP_ITEM_1         "Activate Harpoones!"
#define EMOTE_HARPOON         "Harpoon Turret is ready for use!"
#define EMOTE_BREATH          "Razorscale takes a deep breath..."
#define EMOTE_PERMA           "Razorscale grounded permanently!"

enum Spells
{
    SPELL_FLAMEBUFFET             = 64016,
    SPELL_FIREBALL_10             = 62796,
    SPELL_FIREBALL_25             = 63815,
    SPELL_FLAME_GROUND_10         = 64709,
    SPELL_FLAME_GROUND_25         = 64734,
    SPELL_WINGBUFFET              = 62666,
    SPELL_FLAMEBREATH_10          = 63317,
    SPELL_FLAMEBREATH_25          = 64021,
    SPELL_FUSEARMOR               = 64771,
    SPELL_DEVOURINGFLAME_10       = 63236,
    SPELL_DEVOURINGFLAME_25       = 64733,
    SPELL_HARPOON                 = 54933,
    SPELL_FLAMED                  = 62696,
    SPELL_STUN                    = 9032,
    SPELL_BERSERK                 = 47008
};

const Position Harpoon1 = { 590.442322, -130.550278, 391.516998, 4.789456};
const Position Harpoon2 = { 574.850159, -133.687439, 391.517151, 4.789456};
 
const Position pos1 = {614.975403, -155.138214, 391.517090, 4.154516};
const Position pos2 = {609.814331, -204.968185, 391.517090, 5.385465};
const Position pos3 = {563.530884, -201.557312, 391.517090, 4.108194};
const Position pos4 = {560.231260, -153.677198, 391.517090, 5.402720};

const Position RazorFlight = {588.050293, -251.191223, 470.535980, 1.605303};
const Position RazorGround = {582.101135, -175.312286, 390.516998, 1.691704};
const Position WATCHER1 = {629.309, -197.959, 391.516, 1.691704};
const Position WATCHER2 = {561.045, -214.221, 391.516, 1.691704};
const Position WATCHER3 = {541.707, -166.307, 391.516, 1.691704};

enum Mobs
{
    RAZORSCALE                    = 33186,
    NPC_DARK_RUNE_GUARDIAN        = 33388,
    NPC_DARK_RUNE_SENTINEL        = 33846,
    NPC_DARK_RUNE_WATCHER         = 33453,
    MOLE_MACHINE_TRIGGER          = 33282,
};

enum DarkRuneSpells
{
    // Dark Rune Watcher
    SPELL_CHAIN_LIGHTNING_10      = 64758,
    SPELL_CHAIN_LIGHTNING_25      = 64759,
    SPELL_LIGHTNING_BOLT_10       = 63809,
    SPELL_LIGHTNING_BOLT_25       = 64696,
   
    // Dark Rune Guardian
    SPELL_STORMSTRIKE             = 64757,
   
    // Dark Rune Sentinel
    SPELL_BATTLE_SHOUT_10         = 46763,
    SPELL_BATTLE_SHOUT_25         = 64062,
    SPELL_HEROIC_STRIKE           = 45026,
    SPELL_WHIRLWIND_10            = 63807,
    SPELL_WHIRLWIND_25            = 63808,
   
    // Dark Iron Mole Machine
    SPELL_MOLE_MACHINE            = 43561
};

#define ACHIEVEMENT_QUICK_SHAVE     RAID_MODE(2919, 2921)

enum Phases
{
    PHASE_NULL = 0,
    PHASE_PERMAGROUND,
    PHASE_GROUND,
    PHASE_FLIGHT
};

enum Events
{
    EVENT_NONE,
    EVENT_BERSERK,
    EVENT_BREATH,
    EVENT_BUFFET,
    EVENT_HARPOON,
    EVENT_FIREBALL,
    EVENT_FLIGHT,
    EVENT_DEVOURING,
    EVENT_FLAME,
    EVENT_LAND,
    EVENT_GROUND,
    EVENT_FUSE,
    EVENT_SUMMON
};

struct boss_razorscaleAI : public BossAI
{
    boss_razorscaleAI(Creature *pCreature) : BossAI(pCreature, TYPE_RAZORSCALE)
        , phase(PHASE_NULL)
    {
        // Do not let Razorscale be affected by Battle Shout buff
        me->ApplySpellImmune(0, IMMUNITY_ID, RAID_MODE(SPELL_BATTLE_SHOUT_10, SPELL_BATTLE_SHOUT_25), true);
        pInstance = pCreature->GetInstanceData();
        pMap = me->GetMap();
        PermaGround = false;
        wipe = false;
    }

    Phases phase;
    ScriptedInstance* pInstance;
    Map* pMap;
   
    uint32 EnrageTimer;
    uint32 FlyCount;
   
    Creature* Harpoon[2];
    Creature* MoleTrigger;
    bool PermaGround;
    bool wipe;

    void Reset()
    {
        _Reset();
        me->SetFlying(true);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        me->GetMotionMaster()->MovePoint(0,RazorGround);
       
        // Expedition Commander respawn
        if (wipe)
        {
            if (Creature* pCommander = Unit::GetCreature(*me, pInstance->GetData64(DATA_EXP_COMMANDER)))
            {
                me->ForcedDespawn();
                me->SetVisibility(VISIBILITY_OFF);
                pCommander->SetVisibility(VISIBILITY_ON);
                pCommander->Respawn();
            }
        }
    }

    void EnterCombat(Unit* who)
    {
        _EnterCombat();
        if (Harpoon[0] = me->SummonCreature(NPC_FIRE_STATE, 589.922974, -133.621994, 391.517090, 4.789456, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 0))
            Harpoon[0]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        if (Harpoon[1] = me->SummonCreature(NPC_FIRE_STATE, 571.947021, -136.011993, 391.516998, 4.789456, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 0))
            Harpoon[1]->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE);
        me->SetSpeed(MOVE_RUN, 3.0f);
        me->SetSpeed(MOVE_FLIGHT, 3.0f);
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_PASSIVE);
        phase = PHASE_GROUND;
        events.SetPhase(PHASE_GROUND);
        wipe = true;
        FlyCount = 0;
        EnrageTimer = 15*60*1000; // Enrage in 15 min
        events.ScheduleEvent(EVENT_FLIGHT, 0, 0, PHASE_GROUND);
        DoZoneInCombat();
    }

    void JustDied(Unit* Killer)
    {
        _JustDied();
       
        // Achievements
        if (pInstance)
        {
            // A Quick Shave
            if (FlyCount <= 2)
                pInstance->DoCompleteAchievement(ACHIEVEMENT_QUICK_SHAVE);
        }
    }


    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (me->getVictim() && !me->getVictim()->GetCharmerOrOwnerPlayerOrPlayerItself())
            me->Kill(me->getVictim());
           
        events.Update(diff);
           
        if (HealthBelowPct(50) && !PermaGround)
            EnterPermaGround();
       
        if (EnrageTimer<= diff)
            DoCast(me, SPELL_BERSERK);
        else EnrageTimer -= diff;

        if (phase == PHASE_GROUND)
        {
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FLIGHT:
                        phase = PHASE_FLIGHT;
                        events.SetPhase(PHASE_FLIGHT);
                        me->SetFlying(true);
                        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
                        me->SetReactState(REACT_PASSIVE);
                        me->AttackStop();
                        me->SendMovementFlagUpdate();
                        me->GetMotionMaster()->MovePoint(0,RazorFlight);
                        events.ScheduleEvent(EVENT_FIREBALL, 7000, 0, PHASE_FLIGHT);
                        events.ScheduleEvent(EVENT_DEVOURING, 10000, 0, PHASE_FLIGHT);
                        events.ScheduleEvent(EVENT_SUMMON, 5000, 0, PHASE_FLIGHT);
                        events.ScheduleEvent(EVENT_GROUND, 75000, 0, PHASE_FLIGHT);
                        ++FlyCount;
                        return;
                    case EVENT_LAND:
                        me->SetFlying(false);
                        me->CastSpell(me ,SPELL_STUN, true);
                        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);

                        // Change life amount -16.66 percent. if the boss life is higher than 16.66 percent
                        if (me->GetHealth() > (me->GetMaxHealth() * 0.1666f))
                            me->ModifyHealth(me->GetHealth() - me->GetMaxHealth() * 0.1666f);

                        events.ScheduleEvent(EVENT_HARPOON, 0, 0, PHASE_GROUND);
                        events.ScheduleEvent(EVENT_BREATH, 30000, 0, PHASE_GROUND);
                        events.ScheduleEvent(EVENT_BUFFET, 33000, 0, PHASE_GROUND);
                        events.ScheduleEvent(EVENT_FLIGHT, 35000, 0, PHASE_GROUND);
                        return;
                    case EVENT_HARPOON:
                        events.ScheduleEvent(EVENT_HARPOON, 1500, 0, PHASE_GROUND);
                        return;
                    case EVENT_BREATH:
                        me->MonsterTextEmote(EMOTE_BREATH, 0, true);
                        DoCastAOE(RAID_MODE(SPELL_FLAMEBREATH_10, SPELL_FLAMEBREATH_25));
                        events.CancelEvent(EVENT_HARPOON);
                        events.CancelEvent(EVENT_BREATH);
                        return;
                    case EVENT_BUFFET:
                        if (Harpoon[0])
                            Harpoon[0]->CastSpell(Harpoon[0], SPELL_FLAMED, true);
                        if (Harpoon[1])
                            Harpoon[1]->CastSpell(Harpoon[1], SPELL_FLAMED, true);
                        DoCastAOE(SPELL_WINGBUFFET);
                        events.CancelEvent(EVENT_BUFFET);
                        return;
                }
            }
        }
        if (phase == PHASE_PERMAGROUND)
        {
            while (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_FLAME:
                        DoCastAOE(SPELL_FLAMEBUFFET);
                        events.ScheduleEvent(EVENT_FLAME, 10000, 0, PHASE_PERMAGROUND);
                        return;
                    case EVENT_BREATH:
                        me->MonsterTextEmote(EMOTE_BREATH, 0, true);
                        DoCastVictim(RAID_MODE(SPELL_FLAMEBREATH_10, SPELL_FLAMEBREATH_25));
                        events.ScheduleEvent(EVENT_BREATH, 20000, 0, PHASE_PERMAGROUND);
                        return;
                    case EVENT_FIREBALL:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(pTarget, RAID_MODE(SPELL_FIREBALL_10, SPELL_FIREBALL_25));
                        events.ScheduleEvent(EVENT_FIREBALL, 3000, 0, PHASE_PERMAGROUND);
                        return;
                    case EVENT_DEVOURING:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(pTarget, RAID_MODE(SPELL_DEVOURINGFLAME_10, SPELL_DEVOURINGFLAME_25));
                        events.ScheduleEvent(EVENT_DEVOURING, 10000, 0, PHASE_PERMAGROUND);
                        return;
                    case EVENT_BUFFET:
                        DoCastAOE(SPELL_WINGBUFFET);
                        events.CancelEvent(EVENT_BUFFET);
                        return;
                    case EVENT_FUSE:
                        DoCastVictim(SPELL_FUSEARMOR);
                        events.ScheduleEvent(EVENT_FUSE, 10000, 0, PHASE_PERMAGROUND);
                        return;
                }
            }

            DoMeleeAttackIfReady();
        }
        else
        {
            if (uint32 eventId = events.ExecuteEvent())
            {
                switch (eventId)
                {
                    case EVENT_GROUND:
                        phase = PHASE_GROUND;
                        events.SetPhase(PHASE_GROUND);
                        if (Harpoon[0])
                            Harpoon[0]->MonsterTextEmote(EMOTE_HARPOON, 0, true);
                        me->SetHomePosition(RazorGround);
                        me->GetMotionMaster()->MoveTargetedHome();
                        events.ScheduleEvent(EVENT_LAND, 5500, 0, PHASE_GROUND);
                        return;
                    case EVENT_FIREBALL:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(pTarget, RAID_MODE(SPELL_FIREBALL_10, SPELL_FIREBALL_25));
                        events.ScheduleEvent(EVENT_FIREBALL, 3000, 0, PHASE_FLIGHT);
                        return;
                    case EVENT_DEVOURING:
                        if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                            DoCast(pTarget, RAID_MODE(SPELL_DEVOURINGFLAME_10, SPELL_DEVOURINGFLAME_25));
                        events.ScheduleEvent(EVENT_DEVOURING, 10000, 0, PHASE_FLIGHT);
                        return;
                    case EVENT_SUMMON:
                        SummonAdds();
                        events.ScheduleEvent(EVENT_SUMMON, 45000, 0, PHASE_FLIGHT);
                        return;
                }
            }
        }
    }
   
    void EnterPermaGround()
    {
        me->MonsterTextEmote(EMOTE_PERMA, 0, true);
        phase = PHASE_PERMAGROUND;
        events.SetPhase(PHASE_PERMAGROUND);
        me->SetFlying(false);
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE);
        me->SetReactState(REACT_AGGRESSIVE);
        me->RemoveAurasDueToSpell(SPELL_STUN);
        me->SetSpeed(MOVE_RUN, 1.0f);
        me->SetSpeed(MOVE_FLIGHT, 1.0f);
        me->SendMovementFlagUpdate();
        PermaGround = true;
        DoCastAOE(RAID_MODE(SPELL_FLAMEBREATH_10, SPELL_FLAMEBREATH_25));
        events.ScheduleEvent(EVENT_FLAME, 15000, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_DEVOURING, 15000, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_BREATH, 20000, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_FIREBALL, 3000, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_DEVOURING, 6000, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_BUFFET, 2500, 0, PHASE_PERMAGROUND);
        events.RescheduleEvent(EVENT_FUSE, 5000, 0, PHASE_PERMAGROUND);
    }

    void SummonAdds()
    {
        // Adds will come in waves from mole machines. One mole can spawn a Dark Rune Watcher
        // with 1-2 Guardians, or a lone Sentinel. Up to 4 mole machines can spawn adds at any given time.
        uint8 random = urand(1,4);
        for (uint8 i = 0; i < random; ++i)
        {
            if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
            {
                float x = std::max(500.0f, std::min(650.0f, pTarget->GetPositionX() + irand(-20,20)));   // Safe range is between 500 and 650
                float y = std::max(-235.0f, std::min(-145.0f, pTarget->GetPositionY() + irand(-20,20))); // Safe range is between -235 and -145
                float z = me->GetBaseMap()->GetHeight(x, y, MAX_HEIGHT);                         // Ground level
                MoleTrigger = me->SummonCreature(MOLE_MACHINE_TRIGGER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN, 10000);
            }
        }
    }
};

CreatureAI* GetAI_boss_razorscale(Creature* pCreature)
{
    return new boss_razorscaleAI (pCreature);
}

/*====================================================================================
====================================================================================*/

struct npc_expedition_commanderAI : public ScriptedAI
{
    npc_expedition_commanderAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = pCreature->GetInstanceData();
        greet = false;
    }
   
    ScriptedInstance* pInstance;


    uint32 uiTimer;
    bool greet;

    uint64 m_uiCommanderGUID;
    uint8  uiPhase;
    Creature* engineer[2];
    Creature* defender[4];
    Creature* razorscale;

    void Initialize()
    {
        uiTimer =0;
        uiPhase = 0;
        engineer[0] = 0;
        engineer[1] = 0;
        defender[0] = 0;
        defender[1] = 0;
        defender[2] = 0;
        defender[3] = 0;
    }

    std::list<Creature*> GuardList;

    void Reset()
    {
        uiTimer = 0;
        greet = false;
    }
   
    void MoveInLineOfSight(Unit *who)
    {
        if (!greet && me->IsWithinDistInMap(who, 10.0f) && who->GetTypeId() == TYPEID_PLAYER)
        {
            me->MonsterSay(SAY_GREET, LANG_UNIVERSAL, 0);
            greet = true;
        }
        ScriptedAI::MoveInLineOfSight(who);
    }

    void MovementInform(uint32 uiType, uint32 uiId)
    {
        if (uiType != POINT_MOTION_TYPE)
            return;
    }
   
    void UpdateAI(const uint32 uiDiff)
    {
        ScriptedAI::UpdateAI(uiDiff);
        if (uiTimer <= uiDiff)
        {
            switch (uiPhase)
            {
                case 1:
                    me->MonsterYell(SAY_AGGRO_2, LANG_UNIVERSAL, 0);
                    me->SetVisibility(VISIBILITY_OFF);
                    uiTimer = 1000;
                    uiPhase = 2;
                    break;
                case 2:
                    engineer[0] = me->SummonCreature(NPC_ENGINEER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 480000);
                    engineer[0]->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    engineer[0]->SetSpeed(MOVE_RUN, 0.5f);
                    engineer[0]->SetHomePosition(Harpoon1);
                    engineer[0]->GetMotionMaster()->MoveTargetedHome();
                    engineer[1] = me->SummonCreature(NPC_ENGINEER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 480000);
                    engineer[1]->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    engineer[1]->SetSpeed(MOVE_RUN, 0.5f);
                    engineer[1]->SetHomePosition(Harpoon2);
                    engineer[1]->GetMotionMaster()->MoveTargetedHome();
                    engineer[0]->MonsterYell(SAY_AGGRO_3, LANG_UNIVERSAL, 0);
                    uiPhase = 3;
                    uiTimer = 14000;
                    break;
                case 3:
                    uiPhase = 4;
                    break;
                case 4:
                    defender[0] = me->SummonCreature(NPC_DEFENDER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    defender[0] ->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    defender[0] ->SetHomePosition(pos1);
                    defender[0] ->GetMotionMaster()->MoveTargetedHome();

                    defender[1] = me->SummonCreature(NPC_DEFENDER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    defender[1] ->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    defender[1] ->SetHomePosition(pos2);
                    defender[1] ->GetMotionMaster()->MoveTargetedHome();
                   
                    defender[2] = me->SummonCreature(NPC_DEFENDER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    defender[2] ->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    defender[2] ->SetHomePosition(pos3);
                    defender[2] ->GetMotionMaster()->MoveTargetedHome();

                    defender[3] = me->SummonCreature(NPC_DEFENDER,591.951477, -95.968292, 391.516998, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 120000);
                    defender[3] ->RemoveUnitMovementFlag(MOVEMENTFLAG_WALK_MODE);
                    defender[3] ->SetHomePosition(pos4);
                    defender[3] ->GetMotionMaster()->MoveTargetedHome();
                    uiPhase = 5;
                    break;
                case 5:
                    engineer[0]->HandleEmoteCommand(EMOTE_STATE_USESTANDING);
                    engineer[1]->HandleEmoteCommand(EMOTE_STATE_USESTANDING);
                    defender[0]->HandleEmoteCommand(EMOTE_STATE_READY2H);
                    defender[1]->HandleEmoteCommand(EMOTE_STATE_READY2H);
                    defender[2]->HandleEmoteCommand(EMOTE_STATE_READY2H);
                    defender[3]->HandleEmoteCommand(EMOTE_STATE_READY2H);
                    engineer[0]->MonsterYell(SAY_AGGRO_1, LANG_UNIVERSAL, 0);
                    uiTimer = 16000;
                    uiPhase = 6;
                    break;
                case 6:
                    pInstance->SetData(TYPE_RAZORSCALE, IN_PROGRESS);
                    razorscale = me->SummonCreature (RAZORSCALE,RazorFlight,TEMPSUMMON_CORPSE_TIMED_DESPAWN, 999999);
                    uiPhase =7;
                    me->Kill(me, false);
                    break;
            }
            if (!UpdateVictim())
                return;
               
            DoMeleeAttackIfReady();
        }
        else uiTimer -= uiDiff;
    }
};


CreatureAI* GetAI_commander_ulduar(Creature* pCreature)
{
    return new npc_expedition_commanderAI(pCreature);
}

bool Expedition_commander_ulduar(Player* pPlayer, Creature* pCreature)
{
    ScriptedInstance* pInstance = pCreature->GetInstanceData();
    if (pInstance && pPlayer)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT,GOSSIP_ITEM_1,GOSSIP_SENDER_MAIN,GOSSIP_ACTION_INFO_DEF);
        pPlayer->SEND_GOSSIP_MENU(13853, pCreature->GetGUID());
    }else
        pPlayer->SEND_GOSSIP_MENU(13910, pCreature->GetGUID());
    return true;
}

bool GossipSelect_commander_ulduar(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF:
            if (pPlayer)
                pPlayer->CLOSE_GOSSIP_MENU();
            CAST_AI(npc_expedition_commanderAI, (pCreature->AI()))->uiPhase = 1;
            break;
    }
    return true;
}

struct mob_devouring_flameAI : public ScriptedAI
{
    mob_devouring_flameAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_NON_ATTACKABLE | UNIT_FLAG_NOT_SELECTABLE | UNIT_FLAG_PACIFIED);
    }

    void Reset()
    {
        DoCast(me, RAID_MODE(SPELL_FLAME_GROUND_10, SPELL_FLAME_GROUND_25));
    }
};

CreatureAI* GetAI_mob_devouring_flame(Creature* pCreature)
{
    return new mob_devouring_flameAI(pCreature);
}


struct mob_darkrune_watcherAI : public ScriptedAI
{
    mob_darkrune_watcherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    int32 ChainTimer;
    int32 LightTimer;

    void Reset()
    {
        ChainTimer = urand(10000, 15000);
        LightTimer = urand(1000, 3000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (ChainTimer <= uiDiff)
        {
            DoCastVictim(RAID_MODE(SPELL_CHAIN_LIGHTNING_10, SPELL_CHAIN_LIGHTNING_25));
            ChainTimer = urand(10000, 15000);
        } else ChainTimer -= uiDiff;
       
        if (LightTimer <= uiDiff)
        {
            DoCastVictim(RAID_MODE(SPELL_LIGHTNING_BOLT_10, SPELL_LIGHTNING_BOLT_25));
            LightTimer = urand(5000, 7000);
        } else LightTimer -= uiDiff;


        DoMeleeAttackIfReady();
    }
};


CreatureAI* GetAI_mob_darkrune_watcher(Creature* pCreature)
{
    return new mob_darkrune_watcherAI(pCreature);
}

struct mob_darkrune_guardianAI : public ScriptedAI
{
    mob_darkrune_guardianAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    int32 StormTimer;

    void Reset()
    {
        StormTimer = urand(3000, 6000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (StormTimer <= uiDiff)
        {
            DoCastVictim(SPELL_STORMSTRIKE);
            StormTimer = urand(4000, 8000);
        } else StormTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_darkrune_guardian(Creature* pCreature)
{
    return new mob_darkrune_guardianAI(pCreature);
}


struct mob_darkrune_sentinelAI : public ScriptedAI
{
    mob_darkrune_sentinelAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
    }

    ScriptedInstance* m_pInstance;
    int32 HeroicTimer;
    int32 WhirlTimer;
    int32 ShoutTimer;

    void Reset()
    {
        HeroicTimer = urand(4000, 8000);
        WhirlTimer = urand(20000, 30000);
        ShoutTimer = urand(30000, 40000);
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (HeroicTimer <= uiDiff)
        {
            DoCastVictim(SPELL_HEROIC_STRIKE);
            HeroicTimer = urand(4000, 6000);
        } else HeroicTimer -= uiDiff;
       
        if (WhirlTimer <= uiDiff)
        {
            DoCastVictim(RAID_MODE(SPELL_WHIRLWIND_10, SPELL_WHIRLWIND_25));
            WhirlTimer = urand(20000, 30000);
        } else WhirlTimer -= uiDiff;
       
        if (ShoutTimer <= uiDiff)
        {
            DoCast(me, RAID_MODE(SPELL_BATTLE_SHOUT_10, SPELL_BATTLE_SHOUT_25));
            ShoutTimer = urand(30000, 40000);
        } else ShoutTimer -= uiDiff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_mob_darkrune_sentinel(Creature* pCreature)
{
    return new mob_darkrune_sentinelAI(pCreature);
}


struct mole_machine_triggerAI : public ScriptedAI
{
    mole_machine_triggerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        me->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_DISABLE_MOVE | UNIT_FLAG_PACIFIED);
        me->SetVisibility(VISIBILITY_OFF);
    }

    ScriptedInstance* m_pInstance;
    int32 SummomTimer;

    void Reset()
    {
        DoCast(me, SPELL_MOLE_MACHINE);
        SummomTimer = 8000;
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        if (SummomTimer <= uiDiff)
        {
            float x = me->GetPositionX();
            float y = me->GetPositionY();
            float z = me->GetPositionZ();
            me->SummonCreature(NPC_DARK_RUNE_WATCHER, x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            me->SummonCreature(RAND(NPC_DARK_RUNE_GUARDIAN, NPC_DARK_RUNE_SENTINEL), x, y, z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000);
            SummomTimer = 15000;
        } else SummomTimer -= uiDiff;
    }
   
    void JustSummoned(Creature *summon)
    {
        summon->AI()->DoAction(0);
        summon->AI()->DoZoneInCombat();
    }
};

CreatureAI* GetAI_mole_machine_trigger(Creature* pCreature)
{
    return new mole_machine_triggerAI(pCreature);
}

void AddSC_boss_razorscale()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_expedition_commander_ulduar";
    newscript->GetAI = &GetAI_commander_ulduar;
    newscript->pGossipHello = &Expedition_commander_ulduar;
    newscript->pGossipSelect = &GossipSelect_commander_ulduar;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "boss_razorscale";
    newscript->GetAI = &GetAI_boss_razorscale;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mob_devouring_flame";
    newscript->GetAI = &GetAI_mob_devouring_flame;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mob_darkrune_watcher";
    newscript->GetAI = &GetAI_mob_darkrune_watcher;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mob_darkrune_guardian";
    newscript->GetAI = &GetAI_mob_darkrune_guardian;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mob_darkrune_sentinel";
    newscript->GetAI = &GetAI_mob_darkrune_sentinel;
    newscript->RegisterSelf();
   
    newscript = new Script;
    newscript->Name = "mole_machine_trigger";
    newscript->GetAI = &GetAI_mole_machine_trigger;
    newscript->RegisterSelf();

}

