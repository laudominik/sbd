add_executable(${PROJECT_NAME} ${SOURCE_DIR}/main.cpp)
target_include_directories(${PROJECT_NAME} PUBLIC ${SOURCE_DIR})

add_library(libsbd STATIC ${SOURCE_DIR}/main.cpp)
target_include_directories(libsbd PUBLIC ${SOURCE_DIR} ${SOURCE_DIR}/generic ${SOURCE_DIR}/impl ${SOURCE_DIR}/sorting)
add_subdirectory(${SOURCE_DIR}/impl)

target_link_libraries(${PROJECT_NAME} PRIVATE libsbd)
