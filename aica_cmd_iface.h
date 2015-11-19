/* $Id: aica_cmd_iface.h,v 1.2 2002/10/29 15:45:10 mrbrown Exp $ */

#ifndef __ARM_AICA_CMD_IFACE_H
#define __ARM_AICA_CMD_IFACE_H

#ifndef __ARCH_TYPES_H
typedef unsigned long uint32;
#endif

/* Make this 8 dwords long for one aica bus queue */
typedef struct {
	uint32		cmd;		/* Command ID		*/
	uint32		pos;		/* Sample position	*/
	uint32		length;		/* Sample length	*/
	uint32		freq;		/* Frequency		*/
	uint32		vol;		/* Volume 0-255		*/
	uint32		pan;		/* Pan 0-255		*/
        uint32		sfmt;	        /* Sound format		*/
	uint32		flags;	        /* flags		*/
} aica_channel;

/* Command values */
#define AICA_CMD_KICK		0x80000000
#define AICA_CMD_NONE		0
#define AICA_CMD_START		1
#define AICA_CMD_STOP		2
#define AICA_CMD_VOL		3

#endif	/* __ARM_AICA_CMD_IFACE_H */
