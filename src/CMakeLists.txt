# Add the thread_pool library as a C++20 module
add_library(thread_pool STATIC)

# Add the module interface and implementation
# thread_pool.cxx is the module interface unit
# thread_pool_impl.cxx is a regular source file
target_sources(thread_pool
  PUBLIC
    FILE_SET cxx_modules TYPE CXX_MODULES FILES
      thread_pool.cxx
  PRIVATE
    thread_pool_impl.cxx
)

# Add the search_file executable
add_executable(search_file search_file.cxx)

target_link_libraries(search_file PRIVATE thread_pool)

install(TARGETS search_file
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
)
