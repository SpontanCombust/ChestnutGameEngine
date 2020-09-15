# ========================================= #
#
#			BombermanReworked Makefile
#
#			@author SpontanCombust
#			@date 	15-09-2020
#
# ========================================= #


# -------------------------------------------------------------------------------
PROGRAM_NAME=BombermanReworked
os=linux
# -------------------------------------------------------------------------------
LINUX_DEPENDENCIES_INSTALL=apt-get install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-ttf-dev
WINDOWS_DEPENDENCIES_INSTALL=
# -------------------------------------------------------------------------------
LINUX_COMPILER=g++
LINUX_CPPFLAGS=-Wall -O2
LINUX_EXEC_PATH=bin/linux
LINUX_EXEC_EXTENSION=o

WINDOWS_COMPILER=
WINDOWS_CPPFLAGS=-Wall -O2
WINDOWS_EXEC_PATH=bin/windows
WINDOWS_EXEC_EXTENSION=exe
# -------------------------------------------------------------------------------
INCLUDE=-I./include
HEADERS=$(shell find include -name "*.hpp")
SOURCES=$(shell find src -name "*.cpp")
# -------------------------------------------------------------------------------
PKG_CONFIG_START=pkg-config --cflags --libs
PKG_CONFIG_LIBS=sdl2 SDL2_image SDL2_mixer SDL2_ttf

ifeq ($(os),linux)
TARGET_DEPENDENCY_INSTALL=$(LINUX_DEPENDENCIES_INSTALL)
TARGET_COMPILER=$(LINUX_COMPILER)
TARGET_CPPFLAGS=$(LINUX_CPPFLAGS)
TARGET_EXEC_PATH=$(LINUX_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(LINUX_EXEC_EXTENSION)
else ifeq ($(os),windows)
TARGET_DEPENDENCY_INSTALL=$(WINDOWS_DEPENDENCIES_INSTALL)
TARGET_COMPILER=$(WINDOWS_COMPILER)
TARGET_CPPFLAGS=$(WINDOWS_CPPFLAGS)
TARGET_EXEC_PATH=$(WINDOWS_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(WINDOWS_EXEC_EXTENSION)
else
TARGET_DEPENDENCY_INSTALL=$(LINUX_DEPENDENCIES_INSTALL)
TARGET_COMPILER=$(LINUX_COMPILER)
TARGET_CPPFLAGS=$(LINUX_CPPFLAGS)
TARGET_EXEC_PATH=$(LINUX_EXEC_PATH)
TARGET_EXEC_EXTENSION=$(LINUX_EXEC_EXTENSION)
endif
# -------------------------------------------------------------------------------
.PHONY: help build debug release_dynamic release_static run clean

help:
	@echo "------------------------- HELP ----------------------------"
	@echo "make help		-	print this help"
	@echo "make install_deps	-	install dependency libraries"
	@echo "make debug		-	compile the code for debugging"
	@echo "make release_dynamic	-	compile the code, link dynamically and copy dependencies"
	@echo "make release_static	-	compile the code and link statically"
	@echo "make run		-	run the compiled program"
	@echo "make clean		-	clean up everything"
	@echo "-----------------------------------------------------------"
	@echo "os=linux		-	target platform is linux (default)"
	@echo "os=windows		-	target platform is windows"
	@echo "-----------------------------------------------------------"

install_deps:
	$(TARGET_DEPENDENCY_INSTALL)

debug:
	mkdir -p $(TARGET_EXEC_PATH)/Debug/
	$(TARGET_COMPILER) -Wall -g -o $(TARGET_EXEC_PATH)/Debug/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) `$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS)`

release_dynamic:
	mkdir -p $(TARGET_EXEC_PATH)/Release/
	$(TARGET_COMPILER) $(TARGET_CPPFLAGS) -o $(TARGET_EXEC_PATH)/Release/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) `$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS)`

release_static:
	mkdir -p $(TARGET_EXEC_PATH)/Release/
	$(TARGET_COMPILER) $(TARGET_CPPFLAGS) -o $(TARGET_EXEC_PATH)/Release/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION) $(INCLUDE) $(HEADERS) $(SOURCES) `$(PKG_CONFIG_START) $(PKG_CONFIG_LIBS) --static` -static

run:
	$(TARGET_EXEC_PATH)/Debug/$(PROGRAM_NAME).$(TARGET_EXEC_EXTENSION)

clean:
	rm -rf bin