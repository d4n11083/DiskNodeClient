cmake_minimum_required(VERSION 3.12)
project(DiskNode)

set(CMAKE_CXX_STANDARD 14)

add_executable(DiskNode main.cpp TECMFSNODECliente.cpp TECMFSNODECliente.h JSON/json.hpp DEFINITIONS.h TECMFS.cpp TECMFS.h PUGIXML/pugixml.hpp PUGIXML/pugiconfig.hpp PUGIXML/pugixml.cpp)