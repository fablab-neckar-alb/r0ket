#include <sysinit.h>
#include <funk/nrf24l01p.h>
#include <basic/basic.h>
#include <core/ssp/ssp.h>
#include <usbcdc/util.h>
#include <lcd/render.h>


struct NRF_CFG ubitconfig= {
    .channel= 7,
    .txmac= {'u','b','i','t',0},
    .nrmacs= 1,
    .mac0= {'u','b','i','t',0},
    .maclen= {32,0,0,0,0}
};

/*-----------------------------------------------------------------------*/
/* Transmit a byte via SPI                                               */
/*-----------------------------------------------------------------------*/

inline void xmit_spi(uint8_t dat) {
    sspSend(0, (uint8_t*) &dat, 1);
}

inline void rcv_spi(uint8_t *dat) {
    sspReceive(0, dat, 1);
}

#define CS_LOW()    gpioSetValue(RB_SPI_NRF_CS, 0)
#define CS_HIGH()   gpioSetValue(RB_SPI_NRF_CS, 1)
#define CE_LOW()    gpioSetValue(RB_NRF_CE, 0)
#define CE_HIGH()   gpioSetValue(RB_NRF_CE, 1)

void nrf_setup() {
    // Enable SPI correctly
    sspInit(0, sspClockPolarity_Low, sspClockPhase_RisingEdge);

    // Enable CS & CE pins
    gpioSetDir(RB_SPI_NRF_CS, gpioDirection_Output);
    gpioSetPullup(&RB_SPI_NRF_CS_IO, gpioPullupMode_Inactive);
    gpioSetDir(RB_NRF_CE, gpioDirection_Output);
    gpioSetPullup(&RB_NRF_CE_IO, gpioPullupMode_PullUp);
    CE_LOW();

    // Setup for nrf24l01+
    // power up takes 1.5ms - 3.5ms (depending on crystal)
    CS_LOW();
    nrf_write_reg(R_CONFIG,
            R_CONFIG_PRIM_RX| // Receive mode
            R_CONFIG_PWR_UP|  // Power on
            R_CONFIG_EN_CRC|R_CONFIG_CRCO // CRC on, double byte
            );
    
    nrf_write_reg(R_EN_AA, 0); // Disable Enhanced ShockBurst;

    // Set speed / strength
    nrf_write_reg(R_RF_SETUP,R_RF_SETUP_DR_1M|R_RF_SETUP_RF_PWR_3);

    // Clear MAX_RT, just in case.
    nrf_write_reg(R_STATUS,R_STATUS_MAX_RT);
}


void putreg(uint8_t reg, const char *name)
{
    uint8_t contents= nrf_read_reg(reg);
    printf("%s %02x: %02x\r\n", name, reg, contents);
}

void putlongreg(uint8_t reg, uint8_t bytes, char *name)
{
    uint8_t contents[bytes];
    nrf_read_long(reg, bytes, contents);
    printf("%s %02x: ", name, reg);
    while (0 < bytes--)
        printf("%02x", contents[bytes]);
    printf("\r\n");
}

void dumpRadioRegisters(void)
{
    putreg(R_CONFIG, "R_CONFIG\t");
    putreg(R_EN_AA, "R_EN_AA   \t");
    putreg(R_EN_RXADDR, "R_EN_RXADDR\t");
    putreg(R_SETUP_AW, "R_SETUP_AW\t");
    putreg(R_SETUP_RETR, "R_SETUP_RETR\t");
    putreg(R_RF_CH, "R_RF_CH   \t");
    putreg(R_RF_SETUP, "R_RF_SETUP\t");
    putreg(R_STATUS, "R_STATUS\t");
    putreg(R_OBSERVE_TX, "R_OBSERVE_TX\t");
    putreg(R_RPD, "R_RPD   \t");
    putlongreg(R_RX_ADDR_P0, 5, "R_RX_ADDR_P0\t");
    putlongreg(R_RX_ADDR_P1, 5, "R_RX_ADDR_P1\t");
    putreg(R_RX_ADDR_P2, "R_RX_ADDR_P2\t");
    putreg(R_RX_ADDR_P3, "R_RX_ADDR_P3\t");
    putreg(R_RX_ADDR_P4, "R_RX_ADDR_P4\t");
    putreg(R_RX_ADDR_P5, "R_RX_ADDR_P5\t");
    putlongreg(R_TX_ADDR, 5, "R_TX_ADDR\t");
    putreg(R_RX_PW_P0, "R_RX_PW_P0\t");
    putreg(R_RX_PW_P1, "R_RX_PW_P1\t");
    putreg(R_RX_PW_P2, "R_RX_PW_P2\t");
    putreg(R_RX_PW_P3, "R_RX_PW_P3\t");
    putreg(R_RX_PW_P4, "R_RX_PW_P4\t");
    putreg(R_RX_PW_P5, "R_RX_PW_P5\t");
    putreg(R_FIFO_STATUS, "R_FIFO_STATUS\t");
    putreg(R_DYNPD, "R_DYNPD    \t");
    putreg(R_FEATURE, "R_FEATURE\t");
}

void main_radiotest(void)
{
    static int count= 0;

    gpioSetValue(RB_LED0, 0);
    gpioSetValue(RB_LED1, 0);
    gpioSetValue(RB_LED2, 0);

    usbCDCInit();

    nrf_setup();

    while (BTN_RIGHT != getInputRaw());

    printf("Generic radio setup\r\n");
    dumpRadioRegisters();

    nrf_config_set(&ubitconfig);

    printf("Configured radio setup\r\n");
    dumpRadioRegisters();

    DoString(12,20,"radio test");
    lcdDisplay();
 considered_harmful:
    while (BTN_ENTER != getInputRaw());

    gpioSetValue(RB_LED0, 1);
    gpioSetValue(RB_LED1, 1);
    gpioSetValue(RB_LED2, 1);
    
    printf("dump #%08x\r\n", count++);
    dumpRadioRegisters();
    delayms(100);

    gpioSetValue(RB_LED0, 0);
    gpioSetValue(RB_LED1, 0);
    gpioSetValue(RB_LED2, 0);

    goto considered_harmful;
}
