add_executable(ut-mysimplestorage
  MySimpleStorageTests.cpp
)
target_link_libraries(ut-mysimplestorage
  gtest_main
  Log
  Storage
)
add_test(MySimpleStorageTests ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/ut-mysimplestorage)
