#include "spilib.h"
#include <avr/io.h>

#define SPI_DDR DDRB
#define CS PINB2
#define MOSI PINB3
#define MISO PINB4
#define SCK PINB5

// Initial the SPI as Master and define Prescaler fosc/prescaler
void initSpiMaster(unsigned int prescaler)
{
      /* Set MOSI , SCK and SS output, all others input */
      SPI_DDR |= (1 << CS) | (1 << MOSI) | (1 << SCK);
      /* Enable SPI, Master*/
      SPCR = (1 << SPE) | (1 << MSTR);

      // set clock rate fck/128
      switch (prescaler)
      {
            // fosc/4
      case 4:
            break;
            // fosc/16
      case 16:
            SPCR |= (1 << SPR0);
            break;
            // fosc/64
      case 64:
            SPCR |= (1 << SPR1);
            break;
            // fosc/128
      case 128:
            SPCR |= (1 << SPR1) | (1 << SPR0);
            break;
            // fosc/2
      case 2:
            SPSR = (1 << SPI2X);
            break;
            // fosc/8
      case 8:
            SPCR |= (1 << SPR0);
            SPSR = (1 << SPI2X);
            break;
            // fosc/32
      case 32:
            SPCR |= (1 << SPR1);
            SPSR = (1 << SPI2X);
            break;
      default:
            // fosc/4
            break;

            // case 64:duplicate
            //       SPCR = (1 << SPR1) | (1 << SPR0);
            //       SPSR = (1 << SPI2X);
            break;
      }
}

// Initial the SPI as slave
void initSpiSlave()
{
      /* Set MISO output, all others input */
      SPI_DDR = (1 << MISO);
      /* Enable SPI */
      SPCR = (1 << SPE);
}

//Transmit Master; Transmitting a byte as the SPI master

void SPI_mTrans(uint8_t data)
{
      // load data into register
      SPDR = data;

      // Wait for transmission complete
      while (!(SPSR & (1 << SPIF)))
            ;
}

//Receiving Master; Receivingting a byte as the SPI master
uint8_t SPI_mReceive()
{
      // transmit dummy byte
      SPDR = 0xFF;

      // Wait for reception complete
      while (!(SPSR & (1 << SPIF)))
            ;
      // return Data Register
      return SPDR;
}

//Transmit Slave; Transmitting a byte as the SPI Slave

void SPI_sTrans(uint8_t data)
{
      // load data into register and wait for the Dummy Byte from the master to allow the send
      SPDR = data;

      // Wait for transmission complete
      while (!(SPSR & (1 << SPIF)))
            ;
}

//Receiving slave; Receivingting a byte as the SPI slave
uint8_t SPI_sReceive()
{

      // Wait for reception complete
      while (!(SPSR & (1 << SPIF)))
            ;
      // return Data Register
      return SPDR;
}