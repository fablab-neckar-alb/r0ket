#nRF24L01 radio

##Capabilities
  * .25, 1, and 2Mbps data rates
  * Enhanced ShockBurst™ can handle up to 32 bytes payload
  * 1:6 star networks

##Connections to LPC1343
nRF24L01+ pin | name | LPC1343 pin | name | comment
:---: | :---: | :---: | :---: | :---:
 1 | CE | 45 | PIO1.5/RTS/CT32B0_CAP0
 2 | CSN | 30 | PIO1.10/AD6/CT16B1_MAT1 | pull-up to +3V3_RF
 3 | SCK | 31 | PIO2.11/SCK SCK
 4 | MOSI | 28 | PIO0.9/MOSI/CT1B0_MAT1
 5 | MISO | 27 | PIO0.8/MISO/CT1B0_MAT0
 6 | IRQ | 23 | PIO0.7/CTS

##Find the appropriate abstraction level
It's probably easier to start to communicate between sino:bits and the calliope-mini,
because they use identical libraries.  
Afterwards, try to receive their data packets with the r0ket, and eventually send a packet back.  

##Default register setup
from `funk/nrf24l01p.c`

name | address | content  
:--- | :---: | ---:
R_CONFIG | 00 | 0b
R_EN_AA | 01 | 00
R_EN_RXADDR	| 02 | 03
R_SETUP_AW | 03 | 03
R_SETUP_RETR | 04 | 03
R_RF_CH | 05 | 02
R_RF_SETUP | 06 | 0e
R_STATUS | 07 | 0e
R_OBSERVE_TX | 08 | 00
R_RPD | 09 | 00
R_RX_ADDR_P0 | 0a | e7e7e7e7e7
R_RX_ADDR_P1 | 0b | c2c2c2c2c2
R_RX_ADDR_P2 | 0c | c3
R_RX_ADDR_P3 | 0d | c4
R_RX_ADDR_P4 | 0e | c5
R_RX_ADDR_P5 | 0f | c6
R_TX_ADDR | 10 | e7e7e7e7e7
R_RX_PW_P0 | 11 | 00
R_RX_PW_P1 | 12 | 00
R_RX_PW_P2 | 13 | 00
R_RX_PW_P3 | 14 | 00
R_RX_PW_P4 | 15 | 00
R_RX_PW_P5 | 16 | 00
R_FIFO_STATUS | 17 | 11
R_DYNPD | 1c | 00
R_FEATURE | 1d | 00

