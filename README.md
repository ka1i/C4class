# C/C++ language course code

axidraw.c 挺好玩的

mouse.c 获取鼠标坐标

计算机操作系统课程作业 Computer_operating_system_class 

c++编程基础 cstring

unix网络编程 CS-unix_sock

c动态链接库学习 shard_lib_learning



```
//like this "Thu Jul 19 00:09:09 2018"
string getsystime(){
	string now_t;
	time_t t;
	time(&t);
	//cout<<ctime(&t);
	//cout<<"START_SYSTEM-TIME:"<<ctime(&t);
	//printf("\033[15C%s%s","START_SYSTEM-TIME:",ctime(&t));
	now_t=ctime(&t);
	return now_t.erase(24,sizeof(now_t));
}
//get terminal size (height*width)
void terminal_size(){
      
    if (isatty(STDOUT_FILENO) == 0)  
        exit(1);  
    if(ioctl(STDOUT_FILENO, TIOCGWINSZ, &size)<0) 
    {
        cerr<<"ioctl TIOCGWINSZ error"<<endl;
        exit(1);
    } 
	//stringstream rt;
	//rt<<size.ws_row<<'*'<<size.ws_col;
	//return rt.str(); 
}
void info(int h,int w){
	cout<<"\033[?25l";//hide
	cout<<"\033[1;1H";
	cout<<"\033["<<w/4-12<<"C\033[30m\033[47m***Personal-Assistant***\033[0m"<<endl;
	cout<<"\033[K";cout.flush();
	for(int i=0;i<w/2;i++){cout<<"*";}
	cout<<endl;
	cout<<"*\033[0;31mAuther:\033[0m"<<"\033[4mMardan\033[0m"<<"\033[3;"<<w/2<<"H*"<<endl;
	cout<<"*\033[0;31mSystem-Time:\033[0m"<<getsystime()<<"\033[4;"<<w/2<<"H*"<<endl;
	cout<<"*\033[0;31mSystenInfo:\033[0m";cout.flush();
	system("uname -n -s -m");
	cout<<"\033[5;"<<w/2<<"H*"<<endl;
	for(int i=0;i<w/2;i++){cout<<"*";}
	cout<<"\033[?25h"<<endl;//show
}
/*
 * ===============================================ANSI控制码的说明 
\33[0m 关闭所有属性 
\33[1m 设置高亮度 
\33[4m 下划线 
\33[5m 闪烁 
\33[7m 反显 
\33[8m 消隐 
\33[30m -- \33[37m 设置前景色 
\33[40m -- \33[47m 设置背景色 
\33[nA 光标上移n行 
\33[nB 光标下移n行 
\33[nC 光标右移n行 
\33[nD 光标左移n行 
\33[y;xH设置光标位置 
\33[2J 清屏 
\33[K 清除从光标到行尾的内容 
\33[s 保存光标位置 
\33[u 恢复光标位置 
\33[?25l 隐藏光标 
\33[?25h 显示光标
\x1b[2J\x1b[$;1H    $表示行位

 * 字颜色:30-----------37
30:黑 
31:红 
32:绿 
33:黄 
34:蓝色 
35:紫色 
36:深绿 
37:白色 

字背景颜色范围:40----47
40:黑 
41:深红 
42:绿 
43:黄色 
44:蓝色 
45:紫色 
46:深绿 
47:白色

字体加亮颜色:90------------97
90:黑 
91:红 
92:绿 
93:黄 
94:蓝色 
95:紫色 
96:深绿 
97:白色

背景加亮颜色范围:100--------------------107
40:黑 
41:深红 
42:绿 
43:黄色 
44:蓝色 
45:紫色 
46:深绿 
47:白色
*/
```