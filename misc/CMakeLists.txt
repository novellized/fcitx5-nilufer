set(LOTUS_UINPUT_PROXY_USER "uinput_proxy" CACHE STRING
    "System user granted rw ACL on /dev/uinput (udev rules, sysusers.d, service scripts)")

option(INSTALL_OPENRC "Install OpenRC script" OFF)
option(INSTALL_RUNIT "Install Runit script" OFF)

configure_file(99-nilufer.rules.in ${CMAKE_CURRENT_BINARY_DIR}/99-nilufer.rules @ONLY)
configure_file(fcitx5-nilufer-server@.service.in ${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer-server@.service @ONLY)
configure_file(user-nilufer.conf.in ${CMAKE_CURRENT_BINARY_DIR}/user-nilufer.conf @ONLY)

if(INSTALL_OPENRC)
    configure_file(fcitx5-nilufer.openrc.in ${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer.openrc @ONLY)
endif(INSTALL_OPENRC)

if(INSTALL_RUNIT)
    configure_file(fcitx5-nilufer.runit.in ${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer.runit @ONLY)
endif(INSTALL_RUNIT)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer-server@.service"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/systemd/system)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/99-nilufer.rules"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/udev/rules.d)

install(FILES module-fcitx5-nilufer.conf
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/modules-load.d
    RENAME fcitx5-nilufer.conf)

install(FILES "${CMAKE_CURRENT_BINARY_DIR}/user-nilufer.conf"
    DESTINATION ${CMAKE_INSTALL_PREFIX}/lib/sysusers.d
    RENAME nilufer.conf)

if(INSTALL_OPENRC)
    install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer.openrc"
        DESTINATION /etc/init.d
        RENAME fcitx5-nilufer)
endif(INSTALL_OPENRC)

if(INSTALL_RUNIT)
    set(RUNIT_SV_DIR "/etc/sv" CACHE PATH
        "Path to runit service definitions directory (e.g. /etc/sv on Void, /etc/runit/sv on Artix)")
    install(PROGRAMS "${CMAKE_CURRENT_BINARY_DIR}/fcitx5-nilufer.runit"
        DESTINATION "${RUNIT_SV_DIR}/fcitx5-nilufer"
        RENAME run)
endif(INSTALL_RUNIT)
