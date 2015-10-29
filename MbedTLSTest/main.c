#include "IoTEVB.h"
#include "W5500HardwareDriver.h"
#include "wizchip_conf.h"

wiz_NetInfo gWIZNETINFO = { .mac = {},
							.ip = {000, 000, 000, 000},
							.sn = {000, 000, 000, 000},
							.gw = {000, 000, 000, 000},
							.dns = {000, 000, 000, 000},
							.dhcp = NETINFO_STATIC};

uint8_t mac_address[6] = {};

int main(void)
{
	/*-----------------------------!!!!BASIC HARDWARE INITILIZE!!!!*/

	/*USART1 initialize*/

	USART1Initialze();

	/*W5500 Hardware initialize*/
	W5500HardwareInitilize();

	/*Systick initialize for delay*/
	/*TODO: DO NOT USE SYSTICK FOR DELAY FUNCTION!!!!!!!*/
	//SysTick_Init();

	/*ADC initialize for random number*/
	/*TODO: has to be modified.*/
	random_init();

	/*-----------------------------!!!!BOARD SPECIFIC HARDWARE INITILIZE!!!!*/

	/*I2C initialize for mac eeprom*/
	I2C1Initialize();

	/*-----------------------------!!!!W5500 initialize!!!!*/

	/*Mac address read from eeprom*/
	MACEEP_Read(mac_address,0xfa,6);

	/*W5500 initialize*/
	W5500Initialze();

	/*Input network information to W5500*/
	wizchip_setnetinfo(&gWIZNETINFO);

	/*Input mac address to W5500*/
	setSHAR(mac_address);

	/*-----------------------------!!!!START APPLICATION!!!!!*/
	/*SNTP Client*/
	ssl_client();

	while(1){}
}
