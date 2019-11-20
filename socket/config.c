#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>

#include <time.h>
#include <fcntl.h>


const int MAX_LINE = 2048;
const int PORT = 8080;
const int BACKLOG = 10;
const int LISTENQ = 6666;
const int MAX_CONNECT = 20;

char *HTTP_HEAD="HTTP/1.x 200 ok\nContent-Type: ";
const char *binary = "application/octet-stream";
const char *html="text/html\n\n";
const char *js="application/x-javascript";
const char *xml="text/xml";
const char *ico="image/x-icon";
const char *wrap="\n\n";


char* timestamp(){
	time_t rawtime = time(NULL);
	struct tm *timeinfo = localtime(&rawtime);
	static char nowtime[24];
	strftime(nowtime, sizeof(nowtime), "%Y-%m-%d %H:%M:%S", timeinfo); 
	return nowtime;
}
