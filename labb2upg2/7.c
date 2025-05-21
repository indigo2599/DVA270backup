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
#include <nrfx_rtc.h>   

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

// Funktion för att lägga till en anställd
void laggTillAnstalld(Anstalld** anstallda, int* antaletAnstallda, const char* namn, int fodelsear) {
    // Allokera minne för en ny anställd
    *anstallda = realloc(*anstallda, (*antaletAnstallda + 1) * sizeof(Anstalld));

    // Fyll i den nya anställdens information
    strcpy((*anstallda)[*antaletAnstallda].namn, namn);
    (*anstallda)[*antaletAnstallda].fodelsear = fodelsear;
    (*anstallda)[*antaletAnstallda].lon = 0;  // Initial lön är 0 kronor
    (*antaletAnstallda)++;
}


uint32_t get_rtc_counter_value() {
    return nrfx_rtc_counter_get(&instance);
}

// Funktion för att lägga till pengar till en anställds lön
void laggTillLon(Anstalld* anstalld, int pengar) {
    anstalld->lon += pengar;
}

// Funktion för att skriva ut alla anställdas information
void skrivUtAnstallda(Anstalld* anstallda, int antaletAnstallda) {
    for (int i = 0; i < antaletAnstallda; i++) {
        printf("Anställd: %s, Född: %d, Lön: %d kr\n", anstallda[i].namn, anstallda[i].fodelsear, anstallda[i].lon);
    }
}

// Funktion för att hitta en anställd baserat på namn
Anstalld* hittaAnstalld(Anstalld* anstallda, int antaletAnstallda, const char* namn) {
    for (int i = 0; i < antaletAnstallda; i++) {
        if (strcmp(anstallda[i].namn, namn) == 0) {
            return &anstallda[i];
        }
    }
    return NULL; // Om ingen anställd hittas
}
