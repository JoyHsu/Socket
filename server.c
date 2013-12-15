#include <stdio.h>  
#include <sys/types.h>  
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <arpa/inet.h>  
  
int  main( int  argc,  char  *argv[])  
{  
    int  server_sockfd;  
    int  len;  
    struct  sockaddr_in my_addr;    //服務器網絡地址結構體  
    struct  sockaddr_in remote_addr;  //客戶端網絡地址結構體  
    int  sin_size;  
    char  buf[BUFSIZ];   //數據傳送的緩衝區  
    memset(&my_addr,0, sizeof (my_addr));  //數據初始化--清零  
    my_addr.sin_family=AF_INET;  //設置為IP通信  
    my_addr.sin_addr.s_addr=INADDR_ANY; //服務器IP地址--允許連接到所有本地地址上  
    my_addr.sin_port=htons(55056);  //服務器端口號  
      
    /*創建服務器端套接字--IPv4協議，面向無連接通信，UDP協議*/  
    if ((server_sockfd=socket(PF_INET,SOCK_DGRAM,0))<0)  
    {    
        perror( "socket" );  
        return  1;  
    }  
   
    /*將套接字綁定到服務器的網絡地址上*/  
    if  (bind(server_sockfd,( struct  sockaddr *)&my_addr, sizeof ( struct  sockaddr))<0)  
    {  
        perror( "bind" );  
        return  1;  
    }  
while(1)
    {    
	    sin_size= sizeof ( struct  sockaddr_in);  
	    printf( "waiting for a packet...\n" );  
	      
	    /*接收客戶端的數據並將其發送給客戶端--recvfrom是無連接的*/  
	    if ((len=recvfrom(server_sockfd,buf,BUFSIZ,0,( struct  sockaddr *)&remote_addr,&sin_size))<0)  
	    {  
		perror( "recvfrom" );   
		return  1;  
	    }  
	    printf( "received packet from %s: \n" ,inet_ntoa(remote_addr.sin_addr));  
	    buf[len]= '\0' ;  
	    printf( "contents: %s \n" ,buf); 
    } 
    close(server_sockfd);  
        return  0;  
}  
