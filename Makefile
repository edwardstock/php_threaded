RM                  = rm -f

ifdef CXX
 COMPILER			=	${CXX}
 LINKER				=	${CXX}
else
 COMPILER			=	g++
 LINKER			    =	g++
endif

COMPILER_FLAGS      = -Wall -g -c -I. -Iclasses/ -I$(shell php-config --include-dir) -std=c++11
LINKER_FLAGS        = -Wall -shared

PREFIX			    = /usr
LIBRARY_DIR		    = $(shell php-config --extension-dir)
PHP_CONFIG_DIR	    = /etc/php.d
PHPINIFILE		    = 30-threaded.ini



SOURCES			    = $(wildcard *.cpp) $(wildcard classes/*.cpp) $(wildcard classes/*.hpp)
OBJECTS             = $(SOURCES:%.cpp=%.o)

RESULT              = threaded.so

ifeq ($(shell uname -s),Darwin)
   	COMPILER_FLAGS += -stdlib=libc++
   	LINKER_FLAGS += -undefined dynamic_lookup
endif

ifdef inidir
	PHP_CONFIG_DIR = ${inidir}
endif

all:    ${OBJECTS} ${RESULT}

release: LINKER_FLAGS += -O2
release: COMPILER_FLAGS += -O2

${RESULT}: ${OBJECTS}
		${LINKER} ${LINKER_FLAGS} -o $@ ${OBJECTS} -lphpcpp

clean:
		${RM} *.obj *~* ${OBJECTS} ${RESULT}

${OBJECTS}:
		${COMPILER} ${COMPILER_FLAGS} -fpic -o $@ ${@:%.o=%.cpp}

install:
		cp -f ${RESULT} ${LIBRARY_DIR}
		$(shell ./isdir ${PHP_CONFIG_DIR} && cp -f ${PHPINIFILE} ${PHP_CONFIG_DIR})


