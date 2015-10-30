# MbedTLS-Test
Warning! This is test project!!

- Development Environment
  - Hardware
    - ST MICRO STM32F103VC Cortex M3
    - Wiznet W5500 Hardware TCP/IP Stack IC
    - Personaly designed board.
  - Software
    - CoIDE
    - GCC

<!-- W5500 Custom board pic -->
![W5500 Custom board](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w5500:w5500_evb:img_4834.jpg "W5500 Custom board")

- Firmware
  - MbedTLS 2.1.2
    - Can download from [https://tls.mbed.org](https://tls.mbed.org) but MbedTLS library has some bugs.
  - ST Basic library provided by ST MICRO
    - CoIDE includes stm library.
  - ioLibrary W5500 driver provided by WIZnet
    - Can download from [https://github.com/Wiznet/ioLibrary_Driver](https://github.com/Wiznet/ioLibrary_Driver)
  - Board specific code
  - main.c & ETC
 
- Project Structure

<!-- MbedTLS test project pic -->
![MbedTLS test project](http://wizwiki.net/wiki/lib/exe/fetch.php?media=products:w5500:w5500_evb:mbedtls_software_structure.png "MbedTLS test project")

#Have to change
- Ethernet informations(main.c line 5)
```
wiz_NetInfo gWIZNETINFO = { .mac = {},
							.ip = {000, 000, 000, 000},
							.sn = {000, 000, 000, 000},
							.gw = {000, 000, 000, 000},
							.dns = {000, 000, 000, 000},
							.dhcp = NETINFO_STATIC};
```
- e-mail informations(ssl_client.c line 43)
```
//SMTP server
char *host_id = "smtp.gmail.com";            //SMTP domain name 

//Sending Email address
char *frome_id = "email-address@gmail.com";   //Input email address

//ID name for the SMTP server
char *mail_id = "email-address";			  //Input the ID name

//Password for the SMTP server
char *mail_pwd = "email-password";			  //Input the Password

//Destination email address
char *to_id = "Destination-email-address@naver.com";		  //Input Destination email address

//Topic of the email
char *sub = "W5500 SSL SMTP protocol Test";

//Content of the email
char wkstr[100] = "W5500 SSL SMTP protocol Test!";
```
