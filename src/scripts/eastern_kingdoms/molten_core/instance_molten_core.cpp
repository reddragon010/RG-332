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
SDName: Instance_Molten_Core
SD%Complete: 0
SDComment: Place Holder
SDCategory: Molten Core
EndScriptData */

#include "ScriptedPch.h"
#include "molten_core.h"

#define MAX_ENCOUNTER      10

#define ID_LUCIFRON     12118
#define ID_MAGMADAR     11982
#define ID_GEHENNAS     12259
#define ID_GARR         12057
#define ID_GEDDON       12056
#define ID_SHAZZRAH     12264
#define ID_GOLEMAGG     11988
#define ID_SULFURON     12098
#define ID_DOMO         12018
#define ID_RAGNAROS     11502
#define ID_FLAMEWAKERPRIEST     11662
#define ID_FLAMEWAKER_HEALER    11663
#define ID_FLAMEWAKER_ELITE     11664

#define SAY_SPAWN_DOMO          -1409004

struct instance_molten_core : public ScriptedInstance
{
    instance_molten_core(Map* pMap) : ScriptedInstance(pMap) {Initialize();};

    uint64 Lucifron, Magmadar, Gehennas, Garr, Geddon, Shazzrah, Sulfuron, Golemagg, Domo, Ragnaros, FlamewakerPriest;
    uint64 RuneKoro, RuneZeth, RuneMazj, RuneTheri, RuneBlaz, RuneKress, RuneMohn, m_uiFirelordCacheGUID;

    //If all Bosses are dead.
    bool IsBossDied[MAX_ENCOUNTER];

    uint32 m_auiEncounter[MAX_ENCOUNTER];

    std::list<uint64> majordomoList;
    uint32 uiPhaseMajordomo;
    uint32 uiPhaseRagnaros;

 //   uint64 uiMajordomoChest;

    std::string str_data;

    void Initialize()
    {
        memset(&m_auiEncounter, 0, sizeof(m_auiEncounter));

        Lucifron = 0;
        Magmadar = 0;
        Gehennas = 0;
        Garr = 0;
        Geddon = 0;
        Shazzrah = 0;
        Sulfuron = 0;
        Golemagg = 0;
        Domo = 0;
        Ragnaros = 0;
        FlamewakerPriest = 0;

        RuneKoro = 0;
        RuneZeth = 0;
        RuneMazj = 0;
        RuneTheri = 0;
        RuneBlaz = 0;
        RuneKress = 0;
        RuneMohn = 0;

        m_uiFirelordCacheGUID = 0;

        uiPhaseMajordomo = 1;
        uiPhaseRagnaros = 1;
//        uiMajordomoChest = 0;

        IsBossDied[0] = false;
        IsBossDied[1] = false;
        IsBossDied[2] = false;
        IsBossDied[3] = false;
        IsBossDied[4] = false;
        IsBossDied[5] = false;
        IsBossDied[6] = false;

        IsBossDied[7] = false;
        IsBossDied[8] = false;
    }

    bool IsEncounterInProgress() const
    {
        return false;
    };

    void OnGameObjectCreate(GameObject* pGo, bool add)
    {
        switch(pGo->GetEntry())
        {
        case 176951:                                    //Sulfuron
            RuneKoro = pGo->GetGUID();
            break;
        case 176952:                                    //Geddon
            RuneZeth = pGo->GetGUID();
            break;
        case 176953:                                    //Shazzrah
            RuneMazj = pGo->GetGUID();
            break;
        case 176954:                                    //Golemagg
            RuneTheri = pGo->GetGUID();
            break;
        case 176955:                                    //Garr
            RuneBlaz = pGo->GetGUID();
            break;
        case 176956:                                    //Magmadar
            RuneKress = pGo->GetGUID();
            break;
        case 176957:                                    //Gehennas
            RuneMohn = pGo->GetGUID();
            break;
        case 179703:
            m_uiFirelordCacheGUID = pGo->GetGUID();      //when majordomo event == DONE DoRespawnGameObject(m_uiFirelordCacheGUID,);
//            uiMajordomoChest = pGo->GetGUID();
            if (m_auiEncounter[8] == DONE)
                pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
            break;
        }
    }

    void OnCreatureCreate(Creature* pCreature, bool add)
    {
        switch (pCreature->GetEntry())
        {
            case ID_LUCIFRON:
                Lucifron = pCreature->GetGUID();
                break;

            case ID_MAGMADAR:
                Magmadar = pCreature->GetGUID();
                break;

            case ID_GEHENNAS:
                Gehennas = pCreature->GetGUID();
                break;

            case ID_GARR:
                Garr = pCreature->GetGUID();
                break;

            case ID_GEDDON:
                Geddon = pCreature->GetGUID();
                break;

            case ID_SHAZZRAH:
                Shazzrah = pCreature->GetGUID();
                break;

            case ID_SULFURON:
                Sulfuron = pCreature->GetGUID();
                break;

            case ID_GOLEMAGG:
                Golemagg = pCreature->GetGUID();
                break;

            case ID_DOMO:
                Domo = pCreature->GetGUID();
                majordomoList.push_back(Domo);
                break;

            case ID_RAGNAROS:
                Ragnaros = pCreature->GetGUID();
                if (m_auiEncounter[8] == DONE)
                    pCreature->SetPhaseMask(1, true);
                else
                    pCreature->SetPhaseMask(2, true);
                break;

            case ID_FLAMEWAKERPRIEST:
                FlamewakerPriest = pCreature->GetGUID();
                break;
            case ID_FLAMEWAKER_HEALER:
            case ID_FLAMEWAKER_ELITE:
                majordomoList.push_back(pCreature->GetGUID());
                break;
        }
    }

    uint64 GetData64 (uint32 identifier)
    {
        switch(identifier)
        {
            case DATA_SULFURON:
                return Sulfuron;
            case DATA_GOLEMAGG:
                return Golemagg;

            case DATA_FLAMEWAKERPRIEST:
                return FlamewakerPriest;

            case DATA_MAJORDOMO:
                return Domo;

            case DATA_MAJORDOMOADD:
                {
                    std::vector<uint64> targets;
                    for (std::list<uint64>::const_iterator itr = majordomoList.begin(); itr != majordomoList.end(); ++itr)
                        {
                            Creature *pCreature = instance->GetCreature(*itr);
                            if (pCreature && pCreature->isAlive() && pCreature->GetEntry() != ID_DOMO)
                                targets.push_back(pCreature->GetGUID());
                        }

                    if (!targets.empty())
                    {
                        std::vector<uint64>::const_iterator itr = targets.begin();
                        advance(itr, rand()%targets.size());
                        return (*itr);
                    }
                }
                return 0;
            case DATA_RAGNAROS:
                return Ragnaros;
        }

        return 0;
    }

    uint32 GetData(uint32 type)
    {
        switch(type)
        {
            case DATA_LUCIFRON_EVENT:
                return m_auiEncounter[0];
            case DATA_MAGMADAR_EVENT:
                return m_auiEncounter[1];
            case DATA_GEHENNAS_EVENT:
                return m_auiEncounter[2];
            case DATA_GARRISDEAD:
                return m_auiEncounter[3];
            case DATA_GEDDON_EVENT:
                return m_auiEncounter[4];
            case DATA_SHAZZRAH_EVENT:
                return m_auiEncounter[5];
            case DATA_SULFURON_EVENT:
                return m_auiEncounter[6];
            case DATA_GOLEMAGG_EVENT:
                return m_auiEncounter[7];
            case DATA_MAJORDOMO_EVENT:
                return m_auiEncounter[8];
            case DATA_RAGNAROS_EVENT:
                return m_auiEncounter[9];
        }

        return 0;
    }

    void SetData(uint32 type, uint32 data)
    {
        switch(type)
        {
            case DATA_LUCIFRON_EVENT: 
                m_auiEncounter[0] = data;
                break;

            case DATA_MAGMADAR_EVENT:
                m_auiEncounter[1] = data;
                break;

            case DATA_GEHENNAS_EVENT:
                m_auiEncounter[2] = data;
                break;

            case DATA_GARRISDEAD:
                m_auiEncounter[3] = data;
                break;

            case DATA_GEDDON_EVENT:
                m_auiEncounter[4] = data;
                break;

            case DATA_SHAZZRAH_EVENT:
                m_auiEncounter[5] = data;
                break;

            case DATA_SULFURON_EVENT:
                m_auiEncounter[6] = data;
                break;

            case DATA_GOLEMAGG_EVENT:
            case DATA_GOLEMAGG_DEATH:
                m_auiEncounter[7] = data;
                break;

            case DATA_MAJORDOMO_EVENT:
                m_auiEncounter[8] = data;

                if (data == NOT_STARTED)
                {
                    for (std::list<uint64>::const_iterator itr = majordomoList.begin(); itr != majordomoList.end(); ++itr)
                    {
                        if (Creature *pCreature = instance->GetCreature(*itr))
                        {
                            pCreature->SetPhaseMask(uiPhaseMajordomo, true);
                            if (pCreature->isDead() && pCreature->GetEntry() != ID_DOMO)
                            {
                                pCreature->Respawn();
                                pCreature->GetMotionMaster()->MoveTargetedHome();
                            }
                        }
                    }
                }
                else if (data == DONE)
                {
                    if (GameObject *pGo = instance->GetGameObject(m_uiFirelordCacheGUID))
                    {
                        pGo->SetRespawnTime(pGo->GetRespawnDelay());
                        pGo->RemoveFlag(GAMEOBJECT_FLAGS,GO_FLAG_INTERACT_COND);
                    }
                }
                break;

            case DATA_RAGNAROS_EVENT:
                m_auiEncounter[9] = data;
                break;
        }

        if (data == DONE)
            SaveToDB();

        summonMajordomo();
    }


    std::string GetSaveData()
    {
        OUT_SAVE_INST_DATA;

        std::ostringstream saveStream;
        saveStream << "M C " << m_auiEncounter[0] << " " << m_auiEncounter[1] << " "
            << m_auiEncounter[2] << " " << m_auiEncounter[3] << " " << m_auiEncounter[4] 
            << " " << m_auiEncounter[5] << " " << m_auiEncounter[6] << " " << m_auiEncounter[7] << " " << m_auiEncounter[8] << " " << m_auiEncounter[9];

        str_data = saveStream.str();

        OUT_SAVE_INST_DATA_COMPLETE;
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
        uint16 data0, data1, data2, data3, data4, data5, data6, data7, data8, data9;

        std::istringstream loadStream(in);
        loadStream >> dataHead1 >> dataHead2 >> data0 >> data1 >> data2 >> data3 >> data4 >> data5 >> data6 >> data7 >> data8 >> data9;

        if (dataHead1 == 'M' && dataHead2 == 'C')
        {
            m_auiEncounter[0] = data0;
            m_auiEncounter[1] = data1;
            m_auiEncounter[2] = data2;
            m_auiEncounter[3] = data3;
            m_auiEncounter[4] = data4;
            m_auiEncounter[5] = data5;
            m_auiEncounter[6] = data6;
            m_auiEncounter[7] = data7;
            m_auiEncounter[8] = data8;
            m_auiEncounter[9] = data9;

            for (uint8 i = 0; i < MAX_ENCOUNTER; ++i)
                if (m_auiEncounter[i] == IN_PROGRESS)
                    m_auiEncounter[i] = NOT_STARTED;

            summonMajordomo();

            if (Creature *pCreature = instance->GetCreature(Ragnaros))
                if (m_auiEncounter[8] == DONE)
                    pCreature->SetPhaseMask(1, true);
                else
                    pCreature->SetPhaseMask(2, true);


        } else OUT_LOAD_INST_DATA_FAIL;

        OUT_LOAD_INST_DATA_COMPLETE;
    }
    void summonMajordomo()
    {
        if (m_auiEncounter[8] == DONE)
            return;

        uiPhaseMajordomo = 1;

        for (size_t i=0; i<MAX_ENCOUNTER-2; ++i)
            if (m_auiEncounter[i] != DONE)
            {
                uiPhaseMajordomo = 2;
                break;
            }
                
        for (std::list<uint64>::const_iterator itr = majordomoList.begin(); itr != majordomoList.end(); ++itr)
        {
            if (Creature *pCreature = instance->GetCreature(*itr))
            {
                pCreature->SetPhaseMask(uiPhaseMajordomo, true);

                if (uiPhaseMajordomo == 1 && (*itr) == GetData64(DATA_MAJORDOMO) && GetData(DATA_MAJORDOMO_EVENT) != DONE)
                    DoScriptText(SAY_SPAWN_DOMO, pCreature);
            }
        }

        


    }
};

InstanceData* GetInstance_instance_molten_core(Map* pMap)
{
    return new instance_molten_core (pMap);
}

void AddSC_instance_molten_core()
{
    Script *newscript;
    newscript = new Script;
    newscript->Name = "instance_molten_core";
    newscript->GetInstanceData = &GetInstance_instance_molten_core;
    newscript->RegisterSelf();
}

