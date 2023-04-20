cmake_minimum_required(VERSION 3.10)
project(ipc_example)

# =============================================================================
# Setup Conan Package Manager

# Bootstrap Conan
list(APPEND CMAKE_MODULE_PATH ${CMAKE_BINARY_DIR})
list(APPEND CMAKE_PREFIX_PATH ${CMAKE_BINARY_DIR})

if(NOT EXISTS "${CMAKE_BINARY_DIR}/conan.cmake")
    message(STATUS "Downloading conan.cmake from https://github.com/conan-io/cmake-conan")
    file(DOWNLOAD "https://raw.githubusercontent.com/conan-io/cmake-conan/0.18.1/conan.cmake"
        "${CMAKE_BINARY_DIR}/conan.cmake"
        TLS_VERIFY ON)
endif()

include(${CMAKE_BINARY_DIR}/conan.cmake)

# Configure conan
conan_cmake_configure(REQUIRES libsodium/1.0.18
    zeromq/4.3.4
    zmqpp/4.2.0
    GENERATORS cmake_find_package_multi)

foreach(TYPE ${CMAKE_CONFIGURATION_TYPES})
    conan_cmake_autodetect(settings BUILD_TYPE ${TYPE})
    conan_cmake_install(PATH_OR_REFERENCE .
        BUILD missing
        REMOTE conancenter
        SETTINGS ${settings})
endforeach()

# =============================================================================
# utility to copy executables to bin folder
function(exec_copy_to_bin_folder)
    add_custom_command(TARGET ${PROJECT_NAME}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CMAKE_SOURCE_DIR}/bin/
        COMMAND ${CMAKE_COMMAND} -E copy_if_different $<TARGET_FILE:${PROJECT_NAME}> ${CMAKE_SOURCE_DIR}/bin/
        COMMAND ${CMAKE_COMMAND} -E $<IF:$<CONFIG:Debug>,copy_if_different,true> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.pdb ${CMAKE_SOURCE_DIR}/bin/
        COMMAND ${CMAKE_COMMAND} -E $<IF:$<CONFIG:RelWithDebInfo>,copy_if_different,true> $<TARGET_FILE_DIR:${PROJECT_NAME}>/${PROJECT_NAME}.pdb ${CMAKE_SOURCE_DIR}/bin/
    )
endfunction()

# =============================================================================
# PROJECT CONFIGURATION
# =============================================================================
find_package(zmqpp)

# setup common include dirs and libraries
include_directories(BEFORE include)
link_libraries(zmqpp::zmqpp)

# =============================================================================
# add subdirs
add_subdirectory(sender)
add_subdirectory(receiver)

# =============================================================================
# copy targets to bin folder
# Define the output directory for built targets
# set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)
# set(LIBRARY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/lib)

# # Define the output directory for copied targets
# set(COPY_OUTPUT_PATH ${CMAKE_BINARY_DIR}/copy)

# Create a function to copy all built targets to the output directory
# function(copy_targets)
# add_custom_command(
# TARGET ${CMAKE_PROJECT_NAME} POST_BUILD
# COMMAND ${CMAKE_COMMAND} -E make_directory ${COPY_OUTPUT_PATH}
# COMMAND ${CMAKE_COMMAND} -E copy_directory ${EXECUTABLE_OUTPUT_PATH} ${COPY_OUTPUT_PATH}
# COMMAND ${CMAKE_COMMAND} -E copy_directory ${LIBRARY_OUTPUT_PATH} ${COPY_OUTPUT_PATH}
# )
# endfunction()

# Call the copy_targets function to copy all targets after they are built
# copy_targets()