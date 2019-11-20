/*
* @Author: mardan
* @Date:   2019-11-10 15:39:59
* @Last Modified by:   mardan
* @Last Modified time: 2019-11-17 21:41:15
*/

#include <config.h>

void setNonblocking(int sockfd)
{
	int opts;
    opts=fcntl(sockfd,F_GETFL);
    if(opts<0)
    {
        perror("fcntl(sock,GETFL)");
        return;
    }//if

    opts = opts|O_NONBLOCK;
    if(fcntl(sockfd,F_SETFL,opts)<0)
    {
 		perror("fcntl(sock,SETFL,opts)");
        return;
    }//if
}

int main(int argc , char **argv)
{
	int i, listenfd, connfd, sockfd, epfd, nfds;

	ssize_t n, ret;
		
	char buf[MAX_LINE];

	socklen_t clilen;

	struct sockaddr_in servaddr , cliaddr;

	/*声明epoll_event结构体变量，ev用于注册事件，数组用于回传要处理的事件*/
	struct epoll_event ev, events[20];

	/*(1) 得到监听描述符*/
	listenfd = socket(AF_INET , SOCK_STREAM , 0);
	setNonblocking(listenfd);

	/*生成用于处理accept的epoll专用文件描述符*/	
	epfd = epoll_create(CONNECT_SIZE);
	/*设置监听描述符*/
	ev.data.fd = listenfd;
	/*设置处理事件类型*/
	ev.events = EPOLLIN | EPOLLET;
	/*注册事件*/
	epoll_ctl(epfd, EPOLL_CTL_ADD, listenfd, &ev);		

	/*(2) 绑定套接字*/	
	bzero(&servaddr , sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	bind(listenfd , (struct sockaddr *)&servaddr , sizeof(servaddr));

	/*(3) 监听*/
	listen(listenfd , LISTENQ);

	/*(4) 进入服务器接收请求循环*/
	printf("INFO: echo Server Listening %s:%d ...\n",inet_ntoa(servaddr.sin_addr), PORT);
	while(1)
	{
		/*等待事件发生*/
		nfds = epoll_wait(epfd , events , CONNECT_SIZE , -1);
		printf("nfds = %d\n", nfds);
		if(nfds <= 0)
			continue;
	
		//printf("nfds = %d\t" , nfds);
		/*处理发生的事件*/
		for(i=0 ; i<nfds ; ++i)
		{
			/*检测到用户链接*/
			printf("%d\n", 6);
			if(events[i].data.fd == listenfd)
			{	
				/*接收客户端的请求*/
				clilen = sizeof(cliaddr);

				if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0)
				{
					perror("accept error.\n");
					exit(1);
				}//if		

				printf("INFO: Client %s:%d Connecting ...\n", inet_ntoa(cliaddr.sin_addr) , cliaddr.sin_port);
			
				/*设置为非阻塞*/
				setNonblocking(connfd);
				ev.data.fd = connfd;
				ev.events = EPOLLIN | EPOLLET;
				epoll_ctl(epfd , EPOLL_CTL_ADD , connfd , &ev);
			}//if
			/*如果是已链接用户，并且收到数据，进行读入*/
			else if(events[i].events & EPOLLIN){

				if((sockfd = events[i].data.fd) < 0)
					continue;
				bzero(buf , MAX_LINE);
				if((n = read(sockfd , buf , MAX_LINE)) <= 0)
				{
					close(sockfd);
					events[i].data.fd = -1;
				}//if
				else{
					printf("%d,%ld\n", buf[n],n);
					buf[n] = '\0';
					printf("来自%s:%d的消息：%s\n",inet_ntoa(cliaddr.sin_addr) , cliaddr.sin_port , buf);
				
					/*设置用于注册写操作文件描述符和事件*/
					ev.data.fd = sockfd;
					ev.events = EPOLLOUT| EPOLLET;	
					epoll_ctl(epfd , EPOLL_CTL_MOD , sockfd , &ev);			
				}//else											
			}//else
			else if(events[i].events & EPOLLOUT)
			{
				if((sockfd = events[i].data.fd) < 0)
				continue;

				if((ret = send(sockfd, buf, strlen(buf), 0)) == -1)	
				{
					printf("error writing to the sockfd!\n");
					break;
				}else{
					printf("strlen(buf)==%ld\n", strlen(buf));
					printf("将%s转发到%s:%d ...\n", buf ,inet_ntoa(cliaddr.sin_addr) , cliaddr.sin_port);
					bzero(buf,strlen(buf));
					printf("%d\n", 1);
					usleep(1000);
					printf("%d\n", 2);
				}
				printf("%d\n", 3);
				/*设置用于读的文件描述符和事件*/
				ev.data.fd = sockfd;
				ev.events = EPOLLIN | EPOLLET;
				/*修改*/
				printf("%d\n", 4);
				epoll_ctl(epfd , EPOLL_CTL_MOD , sockfd , &ev);	
				printf("%d\n", 5);	
				printf("i==%d,nfds=%d\n", i,nfds);		
			}//else
		}//for
	}//wh10le
	printf("%d\n", 10);
	free(events);
	close(epfd);
	exit(0);
}