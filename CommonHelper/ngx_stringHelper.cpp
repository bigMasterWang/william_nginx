#include <stdio.h>
#include <string.h>
#include "ngx_stringHelper.h"
void Rtrim(char* string)
{
	size_t len = 0;
	if (string == NULL)
		return;
	len = strlen(string);
	while (len > 0 && string[len - 1] == ' ')
		string[--len] = 0;
	return;
}
void Ltrim(char* string)
{
	size_t len = 0;
	char* p_temp = string;
	//不以空格开头
	if ((*p_temp) != ' ')
		return;

	//找到第一个不为空格的位置
	while ((*p_temp) != '\0')
	{
		if (*(p_temp) == '	')
			p_temp++;
		else
			break;
	}
	//全是空格
	if ((*p_temp) == '\0')
	{
		*string = '\0';
		return;
	}

	char* p_temp2 = string;
	while ((*p_temp) != '\0')
	{
		(*p_temp2) = (*p_temp);
		p_temp++;
		p_temp2++;
	}
	*p_temp2 = '\0';
	return;
}
