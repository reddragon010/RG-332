/*
    TODO:
        GENERAL:
            Add achievements
            Add raid messages
            Make adds do normal damage - DB related
        NATURE BOMB:
            Add glowing visual
        DETONATING LASHER:
            Flame lash not working - At least I think so
            Test if the switching target mechanism works - Needs several players
        ANCIENT CONSERVATOR:
            Produce a better work around for Potent Pheromones
            Make Healthy Spores friendly to mobs + friendly to players
            Make Healthy spores grow over time
        ELEMENTAL ADDS:
            Work around tidal wave
        EONARS GIFT:
            Add potent pheromones buff so players can get the buff.
            Growth rate needs adjustments. Grows to fast at the moment
        ELDER STONEBARK:
            Work around for petrified skin.
        ELDER IRONBRANCH:
            Lookup Thorn swarm timer
        ELDER BRIGHTLEAF
            Add brightleaf flux ability. I don't know how it's supposed to work
            
*/

#include "ScriptedPch.h"
#include "ulduar.h"

#define FACTION_FRIENDLY                           35
#define FACTION_HOSTILE                            16
#define OBJECT_FREYAS_GIFT_N                       194324
#define OBJECT_FREYAS_GIFT_H                       194327
#define OBJECT_NATURE_BOMB                         194902
#define MODEL_INVISIBLE                            11686

enum Spells
{
    //---------------------FREYA-------------------------
    SPELL_ATTUNED_TO_NATURE                    = 62519,
    RAID_10_SPELL_TOUCH_OF_EONAR               = 62528,
    RAID_25_SPELL_TOUCH_OF_EONAR               = 62892,
    RAID_10_SPELL_SUNBEAM                      = 62623,
    RAID_25_SPELL_SUNBEAM                      = 62872,
    SPELL_ENRAGE                               = 47008,
    RAID_10_SPELL_FREYA_GROUND_TREMOR          = 62437,
    RAID_25_SPELL_FREYA_GROUND_TREMOR          = 62859,
    RAID_10_SPELL_FREYA_IRON_ROOTS             = 62283,
    RAID_25_SPELL_FREYA_IRON_ROOTS             = 62930,
    RAID_10_SPELL_FREYA_UNSTABLE_ENERGY        = 62451,
    RAID_25_SPELL_FREYA_UNSTABLE_ENERGY        = 62865,
    SPELL_STONEBARKS_ESSENCE                   = 62386,
    SPELL_IRONBRANCHS_ESSENCE                  = 62387,
    SPELL_BRIGHTLEAFS_ESSENCE                  = 62385,
    SPELL_DRAINED_OF_POWER                     = 62467,
    //----------------DETONATING LASHER------------------
    RAID_10_SPELL_DETONATE                     = 62598,
    RAID_25_SPELL_DETONATE                     = 62937,
    SPELL_FLAME_LASH                           = 62608,
    //---------------ANCIENT CONSERVATOR-----------------
    SPELL_CONSERVATORS_GRIP                    = 62532,
    RAID_10_SPELL_NATURES_FURY                 = 62589,
    RAID_25_SPELL_NATURES_FURY                 = 63571,
    //--------------ANCIENT WATER SPIRIT-----------------
    SPELL_TIDAL_WAVE                           = 62935,
    //------------------STORM LASHER---------------------
    RAID_10_SPELL_LIGHTNING_LASH               = 62648,
    RAID_25_SPELL_LIGHTNING_LASH               = 62939,
    RAID_10_SPELL_STORMBOLT                    = 62649,
    RAID_25_SPELL_STORMBOLT                    = 62938,
    //-------------------SNAPLASHER----------------------
    RAID_10_SPELL_HARDENED_BARK                = 62664,
    RAID_25_SPELL_HARDENED_BARK                = 64191,
    //------------------NATURE BOMB----------------------
    RAID_10_SPELL_NATURE_BOMB                  = 64587,
    RAID_25_SPELL_NATURE_BOMB                  = 64650,
    //------------------EONARS GIFT----------------------
    RAID_10_SPELL_LIFEBINDERS_GIFT             = 62584, 
    RAID_25_SPELL_LIFEBINDERS_GIFT             = 64185,
    //-----------------HEALTHY SPORE---------------------
    SPELL_HEALTHY_SPORE_VISUAL                 = 62538,
    SPELL_POTENT_PHEROMONES                    = 62541,
    SPELL_POTENT_PHEROMONES_AURA               = 64321,
    //----------------ELDER STONEBARK--------------------
    RAID_10_SPELL_PETRIFIED_BARK               = 62337,
    RAID_25_SPELL_PETRIFIED_BARK               = 62933,
    SPELL_FISTS_OF_STONE                       = 62344,
    RAID_10_SPELL_GROUND_TREMOR                = 62325,
    RAID_25_SPELL_GROUND_TREMOR                = 62932,
    //----------------ELDER IRONBRANCH-------------------
    RAID_10_SPELL_IMPALE                       = 62310,
    RAID_25_SPELL_IMPALE                       = 62928,
    RAID_10_SPELL_THORN_SWARM                  = 62285,
    RAID_25_SPELL_THORN_SWARM                  = 62931,
    RAID_10_SPELL_IRON_ROOTS                   = 62438,
    RAID_25_SPELL_IRON_ROOTS                   = 62861,
    //----------------ELDER BRIGHTLEAF-------------------
    SPELL_BRIGHTLEAF_FLUX                      = 62262, //Not used
    SPELL_BRIGHTLEAF_FLUX_PLUS                 = 62251,
    SPELL_BRIGHTLEAF_FLUX_MINUS                = 62252,
    RAID_10_SPELL_UNSTABLE_ENERGY              = 62217,
    RAID_25_SPELL_UNSTABLE_ENERGY              = 62922,
    RAID_10_SPELL_SOLAR_FLARE                  = 62240,
    RAID_25_SPELL_SOLAR_FLARE                  = 62920,
    SPELL_PHOTOSYNTHESIS                       = 62209,
    SPELL_UNSTABLE_SUN_BEAM                    = 62211
};

enum Npcs
{
    NPC_SUN_BEAM                               = 33170,
    NPC_DETONATING_LASHER                      = 32918,
    NPC_ANCIENT_CONSERVATOR                    = 33203,
    NPC_ANCIENT_WATER_SPIRIT                   = 33202,
    NPC_STORM_LASHER                           = 32919,
    NPC_SNAPLASHER                             = 32916,
    NPC_NATURE_BOMB                            = 34129,
    NPC_EONARS_GIFT                            = 33228,
    NPC_HEALTHY_SPORE                          = 33215,
    NPC_UNSTABLE_SUN_BEAM                      = 33050
};

enum SpellTimers
{
    //---------------------FREYA-------------------------
    SUNBEAM_TIMER_MIN                          = 10000,
    SUNBEAM_TIMER_MAX                          = 14000,
    ENRAGE_TIMER                               = 600000,
    FREYA_GROUND_TREMOR_TIMER_MIN              = 25000,
    FREYA_GROUND_TREMOR_TIMER_MAX              = 30000,
    FREYA_IRON_ROOTS_TIMER_MIN                 = 31000,
    FREYA_IRON_ROOTS_TIMER_MAX                 = 32000,
    FREYA_SUN_BEAM_TIMER_MIN                   = 45000,
    FREYA_SUN_BEAM_TIMER_MAX                   = 60000,
    //----------------DETONATING LASHER------------------
    FLAME_LASH_TIMER                           = 10000,
    SWITCH_TARGET_TIMER_MIN                    = 2000,
    SWITCH_TARGET_TIMER_MAX                    = 4000,
    //---------------ANCIENT CONSERVATOR-----------------
    NATURES_FURY_TIMER                         = 5000,
    //--------------ANCIENT WATER SPIRIT-----------------
    TIDAL_WAVE_TIMER                           = 15000,
    //------------------STORM LASHER---------------------
    LIGHTNING_LASH_TIMER                       = 15000,
    STORMBOLT_TIMER                            = 15000,
    //----------------ELDER STONEBARK--------------------
    FISTS_OF_STONE_TIMER                       = 50000,
    GROUND_TREMOR_TIMER_MIN                    = 20000,
    GROUND_TREMOR_TIMER_MAX                    = 30000,
    //----------------ELDER IRONBRANCH-------------------
    IMPALE_TIMER_MIN                           = 17000,
    IMPALE_TIMER_MAX                           = 20000,
    THORN_SWARM_TIMER_MIN                      = 20000,
    THORN_SWARM_TIMER_MAX                      = 27000,
    IRON_ROOTS_TIMER_MIN                       = 17000,
    IRON_ROOTS_TIMER_MAX                       = 24000,
    //----------------ELDER BRIGHTLEAF-------------------
    BRIGHTLEAF_FLUX_TIMER                      = 4000,
    SOLAR_FLARE_TIMER_MIN                      = 20000,
    SOLAR_FLARE_TIMER_MAX                      = 30000
};

enum MiscTimers
{
    SPAWN_ADD_TIMER                            = 60000,
    ENTER_PHASE_TWO_TIMER                      = 320000,
    RESURRECTION_TIMER                         = 12000,
    SUN_BEAM_DESPAWN_TIME                      = 10000,
    SPAWN_HEALTHY_SPORE_TIMER                  = 2000,
    SPAWN_PAUSE_TIMER                          = 20000,
    NATURE_BOMB_TIMER                          = 15000,
    EONARS_GIFT_TIMER_MIN                      = 40000,
    EONARS_GIFT_TIMER_MAX                      = 60000,
    LIFEBINDERS_GIFT_DESPAWN_TIMER             = 10000,
    SCALE_TIMER                                = 500,
    UNSTABLE_SUN_BEAM_TIMER                    = 7000,
    UNSTABLE_SUN_BEAM_DESPAWN_TIMER_MIN        = 5000,
    UNSTABLE_SUN_BEAM_DESPAWN_TIMER_MAX        = 20000
};

enum Yells
{
    SAY_AGGRO                                   = -1603180,
    SAY_AGGRO_WITH_ELDER                        = -1603181,
    SAY_SLAY_1                                  = -1603182,
    SAY_SLAY_2                                  = -1603183,
    SAY_DEATH                                   = -1603184,
    SAY_BERSERK                                 = -1603185,
    SAY_SUMMON_CONSERVATOR                      = -1603186,
    SAY_SUMMON_TRIO                             = -1603187,
    SAY_SUMMON_LASHERS                          = -1603188,
    SAY_YS_HELP                                 = -1603189,

    // Elder Brightleaf
    SAY_BRIGHTLEAF_AGGRO                        = -1603190,
    SAY_BRIGHTLEAF_SLAY_1                       = -1603191,
    SAY_BRIGHTLEAF_SLAY_2                       = -1603192,
    SAY_BRIGHTLEAF_DEATH                        = -1603193,

    // Elder Ironbranch
    SAY_IRONBRANCH_AGGRO                        = -1603194,
    SAY_IRONBRANCH_SLAY_1                       = -1603195,
    SAY_IRONBRANCH_SLAY_2                       = -1603196,
    SAY_IRONBRANCH_DEATH                        = -1603197,

    // Elder Stonebark
    SAY_STONEBARK_AGGRO                         = -1603198,
    SAY_STONEBARK_SLAY_1                        = -1603199,
    SAY_STONEBARK_SLAY_2                        = -1603200,
    SAY_STONEBARK_DEATH                         = -1603201,
};


//----------------GLOBAL VARIABLES-------------------
uint16 attunedToNatureStacks;
Creature* pFreya;
bool bFirstWave;
Creature* elementalAdds[6];
int32 uiRessTimer[2];
bool bElementalAddKilled[2];
Creature* pStonebark;
Creature* pIronbranch;
Creature* pBrightleaf;
Unit* pRootTarget;
int32 uiRandomDespawnSunBeamTimer;

//-----------------GLOBAL METHODS--------------------
void updateAttunedToNatureStacks()
{
    //Removes all the stacks and then add the new amount. Probably could have been done better.
    pFreya->RemoveAurasDueToSpell(SPELL_ATTUNED_TO_NATURE);
    for (uint16 n = 0; n < attunedToNatureStacks; n++)
        pFreya->CastSpell(pFreya, SPELL_ATTUNED_TO_NATURE, false);
}

struct boss_freyaAI : public BossAI
{
    boss_freyaAI(Creature* pCreature) : BossAI(pCreature, TYPE_FREYA)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        pFreya = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiSunbeamTimer;
    int32 uiSpawnAddTimer;
    int32 uiEnterPhaseTwoTimer;
    uint8 phase;
    uint8 spawnOrder[3];
    uint8 spawnedAdds;
    int32 uiEonarsTimer;
    int32 uiNatureBombTimer;
    int32 uiEnrageTimer;
    bool bEnraged;
    int32 uiGroundTremorTimer;
    int32 uiIronRootTimer;
    int32 uiUnstableSunBeamTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void Reset()
    {
        uiSunbeamTimer = refreshTimer(SUNBEAM_TIMER_MIN, SUNBEAM_TIMER_MAX);
        uiSpawnAddTimer = SPAWN_ADD_TIMER / 4;
        uiEnterPhaseTwoTimer = ENTER_PHASE_TWO_TIMER;
        phase = 1;
        attunedToNatureStacks = 150;
        spawnedAdds = 0;
        randomizeSpawnOrder();
        uiEonarsTimer = refreshTimer(EONARS_GIFT_TIMER_MIN, EONARS_GIFT_TIMER_MAX);
        uiNatureBombTimer = NATURE_BOMB_TIMER;
        bFirstWave = true;
        uiRessTimer[0] = RESURRECTION_TIMER;
        uiRessTimer[1] = RESURRECTION_TIMER;
        uiEnrageTimer = ENRAGE_TIMER;
        bEnraged = false;
        uiGroundTremorTimer = refreshTimer(FREYA_GROUND_TREMOR_TIMER_MIN, FREYA_GROUND_TREMOR_TIMER_MAX);
        uiIronRootTimer = refreshTimer(FREYA_IRON_ROOTS_TIMER_MIN, FREYA_IRON_ROOTS_TIMER_MAX);
        uiUnstableSunBeamTimer = refreshTimer(FREYA_SUN_BEAM_TIMER_MIN, FREYA_SUN_BEAM_TIMER_MAX);
    }

    void KilledUnit(Unit* victim)
    {
        switch (rand() % 1)
        {
            case 0: me->MonsterYell("Forgive me.", 0 , 0); break;
            case 1: me->MonsterYell("From your death springs life anew!", 0 , 0); break;
        }
    }

    void JustDied(Unit *victim)
    {
        //If Freya dies - could happen! Make sure the event is done and the loot dropped
        if (m_pInstance)
            m_pInstance->SetData(TYPE_FREYA, DONE);

        me->MonsterYell("His hold on me dissipates. I can see clearly once more. Thank you, heroes.", 0, 0);

        float x = me->GetPositionX();
        float y = me->GetPositionY();
        float z = me->GetPositionZ();
        float ang = me->GetOrientation();

        float rot2 = sin(ang/2);
        float rot3 = cos(ang/2);

        me->SummonGameObject(RAID_MODE(OBJECT_FREYAS_GIFT_N, OBJECT_FREYAS_GIFT_H), x, y, z, ang, 0, 0, rot2, rot3, 0);
    }

    void EnterCombat(Unit* who)
    {
        DoCast(me, RAID_MODE(RAID_10_SPELL_TOUCH_OF_EONAR, RAID_25_SPELL_TOUCH_OF_EONAR));
        updateAttunedToNatureStacks();
        me->MonsterYell("The Conservatory must be protected!", 0, 0);
        if (pStonebark->isAlive())
            DoCast(me, SPELL_STONEBARKS_ESSENCE);
        //Server crashes every time this spell is casted
        /*if(pBrightleaf->isAlive())
            DoCast(me, SPELL_BRIGHTLEAFS_ESSENCE);*/
        if (pIronbranch->isAlive())
            DoCast(me, SPELL_IRONBRANCHS_ESSENCE);
    }

    void UpdateAI(const uint32 diff)
    {
        //Freya wont reset unless this is done
        if (!UpdateVictim())
        {
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->GetMotionMaster()->MoveTargetedHome();
            Reset();
            return;
        }

        if (uiSunbeamTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            DoCast(pTarget, RAID_MODE(RAID_10_SPELL_SUNBEAM, RAID_25_SPELL_SUNBEAM));
            uiSunbeamTimer = refreshTimer(SUNBEAM_TIMER_MIN, SUNBEAM_TIMER_MAX);
        }
        else
            uiSunbeamTimer -= diff;

        if (uiEonarsTimer <= 0)
        {
            int8 randomX = -25 + rand() % 50;
            int8 randomY = -25 + rand() % 50;
            me->SummonCreature(NPC_EONARS_GIFT, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ() + 5, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
            uiEonarsTimer = refreshTimer(EONARS_GIFT_TIMER_MIN, EONARS_GIFT_TIMER_MAX);
        }
        else
            uiEonarsTimer -= diff;

        if (uiGroundTremorTimer <= 0)
        {
            DoCastAOE(RAID_MODE(RAID_10_SPELL_FREYA_GROUND_TREMOR, RAID_25_SPELL_FREYA_GROUND_TREMOR));
            uiGroundTremorTimer = refreshTimer(FREYA_GROUND_TREMOR_TIMER_MIN, FREYA_GROUND_TREMOR_TIMER_MAX);
        }
        else if (pStonebark->isAlive())
            uiGroundTremorTimer -= diff;

        if (uiIronRootTimer <= 0)
        {
            pRootTarget = SelectTarget(SELECT_TARGET_RANDOM);
            pRootTarget->CastSpell(me, RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS), false);
            uiIronRootTimer = refreshTimer(IRON_ROOTS_TIMER_MIN, IRON_ROOTS_TIMER_MAX);
        }
        else if (pIronbranch->isAlive())
            uiIronRootTimer -= diff;

        if (uiUnstableSunBeamTimer <= 0)
        {
            for (int8 n = 0; n < 3; n++)
            {
                Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
                me->SummonCreature(NPC_SUN_BEAM, pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, SUN_BEAM_DESPAWN_TIME);
            }
            uiUnstableSunBeamTimer = refreshTimer(FREYA_SUN_BEAM_TIMER_MIN, FREYA_SUN_BEAM_TIMER_MAX);
        }
        else if (pBrightleaf->isAlive())
            uiUnstableSunBeamTimer -= diff;

        if (uiEnrageTimer <= 0 && !bEnraged)
        {
            DoCast(me, SPELL_ENRAGE);
            me->MonsterYell("You have strayed too far, wasted too much time!", 0, 0);
            bEnraged = true;
        }
        else
            uiEnrageTimer -= diff;

        if (phase == 1)
        {
            if (uiSpawnAddTimer <= 0)
            {
                spawnAdd();
                uiSpawnAddTimer = SPAWN_ADD_TIMER;
            }
            else
                uiSpawnAddTimer -= diff;

            if (uiEnterPhaseTwoTimer <= 0 && phase == 1)
                phase = 2;
            else
                uiEnterPhaseTwoTimer -= diff;

            potentPheromones();
        }
        else
        {
            if (uiNatureBombTimer <= 0)
            {
                spawnNatureBomb();
                uiNatureBombTimer = NATURE_BOMB_TIMER;
            }
            else
                uiNatureBombTimer -= diff;
        }

        //Ressurrection of elemental adds handler - works even if both waves of elemental adds are alive at the same time!
        if (bElementalAddKilled[0])
            uiRessTimer[0] -= diff;
        else if (bElementalAddKilled[1])
            uiRessTimer[1] -= diff;

        if (uiRessTimer[0] <= 0)
        {
            //Im not 100% sure that this is neccessary
            bool swap = false;
            if (!bFirstWave)
            {
                bFirstWave = true;
                swap = true;
            }
            bElementalAddKilled[0] = false;
            if (elementalAdds[0]->isAlive() || elementalAdds[1]->isAlive() || elementalAdds[2]->isAlive())
            {
                //Resurrect those mobs that are dead - if not dead, give full health.
                if (!elementalAdds[0]->isAlive())
                {
                    elementalAdds[0]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[0]->SetHealth(elementalAdds[0]->GetMaxHealth());

                if (!elementalAdds[1]->isAlive())
                {
                    elementalAdds[1]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[1]->SetHealth(elementalAdds[0]->GetMaxHealth());

                if (!elementalAdds[2]->isAlive())
                {
                    elementalAdds[2]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[2]->SetHealth(elementalAdds[0]->GetMaxHealth());

                updateAttunedToNatureStacks();
            }
            if (swap)
                bFirstWave = false;
            uiRessTimer[0] = RESURRECTION_TIMER;
        }
        else if (uiRessTimer[1] <= 0)
        {
            bElementalAddKilled[1] = false;
            if (elementalAdds[3]->isAlive() || elementalAdds[4]->isAlive() || elementalAdds[5]->isAlive())
            {
                //Ress those mobs that are dead
                if (!elementalAdds[3]->isAlive())
                {
                    elementalAdds[3]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[3]->SetHealth(elementalAdds[0]->GetMaxHealth());

                if (!elementalAdds[4]->isAlive())
                {
                    elementalAdds[4]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[4]->SetHealth(elementalAdds[0]->GetMaxHealth());

                if (!elementalAdds[5]->isAlive())
                {
                    elementalAdds[5]->Respawn();
                    attunedToNatureStacks += 10;
                }
                else
                    elementalAdds[5]->SetHealth(elementalAdds[0]->GetMaxHealth());

                updateAttunedToNatureStacks();
            }

            uiRessTimer[1] = RESURRECTION_TIMER;
        }

        //Become friendly and give loot
        if (HealthBelowPct(1))
        {
            me->setFaction(FACTION_FRIENDLY);
            me->MonsterYell("His hold on me dissipates. I can see clearly once more. Thank you, heroes.", 0, 0);
            if (m_pInstance)
                m_pInstance->SetData(TYPE_FREYA, DONE);

            float x = me->GetPositionX();
            float y = me->GetPositionY();
            float z = me->GetPositionZ();
            float ang = me->GetOrientation();
            float rot2 = sin(ang/2);
            float rot3 = cos(ang/2);
            me->SummonGameObject(RAID_MODE(OBJECT_FREYAS_GIFT_N, OBJECT_FREYAS_GIFT_H), x, y, z, ang, 0, 0, rot2, rot3, 0);
            //Resets
            me->RemoveAllAuras();
            me->DeleteThreatList();
            me->CombatStop(false);
            me->GetMotionMaster()->MoveTargetedHome();
            Reset();
        }

        DoMeleeAttackIfReady();
    }

    void randomizeSpawnOrder()
    {
        //Spawn order algorithm
        spawnOrder[0] = 0; //Detonating Lasher
        spawnOrder[1] = 1; //Elemental Adds 
        spawnOrder[2] = 2; //Ancient Conservator
        
        //Swaps the entire array
        for (uint8 n = 0; n < 3; n++)
        {
            uint8 random = rand() % 2;
            uint8 temp = spawnOrder[random];
            spawnOrder[random] = spawnOrder[n];
            spawnOrder[n] = temp;
        }
    }

    void spawnAdd()
    {
        switch (spawnedAdds)
        {
            case 0: spawnHandler(spawnOrder[0]);break;
            case 1: spawnHandler(spawnOrder[1]);break;
            case 2: spawnHandler(spawnOrder[2]);break;
        }

        spawnedAdds++;
        if (spawnedAdds > 2)
        {
            spawnedAdds = 0;
            bFirstWave = false;
        }
    }

    void spawnHandler(uint8 add)
    {
        switch (add)
        {
            case 0:
            {
                me->MonsterYell("The swarm of the elements shall overtake you!", 0, 0);
                //Spawn 10 Detonating Lashers
                for (uint8 n = 0; n < 10; n++)
                {
                    //Make sure that they don't spawn in a pile
                    int8 randomX = -25 + rand() % 50;
                    int8 randomY = -25 + rand() % 50;
                    me->SummonCreature(NPC_DETONATING_LASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                }
                break;
            }
            case 1:
            {
                 me->MonsterYell("Children, assist me!", 0, 0);
                //Make sure that they don't spawn in a pile
                int8 randomX = -25 + rand() % 50;
                int8 randomY = -25 + rand() % 50;
                me->SummonCreature(NPC_SNAPLASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                randomX = -25 + rand() % 50;
                randomY = -25 + rand() % 50;
                me->SummonCreature(NPC_ANCIENT_WATER_SPIRIT, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                randomX = -25 + rand() % 50;
                randomY = -25 + rand() % 50;
                me->SummonCreature(NPC_STORM_LASHER, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                break;
            }
            case 2: 
            {
                me->MonsterYell("Eonar, your servant requires aid!", 0, 0);
                int8 randomX = -25 + rand() % 50;
                int8 randomY = -25 + rand() % 50;
                me->SummonCreature(NPC_ANCIENT_CONSERVATOR, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 60000);
                break;
            }
        }
    }

    void spawnNatureBomb()
    {
        //70% chance that you get a nature bomb spawned at your feet.
        Map* pMap = me->GetMap();
        if (pMap && pMap->IsDungeon())
        {
            Map::PlayerList const &PlayerList = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            {
                uint8 random = rand() % 100;
                if (i->getSource()->isAlive() && random < 70)
                {
                    //Manually despawned to avoid bugs where the explosion never happens
                    me->SummonCreature(NPC_NATURE_BOMB, i->getSource()->GetPositionX(), i->getSource()->GetPositionY(), i->getSource()->GetPositionZ());
                }
            }
        }
    }

    //Removes the silence effect if the player has the potent pheromones aura.
    void potentPheromones()
    {
        Map* pMap = me->GetMap();
        if (pMap && pMap->IsDungeon())
        {
            Map::PlayerList const &PlayerList = pMap->GetPlayers();
            for (Map::PlayerList::const_iterator i = PlayerList.begin(); i != PlayerList.end(); ++i)
            {
                if (i->getSource()->HasAura(SPELL_POTENT_PHEROMONES_AURA))
                {
                    i->getSource()->RemoveAurasDueToSpell(SPELL_CONSERVATORS_GRIP);
                }
            }
        }
    }
};

CreatureAI* GetAI_boss_freya(Creature* pCreature)
{
    return new boss_freyaAI(pCreature);
}

struct creature_nature_bombAI : public Scripted_NoMovementAI
{
    creature_nature_bombAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        uiExplosionTimer = NATURE_BOMB_TIMER - 3000;
        //Summon the object, make it despawn when the spell goes off. Timed despawn.
        float x = me->GetPositionX();
        float y = me->GetPositionY();
        float z = me->GetPositionZ();
        float ang = me->GetOrientation();

        float rot2 = sin(ang/2);
        float rot3 = cos(ang/2);

        me->SummonGameObject(OBJECT_NATURE_BOMB, x, y, z, ang, 0, 0, rot2, rot3, 0);
        bExploded = false;
        me->SetDisplayId(MODEL_INVISIBLE);
    }

    ScriptedInstance* m_pInstance;
    int32 uiExplosionTimer;
    bool bExploded;

    void UpdateAI(const uint32 diff)
    {
        if (uiExplosionTimer <= 0 && !bExploded)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_NATURE_BOMB, RAID_25_SPELL_NATURE_BOMB));
            bExploded = true;
        }
        else if (uiExplosionTimer <= -1000 && bExploded)
        {
            me->ForcedDespawn();
        }
        else
            uiExplosionTimer -= diff;
    }
};

CreatureAI* GetAI_creature_nature_bomb(Creature* pCreature)
{
    return new creature_nature_bombAI(pCreature);
}

struct creature_detonating_lasherAI : public ScriptedAI
{
    creature_detonating_lasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    int32 uiFlameLashTimer;
    int32 uiSwitchTargetTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void JustDied(Unit* victim)
    {
        DoCast(me, RAID_MODE(RAID_10_SPELL_DETONATE, RAID_25_SPELL_DETONATE));
        attunedToNatureStacks -= 2;
        updateAttunedToNatureStacks();
    }

    void Reset()
    {
        uiFlameLashTimer = FLAME_LASH_TIMER;
        uiSwitchTargetTimer = refreshTimer(SWITCH_TARGET_TIMER_MIN, SWITCH_TARGET_TIMER_MAX);
    }

    void updateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiFlameLashTimer <= 0)
        {
            DoCast(me, SPELL_FLAME_LASH);
            uiFlameLashTimer = FLAME_LASH_TIMER;
        }
        else
            uiFlameLashTimer -= diff;

        if (uiSwitchTargetTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            me->Attack(pTarget, true);
            uiSwitchTargetTimer = refreshTimer(SWITCH_TARGET_TIMER_MIN, SWITCH_TARGET_TIMER_MAX);
        }
        else
            uiSwitchTargetTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_creature_detonating_lasher(Creature* pCreature)
{
    return new creature_detonating_lasherAI(pCreature);
}

struct creature_ancient_conservatorAI : public ScriptedAI
{
    creature_ancient_conservatorAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
    }

    ScriptedInstance* m_pInstance;
    int32 uiNaturesFuryTimer;
    int32 uiSpawnHealthySporeTimer;
    uint8 healthySporesSpawned;
    int32 uiSpawnPauseTimer;

    void Reset()
    {
        uiNaturesFuryTimer = NATURES_FURY_TIMER;
        uiSpawnHealthySporeTimer = SPAWN_HEALTHY_SPORE_TIMER * 3;
        healthySporesSpawned = 0;
        uiSpawnPauseTimer = SPAWN_PAUSE_TIMER;
    }

    void JustDied(Unit* victim)
    {
        attunedToNatureStacks -= 25;
        updateAttunedToNatureStacks();
    }

    void EnterCombat(Unit* who)
    {
       DoCast(me->getVictim(), SPELL_CONSERVATORS_GRIP);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiNaturesFuryTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            //Prevent casting natures fury on a target that is already affected
            if (!pTarget->HasAura(RAID_MODE(RAID_10_SPELL_NATURES_FURY, RAID_25_SPELL_NATURES_FURY)))
                DoCast(pTarget, RAID_MODE(RAID_10_SPELL_NATURES_FURY, RAID_25_SPELL_NATURES_FURY));
            uiNaturesFuryTimer = NATURES_FURY_TIMER;
        }
        else
            uiNaturesFuryTimer -= diff;

        if (uiSpawnHealthySporeTimer <= 0 && healthySporesSpawned < 10)
        {
            int8 randomX = -35 + rand() % 70;
            int8 randomY = -35 + rand() % 70;
            me->SummonCreature(NPC_HEALTHY_SPORE, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 20000);
            randomX = -35 + rand() % 70;
            randomY = -35 + rand() % 70;
            me->SummonCreature(NPC_HEALTHY_SPORE, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ(), 0, TEMPSUMMON_TIMED_DESPAWN, 20000);
            healthySporesSpawned += 2;
            uiSpawnHealthySporeTimer = SPAWN_HEALTHY_SPORE_TIMER;
        }
        else
            uiSpawnHealthySporeTimer -= diff;

        if (uiSpawnPauseTimer <= 0)
        {
            healthySporesSpawned = 0;
            uiSpawnPauseTimer = SPAWN_PAUSE_TIMER;
            uiSpawnHealthySporeTimer = 0;
        }
        else
            uiSpawnPauseTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_creature_ancient_conservator(Creature* pCreature)
{
    return new creature_ancient_conservatorAI(pCreature);
}

struct creature_healthy_sporeAI : public Scripted_NoMovementAI
{
    creature_healthy_sporeAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        DoCast(me, SPELL_HEALTHY_SPORE_VISUAL);
        DoCast(me, SPELL_POTENT_PHEROMONES);
    }

    ScriptedInstance* m_pInstance;

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;
    }
};

CreatureAI* GetAI_creature_healthy_spore(Creature* pCreature)
{
    return new creature_healthy_sporeAI(pCreature);
}

struct creature_storm_lasherAI : public ScriptedAI
{
    creature_storm_lasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        if (bFirstWave)
            elementalAdds[0] = me;
        else
            elementalAdds[3] = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiLightningLashTimer;
    int32 uiStormboltTimer;

    void Reset()
    {
        uiLightningLashTimer = LIGHTNING_LASH_TIMER;
        uiStormboltTimer = STORMBOLT_TIMER;
    }

    void JustDied(Unit* victim)
    {
        attunedToNatureStacks -= 10;
        updateAttunedToNatureStacks();

        if (elementalAdds[0] == me)
            bElementalAddKilled[0] = true;
        else if (elementalAdds[3] == me)
            bElementalAddKilled[1] = true;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiLightningLashTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            DoCast(pTarget, RAID_MODE(RAID_10_SPELL_LIGHTNING_LASH, RAID_25_SPELL_LIGHTNING_LASH));
            uiLightningLashTimer = LIGHTNING_LASH_TIMER;
        }
        else
            uiLightningLashTimer -= diff;

        if (uiStormboltTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            DoCast(pTarget, RAID_MODE(RAID_10_SPELL_STORMBOLT, RAID_25_SPELL_STORMBOLT));
            uiStormboltTimer = STORMBOLT_TIMER;
        }
        else
            uiStormboltTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_creature_storm_lasher(Creature* pCreature)
{
    return new creature_storm_lasherAI(pCreature);
}

struct creature_snaplasherAI : public ScriptedAI
{
    creature_snaplasherAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        if (bFirstWave)
            elementalAdds[1] = me;
        else
            elementalAdds[4] = me;
    }

    ScriptedInstance* m_pInstance;
    uint32 health;

    void Reset()
    {
        health = me->GetHealth();
    }

    void JustDied(Unit* victim)
    {
        attunedToNatureStacks -= 10;
        updateAttunedToNatureStacks();

        if (elementalAdds[1] == me)
            bElementalAddKilled[0] = true;
        else if (elementalAdds[4] == me)
            bElementalAddKilled[1] = true;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (health != me->GetHealth())
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_HARDENED_BARK, RAID_25_SPELL_HARDENED_BARK));
            health = me->GetHealth();
        }

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_creature_snaplasher(Creature* pCreature)
{
    return new creature_snaplasherAI(pCreature);
}

struct creature_ancient_water_spiritAI : public ScriptedAI
{
    creature_ancient_water_spiritAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        if (bFirstWave)
            elementalAdds[2] = me;
        else
            elementalAdds[5] = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiTidalWaveTimer;

    void Reset()
    {
        uiTidalWaveTimer = TIDAL_WAVE_TIMER;
    }

    void JustDied(Unit* victim)
    {
        attunedToNatureStacks -= 10;
        updateAttunedToNatureStacks();

        if (elementalAdds[2] == me)
            bElementalAddKilled[0] = true;
        else if (elementalAdds[5] == me)
            bElementalAddKilled[1] = true;
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiTidalWaveTimer <= 0)
        {
            DoCast(me->getVictim(), SPELL_TIDAL_WAVE);
            uiTidalWaveTimer = TIDAL_WAVE_TIMER;
        }
        else
            uiTidalWaveTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_creature_ancient_water_spirit(Creature* pCreature)
{
    return new creature_ancient_water_spiritAI(pCreature);
}

struct creature_eonars_giftAI : public Scripted_NoMovementAI
{
    creature_eonars_giftAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        uiLifebindersGiftTimer = LIFEBINDERS_GIFT_DESPAWN_TIMER;
        fScale = 0.2;
        me->SetFloatValue(OBJECT_FIELD_SCALE_X, fScale);
        uiScaleTimer = SCALE_TIMER;
        //Casted on freya and her adds - Should be casted on players. Removes Ancients Conservators aura right now. Disabled!
        //DoCast(me, SPELL_POTENT_PHEROMONES);
    }

    ScriptedInstance* m_pInstance;
    int32 uiLifebindersGiftTimer;
    float fScale;
    int32 uiScaleTimer;

    void UpdateAI(const uint32 diff)
    {
        if (uiLifebindersGiftTimer <= 0)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_LIFEBINDERS_GIFT, RAID_25_SPELL_LIFEBINDERS_GIFT));
            uiLifebindersGiftTimer = LIFEBINDERS_GIFT_DESPAWN_TIMER;
            fScale = 0.2;
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, fScale);
        }
        else
            uiLifebindersGiftTimer -= diff;

        if (uiScaleTimer <= 0)
        {
            fScale += 0.05;
            me->SetFloatValue(OBJECT_FIELD_SCALE_X, fScale);
        }
        else
            uiScaleTimer -= diff;
    }
};

CreatureAI* GetAI_creature_eonars_gift(Creature* pCreature)
{
    return new creature_eonars_giftAI(pCreature);
}

struct boss_elder_stonebarkAI : public ScriptedAI
{
    boss_elder_stonebarkAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        pStonebark = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiGroundTremorTimer;
    int32 uiFistsOfStoneTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void Reset()
    {
        uiGroundTremorTimer = refreshTimer(GROUND_TREMOR_TIMER_MIN, GROUND_TREMOR_TIMER_MAX);
        uiFistsOfStoneTimer = FISTS_OF_STONE_TIMER;
    }

    void JustDied(Unit* victim)
    {
        me->MonsterYell("Matron, flee! They are ruthless....", 0, 0);
    }

    void EnterCombat(Unit *who)
    {
        uiGroundTremorTimer /= 2;
        uiFistsOfStoneTimer /= 2;
        me->MonsterYell("This place will serve as your graveyard.", 0, 0);
    }

    void KilledUnit(Unit *who)
    {
        me->MonsterYell("Such a waste.", 0, 0);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiGroundTremorTimer <= 0)
        {
            DoCast(me->getVictim(), RAID_MODE(RAID_10_SPELL_GROUND_TREMOR, RAID_25_SPELL_GROUND_TREMOR));
            uiGroundTremorTimer = refreshTimer(GROUND_TREMOR_TIMER_MIN, GROUND_TREMOR_TIMER_MAX);
        }
        else
            uiGroundTremorTimer -= diff;

        if (uiFistsOfStoneTimer <= 0)
        {
            DoCast(me, SPELL_FISTS_OF_STONE);
            uiFistsOfStoneTimer = FISTS_OF_STONE_TIMER;
        }
        else
            uiFistsOfStoneTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_elder_stonebark(Creature* pCreature)
{
    return new boss_elder_stonebarkAI(pCreature);
}

struct boss_elder_ironbranchAI : public ScriptedAI
{
    boss_elder_ironbranchAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        pIronbranch = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiImpaleTimer;
    int32 uiThornSwarmTimer;
    int32 uiIronRootTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void Reset()
    {
        uiImpaleTimer = refreshTimer(IMPALE_TIMER_MIN, IMPALE_TIMER_MAX);
        uiThornSwarmTimer = refreshTimer(THORN_SWARM_TIMER_MIN, THORN_SWARM_TIMER_MAX);
        uiIronRootTimer = refreshTimer(IRON_ROOTS_TIMER_MIN, IRON_ROOTS_TIMER_MAX);
    }

    void EnterCombat(Unit *who)
    {
        uiThornSwarmTimer /= 2;
        me->MonsterYell("Mortals have no place here!", 0, 0);
    }

    void JustDied(Unit *who)
    {
        me->MonsterYell("Freya! They come for you.", 0, 0);
    }

    void KilledUnit(Unit *who)
    {
        switch (rand() % 1)
        {
            case 0: me->MonsterYell("I return you whence you came!", 0, 0); break;
            case 1: me->MonsterYell("BEGONE!", 0, 0); break;
        }
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiImpaleTimer <= 0 && me->IsWithinMeleeRange(me->getVictim()))
        {
            DoCast(me->getVictim(), RAID_MODE(RAID_10_SPELL_IMPALE, RAID_25_SPELL_IMPALE));
            uiImpaleTimer = refreshTimer(IMPALE_TIMER_MIN, IMPALE_TIMER_MAX);
        }
        else
            uiImpaleTimer -= diff;

        if (uiThornSwarmTimer <= 0)
        {
            Unit* pTarget = SelectTarget(SELECT_TARGET_RANDOM);
            DoCast(pTarget, RAID_MODE(RAID_10_SPELL_THORN_SWARM, RAID_25_SPELL_THORN_SWARM));
            uiThornSwarmTimer = refreshTimer(THORN_SWARM_TIMER_MIN, THORN_SWARM_TIMER_MAX);
        }
        else
            uiThornSwarmTimer -= diff;

        if (uiIronRootTimer <= 0)
        {
            pRootTarget = SelectTarget(SELECT_TARGET_RANDOM);
            if (!pRootTarget->HasAura(RAID_MODE(RAID_10_SPELL_IMPALE, RAID_25_SPELL_IMPALE)))
            {
                pRootTarget->CastSpell(me, RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS), false);
                uiIronRootTimer = refreshTimer(IRON_ROOTS_TIMER_MIN, IRON_ROOTS_TIMER_MAX);
            }
        }
        else
            uiIronRootTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_elder_ironbranch(Creature* pCreature)
{
    return new boss_elder_ironbranchAI(pCreature);
}

struct boss_elder_brightleafAI : public ScriptedAI
{
    boss_elder_brightleafAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        pBrightleaf = me;
    }

    ScriptedInstance* m_pInstance;
    int32 uiUnstableSunbeamTimer;
    int32 uiSolarFlareTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void Reset()
    {
        uiUnstableSunbeamTimer = UNSTABLE_SUN_BEAM_TIMER;
        uiSolarFlareTimer = refreshTimer(SOLAR_FLARE_TIMER_MIN, SOLAR_FLARE_TIMER_MAX);
    }

    void UpdateAI(const uint32 diff)
    {
        if (!UpdateVictim())
            return;

        if (uiUnstableSunbeamTimer <= 0)
        {
            float randomX = -10 + rand() % 20;
            float randomY = -10 + rand() % 20;
            //Z + 1: Make sure the sun beam isnt spawned beneath the ground
            me->SummonCreature(NPC_UNSTABLE_SUN_BEAM, me->GetPositionX() + randomX, me->GetPositionY() + randomY, me->GetPositionZ() + 1, 0);
            uiUnstableSunbeamTimer = UNSTABLE_SUN_BEAM_TIMER;
        }
        else
            uiUnstableSunbeamTimer -= diff;

        if (uiSolarFlareTimer <= 0)
        {
            DoCast(me, RAID_MODE(RAID_10_SPELL_SOLAR_FLARE, RAID_25_SPELL_SOLAR_FLARE));
            uiSolarFlareTimer = refreshTimer(SOLAR_FLARE_TIMER_MIN, SOLAR_FLARE_TIMER_MAX);
        }
        else
            uiSolarFlareTimer -= diff;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_boss_elder_brightleaf(Creature* pCreature)
{
    return new boss_elder_brightleafAI(pCreature);
}

struct creature_iron_rootsAI : public Scripted_NoMovementAI
{
    creature_iron_rootsAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        pPlayer = pRootTarget;
        //Should be done in the DB
        me->setFaction(FACTION_HOSTILE);
    }

    ScriptedInstance* m_pInstance;
    Unit* pPlayer;

    void JustDied(Unit* victim)
    {
        pPlayer->RemoveAurasDueToSpell(RAID_MODE(RAID_10_SPELL_IRON_ROOTS, RAID_25_SPELL_IRON_ROOTS));
    }

    void UpdateAI(const uint32 diff)
    {

    }
};

CreatureAI* GetAI_creature_iron_roots(Creature* pCreature)
{
    return new creature_iron_rootsAI(pCreature);
}

struct creature_unstable_sun_beamAI : public Scripted_NoMovementAI
{
    creature_unstable_sun_beamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        DoCast(me, SPELL_UNSTABLE_SUN_BEAM);
        DoCast(me, SPELL_PHOTOSYNTHESIS);
        uiDespawnTimer = refreshTimer(UNSTABLE_SUN_BEAM_DESPAWN_TIMER_MIN, UNSTABLE_SUN_BEAM_DESPAWN_TIMER_MAX);
        me->SetDisplayId(MODEL_INVISIBLE);
    }

    ScriptedInstance* m_pInstance;
    int32 uiDespawnTimer;

    uint32 refreshTimer(uint32 timer_min, uint32 timer_max)
    {
        if (timer_min == timer_max)
            return timer_min;
        else
            return timer_min + rand() % (timer_max - timer_min);
    }

    void UpdateAI(const uint32 diff)
    {
        if (uiDespawnTimer <= 0)
        {
            DoCastAOE(RAID_MODE(RAID_10_SPELL_UNSTABLE_ENERGY, RAID_25_SPELL_UNSTABLE_ENERGY));
            me->ForcedDespawn();
        }
        else
            uiDespawnTimer -= diff;
    }
};

CreatureAI* GetAI_creature_unstable_sun_beam(Creature* pCreature)
{
    return new creature_unstable_sun_beamAI(pCreature);
}

struct creature_sun_beamAI : public Scripted_NoMovementAI
{
    creature_sun_beamAI(Creature* pCreature) : Scripted_NoMovementAI(pCreature)
    {
        m_pInstance = pCreature->GetInstanceData();
        Reset();
        DoCast(RAID_MODE(RAID_10_SPELL_FREYA_UNSTABLE_ENERGY, RAID_25_SPELL_FREYA_UNSTABLE_ENERGY));
        me->SetDisplayId(MODEL_INVISIBLE);
        //Should be changed to just a visual
        DoCast(SPELL_UNSTABLE_SUN_BEAM);
    }

    ScriptedInstance* m_pInstance;

    void UpdateAI(const uint32 diff)
    {

    }
};

CreatureAI* GetAI_creature_sun_beam(Creature* pCreature)
{
    return new creature_sun_beamAI(pCreature);
}

void AddSC_boss_freya()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_freya";
    newscript->GetAI = &GetAI_boss_freya;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_nature_bomb";
    newscript->GetAI = &GetAI_creature_nature_bomb;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_detonating_lasher";
    newscript->GetAI = &GetAI_creature_detonating_lasher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_ancient_conservator";
    newscript->GetAI = &GetAI_creature_ancient_conservator;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_healthy_spore";
    newscript->GetAI = &GetAI_creature_healthy_spore;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_storm_lasher";
    newscript->GetAI = &GetAI_creature_storm_lasher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_snaplasher";
    newscript->GetAI = &GetAI_creature_snaplasher;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_ancient_water_spirit";
    newscript->GetAI = &GetAI_creature_ancient_water_spirit;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_eonars_gift";
    newscript->GetAI = &GetAI_creature_eonars_gift;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_stonebark";
    newscript->GetAI = &GetAI_boss_elder_stonebark;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_ironbranch";
    newscript->GetAI = &GetAI_boss_elder_ironbranch;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "boss_elder_brightleaf";
    newscript->GetAI = &GetAI_boss_elder_brightleaf;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_iron_roots";
    newscript->GetAI = &GetAI_creature_iron_roots;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_unstable_sun_beam";
    newscript->GetAI = &GetAI_creature_unstable_sun_beam;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "creature_sun_beam";
    newscript->GetAI = &GetAI_creature_sun_beam;
    newscript->RegisterSelf();
}
