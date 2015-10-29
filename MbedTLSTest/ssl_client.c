/*
	FileName:		ssl_client.c
	Description:
	Aurthor:		Angel
	Date:	     2014/11/19
*/

#include "ssl_client.h"

#include "config.h"
#include "compat-1.3.h"
#include "check_config.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "entropy.h"
#include "ctr_drbg.h"
#include "certs.h"
#include "x509.h"
#include "ssl.h"
#include "mynet.h"   //angel modify for STM32
#include "error.h"
#include "debug.h"
//#include "ssl_cache.h"

#include "random.h"

#include "socket.h"
/************************************* macro define *******************************/

#define DEBUG_LEVEL 3     //define the debug message output level

#define SERVER_PORT   465 //443
//#define GET_REQUEST "GET / HTTP/1.0\r\n\r\n"

#define SOCK_SMTP	      1//2


#define MAX_USER_INFO  32

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

/************************************* data struct define *************************/
unsigned char gServer_IP[4] = {173,194,72,109};//{173,194,72,109};//{106,10,150,171}; yahoo //{113,108,16,44}; smtp.qq.com //

/************************************* function define ****************************/
#if defined (MBEDTLS_DEBUG_C)
static void my_debug(void *ctx, int level, const char *file, int line, const char *str);
#endif
static void SMTP_protocol(mbedtls_ssl_context *ssl);
static char *encrypt_user_info(const char *info,unsigned char *buf,int len);
static int write_ssl_and_get_response(mbedtls_ssl_context *ssl, unsigned char *buf, int len );

/************************************* main function ******************************/
void ssl_client(void)
{
     int ret,server_fd = SOCK_SMTP;   //len,
	 int shandshake_ok = 0;
	 //UINT8 buf[1024];
 	 //UINT8 *pers = "ssl_client1";
	 mbedtls_ssl_config conf;
	 mbedtls_entropy_context entropy;
	 mbedtls_ctr_drbg_context ctr_drbg;
	 mbedtls_ssl_context ssl;
	 mbedtls_x509_crt cacert;

#if defined (MBEDTLS_ERROR_C)
	 char error_buf[100];
#endif

#if defined (MBEDTLS_DEBUG_C)
	 debug_set_threshold(DEBUG_LEVEL);
#endif

     /*
             Initialize session data
       */
	mbedtls_entropy_init(&entropy);
	mbedtls_ctr_drbg_init(&ctr_drbg);
	mbedtls_x509_crt_init(&cacert);
	mbedtls_ssl_init(&ssl);
	mbedtls_ssl_config_init(&conf);
      /*
             Initialize certificates
	  */
			printf(" Loading the CA root certificate \r\n");

	mbedtls_ssl_config_defaults(&conf,
							MBEDTLS_SSL_IS_CLIENT,
							MBEDTLS_SSL_TRANSPORT_STREAM,
							MBEDTLS_SSL_PRESET_DEFAULT);
	mbedtls_ssl_setup(&ssl, &conf);
#if defined (MBEDTLS_CERTS_C)
	  ret = mbedtls_x509_crt_parse(&cacert,(unsigned char *)mbedtls_test_cas_pem,strlen(mbedtls_test_cas_pem));
#else
      ret = 1;
      printf("SSL_CERTS_C not define .\r\n");
#endif

      if(ret < 0)
      {
    	  printf("x509_crt_parse failed \r\n");
		  goto exit;
	  }
	  /*
	       set ssl session para
	  */
      mbedtls_ssl_conf_ca_chain(&conf, &cacert, NULL);
	  mbedtls_ssl_conf_endpoint(&conf,MBEDTLS_SSL_IS_CLIENT); 		//set the current communication method is SSL Client
	  mbedtls_ssl_conf_authmode(&conf,MBEDTLS_SSL_VERIFY_NONE);
	  	
	  mbedtls_ssl_conf_rng(&conf,my_ctr_drbg_random,&ctr_drbg);
	 // mbedtls_ssl_conf_dbg(&conf,my_debug,stdout);
	  
	  mbedtls_ssl_set_bio(&ssl,&server_fd, my_net_send, my_net_recv, NULL);		 //set client's socket send and receive functions


//        if( ssl.f_rng == NULL )
//        {
//           printf("RNG function is NULL \r\n");
//		   goto exit;
//		}
	  
      /*
            start the connection
	  */
        printf("connecting to Server:%d.%d.%d.%d  Port:%4d\r\n",
	          gServer_IP[0],gServer_IP[1],gServer_IP[2],gServer_IP[3],SERVER_PORT);

#if 0
	  if((ret = my_net_connect(&server_fd,gServer_IP,SERVER_PORT)) != 1)
	  {
		  printf("net_connect faild \r\n");
			goto exit;
	  }
#endif

      /*
             handshake
	  */
	  printf("Performing the SSL/TLS handshake...\r\n");

      while(shandshake_ok != 1)
      {
            switch(getSn_SR(server_fd))
            {
               case SOCK_INIT:
            	   	 printf("SOCKT_INTI \r\n");
					 my_net_connect(&server_fd,gServer_IP,SERVER_PORT);
					 break;
				case SOCK_ESTABLISHED:
					 printf("SOCKET_ESTABLISTHED \r\n");
					 if(getSn_IR(server_fd) & Sn_IR_CON)
					 {
							setSn_IR(0, Sn_IR_CON);/*Sn_IR 0 put into 1*/
					 }
					while((ret = ssl_handshake(&ssl)) != 0)
					{
						if( (ret != ACKETH_SSL_ERR_NET_WANT_READ) &&
							(ret != ACKETH_SSL_ERR_NET_WANT_WRITE))
						{
							 printf("ssl_handshake return -0x%x \r\n",-ret);
							 goto exit;
						}
					}
					shandshake_ok = 1;
					 break;
												
			   case SOCK_CLOSE_WAIT:
				     printf("SOCK_CLOSE_WAIT \r\n");
					 while((ret = ssl_handshake(&ssl)) != 0)
					 {
						if( (ret != ACKETH_SSL_ERR_NET_WANT_READ) &&
							(ret != ACKETH_SSL_ERR_NET_WANT_WRITE))
						{
							 printf("ssl_handshake return -0x%x \r\n",-ret);
							 goto exit;
						}
					 }
					 shandshake_ok = 1;
						my_net_close(server_fd);
			   	   break;
						 
			   case SOCK_CLOSED:
				   printf("SOCKET_CLOSED \r\n");
			   	   //my_net_init(&server_fd,Sn_MR_TCP,3000,Sn_MR_ND);
			   	   my_net_init(&server_fd,Sn_MR_TCP,3000,0x00);
			   	   break;
			   default:
			   	   break;
			}
	  }
	  

	  /*
           Verify the server certificate 
	  */
#if 0	  
	  printf("Verifying peer X.509 certificate ...\r\n");
	  if((ret = ssl_get_verify_result(&ssl)) != 0)
	  {
		  printf("ssl_get_verify_result faild \r\n");

		   if((ret & BADCERT_EXPIRED) != 0)
		   {
			   printf("server certificate has expired \r\n");
		   }

		   if( ( ret & BADCERT_REVOKED ) != 0 ) 	
		   {
			   printf("server certificate has been revoked \r\n");
		   }	
		   
		   if( ( ret & BADCERT_CN_MISMATCH ) != 0 )
		   {
			   printf( "CN mismatch (expected CN=%s) \r\n", "AckethSSL Server 1" );
		   }
		   
		   if( ( ret & BADCERT_NOT_TRUSTED ) != 0 )
		   {
			   printf( "self-signed or not signed by a trusted CA \r\n" );
		   }	 

	  }
	  else
	  {
		  printf("Verify Certificate ok \r\n");
	  }
#endif	  

	  printf("Starting ESMTP \r\n");
		
         /* 
		      SMTP protocol 
		 */
		  SMTP_protocol(&ssl);
      
		  /*
		      close ssl connection
		  */
	    ssl_close_notify(&ssl);

exit:	 

#ifdef ACKETH_SSL_ERROR_C
	if(ret != 0)
	{
		ackethssl_strerror(ret,error_buf,100);
		printf("Last error was: %d - %s\n\n", ret, error_buf );
	}
#endif

    my_net_close(server_fd);


	  x509_crt_free(&cacert);
	  ssl_free(&ssl);
     //ctr_drbg_free(&ctr_drbg);
	  entropy_free(&entropy);
}


/***********************************************************************************/
/*
     function:
             from the defination ssl debug msg output level function   
     parameters:
             level -- debug message output level
             str   -- data for those output msg
     Return value:
               Nothing
*/
#ifdef MBEDTLS_DEBUG_C
static void my_debug(void *ctx, int level, const char *file, int line, const char *str)
{
    if(level < DEBUG_LEVEL)
    {
       printf("%s\r\n",str);
    }
}
#endif
void SMTP_protocol(mbedtls_ssl_context *ssl)
{
	  int len,ret;
	  unsigned char buf[512];
	
	  
	  printf("> Get header from server: \r\n");
	
    ret = write_ssl_and_get_response(ssl,buf,0);
	  if((ret < 200) || (ret > 299))
		{
			 printf("server responded error. \r\n");
		   return;
		}
		
		
		printf("> Write EHLO to server: \r\n");
		len = sprintf((char *)buf,"EHLO %s\r\n",mail_id);
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 299))
		{
			 printf("server responded error. \r\n");
		   return;
		}
		
	
		printf("> Write AUTH LOGIN to server: \r\n");
		len = sprintf((char *)buf,"AUTH LOGIN\r\n");
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 399))
		{
			 printf("server responded error. \r\n");
		   return;
		}		
		

		printf("> Write Username to server: %s \r\n",mail_id);
		len = sprintf((char *)buf,"%s\r\n",encrypt_user_info(mail_id,buf,MAX_USER_INFO));
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 399))
		{
			 printf("server responded error. \r\n");
		   return;
		}	
		
		
		printf("> Write password to server: %s \r\n",mail_pwd);
		len = sprintf((char *)buf,"%s\r\n",encrypt_user_info(mail_pwd,buf,MAX_USER_INFO));
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 399))
		{
			 printf("server responded error. \r\n");
		   return;
		}
		
		
		printf("> Write Mail from to server:");
		printf("Mail from:<%s>\r\n",frome_id);
		len = sprintf((char *)buf,"mail from:<%s>\r\n",frome_id);
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 299))
		{
			 printf("server responded error. \r\n");
		   return;
		}
		
		
		printf("> Write RCPT to server:");
		printf("rcpt to:<%s>\r\n",to_id);
		len = sprintf((char *)buf,"rcpt to:<%s>\r\n",to_id);
    ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 299))
		{
			 printf("server responded error. \r\n");
		   return;
		}		
		
		
		printf("> Write DATAINIT to server:\r\n");
		len = sprintf((char *)buf,"data\r\n");
		ret = write_ssl_and_get_response(ssl,buf,len);
		
	  if((ret < 200) || (ret > 394))
		{
			 printf("server responded error. \r\n\r\n");
		   return;
		}		
		printf("> Write DATA to server:\r\n");
		len = sprintf((char *)buf,"From:%s\r\nTo:%s\r\nSubject:%s\r\nMIME-Version:1.0\r\nContent-Type:text/plain\r\n\r\n%s\r\n.\r\n",frome_id,to_id,sub,wkstr);                //????
		ret = write_ssl_and_get_response(ssl,buf,len);

	  if((ret < 200) || (ret > 394))
		{
			 printf("server responded error. \r\n");
		   return;
		}		
		
		
		len = sprintf( (char *) buf, "Quit\r\n");    
		ret = write_ssl_and_get_response(ssl,buf,len);
	  if((ret < 200) || (ret > 299))
		{
			 printf("server responded error. \r\n");
		   return;
		}
}


static char *encrypt_user_info(const char *info,unsigned char *buf,int len)
{
	  unsigned char *s;
	  s = buf;
	  size_t n;
	  mbedtls_base64_encode(buf,(size_t)len,&n,(const unsigned char *)info,strlen(info));

	  return ((char *)s);
}


static int write_ssl_and_get_response(mbedtls_ssl_context *ssl, unsigned char *buf, int len )
{
	  int ret;
	  unsigned char data[128];
	  char code[4];
	  int i,idx = 0;
	  
	  //printf("\n%s",buf);
	  while(len && (ret = mbedtls_ssl_write(ssl,buf,len)) <= 0)
		{
        if((ret != ACKETH_SSL_ERR_NET_WANT_READ) &&
		  	   (ret != ACKETH_SSL_ERR_NET_WANT_WRITE)
		  	   )
          {
        	printf( " failed\n  ! mbedtls_ssl_write returned %d \n\n", ret );
            return (-1);						
		      }
		}
		
//#ifdef STM32_SSL_CLIENT What is it???!!!
////      DelayNms(1000);
////	    DelayNms(1000);
//#endif

    do
		{
			  len = sizeof(data) - 1;
			  memset(data,0,sizeof(data));
			
			  ret = ssl_read(ssl,data,len);
			
					
			  if((ret == ACKETH_SSL_ERR_NET_WANT_READ) ||
		   	   (ret == ACKETH_SSL_ERR_NET_WANT_WRITE)
		   	   )
		    {
		   	    continue;
		   	}

		   if((ret == MBEDTLS_ERR_SSL_PEER_CLOSE_NOTIFY) ||
		   	  (ret < 0 ) || (ret == 0))
		    {
			   printf( "ssl_read faild,returned %d\n\n", ret );
               return (-1);
		    }
				
				printf("\n%s",data);
				len = ret;
				for(i = 0;i < len;i++)
				{
				    if(data[i] != '\n')
						{
						    if(idx < 4)
								{
                   code[idx++] = data[i];
                }
                continue;								
						}
						
            if( (idx == 4) && (code[0] >= '0') && (code[0] <= '9') && (code[3] == ' ') )
            {
                code[3] = '\0';
                return atoi( code );
            }
						
						idx = 0;
				}
		}while(1);		
}
/* ssl_client.c */

