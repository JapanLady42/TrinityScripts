#include "ScriptMgr.h"
#include "ScriptedCreature.h"
//atiesh isnt a dungeon boss so he should not be on stratholme.h
enum Spells
{
    SPELL_UNHOLY_AURA = 17467,
    SPELL_BREATH_OF_SARGERAS = 28342,
    SPELL_SHADOWBOLT = 36868,
};
 
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
            Timer_Breath = 10000;
            Timer_Shadowbolt = 3500;
        }
 
        uint32 Timer_Breath;
        uint32 Timer_Shadowbolt;
        void Reset() override
        {
            Initialize();
        }
 
        void EnterCombat(Unit* /who/) override
        {
            DoCastSelf(SPELL_UNHOLY_AURA);
        }
 
 
        void SpellHit(Unit* /source/, const SpellInfo* spell) override 
        {
            if (spell->Mechanic == MECHANIC_DISARM) {
                if (me->IsInCombat() == false) {
                    return; 
                }
                else
                {
                    me->GetVictim()>ToPlayer()>AddItem(22736, 1);
                    me->TextEmote("Atiesh drops its weapon.");
                }
            }
        }
        void UpdateAI(uint32 diff) override
        {
            if (!UpdateVictim())
                return;
 
            if (Timer_Breath <= diff){
                DoCastVictim(SPELL_BREATH_OF_SARGERAS);
                Timer_Breath = 25000;
            }
            else Timer_Breath -= diff;
 
            if (Timer_Shadowbolt <= diff) {
                if (SelectTarget(SELECT_TARGET_RANDOM, 0)) {
                    DoCastVictim(SPELL_SHADOWBOLT);
                    Timer_Shadowbolt = 5000 + (rand32() % 9000);
                }
            }
            else Timer_Shadowbolt -= diff;
 
            DoMeleeAttackIfReady();
        }
    };
 
};
 
void AddSC_boss_atiesh()
{
    new boss_atiesh();
}﻿
