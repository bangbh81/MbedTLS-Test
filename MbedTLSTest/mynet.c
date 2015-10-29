/*
     FileName:     mynet.h
     Description:  
     Aurhtor:      angel
     Date:         2014/10/9
     Release:
*/

#include "mynet.h"
#include "socket.h"
/******************************* macro define ******************************/


/****************************** data struct defien *************************/


/****************************** function define ****************************/



/***************************************************************************/
/*
      Funtion: initialize socket channel, set socket operation mode 
      Rarameters:
          fd:Host Channel 
          protocol:Sn_MR_TCP\Sn_MR_UDP\Sn_MR_IPRAW\Sn_MR_MACRAW\Sn_MR_PPPOE  
          port: Port number 
          flag:
      Return value:   
              1 ->sucess
              0 ->fail 
*/
int my_net_init(void *ctx,char protocol,int port,char flag)
{
      int fd;
	  
	  fd = *((int *)ctx);
	  
      return(socket(fd,protocol,port,flag));
}

/*
    Function:Server that listens Client's connection (TCP Server Listen)
    Parameters:  
         fd:Host Channel 
    Return Value:
         1 -> Success
         Others -> Fail 
          
*/
int my_net_listen(int fd)
{
    int ret = 0;

	if((ret = listen(fd)) != 1)
    {
        ret = ACKETH_SSL_ERR_NET_LISTEN_FAILED;
	}

	return ret;
}


/*
     Function:initialize one TCP connection (TCP client Connect)
     Parameters:
        fd:   Host Channel 
        host: Host IP adddress 
        port: Port number 
     ·µ»ØÖµ:   
              1 ->Success
              0 ->Fail      
*/
int my_net_connect(void *ctx,unsigned char *host, int port )
{
	int fd;
	fd = *((int *)ctx);

	return (connect(fd,host,port));
}

/*
    Function:
    Parameters:
    Return values:
*/
int my_net_bind(void *ctx, char protocol,int port,char flag )
{
	  int ret = 0;
	  int fd;

	  fd = *((int *)ctx);
	  
	  if((ret = socket(fd,flag,port,flag)) != 1 )
	  {
               return (ACKETH_SSL_ERR_NET_SOCKET_FAILED);
	  }
	  
	   if((ret = listen(fd)) != 1)
	  {
               return (ACKETH_SSL_ERR_NET_LISTEN_FAILED);
	  }

	   return (ret);
}

/*
    Function:Receive data 
    Parameters:
         fd:Host Channel
         buf:data Buffer 
         len:data length
    Return Value:Return value : activate tcp receive function 
*/
int my_net_recv(void *ctx, unsigned char *buf, unsigned int len )
{
      int fd;

      fd = *((int *)ctx);
	  
      return (recv(fd,buf,len));
}

/*
    Function:Send data
    Parameter:
         fd:Host Channel
         buf:data Buffer 
         len:data length
    Return value : activate tcp send function 
*/
int my_net_send(void *ctx, const unsigned char *buf, unsigned int len )
{

      int fd;

      fd = *((int *)ctx);

      return (send(fd,buf,len));
}

/*
    Function:Close socket connect 
    Parameter:Host Channel
    Return value:Nothing 
*/
void my_net_close( int fd )
{
       close(fd);
}


