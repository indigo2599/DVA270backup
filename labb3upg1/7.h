#ifndef GRUPP_7
#define GRUPP_7

#define PIN_TXD (20)
#define PIN_RXD (22)
#define LED_ON_TIME 200
#define CLEAR_SCREEN "\033c"

#define LED1 (28)
#define LED2 (29)
#define LED3 (30)
#define LED4 (31)



typedef struct Anstalld {
    char namn[100];
    int fodelsear;
    int lon; // Lön i kronor
} Anstalld;

int uarte_read_line(char *buffer, int max_len);
int read_int(void);
void send_int(int number);
void uarte_write(const char *data, int length);

#endif