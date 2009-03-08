
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

/*******************************************************************/
/*                                                                 */
/* File copying                                                    */
/*                                                                 */
/* client part for remote copying                                  */
/*                                                                 */
/*******************************************************************/

#include "cf3.defs.h"
#include "cf3.extern.h"

/*********************************************************************/
/* cfAgent's connection cache                                        */
/*********************************************************************/


/*********************************************************************/

void DetermineCfenginePort()

{ struct servent *server;

if ((server = getservbyname(CFENGINE_SERVICE,"tcp")) == NULL)
   {
   CfOut(cf_verbose,"getservbyname","No registered cfengine service, using default");
   snprintf(STR_CFENGINEPORT,15,"5308");
   SHORT_CFENGINEPORT = htons((unsigned short)5308);
   }
else
   {
   snprintf(STR_CFENGINEPORT,15,"%u",ntohs(server->s_port));
   SHORT_CFENGINEPORT = server->s_port;
   }

CfOut(cf_verbose,"","Setting cfengine default port to %u = %s\n",ntohs(SHORT_CFENGINEPORT),STR_CFENGINEPORT);
}

/*********************************************************************/

struct cfagent_connection *NewServerConnection(struct Attributes attr,struct Promise *pp)

{ struct cfagent_connection *conn;
  struct Rlist *rp;
 
// First one in goal has to open the connection, or mark it failed or private (thread)

 // We never close a non-background connection until end
 // mark serial connections as such
 
for (rp = attr.copy.servers; rp != NULL; rp = rp->next)
   {
   if (ServerOffline(rp->item))
      {
      continue;
      }

   pp->this_server = rp->item;

   if (attr.transaction.background)
      {
      if (RlistLen(SERVERLIST) < CFA_MAXTHREADS)
         {
         conn = ServerConnection(rp->item,attr,pp);
         return conn;
         }
      }
   else
      {   
      if (conn = ServerConnectionReady(rp->item))
         {
         return conn;
         }

      /* This is first usage, need to open */
      
      conn = ServerConnection(rp->item,attr,pp);

      if (conn == NULL)
         {
         cfPS(cf_inform,CF_FAIL,"",pp,attr,"Unable to establish connection with %s\n",rp->item);
         MarkServerOffline(rp->item);
         }
      else
         {
         CacheServerConnection(conn,rp->item);
         return conn;
         }
      }
   }

pp->this_server = NULL;
return NULL;
}

/*****************************************************************************/

struct cfagent_connection *ServerConnection(char *server,struct Attributes attr,struct Promise *pp)

{ struct cfagent_connection *conn;

if ((conn = NewAgentConn()) == NULL)
   {
   cfPS(cf_error,CF_FAIL,"malloc",pp,attr,"Unable to allocate connection structure for %s",server);
   return NULL;
   }
 
if (strcmp(server,"localhost") == 0)
   {
   conn->authenticated = true;
   return conn;
   }

conn->authenticated = false;
 
if (conn->sd == CF_NOT_CONNECTED)
   {   
   Debug("Opening server connnection to %s\n",server);
   
   if (!ServerConnect(conn,server,attr,pp))
      {
      CfOut(cf_inform,"socket","No server is responding on this port");

      if (conn->sd != CF_NOT_CONNECTED)
         {
         ServerDisconnection(conn);
         }

      return NULL;
      }

   Debug("Remote IP set to %s\n",conn->remoteip);
   
   if (!IdentifyAgent(conn->sd,conn->localip,conn->family))
      {
      CfOut(cf_error,"","Id-authentication for %s failed\n",VFQNAME);
      errno = EPERM;
      ServerDisconnection(conn);
      return NULL;
      }

   if (!AuthenticateAgent(conn,attr,pp))
      {
      CfOut(cf_error,"","Authentication dialogue with %s failed\n",server);
      errno = EPERM;
      ServerDisconnection(conn);
      return NULL;
      }

   conn->authenticated = true;
   return conn;
   }
else
   {
   Debug("Server connection to %s already open on %d\n",server,conn->sd);
   }

return conn; 
}

/*********************************************************************/

void ServerDisconnection(struct cfagent_connection *conn)

{
Debug("Closing current server connection\n");

close(conn->sd);
conn->sd = CF_NOT_CONNECTED;
DeleteAgentConn(conn);
}

/*********************************************************************/

int cf_remote_stat(char *file,struct stat *buf,char *stattype,struct Attributes attr,struct Promise *pp)

/* If a link, this reads readlink and sends it back in the same
   package. It then caches the value for each copy command */

{ char sendbuffer[CF_BUFSIZE];
  char recvbuffer[CF_BUFSIZE];
  char in[CF_BUFSIZE],out[CF_BUFSIZE];
  struct cfagent_connection *conn = pp->conn;
  struct cfstat cfst;
  int ret,tosend,cipherlen;
  time_t tloc;

Debug("cf_remotestat(%s,%s)\n",file,stattype);
memset(recvbuffer,0,CF_BUFSIZE); 

if (strlen(file) > CF_BUFSIZE-30)
   {
   CfOut(cf_error,"","Filename too long");
   return -1;
   }
 
ret = CacheStat(file,buf,stattype,attr,pp);

if (ret != 0)
   {
   return ret;
   }

if ((tloc = time((time_t *)NULL)) == -1)
   {
   CfOut(cf_error,"","Couldn't read system clock\n");
   }

sendbuffer[0] = '\0';
 
if (attr.copy.encrypt)
   {
   if (conn->session_key == NULL)
      {
      cfPS(cf_error,CF_FAIL,"",pp,attr,"Cannot do encrypted copy without keys (use cfkey)");
      return -1;
      }
   
   snprintf(in,CF_BUFSIZE-1,"SYNCH %d STAT %s",tloc,file);
   cipherlen = EncryptString(in,out,conn->session_key,strlen(in)+1);
   snprintf(sendbuffer,CF_BUFSIZE-1,"SSYNCH %d",cipherlen);
   memcpy(sendbuffer+CF_PROTO_OFFSET,out,cipherlen);
   tosend = cipherlen+CF_PROTO_OFFSET;
   }
else
   {
   snprintf(sendbuffer,CF_BUFSIZE,"SYNCH %d STAT %s",tloc,file);
   tosend = strlen(sendbuffer);
   }

if (SendTransaction(conn->sd,sendbuffer,tosend,CF_DONE) == -1)
   {
   cfPS(cf_inform,CF_INTERPT,"send",pp,attr,"Transmission failed/refused talking to %.255s:%.255s in stat",pp->this_server,file);
   return -1;
   }

if (ReceiveTransaction(conn->sd,recvbuffer,NULL) == -1)
   {
   return -1;
   }

if (strstr(recvbuffer,"unsynchronized"))
   {
   CfOut(cf_error,"","Clocks differ too much to do copy by date (security) %s",recvbuffer+4);
   return -1;
   }

if (BadProtoReply(recvbuffer))
   {
   CfOut(cf_verbose,"","Server returned error: %s\n",recvbuffer+4);
   errno = EPERM;
   return -1;
   }

if (OKProtoReply(recvbuffer))
   {
   long d1,d2,d3,d4,d5,d6,d7,d8,d9,d10,d11,d12=0,d13=0;
   
   sscanf(recvbuffer,"OK: %1ld %5ld %14ld %14ld %14ld %14ld %14ld %14ld %14ld %14ld %14ld %14ld %14ld",
   &d1,&d2,&d3,&d4,&d5,&d6,&d7,&d8,&d9,&d10,&d11,&d12,&d13);

   cfst.cf_type = (enum cf_filetype) d1;
   cfst.cf_mode = (mode_t) d2;
   cfst.cf_lmode = (mode_t) d3;
   cfst.cf_uid = (uid_t) d4;
   cfst.cf_gid = (gid_t) d5;
   cfst.cf_size = (off_t) d6;
   cfst.cf_atime = (time_t) d7;
   cfst.cf_mtime = (time_t) d8;
   cfst.cf_ctime = (time_t) d9;
   cfst.cf_makeholes = (char) d10;
   pp->makeholes = (char) d10;
   cfst.cf_ino = d11;
   cfst.cf_nlink = d12;
   cfst.cf_dev = d13;

   /* Use %?d here to avoid memory overflow attacks */

   Debug("Mode = %d,%d\n",d2,d3);
   
   Debug("OK: type=%d\n mode=%o\n lmode=%o\n uid=%d\n gid=%d\n size=%ld\n atime=%d\n mtime=%d ino=%d nlnk=%d, dev=%d\n",
 cfst.cf_type,cfst.cf_mode,cfst.cf_lmode,cfst.cf_uid,cfst.cf_gid,(long)cfst.cf_size,
 cfst.cf_atime,cfst.cf_mtime,cfst.cf_ino,cfst.cf_nlink,cfst.cf_dev);

   memset(recvbuffer,0,CF_BUFSIZE);
   
   if (ReceiveTransaction(conn->sd,recvbuffer,NULL) == -1)
      {
      return -1;
      }
   
   Debug("Linkbuffer: %s\n",recvbuffer);

   if (strlen(recvbuffer) > 3)
      {
      cfst.cf_readlink = strdup(recvbuffer+3);
      }
   else
      {
      cfst.cf_readlink = NULL;
      }

   switch (cfst.cf_type)
      {
      case cf_reg:   cfst.cf_mode |= (mode_t) S_IFREG;
              break;
      case cf_dir:   cfst.cf_mode |= (mode_t) S_IFDIR;
                 break;
      case cf_char:  cfst.cf_mode |= (mode_t) S_IFCHR;
              break;
      case cf_fifo:  cfst.cf_mode |= (mode_t) S_IFIFO;
              break;
      case cf_sock:  cfst.cf_mode |= (mode_t) S_IFSOCK;
              break;
      case cf_block: cfst.cf_mode |= (mode_t) S_IFBLK;
              break;
      case cf_link:  cfst.cf_mode |= (mode_t) S_IFLNK;
              break;
      }


   cfst.cf_filename = strdup(file);
   cfst.cf_server =  strdup(pp->this_server);

   if ((cfst.cf_filename == NULL) ||(cfst.cf_server) == NULL)
      {
      FatalError("Memory allocation in cf_rstat");
      }
   
   cfst.cf_failed = false;

   if (cfst.cf_lmode != 0)
      {
      cfst.cf_lmode |= (mode_t) S_IFLNK;
      }

   NewClientCache(&cfst,pp);

   if ((cfst.cf_lmode != 0) && (strcmp(stattype,"link") == 0))
      {
      buf->st_mode = cfst.cf_lmode;
      }
   else
      {
      buf->st_mode = cfst.cf_mode;
      }

   buf->st_uid = cfst.cf_uid;
   buf->st_gid = cfst.cf_gid;
   buf->st_size = cfst.cf_size;
   buf->st_mtime = cfst.cf_mtime;
   buf->st_ctime = cfst.cf_ctime;
   buf->st_atime = cfst.cf_atime;
   buf->st_ino   = cfst.cf_ino;
   buf->st_dev   = cfst.cf_dev;
   buf->st_nlink = cfst.cf_nlink;
   
   return 0;
   }

CfOut(cf_error,"","Transmission refused or failed statting %s\nGot: %s\n",file,recvbuffer); 
errno = EPERM;
return -1;
}

/*********************************************************************/

CFDIR *cf_remote_opendir(char *dirname,struct Attributes attr,struct Promise *pp)

{ struct cfagent_connection *conn = pp->conn;
  char sendbuffer[CF_BUFSIZE];
  char recvbuffer[CF_BUFSIZE];
  char in[CF_BUFSIZE];
  char out[CF_BUFSIZE];
  int n, done=false, cipherlen = 0,plainlen = 0,tosend;
  CFDIR *cfdirh;
  char *sp;

Debug("CfOpenDir(%s:%s)\n",pp->this_server,dirname);

if (strlen(dirname) > CF_BUFSIZE - 20)
   {
   CfOut(cf_error,"","Directory name too long");
   return NULL;
   }

if ((cfdirh = (CFDIR *)malloc(sizeof(CFDIR))) == NULL)
   {
   CfOut(cf_error,"","Couldn't allocate memory in cf_remote_opendir\n");
   exit(1);
   }

cfdirh->cf_list = NULL;
cfdirh->cf_listpos = NULL;
cfdirh->cf_dirh = NULL;

if (attr.copy.encrypt)
   {
   if (conn->session_key == NULL)
      {
      cfPS(cf_error,CF_INTERPT,"",pp,attr,"Cannot do encrypted copy without keys (use cfkey)");
      return NULL;
      }
   
   snprintf(in,CF_BUFSIZE,"OPENDIR %s",dirname);
   cipherlen = EncryptString(in,out,conn->session_key,strlen(in)+1);
   snprintf(sendbuffer,CF_BUFSIZE-1,"SOPENDIR %d",cipherlen);
   memcpy(sendbuffer+CF_PROTO_OFFSET,out,cipherlen);
   tosend = cipherlen+CF_PROTO_OFFSET;
   }
else
   {
   snprintf(sendbuffer,CF_BUFSIZE,"OPENDIR %s",dirname);
   tosend = strlen(sendbuffer);
   }

if (SendTransaction(conn->sd,sendbuffer,tosend,CF_DONE) == -1)
   {
   free((char *)cfdirh);
   return NULL;
   }

while (!done)
   {
   if ((n = ReceiveTransaction(conn->sd,recvbuffer,NULL)) == -1)
      {
      if (errno == EINTR) 
         {
         continue;
         }

      free((char *)cfdirh);
      return NULL;
      }

   if (n == 0)
      {
      break;
      }

   if (attr.copy.encrypt)
      {
      memcpy(in,recvbuffer,n);
      plainlen = DecryptString(in,recvbuffer,conn->session_key,n);
      }

   if (FailedProtoReply(recvbuffer))
      {
      cfPS(cf_inform,CF_INTERPT,"",pp,attr,"Network access to %s:%s denied\n",pp->this_server,dirname);
      free((char *)cfdirh);
      return NULL;      
      }

   if (BadProtoReply(recvbuffer))
      {
      CfOut(cf_inform,"","%s\n",recvbuffer+4);
      free((char *)cfdirh);
      return NULL;      
      }

   for (sp = recvbuffer; *sp != '\0'; sp++)
      {
      if (strncmp(sp,CFD_TERMINATOR,strlen(CFD_TERMINATOR)) == 0)    /* End transmission */
         {
         cfdirh->cf_listpos = cfdirh->cf_list;
         return cfdirh;
         }

      AppendItem(&(cfdirh->cf_list),sp,NULL);
      
      while(*sp != '\0')
         {
         sp++;
         }
      }
   }
 
 cfdirh->cf_listpos = cfdirh->cf_list;
 return cfdirh;
}

/*********************************************************************/

void NewClientCache(struct cfstat *data,struct Promise *pp)

{ struct cfstat *sp;

Debug("NewClientCache\n");
 
if ((sp = (struct cfstat *) malloc(sizeof(struct cfstat))) == NULL)
   {
   CfOut(cf_error,"","Memory allocation faliure in CacheData()\n");
   return;
   }

memcpy(sp,data,sizeof(struct cfstat));

sp->next = pp->cache;
pp->cache = sp;
}

/*********************************************************************/

void DeleteClientCache(struct Attributes attr,struct Promise *pp)

{ struct cfstat *sp,*sps;

Debug("DeleteClientCache\n");
  
sp = pp->cache;

while (sp != NULL)
   {
   sps = sp;
   sp = sp->next;
   free((char *)sps);
   }

pp->cache = NULL;
}

/*********************************************************************/

int CompareHashNet(char *file1,char *file2,struct Attributes attr,struct Promise *pp)

{ static unsigned char d[CF_MD5_LEN];
  char *sp,sendbuffer[CF_BUFSIZE],recvbuffer[CF_BUFSIZE],in[CF_BUFSIZE],out[CF_BUFSIZE];
  int i,tosend,cipherlen;
  struct cfagent_connection *conn = pp->conn;

HashFile(file2,d,cf_md5);
Debug("Send digest of %s to server, %s\n",file2,HashPrint(cf_md5,d));

memset(recvbuffer,0,CF_BUFSIZE);

if (attr.copy.encrypt)
   {
   snprintf(in,CF_BUFSIZE,"MD5 %s",file1);

   sp = in + strlen(in) + CF_SMALL_OFFSET;

   for (i = 0; i < CF_MD5_LEN; i++)
      {
      *sp++ = d[i];
      }
   
   cipherlen = EncryptString(in,out,conn->session_key,strlen(in)+CF_SMALL_OFFSET+CF_MD5_LEN);
   snprintf(sendbuffer,CF_BUFSIZE,"SMD5 %d",cipherlen);
   memcpy(sendbuffer+CF_PROTO_OFFSET,out,cipherlen);
   tosend = cipherlen + CF_PROTO_OFFSET;
   }
else
   {
   snprintf(sendbuffer,CF_BUFSIZE,"MD5 %s",file1);
   sp = sendbuffer + strlen(sendbuffer) + CF_SMALL_OFFSET;

   for (i = 0; i < CF_MD5_LEN; i++)
      {
      *sp++ = d[i];
      }
   
   tosend = strlen(sendbuffer)+CF_SMALL_OFFSET+CF_MD5_LEN;
   } 
 
if (SendTransaction(conn->sd,sendbuffer,tosend,CF_DONE) == -1)
   {
   cfPS(cf_error,CF_INTERPT,"send",pp,attr,"Failed send");
   return false;
   }

if (ReceiveTransaction(conn->sd,recvbuffer,NULL) == -1)
   {
   cfPS(cf_error,CF_INTERPT,"recv",pp,attr,"Failed send");
   CfOut(cf_verbose,"","No answer from host, assuming checksum ok to avoid remote copy for now...\n");
   return false;
   }

if (strcmp(CFD_TRUE,recvbuffer) == 0)
   {
   Debug("MD5 mismatch: (reply - %s)\n",recvbuffer);
   return true; /* mismatch */
   }
else
   {
   Debug("MD5 matched ok: (reply - %s)\n",recvbuffer);
   return false;
   }
 
/* Not reached */
}

/*********************************************************************/

int CopyRegularFileNet(char *source,char *new,off_t size,struct Attributes attr,struct Promise *pp)

{ int dd, buf_size,n_read = 0,toget,towrite,plainlen,more = true;
  int last_write_made_hole = 0, done = false,tosend,cipherlen=0,value;
  char *buf,in[CF_BUFSIZE],out[CF_BUFSIZE],sendbuffer[CF_BUFSIZE],cfchangedstr[265];
  unsigned char iv[] = {1,2,3,4,5,6,7,8};
  long n_read_total = 0;  
  EVP_CIPHER_CTX ctx;
  struct cfagent_connection *conn = pp->conn;

snprintf(cfchangedstr,255,"%s%s",CF_CHANGEDSTR1,CF_CHANGEDSTR2);
  
EVP_CIPHER_CTX_init(&ctx);  

if ((strlen(new) > CF_BUFSIZE-20))
   {
   CfOut(cf_error,"","Filename too long");
   return false;
   }
 
unlink(new);  /* To avoid link attacks */ 
  
if ((dd = open(new,O_WRONLY|O_CREAT|O_TRUNC|O_EXCL|O_BINARY, 0600)) == -1)
   {
   CfOut(cf_error,"open","NetCopy to %s:%s security - failed attempt to exploit a race? (Not copied)\n",pp->this_server,new);
   unlink(new);
   return false;
   }

sendbuffer[0] = '\0';

buf_size = ST_BLKSIZE(dstat);

if (buf_size < 2048)
   {
   buf_size = 2048;
   } 
 
if (attr.copy.encrypt)
   {   
   snprintf(in,CF_BUFSIZE-CF_PROTO_OFFSET,"GET dummykey %s",source);
   cipherlen = EncryptString(in,out,conn->session_key,strlen(in)+1);
   snprintf(sendbuffer,CF_BUFSIZE,"SGET %4d %4d",cipherlen,buf_size);
   memcpy(sendbuffer+CF_PROTO_OFFSET,out,cipherlen);
   tosend=cipherlen+CF_PROTO_OFFSET;   
   EVP_DecryptInit(&ctx,EVP_bf_cbc(),conn->session_key,iv);
   }
else
   {
   snprintf(sendbuffer,CF_BUFSIZE,"GET %d %s",buf_size,source);
   tosend=strlen(sendbuffer);
   }

if (SendTransaction(conn->sd,sendbuffer,tosend,CF_DONE) == -1)
   {
   cfPS(cf_error,CF_INTERPT,"",pp,attr,"Couldn't send data");
   close(dd);
   return false;
   }

buf = (char *) malloc(CF_BUFSIZE + sizeof(int)); /* Note CF_BUFSIZE not buf_size !! */
n_read_total = 0;

while (!done)
   {
   cipherlen = 0;

   if ((size - n_read_total)/buf_size > 0)
      {
      toget = towrite = buf_size;
      }
   else if (size != 0)
      {
      towrite = (size - n_read_total);      
      toget = towrite;
      }
   else
      {
      toget = towrite = 0;
      }
   
   if (attr.copy.encrypt)
      {
      if (more)
         {
         if ((cipherlen = ReceiveTransaction(conn->sd,buf,&more)) == -1)
            {
            return false;
            }
         }
      else
         {
         break;  /* Already written last encrypted buffer */
         }
      }
   else
      {
      if ((n_read = RecvSocketStream(conn->sd,buf,toget,0)) == -1)
         {
         if (errno == EINTR) 
            {
            continue;
            }
         
         cfPS(cf_error,CF_INTERPT,"recv",pp,attr,"Error in client-server stream");
         close(dd);
         free(buf);
         return false;
         }
      }
   
   
   /* If the first thing we get is an error message, break. */
   
   if (n_read_total == 0 && strncmp(buf,CF_FAILEDSTR,strlen(CF_FAILEDSTR)) == 0)
      {
      if (attr.copy.encrypt)
         {
         RecvSocketStream(conn->sd,buf,buf_size-n_read,0); /* flush rest of transaction */
         }
      
      cfPS(cf_inform,CF_INTERPT,"",pp,attr,"Network access to %s:%s denied\n",pp->this_server,source);
      close(dd);
      free(buf);
      return false;      
      }
   
   if (strncmp(buf,cfchangedstr,strlen(cfchangedstr)) == 0)
      {
      RecvSocketStream(conn->sd,buf,buf_size-n_read,0); /* flush rest of transaction */
      cfPS(cf_inform,CF_INTERPT,"",pp,attr,"Source %s:%s changed while copying\n",pp->this_server,source);
      close(dd);
      free(buf);
      return false;      
      }

   value = -1;

   /* Check for mismatch between encryption here and on server - can lead to misunderstanding*/
   
   sscanf(buf,"t %d",&value);
   
   if ((value > 0) && strncmp(buf+CF_INBAND_OFFSET,"BAD: ",5) == 0)
      {
      CfOut(cf_inform,"","Network access to cleartext %s:%s denied\n",pp->this_server,source);      
      close(dd);
      free(buf);
      return false;
      }
   
   if (attr.copy.encrypt)
      {
      if (!EVP_DecryptUpdate(&ctx,(unsigned char *)sendbuffer,&plainlen,(unsigned char*)buf,cipherlen))
         {
         Debug("Decryption failed\n");
         return false;
         }
      
      memcpy(buf,sendbuffer,plainlen);
      n_read = towrite = plainlen;
      }

   if (attr.copy.encrypt)
      {
      if (n_read == 0)
         {
         break;
         }
      
      if (n_read == size)
         {
         if (n_read_total == 0 && strncmp(buf,CF_FAILEDSTR,size) == 0)
            {
            cfPS(cf_inform,CF_INTERPT,"",pp,attr,"Network access to %s:%s denied\n",pp->this_server,source);
            close(dd);
            free(buf);
            return false;      
            }
         }
      }
   
   n_read_total += towrite; /* n_read; */
   
   if (!attr.copy.encrypt)
      {
      if (n_read_total >= (long)size)  /* Handle EOF without closing socket */
         {
         done = true;
         }
      }
   
   if (!FSWrite(new,dd,buf,towrite,&last_write_made_hole,n_read,attr,pp))
      {
      cfPS(cf_error,CF_FAIL,"",pp,attr,"Local disk write failed copying %s:%s to %s\n",pp->this_server,source,new);
      free(buf);
      unlink(new);
      close(dd);
      FlushFileStream(conn->sd,size - n_read_total);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return false;
      }
   }

if (attr.copy.encrypt) /* final crypto cleanup */
   {
   if (!EVP_DecryptFinal(&ctx,buf,&plainlen))
      {
      Debug("Final decrypt failed\n");
      return false;
      }

   if (!FSWrite(new,dd,buf,plainlen,&last_write_made_hole,n_read,attr,pp))
      {
      cfPS(cf_error,CF_FAIL,"",pp,attr,"Local disk write failed copying %s:%s to %s\n",pp->this_server,source,new);
      free(buf);
      unlink(new);
      close(dd);
      FlushFileStream(conn->sd,size - n_read_total);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return false;
      }
   }
 
  /* If the file ends with a `hole', something needs to be written at
     the end.  Otherwise the kernel would truncate the file at the end
     of the last write operation. Write a null character and truncate
     it again.  */

if (last_write_made_hole)   
   {
   if (cf_full_write (dd,"",1) < 0 || ftruncate (dd,n_read_total) < 0)
      {
      cfPS(cf_error,CF_FAIL,"",pp,attr,"cf_full_write or ftruncate error in CopyReg, source %s\n",source);
      free(buf);
      unlink(new);
      close(dd);
      FlushFileStream(conn->sd,size - n_read_total);
      EVP_CIPHER_CTX_cleanup(&ctx);
      return false;
      }
   }
 
Debug("End of CopyNetReg\n");
close(dd);
free(buf);
EVP_CIPHER_CTX_cleanup(&ctx);
return true;
}

/*********************************************************************/
/* Level 2                                                           */
/*********************************************************************/

int ServerConnect(struct cfagent_connection *conn,char *host,struct Attributes attr, struct Promise *pp) 

{ int err;
  short shortport;
  char strport[CF_MAXVARSIZE];

if (attr.copy.portnumber == (short)CF_NOINT)
   {
   shortport = SHORT_CFENGINEPORT;
   strncpy(strport,STR_CFENGINEPORT,CF_MAXVARSIZE);
   }
else
   {
   shortport = htons(attr.copy.portnumber);
   snprintf(strport,CF_MAXVARSIZE,"%u",(int)attr.copy.portnumber);
   }
   
CfOut(cf_verbose,"","Set cfengine port number to %s = %u\n",strport,(int)ntohs(shortport));

#if defined(HAVE_GETADDRINFO)
 
if (!attr.copy.force_ipv4)
   {
   struct addrinfo query, *response, *ap;
   struct addrinfo query2, *response2, *ap2;
   int err,connected = false;

   memset(&query,0,sizeof(struct addrinfo));   
   query.ai_family = AF_UNSPEC;
   query.ai_socktype = SOCK_STREAM;

   if ((err = getaddrinfo(host,strport,&query,&response)) != 0)
      {
      cfPS(cf_inform,CF_INTERPT,"",pp,attr,"Unable to find host or service: (%s/%s) %s",host,strport,gai_strerror(err));
      return false;
      }
   
   for (ap = response; ap != NULL; ap = ap->ai_next)
      {
      CfOut(cf_verbose,"","Connect to %s = %s on port %s\n",host,sockaddr_ntop(ap->ai_addr),strport);
      
      if ((conn->sd = socket(ap->ai_family,ap->ai_socktype,ap->ai_protocol)) == -1)
         {
         CfOut(cf_inform,"socket","Couldn't open a socket");
         continue;
         }
      
      if (BINDINTERFACE[0] != '\0')
         {
         memset(&query2,0,sizeof(struct addrinfo));   
         
         query.ai_family = AF_UNSPEC;
         query.ai_socktype = SOCK_STREAM;
         
         if ((err = getaddrinfo(BINDINTERFACE,NULL,&query2,&response2)) != 0)
            {
            cfPS(cf_error,CF_FAIL,"",pp,attr,"Unable to lookup hostname or cfengine service: %s",gai_strerror(err));
            return false;
            }
         
         for (ap2 = response2; ap2 != NULL; ap2 = ap2->ai_next)
            {
            if (bind(conn->sd, ap2->ai_addr, ap2->ai_addrlen) == 0)
               {
               freeaddrinfo(response2);
               response2 = NULL;
               break;
               }
            }
         
         if (response2)
            {
            freeaddrinfo(response2);
            }
         }
      
      signal(SIGALRM,(void *)TimeOut);
      alarm(CF_TIMEOUT);
      
      if (connect(conn->sd,ap->ai_addr,ap->ai_addrlen) >= 0)
         {
         connected = true;
         alarm(0);
         signal(SIGALRM,SIG_DFL);
         break;
         }

      alarm(0);
      signal(SIGALRM,SIG_DFL);
      }
   
   if (connected)
      {
      conn->family = ap->ai_family;
      snprintf(conn->remoteip,CF_MAX_IP_LEN-1,"%s",sockaddr_ntop(ap->ai_addr));
      }
   else
      {
      close(conn->sd);
      conn->sd = CF_NOT_CONNECTED;
      }
   
   if (response != NULL)
      {
      freeaddrinfo(response);
      }
   
   if (!connected)
      {
      cfPS(cf_verbose,CF_FAIL,"",pp,attr,"Unable to connect to server %s",host);
      return false;
      }
   }
 
 else
     
#endif /* ---------------------- only have ipv4 ---------------------------------*/ 

   {
   struct hostent *hp;
   struct sockaddr_in cin;
   memset(&cin,0,sizeof(cin));
   
   if ((hp = gethostbyname(host)) == NULL)
      {
      CfOut(cf_error,"gethostbyname","Unable to look up IP address of %s",host);
      return false;
      }

   cin.sin_port = shortport;
   cin.sin_addr.s_addr = ((struct in_addr *)(hp->h_addr))->s_addr;
   cin.sin_family = AF_INET; 
   
   CfOut(cf_verbose,"","Connect to %s = %s, port = (%u=%s)\n",host,inet_ntoa(cin.sin_addr),(int)ntohs(shortport),strport);
    
   if ((conn->sd = socket(AF_INET,SOCK_STREAM,0)) == -1)
      {
      cfPS(cf_error,CF_INTERPT,"socket",pp,attr,"Couldn't open a socket");
      return false;
      }

   if (BINDINTERFACE[0] != '\0')
      {
      CfOut(cf_verbose,"","Cannot bind interface with this OS.\n");
      /* Could fix this - any point? */
      }
   
   conn->family = AF_INET;
   snprintf(conn->remoteip,CF_MAX_IP_LEN-1,"%s",inet_ntoa(cin.sin_addr));
    
   signal(SIGALRM,(void *)TimeOut);
   alarm(CF_TIMEOUT);
    
   if (err=connect(conn->sd,(void *)&cin,sizeof(cin)) == -1)
      {
      cfPS(cf_verbose,CF_INTERPT,"connect",pp,attr,"Unable to connect to server %s (old ipv4)",host);
      return false;
      }
   
   alarm(0);
   signal(SIGALRM,SIG_DFL);
   }

LastSaw(host,cf_connect);
return true; 
}


/*********************************************************************/

int ServerOffline(char *server)
    
{ struct Rlist *rp;
  struct cfagent_connection *conn;
  struct ServerItem *svp;
  char ipname[CF_MAXVARSIZE];

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

strncpy(ipname,Hostname2IPString(server),CF_MAXVARSIZE-1);
  
#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif

for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   svp = (struct ServerItem *)rp->item;

   if ((strcmp(ipname,svp->server) == 0) && (svp->conn == NULL))
      {
      return true;
      }
   }

return false;
}

/*********************************************************************/

struct cfagent_connection *ServerConnectionReady(char *server)

{ struct Rlist *rp;
  struct cfagent_connection *conn;
  struct ServerItem *svp;
  char ipname[CF_MAXVARSIZE];

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

strncpy(ipname,Hostname2IPString(server),CF_MAXVARSIZE-1);

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif
  
for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   svp = (struct ServerItem *)rp->item;

   if (svp->busy)
      {
      CfOut(cf_verbose,"","Existing connection seems to be busy...\n",ipname);
      return NULL;
      }
   
   if ((strcmp(ipname,svp->server) == 0) && svp->conn && svp->conn->sd > 0)
      {
      CfOut(cf_verbose,"","Connection to %s is already open and ready...\n",ipname);
      return svp->conn;
      }
   }

CfOut(cf_verbose,"","No existing connection to %s is established...\n",ipname);
return NULL;
}

/*********************************************************************/

void ServerNotBusy(struct cfagent_connection *conn)

{ struct Rlist *rp;
  struct ServerItem *svp;
 
for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   svp = (struct ServerItem *)rp->item;

   if (svp->conn == conn)
      {
      svp->busy = false;
      break;
      }
   }

CfOut(cf_verbose,"","Existing connection just became free...\n");
}

/*********************************************************************/

void MarkServerOffline(char *server)

{ struct Rlist *rp;
  struct cfagent_connection *conn;
  struct ServerItem *svp;
  char ipname[CF_MAXVARSIZE];

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

strncpy(ipname,Hostname2IPString(server),CF_MAXVARSIZE-1);

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif
  
for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   conn = (struct cfagent_connection *)rp->item;

   if (strcmp(ipname,conn->localip) == 0)
      {
      conn->sd = CF_COULD_NOT_CONNECT;
      return;
      }
   }

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

rp = PrependRlist(&SERVERLIST,"nothing",CF_SCALAR);
free(rp->item);
svp = (struct ServerItem *)malloc((sizeof(struct ServerItem)));
rp->item = svp;
svp->server = strdup(ipname);
svp->conn = NewAgentConn();
svp->conn->sd = CF_COULD_NOT_CONNECT;

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif
}

/*********************************************************************/

void CacheServerConnection(struct cfagent_connection *conn,char *server)

{ struct Rlist *rp;
  struct ServerItem *svp;
  char ipname[CF_MAXVARSIZE];

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

strncpy(ipname,Hostname2IPString(server),CF_MAXVARSIZE-1);

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif
  
for (rp = SERVERLIST; rp != NULL; rp=rp->next)
   {
   conn = (struct cfagent_connection *)rp->item;

   if (strcmp(ipname,conn->localip) == 0)
      {
      conn->sd = CF_COULD_NOT_CONNECT;
      return;
      }
   }

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_lock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"lock","pthread_mutex_lock failed");
   exit(1);
   }
#endif

rp = PrependRlist(&SERVERLIST,"nothing",CF_SCALAR);
free(rp->item);
svp = (struct ServerItem *)malloc((sizeof(struct ServerItem)));
rp->item = svp;
svp->server = strdup(ipname);
svp->conn = conn;

#ifdef HAVE_PTHREAD_H  
if (pthread_mutex_unlock(&MUTEX_GETADDR) != 0)
   {
   CfOut(cf_error,"unlock","pthread_mutex_unlock failed");
   exit(1);
   }
#endif
}

/*********************************************************************/

int CacheStat(char *file,struct stat *statbuf,char *stattype,struct Attributes attr,struct Promise *pp)

{ struct cfstat *sp;

Debug("CacheStat(%s,%d)\n",file,pp);

for (sp = pp->cache; sp != NULL; sp=sp->next)
   {
   if ((strcmp(pp->this_server,sp->cf_server) == 0) && (strcmp(file,sp->cf_filename) == 0))
      {
      if (sp->cf_failed)  /* cached failure from cfopendir */
         {
         errno = EPERM;
         Debug("Cached failure to stat\n");
         return -1;
         }
      
      if ((strcmp(stattype,"link") == 0) && (sp->cf_lmode != 0))
         {
         statbuf->st_mode  = sp->cf_lmode;
         }
      else
         {
         statbuf->st_mode  = sp->cf_mode;
         }
      
      statbuf->st_uid   = sp->cf_uid;
      statbuf->st_gid   = sp->cf_gid;
      statbuf->st_size  = sp->cf_size;
      statbuf->st_atime = sp->cf_atime;
      statbuf->st_mtime = sp->cf_mtime;
      statbuf->st_ctime = sp->cf_ctime;
      statbuf->st_ino   = sp->cf_ino;
      statbuf->st_nlink = sp->cf_nlink;      
      
      Debug("Found in cache\n");
      return true;
      }
   }
 
Debug("Did not find in cache\n"); 
return false;
}


/*********************************************************************/

void FlushFileStream(int sd,int toget)

{ int i;
  char buffer[2]; 

CfOut(cf_inform,"","Flushing rest of file...%d bytes\n",toget);
 
for (i = 0; i < toget; i++)
   {
   recv(sd,buffer,1,0);  /* flush to end of current file */
   }
}


