# Copyright (C) 2008-2013 TrinityCore <http://www.trinitycore.org/>
#
# This file is free software; as a special exception the author gives
# unlimited permission to copy and/or distribute it, with or without
# modifications, as long as this notice is preserved.
#
# This program is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY, to the extent permitted by law; without even the
# implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

set(scripts_STAT_SRCS
  ${scripts_STAT_SRCS}
	Custom/Transmogrification.h
	Custom/Transmogrification.cpp
	Custom/Transmogrifier.cpp
	Custom/npc_beastmaster.cpp
	Custom/npc_enchant.cpp
	Custom/npc_profession.cpp
	Custom/npc_arena.cpp
	Custom/pvp_killstreak.cpp
	Custom/pvp_duel_end.cpp
	Custom/sec_anti_farming.cpp
)

message("  -> Prepared: Custom")
