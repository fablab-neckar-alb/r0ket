#include <sysinit.h>
#include <funk/nrf24l01p.h>

#include "usetable.h"

struct NRF_CFG config = {
    .channel= 81,
    .txmac= "\x1\x2\x3\x2\x1",
    .nrmacs=1,
    .mac0=  "\x1\x2\x3\x2\x1",
    .maclen ="\x20",
};

void ram(void)
{
    nrf_config_set(&config);
}
