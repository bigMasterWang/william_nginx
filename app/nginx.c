#include <stdio.h>
#include <unistd.h>

#include "ngx_func.h"
#include "ngx_signal.h"


//配置文件是第一个要解决的问题
//文本文件，除了注释之外不用中文
//以#号为注释行
int main()
{
	printf("william_nginx开始启动");
	myconf();
	mysignal();
	printf("william_nginx程序退出");
	return 0;
}
