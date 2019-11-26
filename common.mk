ifeq ($(DEBUG),true)
CC = gcc -g
VERSION = debug
else
CC = gcc
VERSION = release
endif


#表示扫描当前目录下所有.c文件
SRCS = $(wildcard *.c)

#替换.c为.o
#nginx.c ngx_conf.c
OBJS = $(SRCS:.c=.o)
#替换.c为.d
#nginx.d ngx_conf.d
DEPS = $(SRCS:.c=.d)

#指定bin文件的位置
BIN := $(addprefix $(BUILD_ROOT)/,$(BIN))

#定义存放obj文件的目录，目录统一到一个位置才方便后续链接
LINK_OBJ_DIR = $(BUILD_ROOT)/app/link_obj
DEP_DIR = $(BUILD_ROOT)/app/dep

#-p是递归创建目录
$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))

#把目标文件生成到上属文件目录去，利用函数addprefix增加个前缀
#/mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/nginx.o 和 ngx_conf.o
OBJS := $(addprefix $(LINK_OBJ_DIR)/,$(OBJS))
#/mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/nginx.d 和 ngx_conf.d
DEPS := $(addprefix $(DEP_DIR)/,$(DEPS))

#找到目录中所有的.o文件
LINK_OBJ = $(wildcard &(LINK_OBJ_DIR)/*.o)
#子目录里面.o文件可能还不存在
LINK_OBJ += $(OBJS)



all:&(DEPS) &(OBJS) &(BIN)

ifneq ("$(wildcard $(DEPS))","")
include $(DEPS)
endif


$(BIN):$(LINK_OBJ)
	@echo "-----------build $(VERSION) mode -----------"
	$(CC) -o $@ $^

$(LINK_OBJ_DIR)/%.o:%.c
	$(CC) -I(INCLUDE_PATH) -o $@ -c $(filter %.c,$^)


$(DEP_DIR)/%.d:%.c
	echo -n $(LINK_OBJ_DIR)/ > $@
#-MM是依赖关系
	gcc -I$(INCLUDE_PATH) -MM $^ >> $@