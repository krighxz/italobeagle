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

/*
 *
 * Christian Heinrichs
 *
 * "(B)eagles In The Night"
 *
 * Powered by Heavy and emotion.
 * [ with occasional bi-drectional support from/to Robert Jack ]
 *
 */


#include "../include/render.h"
#include "../include/Utilities.h"
#include "drums.h"
#include <rtdk.h>
#include <cmath>
#include <cstdlib>		// for rand() function
#include "Heavy_beagleSequencer.h"
#define HV_SIMD_NONE
#include <string>

Hv_beagleSequencer *gHeavyContext;

#define NUM_VOICES 16
#define NUM_SYNTHS 5
#define CLOCK_BUFFER_SIZE 1024
#define MASTER 0
#define SLAVE 1

int gClockOutPin = 6;
int gClockInPin = 5;

int gEventTriggeredByClock = 0;

/* Drum samples are pre-loaded in these buffers. Length of each
 * buffer is given in gDrumSampleBufferLengths.
 */
extern float *gDrumSampleBuffers[NUMBER_OF_DRUMS];
extern int gDrumSampleBufferLengths[NUMBER_OF_DRUMS];

int gNumChannels = 0;

/* Read pointers into the current drum sample buffers.
 */
int gReadPointers[NUM_VOICES] = {0};
int gReadPointersState[NUM_VOICES] = {0,};
int gReadPointersBufferID[NUM_VOICES] = {0,};

/* Patterns indicate which drum(s) should play on which beat.
 * Each element of gPatterns is an array, whose length is given
 * by gPatternLengths.
 */
extern int *gPatterns[NUMBER_OF_PATTERNS];
extern int gPatternLengths[NUMBER_OF_PATTERNS];
extern int ***gSynthPatterns[NUMBER_OF_PATTERNS];

/* These variables indicate which pattern we're playing, and
 * where within the pattern we currently are. Used in Step 4c.
 */
int gCurrentPattern = 0;
int gCurrentIndexInPattern = 0;

/* Triggers from buttons (step 2 etc.). Read these here and
 * do something if they are nonzero (resetting them when done). */
extern int gTriggerButton1;
extern int gTriggerButton2;

// global accelerometer variables
float gAccelX = 0;
float gAccelY = 0;
float gAccelZ = 0;
int gAccelState = 0;

// pattern mappings for accelerometer states
int gAccelPatternMappings[6] {0,1,2,3,4,5};

/* This variable holds the interval between events in **milliseconds**
 * To use it (Step 4a), you will need to work out how many samples
 * it corresponds to.
 */
int gEventIntervalMilliseconds = 250;
int gEventIntervalSamples = 11050;

int gSampleCounter = 0;
// global variable used for triggering LED
int gEventJustTriggered = 0;

int gAudioSampleRate = 0;
float gInverseSampleRate = 0;

/* This variable indicates whether samples should be triggered or
 * not. It is used in Step 4b, and should be set in gpio.cpp.
 */
extern int gIsPlaying;

/* This indicates whether we should play the samples backwards.
 */
int gPlaysBackwards = 0;


float gClockBuffer[CLOCK_BUFFER_SIZE];
int gClockReadPointer = 0;
int gMasterClock = 0;
int gClockReset = 0;

float gClockInputBuffer[CLOCK_BUFFER_SIZE];
int gClockInputReadPointer = 0;
float beatClockvalue[4] {0,0.25,0.5,0.75};

int gLastClock = 0;

float gAnalogOut = 0;


// initialise_render() is called once before the audio rendering starts.
// Use it to perform any initialisation and allocation which is dependent
// on the period size or sample rate.
//
// userData holds an opaque pointer to a data structure that was passed
// in from the call to initAudio().
//
// Return true on success; returning false halts the program.

float *gInputBuffers = NULL, *gOutputBuffers = NULL;
int gInputChannels = 0, gOutputChannels = 0;
int gSynthCounter = 0;

bool initialise_render(int numMatrixChannels, int numAudioChannels,
					   int numMatrixFramesPerPeriod,
					   int numAudioFramesPerPeriod,
					   float matrixSampleRate, float audioSampleRate,
					   void *userData)
{

	gNumChannels = numAudioChannels;
	gAudioSampleRate = audioSampleRate;
	gInverseSampleRate = 1/audioSampleRate;

	gHeavyContext = hv_beagleSequencer_new(audioSampleRate);
	gInputChannels = hv_getNumInputChannels(gHeavyContext);
	gOutputChannels = hv_getNumOutputChannels(gHeavyContext);

	printf("Starting Heavy context with %d input channels and %d output channels\n",
			  gInputChannels, gOutputChannels);

	if(gInputChannels != 0) {
		gInputBuffers = (float *)malloc(gInputChannels * numAudioFramesPerPeriod * sizeof(float));
	}
	if(gOutputChannels != 0) {
		gOutputBuffers = (float *)malloc(gOutputChannels * numAudioFramesPerPeriod * sizeof(float));
	}

	// initialise synth parameters
	for(int s=0;s<NUM_SYNTHS;s++)	{
		switch(s)	{
		case 0:		// bass
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"attack",10.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"decay",100.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fAttack",0.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fDecay",100.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeLow",100.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeHigh",2000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"volume",0.3f);
			break;
		case 1:		// crystal (sine-wave + envelope)
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"attack",5.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"decay",2000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"volume",0.25f);
			break;
		case 2:		// bips
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"attack",5.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"decay",100.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fAttack",0.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fDecay",20.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeLow",500.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeHigh",2000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"volume",0.6f);
			break;
		case 3:		// pad voice 1
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"attack",500.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"decay",4000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fAttack",200.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fDecay",2000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeLow",400.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeHigh",1000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"addRate",0.5f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"multRate",0.501f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"volume",0.1f);
			break;
		case 4:		// pad voice 2
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"attack",500.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"decay",4000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fAttack",200.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fDecay",2000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeLow",400.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"fRangeHigh",1000.0f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"addRate",0.5f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"multRate",0.501f);
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)s+1,"volume",0.1f);
			break;
		default:
			break;
		}
	}

	return true;
}

// render() is called regularly at the highest priority by the audio engine.
// Input and output are given from the audio hardware and the other
// ADCs and DACs (if available). If only audio is available, numMatrixFrames
// will be 0.

void render(int numMatrixFrames, int numAudioFrames, float *audioIn, float *audioOut,
			float *matrixIn, float *matrixOut)
{

	// process heavy context
	hv_beagleSequencer_process_inline(gHeavyContext, gInputBuffers, gOutputBuffers, numAudioFrames);

	for(int m=0;m<numMatrixFrames;m++)	{

		#if SLAVE
			float clockValue = matrixIn[m*8+gClockInPin];
//			if(m==0)
//				rt_printf("%f\n",clockValue);
			if(++gClockInputReadPointer>=CLOCK_BUFFER_SIZE)
				gClockInputReadPointer = 0;
//			gClockInputBuffer[gClockInputReadPointer] = constrain(map(clockValue,0.122894,0.974518,0,1),0,1);
			gClockInputBuffer[gClockInputReadPointer] = constrain(map(clockValue,0.3,0.9,0,1),0,1);

		#endif

		// only check accel/pot input at beginning of each block to save computation
		if(m==0)	{
			// 1. Change tempo using potentiometer
			float potIn = matrixIn[m*8+0];
			// range: 60-180bpm (exponential mapping)
			gEventIntervalMilliseconds = (1-(potIn*potIn*1.21065)) *170 + 80; // 1.21065 scaling factor for V range
			gEventIntervalSamples = gEventIntervalMilliseconds * 0.001 * gAudioSampleRate;
			// 2. Change pattern based on accelerometer state
			//// readings:
			// flat: 0.405884 0.436447 0.554550
			// left side: 0.209198 0.429504 0.329636
			// right side: 0.610031 0.437378 0.349640
			// front side: 0.406601 0.630783 0.338867
			// back side: 0.414520 0.242996 0.357086
			// upside-down: 0.408508 0.441162 0.145844
			gAccelX = constrain( map(matrixIn[m*8+1],0.2092,0.61,-1.0,1.0), -1, 1);
			gAccelY = constrain( map(matrixIn[m*8+2],0.2431,0.6308,-1.0,1.0), -1, 1);
			gAccelZ = constrain( map(matrixIn[m*8+3],0.1458,0.5546,-1.0,1.0), -1, 1);
			int accelState = getAccelState(gAccelX,gAccelY,gAccelZ);
			// check for upside-down state first to avoid locking into backwards playback mode
			if(accelState == 5)	{
				gPlaysBackwards = 1;
			} else {
				gPlaysBackwards = 0;
				// only proceed if state has changed and getAccelState hasn't returned an exception
				if(accelState != gAccelState && accelState != -1)	{
					changePattern(accelState);
					//rt_printf("Changed to pattern %d\n",gAccelPatternMappings[accelState]);
					gAccelState = accelState;
				}
			}
		}
	}

	for(int n=0;n<numAudioFrames;n++)	{

		#if MASTER
			// half the sampling rate for analog output
			if(!(n%2))	{
				if(gIsPlaying)	{
					gMasterClock++;
					gClockReadPointer++;
				}
				// reset master clock every 4 beats
				if(!(gCurrentIndexInPattern%4) && !gClockReset)	{
					gMasterClock = 0;
					gClockReset = 1;
				} else if((gCurrentIndexInPattern%4) && gClockReset)	{
					gClockReset = 0;
				}
				// wrap gClockReadPointer
				if(gClockReadPointer >= CLOCK_BUFFER_SIZE)
					gClockReadPointer = 0;
				//float analogOut = 0;

				gAnalogOut = (float)gSampleCounter / (float)gEventIntervalSamples;

				gAnalogOut = fmod(gAnalogOut + 0.5,1);

				gClockBuffer[gClockReadPointer] = gAnalogOut;//gMasterClock;

			}
		// increment timer and trigger events
		if(gIsPlaying)	{
			if(++gSampleCounter >= gEventIntervalSamples)	{
				startNextEvent();
				gSampleCounter = 0;
			}
		}
		#endif

		#if SLAVE
			if(!(n%2))	{

				if(gIsPlaying)	{

					float clockValue = gClockInputBuffer[(gClockInputReadPointer-numMatrixFrames+(n/2)+CLOCK_BUFFER_SIZE)%CLOCK_BUFFER_SIZE];

					if(++gClockInputReadPointer >= CLOCK_BUFFER_SIZE)
						gClockInputReadPointer = 0;

					if(withinRange(clockValue,0.5,0.55) && !gEventTriggeredByClock)	{
						startNextEvent();
						gEventTriggeredByClock = 1;
					}
					if(clockValue >= 0.6 && gEventTriggeredByClock)
						gEventTriggeredByClock = 0;

					gLastClock = clockValue;

				}
			}
		#endif


		// start/stop playback when button is pressed
		if(gTriggerButton1)	{
			++gIsPlaying %= 2;
			gTriggerButton1 = 0;
		}

		// write active sample buffers into output buffer using read pointer array
		for(int ch=0;ch<gNumAudioChannels;ch++)	{
			float out = 0;
			// cycle through readPointers (voices)
			for(int p=0;p<NUM_VOICES;p++){
				// if readPointer is active then copy corresponding sampleBuffer content to output buffer
				if(gReadPointersState[p] == 1){
					if(gReadPointers[p] < gDrumSampleBufferLengths[gReadPointersBufferID[p]])	{
						if(!gPlaysBackwards)
							out += gDrumSampleBuffers[gReadPointersBufferID[p]][gReadPointers[p]]; // for stereo file use [gReadPointer*gNumAudioChannels+ch];
						else
							out += gDrumSampleBuffers[gReadPointersBufferID[p]]
							                          [gDrumSampleBufferLengths[gReadPointersBufferID[p]]-gReadPointers[p]+1];
					}
				}
			}

			// interleave output data from heavy and add to sampleBuffer output
			audioOut[n*gNumAudioChannels+ch] = out + gOutputBuffers[ch * numAudioFrames + n];;

		}

		// increment readPointers and check state
		for(int p=0;p<NUM_VOICES;p++)	{
			if(gReadPointers[p] <= gDrumSampleBufferLengths[gReadPointersBufferID[p]])
				gReadPointers[p]++;
			else
				gReadPointersState[p] = 0;
		}

	}

	#if MASTER
		for(int m=0;m<numMatrixFrames;m++)	{
			// 1. Change tempo using potentiometer
			float clockOut = (float)(gClockBuffer[(gClockReadPointer-numMatrixFrames+m+CLOCK_BUFFER_SIZE)%CLOCK_BUFFER_SIZE]);// / (float)(gEventIntervalSamples * 2);
			//clockOut = map(clockOut,0,1,0.25,0.75); // was 0.1-0.8
//			if(m==0)
//				rt_printf("%f\n",clockOut);
			matrixOut[m*8+gClockOutPin] = clockOut;
//			if(m==0)
//				rt_printf("output %f\n",clockOut);
			//if(m==0)
				//rt_printf("clockBuffer: %d %d\n",gClockBuffer[(gClockReadPointer-numMatrixFrames+m+CLOCK_BUFFER_SIZE)%CLOCK_BUFFER_SIZE],gEventIntervalSamples);
			//if(!(m%32))
			//rt_printf("%d\n",gClockBuffer[(gClockReadPointer-numMatrixFrames+m+CLOCK_BUFFER_SIZE)%CLOCK_BUFFER_SIZE]);
		}
	#endif


}

int withinRange(float value, float min, float max)	{
	return (value>=min && value<=max);
}

int getAccelState(float accelX, float accelY, float accelZ)	{

	// hysteresis thresholds for each state
	float thresholds[6];
	float lower = -0.2;
	float higher = 0.5;
	// +/- tolerance zone for neighbouring axis
	float tolerance = 0.3;

	for(int i=0;i<6;i++)	{
		if(gAccelState == i)
			thresholds[i] = lower;
		else
			thresholds[i] = higher;
	}

	if(withinRange(accelZ,-thresholds[5],1.0))	{
		if(accelX < -thresholds[1] && withinRange(accelY,-tolerance,tolerance))	{
			// tilt left
			return 1;
		} else if(accelX > thresholds[2] && withinRange(accelY,-tolerance,tolerance))	{
			// tilt right
			return 2;
		} else if(accelY < -thresholds[3] && withinRange(accelX,-tolerance,tolerance))	{
			// tilt back
			return 3;
		} else if(accelY > thresholds[4] && withinRange(accelX,-tolerance,tolerance))	{
			// tilt forward
			return 4;
		} else {
			// flat/upright -- no hysteresis for state 0
			return 0;
		}
	} else {
		// upside-down
		return 5;
	}

	return -1;

}

/* Start playing a particular drum sound given by drumIndex.
 */
int startPlayingDrum(int drumIndex) {
	for(int p=0;p<NUM_VOICES;p++){
		if(!gReadPointersState[p])	{
			gReadPointersState[p] = 1;
			gReadPointers[p] = 0;
			gReadPointersBufferID[p] = drumIndex;
			return 1;
		}
	}
	return 0;
}

int startPlayingSynth(int sIndex, int gate, int pitch) {

	// don't update pitch if its value is 0 (easier/quicker to compose patterns this way)
	if(pitch!=0)
		hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)sIndex+1,"pitch",(float)pitch);
	// 1 means sustain - ignore these notes
	if(gate!=1)	{
		if(sIndex==1)	{
		}
		// 3 means trigger automatic gate (within pd, trigger ON and after delay of attack time OFF)
		if(gate==3)
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsb",(float)sIndex+1,"trigger",0);
		// 2 means ON, 0 means OFF
		else if(gate==2 || gate==0)
			hv_vscheduleMessageForReceiver(gHeavyContext, "synthParams", 0.0, "fsf",(float)sIndex+1,"gate",(float)((gate==2)?1:0));
	}
	return 0;

}

int playSynths(int pattern, int pIndex)	{
	for(int s=0;s<NUM_SYNTHS;s++)	{
		int gate = (int)gSynthPatterns[pattern][(s*gPatternLengths[pattern]*2+gCurrentIndexInPattern*2+0)];
		int pitch = (int)gSynthPatterns[pattern][s*gPatternLengths[pattern]*2+gCurrentIndexInPattern*2+1];
		startPlayingSynth( s, gate, pitch );
	}
}


/* Start playing the next event in the pattern */
void startNextEvent() {
	int currentEvent = 0;
	if(gTriggerButton2 == 1){
		if(++gCurrentIndexInPattern>=gPatternLengths[gCurrentPattern])
			gCurrentIndexInPattern=0;
	}

	currentEvent = gPatterns[gCurrentPattern][gCurrentIndexInPattern];
	for(int d;d<NUMBER_OF_DRUMS;d++)	{
		if(eventContainsDrum(currentEvent,d))	{
			startPlayingDrum(d);
		}
	}
	playSynths(gCurrentPattern,gCurrentIndexInPattern);
	gEventJustTriggered = 1;
}

void changePattern(int patternID)	{
	gCurrentPattern = patternID;
	if(gPatternLengths[patternID] >= gCurrentIndexInPattern)
		gCurrentIndexInPattern %= gPatternLengths[patternID];
}

/* Returns whether the given event contains the given drum sound */
int eventContainsDrum(int event, int drum) {
	if(event & (1 << drum))
		return 1;
	return 0;
}

void cleanup_render()
{
	hv_beagleSequencer_free(gHeavyContext);
	if(gInputBuffers != NULL)
		free(gInputBuffers);
	if(gOutputBuffers != NULL)
		free(gOutputBuffers);
}
