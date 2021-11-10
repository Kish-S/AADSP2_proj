#ifndef DISTORTION_H
#define DISTORTION_H

#include "common.h"

typedef struct
{
	int numChannels;
	int numSamples;
} distortion_state_t;


void processSingleChannel(double* input, double* output, distortion_state_t state);
#endif