{
  lib,
  stdenv,
  acl,
  cmake,
  fcitx5,
  fetchFromGitHub,
  gettext,
  hicolor-icon-theme,
  kdePackages,
  libevdev,
  libinput,
  libnotify,
  nix-update-script,
  pkg-config,
  python3,
  qt6,
  udev,
}:

let
  pythonEnv = python3.withPackages (
    ps: with ps; [
      dbus-python
      pyqt6
      qtpy
    ]
  );
in
stdenv.mkDerivation (finalAttrs: {
  pname = "fcitx5-nilufer";
  version = "1.6.0";

  src = fetchFromGitHub {
    owner = "novellized";
    repo = "fcitx5-nilufer";
    tag = "v${finalAttrs.version}";
    hash = "sha256-zWOnjTaifwhzIk9QLksf/g3EF/SOg1vJmM4IQ5P1+H8=";
  };

  passthru = {
    updateScript = nix-update-script { };
  };

  nativeBuildInputs = [
    cmake
    gettext
    hicolor-icon-theme
    kdePackages.extra-cmake-modules
    pkg-config
    qt6.wrapQtAppsHook
  ];

  buildInputs = [
    acl
    fcitx5
    kdePackages.extra-cmake-modules
    libevdev
    libinput
    libnotify
    pythonEnv
    qt6.qtbase
    qt6.qtsvg
    udev
  ];

  strictDeps = true;

  __structuredAttrs = true;

  dontWrapQtApps = true;

  cmakeFlags = [
    "-DLOTUS_ALT_EXECUTABLE_PREFIX=/nix/store/"
    "-DLOTUS_SETFACL_EXECUTABLE=${acl}/bin/setfacl"
  ];

  postFixup = ''
    patchShebangs $out/share/fcitx5-nilufer/settings-gui
    wrapQtApp $out/bin/fcitx5-nilufer-settings \
      --prefix XDG_DATA_DIRS : "${hicolor-icon-theme}/share"
  '';

  meta = {
    description = "Turkish Telex input method engine for Fcitx5 (Nilüfer)";
    homepage = "https://github.com/novellized/fcitx5-nilufer";
    license = with lib.licenses; [
      gpl3Plus
    ];
    maintainers = with lib.maintainers; [
      justanoobcoder
    ];
    platforms = lib.platforms.linux;
  };
})
