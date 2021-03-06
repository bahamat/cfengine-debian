/* 
   Copyright (C) Cfengine AS

   This file is part of Cfengine 3 - written and maintained by Cfengine AS.
 
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; version 3.
   
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License  
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

  To the extent this program is licensed as part of the Enterprise
  versions of Cfengine, the applicable Commerical Open Source License
  (COSL) may apply to this file if you as a licensee so wish it. See
  included file COSL.txt.

*/

/*****************************************************************************/
/*                                                                           */
/* Modestring toolkit                                                        */
/*                                                                           */
/*****************************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

/***************************************************************/

static int CheckModeState (enum modestate stateA, enum modestate stateB,enum modesort modeA, enum modesort modeB, char ch);
static int SetModeMask (char action, int value, int affected, mode_t *p, mode_t *m);

/***************************************************************/

int ParseModeString(char *modestring,mode_t *plusmask,mode_t *minusmask)

{ char *sp;
 int affected = 0, value = 0, gotaction, no_error = true;
  char action = '=';
  enum modestate state = unknown;
  enum modesort found_sort = unknown; /* Already found "sort" of mode */
  enum modesort sort = unknown; /* Sort of started but not yet finished mode */

*plusmask = *minusmask = 0;

if (modestring == NULL)
   {
   return true;
   }

Debug("ParseModeString(%s)\n",modestring);

gotaction = false;

for (sp = modestring; true ; sp++)
   {
   switch (*sp)
      {
      case 'a': no_error = CheckModeState(who,state,symbolic,sort,*sp);
                affected |= 07777;
                sort = symbolic;
                break;

      case 'u': no_error = CheckModeState(who,state,symbolic,sort,*sp);
                affected |= 04700;
                sort = symbolic;
                break;

      case 'g': no_error = CheckModeState(who,state,symbolic,sort,*sp);
                affected |= 02070;
                sort = symbolic;
                break;

      case 'o': no_error = CheckModeState(who,state,symbolic,sort,*sp);
                affected |= 00007;
                sort = symbolic;
                break;

      case '+':
      case '-':
      case '=':
          if (gotaction)
             {
             CfOut(cf_error,"","Too many +-= in mode string");
             return false;
             }

        no_error = CheckModeState(who,state,symbolic,sort,*sp);
        action = *sp;
        state = which;
        gotaction = true;
        sort = unknown;
        break;
                
      case 'r': no_error = CheckModeState(which,state,symbolic,sort,*sp);
                value |= 0444 & affected;
                sort = symbolic;
                break;

      case 'w': no_error = CheckModeState(which,state,symbolic,sort,*sp);
                value |= 0222 & affected;
                sort = symbolic;
                break;

      case 'x': no_error = CheckModeState(which,state,symbolic,sort,*sp);
                value |= 0111 & affected;
                sort = symbolic;
                break;

      case 's': no_error = CheckModeState(which,state,symbolic,sort,*sp);
                value |= 06000 & affected;
                sort = symbolic;
                break;

      case 't': no_error = CheckModeState(which,state,symbolic,sort,*sp);
                value |= 01000;
                sort = symbolic;
                break;

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7': no_error = CheckModeState(which,state,numeric,sort,*sp);
                sort = numeric;
                gotaction = true;
                state = which;
                affected = 07777; /* TODO: Hard-coded; see below */
                sscanf(sp,"%o",&value);
                if (value > 07777) /* TODO: Hardcoded !
                                      Is this correct for all sorts of Unix ?
                                      What about NT ?
                                      Any (POSIX)-constants ??
                                   */
                   {
                   CfOut(cf_error,"","Mode-Value too big : %s\n",modestring);
                   return false;
                   }
                
                while (isdigit((int)*sp) && (*sp != '\0'))
                   {
                   sp++;
                   }
                sp--;
                break;
                
      case ',':
          if (!SetModeMask(action,value,affected,plusmask,minusmask))
             {
             return false;
             }

          if (found_sort != unknown && found_sort != sort)
             {
             CfOut(cf_inform,"","Symbolic and numeric form for modes mixed");
             }
          
          found_sort = sort;
          sort = unknown;
          action = '=';
          affected = 0;
          value = 0;
          gotaction = false;
          state = who;
          break;
          
      case '\0':
          if (state == who || value == 0)
             {
             if (strcmp(modestring,"0000") != 0 && strcmp(modestring,"000") != 0)
                {
                CfOut(cf_error,"","mode string is incomplete");
                return false;
                }
             }
          
          if (!SetModeMask(action,value,affected,plusmask,minusmask))
             {
             return false;
             }

          if (found_sort != unknown && found_sort != sort)
             {
             CfOut(cf_inform,"","Symbolic and numeric form for modes mixed");
             }

          Debug1("[PLUS=%o][MINUS=%o]\n",*plusmask,*minusmask);
          return true;
          
      default:
          CfOut(cf_error,"","Invalid mode string (%s)",modestring);  
          return false;
      }
   }

if (!no_error)
   {
   CfOut(cf_error,"","Error validating mode string %s\n",modestring);
   }

return no_error;
}

/*********************************************************/

static int CheckModeState(enum modestate stateA,enum modestate stateB,enum modesort sortA,enum modesort sortB,char ch)

{
if ((stateA != wild) && (stateB != wild) && (stateA != stateB))
   {
   CfOut(cf_error,"","Mode string constant (%c) used out of context",ch);
   return false;
   }

if ((sortA != unknown) && (sortB != unknown) && (sortA != sortB))
   {
   CfOut(cf_error,"","Symbolic and numeric filemodes mixed within expression");
   return false;
   }

return true;
}

/*********************************************************/

static int SetModeMask(char action,int value,int affected,mode_t *p,mode_t *m)

{
Debug1("SetMask(%c%o,%o)\n",action,value,affected);

switch(action)
   {
   case '+':
             *p |= value;
             *m |= 0;
             return true;
   case '-':
             *p |= 0;
             *m |= value;
             return true;
   case '=':
             *p |= value;
             *m |= ((~value) & 07777 & affected);
             return true;
   default:
       CfOut(cf_error,"","Mode directive %c is unknown",action);
             return false;
   }
}

