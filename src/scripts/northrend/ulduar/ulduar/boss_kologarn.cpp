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

/* ScriptData
SDName: Kologarn
SDAuthor: Hyperion
SD%Complete: 90
SDMissing: Eyebeam Visual - Der Strahl aus den Augen ist nicht sichtbar... buggy.. >:/
EndScriptData */

#include "ScriptedPch.h"
#include "ulduar.h"
#include "Vehicle.h"

enum KologarnSpells
{
    SPELL_OVERHEAD_SMASH_2H    = 63356, //64710
    SPELL_OVERHEAD_SMASH_1H    = 63573, //64715
    SPELL_STONE_SHOUT          = 64004,
    SPELL_PETRIFYING_BREATH    = 62030,
    SPELL_PETRIFYING_BREATH_H  = 63980,
    SPELL_FOCUSED_EYEBEAM      = 63346,
    SPELL_FOCUSED_EYEBEAM_H    = 63976,
    SPELL_RUMBLE               = 63818,

    SPELL_BERSERK              = 64238,

    SPELL_SHOCKWAVE            = 63783,
    SPELL_SHOCKWAVE_H          = 63982,

    SPELL_STONE_GRIP           = 64290,
    SPELL_STONE_GRIP_H         = 64292,
    SPELL_STONE_GRIP_STUNN     = 62056,
    SPELL_STONE_GRIP_VISUAL    = 63962,

    SPELL_EYEBEAM_VISUAL_FLOOR = 63977,
    SPELL_EYEBEAM_VISUAL_BEAM  = 45537
};

enum KologarnSounds
{
    SAY_BERSERK             = -1603238,    // Kologarn SAY_BERSERK   
    SAY_DEATH               = -1603237,    // Kologarn SAY_DEATH   
    SAY_GRAB_PLAYER         = -1603236,    // Kologarn SAY_GRAB_PLAYER   
    SAY_SHOCKWAVE           = -1603235,    // Kologarn SAY_SHOCKWAVE   
    SAY_RIGHT_ARM_GONE      = -1603234,    // Kologarn SAY_RIGHT_ARM_GONE
    SAY_LEFT_ARM_GONE       = -1603233,    // Kologarn SAY_LEFT_ARM_GONE 
    SAY_SLAY_2              = -1603232,    // Kologarn SAY_SLAY_2   
    SAY_SLAY_1              = -1603231,    // Kologarn SAY_SLAY_1   
    SAY_AGGRO               = -1603230     // Kologarn SAY_AGGRO
};

enum KologarnAchiev
{
    ACHIEV_RUBBLE_AND_ROLL      = 2959,     // Defeat Kologarn after causing at least 25 Rubble creatures to spawn in 10-player mode. 
    ACHIEV_RUBBLE_AND_ROLL_H    = 2960,     // Defeat Kologarn after causing at least 25 Rubble creatures to spawn in 25-player mode. 

    ACHIEV_WITH_OPEN_ARMS       = 2951,     // Defeat Kologarn without destroying either of his arms in 10-player mode. 
    ACHIEV_WITH_OPEN_ARMS_H     = 2952,     // Defeat Kologarn without destroying either of his arms in 25-player mode. 
};

enum KologarnNpcs
{
    NPC_RUBBLE                 = 33768,
    NPC_EYEBEAM_TRIGGER        = 33632      
};

enum KologarnArms
{
    ARM_LEFT                   = 0x1,   // 01
    ARM_RIGHT                  = 0x2    // 10
};

// Stone Grip Location
const Position StoneGripPos = { 1769.043, -6.466, 459.234, 0.178 };


// ######################
// ##  KOLOGARN
// ######################

struct boss_kologarnAI : public Scripted_NoMovementAI
{
    boss_kologarnAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature), BossVehicle(me->GetVehicleKit())
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        pMap = pCreature->GetMap();    
        Reset();
    }

    ScriptedInstance *pInstance;
    Creature *EyeTrigger1;
    Creature *EyeTrigger2;
    Vehicle *BossVehicle;
    Unit *pLeft;
    Unit *pRight;
    Map *pMap;

    bool EyeBeamVisual;
    bool OpenArmsAchiev;

    uint8 ArmFlags;
    uint8 ArmFlags2;

    uint32 BreathTimer;
    uint32 SmashTimer;
    uint32 EnrageTimer;
    uint32 LeftArmRespawn;
    uint32 RightArmRespawn;
    uint32 EyeBeamTimer;
    uint32 EyeBeamTimerVisual;
    uint32 RumbleCounter;

    void Reset()
    {
        // Timer
        BreathTimer = 5000;
        LeftArmRespawn = 30000;
        RightArmRespawn = 30000;
        EyeBeamTimer = 30000;
        EyeBeamTimerVisual = 0;
        SmashTimer = 10000 + rand() % 5000;
        EnrageTimer = 10 * MINUTE * IN_MILISECONDS;
        ArmFlags = (ARM_LEFT | ARM_RIGHT);
        RumbleCounter = 0;

        // clear trigger
        EyeTrigger1 = NULL;
        EyeTrigger2 = NULL;
        EyeBeamVisual = false;
        OpenArmsAchiev = true;

        // Despawn adds
        DespawnAdds();

        // make attackable
        me->RemoveFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
        
        if (pInstance)
        {
            // reset event
            pInstance->SetData(TYPE_KOLOGARN, NOT_STARTED);

            if (BossVehicle)
            {
                // Set the arms and save
                BossVehicle->InstallAllAccessories();
                SaveArms();
            }
        }
    }

    void DespawnAdds()
    {
        std::list<Creature*> RubbleAdds;
        std::list<Creature*> FocusingEye;
        GetCreatureListWithEntryInGrid(RubbleAdds, me, NPC_RUBBLE, 200.0f);
        for (std::list<Creature*>::iterator itr2 = RubbleAdds.begin(); itr2 != RubbleAdds.end(); itr2++)
        {
            (*itr2)->DisappearAndDie();
        }

        GetCreatureListWithEntryInGrid(FocusingEye, me, NPC_EYEBEAM_TRIGGER, 200.0f);
        for (std::list<Creature*>::iterator itr2 = FocusingEye.begin(); itr2 != FocusingEye.end(); itr2++)
        {
            (*itr2)->DisappearAndDie();
        }
    }

    void SaveArms()
    {
        if (BossVehicle)
        {
            pLeft = pRight = NULL;
            pLeft = BossVehicle->GetPassenger(0);
            pRight = BossVehicle->GetPassenger(1);
        }
    }

    void PassengerBoarded(Unit *pWho, int8 seatId, bool apply)
    {
        if (pWho->GetTypeId() == TYPEID_UNIT)
        {
            if (apply)
            {
                if (pWho->GetEntry() == NPC_KOLOGARN_LEFT_ARM)
                    ArmFlags |= ARM_LEFT;
                else if (pWho->GetEntry() == NPC_KOLOGARN_RIGHT_ARM)
                    ArmFlags |= ARM_RIGHT;
            }
            else
            {
                if (pWho->GetEntry() == NPC_KOLOGARN_LEFT_ARM)
                    ArmFlags &= ~ARM_LEFT;
                else if (pWho->GetEntry() == NPC_KOLOGARN_RIGHT_ARM)
                    ArmFlags &= ~ARM_RIGHT;
            }
        }
    }

    void ArmReset(int arm)
    {
        if (!BossVehicle)
            return;

        // Get the seat id
        uint8 ArmSeatID = arm - 15;

        // If there is no free place for the arm
        if (!BossVehicle->HasEmptySeat(ArmSeatID))
        {
            // Remove the arm
            if (ArmSeatID == 0)
                BossVehicle->RemovePassenger(pLeft);
            else
                BossVehicle->RemovePassenger(pRight);
        }
           
        // Add the arm
        if (Creature *NewArm = me->SummonCreature(NPC_KOLOGARN_LEFT_ARM + ArmSeatID, *me, TEMPSUMMON_CORPSE_TIMED_DESPAWN, 30000))
        {
            if (BossVehicle->HasEmptySeat(ArmSeatID))
                NewArm->EnterVehicle(BossVehicle, ArmSeatID);
        }

        // Save new arms
        SaveArms();
    }

    void Aggro(Unit *who) 
    {
        if (pInstance)
            pInstance->SetData(TYPE_KOLOGARN, IN_PROGRESS);

        if (pLeft)
            pLeft->AddThreat(who, 1.0f);
        
        if (pRight)
            pRight->AddThreat(who, 1.0f);

        DoScriptText(SAY_AGGRO, me);
    }

    void JustDied(Unit *killer)
    {
        if (pInstance)
        {
        // Chest Spawn
            me->SummonGameObject(RAID_MODE(GO_Kologarn_CHEST, GO_Kologarn_CHEST_HERO), 1836.52, -36.1111, 448.81, 0.558504,0,0,0,0,-10);

            pInstance->SetData(TYPE_KOLOGARN, DONE);
            // Achievement: Rubble and Roll
            if (RumbleCounter >= 25)
                pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_RUBBLE_AND_ROLL, ACHIEV_RUBBLE_AND_ROLL_H));

            // Achievement: With open Arms
            if (OpenArmsAchiev)
                pInstance->DoCompleteAchievement(RAID_MODE(ACHIEV_WITH_OPEN_ARMS, ACHIEV_WITH_OPEN_ARMS_H));
        }

        DoScriptText(SAY_DEATH, me);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Enrage
        if (EnrageTimer < diff)
        {
            DoScriptText(SAY_BERSERK, me);
            DoCast(me, SPELL_BERSERK);
            EnrageTimer = 30000;
        }
        else EnrageTimer -= diff;


        // Petrifying Breath
        if (BreathTimer <= diff)
        {
            if (!me->IsWithinDistInMap(me->getVictim(), ATTACK_DISTANCE))
                DoCast(me->getVictim(), RAID_MODE(SPELL_PETRIFYING_BREATH, SPELL_PETRIFYING_BREATH_H));
            BreathTimer = 5000;
        }
        else BreathTimer -= diff;


        // Arms
        if (pInstance)
        {
            if ((ArmFlags & ARM_LEFT) != ARM_LEFT)
            {
                // Respawn the Left-Arm
                if (LeftArmRespawn <= diff)
                {
                    ArmReset(TYPE_KOLOGARN_LEFT_ARM);
                    LeftArmRespawn = 30000;
                }
                else LeftArmRespawn -= diff;
            }

            if ((ArmFlags & ARM_RIGHT) != ARM_RIGHT)
            {
                // Respawn the Left-Arm
                if (RightArmRespawn <= diff)
                {
                    ArmReset(TYPE_KOLOGARN_RIGHT_ARM);
                    RightArmRespawn = 30000;
                }
                else RightArmRespawn -= diff;
            }
        }


        // Overhead Smash
        if (SmashTimer <= diff)
        {
            DoScriptText(SAY_SHOCKWAVE, me);

            // 2 Arms Alive
            if ((ArmFlags & ARM_LEFT) && (ArmFlags & ARM_RIGHT))
                DoCast(me->getVictim(), SPELL_OVERHEAD_SMASH_2H);

            // 1 Arm Alive
            if ((ArmFlags == ARM_LEFT) || (ArmFlags == ARM_RIGHT))
                DoCast(me->getVictim(), SPELL_OVERHEAD_SMASH_1H);

            // Timer Reset
            SmashTimer = 10000 + rand() % 5000;
        }
        else SmashTimer -= diff;


        // Eyebeam
        if (!EyeBeamVisual)
        {
            if (EyeBeamTimer <= diff)
            {
                if (Unit *pRandomU = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
                {
                    uint8 SummonCount = urand(1, 2);

                    // Reset Triggers
                    EyeTrigger1 = NULL;
                    EyeTrigger2 = NULL;

                    // Create new Triggers
                    if (SummonCount == 1)
                        EyeTrigger1 = me->SummonCreature(NPC_EYEBEAM_TRIGGER, *pRandomU);
                    else
                    {
                        EyeTrigger1 = me->SummonCreature(NPC_EYEBEAM_TRIGGER, *pRandomU);
                        EyeTrigger2 = me->SummonCreature(NPC_EYEBEAM_TRIGGER, *pRandomU);
                    }

                    // Start the visual beam
                    EyeBeamTimer = 0;
                    EyeBeamVisual = true;
                    EyeBeamTimerVisual = 8000;
                }
            }
            else
                EyeBeamTimer -= diff;
        }
        else
        {
            // The visual beam
            if (EyeBeamTimerVisual <= diff)
            {
                // Despawn the triggers
                if (EyeTrigger1) EyeTrigger1->DisappearAndDie();
                if (EyeTrigger2) EyeTrigger2->DisappearAndDie();

                // Reset timer for the eyebeam
                EyeBeamTimer = 30000;
                EyeBeamVisual = false;
                EyeBeamTimerVisual = 0;
            }
            else
                EyeBeamTimerVisual -= diff;
        }

        DoMeleeAttackIfReady();
    }
};

// ######################
// ## KOLOGARN LEFT ARM
// ######################

struct boss_kologarn_left_armAI : public Scripted_NoMovementAI
{
    boss_kologarn_left_armAI(Creature *pCreature) : Scripted_NoMovementAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    uint32 ShockwaveTimer;

    void Reset()
    {
        ShockwaveTimer = 20000 + rand() % 10000;
    }

    void JustDied(Unit *killer)
    {
        if (!pInstance)
            return;

        // Find Kologarn and Deal damage on him
        if (Creature *cKologarn = Unit::GetCreature((*me), pInstance->GetData64(TYPE_KOLOGARN)))
        {
            cKologarn->DealDamage(cKologarn, me->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            ((boss_kologarnAI*)cKologarn)->OpenArmsAchiev = false;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Shockwave
        if (ShockwaveTimer <= diff)
        {
            DoCast(me->getVictim(), SPELL_SHOCKWAVE);
            ShockwaveTimer = 20000 + rand() % 10000;
        }
        else ShockwaveTimer -= diff;
    }
};

// ######################
// ## KOLGOARN RIGHT ARM
// ######################

struct boss_kologarn_right_armAI : public Scripted_NoMovementAI
{
    boss_kologarn_right_armAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    Creature *SummonRubble;
    Unit *RandomTarget;
    Unit *GrippedPlayer;

    bool Gripped;

    uint32 GripThreshold;
    uint32 GripTimer;
    uint32 GripVisual;
  
    void Reset()
    {
        // Reset timer and Gripunit
        Gripped = false;
        GrippedPlayer = NULL;
        GripTimer = 10000 + rand() % 10000;
        GripVisual = 1000;
        GripThreshold = RAID_MODE(100000, 480000);
    }

    void JustDied(Unit *killer)
    {
        if (!pInstance)
            return;

        if (Gripped && GrippedPlayer && GrippedPlayer->isAlive())
        {
            // Remove the auras from the player
            GrippedPlayer->RemoveAurasDueToSpell(RAID_MODE(SPELL_STONE_GRIP, SPELL_STONE_GRIP_H));
            GrippedPlayer->RemoveAurasDueToSpell(SPELL_STONE_GRIP_VISUAL, true);
            GrippedPlayer->RemoveAurasDueToSpell(SPELL_STONE_GRIP_STUNN, true);
        }


        // Find Kologarn and deal damage on him
        if (Creature *cKologarn = Unit::GetCreature((*me), pInstance->GetData64(TYPE_KOLOGARN)))
        {
            cKologarn->DealDamage(cKologarn, me->GetMaxHealth(), NULL, DIRECT_DAMAGE, SPELL_SCHOOL_MASK_NORMAL, NULL, false);
            ((boss_kologarnAI*)cKologarn)->RumbleCounter += 5;
            ((boss_kologarnAI*)cKologarn)->OpenArmsAchiev = false;
        }

        // Summon 5 Rubbles
        for (int i = 0; i < 5; i++)
        {
            // Spawn Rummble and set infight with a random unit
            SummonRubble = me->SummonCreature(NPC_RUBBLE, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 10000);
            RandomTarget = SelectUnit(SELECT_TARGET_RANDOM, 0);

            // Set Rubble infight with the random target
            if (SummonRubble && RandomTarget && RandomTarget->isAlive())
                SummonRubble->AddThreat(RandomTarget, 1.0f);
        }
    }

    void DamageTaken(Unit *done_by, uint32 &dmg)
    {
        if (Gripped)
        {
            if (dmg >= GripThreshold)
                GripThreshold = 0;
            else
                GripThreshold -= dmg;
        }
    }

    Player* FindRandomUnit()
    {
        Map *pMap = me->GetMap();

        if (!pMap)
            return NULL;

        Map::PlayerList const &PL = pMap->GetPlayers();
        uint32 iSize = (PL.getSize() == 0) ? 1 : PL.getSize();
        uint32 iRand = urand(0, (iSize - 1));
        uint32 iCounter = 0;

        if (!PL.isEmpty())
        {
            for (Map::PlayerList::const_iterator i = PL.begin(); i != PL.end(); ++i)
            {
                if (iCounter == iRand)
                    return i->getSource();
                iCounter++;
            }
        }
        return NULL;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Stone Grip
        if (GripTimer <= diff)
        {
            // Reset Gripped
            Gripped = false;

            // Grip a random unit
            if (Unit *RandomUnit = SelectTarget(SELECT_TARGET_RANDOM, 0, 0, true))
            {
                me->MonsterTextEmote("Kologarns rechter Arm hat sich einen Spieler gegriffen!", 0, true);

                GripThreshold = RAID_MODE(100000, 480000);
                GrippedPlayer = RandomUnit;
                Gripped = true;

                // Cast the damage aura, visual aura and stunning aura on the player
                GrippedPlayer->CastSpell(GrippedPlayer, RAID_MODE(SPELL_STONE_GRIP, SPELL_STONE_GRIP_H), true);
                GrippedPlayer->CastSpell(GrippedPlayer, SPELL_STONE_GRIP_VISUAL, true);
                GrippedPlayer->CastSpell(GrippedPlayer, SPELL_STONE_GRIP_STUNN, true);

                // teleport the player to the right arm
                ((Player*)GrippedPlayer)->TeleportTo(603, StoneGripPos.GetPositionX(), StoneGripPos.GetPositionY(), StoneGripPos.GetPositionZ(), StoneGripPos.GetOrientation());
            }

            // Set the timer for the gripped player
            GripTimer = 10000 + rand() % 10000;
        }
        else
            GripTimer -= diff;

        // Gripped Player
        if (GripThreshold <= diff)
        {
            if (GrippedPlayer && GrippedPlayer->isAlive())
            {
                // Remove the auras from the player
                GrippedPlayer->RemoveAurasDueToSpell(RAID_MODE(SPELL_STONE_GRIP, SPELL_STONE_GRIP_H));
                GrippedPlayer->RemoveAurasDueToSpell(SPELL_STONE_GRIP_VISUAL, true);
                GrippedPlayer->RemoveAurasDueToSpell(SPELL_STONE_GRIP_STUNN, true);
            }

            GripThreshold = RAID_MODE(100000, 480000);
            GrippedPlayer = NULL;
            Gripped = false;
        }
        else
        {
            if (GripVisual <= diff)
            {
                if (Gripped && GrippedPlayer && GrippedPlayer->isAlive())
                    GrippedPlayer->CastSpell(GrippedPlayer, SPELL_STONE_GRIP_VISUAL, true);
                GripVisual = 800;
            }
            else
                GripVisual -= diff;
        }
    }
};


// ######################
// ## EYE BEAM TRIGGER
// ######################

struct mob_eyebeamAI : public ScriptedAI
{
    mob_eyebeamAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;

    void Reset()
    {
        // Visual aura
        DoCast(SPELL_EYEBEAM_VISUAL_FLOOR);
        me->SetReactState(REACT_AGGRESSIVE);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
    }
};

// ######################
// ## RUMBLE
// ######################

struct mob_rumbleAI : public ScriptedAI
{
    mob_rumbleAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        pInstance = (ScriptedInstance*)pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance *pInstance;
    uint32 RumbleTimer;

    void Reset()
    {
        RumbleTimer = 5000 + rand() % 5000;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        // Rumble
        if (RumbleTimer <= diff)
        {
            DoCast(SPELL_RUMBLE);
            RumbleTimer = 5000 + rand() % 5000;
        }
        else
            RumbleTimer -= diff;

        // Meele
        DoMeleeAttackIfReady();
    }
};


// ====================================================================================
CreatureAI* GetAI_boss_kologarn(Creature *pCreature)
{
    return new boss_kologarnAI(pCreature);
}

CreatureAI* GetAI_boss_kologarn_left_arm(Creature *pCreature)
{
    return new boss_kologarn_left_armAI(pCreature);
}

CreatureAI* GetAI_boss_kologarn_right_arm(Creature *pCreature)
{
    return new boss_kologarn_right_armAI(pCreature);
}

CreatureAI* GetAI_mob_eyebeam(Creature *pCreature)
{
    return new mob_eyebeamAI(pCreature);
}

CreatureAI* GetAI_mob_rumble(Creature *pCreature)
{
    return new mob_rumbleAI(pCreature);
}

void AddSC_boss_kologarn()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_kologarn";
    newscript->GetAI = &GetAI_boss_kologarn;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_kologarn_left_arm";
    newscript->GetAI = &GetAI_boss_kologarn_left_arm;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_kologarn_right_arm";
    newscript->GetAI = &GetAI_boss_kologarn_right_arm;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_eyebeam";
    newscript->GetAI = &GetAI_mob_eyebeam;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "mob_rumble";
    newscript->GetAI = &GetAI_mob_rumble;
    newscript->RegisterSelf();
}