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

// http://hordeguides.de/index.php?rb=33350
// Mimiron muss noch so eingestellt werden das er alles steuer d.h er ist nicht killbar/angreifbar er steuert lediglich die kisten
// Spawn system für P4 (vehicle kit need)
// Sound einträge fehlen noch
// Assault bot darf keine aggro haben bzw verfolgt immer den auf den der cast kanalisiert wird.

enum Spells
{
    // All P4
    SPELL_SELF_REPAIR             = 64383,
    // Leviathan Mk II - Phase 1 & 4
    SPELL_NAPALM_SHELL            = 63666,
    SPELL_PLASMA_BLAST            = 62997,
    SPELL_PROXIMITY_MINES         = 63016,
    SPELL_SHOCK_BLAST             = 63631,
    SPELL_NAPALM_SHELL_H          = 65026,
    SPELL_PLASMA_BLAST_H          = 64529,
    SPELL_PROXIMITY_MINES_H       = 63016,
    SPELL_SHOCK_BLAST_H           = 63631,
    // VX-001 - Phase 2 & 4
    SPELL_HEAT_WAVE               = 63677,
    SPELL_RAPID_BURST             = 64019,
    SPELL_SPINNING_UP             = 63414,
    SPELL_LASER_BARRAGE           = 63293,
    SPELL_ROCKET_STRIKE           = 63041,
    SPELL_HAND_PULSE              = 64537,
    SPELL_HEAT_WAVE_H             = 64533,
    SPELL_RAPID_BURST_H           = 64531,
    SPELL_SPINNING_UP_H           = 63414,
    SPELL_LASER_BARRAGE_H         = 63293,
    SPELL_ROCKET_STRIKE_H         = 63041,
    SPELL_HAND_PULSE_H            = 64537,
    // Aerial Command Unit - Phase 3 & 4
    SPELL_BOMB_BOT                = 63811,
    SPELL_PLASMA_BALL             = 63689,
    SPELL_BOMB_BOT_H              = 63811,
    SPELL_PLASMA_BALL_H           = 64535,
    // Bomb Bot - Phase 3
    SPELL_BOMB_BOT_EXPLODE        = 63801,
    SPELL_BOMB_BOT_EXPLODE_H      = 63801,
    // Assault Bot - Phase 3
    SPELL_MAGNETIC_FIELD          = 64668,
    SPELL_MAGNETIC_FIELD_H        = 64668,
};

enum Sounds
{
    SAY_AGGRO                                   = -1603240,
    SAY_HARDMODE_ON                             = -1603241,
    SAY_MKII_ACTIVATE                           = -1603242,
    SAY_MKII_SLAY_1                             = -1603243,
    SAY_MKII_SLAY_2                             = -1603244,
    SAY_MKII_DEATH                              = -1603245,
    SAY_VX001_ACTIVATE                          = -1603246,
    SAY_VX001_SLAY_1                            = -1603247,
    SAY_VX001_SLAY_2                            = -1603248,
    SAY_VX001_DEATH                             = -1603249,
    SAY_AERIAL_ACTIVATE                         = -1603250,
    SAY_AERIAL_SLAY_1                           = -1603251,
    SAY_AERIAL_SLAY_2                           = -1603252,
    SAY_AERIAL_DEATH                            = -1603253,
    SAY_V07TRON_ACTIVATE                        = -1603254,
    SAY_V07TRON_SLAY_1                          = -1603255,
    SAY_V07TRON_SLAY_2                          = -1603256,
    SAY_V07TRON_DEATH                           = -1603257,
    SAY_BERSERK                                 = -1603258,
    SAY_YS_HELP                                 = -1603259,

};

enum MimironNpcs
{
    NPC_LEVIATHAN_MK           = 33432, // P1 & 4
    NPC_AERIAL_UNIT            = 33670, // P2 & 4
    NPC_VX001                  = 33651, // P3 & 4 
    NPC_ASSAULT_BOT            = 34057, // P3
    NPC_BOMB_BOT               = 33836, // P3
    NPC_JUNK_BOT               = 33855    // P3
};

enum Objects
{
    OBJECT_MIMIRON_CHEST_N         = 194324, // Chest Spawn 
    OBJECT_MIMIRON_CHEST_H         = 194327, // Chest Spawn 
    OBJECT_GNOMEWING_TELEPORT      = 194748, // P3 Bot spawn
    OBJECT_GNOMEWING_TORSO         = 194749,  // P1 -> P2 Pause
    OBJECT_GNOMEWING_DOOR1         = 194776, // Doors -> Close at encounter start
    OBJECT_GNOMEWING_DOOR2         = 194772, // Doors -> Close at encounter start
    OBJECT_GNOMEWING_DOOR3         = 194775, // Doors -> Close at encounter start
};

enum FlagsAndModels
{
    FACTION_FRIENDLY               = 35, // Apply after kill
    FACTION_HOSTILE                = 16, 
    MODEL_INVISIBLE                = 11686, // Apply after ~ 30min
};

const Position BotSummonPos0 = { 2704.026, 2569.297, 364.313, 6.266 };
const Position BotSummonPos1 = { 2715.234, 2569.107, 364.313, 6.242 };
const Position BotSummonPos2 = { 2726.460, 2569.351, 364.313, 6.251 };
const Position BotSummonPos3 = { 2753.931, 2584.717, 364.313, 4.144 };
const Position BotSummonPos4 = { 2759.647, 2594.675, 364.364, 4.144 };
const Position BotSummonPos5 = { 2765.310, 2604.149, 364.313, 4.172 };
const Position BotSummonPos6 = { 2754.077, 2554.274, 364.313, 2.058 };
const Position BotSummonPos7 = { 2759.904, 2544.117, 364.313, 2.082 };
const Position BotSummonPos8 = { 2765.539, 2533.982, 364.313, 2.090 };

/////////////////////////////////////////////////////////////////////
////////////////////////// Mimiron //////////////////////////////////
/////////////////////////////////////////////////////////////////////

struct boss_mimironAI : public BossAI
{
    boss_mimironAI(Creature* pCreature) : BossAI(pCreature, TYPE_MIMIRON)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    void Reset()
    {
            if (m_pInstance)
        {
            // reset event
            m_pInstance->SetData(TYPE_MIMIRON, NOT_STARTED);
        }
    }


    void Aggro(Unit* pWho)
    {
        me->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_MIMIRON, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

    }

};

CreatureAI* GetAI_boss_mimiron(Creature* pCreature)
{
    return new boss_mimironAI(pCreature);
}

/////////////////////////////////////////////////////////////////////
//////////////////////Leviathan MK II ///////////////////////////////
/////////////////////////////////////////////////////////////////////

struct boss_leviathan_mkAI : public BossAI
{
    boss_leviathan_mkAI(Creature* pCreature) : BossAI(pCreature, TYPE_LEVIATHAN_MK)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    
    uint32 NapalmShellTimer;
    uint32 PlasmaBlastTimer;
    uint32 ProximityMinesTimer;
    uint32 ShockBlastTimer;
    
    void Reset()
    {
    
    NapalmShellTimer = 10000;
    PlasmaBlastTimer = 10000;
    ProximityMinesTimer = 10000;
    ShockBlastTimer = 10000;
    
            if (m_pInstance)
        {
            // reset event
            m_pInstance->SetData(TYPE_MIMIRON, NOT_STARTED);
            m_pInstance->SetData(TYPE_LEVIATHAN_MK, NOT_STARTED);
        }
    }

    void KilledUnit(Unit *victim)
    {
    
    
    }

    void JustDied(Unit *victim)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_LEVIATHAN_MK, DONE);
    }

    void Aggro(Unit* pWho)
    {
        me->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_LEVIATHAN_MK, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

            
        // Napalm shell
        if (NapalmShellTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me, RAID_MODE(SPELL_NAPALM_SHELL, SPELL_NAPALM_SHELL_H));
            NapalmShellTimer = 10000;
        }else NapalmShellTimer -= diff;
            
            
        // Plasma Blast
        if (PlasmaBlastTimer < diff )
        {
            DoCast(me, RAID_MODE(SPELL_PLASMA_BLAST, SPELL_PLASMA_BLAST_H));
            PlasmaBlastTimer = 10000;
        }else PlasmaBlastTimer -= diff;
        
        // Proximity Mines
        if (ProximityMinesTimer < diff )
        {
            DoCast(me, RAID_MODE(SPELL_PROXIMITY_MINES, SPELL_PROXIMITY_MINES_H));
            ProximityMinesTimer = 10000;
        }else ProximityMinesTimer -= diff;
        
        
        // Shock Blast
        if (ShockBlastTimer < diff )
        {
            DoCast(me, RAID_MODE(SPELL_SHOCK_BLAST, SPELL_SHOCK_BLAST_H));
            ShockBlastTimer = 10000;
        }else ShockBlastTimer -= diff;
            
        DoMeleeAttackIfReady();

    }

};

CreatureAI* GetAI_boss_leviathan_mk(Creature* pCreature)
{
    return new boss_leviathan_mkAI(pCreature);
}

/////////////////////////////////////////////////////////////////////
////////////////////////////VX-001 //////////////////////////////////
/////////////////////////////////////////////////////////////////////

struct boss_vx001AI : public BossAI
{
    boss_vx001AI(Creature* pCreature) : BossAI(pCreature, TYPE_VX001AI)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 HeatWaveTimer;
    uint32 RapidBurstTimer;
    uint32 SpinningUpTimer;
    uint32 LaserBarrageTimer;
    uint32 RocketStrikeTimer;
    uint32 HandPulseTimer;
    
    void Reset()
    {
    
    HeatWaveTimer = 10000;
    RapidBurstTimer = 10000;
    SpinningUpTimer = 10000;
    LaserBarrageTimer = 10000;
    RocketStrikeTimer = 10000;
    HandPulseTimer = 10000;
    
            if (m_pInstance)
        {
            // reset event
            m_pInstance->SetData(TYPE_MIMIRON, NOT_STARTED);
        }
    }

    void KilledUnit(Unit *victim)
    {

    }

    void JustDied(Unit *victim)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_VX001AI, DONE);
    }

    void Aggro(Unit* pWho)
    {
        me->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_VX001AI, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

            
        // Heat Wave
        if (HeatWaveTimer < diff )
        {
            DoCast(me, RAID_MODE(SPELL_HEAT_WAVE, SPELL_HEAT_WAVE_H));
            HeatWaveTimer = 10000;
        }else HeatWaveTimer -= diff;
            
            
        // Rapid Burst
        if (RapidBurstTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me, RAID_MODE(SPELL_RAPID_BURST, SPELL_RAPID_BURST_H));
            RapidBurstTimer = 10000;
        }else RapidBurstTimer -= diff;
        
        // Laser Barrage
        if (LaserBarrageTimer < diff )
        {
            DoCast(me, RAID_MODE(SPELL_LASER_BARRAGE, SPELL_LASER_BARRAGE_H));
            LaserBarrageTimer = 10000;
        }else LaserBarrageTimer -= diff;
        
        
        // Rocket Strike
        if (RocketStrikeTimer < diff )
        {
          if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            DoCast(me, RAID_MODE(SPELL_ROCKET_STRIKE, SPELL_ROCKET_STRIKE_H));
          RocketStrikeTimer = 10000;
        }else RocketStrikeTimer -= diff;
        
        // Hand Pulse
        if (HandPulseTimer < diff )
        {
          if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            DoCast(me, RAID_MODE(SPELL_HAND_PULSE, SPELL_HAND_PULSE_H));
            HandPulseTimer = 10000;
        }else HandPulseTimer -= diff;


    }

};

CreatureAI* GetAI_boss_vx001(Creature* pCreature)
{
    return new boss_vx001AI(pCreature);
}

/////////////////////////////////////////////////////////////////////
//////////////////////Aerial Command Unit ///////////////////////////
/////////////////////////////////////////////////////////////////////

struct boss_aerial_unitAI : public BossAI
{
    boss_aerial_unitAI(Creature* pCreature) : BossAI(pCreature, TYPE_AERIAL_UNIT)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;

    uint32 BombBotTimer;
    uint32 PlasmaBallTimer;
    uint32 AssaultBotTimer;
    uint32 JunkBotTimer;
    
    void Reset()
    {
    
    BombBotTimer = 10000;
    PlasmaBallTimer = 10000;
    AssaultBotTimer = 10000;
    JunkBotTimer = 10000;
    
            if (m_pInstance)
        {
            // reset event
            m_pInstance->SetData(TYPE_MIMIRON, NOT_STARTED);
            m_pInstance->SetData(TYPE_AERIAL_UNIT, NOT_STARTED);
        }
    }

    void KilledUnit(Unit *victim)
    {
    }

    void JustDied(Unit *victim)
    {
        if (m_pInstance)
            m_pInstance->SetData(TYPE_AERIAL_UNIT, DONE);
    }

    void Aggro(Unit* pWho)
    {

        me->SetInCombatWithZone();

        if (m_pInstance)
            m_pInstance->SetData(TYPE_AERIAL_UNIT, IN_PROGRESS);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
            
        // Bomb Bot spawn
        if (BombBotTimer < diff )
        {
          if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            DoCast(me, RAID_MODE(SPELL_BOMB_BOT, SPELL_BOMB_BOT_H));
          BombBotTimer = 10000;
        }else BombBotTimer -= diff;
        
        // Plasma Ball
        if (PlasmaBallTimer < diff )
        {
          if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            DoCast(me, RAID_MODE(SPELL_PLASMA_BALL, SPELL_PLASMA_BALL_H));
            PlasmaBallTimer = 10000;
        }else PlasmaBallTimer -= diff;


        // Assault Bot spawn
        if (AssaultBotTimer < diff )
        {
          switch (urand(0, 8))
            {
            case 0: 
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos0, 1);
                break;
            case 1:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos1, 1);
                break;
            case 2:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos2, 1);
                break;
            case 3:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos3, 1);
                break;
            case 4:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos4, 1);
                break;
            case 5:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos5, 1);
                break;
            case 6:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos6, 1);
                break;
            case 7:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos7, 1);
                break;
            case 8:
                DoSummon(NPC_ASSAULT_BOT, BotSummonPos8, 1);
                break;
               }
          AssaultBotTimer = 10000;
        }else AssaultBotTimer -= diff;
        
        // Junk Bot Spawn
        if (JunkBotTimer < diff )
        {

          switch (urand(0, 5))
            {
            case 0: 
                DoSummon(NPC_JUNK_BOT, BotSummonPos0, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos0, 1);
                break;
            case 1:
                DoSummon(NPC_JUNK_BOT, BotSummonPos1, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos1, 1);
                break;
            case 2:
                DoSummon(NPC_JUNK_BOT, BotSummonPos2, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos2, 1);
                break;
            case 3:
                DoSummon(NPC_JUNK_BOT, BotSummonPos3, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos3, 1);
                break;
            case 4:
                DoSummon(NPC_JUNK_BOT, BotSummonPos4, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos4, 1);
                break;
            case 5:
                DoSummon(NPC_JUNK_BOT, BotSummonPos5, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos5, 1);
                break;
            case 6:
                DoSummon(NPC_JUNK_BOT, BotSummonPos6, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos6, 1);
                break;
            case 7:
                DoSummon(NPC_JUNK_BOT, BotSummonPos7, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos7, 1);
                break;
            case 8:
                DoSummon(NPC_JUNK_BOT, BotSummonPos8, 1);
                DoSummon(NPC_JUNK_BOT, BotSummonPos8, 1);
                break;
        }
            JunkBotTimer = 10000;
        }else JunkBotTimer -= diff;


    }

};

CreatureAI* GetAI_boss_aerial_unit(Creature* pCreature)
{
    return new boss_aerial_unitAI(pCreature);
}

struct npc_assault_botAI : public ScriptedAI
{
    npc_assault_botAI(Creature* pCreature) : ScriptedAI(pCreature) {}

    uint32 MagneticFieldTimer;
    
    
    void Aggro(Unit* pWho)
    {
        me->SetInCombatWithZone();
    }
    
    
    void Reset()
    {
    
    MagneticFieldTimer = 10000;
    
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

         // Magnetic Field
        if (MagneticFieldTimer < diff )
        {
          if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
            DoCast(me, RAID_MODE(SPELL_MAGNETIC_FIELD, SPELL_MAGNETIC_FIELD_H));
          MagneticFieldTimer = 10000;
        }else MagneticFieldTimer -= diff;
 
            DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_assault_bot(Creature* pCreature)
{
    return new npc_assault_botAI (pCreature);
}


void AddSC_boss_mimiron()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_mimiron";
    newscript->GetAI = &GetAI_boss_mimiron;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_leviathan_mk";
    newscript->GetAI = &GetAI_boss_leviathan_mk;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_vx001";
    newscript->GetAI = &GetAI_boss_vx001;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_aerial_unit";
    newscript->GetAI = &GetAI_boss_aerial_unit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_assault_bot";
    newscript->GetAI = &GetAI_npc_assault_bot;
    newscript->RegisterSelf();

}
