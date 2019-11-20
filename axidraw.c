#include <time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termio.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/types.h>

#define SCROLL 17
#define SCROLLSTAR 60
#define ROW  10  //hang
#define COL  70  //lie

char sz1[ROW][COL];
struct winsize size;
unsigned len;
FILE *fp=NULL;

int getsystime(){
	time_t t;
	time(&t);
	printf("\033[15C%s%s","START_SYSTEM-TIME:",ctime(&t));
	return 0;
}
int terminal_size(){
      
    if (isatty(STDOUT_FILENO) == 0)  
        exit(1);  
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size)<0) 
    {
        perror("ioctl TIOCGWINSZ error");
        exit(1);
    } 
	return 0; 
}
int txtline_number(char *filename)
{
    fp = fopen(filename, "r");
    char buf[1000];
    int lineCnt = 0;
    if (!fp)
        return -1;
    while (fgets(buf, 1000, fp))
        lineCnt++;
    fclose(fp);
    return lineCnt;
}
int main(int argc,char** argv){
	int ii=1,kk=0,kkk,in=0,jn=0,kn=0;
	int per,ijk ,i ,j ,k,fline,blc;
	float len_1;
	char* serial=malloc(50);
	char file_path[100],s_n1[50];
	if(argc!=3){
		printf("Usage:  axidraw <OPTION> file...\n");
		printf("Axidraw contral of linux\n");
		printf("Options:\n");
		printf("\t-f Gcode file path;\n");
		printf("\t-h Show this help message;\n");
		exit(1);
	}
	if(strcmp(argv[1],"-f")==0){
		fp=fopen(argv[2],"r");
		if(fp==NULL){perror("fopen()");exit(1);fclose(fp);}
	}
	int line = txtline_number(argv[2]);
	fline = line;
	fputs("\033[2J",stderr);
	if(1)
	{
		fputs("\033[?25l", stderr);
		printf("\033[1;1H");
		printf("\033[21C\033[30m\033[47m***AxiDraw grbl contraler***\033[0m\n");
		fputs("\033[30C\033[1B\033[0;31mUSER:\033[0m",stderr);
		fputs("\033[40;41m",stderr);
		system("whoami");
		fputs("\033[24C\033[0m",stderr);
		system("uname -s -n -r");
		getsystime();
		fputs("\033[9C",stderr);
		system("uname -v -o -i");
		printf("\033[10;1H");
		system("find /dev -group dialout > serial.txt");
		usleep(300000);
		printf("Serial list:\n");
		fp=fopen("serial.txt","r");
		while(!feof(fp))
    	{
			in++;
       		fgets(s_n1,50,fp);
			printf("%d. %s",in,s_n1);
   		}
		printf("\033[1A\033[K");
		fputs("\033[?25h", stderr);
		printf("\nPlease input serial number:");
		scanf("%d",&jn);
		fputs("\033[?25l", stderr);
		if(jn==0){exit(1);}
		in=0;
		fseek(fp,0,SEEK_SET);
		while(!feof(fp))
    	{
			in++;
			fgets(serial,50,fp);
			if(in==jn)
			{
				printf("You choice : ->%s",serial);
				fclose(fp);
				break;
			}
    	}
		kn++;
		usleep(1000000);
		printf("\033[2J");
	}
	fp=fopen(argv[2],"r");
//"/dev/ttyACM0"
	FILE *fps;
	char temp;
	strtok(serial,"\n");
	fps=fopen(serial,"r");
	if(fps==NULL)
		{
			perror("fopen()");
	}
//chushihua arduino serial
	terminal_size();
	printf("\033[%d;%dHWaiting Arduino......",size.ws_row/2,size.ws_col/2);
/*
	i=1;
	while(i)
		{
		temp=0;
		fscanf(fps,"%c",&temp);
		if(temp!='\n')
			//{
			printf("%c",temp);
			//i=1;
			//}else{
			//i=0;
			//}
		}
	usleep(100000);
	fputs("\033[2J", stderr);			
*/
//chushihua arduino wancheng*/
	for (ijk = 0;line>0; line--,++ijk)
	{
		terminal_size();
		//fputs("\033[2J", stderr);
		fputs("\033[?25l", stderr);
		printf("\033[1;1H");
		printf("\033[21C\033[30m\033[47m***AxiDraw grbl contraler***\033[0m\n");
		fputs("\033[30C\033[1B\033[0;31mUSER:\033[0m",stderr);
		fputs("\033[40;41m",stderr);
		system("whoami");
		fputs("\033[24C\033[0m",stderr);
		system("uname -s -n -r");
		getsystime();
		fputs("\033[9C",stderr);
		system("uname -v -o -i");
		printf("\033[3C\033[31mTerminal_size:%d row,%d col\tGcode file : %s\033[0m\n",size.ws_row,size.ws_col,argv[2]);
		fputs("workspace path:",stderr);system("pwd");printf("\033[KSerial : %s",serial);
		if(1)
		{	
			printf("\033[%d;%dH\n",SCROLL-1,1);
			for(i=0;i<SCROLLSTAR;i++)
			{
				fputs("_",stderr);
			}
			kkk=kk;
			fputs("\033[1C",stderr);
			for(kkk=0;SCROLL+kkk<=(size.ws_row-3);kkk++)
			{
				fputs("\033[1D\033[1B|",stderr);
			}
			printf("\033[65D\033[1A\n");
			for(i=0;i<SCROLLSTAR;i++)
			{
				fputs("_",stderr);
			}
			fputs("|",stderr);
			if((SCROLL+kk)<=(size.ws_row-4)){
				in++;
       			fgets(s_n1,150,fp);
				printf("\033[%d;%dH%s\n",12,8,"Axis locations:");
				printf("\033[%d;%dH%s%0.3f\n",13,9,"X-axis:",0.2345);
				printf("\033[%d;%dH%s%0.3f\n",14,9,"Y-axis:",12.34568);
				printf("\033[%d;%dH%s%3d\n",15,9,"Z-axis:",1);
				printf("\033[%d;%dH\n",SCROLL+kk,1);
				printf("%-3d%s %s",ii,">>>",s_n1);
				//printf("\033[%d;%dH%s%-3d%s -OK",SCROLL+kk+1,55,"Arduino",kk,":");
				printf("\033[%d;%dH%s ",SCROLL+kk+1,48,"Arduino:");
//read arduino serial date
				int i=1;
				while(i)
				{
					temp=0;
					fscanf(fps,"%c",&temp);
					if(temp!=0)
					{
						putchar(temp);
						//printf("%c",temp);
						i=1;
					}else{
						i=0;
					}
				}			
//over read arduino serial date
			}
			else{
				kk=0;
				in++;
       			fgets(s_n1,150,fp);
				printf("\033[2J");
				printf("\033[%d;%dH%s\n",12,8,"Axis locations:");
				printf("\033[%d;%dH%s%0.3f\n",13,9,"X-axis:",0.2345);
				printf("\033[%d;%dH%s%0.3f\n",14,9,"Y-axis:",12.34568);
				printf("\033[%d;%dH%s%3d\n",15,9,"Z-axis:",1);
				printf("\033[%d;%dH\n",SCROLL+kk,1);
				printf("%-3d%s %s",ii,">>>",s_n1);
				//printf("\033[%d;%dH%s%-3d%s -OK",SCROLL+kk+1,48,"Arduino",kk,":");
				printf("\033[%d;%dH%s ",SCROLL+kk+1,48,"Arduino:");
//read arduino serial date
				int i=1;
				while(i)
				{
					temp=0;
					fscanf(fps,"%c",&temp);
					if(temp!='\n')
					{
						printf("%c",temp);
						i=1;
					}else{
						i=0;
					}
				}
//over read arduino serial date
   				}
			printf("\033[9;27HIn progress : %s",s_n1);
			ii++;
			kk++;
			usleep(3000);
			per=((float)(fline-line)/fline)*100;
			per+=1;
			printf("\033[8;30HBaud Rate :9600\tfline :%d  progress:[%3d%%]",fline,per);
			printf("\033[%d;%dHAccomplish: %d%sSurlpus: %d",size.ws_row-1,10,fline-line,"    ",line-1);
			for(i=0;i<ijk;++i){
				len_1= (float)((size.ws_col-17))/100;
				len = size.ws_col-17;
				blc=per*len_1;
				printf("\033[31m\033[%d;1H\033[Kprogress:[%3d%%][",size.ws_row,per);
				for(k=len;k>0;k--){
					printf(".");
				}
				printf("\033[%d;17H",size.ws_row);
				for(j=0;j<blc-1;++j){
					printf("=");
				}
				printf(">");
				printf("\033[%d;%dH%c",size.ws_row,size.ws_col,']');
			}
			printf("\033[0m");
			fflush(stdout);
		}
	}
	fclose(fps);;
	fclose(fp);
	fputs("\033[0m",stderr); 
	fputs("\033[?25h", stderr);
	return 0;
}
