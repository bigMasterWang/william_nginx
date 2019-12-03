#ifndef __NGX__COMMONFUNC__H__
#define __NGX__COMMONFUNC__H__

//给环境变量换地址
bool ngx_copy_environ();
//设置新的标题
bool ngx_set_title(const char* newTitle);

extern int ngx_environ_len;
extern char* ngx_environ_place;
extern char** ngx_argv;

#endif
