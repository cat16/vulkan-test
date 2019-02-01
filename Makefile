# I/O Definitions

LIB_FOLDER := A:/programming/libs

SRC := src
INC := include
RSC := rsc
SDR := $(RSC)/shader
BIN := bin
OBJ := $(BIN)/obj
SPV := $(BIN)/shader

EXEC_NAME := vulkan-test

GLM := glm
GLFW := glfw/3.2.1/x32
VULKAN_SDK := VulkanSDK/1.1.82.1

INCLUDES := $(GLM)/include $(GLFW)/include $(VULKAN_SDK)/Include
LINK_LOCS := $(GLFW)/lib-mingw $(VULKAN_SDK)/Lib32
LINKS := glfw3dll vulkan-1
DLL_LOCS := $(GLFW)/lib-mingw/glfw3.dll

SHADER_FILE_NAME := shader
SHADER_EXTS := vert tesc tese geom frag comp

# Compiler Definitions

CXX := C:/MinGW/bin/g++
CXXFLAGS := -g -msse3
LDFLAGS := -g

GLSL := $(LIB_FOLDER)/$(VULKAN_SDK)/Bin32/glslangValidator

# Processed Definitions

INCLUDE_DIRS := -I$(INC) $(patsubst %,-I$(LIB_FOLDER)/%,$(INCLUDES))
LINK_DIRS := $(patsubst %,-L$(LIB_FOLDER)/%,$(LINK_LOCS))
LINK_LIBS := $(patsubst %,-l%,$(LINKS))

NOTHING :=
SPACE := $(NOTHING) $(NOTHING)

SRC_FILES := $(shell find $(SRC)/ -type f -name "*.cpp")
SHADER_FILES := $(shell find $(SDR)/ -type f $(subst $(SPACE)-name, -o -name,$(patsubst %,-name "*.%",$(SHADER_EXTS))))
OBJ_FILES := $(patsubst $(SRC)/%.cpp,$(OBJ)/%.o,$(SRC_FILES))
SPV_FILES := $(patsubst .%,$(SPV)/%.spv,$(suffix $(SHADER_FILES)))
EXEC_FILES := $(BIN)/$(EXEC_NAME).exe
DLL_FILES_SRC := $(patsubst %,$(LIB_FOLDER)/%,$(DLL_LOCS))
DLL_FILES := $(patsubst %,$(BIN)/%,$(notdir $(DLL_LOCS)))

# Phony Targets

.PHONY: all clean

# Build Targets

all: $(EXEC_FILES) $(SPV_FILES) $(DLL_FILES)
	@echo Finished building all.

$(DLL_FILES): $(DLL_FILES_SRC)
	@echo Copying $<...
	@cp -u $< $@

$(SPV_FILES): $(SPV)/%.spv: $(SDR)/$(SHADER_FILE_NAME).%
	@echo Compiling $<...
	@mkdir -p $(@D)
	@$(GLSL) -V -s -o $@ $<

$(EXEC_FILES): $(OBJ_FILES)
	@echo Linking $<...
	@$(CXX) $(LDFLAGS) $^ $(LINK_DIRS) $(LINK_LIBS) -o $@

$(OBJ_FILES): $(OBJ)/%.o: $(SRC)/%.cpp
	@echo Compiling $<...
	@mkdir -p $(@D)
	@$(CXX) $(CXXFLAGS) $(INCLUDE_DIRS) -c -o $@ $<

# Clean Targets

clean:
	rm -r $(BIN)/*