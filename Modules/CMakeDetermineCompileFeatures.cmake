# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file Copyright.txt or https://cmake.org/licensing for details.


function(cmake_determine_compile_features lang)

  if(lang STREQUAL C AND COMMAND cmake_record_c_compile_features)
    message(STATUS "Detecting ${lang} compile features")

    set(CMAKE_C90_COMPILE_FEATURES c_std_90)
    set(CMAKE_C99_COMPILE_FEATURES c_std_99)
    set(CMAKE_C11_COMPILE_FEATURES c_std_11)

    include("${CMAKE_ROOT}/Modules/Internal/FeatureTesting.cmake")

    cmake_record_c_compile_features()

    if(NOT _result EQUAL 0)
      message(STATUS "Detecting ${lang} compile features - failed")
      return()
    endif()

    if (CMAKE_C99_COMPILE_FEATURES AND CMAKE_C11_COMPILE_FEATURES)
      list(REMOVE_ITEM CMAKE_C11_COMPILE_FEATURES ${CMAKE_C99_COMPILE_FEATURES})
    endif()
    if (CMAKE_C90_COMPILE_FEATURES AND CMAKE_C99_COMPILE_FEATURES)
      list(REMOVE_ITEM CMAKE_C99_COMPILE_FEATURES ${CMAKE_C90_COMPILE_FEATURES})
    endif()

    if(CMAKE_C_COMPILE_FEATURES)
      list(INSERT CMAKE_C_COMPILE_FEATURES 0
        c_std_90
        c_std_99
        c_std_11
        )
    else()
      set(CMAKE_C_COMPILE_FEATURES
        ${CMAKE_C90_COMPILE_FEATURES}
        ${CMAKE_C99_COMPILE_FEATURES}
        ${CMAKE_C11_COMPILE_FEATURES}
      )
    endif()

    set(CMAKE_C_COMPILE_FEATURES ${CMAKE_C_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_C90_COMPILE_FEATURES ${CMAKE_C90_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_C99_COMPILE_FEATURES ${CMAKE_C99_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_C11_COMPILE_FEATURES ${CMAKE_C11_COMPILE_FEATURES} PARENT_SCOPE)

    message(STATUS "Detecting ${lang} compile features - done")

  elseif(lang STREQUAL CXX AND COMMAND cmake_record_cxx_compile_features)
    message(STATUS "Detecting ${lang} compile features")

    set(CMAKE_CXX98_COMPILE_FEATURES cxx_std_98)
    set(CMAKE_CXX11_COMPILE_FEATURES cxx_std_11)
    set(CMAKE_CXX14_COMPILE_FEATURES cxx_std_14)

    include("${CMAKE_ROOT}/Modules/Internal/FeatureTesting.cmake")

    cmake_record_cxx_compile_features()

    if(NOT _result EQUAL 0)
      message(STATUS "Detecting ${lang} compile features - failed")
      return()
    endif()

    if (CMAKE_CXX11_COMPILE_FEATURES AND CMAKE_CXX14_COMPILE_FEATURES)
      list(REMOVE_ITEM CMAKE_CXX14_COMPILE_FEATURES ${CMAKE_CXX11_COMPILE_FEATURES})
    endif()
    if (CMAKE_CXX98_COMPILE_FEATURES AND CMAKE_CXX11_COMPILE_FEATURES)
      list(REMOVE_ITEM CMAKE_CXX11_COMPILE_FEATURES ${CMAKE_CXX98_COMPILE_FEATURES})
    endif()

    if(CMAKE_CXX_COMPILE_FEATURES)
      list(INSERT CMAKE_CXX_COMPILE_FEATURES 0
        cxx_std_98
        cxx_std_11
        cxx_std_14
        )
    else()
      set(CMAKE_CXX_COMPILE_FEATURES
        ${CMAKE_CXX98_COMPILE_FEATURES}
        ${CMAKE_CXX11_COMPILE_FEATURES}
        ${CMAKE_CXX14_COMPILE_FEATURES}
      )
    endif()

    set(CMAKE_CXX_COMPILE_FEATURES ${CMAKE_CXX_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_CXX98_COMPILE_FEATURES ${CMAKE_CXX98_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_CXX11_COMPILE_FEATURES ${CMAKE_CXX11_COMPILE_FEATURES} PARENT_SCOPE)
    set(CMAKE_CXX14_COMPILE_FEATURES ${CMAKE_CXX14_COMPILE_FEATURES} PARENT_SCOPE)

    message(STATUS "Detecting ${lang} compile features - done")
  endif()

endfunction()
