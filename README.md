How to use?

For MacOS and Linux:

- Install: 
* git clone https://github.com/ValeriiSudakov/TaskManager.git 
* cd TaskManager
* git checkout production
* cmake -DBoost_NO_SYSTEM_PATHS=ON\
-DBOOST_LIBRARYDIR=/<path_to_your_boost_installation>/boost/stage/lib\
-DBOOST_ROOT=/<path_to_your_boost_installation>/boost\
-DProtobuf_ROOT=/<path_to_your_protobuf_installation>/protobuf\
-DGRPC_ROOT=/<path_to_your_grpc_installatino>/grpc\
.
* cmake --build .

- Launch:
* ./Server
* ./Client
