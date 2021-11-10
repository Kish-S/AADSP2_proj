
#include "distortion.h"
#include "processing.h"
#include <math.h>

#define MAX_NUM_OUT_CH		6
#define MAX_NUM_IN_CH		2
#define MAX_NUM_OUT_MODE	6

// Index of channels
#define Ls		0
#define L		1
#define C       2
#define R		3
#define Rs		4
#define LFE		5

#define Lin		0
#define Rin		1

static const int outputChMask[MAX_NUM_OUT_MODE][MAX_NUM_OUT_CH] =
{
	//Ls L  C  R  Rs LFE
	{ 0, 1, 0, 1, 0, 0 },	//2.0.0 (stereo) 
	{ 1, 1, 1, 1, 1, 0 },	//3.2.0 
	{ 1, 1, 1, 1, 1, 1 },	//3.2.1
	{ 0, 1, 0, 1, 0, 1 }	//2.0.1
};

int get_out_num_ch(int mode)
{
	int ret = 0;
	int i;
	for ( i = 0; i < MAX_NUM_OUT_CH; i++)
	{
		ret += outputChMask[mode][i];
	}

	return ret;
}

int is_channel_active(int mode, int channel)
{
	return outputChMask[mode][channel];
}


/////////////////////////////////////////////////////////////////////////////////
// @Author	<student name>
// @Date		<date>  
//
// Function:
// multitap_echo
//
// @param - input - Buffer with input samples
//		  - output - Buffer with output samples
//		  - echo_state - Control state structure
//		  - mode - selected output mode
//
// @return - nothing
// Comment: Apply multichannel processing to input samples
//
// E-mail:	<email>
//
/////////////////////////////////////////////////////////////////////////////////
void processing(double input[][BLOCK_SIZE], double output[][BLOCK_SIZE], int mode, int enable)
{
	double inputGain    = pow(10.0, -6/20.0);
	double headroomGain = pow(10.0, -6/20.0);
	double lGain        = pow(10.0, -3/20.0);
	double rGain		= pow(10.0, -4/20.0);
	double rsGain		= pow(10.0, -1/20.0);
	double lsGain		= pow(10.0, -1/20.0);
	int i;
	if (enable == 1)
	{
		if (mode == OM_2_0_0)
		{
			
			for (i = 0; i < BLOCK_SIZE; i++)
			{
				double headroomOut = (inputGain * input[Lin][i] + inputGain * input[Rin][i]) * headroomGain;
				output[R][i] = headroomOut * rGain;
				output[L][i] = headroomOut * lGain;
			}

		}
		else if (mode == OM_2_0_1)
		{
			distortion_state_t state;
			state.numChannels = 3;
			state.numSamples = BLOCK_SIZE;
			for (i = 0; i < BLOCK_SIZE; i++)
			{
				double headroomOut = (inputGain * input[Lin][i] + inputGain * input[Rin][i]) * headroomGain;
				output[LFE][i] = headroomOut;
			}
			processSingleChannel(output[LFE], output[LFE], state);
		}
	}
	

}
