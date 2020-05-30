add_executable(mt-textinterpreter
  TextInterpreterModuleTests.cpp
)
target_link_libraries(mt-textinterpreter
  gtest_main
  Log
  Interpreter
  Storage
)
add_test(TextInterpreterModuleTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/mt-textinterpreter)
