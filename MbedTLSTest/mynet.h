/*
     FileName:     mynet.h
     Description:  
     Aurhtor:      angel
     Date:         2014/10/9
     Release:
*/

#ifndef _MYNET_H_
#define _MYNET_H_


/******************************* macro define ******************************/
#define ACKETH_SSL_ERR_NET_UNKNOWN_HOST                      -0x0056  /**< Failed to get an IP address for the given hostname. */
#define ACKETH_SSL_ERR_NET_SOCKET_FAILED                     -0x0042  /**< Failed to open a socket. */
#define ACKETH_SSL_ERR_NET_CONNECT_FAILED                    -0x0044  /**< The connection to the given server / port failed. */
#define ACKETH_SSL_ERR_NET_BIND_FAILED                       -0x0046  /**< Binding of the socket failed. */
#define ACKETH_SSL_ERR_NET_LISTEN_FAILED                     -0x0048  /**< Could not listen on the socket. */
#define ACKETH_SSL_ERR_NET_ACCEPT_FAILED                     -0x004A  /**< Could not accept the incoming connection. */
#define ACKETH_SSL_ERR_NET_RECV_FAILED                       -0x004C  /**< Reading information from the socket failed. */
#define ACKETH_SSL_ERR_NET_SEND_FAILED                       -0x004E  /**< Sending information through the socket failed. */
#define ACKETH_SSL_ERR_NET_CONN_RESET                        -0x0050  /**< Connection was reset by peer. */
#define ACKETH_SSL_ERR_NET_WANT_READ                         -0x0052  /**< Connection requires a read call. */
#define ACKETH_SSL_ERR_NET_WANT_WRITE                        -0x0054  /**< Connection requires a write call. */

/****************************** data struct defien *************************/


/****************************** function define ****************************/


/***************************************************************************/
#ifdef __cplusplus
extern "C" {
#endif


/*
      功能:初始化socket通道，设置socket工作模式
      参数:
          fd:主机通道
          protocol:协议(Sn_MR_TCP\Sn_MR_UDP\Sn_MR_IPRAW\Sn_MR_MACRAW\Sn_MR_PPPOE)  
          port:端口
          flag:
      返回值:   
              1 ->成功
              0 ->失败
*/
int my_net_init(void *ctx,char protocol,int port,char flag);

/*
    功能:服务器用于监听客户端的连接
    参数:  
         fd:主机通道
    返回值:
         1 -> 成功
         其它 -> 失败
          
*/
int my_net_listen(int fd);


/*
     功能:初始化一个TCP连接
     参数:
        fd:   主机通道
        host: 主机IP地址
        port: 端口号
     返回值:   
              1 ->成功
              0 ->失败        
*/
int my_net_connect(void *ctx,unsigned char *host, int port );

/*
    功能:
    参数:
    返回值:
*/
int my_net_bind(void *ctx, char protocol,int port,char flag );


/*
    功能:接收数据
    参数:
         fd:主机通道
         buf:数据缓冲区
         len:数据长度
    返回值:
*/
int my_net_recv(void *ctx, unsigned char *buf, unsigned int len );

/*
    功能:发送数据
    参数:数据缓冲区
    返回值:数据长度
*/
int my_net_send(void *ctx, const unsigned char *buf, unsigned int len );


/*
    功能:关闭socket连接
    参数:主机通道
    返回值:无
*/
void my_net_close( int fd );


#ifdef __cplusplus
}
#endif

#endif /* net.h */

