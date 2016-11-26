#include "ScriptMgr.h"
#include "ScriptedCreature.h"
//atiesh is not boss so we dont add stratholme.h

 
class boss_atiesh : public CreatureScript
{
public:
    boss_atiesh() : CreatureScript("boss_atiesh") { }
 
    CreatureAI* GetAI(Creature* creature) const override
    {
        return new boss_atieshAI(creature);
    }
 
    struct boss_atieshAI : public ScriptedAI
    {
        boss_atieshAI(Creature* creature) : ScriptedAI(creature)
        {
            Initialize();
        }
 
        void Initialize()
        {
            
        }
 
        void Reset() override
        {
            Initialize();
        }
 
        void EnterCombat(Unit* /who/) override
        {
        }
 
 
        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
 
            //TODO: Find spells to put here
 
            DoMeleeAttackIfReady();
        }
    };
 
};
 
void AddSC_boss_atiesh()
{
    new boss_atiesh();
}﻿
