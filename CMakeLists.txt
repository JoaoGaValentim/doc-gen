cmake_minimum_required(VERSION 3.20)
project(docGen LANGUAGES CXX)

# ✅ Enable C++20 properly
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# ✅ Define source files
set(SOURCES
    src/main.cpp
    src/Document.cpp
)

# ✅ Add the executable target
add_executable(docGen ${SOURCES})

# ✅ Link C++20 features explicitly
target_compile_features(docGen PRIVATE cxx_std_20)

# ✅ Include header directory (assuming you have an 'include' folder)
target_include_directories(docGen PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ✅ Installation rules
install(TARGETS docGen
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)
