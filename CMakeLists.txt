cmake_minimum_required(VERSION 4.0.1)

# Set C++ standard
set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Enable C++ modules support
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

# Enable standard library modules (C++23/26 std module)
set(CMAKE_EXPERIMENTAL_CXX_STANDARD_MODULES ON)
set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

# Enable C++20 modules support (if needed)
set(CMAKE_CXX_MODULES 1)

# Project name and version
project(search_file_project VERSION 1.0 LANGUAGES CXX)

# Add the src directory
add_subdirectory(src)

# Install target for the binary
install(TARGETS search_file DESTINATION bin)

set(CPACK_PACKAGE_NAME "search_file")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_CONTACT "debashish47@gmail.com")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A fast file search tool")
set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_SOURCE_DIR}/LICENSE")
set(CPACK_RESOURCE_FILE_README "${CMAKE_SOURCE_DIR}/README.md")
set(CPACK_GENERATOR "TGZ;ZIP;DEB;RPM")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Debashish Ghosh")
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libc6 (>= 2.27)")
set(CPACK_PACKAGE_VENDOR "Debashish Ghosh")
set(CPACK_PACKAGING_INSTALL_PREFIX "/usr/local")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")

set(CPACK_COMPONENTS_ALL Runtime Documentation)
set(CPACK_COMPONENT_RUNTIME_DESCRIPTION "The main executable")
set(CPACK_COMPONENT_DOCUMENTATION_DESCRIPTION "Documentation files")
set(CPACK_COMPONENT_RUNTIME_GROUP "Applications")
set(CPACK_COMPONENT_DOCUMENTATION_GROUP "Documentation")

set(CPACK_STRIP_FILES ON)
include(CPack)
