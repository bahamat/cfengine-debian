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
/* File: server_transform.c                                                  */
/*                                                                           */
/*****************************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"
#include "cf3.server.h"

static void KeepContextBundles(void);
static void KeepServerPromise(struct Promise *pp);
static void InstallServerAuthPath(char *path,struct Auth **list,struct Auth **listtop);
static void KeepServerRolePromise(struct Promise *pp);

extern struct BodySyntax CFS_CONTROLBODY[];
extern struct BodySyntax CF_REMROLE_BODIES[];

/*******************************************************************/
/* GLOBAL VARIABLES                                                */
/*******************************************************************/

extern int CLOCK_DRIFT;
extern int CFD_MAXPROCESSES;
extern int ACTIVE_THREADS;
extern int NO_FORK;
extern int MULTITHREAD;
extern int CHECK_RFC931;
extern int CFD_INTERVAL;
extern int DENYBADCLOCKS;
extern int MULTIPLECONNS;
extern int TRIES;
extern int MAXTRIES;
extern int LOGCONNS;
extern int LOGENCRYPT;
extern struct Item *CONNECTIONLIST;
extern struct Auth *ROLES;
extern struct Auth *ROLESTOP;

/*******************************************************************/

void KeepFileAccessPromise(struct Promise *pp);
void KeepLiteralAccessPromise(struct Promise *pp, char *type);
void KeepQueryAccessPromise(struct Promise *pp,char *type);

/*******************************************************************/
/* Level                                                           */
/*******************************************************************/

void KeepPromises()

{
KeepContextBundles();
KeepControlPromises();
KeepPromiseBundles();
}

/*******************************************************************/

void Summarize()

{ struct Auth *ptr;
  struct Item *ip,*ipr;

CfOut(cf_verbose,"","Summarize control promises\n");
  
 CfOut(cf_verbose, "", "Granted access to paths :\n");

 for (ptr = VADMIT; ptr != NULL; ptr=ptr->next)
    {
    CfOut(cf_verbose, "", "Path: %s (encrypt=%d)\n",ptr->path,ptr->encrypt);

    for (ip = ptr->accesslist; ip != NULL; ip=ip->next)
       {
       CfOut(cf_verbose, "", "   Admit: %s root=",ip->name);
       for (ipr = ptr->maproot; ipr !=NULL; ipr=ipr->next)
          {
          CfOut(cf_verbose, "", "%s,",ipr->name);
          }
       }
    }
   

 CfOut(cf_verbose, "", "Denied access to paths :\n");
   
 for (ptr = VDENY; ptr != NULL; ptr=ptr->next)
    {
    CfOut(cf_verbose, "", "Path: %s\n",ptr->path);
      
    for (ip = ptr->accesslist; ip != NULL; ip=ip->next)
       {
       CfOut(cf_verbose, "", "   Deny: %s\n",ip->name);
       }      
    }


CfOut(cf_verbose,""," -> Host IPs allowed connection access :\n");

for (ip = NONATTACKERLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Host IPs denied connection access :\n");

for (ip = ATTACKERLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Host IPs allowed multiple connection access :\n");

for (ip = MULTICONNLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Host IPs from whom we shall accept public keys on trust :\n");

for (ip = TRUSTKEYLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Users from whom we accept connections :\n");

for (ip = ALLOWUSERLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... USERS: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Host IPs from NAT which we don't verify :\n");

for (ip = SKIPVERIFY; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

CfOut(cf_verbose,"","Dynamical Host IPs (e.g. DHCP) whose bindings could vary over time :\n");

for (ip = DHCPLIST; ip != NULL; ip=ip->next)
   {
   CfOut(cf_verbose,""," .... IP: %s\n",ip->name);
   }

}


/*******************************************************************/
/* Level                                                           */
/*******************************************************************/

void KeepControlPromises()
    
{ struct Constraint *cp;
  char rettype;
  void *retval;

CFD_MAXPROCESSES = 30;
MAXTRIES = 5;
CFD_INTERVAL = 0;
CHECKSUMUPDATES = true;
DENYBADCLOCKS = true;
CFRUNCOMMAND[0] = '\0';
CHECK_RFC931 = false;

/* Keep promised agent behaviour - control bodies */

Banner("Server control promises..");

HashControls();

/* Now expand */

for (cp = ControlBodyConstraints(cf_server); cp != NULL; cp=cp->next)
   {
   if (IsExcluded(cp->classes))
      {
      continue;
      }

   if (GetVariable("control_server",cp->lval,&retval,&rettype) == cf_notype)
      {
      CfOut(cf_error,"","Unknown lval %s in server control body",cp->lval);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_serverfacility].lval) == 0)
      {
      SetFacility(retval);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_denybadclocks].lval) == 0)
      {
      DENYBADCLOCKS = GetBoolean(retval);
      CfOut(cf_verbose,"","SET denybadclocks = %d\n",DENYBADCLOCKS);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_logencryptedtransfers].lval) == 0)
      {
      LOGENCRYPT = GetBoolean(retval);
      CfOut(cf_verbose,"","SET LOGENCRYPT = %d\n",LOGENCRYPT);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_logallconnections].lval) == 0)
      {
      LOGCONNS = GetBoolean(retval);
      CfOut(cf_verbose,"","SET LOGCONNS = %d\n",LOGCONNS);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_maxconnections].lval) == 0)
      {
      CFD_MAXPROCESSES = (int)Str2Int(retval);
      MAXTRIES = CFD_MAXPROCESSES / 3;
      CfOut(cf_verbose,"","SET maxconnections = %d\n",CFD_MAXPROCESSES);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_cfruncommand].lval) == 0)
      {
      strncpy(CFRUNCOMMAND,retval,CF_BUFSIZE-1);
      CfOut(cf_verbose,"","SET cfruncommand = %s\n",CFRUNCOMMAND);
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_allowconnects].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Allowing connections from ...\n");
      
      for (rp  = (struct Rlist *) retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(NONATTACKERLIST,rp->item))
            {
            AppendItem(&NONATTACKERLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_denyconnects].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Denying connections from ...\n");
      
      for (rp  = (struct Rlist *) retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(ATTACKERLIST,rp->item))
            {
            AppendItem(&ATTACKERLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_skipverify].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Skip verify connections from ...\n");
      
      for (rp  = (struct Rlist *) retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(SKIPVERIFY,rp->item))
            {
            AppendItem(&SKIPVERIFY,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_dynamicaddresses].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Dynamic addresses from ...\n");
      
      for (rp  = (struct Rlist *)retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(DHCPLIST,rp->item))
            {
            AppendItem(&DHCPLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_allowallconnects].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Allowing multiple connections from ...\n");
      
      for (rp  = (struct Rlist *)retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(MULTICONNLIST,rp->item))
            {
            AppendItem(&MULTICONNLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_allowusers].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Allowing users ...\n");
      
      for (rp  = (struct Rlist *)retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(ALLOWUSERLIST,rp->item))
            {
            AppendItem(&ALLOWUSERLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }
   
   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_trustkeysfrom].lval) == 0)
      {
      struct Rlist *rp;
      CfOut(cf_verbose,"","SET Trust keys from ...\n");
      
      for (rp  = (struct Rlist *)retval; rp != NULL; rp = rp->next)
         {
         if (!IsItemIn(TRUSTKEYLIST,rp->item))
            {
            AppendItem(&TRUSTKEYLIST,rp->item,cp->classes);
            }
         }
      
      continue;
      }

   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_portnumber].lval) == 0)
      {
      SHORT_CFENGINEPORT = (short)Str2Int(retval);
      strncpy(STR_CFENGINEPORT,retval,15);
      CfOut(cf_verbose,"","SET default portnumber = %u = %s = %s\n",(int)SHORT_CFENGINEPORT,STR_CFENGINEPORT,retval);
      SHORT_CFENGINEPORT = htons((short)Str2Int(retval));
      continue;
      }

   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_keyttl].lval) == 0)
      {
      KEYTTL = (short)Str2Int(retval);
      CfOut(cf_verbose,"","SET key TTL = %d\n",KEYTTL);
      continue;
      }

   if (strcmp(cp->lval,CFS_CONTROLBODY[cfs_bindtointerface].lval) == 0)
      {
      strncpy(BINDINTERFACE,retval,CF_BUFSIZE-1);
      CfOut(cf_verbose,"","SET bindtointerface = %s\n",BINDINTERFACE);
      continue;
      }
   }

if (GetVariable("control_common",CFG_CONTROLBODY[cfg_syslog_host].lval,&retval,&rettype) != cf_notype)
   {
   SYSLOGPORT = (unsigned short)Str2Int(retval);
   }

if (GetVariable("control_common",CFG_CONTROLBODY[cfg_syslog_port].lval,&retval,&rettype) != cf_notype)
   {
   strncpy(SYSLOGHOST,Hostname2IPString(retval),CF_MAXVARSIZE-1);
   }

if (GetVariable("control_common",CFG_CONTROLBODY[cfg_fips_mode].lval,&retval,&rettype) != cf_notype)
   {
   FIPS_MODE = GetBoolean(retval);
   CfOut(cf_verbose,"","SET FIPS_MODE = %d\n",FIPS_MODE);
   }
}

/*********************************************************************/

static void KeepContextBundles()
    
{ struct Bundle *bp;
  struct SubType *sp;
  struct Promise *pp;
  char *scope;

/* Dial up the generic promise expansion with a callback */

for (bp = BUNDLES; bp != NULL; bp = bp->next) /* get schedule */
   {
   scope = bp->name;
   SetNewScope(bp->name);
   
   if ((strcmp(bp->type,CF_AGENTTYPES[cf_server]) == 0) || (strcmp(bp->type,CF_AGENTTYPES[cf_common]) == 0))
      {
      DeletePrivateClassContext(); // Each time we change bundle
      
      BannerBundle(bp,NULL);
      scope = bp->name;
      
      for (sp = bp->subtypes; sp != NULL; sp = sp->next) /* get schedule */
         {
         if (strcmp(sp->name,"vars") != 0 && strcmp(sp->name,"classes") != 0)
            {
            continue;
            }
         
         BannerSubType(scope,sp->name,0);
         SetScope(scope);
         AugmentScope(scope,NULL,NULL);
         
         for (pp = sp->promiselist; pp != NULL; pp=pp->next)
            {
            ExpandPromise(cf_server,scope,pp,KeepServerPromise);
            }
         }
      }
   }
}

/*********************************************************************/

void KeepPromiseBundles()
    
{ struct Bundle *bp;
  struct SubType *sp;
  struct Promise *pp;
  char *scope;

/* Dial up the generic promise expansion with a callback */

for (bp = BUNDLES; bp != NULL; bp = bp->next) /* get schedule */
   {
   scope = bp->name;
   SetNewScope(bp->name);
   
   if ((strcmp(bp->type,CF_AGENTTYPES[cf_server]) == 0) || (strcmp(bp->type,CF_AGENTTYPES[cf_common]) == 0))
      {
      DeletePrivateClassContext(); // Each time we change bundle
      
      BannerBundle(bp,NULL);
      scope = bp->name;
      
      for (sp = bp->subtypes; sp != NULL; sp = sp->next) /* get schedule */
         {
         if (strcmp(sp->name,"access") != 0 && strcmp(sp->name,"roles") != 0)
            {
            continue;
            }
         
         BannerSubType(scope,sp->name,0);
         SetScope(scope);
         AugmentScope(scope,NULL,NULL);
         
         for (pp = sp->promiselist; pp != NULL; pp=pp->next)
            {
            ExpandPromise(cf_server,scope,pp,KeepServerPromise);
            }
         }
      }
   }
}

/*********************************************************************/
/* Level                                                             */
/*********************************************************************/

static void KeepServerPromise(struct Promise *pp)

{ char *sp = NULL;
 
if (!IsDefinedClass(pp->classes))
   {
   CfOut(cf_verbose,"","Skipping whole promise, as context is %s\n",pp->classes);
   return;
   }

if (VarClassExcluded(pp,&sp))
   {
   CfOut(cf_verbose,"","\n");
   CfOut(cf_verbose,"",". . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
   CfOut(cf_verbose,"","Skipping whole next promise (%s), as var-context %s is not relevant\n",pp->promiser,sp);
   CfOut(cf_verbose,"",". . . . . . . . . . . . . . . . . . . . . . . . . . . . \n");
   return;
   }

if (strcmp(pp->agentsubtype,"classes") == 0)
   {
   KeepClassContextPromise(pp);
   return;
   }

sp = (char *)GetConstraint("resource_type",pp,CF_SCALAR);

if (strcmp(pp->agentsubtype,"access") == 0 && sp && strcmp(sp,"literal") == 0)
   {
   KeepLiteralAccessPromise(pp,"literal");
   return;
   }

if (strcmp(pp->agentsubtype,"access") == 0 && sp && strcmp(sp,"query") == 0)
   {
   KeepQueryAccessPromise(pp,"query");
   return;
   }

if (strcmp(pp->agentsubtype,"access") == 0 && sp && strcmp(sp,"context") == 0)
   {
   KeepLiteralAccessPromise(pp,"context");
   return;
   }

/* Default behaviour is file access */

if (strcmp(pp->agentsubtype,"access") == 0)
   {
   KeepFileAccessPromise(pp);
   return;
   }

if (strcmp(pp->agentsubtype,"roles") == 0)
   {
   KeepServerRolePromise(pp);
   return;
   }
}

/*********************************************************************/

void KeepFileAccessPromise(struct Promise *pp)

{ struct Constraint *cp;
  struct Rlist *rp;
  struct Auth *ap,*dp;
  char *val;

if (strlen(pp->promiser) != 1)
   {
   DeleteSlash(pp->promiser);
   }

if (!GetAuthPath(pp->promiser,VADMIT))
   {
   InstallServerAuthPath(pp->promiser,&VADMIT,&VADMITTOP);
   }

if (!GetAuthPath(pp->promiser,VDENY))
   {
   InstallServerAuthPath(pp->promiser,&VDENY,&VDENYTOP);
   }

ap = GetAuthPath(pp->promiser,VADMIT);
dp = GetAuthPath(pp->promiser,VDENY);

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   if (!IsDefinedClass(cp->classes))
      {
      continue;
      }

   switch (cp->type)
      {
      case CF_SCALAR:

          val = (char *)cp->rval;

          if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_encrypted].lval) == 0)
             {
             ap->encrypt = true;
             }
             
          break;

      case CF_LIST:
          
          for (rp = (struct Rlist *)cp->rval; rp != NULL; rp=rp->next)
             {
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_admit].lval) == 0)
                {
                PrependItem(&(ap->accesslist),rp->item,NULL);
                continue;
                }
             
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_deny].lval) == 0)
                {
                PrependItem(&(dp->accesslist),rp->item,NULL);
                continue;
                }

             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_maproot].lval) == 0)
                {
                PrependItem(&(ap->maproot),rp->item,NULL);
                continue;
                }
             }
          break;

      case CF_FNCALL:
          /* Shouldn't happen */
          break;
      }
   }
}

/*********************************************************************/

void KeepLiteralAccessPromise(struct Promise *pp,char *type)

{ struct Constraint *cp;
  struct Rlist *rp;
  struct Auth *ap,*dp;
  char *handle = GetConstraint("handle",pp,CF_SCALAR);
  char *val;

if (handle == NULL)
   {
   CfOut(cf_error,"","Access to literal server data requires you to define a promise handle for reference");
   return;
   }
  
if (!GetAuthPath(handle,VARADMIT))
   {
   InstallServerAuthPath(handle,&VARADMIT,&VARADMITTOP);
   }

RegisterLiteralServerData(handle,pp);

if (!GetAuthPath(handle,VARDENY))
   {
   InstallServerAuthPath(handle,&VARDENY,&VARDENYTOP);
   }

ap = GetAuthPath(handle,VARADMIT);
dp = GetAuthPath(handle,VARDENY);

if (strcmp(type,"literal") == 0)
   {
   ap->literal = true;
   }

if (strcmp(type,"context") == 0)
   {
   ap->classpattern = true;
   }

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   if (!IsDefinedClass(cp->classes))
      {
      continue;
      }

   switch (cp->type)
      {
      case CF_SCALAR:

          val = (char *)cp->rval;

          if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_encrypted].lval) == 0)
             {
             ap->encrypt = true;
             }
             
          break;

      case CF_LIST:
          
          for (rp = (struct Rlist *)cp->rval; rp != NULL; rp=rp->next)
             {
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_admit].lval) == 0)
                {
                PrependItem(&(ap->accesslist),rp->item,NULL);
                continue;
                }
             
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_deny].lval) == 0)
                {
                PrependItem(&(dp->accesslist),rp->item,NULL);
                continue;
                }

             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_maproot].lval) == 0)
                {
                PrependItem(&(ap->maproot),rp->item,NULL);
                continue;
                }
             }
          break;

      case CF_FNCALL:
          /* Shouldn't happen */
          break;
      }
   }
}

/*********************************************************************/

void KeepQueryAccessPromise(struct Promise *pp,char *type)

{ struct Constraint *cp;
  struct Rlist *rp;
  struct Auth *ap,*dp;
  char *val;

if (!GetAuthPath(pp->promiser,VARADMIT))
   {
   InstallServerAuthPath(pp->promiser,&VARADMIT,&VARADMITTOP);
   }

RegisterLiteralServerData(pp->promiser,pp);

if (!GetAuthPath(pp->promiser,VARDENY))
   {
   InstallServerAuthPath(pp->promiser,&VARDENY,&VARDENYTOP);
   }

ap = GetAuthPath(pp->promiser,VARADMIT);
dp = GetAuthPath(pp->promiser,VARDENY);

if (strcmp(type,"query") == 0)
   {
   ap->literal = true;
   }

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   if (!IsDefinedClass(cp->classes))
      {
      continue;
      }

   switch (cp->type)
      {
      case CF_SCALAR:

          val = (char *)cp->rval;

          if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_encrypted].lval) == 0)
             {
             ap->encrypt = true;
             }
             
          break;

      case CF_LIST:
          
          for (rp = (struct Rlist *)cp->rval; rp != NULL; rp=rp->next)
             {
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_admit].lval) == 0)
                {
                PrependItem(&(ap->accesslist),rp->item,NULL);
                continue;
                }
             
             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_deny].lval) == 0)
                {
                PrependItem(&(dp->accesslist),rp->item,NULL);
                continue;
                }

             if (strcmp(cp->lval,CF_REMACCESS_BODIES[cfs_maproot].lval) == 0)
                {
                PrependItem(&(ap->maproot),rp->item,NULL);
                continue;
                }
             }
          break;

      case CF_FNCALL:
          /* Shouldn't happen */
          break;
      }
   }
}

/*********************************************************************/

static void KeepServerRolePromise(struct Promise *pp)

{ struct Constraint *cp;
  struct Rlist *rp;
  struct Auth *ap;

if (!GetAuthPath(pp->promiser,ROLES))
   {
   InstallServerAuthPath(pp->promiser,&ROLES,&ROLESTOP);
   }

ap = GetAuthPath(pp->promiser,ROLES);

for (cp = pp->conlist; cp != NULL; cp = cp->next)
   {
   if (!IsDefinedClass(cp->classes))
      {
      continue;
      }

   switch (cp->type)
      {
      case CF_LIST:
          
          for (rp = (struct Rlist *)cp->rval; rp != NULL; rp=rp->next)
             {
             if (strcmp(cp->lval,CF_REMROLE_BODIES[cfs_authorize].lval) == 0)
                {
                PrependItem(&(ap->accesslist),rp->item,NULL);
                continue;
                }
             }
          break;

      case CF_FNCALL:
          /* Shouldn't happen */
          break;

      default:

          if (strcmp(cp->lval,"comment") == 0 || strcmp(cp->lval,"handle") == 0)
             {
             }
          else
             {
             CfOut(cf_error,"","RHS of authorize promise for %s should be a list\n",pp->promiser);
             }
          break;
      }
   }
}

/***********************************************************************/
/* Level                                                               */
/***********************************************************************/

static void InstallServerAuthPath(char *path,struct Auth **list,struct Auth **listtop)

{ struct Auth *ptr;

#ifdef MINGW
int i;
for(i = 0; path[i] != '\0'; i++)
  {
  path[i] = ToLower(path[i]);
  }
#endif  /* MINGW */

if ((ptr = (struct Auth *)malloc(sizeof(struct Auth))) == NULL)
   {
   FatalError("Memory Allocation failed for InstallAuthPath() #1");
   }

if ((ptr->path = strdup(path)) == NULL)
   {
   FatalError("Memory Allocation failed for InstallAuthPath() #3");
   }

if (*listtop == NULL)                 /* First element in the list */
   {
   *list = ptr;
   }
else
   {
   (*listtop)->next = ptr;
   }

ptr->accesslist = NULL;
ptr->maproot = NULL;
ptr->literal = false;
ptr->encrypt = false; 
ptr->next = NULL;
*listtop = ptr;
}

/***********************************************************************/
/* Level                                                               */
/***********************************************************************/

struct Auth *GetAuthPath(char *path,struct Auth *list)

{ struct Auth *ap;

#ifdef MINGW
int i;
for(i = 0; path[i] != '\0'; i++)
  {
  path[i] = ToLower(path[i]);
  }
#endif  /* MINGW */

if (strlen(path) != 1)
   {
   DeleteSlash(path);
   }

for (ap = list; ap != NULL; ap=ap->next)
   {
   if (strcmp(ap->path,path) == 0)
      {
      return ap;
      }
   }

return NULL;
}

/***********************************************************************/
