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

    nrf_init();

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
