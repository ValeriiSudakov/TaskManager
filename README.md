How to use?

For MacOS and Linux:

- Install: 
* git clone https://github.com/ValeriiSudakov/TaskManager.git 
* cd TaskManager
* git checkout production
* cmake -DBoost_NO_SYSTEM_PATHS=ON\ \
-DBOOST_ROOT=/<path_to_your_boost_lib>/boost\ \
-DProtobuf_ROOT=/<path_to_your_protobuf_lib>/protobuf\ \
-DGRPC_ROOT=/<path_to_your_grpc_lib>/grpc\ \
-DGTEST_ROOT=/<path_to_your_gtest_lib>/googletest\ \
-DABSL_ROOT=/<path_to_your_absl_lib>/abseil\ \
.
* cmake --build .

- Launch:
* ./Server
* ./Client
