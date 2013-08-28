/*
Killstreak Script by Nekro


*/

#include "ScriptPCH.h"
#include "Chat.h"
#include "Language.h"

std::string GetNameColor(Player* player)
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
        return color + name + "|cffFFFFFF";
}

class Killstreak : public PlayerScript
{
public:
	Killstreak() : PlayerScript("Killstreak") {}
	
	void OnLogout(Player* player)
	{
		QueryResult result = CharacterDatabase.PQuery("DELETE FROM killstreaks WHERE guid = %u", player->GetGUID());
	}

	void OnPVPKill(Player* killer, Player* killed)
	{
		if (killer->getLevel() == 255 && killed->getLevel() == 255)
		{
		QueryResult result = CharacterDatabase.PQuery("SELECT killstreak FROM killstreaks WHERE guid = %u", killer->GetGUID());
		if(result)
		{
			uint32 current = (*result)[0].GetUInt32();
			if(current == 0)
				current = 1;
			else
				current++;
			QueryResult update = CharacterDatabase.PQuery("UPDATE killstreaks SET killstreak = %u WHERE guid = %u", current, killer->GetGUID());
			QueryResult findStreak = WorldDatabase.PQuery("SELECT title,global FROM killstreaks WHERE requirement = %u", current);
			if(findStreak)
			{
				const char* title = (*findStreak)[0].GetCString();
				uint16 global = (*findStreak)[1].GetUInt16();
				if(global == 1)
				{
					char msg[200];
					sprintf(msg, "%s is %s. %d kills!", GetNameColor(killer).c_str(), title, current); 
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					std::string str = msg;

					WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
					data << str;
					sWorld->SendGlobalMessage(&data);
				}
				else
				{
					if(killer->GetSession())
					{
						ChatHandler(killer->GetSession()).PSendSysMessage("%s is %s. %d kills!", GetNameColor(killer).c_str(), title, current);
						killer->GetSession()->SendNotification("%s is %s. %d kills!", GetNameColor(killer).c_str(), title, current);
					}
				}
			}
		}
		else
		{
			CharacterDatabase.PQuery("REPLACE INTO killstreaks VALUES(%u, 1)", killer->GetGUID());
		}
		QueryResult killedStreak = CharacterDatabase.PQuery("SELECT killstreak FROM killstreaks WHERE guid = %u", killed->GetGUID());
		if(killedStreak)
		{
			uint32 streak = (*killedStreak)[0].GetUInt32();
			if(streak > 150)
				streak = 150;
			else if(streak > 100)
				streak = 100;
			streak = streak - (streak % 5);
			QueryResult findStreak = WorldDatabase.PQuery("SELECT title,global FROM killstreaks WHERE requirement = %u", streak);
			if(findStreak)
			{
				const char * title = (*findStreak)[0].GetCString();
				uint16 global = (*findStreak)[1].GetUInt16();
				if(global == 1)
				{
					char msg[200];
					sprintf(msg, "%s's %s killstreak has been ended by %s", GetNameColor(killed).c_str(), title, GetNameColor(killer).c_str());
					sWorld->SendServerMessage(SERVER_MSG_STRING, msg);
					std::string str = msg;

					WorldPacket data(SMSG_NOTIFICATION, (str.size()+1));
					data << str;
					sWorld->SendGlobalMessage(&data);
				}
				else
				{
					if(killer->GetSession())
					{
						ChatHandler(killer->GetSession()).PSendSysMessage("%s's %s killstreak has been ended by %s", GetNameColor(killed).c_str(), title, GetNameColor(killer).c_str());
						killer->GetSession()->SendNotification("%s's %s killstreak has been ended by %s", GetNameColor(killed).c_str(), title, GetNameColor(killer).c_str());
					}
				}
			}
			CharacterDatabase.PQuery("DELETE FROM killstreaks WHERE guid = %u", killed->GetGUID());
		}
	}
	}
};

void AddSC_Killstreak()
{
	new Killstreak();
}