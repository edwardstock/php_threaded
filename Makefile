CXX             = g++
RM              = rm -f
CXX_FLAGS       = -Wall -c -I. -Iclasses/. -O2 -std=c++11

PREFIX			= /usr
LIBRARY_DIR		= $(shell php-config --extension-dir)
PHP_CONFIG_DIR	= /etc/php.d/

LD              = g++
LD_FLAGS        = -Wall -shared -O2
RESULT          = threaded.so

PHPINIFILE		= 30-threaded.ini

SOURCES			= $(wildcard *.cpp)
OBJECTS         = $(SOURCES:%.cpp=%.o)

all:	${OBJECTS} ${RESULT}

${RESULT}: ${OBJECTS}
		${LD} ${LD_FLAGS} -o $@ ${OBJECTS} -lphpcpp
clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

${OBJECTS}:
		${CXX} ${CXX_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}