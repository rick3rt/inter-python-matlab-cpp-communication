project(zeromq_sender)

add_executable(zeromq_sender_cpp sender.cpp)
exec_copy_to_bin_folder(zeromq_sender_cpp)

if(${MATLAB_FOUND})
    matlab_add_mex(
        NAME zeromq_sender_mex
        SRC sender.cpp
        R2018a
    )
    target_compile_definitions(zeromq_sender_mex PUBLIC -DMEX)
    exec_copy_to_bin_folder(zeromq_sender_mex)
endif()
