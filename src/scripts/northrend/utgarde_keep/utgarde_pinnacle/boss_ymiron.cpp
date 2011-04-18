/* Script Data Start
SDName: Boss ymiron
SDAuthor: LordVanMartin
SD%Complete:
SDComment:
SDCategory:
Script Data End */

/*** SQL START ***
update creature_template set scriptname = 'boss_ymiron' where entry = '';
*** SQL END ***/
#include "ScriptedPch.h"
#include "utgarde_pinnacle.h"

enum Spells
{
    SPELL_BANE                                = 48294,
    H_SPELL_BANE                              = 59301,
    SPELL_DARK_SLASH                          = 48292,
    SPELL_FETID_ROT                           = 48291,
    H_SPELL_FETID_ROT                         = 59300,
    SPELL_SCREAMS_OF_THE_DEAD                 = 51750,
    SPELL_SPIRIT_BURST                        = 48529,
    H_SPELL_SPIRIT_BURST                      = 59305,
    SPELL_SPIRIT_STRIKE                       = 48423,
    H_SPELL_SPIRIT_STRIKE                     = 59304,
    SPELL_ANCESTORS_VENGEANCE                 = 16939,

    SPELL_SUMMON_AVENGING_SPIRIT              = 48592,
    SPELL_SUMMON_SPIRIT_FOUNT                 = 48386,

    SPELL_CHANNEL_SPIRIT_TO_YMIRON            = 48316,
    SPELL_CHANNEL_YMIRON_TO_SPIRIT            = 48307,

    SPELL_SPIRIT_FOUNT                        = 48380,
    H_SPELL_SPIRIT_FOUNT                      = 59320
};

//not in db
enum Yells
{
    SAY_AGGRO                               = -1575031,
    SAY_SUMMON_BJORN                        = -1575032,
    SAY_SUMMON_HALDOR                       = -1575033,
    SAY_SUMMON_RANULF                       = -1575034,
    SAY_SUMMON_TORGYN                       = -1575035,
    SAY_SLAY_1                              = -1575036,
    SAY_SLAY_2                              = -1575037,
    SAY_SLAY_3                              = -1575038,
    SAY_SLAY_4                              = -1575039,
    SAY_DEATH                               = -1575040,

};

enum Creatures
{
    CREATURE_BJORN                          = 27303,
    CREATURE_BJORN_VISUAL                   = 27304,
    CREATURE_HALDOR                         = 27307,
    CREATURE_HALDOR_VISUAL                  = 27310,
    CREATURE_RANULF                         = 27308,
    CREATURE_RANULF_VISUAL                  = 27311,
    CREATURE_TORGYN                         = 27309,
    CREATURE_TORGYN_VISUAL                  = 27312,
    CREATURE_SPIRIT_FOUNT                   = 27339,
    CREATURE_AVENGING_SPIRIT                = 27386
};
enum Achievements
{
    ACHIEV_KINGS_BANE                       = 2157
};

struct ActiveBoatStruct
{
    uint32 npc;
    uint32 say;
    float MoveX,MoveY,MoveZ,SpawnX,SpawnY,SpawnZ,SpawnO;
};

static ActiveBoatStruct ActiveBot[4] =
{
    {CREATURE_BJORN_VISUAL,  SAY_SUMMON_BJORN,  404.379, -335.335, 104.756, 413.594, -335.408, 107.995, 3.157},
    {CREATURE_HALDOR_VISUAL, SAY_SUMMON_HALDOR, 380.813, -335.069, 104.756, 369.994, -334.771, 107.995, 6.232},
    {CREATURE_RANULF_VISUAL, SAY_SUMMON_RANULF, 381.546, -314.362, 104.756, 370.841, -314.426, 107.995, 6.232},
    {CREATURE_TORGYN_VISUAL, SAY_SUMMON_TORGYN, 404.310, -314.761, 104.756, 413.992, -314.703, 107.995, 3.157}
};

struct boss_ymironAI : public ScriptedAI
{
    boss_ymironAI(Creature *c) : ScriptedAI(c), summons(c)
    {
        pInstance = c->GetInstanceData();
        srand(time(NULL));
        for (int i = 0; i < 4; ++i)
            m_uiActiveOrder[i] = i;
        for (int i = 0; i < 3; ++i)
        {
            int r = i + (rand()%(4-i));
            int temp = m_uiActiveOrder[i];
            m_uiActiveOrder[i] = m_uiActiveOrder[r];
            m_uiActiveOrder[r] = temp;
        }
    }

    bool m_bIsWalking;
    bool m_bIsPause;
    bool m_bIsActiveWithBJORN;
    bool m_bIsActiveWithHALDOR;
    bool m_bIsActiveWithRANULF;
    bool m_bIsActiveWithTORGYN;
    bool m_bAchievement;

    uint8 m_uiActiveOrder[4];
    uint8 m_uiActivedNumber;

    uint32 m_uiFetidRot_Timer;
    uint32 m_uiBane_Timer;
    uint32 m_uiDarkSlash_Timer;
    uint32 m_uiAncestors_Vengeance_Timer;

    uint32 m_uiAbility_BJORN_Timer;
    uint32 m_uiAbility_HALDOR_Timer;
    uint32 m_uiAbility_RANULF_Timer;
    uint32 m_uiAbility_TORGYN_Timer;

    uint32 m_uiPause_Timer;
    uint32 m_uiHealthAmountModifier;
    uint32 m_uiHealthAmountMultipler;

    uint64 m_uiActivedCreatureGUID;
    uint64 m_uiOrbGUID;

    ScriptedInstance *pInstance;
    SummonList summons;

    void Reset()
    {
        m_bIsPause = false;
        m_bIsActiveWithBJORN = false;
        m_bIsActiveWithHALDOR = false;
        m_bIsActiveWithRANULF = false;
        m_bIsActiveWithTORGYN = false;

        m_uiFetidRot_Timer            = urand(8*IN_MILISECONDS,13*IN_MILISECONDS);
        m_uiBane_Timer                = urand(18*IN_MILISECONDS,23*IN_MILISECONDS);
        m_uiDarkSlash_Timer           = urand(28*IN_MILISECONDS,33*IN_MILISECONDS);
        m_uiAncestors_Vengeance_Timer = DUNGEON_MODE(60*IN_MILISECONDS,45*IN_MILISECONDS);
        m_uiPause_Timer               = 0;

        m_uiAbility_BJORN_Timer  = 0;
        m_uiAbility_HALDOR_Timer = 0;
        m_uiAbility_RANULF_Timer = 0;
        m_uiAbility_TORGYN_Timer = 0;

        m_uiActivedNumber        = 0;
        m_uiHealthAmountModifier = 1;
        m_uiHealthAmountMultipler = DUNGEON_MODE(33,20);

        DespawnBoatGhosts(m_uiActivedCreatureGUID);
        DespawnBoatGhosts(m_uiOrbGUID);

        summons.DespawnAll();

        if (pInstance)
            pInstance->SetData(DATA_KING_YMIRON_EVENT, NOT_STARTED);
    }

    void EnterCombat(Unit* who)
    {
        DoScriptText(SAY_AGGRO, me);

        if (pInstance)
            pInstance->SetData(DATA_KING_YMIRON_EVENT, IN_PROGRESS);
    }

    void JustSummoned(Creature *summon)
    {
        summons.Summon(summon);
    }

    void UpdateAI(const uint32 diff)
    {
        if (m_bIsWalking)
        {
            if (m_uiPause_Timer <= diff)
            {
                DoScriptText(ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].say, me);
                DoCast(me, SPELL_CHANNEL_YMIRON_TO_SPIRIT); // should be on spirit
                if (Creature* pTemp = me->SummonCreature(ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].npc, ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].SpawnX, ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].SpawnY, ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].SpawnZ, ActiveBot[m_uiActiveOrder[m_uiActivedNumber]].SpawnO, TEMPSUMMON_CORPSE_DESPAWN, 0))
                {
                    m_uiActivedCreatureGUID = pTemp->GetGUID();
                    pTemp->CastSpell(me, SPELL_CHANNEL_SPIRIT_TO_YMIRON, true);
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    pTemp->AddUnitMovementFlag(MOVEMENTFLAG_LEVITATING);
                    switch(m_uiActiveOrder[m_uiActivedNumber])
                    {
                        case 0: m_bIsActiveWithBJORN  = true; break;
                        case 1: m_bIsActiveWithHALDOR = true; break;
                        case 2: m_bIsActiveWithRANULF = true; break;
                        case 3: m_bIsActiveWithTORGYN = true; break;
                    }
                }

                m_bIsPause = true;
                m_bIsWalking = false;
                m_uiPause_Timer = 3*IN_MILISECONDS;
            } else m_uiPause_Timer -= diff;
            return;
        }
        else if (m_bIsPause)
        {
            if (m_uiPause_Timer <= diff)
            {
                m_uiAbility_BJORN_Timer = 5*IN_MILISECONDS;
                m_uiAbility_HALDOR_Timer = 5*IN_MILISECONDS;
                m_uiAbility_RANULF_Timer = 5*IN_MILISECONDS;
                m_uiAbility_TORGYN_Timer = 5*IN_MILISECONDS;

                m_bIsPause = false;
                m_uiPause_Timer = 0;
            } else m_uiPause_Timer -= diff;
            return;
        }

        //Return since we have no target
         if (!UpdateVictim())
             return;

        if (!m_bIsPause)
        {
            // Normal spells ------------------------------------------------------------------------
            if (m_uiBane_Timer <= diff)
            {
                DoCast(me, DUNGEON_MODE(SPELL_BANE, H_SPELL_BANE));
                m_uiBane_Timer = urand(20*IN_MILISECONDS,25*IN_MILISECONDS);
            } else m_uiBane_Timer -= diff;

            if (m_uiFetidRot_Timer <= diff)
            {
                if (Unit *pTarget = SelectTarget(SELECT_TARGET_RANDOM, 0, 200, true))
                    DoCast(pTarget, DUNGEON_MODE(SPELL_FETID_ROT, H_SPELL_FETID_ROT));
                m_uiFetidRot_Timer = urand(10*IN_MILISECONDS,15*IN_MILISECONDS);
            } else m_uiFetidRot_Timer -= diff;

            if (m_uiDarkSlash_Timer <= diff)
            {
                DoCast(me->getVictim(), SPELL_DARK_SLASH);
                //workaround
                me->getVictim()->SetHealth((me->getVictim()->GetHealth()*0.5));
                m_uiDarkSlash_Timer = urand(30*IN_MILISECONDS,35*IN_MILISECONDS);
            } else m_uiDarkSlash_Timer -= diff;

            if (m_uiAncestors_Vengeance_Timer <= diff)
            {
                DoCast(me, SPELL_ANCESTORS_VENGEANCE);
                m_uiAncestors_Vengeance_Timer = DUNGEON_MODE(urand(60*IN_MILISECONDS,65*IN_MILISECONDS),urand(45*IN_MILISECONDS,50*IN_MILISECONDS));
            } else m_uiAncestors_Vengeance_Timer -= diff;

            // Abilities ------------------------------------------------------------------------------
            if (m_bIsActiveWithBJORN && m_uiAbility_BJORN_Timer <= diff)
            {
                //DoCast(me, SPELL_SUMMON_SPIRIT_FOUNT); // works fine, but using summon has better control
                if (Creature* pTemp = me->SummonCreature(CREATURE_SPIRIT_FOUNT, 385+rand()%10, -330+rand()%10, 104.756, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 180*IN_MILISECONDS))
                {
                    pTemp->SetSpeed(MOVE_RUN, 0.4f);
                    pTemp->CastSpell(pTemp, DUNGEON_MODE(SPELL_SPIRIT_FOUNT, H_SPELL_SPIRIT_FOUNT), true);
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pTemp->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    pTemp->SetDisplayId(11686);
                    pTemp->GetMotionMaster()->MoveChase(me->getVictim());
                    m_uiOrbGUID = pTemp->GetGUID();
                }
                m_bIsActiveWithBJORN = false; // only one orb
            } else m_uiAbility_BJORN_Timer -= diff;

            if (m_bIsActiveWithHALDOR && m_uiAbility_HALDOR_Timer <= diff)
            {
                DoCast(me->getVictim(), DUNGEON_MODE(SPELL_SPIRIT_STRIKE, H_SPELL_SPIRIT_STRIKE));
                m_uiAbility_HALDOR_Timer = 5*IN_MILISECONDS; // overtime
            } else m_uiAbility_HALDOR_Timer -= diff;

            if (m_bIsActiveWithRANULF && m_uiAbility_RANULF_Timer <= diff)
            {
                DoCast(me, DUNGEON_MODE(SPELL_SPIRIT_BURST, H_SPELL_SPIRIT_BURST));
                m_uiAbility_RANULF_Timer = 10*IN_MILISECONDS; // overtime
            } else m_uiAbility_RANULF_Timer -= diff;

            if (m_bIsActiveWithTORGYN && m_uiAbility_TORGYN_Timer <= diff)
            {
                float x,y,z;
                x = me->GetPositionX()-5;
                y = me->GetPositionY()-5;
                z = me->GetPositionZ();
                for (uint8 i = 0; i < 4; ++i)
                {
                    //DoCast(me, SPELL_SUMMON_AVENGING_SPIRIT); // works fine, but using summon has better control
                    if (Creature* pTemp = me->SummonCreature(CREATURE_AVENGING_SPIRIT, x+rand()%10, y+rand()%10, z, 0, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30*IN_MILISECONDS))
                    {
                        if (Unit* pTarget = SelectUnit(SELECT_TARGET_RANDOM, 0))
                        {
                            pTemp->AddThreat(pTarget, 0.0f);
                            pTemp->AI()->AttackStart(pTarget);
                        }
                    }
                }
                m_uiAbility_TORGYN_Timer = 15*IN_MILISECONDS; // overtime
            } else m_uiAbility_TORGYN_Timer -= diff;
            DoMeleeAttackIfReady();
            // Health check -----------------------------------------------------------------------------
            if ((me->GetHealth()*100 / me->GetMaxHealth()) < (100-(m_uiHealthAmountMultipler * m_uiHealthAmountModifier)))
            {
               uint8 m_uiOrder = m_uiHealthAmountModifier - 1;
               ++m_uiHealthAmountModifier;

                me->InterruptNonMeleeSpells(true);
                DoCast(me, SPELL_SCREAMS_OF_THE_DEAD);
                me->GetMotionMaster()->Clear();
                me->StopMoving();
                me->AttackStop();
                me->GetMotionMaster()->MovePoint(0, ActiveBot[m_uiActiveOrder[m_uiOrder]].MoveX, ActiveBot[m_uiActiveOrder[m_uiOrder]].MoveY, ActiveBot[m_uiActiveOrder[m_uiOrder]].MoveZ);

                DespawnBoatGhosts(m_uiActivedCreatureGUID);
                DespawnBoatGhosts(m_uiOrbGUID);

                m_bIsActiveWithBJORN  = false;
                m_bIsActiveWithHALDOR = false;
                m_bIsActiveWithRANULF = false;
                m_bIsActiveWithTORGYN = false;
                m_bAchievement = true;

                m_uiBane_Timer                += 8*IN_MILISECONDS;
                m_uiFetidRot_Timer            += 8*IN_MILISECONDS;
                m_uiDarkSlash_Timer           += 8*IN_MILISECONDS;
                m_uiAncestors_Vengeance_Timer += 8*IN_MILISECONDS;

                m_uiActivedNumber = m_uiOrder;
                m_bIsWalking = true;
                m_uiPause_Timer = 3*IN_MILISECONDS;
                return;
            }
        }
    }

    void JustDied(Unit* killer)
    {
        DoScriptText(SAY_DEATH, me);

        DespawnBoatGhosts(m_uiActivedCreatureGUID);
        DespawnBoatGhosts(m_uiOrbGUID);

        if (pInstance)
        {
            if (IsHeroic() && m_bAchievement)
                pInstance->DoCompleteAchievement(ACHIEV_KINGS_BANE);
            pInstance->SetData(DATA_KING_YMIRON_EVENT, DONE);
        }
    }

    void KilledUnit(Unit *victim)
    {
        DoScriptText(RAND(SAY_SLAY_1,SAY_SLAY_2,SAY_SLAY_3,SAY_SLAY_4), me);
    }

    void SpellHitTarget(Unit *pTarget, const SpellEntry *spell) 
    {
        if ( IsHeroic() && (spell->Id == SPELL_DARK_SLASH))
            m_bAchievement = false;
    }

    void DespawnBoatGhosts(uint64& m_uiCreatureGUID)
    {
        if (m_uiCreatureGUID)
            if (Creature* pTemp = (Creature*)Unit::GetUnit(*me, m_uiCreatureGUID))
                pTemp->DisappearAndDie();

        m_uiCreatureGUID = 0;
    }
};

CreatureAI* GetAI_boss_ymiron(Creature* pCreature)
{
    return new boss_ymironAI(pCreature);
}

void AddSC_boss_ymiron()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "boss_ymiron";
    newscript->GetAI = &GetAI_boss_ymiron;
    newscript->RegisterSelf();
}
