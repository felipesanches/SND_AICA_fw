/* $Id: aica.h,v 1.3 2002/10/29 15:43:51 mrbrown Exp $ */

#ifndef __AICA_H
#define __AICA_H

/* volatile unsigned char *dc_snd_base = (unsigned char *)0x00800000; */
#define dc_snd_base ((volatile unsigned char *)0x00800000)

/* Some convienence macros */
#define SNDREG32A(x) ((volatile unsigned long *)(dc_snd_base + (x)))
#define SNDREG32(x) (*SNDREG32A(x))
#define SNDREG8A(x) (dc_snd_base + (x))
#define SNDREG8(x) (*SNDREG8A(x))
#define CHNREG32A(chn, x) SNDREG32A(0x80*(chn) + (x))
#define CHNREG32(chn, x) (*CHNREG32A(chn, x))
#define CHNREG8A(chn, x) SNDREG8A(0x80*(chn) + (x))
#define CHNREG8(chn, x) (*CHNREG8A(chn, x))

/* Sound modes */
#define SM_8BIT		1
#define SM_16BIT	0
#define SM_ADPCM	2

#endif	/* __AICA_H */

