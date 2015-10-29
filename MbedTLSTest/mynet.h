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
      ����:��ʼ��socketͨ��������socket����ģʽ
      ����:
          fd:����ͨ��
          protocol:Э��(Sn_MR_TCP\Sn_MR_UDP\Sn_MR_IPRAW\Sn_MR_MACRAW\Sn_MR_PPPOE)  
          port:�˿�
          flag:
      ����ֵ:   
              1 ->�ɹ�
              0 ->ʧ��
*/
int my_net_init(void *ctx,char protocol,int port,char flag);

/*
    ����:���������ڼ����ͻ��˵�����
    ����:  
         fd:����ͨ��
    ����ֵ:
         1 -> �ɹ�
         ���� -> ʧ��
          
*/
int my_net_listen(int fd);


/*
     ����:��ʼ��һ��TCP����
     ����:
        fd:   ����ͨ��
        host: ����IP��ַ
        port: �˿ں�
     ����ֵ:   
              1 ->�ɹ�
              0 ->ʧ��        
*/
int my_net_connect(void *ctx,unsigned char *host, int port );

/*
    ����:
    ����:
    ����ֵ:
*/
int my_net_bind(void *ctx, char protocol,int port,char flag );


/*
    ����:��������
    ����:
         fd:����ͨ��
         buf:���ݻ�����
         len:���ݳ���
    ����ֵ:
*/
int my_net_recv(void *ctx, unsigned char *buf, unsigned int len );

/*
    ����:��������
    ����:���ݻ�����
    ����ֵ:���ݳ���
*/
int my_net_send(void *ctx, const unsigned char *buf, unsigned int len );


/*
    ����:�ر�socket����
    ����:����ͨ��
    ����ֵ:��
*/
void my_net_close( int fd );


#ifdef __cplusplus
}
#endif

#endif /* net.h */

