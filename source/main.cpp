/*
 * assignment2_drums
 *
 * Second assignment for ECS732 RTDSP, to create a sequencer-based
 * drum machine which plays sampled drum sounds in loops.
 *
 * This code runs on BeagleBone Black with the BeagleRT environment.
 *
 * 2015
 * Andrew McPherson and Victor Zappi
 * Queen Mary University of London
 */

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <libgen.h>
#include <signal.h>
#include <getopt.h>
#include <sndfile.h>
#include "../include/RTAudio.h"
#include "drums.h"

using namespace std;

void *gpioLoop(void *data);

/* Drum samples are pre-loaded in these buffers. Length of each
 * buffer is given in gDrumSampleBufferLengths.
 */
float *gDrumSampleBuffers[NUMBER_OF_DRUMS];
int gDrumSampleBufferLengths[NUMBER_OF_DRUMS];

/* Patterns indicate which drum(s) should play on which beat.
 * Each element of gPatterns is an array, whose length is given
 * by gPatternLengths.
 */
int *gPatterns[NUMBER_OF_PATTERNS];
int gPatternLengths[NUMBER_OF_PATTERNS];
int ***gSynthPatterns[NUMBER_OF_PATTERNS];

// Handle Ctrl-C by requesting that the audio rendering stop
void interrupt_handler(int var)
{
	gShouldStop = true;
}

// Print usage information
void usage(const char * processName)
{
	cerr << "Usage: " << processName << " [options]" << endl;

	BeagleRT_usage();

	cerr << "   --help [-h]:                Print this menu\n";
}

int initDrums() {
	/* Load drums from WAV files */
	SNDFILE *sndfile ;
	SF_INFO sfinfo ;
	char filename[64];

	for(int i = 0; i < NUMBER_OF_DRUMS; i++) {
		snprintf(filename, 64, "drums/drum%d.wav", i);

		if (!(sndfile = sf_open (filename, SFM_READ, &sfinfo))) {
			printf("Couldn't open file %s\n", filename);

			/* Free already loaded sounds */
			for(int j = 0; j < i; j++)
				free(gDrumSampleBuffers[j]);
			return 1;
		}

		if (sfinfo.channels != 1) {
			printf("Error: %s is not a mono file\n", filename);

			/* Free already loaded sounds */
			for(int j = 0; j < i; j++)
				free(gDrumSampleBuffers[j]);
			return 1;
		}

		gDrumSampleBufferLengths[i] = sfinfo.frames;
		gDrumSampleBuffers[i] = (float *)malloc(gDrumSampleBufferLengths[i] * sizeof(float));
		if(gDrumSampleBuffers[i] == NULL) {
			printf("Error: couldn't allocate buffer for %s\n", filename);

			/* Free already loaded sounds */
			for(int j = 0; j < i; j++)
				free(gDrumSampleBuffers[j]);
			return 1;
		}

		int subformat = sfinfo.format & SF_FORMAT_SUBMASK;
		int readcount = sf_read_float(sndfile, gDrumSampleBuffers[i], gDrumSampleBufferLengths[i]);

		/* Pad with zeros in case we couldn't read whole file */
		for(int k = readcount; k < gDrumSampleBufferLengths[i]; k++)
			gDrumSampleBuffers[i][k] = 0;

		if (subformat == SF_FORMAT_FLOAT || subformat == SF_FORMAT_DOUBLE) {
			double	scale ;
			int 	m ;

			sf_command (sndfile, SFC_CALC_SIGNAL_MAX, &scale, sizeof (scale)) ;
			if (scale < 1e-10)
				scale = 1.0 ;
			else
				scale = 32700.0 / scale ;
			printf("Scale = %f\n", scale);

			for (m = 0; m < gDrumSampleBufferLengths[i]; m++)
				gDrumSampleBuffers[i][m] *= scale;
		}

		sf_close(sndfile);
	}

	return 0;
}

void cleanupDrums() {
	for(int i = 0; i < NUMBER_OF_DRUMS; i++)
		free(gDrumSampleBuffers[i]);
}

void initPatterns() {

	// pID_synth[synth][patternIndex][gate,pitch]
	// gate messages: 3=auto-trigger, 2=on, 1=sustain, 0=offs
 int p0_synth[5][32][2] = { { {3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0,},
								{3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0,},
								{3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0},
								{3,48},{0,0},{3,48},{0,0},
								{3,48},{0,0},{3,48},{0,0}	},

							 { {0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0}		},

							 { {0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{3,60},{3,60},{3,60},{3,60},
								{3,60},{0,0},{3,60},{0,0},
								{3,60},{0,0},{3,60},{0,0},
								{3,60},{0,0},{3,60},{0,0}		},

							{ {0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0}		},

							{ {0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0}		},

	 	 	 	 	 	 	 };

 int p1_synth[5][32][2] = { { {3,45},{3,45},{3,45},{3,45},
 								{3,45},{0,0},{3,45},{0,0,},
 								{3,45},{3,45},{3,45},{3,45},
 								{3,45},{0,0},{3,45},{0,0,},
 								{3,43},{3,43},{3,43},{3,43},
 								{3,43},{0,0},{3,43},{0,0},
 								{3,43},{0,0},{3,43},{0,0},
 								{3,43},{0,0},{3,43},{0,0}	},

 							 { {0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0}		},

 							 { {0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0}		},

 							 { {2,57},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{2,55},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0}		},

 							{ {2,52},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{2,50},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0}		},

 	 	 	 	 	 	 	 };

 int p2_synth[5][32][2] = { { {3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0,},
								{3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0,},
								{3,48},{3,48},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0},
								{3,48},{0,0},{3,48},{3,48},
								{3,48},{0,0},{3,48},{0,0}	},

							 { {0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{3,89},{0,0},{0,0},{0,0},
								{3,88},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0}		},

							 { {3,76},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{0,0},{0,0},{0,0},{0,0},
								{3,76},{0,0},{3,76},{3,76},
								{3,79},{0,0},{3,79},{0,0}		},

							 { {2,60},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{0,0},{0,0},{0,0},{0,0}		},

							{ {1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{0,0},{0,0},{0,0},{0,0},
								{2,64},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0},
								{1,0},{1,0},{1,0},{1,0}		},

	 	 	 	 	 	 	 };
 int p3_synth[5][32][2] = { { {2,38},{1,0},{1,0},{0,38},
		 	 	 	 	 	    {2,38},{1,0},{0,38},{3,36},
 								{2,38},{1,38},{2,36},{1,36},
 								{2,38},{1,38},{2,36},{1,36},
 								{2,38},{1,0},{1,0},{0,38},
 								{2,38},{1,0},{0,38},{3,36},
 								{2,38},{1,38},{2,36},{1,36},
 								{2,38},{1,38},{2,36},{1,36},	},

 							 { {3,62},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{0,0},{0,0},{0,0},{0,0}		},

 							 { {3,62},{3,62},{3,62},{3,62},
 								{3,62},{3,62},{3,62},{3,62},
 								{3,60},{3,62},{3,62},{3,62},
 								{3,62},{3,60},{3,62},{3,60},
 								{3,62},{3,62},{3,62},{3,62},
								{3,62},{3,62},{3,62},{3,62},
								{3,60},{3,62},{3,62},{3,62},
								{3,62},{3,60},{3,62},{3,60}		},

 							 { {2,62},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0}		},

 							{ {1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{0,0},{0,0},{0,0},{0,0},
 								{2,65},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0},
 								{1,0},{1,0},{1,0},{1,0}		},

 	 	 	 	 	 	 	 };

 int p4_synth[5][32][2] = { { {2,33},{1,0},{1,0},{0,33},
 		 	 	 	 	 	    {2,33},{1,0},{0,33},{3,31},
  								{2,33},{1,33},{2,31},{1,31},
  								{2,33},{1,33},{2,31},{1,31},
  								{2,33},{1,0},{1,0},{0,33},
								{2,33},{1,0},{0,33},{3,31},
								{2,33},{1,33},{2,31},{1,31},
								{2,33},{1,33},{2,31},{1,31},	},

  							 { {3,60},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{0,0},{0,0},{0,0},{0,0}		},

  							 { {3,57},{3,57},{3,57},{3,57},
  								{3,57},{3,57},{3,57},{3,57},
  								{3,55},{3,57},{3,57},{3,57},
  								{3,57},{3,55},{3,57},{3,55},
  								{3,57},{3,57},{3,57},{3,57},
								{3,57},{3,57},{3,57},{3,57},
								{3,55},{3,57},{3,57},{3,57},
								{3,57},{3,55},{3,57},{3,55}		},

  							 { {2,60},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{0,0},{0,0},{0,0},{0,0}		},

  							{ {1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{0,0},{0,0},{0,0},{0,0},
  								{2,64},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0},
  								{1,0},{1,0},{1,0},{1,0}		},

  	 	 	 	 	 	 	 };

	int pattern0[32] = {0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x00, 0x04,
						0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x04, 0x04 };
	int pattern1[32] = {0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x00, 0x04,
						0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x03, 0x04, 0x02, 0x03, 0x04, 0x01, 0x06, 0x06 };
	int pattern2[32] = {0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x00, 0x04,
						0x01, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x84, 0x44 };
	int pattern3[32] = {0x09, 0, 0x04, 0, 0x03, 0, 0x04, 0, 0x01, 0, 0x04, 0, 0x03, 0, 0x04, 0x04,
						0x01, 0, 0x04, 0, 0x03, 0, 0x04, 0, 0x01, 0, 0x04, 0, 0x03, 0, 0x04, 0x04 };
	int pattern4[32] = {0x09, 0, 0, 0, 0x03, 0, 0, 0, 0x01, 0, 0, 0, 0x03, 0, 0x00, 0x04,
						0x01, 0, 0x04, 0, 0x03, 0, 0x04, 0, 0x01, 0, 0, 0, 0x03, 0, 0x04, 0x04 };

	gPatternLengths[0] = 32;
	gPatterns[0] = (int *)malloc(gPatternLengths[0] * sizeof(int));
	memcpy(gPatterns[0], pattern0, gPatternLengths[0] * sizeof(int));
	// synth patterns
	gSynthPatterns[0] = (int ***)malloc(5 * gPatternLengths[0] * 2 * sizeof(int));
	memcpy(gSynthPatterns[0], p0_synth, 5 * gPatternLengths[0] * 2 * sizeof(int));

	gPatternLengths[1] = 32;
	gPatterns[1] = (int *)malloc(gPatternLengths[1] * sizeof(int));
	memcpy(gPatterns[1], pattern1, gPatternLengths[1] * sizeof(int));
	// synth patterns
	gSynthPatterns[1] = (int ***)malloc(5 * gPatternLengths[1] * 2 * sizeof(int));
	memcpy(gSynthPatterns[1], p1_synth, 5 * gPatternLengths[1] * 2 * sizeof(int));

	gPatternLengths[2] = 32;
	gPatterns[2] = (int *)malloc(gPatternLengths[2] * sizeof(int));
	memcpy(gPatterns[2], pattern2, gPatternLengths[2] * sizeof(int));
	// synth patterns
	gSynthPatterns[2] = (int ***)malloc(5 * gPatternLengths[2] * 2 * sizeof(int));
	memcpy(gSynthPatterns[2], p2_synth, 5 * gPatternLengths[2] * 2 * sizeof(int));

	gPatternLengths[3] = 32;
	gPatterns[3] = (int *)malloc(gPatternLengths[3] * sizeof(int));
	memcpy(gPatterns[3], pattern3, gPatternLengths[3] * sizeof(int));
	// synth patterns
	gSynthPatterns[3] = (int ***)malloc(5 * gPatternLengths[3] * 2 * sizeof(int));
	memcpy(gSynthPatterns[3], p3_synth, 5 * gPatternLengths[3] * 2 * sizeof(int));

	gPatternLengths[4] = 32;
	gPatterns[4] = (int *)malloc(gPatternLengths[4] * sizeof(int));
	memcpy(gPatterns[4], pattern4, gPatternLengths[4] * sizeof(int));
	// synth patterns
	gSynthPatterns[4] = (int ***)malloc(5 * gPatternLengths[4] * 2 * sizeof(int));
	memcpy(gSynthPatterns[4], p4_synth, 5 * gPatternLengths[4] * 2 * sizeof(int));

}

void cleanupPatterns() {
	for(int i = 0; i < NUMBER_OF_PATTERNS; i++)	{
		free(gPatterns[i]);
		free(gSynthPatterns[i]);
	}
}

int main(int argc, char *argv[])
{

	RTAudioSettings settings;	// Standard audio settings
	pthread_t sensorThread;		// Thread for the sensor (GPIO) loop

	struct option customOptions[] =
	{
		{"help", 0, NULL, 'h'},
		{NULL, 0, NULL, 0}
	};

	// Set default settings
	BeagleRT_defaultSettings(&settings);

	// Parse command-line arguments
	while (1) {
		int c;
		if ((c = BeagleRT_getopt_long(argc, argv, "hf:", customOptions, &settings)) < 0)
				break;
		switch (c) {
		case 'h':
				usage(basename(argv[0]));
				exit(0);
		case '?':
		default:
				usage(basename(argv[0]));
				exit(1);
		}
	}

	// Load the drum sounds and the patterns
    if(initDrums()) {
    	printf("Unable to load drum sounds. Check that you have all the WAV files!\n");
    	return -1;
    }
    printf("Drum sounds loaded correctly. Starting ...\n");
    initPatterns();

	// Initialise the PRU audio device
	if(BeagleRT_initAudio(&settings, 0) != 0) {
		cout << "Error: unable to initialise audio" << endl;
		return -1;
	}

	// Start the sensor loop for GPIO
	pthread_create(&sensorThread, NULL, gpioLoop, NULL);

	// Start the audio device running
	if(BeagleRT_startAudio()) {
		cout << "Error: unable to start real-time audio" << endl;
		return -1;
	}

	// Set up interrupt handler to catch Control-C
	signal(SIGINT, interrupt_handler);
	signal(SIGTERM, interrupt_handler);

	// Run until told to stop
	while(!gShouldStop) {
		usleep(100000);
	}

	// Stop the audio device and sensor thread
	BeagleRT_stopAudio();
	(void)pthread_join(sensorThread, NULL);

	// Clean up any resources allocated for audio
	BeagleRT_cleanupAudio();

	// Clean up the drums
	cleanupPatterns();
	cleanupDrums();

	// All done!
	return 0;
}
