#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "ngx_global.h"
#include "ngx_commonFunc.h"

bool ngx_copy_environ()
{
	int i;
	//ͳ�ƻ������������ڴ��С
	for (i = 0; environ[i]; i++)
	{
		//ĩβ��\0Ҳ��ռ��ʵ�ʿռ��
		ngx_environ_len += strlen(environ[i])+1;
	}
	//����һ���µĿռ䣬���Ҹ�ֵΪ0
	ngx_environ_place = new char[ngx_environ_len];
	if (ngx_environ_place == NULL)
		return false;
	memset(ngx_environ_place, 0, ngx_environ_len);

	//��������һ��ָ�룬ָ����οռ���׵�ַ
	char* temp = ngx_environ_place;

	//����������һ��һ��Ŀ������µ��ڴ���ȥ
	for (i = 0; environ[i]; i++)
	{
		//ǧ�������ĩβ��0
		size_t itemSize = strlen(environ[i])+1;
		strcpy(temp, environ[i]);
		environ[i] = temp;
		temp += itemSize;
	}
	return true;
}

bool ngx_set_title(const char* newTitle)
{
	//�������ñ���,��Ϊ���в���Ҳ����ʾ��cmd��
	//�����ֱ����Ϊ���е����в���ȫ���Ѿ����������������Ѿ�������

	//1�������±���ĳ���
	size_t titleLen = strlen(newTitle) + 1;

	//2������������ڴ��С
	int i;
	size_t argvLen = 0;
	for (i = 0; ngx_argv[i]; i++)
	{
		argvLen += strlen(ngx_argv[i]) + 1;
	}

	//3�����±�����ڴ��С �� �����ͻ��������Ĵ�С֮�� ���
	if (titleLen > (titleLen + ngx_environ_len))
	{
		printf("����̫��");
		return false;
	}
	//4����[0]����Ϊ�����ƣ�[1]ΪNULL
	strcpy(ngx_argv[0], newTitle);
	ngx_argv[1] = NULL;

	//5���������б�ͻ��������б��� ���˱����� ��������λ��ȫ����Ϊ0
	size_t releaseSpaceLen = titleLen + ngx_environ_len - titleLen;
	memset(ngx_argv[0] + titleLen, 0, releaseSpaceLen);
	return true;
} 
