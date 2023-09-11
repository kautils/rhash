if(NOT DEFINED KAUTIL_THIRD_PARTY_DIR)
    set(KAUTIL_THIRD_PARTY_DIR ${CMAKE_BINARY_DIR})
    file(MAKE_DIRECTORY "${KAUTIL_THIRD_PARTY_DIR}")
endif()

macro(git_clone url)
    get_filename_component(file_name ${url} NAME)
    if(NOT EXISTS ${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name})
        file(DOWNLOAD ${url} "${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name}")
    endif()
    include("${KAUTIL_THIRD_PARTY_DIR}/kautil_cmake/${file_name}")
    unset(file_name)
endmacro()

git_clone(https://raw.githubusercontent.com/kautils/CMakeLibrarytemplate/v0.0.1/CMakeLibrarytemplate.cmake)

set(__rhash_dir ${CMAKE_CURRENT_LIST_DIR}/third_party/mingw-w64-x86_64-rhash_1.4.3-1)
set(module_name rhash)
get_filename_component(__include_dir "${CMAKE_CURRENT_LIST_DIR}" DIRECTORY)
unset(srcs)
file(GLOB srcs ${CMAKE_CURRENT_LIST_DIR}/*.cc)
set(${module_name}_common_pref
    #DEBUG_VERBOSE
    MODULE_PREFIX kautil hash
    MODULE_NAME ${module_name}
    INCLUDES $<BUILD_INTERFACE:${CMAKE_CURRENT_LIST_DIR}> $<INSTALL_INTERFACE:include> 
    SOURCES ${srcs}
    LINK_LIBS rhash
    EXPORT_NAME_PREFIX ${PROJECT_NAME}
    EXPORT_VERSION ${PROJECT_VERSION}
    EXPORT_VERSION_COMPATIBILITY AnyNewerVersion
        
    DESTINATION_INCLUDE_DIR include/kautil/hash
    DESTINATION_CMAKE_DIR cmake
    DESTINATION_LIB_DIR lib
)


foreach(__libtype shared static)
    CMakeLibraryTemplate(${module_name} EXPORT_LIB_TYPE ${__libtype} ${${module_name}_common_pref} )
    target_link_directories(${${module_name}_${__libtype}} PRIVATE ${__rhash_dir}/lib)
    target_include_directories(${${module_name}_${__libtype}} PRIVATE $<BUILD_INTERFACE:${__rhash_dir}/include>)
endforeach()


set(__t ${${module_name}_static_tmain})
add_executable(${__t})
target_sources(${__t} PRIVATE ${CMAKE_CURRENT_LIST_DIR}/unit_test.cc)
target_link_libraries(${__t} PRIVATE ${${module_name}_static})
target_compile_definitions(${__t} PRIVATE ${${module_name}_static_tmain_ppcs})
