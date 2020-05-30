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

add_executable(ut-textinterpreter
  TextInterpreterUnitTests.cpp
)
target_link_libraries(ut-textinterpreter
  gmock_main
  mocks
  Log
  Interpreter
  Storage
)
add_test(TextInterpreterUnitTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ut-textinterpreter)
