if(OpenCL_FOUND)
  if(OpenCL_LIBRARY)
    set(HAVE_OPENCL_STATIC ON)
    set(OpenCL_LIBRARY "${OpenCL_LIBRARY}")
  else()
    set(HAVE_OPENCL_STATIC OFF)
  endif()

  if(NOT HAVE_OPENCL_STATIC)
    try_compile(__VALID_OPENCL
      "${CMAKE_BINARY_DIR}"
      "${CMAKE_SOURCE_DIR}/checks/opencl.cpp"
      CMAKE_FLAGS "-DINCLUDE_DIRECTORIES:STRING=${OPENCL_INCLUDE_DIR}"
      OUTPUT_VARIABLE TRY_OUT
      )
    if(NOT TRY_OUT MATCHES "OpenCL is valid")
      message(WARNING "Can't use OpenCL")
      return()
    endif()
  endif()

  set(HAVE_OPENCL 1)

  set(OPENCL_INCLUDE_DIRS ${OPENCL_INCLUDE_DIR})

  find_path(CL_BLAS_INCLUDE_DIRS
            NAMES clBLAS.h
            HINTS ${CLBLAS_ROOT_DIR}
            PATH_SUFFIXES include
            DOC "clBLAS include directory")

  find_library(CL_BLAS_LIBRARYIES
            NAMES "clBLAS"
            PATH_SUFFIXES lib lib/import
            DOC "clBLAS library path")

  if(CL_BLAS_INCLUDE_DIR)
    set(HAVE_CL_BLAS 1)
    list(APPEND OPENCL_INCLUDE_DIRS "${CL_BLAS_INCLUDE_DIR}")
  endif()
endif()
