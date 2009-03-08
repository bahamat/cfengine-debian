/* 
   Copyright (C) 2008 - Cfengine AS

   This file is part of Cfengine 3 - written and maintained by Cfengine AS.
 
   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the
   Free Software Foundation; either version 3, or (at your option) any
   later version. 
   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
 
  You should have received a copy of the GNU General Public License
  
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA

*/

/*****************************************************************************/
/*                                                                           */
/* File: pipes.c                                                             */
/*                                                                           */
/*****************************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

/*****************************************************************************/

# if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
extern pthread_attr_t PTHREADDEFAULTS;
extern pthread_mutex_t MUTEX_COUNT;
extern pthread_mutex_t MUTEX_HOSTNAME;
# endif

pid_t *CHILDREN;
int    MAX_FD = 20; /* Max number of simultaneous pipes */

/*****************************************************************************/

FILE *cf_popen(char *command,char *type)

 { static char arg[CF_MAXSHELLARGS][CF_BUFSIZE];
   int i, argc, pd[2];
   char **argv;
   pid_t pid;
   FILE *pp = NULL;

Debug("cf_popen(%s)\n",command);

if ((*type != 'r' && *type != 'w') || (type[1] != '\0'))
   {
   errno = EINVAL;
   return NULL;
   }

#if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
if (pthread_mutex_lock(&MUTEX_COUNT) != 0)
   {
   CfOut(cf_error,"pthread_mutex_lock","pthread_mutex_unlock failed");
   return NULL;
   }
#endif

if (CHILDREN == NULL)   /* first time */
   {
   if ((CHILDREN = calloc(MAX_FD,sizeof(pid_t))) == NULL)
      {
#if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
      pthread_mutex_unlock(&MUTEX_COUNT);
#endif
      return NULL;
      }
   }

#if defined HAVE_PTHREAD_H && (defined HAVE_LIBPTHREAD || defined BUILDTIN_GCC_THREAD)
if (pthread_mutex_unlock(&MUTEX_COUNT) != 0)
   {
   CfOut(cf_error,"pthread_mutex_unlock","pthread_mutex_unlock failed");
   return NULL;
   }
#endif


if (pipe(pd) < 0)        /* Create a pair of descriptors to this process */
   {
   return NULL;
   }

if ((pid = fork()) == -1)
   {
   return NULL;
   }

signal(SIGCHLD,SIG_DFL);

ALARM_PID = (pid != 0 ? pid : -1);

if (pid == 0)
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[0]);        /* Don't need output from parent */
          
          if (pd[1] != 1)
             {
             dup2(pd[1],1);    /* Attach pp=pd[1] to our stdout */
             dup2(pd[1],2);    /* Merge stdout/stderr */
             close(pd[1]);
             }
          
          break;
          
      case 'w':
          
          close(pd[1]);
          
          if (pd[0] != 0)
             {
             dup2(pd[0],0);
             close(pd[0]);
             }
       }
   
   for (i = 0; i < MAX_FD; i++)
      {
      if (CHILDREN[i] > 0)
         {
         close(i);
         }
      }
   
   argc = ArgSplitCommand(command,arg);
   argv = (char **) malloc((argc+1)*sizeof(char *));
   
   if (argv == NULL)
      {
      FatalError("Out of memory");
      }
   
   for (i = 0; i < argc; i++)
      {
      argv[i] = arg[i];
      }
   
   argv[i] = (char *) NULL;
   
   if (execv(arg[0],argv) == -1)
      {
      CfOut(cf_error,"execv","Couldn't run %s",arg[0]);
      }
   
   free((char *)argv);
   _exit(1);
   }
else
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[1]);
          
          if ((pp = fdopen(pd[0],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
          break;
          
      case 'w':
          
          close(pd[0]);
          
          if ((pp = fdopen(pd[1],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
      }
   
   if (fileno(pp) >= MAX_FD)
      {
      CfOut(cf_error,"","File descriptor %d of child %d higher than MAX_FD, check for defunct children", fileno(pp), pid);
      }
   else
      {
      CHILDREN[fileno(pp)] = pid;
      }

   return pp;
   }

return NULL; /* Cannot reach here */
}

/*****************************************************************************/

FILE *cf_popensetuid(char *command,char *type,uid_t uid,gid_t gid,char *chdirv,char *chrootv)
    
 { static char arg[CF_MAXSHELLARGS][CF_BUFSIZE];
   int i, argc, pd[2];
   char **argv;
   pid_t pid;
   FILE *pp = NULL;

Debug("cfpopensetuid(%s,%s,%d,%d)\n",command,type,uid,gid);

if ((*type != 'r' && *type != 'w') || (type[1] != '\0'))
   {
   errno = EINVAL;
   return NULL;
   }

if (CHILDREN == NULL)   /* first time */
   {
   if ((CHILDREN = calloc(MAX_FD,sizeof(pid_t))) == NULL)
      {
      return NULL;
      }
   }

if (pipe(pd) < 0)        /* Create a pair of descriptors to this process */
   {
   return NULL;
   }

if ((pid = fork()) == -1)
   {
   return NULL;
   }

signal(SIGCHLD,SIG_DFL);
ALARM_PID = (pid != 0 ? pid : -1);

if (pid == 0)
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[0]);        /* Don't need output from parent */
          
          if (pd[1] != 1)
             {
             dup2(pd[1],1);    /* Attach pp=pd[1] to our stdout */
             dup2(pd[1],2);    /* Merge stdout/stderr */
             close(pd[1]);
             }
          
          break;
          
      case 'w':
          
          close(pd[1]);
          
          if (pd[0] != 0)
             {
             dup2(pd[0],0);
             close(pd[0]);
             }
      }
   
   for (i = 0; i < MAX_FD; i++)
      {
      if (CHILDREN[i] > 0)
         {
         close(i);
         }
      }
   
   argc = ArgSplitCommand(command,arg);
   argv = (char **) malloc((argc+1)*sizeof(char *));
   
   if (argv == NULL)
      {
      FatalError("Out of memory");
      }
   
   for (i = 0; i < argc; i++)
      {
      argv[i] = arg[i];
      }
   
   argv[i] = (char *) NULL;
   
   if (chrootv && strlen(chrootv) != 0)
      {
      if (chroot(chrootv) == -1)
         {
         CfOut(cf_error,"chroot","Couldn't chroot to %s\n",chrootv);
         free((char *)argv);
         return NULL;
         }
      }
   
   if (chdirv && strlen(chdirv) != 0)
      {
      if (chdir(chdirv) == -1)
         {
         CfOut(cf_error,"chdir","Couldn't chdir to %s\n",chdirv);
         free((char *)argv);
         return NULL;
         }
      }
   
   if (!CfSetuid(uid,gid))
      {
      free((char *)argv);
      _exit(1);
      }
   
   if (execv(arg[0],argv) == -1)
      {
      CfOut(cf_error,"execv","Couldn't run %s",arg[0]);
      }
   
   free((char *)argv);
   _exit(1);
   }
else
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[1]);
          
          if ((pp = fdopen(pd[0],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
          break;
          
      case 'w':
          
          close(pd[0]);
          
          if ((pp = fdopen(pd[1],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
      }
   
   if (fileno(pp) >= MAX_FD)
      {
      CfOut(cf_error,"","File descriptor %d of child %d higher than MAX_FD, check for defunct children", fileno(pp), pid);
      }
   else
      {
      CHILDREN[fileno(pp)] = pid;
      }
   
   return pp;
   }

return NULL; /* cannot reach here */
}

/*****************************************************************************/
/* Shell versions of commands - not recommended for security reasons         */
/*****************************************************************************/

FILE *cf_popen_sh(char *command,char *type)
    
 { int i,pd[2];
   pid_t pid;
   FILE *pp = NULL;

Debug("cf_popen_sh(%s)\n",command);

if ((*type != 'r' && *type != 'w') || (type[1] != '\0'))
   {
   errno = EINVAL;
   return NULL;
   }

if (CHILDREN == NULL)   /* first time */
   {
   if ((CHILDREN = calloc(MAX_FD,sizeof(pid_t))) == NULL)
      {
      return NULL;
      }
   }

if (pipe(pd) < 0)        /* Create a pair of descriptors to this process */
   {
   return NULL;
   }

if ((pid = fork()) == -1)
   {
   return NULL;
   }

signal(SIGCHLD,SIG_DFL);
ALARM_PID = (pid != 0 ? pid : -1);

if (pid == 0)
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[0]);        /* Don't need output from parent */
          
          if (pd[1] != 1)
             {
             dup2(pd[1],1);    /* Attach pp=pd[1] to our stdout */
             dup2(pd[1],2);    /* Merge stdout/stderr */
             close(pd[1]);
             }
          
          break;
          
      case 'w':
          
          close(pd[1]);
          
          if (pd[0] != 0)
             {
             dup2(pd[0],0);
             close(pd[0]);
             }
      }
   
   for (i = 0; i < MAX_FD; i++)
      {
      if (CHILDREN[i] > 0)
         {
         close(i);
         }
      }
   
   execl("/bin/sh","sh","-c",command,NULL);
   _exit(1);
   }
else
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[1]);
          
          if ((pp = fdopen(pd[0],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
          break;
          
      case 'w':
          
          close(pd[0]);
          
          if ((pp = fdopen(pd[1],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
      }
   
   if (fileno(pp) >= MAX_FD)
      {
      CfOut(cf_error,"","File descriptor %d of child %d higher than MAX_FD, check for defunct children", fileno(pp), pid);
      }
   else
      {
      CHILDREN[fileno(pp)] = pid;
      }
   
   return pp;
   }

return NULL;
}

/******************************************************************************/

FILE *cf_popen_shsetuid(char *command,char *type,uid_t uid,gid_t gid,char *chdirv,char *chrootv)
    
 { int i,pd[2];
   pid_t pid;
   FILE *pp = NULL;

Debug("cf_popen_shsetuid(%s,%s,%d,%d)\n",command,type,uid,gid);

if ((*type != 'r' && *type != 'w') || (type[1] != '\0'))
   {
   errno = EINVAL;
   return NULL;
   }

if (CHILDREN == NULL)   /* first time */
   {
   if ((CHILDREN = calloc(MAX_FD,sizeof(pid_t))) == NULL)
      {
      return NULL;
      }
   }

if (pipe(pd) < 0)        /* Create a pair of descriptors to this process */
   {
   return NULL;
   }

if ((pid = fork()) == -1)
   {
   return NULL;
   }

signal(SIGCHLD,SIG_DFL);
ALARM_PID = (pid != 0 ? pid : -1);

if (pid == 0)
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[0]);        /* Don't need output from parent */
          
          if (pd[1] != 1)
             {
             dup2(pd[1],1);    /* Attach pp=pd[1] to our stdout */
             dup2(pd[1],2);    /* Merge stdout/stderr */
             close(pd[1]);
             }
          
          break;
          
      case 'w':
          
          close(pd[1]);
          
          if (pd[0] != 0)
             {
             dup2(pd[0],0);
             close(pd[0]);
             }
      }
   
   for (i = 0; i < MAX_FD; i++)
      {
      if (CHILDREN[i] > 0)
         {
         close(i);
         }
      }
   
   if (chrootv && strlen(chrootv) != 0)
      {
      if (chroot(chrootv) == -1)
         {
         CfOut(cf_error,"chroot","Couldn't chroot to %s\n",chrootv);
         return NULL;
         }
      }
   
   if (chdirv && strlen(chdirv) != 0)
      {
      if (chdir(chdirv) == -1)
         {
         CfOut(cf_error,"chdir","Couldn't chdir to %s\n",chdirv);
         return NULL;
         }
      }
   
   if (!CfSetuid(uid,gid))
      {
      _exit(1);
      }
   
   execl("/bin/sh","sh","-c",command,NULL);
   _exit(1);
   }
else
   {
   switch (*type)
      {
      case 'r':
          
          close(pd[1]);
          
          if ((pp = fdopen(pd[0],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
          break;
          
      case 'w':
          
          close(pd[0]);
          
          if ((pp = fdopen(pd[1],type)) == NULL)
             {
             cf_pwait(pid);
             return NULL;
             }
      }
   
   if (fileno(pp) >= MAX_FD)
      {
      CfOut(cf_error,"","File descriptor %d of child %d higher than MAX_FD, check for defunct children", fileno(pp), pid);
      cf_pwait(pid);
      return NULL;
      }
   else
      {
      CHILDREN[fileno(pp)] = pid;
      }
   return pp;
   }

return NULL;
}


/******************************************************************************/
/* Close commands                                                             */
/******************************************************************************/

int cf_pwait(pid_t pid)

{ int status, wait_result;

Debug("cf_pwait - Waiting for process %d\n",pid); 

#ifdef HAVE_WAITPID

while(waitpid(pid,&status,0) < 0)
   {
   if (errno != EINTR)
      {
      return -1;
      }
   }

return status; 
 
#else

while ((wait_result = wait(&status)) != pid)
   {
   if (wait_result <= 0)
      {
      CfOut(cf_inform,"wait","Wait for child failed\n");
      return -1;
      }
   }
 
if (WIFSIGNALED(status))
   {
   return -1;
   }
 
if (! WIFEXITED(status))
   {
   return -1;
   }
 
return (WEXITSTATUS(status));
#endif
}

/*******************************************************************/

int cf_pclose(FILE *pp)

{ int fd, status, wait_result;
  pid_t pid;

Debug("cf_pclose(pp)\n");

if (CHILDREN == NULL)  /* popen hasn't been called */
   {
   return -1;
   }

ALARM_PID = -1;
fd = fileno(pp);

if (fd >= MAX_FD)
   {
   CfOut(cf_error,"","File descriptor %d of child higher than MAX_FD, check for defunct children", fd);
   pid = -1;
   }
else
   {
   if ((pid = CHILDREN[fd]) == 0)
      {
      return -1;
      }
   
   CHILDREN[fd] = 0;
   }

if (fclose(pp) == EOF)
   {
   return -1;
   }

return cf_pwait(pid);
}

/*******************************************************************/

int cf_pclose_def(FILE *pfp,struct Attributes a,struct Promise *pp)

{ int fd, status, wait_result;
  pid_t pid;

Debug("cf_pclose_def(pfp)\n");

if (CHILDREN == NULL)  /* popen hasn't been called */
   {
   return -1;
   }

ALARM_PID = -1;
fd = fileno(pfp);

if (fd >= MAX_FD)
   {
   CfOut(cf_error,"","File descriptor %d of child higher than MAX_FD, check for defunct children", fd);
   fclose(pfp);
   return -1;
   }

if ((pid = CHILDREN[fd]) == 0)
   {
   return -1;
   }

CHILDREN[fd] = 0;

if (fclose(pfp) == EOF)
   {
   return -1;
   }

Debug("cf_pclose_def - Waiting for process %d\n",pid); 

#ifdef HAVE_WAITPID

while(waitpid(pid,&status,0) < 0)
   {
   if (errno != EINTR)
      {
      return -1;
      }
   }

if (status == 0)
   {
   Debug(" -> Finished script %s ok\n",pp->promiser);
   }
else
   {
   cfPS(cf_inform,CF_INTERPT,"",pp,a," !! Finished script %s -- an error occurred\n",pp->promiser);
   }

return status; 
 
#else

while ((wait_result = wait(&status)) != pid)
   {
   if (wait_result <= 0)
      {
      CfOut(cf_inform,"wait","Wait for child failed\n");
      return -1;
      }
   }
 

if (WIFSIGNALED(status))
   {
   cfPS(cf_inform,CF_INTERPT,"",pp,a," -> Finished script - interrupted %s\n",pp->promiser);
   return -1;
   }

if (!WIFEXITED(status))
   {
   cfPS(cf_inform,CF_FAIL,"",pp,a," !! Finished script - failed %s\n",pp->promiser);
   return -1;
   }

if (WEXITSTATUS(status) == 0)
   {
   Debug(" -> Finished script %s ok\n",pp->promiser);
   }
else
   {
   if (errno != EINTR)
      {
      cfPS(cf_inform,CF_FAIL,"",pp,a," !! Finished script - failed %s\n",pp->promiser);
      return -1;
      }
   else
      {
      cfPS(cf_inform,CF_INTERPT,"",pp,a," !! Script %s - interrupt\n",pp->promiser);
      }
   }

return (WEXITSTATUS(status));
#endif
}

/*******************************************************************/

int CfSetuid(uid_t uid,gid_t gid)

{ struct passwd *pw;
 
if (gid != (gid_t) -1)
   {
   CfOut(cf_verbose,"","Changing gid to %d\n",gid);      
   
   if (setgid(gid) == -1)
      {
      CfOut(cf_error,"setgid","Couldn't set gid to %d\n",gid);
      return false;
      }

   /* Now eliminate any residual privileged groups */
   
   if ((pw = getpwuid(uid)) == NULL)
      {
      CfOut(cf_error,"initgroups","Unable to get login groups when dropping privilege to %d",uid);
      return false;
      }
   
   if (initgroups(pw->pw_name, pw->pw_gid) == -1)
      {
      CfOut(cf_error,"initgroups","Unable to set login groups when dropping privilege to %s=%d",pw->pw_name,uid);
      return false;
      }
   }

if (uid != (uid_t) -1)
   {
   CfOut(cf_verbose,"","Changing uid to %d\n",uid);
   
   if (setuid(uid) == -1)
      {
      CfOut(cf_error,"setuid","Couldn't set uid to %d\n",uid);
      return false;
      }
   }

return true;
}

/*******************************************************************/
/* Command exec aids                                               */
/*******************************************************************/

int ArgSplitCommand(char *comm,char arg[CF_MAXSHELLARGS][CF_BUFSIZE])

{ char *sp;
  int i = 0;

for (sp = comm; sp < comm+strlen(comm); sp++)
   {
   if (i >= CF_MAXSHELLARGS-1)
      {
      CfOut(cf_error,"","Too many arguments in embedded script");
      FatalError("Use a wrapper");
      }
   
   while (*sp == ' ' || *sp == '\t')
      {
      sp++;
      }
   
   switch (*sp)
      {
      case '\0': return(i-1);
   
      case '\"': sscanf (++sp,"%[^\"]",arg[i]);
          break;
      case '\'': sscanf (++sp,"%[^\']",arg[i]);
          break;
      case '`':  sscanf (++sp,"%[^`]",arg[i]);
          break;
      default:   sscanf (sp,"%s",arg[i]);
          break;
      }
   
   sp += strlen(arg[i]);
   i++;
   }
 
 return (i);
}
