/*
 * AsynchronousRateConverter.h
 *
 *  Created on: 8 apr. 2018
 *      Author: more10
 */

#ifndef ASYNCHRONOUSRATECONVERTER_H_
#define ASYNCHRONOUSRATECONVERTER_H_

#include <drivers/asrc/adi_asrc.h>

class AsynchronousRateConverter {
private:
	static uint8_t AsrcMemory0[ADI_ASRC_MEMORY_SIZE];
	/* ASRC SPORT configuration */
	static uint8_t OpAsrcSportMemory[ADI_SPORT_DMA_MEMORY_SIZE];
	static ADI_ASRC_SPORT_CONFIG OpAsrcSportConfig;
public:
	AsynchronousRateConverter();
	virtual ~AsynchronousRateConverter();
	void AsrcSubmitBuffers(void);
	void Enable();
	void Disable();
	void Close();
	static void CheckAsrcResult(ADI_ASRC_RESULT expected, ADI_ASRC_RESULT result);
	static ADI_ASRC_HANDLE phAsrc0;
	/* Counter to keep track of number of ADC buffers processed */
	static volatile uint32_t AsrcCount;
};

#endif /* ASYNCHRONOUSRATECONVERTER_H_ */