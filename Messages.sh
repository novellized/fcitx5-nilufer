#!/bin/bash

xgettext \
--language=C++ \
--from-code=UTF-8 \
--keyword=_ \
--keyword=N_ \
-o /tmp/nilufer-cpp.pot \
$(find . \( -name "*.cpp" -o -name "*.h" \))

xgettext \
--language=appdata \
--from-code=UTF-8 \
-o /tmp/nilufer-xml.pot \
org.fcitx.Fcitx5.Addon.Nilufer.metainfo.xml.in.in

xgettext \
--language=Python \
--from-code=UTF-8 \
--keyword=_ \
--keyword=N_ \
-o /tmp/nilufer-python.pot \
$(find . -name "*.py")

xgettext \
--language=Desktop \
--from-code=UTF-8 \
--keyword=Name \
--keyword=Comment \
-o /tmp/nilufer-desktop.pot \
settings-gui/org.fcitx.Fcitx5.Addon.Nilufer.Settings.desktop.in

{
    echo 'msgid ""'
    echo 'msgstr ""'
    echo '"Content-Type: text/plain; charset=UTF-8\n"'
    echo ""
    grep -hE "^Name=" \
    src/nilufer.conf.in \
    src/nilufer-addon.conf.in.in \
    | sed 's/^Name=\(.*\)/msgid "\1"\nmsgstr ""\n/'
} > /tmp/nilufer-conf.pot

msgcat \
--use-first \
--sort-output \
/tmp/nilufer-cpp.pot \
/tmp/nilufer-xml.pot \
/tmp/nilufer-conf.pot \
/tmp/nilufer-python.pot \
/tmp/nilufer-desktop.pot \
-o po/fcitx5-nilufer.pot

rm -f /tmp/nilufer-*.pot