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


#ifndef _DRUMS_H
#define _DRUMS_H

#define NUMBER_OF_DRUMS 8
#define NUMBER_OF_PATTERNS 6
#define FILL_PATTERN 5

/* Start playing a particular drum sound */
int startPlayingDrum(int drumIndex);

/* Start playing the next event in the pattern */
void startNextEvent();

//change pattern
void changePattern(int patternID);

/* Returns whether the given event contains the given drum sound */
int eventContainsDrum(int event, int drum);

int getAccelState(float gAccelX, float gAccelY, float gAccelZ);

int withinRange(float value, float min, float max);

#endif /* _DRUMS_H */
