# CMake generated Testfile for 
# Source directory: /home/kate/catkin_ws/src/map_server
# Build directory: /home/kate/catkin_ws/build/map_server
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
ADD_TEST(_ctest_map_server_gtest_map_server_utest "/home/kate/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/jade/share/catkin/cmake/test/run_tests.py" "/home/kate/catkin_ws/build/test_results/map_server/gtest-map_server_utest.xml" "--return-code" "/home/kate/catkin_ws/devel/lib/map_server/map_server_utest --gtest_output=xml:/home/kate/catkin_ws/build/test_results/map_server/gtest-map_server_utest.xml")
ADD_TEST(_ctest_map_server_rostest_test_rtest.xml "/home/kate/catkin_ws/build/catkin_generated/env_cached.sh" "/usr/bin/python" "/opt/ros/jade/share/catkin/cmake/test/run_tests.py" "/home/kate/catkin_ws/build/test_results/map_server/rostest-test_rtest.xml" "--return-code" "/opt/ros/jade/share/rostest/cmake/../../../bin/rostest --pkgdir=/home/kate/catkin_ws/src/map_server --package=map_server --results-filename test_rtest.xml --results-base-dir \"/home/kate/catkin_ws/build/test_results\" /home/kate/catkin_ws/src/map_server/test/rtest.xml ")
