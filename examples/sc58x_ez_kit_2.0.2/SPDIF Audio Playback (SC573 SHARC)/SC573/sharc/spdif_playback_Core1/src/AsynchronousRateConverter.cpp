/*
 * AsynchronousRateConverter.cpp
 *
 *  Created on: 8 apr. 2018
 *      Author: more10
 */

#include "AsynchronousRateConverter.h"
#include "../../../../spdif_playback.h"
#include <stdio.h>
#include <stdlib.h>

uint8_t AsynchronousRateConverter::AsrcMemory0[ADI_ASRC_MEMORY_SIZE];
ADI_ASRC_HANDLE AsynchronousRateConverter::phAsrc0;
/* ASRC SPORT configuration */
uint8_t AsynchronousRateConverter::OpAsrcSportMemory[ADI_SPORT_DMA_MEMORY_SIZE];
ADI_ASRC_SPORT_CONFIG AsynchronousRateConverter::OpAsrcSportConfig;


AsynchronousRateConverter::AsynchronousRateConverter(ADI_CALLBACK callback) {
    /* Open ASRC 0 */
	ADI_ASRC_RESULT result = adi_asrc_Open(0u,
    				  0u,
                      &AsrcMemory0[0],
                      ADI_ASRC_MEMORY_SIZE,
                      &phAsrc0);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);

    result = adi_asrc_SetSerialFormat(phAsrc0, ADI_ASRC_INPUT_I2S, ADI_ASRC_OUTPUT_I2S, ADI_ASRC_WORD_LENGTH_24);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);

    /* configure SPORT, this will handle Asrc0 */
    OpAsrcSportConfig.SportDevNum		= 0u;
    OpAsrcSportConfig.pSportDevMem 	    = &OpAsrcSportMemory[0u];
    OpAsrcSportConfig.SportDevMemSize 	= ADI_SPORT_DMA_MEMORY_SIZE;
    OpAsrcSportConfig.bLsbFirst			= false;
    OpAsrcSportConfig.bPack   			= false;
    OpAsrcSportConfig.bSecondaryEnabled	= false;
    OpAsrcSportConfig.eSportChnl		= ADI_ASRC_SPORT_A;

    /* Configure input ASRC sport channel */
    result = adi_asrc_OpConfigSport(phAsrc0, &OpAsrcSportConfig);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);

    /* Register output Sport callback */
    result = adi_asrc_OpRegisterSportCallback(phAsrc0, callback, NULL);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);
}

AsynchronousRateConverter::~AsynchronousRateConverter() {
	// TODO Auto-generated destructor stub
}

void AsynchronousRateConverter::Enable() {
	ADI_ASRC_RESULT result = adi_asrc_Enable(phAsrc0, true);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);
}

void AsynchronousRateConverter::Disable() {
	ADI_ASRC_RESULT result = adi_asrc_Enable(phAsrc0, false);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);
}

void AsynchronousRateConverter::Close() {
	ADI_ASRC_RESULT result = adi_asrc_Close(phAsrc0);
	CheckAsrcResult(ADI_ASRC_SUCCESS, result);
}

void AsynchronousRateConverter::CheckAsrcResult(ADI_ASRC_RESULT expected, ADI_ASRC_RESULT result)
{
	if ( result != expected )
	{
		char message[96];
		sprintf(message, "AsynchronousRateConverter::CheckAsrcResult expected(%d) != result(%d)", expected, result);
		perror(message);
		abort();
	}
}
