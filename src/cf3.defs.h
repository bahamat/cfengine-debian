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
/* File: cf3.defs.h                                                          */
/*                                                                           */
/*****************************************************************************/

#ifndef CFENGINE_CF3_DEFS_H
#define CFENGINE_CF3_DEFS_H

/* These files are hard links to the cfengine 2 sources */

#include "cf.defs.h"
#include "cf.extern.h"

#undef VERSION
#undef Verbose

#include "conf.h"

#ifndef NGROUPS
# define NGROUPS 20
#endif

/*************************************************************************/
/* Fundamental (meta) types                                              */
/*************************************************************************/

#define CF3COPYRIGHT "Copyright (C) CFEngine AS 2008,2010-"

#define CF_SCALAR 's'
#define CF_LIST   'l'
#define CF_FNCALL 'f'
#define CF_STACK  'k'

#define CF_NOPROMISEE 'X'
#define CF_UNDEFINED -1
#define CF_NODOUBLE -123.45
#define CF_NOINT    -678L
#define CF_ANYUSER  (uid_t)-1
#define CF_ANYGROUP (gid_t)-1
#define CF_UNDEFINED_ITEM (void *)0x1234
#define CF_VARARGS 99
#define CF_UNKNOWN_IP "location unknown"

#define CF_INBODY   1
#define CF_INBUNDLE 2

#define CF_MAX_NESTING 10
#define CF_MAX_REPLACE 20
#define CF_DONEPASSES  4

#define CF_TIME_SIZE 32
#define CF_FIPS_SIZE 32

#define CFPULSETIME 60

/*************************************************************************/
/** Design criteria                                                      */
/*************************************************************************/

#define CF_DUNBAR_INTIMATE 6
#define CF_DUNBAR_WORK 30
#define CF_DUNBAR_KNOW 120

/*************************************************************************/
/* Parsing and syntax tree structures                                    */
/*************************************************************************/

#define CF_DEFINECLASSES "classes"
#define CF_TRANSACTION   "action"

#define CF3_MODULES 15 /* This value needs to be incremented when adding modules */

/*************************************************************************/

struct PromiseParser
   {
   char *block;                     /* body/bundle  */
   char blocktype[CF_MAXVARSIZE];
   char blockid[CF_MAXVARSIZE];

   char filename[CF_MAXVARSIZE];
   int line_pos;
   int line_no;

   int arg_nesting;
   int list_nesting;
      
   char lval[CF_MAXVARSIZE];
   void *rval;
   char rtype;
   int isbody;

   char *promiser;
   void *promisee;

   char currentid[CF_MAXVARSIZE];
   char currenttype[CF_MAXVARSIZE];
   char *currentstring;
   char *currentclasses;

   struct Bundle *currentbundle;
   struct Body *currentbody;
   struct Promise *currentpromise;
   struct SubType *currentstype;
   struct Rlist *useargs;
      
   struct RList *currentRlist;

   char *currentfnid[CF_MAX_NESTING];
   struct Rlist *giveargs[CF_MAX_NESTING];
   struct FnCall *currentfncall[CF_MAX_NESTING];
   };

/*************************************************************************/
/* Abstract datatypes                                                    */
/*************************************************************************/

enum cfdatatype
   {
   cf_str,
   cf_int,
   cf_real,
   cf_slist,
   cf_ilist,
   cf_rlist,
   cf_opts,
   cf_olist,
   cf_body,
   cf_bundle,
   cf_class,
   cf_clist,
   cf_irange,
   cf_rrange,
   cf_counter,
   cf_notype
   };

enum cfx_formatindex
   {
   cfb,
   cfe,
   };

enum cfx_format
   {
   cfx_head,
   cfx_bundle,
   cfx_block,
   cfx_blockheader,
   cfx_blockid,
   cfx_blocktype,
   cfx_args,
   cfx_promise,
   cfx_class,
   cfx_subtype,
   cfx_object,
   cfx_lval,
   cfx_rval,
   cfx_qstring,
   cfx_rlist,
   cfx_function,
   cfx_line,
   };

/*************************************************************************/

#define CF_COMMONC  "common"
#define CF_AGENTC   "agent"
#define CF_SERVERC  "server"
#define CF_MONITORC "monitor"
#define CF_EXECC    "executor"
#define CF_KNOWC    "knowledge"
#define CF_RUNC     "runagent"
#define CF_REPORTC  "reporter"
#define CF_KEYGEN   "keygenerator"
#define CF_HUBC     "hub"

enum cfagenttype
   {
   cf_common,
   cf_agent,
   cf_server,
   cf_monitor,
   cf_executor,
   cf_runagent,
   cf_know,
   cf_report,
   cf_keygen,
   cf_hub,
   cf_noagent
   };

/*************************************************************************/

enum cfgcontrol
   {
   cfg_bundlesequence,
   cfg_goalcategories,
   cfg_goalpatterns,
   cfg_ignore_missing_bundles,
   cfg_ignore_missing_inputs,
   cfg_inputs,
   cfg_version,
   cfg_lastseenexpireafter,
   cfg_output_prefix,
   cfg_domain,
   cfg_require_comments,
   cfg_licenses,
   cfg_site_classes,
   cfg_syslog_host,
   cfg_syslog_port,
   cfg_fips_mode,
   cfg_noagent
   };
    
/*************************************************************************/

enum cfacontrol
   {
   cfa_abortclasses,
   cfa_abortbundleclasses,
   cfa_addclasses,
   cfa_agentaccess,
   cfa_agentfacility,
   cfa_alwaysvalidate,
   cfa_auditing,
   cfa_binarypaddingchar,
   cfa_bindtointerface,
   cfa_hashupdates,
   cfa_childlibpath,
   cfa_checksum_alert_time,
   cfa_defaultcopytype,
   cfa_dryrun,
   cfa_editbinaryfilesize,
   cfa_editfilesize,
   cfa_environment,
   cfa_exclamation,
   cfa_expireafter,
   cfa_fsinglecopy,
   cfa_fautodefine,
   cfa_hostnamekeys,
   cfa_ifelapsed,
   cfa_inform,
   cfa_intermittency,
   cfa_max_children,
   cfa_maxconnections,
   cfa_mountfilesystems,
   cfa_nonalphanumfiles,
   cfa_repchar,
   cfa_refresh_processes,
   cfa_repository,
   cfa_secureinput,
   cfa_sensiblecount,
   cfa_sensiblesize,
   cfa_skipidentify,
   cfa_suspiciousnames,
   cfa_syslog,
   cfa_track_value,
   cfa_timezone,
   cfa_timeout,
   cfa_verbose,
   cfa_notype,
   };

/*************************************************************************/

enum cfexcontrol
   {
   cfex_splaytime,
   cfex_mailfrom,
   cfex_mailto,
   cfex_smtpserver,
   cfex_mailmaxlines,
   cfex_schedule,
   cfex_executorfacility,
   cfex_execcommand,
   cfex_notype,
   };

/*************************************************************************/

enum cfmcontrol
   {
   cfm_forgetrate,
   cfm_monitorfacility,
   cfm_histograms,
   cfm_tcpdump,
   cfm_notype,
   };

/*************************************************************************/

enum cfrcontrol
   {
   cfr_hosts,
   cfr_portnumber,
   cfr_force_ipv4,
   cfr_trustkey,
   cfr_encrypt,
   cfr_background,
   cfr_maxchild,
   cfr_output_to_file,
   cfr_output_directory,
   cfr_timeout,
   cfr_notype
   };

/*************************************************************************/

enum cfscontrol
   {
   cfs_allowallconnects,
   cfs_allowconnects,
   cfs_allowusers,
   cfs_auditing,
   cfs_bindtointerface,
   cfs_cfruncommand,
   cfs_denybadclocks,
   cfs_denyconnects,
   cfs_dynamicaddresses,
   cfs_hostnamekeys,
   cfs_keyttl,
   cfs_logallconnections,
   cfs_logencryptedtransfers,
   cfs_maxconnections,
   cfs_portnumber,
   cfs_serverfacility,
   cfs_skipverify,
   cfs_trustkeysfrom,
   cfs_notype,
   };

/*************************************************************************/

enum cfkcontrol
   {
   cfk_builddir,
   cfk_docroot,
   cfk_genman,
   cfk_graph_dir,
   cfk_graph_output,
   cfk_htmlbanner,
   cfk_htmlfooter,
   cfk_tm_prefix,
   cfk_mandir,
   cfk_query_engine,   
   cfk_query_output,
   cfk_sql_type,
   cfk_sql_database,
   cfk_sql_owner,
   cfk_sql_passwd,
   cfk_sql_server,
   cfk_sql_connect_db,
   cfk_stylesheet,
   cfk_views,
   cfk_view_projection,
   cfk_notype
   };

/*************************************************************************/

enum cfrecontrol
   {
   cfre_aggregation_point,
   cfre_autoscale,
   cfre_builddir,
   cfre_csv,
   cfre_errorbars,
   cfre_htmlbanner,
   cfre_html_embed,
   cfre_htmlfooter,
   cfre_query_engine,
   cfre_reports,
   cfre_report_output,
   cfre_stylesheet,
   cfre_timestamps,
   cfre_notype
   };

/*************************************************************************/

enum cfhcontrol
   {
   cfh_export_zenoss,
   cfh_federation,
   cfh_exclude_hosts,
   cfh_schedule,
   cfh_port,
   cfh_notype
   };

/*************************************************************************/

enum cfsbundle
   {
   cfs_access,
   cfs_nobtype
   };

enum cfsrole
   {
   cfs_authorize,
   cfs_nortype
   };

enum cfspromises
   {
   cfs_admit,
   cfs_deny,
   cfs_maproot,
   cfs_encrypted,
   cfs_noptype
   };

enum cfreport
   {
   cf_inform,
   cf_verbose,
   cf_error,
   cf_log,
   cf_reporting,
   cf_cmdout,
   cf_noreport
   };

enum cfeditorder
   {
   cfe_before,
   cfe_after
   };

/*************************************************************************/
/* Syntax module range/pattern constants for type validation             */
/*************************************************************************/

#define CF_BUNDLE  (void*)1234           /* any non-null value, not used */

#define CF_HIGHINIT 99999L
#define CF_LOWINIT -999999L

#define CF_SIGNALRANGE "hup,int,trap,kill,pipe,cont,abrt,stop,quit,term,child,usr1,usr2,bus,segv"
#define CF_BOOL      "true,false,yes,no,on,off"
#define CF_LINKRANGE "symlink,hardlink,relative,absolute"
#define CF_TIMERANGE "0,2147483647"
#define CF_VALRANGE  "0,99999999999"
#define CF_INTRANGE  "-99999999999,9999999999"
#define CF_INTLISTRANGE  "[-0-9_$(){}\\[\\].]+"
#define CF_REALRANGE "-9.99999E100,9.99999E100"
#define CF_CHARRANGE "^.$"
#define CF_NULL_VALUE "cf_null"

#define CF_MODERANGE   "[0-7augorwxst,+-]+"
#define CF_BSDFLAGRANGE "[+-]*[(arch|archived|nodump|opaque|sappnd|sappend|schg|schange|simmutable|sunlnk|sunlink|uappnd|uappend|uchg|uchange|uimmutable|uunlnk|uunlink)]+"
#define CF_CLASSRANGE  "[a-zA-Z0-9_!&@@$|.()\\[\\]{}]+"
#define CF_IDRANGE     "[a-zA-Z0-9_$(){}\\[\\].]+"
#define CF_USERRANGE   "[a-zA-Z0-9_$.-]+"
#define CF_IPRANGE     "[a-zA-Z0-9_$(){}.:-]+"
#define CF_FNCALLRANGE "[a-zA-Z0-9_(){}.$@]+"
#define CF_NAKEDLRANGE "@[(][a-zA-Z0-9]+[)]"
#define CF_ANYSTRING   ".*"

#ifndef MINGW
#define CF_ABSPATHRANGE   "\042?(/.*)"
#else
// can start with e.g. c:\... or "c:\...  |  unix (for Cygwin-style paths)
#define CF_ABSPATHRANGE   "\042?(([a-zA-Z]:\\\\.*)|(/.*))"
#endif

/* Any non-empty string can be an absolute path under Unix */
#define CF_PATHRANGE ".+"

#define CF_LOGRANGE    "stdout|udp_syslog|(\042?[a-zA-Z]:\\\\.*)|(/.*)"

#define CF_FACILITY "LOG_USER,LOG_DAEMON,LOG_LOCAL0,LOG_LOCAL1,LOG_LOCAL2,LOG_LOCAL3,LOG_LOCAL4,LOG_LOCAL5,LOG_LOCAL6,LOG_LOCAL7"

// Put this here now for caching efficiency

#define SOFTWARE_PACKAGES_CACHE "software_packages.csv"

/***************************************************************************/
/* Knowledge relationships                                                 */
/***************************************************************************/

enum storytype
   {
   cfi_cause,
   cfi_connect,
   cfi_part,
   cfi_access,
   cfi_none
   };

#define KM_AFFECTS_CERT_F "affects"
#define KM_AFFECTS_CERT_B "is affected by"
#define KM_CAUSE_CERT_F "causes"
#define KM_CAUSE_CERT_B "is caused by"
#define KM_PARTOF_CERT_F "is/are a part of"
#define KM_PARTOF_CERT_B "has/have a part"
#define KM_DETERMINES_CERT_F "determine(s)"
#define KM_DETERMINES_CERT_B "is/are determined by"
#define KM_CONTRIBUTES_CERT_F "contibutes to"
#define KM_CONTRIBUTES_CERT_B "is contibuted to by"
#define KM_USES_CERT_F "use(s)"
#define KM_USES_CERT_B "is/are used by"
#define KM_PROVIDES_CERT_F "provide(s)"
#define KM_PROVIDES_CERT_B "is/are provided by"
#define KM_BELONGS_CERT_F "belongs to"
#define KM_BELONGS_CERT_B "owns"
#define KM_CONNECTS_CERT_F "connects to"
#define KM_CONNECTS_CERT_B "connects to"
#define KM_NEEDS_CERT_F "need(s)"
#define KM_NEEDS_CERT_B "is needed by"
#define KM_EQUIV_CERT_F "is equivalent to"
#define KM_EQUIV_CERT_B "is equivalent to"
#define KM_SHIELD_CERT_F "denies access from"
#define KM_SHIELD_CERT_B "is not allowed access to"
#define KM_ACCESS_CERT_F "grants access to"
#define KM_ACCESS_CERT_B "is allowed to access"
#define KM_MONITOR_CERT_F "monitor(s)"
#define KM_MONITOR_CERT_B "is/are monitored by"
#define KM_LOCATED_CERT_F "is located in"
#define KM_LOCATED_CERT_B "situates"
#define KM_REPAIR_CERT_F "repairs"
#define KM_REPAIR_CERT_B "is repaired by"

#define KM_CAUSE_POSS_F "can cause"
#define KM_CAUSE_POSS_B "can be caused by"
#define KM_PARTOF_POSS_F "can be a part of"
#define KM_PARTOF_POSS_B "can have a part"
#define KM_DETERMINES_POSS_F "can determine"
#define KM_DETERMINES_POSS_B "can be determined by"
#define KM_CONTRIBUTES_POSS_F "can contibute to"
#define KM_CONTRIBUTES_POSS_B "can be contibuted to by"
#define KM_USES_POSS_F "can use"
#define KM_USES_POSS_B "can be used by"
#define KM_PROVIDES_POSS_F "can provide"
#define KM_PROVIDES_POSS_B "can be provided by"
#define KM_BELONGS_POSS_F "can belong to"
#define KM_BELONGS_POSS_B "can own"
#define KM_AFFECTS_POSS_F "can affect"
#define KM_AFFECTS_POSS_B "can be affected by"
#define KM_CONNECTS_POSS_F "can connect to"
#define KM_CONNECTS_POSS_B "can connect to"
#define KM_NEEDS_POSS_F "can need"
#define KM_NEEDS_POSS_B "can be needed by"
#define KM_EQUIV_POSS_F "can be equivalent to"
#define KM_EQUIV_POSS_B "can be equivalent to"
#define KM_MONITOR_POSS_F "can monitor"
#define KM_MONITOR_POSS_B "can be monitored by"
#define KM_ACCESS_POSS_F "can access to"
#define KM_ACCESS_POSS_B "can be allowed to access"
#define KM_LOCATED_POSS_F "can be located in"
#define KM_LOCATED_POSS_B "can situate"
#define KM_REPAIR_POSS_F "can repair"
#define KM_REPAIR_POSS_B "can be repaired by"

#define KM_CAUSE_UNCERT_F "might cause"
#define KM_CAUSE_UNCERT_B "might be caused by"
#define KM_PARTOF_UNCERT_F "might be a part of"
#define KM_PARTOF_UNCERT_B "might have a part"
#define KM_DETERMINES_UNCERT_F "might determine"
#define KM_DETERMINES_UNCERT_B "might be determined by"
#define KM_CONTRIBUTES_UNCERT_F "might contibute to"
#define KM_CONTRIBUTES_UNCERT_B "might be contibuted to by"
#define KM_USES_UNCERT_F "might use"
#define KM_USES_UNCERT_B "might be used by"
#define KM_PROVIDES_UNCERT_F "might provide"
#define KM_PROVIDES_UNCERT_B "might be provided by"
#define KM_BELONGS_UNCERT_F "might belong to"
#define KM_BELONGS_UNCERT_B "might own"
#define KM_AFFECTS_UNCERT_F "might affect"
#define KM_AFFECTS_UNCERT_B "might be affected by"
#define KM_CONNECTS_UNCERT_F "might connect to"
#define KM_CONNECTS_UNCERT_B "might connect to"
#define KM_NEEDS_UNCERT_F "might need"
#define KM_NEEDS_UNCERT_B "might be needed by"
#define KM_EQUIV_UNCERT_F "might be equivalent to"
#define KM_EQUIV_UNCERT_B "might be equivalent to"
#define KM_SHIELD_UNCERT_F "might deny access from"
#define KM_SHIELD_UNCERT_B "might not be allowed access to"
#define KM_MONITOR_UNCERT_F "might monitor"
#define KM_MONITOR_UNCERT_B "might be monitored by"
#define KM_ACCESS_UNCERT_F "might grant access to"
#define KM_ACCESS_UNCERT_B "might be allowed to access"
#define KM_LOCATED_UNCERT_F "might be located in"
#define KM_LOCATED_UNCERT_B "might situate"
#define KM_REPAIR_UNCERT_F "might repair"
#define KM_REPAIR_UNCERT_B "might be repaired by"

#define KM_GENERALIZES_F "is a generalization of"
#define KM_GENERALIZES_B "is a special case of"
#define KM_SYNONYM "is a synonym for"

enum knowledgecertainty
   {
   cfk_certain,
   cfk_uncertain,
   cfk_possible
   };

/*************************************************************************/

struct BodySyntax
   {
   char *lval;
   enum cfdatatype dtype;
   void *range;               /* either char or struct BodySyntax **/
   char *description;
   };

struct BodyDefault
   {
   char *lval;
   char *rval;
   };

/*************************************************************************/

struct SubTypeSyntax
   {
   char *btype;
   char *subtype;
   struct BodySyntax *bs;
   };

/*************************************************************************/

struct FnCall;

typedef struct FnCallType
   {
   char *name;
   enum cfdatatype dtype;
   int numargs;
   struct FnCallArg *args;
   struct Rval (*impl)(struct FnCall *, struct Rlist *);
   char *description;
   } FnCallType;

struct FnCallArg
   {
   char *pattern;
   enum cfdatatype dtype;
   char *description;
   };

/*************************************************************************/

#define UNKNOWN_FUNCTION -1

/*************************************************************************/

struct Bundle
   {
   char *type;
   char *name;
   struct Rlist *args;
   struct SubType *subtypes;
   struct Bundle *next;
   };

/*************************************************************************/

struct Body
   {
   char *type;
   char *name;
   struct Rlist *args;
   struct Constraint *conlist;
   struct Body *next;
   };

/*************************************************************************/

struct SubType
   {
   char *name;
   struct Promise *promiselist;
   struct SubType *next;
   };

/*************************************************************************/

struct edit_context
   {
   char *filename;
   struct Item *file_start;
   struct Item *file_classes;
   int num_edits;
   int empty_first;
   };

/*************************************************************************/

struct Promise
   {
   char *classes;
   char *ref;                   /* comment */
   char ref_alloc;
   char *promiser;
   void *promisee;              /* Can be a general rval */
   char  petype;                /* rtype of promisee - list or scalar recipient? */
   int   lineno;
   char *bundle;
   struct Audit *audit;
   struct Constraint *conlist;
   struct Promise *next;
      
    /* Runtime bus for private flags and work space */

   char  *agentsubtype;         /* cache the promise subtype */
   char  *bundletype;           /* cache the agent type */
   int    done;                 /* this needs to be preserved across runs */
   int   *donep;                /* used by locks to mark as done */
   int    makeholes;
   char  *this_server;
   struct cfstat *cache;      
   struct cfagent_connection *conn;
   struct CompressedArray *inode_cache;
   struct edit_context *edcontext;
   dev_t rootdevice;                          /* for caching during work*/
   };

/*************************************************************************/

struct PromiseIdent
   {
   char *handle;
   char *filename;
   char *classes;
   int lineno;
   struct PromiseIdent *next;
   };

/*************************************************************************/

struct Constraint
   {
   char *lval;
   void *rval;    /* should point to either string, Rlist or FnCall */
   char type;     /* scalar, list, or function */
   char *classes; /* only used within bodies */
   int lineno;
   int isbody;
   struct Audit *audit;
   struct Constraint *next;
   };

/*************************************************************************/
/* Rvalues and lists - basic workhorse structure                         */
/*************************************************************************/

/*
  In an OO language one would probably think of Rval as a parent class
  and CF_SCALAR, CF_LIST and CF_FNCALL as children. There is more or
  less a sub-type polymorphism going on in the code around these structures,
  but it is not a proper inheritance relationship as lists could
  contain functions which return lists or scalars etc..

*/

/*************************************************************************/

struct Rval
   {
   void *item;        /* (char *), (struct Rlist *), or (struct FnCall)  */
   char rtype;        /* Points to CF_SCALAR, CF_LIST, CF_FNCALL usually */
   };

/*************************************************************************/

struct Rlist
   {
   void *item;
   char type;
   struct Rlist *state_ptr; /* Points to "current" state/element of sub-list */
   struct Rlist *next;
   };

/*************************************************************************/

struct FnCall
   {
   char *name;
   struct Rlist *args;
   int argc;
   };

/*******************************************************************/
/* Variable processing                                             */
/*******************************************************************/

struct Scope                         /* $(bundlevar) $(scope.name) */
   {
   char *scope;                                 /* Name of scope */
   struct CfAssoc *hashtable[CF_HASHTABLESIZE]; /* Variable heap  */
   struct Scope *next;
   };

/*******************************************************************/

typedef struct CfAssoc        /* variable reference linkage , with metatype*/
   {
   char *lval;
   void *rval;
   char rtype;
   enum cfdatatype dtype;
   } CfAssoc;

/*******************************************************************/

/*
 * Disposable iterator over hash table. Does not require deinitialization.
 */
typedef struct HashIterator
   {
   CfAssoc **hash;
   int bucket;
   } HashIterator;

/*******************************************************************/
/* Return value signalling                                         */
/*******************************************************************/

#define FNCALL_NOP     -1
#define FNCALL_SUCCESS 0
#define FNCALL_FAILURE 1
#define FNCALL_ALERT   2

struct FnCallStatus  /* from builtin functions */
   {
   int status;
   char message[CF_BUFSIZE];
   char fncall_classes[CF_BUFSIZE]; /* set by functions in the form fncall_CLASS */
   };

/*******************************************************************/
/* Return value signalling                                         */
/*******************************************************************/

enum cfinterval
   {
   cfa_hourly,
   cfa_daily,
   cfa_nointerval
   };

enum cfdatetemplate
   {
   cfa_year,
   cfa_month,
   cfa_day,
   cfa_hour,
   cfa_min,
   cfa_sec
   };

enum cfcomparison
   {
   cfa_atime,
   cfa_mtime,
   cfa_ctime,
   cfa_checksum,
   cfa_hash,
   cfa_binary,
   cfa_exists,
   cfa_nocomparison
   };

enum cflinktype
   {
   cfa_symlink,
   cfa_hardlink,
   cfa_relative,
   cfa_absolute,
   cfa_notlinked
   };

enum cfopaction
   {
   cfa_fix,
   cfa_warn,
   };

enum cfbackupoptions
   {
   cfa_backup,
   cfa_nobackup,
   cfa_timestamp,
   cfa_repos_store/* for internal use only */
   };

enum cftidylinks
   {
   cfa_linkdelete,
   cfa_linkkeep
   };

enum cfhashes
   {
   cf_md5,
   cf_sha224,
   cf_sha256,
   cf_sha384,
   cf_sha512,
   cf_sha1,
   cf_sha,
   cf_besthash,
   cf_crypt,
   cf_nohash
   };

enum cfnofile
   {
   cfa_force,
   cfa_delete,
   cfa_skip
   };

enum cflinkchildren
   {
   cfa_override,
   cfa_onlynonexisting
   };

enum cfchanges
   {
   cfa_noreport,
   cfa_contentchange,
   cfa_statschange,
   cfa_allchanges
   };

enum signalnames
   {
   cfa_hup,
   cfa_int,
   cfa_trap,
   cfa_kill,
   cfa_pipe,
   cfa_cont,
   cfa_abrt,
   cfa_stop,
   cfa_quit,
   cfa_term,
   cfa_child,
   cfa_usr1,
   cfa_usr2,
   cfa_bus,
   cfa_segv
   };


enum representations
   {
   cfk_url,
   cfk_web,
   cfk_file,
   cfk_db,
   cfk_literal,
   cfk_image,
   cfk_portal,
   cfk_none
   };

enum package_actions
  {
  cfa_addpack,
  cfa_deletepack,
  cfa_reinstall,
  cfa_update,
  cfa_addupdate,
  cfa_patch,
  cfa_verifypack,
  cfa_pa_none
  };

enum version_cmp
   {
   cfa_eq,
   cfa_neq,
   cfa_gt,
   cfa_lt,
   cfa_ge,
   cfa_le,
   cfa_cmp_none
   };

enum action_policy
  {
  cfa_individual,
  cfa_bulk,
  cfa_no_ppolicy
  };

enum cf_thread_mutex
/* Adding:
 *) Add enum here
 *) Add mutex in cf3globals.c and cf.extern.h
 *) Add enum -> mutex in NameToThreadMutex() */
  {
  cft_system,
  cft_count,
  cft_getaddr,
  cft_lock,
  cft_output,
  cft_dbhandle,
  cft_policy,       // protects structs for refreshing policy files
  cft_db_lastseen,  // lastseen dbs (in cf-serverd)
  cft_no_tpolicy,
  cft_report,
  cft_vscope,           // protects VSCOPE
  cft_server_keyseen,  // protects   SERVER_KEYSEEN
  cft_server_children,
  };

enum cf_status
  {
  cfn_repaired,
  cfn_notkept,
  cfn_kept,
  cfn_nop
  };

/************************************************************************************/

enum cf_acl_method
   {
   cfacl_append,
   cfacl_overwrite,
   cfacl_nomethod
   };

enum cf_acl_type
   {
   cfacl_generic,
   cfacl_posix,
   cfacl_ntfs,
   cfacl_notype
   };
       
enum cf_acl_inherit
   {
   cfacl_nochange,
   cfacl_specify,
   cfacl_parent,
   cfacl_clear,
   cfacl_noinherit,
   };

struct CfACL
   {
   enum cf_acl_method acl_method;
   enum cf_acl_type acl_type;
   enum cf_acl_inherit acl_directory_inherit;
   struct Rlist *acl_entries;
   struct Rlist *acl_inherit_entries;
   };

typedef enum
  {
  INHERIT_ACCESS_ONLY,
  INHERIT_DEFAULT_ONLY,
  INHERIT_ACCESS_AND_DEFAULT
  }
inherit_t;

enum insert_match
   {
   cf_ignore_leading,
   cf_ignore_trailing,
   cf_ignore_embedded,
   cf_exact_match
   };

enum monitord_rep
   {
   mon_rep_mag,
   mon_rep_week,
   mon_rep_yr
   };

enum software_rep
   {
   sw_rep_installed,
   sw_rep_patch_avail,
   sw_rep_patch_installed
   };

enum promiselog_rep
   {
   plog_repaired,
   plog_notkept
   };

enum time_window
   {
   time_hour,
   time_day,
   time_week
   };

/*************************************************************************/

enum cfd_menu
   {
   cfd_menu_delta,
   cfd_menu_full,
   cfd_menu_relay,
   cfd_menu_error
   };

/*************************************************************************/
/* Runtime constraint structures                                         */
/*************************************************************************/

#define OVECCOUNT 30

/*******************************************************************/

struct CfKeyBinding
   {
   char *name;
   RSA *key;
   char *address;
   time_t timestamp;
   };

/*************************************************************************/

struct CfKeyHostSeen
   {
   char address[CF_ADDRSIZE];
   struct QPoint Q;   
   };

/*************************************************************************/

struct CfLock
   {
   char *last;
   char *lock;
   char *log;
   };

/*************************************************************************/

struct CfMount
   {
   char *host;
   char *source;
   char *mounton;
   char *options;
   int unmount;
   };

/*************************************************************************/

struct Recursion
   {
   int travlinks;
   int rmdeadlinks;
   int depth;
   int xdev;
   int include_basedir;
   struct Rlist *include_dirs;
   struct Rlist *exclude_dirs;
   };

/*************************************************************************/

struct TransactionContext
   {
   enum cfopaction action;
   int ifelapsed;
   int expireafter;
   int background;
   char *log_string;
   char *log_kept;
   char *log_repaired;
   char *log_failed;
   int log_priority;
   char *measure_id;
   double value_kept;
   double value_notkept;
   double value_repaired;
   int  audit;
   enum cfreport report_level;
   enum cfreport log_level;
   };

/*************************************************************************/

struct DefineClasses
   {
   struct Rlist *change;
   struct Rlist *failure;
   struct Rlist *denied;
   struct Rlist *timeout;
   struct Rlist *kept;
   struct Rlist *interrupt;
   int persist;
   enum statepolicy timer;
   struct Rlist *del_change;
   struct Rlist *del_kept;
   struct Rlist *del_notkept;
   struct Rlist *retcode_kept;
   struct Rlist *retcode_repaired;
   struct Rlist *retcode_failed;
   };


/*************************************************************************/
/* Ontology                                                              */
/*************************************************************************/

struct Topic
   {
   int id;
   char *topic_context;
   char *topic_name;
   double evc;
   struct TopicAssociation *associations;
   struct Topic *next;
   };

struct TopicAssociation
   {
   char *fwd_context;
   char *fwd_name;
   char *bwd_name;
   struct Item *associates;
   char *bwd_context;
   struct TopicAssociation *next;
   };

struct Occurrence
   {
   char *occurrence_context;
   char *locator; /* Promiser */
   enum representations rep_type;
   struct Rlist *represents; /* subtype represented by promiser */
   struct Occurrence *next;
   };

struct Inference
   {
   char *inference; // Promiser
   char *precedent;
   char *qualifier;
   struct Inference *next;
   };

/*************************************************************************/
/* SQL Database connectors                                               */
/*************************************************************************/

enum cfdbtype
   {
   cfd_mysql,
   cfd_postgres,
   cfd_notype
   };

typedef struct 
   {
   int connected;
   int result;
   int row;
   unsigned int maxcolumns;
   unsigned int maxrows;
   int column;
   char **rowdata;
   char *blank;
   enum cfdbtype type;
   void *data; /* Generic pointer to RDBMS-specific data */
   }
CfdbConn;

/*************************************************************************/
/* Threading container                                                   */
/*************************************************************************/

struct PromiseThread
   {
   enum cfagenttype agent;
   char *scopeid;
   struct Promise *pp;
   void *fnptr;
   };

/*************************************************************************/
/* Package promises                                                      */
/*************************************************************************/

struct CfPackageManager
   {
   char *manager;
   enum package_actions action;
   enum action_policy policy;
   struct CfPackageItem *pack_list;
   struct CfPackageItem *patch_list;
   struct CfPackageItem *patch_avail;
   struct CfPackageManager *next;
   };

/*************************************************************************/

struct CfPackageItem 
   {
   char *name;
   char *version;
   char *arch;
   struct Promise *pp;
   struct CfPackageItem *next;
   };

/*************************************************************************/
/* Files                                                                 */
/*************************************************************************/

struct FileCopy
   {
   char *source;
   char *destination;
   enum cfcomparison compare;
   enum cflinktype link_type;
   struct Rlist *servers;
   struct Rlist *link_instead;
   struct Rlist *copy_links;
   enum cfbackupoptions backup;
   int stealth;
   int preserve;
   int collapse;
   int check_root;
   int type_check;
   int force_update;
   int force_ipv4;
   size_t min_size;      /* Safety margin not search criterion */
   size_t max_size;
   int trustkey;
   int encrypt;
   int verify;
   int purge;
   short portnumber;
   short timeout;
   };

struct ServerItem
   {
   char *server;
   struct cfagent_connection *conn;
   int busy;
   };

/*************************************************************************/

struct CfState
   {
   unsigned int expires;
   enum statepolicy policy;
   };

/*************************************************************************/

struct FilePerms
   {
   mode_t plus;
   mode_t minus;
   struct UidList *owners;
   struct GidList *groups;
   char  *findertype;
   u_long plus_flags;     /* for *BSD chflags */
   u_long minus_flags;    /* for *BSD chflags */
   int    rxdirs;
   };

/*************************************************************************/

struct FileSelect
   {
   struct Rlist *name;
   struct Rlist *path;
   struct Rlist *perms;
   struct Rlist *bsdflags;      
   struct Rlist *owners;
   struct Rlist *groups;
   long max_size;
   long min_size;
   time_t max_ctime;
   time_t min_ctime;
   time_t max_mtime;
   time_t min_mtime;
   time_t max_atime;
   time_t min_atime;
   char *exec_regex;
   char *exec_program;
   struct Rlist *filetypes;
   struct Rlist *issymlinkto;
   char *result;
   };

/*************************************************************************/

struct FileDelete

   {
   enum cftidylinks dirlinks;
   int rmdirs;
   };

/*************************************************************************/

struct FileRename
   {
   char *newname;
   char *disable_suffix;
   int disable;
   int rotate;
   mode_t plus;
   mode_t minus;
   };

/*************************************************************************/

struct FileChange
   {
   enum cfhashes hash;
   enum cfchanges report_changes;
   int report_diffs;
   int update;
   };

/*************************************************************************/

struct FileLink
   {
   char *source;
   enum cflinktype link_type;
   struct Rlist *copy_patterns;
   enum cfnofile when_no_file;
   enum cflinkchildren when_linking_children;
   int link_children;   
   };

/*************************************************************************/

struct ExecContain
   {
   int useshell;
   mode_t umask;
   uid_t owner;
   gid_t group;
   char *chdir;
   char *chroot;
   int preview;
   int nooutput;
   int timeout;
   };

/*************************************************************************/

struct ProcessCount
   {
   long min_range;
   long max_range;
   struct Rlist *in_range_define;
   struct Rlist *out_of_range_define;
   };

/*************************************************************************/

struct ProcessSelect
   {
   struct Rlist *owner;
   long min_pid;
   long max_pid;
   long min_ppid;
   long max_ppid;
   long min_pgid;
   long max_pgid;
   long min_rsize;
   long max_rsize;
   long min_vsize;
   long max_vsize;
   time_t min_ttime;
   time_t max_ttime;
   time_t min_stime;
   time_t max_stime;
   long min_pri;
   long max_pri;
   long min_thread;
   long max_thread;
   char *status;
   char *command;
   char *tty;
   char *process_result;
   };

/*************************************************************************/

struct Context
   {
   struct Constraint *expression;
   int broken;
   };

/*************************************************************************/

struct EditDefaults
   {
   enum cfbackupoptions backup;
   int empty_before_use;
   int maxfilesize;
   int joinlines;
   };

/*************************************************************************/

struct LineSelect
   {
   struct Rlist *startwith_from_list;
   struct Rlist *not_startwith_from_list;
   struct Rlist *match_from_list;
   struct Rlist *not_match_from_list;
   struct Rlist *contains_from_list;
   struct Rlist *not_contains_from_list;
   };

struct EditLocation
   {
   char *line_matching;
   enum cfeditorder before_after;
   char *first_last;
   };

struct EditRegion
   {
   char *select_start;
   char *select_end;
   int include_start;
   int include_end;
   };

struct EditColumn
   {
   char *column_separator;
   int select_column;
   char value_separator;
   char *column_value;
   char *column_operation;
   int extend_columns;
   int blanks_ok;
   };

struct EditReplace
   {
   char *replace_value;
   char *occurrences;
   };

/*************************************************************************/

struct StorageMount
   {
   char *mount_type;
   char *mount_source;
   char *mount_server;
   struct Rlist *mount_options;
   int editfstab;
   int unmount;
   };

struct StorageVolume
   {
   int check_foreign;
   long freespace;
   int sensible_size;
   int sensible_count;
   int scan_arrivals;
   };

/*************************************************************************/

struct Report
   {
   int haveprintfile;
   int havelastseen;
   int lastseen;
   double intermittency;
   char *friend_pattern;
   char *filename;
   char *to_file;
   int numlines;
   struct Rlist *showstate;
   };

/*************************************************************************/

struct Packages
   {
   enum package_actions package_policy;
   int have_package_methods;
   char *package_version;
   struct Rlist *package_architectures;
   enum version_cmp package_select;
   enum action_policy package_changes;
   struct Rlist *package_file_repositories;

   char *package_list_command;
   char *package_list_version_regex;
   char *package_list_name_regex;
   char *package_list_arch_regex;
   char *package_patch_list_command;

   char *package_patch_version_regex;
   char *package_patch_name_regex;
   char *package_patch_arch_regex;
   char *package_patch_installed_regex;
      
   char *package_list_update_command;
   int package_list_update_ifelapsed;

   char *package_version_regex;
   char *package_name_regex;
   char *package_arch_regex;
   char *package_installed_regex;

   char *package_add_command;
   char *package_delete_command;
   char *package_update_command;
   char *package_patch_command;
   char *package_verify_command;
   char *package_noverify_regex;
   char *package_name_convention;
   char *package_delete_convention;

   char *package_multiline_start;
      
   int package_noverify_returncode;
   };

/*************************************************************************/

struct Measurement
   {
   char *stream_type;
   enum cfdatatype data_type;
   char *history_type;
   char *select_line_matching;
   int select_line_number;
   char *extraction_regex;
   char *units;
   int growing;
   };

/*************************************************************************/

struct CfTcpIp
   {
   char *ipv4_address;
   char *ipv4_netmask;
   };

/*************************************************************************/

struct CfDatabase
   {
   char *db_server_owner;
   char *db_server_password;
   char *db_server_host;
   char *db_connect_db;
   enum cfdbtype  db_server_type;
   char *server;
   char *type;
   char *operation;
   struct Rlist *columns;
   struct Rlist *rows;
   struct Rlist *exclude;
   };
    
/*************************************************************************/

enum cf_srv_policy
   {
   cfsrv_start,
   cfsrv_stop,
   cfsrv_disable,
   cfsrv_nostatus
   };

struct CfServices
   {
   struct Rlist *service_depend;
   char *service_type;
   char *service_args;
   enum cf_srv_policy service_policy;
   char *service_autostart_policy;
   char *service_depend_chain;
   };

/*************************************************************************/

struct Outputs
   {
   char *level;
   char *promiser_type;
   };

/*************************************************************************/

enum cfhypervisors
   {
   cfv_virt_xen,
   cfv_virt_kvm,
   cfv_virt_esx,
   cfv_virt_test,
   cfv_virt_xen_net,
   cfv_virt_kvm_net,
   cfv_virt_esx_net,
   cfv_virt_test_net,
   cfv_zone,
   cfv_ec2,
   cfv_eucalyptus,
   cfv_none
   };

enum cfenvironment_state
   {
   cfvs_create,
   cfvs_delete,
   cfvs_running,
   cfvs_suspended,
   cfvs_down,
   cfvs_none
   };

struct CfEnvironments
   {
   int cpus;
   int memory;
   int disk;
   char *baseline;
   char *specfile;
   struct Rlist *addresses;
   char *name;
   char *host;
   char *type;
   enum cfenvironment_state state;
   };

/*************************************************************************/

 /* This is huge, but the simplification of logic is huge too
    so we leave it to the compiler to optimize */

struct Attributes
   {
   struct Outputs output;
   struct FileSelect select;
   struct FilePerms perms;
   struct FileCopy copy;
   struct FileDelete delete;
   struct FileRename rename;
   struct FileChange change;
   struct FileLink link;
   struct EditDefaults edits;
   struct Packages packages;
   struct Context context;
   struct Measurement measure;
   struct CfACL acl;
   struct CfDatabase database;
   struct CfServices service;
   struct CfEnvironments env;
   char *transformer;
   char *pathtype;
   char *repository;
   int touch;
   int create;
   int move_obstructions;
      
   struct Recursion recursion;
   struct TransactionContext transaction;
   struct DefineClasses classes;

   struct ExecContain contain;
   char *args;
   int module;

   struct Rlist *signals;
   char *process_stop;
   char *restart_class;
   struct ProcessCount process_count;
   struct ProcessSelect process_select;

   struct Report report;
   struct StorageMount mount;
   struct StorageVolume volume;
      
   struct CfTcpIp tcpip;
   int havedepthsearch;
   int haveselect;
   int haverename;
   int havedelete;
   int haveperms;
   int havechange;
   int havecopy;
   int havelink;
   int haveeditline;
   int haveeditxml;
   int haveedit;
   int havecontain;
   int haveclasses;
   int havetrans;
   int haveprocess_count;
   int havemount;
   int havevolume;
   int havebundle;
   int havetcpip;
   int havepackages;

      /* editline */

   struct EditRegion region;
   struct EditLocation location;
   struct EditColumn column;
   struct EditReplace replace;
   int haveregion;
   int havelocation;
   int havecolumn;
   int havereplace;
   int haveinsertselect;
   int havedeleteselect;
   struct LineSelect line_select;
   char *sourcetype;
   int expandvars;
   int not_matching;
   struct Rlist *insert_match;

      /* knowledge */

   char *fwd_name;
   char *bwd_name;
   struct Rlist *precedents;
   struct Rlist *qualifiers;
   struct Rlist *associates;
   struct Rlist *represents;
   struct Rlist *synonyms;
   struct Rlist *general;
   char *rep_type;
   char *path_root;
   char *web_root;
   };

enum cf_meter
{
meter_compliance_week,
meter_compliance_day,
meter_compliance_hour,
meter_perf_day,
meter_other_day,
meter_comms_hour,
meter_anomalies_day,
meter_endmark
};

/*************************************************************************/
/* definitions for reporting                                            */
/*************************************************************************/

typedef enum cdp_report
   {
   cdp_acls,
   cdp_commands,
   cdp_filechanges,
   cdp_filediffs,
   cdp_registry,
   cdp_services,
   cdp_unknown
   }
cdp_t;

typedef enum basic_reports
   {
   cfrep_bundle,
   cfrep_business,
   cfrep_classes,
   cfrep_promise_compliance,
   cfrep_total_compliance,
   cfrep_change,
   cfrep_diff,
   cfrep_lastseen,
   cfrep_patch_avail,
   cfrep_patch_status,
   cfrep_performance,
   cfrep_repaired,
   cfrep_repair_summary,
   cfrep_notkept,
   cfrep_notkept_summary,
   cfrep_setuid,
   cfrep_software_installed,
   cfrep_variables,
   cfrep_unknown
   }
cfrep_t;

/*************************************************************************/
/* definitions for test suite                                            */
/*************************************************************************/

// Classes: 601 - 650
#define CF_CLASS_ALL 0
#define CF_CLASS_REPORT 2
#define CF_CLASS_VARS 4
#define CF_CLASS_SLIST 8
#define CF_CLASS_STRING 16
#define CF_CLASS_PROCESS 32
#define CF_CLASS_FILE 64
#define CF_CLASS_DIR 128
#define CF_CLASS_CMD 256
#define CF_CLASS_OTHER 512
#define CF_CLASS_TOP10 1024

/*************************************************************************/
/* common macros                                                         */
/*************************************************************************/

#define EMPTY(str) ((str == NULL) || (str[0] == '\0'))
#define BEGINSWITH(str,start) (strncmp(str,start,strlen(start)) == 0)
#define CFSTRDUP(str) ((str != NULL) ? strdup(str) : NULL)
#define CFFREE(ptr) if(ptr) free(ptr)

// classes not interesting in reports
#define IGNORECLASS(c)                                                         \
 (strncmp(c,"Min",3) == 0 || strncmp(c,"Hr",2) == 0 || strcmp(c,"Q1") == 0     \
  || strcmp(c,"Q2") == 0 || strcmp(c,"Q3") == 0 || strcmp(c,"Q4") == 0         \
  || strncmp(c,"GMT_Hr",6) == 0  || strncmp(c,"Yr",2) == 0                     \
  || strncmp(c,"Day",3) == 0 || strcmp(c,"license_expired") == 0               \
  || strcmp(c,"any") == 0 || strcmp(c,"from_cfexecd") == 0                     \
  || IsStrIn(c,MONTH_TEXT) || IsStrIn(c,DAY_TEXT)                  \
  || IsStrIn(c,SHIFT_TEXT))

// Date time classes 
#define ISCLASS_DATETIME(c)						\
  (strncmp(c,"Min",3) == 0 || strncmp(c,"Hr",2) == 0 || strcmp(c,"Q1") == 0 \
    || strcmp(c,"Q2") == 0 || strcmp(c,"Q3") == 0 || strcmp(c,"Q4") == 0 \
    || strncmp(c,"GMT_Hr",6) == 0  || strncmp(c,"Yr",2) == 0                     \
   || strncmp(c,"Day",3) == 0 || IsStrIn(c,MONTH_TEXT)		\
  || IsStrIn(c,DAY_TEXT) || IsStrIn(c,SHIFT_TEXT)                 \
  || strncmp(c,"Lcycle",6) == 0)

#include "prototypes3.h"

#ifdef HAVE_NOVA
#include <cf.nova.h>
#endif

#endif
