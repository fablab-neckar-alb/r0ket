#nRF24L01 radio

##Capabilities
  * .25, 1, and 2Mbps data rates
  * Enhanced ShockBurst™ can handle up to 32 bytes payload
  * 1:6 star networks

##Connections to LPC1343
pin 1 CE to 45 PIO1.5/RTS/CT32B0_CAP0  
pin 2 CSN to 30 PIO1.10/AD6/CT16B1_MAT1, pull-up to +3V3_RF  
pin 3 SCK to 31 PIO2.11/SCK SCK  
pin 4 MOSI to 28 PIO0.9/MOSI/CT1B0_MAT1  
pin 5 MISO to 27 PIO0.8/MISO/CT1B0_MAT0  
pin 6 IRQ to 23 PIO0.7/CTS  

##Find the appropriate abstraction level
It's probably easier to start to communicate between sino:bits and the calliope-mini,
because they use identical libraries.  
Afterwards, try to receive their data packets with the r0ket, and eventually send a packet back.  


