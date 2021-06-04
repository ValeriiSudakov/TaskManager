set(COMMON ${SRC_ROOT}/common)
set(CLI ${SRC_ROOT}/cli)
set(CORE ${SRC_ROOT}/core)

set(COMMON_INCLUDE_DIRS  ${COMMON} ${COMMON}/Task ${COMMON}/Task/Date ${COMMON}/Task/ID ${COMMON}/DTO ${COMMON}/DTO/Utils ${COMMON}/Service ${COMMON}/Utils)
set(CLI_INCLUDE_DIRS     ${CLI} ${CLI}/Service ${CLI}/Factory ${CLI}/States ${CLI}/States/EditSystemStates ${CLI}/States/InputStates
                         ${CLI}/States/ShowStates ${CLI}/States/Menus ${CLI}/StatesControllers)
set(CORE_INCLUDE_DIRS    ${CORE} ${CORE}/Service ${CORE}/Persister ${CORE}/Persister/Utils ${CORE}/Repository ${CORE}/Repository/Utils
                         ${CORE}/Repository/DTO ${CORE}/Repository/RepositoriesFactory ${CORE}/Repository/RepositoryController
                         ${CORE}/Repository/Storage ${CORE}/Repository/Task ${CORE}/Repository/Task/Date ${CORE}/Repository/Task/ID
                         ${CORE}/Repository/View)

############## common ########################################################
file(GLOB_RECURSE common_SOURCES "${SRC_ROOT}/common/*.cpp")
############## cli ########################################################
file(GLOB_RECURSE cli_SOURCES "${SRC_ROOT}/cli/*.cpp")
############## core ########################################################
file(GLOB_RECURSE core_SOURCES "${SRC_ROOT}/core/*.cpp")

############ Common #####################################################
add_library(common_lib ${common_SOURCES} ${service_proto_srcs} ${service_grpc_srcs})
target_include_directories(common_lib PUBLIC ${COMMON_INCLUDE_DIRS} ${PROTO_HDRS})
target_link_libraries(common_lib gRPC::grpc++ gRPC::grpc++_reflection ${Protobuf_LIBRARIES} proto_files)

############ CORE #####################################################
add_library(core_lib ${core_SOURCES})
target_include_directories(core_lib PUBLIC ${COMMON_INCLUDE_DIRS} ${CORE_INCLUDE_DIRS} ${PROTO_HDRS})
target_link_libraries(core_lib common_lib)

############ CLI #####################################################
add_library(cli_lib ${cli_SOURCES})
target_include_directories(cli_lib PUBLIC ${COMMON_INCLUDE_DIRS} ${CLI_INCLUDE_DIRS} ${PROTO_HDRS})
target_link_libraries(cli_lib common_lib core_lib)

############ Server #####################################################
add_executable(Server ${SRC_ROOT}/Server.cpp)
target_include_directories(Server PRIVATE ${COMMON_INCLUDE_DIRS} ${CORE_INCLUDE_DIRS} ${PROTO_HDRS})
target_link_libraries(Server common_lib core_lib)

############ Client #####################################################
add_executable(Client ${SRC_ROOT}/Client.cpp)
target_include_directories(Client PRIVATE ${COMMON_INCLUDE_DIRS} ${CLI_INCLUDE_DIRS} ${PROTO_HDRS})
target_link_libraries(Client common_lib cli_lib)