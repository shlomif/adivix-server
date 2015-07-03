#ifndef __ADIVIX_ZERO_H__
#define __ADIVIX_ZERO_H__

/* connection handshake
 * --------------------
 * - client sends struct zbbsver to server
 * - server replies with 8-character (hexadecimal string) connection ID
 *   - "00000000" for errors
 */

#define ZERO_ERROR       0x00000000
#define ZERO_AUTH_LE     0x41555448             // "AUTH", little-endian
#define ZERO_AUTH_BE     0x48545541             // "AUTH", big-endian
#define ZERO_BYTE_LE                            // "BYTE" (byte-order)
#define ZERO_BYTE_BE                            // "BYTE" (byte-order)
#define ZERO_HELO_LE     0x48454c4f             // "HELO"
#define ZERO_HELO_BE     0x4f4c4548
#define ZERO_PERM_LE                            // "PERM" (permissions)
#define ZERO_PERM_BE
#define ZERO_LIST_LE     0x4c495354             // "LIST", little-endian
#define ZERO_LIST_BE     0x5453494c
#define ZERO_PASS_LE                            // "PASS" (password)
#define ZERO_PASS_BE
#define ZERO_PROT_LE                            // "PROT" (protocol)
#define ZERO_PROT_BE
#define ZERO_CHAN_LE                            // "CHAN" (channel)
#define ZERO_CHAN_BE
#define ZERO_USER_LE                            // "USER"
#define ZERO_USER_BE
#define ZERO_JOIN_LE                            // "JOIN"
#define ZERO_JOIN_BE
#define ZERO_VER_LE      0x56455200             // "VER\0"
#define ZERO_VER_BE      0x00524556
#define ZERO_XFER_LE     0x58464552             // "XFER"
#define ZERO_XFER_BE     0x52454658
#define ZERO_SEND_LE
#define ZERO_SEND_BE
#define ZERO_RECV_LE
#define ZERO_RECV_BE

#define ZERO_PERM_UR     0400
#define ZERO_PERM_UW     0200
#define ZERO_PERM_UX     0100
#define ZERO_PERM_GR     0040
#define ZERO_PERM_GW     0020
#define ZERO_PERM_GX     0010
/* ATTENTION: take care with world-permission bits */
#define ZERO_PERM_AR     0004
#define ZERO_PERM_AW     0002
#define ZERO_PERM_AX     0001

#define ZERO_ERROR_AUTH  0x00000001     // no proper authentication
#define ZERO_ERROR_NOOBJ 0x00000002     // object non-existent or not creted
#define ZERO_ERROR_PERM  0x00000003     // inadequate access permissions
#define ZERO_ERROR_PASS  0x00000004     // invalid password
#define ZERO_ERROR_USER  0x00000005     // invalid user ID

/* version message */
struct zeroverreply {
    uint32_t proto;     // e.g. "ZBBS"
    uint32_t ver;       // e.g. 0x00000001
};

/* error message */
struct zeroerrorreply {
    uint32_t obj;       // object ID
    uint32_t code;      // error-code
};

/* permission query */
struct zeropermreq {
    uint32_t obj;       // object ID
};

/* permission reply */
struct zeropermreply {
    uint32_t obj;       // object ID
    uint32_t flg;       // effective permission-bits; ZERO_PERM_-values
};

/* username message */
struct zerouserreq {
    uint32_t size;
    uint32_t name[EMPTY];
};

/* sign-on reply */
struct zerosignreply {
    uint32_t id;        // user ID
    uint32_t connid;    // connection ID
};

struct zeropassreq {
    uint32_t usr;
    uint32_t size;
    uint32_t hash[EMPTY];
};

#define ZERO_BYTE_MSB 0x00
#define ZERO_BYTE_LSB 0x01
struct zerobytereply {
    uint8_t flg;
};

/* generic protocol request */
struct zeroreq {
    uint32_t cmd;
    uint32_t size;
    uint8_t  data[EMPTY];
};

/* protocol reply */
struct zeroreply {
    uint32_t code;
    uint32_t size;
    uint8_t  data[EMPTY];
};

#endif /* __ADIVIX_ZERO_H__ */

