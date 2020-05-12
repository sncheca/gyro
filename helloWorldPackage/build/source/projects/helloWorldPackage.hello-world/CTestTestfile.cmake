# CMake generated Testfile for 
# Source directory: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world
# Build directory: /Users/sofia/Documents/GitHub/gyro/helloWorldPackage/build/source/projects/helloWorldPackage.hello-world
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
if("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
  add_test(helloWorldPackage.hello-world_test "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test")
  set_tests_properties(helloWorldPackage.hello-world_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/max-api/script/cmakepp.cmake;5668;_add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;65;add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;0;;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;39;include;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
  add_test(helloWorldPackage.hello-world_test "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/helloWorldPackage.hello-world_test")
  set_tests_properties(helloWorldPackage.hello-world_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/max-api/script/cmakepp.cmake;5668;_add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;65;add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;0;;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;39;include;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
  add_test(helloWorldPackage.hello-world_test "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/MinSizeRel/helloWorldPackage.hello-world_test")
  set_tests_properties(helloWorldPackage.hello-world_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/max-api/script/cmakepp.cmake;5668;_add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;65;add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;0;;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;39;include;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;0;")
elseif("${CTEST_CONFIGURATION_TYPE}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
  add_test(helloWorldPackage.hello-world_test "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/tests/RelWithDebInfo/helloWorldPackage.hello-world_test")
  set_tests_properties(helloWorldPackage.hello-world_test PROPERTIES  _BACKTRACE_TRIPLES "/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/max-api/script/cmakepp.cmake;5668;_add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;65;add_test;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/min-api/test/min-object-unittest.cmake;0;;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;39;include;/Users/sofia/Documents/GitHub/gyro/helloWorldPackage/source/projects/helloWorldPackage.hello-world/CMakeLists.txt;0;")
else()
  add_test(helloWorldPackage.hello-world_test NOT_AVAILABLE)
endif()
