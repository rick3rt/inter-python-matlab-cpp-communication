project(zeromq_receiver)

add_executable(zeromq_receiver_cpp receiver.cpp)
exec_copy_to_bin_folder(zeromq_receiver_cpp)

if(${MATLAB_FOUND})
    matlab_add_mex(
        NAME zeromq_receiver_mex
        SRC receiver.cpp
        R2018a
    )
    target_compile_definitions(zeromq_receiver_mex PUBLIC -DMEX)
    exec_copy_to_bin_folder(zeromq_receiver_mex)
endif()
