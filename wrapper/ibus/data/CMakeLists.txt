configure_file(${CMAKE_CURRENT_SOURCE_DIR}/laipinyin.xml.in
               ${CMAKE_CURRENT_BINARY_DIR}/laipinyin.xml)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/laipinyin.xml
    DESTINATION "${CMAKE_INSTALL_PREFIX}/share/ibus/component")

# -*- indent-tabs-mode: nil -*- vim:et:ts=4
