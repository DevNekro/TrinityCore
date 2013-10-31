#include "AccountMgr.h"
#include "Chat.h"
#include "Language.h"
#include "Player.h"
#include "ScriptMgr.h"
#include "RBAC.h"

std::string GetNameLink(Player* player)
{
        std::string name = player->GetName();
        std::string color;
        switch(player->getClass())
        {
        case CLASS_DEATH_KNIGHT:
                color = "|cffC41F3B";
                break;
        case CLASS_DRUID:
                color = "|cffFF7D0A";
                break;
        case CLASS_HUNTER:
                color = "|cffABD473";
                break;
        case CLASS_MAGE:
                color = "|cff69CCF0";
                break;
        case CLASS_PALADIN:
                color = "|cffF58CBA";
                break;
        case CLASS_PRIEST:
                color = "|cffFFFFFF";
                break;
        case CLASS_ROGUE:
                color = "|cffFFF569";
                break;
        case CLASS_SHAMAN:
                color = "|cff0070DE";
                break;
        case CLASS_WARLOCK:
                color = "|cff9482C9";
                break;
        case CLASS_WARRIOR:
                color = "|cffC79C6E";
                break;
        }
        return "|Hplayer:"+name+"|h|cffFFFFFF["+color+name+"|cffFFFFFF]|h|r";
} 
 
class cs_world_chat : public CommandScript
{
public:
	cs_world_chat() : CommandScript("cs_world_chat") { }
 
	ChatCommand * GetCommands() const OVERRIDE
	{
		static ChatCommand commandTable[] =
		{
			{ "chat", rbac::RBAC_CUSTOM_COMMAND_CHAT, false, &HandleWorldChatCommand, "", NULL },
			{ NULL,   0,                        false, NULL,                    "", NULL }
		};
 
		return commandTable;
	}
 
	static bool HandleWorldChatCommand(ChatHandler * handler, const char * args)
	{
		if (!handler->GetSession()->GetPlayer()->CanSpeak())
			return false;
				
		std::string temp = args;
		
		if (!args || temp.find_first_not_of(' ') == std::string::npos)   
			return false;

		std::string msg = "";
		Player * player = handler->GetSession()->GetPlayer();
 
		msg += "|cff1eff00[World]";
		if (player->GetTeam() == ALLIANCE)
			msg += "|TInterface\\TARGETINGFRAME\\UI-PVP-Alliance.blp:30:30:0:-4|t";
		else
			msg += "|TInterface\\TARGETINGFRAME\\UI-PVP-Horde.blp:30:30:0:-4|t";
		switch (player->getORace())
		{
			case RACE_HUMAN:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Human_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Human_Female.blp:20:20:0:0|t";
				break;
			case RACE_ORC:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Orc_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Orc_Female.blp:20:20:0:0|t";
				break;
			case RACE_DWARF:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Dwarf_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Dwarf_Female.blp:20:20:0:0|t";
				break;
			case RACE_NIGHTELF:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Nightelf_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Nightelf_Female.blp:20:20:0:0|t";
				break;
			case RACE_UNDEAD_PLAYER:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Undead_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Undead_Female.blp:20:20:0:0|t";
				break;
			case RACE_TAUREN:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Tauren_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Tauren_Female.blp:20:20:0:0|t";
				break;
			case RACE_GNOME:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Gnome_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Gnome_Female.blp:20:20:0:0|t";
				break;
			case RACE_TROLL:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Troll_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Troll_Female.blp:20:20:0:0|t";
				break;
			case RACE_BLOODELF:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Bloodelf_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Bloodelf_Female.blp:20:20:0:0|t";
				break;
			case RACE_DRAENEI:
				if (player->getGender() == GENDER_MALE)
					msg += "|TInterface\\Icons\\Achievement_Character_Draenei_Male.blp:20:20:0:0|t";
				else
					msg += "|TInterface\\Icons\\Achievement_Character_Draenei_Female.blp:20:20:0:0|t";
				break;
		}
		switch(player->getClass())
		{
			case CLASS_WARRIOR:
				msg += "|TInterface\\Icons\\inv_sword_27.blp:20:20:0:0|t";
				break;
			case CLASS_PALADIN:
				msg += "|TInterface\\Icons\\inv_hammer_01.blp:20:20:0:0|t";
				break;
			case CLASS_HUNTER:
				msg += "|TInterface\\Icons\\inv_weapon_bow_07.blp:20:20:0:0|t";
				break;
			case CLASS_ROGUE:
				msg += "|TInterface\\Icons\\inv_throwingknife_04.blp:20:20:0:0|t";
				break;
			case CLASS_PRIEST:
				msg += "|TInterface\\Icons\\inv_staff_30.blp:20:20:0:0|t";
				break;
			case CLASS_DEATH_KNIGHT:
				msg += "|TInterface\\Icons\\spell_deathknight_classicon.blp:20:20:0:0|t";
				break;
			case CLASS_SHAMAN:
				msg += "|TInterface\\Icons\\inv_jewelry_talisman_04.blp:20:20:0:0|t";
				break;
			case CLASS_MAGE:
				msg += "|TInterface\\Icons\\inv_staff_13.blp:20:20:0:0|t";
				break;
			case CLASS_WARLOCK:
				msg += "|TInterface\\Icons\\spell_nature_drowsy.blp:20:20:0:0|t";
				break;
			case CLASS_DRUID:
				msg += "|TInterface\\Icons\\inv_misc_monsterclaw_04.blp:20:20:0:0|t";
				break;
		}
		msg += GetNameLink(player);
		msg += ":|cfffaeb00";
		msg += args;
		sWorld->SendServerMessage(SERVER_MSG_STRING, msg.c_str(), 0);  
		return true;
	}
};
 
void AddSC_cs_world_chat()
{
        new cs_world_chat();
}