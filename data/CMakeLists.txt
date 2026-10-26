install(DIRECTORY icons/ DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/"
    PATTERN .* EXCLUDE
    PATTERN *~ EXCLUDE)

# ── Status/tray icon coverage: hicolor status/ ────────────────────────────
# The engine returns plain icon names (see lotus-engine.cpp subModeIconImpl);
# the SNI host resolves them through standard XDG icon theme lookup. Install
# copies of every variant into hicolor status dirs in addition to the
# breeze/breeze-dark theme dirs installed above.
set(LOTUS_STATUS_ICONS
    fcitx-nilufer fcitx-nilufer-off fcitx-nilufer-emoji
    fcitx-nilufer-default fcitx-nilufer-default-black
    fcitx-nilufer-off-default fcitx-nilufer-off-default-black
    fcitx-nilufer-emoji-default fcitx-nilufer-emoji-default-black
    fcitx-nilufer-default-symbolic
    fcitx-nilufer-off-default-symbolic
    fcitx-nilufer-emoji-default-symbolic)

foreach(ICON ${LOTUS_STATUS_ICONS})
    # status/ — system tray (SVG, renderable by most compositors and SNI hosts)
    install(FILES icons/hicolor/scalable/apps/${ICON}.svg
        DESTINATION "${CMAKE_INSTALL_DATADIR}/icons/hicolor/scalable/status"
        RENAME "${ICON}.svg")
endforeach()

install(FILES dictionaries/turkish.dict DESTINATION "${FCITX_INSTALL_PKGDATADIR}/nilufer")
