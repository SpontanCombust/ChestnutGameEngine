# ========================================= #
#
#			BombermanReworked Makefile
#
#			@author SpontanCombust
#			@date 	15-09-2020
#
#			made for GCC compiler
#
# ========================================= #


# -------------------------------------------------------------------------------
PROGRAM_NAME=BombermanReworked
os=linux 		# linux, windows
ver=debug 		# debug, release
link=dynamic	# dynamic, static
# -------------------------------------------------------------------------------
LINUX_DEPENDENCIES_INSTALL=apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
WINDOWS_DEPENDENCIES_INSTALL=
# -------------------------------------------------------------------------------

# -------------------------------------------------------------------------------
TARGET_COMPILER=g++
OPT_FLAGS_DEBUG=-Wall -g -DCHESTNUT_DEBUG
OPT_FLAGS_RELEASE=-O2
# -------------------------------------------------------------------------------
LINUX_EXEC_PATH=bin/linux
LINUX_EXEC_EXTENSION=o

WINDOWS_EXEC_PATH=bin/windows
WINDOWS_EXEC_EXTENSION=exe

EXEC_FOLDER_DEBUG=Debug
EXEC_FOLDER_RELEASE=Release
# -------------------------------------------------------------------------------
INCLUDE=-I./include
HEADERS=$(shell find include -name "*.hpp")
SOURCES=$(shell find src -name "*.cpp")
# -------------------------------------------------------------------------------
PKG_CONFIG_START=pkg-config --cflags --libs
PKG_CONFIG_LIBS=sdl2 SDL2_image SDL2_mixer SDL2_ttf
# -------------------------------------------------------------------------------

# -------------------------------------------------------------------------------
ifeq ($(os),linux)
TARGET_DEPENDENCY_INSTALL=$(LINUX_DEPENDENCIES_INSTALL)
TARGET_EXEC_PATH=$(LINUX_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(LINUX_EXEC_EXTENSION)
else ifeq ($(os),windows)
TARGET_DEPENDENCY_INSTALL=$(WINDOWS_DEPENDENCIES_INSTALL)
TARGET_EXEC_PATH=$(WINDOWS_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(WINDOWS_EXEC_EXTENSION)
else
TARGET_DEPENDENCY_INSTALL=$(LINUX_DEPENDENCIES_INSTALL)
TARGET_EXEC_PATH=$(LINUX_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(LINUX_EXEC_EXTENSION)
endif
# -------------------------------------------------------------------------------
ifeq ($(link),dynamic)
TARGET_PKG_CONFIG=`$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS)`
else ifeq ($(link),static)
TARGET_PKG_CONFIG=`$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS) --static`
else
TARGET_PKG_CONFIG=`$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS)`
endif
# -------------------------------------------------------------------------------
ifeq ($(link),dynamic)
TARGET_LINKING=
else ifeq ($(link),static)
TARGET_LINKING=-static
else
TARGET_LINKING=
endif
# -------------------------------------------------------------------------------

# -------------------------------------------------------------------------------
.PHONY: help build debug release_dynamic release_static run clean

help:
	@echo "------------------------- HELP ----------------------------"
	@echo "$$ make help - print this help"
	@echo "$$ make install_deps - install dependency libraries"
	@echo "$$ make build - compiles the project"
	@echo "    options: os, ver, link"
	@echo "    available os:	os=linux, os=windows; default: os=linux"
	@echo "    available ver:	ver=debug, ver=release; default: ver=debug"
	@echo "    available link:	link=dynamic, link=static; default: link=dynamic"
	@echo "$$ make run - run the compiled program"
	@echo "$$ make clean - clean up everything"
	@echo "-----------------------------------------------------------"

install_deps:
	$(TARGET_DEPENDENCY_INSTALL)

build:
ifeq ($(ver),debug)
	mkdir -p $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_DEBUG)/
	$(TARGET_COMPILER) $(OPT_FLAGS_DEBUG) -o $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_DEBUG)/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) $(TARGET_PKG_CONFIG) $(TARGET_LINKING)
else ifeq ($(ver),release)
	mkdir -p $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_RELEASE)/
	$(TARGET_COMPILER) $(OPT_FLAGS_RELEASE) -o $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_RELEASE)/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) $(TARGET_PKG_CONFIG) $(TARGET_LINKING)
else
	mkdir -p $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_DEBUG)/
	$(TARGET_COMPILER) $(OPT_FLAGS_DEBUG) -o $(TARGET_EXEC_PATH)/$(EXEC_FOLDER_DEBUG)/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) $(TARGET_PKG_CONFIG) $(TARGET_LINKING)
endif

run:
	$(TARGET_EXEC_PATH)/Debug/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION)

clean:
	rm -rf bin