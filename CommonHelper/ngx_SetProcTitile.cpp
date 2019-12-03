#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ngx_global.h"
#include "ngx_commonFunc.h"

bool ngx_copy_environ()
{
	int i;
	//统计环境变量所在内存大小
	for (i = 0; environ[i]; i++)
	{
		//末尾的\0也是占用实际空间的
		ngx_environ_len += strlen(environ[i])+1;
	}
	//声明一个新的空间，并且赋值为0
	ngx_environ_place = new char[ngx_environ_len];
	if (ngx_environ_place == NULL)
		return false;
	memset(ngx_environ_place, 0, ngx_environ_len);

	//另外声明一个指针，指向这段空间的首地址
	char* temp = ngx_environ_place;

	//将环境变量一项一项的拷贝到新的内存中去
	for (i = 0; environ[i]; i++)
	{
		//千万别忘了末尾的0
		size_t itemSize = strlen(environ[i])+1;
		strcpy(temp, environ[i]);
		environ[i] = temp;
		temp += itemSize;
	}
	return true;
}

bool ngx_set_title(const char* newTitle)
{
	//重新设置标题,因为运行参数也会显示在cmd里
	//这里就直接认为所有的运行参数全部已经被保存起来或者已经不用了

	//1、计算新标题的长度
	size_t titleLen = strlen(newTitle) + 1;

	//2、计算参数的内存大小
	int i;
	size_t argvLen = 0;
	for (i = 0; ngx_argv[i]; i++)
	{
		argvLen += strlen(ngx_argv[i]) + 1;
	}

	//3、将新标题的内存大小 与 参数和环境变量的大小之和 相比
	if (titleLen > (titleLen + ngx_environ_len))
	{
		printf("名字太长");
		return false;
	}
	//4、将[0]设置为新名称，[1]为NULL
	strcpy(ngx_argv[0], newTitle);
	ngx_argv[1] = NULL;

	//5、将参数列表和环境变量列表中 除了标题外 ，其他的位置全部置为0
	size_t releaseSpaceLen = titleLen + ngx_environ_len - titleLen;
	memset(ngx_argv[0] + titleLen, 0, releaseSpaceLen);
	return true;
} 
