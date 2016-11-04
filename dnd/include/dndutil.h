/* ---------------------------------------------------------------------- *
 * dndutil.h
 *
 * by Jamis Buck (jgb3@email.byu.edu)
 *
 * Utility functions for the Dungeons & Dragons(tm) API.  This file is in
 * the public domain.
 *
 * Function summary:
 *
 *   int   dndClassBonusFeatEveryXLevels( int id )
 *   int   dndClassHasBonusFeatAtFirstLevel( int id )
 *   int   dndFeatIsReusable( int id )
 *   int   dndGetAbilityBonus( int abilityScore )
 *   char* dndGetAbilityName( int ability )
 *   char* dndGetAlignmentAbbr( int alignment )
 *   char* dndGetAlignmentText( int alignment )
 *   int   dndGetArmorACBonus( int id )
 *   int   dndGetArmorArcaneSpellFailure( int id )
 *   int   dndGetArmorCheckPenalty( int id )
 *   int   dndGetArmorCost( int id )
 *   int   dndGetArmorMaxDexterity( int id )
 *   char* dndGetArmorName( int id )
 *   int   dndGetArmorType( int id )
 *   int   dndGetBonusLanguages( int id, char** next )
 *   int   dndGetBonusSpellsPerDay( int relevantAbility, int spellLevel )
 *   char* dndGetClassAbbr( int id )
 *   int   dndGetClassAttackBonus( int id, int level )
 *   int   dndGetClassAttacksPerRound( int baseAttack )
 *   int   dndGetClassHitDie( int id )
 *   int   dndGetClassMultipleAttackBonus( int baseAttack, int which )
 *   char* dndGetClassName( int id )
 *   int   dndGetClassType( int id )
 *   char* dndGetClassTypeName( int id )
 *   char* dndGetDomainName( int id )
 *   char* dndGetFeatName( int id )
 *   int   dndGetFeatPrerequisite( int id, int* type, int* data1, int* data2, char** next )
 *   int   dndGetForbiddenAlignmentsForDomain( int id )
 *   int   dndGetFortitudeSave( int classType, int level )
 *   int   dndGetRelativeWeaponSize( int raceid, int weapon )
 *   int   dndGetGivenLanguages( int id, char** next )
 *   char* dndGetLanguageName( int id )
 *   int   dndGetMonkAttacksPerRound( int baseAttack )
 *   int   dndGetMonkMultipleAttackBonus( int baseAttack, int which )
 *   int   dndGetMonkSpeedForRace( int raceid, int level )
 *   int   dndGetNPCGearValue( int level )
 *   int   dndGetRaceAlignment( int race )
 *   int   dndGetRaceCR( int id )
 *   int   dndGetRaceExtraHitDice( int race, int* count, int* type )
 *   char* dndGetRaceName( int id )
 *   int   dndGetRaceSize( int id )
 *   int   dndGetRaceSpeed( int id )
 *   int   dndGetRaceBonus( int id, int gender, int type, int data )
 *   int   dndGetRaceBonusOfType( int race, int gender, int type, int* data, int* bonus, char** next )
 *   int   dndGetRacePreferredClass( int race );
 *   int   dndGetRacialHeightWeight( int race, int gender, DNDRACIALHEIGHTWEIGHT* data )
 *   int   dndGetReflexSave( int classType, int level )
 *   char* dndGetSchoolOfMagicName( int id )
 *   int   dndGetSizeACMod( int id )
 *   int   dndGetSizeHideMod( int id )
 *   char* dndGetSizeName( int id )
 *   int   dndGetSkillAbility( int skill )
 *   int   dndGetSkillBonusForClass( int classType )
 *   char* dndGetSkillName( int skill )
 *   int   dndGetSkillType( int classType, int skill )
 *   int   dndGetSpellLevel( int classid, int spellid )
 *   char* dndGetSpellName( int id )
 *   int   dndGetSpellSchool( int id )
 *   int   dndGetSpellOfLevel( int classid, int level, char** next )
 *   int   dndGetSpellsKnown( int classid, int classLevel, int spellLevel )
 *   int   dndGetSpellsPerDay( int classid, int classLevel, int spellLevel )
 *   int   dndGetWeaponCost( int id )
 *   char* dndGetWeaponName( int id )
 *   int   dndGetWeaponSize( int id )
 *   int   dndGetWeaponType( int id )
 *   int   dndGetWillSave( int classType, int level )
 *
 * ---------------------------------------------------------------------- */

#ifndef __DNDUTIL_H__
#define __DNDUTIL_H__

/* ---------------------------------------------------------------------- *
 * Dependencies
 * ---------------------------------------------------------------------- */

#include "dndconst.h"

/* ---------------------------------------------------------------------- *
 * Constant definitions
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Type definitions
 * ---------------------------------------------------------------------- */

typedef struct __dndracialheightweight__ DNDRACIALHEIGHTWEIGHT;

/* ---------------------------------------------------------------------- *
 * Structure definitions
 * ---------------------------------------------------------------------- */

struct __dndracialheightweight__ {
  int baseHeight_Feet;
  int baseHeight_Inches;
  int heightModDieCount;
  int heightModDie;
  int baseWeight;
  int weightModDieCount;
  int weightModDie;
};

/* ---------------------------------------------------------------------- *
 * Functions
 * ---------------------------------------------------------------------- */

#ifdef __cplusplus
extern "C" {
#endif

/* ---------------------------------------------------------------------- *
 * dndGetClassName( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           class's name, or NULL if an unknown class was specified.
 * ---------------------------------------------------------------------- */

char* dndGetClassName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetClassAbbr( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the 3 character abbreviation for
 *           the given class.
 * ---------------------------------------------------------------------- */

char* dndGetClassAbbr( int id );

/* ---------------------------------------------------------------------- *
 * dndGetClassType( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   int - the id of the class type that the class is (player, npc, or
 *         prestige), or 0 if the id is not known.
 * ---------------------------------------------------------------------- */

int dndGetClassType( int id );

/* ---------------------------------------------------------------------- *
 * dndGetClassHitDie( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   int - the number of sides for the die used for calculating the hit
 *         points for a character of the given class.
 * ---------------------------------------------------------------------- */

int dndGetClassHitDie( int id );

/* ---------------------------------------------------------------------- *
 * dndClassHasBonusFeatAtFirstLevel( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   boolean - 1 (true) or 0 (false)
 * ---------------------------------------------------------------------- */

int dndClassHasBonusFeatAtFirstLevel( int id );

/* ---------------------------------------------------------------------- *
 * dndClassBonusFeatEveryXLevels( int id )
 *
 * INPUT:
 *   id (int) - one of the pc, npc, or prestige class constants.
 *
 * OUTPUT:
 *   boolean - the number of levels that, once a character of the given
 *             class has attained, he gains a bonus feat.  This will return
 *             zero if the class has no bonus feats.
 * ---------------------------------------------------------------------- */

int dndClassBonusFeatEveryXLevels( int id );

/* ---------------------------------------------------------------------- *
 * dndGetClassTypeName( int id )
 *
 * INPUT:
 *   id (int) - one of the class type constants (player, prestige, or
 *              nonplayer)
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           class type's name, or NULL if an unknown type was specified.
 * ---------------------------------------------------------------------- */

char* dndGetClassTypeName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetClassAttackBonus( int id, int level )
 *
 * INPUT:
 *   id (int) - one of the class type constants (player, prestige, or
 *              nonplayer)
 *   level (int) - a number from 1 to 20, inclusive.
 *
 * OUTPUT:
 *   int - the base attack bonus for the given class at the given level.
 * ---------------------------------------------------------------------- */

int dndGetClassAttackBonus( int id, int level );

/* ---------------------------------------------------------------------- *
 * dndGetClassAttacksPerRound( int baseAttack )
 *
 * INPUT:
 *    baseAttack (int) - the base attack bonus
 *
 * OUTPUT:
 *   int - the number of attacks granted per round.
 * ---------------------------------------------------------------------- */

int dndGetClassAttacksPerRound( int baseAttack );

/* ---------------------------------------------------------------------- *
 * dndGetMonkAttacksPerRound( int baseAttack )
 *
 * INPUT:
 *    baseAttack (int) - the base attack bonus
 *
 * OUTPUT:
 *   int - the number of attacks granted per round, for monks with the
 *         given base attack.
 * ---------------------------------------------------------------------- */

int dndGetMonkAttacksPerRound( int baseAttack );

/* ---------------------------------------------------------------------- *
 * dndGetClassMultipleAttackBonus( int baseAttack, int which )
 *
 * INPUT:
 *    baseAttack (int) - the base attack bonus
 *    which (int) - which multiple attack bonus to return (1,2,3,4)
 *
 * OUTPUT:
 *   int - the bonus of the given attack
 * ---------------------------------------------------------------------- */

int dndGetClassMultipleAttackBonus( int baseAttack, int which );

/* ---------------------------------------------------------------------- *
 * dndGetMonkMultipleAttackBonus( int baseAttack, int which )
 *
 * INPUT:
 *    baseAttack (int) - the base attack bonus
 *    which (int) - which multiple attack bonus to return (1,2,3,4)
 *
 * OUTPUT:
 *   int - the bonus of the given attack for a monk with the given
 *         base attack bonus.
 * ---------------------------------------------------------------------- */

int dndGetMonkMultipleAttackBonus( int baseAttack, int which );

/* ---------------------------------------------------------------------- *
 * dndGetAlignmentText( int alignment )
 *
 * INPUT:
 *   alignment (int) - a valid combination of the alignment constants
 *                     (lawful good, lawful neutral, lawful evil, netural
 *                     good, true neutral, neutral evil, chaotic good,
 *                     chaotic neutral, or chaotic evil).
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           alignment, or NULL if an unknown alignment was specified.
 * ---------------------------------------------------------------------- */

char* dndGetAlignmentText( int alignment );

/* ---------------------------------------------------------------------- *
 * dndGetAlignmentAbbr( int alignment )
 *
 * INPUT:
 *   alignment (int) - a valid combination of the alignment constants
 *                     (lawful good, lawful neutral, lawful evil, netural
 *                     good, true neutral, neutral evil, chaotic good,
 *                     chaotic neutral, or chaotic evil).
 *
 * OUTPUT:
 *   char* - a static buffer containing the one or two letter abbreviation
 *           for the specified alignment, or NULL if an unknown alignment
 *           was specified.
 * ---------------------------------------------------------------------- */

char* dndGetAlignmentAbbr( int alignment );

/* ---------------------------------------------------------------------- *
 * dndGetSkillName( int skill )
 *
 * INPUT:
 *   skill (int) - one of the sk-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           skill, or NULL if an unknown skill was specified.
 * ---------------------------------------------------------------------- */

char* dndGetSkillName( int skill );

/* ---------------------------------------------------------------------- *
 * dndGetSkillAbility( int skill )
 *
 * INPUT:
 *   skill (int) - one of the sk-- constants.
 *
 * OUTPUT:
 *   int - one of the ab--- constants that indicates the ability associated
 *         with the given skill.
 * ---------------------------------------------------------------------- */

int dndGetSkillAbility( int skill );

/* ---------------------------------------------------------------------- *
 * dndGetSkillType( int classType, int skill )
 *
 * INPUT:
 *   classType (int) - one of the pc---, npc---, or prc--- constants.
 *   skill (int) - one of the sk-- constants.
 *
 * OUTPUT:
 *   int - one of the skt--- constants that indicates the the skill type
 *         of the given skill for the given class
 * ---------------------------------------------------------------------- */

int dndGetSkillType( int classType, int skill );

/* ---------------------------------------------------------------------- *
 * dndGetSkillBonusForClass( int classType )
 *
 * INPUT:
 *   classType (int) - one of the pc---, npc---, or prc--- constants.
 *
 * OUTPUT:
 *   int - the skill bonus for a given class.
 * ---------------------------------------------------------------------- */

int dndGetSkillBonusForClass( int classType );

/* ---------------------------------------------------------------------- *
 * dndGetAbilityName( int ability )
 *
 * INPUT:
 *   ability (int) - one of the ab-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           ability, or NULL if an unknown ability was specified.
 * ---------------------------------------------------------------------- */

char* dndGetAbilityName( int ability );

/* ---------------------------------------------------------------------- *
 * dndGetAbilityBonus( int abilityScore )
 *
 * INPUT:
 *   abilityScore (int) - the ability score to calculate the bonus for
 *
 * OUTPUT:
 *   int - the ability bonus
 * ---------------------------------------------------------------------- */

int dndGetAbilityBonus( int abilityScore );

/* ---------------------------------------------------------------------- *
 * dndGetRaceName( int id )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           race, or NULL if an unknown race was specified.
 * ---------------------------------------------------------------------- */

char* dndGetRaceName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetRaceSize( int id )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *
 * OUTPUT:
 *   int - one of the sz--- constants.
 * ---------------------------------------------------------------------- */

int dndGetRaceSize( int id );

/* ---------------------------------------------------------------------- *
 * dndGetRaceSpeed( int id )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *
 * OUTPUT:
 *   int - the base speed of the given race.
 * ---------------------------------------------------------------------- */

int dndGetRaceSpeed( int id );

/* ---------------------------------------------------------------------- *
 * dndGetRaceCR( int id )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *
 * OUTPUT:
 *   int - the challenge rating (CR) for an average specimen of the given
 *         race.  A CR of 1 here actually represents a CR of 1 or less.
 * ---------------------------------------------------------------------- */

int dndGetRaceCR( int id );

/* ---------------------------------------------------------------------- *
 * dndGetRaceBonus( int id, int gender, int type, int data )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *   gender (int) - on of the g--- constants.
 *   type (int) - one of the rbt-- constants.
 *   data (int) - data corresponding to the 'type' field.
 *
 * OUTPUT:
 *   int - the bonus associated with the given type for the given race.
 * ---------------------------------------------------------------------- */

int dndGetRaceBonus( int id, int gender, int type, int data );

/* ---------------------------------------------------------------------- *
 * dndGetFeatName( int id )
 *
 * INPUT:
 *   id (int) - one of the ft-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the text that describes the given
 *           feat, or NULL if an unknown feat was specified.
 * ---------------------------------------------------------------------- */

char* dndGetFeatName( int id );

/* ---------------------------------------------------------------------- *
 * dndFeatIsReusable( int id )
 *
 * INPUT:
 *   id (int) - one of the ft-- constants.
 *
 * OUTPUT:
 *   boolean - 1 (true) or 0 (false), indicating whether or not the given
 *             feat may be taken more than once.
 * ---------------------------------------------------------------------- */

int dndFeatIsReusable( int id );

/* ---------------------------------------------------------------------- *
 * dndGetFeatPrerequisite( int id, int* type, int *data1, int *data2, char** next )
 *
 * INPUT:
 *   id (int) - one of the ft-- constants.
 *   type (int*) - will contain the type of the prerequisite
 *   data1 (int*) - will contain data regarding the prerequisite
 *   data2 (int*) - will contain data regarding the prerequisite
 *   next (char**) - a place holder
 *
 * OUTPUT:
 *   boolean - 1 (true) or 0 (false), indicating whether or not the data
 *             returned is valid.  If not, then the end of the prerequisite
 *             list has been reached.
 *
 * The first time dndGetFeatPrerequisite is called, 'id' must indicate a 
 * valid feat identifier.  On subsequent calls, id must be 0 and 'next' will
 * be used to maintain positional information.
 * ---------------------------------------------------------------------- */

int dndGetFeatPrerequisite( int id, int* type, int* data1, int* data2, char** next );

/* ---------------------------------------------------------------------- *
 * dndGetWeaponName( int id )
 *
 * INPUT:
 *   id (int) - one of the wp-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the indicated weapon,
 *           or NULL if the weapon is not known.
 * ---------------------------------------------------------------------- */

char* dndGetWeaponName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetWeaponSize( int id )
 *
 * INPUT:
 *   id (int) - one of the wp-- constants.
 *
 * OUTPUT:
 *   int - one of the sz--- constants, or 0 if the weapon is not known.
 * ---------------------------------------------------------------------- */

int dndGetWeaponSize( int id );

/* ---------------------------------------------------------------------- *
 * dndGetWeaponType( int id )
 *
 * INPUT:
 *   id (int) - one of the wp-- constants.
 *
 * OUTPUT:
 *   int - one or more of the wt--- constants OR'd together, or 0 if the 
 *         weapon is not known.
 * ---------------------------------------------------------------------- */

int dndGetWeaponType( int id );

/* ---------------------------------------------------------------------- *
 * dndGetWeaponCost( int id )
 *
 * INPUT:
 *   id (int) - one of the wp-- constants.
 *
 * OUTPUT:
 *   int - the cost of the weapon in copper pieces (gp x 100).
 * ---------------------------------------------------------------------- */

int dndGetWeaponCost( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSchoolOfMagicName( int id )
 *
 * INPUT:
 *   id (int) - one of the ss-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the given school of
 *           magic.
 * ---------------------------------------------------------------------- */

char* dndGetSchoolOfMagicName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSizeName( int id )
 *
 * INPUT:
 *   id (int) - one of the sz-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the given size, or
 *           NULL if the size was not found.
 * ---------------------------------------------------------------------- */

char* dndGetSizeName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSizeACMod( int id )
 *
 * INPUT:
 *   id (int) - one of the sz-- constants.
 *
 * OUTPUT:
 *   int - the armor class modifier for the given size.
 * ---------------------------------------------------------------------- */

int dndGetSizeACMod( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSizeHideMod( int id )
 *
 * INPUT:
 *   id (int) - one of the sz-- constants.
 *
 * OUTPUT:
 *   int - the hide skill modifier for the given size.
 * ---------------------------------------------------------------------- */

int dndGetSizeHideMod( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSpellName( int id )
 *
 * INPUT:
 *   id (int) - one of the sp-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the spell, or NULL if
 *           the spell is not known.
 * ---------------------------------------------------------------------- */

char* dndGetSpellName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSpellSchool( int id )
 *
 * INPUT:
 *   id (int) - one of the sp-- constants.
 *
 * OUTPUT:
 *   int - one of ss--- constants.
 * ---------------------------------------------------------------------- */

int dndGetSpellSchool( int id );

/* ---------------------------------------------------------------------- *
 * dndGetSpellLevel( int classid, int spellid )
 *
 * INPUT:
 *   classid (int) - one of the pc--, npc--, or prc-- constants.
 *   spellid (int) - one of the sp-- constants.
 *
 * OUTPUT:
 *   int - the level that the spell is for the given class, or -1 if the
 *         spell is unusuable by that class.
 * ---------------------------------------------------------------------- */

int dndGetSpellLevel( int classid, int spellid );

/* ---------------------------------------------------------------------- *
 * dndGetSpellOfLevel( int classid, int level, char** next )
 *
 * INPUT:
 *   classid (int) - one of the pc--, npc--, or prc-- constants.
 *   level (int) - the level of the spell desired
 *   next (char**) - a placeholder
 *
 * OUTPUT:
 *   int - one of the sp--- constants, or 0 (see below).
 *
 * If classid is not zero, the first spell of the given level for the given
 * class (if any) is returned.  If classid is NOT zero, another spell for
 * the given level is returned for each invocation.  When there are no
 * more spells for the given level (or if there were none to begin with)
 * 0 is returned.
 * ---------------------------------------------------------------------- */

int dndGetSpellOfLevel( int classid, int level, char** next );

/* ---------------------------------------------------------------------- *
 * dndGetSpellsPerDay( int classid, int classLevel, int spellLevel )
 *
 * INPUT:
 *   classid (int) - one of the pc--, npc--, or prc-- constants.
 *   classLevel (int) - from 1 to 20, inclusive
 *   spellLevel (int) - from 0 to 9, inclusive
 *
 * OUTPUT:
 *   int - the number of spells usable by that class per day, or 0 if 
 *         they need an ability bonus to be able to cast any spells of
 *         that level, or -1 if they cannot cast any spells of that level.
 * ---------------------------------------------------------------------- */

int dndGetSpellsPerDay( int classid, int classLevel, int spellLevel );

/* ---------------------------------------------------------------------- *
 * dndGetSpellsKnown( int classid, int classLevel, int spellLevel )
 *
 * INPUT:
 *   classid (int) - one of the pc--, npc--, or prc-- constants.
 *   classLevel (int) - from 1 to 20, inclusive
 *   spellLevel (int) - from 0 to 9, inclusive
 *
 * OUTPUT:
 *   int - the number of spells known by that class of the given level, or
 *         -1 if they cannot know any spells of that level, or 0 if they
 *         may know as many spells of that level as they want, provided
 *         they can cast spells of that level.
 * ---------------------------------------------------------------------- */

int dndGetSpellsKnown( int classid, int classLevel, int spellLevel );

/* ---------------------------------------------------------------------- *
 * dndGetBonusSpellsPerDay( int relevantAbility, int spellLevel )
 *
 * INPUT:
 *   relevantAbility (int) - the value of the relevant ability score
 *   spellLevel (int) - from 0 to 9, inclusive
 *
 * OUTPUT:
 *   int - the number of bonus spells that may be cast per day given the
 *         specified ability score and spell level, or -1 if the character
 *         would be unable to cast ANY spells, given the specified ability
 *         score.
 * ---------------------------------------------------------------------- */

int dndGetBonusSpellsPerDay( int relevantAbility, int spellLevel );

/* ---------------------------------------------------------------------- *
 * dndGetDomainName( int id )
 *
 * INPUT:
 *   id (int) - one of the dm-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the domain, or NULL if
 *           the domain is not known.
 * ---------------------------------------------------------------------- */

char* dndGetDomainName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetForbiddenAlignmentsForDomain( int id )
 *
 * INPUT:
 *   id (int) - one of the dm-- constants.
 *
 * OUTPUT:
 *   int - a bit field containing zero or more al--- constants or'ed
 *         together, representing the set of alignments for which this
 *         domain is forbidden.
 * ---------------------------------------------------------------------- */

int dndGetForbiddenAlignmentsForDomain( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorName( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the given armor, or
 *           NULL if the armor is not known.
 * ---------------------------------------------------------------------- */

char* dndGetArmorName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorType( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - one of the at-- constants.
 * ---------------------------------------------------------------------- */

int dndGetArmorType( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorCost( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - the cost of the given armor in copper pieces (gp x 100).
 * ---------------------------------------------------------------------- */

int dndGetArmorCost( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorACBonus( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - the armor class bonus of the given armor.
 * ---------------------------------------------------------------------- */

int dndGetArmorACBonus( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorMaxDexterity( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - the maximum dexterity bonus available while using this armor.
 * ---------------------------------------------------------------------- */

int dndGetArmorMaxDexterity( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorCheckPenalty( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - the penalty to certain skill checks while wearing this armor.
 * ---------------------------------------------------------------------- */

int dndGetArmorCheckPenalty( int id );

/* ---------------------------------------------------------------------- *
 * dndGetArmorArcaneSpellFailure( int id )
 *
 * INPUT:
 *   id (int) - one of the ar-- constants.
 *
 * OUTPUT:
 *   int - the chance in 100 (d%) of an arcane spell failing while the
 *         caster is wearing the given armor.
 * ---------------------------------------------------------------------- */

int dndGetArmorArcaneSpellFailure( int id );

/* ---------------------------------------------------------------------- *
 * dndGetFortitudeSave( int classType, int level )
 *
 * INPUT:
 *   classType (int) - one of the pc--, npc--, or prc-- constants.
 *   level (int) - from 1 to 20, inclusive
 *
 * OUTPUT:
 *   int - the base fortitude saving throw for the given class at the
 *         given level.
 * ---------------------------------------------------------------------- */

int dndGetFortitudeSave( int classType, int level );

/* ---------------------------------------------------------------------- *
 * dndGetReflexSave( int classType, int level )
 *
 * INPUT:
 *   classType (int) - one of the pc--, npc--, or prc-- constants.
 *   level (int) - from 1 to 20, inclusive
 *
 * OUTPUT:
 *   int - the base reflex saving throw for the given class at the
 *         given level.
 * ---------------------------------------------------------------------- */

int dndGetReflexSave( int classType, int level );

/* ---------------------------------------------------------------------- *
 * dndGetWillSave( int classType, int level )
 *
 * INPUT:
 *   classType (int) - one of the pc--, npc--, or prc-- constants.
 *   level (int) - from 1 to 20, inclusive
 *
 * OUTPUT:
 *   int - the base will saving throw for the given class at the
 *         given level.
 * ---------------------------------------------------------------------- */

int dndGetWillSave( int classType, int level );

/* ---------------------------------------------------------------------- *
 * dndGetNPCGearValue( int level )
 *
 * INPUT:
 *   level (int) - from 1 to 20, inclusive
 *
 * OUTPUT:
 *   int - the value of the gear of an NPC of the given character level,
 *         in gold pieces.
 * ---------------------------------------------------------------------- */

int dndGetNPCGearValue( int level );

/* ---------------------------------------------------------------------- *
 * dndGetRacialHeightWeight( int race, int gender, DNDRACIALHEIGHTWEIGHT* data )
 *
 * INPUT:
 *   race (int) - one of the rc--- constants
 *   gender (int) - one of the g--- constants
 *   data (DNDRACIALHEIGHTWEIGHT*) - where to put the data
 *
 * OUTPUT:
 *   boolean - 1 if the race exists, 0 if it does not.
 *
 * ---------------------------------------------------------------------- */

int dndGetRacialHeightWeight( int race, int gender, DNDRACIALHEIGHTWEIGHT* data );

/* ---------------------------------------------------------------------- *
 * dndGetRaceAlignment( int race )
 *
 * INPUT:
 *   race (int) - one of the rc--- constants
 *
 * OUTPUT:
 *   int - 0, or a combination of the al--- constants.
 *
 * ---------------------------------------------------------------------- */

int dndGetRaceAlignment( int race );

/* ---------------------------------------------------------------------- *
 * dndGetRacePreferredClass( int race )
 *
 * INPUT:
 *   race (int) - one of the rc--- constants
 *
 * OUTPUT:
 *   int - 0, or one of the pc---, npc---, or prc--- constants.
 *
 * ---------------------------------------------------------------------- */

int dndGetRacePreferredClass( int race );

/* ---------------------------------------------------------------------- *
 * dndGetRaceExtraHitDice( int race, int* count, int* type )
 *
 * INPUT:
 *   race (int) - one of the rc--- constants
 *   count (int*) - will contain the number of extra hit dice to use
 *   type (int*) - will contain the type of extra hit dice to use
 *
 * OUTPUT:
 *   boolean - 1 if the race has extra hit dice, 0 otherwise.
 *
 * ---------------------------------------------------------------------- */

int dndGetRaceExtraHitDice( int race, int* count, int* type );

/* ---------------------------------------------------------------------- *
 * dndGetRaceBonusOfType( int race, int gender, int type, int* data, int* bonus, char** next )
 *
 * INPUT:
 *   id (int) - one of the rc-- constants.
 *   gender (int) - on of the g--- constants.
 *   type (int) - one of the rbt-- constants.
 *   data (int) - where the data corresponding to the 'type' field will be
 *                placed.
 *   bonus (int*) - where the requested bonus will be placed.
 *   next (char**) - a place holder for iteration
 *
 * OUTPUT:
 *   int - 0 if there are not more bonuses of the given type, 1 otherwise.
 *
 * ---------------------------------------------------------------------- */

int dndGetRaceBonusOfType( int race, int gender, int type, int* data, int* bonus, char** next );

/* ---------------------------------------------------------------------- *
 * dndGetLanguageName( int id )
 *
 * INPUT:
 *   id (int) - one of the ln--- constants
 *
 * OUTPUT:
 *   char* - a static buffer containing the name of the indicated language
 *           or NULL if the language is unknown.
 * ---------------------------------------------------------------------- */

char* dndGetLanguageName( int id );

/* ---------------------------------------------------------------------- *
 * dndGetGivenLanguages( int id, char** next )
 *
 * INPUT:
 *   id (int) - one of the rc--- constants
 *   next (char**) - a placeholder 
 *
 * OUTPUT:
 *   int - the next language in the series, or 0 if there are no more
 *         languages given to the indicated race.
 * ---------------------------------------------------------------------- */

int dndGetGivenLanguages( int id, char** next );

/* ---------------------------------------------------------------------- *
 * dndGetBonusLanguages( int id, char** next )
 *
 * INPUT:
 *   id (int) - one of the rc--- constants
 *   next (char**) - a placeholder 
 *
 * OUTPUT:
 *   int - the next language in the series, or 0 if there are no more
 *         languages that the indicated race gains as a bonus.
 * ---------------------------------------------------------------------- */

int dndGetBonusLanguages( int id, char** next );

/* ---------------------------------------------------------------------- *
 * dndGetRelativeWeaponSize( int raceid, int weapon )
 *
 * INPUT:
 *   raceid (int) - one of the rc--- constants
 *   weapon (int) - one of the wp--- constants
 *
 * OUTPUT:
 *   int - one of the wt--- constants (wtLIGHT, wtONEHANDED, wtTWOHANDED)
 * ---------------------------------------------------------------------- */

int dndGetRelativeWeaponSize( int raceid, int weapon );

/* ---------------------------------------------------------------------- *
 * dndGetMonkSpeedForRace( int raceid, int level )
 *
 * INPUT:
 *   raceid (int) - one of the rc--- constants
 *   level (int) - from 1 to 20, inclusive
 *
 * OUTPUT:
 *   int - the base speed of the monk
 * ---------------------------------------------------------------------- */

int dndGetMonkSpeedForRace( int raceid, int level );

#ifdef __cplusplus
}
#endif

#endif /* __DNDUTIL_H__ */
