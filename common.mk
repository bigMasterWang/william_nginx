ifeq ($(DEBUG),true)
CC = g++ -g
VERSION = debug
else
CC = g++
VERSION = release
endif

SRCS = $(wildcard *.cpp)
OBJS = $(SRCS:.cpp=.o)
DEPS = $(SRCS:.cpp=.d)

BIN:=$(addprefix $(BUILD_ROOT)/,$(BIN))

LINK_OBJ_DIR = $(BUILD_ROOT)/app/link_obj
DEP_DIR = $(BUILD_ROOT)/app/dep

$(shell mkdir -p $(LINK_OBJ_DIR))
$(shell mkdir -p $(DEP_DIR))

OBJS:=$(addprefix $(LINK_OBJ_DIR)/,$(OBJS))
DEPS:=$(addprefix $(DEP_DIR)/,$(DEPS))

LINK_OBJ = $(wildcard $(LINK_OBJ_DIR)/*.o)
LINK_OBJ += $(OBJS)

all:$(DEPS) $(OBJS) $(BIN)

ifneq ("$(wildcard $(DEPS))","")
include $(DEPS)
endif

$(BIN):$(LINK_OBJ)
	@echo "==========$(LINK_OBJ)================"
	$(CC) -o $@ $^
#	mv $(BUILD_ROOT)/nginx $(BIN_ROOT)/nginx
#	gcc -o nginx /mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/nginx.o /mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/ngx_conf.o /mnt/hgfs/LinuxSharedFolder/william_nginx/app/link_obj/ngx_signal.o

$(LINK_OBJ_DIR)/%.o:%.cpp
	$(CC) -I$(INCLUDE_ROOT) -o $@ -c $(filter %.cpp,$^)

$(DEP_DIR)/%.d:%.cpp
	echo -n $(LINK_OBJ_DIR)/ > $@
	gcc -I$(INCLUDE_ROOT) -MM $^ >> $@
