/* ---------------------------------------------------------------------- *
 * dndutil.c
 *
 * by Jamis Buck (jgb3@email.byu.edu)
 *
 * Utility functions for the Dungeons & Dragons(tm) API.  This file is in
 * the public domain.
 * ---------------------------------------------------------------------- */

/* ---------------------------------------------------------------------- *
 * Dependencies
 * ---------------------------------------------------------------------- */

#include <string.h>

#include "dndconst.h"
#include "dndutil.h"

/* ---------------------------------------------------------------------- *
 * Constants
 * ---------------------------------------------------------------------- */

#if !defined(NULL)
#define NULL ( 0 )
#endif

/* ---------------------------------------------------------------------- *
 * Data types
 * ---------------------------------------------------------------------- */

typedef struct __skillsforclass__ SKILLSFORCLASS;
typedef struct __featprereq__     FEATPREREQ;
typedef struct __spellsforclass__ SPELLSFORCLASS;
typedef struct __racialbonus__    RACIALBONUS;

typedef int SPELLMATRIX[20][10];

struct __spellsforclass__ {
  int spell;
  int level;
};

struct __featprereq__ {
  int preReqType;
  int data1;
  int data2;
};

struct __skillsforclass__ {
  int skill;
  int classSkill;
};

struct __racialbonus__  {
  int type;
  int data;
  int bonus;
};

/* ---------------------------------------------------------------------- *
 * Data definitions
 * ---------------------------------------------------------------------- */

/* class and cross-class skill designations */

static SKILLSFORCLASS barbarianSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS bardSkills[] = {
  { skALCHEMY,            1 },
  { skAPPRAISE,           1 },
  { skBALANCE,            1 },
  { skBLUFF,              1 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDECIPHERSCRIPT,     1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           1 },
  { skESCAPEARTIST,       1 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  1 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          1 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           0 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         1 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        1 },
  { skSPEAKLANGUAGE,      1 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             1 },
  { skUSEMAGICDEVICE,     1 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS clericSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS druidSkills[] = {
  { skALCHEMY,            0 },
  { skANIMALEMPATHY,      1 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS fighterSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS monkSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            1 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       1 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           0 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             1 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS paladinSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS rangerSkills[] = {
  { skALCHEMY,            0 },
  { skANIMALEMPATHY,      1 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               1 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               1 },
  { skSEARCH,             1 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS rogueSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           1 },
  { skBALANCE,            1 },
  { skBLUFF,              1 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDECIPHERSCRIPT,     1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      1 },
  { skDISGUISE,           1 },
  { skESCAPEARTIST,       1 },
  { skFORGERY,            1 },
  { skGATHERINFORMATION,  1 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           1 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           1 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         1 },
  { skPROFESSION,         1 },
  { skREADLIPS,           1 },
  { skRIDE,               0 },
  { skSEARCH,             1 },
  { skSENSEMOTIVE,        1 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               1 },
  { skTUMBLE,             1 },
  { skUSEMAGICDEVICE,     1 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS sorcererSkills[] = {
  { skALCHEMY,            1 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS wizardSkills[] = {
  { skALCHEMY,            1 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          1 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS arcaneArcherSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS assassinSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            1 },
  { skBLUFF,              1 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDECIPHERSCRIPT,     1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      1 },
  { skDISGUISE,           1 },
  { skESCAPEARTIST,       1 },
  { skFORGERY,            1 },
  { skGATHERINFORMATION,  1 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           1 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    1 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           1 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         1 },
  { skPROFESSION,         0 },
  { skREADLIPS,           1 },
  { skRIDE,               0 },
  { skSEARCH,             1 },
  { skSENSEMOTIVE,        1 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               1 },
  { skTUMBLE,             1 },
  { skUSEMAGICDEVICE,     1 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS blackguardSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS dwarvenDefenderSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               0 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        1 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS loremasterSkills[] = {
  { skALCHEMY,            1 },
  { skAPPRAISE,           1 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              0 },
  { skDECIPHERSCRIPT,     1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  1 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          1 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      1 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEMAGICDEVICE,     1 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS shadowdancerSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            1 },
  { skBLUFF,              1 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              0 },
  { skDECIPHERSCRIPT,     1 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           1 },
  { skESCAPEARTIST,       1 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               1 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       1 },
  { skOPENLOCK,           0 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         1 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSEARCH,             1 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               0 },
  { skTUMBLE,             1 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS adeptSkills[] = {
  { skALCHEMY,            1 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      1 },
  { skCRAFT,              1 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               1 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          1 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               0 },
  { skSCRY,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         1 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS aristocratSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           1 },
  { skBALANCE,            0 },
  { skBLUFF,              1 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              0 },
  { skDIPLOMACY,          1 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           1 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            1 },
  { skGATHERINFORMATION,  1 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           1 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   1 },    
  { skKNOWLEDGE_RELIGION, 1 },
  { skKNOWLEDGE_NATURE,   1 },
  { skKNOWLEDGE,          1 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            1 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skREADLIPS,           1 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        1 },
  { skSPEAKLANGUAGE,      1 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     1 },
  { 0,                    0 }
};


static SKILLSFORCLASS commonerSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              0 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             1 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         1 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               1 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            1 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS expertSkills[] = {
  { skALCHEMY,            0 },
  { skANIMALEMPATHY,      0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              0 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              0 },
  { skDECIPHERSCRIPT,     0 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       0 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         0 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               0 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               0 },
  { skSCRY,               0 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               0 },
  { skTUMBLE,             0 },
  { skUSEMAGICDEVICE,     0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SKILLSFORCLASS warriorSkills[] = {
  { skALCHEMY,            0 },
  { skAPPRAISE,           0 },
  { skBALANCE,            0 },
  { skBLUFF,              0 },
  { skCLIMB,              1 },
  { skCONCENTRATION,      0 },
  { skCRAFT,              0 },
  { skDIPLOMACY,          0 },
  { skDISABLEDEVICE,      0 },
  { skDISGUISE,           0 },
  { skESCAPEARTIST,       0 },
  { skFORGERY,            0 },
  { skGATHERINFORMATION,  0 },
  { skHANDLEANIMAL,       1 },
  { skHEAL,               0 },
  { skHIDE,               0 },
  { skINNUENDO,           0 },
  { skINTIMIDATE,         1 },
  { skINTUITDIRECTION,    0 },
  { skJUMP,               1 },
  { skKNOWLEDGE_ARCANA,   0 },    
  { skKNOWLEDGE_RELIGION, 0 },
  { skKNOWLEDGE_NATURE,   0 },
  { skKNOWLEDGE,          0 },
  { skLISTEN,             0 },
  { skMOVESILENTLY,       0 },
  { skOPENLOCK,           0 },
  { skPERFORM,            0 },
  { skPICKPOCKET,         0 },
  { skPROFESSION,         0 },
  { skRIDE,               1 },
  { skSEARCH,             0 },
  { skSENSEMOTIVE,        0 },
  { skSPEAKLANGUAGE,      0 },
  { skSPELLCRAFT,         0 },
  { skSPOT,               0 },
  { skSWIM,               1 },
  { skTUMBLE,             0 },
  { skUSEROPE,            0 },
  { skWILDERNESSLORE,     0 },
  { 0,                    0 }
};


static SPELLSFORCLASS s_Adept[] = {
  { spAID,                                   2 },
  { spANIMALTRANCE,                          2 },
  { spANIMATEDEAD,                           3 },
  { spBESTOWCURSE,                           3 },
  { spBLESS,                                 1 },
  { spBREAKENCHANTMENT,                      5 },
  { spBULLSSTRENGTH,                         2 },
  { spBURNINGHANDS,                          1 },
  { spCATSGRACE,                             2 },
  { spCAUSEFEAR,                             1 },
  { spCOMMAND,                               1 },
  { spCOMMUNE,                               5 },
  { spCOMPREHENDLANGUAGES,                   1 },
  { spCONTAGION,                             3 },
  { spCONTINUALFLAME,                        3 },
  { spCREATEWATER,                           0 },
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMINORWOUNDS,                       0 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spDARKNESS,                              2 },
  { spDAYLIGHT,                              3 },
  { spDEEPERDARKNESS,                        3 },
  { spDELAYPOISON,                           2 },
  { spDETECTCHAOS,                           1 },
  { spDETECTEVIL,                            1 },
  { spDETECTGOOD,                            1 },
  { spDETECTLAW,                             1 },
  { spDETECTMAGIC,                           0 },
  { spENDURANCE,                             2 },
  { spENDUREELEMENTS,                        1 },
  { spGHOSTSOUND,                            0 },
  { spGUIDANCE,                              0 },
  { spHEAL,                                  5 },
  { spINVISIBILITY,                          2 },
  { spLIGHT,                                 0 },
  { spLIGHTNINGBOLT,                         3 },
  { spMAJORCREATION,                         5 },
  { spMENDING,                               0 },
  { spMINORCREATION,                         4 },
  { spMIRRORIMAGE,                           2 },
  { spNEUTRALIZEPOISON,                      3 },
  { spOBSCURINGMIST,                         1 },
  { spPOLYMORPHOTHER,                        4 },
  { spPOLYMORPHSELF,                         4 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spPROTECTIONFROMLAW,                     1 },
  { spPURIFYFOODANDDRINK,                    0 },
  { spRAISEDEAD,                             5 },
  { spREADMAGIC,                             0 },
  { spREMOVECURSE,                           3 },
  { spRESISTELEMENTS,                        2 },
  { spRESTORATION,                           4 },
  { spSEEINVISIBILITY,                       2 },
  { spSLEEP,                                 1 },
  { spSTONESKIN,                             4 },
  { spTONGUES,                               3 },
  { spTRUESEEING,                            5 },
  { spWALLOFFIRE,                            4 },
  { spWALLOFSTONE,                           5 },
  { spWEB,                                   2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Air[] = {
  { spAIRWALK,                               4 },
  { spCHAINLIGHTNING,                        6 },
  { spCONTROLWEATHER,                        7 },
  { spCONTROLWINDS,                          5 },
  { spELEMENTALSWARM,                        9 },
  { spGASEOUSFORM,                           3 },
  { spOBSCURINGMIST,                         1 },
  { spWHIRLWIND,                             8 },
  { spWINDWALL,                              2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Animal[] = {
  { spANIMALSHAPES,                          7 },
  { spANTILIFESHELL,                         6 },
  { spCALMANIMALS,                           1 },
  { spCOMMUNEWITHNATURE,                     5 },
  { spCREEPINGDOOM,                          8 },
  { spDOMINATEANIMAL,                        3 },
  { spHOLDANIMAL,                            2 },
  { spREPELVERMIN,                           4 },
  { spSHAPECHANGE,                           9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Assassin[] = {
  { spALTERSELF,                             2 },
  { spCHANGESELF,                            1 },
  { spDARKNESS,                              2 },
  { spDEEPERDARKNESS,                        3 },
  { spDETECTPOISON,                          1 },
  { spDIMENSIONDOOR,                         4 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spGHOSTSOUND,                            1 },
  { spIMPROVEDINVISIBILITY,                  4 },
  { spINVISIBILITY,                          3 },
  { spMISDIRECTION,                          3 },
  { spNONDETECTION,                          3 },
  { spOBSCURINGMIST,                         1 },
  { spPASSWITHOUTTRACE,                      2 },
  { spPOISON,                                4 },
  { spSPIDERCLIMB,                           1 },
  { spUNDETECTABLEALIGNMENT,                 2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Bard[] = {
  { spALARM,                                 1 },
  { spANIMALTRANCE,                          2 },
  { spBESTOWCURSE,                           3 },
  { spBLINDNESSDEAFNESS,                     2 },
  { spBLINK,                                 3 },
  { spBLUR,                                  2 },
  { spBREAKENCHANTMENT,                      4 },
  { spBULLSSTRENGTH,                         2 },
  { spCATSGRACE,                             2 },
  { spCAUSEFEAR,                             1 },
  { spCHARMMONSTER,                          3 },
  { spCHARMPERSON,                           1 },
  { spCLAIRAUDIENCECLAIRVOYANCE,             3 },
  { spCONFUSION,                             3 },
  { spCONTACTOTHERPLANE,                     5 },
  { spCONTROLWATER,                          5 },
  { spCONTROLWEATHER,                        6 },
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spDANCINGLIGHTS,                         0 },
  { spDARKNESS,                              2 },
  { spDAYLIGHT,                              2 },
  { spDAZE,                                  0 },
  { spDELAYPOISON,                           2 },
  { spDETECTMAGIC,                           0 },
  { spDETECTSCRYING,                         4 },
  { spDETECTSECRETDOORS,                     1 },
  { spDETECTTHOUGHTS,                        2 },
  { spDIMENSIONDOOR,                         4 },
  { spDISMISSAL,                             4 },
  { spDISPELMAGIC,                           3 },
  { spDISPLACEMENT,                          3 },
  { spDOMINATEPERSON,                        4 },
  { spDREAM,                                 5 },
  { spEMOTION,                               3 },
  { spENTHRALL,                              2 },
  { spERASE,                                 1 },
  { spEXPEDITIOUSRETREAT,                    1 },
  { spEYEBITE,                               6 },
  { spFALSEVISION,                           5 },
  { spFEAR,                                  3 },
  { spFEATHERFALL,                           1 },
  { spFLARE,                                 0 },
  { spGASEOUSFORM,                           3 },
  { spGEASQUEST,                             6 },
  { spGHOSTSOUND,                            0 },
  { spGLITTERDUST,                           2 },
  { spGREASE,                                1 },
  { spGREATERDISPELLING,                     5 },
  { spGREATERMAGICWEAPON,                    3 },
  { spGREATERSCRYING,                        6 },
  { spGUSTOFWIND,                            3 },
  { spHALLUCINATORYTERRAIN,                  4 },
  { spHASTE,                                 3 },
  { spHEALINGCIRCLE,                         5 },
  { spHOLDMONSTER,                           4 },
  { spHOLDPERSON,                            2 },
  { spHYPNOTICPATTERN,                       2 },
  { spHYPNOTISM,                             1 },
  { spIDENTIFY,                              1 },
  { spILLUSORYSCRIPT,                        3 },
  { spIMPROVEDINVISIBILITY,                  4 },
  { spINVISIBILITY,                          2 },
  { spINVISIBILITYSPHERE,                    3 },
  { spKEENEDGE,                              3 },
  { spLEGENDLORE,                            4 },
  { spLEOMUNDSSECURESHELTER,                 4 },
  { spLEOMUNDSTINYHUT,                       3 },
  { spLESSERGEAS,                            3 },
  { spLEVITATE,                              2 },
  { spLIGHT,                                 0 },
  { spLOCATECREATURE,                        4 },
  { spLOCATEOBJECT,                          2 },
  { spMAGEARMOR,                             1 },
  { spMAGEHAND,                              0 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spMAGICMOUTH,                            2 },
  { spMAGICWEAPON,                           1 },
  { spMAJORIMAGE,                            3 },
  { spMASSHASTE,                             6 },
  { spMASSSUGGESTION,                        6 },
  { spMENDING,                               0 },
  { spMESSAGE,                               1 },
  { spMINDFOG,                               5 },
  { spMINORIMAGE,                            2 },
  { spMIRAGEARCANA,                          5 },
  { spMIRRORIMAGE,                           2 },
  { spMISDIRECTION,                          2 },
  { spMISLEAD,                               5 },
  { spMODIFYMEMORY,                          4 },
  { spNEUTRALIZEPOISON,                      4 },
  { spNIGHTMARE,                             5 },
  { spOBSCUREOBJECT,                         2 },
  { spOPENCLOSE,                             0 },
  { spPERMANENTIMAGE,                        6 },
  { spPERSISTENTIMAGE,                       5 },
  { spPHANTOMSTEED,                          3 },
  { spPLANESHIFT,                            6 },
  { spPRESTIDIGITATION,                      0 },
  { spPROGRAMMEDIMAGE,                       6 },
  { spPROJECTIMAGE,                          6 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spPROTECTIONFROMLAW,                     1 },
  { spPYROTECHNICS,                          2 },
  { spRAINBOWPATTERN,                        4 },
  { spREADMAGIC,                             0 },
  { spREMOVECURSE,                           3 },
  { spREMOVEDISEASE,                         3 },
  { spREPULSION,                             6 },
  { spRESISTANCE,                            0 },
  { spSCARE,                                 2 },
  { spSCRYING,                               3 },
  { spSCULPTSOUND,                           3 },
  { spSEEINVISIBILITY,                       2 },
  { spSEPIASNAKESIGIL,                       3 },
  { spSHATTER,                               2 },
  { spSHOUT,                                 4 },
  { spSILENCE,                               2 },
  { spSILENTIMAGE,                           1 },
  { spSLEEP,                                 1 },
  { spSLOW,                                  3 },
  { spSOUNDBURST,                            2 },
  { spSUGGESTION,                            2 },
  { spSUMMONMONSTERI,                        1 },
  { spSUMMONMONSTERII,                       2 },
  { spSUMMONMONSTERIII,                      3 },
  { spSUMMONMONSTERIV,                       4 },
  { spSUMMONMONSTERV,                        5 },
  { spSUMMONMONSTERVI,                       6 },
  { spSUMMONSWARM,                           2 },
  { spTASHASHIDEOUSLAUGHTER,                 2 },
  { spTONGUES,                               2 },
  { spUNDETECTABLEALIGNMENT,                 2 },
  { spUNSEENSERVANT,                         1 },
  { spVEIL,                                  6 },
  { spVENTRILOQUISM,                         1 },
  { spWHISPERINGWIND,                        2 },
  { spWINDWALL,                              3 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Blackguard[] = {
  { spBULLSSTRENGTH,                         2 },
  { spCAUSEFEAR,                             1 },
  { spCONTAGION,                             3 },
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spDARKNESS,                              2 },
  { spDEATHKNELL,                            2 },
  { spDEEPERDARKNESS,                        3 },
  { spDOOM,                                  1 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spINFLICTCRITICALWOUNDS,                 4 },
  { spINFLICTLIGHTWOUNDS,                    1 },
  { spINFLICTMODERATEWOUNDS,                 2 },
  { spINFLICTSERIOUSWOUNDS,                  3 },
  { spMAGICWEAPON,                           1 },
  { spPOISON,                                4 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spSHATTER,                               2 },
  { spSUMMONMONSTERI,                        1 },
  { spSUMMONMONSTERII,                       2 },
  { spSUMMONMONSTERIII,                      3 },
  { spSUMMONMONSTERIV,                       4 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Chaos[] = {
  { spANIMATEOBJECTS,                        6 },
  { spCHAOSHAMMER,                           4 },
  { spCLOAKOFCHAOS,                          8 },
  { spDISPELLAW,                             5 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spPROTECTIONFROMLAW,                     1 },
  { spSHATTER,                               2 },
  { spSUMMONMONSTERIX,                       9 },
  { spWORDOFCHAOS,                           7 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Cleric[] = {
  { spAID,                                   2 },
  { spAIRWALK,                               4 },
  { spANIMALMESSENGER,                       2 },
  { spANIMATEDEAD,                           3 },
  { spANIMATEOBJECTS,                        6 },
  { spANTILIFESHELL,                         6 },
  { spANTIMAGICFIELD,                        8 },
  { spASTRALPROJECTION,                      9 },
  { spATONEMENT,                             5 },
  { spAUGURY,                                2 },
  { spBANE,                                  1 },
  { spBANISHMENT,                            6 },
  { spBESTOWCURSE,                           3 },
  { spBLADEBARRIER,                          6 },
  { spBLASPHEMY,                             7 },
  { spBLESS,                                 1 },
  { spBLESSWATER,                            1 },
  { spBLINDNESSDEAFNESS,                     3 },
  { spBREAKENCHANTMENT,                      5 },
  { spBULLSSTRENGTH,                         2 },
  { spCALMEMOTIONS,                          2 },
  { spCAUSEFEAR,                             1 },
  { spCIRCLEOFDOOM,                          5 },
  { spCLOAKOFCHAOS,                          8 },
  { spCOMMAND,                               1 },
  { spCOMMUNE,                               5 },
  { spCOMPREHENDLANGUAGES,                   1 },
  { spCONSECRATE,                            2 },
  { spCONTAGION,                             3 },
  { spCONTINUALFLAME,                        3 },
  { spCONTROLWATER,                          4 },
  { spCONTROLWEATHER,                        7 },
  { spCREATEFOODANDWATER,                    3 },
  { spCREATEGREATERUNDEAD,                   8 },
  { spCREATEUNDEAD,                          6 },
  { spCREATEWATER,                           0 },
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMINORWOUNDS,                       0 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spCURSEWATER,                            1 },
  { spDARKNESS,                              2 },
  { spDAYLIGHT,                              3 },
  { spDEATHKNELL,                            2 },
  { spDEATHWARD,                             4 },
  { spDEATHWATCH,                            1 },
  { spDEEPERDARKNESS,                        3 },
  { spDELAYPOISON,                           2 },
  { spDESECRATE,                             2 },
  { spDESTRUCTION,                           7 },
  { spDETECTCHAOS,                           1 },
  { spDETECTEVIL,                            1 },
  { spDETECTGOOD,                            1 },
  { spDETECTLAW,                             1 },
  { spDETECTMAGIC,                           0 },
  { spDETECTPOISON,                          0 },
  { spDETECTUNDEAD,                          1 },
  { spDICTUM,                                7 },
  { spDIMENSIONALANCHOR,                     4 },
  { spDISCERNLIES,                           4 },
  { spDISCERNLOCATION,                       8 },
  { spDISMISSAL,                             4 },
  { spDISPELCHAOS,                           5 },
  { spDISPELEVIL,                            5 },
  { spDISPELGOOD,                            5 },
  { spDISPELLAW,                             5 },
  { spDISPELMAGIC,                           3 },
  { spDIVINATION,                            4 },
  { spDIVINEFAVOR,                           1 },
  { spDIVINEPOWER,                           4 },
  { spDOOM,                                  1 },
  { spEARTHQUAKE,                            8 },
  { spENDURANCE,                             2 },
  { spENDUREELEMENTS,                        1 },
  { spENERGYDRAIN,                           9 },
  { spENTHRALL,                              2 },
  { spENTROPICSHIELD,                        1 },
  { spETHEREALJAUNT,                         5 },
  { spETHEREALNESS,                          6 },
  { spFINDTHEPATH,                           6 },
  { spFINDTRAPS,                             2 },
  { spFIRESTORM,                             8 },
  { spFLAMESTRIKE,                           5 },
  { spFORBIDDANCE,                           6 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spGATE,                                  9 },
  { spGEASQUEST,                             6 },
  { spGENTLEREPOSE,                          2 },
  { spGIANTVERMIN,                           4 },
  { spGLYPHOFWARDING,                        3 },
  { spGREATERCOMMAND,                        5 },
  { spGREATERDISPELLING,                     6 },
  { spGREATERGLYPHOFWARDING,                 6 },
  { spGREATERMAGICWEAPON,                    4 },
  { spGREATERPLANARALLY,                     8 },
  { spGREATERRESTORATION,                    7 },
  { spGREATERSCRYING,                        7 },
  { spGUIDANCE,                              0 },
  { spHALLOW,                                5 },
  { spHARM,                                  6 },
  { spHEAL,                                  6 },
  { spHEALINGCIRCLE,                         5 },
  { spHELPINGHAND,                           3 },
  { spHEROESFEAST,                           6 },
  { spHOLDPERSON,                            2 },
  { spHOLYAURA,                              8 },
  { spHOLYWORD,                              7 },
  { spIMBUEWITHSPELLABILITY,                 4 },
  { spIMPLOSION,                             9 },
  { spINFLICTCRITICALWOUNDS,                 4 },
  { spINFLICTLIGHTWOUNDS,                    1 },
  { spINFLICTMINORWOUNDS,                    0 },
  { spINFLICTMODERATEWOUNDS,                 2 },
  { spINFLICTSERIOUSWOUNDS,                  3 },
  { spINSECTPLAGUE,                          5 },
  { spINVISIBILITYPURGE,                     3 },
  { spINVISIBILITYTOUNDEAD,                  1 },
  { spLESSERPLANARALLY,                      4 },
  { spLESSERRESTORATION,                     2 },
  { spLIGHT,                                 0 },
  { spLOCATEOBJECT,                          3 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spMAGICSTONE,                            1 },
  { spMAGICVESTMENT,                         3 },
  { spMAGICWEAPON,                           1 },
  { spMAKEWHOLE,                             2 },
  { spMARKOFJUSTICE,                         5 },
  { spMASSHEAL,                              8 },
  { spMELDINTOSTONE,                         3 },
  { spMENDING,                               0 },
  { spMIRACLE,                               9 },
  { spNEGATIVEENERGYPROTECTION,              3 },
  { spNEUTRALIZEPOISON,                      4 },
  { spOBSCUREOBJECT,                         3 },
  { spOBSCURINGMIST,                         1 },
  { spPLANARALLY,                            6 },
  { spPLANESHIFT,                            5 },
  { spPOISON,                                4 },
  { spPRAYER,                                3 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spPROTECTIONFROMLAW,                     1 },
  { spPURIFYFOODANDDRINK,                    0 },
  { spRAISEDEAD,                             5 },
  { spRANDOMACTION,                          1 },
  { spREADMAGIC,                             0 },
  { spREFUGE,                                7 },
  { spREGENERATE,                            7 },
  { spREMOVEBLINDNESSDEAFNESS,               3 },
  { spREMOVECURSE,                           3 },
  { spREMOVEDISEASE,                         3 },
  { spREMOVEFEAR,                            1 },
  { spREMOVEPARALYSIS,                       2 },
  { spREPELVERMIN,                           4 },
  { spREPULSION,                             7 },
  { spRESISTELEMENTS,                        2 },
  { spRESISTANCE,                            0 },
  { spRESTORATION,                           4 },
  { spRESURRECTION,                          7 },
  { spRIGHTEOUSMIGHT,                        5 },
  { spSANCTUARY,                             1 },
  { spSCRYING,                               5 },
  { spSEARINGLIGHT,                          3 },
  { spSENDING,                               4 },
  { spSHATTER,                               2 },
  { spSHIELDOFFAITH,                         1 },
  { spSHIELDOFLAW,                           8 },
  { spSHIELDOTHER,                           2 },
  { spSILENCE,                               2 },
  { spSLAYLIVING,                            5 },
  { spSOULBIND,                              9 },
  { spSOUNDBURST,                            2 },
  { spSPEAKWITHANIMALS,                      2 },
  { spSPEAKWITHDEAD,                         3 },
  { spSPEAKWITHPLANTS,                       3 },
  { spSPELLIMMUNITY,                         4 },
  { spSPELLRESISTANCE,                       5 },
  { spSPRITUALWEAPON,                        2 },
  { spSTATUS,                                4 },
  { spSTONESHAPE,                            3 },
  { spSTORMOFVENGEANCE,                      9 },
  { spSUMMONMONSTERI,                        1 },
  { spSUMMONMONSTERII,                       2 },
  { spSUMMONMONSTERIII,                      3 },
  { spSUMMONMONSTERIV,                       4 },
  { spSUMMONMONSTERIX,                       9 },
  { spSUMMONMONSTERV,                        5 },
  { spSUMMONMONSTERVI,                       6 },
  { spSUMMONMONSTERVII,                      7 },
  { spSUMMONMONSTERVIII,                     8 },
  { spSYMBOL,                                8 },
  { spTONGUES,                               4 },
  { spTRUERESURRECTION,                      9 },
  { spTRUESEEING,                            5 },
  { spUNDETECTABLEALIGNMENT,                 2 },
  { spUNHALLOW,                              5 },
  { spUNHOLYAURA,                            8 },
  { spVIRTUE,                                0 },
  { spWALLOFSTONE,                           5 },
  { spWATERBREATHING,                        3 },
  { spWATERWALK,                             3 },
  { spWINDWALK,                              6 },
  { spWINDWALL,                              3 },
  { spWORDOFCHAOS,                           7 },
  { spWORDOFRECALL,                          6 },
  { spZONEOFTRUTH,                           2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Death[] = {
  { spANIMATEDEAD,                           3 },
  { spCAUSEFEAR,                             1 },
  { spCREATEGREATERUNDEAD,                   8 },
  { spCREATEUNDEAD,                          6 },
  { spDEATHKNELL,                            2 },
  { spDEATHWARD,                             4 },
  { spDESTRUCTION,                           7 },
  { spSLAYLIVING,                            5 },
  { spWAILOFTHEBANSHEE,                      9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Destruction[] = {
  { spCIRCLEOFDOOM,                          5 },
  { spCONTAGION,                             3 },
  { spDISINTEGRATE,                          7 },
  { spEARTHQUAKE,                            8 },
  { spHARM,                                  6 },
  { spIMPLOSION,                             9 },
  { spINFLICTCRITICALWOUNDS,                 4 },
  { spINFLICTLIGHTWOUNDS,                    1 },
  { spSHATTER,                               2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Druid[] = {
  { spANIMALFRIENDSHIP,                      1 },
  { spANIMALGROWTH,                          5 },
  { spANIMALMESSENGER,                       2 },
  { spANIMALSHAPES,                          8 },
  { spANIMALTRANCE,                          2 },
  { spANTILIFESHELL,                         6 },
  { spANTIPATHY,                             9 },
  { spANTIPLANTSHELL,                        4 },
  { spATONEMENT,                             5 },
  { spAWAKEN,                                5 },
  { spBARKSKIN,                              2 },
  { spCALLLIGHTNING,                         3 },
  { spCALMANIMALS,                           1 },
  { spCHANGESTAFF,                           7 },
  { spCHARMPERSONORANIMAL,                   2 },
  { spCHILLMETAL,                            2 },
  { spCOMMANDPLANTS,                         8 },
  { spCOMMUNEWITHNATURE,                     5 },
  { spCONTAGION,                             3 },
  { spCONTROLPLANTS,                         4 },
  { spCONTROLWEATHER,                        7 },
  { spCONTROLWINDS,                          5 },
  { spCREATEWATER,                           0 },
  { spCREEPINGDOOM,                          7 },
  { spCURECRITICALWOUNDS,                    5 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMINORWOUNDS,                       0 },
  { spCUREMODERATEWOUNDS,                    3 },
  { spCURESERIOUSWOUNDS,                     4 },
  { spDEATHWARD,                             5 },
  { spDELAYPOISON,                           2 },
  { spDETECTANIMALSORPLANTS,                 1 },
  { spDETECTMAGIC,                           0 },
  { spDETECTPOISON,                          0 },
  { spDETECTSNARESANDPITS,                   1 },
  { spDIMINISHPLANTS,                        3 },
  { spDISPELMAGIC,                           4 },
  { spDOMINATEANIMAL,                        3 },
  { spEARTHQUAKE,                            9 },
  { spELEMENTALSWARM,                        9 },
  { spENDUREELEMENTS,                        1 },
  { spENTANGLE,                              1 },
  { spFAERIEFIRE,                            1 },
  { spFINDTHEPATH,                           6 },
  { spFINGEROFDEATH,                         8 },
  { spFIRESEEDS,                             6 },
  { spFIRESTORM,                             7 },
  { spFIRETRAP,                              2 },
  { spFLAMEBLADE,                            2 },
  { spFLAMESTRIKE,                           4 },
  { spFLAMINGSPHERE,                         2 },
  { spFLARE,                                 0 },
  { spFORESIGHT,                             9 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spGIANTVERMIN,                           4 },
  { spGOODBERRY,                             1 },
  { spGREATERDISPELLING,                     6 },
  { spGREATERMAGICFANG,                      3 },
  { spGREATERSCRYING,                        7 },
  { spGUIDANCE,                              0 },
  { spHALLOW,                                5 },
  { spHARM,                                  7 },
  { spHEAL,                                  7 },
  { spHEALINGCIRCLE,                         6 },
  { spHEATMETAL,                             2 },
  { spHOLDANIMAL,                            2 },
  { spICEPATH,                               5 },
  { spINSECTPLAGUE,                          5 },
  { spINVISIBILITYTOANIMALS,                 1 },
  { spIRONWOOD,                              6 },
  { spKNOWDIRECTION,                         0 },
  { spLESSERRESTORATION,                     2 },
  { spLIGHT,                                 0 },
  { spLIVEOAK,                               6 },
  { spMAGICFANG,                             1 },
  { spMASSHEAL,                              9 },
  { spMELDINTOSTONE,                         3 },
  { spMENDING,                               0 },
  { spNEUTRALIZEPOISON,                      3 },
  { spOBSCURINGMIST,                         1 },
  { spPASSWITHOUTTRACE,                      1 },
  { spPLANTGROWTH,                           3 },
  { spPOISON,                                3 },
  { spPRODUCEFLAME,                          2 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spPURIFYFOODANDDRINK,                    0 },
  { spQUENCH,                                4 },
  { spREADMAGIC,                             0 },
  { spREINCARNATE,                           4 },
  { spREMOVEDISEASE,                         3 },
  { spREPELMETALORSTONE,                     8 },
  { spREPELVERMIN,                           4 },
  { spREPELWOOD,                             6 },
  { spRESISTELEMENTS,                        2 },
  { spRESISTANCE,                            0 },
  { spREVERSEGRAVITY,                        8 },
  { spRUSTINGGRASP,                          4 },
  { spSCRYING,                               4 },
  { spSHAMBLER,                              9 },
  { spSHAPECHANGE,                           9 },
  { spSHILLELAGH,                            1 },
  { spSLEETSTORM,                            4 },
  { spSNARE,                                 3 },
  { spSOFTENEARTHANDSTONE,                   2 },
  { spSPEAKWITHANIMALS,                      2 },
  { spSPEAKWITHPLANTS,                       3 },
  { spSPELLSTAFF,                            6 },
  { spSPIKEGROWTH,                           3 },
  { spSPIKESTONES,                           4 },
  { spSTONESHAPE,                            3 },
  { spSTONETELL,                             6 },
  { spSUMMONNATURESALLYI,                    1 },
  { spSUMMONNATURESALLYII,                   2 },
  { spSUMMONNATURESALLYIII,                  3 },
  { spSUMMONNATURESALLYIV,                   4 },
  { spSUMMONNATURESALLYIX,                   9 },
  { spSUMMONNATURESALLYV,                    5 },
  { spSUMMONNATURESALLYVI,                   6 },
  { spSUMMONNATURESALLYVII,                  7 },
  { spSUMMONNATURESALLYVIII,                 8 },
  { spSUMMONSWARM,                           2 },
  { spSUNBEAM,                               7 },
  { spSUNBURST,                              8 },
  { spSYMPATHY,                              9 },
  { spTRANSMUTEMETALTOWOOD,                  7 },
  { spTRANSMUTEMUDTOROCK,                    5 },
  { spTRANSMUTEROCKTOMUD,                    5 },
  { spTRANSPORTVIAPLANTS,                    6 },
  { spTREESHAPE,                             2 },
  { spTREESTRIDE,                            5 },
  { spTRUESEEING,                            7 },
  { spUNHALLOW,                              5 },
  { spVIRTUE,                                0 },
  { spWALLOFFIRE,                            5 },
  { spWALLOFSTONE,                           6 },
  { spWALLOFTHORNS,                          5 },
  { spWARPWOOD,                              2 },
  { spWATERBREATHING,                        3 },
  { spWHIRLWIND,                             8 },
  { spWINDWALK,                              7 },
  { spWOODSHAPE,                             2 },
  { spWORDOFRECALL,                          8 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Earth[] = {
  { spEARTHQUAKE,                            7 },
  { spELEMENTALSWARM,                        9 },
  { spIRONBODY,                              8 },
  { spMAGICSTONE,                            1 },
  { spSOFTENEARTHANDSTONE,                   2 },
  { spSPIKESTONES,                           4 },
  { spSTONESHAPE,                            3 },
  { spSTONESKIN,                             6 },
  { spWALLOFSTONE,                           5 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Evil[] = {
  { spBLASPHEMY,                             7 },
  { spCREATEUNDEAD,                          6 },
  { spDESECRATE,                             2 },
  { spDISPELGOOD,                            5 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spSUMMONMONSTERIX,                       9 },
  { spUNHOLYAURA,                            8 },
  { spUNHOLYBLIGHT,                          4 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Fire[] = {
  { spBURNINGHANDS,                          1 },
  { spELEMENTALSWARM,                        9 },
  { spFIRESEEDS,                             6 },
  { spFIRESHIELD,                            5 },
  { spFIRESTORM,                             7 },
  { spINCENDIARYCLOUD,                       8 },
  { spPRODUCEFLAME,                          2 },
  { spRESISTELEMENTS,                        3 },
  { spWALLOFFIRE,                            4 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Good[] = {
  { spAID,                                   2 },
  { spBLADEBARRIER,                          6 },
  { spDISPELEVIL,                            5 },
  { spHOLYAURA,                              8 },
  { spHOLYSMITE,                             4 },
  { spHOLYWORD,                              7 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spSUMMONMONSTERIX,                       9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Healing[] = {
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spHEAL,                                  6 },
  { spHEALINGCIRCLE,                         5 },
  { spMASSHEAL,                              8 },
  { spREGENERATE,                            7 },
  { spTRUERESURRECTION,                      9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Knowledge[] = {
  { spCLAIRAUDIENCECLAIRVOYANCE,             3 },
  { spDETECTSECRETDOORS,                     1 },
  { spDETECTTHOUGHTS,                        2 },
  { spDISCERNLOCATION,                       8 },
  { spDIVINATION,                            4 },
  { spFINDTHEPATH,                           6 },
  { spFORESIGHT,                             9 },
  { spLEGENDLORE,                            7 },
  { spTRUESEEING,                            5 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Law[] = {
  { spCALMEMOTIONS,                          2 },
  { spDICTUM,                                7 },
  { spDISPELCHAOS,                           5 },
  { spHOLDMONSTER,                           6 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spORDERSWRATH,                           4 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spSHIELDOFLAW,                           8 },
  { spSUMMONMONSTERIX,                       9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Luck[] = {
  { spAID,                                   2 },
  { spBREAKENCHANTMENT,                      5 },
  { spENTROPICSHIELD,                        1 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spHOLYAURA,                              8 },
  { spMIRACLE,                               9 },
  { spMISLEAD,                               6 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spSPELLTURNING,                          7 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Magic[] = {
  { spANTIMAGICFIELD,                        6 },
  { spDISPELMAGIC,                           3 },
  { spIDENTIFY,                              2 },
  { spIMBUEWITHSPELLABILITY,                 4 },
  { spMORDENKAINENSDISJUNCTION,              9 },
  { spNYSTULSUNDETECTABLEAURA,               1 },
  { spPROTECTIONFROMSPELLS,                  8 },
  { spSPELLRESISTANCE,                       5 },
  { spSPELLTURNING,                          7 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Paladin[] = {
  { spBLESS,                                 1 },
  { spBLESSWATER,                            1 },
  { spBLESSWEAPON,                           1 },
  { spCREATEWATER,                           1 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMODERATEWOUNDS,                    3 },
  { spCURESERIOUSWOUNDS,                     4 },
  { spDEATHWARD,                             4 },
  { spDELAYPOISON,                           2 },
  { spDETECTPOISON,                          1 },
  { spDETECTUNDEAD,                          1 },
  { spDISCERNLIES,                           3 },
  { spDISPELEVIL,                            4 },
  { spDISPELMAGIC,                           3 },
  { spDIVINEFAVOR,                           1 },
  { spENDUREELEMENTS,                        1 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spGREATERMAGICWEAPON,                    3 },
  { spHEALMOUNT,                             3 },
  { spHOLYSWORD,                             4 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICWEAPON,                           1 },
  { spNEUTRALIZEPOISON,                      4 },
  { spPRAYER,                                3 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spREADMAGIC,                             1 },
  { spREMOVEBLINDNESSDEAFNESS,               3 },
  { spREMOVEPARALYSIS,                       2 },
  { spRESISTELEMENTS,                        2 },
  { spRESISTANCE,                            1 },
  { spSHIELDOTHER,                           2 },
  { spUNDETECTABLEALIGNMENT,                 2 },
  { spVIRTUE,                                1 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Plant[] = {
  { spBARKSKIN,                              2 },
  { spCHANGESTAFF,                           7 },
  { spCOMMANDPLANTS,                         8 },
  { spCONTROLPLANTS,                         4 },
  { spENTANGLE,                              1 },
  { spPLANTGROWTH,                           3 },
  { spREPELWOOD,                             6 },
  { spSHAMBLER,                              9 },
  { spWALLOFTHORNS,                          5 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Protection[] = {
  { spANTIMAGICFIELD,                        6 },
  { spMINDBLANK,                             8 },
  { spPRISMATICSPHERE,                       9 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spREPULSION,                             7 },
  { spSANCTUARY,                             1 },
  { spSHIELDOTHER,                           2 },
  { spSPELLIMMUNITY,                         4 },
  { spSPELLRESISTANCE,                       5 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Ranger[] = {
  { spALARM,                                 1 },
  { spANIMALFRIENDSHIP,                      1 },
  { spANIMALMESSENGER,                       2 },
  { spCONTROLPLANTS,                         3 },
  { spCURELIGHTWOUNDS,                       2 },
  { spCURESERIOUSWOUNDS,                     4 },
  { spDELAYPOISON,                           1 },
  { spDETECTANIMALSORPLANTS,                 1 },
  { spDETECTCHAOS,                           2 },
  { spDETECTEVIL,                            2 },
  { spDETECTGOOD,                            2 },
  { spDETECTLAW,                             2 },
  { spDETECTSNARESANDPITS,                   1 },
  { spDIMINISHPLANTS,                        3 },
  { spENTANGLE,                              1 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spGREATERMAGICFANG,                      3 },
  { spHOLDANIMAL,                            2 },
  { spMAGICFANG,                             1 },
  { spNEUTRALIZEPOISON,                      3 },
  { spNONDETECTION,                          4 },
  { spPASSWITHOUTTRACE,                      1 },
  { spPLANTGROWTH,                           3 },
  { spPOLYMORPHSELF,                         4 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spREADMAGIC,                             1 },
  { spREMOVEDISEASE,                         3 },
  { spRESISTELEMENTS,                        1 },
  { spSLEEP,                                 2 },
  { spSNARE,                                 2 },
  { spSPEAKWITHANIMALS,                      1 },
  { spSPEAKWITHPLANTS,                       2 },
  { spSUMMONNATURESALLYI,                    1 },
  { spSUMMONNATURESALLYII,                   2 },
  { spSUMMONNATURESALLYIII,                  3 },
  { spSUMMONNATURESALLYIV,                   4 },
  { spTREESHAPE,                             3 },
  { spTREESTRIDE,                            4 },
  { spWATERWALK,                             3 },
  { spWINDWALL,                              4 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Sorcerer[] = {
  { spACIDFOG,                               6 },
  { spALARM,                                 1 },
  { spALTERSELF,                             2 },
  { spANALYZEDWEOMER,                        6 },
  { spANIMALGROWTH,                          5 },
  { spANIMATEDEAD,                           5 },
  { spANIMATEROPE,                           1 },
  { spANTIMAGICFIELD,                        6 },
  { spANTIPATHY,                             8 },
  { spARCANEEYE,                             4 },
  { spARCANELOCK,                            2 },
  { spARCANEMARK,                            0 },
  { spASTRALPROJECTION,                      9 },
  { spBANISHMENT,                            7 },
  { spBESTOWCURSE,                           4 },
  { spBIGBYSCLENCHEDFIST,                    8 },
  { spBIGBYSCRUSHINGHAND,                    9 },
  { spBIGBYSFORCEFULHAND,                    6 },
  { spBIGBYSGRASPINGHAND,                    7 },
  { spBIGBYSINTERPOSINGHAND,                 5 },
  { spBINDING,                               8 },
  { spBLINDNESSDEAFNESS,                     2 },
  { spBLINK,                                 3 },
  { spBLUR,                                  2 },
  { spBULLSSTRENGTH,                         2 },
  { spBURNINGHANDS,                          1 },
  { spCATSGRACE,                             2 },
  { spCAUSEFEAR,                             1 },
  { spCHAINLIGHTNING,                        6 },
  { spCHANGESELF,                            1 },
  { spCHARMMONSTER,                          4 },
  { spCHARMPERSON,                           1 },
  { spCHILLTOUCH,                            1 },
  { spCIRCLEOFDEATH,                         6 },
  { spCLAIRAUDIENCECLAIRVOYANCE,             3 },
  { spCLONE,                                 8 },
  { spCLOUDKILL,                             5 },
  { spCOLORSPRAY,                            1 },
  { spCOMPREHENDLANGUAGES,                   1 },
  { spCONEOFCOLD,                            5 },
  { spCONFUSION,                             4 },
  { spCONTACTOTHERPLANE,                     5 },
  { spCONTAGION,                             4 },
  { spCONTINGENCY,                           6 },
  { spCONTINUALFLAME,                        2 },
  { spCONTROLUNDEAD,                         7 },
  { spCONTROLWATER,                          6 },
  { spCONTROLWEATHER,                        6 },
  { spDANCINGLIGHTS,                         0 },
  { spDARKNESS,                              2 },
  { spDARKVISION,                            2 },
  { spDAYLIGHT,                              2 },
  { spDAZE,                                  0 },
  { spDELAYEDBLASTFIREBALL,                  7 },
  { spDEMAND,                                8 },
  { spDETECTMAGIC,                           0 },
  { spDETECTPOISON,                          0 },
  { spDETECTSCRYING,                         4 },
  { spDETECTSECRETDOORS,                     1 },
  { spDETECTTHOUGHTS,                        2 },
  { spDETECTUNDEAD,                          1 },
  { spDIMENSIONDOOR,                         4 },
  { spDIMENSIONALANCHOR,                     4 },
  { spDISCERNLOCATION,                       8 },
  { spDISINTEGRATE,                          6 },
  { spDISMISSAL,                             5 },
  { spDISPELMAGIC,                           3 },
  { spDISPLACEMENT,                          3 },
  { spDISRUPTUNDEAD,                         0 },
  { spDOMINATEMONSTER,                       9 },
  { spDOMINATEPERSON,                        5 },
  { spDRAWMIJSINSTANTSUMMONS,                7 },
  { spDREAM,                                 5 },
  { spEMOTION,                               4 },
  { spENDURANCE,                             2 },
  { spENDUREELEMENTS,                        1 },
  { spENERGYDRAIN,                           9 },
  { spENERVATION,                            4 },
  { spENLARGE,                               1 },
  { spERASE,                                 1 },
  { spETHEREALJAUNT,                         7 },
  { spETHEREALNESS,                          8 },
  { spEVARDSBLACKTENTACLES,                  4 },
  { spEXPEDITIOUSRETREAT,                    1 },
  { spEXPLOSIVERUNES,                        3 },
  { spEYEBITE,                               6 },
  { spFABRICATE,                             5 },
  { spFALSEVISION,                           5 },
  { spFEAR,                                  4 },
  { spFEATHERFALL,                           1 },
  { spFEEBLEMIND,                            5 },
  { spFINGEROFDEATH,                         7 },
  { spFIRESHIELD,                            4 },
  { spFIRETRAP,                              4 },
  { spFIREBALL,                              3 },
  { spFLAMEARROW,                            3 },
  { spFLAMINGSPHERE,                         2 },
  { spFLARE,                                 0 },
  { spFLESHTOSTONE,                          6 },
  { spFLY,                                   3 },
  { spFOGCLOUD,                              2 },
  { spFORCECAGE,                             7 },
  { spFORESIGHT,                             9 },
  { spFREEDOM,                               9 },
  { spGASEOUSFORM,                           3 },
  { spGATE,                                  9 },
  { spGEASQUEST,                             6 },
  { spGENTLEREPOSE,                          3 },
  { spGHOSTSOUND,                            0 },
  { spGHOULTOUCH,                            2 },
  { spGLITTERDUST,                           2 },
  { spGLOBEOFINVULNERABILITY,                6 },
  { spGREASE,                                1 },
  { spGREATERDISPELLING,                     6 },
  { spGREATERMAGICWEAPON,                    3 },
  { spGREATERPLANARBINDING,                  8 },
  { spGREATERSCRYING,                        7 },
  { spGREATERSHADOWCONJURATION,              5 },
  { spGREATERSHADOWEVOCATION,                6 },
  { spGUARDSANDWARDS,                        6 },
  { spGUSTOFWIND,                            3 },
  { spHALLUCINATORYTERRAIN,                  4 },
  { spHALTUNDEAD,                            3 },
  { spHASTE,                                 3 },
  { spHOLDMONSTER,                           5 },
  { spHOLDPERSON,                            3 },
  { spHOLDPORTAL,                            1 },
  { spHORRIDWILTING,                         8 },
  { spHYPNOTICPATTERN,                       2 },
  { spHYPNOTISM,                             1 },
  { spICEPATH,                               4 },
  { spIDENTIFY,                              1 },
  { spILLUSORYSCRIPT,                        3 },
  { spILLUSORYWALL,                          4 },
  { spIMPRISONMENT,                          9 },
  { spIMPROVEDINVISIBILITY,                  4 },
  { spINCENDIARYCLOUD,                       8 },
  { spINSANITY,                              7 },
  { spINVISIBILITY,                          2 },
  { spINVISIBILITYSPHERE,                    3 },
  { spIRONBODY,                              8 },
  { spJUMP,                                  1 },
  { spKEENEDGE,                              3 },
  { spKNOCK,                                 2 },
  { spLEGENDLORE,                            6 },
  { spLEOMUNDSSECRETCHEST,                   5 },
  { spLEOMUNDSSECURESHELTER,                 4 },
  { spLEOMUNDSTINYHUT,                       3 },
  { spLEOMUNDSTRAP,                          2 },
  { spLESSERGEAS,                            4 },
  { spLESSERPLANARBINDING,                   5 },
  { spLEVITATE,                              2 },
  { spLIGHT,                                 0 },
  { spLIGHTNINGBOLT,                         3 },
  { spLIMITEDWISH,                           7 },
  { spLOCATECREATURE,                        4 },
  { spLOCATEOBJECT,                          2 },
  { spMAGEARMOR,                             1 },
  { spMAGEHAND,                              0 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spMAGICJAR,                              5 },
  { spMAGICMISSILE,                          1 },
  { spMAGICMOUTH,                            2 },
  { spMAGICWEAPON,                           1 },
  { spMAJORCREATION,                         5 },
  { spMAJORIMAGE,                            3 },
  { spMASSCHARM,                             8 },
  { spMASSHASTE,                             6 },
  { spMASSINVISIBILITY,                      7 },
  { spMASSSUGGESTION,                        6 },
  { spMAZE,                                  8 },
  { spMELFSACIDARROW,                        2 },
  { spMENDING,                               0 },
  { spMESSAGE,                               1 },
  { spMETEORSWARM,                           9 },
  { spMINDBLANK,                             8 },
  { spMINDFOG,                               5 },
  { spMINORCREATION,                         4 },
  { spMINORGLOBEOFINVULNERABILITY,           4 },
  { spMINORIMAGE,                            2 },
  { spMIRAGEARCANA,                          5 },
  { spMIRRORIMAGE,                           2 },
  { spMISDIRECTION,                          2 },
  { spMISLEAD,                               6 },
  { spMORDENKAINENSDISJUNCTION,              9 },
  { spMORDENKAINENSFAITHFULHOUND,            5 },
  { spMORDENKAINENSMAGNIFICENTMANSION,       7 },
  { spMORDENKAINENSSWORD,                    7 },
  { spMOUNT,                                 1 },
  { spMOVEEARTH,                             6 },
  { spNIGHTMARE,                             5 },
  { spNONDETECTION,                          3 },
  { spNYSTULSMAGICAURA,                      1 },
  { spNYSTULSUNDETECTABLEAURA,               1 },
  { spOBSCUREOBJECT,                         2 },
  { spOBSCURINGMIST,                         1 },
  { spOPENCLOSE,                             0 },
  { spOTILUKESFREEZINGSPHERE,                6 },
  { spOTILUKESRESILIENTSPHERE,               4 },
  { spOTILUKESTELEKINETICSPHERE,             8 },
  { spOTTOSIRRESISTIBLEDANCE,                8 },
  { spPASSWALL,                              5 },
  { spPERMANENCY,                            5 },
  { spPERMANENTIMAGE,                        6 },
  { spPERSISTENTIMAGE,                       5 },
  { spPHANTASMALKILLER,                      4 },
  { spPHANTOMSTEED,                          3 },
  { spPHASEDOOR,                             7 },
  { spPLANARBINDING,                         6 },
  { spPLANESHIFT,                            7 },
  { spPOLYMORPHANYOBJECT,                    8 },
  { spPOLYMORPHOTHER,                        4 },
  { spPOLYMORPHSELF,                         4 },
  { spPOWERWORDBLIND,                        8 },
  { spPOWERWORDKILL,                         9 },
  { spPOWERWORDSTUN,                         7 },
  { spPRESTIDIGITATION,                      0 },
  { spPRISMATICSPHERE,                       9 },
  { spPRISMATICSPRAY,                        7 },
  { spPRISMATICWALL,                         8 },
  { spPROGRAMMEDIMAGE,                       6 },
  { spPROJECTIMAGE,                          6 },
  { spPROTECTIONFROMARROWS,                  2 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spPROTECTIONFROMLAW,                     1 },
  { spPROTECTIONFROMSPELLS,                  8 },
  { spPRYINGEYES,                            5 },
  { spPYROTECHNICS,                          2 },
  { spRAINBOWPATTERN,                        4 },
  { spRARYSTELEPATHICBOND,                   5 },
  { spRAYOFENFEEBLEMENT,                     1 },
  { spRAYOFFROST,                            0 },
  { spREADMAGIC,                             0 },
  { spREDUCE,                                1 },
  { spREFUGE,                                9 },
  { spREMOVECURSE,                           4 },
  { spREPULSION,                             6 },
  { spRESISTELEMENTS,                        2 },
  { spRESISTANCE,                            0 },
  { spREVERSEGRAVITY,                        7 },
  { spROPETRICK,                             2 },
  { spSCARE,                                 2 },
  { spSCREEN,                                8 },
  { spSCRYING,                               4 },
  { spSECRETPAGE,                            3 },
  { spSEEINVISIBILITY,                       2 },
  { spSEEMING,                               5 },
  { spSENDING,                               5 },
  { spSEPIASNAKESIGIL,                       3 },
  { spSEQUESTER,                             7 },
  { spSHADES,                                6 },
  { spSHADOWCONJURATION,                     4 },
  { spSHADOWEVOCATION,                       5 },
  { spSHADOWWALK,                            7 },
  { spSHAPECHANGE,                           9 },
  { spSHATTER,                               2 },
  { spSHIELD,                                1 },
  { spSHOCKINGGRASP,                         1 },
  { spSHOUT,                                 4 },
  { spSHRINKITEM,                            3 },
  { spSILENTIMAGE,                           1 },
  { spSIMULACRUM,                            7 },
  { spSLEEP,                                 1 },
  { spSLEETSTORM,                            3 },
  { spSLOW,                                  3 },
  { spSOLIDFOG,                              4 },
  { spSOULBIND,                              9 },
  { spSPECTRALHAND,                          2 },
  { spSPELLTURNING,                          7 },
  { spSPIDERCLIMB,                           1 },
  { spSTATUE,                                7 },
  { spSTINKINGCLOUD,                         3 },
  { spSTONESHAPE,                            5 },
  { spSTONETOFLESH,                          6 },
  { spSTONESKIN,                             4 },
  { spSUGGESTION,                            3 },
  { spSUMMONMONSTERI,                        1 },
  { spSUMMONMONSTERII,                       2 },
  { spSUMMONMONSTERIII,                      3 },
  { spSUMMONMONSTERIV,                       4 },
  { spSUMMONMONSTERIX,                       9 },
  { spSUMMONMONSTERV,                        5 },
  { spSUMMONMONSTERVI,                       6 },
  { spSUMMONMONSTERVII,                      7 },
  { spSUMMONMONSTERVIII,                     8 },
  { spSUMMONSWARM,                           2 },
  { spSUNBURST,                              8 },
  { spSYMBOL,                                8 },
  { spSYMPATHY,                              8 },
  { spTASHASHIDEOUSLAUGHTER,                 2 },
  { spTELEKINESIS,                           5 },
  { spTELEPORT,                              5 },
  { spTELEPORTWITHOUTERROR,                  7 },
  { spTELEPORTATIONCIRCLE,                   9 },
  { spTEMPORALSTASIS,                        9 },
  { spTENSERSFLOATINGDISK,                   1 },
  { spTENSERSTRANSFORMATION,                 6 },
  { spTIMESTOP,                              9 },
  { spTONGUES,                               3 },
  { spTRANSMUTEMUDTOROCK,                    5 },
  { spTRANSMUTEROCKTOMUD,                    5 },
  { spTRAPTHESOUL,                           8 },
  { spTRUESEEING,                            6 },
  { spTRUESTRIKE,                            1 },
  { spUNSEENSERVANT,                         1 },
  { spVAMPIRICTOUCH,                         3 },
  { spVANISH,                                7 },
  { spVEIL,                                  6 },
  { spVENTRILOQUISM,                         1 },
  { spVISION,                                7 },
  { spWAILOFTHEBANSHEE,                      9 },
  { spWALLOFFIRE,                            4 },
  { spWALLOFFORCE,                           5 },
  { spWALLOFICE,                             4 },
  { spWALLOFIRON,                            5 },
  { spWALLOFSTONE,                           5 },
  { spWATERBREATHING,                        3 },
  { spWEB,                                   2 },
  { spWEIRD,                                 9 },
  { spWHISPERINGWIND,                        2 },
  { spWINDWALL,                              3 },
  { spWISH,                                  9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Strength[] = {
  { spBIGBYSCLENCHEDFIST,                    8 },
  { spBIGBYSCRUSHINGHAND,                    9 },
  { spBIGBYSGRASPINGHAND,                    7 },
  { spBULLSSTRENGTH,                         2 },
  { spENDUREELEMENTS,                        1 },
  { spMAGICVESTMENT,                         3 },
  { spRIGHTEOUSMIGHT,                        5 },
  { spSPELLIMMUNITY,                         4 },
  { spSTONESKIN,                             6 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Sun[] = {
  { spENDUREELEMENTS,                        1 },
  { spFIRESEEDS,                             6 },
  { spFIRESHIELD,                            4 },
  { spFLAMESTRIKE,                           5 },
  { spHEATMETAL,                             2 },
  { spPRISMATICSPHERE,                       9 },
  { spSEARINGLIGHT,                          3 },
  { spSUNBEAM,                               7 },
  { spSUNBURST,                              8 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Travel[] = {
  { spASTRALPROJECTION,                      9 },
  { spDIMENSIONDOOR,                         4 },
  { spEXPEDITIOUSRETREAT,                    1 },
  { spFINDTHEPATH,                           6 },
  { spFLY,                                   3 },
  { spLOCATEOBJECT,                          2 },
  { spPHASEDOOR,                             8 },
  { spTELEPORT,                              5 },
  { spTELEPORTWITHOUTERROR,                  7 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Trickery[] = {
  { spCHANGESELF,                            1 },
  { spCONFUSION,                             4 },
  { spFALSEVISION,                           5 },
  { spINVISIBILITY,                          2 },
  { spMISLEAD,                               6 },
  { spNONDETECTION,                          3 },
  { spPOLYMORPHANYOBJECT,                    8 },
  { spSCREEN,                                7 },
  { spTIMESTOP,                              9 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Undead_Slayer[] = {
  { spBULLSSTRENGTH,                         2 },
  { spCONTINUALFLAME,                        2 },
  { spCURECRITICALWOUNDS,                    4 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spCURESERIOUSWOUNDS,                     3 },
  { spDARKVISION,                            2 },
  { spDEATHWARD,                             4 },
  { spFREEDOMOFMOVEMENT,                     4 },
  { spHALTUNDEAD,                            3 },
  { spINVISIBILITYTOUNDEAD,                  1 },
  { spMAGICWEAPON,                           1 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spREMOVEFEAR,                            1 },
  { spSEARINGLIGHT,                          3 },
  { 0, 0 }
};


static SPELLSFORCLASS s_War[] = {
  { spBLADEBARRIER,                          6 },
  { spDIVINEPOWER,                           4 },
  { spFLAMESTRIKE,                           5 },
  { spMAGICVESTMENT,                         3 },
  { spMAGICWEAPON,                           1 },
  { spPOWERWORDBLIND,                        8 },
  { spPOWERWORDKILL,                         9 },
  { spPOWERWORDSTUN,                         7 },
  { spSPRITUALWEAPON,                        2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Water[] = {
  { spACIDFOG,                               7 },
  { spCONEOFCOLD,                            6 },
  { spCONTROLWATER,                          4 },
  { spELEMENTALSWARM,                        9 },
  { spFOGCLOUD,                              2 },
  { spHORRIDWILTING,                         8 },
  { spICEPATH,                               5 },
  { spOBSCURINGMIST,                         1 },
  { spWATERBREATHING,                        3 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Witch[] = {
  { spALTERSELF,                             2 },
  { spANIMALGROWTH,                          5 },
  { spANIMATEOBJECTS,                        6 },
  { spANTIPATHY,                             8 },
  { spARCANEMARK,                            0 },
  { spBESTOWCURSE,                           3 },
  { spBLINDNESSDEAFNESS,                     2 },
  { spCALMEMOTIONS,                          2 },
  { spCAUSEFEAR,                             1 },
  { spCHANGESELF,                            1 },
  { spCHARMMONSTER,                          4 },
  { spCHARMPERSON,                           1 },
  { spCLAIRAUDIENCECLAIRVOYANCE,             3 },
  { spCOMMAND,                               1 },
  { spCOMPREHENDLANGUAGES,                   1 },
  { spCONTAGION,                             3 },
  { spCONTROLWEATHER,                        6 },
  { spCREATEFOODANDWATER,                    3 },
  { spCREEPINGDOOM,                          7 },
  { spCURELIGHTWOUNDS,                       1 },
  { spCUREMINORWOUNDS,                       0 },
  { spCUREMODERATEWOUNDS,                    2 },
  { spDANCINGLIGHTS,                         0 },
  { spDAZE,                                  0 },
  { spDELAYPOISON,                           2 },
  { spDETECTMAGIC,                           0 },
  { spDETECTPOISON,                          0 },
  { spDETECTTHOUGHTS,                        2 },
  { spDISCERNLIES,                           4 },
  { spDISCERNLOCATION,                       8 },
  { spDISPELMAGIC,                           3 },
  { spDIVINATION,                            4 },
  { spDOOM,                                  1 },
  { spDREAM,                                 5 },
  { spEARTHQUAKE,                            9 },
  { spEMOTION,                               4 },
  { spENDUREELEMENTS,                        1 },
  { spENTHRALL,                              2 },
  { spEYEBITE,                               6 },
  { spFALSEVISION,                           5 },
  { spFEAR,                                  4 },
  { spFEEBLEMIND,                            5 },
  { spFINDTHEPATH,                           6 },
  { spFINGEROFDEATH,                         7 },
  { spFLARE,                                 0 },
  { spFORESIGHT,                             9 },
  { spGEASQUEST,                             6 },
  { spGHOSTSOUND,                            0 },
  { spGIANTVERMIN,                           4 },
  { spGREATERCOMMAND,                        5 },
  { spGREATERSCRYING,                        5 },
  { spHEROESFEAST,                           6 },
  { spHORRIDWILTING,                         8 },
  { spHYPNOTISM,                             1 },
  { spIDENTIFY,                              1 },
  { spINSANITY,                              7 },
  { spINVISIBILITY,                          2 },
  { spLEGENDLORE,                            6 },
  { spLEOMUNDSTINYHUT,                       3 },
  { spLIGHT,                                 0 },
  { spLIVEOAK,                               7 },
  { spLOCATECREATURE,                        4 },
  { spLOCATEOBJECT,                          2 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spMAGICJAR,                              5 },
  { spMAJORCREATION,                         5 },
  { spMAJORIMAGE,                            3 },
  { spMASSSUGGESTION,                        6 },
  { spMENDING,                               0 },
  { spMINORCREATION,                         4 },
  { spMINORIMAGE,                            2 },
  { spMIRAGEARCANA,                          5 },
  { spMISLEAD,                               6 },
  { spNEUTRALIZEPOISON,                      4 },
  { spNIGHTMARE,                             5 },
  { spPOLYMORPHANYOBJECT,                    8 },
  { spPOLYMORPHOTHER,                        4 },
  { spPOLYMORPHSELF,                         4 },
  { spPROJECTIMAGE,                          6 },
  { spREADMAGIC,                             0 },
  { spREFUGE,                                9 },
  { spREMOVEBLINDNESSDEAFNESS,               3 },
  { spREMOVECURSE,                           4 },
  { spREPELWOOD,                             7 },
  { spREPULSION,                             6 },
  { spRESISTANCE,                            0 },
  { spSCARE,                                 2 },
  { spSCRYING,                               4 },
  { spSEEMING,                               5 },
  { spSENDING,                               5 },
  { spSHAPECHANGE,                           9 },
  { spSILENTIMAGE,                           1 },
  { spSLEEP,                                 1 },
  { spSPEAKWITHANIMALS,                      2 },
  { spSUGGESTION,                            3 },
  { spSYMPATHY,                              8 },
  { spTENSERSTRANSFORMATION,                 6 },
  { spTONGUES,                               3 },
  { spTRANSPORTVIAPLANTS,                    7 },
  { spTRAPTHESOUL,                           8 },
  { spTRUESEEING,                            6 },
  { spVENTRILOQUISM,                         1 },
  { spVIRTUE,                                0 },
  { spWAILOFTHEBANSHEE,                      9 },
  { spWATERBREATHING,                        3 },
  { spWEIRD,                                 9 },
  { spWHISPERINGWIND,                        2 },
  { 0, 0 }
};


static SPELLSFORCLASS s_Wizard[] = {
  { spACIDFOG,                               6 },
  { spALARM,                                 1 },
  { spALTERSELF,                             2 },
  { spANALYZEDWEOMER,                        6 },
  { spANIMALGROWTH,                          5 },
  { spANIMATEDEAD,                           5 },
  { spANIMATEROPE,                           1 },
  { spANTIMAGICFIELD,                        6 },
  { spANTIPATHY,                             8 },
  { spARCANEEYE,                             4 },
  { spARCANELOCK,                            2 },
  { spARCANEMARK,                            0 },
  { spASTRALPROJECTION,                      9 },
  { spBANISHMENT,                            7 },
  { spBESTOWCURSE,                           4 },
  { spBIGBYSCLENCHEDFIST,                    8 },
  { spBIGBYSCRUSHINGHAND,                    9 },
  { spBIGBYSFORCEFULHAND,                    6 },
  { spBIGBYSGRASPINGHAND,                    7 },
  { spBIGBYSINTERPOSINGHAND,                 5 },
  { spBINDING,                               8 },
  { spBLINDNESSDEAFNESS,                     2 },
  { spBLINK,                                 3 },
  { spBLUR,                                  2 },
  { spBULLSSTRENGTH,                         2 },
  { spBURNINGHANDS,                          1 },
  { spCATSGRACE,                             2 },
  { spCAUSEFEAR,                             1 },
  { spCHAINLIGHTNING,                        6 },
  { spCHANGESELF,                            1 },
  { spCHARMMONSTER,                          4 },
  { spCHARMPERSON,                           1 },
  { spCHILLTOUCH,                            1 },
  { spCIRCLEOFDEATH,                         6 },
  { spCLAIRAUDIENCECLAIRVOYANCE,             3 },
  { spCLONE,                                 8 },
  { spCLOUDKILL,                             5 },
  { spCOLORSPRAY,                            1 },
  { spCOMPREHENDLANGUAGES,                   1 },
  { spCONEOFCOLD,                            5 },
  { spCONFUSION,                             4 },
  { spCONTACTOTHERPLANE,                     5 },
  { spCONTAGION,                             4 },
  { spCONTINGENCY,                           6 },
  { spCONTINUALFLAME,                        2 },
  { spCONTROLUNDEAD,                         7 },
  { spCONTROLWATER,                          6 },
  { spCONTROLWEATHER,                        6 },
  { spDANCINGLIGHTS,                         0 },
  { spDARKNESS,                              2 },
  { spDARKVISION,                            2 },
  { spDAYLIGHT,                              2 },
  { spDAZE,                                  0 },
  { spDELAYEDBLASTFIREBALL,                  7 },
  { spDEMAND,                                8 },
  { spDETECTMAGIC,                           0 },
  { spDETECTPOISON,                          0 },
  { spDETECTSCRYING,                         4 },
  { spDETECTSECRETDOORS,                     1 },
  { spDETECTTHOUGHTS,                        2 },
  { spDETECTUNDEAD,                          1 },
  { spDIMENSIONDOOR,                         4 },
  { spDIMENSIONALANCHOR,                     4 },
  { spDISCERNLOCATION,                       8 },
  { spDISINTEGRATE,                          6 },
  { spDISMISSAL,                             5 },
  { spDISPELMAGIC,                           3 },
  { spDISPLACEMENT,                          3 },
  { spDISRUPTUNDEAD,                         0 },
  { spDOMINATEMONSTER,                       9 },
  { spDOMINATEPERSON,                        5 },
  { spDRAWMIJSINSTANTSUMMONS,                7 },
  { spDREAM,                                 5 },
  { spEMOTION,                               4 },
  { spENDURANCE,                             2 },
  { spENDUREELEMENTS,                        1 },
  { spENERGYDRAIN,                           9 },
  { spENERVATION,                            4 },
  { spENLARGE,                               1 },
  { spERASE,                                 1 },
  { spETHEREALJAUNT,                         7 },
  { spETHEREALNESS,                          8 },
  { spEVARDSBLACKTENTACLES,                  4 },
  { spEXPEDITIOUSRETREAT,                    1 },
  { spEXPLOSIVERUNES,                        3 },
  { spEYEBITE,                               6 },
  { spFABRICATE,                             5 },
  { spFALSEVISION,                           5 },
  { spFEAR,                                  4 },
  { spFEATHERFALL,                           1 },
  { spFEEBLEMIND,                            5 },
  { spFINGEROFDEATH,                         7 },
  { spFIRESHIELD,                            4 },
  { spFIRETRAP,                              4 },
  { spFIREBALL,                              3 },
  { spFLAMEARROW,                            3 },
  { spFLAMINGSPHERE,                         2 },
  { spFLARE,                                 0 },
  { spFLESHTOSTONE,                          6 },
  { spFLY,                                   3 },
  { spFOGCLOUD,                              2 },
  { spFORCECAGE,                             7 },
  { spFORESIGHT,                             9 },
  { spFREEDOM,                               9 },
  { spGASEOUSFORM,                           3 },
  { spGATE,                                  9 },
  { spGEASQUEST,                             6 },
  { spGENTLEREPOSE,                          3 },
  { spGHOSTSOUND,                            0 },
  { spGHOULTOUCH,                            2 },
  { spGLITTERDUST,                           2 },
  { spGLOBEOFINVULNERABILITY,                6 },
  { spGREASE,                                1 },
  { spGREATERDISPELLING,                     6 },
  { spGREATERMAGICWEAPON,                    3 },
  { spGREATERPLANARBINDING,                  8 },
  { spGREATERSCRYING,                        7 },
  { spGREATERSHADOWCONJURATION,              5 },
  { spGREATERSHADOWEVOCATION,                6 },
  { spGUARDSANDWARDS,                        6 },
  { spGUSTOFWIND,                            3 },
  { spHALLUCINATORYTERRAIN,                  4 },
  { spHALTUNDEAD,                            3 },
  { spHASTE,                                 3 },
  { spHOLDMONSTER,                           5 },
  { spHOLDPERSON,                            3 },
  { spHOLDPORTAL,                            1 },
  { spHORRIDWILTING,                         8 },
  { spHYPNOTICPATTERN,                       2 },
  { spHYPNOTISM,                             1 },
  { spICEPATH,                               4 },
  { spIDENTIFY,                              1 },
  { spILLUSORYSCRIPT,                        3 },
  { spILLUSORYWALL,                          4 },
  { spIMPRISONMENT,                          9 },
  { spIMPROVEDINVISIBILITY,                  4 },
  { spINCENDIARYCLOUD,                       8 },
  { spINSANITY,                              7 },
  { spINVISIBILITY,                          2 },
  { spINVISIBILITYSPHERE,                    3 },
  { spIRONBODY,                              8 },
  { spJUMP,                                  1 },
  { spKEENEDGE,                              3 },
  { spKNOCK,                                 2 },
  { spLEGENDLORE,                            6 },
  { spLEOMUNDSSECRETCHEST,                   5 },
  { spLEOMUNDSSECURESHELTER,                 4 },
  { spLEOMUNDSTINYHUT,                       3 },
  { spLEOMUNDSTRAP,                          2 },
  { spLESSERGEAS,                            4 },
  { spLESSERPLANARBINDING,                   5 },
  { spLEVITATE,                              2 },
  { spLIGHT,                                 0 },
  { spLIGHTNINGBOLT,                         3 },
  { spLIMITEDWISH,                           7 },
  { spLOCATECREATURE,                        4 },
  { spLOCATEOBJECT,                          2 },
  { spMAGEARMOR,                             1 },
  { spMAGEHAND,                              0 },
  { spMAGICCIRCLEAGAINSTCHAOS,               3 },
  { spMAGICCIRCLEAGAINSTEVIL,                3 },
  { spMAGICCIRCLEAGAINSTGOOD,                3 },
  { spMAGICCIRCLEAGAINSTLAW,                 3 },
  { spMAGICJAR,                              5 },
  { spMAGICMISSILE,                          1 },
  { spMAGICMOUTH,                            2 },
  { spMAGICWEAPON,                           1 },
  { spMAJORCREATION,                         5 },
  { spMAJORIMAGE,                            3 },
  { spMASSCHARM,                             8 },
  { spMASSHASTE,                             6 },
  { spMASSINVISIBILITY,                      7 },
  { spMASSSUGGESTION,                        6 },
  { spMAZE,                                  8 },
  { spMELFSACIDARROW,                        2 },
  { spMENDING,                               0 },
  { spMESSAGE,                               1 },
  { spMETEORSWARM,                           9 },
  { spMINDBLANK,                             8 },
  { spMINDFOG,                               5 },
  { spMINORCREATION,                         4 },
  { spMINORGLOBEOFINVULNERABILITY,           4 },
  { spMINORIMAGE,                            2 },
  { spMIRAGEARCANA,                          5 },
  { spMIRRORIMAGE,                           2 },
  { spMISDIRECTION,                          2 },
  { spMISLEAD,                               6 },
  { spMORDENKAINENSDISJUNCTION,              9 },
  { spMORDENKAINENSFAITHFULHOUND,            5 },
  { spMORDENKAINENSLUCUBRATION,              6 },
  { spMORDENKAINENSMAGNIFICENTMANSION,       7 },
  { spMORDENKAINENSSWORD,                    7 },
  { spMOUNT,                                 1 },
  { spMOVEEARTH,                             6 },
  { spNIGHTMARE,                             5 },
  { spNONDETECTION,                          3 },
  { spNYSTULSMAGICAURA,                      1 },
  { spNYSTULSUNDETECTABLEAURA,               1 },
  { spOBSCUREOBJECT,                         2 },
  { spOBSCURINGMIST,                         1 },
  { spOPENCLOSE,                             0 },
  { spOTILUKESFREEZINGSPHERE,                6 },
  { spOTILUKESRESILIENTSPHERE,               4 },
  { spOTILUKESTELEKINETICSPHERE,             8 },
  { spOTTOSIRRESISTIBLEDANCE,                8 },
  { spPASSWALL,                              5 },
  { spPERMANENCY,                            5 },
  { spPERMANENTIMAGE,                        6 },
  { spPERSISTENTIMAGE,                       5 },
  { spPHANTASMALKILLER,                      4 },
  { spPHANTOMSTEED,                          3 },
  { spPHASEDOOR,                             7 },
  { spPLANARBINDING,                         6 },
  { spPLANESHIFT,                            7 },
  { spPOLYMORPHANYOBJECT,                    8 },
  { spPOLYMORPHOTHER,                        4 },
  { spPOLYMORPHSELF,                         4 },
  { spPOWERWORDBLIND,                        8 },
  { spPOWERWORDKILL,                         9 },
  { spPOWERWORDSTUN,                         7 },
  { spPRESTIDIGITATION,                      0 },
  { spPRISMATICSPHERE,                       9 },
  { spPRISMATICSPRAY,                        7 },
  { spPRISMATICWALL,                         8 },
  { spPROGRAMMEDIMAGE,                       6 },
  { spPROJECTIMAGE,                          6 },
  { spPROTECTIONFROMARROWS,                  2 },
  { spPROTECTIONFROMCHAOS,                   1 },
  { spPROTECTIONFROMELEMENTS,                3 },
  { spPROTECTIONFROMEVIL,                    1 },
  { spPROTECTIONFROMGOOD,                    1 },
  { spPROTECTIONFROMLAW,                     1 },
  { spPROTECTIONFROMSPELLS,                  8 },
  { spPRYINGEYES,                            5 },
  { spPYROTECHNICS,                          2 },
  { spRAINBOWPATTERN,                        4 },
  { spRARYSMNEMONICENHANCER,                 4 },
  { spRARYSTELEPATHICBOND,                   5 },
  { spRAYOFENFEEBLEMENT,                     1 },
  { spRAYOFFROST,                            0 },
  { spREADMAGIC,                             0 },
  { spREDUCE,                                1 },
  { spREFUGE,                                9 },
  { spREMOVECURSE,                           4 },
  { spREPULSION,                             6 },
  { spRESISTELEMENTS,                        2 },
  { spRESISTANCE,                            0 },
  { spREVERSEGRAVITY,                        7 },
  { spROPETRICK,                             2 },
  { spSCARE,                                 2 },
  { spSCREEN,                                8 },
  { spSCRYING,                               4 },
  { spSECRETPAGE,                            3 },
  { spSEEINVISIBILITY,                       2 },
  { spSEEMING,                               5 },
  { spSENDING,                               5 },
  { spSEPIASNAKESIGIL,                       3 },
  { spSEQUESTER,                             7 },
  { spSHADES,                                6 },
  { spSHADOWCONJURATION,                     4 },
  { spSHADOWEVOCATION,                       5 },
  { spSHADOWWALK,                            7 },
  { spSHAPECHANGE,                           9 },
  { spSHATTER,                               2 },
  { spSHIELD,                                1 },
  { spSHOCKINGGRASP,                         1 },
  { spSHOUT,                                 4 },
  { spSHRINKITEM,                            3 },
  { spSILENTIMAGE,                           1 },
  { spSIMULACRUM,                            7 },
  { spSLEEP,                                 1 },
  { spSLEETSTORM,                            3 },
  { spSLOW,                                  3 },
  { spSOLIDFOG,                              4 },
  { spSOULBIND,                              9 },
  { spSPECTRALHAND,                          2 },
  { spSPELLTURNING,                          7 },
  { spSPIDERCLIMB,                           1 },
  { spSTATUE,                                7 },
  { spSTINKINGCLOUD,                         3 },
  { spSTONESHAPE,                            5 },
  { spSTONETOFLESH,                          6 },
  { spSTONESKIN,                             4 },
  { spSUGGESTION,                            3 },
  { spSUMMONMONSTERI,                        1 },
  { spSUMMONMONSTERII,                       2 },
  { spSUMMONMONSTERIII,                      3 },
  { spSUMMONMONSTERIV,                       4 },
  { spSUMMONMONSTERIX,                       9 },
  { spSUMMONMONSTERV,                        5 },
  { spSUMMONMONSTERVI,                       6 },
  { spSUMMONMONSTERVII,                      7 },
  { spSUMMONMONSTERVIII,                     8 },
  { spSUMMONSWARM,                           2 },
  { spSUNBURST,                              8 },
  { spSYMBOL,                                8 },
  { spSYMPATHY,                              8 },
  { spTASHASHIDEOUSLAUGHTER,                 2 },
  { spTELEKINESIS,                           5 },
  { spTELEPORT,                              5 },
  { spTELEPORTWITHOUTERROR,                  7 },
  { spTELEPORTATIONCIRCLE,                   9 },
  { spTEMPORALSTASIS,                        9 },
  { spTENSERSFLOATINGDISK,                   1 },
  { spTENSERSTRANSFORMATION,                 6 },
  { spTIMESTOP,                              9 },
  { spTONGUES,                               3 },
  { spTRANSMUTEMUDTOROCK,                    5 },
  { spTRANSMUTEROCKTOMUD,                    5 },
  { spTRAPTHESOUL,                           8 },
  { spTRUESEEING,                            6 },
  { spTRUESTRIKE,                            1 },
  { spUNSEENSERVANT,                         1 },
  { spVAMPIRICTOUCH,                         3 },
  { spVANISH,                                7 },
  { spVEIL,                                  6 },
  { spVENTRILOQUISM,                         1 },
  { spVISION,                                7 },
  { spWAILOFTHEBANSHEE,                      9 },
  { spWALLOFFIRE,                            4 },
  { spWALLOFFORCE,                           5 },
  { spWALLOFICE,                             4 },
  { spWALLOFIRON,                            5 },
  { spWALLOFSTONE,                           5 },
  { spWATERBREATHING,                        3 },
  { spWEB,                                   2 },
  { spWEIRD,                                 9 },
  { spWHISPERINGWIND,                        2 },
  { spWINDWALL,                              3 },
  { spWISH,                                  9 },
  { 0, 0 }
};


static int goodAttackProgression[]   = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20 };
static int mediumAttackProgression[] = { 0, 1, 2, 3, 3, 4, 5, 6, 6,  7,  8,  9,  9, 10, 11, 12, 12, 13, 14, 15 };
static int poorAttackProgression[]   = { 0, 1, 1, 2, 2, 3, 3, 4, 4,  5,  5,  6,  6,  7,  7,  8,  8,  9,  9, 10 };

static int goodSaveProgression[] = { 2, 3, 3, 4, 4, 5, 5, 6, 6, 7, 7, 8, 8, 9, 9, 10, 10, 11, 11, 12 };
static int poorSaveProgression[] = { 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5,  5,  5,  6,  6,  6 };

static SPELLMATRIX adeptSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  0, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  0, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  0, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  0, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  3,  2, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  3,  2, -1, -1, -1, -1 }
};


static SPELLMATRIX bardSpellsPerDay = {
  {  2, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  2,  0, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  2,  0, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  1, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  2,  0, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  1, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  3,  3,  3,  3,  2,  0, -1, -1, -1, -1 },
  {  4,  3,  3,  3,  3,  1, -1, -1, -1, -1 },
  {  4,  4,  3,  3,  3,  2, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  3,  2,  0, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  3,  1, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  2, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  3, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  4, -1, -1, -1 }
};


static SPELLMATRIX bardSpellsKnown = {
  {  4, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  3, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  3, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  2, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  3, -1, -1, -1, -1 },
  {  6,  4,  4,  4,  4,  3, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  4,  4,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  4,  3, -1, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3, -1, -1, -1 },
  {  6,  5,  5,  5,  5,  4,  4, -1, -1, -1 },
  {  6,  5,  5,  5,  5,  5,  4, -1, -1, -1 }
};


static SPELLMATRIX clericSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  3,  2, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  2,  1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  3,  2, -1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  2,  1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  3,  2 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  3,  3 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  4,  4 }
};


static SPELLMATRIX druidSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  5,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  6,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  6,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  6,  5,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  6,  5,  5,  4,  4,  3,  3,  2, -1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  2,  1, -1 },
  {  6,  5,  5,  5,  4,  4,  3,  3,  2, -1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  2,  1 },
  {  6,  5,  5,  5,  5,  4,  4,  3,  3,  2 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  3,  3 },
  {  6,  5,  5,  5,  5,  5,  4,  4,  4,  4 }
};


static SPELLMATRIX paladinSpellsPerDay = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  0, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  0, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  3, -1, -1, -1, -1, -1 }
};


static SPELLMATRIX rangerSpellsPerDay = {
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1, -1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  0, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  0, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1, -1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  0, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  1,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1, -1, -1, -1, -1, -1, -1 },
  { -1,  2,  1,  1,  0, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  1,  1, -1, -1, -1, -1, -1 },
  { -1,  2,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  2,  2,  1, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  2, -1, -1, -1, -1, -1 },
  { -1,  3,  3,  3,  3, -1, -1, -1, -1, -1 }
};


static SPELLMATRIX sorcererSpellsPerDay = {
  {  5,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  5, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  3, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  4, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  5,  3, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  4, -1, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  5,  3, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  4, -1, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  5,  3, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  4, -1, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  5,  3, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  4, -1, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  5,  3, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  4, -1, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  5,  3, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  4, -1 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  5,  3 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  6,  4 },
  {  6,  6,  6,  6,  6,  6,  6,  6,  6,  6 }
};


static SPELLMATRIX sorcererSpellsKnown = {
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  5,  3, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  3,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  6,  4,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  7,  4,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  7,  5,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  8,  5,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  8,  5,  4,  3,  2, -1, -1, -1, -1, -1 },
  {  9,  5,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  9,  5,  5,  4,  3,  2, -1, -1, -1, -1 },
  {  9,  5,  5,  4,  3,  2,  1, -1, -1, -1 },
  {  9,  5,  5,  4,  4,  3,  2, -1, -1, -1 },
  {  9,  5,  5,  4,  4,  3,  2,  1, -1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  2, -1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  2,  1, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  2, -1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  2,  1 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  3,  2 },
  {  9,  5,  5,  4,  4,  4,  3,  3,  3,  3 }
};


static SPELLMATRIX wizardSpellsPerDay = {
  {  3,  1, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2, -1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  2,  1, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  2, -1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  2,  1, -1, -1, -1, -1, -1, -1 },
  {  4,  3,  3,  2, -1, -1, -1, -1, -1, -1 },
  {  4,  4,  3,  2,  1, -1, -1, -1, -1, -1 },
  {  4,  4,  3,  3,  2, -1, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  2,  1, -1, -1, -1, -1 },
  {  4,  4,  4,  3,  3,  2, -1, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  2,  1, -1, -1, -1 },
  {  4,  4,  4,  4,  3,  3,  2, -1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  2,  1, -1, -1 },
  {  4,  4,  4,  4,  4,  3,  3,  2, -1, -1 },
  {  4,  4,  4,  4,  4,  4,  3,  2,  1, -1 },
  {  4,  4,  4,  4,  4,  4,  3,  3,  2, -1 },
  {  4,  4,  4,  4,  4,  4,  4,  3,  2,  1 },
  {  4,  4,  4,  4,  4,  4,  4,  3,  3,  2 },
  {  4,  4,  4,  4,  4,  4,  4,  4,  3,  3 },
  {  4,  4,  4,  4,  4,  4,  4,  4,  4,  4 }
};


static const struct {
  int             id;
  int             type;
  int             skillCount;
  int             hitDie;
  int             bonusFeatAtFirst;
  int             bonusFeatEveryX;
  int*            attack;
  int*            fortSave;
  int*            refSave;
  int*            willSave;
  SKILLSFORCLASS* skills;
  SPELLSFORCLASS* spells;
  void*           spellsPerDay;
  void*           spellsKnown;
  char*           abbr;
  char*           name;
} s_classInfo[] = { /*              skills feat1   attack          */
    /* class            type             HD   feat2                         fortitude            reflex               will                 skills                 spells        spells per day         spells known          abbr    name         */
  { pcBARBARIAN,        cctPLAYER,    4, 12, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, barbarianSkills,       0,            0,                     0,                    "bbn", "barbarian" },
  { pcBARD,             cctPLAYER,    4,  6, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, goodSaveProgression, bardSkills,            s_Bard,       &bardSpellsPerDay,     &bardSpellsKnown,     "brd", "bard" },
  { pcCLERIC,           cctPLAYER,    2,  8, 0, 0, mediumAttackProgression, goodSaveProgression, poorSaveProgression, goodSaveProgression, clericSkills,          s_Cleric,     &clericSpellsPerDay,   0,                    "clr", "cleric" },
  { pcDRUID,            cctPLAYER,    4,  8, 0, 0, mediumAttackProgression, goodSaveProgression, poorSaveProgression, goodSaveProgression, druidSkills,           s_Druid,      &druidSpellsPerDay,    0,                    "drd", "druid" },
  { pcFIGHTER,          cctPLAYER,    2, 10, 1, 2, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, fighterSkills,         0,            0,                     0,                    "ftr", "fighter" },
  { pcMONK,             cctPLAYER,    4,  8, 0, 0, mediumAttackProgression, goodSaveProgression, goodSaveProgression, goodSaveProgression, monkSkills,            0,            0,                     0,                    "mnk", "monk" },
  { pcPALADIN,          cctPLAYER,    2, 10, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, paladinSkills,         s_Paladin,    &paladinSpellsPerDay,  0,                    "pal", "paladin" },
  { pcRANGER,           cctPLAYER,    4, 10, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, rangerSkills,          s_Ranger,     &rangerSpellsPerDay,   0,                    "rgr", "ranger" },
  { pcROGUE,            cctPLAYER,    8,  6, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, poorSaveProgression, rogueSkills,           0,            0,                     0,                    "rog", "rogue" },
  { pcSORCERER,         cctPLAYER,    2,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, sorcererSkills,        s_Sorcerer,   &sorcererSpellsPerDay, &sorcererSpellsKnown, "sor", "sorcerer" },
  { pcWIZARD,           cctPLAYER,    2,  4, 0, 5, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, wizardSkills,          s_Wizard,     &wizardSpellsPerDay,   0,                    "wiz", "wizard" },
  { prcARCANEARCHER,    cctPRESTIGE,  4,  8, 0, 0, goodAttackProgression,   goodSaveProgression, goodSaveProgression, poorSaveProgression, arcaneArcherSkills,    0,            0,                     0,                    "arc", "arcane archer" },
  { prcASSASSIN,        cctPRESTIGE,  4,  6, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, assassinSkills,        s_Assassin,   0,                     0,                    "asn", "assassin" },
  { prcBLACKGUARD,      cctPRESTIGE,  2, 10, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, blackguardSkills,      s_Blackguard, 0,                     0,                    "bgd", "blackguard" },
  { prcDWARVENDEFENDER, cctPRESTIGE,  2, 12, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, goodSaveProgression, dwarvenDefenderSkills, 0,            0,                     0,                    "ddr", "dwarven defender" },
  { prcLOREMASTER,      cctPRESTIGE,  4,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, loremasterSkills,      0,            0,                     0,                    "lmr", "loremaster" },
  { prcSHADOWDANCER,    cctPRESTIGE,  6,  8, 0, 0, mediumAttackProgression, poorSaveProgression, goodSaveProgression, poorSaveProgression, shadowdancerSkills,    0,            0,                     0,                    "sdr", "shadowdancer" },
  { npcADEPT,           cctNONPLAYER, 2,  6, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, goodSaveProgression, adeptSkills,           s_Adept,      &adeptSpellsPerDay,    0,                    "adp", "adept" },
  { npcARISTOCRAT,      cctNONPLAYER, 4,  8, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, aristocratSkills,      0,            0,                     0,                    "nob", "aristocrat" },
  { npcCOMMONER,        cctNONPLAYER, 2,  4, 0, 0, poorAttackProgression,   poorSaveProgression, poorSaveProgression, poorSaveProgression, commonerSkills,        0,            0,                     0,                    "com", "commoner" },
  { npcEXPERT,          cctNONPLAYER, 6,  6, 0, 0, mediumAttackProgression, poorSaveProgression, poorSaveProgression, goodSaveProgression, expertSkills,          0,            0,                     0,                    "exp", "expert" },
  { npcWARRIOR,         cctNONPLAYER, 2,  8, 0, 0, goodAttackProgression,   goodSaveProgression, poorSaveProgression, poorSaveProgression, warriorSkills,         0,            0,                     0,                    "war", "warrior" },
  { 0,                  0,            0,  0, 0, 0, 0,                       0,                   0,                   0,                   0,                     0,            0,                     0,                    0,     0 }
};


static const struct {
  int   id;
  char* name;
} s_classTypeInfo[] = {
  { cctPLAYER,    "player" },
  { cctPRESTIGE,  "prestige" },
  { cctNONPLAYER, "non-player" },
  { 0,            0 }
};


static const struct {
  int   alignment;
  char* abbr;
  char* text;
} s_alignmentText[] = {
  { alLAWFUL | alGOOD,         "LG", "lawful good" },
  { alLAWFUL | alGENEUTRAL,    "LN", "lawful neutral" },
  { alLAWFUL | alEVIL,         "LE", "lawful evil" },
  { alLCNEUTRAL | alGOOD,      "NG", "neutral good" },
  { alLCNEUTRAL | alGENEUTRAL, "N",  "true neutral" },
  { alLCNEUTRAL | alEVIL,      "NE", "neutral evil" },
  { alCHAOTIC | alGOOD,        "CG", "chaotic good" },
  { alCHAOTIC | alGENEUTRAL,   "CN", "chaotic neutral" },
  { alCHAOTIC | alEVIL,        "CE", "chaotic evil" },
  { 0,                         0,    0 }
};


static const struct {
  int   type;
  int   ability;
  int   untrained;
  int   acCheck;
  char* name;
} s_skills[] = {
  { skALCHEMY,            abINTELLIGENCE, 0, 0, "alchemy" },
  { skANIMALEMPATHY,      abCHARISMA,     0, 0, "animal empathy" },
  { skAPPRAISE,           abINTELLIGENCE, 1, 0, "appraise" },
  { skBALANCE,            abDEXTERITY,    1, 1, "balance" },
  { skBLUFF,              abCHARISMA,     1, 0, "bluff" },
  { skCLIMB,              abSTRENGTH,     1, 1, "climb" },
  { skCONCENTRATION,      abCONSTITUTION, 1, 0, "concentration" },
  { skCRAFT,              abINTELLIGENCE, 1, 0, "craft" },
  { skDECIPHERSCRIPT,     abINTELLIGENCE, 0, 0, "decipher script" },
  { skDIPLOMACY,          abCHARISMA,     1, 0, "diplomacy" },
  { skDISABLEDEVICE,      abINTELLIGENCE, 0, 0, "disable device" },
  { skDISGUISE,           abCHARISMA,     1, 0, "disguise" },
  { skESCAPEARTIST,       abDEXTERITY,    1, 1, "escape artist" },
  { skFORGERY,            abINTELLIGENCE, 1, 0, "forgery" },
  { skGATHERINFORMATION,  abCHARISMA,     1, 0, "gather information" },
  { skHANDLEANIMAL,       abCHARISMA,     0, 0, "handle animal" },
  { skHEAL,               abWISDOM,       1, 0, "heal" },
  { skHIDE,               abDEXTERITY,    1, 1, "hide" },
  { skINNUENDO,           abWISDOM,       0, 0, "innuendo" },
  { skINTIMIDATE,         abCHARISMA,     1, 0, "intimidate" },
  { skINTUITDIRECTION,    abWISDOM,       0, 0, "intuit direction" },
  { skJUMP,               abSTRENGTH,     1, 1, "jump" },
  { skKNOWLEDGE_ARCANA,   abINTELLIGENCE, 0, 0, "knowledge (arcana)" },
  { skKNOWLEDGE_RELIGION, abINTELLIGENCE, 0, 0, "knowledge (religion)" },
  { skKNOWLEDGE_NATURE,   abINTELLIGENCE, 0, 0, "knowledge (nature)" },
  { skKNOWLEDGE,          abINTELLIGENCE, 0, 0, "knowledge" },
  { skLISTEN,             abWISDOM,       1, 0, "listen" },
  { skMOVESILENTLY,       abDEXTERITY,    1, 1, "move silently" },
  { skOPENLOCK,           abDEXTERITY,    0, 0, "open lock" },
  { skPERFORM,            abCHARISMA,     1, 0, "perform" },
  { skPICKPOCKET,         abDEXTERITY,    0, 1, "pick pocket" },
  { skPROFESSION,         abWISDOM,       0, 0, "profession" },
  { skREADLIPS,           abINTELLIGENCE, 0, 0, "read lips" },
  { skRIDE,               abDEXTERITY,    1, 0, "ride" },
  { skSCRY,               abINTELLIGENCE, 1, 0, "scry" },
  { skSEARCH,             abINTELLIGENCE, 1, 0, "search" },
  { skSENSEMOTIVE,        abWISDOM,       1, 0, "sense motive" },
  { skSPEAKLANGUAGE,      abNONE,         0, 0, "speak language" },
  { skSPELLCRAFT,         abINTELLIGENCE, 0, 0, "spellcraft" },
  { skSPOT,               abWISDOM,       1, 0, "spot" },
  { skSWIM,               abSTRENGTH,     1, 0, "swim" },
  { skTUMBLE,             abDEXTERITY,    0, 1, "tumble" },
  { skUSEMAGICDEVICE,     abCHARISMA,     0, 0, "use magic device" },
  { skUSEROPE,            abDEXTERITY,    1, 0, "use rope" },
  { skWILDERNESSLORE,     abWISDOM,       1, 0, "wilderness lore" },
  { 0,                    0,              0, 0, 0 }
};


static const struct {
  int   ability;
  char* name;
} s_abilities[] = {
  { abNONE,         "none" },
  { abSTRENGTH,     "strength" },
  { abDEXTERITY,    "dexterity" },
  { abCONSTITUTION, "constitution" },
  { abINTELLIGENCE, "intelligence" },
  { abWISDOM,       "wisdom" },
  { abCHARISMA,     "charisma" },
  { 0,              0 }
};


static const struct {
  int   id;
  char* name;
} s_featTypes[] = {
  { fttGENERAL,      "general" },
  { fttITEMCREATION, "item creation" },
  { fttMETAMAGIC,    "metamagic" },
  { fttSPECIAL,      "special" },
  { 0,               0 }
};

/* feat pre-requisite definitions */

static FEATPREREQ alertnessPR[] = { { 0, 0, 0 } };
static FEATPREREQ blindfightPR[] = { { 0, 0, 0 } };
static FEATPREREQ combatCastingPR[] = { { 0, 0, 0 } };
static FEATPREREQ combatReflexesPR[] = { { 0, 0, 0 } };
static FEATPREREQ endurancePR[] = { { 0, 0, 0 } };
static FEATPREREQ greatFortPR[] = { { 0, 0, 0 } };
static FEATPREREQ improvedInitPR[] = { { 0, 0, 0 } };
static FEATPREREQ improvedUnarmedStrikePR[] = { { 0, 0, 0 } };
static FEATPREREQ ironWillPR[] = { { 0, 0, 0 } };
static FEATPREREQ lightningReflexesPR[] = { { 0, 0, 0 } };
static FEATPREREQ martialWeaponProfPR[] = { { 0, 0, 0 } };
static FEATPREREQ pointBlankShotPR[] = { { 0, 0, 0 } };
static FEATPREREQ runPR[] = { { 0, 0, 0 } };
static FEATPREREQ shieldProfPR[] = { { 0, 0, 0 } };
static FEATPREREQ simpleWeaponProfPR[] = { { 0, 0, 0 } };
static FEATPREREQ skillFocusPR[] = { { 0, 0, 0 } };
static FEATPREREQ spellFocusPR[] = { { 0, 0, 0 } };
static FEATPREREQ spellPenetrationPR[] = { { 0, 0, 0 } };
static FEATPREREQ toughnessPR[] = { { 0, 0, 0 } };
static FEATPREREQ trackPR[] = { { 0, 0, 0 } };
static FEATPREREQ twoWeaponFightingPR[] = { { 0, 0, 0 } };
static FEATPREREQ empowerSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ enlargeSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ extendSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ heightenSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ maximizeSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ quickenSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ silentSpellPR[] = { { 0, 0, 0 } };
static FEATPREREQ stillSpellPR[] = { { 0, 0, 0 } };

static FEATPREREQ ambidexterityPR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 15 },
  { 0, 0, 0 }
};

static FEATPREREQ armorProfLightPR[] = { { 0, 0, 0 } };

static FEATPREREQ armorProfMedPR[] = {
  { fprFEAT, ftARMORPROFICIENCY_LIGHT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ armorProfHeavyPR[] = {
  { fprFEAT, ftARMORPROFICIENCY_LIGHT, 0 },
  { fprFEAT, ftARMORPROFICIENCY_MEDIUM, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ dodgePR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { 0, 0, 0 }
};

static FEATPREREQ mobilityPR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftDODGE, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ springAttackPR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftDODGE, 0 },
  { fprFEAT, ftMOBILITY, 0 },
  { fprMINIMUMBASEATTACKBONUS, 4, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ exoticWeaponProfPR[] = {
  { fprMINIMUMBASEATTACKBONUS, 1, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ expertisePR[] = {
  { fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
  { 0, 0, 0 }
};

static FEATPREREQ improvedDisarmPR[] = {
  { fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
  { fprFEAT, ftEXPERTISE, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ improvedTripPR[] = {
  { fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
  { fprFEAT, ftEXPERTISE, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ whirlWindAttPR[] = {
  { fprMINIMUMABILITYSCORE, abINTELLIGENCE, 13 },
  { fprFEAT, ftEXPERTISE, 0 },
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftDODGE, 0 },
  { fprFEAT, ftMOBILITY, 0 },
  { fprMINIMUMBASEATTACKBONUS, 4, 0 },
  { fprFEAT, ftSPRINGATTACK, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ improvedCritPR[] = {
  { fprPROFICIENTWITHWEAPON, 0, 0 },
  { fprMINIMUMBASEATTACKBONUS, 8, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ deflectArrowsPR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ stunningFistPR[] = {
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftIMPROVEDUNARMEDSTRIKE, 0 },
  { fprMINIMUMABILITYSCORE, abWISDOM, 13 },
  { fprMINIMUMBASEATTACKBONUS, 8, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ leadershipPR[] = {
  { fprMINIMUMCHARACTERLEVEL, 6, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ mountedCombatPR[] = {
  { fprSKILL, skRIDE, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ mountedArcheryPR[] = {
  { fprSKILL, skRIDE, 0 },
  { fprFEAT, ftMOUNTEDCOMBAT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ tramplePR[] = {
  { fprSKILL, skRIDE, 0 },
  { fprFEAT, ftMOUNTEDCOMBAT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ rideByAttPR[] = {
  { fprSKILL, skRIDE, 0 },
  { fprFEAT, ftMOUNTEDCOMBAT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ spiritedChargePR[] = {
  { fprSKILL, skRIDE, 0 },
  { fprFEAT, ftMOUNTEDCOMBAT, 0 },
  { fprFEAT, ftRIDEBYATTACK, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ farShotPR[] = {
  { fprFEAT, ftPOINTBLANKSHOT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ preciseShotPR[] = {
  { fprFEAT, ftPOINTBLANKSHOT, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ rapidShotPR[] = {
  { fprFEAT, ftPOINTBLANKSHOT, 0 },
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { 0, 0, 0 }
};

static FEATPREREQ shotOnTheRunPR[] = {
  { fprFEAT, ftPOINTBLANKSHOT, 0 },
  { fprMINIMUMABILITYSCORE, abDEXTERITY, 13 },
  { fprFEAT, ftDODGE, 0 },
  { fprFEAT, ftMOBILITY, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ powerAttPR[] = {
  { fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
  { 0, 0, 0 }
};

static FEATPREREQ cleavePR[] = {
  { fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
  { fprFEAT, ftPOWERATTACK, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ improvedBullRushPR[] = {
  { fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
  { fprFEAT, ftPOWERATTACK, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ sunderPR[] = {
  { fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
  { fprFEAT, ftPOWERATTACK, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ greatCleavePR[] = {
  { fprMINIMUMABILITYSCORE, abSTRENGTH, 13 },
  { fprFEAT, ftPOWERATTACK, 0 },
  { fprFEAT, ftCLEAVE, 0 },
  { fprMINIMUMBASEATTACKBONUS, 4 },
  { 0, 0, 0 }
};

static FEATPREREQ quickDrawPR[] = {
  { fprMINIMUMBASEATTACKBONUS, 1, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ improvedTwoWeaponFightingPR[] = {
  { fprFEAT, ftTWOWEAPONFIGHTING, 0 },
  { fprFEAT, ftAMBIDEXTERITY, 0 },
  { fprMINIMUMBASEATTACKBONUS, 9, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ weaponFinessePR[] = {
  { fprPROFICIENTWITHWEAPON, 0, 0 },
  { fprMINIMUMBASEATTACKBONUS, 1, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ weaponFocusPR[] = {
  { fprPROFICIENTWITHWEAPON, 0, 0 },
  { fprMINIMUMBASEATTACKBONUS, 1, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ brewPotionPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 3, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ craftMagicArmsAndArmorPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 5, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ craftRodPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 9, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ craftStaffPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 12, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ craftWandPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 5, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ craftWondrousItemPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 3, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ forgeRingPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 12, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ scribeScrollPR[] = {
  { fprMINIMUMSPELLCASTERLEVEL, 1, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ extraTurningPR[] = {
  { fprCLERICORPALADIN, 0, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ spellMasteryPR[] = {
  { fprWIZARD, 0, 0 },
  { 0, 0, 0 }
};

static FEATPREREQ weaponSpecializationPR[] = {
  { fprMINIMUMFIGHTERLEVEL, 4, 0 },
  { 0, 0, 0 }
};

/* feat definitions */

static const struct {
  int         id;
  int         type;
  int         multi;
  FEATPREREQ* prereqs;
  char*       name;
} s_feats[] = {
  { ftALERTNESS,                  fttGENERAL,      0, alertnessPR,                 "alertness" },
  { ftAMBIDEXTERITY,              fttGENERAL,      0, ambidexterityPR,             "ambidexterity" },
  { ftARMORPROFICIENCY_LIGHT,     fttGENERAL,      0, armorProfLightPR,            "armor proficiency (light)" },
  { ftARMORPROFICIENCY_MEDIUM,    fttGENERAL,      0, armorProfMedPR,              "armor proficiency (medium)" },
  { ftARMORPROFICIENCY_HEAVY,     fttGENERAL,      0, armorProfHeavyPR,            "armor proficiency (heavy)" },
  { ftBLINDFIGHT,                 fttGENERAL,      0, blindfightPR,                "blind-fight" },
  { ftCOMBATCASTING,              fttGENERAL,      0, combatCastingPR,             "combat casting" },
  { ftCOMBATREFLEXES,             fttGENERAL,      0, combatReflexesPR,            "combat reflexes" },
  { ftDODGE,                      fttGENERAL,      0, dodgePR,                     "dodge" },
  { ftMOBILITY,                   fttGENERAL,      0, mobilityPR,                  "mobility" },
  { ftSPRINGATTACK,               fttGENERAL,      0, springAttackPR,              "spring attack" },
  { ftENDURANCE,                  fttGENERAL,      0, endurancePR,                 "endurance" },
  { ftWEAPONPROFICIENCY_EXOTIC,   fttGENERAL,      1, exoticWeaponProfPR,          "exotic weapon proficiency" },
  { ftWEAPONPROFICIENCY_MARTIAL,  fttGENERAL,      1, martialWeaponProfPR,         "martial weapon proficiency" },
  { ftWEAPONPROFICIENCY_SIMPLE,   fttGENERAL,      1, simpleWeaponProfPR,          "simple weapon proficiency" },
  { ftEXPERTISE,                  fttGENERAL,      0, expertisePR,                 "expertise" },
  { ftIMPROVEDDISARM,             fttGENERAL,      0, improvedDisarmPR,            "improved disarm" },
  { ftIMPROVEDTRIP,               fttGENERAL,      0, improvedTripPR,              "improved trip" },
  { ftWHIRLWINDATTACK,            fttGENERAL,      0, whirlWindAttPR,              "whirlwind attack" },
  { ftGREATFORTITUDE,             fttGENERAL,      0, greatFortPR,                 "great fortitude" },
  { ftIMPROVEDCRITICAL,           fttGENERAL,      1, improvedCritPR,              "improved critical" },
  { ftIMPROVEDINITIATIVE,         fttGENERAL,      0, improvedInitPR,              "improved initiative" },
  { ftIMPROVEDUNARMEDSTRIKE,      fttGENERAL,      0, improvedUnarmedStrikePR,     "improved unarmed strike" },
  { ftDEFLECTARROWS,              fttGENERAL,      0, deflectArrowsPR,             "deflect arrows" },
  { ftSTUNNINGFIST,               fttGENERAL,      0, stunningFistPR,              "stunning fist" },
  { ftIRONWILL,                   fttGENERAL,      0, ironWillPR,                  "iron will" },
  { ftLEADERSHIP,                 fttGENERAL,      0, leadershipPR,                "leadership" },
  { ftLIGHTNINGREFLEXES,          fttGENERAL,      0, lightningReflexesPR,         "lightning reflexes" },
  { ftMOUNTEDCOMBAT,              fttGENERAL,      0, mountedCombatPR,             "mounted combat" },
  { ftMOUNTEDARCHERY,             fttGENERAL,      0, mountedArcheryPR,            "mounted archery" },
  { ftTRAMPLE,                    fttGENERAL,      0, tramplePR,                   "trample" },
  { ftRIDEBYATTACK,               fttGENERAL,      0, rideByAttPR,                 "ride-by attack" },
  { ftSPIRITEDCHARGE,             fttGENERAL,      0, spiritedChargePR,            "spirited charge" },
  { ftPOINTBLANKSHOT,             fttGENERAL,      0, pointBlankShotPR,            "point blank shot" },
  { ftFARSHOT,                    fttGENERAL,      0, farShotPR,                   "far shot" },
  { ftPRECISESHOT,                fttGENERAL,      0, preciseShotPR,               "precise shot" },
  { ftRAPIDSHOT,                  fttGENERAL,      0, rapidShotPR,                 "rapid shot" },
  { ftSHOTONTHERUN,               fttGENERAL,      0, shotOnTheRunPR,              "shot on the run" },
  { ftPOWERATTACK,                fttGENERAL,      0, powerAttPR,                  "power attack" },
  { ftCLEAVE,                     fttGENERAL,      0, cleavePR,                    "cleave" },
  { ftIMPROVEDBULLRUSH,           fttGENERAL,      0, improvedBullRushPR,          "improved bull rush" },
  { ftSUNDER,                     fttGENERAL,      0, sunderPR,                    "sunder" },
  { ftGREATCLEAVE,                fttGENERAL,      0, greatCleavePR,               "great cleave" },
  { ftQUICKDRAW,                  fttGENERAL,      0, quickDrawPR,                 "quick draw" },
  { ftRUN,                        fttGENERAL,      0, runPR,                       "run" },
  { ftSHIELDPROFICIENCY,          fttGENERAL,      0, shieldProfPR,                "shield proficiency" },
  { ftSKILLFOCUS,                 fttGENERAL,      1, skillFocusPR,                "skill focus" },
  { ftSPELLFOCUS,                 fttGENERAL,      1, spellFocusPR,                "spell focus" },
  { ftSPELLPENETRATION,           fttGENERAL,      0, spellPenetrationPR,          "spell penetration" },
  { ftTOUGHNESS,                  fttGENERAL,      1, toughnessPR,                 "toughness" },
  { ftTRACK,                      fttGENERAL,      0, trackPR,                     "track" },
  { ftTWOWEAPONFIGHTING,          fttGENERAL,      0, twoWeaponFightingPR,         "two-weapon fighting" },
  { ftIMPROVEDTWOWEAPONFIGHTING,  fttGENERAL,      0, improvedTwoWeaponFightingPR, "improved two-weapon fighting" },
  { ftWEAPONFINESSE,              fttGENERAL,      1, weaponFinessePR,             "weapon finesse" },
  { ftWEAPONFOCUS,                fttGENERAL,      1, weaponFocusPR,               "weapon focus" },
  { ftBREWPOTION,                 fttITEMCREATION, 0, brewPotionPR,                "brew potion" },
  { ftCRAFTMAGICARMSANDARMOR,     fttITEMCREATION, 0, craftMagicArmsAndArmorPR,    "craft magic arms and armor" },
  { ftCRAFTROD,                   fttITEMCREATION, 0, craftRodPR,                  "craft rod" },
  { ftCRAFTSTAFF,                 fttITEMCREATION, 0, craftStaffPR,                "craft staff" },
  { ftCRAFTWAND,                  fttITEMCREATION, 0, craftWandPR,                 "craft wand" },
  { ftCRAFTWONDROUSITEM,          fttITEMCREATION, 0, craftWondrousItemPR,         "craft wondrous item" },
  { ftFORGERING,                  fttITEMCREATION, 0, forgeRingPR,                 "forge ring" },
  { ftSCRIBESCROLL,               fttITEMCREATION, 0, scribeScrollPR,              "scribe scroll" },
  { ftEMPOWERSPELL,               fttMETAMAGIC,    0, empowerSpellPR,              "empower spell" },
  { ftENLARGESPELL,               fttMETAMAGIC,    0, enlargeSpellPR,              "enlarge spell" },
  { ftEXTENDSPELL,                fttMETAMAGIC,    0, extendSpellPR,               "extend spell" },
  { ftHEIGHTENSPELL,              fttMETAMAGIC,    0, heightenSpellPR,             "heighten spell" },
  { ftMAXIMIZESPELL,              fttMETAMAGIC,    0, maximizeSpellPR,             "maximize spell" },
  { ftQUICKENSPELL,               fttMETAMAGIC,    0, quickenSpellPR,              "quicken spell" },
  { ftSILENTSPELL,                fttMETAMAGIC,    0, silentSpellPR,               "silent spell" },
  { ftSTILLSPELL,                 fttMETAMAGIC,    0, stillSpellPR,                "still spell" },
  { ftEXTRATURNING,               fttSPECIAL,      1, extraTurningPR,              "extra turning" },
  { ftSPELLMASTERY,               fttSPECIAL,      1, spellMasteryPR,              "spell mastery" },
  { ftWEAPONSPECIALIZATION,       fttSPECIAL,      1, weaponSpecializationPR,      "weapon specialization" },
  { ftFLYBYATTACK,                fttGENERAL,      0, 0,                           "flyby attack" },
  { ftMULTIATTACK,                fttGENERAL,      0, 0,                           "multiattack" },
  { ftMULTIDEXTERITY,             fttGENERAL,      0, 0,                           "multidexterity" },
  { ftMULTIWEAPONFIGHTING,        fttGENERAL,      0, 0,                           "multiweapon fighting" },
  { 0,                            0,               0,                              0 }
};


static RACIALBONUS dwarvenHBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skAPPRAISE,      2 },
  { rbtSKILL,        skCRAFT,         2 },
  { 0,               0,               0 }
};

static RACIALBONUS elvenHBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS aqElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS gnomeRBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skALCHEMY,       2 },
  { 0,               0,               0 }
};

static RACIALBONUS halfElvenBonuses[] = {
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSEARCH,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS halflingLFBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skJUMP,          2 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS halforcBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { 0,               0,               0 }
};

static RACIALBONUS aasimarBonuses[] = {
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS deepDwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { 0,               0,               0 }
};

static RACIALBONUS mtnDwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skAPPRAISE,      2 },
  { rbtSKILL,        skCRAFT,         2 },
  { 0,               0,               0 }
};

static RACIALBONUS grayElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS wildElfBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS woodElfBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS forestGnomeBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skHIDE,          4 },
  { 0,               0,               0 }
};

static RACIALBONUS tallfellowBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS halflingDeepBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skAPPRAISE,      2 },
  { rbtSKILL,        skCRAFT,         2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS svirfneblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtARMORCLASS,   0,               4 },
  { 0,               0,               0 }
};

static RACIALBONUS lizardFolkBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skJUMP,          6 },
  { rbtSKILL,        skSWIM,          8 },
  { rbtSKILL,        skBALANCE,       4 },
  { 0,               0,               0 }
};

static RACIALBONUS dopplegangerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtARMORCLASS,   0,               4 },
  { rbtSKILL,        skBLUFF,        11 },
  { rbtSKILL,        skDISGUISE,     11 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtSKILL,        skSENSEMOTIVE,   4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS goblinBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { 0,               0,               0 }
};

static RACIALBONUS hobgoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { 0,               0,               0 }
};

static RACIALBONUS koboldBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCRAFT,         2 },
  { rbtSKILL,        skPROFESSION,    2 },
  { rbtSKILL,        skSEARCH,        2 },
  { 0,               0,               0 }
};

static RACIALBONUS orcBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { 0,               0,               0 }
};

static RACIALBONUS tieflingBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skBLUFF,         2 },
  { rbtSKILL,        skHIDE,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS drowMaleBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS drowFemaleBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          2 },
  { 0,               0,               0 }
};

static RACIALBONUS duergarBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skMOVESILENTLY,  4 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS derroBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS gnollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS troglodyteBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtFEAT,         ftMULTIATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS bugbearBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS ogreBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     10 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skCLIMB,         3 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { 0,               0,               0 }
};

static RACIALBONUS ogreMageBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     10 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               3 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skCONCENTRATION, 3 },
  { rbtSKILL,        skSPELLCRAFT,    2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS minotaurBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtATTACK,       0,               6 },
  { rbtARMORCLASS,   0,               5 },
  { rbtSKILL,        skINTIMIDATE,    6 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSEARCH,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS mindflayerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtATTACK,       0,               6 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skBLUFF,         6 },
  { rbtSKILL,        skCONCENTRATION, 11 },
  { rbtSKILL,        skHIDE,         11 },
  { rbtSKILL,        skINTIMIDATE,   11 },
  { rbtSKILL,        skKNOWLEDGE_ARCANA, 4 },
  { rbtSKILL,        skKNOWLEDGE,     4 },
  { rbtSKILL,        skLISTEN,       11 },
  { rbtSKILL,        skMOVESILENTLY, 11 },
  { rbtSKILL,        skSPOT,         11 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS araneaBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCLIMB,        14 },
  { rbtSKILL,        skCONCENTRATION, 6 },
  { rbtSKILL,        skCRAFT,         6 },
  { rbtSKILL,        skESCAPEARTIST,  6 },
  { rbtSKILL,        skJUMP,          6 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS azerBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skCRAFT,         5 },
  { rbtSKILL,        skHIDE,         -2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSEARCH,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS centaurBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skWILDERNESSLORE, 4 },
  { rbtARMORCLASS,   0,               2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { 0,               0,               0 }
};

static RACIALBONUS driderBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               6 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCLIMB,        12 },
  { rbtSKILL,        skCONCENTRATION, 7 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skMOVESILENTLY,  5 },
  { rbtSKILL,        skSPELLCRAFT,    8 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftAMBIDEXTERITY, 0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftTWOWEAPONFIGHTING, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS ettinBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     12 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtARMORCLASS,   0,               7 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     7 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS hillGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     14 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,      6 },
  { rbtARMORCLASS,   0,               9 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     8 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS stoneGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     16 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtARMORCLASS,   0,              11 },
  { rbtATTACK,       0,               9 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          8 },
  { rbtSKILL,        skJUMP,          2 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS frostGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     18 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION, 10 },
  { rbtARMORCLASS,   0,               9 },
  { rbtATTACK,       0,               9 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS fireGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     20 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION, 10 },
  { rbtARMORCLASS,   0,               8 },
  { rbtATTACK,       0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,     9 },
  { rbtSAVINGTHROW,  svREFLEX,        4 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skCLIMB,         1 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS cloudGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     24 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtARMORCLASS,   0,              12 },
  { rbtATTACK,       0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,    10 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,          4 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS stormGiantBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     28 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE,  6 },
  { rbtABILITYSCORE, abWISDOM,        6 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,              12 },
  { rbtATTACK,       0,              12 },
  { rbtSAVINGTHROW,  svFORTITUDE,    11 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skJUMP,         -2 },
  { rbtSKILL,        skSPOT,          5 },
  { rbtSKILL,        skPERFORM,       5 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftGREATCLEAVE,   0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftSUNDER,        0 },
  { 0,               0,               0 }
};

static RACIALBONUS grimlockBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               4 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skCLIMB,         5 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skSEARCH,        5 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS seaHagBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skKNOWLEDGE,     4 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS annisBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     14 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,              10 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION,10 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS greenHagBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,              11 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCONCENTRATION,12 },
  { rbtSKILL,        skKNOWLEDGE,     4 },
  { rbtSKILL,        skHIDE,         10 },
  { rbtSKILL,        skLISTEN,        8 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATCASTING, 0 },
  { rbtFEAT,         ftGREATFORTITUDE,0 },
  { 0,               0,               0 }
};

static RACIALBONUS harpyBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skBLUFF,         6 },
  { rbtSKILL,        skLISTEN,        7 },
  { rbtSKILL,        skPERFORM,       7 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftFLYBYATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS kuotoaBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               6 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          3 },
  { rbtSKILL,        skESCAPEARTIST, 18 },
  { rbtSKILL,        skKNOWLEDGE,     5 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skMOVESILENTLY,  3 },
  { rbtSKILL,        skSEARCH,        9 },
  { rbtSKILL,        skSPOT,          7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftGREATFORTITUDE,0 },
  { 0,               0,               0 }
};

static RACIALBONUS locathahBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCRAFT,         2 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS medusaBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skBLUFF,         9 },
  { rbtSKILL,        skDISGUISE,      9 },
  { rbtSKILL,        skMOVESILENTLY,  7 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS merfolkBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { 0,               0,               0 }
};

static RACIALBONUS sahuaginBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skANIMALEMPATHY, 3 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        6 },
  { rbtSKILL,        skPROFESSION,    1 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtSKILL,        skWILDERNESSLORE,-1 },
  { rbtFEAT,         ftMULTIATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS trollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     12},
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION, 12 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               7 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     5 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftIRONWILL,      0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti1Bonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               6 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION, 9 },
  { rbtSKILL,        skCRAFT,         5 },
  { rbtSKILL,        skKNOWLEDGE,     5 },
  { rbtSKILL,        skDISGUISE,      0 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti2Bonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,               1 },
  { rbtATTACK,       0,               7 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtSAVINGTHROW,  svREFLEX,        5 },
  { rbtSAVINGTHROW,  svWILL,          5 },
  { rbtSKILL,        skCONCENTRATION,10 },
  { rbtSKILL,        skCRAFT,         5 },
  { rbtSKILL,        skKNOWLEDGE,     5 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS yuanti3Bonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  8 },
  { rbtABILITYSCORE, abWISDOM,        8 },
  { rbtABILITYSCORE, abCHARISMA,      6 },  
  { rbtARMORCLASS,   0,              10 },
  { rbtATTACK,       0,               8 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        6 },
  { rbtSAVINGTHROW,  svWILL,          6 },
  { rbtSKILL,        skCONCENTRATION, 8 },
  { rbtSKILL,        skCRAFT,         5 },
  { rbtSKILL,        skKNOWLEDGE,     5 },
  { rbtSKILL,        skHIDE,          8 },
  { rbtSKILL,        skLISTEN,        9 },
  { rbtSKILL,        skSPOT,          9 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftEXPERTISE,     0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_abandonedBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCLIMB,         2 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skJUMP,          0 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skWILDERNESSLORE,4 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_asaathBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     1 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          4 },
  { rbtSKILL,        skALCHEMY,       3 },
  { rbtSKILL,        skESCAPEARTIST,  0 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          5 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  7 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtSKILL,        skSPELLCRAFT,    7 },
  { rbtSKILL,        skSPOT,          0 },
  { rbtSKILL,        skUSEMAGICDEVICE,0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftCOMBATREFLEXES,0 },
  { rbtFEAT,         ftEXPERTISE,     0 },
  { rbtFEAT,         ftRUN,           0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_batDevilBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     8 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abWISDOM,        4 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtARMORCLASS,   0,               3 },
  { rbtATTACK,       0,               2 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSKILL,        skCLIMB,         4 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skLISTEN,       18 },
  { rbtSKILL,        skSPOT,          6 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { rbtFEAT,         ftFLYBYATTACK,   0 },
  { rbtFEAT,         ftLIGHTNINGREFLEXES, 0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_plagueWretchBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtARMORCLASS,   0,               5 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtSKILL,        skBALANCE,       1 },
  { rbtSKILL,        skBLUFF,         5 },
  { rbtSKILL,        skCLIMB,         0 },
  { rbtSKILL,        skDIPLOMACY,     3 },
  { rbtSKILL,        skINTIMIDATE,    6 },
  { rbtSKILL,        skJUMP,          0 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skPERFORM,       6 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtSKILL,        skTUMBLE,        2 },
  { rbtFEAT,         ftENDURANCE,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_charduniBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skAPPRAISE,      1 },
  { rbtSKILL,        skCLIMB,        -1 },
  { rbtSKILL,        skCRAFT,         2 },
  { rbtSKILL,        skINTIMIDATE,    3 },
  { rbtSKILL,        skINTUITDIRECTION, 3 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_coalGoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtATTACK,       0,               3 },
  { rbtSAVINGTHROW,  svFORTITUDE,     0 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtSAVINGTHROW,  svWILL,          0 },
  { rbtSKILL,        skHIDE,          6 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skMOVESILENTLY,  6 },
  { rbtSKILL,        skOPENLOCK,      1 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_fdwarfBonuses[] = {
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSKILL,        skCRAFT,         4 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_felfBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,     -2 },
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION, -2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtSKILL,        skHIDE,          2 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSEARCH,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftDODGE,         0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_iceGhoulBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      8 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -4 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skESCAPEARTIST,  0 },
  { rbtSKILL,        skHIDE,          3 },
  { rbtSKILL,        skINTUITDIRECTION, 3 },
  { rbtSKILL,        skLISTEN,        3 },
  { rbtSKILL,        skMOVESILENTLY,  3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skSWIM,          3 },
  { rbtSKILL,        skWILDERNESSLORE,7 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_manticoraBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      2 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtARMORCLASS,   0,               2 },
  { rbtATTACK,       0,               3 },
  { rbtSKILL,        skCLIMB,         5 },
  { rbtSKILL,        skHIDE,          3 },
  { rbtSKILL,        skINTIMIDATE,    4 },
  { rbtSKILL,        skJUMP,          3 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  5 },
  { rbtSKILL,        skWILDERNESSLORE,3 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_morgauntBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtATTACK,       0,               3 },
  { rbtSKILL,        skBLUFF,         8 },
  { rbtSKILL,        skHIDE,          1 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          2 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { rbtFEAT,         ftBLINDFIGHT,    0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_proudBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               6 },
  { rbtSKILL,        skHIDE,          7 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skLISTEN,        5 },
  { rbtSKILL,        skMOVESILENTLY,  1 },
  { rbtSKILL,        skSPOT,          8 },
  { rbtSKILL,        skWILDERNESSLORE,2 },
  { rbtFEAT,         ftCLEAVE,        0 },
  { rbtFEAT,         ftIMPROVEDINITIATIVE, 0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_ratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_bgratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSEARCH,        2 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_dratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,      2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skDIPLOMACY,     0 },
  { rbtSKILL,        skESCAPEARTIST,  2 },
  { rbtSKILL,        skHIDE,          1 },
  { rbtFEAT,         ftDODGE,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_fratmanBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skJUMP,         -1 },
  { rbtSKILL,        skSWIM,          3 },
  { rbtFEAT,         ftPOWERATTACK,   0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_rwratmanBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abCONSTITUTION,  6 },
  { rbtABILITYSCORE, abINTELLIGENCE,  4 },
  { rbtABILITYSCORE, abWISDOM,        2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               1 },
  { rbtARMORCLASS,   0,               1 },
  { rbtSKILL,        skCONCENTRATION,-1 },
  { rbtSKILL,        skESCAPEARTIST,  1 },
  { rbtSKILL,        skHIDE,          0 },
  { rbtSKILL,        skJUMP,          1 },
  { rbtSKILL,        skSCRY,          0 },
  { rbtSKILL,        skSPELLCRAFT,    3 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_skinDevilBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE,  2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,      4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               5 },
  { rbtARMORCLASS,   0,               3 },
  { rbtSKILL,        skBLUFF,         8 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skSPOT,          4 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_segoblinBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abCHARISMA,     -8 },
  { rbtSAVINGTHROW,  svFORTITUDE,     2 },
  { rbtATTACK,       0,               2 },
  { rbtARMORCLASS,   0,               2 },
  { rbtSKILL,        skBALANCE,       0 },
  { rbtSKILL,        skHIDE,          5 },
  { rbtSKILL,        skJUMP,          5 },
  { rbtSKILL,        skLISTEN,        4 },
  { rbtSKILL,        skMOVESILENTLY,  2 },
  { rbtSKILL,        skSPOT,          6 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_strollBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      4 },
  { rbtABILITYSCORE, abDEXTERITY,    -2 },
  { rbtABILITYSCORE, abCONSTITUTION,  8 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     6 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtSAVINGTHROW,  svWILL,          2 },
  { rbtATTACK,       0,               7 },
  { rbtARMORCLASS,   0,               9 },
  { rbtSKILL,        skANIMALEMPATHY,16 },
  { rbtSKILL,        skCRAFT,         9 },
  { rbtSKILL,        skLISTEN,       11 },
  { rbtSKILL,        skRIDE,         16 },
  { rbtSKILL,        skSPOT,         16 },
  { rbtSKILL,        skWILDERNESSLORE,11 },
  { rbtFEAT,         ftRIDEBYATTACK,  0 },
  { rbtFEAT,         ftSPIRITEDCHARGE,0 },
  { rbtFEAT,         ftTOUGHNESS,     0 },
  { rbtFEAT,         ftTOUGHNESS,     0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_selementBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCONSTITUTION,  2 },
  { rbtSAVINGTHROW,  svFORTITUDE,     4 },
  { rbtSAVINGTHROW,  svREFLEX,        1 },
  { rbtSAVINGTHROW,  svWILL,          1 },
  { rbtATTACK,       0,               4 },
  { rbtARMORCLASS,   0,               3 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_tokalBonuses[] = {
  { rbtABILITYSCORE, abSTRENGTH,      6 },
  { rbtABILITYSCORE, abDEXTERITY,     6 },
  { rbtABILITYSCORE, abCONSTITUTION,  4 },
  { rbtABILITYSCORE, abINTELLIGENCE, -2 },
  { rbtABILITYSCORE, abWISDOM,       -2 },
  { rbtABILITYSCORE, abCHARISMA,     -4 },
  { rbtSAVINGTHROW,  svFORTITUDE,     3 },
  { rbtSAVINGTHROW,  svREFLEX,        3 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skLISTEN,        1 },
  { rbtSKILL,        skSPOT,          1 },
  { rbtFEAT,         ftALERTNESS,     0 },
  { 0,               0,               0 }
};

static RACIALBONUS cc_ubantuBonuses[] = {
  { rbtABILITYSCORE, abDEXTERITY,     2 },
  { rbtABILITYSCORE, abCHARISMA,     -2 },
  { rbtSAVINGTHROW,  svREFLEX,        2 },
  { rbtATTACK,       0,               2 },
  { rbtSKILL,        skCRAFT,         2 },
  { rbtSKILL,        skHANDLEANIMAL,  1 },
  { rbtSKILL,        skINTUITDIRECTION, 3 },
  { rbtSKILL,        skLISTEN,        2 },
  { rbtSKILL,        skRIDE,          1 },
  { rbtSKILL,        skSEARCH,        3 },
  { rbtSKILL,        skSPOT,          3 },
  { rbtSKILL,        skWILDERNESSLORE,2 },
  { rbtFEAT,         ftENDURANCE,     0 },
  { rbtFEAT,         ftMOUNTEDCOMBAT, 0 },
  { rbtFEAT,         ftPOINTBLANKSHOT,0 },
  { rbtFEAT,         ftPRECISESHOT,   0 },
  { rbtFEAT,         ftRIDEBYATTACK,  0 },
  { rbtFEAT,         ftRUN,           0 },
  { rbtFEAT,         ftTRACK,         0 },
  { 0,               0,               0 }
};

static int humanLanguages[] = { lnCOMMON, 0 };
static int elfLanguages[] = { lnELVEN, lnCOMMON, 0 };
static int dwarfLanguages[] = { lnDWARVEN, lnCOMMON, 0 };
static int gnomeLanguages[] = { lnGNOME, lnCOMMON, 0 };
static int halflingLanguages[] = { lnHALFLING, lnCOMMON, 0 };
static int halforcLanguages[] = { lnCOMMON, lnORC, 0 };
static int sylvanLanguages[] = { lnCOMMON, lnSYLVAN, 0 };
static int ignanLanguages[] = { lnCOMMON, lnIGNAN, 0 };
static int bugbearLanguages[] = { lnCOMMON, lnGOBLIN, 0 };
static int centaurLanguages[] = { lnSYLVAN, lnELVEN, 0 };
static int undercommonLanguages[] = { lnCOMMON, lnUNDERCOMMON, 0 };
static int drowLanguages[] = { lnELVEN, lnCOMMON, lnUNDERCOMMON, 0 };
static int giantLanguages[] = { lnGIANT, lnCOMMON, 0 };
static int gnollLanguages[] = { lnGNOLL, 0 };
static int forestGnomeLanguages[] = { lnGNOME, lnELVEN, lnSYLVAN, 0 };
static int svirfneblinLanguages[] = { lnGNOME, lnCOMMON, lnTERRAN, lnUNDERCOMMON, 0 };
static int goblinLanguages[] = { lnGOBLIN, 0 };
static int tallfellowLanguages[] = { lnCOMMON, lnHALFLING, lnELVEN, 0 };
static int deepHalfLanguages[] = { lnCOMMON, lnHALFLING, lnDWARVEN, 0 };
static int draconicLanguages[] = { lnDRACONIC, 0 };
static int kuotoaLanguages[] = { lnUNDERCOMMON, lnAQUAN, 0 };
static int merfolkLanguages[] = { lnCOMMON, lnAQUAN, 0 };
static int orcLanguages[] = { lnORC, 0 };
static int yuantiLanguages[] = { lnCOMMON, lnDRACONIC, lnABYSSAL, 0 };
static int majorLanguages[] = { lnCOMMON, lnDWARVEN, lnELVEN, lnGNOME, lnHALFLING, 0 };

static int asaathLanguages[] = { lnCOMMON, lnDRACONIC, 0 };

static int dwarvenBonusLang[] = { lnGIANT, lnGNOME, lnGOBLIN, lnORC, lnTERRAN, lnUNDERCOMMON, 0 };
static int elvenBonusLang[] = { lnDRACONIC, lnGNOLL, lnGNOME, lnGOBLIN, lnORC, lnSYLVAN, 0 };
static int halforcBonusLang[] = { lnDRACONIC, lnGIANT, lnGNOLL, lnGOBLIN, lnINFERNAL, 0 };
static int halflingBonusLang[] = { lnDWARVEN, lnELVEN, lnGNOME, lnGOBLIN, lnORC, 0 };
static int araneaBonusLang[] = { lnELVEN, lnUNDERCOMMON, 0 };
static int evilBonusLang[] = { lnORC, lnGOBLIN, lnGNOLL, lnABYSSAL, lnGIANT, lnINFERNAL, lnUNDERCOMMON, 0 };
static int goodBonusLang[] = { lnCELESTIAL, lnAURAN, lnELVEN, lnSYLVAN, 0 };

static const struct {
  int                   id;
  int                   speed;
  int                   challengeRating;
  int                   size;
  int                   extraHitDieCount;
  int                   extraHitDie;
  int                   preferredClass;
  int                   usualAlignment;
  RACIALBONUS*          maleBonuses;
  RACIALBONUS*          femaleBonuses;
  DNDRACIALHEIGHTWEIGHT male;
  DNDRACIALHEIGHTWEIGHT female;
  int*                  automaticLanguages;
  int*                  bonusLanguages;
  char*                 name;
} s_races[] = {
  { rcAASIMAR,              30,  0, szMEDIUM,  0, 0, pcPALADIN,   alGOOD,                    aasimarBonuses,      aasimarBonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "aasimar" },
  { rcARANEA,               50,  4, szMEDIUM,  3, 8, pcSORCERER,  alLCNEUTRAL | alGENEUTRAL, araneaBonuses,       araneaBonuses,       {  2,  8, 2,  4,   100, 4,  4 }, { 2,   8, 2,  4,   100, 4,  4 }, sylvanLanguages,      araneaBonusLang, "aranea" },
  { rcAZER,                 30,  2, szMEDIUM,  2, 8, pcFIGHTER,   alLAWFUL | alGENEUTRAL,    azerBonuses,         azerBonuses,         {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, ignanLanguages,       dwarvenBonusLang,"azer" },
  { rcBUGBEAR,              30,  2, szMEDIUM,  3, 8, pcROGUE,     alCHAOTIC | alEVIL,        bugbearBonuses,      bugbearBonuses,      {  6,  5, 2,  6,   170, 1,  8 }, { 6,   4, 2,  6,   160, 1,  8 }, bugbearLanguages,     evilBonusLang,   "bugbear" },
  { rcCENTAUR,              50,  3, szLARGE,   4, 8, pcRANGER,    alLCNEUTRAL | alGOOD,      centaurBonuses,      centaurBonuses,      {  7,  6, 2, 10,   600, 3,  8 }, { 7,   6, 2, 10,   600, 3,  8 }, centaurLanguages,     elvenBonusLang,  "centaur" },
  { rcDOPPLEGANGER,         30,  3, szMEDIUM,  4, 8, 0,           alGENEUTRAL,               dopplegangerBonuses, dopplegangerBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       evilBonusLang,   "doppleganger" },
  { rcDRIDER,               30,  7, szLARGE,   6, 8, pcSORCERER,  alCHAOTIC | alEVIL,        driderBonuses,       driderBonuses,       {  7,  6, 2, 10,   600, 3,  8 }, { 7,   6, 2, 10,   600, 3,  8 }, undercommonLanguages, evilBonusLang,   "drider" },
  { rcDWARF_DEEP,           20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alGENEUTRAL,               deepDwarfBonuses,    deepDwarfBonuses,    {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (deep)" },
  { rcDWARF_DERRO,          20,  1, szMEDIUM,  0, 0, pcSORCERER,  alCHAOTIC | alEVIL,        derroBonuses,        derroBonuses,        {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (derro)" },
  { rcDWARF_DUERGAR,        20,  1, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alEVIL,         duergarBonuses,      duergarBonuses,      {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (duergar)" },
  { rcDWARF_HILL,           20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL,                  dwarvenHBonuses,     dwarvenHBonuses,     {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (hill)" },
  { rcDWARF_MOUNTAIN,       20,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alGOOD,         mtnDwarfBonuses,     mtnDwarfBonuses,     {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (mountain)" },
  { rcELF_AQUATIC,          30,  0, szMEDIUM,  0, 0, pcFIGHTER,   alCHAOTIC,                 aqElfBonuses,        aqElfBonuses,        {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (aquatic)" },
  { rcELF_DROW,             30,  1, szMEDIUM,  0, 0, pcWIZARD,    alLCNEUTRAL | alEVIL,      drowMaleBonuses,     drowFemaleBonuses,   {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, drowLanguages,        elvenBonusLang,  "elf (drow)" },
  { rcELF_GRAY,             30,  0, szMEDIUM,  0, 0, pcWIZARD,    alCHAOTIC | alGOOD,        grayElfBonuses,      grayElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (gray)" },
  { rcELF_HIGH,             30,  0, szMEDIUM,  0, 0, pcWIZARD,    alCHAOTIC,                 elvenHBonuses,       elvenHBonuses,       {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (high)" },
  { rcELF_WILD,             30,  0, szMEDIUM,  0, 0, pcSORCERER,  alCHAOTIC | alGOOD,        wildElfBonuses,      wildElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (wild)" },
  { rcELF_WOOD,             30,  0, szMEDIUM,  0, 0, pcRANGER,    alLCNEUTRAL,               woodElfBonuses,      woodElfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (wood)" },
  { rcETTIN,                40,  5, szLARGE,  10, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        ettinBonuses,        ettinBonuses,        { 12,  0, 2, 12,  4500, 9, 12 }, { 12,  0, 2, 12,  4500, 9, 12 }, 0,                    evilBonusLang,   "ettin" },
  { rcGIANT_CLOUD,          50, 11, szHUGE,   17, 8, pcSORCERER,  alLCNEUTRAL,               cloudGiantBonuses,   cloudGiantBonuses,   { 17,  0, 2, 12,  4800, 3, 20 }, { 16,  6, 2, 12,  4600, 3, 20 }, giantLanguages,       goodBonusLang,   "giant, cloud" },
  { rcGIANT_FIRE,           40, 10, szLARGE,  15, 8, pcCLERIC,    alLAWFUL | alEVIL,         fireGiantBonuses,    fireGiantBonuses,    { 11,  6, 1, 12,  6850, 2, 20 }, { 11,  0, 1, 12,  6650, 2, 20 }, giantLanguages,       evilBonusLang,   "giant, fire" },
  { rcGIANT_FROST,          40,  9 ,szLARGE,  14, 8, pcCLERIC,    alCHAOTIC | alEVIL,        frostGiantBonuses,   frostGiantBonuses,   { 14,  0, 2, 12,  2600, 2, 20 }, { 13,  8, 2, 12,  2500, 2, 20 }, giantLanguages,       evilBonusLang,   "giant, frost" },
  { rcGIANT_HILL,           40,  7, szLARGE,  12, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        hillGiantBonuses,    hillGiantBonuses,    {  9,  8, 2, 10,  1000, 1, 10 }, {  9,  8, 2, 10,  1000, 1, 10 }, giantLanguages,       evilBonusLang,   "giant, hill" },
  { rcGIANT_STONE,          40,  8, szLARGE,  14, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, stoneGiantBonuses,   stoneGiantBonuses,   { 11,  4, 2,  8,  1400, 2, 10 }, { 11,  4, 2,  8,  1400, 2, 10 }, giantLanguages,       evilBonusLang,   "giant, stone" },
  { rcGIANT_STORM,          50, 13, szHUGE,   19, 8, pcSORCERER,  alCHAOTIC | alGOOD,        stormGiantBonuses,   stormGiantBonuses,   { 20,  0, 2, 12, 11500, 4, 20 }, { 20,  0, 2, 12, 11500, 4, 20 }, giantLanguages,       goodBonusLang,   "giant, storm" },
  { rcGNOLL,                30,  1, szMEDIUM,  2, 8, pcRANGER,    alCHAOTIC | alEVIL,        gnollBonuses,        gnollBonuses,        {  6,  8, 2, 10,   180, 2,  6 }, { 6,   4, 2, 10,   180, 2,  6 }, gnollLanguages,       evilBonusLang,   "gnoll" },
  { rcGNOME_FOREST,         20,  0, szSMALL,   0, 0, pcWIZARD,    alLCNEUTRAL | alGOOD,      forestGnomeBonuses,  forestGnomeBonuses,  {  1, 11, 2,  4,    25, 1,  1 }, { 2,   0, 2,  4,    25, 1,  1 }, forestGnomeLanguages, halflingBonusLang, "gnome (forest)" },
  { rcGNOME_ROCK,           20,  0, szSMALL,   0, 0, pcWIZARD,    alGOOD,                    gnomeRBonuses,       gnomeRBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, gnomeLanguages,       halflingBonusLang, "gnome (rock)" },
  { rcGNOME_SVIRFNEBLIN,    20,  1, szSMALL,   0, 0, pcWIZARD,    alLCNEUTRAL,               svirfneblinBonuses,  svirfneblinBonuses,  {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, svirfneblinLanguages, halflingBonusLang, "gnome (svirfneblin)" },
  { rcGOBLIN,               30,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL | alEVIL,      goblinBonuses,       goblinBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "goblin" },
  { rcGRIMLOCK,             30,  1, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alEVIL,      grimlockBonuses,     grimlockBonuses,     {  4,  5, 2,  6,   100, 2,  6 }, { 4,   5, 2,  6,   100, 2,  6 }, goblinLanguages,      evilBonusLang,   "grimlock" },
  { rcHAG_ANNIS,            40,  6, szLARGE,   7, 8, pcSORCERER,  alCHAOTIC | alEVIL,        annisBonuses,        annisBonuses,        {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, giantLanguages,       evilBonusLang,   "hag, annis" },
  { rcHAG_GREEN,            30,  5, szLARGE,   9, 8, pcSORCERER,  alCHAOTIC | alEVIL,        greenHagBonuses,     greenHagBonuses,     {  6,  5, 2,  6,   170, 1,  8 }, { 6,   4, 2,  6,   160, 1,  8 }, giantLanguages,       evilBonusLang,   "hag, green" },
  { rcHAG_SEA,              30,  4, szLARGE,   3, 8, pcSORCERER,  alCHAOTIC | alEVIL,        seaHagBonuses,       seaHagBonuses,       {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, giantLanguages,       evilBonusLang,   "hag, sea" },
  { rcHALFELF,              30,  0, szMEDIUM,  0, 0, 0,           0,                         halfElvenBonuses,    halfElvenBonuses,    {  4,  7, 2,  8,   100, 2,  4 }, { 4,   5, 2,  8,    80, 2,  4 }, elfLanguages,         0,               "half-elf" },
  { rcHALFLING_DEEP,        20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               halflingDeepBonuses, halflingDeepBonuses, {  2,  8, 2,  4,    30, 1,  1 }, { 2,   6, 2,  4,    25, 1,  1 }, deepHalfLanguages,    halflingBonusLang, "halfling (deep)" },
  { rcHALFLING_LIGHTFOOT,   20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               halflingLFBonuses,   halflingLFBonuses,   {  2,  8, 2,  4,    30, 1,  1 }, { 2,   6, 2,  4,    25, 1,  1 }, halflingLanguages,    halflingBonusLang, "halfling (lightfoot)" },
  { rcHALFLING_TALLFELLOW,  20,  0, szSMALL,   0, 0, pcROGUE,     alLCNEUTRAL,               tallfellowBonuses,   tallfellowBonuses,   {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, tallfellowLanguages,  halflingBonusLang, "halfling (tallfellow)" },
  { rcHALFORC,              30,  0, szMEDIUM,  0, 0, pcBARBARIAN, alCHAOTIC,                 halforcBonuses,      halforcBonuses,      {  4, 10, 2, 10,   130, 2,  4 }, { 4,   4, 2, 10,    90, 2,  4 }, halforcLanguages,     evilBonusLang,   "half-orc" },
  { rcHARPY,                20,  4, szMEDIUM,  7, 8, pcBARD,      alCHAOTIC | alEVIL,        harpyBonuses,        harpyBonuses,        {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, humanLanguages,       evilBonusLang,   "harpy" },
  { rcHOBGOBLIN,            30,  0, szMEDIUM,  0, 0, pcFIGHTER,   alLAWFUL | alEVIL,         hobgoblinBonuses,    hobgoblinBonuses,    {  5,  6, 2, 10,   180, 2,  6 }, { 5,   4, 2, 10,   170, 2,  6 }, bugbearLanguages,     evilBonusLang,   "hobgoblin" },
  { rcHUMAN,                30,  0, szMEDIUM,  0, 0, 0,           0,                         0,                   0,                   {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "human" },
  { rcKOBOLD,               30,  0, szSMALL,   0, 0, pcSORCERER,  alLAWFUL | alEVIL,         koboldBonuses,       koboldBonuses,       {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, draconicLanguages,    evilBonusLang,   "kobold" },
  { rcKUOTOA,               20,  2, szMEDIUM,  2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      kuotoaBonuses,       kuotoaBonuses,       {  4,  6, 2,  6,    85, 1,  6 }, { 4,   6, 2,  6,    80, 1,  6 }, kuotoaLanguages,      evilBonusLang,   "kuo-toa" },
  { rcLIZARDFOLK,           30,  1, szMEDIUM,  2, 8, pcDRUID,     alLCNEUTRAL,               lizardFolkBonuses,   lizardFolkBonuses,   {  5,  8, 2, 10,   180, 2,  6 }, { 5,   8, 2, 10,   180, 2,  6 }, draconicLanguages,    evilBonusLang,   "lizardfolk" },
  { rcLOCATHAH,             10,  0, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, locathahBonuses,     locathahBonuses,     {  4,  6, 2,  6,   150, 1,  6 }, { 4,   6, 2,  6,   150, 1,  6 }, merfolkLanguages,     evilBonusLang,   "locathah" },
  { rcMEDUSA,               30,  7, szMEDIUM,  6, 8, pcROGUE,     alLAWFUL | alEVIL,         medusaBonuses,       medusaBonuses,       {  4, 10, 2, 10,   120, 2,  4 }, { 4,   8, 2, 10,   105, 2,  4 }, undercommonLanguages, evilBonusLang,   "medusa" },
  { rcMERFOLK,               5,  0, szMEDIUM,  0, 0, pcBARD,      alLCNEUTRAL | alGENEUTRAL, merfolkBonuses,      merfolkBonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   8, 2, 10,   105, 2,  4 }, merfolkLanguages,     evilBonusLang,   "merfolk" },
  { rcMINDFLAYER,           30,  8, szMEDIUM,  8, 8, pcSORCERER,  alLAWFUL | alEVIL,         mindflayerBonuses,   mindflayerBonuses,   {  5,  0, 2, 10,   130, 2,  4 }, { 4,   9, 2, 10,   100, 2,  4 }, undercommonLanguages, evilBonusLang,   "mind flayer" },
  { rcMINOTAUR,             30,  4, szLARGE,   6, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        minotaurBonuses,     minotaurBonuses,     {  6,  8, 2,  6,   250, 2,  8 }, { 6,   8, 4,  6,   250, 2,  8 }, giantLanguages,       evilBonusLang,   "minotaur" },
  { rcOGRE,                 30,  2, szLARGE,   4, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        ogreBonuses,         ogreBonuses,         {  8,  6, 4,  6,   250, 2,  8 }, { 8,   6, 4,  6,   250, 2,  8 }, giantLanguages,       evilBonusLang,   "ogre" },
  { rcOGREMAGE,             30,  8, szLARGE,   5, 8, pcSORCERER,  alLAWFUL | alEVIL,         ogreMageBonuses,     ogreMageBonuses,     {  9,  0, 4,  6,   450, 2,  8 }, { 9,   0, 4,  6,   450, 2,  8 }, giantLanguages,       evilBonusLang,   "ogre mage" },
  { rcORC,                  30,  0, szMEDIUM,  0, 0, pcBARBARIAN, alCHAOTIC | alEVIL,        orcBonuses,          orcBonuses,          {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, orcLanguages,         evilBonusLang,   "orc" },
  { rcSAHUAGIN,             30,  2, szMEDIUM,  2, 8, pcRANGER,    alLAWFUL | alEVIL,         sahuaginBonuses,     sahuaginBonuses,     {  5,  1, 2, 10,   150, 2,  4 }, { 5,   0, 2, 10,   150, 2,  4 }, kuotoaLanguages,      evilBonusLang,   "sahuagin" },
  { rcTIEFLING,             30,  0, szMEDIUM,  0, 0, pcROGUE,     alEVIL,                    tieflingBonuses,     tieflingBonuses,     {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "tiefling" },
  { rcTROGLODYTE,           30,  1, szMEDIUM,  2, 8, pcCLERIC,    alCHAOTIC | alEVIL,        troglodyteBonuses,   troglodyteBonuses,   {  4,  5, 2,  6,   130, 1,  6 }, { 4,   5, 2,  6,   120, 1,  6 }, draconicLanguages,    evilBonusLang,   "troglodyte" },
  { rcTROLL,                30,  5, szLARGE,   6, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        trollBonuses,        trollBonuses,        {  8,  6, 1, 12,   400, 2, 20 }, {  8,  6, 1, 12,   400, 2, 20 }, giantLanguages,       evilBonusLang,   "troll" },
  { rcYUANTI_ABOMINATION,   30,  7, szLARGE,   9, 8, pcCLERIC,    alCHAOTIC | alEVIL,        yuanti3Bonuses,      yuanti3Bonuses,      {  7,  6, 1, 12,   380, 2,  6 }, {  7,  6, 1, 12,   380, 2,  6 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, abomination" },
  { rcYUANTI_HALFBLOOD,     30,  5, szMEDIUM,  7, 8, pcRANGER,    alCHAOTIC | alEVIL,        yuanti2Bonuses,      yuanti2Bonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, halfblood" },
  { rcYUANTI_PUREBLOOD,     30,  5, szMEDIUM,  6, 8, pcRANGER,    alCHAOTIC | alEVIL,        yuanti1Bonuses,      yuanti1Bonuses,      {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, yuantiLanguages,      evilBonusLang,   "yuan-ti, pureblood" },
  { rcCC_ABANDONED,         30,  0, szLARGE,   2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_abandonedBonuses, cc_abandonedBonuses, {  8,  6, 4,  6,   250, 2,  8 }, { 8,   6, 4,  6,   250, 2,  8 }, 0,                    0,               "abandoned" },
  { rcCC_ASAATH,            40,  2, szMEDIUM,  3, 8, pcFIGHTER,   alCHAOTIC | alEVIL,        cc_asaathBonuses,    cc_asaathBonuses,    {  5,  6, 2, 10,   100, 2,  4 }, { 5,   4, 2, 10,    85, 2,  4 }, asaathLanguages,      evilBonusLang,   "asaath" },
  { rcCC_BATDEVIL,          30,  0, szMEDIUM,  2, 8, pcROGUE,     alLCNEUTRAL | alGENEUTRAL, cc_batDevilBonuses,  cc_batDevilBonuses,  {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, 0,                    0,               "bat devil" },
  { rcCC_PLAGUEWRETCH,      30,  2, szMEDIUM,  3, 8, pcFIGHTER,   alLCNEUTRAL | alEVIL,      cc_plagueWretchBonuses, cc_plagueWretchBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,              0,               "plague wretch (carnival krewe)" },
  { rcCC_CHARDUNI,          20,  0, szMEDIUM,  1, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_charduniBonuses,  cc_charduniBonuses,  {  3, 11, 2,  4,   130, 2,  6 }, { 3,   9, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"charduni" },
  { rcCC_COALGOBLIN,        30,  0, szSMALL,   2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      cc_coalGoblinBonuses,cc_coalGoblinBonuses,{  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "coal goblin" },
  { rcCC_DWARF_FORSAKEN,    15,  0, szMEDIUM,  1, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_fdwarfBonuses,    cc_fdwarfBonuses,    {  3,  9, 2,  4,   130, 2,  6 }, { 3,   7, 2,  4,   100, 2,  6 }, dwarfLanguages,       dwarvenBonusLang,"dwarf (forsaken)" },
  { rcCC_ELF_FORSAKEN,      30,  0, szMEDIUM,  1, 8, pcFIGHTER,   alCHAOTIC | alGENEUTRAL,   cc_felfBonuses,      cc_felfBonuses,      {  4,  5, 2,  6,    85, 1,  6 }, { 4,   5, 2,  6,    80, 1,  6 }, elfLanguages,         elvenBonusLang,  "elf (forsaken)" },
  { rcCC_ICE_GHOUL,         40,  1, szMEDIUM,  2, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_iceGhoulBonuses,  cc_iceGhoulBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "ice ghoul" },
  { rcCC_MANTICORA,         30,  2, szMEDIUM,  2, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_manticoraBonuses, cc_manticoraBonuses, {  5,  2, 2, 10,   100, 2,  4 }, { 5,   2, 2, 10,    85, 2,  4 }, humanLanguages,       evilBonusLang,   "manticora" },
  { rcCC_MORGAUNT,          60,  1, szMEDIUM,  3, 8, npcCOMMONER, alLCNEUTRAL | alEVIL,      cc_morgauntBonuses,  cc_morgauntBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "morgaunt" }, 
  { rcCC_PROUD,             60,  1, szLARGE,   3, 8, pcBARBARIAN, alCHAOTIC | alEVIL,        cc_proudBonuses,     cc_proudBonuses,     {  6,  6, 2, 10,   400, 3,  8 }, { 6,   6, 2, 10,   400, 3,  8 }, humanLanguages,       0,               "proud" },
  { rcCC_RATMAN,            30,  0, szMEDIUM,  1, 8, pcROGUE,     alLAWFUL | alEVIL,         cc_ratmanBonuses,    cc_ratmanBonuses,    {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman" }, 
  { rcCC_RATMAN_BROWNGORGER,30,  0, szMEDIUM,  1, 8, pcFIGHTER,   alLAWFUL | alEVIL,         cc_bgratmanBonuses,  cc_bgratmanBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, brown gorger" }, 
  { rcCC_RATMAN_DISEASED,   30,  0, szMEDIUM,  1, 8, pcCLERIC,    alLAWFUL | alEVIL,         cc_dratmanBonuses,   cc_dratmanBonuses,   {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, the diseased" }, 
  { rcCC_RATMAN_FOAMER,     30,  0, szMEDIUM,  2, 8, npcWARRIOR,  alLAWFUL | alEVIL,         cc_fratmanBonuses,   cc_fratmanBonuses,   {  6,  6, 2, 10,   180, 3,  8 }, { 6,   6, 2, 10,   180, 3,  8 }, humanLanguages,       0,               "ratman, foamer" },
  { rcCC_RATMAN_REDWITCH,   30,  0, szMEDIUM,  1, 8, pcWIZARD,    alLAWFUL | alEVIL,         cc_rwratmanBonuses,  cc_rwratmanBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, humanLanguages,       0,               "ratman, red witch" },
  { rcCC_SKINDEVIL,         60,  4, szMEDIUM,  5, 8, pcROGUE,     alCHAOTIC | alGENEUTRAL,   cc_skinDevilBonuses, cc_skinDevilBonuses, {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, majorLanguages,       0,               "skin devil" },
  { rcCC_SPIDEREYEGOBLIN,   30,  0, szSMALL,   2, 8, pcROGUE,     alLCNEUTRAL | alEVIL,      cc_segoblinBonuses,  cc_segoblinBonuses,  {  3,  0, 2,  4,    40, 1,  1 }, { 2,  10, 2,  4,    35, 1,  1 }, goblinLanguages,      evilBonusLang,   "spider-eye goblin" },
  { rcCC_STEPPETROLL,       40,  5, szLARGE,   8, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_strollBonuses,    cc_strollBonuses,    {  8,  6, 1, 12,   400, 2, 20 }, {  8,  6, 1, 12,   400, 2, 20 }, giantLanguages,       evilBonusLang,   "steppe troll" },
  { rcCC_STRIFEELEMENTAL,   30,  2, szMEDIUM,  4, 8, pcFIGHTER,   alCHAOTIC | alGENEUTRAL,   cc_selementBonuses,  cc_selementBonuses,  {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, majorLanguages,       0,               "strife elemental" },
  { rcCC_TOKALTRIBESMAN,    30,  0, szMEDIUM,  2, 8, pcBARBARIAN, alLCNEUTRAL | alGENEUTRAL, cc_tokalBonuses,     cc_tokalBonuses,     {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "tokal tribesman" },
  { rcCC_UBANTUTRIBESMAN,   30,  0, szMEDIUM,  1, 8, pcBARBARIAN, alLAWFUL | alGENEUTRAL,    cc_ubantuBonuses,    cc_ubantuBonuses,    {  4, 10, 2, 10,   120, 2,  4 }, { 4,   5, 2, 10,    85, 2,  4 }, 0,                    0,               "ubantu tribesman" },
  { 0,                       0,  0, 0,         0, 0, 0,           0,                         0,                   0,                   {  0,  0, 0,  0,     0, 0,  0 }, {  0,  0, 0,  0,     0, 0,  0 }, 0,                    0,               0 }
};


static const struct {
  int   id;
  int   type;
  int   cost; /* copper pieces */
  int   acBonus;
  int   maxDex;
  int   checkPenalty;
  int   arcaneSpellFailure;
  char* name;
} s_armors[] = {                    
  { arPADDED,               atLIGHT,    500, 1,  8,   0,  5, "padded" },
  { arLEATHER,              atLIGHT,   1000, 2,  6,   0, 10, "leather" },
  { arSTUDDEDLEATHER,       atLIGHT,   2500, 3,  5,  -1, 15, "studded leather" },
  { arCHAINSHIRT,           atLIGHT,  10000, 4,  4,  -2, 20, "chain shirt" },
  { arHIDE,                atMEDIUM,   1500, 3,  4,  -3, 20, "hide" },
  { arSCALEMAIL,           atMEDIUM,   5000, 4,  3,  -4, 25, "scale mail" },
  { arCHAINMAIL,           atMEDIUM,  15000, 5,  2,  -5, 30, "chainmail" },
  { arBREASTPLATE,         atMEDIUM,  20000, 5,  3,  -4, 25, "breastplate" },
  { arSPLINTMAIL,           atHEAVY,  20000, 6,  0,  -7, 40, "splint mail" },
  { arBANDEDMAIL,           atHEAVY,  25000, 6,  1,  -6, 35, "banded mail" },
  { arHALFPLATE,            atHEAVY,  60000, 7,  0,  -7, 40, "half-plate" },
  { arFULLPLATE,            atHEAVY, 150000, 8,  1,  -6, 35, "full plate" },
  { arBUCKLER,             atSHIELD,   1500, 1, 99,  -1,  5, "buckler" },
  { arSHIELD_SMALL_WOODEN, atSHIELD,    300, 1, 99,  -1,  5, "shield, small, wooden" },
  { arSHIELD_SMALL_STEEL,  atSHIELD,    900, 1, 99,  -1,  5, "shield, small, steel" }, 
  { arSHIELD_LARGE_WOODEN, atSHIELD,    700, 2, 99,  -2, 15, "shield, large, wooden" },
  { arSHIELD_LARGE_STEEL,  atSHIELD,   2000, 2, 99,  -2, 15, "shield, large, steel" },
  { arSHIELD_TOWER,        atSHIELD,   3000, 0, 99, -10, 50, "shield, tower" },
  { 0,                     0,          0,    0,  0,   0,  0, 0 }
};


static const struct {
  int   id;
  int   size;
  int   cost; /* copper pieces */
  int   type;
  char* name;
} s_weapons[] = {                         
  { wpGAUNTLET,             szTINY,         200, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "gauntlet" },
  { wpUNARMED,              szTINY,           0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "strike, unarmed" },
  { wpDAGGER,               szTINY,         200, wtMELEE | wtPIERCING | wtSIMPLE,                   "dagger" },
  { wpDAGGER_PUNCHING,      szTINY,         200, wtMELEE | wtPIERCING | wtSIMPLE,                   "dagger, punching" },
  { wpGAUNTLET_SPIKED,      szTINY,         500, wtMELEE | wtPIERCING | wtSIMPLE,                   "gauntlet, spiked" },
  { wpMACE_LIGHT,           szSMALL,        500, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "mace, light" },
  { wpSICKLE,               szSMALL,        600, wtMELEE | wtSLASHING | wtSIMPLE,                   "sickle" },
  { wpCLUB,                 szMEDIUM,         0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "club" },
  { wpHALFSPEAR,            szMEDIUM,       100, wtMELEE | wtPIERCING | wtSIMPLE,                   "halfspear" },
  { wpMACE_HEAVY,           szMEDIUM,      1200, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "mace, heavy" },
  { wpMORNINGSTAR,          szMEDIUM,       800, wtMELEE | wtBLUDGEONING | wtPIERCING | wtSIMPLE,   "morningstar" },
  { wpQUARTERSTAFF,         szLARGE,          0, wtMELEE | wtBLUDGEONING | wtSIMPLE,                "quarterstaff" },
  { wpSHORTSPEAR,           szLARGE,        200, wtMELEE | wtPIERCING | wtSIMPLE,                   "shortspear" },
  { wpCROSSBOW_LIGHT,       szSMALL,       3500, wtRANGED | wtPIERCING | wtSIMPLE,                  "crossbow, light" },
  { wpDART,                 szSMALL,         50, wtRANGED | wtPIERCING | wtSIMPLE,                  "dart" },
  { wpSLING,                szSMALL,          0, wtRANGED | wtBLUDGEONING | wtSIMPLE,               "sling" },
  { wpCROSSBOW_HEAVY,       szMEDIUM,      5000, wtRANGED | wtPIERCING | wtSIMPLE,                  "crossbow, heavy" },
  { wpJAVELIN,              szMEDIUM,       100, wtRANGED | wtPIERCING | wtSIMPLE,                  "javelin" },
  { wpAXE_THROWING,         szSMALL,        800, wtMELEE | wtSLASHING | wtMARTIAL,                  "axe, throwing" },
  { wpHAMMER_LIGHT,         szSMALL,        100, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "hammer, light" },
  { wpHANDAXE,              szSMALL,        600, wtMELEE | wtSLASHING | wtMARTIAL,                  "handaxe" },
  { wpLANCE_LIGHT,          szSMALL,        600, wtMELEE | wtPIERCING | wtMARTIAL,                  "lance, light" },
  { wpPICK_LIGHT,           szSMALL,        400, wtMELEE | wtPIERCING | wtMARTIAL,                  "pick, light" },
  { wpSAP,                  szSMALL,        100, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "sap" },
  { wpSWORD_SHORT,          szSMALL,       1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "sword, short" },
  { wpBATTLEAXE,            szMEDIUM,      1000, wtMELEE | wtSLASHING | wtMARTIAL,                  "battleaxe" },
  { wpFLAIL_LIGHT,          szMEDIUM,       800, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "flail, light" },
  { wpLANCE_HEAVY,          szMEDIUM,      1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "lance, heavy" },
  { wpLONGSWORD,            szMEDIUM,      1500, wtMELEE | wtSLASHING | wtMARTIAL,                  "longsword" },
  { wpPICK_HEAVY,           szMEDIUM,       800, wtMELEE | wtPIERCING | wtMARTIAL,                  "pick, heavy" },
  { wpRAPIER,               szMEDIUM,      2000, wtMELEE | wtPIERCING | wtMARTIAL,                  "rapier" },
  { wpSCIMITAR,             szMEDIUM,      1500, wtMELEE | wtSLASHING | wtMARTIAL,                  "scimitar" },
  { wpTRIDENT,              szMEDIUM,      1500, wtMELEE | wtPIERCING | wtMARTIAL,                  "trident" },
  { wpWARHAMMER,            szMEDIUM,      1200, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "warhammer" },
  { wpFALCHION,             szLARGE,       7500, wtMELEE | wtSLASHING | wtMARTIAL,                  "falchion" },
  { wpFLAIL_HEAVY,          szLARGE,       1500, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "flail, heavy" },
  { wpGLAIVE,               szLARGE,        800, wtMELEE | wtSLASHING | wtMARTIAL,                  "glaive" },
  { wpGREATAXE,             szLARGE,       2000, wtMELEE | wtSLASHING | wtMARTIAL,                  "greataxe" },
  { wpGREATCLUB,            szLARGE,        500, wtMELEE | wtBLUDGEONING | wtMARTIAL,               "greatclub" },
  { wpGREATSWORD,           szLARGE,       5000, wtMELEE | wtSLASHING | wtMARTIAL,                  "greatsword" },
  { wpGUISARME,             szLARGE,        900, wtMELEE | wtSLASHING | wtMARTIAL,                  "guisarme" },
  { wpHALBERD,              szLARGE,       1000, wtMELEE | wtPIERCING | wtSLASHING | wtMARTIAL,     "halberd" },
  { wpLONGSPEAR,            szLARGE,        500, wtMELEE | wtPIERCING | wtMARTIAL,                  "longspear" },
  { wpRANSEUR,              szLARGE,       1000, wtMELEE | wtPIERCING | wtMARTIAL,                  "ranseur" },
  { wpSCYTHE,               szLARGE,       1800, wtMELEE | wtPIERCING | wtSLASHING | wtMARTIAL,     "scythe" },
  { wpSHORTBOW,             szMEDIUM,      3000, wtRANGED | wtPIERCING | wtMARTIAL,                 "shortbow" },
  { wpSHORTBOW_COMPOSITE,   szMEDIUM,      7500, wtRANGED | wtPIERCING | wtMARTIAL,                 "shortbow, composite" },
  { wpLONGBOW,              szLARGE,       7500, wtRANGED | wtPIERCING | wtMARTIAL,                 "longbow" },
  { wpLONGBOW_COMPOSITE,    szLARGE,      10000, wtRANGED | wtPIERCING | wtMARTIAL,                 "longbow, composite" },
  { wpKUKRI,                szTINY,         800, wtMELEE | wtSLASHING | wtEXOTIC,                   "kukri" },
  { wpKAMA,                 szSMALL,        200, wtMELEE | wtSLASHING | wtEXOTIC,                   "kama" },
  { wpNUNCHAKU,             szSMALL,        200, wtMELEE | wtBLUDGEONING | wtEXOTIC,                "nunchaku" },
  { wpSIANGHAM,             szSMALL,        300, wtMELEE | wtPIERCING | wtEXOTIC,                   "siangham" },
  { wpSWORD_BASTARD,        szMEDIUM,      3500, wtMELEE | wtSLASHING | wtEXOTIC,                   "sword, bastard" },
  { wpWARAXE_DWARVEN,       szMEDIUM,      3000, wtMELEE | wtSLASHING | wtEXOTIC,                   "waraxe, dwarven" },
  { wpHAMMER_GNOMEHOOKED,   szMEDIUM,      2000, wtMELEE | wtBLUDGEONING | wtPIERCING | wtEXOTIC,   "hammer, gnome hooked" },
  { wpAXE_ORCDOUBLE,        szLARGE,       6000, wtMELEE | wtSLASHING | wtEXOTIC,                   "axe, orc double" },
  { wpCHAIN_SPIKED,         szLARGE,       2500, wtMELEE | wtPIERCING | wtEXOTIC,                   "chain, spiked" },
  { wpFLAIL_DIRE,           szLARGE,       9000, wtMELEE | wtBLUDGEONING | wtEXOTIC,                "flail, dire" },
  { wpSWORD_TWOBLADED,      szLARGE,      10000, wtMELEE | wtSLASHING | wtEXOTIC,                   "sword, two-bladed" },
  { wpURGOSH_DWARVEN,       szLARGE,       5000, wtMELEE | wtSLASHING | wtPIERCING | wtEXOTIC,      "urgosh, dwarven" },
  { wpCROSSBOW_HAND,        szTINY,       10000, wtRANGED | wtPIERCING | wtEXOTIC,                  "crossbow, hand" },
  { wpSHURIKEN,             szTINY,         100, wtRANGED | wtPIERCING | wtEXOTIC,                  "shuriken" },
  { wpWHIP,                 szSMALL,        100, wtRANGED | wtSLASHING | wtEXOTIC,                  "whip" },
  { wpCROSSBOW_REPEATING,   szMEDIUM,     25000, wtRANGED | wtPIERCING | wtEXOTIC,                  "crossbow, repeating" },
  { wpNET,                  szMEDIUM,      2000, wtRANGED | wtEXOTIC,                               "net" },
  { 0,                      0,                0, 0,                                                 0 }
};


static const struct {
  int   id;
  int   acMod;
  int   grappleMod;
  int   hideCheck;
  char* name;
} s_sizes[] = {
  { szFINE,        8, -16,  16, "fine" },
  { szDIMINUTIVE,  4, -12,  12, "diminutive" },
  { szTINY,        2,  -8,   8, "tiny" },
  { szSMALL,       1,  -4,   4, "small" },
  { szMEDIUM,      0,   0,   0, "medium" },
  { szLARGE,      -1,   4,  -4, "large" },
  { szHUGE,       -2,   8,  -8, "huge" },
  { szGARGANTUAN, -4,  12, -12, "gargantuan" },
  { szCOLOSSAL,   -8,  16, -16, "colossal" },
  { 0,             0,   0,   0, 0 }
};


static const struct {
  int   id;
  char* name;
} s_magicSchools[] = {
  { ssUNIVERSAL,     "universal" },
  { ssABJURATION,    "abjuration" },
  { ssCONJURATION,   "conjuration" },
  { ssDIVINATION,    "divination" },
  { ssENCHANTMENT,   "enchanment" },
  { ssEVOCATION,     "evocation" },
  { ssILLUSION,      "illusion" },
  { ssNECROMANCY,    "necromancy" },
  { ssTRANSMUTATION, "transmutation" },
  { 0,               0 }
};


static const struct {
  int   id;
  int   school;
  char* name;
} s_spells[] = {
  { spACIDFOG,                            ssCONJURATION,     "Acid Fog" },
  { spAID,                                ssENCHANTMENT,     "Aid" },
  { spAIRWALK,                            ssTRANSMUTATION,   "Air Walk" },
  { spALARM,                              ssABJURATION,      "Alarm" },
  { spALTERSELF,                          ssTRANSMUTATION,   "Alter Self" },
  { spANALYZEDWEOMER,                     ssDIVINATION,      "Analyze Dweomer" },
  { spANIMALFRIENDSHIP,                   ssENCHANTMENT,     "Animal Friendship" },
  { spANIMALGROWTH,                       ssTRANSMUTATION,   "Animal Growth" },
  { spANIMALMESSENGER,                    ssENCHANTMENT,     "Animal Messenger" },
  { spANIMALSHAPES,                       ssTRANSMUTATION,   "Animal Shapes" },
  { spANIMALTRANCE,                       ssENCHANTMENT,     "Animal Trance" },
  { spANIMATEDEAD,                        ssNECROMANCY,      "Animate Dead" },
  { spANIMATEOBJECTS,                     ssTRANSMUTATION,   "Animate Objects" },
  { spANIMATEROPE,                        ssTRANSMUTATION,   "Animate Rope" },
  { spANTILIFESHELL,                      ssABJURATION,      "Antilife Shell" },
  { spANTIMAGICFIELD,                     ssABJURATION,      "Antimagic Field" },
  { spANTIPATHY,                          ssENCHANTMENT,     "Antipathy" },
  { spANTIPLANTSHELL,                     ssABJURATION,      "Antiplant Shell" },
  { spARCANEEYE,                          ssDIVINATION,      "Arcane Eye" },
  { spARCANELOCK,                         ssABJURATION,      "Arcane Lock" },
  { spARCANEMARK,                         ssUNIVERSAL,       "Arcane Mark" },
  { spASTRALPROJECTION,                   ssNECROMANCY,      "Astral Projection" },
  { spATONEMENT,                          ssABJURATION,      "Atonement" },
  { spAUGURY,                             ssDIVINATION,      "Augury" },
  { spAWAKEN,                             ssTRANSMUTATION,   "Awaken" },
  { spBANE,                               ssENCHANTMENT,     "Bane" },
  { spBANISHMENT,                         ssABJURATION,      "Banishment" },
  { spBARKSKIN,                           ssTRANSMUTATION,   "Barkskin" },
  { spBESTOWCURSE,                        ssTRANSMUTATION,   "Bestow Curse" },
  { spBIGBYSCLENCHEDFIST,                 ssEVOCATION,       "Bigby's Clenched Fist" },
  { spBIGBYSCRUSHINGHAND,                 ssEVOCATION,       "Bigby's Crushing Hand" },
  { spBIGBYSFORCEFULHAND,                 ssEVOCATION,       "Bigby's Forceful Hand" },
  { spBIGBYSGRASPINGHAND,                 ssEVOCATION,       "Bigby's Grasping Hand" },
  { spBIGBYSINTERPOSINGHAND,              ssEVOCATION,       "Bigby's Interposing Hand" },
  { spBINDING,                            ssENCHANTMENT,     "Binding" },
  { spBLADEBARRIER,                       ssEVOCATION,       "Blade Barrier" },
  { spBLASPHEMY,                          ssEVOCATION,       "Blasphemy" },
  { spBLESS,                              ssENCHANTMENT,     "Bless" },
  { spBLESSWATER,                         ssTRANSMUTATION,   "Bless Water" },
  { spBLESSWEAPON,                        ssTRANSMUTATION,   "Bless Weapon" },
  { spBLINDNESSDEAFNESS,                  ssTRANSMUTATION,   "Blindness/Deafness" },
  { spBLINK,                              ssTRANSMUTATION,   "Blink" },
  { spBLUR,                               ssILLUSION,        "Blur" },
  { spBREAKENCHANTMENT,                   ssABJURATION,      "Break Enchantment" },
  { spBULLSSTRENGTH,                      ssTRANSMUTATION,   "Bull's Strength" },
  { spBURNINGHANDS,                       ssTRANSMUTATION,   "Burning Hands" },
  { spCALLLIGHTNING,                      ssEVOCATION,       "Call Lightning" },
  { spCALMANIMALS,                        ssENCHANTMENT,     "Calm Animals" },
  { spCALMEMOTIONS,                       ssENCHANTMENT,     "Calm Emotions" },
  { spCATSGRACE,                          ssTRANSMUTATION,   "Cat's Grace" },
  { spCAUSEFEAR,                          ssNECROMANCY,      "Cause Fear" },
  { spCHAINLIGHTNING,                     ssEVOCATION,       "Chain Lightning" },
  { spCHANGESELF,                         ssILLUSION,        "Change Self" },
  { spCHANGESTAFF,                        ssTRANSMUTATION,   "Changestaff" },
  { spCHAOSHAMMER,                        ssEVOCATION,       "Chaos Hammer" },
  { spCHARMMONSTER,                       ssENCHANTMENT,     "Charm Monster" },
  { spCHARMPERSON,                        ssENCHANTMENT,     "Charm Person" },
  { spCHARMPERSONORANIMAL,                ssENCHANTMENT,     "Charm Person or Animal" },
  { spCHILLMETAL,                         ssTRANSMUTATION,   "Chill Metal" },
  { spCHILLTOUCH,                         ssNECROMANCY,      "Chill Touch" },
  { spCIRCLEOFDEATH,                      ssNECROMANCY,      "Circle of Death" },
  { spCIRCLEOFDOOM,                       ssNECROMANCY,      "Circle of Doom" },
  { spCLAIRAUDIENCECLAIRVOYANCE,          ssDIVINATION,      "Clairaudience/Clairvoyance" },
  { spCLOAKOFCHAOS,                       ssABJURATION,      "Cloak of Chaos" },
  { spCLONE,                              ssNECROMANCY,      "Clone" },
  { spCLOUDKILL,                          ssCONJURATION,     "Cloudkill" },
  { spCOLORSPRAY,                         ssILLUSION,        "Color Spray" },
  { spCOMMAND,                            ssENCHANTMENT,     "Command" },
  { spCOMMANDPLANTS,                      ssENCHANTMENT,     "Command Plants" },
  { spCOMMUNE,                            ssDIVINATION,      "Commune" },
  { spCOMMUNEWITHNATURE,                  ssDIVINATION,      "Commune with Nature" },
  { spCOMPREHENDLANGUAGES,                ssDIVINATION,      "Comprehend Languages" },
  { spCONEOFCOLD,                         ssEVOCATION,       "Cone of Cold" },
  { spCONFUSION,                          ssENCHANTMENT,     "Confusion" },
  { spCONSECRATE,                         ssEVOCATION,       "Consecrate" },
  { spCONTACTOTHERPLANE,                  ssDIVINATION,      "Contact Other Plane" },
  { spCONTAGION,                          ssNECROMANCY,      "Contagion" },
  { spCONTINGENCY,                        ssEVOCATION,       "Contingency" },
  { spCONTINUALFLAME,                     ssEVOCATION,       "Continual Flame" },
  { spCONTROLPLANTS,                      ssTRANSMUTATION,   "Control Plants" },
  { spCONTROLUNDEAD,                      ssNECROMANCY,      "Control Undead" },
  { spCONTROLWATER,                       ssTRANSMUTATION,   "Control Water" },
  { spCONTROLWEATHER,                     ssTRANSMUTATION,   "Control Weather" },
  { spCONTROLWINDS,                       ssTRANSMUTATION,   "Control Winds" },
  { spCREATEFOODANDWATER,                 ssCONJURATION,     "Create Food and Water" },
  { spCREATEGREATERUNDEAD,                ssNECROMANCY,      "Create Greater Undead" },
  { spCREATEUNDEAD,                       ssNECROMANCY,      "Create Undead" },
  { spCREATEWATER,                        ssCONJURATION,     "Create Water" },
  { spCREEPINGDOOM,                       ssCONJURATION,     "Creeping Doom" },
  { spCURECRITICALWOUNDS,                 ssCONJURATION,     "Cure Critical Wounds" },
  { spCURELIGHTWOUNDS,                    ssCONJURATION,     "Cure Light Wounds" },
  { spCUREMINORWOUNDS,                    ssCONJURATION,     "Cure Minor Wounds" },
  { spCUREMODERATEWOUNDS,                 ssCONJURATION,     "Cure Moderate Wounds" },
  { spCURESERIOUSWOUNDS,                  ssCONJURATION,     "Cure Serious Wounds" },
  { spCURSEWATER,                         ssTRANSMUTATION,   "Curse Water" },
  { spDANCINGLIGHTS,                      ssEVOCATION,       "Dancing Lights" },
  { spDARKNESS,                           ssEVOCATION,       "Darkness" },
  { spDARKVISION,                         ssTRANSMUTATION,   "Darkvision" },
  { spDAYLIGHT,                           ssEVOCATION,       "Daylight" },
  { spDAZE,                               ssENCHANTMENT,     "Daze" },
  { spDEATHKNELL,                         ssNECROMANCY,      "Death Knell" },
  { spDEATHWARD,                          ssNECROMANCY,      "Death Ward" },
  { spDEATHWATCH,                         ssNECROMANCY,      "Deathwatch" },
  { spDEEPERDARKNESS,                     ssEVOCATION,       "Deeper Darkness" },
  { spDELAYPOISON,                        ssCONJURATION,     "Delay Poison" },
  { spDELAYEDBLASTFIREBALL,               ssEVOCATION,       "Delayed Blast Fireball" },
  { spDEMAND,                             ssENCHANTMENT,     "Demand" },
  { spDESECRATE,                          ssEVOCATION,       "Desecrate" },
  { spDESTRUCTION,                        ssNECROMANCY,      "Destruction" },
  { spDETECTANIMALSORPLANTS,              ssDIVINATION,      "Detect Animals or Plants" },
  { spDETECTCHAOS,                        ssDIVINATION,      "Detect Chaos" },
  { spDETECTEVIL,                         ssDIVINATION,      "Detect Evil" },
  { spDETECTGOOD,                         ssDIVINATION,      "Detect Good" },
  { spDETECTLAW,                          ssDIVINATION,      "Detect Law" },
  { spDETECTMAGIC,                        ssUNIVERSAL,       "Detect Magic" },
  { spDETECTPOISON,                       ssDIVINATION,      "Detect Poison" },
  { spDETECTSCRYING,                      ssDIVINATION,      "Detect Scrying" },
  { spDETECTSECRETDOORS,                  ssDIVINATION,      "Detect Secret Doors" },
  { spDETECTSNARESANDPITS,                ssDIVINATION,      "Detect Snares and Pits" },
  { spDETECTTHOUGHTS,                     ssDIVINATION,      "Detect Thoughts" },
  { spDETECTUNDEAD,                       ssDIVINATION,      "Detect Undead" },
  { spDICTUM,                             ssEVOCATION,       "Dictum" },
  { spDIMENSIONDOOR,                      ssTRANSMUTATION,   "Dimension Door" },
  { spDIMENSIONALANCHOR,                  ssABJURATION,      "Dimensional Anchor" },
  { spDIMINISHPLANTS,                     ssTRANSMUTATION,   "Diminish Plants" },
  { spDISCERNLIES,                        ssDIVINATION,      "Discern Lies" },
  { spDISCERNLOCATION,                    ssDIVINATION,      "Discern Location" },
  { spDISINTEGRATE,                       ssTRANSMUTATION,   "Disintegrate" },
  { spDISMISSAL,                          ssABJURATION,      "Dismissal" },
  { spDISPELCHAOS,                        ssABJURATION,      "Dispel Chaos" },
  { spDISPELEVIL,                         ssABJURATION,      "Dispel Evil" },
  { spDISPELGOOD,                         ssABJURATION,      "Dispel Good" },
  { spDISPELLAW,                          ssABJURATION,      "Dispel Law" },
  { spDISPELMAGIC,                        ssABJURATION,      "Dispel Magic" },
  { spDISPLACEMENT,                       ssILLUSION,        "Displacement" },
  { spDISRUPTUNDEAD,                      ssNECROMANCY,      "Disrupt Undead" },
  { spDIVINATION,                         ssDIVINATION,      "Divination" },
  { spDIVINEFAVOR,                        ssEVOCATION,       "Divine Favor" },
  { spDIVINEPOWER,                        ssEVOCATION,       "Divine Power" },
  { spDOMINATEANIMAL,                     ssENCHANTMENT,     "Dominate Animal" },
  { spDOMINATEMONSTER,                    ssENCHANTMENT,     "Dominate Monster" },
  { spDOMINATEPERSON,                     ssENCHANTMENT,     "Dominate Person" },
  { spDOOM,                               ssENCHANTMENT,     "Doom" },
  { spDRAWMIJSINSTANTSUMMONS,             ssCONJURATION,     "Drawmij's Instant Summons" },
  { spDREAM,                              ssILLUSION,        "Dream" },
  { spEARTHQUAKE,                         ssEVOCATION,       "Earthquake" },
  { spELEMENTALSWARM,                     ssCONJURATION,     "Elemental Swarm" },
  { spEMOTION,                            ssENCHANTMENT,     "Emotion" },
  { spENDURANCE,                          ssTRANSMUTATION,   "Endurance" },
  { spENDUREELEMENTS,                     ssABJURATION,      "Endure Elements" },
  { spENERGYDRAIN,                        ssNECROMANCY,      "Energy Drain" },
  { spENERVATION,                         ssNECROMANCY,      "Enervation" },
  { spENLARGE,                            ssTRANSMUTATION,   "Enlarge" },
  { spENTANGLE,                           ssTRANSMUTATION,   "Entangle" },
  { spENTHRALL,                           ssENCHANTMENT,     "Enthrall" },
  { spENTROPICSHIELD,                     ssABJURATION,      "Entropic Shield" },
  { spERASE,                              ssTRANSMUTATION,   "Erase" },
  { spETHEREALJAUNT,                      ssTRANSMUTATION,   "Ethereal Jaunt" },
  { spETHEREALNESS,                       ssTRANSMUTATION,   "Etherealness" },
  { spEVARDSBLACKTENTACLES,               ssCONJURATION,     "Evard's Black Tentacles" },
  { spEXPEDITIOUSRETREAT,                 ssTRANSMUTATION,   "Expeditious Retreat" },
  { spEXPLOSIVERUNES,                     ssABJURATION,      "Explosive Runes" },
  { spEYEBITE,                            ssTRANSMUTATION,   "Eyebite" },
  { spFABRICATE,                          ssTRANSMUTATION,   "Fabricate" },
  { spFAERIEFIRE,                         ssEVOCATION,       "Faerie Fire" },
  { spFALSEVISION,                        ssILLUSION,        "False Vision" },
  { spFEAR,                               ssNECROMANCY,      "Fear" },
  { spFEATHERFALL,                        ssTRANSMUTATION,   "Feather Fall" },
  { spFEEBLEMIND,                         ssENCHANTMENT,     "Feeblemind" },
  { spFINDTHEPATH,                        ssDIVINATION,      "Find the Path" },
  { spFINDTRAPS,                          ssDIVINATION,      "Find Traps" },
  { spFINGEROFDEATH,                      ssNECROMANCY,      "Finger of Death" },
  { spFIRESEEDS,                          ssCONJURATION,     "Fire Seeds" },
  { spFIRESHIELD,                         ssEVOCATION,       "Fire Shield" },
  { spFIRESTORM,                          ssEVOCATION,       "Fire Storm" },
  { spFIRETRAP,                           ssABJURATION,      "Fire Trap" },
  { spFIREBALL,                           ssEVOCATION,       "Fireball" },
  { spFLAMEARROW,                         ssCONJURATION,     "Flame Arrow" },
  { spFLAMEBLADE,                         ssEVOCATION,       "Flame Blade" },
  { spFLAMESTRIKE,                        ssEVOCATION,       "Flame Strike" },
  { spFLAMINGSPHERE,                      ssEVOCATION,       "Flaming Sphere" },
  { spFLARE,                              ssEVOCATION,       "Flare" },
  { spFLESHTOSTONE,                       ssTRANSMUTATION,   "Flesh to Stone" },
  { spFLY,                                ssTRANSMUTATION,   "Fly" },
  { spFOGCLOUD,                           ssCONJURATION,     "Fog Cloud" },
  { spFORBIDDANCE,                        ssABJURATION,      "Forbiddance" },
  { spFORCECAGE,                          ssEVOCATION,       "Forcecage" },
  { spFORESIGHT,                          ssDIVINATION,      "Foresight" },
  { spFREEDOM,                            ssABJURATION,      "Freedom" },
  { spFREEDOMOFMOVEMENT,                  ssABJURATION,      "Freedom of Movement" },
  { spGASEOUSFORM,                        ssTRANSMUTATION,   "Gaseous Form" },
  { spGATE,                               ssCONJURATION,     "Gate" },
  { spGEASQUEST,                          ssENCHANTMENT,     "Geas/Quest" },
  { spGENTLEREPOSE,                       ssNECROMANCY,      "Gentle Repose" },
  { spGHOSTSOUND,                         ssILLUSION,        "Ghost Sound" },
  { spGHOULTOUCH,                         ssNECROMANCY,      "Ghoul Touch" },
  { spGIANTVERMIN,                        ssTRANSMUTATION,   "Giant Vermin" },
  { spGLITTERDUST,                        ssCONJURATION,     "Glitterdust" },
  { spGLOBEOFINVULNERABILITY,             ssABJURATION,      "Globe of Invulnerability" },
  { spGLYPHOFWARDING,                     ssABJURATION,      "Glyph of Warding" },
  { spGOODBERRY,                          ssTRANSMUTATION,   "Goodberry" },
  { spGREASE,                             ssCONJURATION,     "Grease" },
  { spGREATERCOMMAND,                     ssENCHANTMENT,     "Greater Command" },
  { spGREATERDISPELLING,                  ssABJURATION,      "Greater Dispelling" },
  { spGREATERGLYPHOFWARDING,              ssABJURATION,      "Greater Glyph of Warding" },
  { spGREATERMAGICFANG,                   ssTRANSMUTATION,   "Greater Magic Fang" },
  { spGREATERMAGICWEAPON,                 ssTRANSMUTATION,   "Greater Magic Weapon" },
  { spGREATERPLANARALLY,                  ssCONJURATION,     "Greater Planar Ally" },
  { spGREATERPLANARBINDING,               ssCONJURATION,     "Greater Planar Binding" },
  { spGREATERRESTORATION,                 ssNECROMANCY,      "Greater Restoration" },
  { spGREATERSCRYING,                     ssDIVINATION,      "Greater Scrying" },
  { spGREATERSHADOWCONJURATION,           ssILLUSION,        "Greater Shadow Conjuration" },
  { spGREATERSHADOWEVOCATION,             ssILLUSION,        "Greater Shadow Evocation" },
  { spGUARDSANDWARDS,                     ssABJURATION,      "Guards and Wards" },
  { spGUIDANCE,                           ssDIVINATION,      "Guidance" },
  { spGUSTOFWIND,                         ssEVOCATION,       "Gust of Wind" },
  { spHALLOW,                             ssEVOCATION,       "Hallow" },
  { spHALLUCINATORYTERRAIN,               ssILLUSION,        "Hallucinatory Terrain" },
  { spHALTUNDEAD,                         ssNECROMANCY,      "Halt Undead" },
  { spHARM,                               ssNECROMANCY,      "Harm" },
  { spHASTE,                              ssTRANSMUTATION,   "Haste" },
  { spHEAL,                               ssCONJURATION,     "Heal" },
  { spHEALMOUNT,                          ssCONJURATION,     "Heal Mount" },
  { spHEALINGCIRCLE,                      ssCONJURATION,     "Healing Circle" },
  { spHEATMETAL,                          ssTRANSMUTATION,   "Heat Metal" },
  { spHELPINGHAND,                        ssEVOCATION,       "Helping Hand" },
  { spHEROESFEAST,                        ssEVOCATION,       "Heroes' Feast" },
  { spHOLDANIMAL,                         ssENCHANTMENT,     "Hold Animal" },
  { spHOLDMONSTER,                        ssENCHANTMENT,     "Hold Monster" },
  { spHOLDPERSON,                         ssENCHANTMENT,     "Hold Person" },
  { spHOLDPORTAL,                         ssABJURATION,      "Hold Portal" },
  { spHOLYAURA,                           ssABJURATION,      "Holy Aura" },
  { spHOLYSMITE,                          ssEVOCATION,       "Holy Smite" },
  { spHOLYSWORD,                          ssEVOCATION,       "Holy Sword" },
  { spHOLYWORD,                           ssEVOCATION,       "Holy Word" },
  { spHORRIDWILTING,                      ssNECROMANCY,      "Horrid Wilting" },
  { spHYPNOTICPATTERN,                    ssILLUSION,        "Hypnotic Pattern" },
  { spHYPNOTISM,                          ssENCHANTMENT,     "Hypnotism" },
  { spICEPATH,                            ssEVOCATION,       "Ice Path" },
  { spIDENTIFY,                           ssDIVINATION,      "Identify" },
  { spILLUSORYSCRIPT,                     ssILLUSION,        "Illusory Script" },
  { spILLUSORYWALL,                       ssILLUSION,        "Illusory Wall" },
  { spIMBUEWITHSPELLABILITY,              ssEVOCATION,       "Imbue With Spell Ability" },
  { spIMPLOSION,                          ssEVOCATION,       "Implosion" },
  { spIMPRISONMENT,                       ssABJURATION,      "Imprisonment" },
  { spIMPROVEDINVISIBILITY,               ssILLUSION,        "Improved Invisibility" },
  { spINCENDIARYCLOUD,                    ssCONJURATION,     "Incendiary Cloud" },
  { spINFLICTCRITICALWOUNDS,              ssNECROMANCY,      "Inflict Critical Wounds" },
  { spINFLICTLIGHTWOUNDS,                 ssNECROMANCY,      "Inflict Light Wounds" },
  { spINFLICTMINORWOUNDS,                 ssNECROMANCY,      "Inflict Minor Wounds" },
  { spINFLICTMODERATEWOUNDS,              ssNECROMANCY,      "Inflict Moderate Wounds" },
  { spINFLICTSERIOUSWOUNDS,               ssNECROMANCY,      "Inflict Serious Wounds" },
  { spINSANITY,                           ssENCHANTMENT,     "Insanity" },
  { spINSECTPLAGUE,                       ssCONJURATION,     "Insect Plague" },
  { spINVISIBILITY,                       ssILLUSION,        "Invisibility" },
  { spINVISIBILITYPURGE,                  ssEVOCATION,       "Invisibility Purge" },
  { spINVISIBILITYSPHERE,                 ssILLUSION,        "Invisibility Sphere" },
  { spINVISIBILITYTOANIMALS,              ssABJURATION,      "Invisibility to Animals" },
  { spINVISIBILITYTOUNDEAD,               ssABJURATION,      "Invisibility to Undead" },
  { spIRONBODY,                           ssTRANSMUTATION,   "Iron Body" },
  { spIRONWOOD,                           ssTRANSMUTATION,   "Ironwood" },
  { spJUMP,                               ssTRANSMUTATION,   "Jump" },
  { spKEENEDGE,                           ssTRANSMUTATION,   "Keen Edge" },
  { spKNOCK,                              ssTRANSMUTATION,   "Knock" },
  { spKNOWDIRECTION,                      ssDIVINATION,      "Know Direction" },
  { spLEGENDLORE,                         ssDIVINATION,      "Legend Lore" },
  { spLEOMUNDSSECRETCHEST,                ssCONJURATION,     "Leomund's Secret Chest" },
  { spLEOMUNDSSECURESHELTER,              ssCONJURATION,     "Leomund's Secure Shelter" },
  { spLEOMUNDSTINYHUT,                    ssEVOCATION,       "Leomund's Tiny Hut" },
  { spLEOMUNDSTRAP,                       ssILLUSION,        "Leomund's Trap" },
  { spLESSERGEAS,                         ssENCHANTMENT,     "Lesser Geas" },
  { spLESSERPLANARALLY,                   ssCONJURATION,     "Lesser Planar Ally" },
  { spLESSERPLANARBINDING,                ssCONJURATION,     "Lesser Planar Binding" },
  { spLESSERRESTORATION,                  ssCONJURATION,     "Lesser Restoration" },
  { spLEVITATE,                           ssTRANSMUTATION,   "Levitate" },
  { spLIGHT,                              ssEVOCATION,       "Light" },
  { spLIGHTNINGBOLT,                      ssEVOCATION,       "Lightning Bolt" },
  { spLIMITEDWISH,                        ssUNIVERSAL,       "Limited Wish" },
  { spLIVEOAK,                            ssTRANSMUTATION,   "Liveoak" },
  { spLOCATECREATURE,                     ssDIVINATION,      "Locate Creature" },
  { spLOCATEOBJECT,                       ssDIVINATION,      "Locate Object" },
  { spMAGEARMOR,                          ssCONJURATION,     "Mage Armor" },
  { spMAGEHAND,                           ssTRANSMUTATION,   "Mage Hand" },
  { spMAGICCIRCLEAGAINSTCHAOS,            ssABJURATION,      "Magic Circle against Chaos" },
  { spMAGICCIRCLEAGAINSTEVIL,             ssABJURATION,      "Magic Circle against Evil" },
  { spMAGICCIRCLEAGAINSTGOOD,             ssABJURATION,      "Magic Circle against Good" },
  { spMAGICCIRCLEAGAINSTLAW,              ssABJURATION,      "Magic Circle against Law" },
  { spMAGICFANG,                          ssTRANSMUTATION,   "Magic Fang" },
  { spMAGICJAR,                           ssNECROMANCY,      "Magic Jar" },
  { spMAGICMISSILE,                       ssEVOCATION,       "Magic Missile" },
  { spMAGICMOUTH,                         ssILLUSION,        "Magic Mouth" },
  { spMAGICSTONE,                         ssTRANSMUTATION,   "Magic Stone" },
  { spMAGICVESTMENT,                      ssTRANSMUTATION,   "Magic Vestment" },
  { spMAGICWEAPON,                        ssTRANSMUTATION,   "Magic Weapon" },
  { spMAJORCREATION,                      ssCONJURATION,     "Major Creation" },
  { spMAJORIMAGE,                         ssILLUSION,        "Major Image" },
  { spMAKEWHOLE,                          ssTRANSMUTATION,   "Make Whole" },
  { spMARKOFJUSTICE,                      ssTRANSMUTATION,   "Mark of Justice" },
  { spMASSCHARM,                          ssENCHANTMENT,     "Mass Charm" },
  { spMASSHASTE,                          ssTRANSMUTATION,   "Mass Haste" },
  { spMASSHEAL,                           ssCONJURATION,     "Mass Heal" },
  { spMASSINVISIBILITY,                   ssILLUSION,        "Mass Invisibility" },
  { spMASSSUGGESTION,                     ssENCHANTMENT,     "Mass Suggestion" },
  { spMAZE,                               ssCONJURATION,     "Maze" },
  { spMELDINTOSTONE,                      ssTRANSMUTATION,   "Meld into Stone" },
  { spMELFSACIDARROW,                     ssCONJURATION,     "Melf's Acid Arrow" },
  { spMENDING,                            ssTRANSMUTATION,   "Mending" },
  { spMESSAGE,                            ssTRANSMUTATION,   "Message" },
  { spMETEORSWARM,                        ssEVOCATION,       "Meteor Swarm" },
  { spMINDBLANK,                          ssABJURATION,      "Mind Blank" },
  { spMINDFOG,                            ssENCHANTMENT,     "Mind Fog" },
  { spMINORCREATION,                      ssCONJURATION,     "Minor Creation" },
  { spMINORGLOBEOFINVULNERABILITY,        ssABJURATION,      "Minor Globe of Invulnerability" },
  { spMINORIMAGE,                         ssILLUSION,        "Minor Image" },
  { spMIRACLE,                            ssEVOCATION,       "Miracle" },
  { spMIRAGEARCANA,                       ssILLUSION,        "Mirage Arcana" },
  { spMIRRORIMAGE,                        ssILLUSION,        "Mirror Image" },
  { spMISDIRECTION,                       ssILLUSION,        "Misdirection" },
  { spMISLEAD,                            ssILLUSION,        "Mislead" },
  { spMODIFYMEMORY,                       ssENCHANTMENT,     "Modify Memory" },
  { spMORDENKAINENSDISJUNCTION,           ssABJURATION,      "Mordenkainen's Disjunction" },
  { spMORDENKAINENSFAITHFULHOUND,         ssCONJURATION,     "Mordenkainen's Faithful Hound" },
  { spMORDENKAINENSLUCUBRATION,           ssTRANSMUTATION,   "Mordenkainen's Lucubration" },
  { spMORDENKAINENSMAGNIFICENTMANSION,    ssCONJURATION,     "Mordenkainen's Magnificent Mansion" },
  { spMORDENKAINENSSWORD,                 ssEVOCATION,       "Mordenkainen's Sword" },
  { spMOUNT,                              ssCONJURATION,     "Mount" },
  { spMOVEEARTH,                          ssTRANSMUTATION,   "Move Earth" },
  { spNEGATIVEENERGYPROTECTION,           ssABJURATION,      "Negative Energy Protection" },
  { spNEUTRALIZEPOISON,                   ssCONJURATION,     "Neutralize Poison" },
  { spNIGHTMARE,                          ssILLUSION,        "Nightmare" },
  { spNONDETECTION,                       ssABJURATION,      "Nondetection" },
  { spNYSTULSMAGICAURA,                   ssILLUSION,        "Nystul's Magic Aura" },
  { spNYSTULSUNDETECTABLEAURA,            ssILLUSION,        "Nystul's Undetectable Aura" },
  { spOBSCUREOBJECT,                      ssABJURATION,      "Obscure Object" },
  { spOBSCURINGMIST,                      ssCONJURATION,     "Obscuring Mist" },
  { spOPENCLOSE,                          ssTRANSMUTATION,   "Open/Close" },
  { spORDERSWRATH,                        ssEVOCATION,       "Order's Wrath" },
  { spOTILUKESFREEZINGSPHERE,             ssEVOCATION,       "Otiluke's Freezing Sphere" },
  { spOTILUKESRESILIENTSPHERE,            ssEVOCATION,       "Otiluke's Resilient Sphere" },
  { spOTILUKESTELEKINETICSPHERE,          ssEVOCATION,       "Otiluke's Telekinetic Sphere" },
  { spOTTOSIRRESISTIBLEDANCE,             ssENCHANTMENT,     "Otto's Irresistible Dance" },
  { spPASSWITHOUTTRACE,                   ssTRANSMUTATION,   "Pass without Trace" },
  { spPASSWALL,                           ssTRANSMUTATION,   "Passwall" },
  { spPERMANENCY,                         ssUNIVERSAL,       "Permanency" },
  { spPERMANENTIMAGE,                     ssILLUSION,        "Permanent Image" },
  { spPERSISTENTIMAGE,                    ssILLUSION,        "Persistent Image" },
  { spPHANTASMALKILLER,                   ssILLUSION,        "Phantasmal Killer" },
  { spPHANTOMSTEED,                       ssCONJURATION,     "Phantom Steed" },
  { spPHASEDOOR,                          ssCONJURATION,     "Phase Door" },
  { spPLANARALLY,                         ssCONJURATION,     "Planar Ally" },
  { spPLANARBINDING,                      ssCONJURATION,     "Planar Binding" },
  { spPLANESHIFT,                         ssTRANSMUTATION,   "Plane Shift" },
  { spPLANTGROWTH,                        ssTRANSMUTATION,   "Plant Growth" },
  { spPOISON,                             ssNECROMANCY,      "Poison" },
  { spPOLYMORPHANYOBJECT,                 ssTRANSMUTATION,   "Polymorph Any Object" },
  { spPOLYMORPHOTHER,                     ssTRANSMUTATION,   "Polymorph Other" },
  { spPOLYMORPHSELF,                      ssTRANSMUTATION,   "Polymorph Self" },
  { spPOWERWORDBLIND,                     ssCONJURATION,     "Power Word, Blind" },
  { spPOWERWORDKILL,                      ssCONJURATION,     "Power Word, Kill" },
  { spPOWERWORDSTUN,                      ssCONJURATION,     "Power Word, Stun" },
  { spPRAYER,                             ssCONJURATION,     "Prayer" },
  { spPRESTIDIGITATION,                   ssUNIVERSAL,       "Prestidigitation" },
  { spPRISMATICSPHERE,                    ssABJURATION,      "Prismatic Sphere" },
  { spPRISMATICSPRAY,                     ssEVOCATION,       "Prismatic Spray" },
  { spPRISMATICWALL,                      ssABJURATION,      "Prismatic Wall" },
  { spPRODUCEFLAME,                       ssEVOCATION,       "Produce Flame" },
  { spPROGRAMMEDIMAGE,                    ssILLUSION,        "Programmed Image" },
  { spPROJECTIMAGE,                       ssILLUSION,        "Project Image" },
  { spPROTECTIONFROMARROWS,               ssABJURATION,      "Protection from Arrows" },
  { spPROTECTIONFROMCHAOS,                ssABJURATION,      "Protection from Chaos" },
  { spPROTECTIONFROMELEMENTS,             ssABJURATION,      "Protection from Elements" },
  { spPROTECTIONFROMEVIL,                 ssABJURATION,      "Protection from Evil" },
  { spPROTECTIONFROMGOOD,                 ssABJURATION,      "Protection from Good" },
  { spPROTECTIONFROMLAW,                  ssABJURATION,      "Protection from Law" },
  { spPROTECTIONFROMSPELLS,               ssABJURATION,      "Protection from Spells" },
  { spPRYINGEYES,                         ssDIVINATION,      "Prying Eyes" },
  { spPURIFYFOODANDDRINK,                 ssUNIVERSAL,       "Purify Food and Drink" },
  { spPYROTECHNICS,                       ssTRANSMUTATION,   "Pyrotechnics" },
  { spQUENCH,                             ssTRANSMUTATION,   "Quench" },
  { spRAINBOWPATTERN,                     ssILLUSION,        "Rainbow Pattern" },
  { spRAISEDEAD,                          ssCONJURATION,     "Raise Dead" },
  { spRANDOMACTION,                       ssENCHANTMENT,     "Random Action" },
  { spRARYSMNEMONICENHANCER,              ssTRANSMUTATION,   "Rary's Mnemonic Enhancer" },
  { spRARYSTELEPATHICBOND,                ssDIVINATION,      "Rary's Telepathic Bond" },
  { spRAYOFENFEEBLEMENT,                  ssNECROMANCY,      "Ray of Enfeeblement" },
  { spRAYOFFROST,                         ssCONJURATION,     "Ray of Frost" },
  { spREADMAGIC,                          ssUNIVERSAL,       "Read Magic" },
  { spREDUCE,                             ssTRANSMUTATION,   "Reduce" },
  { spREFUGE,                             ssTRANSMUTATION,   "Refuge" },
  { spREGENERATE,                         ssCONJURATION,     "Regenerate" },
  { spREINCARNATE,                        ssTRANSMUTATION,   "Reincarnate" },
  { spREMOVEBLINDNESSDEAFNESS,            ssCONJURATION,     "Remove Blindness/Deafness" },
  { spREMOVECURSE,                        ssABJURATION,      "Remove Curse" },
  { spREMOVEDISEASE,                      ssCONJURATION,     "Remove Disease" },
  { spREMOVEFEAR,                         ssABJURATION,      "Remove Fear" },
  { spREMOVEPARALYSIS,                    ssCONJURATION,     "Remove Paralysis" },
  { spREPELMETALORSTONE,                  ssABJURATION,      "Repel Metal or Stone" },
  { spREPELVERMIN,                        ssABJURATION,      "Repel Vermin" },
  { spREPELWOOD,                          ssTRANSMUTATION,   "Repel Wood" },
  { spREPULSION,                          ssABJURATION,      "Repulsion" },
  { spRESISTELEMENTS,                     ssABJURATION,      "Resist Elements" },
  { spRESISTANCE,                         ssABJURATION,      "Resistance" },
  { spRESTORATION,                        ssCONJURATION,     "Restoration" },
  { spRESURRECTION,                       ssCONJURATION,     "Resurrection" },
  { spREVERSEGRAVITY,                     ssTRANSMUTATION,   "Reverse Gravity" },
  { spRIGHTEOUSMIGHT,                     ssTRANSMUTATION,   "Righteous Might" },
  { spROPETRICK,                          ssTRANSMUTATION,   "Rope Trick" },
  { spRUSTINGGRASP,                       ssTRANSMUTATION,   "Rusting Grasp" },
  { spSANCTUARY,                          ssABJURATION,      "Sanctuary" },
  { spSCARE,                              ssNECROMANCY,      "Scare" },
  { spSCREEN,                             ssILLUSION,        "Screen" },
  { spSCRYING,                            ssDIVINATION,      "Scrying" },
  { spSCULPTSOUND,                        ssTRANSMUTATION,   "Sculpt Sound" },
  { spSEARINGLIGHT,                       ssEVOCATION,       "Searing Light" },
  { spSECRETPAGE,                         ssTRANSMUTATION,   "Secret Page" },
  { spSEEINVISIBILITY,                    ssDIVINATION,      "See Invisibility" },
  { spSEEMING,                            ssILLUSION,        "Seeming" },
  { spSENDING,                            ssEVOCATION,       "Sending" },
  { spSEPIASNAKESIGIL,                    ssCONJURATION,     "Sepia Snake Sigil" },
  { spSEQUESTER,                          ssABJURATION,      "Sequester" },
  { spSHADES,                             ssILLUSION,        "Shades" },
  { spSHADOWCONJURATION,                  ssILLUSION,        "Shadow Conjuration" },
  { spSHADOWEVOCATION,                    ssILLUSION,        "Shadow Evocation" },
  { spSHADOWWALK,                         ssILLUSION,        "Shadow Walk" },
  { spSHAMBLER,                           ssCONJURATION,     "Shambler" },
  { spSHAPECHANGE,                        ssTRANSMUTATION,   "Shapechange" },
  { spSHATTER,                            ssEVOCATION,       "Shatter" },
  { spSHIELD,                             ssABJURATION,      "Shield" },
  { spSHIELDOFFAITH,                      ssABJURATION,      "Shield of Faith" },
  { spSHIELDOFLAW,                        ssABJURATION,      "Shield of Law" },
  { spSHIELDOTHER,                        ssABJURATION,      "Shield Other" },
  { spSHILLELAGH,                         ssTRANSMUTATION,   "Shillelagh" },
  { spSHOCKINGGRASP,                      ssTRANSMUTATION,   "Shocking Grasp" },
  { spSHOUT,                              ssEVOCATION,       "Shout" },
  { spSHRINKITEM,                         ssTRANSMUTATION,   "Shrink Item" },
  { spSILENCE,                            ssILLUSION,        "Silence" },
  { spSILENTIMAGE,                        ssILLUSION,        "Silent Image" },
  { spSIMULACRUM,                         ssILLUSION,        "Simulacrum" },
  { spSLAYLIVING,                         ssNECROMANCY,      "Slay Living" },
  { spSLEEP,                              ssENCHANTMENT,     "Sleep" },
  { spSLEETSTORM,                         ssCONJURATION,     "Sleet Storm" },
  { spSLOW,                               ssTRANSMUTATION,   "Slow" },
  { spSNARE,                              ssTRANSMUTATION,   "Snare" },
  { spSOFTENEARTHANDSTONE,                ssTRANSMUTATION,   "Soften Earth and Stone" },
  { spSOLIDFOG,                           ssCONJURATION,     "Solid Fog" },
  { spSOULBIND,                           ssNECROMANCY,      "Soul Bind" },
  { spSOUNDBURST,                         ssEVOCATION,       "Sound Burst" },
  { spSPEAKWITHANIMALS,                   ssDIVINATION,      "Speak with Animals" },
  { spSPEAKWITHDEAD,                      ssNECROMANCY,      "Speak with Dead" },
  { spSPEAKWITHPLANTS,                    ssDIVINATION,      "Speak with Plants" },
  { spSPECTRALHAND,                       ssNECROMANCY,      "Spectral Hand" },
  { spSPELLIMMUNITY,                      ssABJURATION,      "Spell Immunity" },
  { spSPELLRESISTANCE,                    ssABJURATION,      "Spell Resistance" },
  { spSPELLTURNING,                       ssABJURATION,      "Spell Turning" },
  { spSPELLSTAFF,                         ssTRANSMUTATION,   "Spellstaff" },
  { spSPIDERCLIMB,                        ssTRANSMUTATION,   "Spider Climb" },
  { spSPIKEGROWTH,                        ssTRANSMUTATION,   "Spike Growth" },
  { spSPIKESTONES,                        ssTRANSMUTATION,   "Spike Stones" },
  { spSPRITUALWEAPON,                     ssEVOCATION,       "Spritual Weapon" },
  { spSTATUE,                             ssTRANSMUTATION,   "Statue" },
  { spSTATUS,                             ssDIVINATION,      "Status" },
  { spSTINKINGCLOUD,                      ssCONJURATION,     "Stinking Cloud" },
  { spSTONESHAPE,                         ssTRANSMUTATION,   "Stone Shape" },
  { spSTONETELL,                          ssDIVINATION,      "Stone Tell" },
  { spSTONETOFLESH,                       ssTRANSMUTATION,   "Stone to Flesh" },
  { spSTONESKIN,                          ssABJURATION,      "Stoneskin" },
  { spSTORMOFVENGEANCE,                   ssCONJURATION,     "Storm of Vengeance" },
  { spSUGGESTION,                         ssENCHANTMENT,     "Suggestion" },
  { spSUMMONMONSTERI,                     ssCONJURATION,     "Summon Monster I" },
  { spSUMMONMONSTERII,                    ssCONJURATION,     "Summon Monster II" },
  { spSUMMONMONSTERIII,                   ssCONJURATION,     "Summon Monster III" },
  { spSUMMONMONSTERIV,                    ssCONJURATION,     "Summon Monster IV" },
  { spSUMMONMONSTERIX,                    ssCONJURATION,     "Summon Monster IX" },
  { spSUMMONMONSTERV,                     ssCONJURATION,     "Summon Monster V" },
  { spSUMMONMONSTERVI,                    ssCONJURATION,     "Summon Monster VI" },
  { spSUMMONMONSTERVII,                   ssCONJURATION,     "Summon Monster VII" },
  { spSUMMONMONSTERVIII,                  ssCONJURATION,     "Summon Monster VIII" },
  { spSUMMONNATURESALLYI,                 ssCONJURATION,     "Summon Nature's Ally I" },
  { spSUMMONNATURESALLYII,                ssCONJURATION,     "Summon Nature's Ally II" },
  { spSUMMONNATURESALLYIII,               ssCONJURATION,     "Summon Nature's Ally III" },
  { spSUMMONNATURESALLYIV,                ssCONJURATION,     "Summon Nature's Ally IV" },
  { spSUMMONNATURESALLYIX,                ssCONJURATION,     "Summon Nature's Ally IX" },
  { spSUMMONNATURESALLYV,                 ssCONJURATION,     "Summon Nature's Ally V" },
  { spSUMMONNATURESALLYVI,                ssCONJURATION,     "Summon Nature's Ally VI" },
  { spSUMMONNATURESALLYVII,               ssCONJURATION,     "Summon Nature's Ally VII" },
  { spSUMMONNATURESALLYVIII,              ssCONJURATION,     "Summon Nature's Ally VIII" },
  { spSUMMONSWARM,                        ssCONJURATION,     "Summon Swarm" },
  { spSUNBEAM,                            ssEVOCATION,       "Sunbeam" },
  { spSUNBURST,                           ssEVOCATION,       "Sunburst" },
  { spSYMBOL,                             ssUNIVERSAL,       "Symbol" },
  { spSYMPATHY,                           ssENCHANTMENT,     "Sympathy" },
  { spTASHASHIDEOUSLAUGHTER,              ssENCHANTMENT,     "Tasha's Hideous Laughter" },
  { spTELEKINESIS,                        ssTRANSMUTATION,   "Telekinesis" },
  { spTELEPORT,                           ssTRANSMUTATION,   "Teleport" },
  { spTELEPORTWITHOUTERROR,               ssTRANSMUTATION,   "Teleport without Error" },
  { spTELEPORTATIONCIRCLE,                ssTRANSMUTATION,   "Teleportation Circle" },
  { spTEMPORALSTASIS,                     ssTRANSMUTATION,   "Temporal Stasis" },
  { spTENSERSFLOATINGDISK,                ssEVOCATION,       "Tenser's Floating Disk" },
  { spTENSERSTRANSFORMATION,              ssTRANSMUTATION,   "Tenser's Transformation" },
  { spTIMESTOP,                           ssTRANSMUTATION,   "Time Stop" },
  { spTONGUES,                            ssDIVINATION,      "Tongues" },
  { spTRANSMUTEMETALTOWOOD,               ssTRANSMUTATION,   "Transmute Metal to Wood" },
  { spTRANSMUTEMUDTOROCK,                 ssTRANSMUTATION,   "Transmute Mud to Rock" },
  { spTRANSMUTEROCKTOMUD,                 ssTRANSMUTATION,   "Transmute Rock to Mud" },
  { spTRANSPORTVIAPLANTS,                 ssTRANSMUTATION,   "Transport via Plants" },
  { spTRAPTHESOUL,                        ssCONJURATION,     "Trap the Soul" },
  { spTREESHAPE,                          ssTRANSMUTATION,   "Tree Shape" },
  { spTREESTRIDE,                         ssTRANSMUTATION,   "Tree Stride" },
  { spTRUERESURRECTION,                   ssCONJURATION,     "True Resurrection" },
  { spTRUESEEING,                         ssDIVINATION,      "True Seeing" },
  { spTRUESTRIKE,                         ssDIVINATION,      "True Strike" },
  { spUNDETECTABLEALIGNMENT,              ssABJURATION,      "Undetectable Alignment" },
  { spUNHALLOW,                           ssEVOCATION,       "Unhallow" },
  { spUNHOLYAURA,                         ssABJURATION,      "Unholy Aura" },
  { spUNHOLYBLIGHT,                       ssEVOCATION,       "Unholy Blight" },
  { spUNSEENSERVANT,                      ssCONJURATION,     "Unseen Servant" },
  { spVAMPIRICTOUCH,                      ssNECROMANCY,      "Vampiric Touch" },
  { spVANISH,                             ssTRANSMUTATION,   "Vanish" },
  { spVEIL,                               ssILLUSION,        "Veil" },
  { spVENTRILOQUISM,                      ssILLUSION,        "Ventriloquism" },
  { spVIRTUE,                             ssTRANSMUTATION,   "Virtue" },
  { spVISION,                             ssDIVINATION,      "Vision" },
  { spWAILOFTHEBANSHEE,                   ssNECROMANCY,      "Wail of the Banshee" },
  { spWALLOFFIRE,                         ssEVOCATION,       "Wall of Fire" },
  { spWALLOFFORCE,                        ssEVOCATION,       "Wall of Force" },
  { spWALLOFICE,                          ssEVOCATION,       "Wall of Ice" },
  { spWALLOFIRON,                         ssCONJURATION,     "Wall of Iron" },
  { spWALLOFSTONE,                        ssCONJURATION,     "Wall of Stone" },
  { spWALLOFTHORNS,                       ssCONJURATION,     "Wall of Thorns" },
  { spWARPWOOD,                           ssTRANSMUTATION,   "Warp Wood" },
  { spWATERBREATHING,                     ssTRANSMUTATION,   "Water Breathing" },
  { spWATERWALK,                          ssTRANSMUTATION,   "Water Walk" },
  { spWEB,                                ssCONJURATION,     "Web" },
  { spWEIRD,                              ssILLUSION,        "Weird" },
  { spWHIRLWIND,                          ssEVOCATION,       "Whirlwind" },
  { spWHISPERINGWIND,                     ssTRANSMUTATION,   "Whispering Wind" },
  { spWINDWALK,                           ssTRANSMUTATION,   "Wind Walk" },
  { spWINDWALL,                           ssEVOCATION,       "Wind Wall" },
  { spWISH,                               ssUNIVERSAL,       "Wish" },
  { spWOODSHAPE,                          ssTRANSMUTATION,   "Wood Shape" },
  { spWORDOFCHAOS,                        ssEVOCATION,       "Word of Chaos" },
  { spWORDOFRECALL,                       ssTRANSMUTATION,   "Word of Recall" },
  { spZONEOFTRUTH,                        ssENCHANTMENT,     "Zone of Truth" },
  { 0,                                    0,                 0 }
};


static const struct {
  int   id;
  int   forbiddenAlignments;
  char* name;
} s_domains[] = {
  { dmAIR,         0,                       "air" },
  { dmANIMAL,      0,                       "animal" },
  { dmCHAOS,       alLAWFUL | alLCNEUTRAL,  "chaos" },
  { dmDEATH,       alGOOD,                  "death" },
  { dmDESTRUCTION, alGOOD,                  "destruction" },
  { dmEARTH,       0,                       "earth" },
  { dmEVIL,        alGOOD | alGENEUTRAL,    "evil" },       
  { dmFIRE,        0,                       "fire" },
  { dmGOOD,        alEVIL | alGENEUTRAL,    "good" },
  { dmHEALING,     0,                       "healing" },
  { dmKNOWLEDGE,   0,                       "knowledge" },
  { dmLAW,         alCHAOTIC | alLCNEUTRAL, "law" },
  { dmLUCK,        0,                       "luck" },
  { dmMAGIC,       0,                       "magic" },
  { dmPLANT,       0,                       "plant" },
  { dmPROTECTION,  0,                       "protection" },
  { dmSTRENGTH,    0,                       "strength" },
  { dmSUN,         0,                       "sun" },
  { dmTRAVEL,      0,                       "travel" },
  { dmTRICKERY,    alLAWFUL,                "trickery" },
  { dmWAR,         0,                       "war" },
  { dmWATER,       0,                       "water" },
  { 0,             0,                       0 }      
};


static int s_npcGearValue[] = { 900, 2000, 2500, 3300, 4300, 5600, 7200,
        9400, 12000, 16000, 21000, 27000, 35000, 45000, 59000, 77000,
        100000, 130000, 170000, 220000 };

static struct {
  int   id;
  char* name;
} s_languages[] = {
  { lnABYSSAL,     "abyssal" },
  { lnAQUAN,       "aquan" },
  { lnAURAN,       "auran" },
  { lnCELESTIAL,   "celestial" },
  { lnCOMMON,      "common" },
  { lnDRACONIC,    "draconic" },
  { lnDRUIDIC,     "druidic" },
  { lnDWARVEN,     "dwarven" },
  { lnELVEN,       "elven" },
  { lnGNOME,       "gnome" },
  { lnGOBLIN,      "goblin" },
  { lnGIANT,       "giant" },
  { lnGNOLL,       "gnoll" },
  { lnHALFLING,    "halfling" },
  { lnIGNAN,       "ignan" },
  { lnINFERNAL,    "infernal" },
  { lnORC,         "orc" },
  { lnSYLVAN,      "sylvan" },
  { lnTERRAN,      "terran" },
  { lnUNDERCOMMON, "undercommon" },
  { 0,             0 }
};

/* ---------------------------------------------------------------------- *
 * Function definitions
 * ---------------------------------------------------------------------- */

static int roundToNearest5( int num ) {
  int mod5;
  
  mod5 = num % 5;
  if( mod5 <= 2 ) {
    return ( num - mod5 );
  }
  
  return ( num - mod5 ) + 5;  
}


char* dndGetClassName( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].name;
    }
  }

  return NULL;
}


int dndGetClassHitDie( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].hitDie;
    }
  }

  return 0;
}


int dndGetClassType( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].type;
    }
  }

  return 0;
}


char* dndGetClassTypeName( int id ) {
  int i;

  for( i = 0; s_classTypeInfo[ i ].id != 0; i++ ) {
    if( s_classTypeInfo[ i ].id == id ) {
      return s_classTypeInfo[ i ].name;
    }
  }

  return NULL;
}


char* dndGetAlignmentText( int alignment ) {
  int i;

  for( i = 0; s_alignmentText[ i ].alignment != 0; i++ ) {
    if( s_alignmentText[ i ].alignment == alignment ) {
      return s_alignmentText[ i ].text;
    }
  }

  return NULL;
}


char* dndGetSkillName( int skill ) {
  int i;

  for( i = 0; s_skills[ i ].name != 0; i++ ) {
    if( s_skills[ i ].type == skill ) {
      return s_skills[ i ].name;
    }
  }
  
  return NULL;
}


int dndGetSkillAbility( int skill ) {
  int i;

  for( i = 0; s_skills[ i ].name != 0; i++ ) {
    if( s_skills[ i ].type == skill ) {
      return s_skills[ i ].ability;
    }
  }
  
  return 0;
}


int dndGetSkillType( int classType, int skill ) {
  int i;
  int j;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      for( j = 0; s_classInfo[ i ].skills[ j ].skill != 0; j++ ) {
        if( s_classInfo[ i ].skills[ j ].skill == skill ) {
          if( s_classInfo[ i ].skills[ j ].classSkill ) {
            return sktCLASS;
          } else {
            return sktCROSSCLASS;
          }
        }
      }

      break;
    }
  }

  return sktEXCLUSIVE;
}


int dndGetSkillBonusForClass( int classType ) {
  int i;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].skillCount;
    }
  }
  
  return 0;
}


char* dndGetAbilityName( int ability ) {
  int i;

  for( i = 0; s_abilities[ i ].name != 0; i++ ) {
    if( s_abilities[ i ].ability == ability ) {
      return s_abilities[ i ].name;
    }
  }

  return NULL;
}


int dndGetAbilityBonus( int abilityScore ) {
  int i;

  i = abilityScore - 10;
  if( abilityScore < 0 ) {
    abilityScore--;
  }

  return i >> 1;
}


int dndClassHasBonusFeatAtFirstLevel( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].bonusFeatAtFirst;
    }
  }

  return 0;
}


int dndClassBonusFeatEveryXLevels( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].bonusFeatEveryX;
    }
  }

  return 0;
}


char* dndGetFeatName( int id ) {
  int i;

  for( i = 0; s_feats[ i ].name != 0; i++ ) {
    if( s_feats[ i ].id == id ) {
      return s_feats[ i ].name;
    }
  }

  return NULL;
}


int dndFeatIsReusable( int id ) {
  int i;

  for( i = 0; s_feats[ i ].name != 0; i++ ) {
    if( s_feats[ i ].id == id ) {
      return s_feats[ i ].multi;
    }
  }

  return 0;
}


int dndGetFeatPrerequisite( int id, int* type, int* data1, int* data2, char** next ) {
  int i;
  FEATPREREQ* fpr = NULL;

  if( id != 0 ) {
    for( i = 0; s_feats[ i ].name != 0; i++ ) {
      if( s_feats[ i ].id == id ) {
        fpr = s_feats[ i ].prereqs;
        break;
      }
    }
    if( fpr == NULL ) {
      return 0;
    }
  } else {
    if( *next == NULL ) {
      return 0;
    }
    fpr = (FEATPREREQ*)(*next);
  }

  *next = NULL;

  if( fpr->preReqType == 0 ) {
    return 0;
  }

  *type = fpr->preReqType;
  *data1 = fpr->data1;
  *data2 = fpr->data2;

  *next = (char*)( fpr + 1 );

  return 1;
}


int dndGetClassAttackBonus( int id, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].id != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].attack[ level-1 ];
    }
  }

  return 0;
}


char* dndGetRaceName( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].name;
    }
  }

  return NULL;
}


int dndGetRaceSize( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].size;
    }
  }

  return 0;
}


char* dndGetWeaponName( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].name;
    }
  }

  return NULL;
}


int dndGetWeaponSize( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].size;
    }
  }

  return 0;
}


int dndGetWeaponType( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].type;
    }
  }

  return 0;
}


int dndGetWeaponCost( int id ) {
  int i;

  for( i = 0; s_weapons[ i ].name != 0; i++ ) {
    if( s_weapons[ i ].id == id ) {
      return s_weapons[ i ].cost;
    }
  }

  return 0;
}


char* dndGetSchoolOfMagicName( int id ) {
  int i;

  for( i = 0; s_magicSchools[ i ].name != 0; i++ ) {
    if( s_magicSchools[ i ].id == id ) {
      return s_magicSchools[ i ].name;
    }
  }

  return NULL;
}


char* dndGetSizeName( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].name;
    }
  }

  return NULL;
}


int dndGetSizeACMod( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].acMod;
    }
  }

  return 0;
}


char* dndGetSpellName( int id ) {
  int i;

  for( i = 0; s_spells[ i ].name != 0; i++ ) {
    if( s_spells[ i ].id == id ) {
      return s_spells[ i ].name;
    }
  }

  return NULL;
}


int dndGetSpellLevel( int classid, int spellid ) {
  SPELLSFORCLASS* list;
  int i;

  list = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      list = s_classInfo[ i ].spells;
      break;
    }
  }

  if( list == 0 ) {
    return -1;
  }

  for( i = 0; list[ i ].spell != 0; i++ ) {
    if( list[ i ].spell == spellid ) {
      return list[ i ].level;
    }
  }

  return -1;
}


int dndGetSpellOfLevel( int classid, int level, char** next ) {
  SPELLSFORCLASS* list;
  int i;

  list = 0;

  if( classid != 0 ) {
    for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
      if( s_classInfo[ i ].id == classid ) {
        list = s_classInfo[ i ].spells;
        break;
      }
    }
  } else {
    list = (SPELLSFORCLASS*)(*next);
  }

  if( list == 0 ) {
    *next = 0;
    return 0;
  }

  if( list->spell == 0 ) {
    *next = 0;
    return 0;
  }

  while( list->level != level ) {
    list++;
    if( list->spell == 0 ) {
      *next = 0;
      return 0;
    }
  }

  *next = (char*)( list + 1 );

  return list->spell;
}


int dndGetSpellsPerDay( int classid, int classLevel, int spellLevel ) {
  int i;
  SPELLMATRIX* s;

  s = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      if( s_classInfo[ i ].spellsPerDay == 0 ) {
        return -1;
      }
      s = (SPELLMATRIX*)s_classInfo[ i ].spellsPerDay;
      break;
    }
  }

  if( s == 0 ) {
    return -1;
  }

  return (*s)[ classLevel - 1 ][ spellLevel ];
}


int dndGetSpellsKnown( int classid, int classLevel, int spellLevel ) {
  int i;
  SPELLMATRIX* s;

  switch( classid ) {
    case pcWIZARD:
    case pcDRUID:
    case pcCLERIC:
    case pcRANGER:
    case pcPALADIN:
      return 0;
  }

  s = 0;
  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classid ) {
      if( s_classInfo[ i ].spellsPerDay == 0 ) {
        return -1;
      }
      s = (SPELLMATRIX*)s_classInfo[ i ].spellsKnown;
      break;
    }
  }

  if( s == 0 ) {
    return -1;
  }

  return (*s)[ classLevel - 1 ][ spellLevel ];
}


int dndGetBonusSpellsPerDay( int relevantAbility, int spellLevel ) {
  int rc;

  if( spellLevel < 1 ) {
    return 0;
  }

  if( relevantAbility < 10 ) {
    return -1;
  }

  if( relevantAbility < ( 10 + spellLevel*2 ) ) {
    return 0;
  }

  /* formula is:
   *   AS -> ability score
   *   SL -> spell level
   *
   *   bonus = floor( ( AS - 10 - SL*2 ) / 8 ) + 1
   */

  rc = ( ( relevantAbility - 10 - spellLevel*2 ) >> 3 ) + 1;
  if( rc < 1 ) {
    rc = 0;
  }

  return rc;
}


char* dndGetDomainName( int id ) {
  int i;

  for( i = 0; s_domains[ i ].name != 0; i++ ) {
    if( s_domains[ i ].id == id ) {
      return s_domains[ i ].name;
    }
  }

  return NULL;
}


int dndGetForbiddenAlignmentsForDomain( int id ) {
  int i;

  for( i = 0; s_domains[ i ].name != 0; i++ ) {
    if( s_domains[ i ].id == id ) {
      return s_domains[ i ].forbiddenAlignments;
    }
  }

  return 0;
}


char* dndGetArmorName( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].name;
    }
  }

  return NULL;
}


int dndGetArmorType( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].type;
    }
  }

  return 0;
}


int dndGetArmorCost( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].cost;
    }
  }

  return 0;
}


int dndGetArmorACBonus( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].acBonus;
    }
  }

  return 0;
}


int dndGetArmorMaxDexterity( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].maxDex;
    }
  }

  return 0;
}


int dndGetArmorCheckPenalty( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].checkPenalty;
    }
  }

  return 0;
}


int dndGetArmorArcaneSpellFailure( int id ) {
  int i;

  for( i = 0; s_armors[ i ].name != 0; i++ ) {
    if( s_armors[ i ].id == id ) {
      return s_armors[ i ].arcaneSpellFailure;
    }
  }

  return 0;
}


int dndGetClassMultipleAttackBonus( int baseAttack, int which ) {
  int bonus;

  if( which < 1 ) {
    return 0;
  }
  
  bonus = baseAttack - ( which - 1 ) * 5;

  return bonus;
}


int dndGetClassAttacksPerRound( int baseAttack ) {
  int count;

  /* extra attacks are gained when the baseAttack is +6, +11, and +16 */

  count = ( baseAttack - 1 ) / 5 + 1;
  return count;
}


int dndGetMonkAttacksPerRound( int baseAttack ) {
  int count;

  /* extra attacks are gained when the baseAttack is +4, +7, +10, +13 */

  count = ( baseAttack - 1 ) / 3 + 1;
  return count;
}


int dndGetMonkMultipleAttackBonus( int baseAttack, int which ) {
  int bonus;

  if( which < 1 ) {
    return 0;
  }
  
  bonus = baseAttack - ( which - 1 ) * 3;

  return bonus;
}


int dndGetFortitudeSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].fortSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetReflexSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].refSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetWillSave( int classType, int level ) {
  int i;

  if( ( level < 1 ) || ( level > 20 ) ) {
    return 0;
  }

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == classType ) {
      return s_classInfo[ i ].willSave[ level - 1 ];
    }
  }

  return 0;
}


int dndGetNPCGearValue( int level ) {
  if( level < 1 ) {
    return 0;
  }
  if( level > 20 ) {
    level = 20;
  }
  
  return s_npcGearValue[ level - 1 ];  
}


int dndGetRaceBonus( int id, int gender, int type, int data ) {
  int i;
  int j;
  RACIALBONUS *bonuses;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      if( gender == gFEMALE ) {
        bonuses = s_races[ i ].femaleBonuses;
      } else {
        bonuses = s_races[ i ].maleBonuses;
      }

      if( bonuses == 0 ) {
        break;
      }

      for( j = 0; bonuses[ j ].type != 0; j++ ) {
        if( bonuses[ j ].type == type ) {
          if( bonuses[ j ].data == data ) {
            return bonuses[ j ].bonus;
          }
        }
      }
      break;
    }
  }

  return 0;
}


int dndGetRacialHeightWeight( int race, int gender, DNDRACIALHEIGHTWEIGHT* data ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      if( gender == gMALE ) {
        memcpy( data, &(s_races[ i ].male), sizeof( *data ) );
      } else if( gender == gFEMALE ) {
        memcpy( data, &(s_races[ i ].female), sizeof( *data ) );
      } else {
        return 0;
      }
      return 1;
    }
  }

  return 0;
}


int dndGetRaceAlignment( int race ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      return s_races[ i ].usualAlignment;
    }
  }

  return 0;
}


int dndGetRaceExtraHitDice( int race, int* count, int* type ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      *count = s_races[ i ].extraHitDieCount;
      *type  = s_races[ i ].extraHitDie;

      return ( *count > 0 ? 1 : 0 );
    }
  }

  return 0;
}


int dndGetRaceBonusOfType( int race, int gender, int type, int* data, int* bonus, char** next ) {
  RACIALBONUS* b;
  int i;

  b = 0;

  if( race != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == race ) {
        if( gender == gFEMALE ) {
          b = s_races[ i ].femaleBonuses;
        } else {
          b = s_races[ i ].maleBonuses;
        }
        break;
      }
    }

  } else {
    b = (RACIALBONUS*)(*next);
  }

  if( b == 0 ) {
    *next = 0;
    return 0;
  }

  while( ( b->type != 0 ) && ( b->type != type ) ) {
    b++;
  }

  if( b->type == 0 ) {
    *next = 0;
    return 0;
  }

  *data  = b->data;
  *bonus = b->bonus;

  b++;
  *next = (char*)b;

  return 1;
}


int dndGetRacePreferredClass( int race ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == race ) {
      return s_races[ i ].preferredClass;
    }
  }

  return 0;
}


int dndGetRaceCR( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].challengeRating;
    }
  }

  return 0;
}


char* dndGetClassAbbr( int id ) {
  int i;

  for( i = 0; s_classInfo[ i ].name != 0; i++ ) {
    if( s_classInfo[ i ].id == id ) {
      return s_classInfo[ i ].abbr;
    }
  }

  return NULL;
}


char* dndGetAlignmentAbbr( int alignment ) {
  int i;

  for( i = 0; s_alignmentText[ i ].text != 0; i++ ) {
    if( s_alignmentText[ i ].alignment == alignment ) {
      return s_alignmentText[ i ].abbr;
    }
  }

  return NULL;
}


char* dndGetLanguageName( int id ) {
  int i;

  for( i = 0; s_languages[ i ].name != 0; i++ ) {
    if( s_languages[ i ].id == id ) {
      return s_languages[ i ].name;
    }
  }

  return NULL;
}


int dndGetGivenLanguages( int id, char** next ) {
  int *entry;
  int  i;

  entry = 0;

  if( id != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == id ) {
        entry = s_races[i].automaticLanguages;
        break;
      }
    }
  } else {
    entry = (int*)(*next);
  }

  if( entry == 0 ) {
    return 0;
  }

  i = *entry;
  entry++;

  *next = (char*)entry;

  return i;
}


int dndGetBonusLanguages( int id, char** next ) {
  int *entry;
  int  i;

  entry = 0;

  if( id != 0 ) {
    for( i = 0; s_races[ i ].name != 0; i++ ) {
      if( s_races[ i ].id == id ) {
        entry = s_races[i].bonusLanguages;
        break;
      }
    }
  } else {
    entry = (int*)(*next);
  }

  if( entry == 0 ) {
    return 0;
  }

  i = *entry;
  entry++;

  *next = (char*)entry;

  return i;
}


int dndGetRelativeWeaponSize( int raceid, int weapon ) {
  int raceSize;
  int weaponSize;

  raceSize = dndGetRaceSize( raceid );
  weaponSize = dndGetWeaponSize( weapon );

  if( weaponSize < raceSize ) {
    return wtLIGHT;
  } else if( weaponSize == raceSize ) {
    return wtONEHANDED;
  }

  return wtTWOHANDED;
}


int dndGetSizeHideMod( int id ) {
  int i;

  for( i = 0; s_sizes[ i ].name != 0; i++ ) {
    if( s_sizes[ i ].id == id ) {
      return s_sizes[ i ].hideCheck;
    }
  }

  return 0;
}


int dndGetSpellSchool( int id ) {
  int i;

  for( i = 0; s_spells[ i ].name != 0; i++ ) {
    if( s_spells[ i ].id == id ) {
      return s_spells[ i ].school;
    }
  }

  return 0;
}


int dndGetMonkSpeedForRace( int raceid, int level ) {
  int baseSpeed;
  
  /* formula for calculating a monk's speed is:
   * baseSpeed * ( ( 3 + floor(level/3) ) / 3 )
   */

  baseSpeed = dndGetRaceSpeed( raceid );
  baseSpeed = (int)( baseSpeed * ( ( 3 + level/3 ) / 3.0 ) );

  return roundToNearest5( baseSpeed );
}


int dndGetRaceSpeed( int id ) {
  int i;

  for( i = 0; s_races[ i ].name != 0; i++ ) {
    if( s_races[ i ].id == id ) {
      return s_races[ i ].speed;
    }
  }

  return 0;
}
