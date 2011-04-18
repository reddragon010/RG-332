/* Copyright (C) 2006 - 2008 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
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
#include "Database/DatabaseEnv.h"
#include "Log.h"
#include <cstring>
extern DatabaseType InternDatabase;

 const int32 PetItems[] =
{
        23713,  34493,  49287,
        35227,  20371,  13584,
        39286,  32588,  49693,
        38050,  30360,  25535,
        13583,  49665,  34492,
        22114,  46802,  49343,
        39656,  13582,  32498
};

#define PET_COUNT               21

struct playerVIPCodeTmp
{
                uint64 timestamp; //Timestamp der ersten Codeeingabe -- automatische bereinigung!!
                std::string code; //PremiumCode
                std::string usage; //z.B. "PET"
};

typedef std::map<uint64, playerVIPCodeTmp> VipCodeMapType;
typedef std::map<std::string, VendorItemData> CodeVendorDataMapType;
VipCodeMapType VipCodeTmp;
CodeVendorDataMapType CodeVendorTmp;

#define VIP_CODE_ENTER		100001
#define VIP_CODE_CLOSE		100002
#define VIP_CODE_INVALID	100003
#define VIP_CODE_USED		100004
#define VIP_CODE_NO		100005

bool GossipHello_vip_codebox(Player* pPlayer, Creature* pCreature)
{
    pPlayer->ADD_GOSSIP_ITEM_EXTENDED(GOSSIP_ICON_VENDOR, VIP_CODE_ENTER, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_TRADE, "", 0, true);
    pPlayer->ADD_GOSSIP_ITEM(GOSSIP_ICON_CHAT, VIP_CODE_CLOSE, GOSSIP_SENDER_MAIN, GOSSIP_ACTION_INFO_DEF+2);

    pPlayer->PlayerTalkClass->SendGossipMenu(pPlayer->GetGossipTextId(pCreature), pCreature->GetGUID());
    return true;
}

bool GossipSelect_vip_codebox(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction)
{
    if(uiSender == GOSSIP_SENDER_MAIN)
    {
        if(uiAction == GOSSIP_ACTION_INFO_DEF+2)
                pPlayer->CLOSE_GOSSIP_MENU();
    }
    //outstring_log("VIP: Select: Sender: %u (%u), Action: %u (%u)", uiSender, (uiSender == GOSSIP_SENDER_MAIN), uiAction, (uiAction == GOSSIP_ACTION_INFO_DEF+2));
    return true;
}

bool GossipSelectWithCode_vip_codebox(Player* pPlayer, Creature* pCreature, uint32 uiSender, uint32 uiAction, const char* sCode)
{
    if (uiSender == GOSSIP_SENDER_MAIN)
    {
        if (uiAction == GOSSIP_ACTION_TRADE)
        {
            std::string escaped = sCode;
            InternDatabase.escape_string(escaped);
            QueryResult_AutoPtr res = InternDatabase.PQuery("SELECT `for` FROM `jos_rgpremium_codes` WHERE `used`=0 AND `code`='%s' LIMIT 0,1;", escaped.c_str());

            if(!res) {
                    pPlayer->GetSession()->SendAreaTriggerMessage(objmgr.GetTrinityString(VIP_CODE_INVALID, pPlayer->GetSession()->GetSessionDbLocaleIndex()));
		    pPlayer->CLOSE_GOSSIP_MENU();
                    return false;
            }


            VipCodeMapType::iterator itr = VipCodeTmp.find(pPlayer->GetGUID());
            if (itr != VipCodeTmp.end())
                    VipCodeTmp.erase(itr);
	    Field* fields = res->Fetch();

            //Code ungenutzt und gueltig -> speichern und itemid abfragen
            playerVIPCodeTmp Code;
            Code.timestamp = time(NULL);
            Code.code = escaped;
            Code.usage = fields[0].GetCppString();

            VipCodeTmp.insert(std::pair<uint64, playerVIPCodeTmp>((uint64)pPlayer->GetGUID(), (playerVIPCodeTmp)Code));

	    //Code teilweise aus pPlayer->GetSession()->SendListInventory()
	    if(pPlayer->hasUnitState(UNIT_STAT_DIED))
		pPlayer->RemoveAurasByType(SPELL_AURA_FEIGN_DEATH);
	    pCreature->StopMoving();
	    
	    VendorItemData data;
	    
	    //Suche Vendorinfo
	    CodeVendorDataMapType::iterator codeItr = CodeVendorTmp.find(Code.usage);
	    if(codeItr == CodeVendorTmp.end()) { //info erstellen
		    if(Code.usage == "PET") {
			for (int i = 0; i < PET_COUNT; i++) {
				data.AddItem(PetItems[i], 0, 0, 0);
			}
		    }
    		    CodeVendorTmp.insert(std::pair<std::string, VendorItemData>(Code.usage, data));
	    } else {
		    data = codeItr->second;
	    }
	    
	    uint8 numitems = data.GetItemCount();
	    uint8 count = 0;
	    WorldPacket pack( SMSG_LIST_INVENTORY, (8+1+numitems*8*4) );
	    pack << uint64(pCreature->GetGUID());
	    pack << uint8(numitems);
	    for (int i = 0; i < numitems; ++i )
	    {
		if(VendorItem const* crItem = data.GetItem(i))
		{
			if(ItemPrototype const *pProto = objmgr.GetItemPrototype(crItem->item))
			{
				++count;
				int32 price = uint32(pProto->BuyPrice);
				pack << uint32(count);
				pack << uint32(crItem->item);
				pack << uint32(pProto->DisplayInfoID);
				pack << int32(crItem->maxcount <= 0 ? 0xFFFFFFFF : pCreature->GetVendorItemCurrentCount(crItem));
				pack << uint32(price);
				pack << uint32(pProto->MaxDurability);
				pack << uint32(pProto->BuyCount);
				pack << uint32(crItem->ExtendedCost);
			}
		}
	    }

	    if ( count == 0 || pack.size() != 8 + 1 + size_t(count) * 8 * 4 )
		return false;

	    pack.put<uint8>(8, count);
 	    pPlayer->GetSession()->SendPacket( &pack );
            return true;
        }
    }
    return false;
}

//0 -> Pruefung fehlgeschlagen
// > 0 -> Pruefung erfolgreich -> Item geben
int8 ItemBuy_vip_codebox(Player* pPlayer, Creature* pCreature, uint32 itemId, uint32 count, size_t* vendorslot)
{
	if (count != 1) { //Nur 1 Item pro Code
		pPlayer->SendBuyError(BUY_ERR_ITEM_SOLD_OUT, pCreature, itemId, 0);
		pPlayer->CLOSE_GOSSIP_MENU();
		return 0;
	}
	VipCodeMapType::iterator itr = VipCodeTmp.find(pPlayer->GetGUID());
	if (itr == VipCodeTmp.end()) {
		pPlayer->GetSession()->SendAreaTriggerMessage(objmgr.GetTrinityString(VIP_CODE_USED, pPlayer->GetSession()->GetSessionDbLocaleIndex()));
                pPlayer->SendBuyError(BUY_ERR_CANT_FIND_ITEM, pCreature, itemId, 0);
		pPlayer->CLOSE_GOSSIP_MENU();
                return 0;
	}

	//Richtiges Inventar suchen
	CodeVendorDataMapType::iterator vendorItr = CodeVendorTmp.find(itr->second.usage);
	if(vendorItr == CodeVendorTmp.end()) { //Code nicht initialisert - Cheater?
		pPlayer->GetSession()->SendAreaTriggerMessage(objmgr.GetTrinityString(VIP_CODE_NO, pPlayer->GetSession()->GetSessionDbLocaleIndex()));
                pPlayer->SendBuyError(BUY_ERR_CANT_FIND_ITEM, pCreature, itemId, 0);
		pPlayer->CLOSE_GOSSIP_MENU();
                return 0;
	}
	
	VendorItemData vItems = vendorItr->second;
        if(vItems.Empty()) {
		pPlayer->SendBuyError(BUY_ERR_CANT_FIND_ITEM, pCreature, itemId, 0);
                pPlayer->CLOSE_GOSSIP_MENU();
                return 0;
	}
	
	size_t vendor_slot = vItems.FindItemSlot(itemId);
	*vendorslot = vendor_slot;
	if(vendor_slot >= vItems.GetItemCount())
	{
		pPlayer->SendBuyError(BUY_ERR_CANT_FIND_ITEM, pCreature, itemId, 0);
		pPlayer->CLOSE_GOSSIP_MENU();
		return 0;
	}
	
	InternDatabase.PExecute("UPDATE `jos_rgpremium_codes` SET `used`=1 WHERE `code`='%s' LIMIT 1;", itr->second.code.c_str());
	VipCodeTmp.erase(itr);
	
	return 1; //alles super
}

struct vip_codeboxAI : public ScriptedAI
{
        uint32 uiResetCheck;
        vip_codeboxAI(Creature *c) : ScriptedAI(c) {uiResetCheck = 60000;}

        //Player, die nicht beendet haben loeschen
        void UpdateAI(const uint32 diff)
        {
                if(uiResetCheck < diff)
                {
                        for(VipCodeMapType::iterator itr = VipCodeTmp.begin(); itr != VipCodeTmp.end(); itr++) {
                                if(time(NULL) - itr->second.timestamp > 5*60)
                                        VipCodeTmp.erase(itr);
                        }
                } else uiResetCheck -= diff;
        }
};

CreatureAI* GetAI_vip_codebox(Creature* pCreature)
{
    return new vip_codeboxAI (pCreature);
}

void AddSC_vip_codebox()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name="vip_codebox";
    newscript->GetAI = &GetAI_vip_codebox;
    newscript->pGossipHello =           &GossipHello_vip_codebox;
    newscript->pGossipSelect = &GossipSelect_vip_codebox;
    newscript->pGossipSelectWithCode =  &GossipSelectWithCode_vip_codebox;
    newscript->pItemBuy = &ItemBuy_vip_codebox;
    newscript->RegisterSelf();
}
