#include <avr/io.h>
#ifndef SPILIB_H
#define SPILIB_h

// Initial the SPI as Master and define Prescaler fosc/prescaler
void initSpiMaster(unsigned int prescaler);

// Initial the SPI as slave
void initSpiSlave();

void SPI_mTrans(uint8_t data);
uint8_t SPI_mReceive();
void SPI_sTrans(uint8_t data);
uint8_t SPI_sReceive();

#endif