cmake_minimum_required(VERSION 3.5)

project(projekt_pk4 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# QtCreator supports the following variables for Android, which are identical to qmake Android variables.
# Check https://doc.qt.io/qt/deployment-android.html for more information.
# They need to be set before the find_package( ...) calls below.

#if(ANDROID)
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
#    if (ANDROID_ABI STREQUAL "armeabi-v7a")
#        set(ANDROID_EXTRA_LIBS
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libcrypto.so
#            ${CMAKE_CURRENT_SOURCE_DIR}/path/to/libssl.so)
#    endif()
#endif()

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets LinguistTools REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets LinguistTools REQUIRED)


set(TS_FILES projekt_pk4_pl_PL.ts)


set(PROJECT_SOURCES
        main.cpp
        data_structs/headers/Dish.hpp
        data_structs/headers/Dishes.hpp
        data_structs/headers/Food.hpp
        data_structs/headers/Meal.hpp
        data_structs/headers/Meals.hpp
        data_structs/headers/Product.hpp
        data_structs/headers/Products.hpp
        data_structs/Dish.cpp
        data_structs/Dishes.cpp
        data_structs/Food.cpp
        data_structs/Meal.cpp
        data_structs/Meals.cpp
        data_structs/Product.cpp
        data_structs/Products.cpp
        networking/headers/Fetcher.hpp
        networking/headers/Poster.hpp
        networking/Fetcher.cpp
        networking/Poster.cpp
        header.h
        global_obj.cpp
        global_obj.hpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        Start.cpp
        Start.h
        tables/CustomTable.cpp
        tables/headers/CustomTable.h
        tables/ProductsTable.cpp
        tables/headers/ProductsTable.h
        tables/MealsTable.cpp
        tables/headers/MealsTable.h
        tables/DishesTable.cpp
        tables/headers/DishesTable.h
        tables/headers/SimpleTable.h
        tables/SimpleTable.cpp
        ${TS_FILES}
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(projekt_pk4
        ${PROJECT_SOURCES}
    )

    qt_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
else()
    if(ANDROID)
        add_library(projekt_pk4 SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(projekt_pk4
            ${PROJECT_SOURCES}
        )
    endif()

    qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
endif()

    set(CURL_LIBRARY "-lcurl")
    find_package(CURL REQUIRED)
    set(jsoncpp_LIBRARY)
    find_package(jsoncpp REQUIRED)

    if (CURL_FOUND)
        target_link_libraries(projekt_pk4 PRIVATE ${CURL_LIBRARIES})
        target_include_directories(projekt_pk4 PRIVATE ${CURL_INCLUDE_DIRS})
    endif()

    if (jsoncpp_FOUND)
        message("FOUND")
        include_directories(${jsoncpp_INCLUDE_DIR})
        target_link_libraries(projekt_pk4 PRIVATE ${jsoncpp_LIBRARY})
    endif()
    find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Core Quick QuickControls2 REQUIRED)
target_link_libraries(projekt_pk4 PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)
target_link_libraries(projekt_pk4 PRIVATE Qt${QT_VERSION_MAJOR}::Quick)
