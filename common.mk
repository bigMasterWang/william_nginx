ifeq ($(DEBUG),true)
CC = gcc -g
VERSION = debug
else
CC = gcc
VERSION = release
endif


#��ʾɨ�赱ǰĿ¼������.c�ļ�
SRCS = $(wildcard *.c)

#�滻.cΪ.o
#nginx.c ngx_conf.c
OBJS = $(SRCS:.c=.o)
#�滻.cΪ.d
#nginx.d ngx_conf.d
DEPS = $(SRCS:.c=.d)

#ָ��bin�ļ���λ��
BIN := $(addprefix $(BUILD_ROOT)/,$(BIN))

#������obj�ļ���Ŀ¼��Ŀ¼ͳһ��һ��λ�òŷ����������
LINK_OBJ_DIR = $(BUILD_ROOT)/app/link_obj
DEP_DIR = $(BUILD_ROOT)/app/dep

#-p�ǵݹ鴴��Ŀ¼
$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))

#��Ŀ���ļ����ɵ������ļ�Ŀ¼ȥ�����ú���addprefix���Ӹ�ǰ׺
#/mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/nginx.o �� ngx_conf.o
OBJS := $(addprefix $(LINK_OBJ_DIR)/,$(OBJS))
#/mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/nginx.d �� ngx_conf.d
DEPS := $(addprefix $(DEP_DIR)/,$(DEPS))

#�ҵ�Ŀ¼�����е�.o�ļ�
LINK_OBJ = $(wildcard &(LINK_OBJ_DIR)/*.o)
#��Ŀ¼����.o�ļ����ܻ�������
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
#-MM��������ϵ
	gcc -I$(INCLUDE_PATH) -MM $^ >> $@