/* Copyright (C) 2006 - 2009 ScriptDev2 <https://scriptdev2.svn.sourceforge.net/>
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* ScriptData
SDName: GO_Scripts
SD%Complete: 100
SDComment: Quest support: 4285,4287,4288(crystal pylons), 4296, 5088, 6481, 10990, 10991, 10992. Field_Repair_Bot->Teaches spell 22704. Barov_journal->Teaches spell 26089
SDCategory: Game Objects
EndScriptData */

/* ContentData
go_cat_figurine (the "trap" version of GO, two different exist)
go_eastern_crystal_pylon
go_western_crystal_pylon
go_barov_journal
go_field_repair_bot_74A
go_orb_of_command
go_resonite_cask
go_sacred_fire_of_life
go_tablet_of_madness
go_tablet_of_the_seven
EndContentData */

#include "precompiled.h"

/*######
## go_cat_figurine
######*/

enum
{
    SPELL_SUMMON_GHOST_SABER    = 5968,
};

bool GOHello_go_cat_figurine(Player* pPlayer, GameObject* pGo)
{
    pPlayer->CastSpell(pPlayer,SPELL_SUMMON_GHOST_SABER,true);
    return false;
}

/*######
## go_crystal_pylons (3x)
######*/


bool GOHello_go_eastern_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetGUID());
        pPlayer->SendPreparedQuest(pGo->GetGUID());
    }

    if (pPlayer->GetQuestStatus(4287) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4287);

    return true;
}

bool GOHello_go_western_crystal_pylon(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() == GAMEOBJECT_TYPE_QUESTGIVER)
    {
        pPlayer->PrepareQuestMenu(pGo->GetGUID());
        pPlayer->SendPreparedQuest(pGo->GetGUID());
    }

    if (pPlayer->GetQuestStatus(4288) == QUEST_STATUS_INCOMPLETE)
        pPlayer->AreaExploredOrEventHappens(4288);

    return true;
}

/*######
## go_barov_journal
######*/

bool GOHello_go_barov_journal(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_TAILORING) && pPlayer->GetBaseSkillValue(SKILL_TAILORING) >= 280 && !pPlayer->HasSpell(26086))
    {
        pPlayer->CastSpell(pPlayer,26095,false);
    }
    return true;
}


/*######
## go_field_repair_bot_74A
######*/

bool GOHello_go_field_repair_bot_74A(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ENGINEERING) && pPlayer->GetBaseSkillValue(SKILL_ENGINEERING) >= 300 && !pPlayer->HasSpell(22704))
    {
        pPlayer->CastSpell(pPlayer,22864,false);
    }
    return true;
}

/*######
## go_gilded_brazier
######*/

enum
{
    NPC_STILLBLADE  = 17716,
};

bool GOHello_go_gilded_brazier(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
    {
        if (Creature* pCreature = pPlayer->SummonCreature(NPC_STILLBLADE, 8087.632f, -7542.740f, 151.568f, 0.122f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 5000))
            pCreature->AI()->AttackStart(pPlayer);
    }

    return true;
}


/*######
## go_orb_of_command
######*/

bool GOHello_go_orb_of_command(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->GetQuestRewardStatus(7761))
        pPlayer->CastSpell(pPlayer,23460,true);

    return true;
}

/*######
## go_resonite_cask
######*/

enum
{
    NPC_GOGGEROC    = 11920
};

bool GOHello_go_resonite_cask(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pGO->SummonCreature(NPC_GOGGEROC, 0.0f, 0.0f, 0.0f, 0.0f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 300000);

    return false;
}

/*######
## go_sacred_fire_of_life
######*/

enum
{
    NPC_ARIKARA     = 10882,
};

bool GOHello_go_sacred_fire_of_life(Player* pPlayer, GameObject* pGO)
{
    if (pGO->GetGoType() == GAMEOBJECT_TYPE_GOOBER)
        pPlayer->SummonCreature(NPC_ARIKARA, -5008.338f, -2118.894f, 83.657f, 0.874f, TEMPSUMMON_TIMED_DESPAWN_OUT_OF_COMBAT, 30000);

    return true;
}

/*######
## go_tablet_of_madness
######*/

bool GOHello_go_tablet_of_madness(Player* pPlayer, GameObject* pGo)
{
    if (pPlayer->HasSkill(SKILL_ALCHEMY) && pPlayer->GetSkillValue(SKILL_ALCHEMY) >= 300 && !pPlayer->HasSpell(24266))
    {
        pPlayer->CastSpell(pPlayer,24267,false);
    }
    return true;
}

/*######
## go_tablet_of_the_seven
######*/

//TODO: use gossip option ("Transcript the Tablet") instead, if Mangos adds support.
bool GOHello_go_tablet_of_the_seven(Player* pPlayer, GameObject* pGo)
{
    if (pGo->GetGoType() != GAMEOBJECT_TYPE_QUESTGIVER)
        return true;

    if (pPlayer->GetQuestStatus(4296) == QUEST_STATUS_INCOMPLETE)
        pPlayer->CastSpell(pPlayer,15065,false);

    return true;
}


void AddSC_go_scripts()
{
    Script *newscript;

    newscript = new Script;
    newscript->Name = "go_cat_figurine";
    newscript->pGOHello =           &GOHello_go_cat_figurine;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_eastern_crystal_pylon";
    newscript->pGOHello =           &GOHello_go_eastern_crystal_pylon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_western_crystal_pylon";
    newscript->pGOHello =           &GOHello_go_western_crystal_pylon;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_barov_journal";
    newscript->pGOHello =           &GOHello_go_barov_journal;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_field_repair_bot_74A";
    newscript->pGOHello =           &GOHello_go_field_repair_bot_74A;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_gilded_brazier";
    newscript->pGOHello =           &GOHello_go_gilded_brazier;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_orb_of_command";
    newscript->pGOHello =           &GOHello_go_orb_of_command;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_resonite_cask";
    newscript->pGOHello =           &GOHello_go_resonite_cask;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_sacred_fire_of_life";
    newscript->pGOHello =           &GOHello_go_sacred_fire_of_life;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tablet_of_madness";
    newscript->pGOHello =           &GOHello_go_tablet_of_madness;
    newscript->RegisterSelf();

    newscript = new Script;
    newscript->Name = "go_tablet_of_the_seven";
    newscript->pGOHello =           &GOHello_go_tablet_of_the_seven;
    newscript->RegisterSelf();

}
