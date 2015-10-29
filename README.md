# MbedTLS-Test
This firmware is for MbedTLS poring and test.

- Development Environment
  - Hardware
    - ST MICRO STM32F103VC Cortex M3
    - Wiznet W5500 Hardware TCP/IP Stack IC
    - Personaly designed board.
  - Software
    - CoIDE
    - Gcc

<!-- ioLibrary pic -->
![ioLibrary](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w5500:w5500_evb:img_4834.jpg "ioLibrary")

- Software
  - MbedTLS 2.1.2
    - Can download from [https://tls.mbed.org](https://tls.mbed.org) but MbedTLS library has some bugs.
  - ST Basic library provided by ST MICRO
    - CoIDE includes stm library.
  - ioLibrary W5500 driver provided by WIZnet
    - Can download from [https://github.com/Wiznet/ioLibrary_Driver](https://github.com/Wiznet/ioLibrary_Driver)
  - Board specific code
  - main.c & ETC

#Have to change
- Ethernet informations(main.c)
```
wiz_NetInfo gWIZNETINFO = { .mac = {},
							.ip = {000, 000, 000, 000},
							.sn = {000, 000, 000, 000},
							.gw = {000, 000, 000, 000},
							.dns = {000, 000, 000, 000},
							.dhcp = NETINFO_STATIC};
```
- 
