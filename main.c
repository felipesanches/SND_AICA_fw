/* Streaming sound driver
 *
 * (c)2000 Dan Potter
 *
 * This slightly more complicated version allows for sound effect channels,
 * and full sampling rate, panning, and volume control for each. The two
 * streaming channels are still always first and always occur at 0x11000 and
 * 0x21000. All other sample data can begin at 0x31000. "pos" only works for
 * input on the two streaming channels (which will always have the same
 * "pos" value).
 * 
 * $Id: main.c,v 1.3 2002/10/29 15:48:47 mrbrown Exp $
 */

#include "aica.h"
#include "aica_cmd_iface.h"

static int buffer_index;
static int active;

/****************** Timer *******************************************/

extern volatile int timer;

void timer_wait(int jiffies) {
	int fin = timer + jiffies;
	while (timer <= fin)
		;
}

/****************** Main Program ************************************/

/* Set channel id at 0x80280d (byte), read position at 0x802814 (long) */

volatile uint32 *cmd = (volatile uint32 *)0x10000;
volatile aica_channel *chans = (volatile aica_channel *)0x10004;

void start_channel(int chn) {
  int samplesize = 1;
  int stereo = (chans[chn].flags & 1);
  if (chans[chn].sfmt == SM_16BIT) samplesize = 2;
  if (stereo)
    {
      aica_play(0, 0x11000  , chans[chn].sfmt, 0, 0x8000/samplesize, chans[chn].freq, chans[chn].vol, 0, 1);
      aica_play(1, 0x21000, chans[chn].sfmt, 0, 0x8000/samplesize, chans[chn].freq, chans[chn].vol, 0xff, 1);
    }
else
  {
    aica_play(chn, 0x11000, chans[chn].sfmt, 0, 0x8000/samplesize, chans[chn].freq, chans[chn].vol, chans[chn].pan, 1);
  }	
}

void stop_channel(int chn) {
	if (chn == 0) {
		aica_stop(0);
		aica_stop(1);
	} else {
		aica_stop(chn);
	}
}

void vol_channel(int chn) {
	if (chn == 0) {
		aica_vol(0, chans[chn].vol);
		aica_vol(1, chans[chn].vol);
	} else {
		aica_vol(chn, chans[chn].vol);
	}
}

void process_cmd(uint32 cmd) {
	/* cmd is channel to look at +1 */
	cmd--;
	switch(chans[cmd].cmd) {
		case AICA_CMD_NONE:
			break;
		case AICA_CMD_START:
			start_channel(cmd);
			active = 0;
			break;
		case AICA_CMD_STOP:
			stop_channel(cmd);
			active = 0;
			break;
		case AICA_CMD_VOL:
			vol_channel(cmd);
			break;
	}
}

int arm_main() {
	int cmdl;
	int flags, shift_buffer, pass;
	/* Initialize the AICA part of the SPU */
	aica_init();
	

	/* Observe channel 0 */
	SNDREG8(0x280d) = 0;

	/* Wait for a command */
	while(1) {
		/* Check for a command */
		cmdl = *cmd;
		if (cmdl & AICA_CMD_KICK) {
			*cmd = 0;
			process_cmd(cmdl & ~AICA_CMD_KICK);
		}
		
		/* Update position counters */
		chans[0].pos = SNDREG32(0x2814);
		
		/* Little delay to prevent memory lock */
		timer_wait(10);

	}
}






