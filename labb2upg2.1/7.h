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

#define BUTTON1 23
#define BUTTON2 24
#define BUTTON3 8
#define BUTTON4 9

#define LED_OFF 1
#define LED_ON 0 




int uarte_read_line(char *buffer, int max_len);
int read_int(void);
void send_int(int number);
void uarte_write(const char *data, int length);


#endif