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
//TODO:
//     SPELL_LIGHTNING_CHARGE_2           = 62466, // aoe - Trigger spawn, Blitzkugeln zur andeutung ~5sec später explosion
//     Phase 2 Switch bei betreten von    const Position P2Switch = { 2134.580, -321.498  }; 
//     Timer abfrage ob gang fertig in < 3min -> Hardmode on = kein sif despawn
//     Hebel mit Tür verlinken zum Gang
//     Türen im Iniscript eintragen -> koloss down -> tür offen
//     Falle bei Thorim per trigger erstellen
#include "ScriptedPch.h"
#include "ulduar.h"

enum Spells
{
    /////////////////// THORIM ////////////////
    SPELL_SHEATH_OF_LIGHTNING          = 62276,
    SPELL_STORMHAMMER                  = 62042,
    SPELL_DEAFENING_THUNDER            = 62470,
    SPELL_CHARGE_ORB                   = 62016,
    SPELL_BERSERK                      = 62560, 
    /////////////////// P2 ///////////////////
    SPELL_SUMMON_LIGHTNING_ORB         = 62391,
    SPELL_CHAIN_LIGHTNING_N            = 62131,
    SPELL_CHAIN_LIGHTNING_H            = 64390,
    SPELL_LIGHTNING_CHARGE             = 62279, // buff
    SPELL_LIGHTNING_CHARGE_2           = 62466, // aoe
    SPELL_UNBALANCING_STRIKE           = 62130,
    ////////////////// SIF ///////////////////
    SPELL_FROSTBOLD_VOLLEY_N           = 62580,
    SPELL_FROSTBOLD_VOLLEY_H           = 62604,
    SPELL_FROST_NOVA_N                 = 62597,
    SPELL_FROST_NOVA_H                 = 62605,
    SPELL_BLIZZARD_N                   = 62576,
    SPELL_BLIZZARD_H                   = 62602,
    SPELL_FROSTBOLD                    = 62583,
};

enum Yells
{
    SAY_AGGRO_1                        = -1603270,
    SAY_AGGRO_2                        = -1603271,
    SAY_SPECIAL_1                      = -1603272,
    SAY_SPECIAL_2                      = -1603273,
    SAY_SPECIAL_3                      = -1603274,
    SAY_JUMPDOWN                       = -1603275,
    SAY_SLAY_1                         = -1603276,
    SAY_SLAY_2                         = -1603277,
    SAY_BERSERK                        = -1603278,
    SAY_WIPE                           = -1603279,
    SAY_DEATH                          = -1603280,
    SAY_END_NORMAL_1                   = -1603281,
    SAY_END_NORMAL_2                   = -1603282,
    SAY_END_NORMAL_3                   = -1603283,
    SAY_END_HARD_1                     = -1603284,
    SAY_END_HARD_2                     = -1603285,
    SAY_END_HARD_3                     = -1603286,
    SAY_YS_HELP                        = -1603287,
    SAY_SIF_START                      = 15668,
    SAY_SIF_DESPAWN                    = 15669,
    SAY_SIF_EVENT                      = 15670,
};

enum Npcs
{
//    BOSS_THORIM                = 32865,
    BOSS_SIF                   = 33196,
    DARK_RUNE_COMMONER         = 32904,
    DARK_RUNE_CHAMPION         = 32876,
    DARK_RUNE_EVOKER           = 32878,
    DARK_RUNE_WARBRINGER       = 32877,
    DARK_RUNE_ACOLYTE          = 33110,
    DARK_RUNE_GUARD            = 33388,
    RUNIC_COLOSSUS             = 32872,
    ANCIENT_RUNE_GIANT         = 32873,
    IRON_RING_GUARD            = 32874,
    IRON_HONOR_GUARD           = 32875,
    CHAIN_LIGHTNING_TRIGGER    = 123,
};

const Position OrbSummonPos0 = { 2105.542, -292.76, 433.26, 0.753 }; 
const Position OrbSummonPos1 = { 2093.061, -262.84, 433.15, 0.086 }; 
const Position OrbSummonPos2 = { 2105.367, -233.96, 433.26, 5.493 }; 
const Position OrbSummonPos3 = { 2124.338, -222.65, 433.26, 4.865 }; 
const Position OrbSummonPos4 = { 2145.458, -222.37, 433.26, 4.763 }; 
const Position OrbSummonPos5 = { 2164.466, -233.46, 433.26, 3.942 };
const Position OrbSummonPos6 = { 2164.364, -292.71, 433.26, 2.072 };
                                                                       // 1-4 = Ads E = Eingang T= Thorim
const Position AdsSummonPos0 = { 2117.816, -236.45, 419.33, 5.241 };   //       =============
const Position AdsSummonPos1 = { 2103.741, -279.91, 420.14, 0.603 };   //       |0    E    3|
const Position AdsSummonPos2 = { 2161.465, -275.62, 419.37, 2.653 };   //       |           |
const Position AdsSummonPos3 = { 2151.248, -236.32, 419.33, 4.138 };   //       |1    T    2|
                                                                       //       =============
const Position TunnelRunPos0  = { 2218.590, -297.53, 412.13, 1.124 };  // Iron Ring Guard
const Position TunnelRunPos1  = { 2235.191, -298.04, 412.13, 1.681 };  // Iron Ring Guard
const Position TunnelRunPos2  = { 2227.505, -300.05, 412.13, 1.548 };  // Dark Rune Acolyte
const Position TunnelRunPos3  = { 2235.260, -338.34, 412.13, 1.589 };  // Iron Ring Guard
const Position TunnelRunPos4  = { 2227.164, -341.18, 412.13, 1.164 };  // Dark Rune Acolyte
const Position TunnelRunPos5  = { 2217.689, -337.39, 412.17, 1.239 };  // Iron Ring Guard
const Position TunnelRunPos6  = { 2227.500, -396.17, 412.17, 1.797 };  // Runic Colossus
const Position TunnelRunPos7  = { 2220.310, -436.22, 412.26, 1.064 };  // Iron Honor Guard 
const Position TunnelRunPos8  = { 2198.050, -428.76, 419.98, 6.056 };  // Iron Honor Guard
const Position TunnelRunPos9  = { 2198.290, -436.92, 419.98, 0.261 };  // Dark Rune Acolyte
const Position TunnelRunPos10 = { 2134.570, -440.31, 438.33, 0.226 };  // Ancient Rune Giant
const Position TunnelRunPos11 = { 2143.506, -432.15, 438.24, 5.637  }; // Dark Rune Acolyte

const Position P2Switch = { 2134.580, -321.498  }; 


struct boss_thorimAI : public BossAI
{
    boss_thorimAI(Creature* pCreature) : BossAI(pCreature, TYPE_THORIM)
    {
     
    }
    ScriptedInstance *m_pInstance;
    uint8 Phase;
    uint32 SheathOfLightningTimer;
    uint32 StormhammerTimer;
    uint32 DeafeningThunderTimer;
    uint32 ChargeOrbTimer;
    uint32 BerserkTimer;
    uint32 ChainLightningTimer;
    uint32 ChainLightningTimer2;
    uint32 LightningChargeTimer;
    uint32 LightningCharge2Timer;
    uint32 UnbalancingStrikeTimer;
    uint32 SummonArenaAds;
    
    void Reset()
    {
    Phase = 1;
    SheathOfLightningTimer = 10000;
    StormhammerTimer = 10000;
    DeafeningThunderTimer = 10000;
    ChargeOrbTimer = 10000;
    BerserkTimer = 10000;
    ChainLightningTimer = 10000;
    LightningChargeTimer = 10000;
    LightningCharge2Timer = 10000;
    UnbalancingStrikeTimer = 10000;
    SummonArenaAds = 15000;
        _Reset();
    }

    void EnterEvadeMode()
    {
        DoScriptText(SAY_WIPE, me);
        _EnterEvadeMode();
    }

    void KilledUnit(Unit * victim)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2), me);
    }

    void EnterCombat(Unit* pWho)
    {
            DoScriptText(SAY_AGGRO_1, me);
            DoScriptText(SAY_AGGRO_2, me);
            DoScriptText(SAY_SIF_START, me);
            DoSummon(IRON_RING_GUARD, TunnelRunPos0, 1);
            DoSummon(IRON_RING_GUARD, TunnelRunPos1, 1);
            DoSummon(DARK_RUNE_ACOLYTE, TunnelRunPos2, 1);
            DoSummon(IRON_RING_GUARD, TunnelRunPos3, 1);
            DoSummon(DARK_RUNE_ACOLYTE, TunnelRunPos4, 1);
            DoSummon(IRON_RING_GUARD, TunnelRunPos5, 1);
            DoSummon(RUNIC_COLOSSUS, TunnelRunPos6, 1);
            DoSummon(IRON_HONOR_GUARD, TunnelRunPos7, 1);
            DoSummon(IRON_HONOR_GUARD, TunnelRunPos8, 1);
            DoSummon(DARK_RUNE_ACOLYTE, TunnelRunPos9, 1);
            DoSummon(ANCIENT_RUNE_GIANT, TunnelRunPos10, 1);
            DoSummon(DARK_RUNE_ACOLYTE, TunnelRunPos11, 1);
        _EnterCombat();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

    if (Phase == 1)
    { 
        if (SummonArenaAds < diff )
        {
            switch (urand(0, 3))
            {
            case 0: 
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_CHAMPION, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_EVOKER, AdsSummonPos0, 1);
                DoSummon(DARK_RUNE_WARBRINGER, AdsSummonPos0, 1);
                break;
            case 1:
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_CHAMPION, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_EVOKER, AdsSummonPos1, 1);
                DoSummon(DARK_RUNE_WARBRINGER, AdsSummonPos1, 1);
                break;
            case 2:
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_CHAMPION, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_EVOKER, AdsSummonPos2, 1);
                DoSummon(DARK_RUNE_WARBRINGER, AdsSummonPos2, 1);
                break;
            case 3:
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_COMMONER, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_CHAMPION, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_EVOKER, AdsSummonPos3, 1);
                DoSummon(DARK_RUNE_WARBRINGER, AdsSummonPos3, 1);
                break;
            }
            SummonArenaAds = 15000;
        }else SummonArenaAds -= diff;
    
        // Sheath Of Lightning Check
        if (SheathOfLightningTimer < diff )
        {
                DoCast(me->getVictim(), SPELL_SHEATH_OF_LIGHTNING);
            SheathOfLightningTimer = 10000;
        }else SheathOfLightningTimer -= diff;
        
        // Stormhammer
        if (StormhammerTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_STORMHAMMER);
            StormhammerTimer = 16000;
        }else StormhammerTimer -= diff;
        
        // Deafening Thunder
        if (DeafeningThunderTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_DEAFENING_THUNDER);
            DeafeningThunderTimer = 16000;
        }else DeafeningThunderTimer -= diff;
        
        // Charge Orb
        if (ChargeOrbTimer < diff )
        {
            DoCast(me->getVictim(), SPELL_CHARGE_ORB);
            ChargeOrbTimer = 16000;
        }else ChargeOrbTimer -= diff;
    
        // Berserk P1
        if (BerserkTimer < diff )
        {
           DoCast(me->getVictim(), SPELL_BERSERK);
        }else BerserkTimer -= diff;

    }
    
    if (Phase == 2)
    {
        
        // Chain Lightning
        if (ChainLightningTimer < diff )
        {
                DoCast(me->getVictim(), RAID_MODE(SPELL_CHAIN_LIGHTNING_N, SPELL_CHAIN_LIGHTNING_H));
            ChainLightningTimer = 16000;
        }else ChainLightningTimer -= diff;
        
        // Lightning Charge
        if (LightningChargeTimer < diff )
        {
                DoCast(me->getVictim(), SPELL_LIGHTNING_CHARGE);
            LightningChargeTimer = 16000;
        }else LightningChargeTimer -= diff;
        
        // Lightning Charge
        if (LightningCharge2Timer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_LIGHTNING_CHARGE_2);
            LightningCharge2Timer = 16000;
        }else LightningCharge2Timer -= diff;
        
        // Unbalancing Stirke
        if (UnbalancingStrikeTimer < diff )
        {
                DoCast(me->getVictim(), SPELL_UNBALANCING_STRIKE);
            UnbalancingStrikeTimer = 16000;
        }else UnbalancingStrikeTimer -= diff;
        
    }

        if ((me->GetHealth()*100 / me->GetMaxHealth()) < 30000)
        {
            DoScriptText(SAY_DEATH, me);
            me->setFaction(35);    
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->SummonGameObject(RAID_MODE(GO_THORIM_CHEST_N, GO_THORIM_CHEST_H), 2134.754, -284.914, 419.537,0,0,0,0,0,-10);
            DoScriptText(SAY_END_NORMAL_1, me);
            DoScriptText(SAY_END_NORMAL_2, me);
            DoScriptText(SAY_END_NORMAL_3, me);
            Reset();
            me->DisappearAndDie();

            if (m_pInstance)
                m_pInstance->SetData(TYPE_THORIM, DONE);
        }    

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_thorim(Creature* pCreature)
{
    return new boss_thorimAI(pCreature);
}


struct boss_sifAI : public BossAI
{
    boss_sifAI(Creature* pCreature) : BossAI(pCreature, TYPE_THORIM)
    {
    
    }
    uint32 BlizzardTimer;
    uint32 FrostNovaTimer;
    uint32 FrostboldVolleyTimer;
    uint32 TeleportTimer;
    uint32 FrostboldTimer;
    
    void Reset()
    {
    BlizzardTimer = 10000;
    FrostNovaTimer = 6000;
    FrostboldVolleyTimer = 9000;
    TeleportTimer = 5000;
    FrostboldTimer = 1000;
        _Reset();
    }

    void EnterCombat(Unit* pWho)
    {
        _EnterCombat();
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Blizzard Timer
        if (BlizzardTimer < diff )
        {
                DoCast(me->getVictim(), RAID_MODE(SPELL_BLIZZARD_N, SPELL_BLIZZARD_H));
            BlizzardTimer = 16000;
        }else BlizzardTimer -= diff;
        
        // Frost Nova
        if (FrostNovaTimer < diff )
        {
                DoCast(me->getVictim(), RAID_MODE(SPELL_FROST_NOVA_N, SPELL_FROST_NOVA_H));
            FrostNovaTimer = 7000;
        }else FrostNovaTimer -= diff;
        
        // Frostbold Volley
        if (FrostboldVolleyTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), RAID_MODE(SPELL_FROSTBOLD_VOLLEY_N, SPELL_FROSTBOLD_VOLLEY_H));
            FrostboldVolleyTimer = 10000;
        }else FrostboldVolleyTimer -= diff;
        
        // Frostbold
        if (FrostboldTimer < diff )
        {
            if (Unit *target = SelectUnit(SELECT_TARGET_RANDOM, 0))
                DoCast(me->getVictim(), SPELL_FROSTBOLD);
            FrostboldTimer = 1000;
        }else FrostboldVolleyTimer -= diff;
        
        // Random Teleport
        if (TeleportTimer < diff )
        {
            if (Unit *target = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
            me->GetMap()->CreatureRelocation(me, target->GetPositionX(),target->GetPositionY(),target->GetPositionZ(),target->GetOrientation());
            TeleportTimer = 6000;
        }else TeleportTimer -= diff;


    }
};

CreatureAI* GetAI_boss_sif(Creature* pCreature)
{
    return new boss_sifAI(pCreature);
}

void AddSC_boss_thorim()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "boss_thorim";
    newscript->GetAI = &GetAI_boss_thorim;
    newscript->RegisterSelf();
    
    newscript = new Script;
    newscript->Name = "boss_sif";
    newscript->GetAI = &GetAI_boss_sif;
    newscript->RegisterSelf();
}
