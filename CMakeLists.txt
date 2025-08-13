cmake_minimum_required(VERSION 3.20)
project(docGen)

set(CMAKE_CXX_STANDARD_REQUIRED 23)

set(SOURCE
   src/main.cpp
   src/Document.cpp
)


add_executable(docGen ${SOURCE})
include_directories(vident PRIVATE ${SOURCE}/include)

# Diretiva de instalação do binário
install(TARGETS docGen
    RUNTIME DESTINATION bin
)
install(DIRECTORY include/ DESTINATION include)
