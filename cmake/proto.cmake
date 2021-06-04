set(PROTO_DIR ${PROJECT_SOURCE_DIR}/Proto)
file(GLOB_RECURSE PROTO_SOURCES CONFIGURE_DEPENDS ${PROTO_DIR}/*.proto)

find_package(gRPC REQUIRED)
message(STATUS "Using gRPC ${gRPC_VERSION}")

set(GENERATED_DIR ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(MAKE_DIRECTORY ${GENERATED_DIR})
include_directories(${GENERATED_DIR})

find_program(_GRPC_CPP_PLUGIN_EXECUTABLE grpc_cpp_plugin REQUIRED)

macro(compile_proto_file filename)
    get_filename_component(dirname ${filename} PATH)
    get_filename_component(basename ${filename} NAME_WE)

    add_custom_command(
            OUTPUT ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc
            DEPENDS ${Protobuf_PROTOC_EXECUTABLE} ${PROTO_DIR}/${basename}.proto
            COMMAND ${Protobuf_PROTOC_EXECUTABLE} ${filename}
            --cpp_out=${GENERATED_DIR}
            --grpc_out=${GENERATED_DIR}
            --plugin=protoc-gen-grpc=${_GRPC_CPP_PLUGIN_EXECUTABLE}
            -I ${PROTO_DIR}
            DEPENDS ${filename}
            VERBATIM
    )
endmacro(compile_proto_file)

foreach(proto_file ${PROTO_SOURCES})
    compile_proto_file(${proto_file})
    get_filename_component(basename ${proto_file} NAME_WE)
    set(proto_generated_files ${proto_generated_files} ${GENERATED_DIR}/${basename}.pb.cc ${GENERATED_DIR}/${basename}.grpc.pb.cc)
endforeach(proto_file)

SET_SOURCE_FILES_PROPERTIES(${proto_generated_files} PROPERTIES GENERATED TRUE)

add_library(proto_files STATIC ${proto_generated_files})
target_include_directories(proto_files PRIVATE ${GRPC_ROOT}/include ${ABSL_ROOT}/include)
