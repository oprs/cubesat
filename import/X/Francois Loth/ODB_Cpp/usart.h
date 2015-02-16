#include <stm32f4xx_spi.h>


void initialiserUSART1();
void initialiserUSART2();
void initialiserUSART3();
void initialiserUSART6();
void enableUSART1();

void envoyerDataUSART1(uint8_t data);
void envoyerDataUSART2(uint8_t data);
void envoyerDataUSART3(uint8_t data);
void envoyerDataUSART6(uint8_t data);

void envoyerDataDecimalUSART1(uint8_t data);
void envoyerDataDecimalUSART2(uint8_t data);
void envoyerDataDecimalUSART3(uint8_t data);
void envoyerDataDecimalUSART6(uint8_t data);

void envoyerDataHexaUSART1(uint8_t data);
void envoyerDataHexaUSART2(uint8_t data);
void envoyerDataHexaUSART3(uint8_t data);
void envoyerDataHexaUSART6(uint8_t data);
void USART_puts(char *s);
