set(OPENCL_FOUND ON CACHE BOOL "OpenCL library is found")
if(APPLE)
  set(OPENCL_LIBRARY "-framework OpenCL" CACHE STRING "OpenCL library")
  set(OPENCL_INCLUDE_DIR "" CACHE PATH "OpenCL include directory")
else(APPLE)
  set(OPENCL_LIBRARY "" CACHE STRING "OpenCL library")
  set(OPENCL_INCLUDE_DIR "${OpenCV_SOURCE_DIR}/3rdparty/include/opencl/1.2" CACHE PATH "OpenCL include directory")
endif(APPLE)
mark_as_advanced(OPENCL_INCLUDE_DIR OPENCL_LIBRARY)

if(OPENCL_FOUND)
  if(OPENCL_LIBRARY)
    set(HAVE_OPENCL_STATIC ON)
    set(OPENCL_LIBRARIES "${OPENCL_LIBRARY}")
  else()
    set(HAVE_OPENCL_STATIC OFF)
  endif()

  if(NOT HAVE_OPENCL_STATIC)
    try_compile(__VALID_OPENCL
      "${OpenCV_BINARY_DIR}"
      "${OpenCV_SOURCE_DIR}/cmake/checks/opencl.cpp"
      CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${OPENCL_INCLUDE_DIR}"
      OUTPUT_VARIABLE TRY_OUT
      )
    if(NOT TRY_OUT MATCHES "OpenCL is valid")
      message(WARNING "Can't use OpenCL")
      return()
    endif()
  endif()

  set(HAVE_OPENCL 1)

  if(WITH_OPENCL_SVM)
    set(HAVE_OPENCL_SVM 1)
  endif()

  set(OPENCL_INCLUDE_DIRS ${OPENCL_INCLUDE_DIR})

  find_path(CL_BLAS_ROOT_DIR
            NAMES include/clBLAS.h
            PATHS ENV CLAMDBLAS_PATH ENV ProgramFiles
            PATH_SUFFIXES clAmdBlas AMD/clAmdBlas
            DOC "clBLAS root directory"
            NO_DEFAULT_PATH)

  find_path(CL_BLAS_INCLUDE_DIR
            NAMES clBLAS.h
            HINTS ${CLBLAS_ROOT_DIR}
            PATH_SUFFIXES include
            DOC "clBLAS include directory")

  if(CL_BLAS_INCLUDE_DIR)
    set(HAVE_CL_BLAS 1)
    list(APPEND OPENCL_INCLUDE_DIRS "${CL_BLAS_INCLUDE_DIR}")
  endif()
endif()
