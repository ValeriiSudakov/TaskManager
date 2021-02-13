############## protobuf ########################################################
find_package(Protobuf REQUIRED)
if(Protobuf_FOUND)
    message("Protobuf version is: ${Protobuf_VERSION}")
    include_directories(${Protobuf_INCLUDE_DIRS})
endif()


############## boost ########################################################
set(Boost_USE_STATIC_LIBS    OFF)  # only find static libs
#set(Boost_USE_DEBUG_LIBS     ON)   # ignore debug libs and
#set(Boost_USE_RELEASE_LIBS   ON)  # only find release libs
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)

set(Boost_NO_BOOST_CMAKE 1) # Since 1.70 Boost have its own FindBoost.cmake, which conflicts with bundled one. Avoiding the warning before we migrate to 1.70
find_package(Boost 1.68.0 REQUIRED COMPONENTS)

if(Boost_FOUND)
    message("Boost version is: ${Boost_VERSION}")
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIR})
endif()