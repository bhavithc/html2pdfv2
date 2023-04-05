cmake_minimum_required(VERSION 3.14)

project(html2pdfv2 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core WebEngineWidgets)

add_library(pdfconvertor
  pdfconvertor/include/HtmlToPdfConvertor.h
  pdfconvertor/src/HtmlToPdfConvertor.cpp
)

target_include_directories(pdfconvertor PUBLIC pdfconvertor/include)
target_link_libraries(pdfconvertor Qt${QT_VERSION_MAJOR}::WebEngineWidgets)

add_executable(html2pdfv2
  main.cpp
)

target_link_libraries(
    html2pdfv2

    Qt${QT_VERSION_MAJOR}::Core
    pdfconvertor
)

install(TARGETS html2pdfv2
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
