Name:           fcitx5-nilufer
Version:        1.6.0
Release:        1
Summary:        Turkish Telex input method for fcitx5 (Nilüfer)
License:        GPL-3.0-or-later
URL:            https://github.com/novellized/fcitx5-nilufer
Source0:        %{url}/archive/v%{version}/%{name}-%{version}.tar.gz

BuildRequires:  cmake
BuildRequires:  kf6-extra-cmake-modules
BuildRequires:  gcc-c++
BuildRequires:  glibc-devel
BuildRequires:  fcitx5-devel
BuildRequires:  libinput-devel
BuildRequires:  libevdev-devel
BuildRequires:  libnotify-devel
BuildRequires:  systemd-devel

BuildRequires:  sysuser-tools
BuildRequires:  python3
Requires(pre):  sysuser-shadow >= 3.1

%{?systemd_ordering}
Requires:       fcitx5
Requires:       python3-QtPy
Requires:       (python3-PyQt6 or python3-pyside6)
Requires:       python3-dbus-python
Requires:       acl

%description
Turkish Telex input method for fcitx5 (Nilüfer)

%prep
%setup -q
find . -type f -name '*.py' -exec sed -i '1s|^#!.*env python3|#!/usr/bin/python3|' {} +

%build
%cmake -DLOTUS_BYTECOMPILE_PYTHON:BOOL=OFF -DBUILD_TESTING:BOOL=ON
%cmake_build
cd %{_builddir}/%{name}-%{version}
%sysusers_generate_pre build/misc/user-nilufer.conf nilufer nilufer.conf

%install
%cmake_install
%find_lang %{name}
%py3_compile %{buildroot}%{_datadir}/fcitx5-nilufer

%check
%ctest

%files -f %{name}.lang
%{_datadir}/licenses/%{name}/LICENSE

%dir %{_datadir}/licenses/%{name}
%dir %{_modulesloaddir}
%{_bindir}/fcitx5-nilufer-server
%{_bindir}/fcitx5-nilufer-settings

%{_libdir}/fcitx5/libnilufer.so

%{_modulesloaddir}/fcitx5-nilufer.conf
%{_unitdir}/fcitx5-nilufer-server@.service
%{_sysusersdir}/nilufer.conf
%{_udevrulesdir}/99-nilufer.rules

%{_datadir}/fcitx5/addon/nilufer.conf
%{_datadir}/fcitx5/inputmethod/nilufer.conf

%{_datadir}/fcitx5/nilufer/

%{_datadir}/fcitx5-nilufer/
%{_datadir}/applications/org.fcitx.Fcitx5.Addon.Nilufer.Settings.desktop
%{_datadir}/metainfo/org.fcitx.Fcitx5.Addon.Nilufer.metainfo.xml

%{_datadir}/icons/hicolor/scalable/apps/*fcitx-nilufer*.svg
%{_datadir}/icons/hicolor/scalable/status/fcitx-nilufer*.svg

%dir %{_datadir}/icons/breeze
%dir %{_datadir}/icons/breeze/status
%dir %{_datadir}/icons/breeze/status/22
%dir %{_datadir}/icons/breeze/status/24
%{_datadir}/icons/breeze/status/*/fcitx-nilufer*.svg

%dir %{_datadir}/icons/breeze-dark
%dir %{_datadir}/icons/breeze-dark/status
%dir %{_datadir}/icons/breeze-dark/status/22
%dir %{_datadir}/icons/breeze-dark/status/24
%{_datadir}/icons/breeze-dark/status/*/fcitx-nilufer*.svg

%pre -f nilufer.pre

%post
%service_add_post fcitx5-nilufer-server@.service

if [ $1 -eq 1 ]; then
    echo "--- Cấu hình Nilüfer ---"
    echo "Hướng dẫn sau cài đặt:"
    echo "1. Kích hoạt Server cho user của bạn:"
    echo "   sudo systemctl enable --now fcitx5-nilufer-server@\$(whoami).service"
    echo ""
    echo "2. Cấu hình Fcitx5:"
    echo "   - Mở 'Fcitx5 Configuration', thêm bộ gõ Nilüfer"
    echo ""
    echo "3. Lưu ý cho Wayland (KDE):"
    echo "   - Hãy chọn 'Fcitx 5' trong phần Virtual Keyboard của hệ thống."
    echo "------------------------------------------------"
elif [ $1 -eq 2 ]; then
    echo "--- Cấu hình Nilüfer ---"
    echo "Hướng dẫn sau cập nhật:"
    echo "1. Khởi động lại Server cho user của bạn:"
    echo "   sudo systemctl restart fcitx5-nilufer-server@\$(whoami).service"
    echo ""
    echo "2. Cấu hình Fcitx5:"
    echo "   - Mở 'Fcitx5 Configuration', nhấn restart để khởi động lại."
fi

%preun
%service_del_preun fcitx5-nilufer-server@.service

%postun
%service_del_postun fcitx5-nilufer-server@.service

%changelog
* Wed Oct 21 2026 Nguyen Hoang Ky <nhktmdzhg@gmail.com> - 1.6.0-1
- Warn when a uinput mode is selected but the uinput server is down
- Fix bug backspace in preedit mode is commit the buffer
- Fix bug lost replacement backspace when client is focus out
- Fix bug focus bounce when deleting
- Remove Minecraft mode
