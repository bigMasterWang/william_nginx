#��Ŀ�����Ŀ¼��ͨ��export����������Ϊȫ�ֵ�
export BUILD_ROOT = $(shell pwd)

#ͷ�ļ���·��
export INCLUDE_PATH = $(BUILD_ROOT)/_include

#��������Ҫ�����Ŀ¼
BUILD_DIR = $(BUILD_ROOT)/signal/ \
			$(BUILD_ROOT)/app/

#����ʱ�Ƿ����ɵ�����Ϣ��GUN�������������ø���Ϣ
export DEBUG = true