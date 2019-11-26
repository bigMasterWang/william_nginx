#include <stdio.h>
#include <unistd.h>

#include "ngx_func.h"
#include "ngx_signal.h"



int main(int argc, char* const* argv)
{
	printf("william_nginx开始启动");
	myconf();
	mysignal();

	printf("william_nginx程序退出");

	return 0;
}
