/*
 * Std_Types.h
 *
 *  Created on: 23.01.2019
 *      Author: RNT9FE
 */

#ifndef STD_TYPES_H_
#define STD_TYPES_H_

typedef unsigned char uint8;
typedef unsigned int uint16;
typedef unsigned long uint32;
typedef unsigned long long uint64;

typedef unsigned char uint8_least;
typedef unsigned int uint16_least;
typedef unsigned long uint32_least;
typedef unsigned long long uint64_least;

typedef unsigned char boolean;

#define FALSE 0
#define TRUE 1
#define NULL_PTR ((void *)0)


typedef uint8 Std_ReturnType;

/* STD015: Standard Version Info Type */
/* This type shall be used to request the version of a BSW module using the <Module name>_GetVersionInfo()function. */
typedef struct
{
    uint16 vendorID;
    uint16 moduleID;
    uint8 sw_major_version;
    uint8 sw_minor_version;
    uint8 sw_patch_version;
} Std_VersionInfoType;



#endif /* STD_TYPES_H_ */
