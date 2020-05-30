set(MODULE_NAME "Interpreter")

add_library(${MODULE_NAME}
  ./TextInterpreter.cpp
)

target_include_directories(${MODULE_NAME} PUBLIC include)
target_link_libraries(${MODULE_NAME} PUBLIC Storage Log)
