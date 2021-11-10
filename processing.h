#ifndef PROCESSING_H
#define PROCESSING_H

#include "common.h"
#include "distortion.h"

#if __cplusplus
extern "C" {
#endif

enum ENABLE
{
	ON = 1,
	OFF = 0
};

enum OUTPUT_MODES
{
	OM_2_0_0 = 0,
	OM_3_2_0 = 1,
	OM_3_2_1 = 2,
	OM_2_0_1 = 3
};

int get_out_num_ch(int mode);

int is_channel_active(int mode, int channel);

void processing(double input[][BLOCK_SIZE], double output[][BLOCK_SIZE], int mode, int enable);

#if __cplusplus
}
#endif

#endif // !PROCESSING_H
