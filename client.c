#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
  
int  main( int  argc,  char  *argv[])  
{  
    int  client_sockfd;  
    int  len,i;  
    struct  sockaddr_in remote_addr;  //服務器端網絡地址結構體  
    int  sin_size;
    char  buf[BUFSIZ];   //數據傳送的緩衝區  
    memset(&remote_addr,0, sizeof (remote_addr));  //數據初始化--清零  
    remote_addr.sin_family=AF_INET;  //設置為IP通信  
    remote_addr.sin_addr.s_addr=inet_addr( "192.168.0.10" ); //服務器IP地址 (loacl host:127.0.0.1)
    remote_addr.sin_port=htons(8080);  //服務器端口號  (local host:8000)
  
         /*創建客戶端套接字--IPv4協議，面向無連接通信，UDP協議*/  
    if ((client_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)  
    {    
        perror( "socket" );  
        return  1;  
    } 
    while(1)
    {  
	 gets(buf);
	 i = 0;
	 while(1)
	 {
	   if(buf[i] == '\0')
	     {
	        buf[i++] = '\n';
	        buf[i++] = '\0';
	        break;
	      }
	   i++;
	 }
	 printf( "sending: %s \n" ,buf);  
	 sin_size= sizeof ( struct  sockaddr_in); 

	 /*向服務器發送數據包*/
	 if ((len=sendto(client_sockfd,buf,strlen(buf),0,( struct  sockaddr *)&remote_addr, sizeof ( struct sockaddr)))<0)  
	 {  
	 perror( "recvfrom" );   
	 return  1;  
	 }
	 
    }
    close(client_sockfd);  
    return  0;  
}  
