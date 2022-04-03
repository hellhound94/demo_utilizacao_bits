/*
* Autor: Abner Cordeiro - 30/03/2022
* 
* Relembrando utilização de operadores bit a bit.
* São exatamente 20:59 estou o dia inteiro sem internet
* então estou brincando com isso, espero que seja útil para alguém, algum dia, por algum motivo....
* 
* Manipulando bits de duas formas.
*	1ª -> com operadores bit a bit.
*   2ª -> com campos de bits
* 
*/

#include <stdio.h>

/*********************************************************************************************************************/
/* Tudo está em bit e não hexadecimal para facilitar a visualização													 */		
#define B7 0b10000000
#define B6 0b01000000
#define B5 0b00100000
#define B4 0b00010000
#define B3 0b00001000
#define B2 0b00000100
#define B1 0b00000010
#define B0 0b00000001

void print_bin(unsigned char ucByte)
{
	unsigned char ucFlag = 0b10000000;

	for (int iCount = 0; iCount < 8; iCount++, ucFlag >>= 1)
	{
		printf((ucByte & ucFlag) ? "1"  : "0");
	}
	printf("\n");
}

void set_bit(unsigned char *ucByte, unsigned char ucBit)
{
	*ucByte |= ucBit;
}

void zero_bit(unsigned char* ucByte, unsigned char ucBit)
{
	*ucByte = ~*ucByte;
	set_bit(ucByte, ucBit);
	*ucByte = ~*ucByte;
}

void invert_bit(unsigned char* ucByte, unsigned char ucBit)
{
	(*ucByte & ucBit) ? zero_bit(ucByte, ucBit) : set_bit(ucByte, ucBit);
}

void bit_a_bit()
{
	unsigned char ucTest = 0b10100110;

	print_bin(ucTest);

	set_bit(&ucTest, B0);
	print_bin(ucTest);

	zero_bit(&ucTest, B5);
	print_bin(ucTest);

	zero_bit(&ucTest, B0);
	print_bin(ucTest);

	invert_bit(&ucTest, B7);
	print_bin(ucTest);

	invert_bit(&ucTest, B7);
	print_bin(ucTest);

	invert_bit(&ucTest, B7);
	print_bin(ucTest);

	invert_bit(&ucTest, B7);
	print_bin(ucTest);
}

/*******************************************************************************************************************/

/* simulando um GPIO */
typedef struct tagGPIO_FAKE {
	unsigned char ucPIN7 : 1;
	unsigned char ucPIN6 : 1;
	unsigned char ucPIN5 : 1;
	unsigned char ucPIN4 : 1;
	unsigned char ucPIN3 : 1;
	unsigned char ucPIN2 : 1;
	unsigned char ucPIN1 : 1;
	unsigned char ucPIN0 : 1;
}GPIO_FAKE, *PGPIO_FAKE;


void struct_to_byte(GPIO_FAKE gpIO, unsigned char *pucByte)
{
	(gpIO.ucPIN0) ? set_bit(pucByte, B0) : zero_bit(pucByte, B0);
	(gpIO.ucPIN1) ? set_bit(pucByte, B1) : zero_bit(pucByte, B1);
	(gpIO.ucPIN2) ? set_bit(pucByte, B2) : zero_bit(pucByte, B2);
	(gpIO.ucPIN3) ? set_bit(pucByte, B3) : zero_bit(pucByte, B3);
	(gpIO.ucPIN4) ? set_bit(pucByte, B4) : zero_bit(pucByte, B4);
	(gpIO.ucPIN5) ? set_bit(pucByte, B5) : zero_bit(pucByte, B5);
	(gpIO.ucPIN6) ? set_bit(pucByte, B6) : zero_bit(pucByte, B6);
	(gpIO.ucPIN7) ? set_bit(pucByte, B7) : zero_bit(pucByte, B7);
}

/* Não sei se essa é a melhor forma, mas aparentemente está funcionando... */
void byte_to_struct(unsigned char ucByte, PGPIO_FAKE pgpIO)
{
	pgpIO->ucPIN0 = ((ucByte & B0) == B0) ? 1 : 0;
	pgpIO->ucPIN1 = ((ucByte & B1) == B1) ? 1 : 0;
	pgpIO->ucPIN2 = ((ucByte & B2) == B2) ? 1 : 0;
	pgpIO->ucPIN3 = ((ucByte & B3) == B3) ? 1 : 0;
	pgpIO->ucPIN4 = ((ucByte & B4) == B4) ? 1 : 0;
	pgpIO->ucPIN5 = ((ucByte & B5) == B5) ? 1 : 0;
	pgpIO->ucPIN6 = ((ucByte & B6) == B6) ? 1 : 0;
	pgpIO->ucPIN7 = ((ucByte & B7) == B7) ? 1 : 0;
}

void campos_de_bits()
{
	/* Uma maneira de iniciar uma struct */
	GPIO_FAKE My_GPIO =
	{
		.ucPIN7 = 0,
		.ucPIN6 = 0,
		.ucPIN5 = 0,
		.ucPIN4 = 0,
		.ucPIN3 = 0,
		.ucPIN2 = 0,
		.ucPIN1 = 0,
		.ucPIN0 = 0
	};

	/* Outra maneira de iniciar uma struct */
	GPIO_FAKE My_GPIO2 = { 0, 0, 0, 0, 0, 0, 0, 0 };

	My_GPIO.ucPIN0 = 1;
	My_GPIO.ucPIN6 = 1;

	printf("My_GPIO = %d %d %d %d %d %d %d %d\n", My_GPIO.ucPIN7, My_GPIO.ucPIN6, My_GPIO.ucPIN5, My_GPIO.ucPIN4, My_GPIO.ucPIN3, My_GPIO.ucPIN2, My_GPIO.ucPIN1, My_GPIO.ucPIN0);

	unsigned char ucConvert = 0x00;

	/*			Convertendo de GPIO_FAKE para unsigned char  				*/
	struct_to_byte(My_GPIO, &ucConvert);
	/*							FIM CONVERSÃO								*/
	printf("de My_GPIO para unsigned char ucConvert = ");
	print_bin(ucConvert);
	printf("\n\n");

	/*			Convertendo de unsigned char para GPIO_FAKE    				*/
	byte_to_struct(ucConvert, &My_GPIO2);
	/*							FIM CONVERSÃO								*/

	printf("de ucConvert para My_GPIO2 = %d %d %d %d %d %d %d %d\n\n", My_GPIO2.ucPIN7, My_GPIO2.ucPIN6, My_GPIO2.ucPIN5, My_GPIO2.ucPIN4, My_GPIO2.ucPIN3, My_GPIO2.ucPIN2, My_GPIO2.ucPIN1, My_GPIO2.ucPIN0);
}

/*********************************************************************************************************************/
/* INICIO....do pesadelo!																							 */
int main()
{
	while (1) {
		int x = 0;

		printf("Selecione uma das opcoes:\n");
		printf("1 - bit a bit\n");
		printf("2 - campos de bits\n");

		scanf_s("%d", &x);

		switch (x)
		{
		case 1:
			bit_a_bit();
			break;

		case 2:
			campos_de_bits();
			break;

		default:
			printf("Opcao invalida!!!\n");
			break;
		}
	}
	
	return 0;
}