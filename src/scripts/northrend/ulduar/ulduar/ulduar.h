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

#ifndef DEF_ULDUAR_H
#define DEF_ULDUAR_H

enum Encounter

{
    BOSS_LEVIATHAN,
    BOSS_IGNIS,
    BOSS_RAZORSCALE,
    BOSS_XT002,
    BOSS_ASSEMBLY,
    BOSS_KOLOGARN,
    BOSS_AURIAYA,
    BOSS_MIMIRON,
    BOSS_HODIR,
    BOSS_THORIM,
    BOSS_FREYA,
    BOSS_VEZAX,
    BOSS_YOGGSARON,
    BOSS_ALGALON,
    MAX_BOSS_NUMBER
};


//enum Data64
//{
//    DATA_LEVIATHAN,
//    DATA_NORGANNON,
//    DATA_IGNIS,
//    DATA_RAZORSCALE,
//    DATA_EXP_COMMANDER,
//    DATA_XT002,
//    DATA_STEELBREAKER,
//    DATA_MOLGEIM,
//    DATA_BRUNDIR,
//    DATA_KOLOGARN,
//    DATA_RIGHT_ARM,
//    DATA_LEFT_ARM,
//    DATA_AURIAYA,
//    DATA_BRIGHTLEAF,
//    DATA_IRONBRANCH,
//    DATA_STONEBARK,
//    DATA_FREYA,
//    DATA_THORIM,
//    DATA_RUNIC_COLOSSUS,
//    DATA_RUNE_GIANT,
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//
//    DATA_SARONITE_ANIMUS
//};

enum Data
{
    DATA_LEVIATHAN_DOOR,
    DATA_RUNIC_DOOR,
    DATA_STONE_DOOR,
    DATA_NORGANNON
};

enum eTypes
{
    MAX_ENCOUNTER               = 15,

    TYPE_LEVIATHAN              = 0,
    TYPE_IGNIS                  = 1,
    TYPE_RAZORSCALE             = 2,
    TYPE_XT002                  = 3,
    TYPE_ASSEMBLY               = 4,
    TYPE_KOLOGARN               = 5,
    TYPE_AURIAYA                = 6,
    TYPE_MIMIRON                = 7,
    TYPE_HODIR                  = 8,
    TYPE_THORIM                 = 9,
    TYPE_FREYA                  = 10,
    TYPE_VEZAX                  = 11,
    TYPE_YOGGSARON              = 12,
    TYPE_ALGALON                = 13,
    TYPE_COMMANDER              = 14,
    TYPE_KOLOGARN_LEFT_ARM      = 15,
    TYPE_KOLOGARN_RIGHT_ARM     = 16,
    TYPE_LEVIATHAN_MK           = 17,
    TYPE_AERIAL_UNIT            = 18,
    TYPE_VX001AI                = 19,
    TYPE_SARONITE_ANIMUS        = 20,
    TYPE_COLOSSUS               = 21,

    DATA_STEELBREAKER           = 40,
    DATA_MOLGEIM                = 41,
    DATA_BRUNDIR                = 42,
    DATA_RUNEMASTER_MOLGEIM     = 43,
    DATA_STORMCALLER_BRUNDIR    = 44,
    DATA_UNIVERSE_GLOBE         = 45,
    DATA_RANDOM_CONSTRUCT         = 46,
    DATA_KOLOGARN               = 47,
    DATA_RIGHT_ARM              = 48,
    DATA_LEFT_ARM               = 49,
    DATA_AURIAYA                = 50,
    DATA_SENTRY_1               = 51,
    DATA_SENTRY_2               = 52,
    DATA_SENTRY_3               = 53,
    DATA_SENTRY_4               = 54,
    DATA_FERAL_DEFENDER         = 55,
    DATA_RAZORSCALE             = 56,
    DATA_XT002                  = 57,
    DATA_LEVIATHAN_TRIGGER      = 58,
    DATA_EXP_COMMANDER          = 59,
    DATA_LEVIATHAN              = 50,

    NPC_LEVIATHAN               = 33113,
    NPC_IGNIS                   = 33118,
    NPC_IRON_CONSTRUCT          = 33121,
    NPC_RAZORSCALE              = 33186,
    NPC_XT002                   = 33293,
    NPC_STEELBREAKER            = 32867,
    NPC_MOLGEIM                 = 32927,
    NPC_BRUNDIR                 = 32857,
    NPC_KOLOGARN                = 32930,
    NPC_AURIAYA                 = 33515,
    NPC_SANCTUM_SENTRY          = 34014,
    NPC_MIMIRON                 = 33350,
    NPC_HODIR                   = 32845,
    NPC_THORIM                  = 32865,
    NPC_FREYA                   = 32906,
    NPC_VEZAX                   = 33271,
    NPC_YOGGSARON               = 33288,
    NPC_ALGALON                 = 32871,
    NPC_COMMANDER               = 33210,
    NPC_GTRAPPER                = 33259,
    NPC_ENGINEER                = 33287,
    NPC_DEFENDER                = 33816,

    NPC_FIRE_STATE              = 33184,
    NPC_KOLOGARN_LEFT_ARM       = 32933,
    NPC_KOLOGARN_RIGHT_ARM      = 32934,
    NPC_LEVIATHAN_TRIGGER       = 33115,

    GO_KOLOGARN_BRIDGE          = 194232,
    GO_Kologarn_CHEST_HERO      = 195047,
    GO_Kologarn_CHEST           = 195046,
    GO_THORIM_CHEST_H           = 194315,
    GO_THORIM_CHEST_N           = 194314,

    EVENT_TOWER_OF_STORM_DESTROYED     = 21031,
    EVENT_TOWER_OF_FROST_DESTROYED     = 21032,
    EVENT_TOWER_OF_FLAMES_DESTROYED    = 21033,
    EVENT_TOWER_OF_NATURE_DESTROYED    = 21030
};

#endif

