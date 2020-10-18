/*
 * masterSPI.c
 *
 * Created: 17.10.2020 21:29:32
 * Author : Ahmad Asmandar
 */

#include <avr/io.h>
#include "USART.h"
// #define F_CPU 8000000L
#include "spilib.h"
#include <avr/io.h>
#include "util/delay.h"
char rec;
int main(void)
{
  // DDRC |= (1 << PC0) | (1 << PC1) | (1 << PC2);
  // PORTC = (1 << PC0) | (1 << PC1) | ~(1 << PC2);
  initSpiMaster(2);

  while (1)
  {
    initUSART();
    SPI_mTrans('H');
    _delay_ms(1000);
    rec = SPI_mReceive();
    transmitByte(rec);
    transmitByte('\r');
    transmitByte('\n');
    _delay_ms(150);
  }
}
