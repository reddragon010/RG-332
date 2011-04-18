/* Copyright (C) 2008-2010 Trinity <http://www.trinitycore.org/>
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
SDName: Sholazar_Basin
SD%Complete: 100
SDComment: Quest support: 12570, 12573, 12621.
SDCategory: Sholazar_Basin
EndScriptData */

/* ContentData
npc_injured_rainspeaker_oracle
npc_vekjik
avatar_of_freya
EndContentData */

#include "ScriptedPch.h"
#include "ScriptedEscortAI.h"

/*######
## npc_injured_rainspeaker_oracle
######*/

#define GOSSIP_ITEM1 "I am ready to travel to your village now."

enum eRainspeaker
{
    SAY_START_IRO                       = -1571000,
    SAY_QUEST_ACCEPT_IRO                = -1571001,
    SAY_END_IRO                         = -1571002,

    QUEST_FORTUNATE_MISUNDERSTANDINGS   = 12570,
    FACTION_ESCORTEE_A                  = 774,
    FACTION_ESCORTEE_H                  = 775
};

struct npc_injured_rainspeaker_oracleAI : public npc_escortAI
{
    npc_injured_rainspeaker_oracleAI(Creature* c) : npc_escortAI(c) { c_guid = c->GetGUID(); }

    uint64 c_guid;

    void Reset()
    {
        me->RestoreFaction();
        // if we will have other way to assign this to only one npc remove this part
        if (GUID_LOPART(me->GetGUID()) != 101030)
        {
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_QUESTGIVER);
            me->RemoveFlag(UNIT_NPC_FLAGS, UNIT_NPC_FLAG_GOSSIP);
        }
    }

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        switch(i)
        {
        case 1: SetRun(); break;
        case 10:
        case 11:
        case 12:
        case 13:
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
            m_creature->RemoveUnitMovementFlag(MOVEMENTFLAG_SWIMMING);
            m_creature->RemoveUnitMovementFlag(MOVEMENTFLAG_JUMPING);
            m_creature->SetSpeed(MOVE_SWIM, 0.85f, true);
            m_creature->AddUnitMovementFlag(MOVEMENTFLAG_SWIMMING | MOVEMENTFLAG_LEVITATING);
            break;
        case 19:
            m_creature->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
            break;
        case 28:
            if (Player* pPlayer = GetPlayerForEscort())
                pPlayer->GroupEventHappens(QUEST_FORTUNATE_MISUNDERSTANDINGS, m_creature);
          //  me->RestoreFaction();
            DoScriptText(SAY_END_IRO,m_creature);
            SetRun(false);
            break;
        }
    }

    void JustDied(Unit* killer)
    {
        if (!HasEscortState(STATE_ESCORT_ESCORTING))
            return;

        if (Player* pPlayer = GetPlayerForEscort())
        {
          if (pPlayer->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTANDINGS) != QUEST_STATUS_COMPLETE)
            pPlayer->FailQuest(QUEST_FORTUNATE_MISUNDERSTANDINGS);
        }
    }
};

bool GossipHello_npc_injured_rainspeaker_oracle(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_FORTUNATE_MISUNDERSTANDINGS) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());

    return true;
}

bool GossipSelect_npc_injured_rainspeaker_oracle(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        CAST_AI(npc_escortAI, (pCreature->AI()))->Start(true, false, pPlayer->GetGUID());
        CAST_AI(npc_escortAI, (pCreature->AI()))->SetMaxPlayerDistance(35.0f);
        pCreature->SetUnitMovementFlags(MOVEMENTFLAG_JUMPING);
        DoScriptText(SAY_START_IRO, pCreature);

        switch (pPlayer->GetTeam()){
        case ALLIANCE:
            pCreature->setFaction(FACTION_ESCORTEE_A);
            break;
        case HORDE:
            pCreature->setFaction(FACTION_ESCORTEE_H);
            break;
        }
    }
    return true;
}

bool QuestAccept_npc_injured_rainspeaker_oracle(Player* pPlayer, Creature* pCreature, Quest const *_Quest)
{
    DoScriptText(SAY_QUEST_ACCEPT_IRO, pCreature);
    return false;
}

CreatureAI* GetAI_npc_injured_rainspeaker_oracle(Creature* pCreature)
{
    return new npc_injured_rainspeaker_oracleAI(pCreature);
}

/*######
## npc_vekjik
######*/

#define GOSSIP_VEKJIK_ITEM1 "Shaman Vekjik, I have spoken with the big-tongues and they desire peace. I have brought this offering on their behalf."
#define GOSSIP_VEKJIK_ITEM2 "No no... I had no intentions of betraying your people. I was only defending myself. it was all a misunderstanding."

enum eVekjik
{
    GOSSIP_TEXTID_VEKJIK1       = 13137,
    GOSSIP_TEXTID_VEKJIK2       = 13138,

    SAY_TEXTID_VEKJIK1          = -1000208,

    SPELL_FREANZYHEARTS_FURY    = 51469,

    QUEST_MAKING_PEACE          = 12573
};

bool GossipHello_npc_vekjik(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_MAKING_PEACE) == QUEST_STATUS_INCOMPLETE)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK1, pCreature->GetGUID());
        return true;
    }

    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_vekjik(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch(uiAction)
    {
        case GOSSIP_ACTION_INFO_DEF+1:
            pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_VEKJIK_ITEM2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
            pPlayer->SEND_GOSSIP_MENU(GOSSIP_TEXTID_VEKJIK2, pCreature->GetGUID());
            break;
        case GOSSIP_ACTION_INFO_DEF+2:
            pPlayer->CLOSE_GOSSIP_MENU();
            DoScriptText(SAY_TEXTID_VEKJIK1, pCreature, pPlayer);
            pPlayer->AreaExploredOrEventHappens(QUEST_MAKING_PEACE);
            pCreature->CastSpell(pPlayer, SPELL_FREANZYHEARTS_FURY, false);
            break;
    }

    return true;
}

/*######
## avatar_of_freya
######*/

#define GOSSIP_ITEM_AOF1 "I want to stop the Scourge as much as you do. How can I help?"
#define GOSSIP_ITEM_AOF2 "You can trust me. I am no friend of the Lich King."
#define GOSSIP_ITEM_AOF3 "I will not fail."

enum eFreya
{
    QUEST_FREYA_PACT         = 12621,

    SPELL_FREYA_CONVERSATION = 52045,

    GOSSIP_TEXTID_AVATAR1    = 13303,
    GOSSIP_TEXTID_AVATAR2    = 13304,
    GOSSIP_TEXTID_AVATAR3    = 13305
};

bool GossipHello_npc_avatar_of_freya(Player* pPlayer, Creature* pCreature)
{
    if (pCreature->isQuestGiver())
        pPlayer->PrepareQuestMenu(pCreature->GetGUID());

    if (pPlayer->GetQuestStatus(QUEST_FREYA_PACT) == QUEST_STATUS_INCOMPLETE)
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);

    pPlayer->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR1, pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_avatar_of_freya(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    switch (uiAction)
    {
    case GOSSIP_ACTION_INFO_DEF+1:
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF2, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);
        pPlayer->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR2, pCreature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF+2:
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_ITEM_AOF3, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+3);
        pPlayer->PlayerTalkClass->SendGossipMenu(GOSSIP_TEXTID_AVATAR3, pCreature->GetGUID());
        break;
    case GOSSIP_ACTION_INFO_DEF+3:
        pPlayer->CastSpell(pPlayer, SPELL_FREYA_CONVERSATION, true);
	pPlayer->CompleteQuest(QUEST_FREYA_PACT);
        pPlayer->CLOSE_GOSSIP_MENU();
        break;
    }
    return true;
}

/*######
## npc_geezle
######*/

struct npc_bushwhackerAI : public ScriptedAI
{
    npc_bushwhackerAI(Creature* pCreature) : ScriptedAI(pCreature)
    {
        MoveToSummoner();
    }

    void MoveToSummoner()
    {
        if (m_creature->isSummon())
            if (Unit* pSummoner = CAST_SUM(m_creature)->GetSummoner())
                if (pSummoner)
                    m_creature->GetMotionMaster()->MovePoint(0,pSummoner->GetPositionX(),pSummoner->GetPositionY(),pSummoner->GetPositionZ());
    }

    void UpdateAI(const uint32 uiDiff)
    {
        if (!UpdateVictim())
            return;

        DoMeleeAttackIfReady();
    }
};

CreatureAI* GetAI_npc_bushwhacker(Creature* pCreature)
{
    return new npc_bushwhackerAI(pCreature);
}



/*######
## npc_tipsy
######*/

#define QUEST_STILL_AT_IT                 12644
#define GOSSIP_TIPSY_ITEM1                "I'm ready to start the distillation, uh, Tipsy."
#define DISTILLATION_BEGIN                 -1999980
#define SAY_PAPAYA                         -1999981
#define SAY_BANANA                         -1999982
#define SAY_ORANGE                         -1999983
#define SAY_BRAZIER                        -1999984
#define SAY_VALVE                          -1999985
#define SAY_END1                           -1999986
#define SAY_END2                           -1999987
#define SAY_END3                           -1999988
#define SAY_QEND                           -1999989
#define SAY_QFAIL                          -1999990

bool phase;
uint32 Phase_Timer;
uint32 Item_Timer;
int i ;
bool papayas;
bool bananas;
bool oranges;
bool brazier;
bool valve;
bool papSay;
bool banSay;
bool oraSay;
bool braSay;
bool valSay;
uint64 someplayer;
int still_count;

bool GossipHello_npc_tipsy(Player* pPlayer, Creature* pCreature)
{

    if (pPlayer->GetQuestStatus(QUEST_STILL_AT_IT) == QUEST_STATUS_INCOMPLETE && phase == false)
    {
        pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, GOSSIP_TIPSY_ITEM1, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+1);
        pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
        return true;
    }
    pPlayer->SEND_GOSSIP_MENU(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_npc_tipsy(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if (uiAction == GOSSIP_ACTION_INFO_DEF+1)
    {
        pPlayer->CLOSE_GOSSIP_MENU();
        someplayer = pPlayer->GetGUID();
        phase = true;
        still_count = 0;
        Phase_Timer = 5000;
        Item_Timer = 10000;
        srand( (unsigned)time( NULL ) );
        i = rand() % 4;
        DoScriptText(DISTILLATION_BEGIN, pCreature);
    }

    return true;
}

struct npc_tipsyAI : public ScriptedAI
{
 npc_tipsyAI(Creature *c) : ScriptedAI(c) {}
 void UpdateAI(const uint32 uiDiff) {
 Unit* target = Unit::GetUnit((*m_creature), someplayer);
       if (still_count == 9){
          GameObject* JunglePunch = m_creature->SummonGameObject(190643, m_creature->GetPositionX() + 2, m_creature->GetPositionY(), m_creature->GetPositionZ(), m_creature->GetOrientation(), 0, 0, 0, 0, 0);
          still_count = 0;
          DoScriptText(SAY_QEND, m_creature);
          phase = false;
       }
       
       if (phase == true) {
          if (Phase_Timer < uiDiff)
          {
             switch(i){
             
                       case 0:
                            if (papSay == false) {
                               DoScriptText(SAY_PAPAYA, m_creature);
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                               Item_Timer = 10000;
                               papSay = true;
                            }
                            
                            if (Item_Timer < uiDiff && papayas == false) {
                               DoScriptText(SAY_QFAIL, m_creature);
                               CAST_PLR(target)->FailQuest(QUEST_STILL_AT_IT);
                               still_count = 0;
                               phase = false;
                               papSay = false;
                               break;
                            } else Item_Timer -= uiDiff;
                            
                            if (papayas == true) {
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                               DoScriptText(SAY_END1, m_creature);
                               papSay = false;
                               papayas = false;
                               srand( (unsigned)time( NULL ) );
                               i = rand() % 4;
                               still_count++;
                               break;
                            }
                            break;
                       case 1:
                            if (banSay == false) {
                               DoScriptText(SAY_BANANA, m_creature);
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                               Item_Timer = 10000;
                               banSay = true;
                            }
                            
                            if (Item_Timer < uiDiff && bananas == false) {
                               DoScriptText(SAY_QFAIL, m_creature);
                               CAST_PLR(target)->FailQuest(QUEST_STILL_AT_IT);
                               still_count = 0;
                               phase = false;
                               banSay = false;
                               break;
                            } else Item_Timer -= uiDiff;
                            
                            if (bananas == true) {
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                               DoScriptText(SAY_END1, m_creature);
                               banSay = false;
                               bananas = false;
                               srand( (unsigned)time( NULL ) );
                               i = rand() % 4;
                               still_count++;
                               break;
                            }
                            break;
                       case 2:
                            if (oraSay == false) {
                               DoScriptText(SAY_ORANGE, m_creature);
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                               Item_Timer = 10000;
                               oraSay = true;
                            }
                            
                            if (Item_Timer < uiDiff && oranges == false) {
                               DoScriptText(SAY_QFAIL, m_creature);
                               CAST_PLR(target)->FailQuest(QUEST_STILL_AT_IT);
                               still_count = 0;
                               phase = false;
                               oraSay = false;
                               break;
                            } else Item_Timer -= uiDiff;
                            
                            if (oranges == true) {
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                               DoScriptText(SAY_END1, m_creature);
                               oraSay = false;
                               oranges = false;
                               srand( (unsigned)time( NULL ) );
                               i = rand() % 4;
                               still_count++;
                               break;
                            }
                            break;
                       case 3:
                            if (braSay == false) {
                               DoScriptText(SAY_BRAZIER, m_creature);
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                               Item_Timer = 10000;
                               braSay = true;
                            }
                            
                            if (Item_Timer < uiDiff && brazier == false) {
                               DoScriptText(SAY_QFAIL, m_creature);
                               CAST_PLR(target)->FailQuest(QUEST_STILL_AT_IT);
                               still_count = 0;
                               phase = false;
                               braSay = false;
                               break;
                            } else Item_Timer -= uiDiff;
                            
                            if (brazier == true) {
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                               DoScriptText(SAY_END2, m_creature);
                               braSay = false;
                               brazier = false;
                               srand( (unsigned)time( NULL ) );
                               i = rand() % 4;
                               still_count++;
                               break;
                            }
                            break;
                       case 4:
                            if (valSay == false) {
                               DoScriptText(SAY_VALVE, m_creature);
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_POINT);
                               Item_Timer = 10000;
                               valSay = true;
                            }
                            
                            if (Item_Timer < uiDiff && valve == false) {
                               DoScriptText(SAY_QFAIL, m_creature);
                               CAST_PLR(target)->FailQuest(QUEST_STILL_AT_IT);
                               still_count = 0;
                               phase = false;
                               valSay = false;
                               break;
                            } else Item_Timer -= uiDiff;
                            
                            if (valve == true) {
                               m_creature->HandleEmoteCommand(EMOTE_ONESHOT_CHEER);
                               DoScriptText(SAY_END3, m_creature);
                               valSay = false;
                               valve = false;
                               srand( (unsigned)time( NULL ) );
                               i = rand() % 4;
                               still_count++;
                               break;
                            }
                            break;
             }
          }
          else Phase_Timer -= uiDiff;
       }
 }
};

bool GOHello_go_barrel_of_papayas(Player* pPlayer, GameObject* pGo)
{
    if (phase == true)
       papayas = true;
    return true;
}

bool GOHello_go_barrel_of_bananas(Player* pPlayer, GameObject* pGo)
{
    if (phase == true)
       bananas = true;
    return true;
}

bool GOHello_go_barrel_of_oranges(Player* pPlayer, GameObject* pGo)
{
    if (phase == true)
       oranges = true;
    return true;
}

bool GOHello_go_brazier(Player* pPlayer, GameObject* pGo)
{
    if (phase == true)
       brazier = true;
    return true;
}

bool GOHello_go_pressure_valve(Player* pPlayer, GameObject* pGo)
{
    if (phase == true)
       valve = true;
    return true;
}

CreatureAI* GetAI_npc_tipsy(Creature* pCreature)
{
    return new npc_tipsyAI (pCreature);
}

/*######
## npc_engineer_helice
######*/

enum eEngineerHelice 
{
    QUEST_ENGINEERING_A_DISASTER  = 12688 
};

struct npc_engineer_helice_elfAI : public npc_escortAI 
{
    npc_engineer_helice_elfAI(Creature *c) : npc_escortAI(c) {}

    void WaypointReached(uint32 i)
    {
        Player* pPlayer = GetPlayerForEscort();

        if (!pPlayer)
            return;

        if(i == 28)
		{
            pPlayer->GroupEventHappens(QUEST_ENGINEERING_A_DISASTER,m_creature);
        }
    }

    void Reset() { } 

    /*void EnterCombat(Unit* who) 
    {
        if (HasEscortState(STATE_ESCORT_ESCORTING))
            DoScriptText(....., m_creature);
    }*/

    void JustSummoned(Creature* summoned) 
    {
        summoned->AI()->AttackStart(m_creature);
    }
};

CreatureAI* GetAI_npc_engineer_helice(Creature* pCreature)
{
    return new npc_engineer_helice_elfAI(pCreature); 
}

bool QuestAccept_npc_engineer_helice(Player* pPlayer, Creature* pCreature, Quest const* quest)
{
    if (quest->GetQuestId() == QUEST_ENGINEERING_A_DISASTER)
    {
        if (npc_escortAI* pEscortAI = CAST_AI(npc_engineer_helice_elfAI, pCreature->AI()))
            pEscortAI->Start(true, false, pPlayer->GetGUID());

        
        pCreature->setFaction(775);
    }
	     
	return true;
 }

/*######
## QUEST 12645: The Taste Test
######*/

enum THE_TASTE_TEST 
{
	HEMET_TASTE_TEST = 27986,
	HADRIUS_TASTE_TEST = 28047,
	TAMARA_TASTE_TEST = 28568
};

/*######
## npc_tamara_wobbleAI
######*/

struct npc_tamara_wobbleAI : public ScriptedAI 
{
    npc_tamara_wobbleAI(Creature *c) : ScriptedAI(c) {}

	void SpellHit(Unit *caster, const SpellEntry *spell) {
		if (spell->Id == 51962) {
			caster->ToPlayer()->KilledMonsterCredit(TAMARA_TASTE_TEST,0);
		}
	}
};
CreatureAI* GetAI_npc_tamara_wobble(Creature* pCreature)
{
    return new npc_tamara_wobbleAI(pCreature); 
}

/*######
## npc_hadrius_harloweAI
######*/

struct npc_hadrius_harloweAI : public ScriptedAI 
{
    npc_hadrius_harloweAI(Creature *c) : ScriptedAI(c) {}

	void SpellHit(Unit *caster, const SpellEntry *spell) {
		if (spell->Id == 51962) {
			caster->ToPlayer()->KilledMonsterCredit(HADRIUS_TASTE_TEST,0);
		}
	}
};

CreatureAI* GetAI_npc_hadrius_harlowe(Creature* pCreature)
{
    return new npc_hadrius_harloweAI(pCreature); 
}

/*######
## npc_hemet_nesingwaryAI
######*/

struct npc_hemet_nesingwaryAI : public ScriptedAI 
{
    npc_hemet_nesingwaryAI(Creature *c) : ScriptedAI(c) {}

	void SpellHit(Unit *caster, const SpellEntry *spell) {
		if (spell->Id == 51962) {
			caster->ToPlayer()->KilledMonsterCredit(HEMET_TASTE_TEST,0);
		}
	}
};

CreatureAI* GetAI_npc_hemet_nesingwary(Creature* pCreature)
{
    return new npc_hemet_nesingwaryAI(pCreature); 
}

void AddSC_sholazar_basin()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "npc_injured_rainspeaker_oracle";
    newscript->GetAI = &GetAI_npc_injured_rainspeaker_oracle;
    newscript->pGossipHello = &GossipHello_npc_injured_rainspeaker_oracle;
    newscript->pGossipSelect = &GossipSelect_npc_injured_rainspeaker_oracle;
    newscript->pQuestAccept = &QuestAccept_npc_injured_rainspeaker_oracle;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_vekjik";
    newscript->pGossipHello = &GossipHello_npc_vekjik;
    newscript->pGossipSelect = &GossipSelect_npc_vekjik;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_avatar_of_freya";
    newscript->pGossipHello = &GossipHello_npc_avatar_of_freya;
    newscript->pGossipSelect = &GossipSelect_npc_avatar_of_freya;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_bushwhacker";
    newscript->GetAI = &GetAI_npc_bushwhacker;
    newscript->RegisterSelf();
	
	newscript = new Script;
    newscript->Name = "npc_tipsy";
	newscript->pGossipHello = &GossipHello_npc_tipsy;
	newscript->pGossipSelect = &GossipSelect_npc_tipsy;
    newscript->GetAI = &GetAI_npc_tipsy;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "go_barrel_of_papayas";
	newscript->pGOHello = &GOHello_go_barrel_of_papayas;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "go_barrel_of_bananas";
	newscript->pGOHello = &GOHello_go_barrel_of_bananas;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "go_barrel_of_oranges";
	newscript->pGOHello = &GOHello_go_barrel_of_oranges;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "go_brazier";
	newscript->pGOHello = &GOHello_go_brazier;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "go_pressure_valve";
	newscript->pGOHello = &GOHello_go_pressure_valve;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_engineer_helice";
    newscript->GetAI = &GetAI_npc_engineer_helice;
    newscript->pQuestAccept = &QuestAccept_npc_engineer_helice;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "npc_tamara_wobble";
    newscript->GetAI = &GetAI_npc_tamara_wobble;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_hadrius_harlowe";
    newscript->GetAI = &GetAI_npc_hadrius_harlowe;
    newscript->RegisterSelf();

	newscript = new Script;
    newscript->Name = "npc_hemet_nesingwary";
    newscript->GetAI = &GetAI_npc_hemet_nesingwary;
    newscript->RegisterSelf();
}


