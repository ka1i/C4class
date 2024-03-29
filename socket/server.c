#include <config.h>


int main(int argc , char **argv)
{

	struct sockaddr_in servaddr , cliaddr;

	int listenfd , connfd;
	pid_t childpid;


	char buf[MAX_LINE];

	socklen_t clilen;

	if((listenfd = socket(AF_INET , SOCK_STREAM , 0)) < 0){
		perror("socket error");
		exit(1);
	}

	bzero(&servaddr , sizeof(servaddr));

	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	servaddr.sin_port = htons(PORT);

	if(bind(listenfd , (struct sockaddr*)&servaddr , sizeof(servaddr)) < 0){
		perror("bind error");
		exit(1);
	}


	if(listen(listenfd , LISTENQ) < 0){
		perror("listen error");
		exit(1);
	}
	printf("TCPServer %s:%d Listening Success...\n","0.0.0.0",PORT);

	for( ; ; )
	{
		clilen = sizeof(cliaddr);
		if((connfd = accept(listenfd , (struct sockaddr *)&cliaddr , &clilen)) < 0 ){
			perror("accept error");
			exit(1);
		}
		send(connfd,"Welcome to GuzalAida!\n",25,0);

		if((childpid = fork()) == 0) {
			close(listenfd);
			ssize_t n;
			int res;
			char buff[MAX_LINE];
			printf("[%s] TCPClient %s:%d Connecting Success...\n",timestamp(),inet_ntoa(cliaddr.sin_addr),ntohs(cliaddr.sin_port));
			while((n = recv(connfd , buff , MAX_LINE,0)) > 0){
				printf("ACK:--->%s\n",strcat(HTTP_HEAD,html));
				//send(connfd,strcat(HTTP_HEAD,html),50,0);
				send(connfd,"Welcome to GuzalAida!\n",25,0);
				
			}
			exit(0);
		}
		close(connfd);
	}

	close(listenfd);
}
