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


/* Needed to made usleep declaration visible with C99 */
#define _BSD_SOURCE

#include "../include/render.h"
#include "../include/Utilities.h"
#include "drums.h"
#include <cstdio>
#include <rtdk.h>
#include <pthread.h>
#include <unistd.h>
#include "SimpleGPIO.h"

extern int gShouldStop;	/* Main code sets this to true when finished */
extern int gEventJustTriggered;

int gInputPin1 = 69;
int gInputPin2 = 68;
int gLedPin = 67;

int gTriggerButton1 = 0;	/* Triggers that can be sent to audio code from buttons */
int gTriggerButton2 = 0;

int gTriggerButton1_last = 0;
int gTriggerButton2_last = 0;

int gLedState = 0;

int gIsPlaying = 0;			/* Whether we should play or not. Implement this in Step 4b. */

/* Main function for thread which reads GPIO data.
 * This function will run on its own
 * thread and will run as long as the audio is running.
 * It should be used to gather data from buttons and
 * send values to the LEDs.
 */
void *gpioLoop(void *data) {

	// Initialise GPIO pins
	if(gpio_export(gInputPin1) || gpio_export(gInputPin2) || gpio_export(gLedPin)) {
		printf("Unable to export GPIO input pin\n");
	}
	if(gpio_set_dir(gInputPin1, INPUT_PIN) || gpio_set_dir(gInputPin2, INPUT_PIN) || gpio_set_dir(gLedPin, OUTPUT_PIN)) {
		printf("Unable to set GPIO input direction\n");
	}

	unsigned int latestValue1;
	unsigned int latestValue2;

	while(!gShouldStop) {

		gpio_get_value(gInputPin1, &latestValue1);
		gpio_get_value(gInputPin2, &latestValue2);

		if(latestValue1 == 1 && gTriggerButton1_last == 0)	{
			gTriggerButton1 = 1;
		}
		if(latestValue2 == 1 && gTriggerButton2_last == 0)	{
			gTriggerButton2 = 1;
		}

		// set LED on/off each time event is triggered
		if(gEventJustTriggered)	{
			gEventJustTriggered = 0;
			gLedState = (gLedState)?0:1;
		}

		gTriggerButton1_last = latestValue1;
		gTriggerButton2_last = latestValue2;

		gpio_set_value(gLedPin, gLedState);

		usleep(1000);	/* Wait 1ms to avoid checking too quickly */
	}

	if(gpio_unexport(gInputPin1) || gpio_unexport(gInputPin2) || gpio_unexport(gLedPin)) {
		printf("Warning: unable to unexport GPIO input pin\n");
	}

	pthread_exit(NULL); /* Don't change this */
}
