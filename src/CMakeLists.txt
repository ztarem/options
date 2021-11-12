add_library(options optionsbase.cpp)
target_link_libraries(options CONAN_PKG::spdlog CONAN_PKG::cli11)
add_library(options::options ALIAS options)

target_include_directories(options
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(options PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

include(GNUInstallDirs)

install(TARGETS options
    EXPORT options-targets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    INCLUDES DESTINATION ${LIBLEGACY_INCLUDE_DIRS}
)
install(DIRECTORY ${CMAKE_SOURCE_DIR}/include/options
    DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)
install(EXPORT options-targets
    FILE options-targets.cmake
    NAMESPACE options::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/options
)
include(CMakePackageConfigHelpers)

configure_package_config_file(
    ${CMAKE_SOURCE_DIR}/cmake/options-config.cmake.in
    ${CMAKE_BINARY_DIR}/cmake/options-config.cmake
    INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/options
)

write_basic_package_version_file(
    ${CMAKE_BINARY_DIR}/cmake/options-config-version.cmake
    VERSION ${options_VERSION}
    COMPATIBILITY AnyNewerVersion
)

install(
    FILES
        ${CMAKE_BINARY_DIR}/cmake/options-config.cmake
        ${CMAKE_BINARY_DIR}/cmake/options-config-version.cmake
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/options
)

export(EXPORT options-targets
    FILE ${CMAKE_BINARY_DIR}/cmake/options-targets.cmake
    NAMESPACE options::
)
