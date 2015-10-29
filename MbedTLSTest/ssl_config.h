/*
    FileName:      ssl_config.h
    Description:   The required defination that connects to ssl protcol database 
    Aurthor:       angel
    Date:          2014/9/18
*/

#ifndef ACKETH_SSL_CONFIG_H
#define ACKETH_SSL_CONFIG_H

/*********** include file *********************/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

/************************ macro define ***********************************/
#define AS_SSL_CLIENT   //complie SSL cleint protocols
#define STM32_SSL_CLIENT //complie STM32 SSL client program 

/*
   The following setting is base on the protocol for gmail & yahoo servers (TLS v1.2)
*/
//#defien SSL_CLIENT_SUPPOR_AILPAY

/************************ ssl config *************************************/

/* System supports functions */
#define ACKETH_SSL_CONFIG_FILE  "ssl_config.h"   //define ssl function setting documenation
//#define ACKETH_SSL_FS_IO    //

/* ssl features supports functions */
//#define ACKETH_SSL_PROTO_TLS1    //supports TLS v1.0
//#define ACKETH_SSL_PROTO_TLS1_1  //supports TLS v1.1
#define ACKETH_SSL_PROTO_TLS1_2        //supports TL v1.2
//#define ACKETH_SSL_PROTO_SSL3         //supports SSL v3.0

#define ACKETH_SSL_CIPHER_MODE_CBC //Use verify certificate function 
#define ACKETH_SSL_PKCS1_V15       //define public key padding method

//#define ACKETH_SSL_SRV_SUPPORT_SSLV2_CLIENT_HELLO //define suppots SSL v2  

/* ssl function supports */
#define ACKETH_SSL_CERTS_C             //define to use certication testing function 
#define ACKETH_SSL_RSA_C               //define public key encryption method (Using RSA) 

//#define ACKETH_SSL_ECDH_C  //LIU
//#define ACKETH_SSL_ECP_C

//#define #define ACKETH_SSL_ARC4_C      //define public key encryption method (Using RC4)

#define ACKETH_SSL_X509_USE_C          //Using X509 frame function 
#define ACKETH_SSL_X509_CRT_PARSE_C    //define supporting ssl x.509 certificate analyze
#define ACKETH_SSL_PK_C                //Using private key encryption function 
#define ACKETH_SSL_PK_PARSE_C          //Using private key encryption analyze function 

#define ACKETH_SSL_BIGNUM_C            //define using Big number function 
#define ACKETH_SSL_CIPHER_C            //define using certificate function 

#define ACKETH_SSL_ENTROPY_C           //define using Entropy calcuation
//#define ACKETH_SSL_SHA512_C            //define using SHA512 calcuation 
#define ACKETH_SSL_SHA1_C            //define using SHA128 calcuation 
#define ACKETH_SSL_SHA256_C          //define using SHA256 calcuation 

#define ACKETH_SSL_MD_C              //define using MD calculation
#define ACKETH_SSL_MD5_C             //define using MD5 calculation 

#define ACKETH_SSL_CTR_DRBG_C          //define using random number function 

#define ACKETH_SSL_AES_C               //define using AES function (after handshake - communicate stage)
//#define ACKETH_SSL_DES_C                     //define using DES function 
#define ACKETH_SSL_ASN1_PARSE_C        //define using ASN analysis function 
#define ACKETH_SSL_ASN1_WRITE_C        //define using ASN write function 
#define ACKETH_SSL_OID_C              //define using OID function 


#if defined (AS_SSL_CLIENT)
	#define ACKETH_SSL_CLI_C           //define using SSL client handshark supports function
#endif

#if defined (AS_SSL_SERVER)
    #define ACKETH_SSL_SRV_C           //define using SSL server handshark supports function
#endif

#define ACKETH_SSL_TLS_C           //define using TLS support function  

//#define ACKETH_SSL_ERROR_C             //define using ERROR function (Showing error message)
//#define ACKETH_SSL_DEBUG_C             //define using debug function (Showing debug message)
#define ACKETH_SSL_DEBUG_DFL_MODE  0 //define testing information output format. Default setting: Show file name and line

/* Testing certificate procedure */
#define ACKETH_SSL_CERTS_C        //define using certificate testing function 
#define ACKETH_SSL_PEM_PARSE_C    //define testing certifcate will use ASCII format (Sending PEM file)
#define ACKETH_SSL_BASE64_C       //define testing certificate is in ASCII format 

//define communicate encrytion methods 
//#define ACKETH_SSL_KEY_EXCHANGE_ECDHE_PSK_ENABLED
//#define ACKETH_SSL_KEY_EXCHANGE_ECDHE_RSA_ENABLED

#define ACKETH_SSL_KEY_EXCHANGE_RSA_ENABLED        //
#define ACKETH_SSL_KEY_EXCHANGE_RSA_PSK_ENABLED   //
//#define ACKETH_SSL_GCM_C    //AES in GCM mode£¬base on parallel design£¬therefore it can good performance on speed,cost and less delay 
//#define ACKETH_SSL_CCM_C    //

//define encryption and discrete methods
#define SSL_CIPHERSUITES                    \
        TLS_RSA_WITH_AES_128_CBC_SHA,       \
		    TLS_RSA_WITH_AES_256_CBC_SHA,       \
			  TLS_RSA_WITH_RC4_128_SHA
				//TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256 
			 // TLS_RSA_WITH_AES_128_GCM_SHA256  	

//Save RAM 
#define ACKETH_MPI_MAX_SIZE   48
#define ENTROPY_MAX_SOURCES   2

//#define SSL_MAX_CONTENT_LEN    4096

//According to SSL requested data length to define, if the data is long, it takes a larger RAM space 

#if defined (SSL_CLIENT_SUPPOR_AILPAY) //defines for alipay
		#define SSL_MAX_CONTENT_LEN   5120   //define SSL client for connection to AILPAY
#else
		#define SSL_MAX_CONTENT_LEN    4096 //2048  
#endif

#define ACKETH_SSL_X509_ALLOW_UNSUPPORTED_CRITICAL_EXTENSION

#endif /* ssl_config */
