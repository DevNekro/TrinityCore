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
			{ "chat", RBAC_CUSTOM_COMMAND_CHAT, false, &HandleWorldChatCommand, "", NULL },
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
		//if (player->GetTeam() == ALLIANCE)
			//msg += "\124Tinterface\\TARGETINGFRAME\\UI-PVP-Alliance.blp:40:40:0:-1\124t";
		//else
			//msg += "\124Tinterface\\TARGETINGFRAME\\UI-PVP-Horde.blp:40:40:0:-1\124t";
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