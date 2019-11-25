this is my first step
hello world!

* _include：各种头文件
* app：主应用程序.c(main.c)以及一些核心文件，
	* link_obj：临时目录，存放临时的.o文件，不手工创建，后续使用makefile脚本创建
	* dep：临时目录，存放临时的.d依赖文件，能够告知系统那些相关文件发生变化，需要重新编译
	* nginx.c：主文件，main()入口函数
	* ngx_conf.c：普通的源码文件，跟主文件关系密切，有不值得单独放一个目录
* misc：准备专门存放杂合性的，不好归类的.c文件
* net：专门存放网络处理有关的
* proc：专门存放和进程处理有关的文件
* signal：专门存放和信号处理有关的文件
	* mgx_signal.c：一些测试代码
