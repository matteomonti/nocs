cmake_minimum_required (VERSION 3.8.2)

# Nocs Version
set (NOCS_MAJOR    1)
set (NOCS_MINOR    0)
set (NOCS_REVISION 0)
set (NOCS_VERSION ${NOCS_MAJOR}.${NOCS_MINOR}.${NOCS_REVISION})

project (nocs LANGUAGES CXX VERSION ${NOCS_VERSION} DESCRIPTION "Nocs (Not Only Colliding Sphere) library")
set (CMAKE_CXX_STANDARD 14)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

add_definitions (-DMAJOR=${NOCS_MAJOR} -DMINOR=${NOCS_MINOR} -DREVISION=${NOCS_REVISION})

#################################################################
#                         COMPILE OPTIONS                       #
#################################################################

option (GRAPHICS     "Enable graphics                support" OFF )

#################################################################
#                         SETTING VARIABLES                     #
#################################################################

set (CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake/Modules/" ${CMAKE_MODULE_PATH})

if ( NOT APPLE )
  set (CMAKE_SKIP_BUILD_RPATH             FALSE )
  set (CMAKE_BUILD_WITH_INSTALL_RPATH     FALSE )
  set (CMAKE_INSTALL_RPATH_USE_LINK_PATH  TRUE  )
endif()

# make sure that the default is a RELEASE
set(default_build_type "Release")
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
  set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE STRING "Choose the type of build." FORCE)
  # Set the possible values of build type for cmake-gui
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

if ( CMAKE_COMPILER_IS_GNUCXX )
  add_compile_options (-Wall -Wextra -Wno-unused-result -Wno-unknown-pragmas -Wfatal-errors -Wno-narrowing -Wpedantic)
  string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  string (REGEX REPLACE "-O0" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
  set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DDEBUG" )
  set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG" )
endif()

if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
  set (CMAKE_CXX_FLAGS "-Wno-deprecated -Wno-writable-strings ${CMAKE_CXX_FLAGS}")
  string (REGEX REPLACE "-O0" "-Og" CMAKE_CXX_FLAGS_DEBUG ${CMAKE_CXX_FLAGS_DEBUG})
  string (REGEX REPLACE "-O3" "-Ofast" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  add_definitions (-D__apple__)
endif()

if (MSVC)
  set (CMAKE_CXX_FLAGS "/wd4013 /wd4018 /wd4028 /wd4047 /wd4068 /wd4090 /wd4101 /wd4113 /wd4133 /wd4190 /wd4244 /wd4267 /wd4305 /wd4477 /wd4996 /wd4819 /fp:fast ${CMAKE_CXX_FLAGS}")
  string (REGEX REPLACE "/O2" "/Ox" CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  add_definitions (-D_CRT_RAND_S)
  add_definitions (-DNOMINMAX)
  add_definitions (-D_USE_MATH_DEFINES)
  add_definitions (-D_CRT_SECURE_NO_DEPRECATE -D_SCL_SECURE_NO_WARNINGS)
  set (CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
endif()


include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-march=native" COMPILER_SUPPORTS_MARCH_NATIVE)
if (COMPILER_SUPPORTS_MARCH_NATIVE)
  if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
  endif()
endif()

#################################################################
#                         PARSE OPTIONS                         #
#################################################################

if (GRAPHICS)
  find_package(OpenGL REQUIRED)
  find_package(GLUT REQUIRED)
  set(linked_libs ${OPENGL_gl_LIBRARY} ${OPENGL_glu_LIBRARY} ${OPENGL_LIBRARIES} ${GLUT_LIBRARIES})
  include_directories(${OPENGL_INCLUDE_DIRS})
  include_directories(${GLUT_INCLUDE_DIR})
  message (STATUS "Viewer enabled")
else()
  message (STATUS "Viewer disabled")
endif()

#################################################################
#                         SETTING DIRECTORIES                   #
#################################################################

set(SRC_DIR    ${CMAKE_SOURCE_DIR}/src          CACHE PATH "Path where find cpp files"                        )
set(TEST_DIR   ${CMAKE_SOURCE_DIR}/test         CACHE PATH "Path where find test files"                       )
set(OBJ_DIR    ${CMAKE_SOURCE_DIR}/obj          CACHE PATH "Path where obj will be installed"            FORCE)
set(OUT_DIR    ${CMAKE_SOURCE_DIR}/bin          CACHE PATH "Path where outputs will be installed"        FORCE)
set(LIB_DIR    ${CMAKE_SOURCE_DIR}/lib          CACHE PATH "Path where lib will be installed"            FORCE)
set(INST_DIR   ${CMAKE_SOURCE_DIR}/share/byron  CACHE PATH "Path where cmake configs will be installed"  FORCE)

set(nocslib nocs)

file(GLOB_RECURSE SRC    "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE EXE    "${SRC_DIR}/*.cpp")

include_directories(${SRC_DIR})
include_directories(${TEST_DIR})

string(REPLACE " " ";" CMAKE_CXX_FLAGS_LIST ${CMAKE_CXX_FLAGS})

#################################################################
#                          SUMMARY                              #
#################################################################



message(STATUS ""                                                                    )
message(STATUS "=================== nocs configuration Summary =================="   )
message(STATUS "   nocs version: ${NOCS_MAJOR}.${NOCS_MINOR}.${NOCS_REVISION}"       )
message(STATUS ""                                                                    )
message(STATUS "   C++ :"                                                            )
message(STATUS "      C++ Compiler : ${CMAKE_CXX_COMPILER}"                          )
message(STATUS "      C++ flags    :"                                                )
foreach(FLAG ${CMAKE_CXX_FLAGS_LIST})
  message(STATUS "                    * ${FLAG}"                                     )
endforeach(FLAG)
if (${CMAKE_BUILD_TYPE} MATCHES "Release")
  foreach(FLAG ${CMAKE_CXX_FLAGS_RELEASE})
    message(STATUS "                    * ${FLAG}"                                   )
  endforeach(FLAG)
elseif (${CMAKE_BUILD_TYPE} MATCHES "Debug")
  foreach(FLAG ${CMAKE_CXX_FLAGS_DEBUG})
    message(STATUS "                    * ${FLAG}"                                   )
  endforeach(FLAG)
endif()
message(STATUS "      Linker flags : "                                               )
foreach(FLAG ${linked_libs})
  message(STATUS "                    * ${FLAG}"                                     )
endforeach(FLAG)
message(STATUS ""                                                                    )
message(STATUS "   Graphic   support : ${GRAPHICS}"                                  )
message(STATUS ""                                                                    )

#################################################################
#                         MAIN RULES                            #
#################################################################

add_library(${nocslib} SHARED ${SRC} ${HEADER})
set_property(TARGET ${nocslib} PROPERTY POSITION_INDEPENDENT_CODE ON)
if (GRAPHICS)
  target_compile_definitions(${nocslib} PRIVATE __graphics__)
endif()
target_link_libraries(${nocslib} ${linked_libs})

# mainexec
add_custom_target(exec)
add_executable(main ${SRC_DIR}/main.cpp)
target_link_libraries(main ${linked_libs} ${nocslib})
target_compile_definitions(main PRIVATE __main__)
if (GRAPHICS)
  target_compile_definitions(main PRIVATE __graphics__)
endif()
add_dependencies(exec main)

# testexec
add_custom_target(Testing)
add_executable(Test ${TEST_DIR}/test.cpp)
target_link_libraries(Test ${linked_libs} ${nocslib})
target_compile_definitions(Test PRIVATE __test__)
add_dependencies(Testing Test)

#################################################################
#                          INSTALLERS                           #
#################################################################

install(TARGETS ${nocslib}    EXPORT nocsTargets
                              RUNTIME DESTINATION ${OUT_DIR}
                              LIBRARY DESTINATION ${LIB_DIR}
                              ARCHIVE DESTINATION ${LIB_DIR}
                              PUBLIC_HEADER DESTINATION ${LIB_DIR}/include
                              COMPONENT dev
                              )

install(TARGETS main          DESTINATION ${OUT_DIR})
install(TARGETS Test          DESTINATION ${OUT_DIR})

#################################################################
#                          EXPORT NOCS                          #
#################################################################

install (EXPORT nocsTargets
         FILE nocsTargets.cmake
         NAMESPACE nocs::
         DESTINATION "${INST_DIR}"
        )

# Export the package for use from the build-tree (this registers the build-tree with a global CMake-registry)
export (PACKAGE nocs)

# Create the nocsConfig.cmake
# First of all we compute the relative path between the cmake config file and the include path
file (RELATIVE_PATH REL_INCLUDE_DIR "${INST_DIR}" "${LIB_DIR}/include")
set (CONF_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
configure_file (nocsConfig.cmake.in "${PROJECT_BINARY_DIR}/nocsConfig.cmake" @ONLY)
set (CONF_INCLUDE_DIRS "\${nocs_CMAKE_DIR}/${REL_INCLUDE_DIR}")
configure_file (nocsConfig.cmake.in "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/nocsConfig.cmake" @ONLY)

# Create the nocsConfigVersion.cmake
include(CMakePackageConfigHelpers)
write_basic_package_version_file ("${PROJECT_BINARY_DIR}/nocsConfigVersion.cmake"
                                  COMPATIBILITY SameMajorVersion
                                 )

install (FILES
         "${PROJECT_BINARY_DIR}${CMAKE_FILES_DIRECTORY}/nocsConfig.cmake"
         "${PROJECT_BINARY_DIR}/nocsConfigVersion.cmake"
         DESTINATION "${INST_DIR}"
         )

