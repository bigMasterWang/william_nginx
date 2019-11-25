#项目编译根目录，通过export将变量声明为全局的
export BUILD_ROOT = $(shell pwd)

#头文件的路径
export INCLUDE_PATH = $(BUILD_ROOT)/_include

#定义我们要编译的目录
BUILD_DIR = $(BUILD_ROOT)/signal/ \
			$(BUILD_ROOT)/app/

#编译时是否生成调试信息，GUN调试器可以利用该信息
export DEBUG = true