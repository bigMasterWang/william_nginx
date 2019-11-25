this is my first step
hello world!

# 目录结构规划
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
* makefile：编译项目入口脚本，总体控制
* config.mk：配置脚本，被makefile包含，以后可能存在一些变动的东西，因此单独抽离出来
* common.mk：最核心的编译脚本，定义makefile的编译规则，依赖等，并且各个子目录中的.c文件都会用到，通用性很强

每个子目录下都有makefile文件，都会包含common.mk，实现自己子目录下.c文件的编译