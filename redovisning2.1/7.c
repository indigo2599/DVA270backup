#include <nrfx.h>
#include <nrf5340_application.h>
#include <nrfx_config.h>
#include <nrf.h>
#include <nrf_gpio.h>
#include <nrfx_uarte.h>
#include <nrfx_systick.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <7.h>



#define MAX_LEN 20

static nrfx_uarte_t instance = NRFX_UARTE_INSTANCE(0);
static uint8_t uarte_buffer;

void uarte_write(const char *data, int length)
{
    nrfx_uarte_tx(&instance, (const uint8_t *)data, length, 0);
}

int uarte_read_line(char *buffer, int max_len)
{
    int index = 0;

    while (index < max_len - 1)
    {
        
        nrfx_err_t err_code = nrfx_uarte_rx(&instance, &uarte_buffer, sizeof(uarte_buffer));
        if (err_code != NRFX_SUCCESS)
        {
            break;
        }

        if (uarte_buffer == '\r' || uarte_buffer == '\n')
        {
            break;
        }
        buffer[index++] = (char)uarte_buffer;
    }
    buffer[index] = '\0';
    return index;
}

int read_int(void)
{
    char buffer[MAX_LEN];
    uarte_read_line(buffer, MAX_LEN);
    return atoi(buffer);
}

void send_int(int number)
{
    char buffer[MAX_LEN];
    sprintf(buffer, "%d", number);
    uarte_write(buffer, strlen(buffer));
}


