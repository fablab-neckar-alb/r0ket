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
from `funk/nrf24l01p.c` after `nrf_init()`

name | address | content | explanation  
:--- | :---: | ---: | ---
R_CONFIG | 00 | 0b | Rx, power up, 1 byte CRC, enable CRC, all interrupts enabled
R_EN_AA | 01 | 00 | Disable auto acknowledgements 0-5
R_EN_RXADDR	| 02 | 03 | enable RxD pipes 0-1, disable 2-5
R_SETUP_AW | 03 | 03 | 5 bytes address width
R_SETUP_RETR | 04 | 03 | 1 ms auto retransmit delay
R_RF_CH | 05 | 02 | RF Channel 2002+2 MHz
R_RF_SETUP | 06 | 0e | 0 dBm Tx power, 2 Mbit data rate
R_STATUS | 07 | 0e | TxFIFO available, RxFIFOs empty, no interrupts
R_OBSERVE_TX | 08 | 00 | no lost or retried packets
R_RPD | 09 | 00 | no RxPower detected
R_RX_ADDR_P0 | 0a | e7e7e7e7e7 | RxD pipe 0 address
R_RX_ADDR_P1 | 0b | c2c2c2c2c2 | RxD pipe 1 address
R_RX_ADDR_P2 | 0c | c3 | LSB, RxD pipe 2
R_RX_ADDR_P3 | 0d | c4 | LSB, RxD pipe 3
R_RX_ADDR_P4 | 0e | c5 | LSB, RxD pipe 4
R_RX_ADDR_P5 | 0f | c6 | LSB, RxD pipe 5
R_TX_ADDR | 10 | e7e7e7e7e7 | TxD pipe address
R_RX_PW_P0 | 11 | 00 | payload bytes in RxD pipe 0
R_RX_PW_P1 | 12 | 00 | payload bytes in RxD pipe 1
R_RX_PW_P2 | 13 | 00 | payload bytes in RxD pipe 2
R_RX_PW_P3 | 14 | 00 | payload bytes in RxD pipe 3
R_RX_PW_P4 | 15 | 00 | payload bytes in RxD pipe 4
R_RX_PW_P5 | 16 | 00 | payload bytes in RxD pipe 5
R_FIFO_STATUS | 17 | 11 | RxFIFOs empty, TxFIFOs empty
R_DYNPD | 1c | 00 | dynamic payload lenghts disabled
R_FEATURE | 1d | 00 | no features enabled

##micro:bit compatibility mode
###Generic radio setup
name | address | content | explanation  
:--- | :---: | ---: | ---
R_CONFIG | 00 | 0f | Rx, power up, 2 byte CRC, enable CRC, all interrupts enabled
R_EN_AA | 01 | 00
R_EN_RXADDR | 02 | 03
R_SETUP_AW | 03 | 03
R_SETUP_RETR | 04 | 03
R_RF_CH | 05 | 02
R_RF_SETUP | 06 | 06 | 0 dBm Tx power, 1 Mbit data rate
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

###Configured radio setup
name | address | content | explanation  
:--- | :---: | ---: | ---
R_CONFIG | 00 | 0f
R_EN_AA | 01 | 00
R_EN_RXADDR | 02 | 01
R_SETUP_AW | 03 | 03
R_SETUP_RETR | 04 | 03
R_RF_CH | 05 | 07 | channel 7 (2.409 GHz)
R_RF_SETUP | 06 | 06
R_STATUS | 07 | 0e
R_OBSERVE_TX | 08 | 00
R_RPD | 09 | 00
R_RX_ADDR_P0 | 0a | 0074696275
R_RX_ADDR_P1 | 0b | c2c2c2c2c2
R_RX_ADDR_P2 | 0c | c3
R_RX_ADDR_P3 | 0d | c4
R_RX_ADDR_P4 | 0e | c5
R_RX_ADDR_P5 | 0f | c6
R_TX_ADDR | 10 | 0074696275
R_RX_PW_P0 | 11 | 20
R_RX_PW_P1 | 12 | 00
R_RX_PW_P2 | 13 | 00
R_RX_PW_P3 | 14 | 00
R_RX_PW_P4 | 15 | 00
R_RX_PW_P5 | 16 | 00
R_FIFO_STATUS | 17 | 11
R_DYNPD | 1c | 00
R_FEATURE | 1d | 00
