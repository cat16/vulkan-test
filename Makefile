#g++ from mingw64 gets very angry when you try to compile with vulkan...
#CXX := x86_64-w64-mingw32-g++
CXX := C:/MinGW/bin/g++
CXXFLAGS := -g -msse3
LDFLAGS := -g

SRC := src
BIN := bin
OBJ := $(BIN)/obj

EXEC_NAME = vulkan-test

INCLUDE := -Iinclude/ -IA:/programming/libs/glm/include -IA:/programming/libs/glfw/3.2.1/x64/include -IA:/programming/libs/VulkanSDK/1.1.82.1/Include
LINK := -LA:/programming/libs/glfw/3.2.1/x32/lib-mingw -LA:/programming/libs/VulkanSDK/1.1.82.1/Lib32 -lglfw3dll -lvulkan-1
DLL_LOCATIONS := A:/programming/libs/glfw/3.2.1/x32/lib-mingw/glfw3.dll

SRC_FILES := $(shell find $(SRC)/ -type f -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))
EXEC_FILES := $(BIN)/$(EXEC_NAME).exe
DLL_FILES := $(patsubst %,$(BIN)/%,$(notdir $(DLL_LOCATIONS)))

.PHONY: all clean clean-libs

all: $(EXEC_FILES) $(DLL_FILES)
	@echo Finished building all.

$(DLL_FILES):
	cp -v -f $(DLL_LOCATIONS) $(BIN)

$(EXEC_FILES): $(OBJ_FILES)
	@echo Linking $<...
	@$(CXX) $(LDFLAGS) $^ $(LINK) -o $@

$(OBJ_FILES): $(OBJ)/%.o: $(SRC)/%.cpp
	@echo Compiling $<...
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c -o $@ $<

clean:
	rm -r $(BIN)/*

clean-libs:
	rm -r $(DLL_FILES)