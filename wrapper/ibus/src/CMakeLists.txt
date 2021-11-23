# CMakeLists.txt: cmake config file for ibus-laipinyin

find_package(GTK2 REQUIRED gtk)
find_package(iBus 1.2 REQUIRED)
find_package(laipinyin 2.0 REQUIRED)

include_directories(${GTK2_INCLUDE_DIRS} ${iBus_INCLUDE_DIRS} ${laipinyin_INCLUDE_DIRS})
set(LIBS ${LIBS} ${GTK2_LIBRARIES} ${iBus_LIBRARIES} ${laipinyin_LIBRARIES})
set(ENGINE_SRCS
    main.cpp
    engine.cpp 
    pointer.h ibus_common.h
    imi_ibus_win.cpp imi_ibus_win.h
    laipinyin_config_keys.h
    laipinyin_config.cpp laipinyin_config.h
    laipinyin_engine.cpp laipinyin_engine.h
    laipinyin_engine_proxy.cpp laipinyin_engine_proxy.h
    laipinyin_lookup_table.cpp laipinyin_lookup_table.h
    laipinyin_property.cpp laipinyin_property.h)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)
add_executable(ibus-engine-laipinyin ${ENGINE_SRCS})
target_link_libraries(ibus-engine-laipinyin ${LIBS})

install(TARGETS ibus-engine-laipinyin
    RUNTIME DESTINATION ${LIBEXEC_DIR})

# -*- indent-tabs-mode: nil -*- vim:et:ts=4
