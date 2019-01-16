CXX := C:/MinGW/bin/g++
CXXFLAGS := -g
LDFLAGS := -g

SRC := src
BIN := bin
OBJ := $(BIN)/obj

INCLUDE := -Iinclude/ -IA:/programming/libs/glm/include -IA:/programming/libs/glfw/include -IC:/VulkanSDK/1.1.82.1/Include
LINK := -LA:/programming/libs/glfw/lib-mingw-w64 -lglfw3 -LC:/VulkanSDK/1.1.82.1/Lib -lvulkan-1

SRC_FILES := $(shell find $(SRC)/ -type f -name '*.cpp')
OBJ_FILES := $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, $(SRC_FILES))

.PHONY: executable objects clean

executable: objects
	@$(CXX) $(LDFLAGS) $(LINK) $(OBJ_FILES) -o bin/vulkan-test.exe

objects: $(OBJ_FILES)
	@echo Finished compiling.

$(OBJ_FILES): $(OBJ)/%.o: $(SRC)/%.cpp
	@echo Compiling $<...
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE) -c -msse3 -o $@ $<

clean:
	rm -r $(BIN)/*