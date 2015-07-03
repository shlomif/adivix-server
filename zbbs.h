#infdef __ZERO_ZBBS_H__
#define __ZERO_ZBBS_H__

#include <zero/param.h>
#include <zero/cdecl.h>

/*
 * Zero BBS Protocol, Revision 0.0
 * -------------------------------
 *
 * Protocol Requests/Commands
 * --------------------------
 * - PROTOS             - query protocols supported by server
 * - USERS              - obtain information on [service] users
 * - ROOMS              - list service rooms
 * - CHANNELS           - list chat channels
 * - BULLETIN           - fetch bulletins
 * - RIGHTS             - query user access level
 * - PRIVMSG            - send private message to given users
 * - FORUM              - set active forum
 * - NEWSGRP            - set active newsgroup
 * - PUBLISH            - publish a post to given forums
 * - MKAREA             - create new file area
 * - FILEAREA           - enter file area
 * - FILES              - list files in given areas (empty - current, * - all)
 * - SENDFILE           - send file to server
 * - RECVFILE           - receive file from server
 * - PROFILE            - profile actions such as edit
 * - ACCOUNT            - account (user) actions
 * - JOIN               - join [IRC] chat channel
 * - YELL               - try to catch a system operator's attention
 */

#define ZBBS_PROTO_LE  "0x5a424253"             // "ZBBS"
#define ZBBS_PROTO_BE  "0x5342425a"
#define ZBBS_PROTO     "ZBBS"                   // protocol ID
#define ZBBS_VERSION   "XXXXXXXX"               // version, hexadecimal string
/* protocol commands */
#define ZBBS_PROTOS    "PROTOS"                 // query supported protocols
#define ZBBS_DATE      "YYYYMMDD"               // 8-character string
#define ZBBS_TIME      "uuuuuuuuuuuuuuuu"       // microseconds into day, text

#define ZBBS_ID_STRING (ZBBS_PROTO " " ZBBS_VERSION)

#endif /* __ZERO_ZBBS_H__ */

