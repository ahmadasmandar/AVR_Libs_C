/*
 * slaveSPI.c
 *
 * Created: 17.10.2020 21:29:32
 * Author : Ahmad Asmandar
 */

#include <avr/io.h>
#include "util/delay.h"
#include <stdio.h>
#include "USART.h"

#include "spilib.h"

char rec;

int main(void)
{
  initSpiSlave();
  initUSART();
  /* Replace with your application code */
  while (1)
  {
    rec = SPI_sReceive();
    transmitByte(rec);
    transmitByte('\r');
    transmitByte('\n');
    _delay_ms(50);
    SPI_sTrans('x');
    _delay_ms(50);
  }
}