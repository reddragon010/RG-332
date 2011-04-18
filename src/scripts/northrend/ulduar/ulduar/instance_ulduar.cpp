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


const DoorData doorData[] =
{
    {194416,    BOSS_LEVIATHAN, DOOR_TYPE_ROOM,     0},
    {194905,    BOSS_LEVIATHAN, DOOR_TYPE_PASSAGE,  0},
    {194631,    BOSS_XT002,     DOOR_TYPE_ROOM,     0},
    {194553,    BOSS_ASSEMBLY,  DOOR_TYPE_PASSAGE,  0},
    {194554,    BOSS_ASSEMBLY,  DOOR_TYPE_ROOM,     0},
    {194556,    BOSS_ASSEMBLY,  DOOR_TYPE_PASSAGE,  0},
    {194553,    BOSS_KOLOGARN,  DOOR_TYPE_ROOM,     0},
    {194441,    BOSS_HODIR,     DOOR_TYPE_PASSAGE,  0},
    {194634,    BOSS_HODIR,     DOOR_TYPE_PASSAGE,  0},
    {194442,    BOSS_HODIR,     DOOR_TYPE_ROOM,     0},
    {194559,    BOSS_THORIM,    DOOR_TYPE_ROOM,     0},
    {0,         0,              DOOR_TYPE_ROOM,     0}, // EOF
};














enum eGameObjects
{
    GO_Leviathan_DOOR       = 194630,
//    GO_Kologarn_CHEST_HERO  = 195047,
//    GO_Kologarn_CHEST       = 195046,
    GO_Kologarn_BRIDGE      = 194232,

    GO_Hodir_CHEST_HERO     = 194308,
    GO_Hodir_CHEST          = 194307,
    GO_Runic_DOOR           = 194557,
    GO_Stone_DOOR           = 194558,
    GO_Thorim_CHEST_HERO    = 194315,


    GO_Thorim_CHEST         = 194314,




    GO_Freya_CHEST_HERO     = 194325,
    GO_Freya_CHEST          = 194324,
    GO_Universe_GLOBE       = 194148,
    GO_XT002_DOOR           = 194631,
    GO_LEVIATHAN_DOOR       = 194416,
    GO_LEVIATHAN_GATE       = 194630,
    GO_HARPOON              = 194565,
    GO_COUNCIL_DOOR         = 194554
};

struct instance_ulduar : public InstanceData
{
    instance_ulduar(Map* pMap) : InstanceData(pMap), KologarnChest(NULL), ThorimChest(NULL), HodirChest(NULL), FreyaChest(NULL) { Initialize(); };

    uint32 m_auiEncounter[MAX_ENCOUNTER];
    std::string str_data;
    uint32 m_auiConstrCount;
    std::string m_strInstData;
    uint8  flag;

    uint64 m_uiIronConstructGUIDs[16];
    uint64 m_uiLeviathanGUID;
    uint64 m_uiLeviathan_Trigger;
    uint64 m_uiIgnisGUID;
    uint64 m_uiRazorscaleGUID;
    uint64 m_uiXT002GUID;
    uint64 m_uiSteelbreaker;
    uint64 m_uiMolgeim;
    uint64 m_uiBrundir;
    uint64 m_uiKologarnGUID;
    uint64 m_uiKologarnLeftGUID;
    uint64 m_uiKologarnRightGUID;
    uint64 m_uiAuriayaGUID;
    uint64 m_uiMimironGUID;
    uint64 m_uiHodirGUID;
    uint64 m_uiThorimGUID;
    uint64 m_uiFreyaGUID;
    uint64 m_uiVezaxGUID;
    uint64 m_uiYoggSaronGUID;
    uint64 m_uiAlgalonGUID;    
    uint64 m_uiUniverseGlobeGUID;
    uint64 m_uiXT002Door;
    uint64 m_uiLeviathanGate;
    uint64 m_uiLeviathanDoor;
    uint64 m_uiAssemblyDoor;
    uint64 m_uiExpCommander;
    uint64 m_uiHarpoon[2];
    uint64 mole_machine[3];

    GameObject* KologarnChest, *ThorimChest, *HodirChest, *FreyaChest;

    void Initialize()
    {


        m_uiLeviathanGUID       = 0;
        m_uiIgnisGUID           = 0;
        m_uiRazorscaleGUID      = 0;
        m_uiXT002GUID           = 0;
        m_uiKologarnGUID        = 0;
        m_uiKologarnLeftGUID    = 0;
        m_uiKologarnRightGUID   = 0;
        m_uiAuriayaGUID         = 0;
        m_uiMimironGUID         = 0;
        m_uiHodirGUID           = 0;
        m_uiThorimGUID          = 0;
        m_uiFreyaGUID           = 0;
        m_uiVezaxGUID           = 0;
        m_uiYoggSaronGUID       = 0;
        m_uiAlgalonGUID         = 0;
        m_uiUniverseGlobeGUID   = 0;
        KologarnChest           = 0;
        ThorimChest             = 0;
        HodirChest              = 0;
        FreyaChest              = 0;
        m_auiConstrCount        = 0;
        m_uiXT002Door           = 0;
        m_uiLeviathanGate       = 0;
        m_uiExpCommander        = 0;
        m_uiAssemblyDoor        = 0;
        mole_machine[0]         = 0;

        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));
        memset(&m_uiIronConstructGUIDs, 0, sizeof(m_uiIronConstructGUIDs));
        memset(&m_uiLeviathanDoor, 0, sizeof(m_uiLeviathanDoor));
    }






















    bool IsEncounterInProgress() const
    {
        for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
        {
            if (m_auiEncounter[i] == IN_PROGRESS)
                return true;
        }


        return false;
    }

    void OnCreatureCreate(Creature* pCreature, bool add/*, uint32 data, ScriptedInstance* m_pInstance, Map *m_pMap*/)
    {
        std::stringstream ss;
        ss << "pCreature->GetEntry()== " << pCreature->GetEntry();
        outstring_log(ss.str().c_str());

        outstring_log("OnCreatureCreate");
        switch (pCreature->GetEntry())
        {
            case NPC_LEVIATHAN:
                outstring_log("NPC_LEVIATHAN");
                m_uiLeviathanGUID = pCreature->GetGUID();
                break;
            case NPC_LEVIATHAN_TRIGGER:
                m_uiLeviathan_Trigger = pCreature->GetGUID();
                break;
            case NPC_IGNIS:
                m_uiIgnisGUID = pCreature->GetGUID();
                break;
            case NPC_RAZORSCALE:
                m_uiRazorscaleGUID = pCreature->GetGUID();
                if (/*data == FAIL && */instance)
                {
                    if (Creature *commander = instance->GetCreature(GetData64(TYPE_COMMANDER)))
                        commander->SetVisibility(VISIBILITY_ON);
                }
                break;
            case NPC_XT002:
                m_uiXT002GUID = pCreature->GetGUID();
                break;
            case NPC_STEELBREAKER:
                m_uiSteelbreaker = pCreature->GetGUID();
                break;
            case NPC_MOLGEIM:
                m_uiMolgeim = pCreature->GetGUID();
                break;
            case NPC_BRUNDIR:
                m_uiBrundir = pCreature->GetGUID();
                break;
            case NPC_KOLOGARN:
                m_uiKologarnGUID = pCreature->GetGUID();
                break;
            case NPC_KOLOGARN_LEFT_ARM:
                m_uiKologarnLeftGUID = pCreature->GetGUID();
                break;
            case NPC_KOLOGARN_RIGHT_ARM:
                m_uiKologarnRightGUID = pCreature->GetGUID();
                break;
            case NPC_AURIAYA:
                m_uiAuriayaGUID = pCreature->GetGUID();
                break;
            case NPC_MIMIRON:
                m_uiMimironGUID = pCreature->GetGUID();
                break;
            case NPC_HODIR:
                m_uiHodirGUID = pCreature->GetGUID();
                break;
            case NPC_THORIM:
                m_uiThorimGUID = pCreature->GetGUID();
                break;
            case NPC_FREYA:
                m_uiFreyaGUID = pCreature->GetGUID();
                break;
            case NPC_VEZAX:
                m_uiVezaxGUID = pCreature->GetGUID();
                break;
            case NPC_YOGGSARON:
                m_uiYoggSaronGUID = pCreature->GetGUID();
                break;
            case NPC_ALGALON:
                m_uiAlgalonGUID = pCreature->GetGUID();
                break;
            case NPC_COMMANDER:
                m_uiExpCommander = pCreature->GetGUID();
                break;
            case NPC_IRON_CONSTRUCT:
                {
                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NON_ATTACKABLE);
                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_NOT_SELECTABLE);
                    pCreature->SetFlag(UNIT_FIELD_FLAGS, UNIT_FLAG_OOC_NOT_ATTACKABLE);
                    m_uiIronConstructGUIDs[m_auiConstrCount] = pCreature->GetGUID();
                    m_auiConstrCount++;
                    break;
                }
        }
    }

    void OnGameObjectCreate(GameObject* pGo, bool add)
    {

        switch (pGo->GetEntry())
        {

            case GO_Kologarn_CHEST_HERO: KologarnChest = add ? pGo : NULL; 
                pGo->SetRespawnTime(DAY * 7);
                break;
            case GO_Kologarn_CHEST: KologarnChest = add ? pGo : NULL; 
                pGo->SetRespawnTime(DAY * 7);
                break;
            case GO_Thorim_CHEST_HERO: ThorimChest = add ? pGo : NULL; break;

            case GO_Thorim_CHEST: ThorimChest = add ? pGo : NULL; break;
            case GO_Hodir_CHEST_HERO: HodirChest = add ? pGo : NULL; break;
            case GO_Hodir_CHEST: HodirChest = add ? pGo : NULL; break;
            case GO_Freya_CHEST_HERO: FreyaChest = add ? pGo : NULL; break;

            case GO_Freya_CHEST: FreyaChest = add ? pGo : NULL; break;
            case GO_Universe_GLOBE: m_uiUniverseGlobeGUID = pGo->GetGUID(); break;
            case 194631:
                 m_uiXT002Door = pGo->GetGUID();
                 HandleGameObject(NULL, true, pGo);
                 break;
            case 194416:
                 m_uiLeviathanDoor = pGo->GetGUID();
                 HandleGameObject(NULL, true, pGo);
                flag++;
                if (flag == 7)
                    flag =0;
                 break;
            case 194630:
                 m_uiLeviathanGate = pGo->GetGUID();
                 HandleGameObject(NULL, false, pGo);
                 break;
        }
    }


    void ProcessEvent(GameObject* pGo, uint32 uiEventId)
    {


        // Flame Leviathan's Tower Event triggers
        Creature* pFlameLeviathan = instance->GetCreature(NPC_LEVIATHAN);
        if (pFlameLeviathan && pFlameLeviathan->isAlive()) //No leviathan, no event triggering ;)
            switch(uiEventId)
            {
                case EVENT_TOWER_OF_STORM_DESTROYED:
                    pFlameLeviathan->AI()->DoAction(1);
                    break;
                case EVENT_TOWER_OF_FROST_DESTROYED:
                    pFlameLeviathan->AI()->DoAction(2);
                    break;
                case EVENT_TOWER_OF_FLAMES_DESTROYED:
                    pFlameLeviathan->AI()->DoAction(3);
                    break;
                case EVENT_TOWER_OF_NATURE_DESTROYED:
                    pFlameLeviathan->AI()->DoAction(4);
                    break;
    



            }
    }


    void SetData(uint32 type, uint32 data)
    {




















        switch (type)
        {
            case TYPE_LEVIATHAN:
            {
                if (data == IN_PROGRESS)
                {
                    HandleGameObject(m_uiLeviathanGate, true);
                    HandleGameObject(m_uiLeviathanDoor, false);              
                  //HandleGameObject(m_uiLeviathanDoor[2],false);
                  //HandleGameObject(m_uiLeviathanDoor[3],false);
                  //HandleGameObject(m_uiLeviathanDoor[4],false);
                  //HandleGameObject(m_uiLeviathanDoor[5],false);
                  //HandleGameObject(m_uiLeviathanDoor[6],false);
                }
                else
                {
                    HandleGameObject(m_uiLeviathanGate, false);
                    HandleGameObject(m_uiLeviathanDoor, true);
                }
                m_auiEncounter[0] = data;
                break;
                  //HandleGameObject(m_uiLeviathanDoor[5],true);
                  //HandleGameObject(m_uiLeviathanDoor[6],true);
            }
            case TYPE_IGNIS:
            {
                m_auiEncounter[1] = data;
                break;
            }
            case TYPE_RAZORSCALE:
            {
                if (data == IN_PROGRESS)
                {
                    HandleGameObject(mole_machine[0], true);
                    HandleGameObject(mole_machine[1], true);
                    HandleGameObject(mole_machine[2], true);
                }
                else
                {
                    HandleGameObject(mole_machine[0], false);
                    HandleGameObject(mole_machine[1], false);
                    HandleGameObject(mole_machine[2], false);
                }
                m_auiEncounter[2] = data;
                break;
            }
            case TYPE_XT002:
            {
                if (data == IN_PROGRESS) 
                    HandleGameObject(m_uiXT002Door, false);
                else 
                    HandleGameObject(m_uiXT002Door, true);
                m_auiEncounter[3] = data;
                break;
            }
            case TYPE_ASSEMBLY:
            {
                if (data == IN_PROGRESS) 
                    HandleGameObject(m_uiAssemblyDoor, true);
                else 
                    HandleGameObject(m_uiAssemblyDoor, false);
                m_auiEncounter[4] = data;
                break;
            }
            case TYPE_KOLOGARN:
            {
                if (data == DONE && KologarnChest)
                    KologarnChest->SetRespawnTime(KologarnChest->GetRespawnDelay());
                m_auiEncounter[5] = data;
                break;
            }
            case TYPE_AURIAYA:
            {
                m_auiEncounter[6] = data;
                break;
            }
            case TYPE_MIMIRON:
            {
                m_auiEncounter[7] = data;
                break;
            }
            case TYPE_HODIR:
            {
                if (data == DONE && HodirChest)
                    HodirChest->SetRespawnTime(HodirChest->GetRespawnDelay());
                m_auiEncounter[8] = data;
                break;
            }
            case TYPE_THORIM:
            {
                if (data == DONE && ThorimChest)
                    ThorimChest->SetRespawnTime(ThorimChest->GetRespawnDelay());
                m_auiEncounter[9] = data;
                break;
            }
            case TYPE_FREYA:
            {
                if (data == DONE && FreyaChest)
                    FreyaChest->SetRespawnTime(FreyaChest->GetRespawnDelay());
                m_auiEncounter[10] = data;
                break;
            }
            case TYPE_VEZAX:
            {
                m_auiEncounter[11] = data;
                break;
            }
            case TYPE_YOGGSARON:
            {
                m_auiEncounter[12] = data;
                break;
            }
            case TYPE_ALGALON:
                if (data == 2)
                {
                    m_auiEncounter[13] = data;
               //     pBoss->AI()->DoAction(10);
                    //if (GameObject* pGate = instance->GetGameObject(m_uiLeviathanGateGUID))
                    //    pGate->SetGoState(GO_STATE_ACTIVE_ALTERNATIVE);
                }
                break;
            case TYPE_COLOSSUS:
                m_auiEncounter[TYPE_COLOSSUS] = data;
                break;

        if (data == DONE)
        {
            OUT_SAVE_INST_DATA;

            std::ostringstream saveStream;
            saveStream << "U U " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " " << m_auiEncounter[2] << " "
                                 << m_auiEncounter[3] << " " << m_auiEncounter[4] << " " << m_auiEncounter[5] << " "
                                 << m_auiEncounter[6] << " " << m_auiEncounter[7] << " " << m_auiEncounter[8] << " "
                                 << m_auiEncounter[9] << " " << m_auiEncounter[10] << " " << m_auiEncounter[11] << " "
                                 << m_auiEncounter[12] << " " << m_auiEncounter[13];

            str_data = saveStream.str();

            SaveToDB();
            OUT_SAVE_INST_DATA_COMPLETE;
        }


    }
    }

    uint64 GetData64(uint32 data)
    {
        std::stringstream ss;
        switch (data)
        {
            case TYPE_LEVIATHAN:            
                outstring_log("TYPE_LEVIATHAN") ;
           //     std::stringstream ss;
                ss << "m_uiLeviathanGUID== " << m_uiLeviathanGUID;
                outstring_log(ss.str().c_str());
                    return m_uiLeviathanGUID;
            case TYPE_IGNIS:                return m_uiIgnisGUID;
            case DATA_LEVIATHAN_TRIGGER:
                return m_uiLeviathan_Trigger;






            case TYPE_KOLOGARN:             return m_uiKologarnGUID;
            case TYPE_AURIAYA:              return m_uiAuriayaGUID;
            case TYPE_MIMIRON:              return m_uiMimironGUID;
            case TYPE_HODIR:                return m_uiMimironGUID;
            case TYPE_THORIM:               return m_uiThorimGUID;
            case TYPE_FREYA:                return m_uiFreyaGUID;
            case TYPE_VEZAX:                return m_uiVezaxGUID;
            case TYPE_YOGGSARON:            return m_uiYoggSaronGUID;
            case TYPE_KOLOGARN_LEFT_ARM:
                return m_uiKologarnLeftGUID;
            case TYPE_KOLOGARN_RIGHT_ARM:
                return m_uiKologarnRightGUID;
            case DATA_EXP_COMMANDER:



                return m_uiExpCommander;

            // Assembly of Iron
            case DATA_STEELBREAKER:        // return m_auiAssemblyGUIDs[0];



                 return m_uiSteelbreaker;
            case DATA_BRUNDIR:              //return m_auiAssemblyGUIDs[2];

            return m_uiBrundir;













            case DATA_MOLGEIM:
                 return m_uiMolgeim; 
            case DATA_UNIVERSE_GLOBE:
                return m_uiUniverseGlobeGUID;
            case DATA_RANDOM_CONSTRUCT:







                {
                    uint32 idx = urand(0, 15);
                    if (m_uiIronConstructGUIDs[idx])
                        return m_uiIronConstructGUIDs[idx];
                    else
                        return NULL;
                }
        }
        return 0;
    }


    uint32 GetData(uint32 type)
    {
        switch (type)
        {
            case TYPE_LEVIATHAN:  return m_auiEncounter[0];












            case TYPE_IGNIS:      return m_auiEncounter[1];
            case TYPE_RAZORSCALE: return m_auiEncounter[2];
            case TYPE_XT002:      return m_auiEncounter[3];
            case TYPE_ASSEMBLY:   return m_auiEncounter[4];
            case TYPE_KOLOGARN:   return m_auiEncounter[5];
            case TYPE_AURIAYA:    return m_auiEncounter[6];
            case TYPE_MIMIRON:    return m_auiEncounter[7];
            case TYPE_HODIR:      return m_auiEncounter[8];
            case TYPE_THORIM:     return m_auiEncounter[9];
            case TYPE_FREYA:      return m_auiEncounter[10];
            case TYPE_VEZAX:      return m_auiEncounter[11];
            case TYPE_YOGGSARON:  return m_auiEncounter[12];
            case TYPE_ALGALON:    return m_auiEncounter[13];
            case TYPE_COLOSSUS:   return m_auiEncounter[14];
        }

        return 0;
    }


   std::string GetSaveData()
    {


        return str_data;
    }


    void Load(const char* in)
    {


        if (!in)
        {
            OUT_LOAD_INST_DATA_FAIL;
            return;
        }


        OUT_LOAD_INST_DATA(in);

        char dataHead1, dataHead2;
        std::istringstream loadStream(in);

        loadStream >> dataHead1 >> dataHead2 >> m_auiEncounter[0] >> m_auiEncounter[1]
                   >> m_auiEncounter[2] >> m_auiEncounter[3] >> m_auiEncounter[4]
                   >> m_auiEncounter[5] >> m_auiEncounter[6] >> m_auiEncounter[7]
                   >> m_auiEncounter[8] >> m_auiEncounter[9] >> m_auiEncounter[10]
                   >> m_auiEncounter[11] >> m_auiEncounter[12] >> m_auiEncounter[13];

        if (dataHead1 == 'U' && dataHead2 == 'U')
        {

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
            {
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;
            }
        }


        OUT_LOAD_INST_DATA_COMPLETE;
    }
};

InstanceData* GetInstanceData_instance_ulduar(Map* pMap)
{
    return new instance_ulduar(pMap);
}

void AddSC_instance_ulduar()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_ulduar";
    newscript->GetInstanceData = &GetInstanceData_instance_ulduar;
    newscript->RegisterSelf();
}
