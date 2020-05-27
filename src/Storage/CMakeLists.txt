set(MODULE_NAME "Storage")

add_library(${MODULE_NAME}
  ./MySimpleStorage.cpp
)

target_include_directories(${MODULE_NAME} PUBLIC include)
