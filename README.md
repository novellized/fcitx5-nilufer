[English](README.md) | [Tiếng Việt](README_vi.md)

<a id="readme-top"></a>

<div align="center">
  <img src="data/fcitx-nilufer-README.svg" alt="Nilüfer Logo" width="80" height="80">

  <h2 align="center">Nilüfer (fcitx5-nilufer)</h2>

  <p align="center">
    <b>A fast, lightweight, and ergonomic Turkish Telex input method for Linux (Fcitx5)</b>
    <br />
    <a href="https://github.com/novellized/fcitx5-nilufer"><strong>GitHub Repository »</strong></a>
    ·
    <a href="https://github.com/novellized/fcitx5-nilufer/issues">Report Bug</a>
    ·
    <a href="https://github.com/novellized/fcitx5-nilufer/issues">Request Feature</a>
  </p>
</div>

---

## 🇹🇷 Overview

**Nilüfer** is a Turkish Telex input method engine for [Fcitx5](https://github.com/fcitx/fcitx5) on Linux. It allows touch-typists and developers using standard US/QWERTY keyboards to type Turkish-specific characters (`ç`, `ğ`, `ı`, `ö`, `ş`, `ü`, `Ç`, `Ğ`, `İ`, `Ö`, `Ş`, `Ü`) effortlessly without shifting hands to Turkish Q keyboard layouts or relying on AltGr combinations.

### ⌨️ Typing Rules (Telex Convention)

Nilüfer uses the letter `w` as the intuitive transformation key:

| Keystroke | Output | Uppercase Keystroke | Output | Description |
| :---: | :---: | :---: | :---: | :--- |
| `cw` | **ç** | `Cw` / `CW` | **Ç** | Latin C with cedilla |
| `sw` | **ş** | `Sw` / `SW` | **Ş** | Latin S with cedilla |
| `gw` | **ğ** | `Gw` / `GW` | **Ğ** | Latin G with breve (yumuşak g) |
| `uw` | **ü** | `Uw` / `UW` | **Ü** | Latin U with diaeresis |
| `ow` | **ö** | `Ow` / `OW` | **Ö** | Latin O with diaeresis |
| `iw` | **ı** | `Iw` / `IW` | **İ** | Dotless `ı` / Dotted `İ` |

#### Reversion / Undo
- Pressing `w` again on any transformed character immediately reverts it back to the base character + `w` (e.g. `ç` + `w` $\rightarrow$ `cw`).
- Standard Backspace deletes characters by Unicode code point accurately.
- Space, Enter, Tab, and punctuation marks commit the word cleanly.

---

## ✨ Features

- **Pure Unicode**: Built completely on standard UTF-8 Unicode.
- **Desktop Friendly**:
  - **GNOME Shell**: Displays native `tr` indicator in the top-bar status area.
  - **KDE Plasma, XFCE, Wayland (Sway, Hyprland)**: Fully supported with dark/light theme status icons.
- **Versatile Input Modes**:
  - **Preedit Mode**: Standard inline preedit composition supported by most GUI applications.
  - **Uinput (Smooth) Mode**: Direct replacement mode powered by virtual keyboard backend with zero preedit flicker.
  - **Select Mode**: Smooth replacement via selection where supported.
  - **Emoji Picker**: Built-in quick emoji selection.
  - **Custom Keymaps & Macros**: Expand customized abbreviation triggers seamlessly.

---

## 🛠️ Building & Installation

### Build Dependencies

#### Ubuntu / Debian / WSL2:
```bash
sudo apt update
sudo apt install -y \
    build-essential \
    cmake \
    extra-cmake-modules \
    pkg-config \
    gettext \
    libfcitx5core-dev \
    libfcitx5config-dev \
    libfcitx5utils-dev \
    fcitx5-modules-dev \
    libevdev-dev \
    libinput-dev \
    libnotify-dev \
    libudev-dev \
    python3
```

#### Arch Linux:
```bash
sudo pacman -S --needed base-devel cmake extra-cmake-modules fcitx5 libevdev libinput libnotify
```

### Compiling and Installing

```bash
git clone https://github.com/novellized/fcitx5-nilufer.git
cd fcitx5-nilufer

mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make -j$(nproc)
sudo make install
```

### Running Test Suite

Nilüfer includes an extensive automated test suite covering all Turkish Telex typing rules and integration lifecycles:

```bash
ctest --output-on-failure
```

---

## 🚀 Usage

1. **Start Fcitx5**:
   ```bash
   fcitx5 -d --replace
   ```
2. **Add Nilüfer to Fcitx5 Configuration**:
   - Open Fcitx5 configuration tool: `fcitx5-configtool`
   - In the input method list, search for **Nilüfer** (Language: Turkish / `tr`) and add it.
3. **Switch & Type**:
   - Press `Ctrl + Space` (or your configured trigger hotkey) to switch to Nilüfer.
   - Start typing using the Telex rules (e.g., type `teswekkuwr` $\rightarrow$ `teşekkür`, `Tuwrkcwe` $\rightarrow$ `Türkçe`).

---

## 🙏 Acknowledgements & Credits

Nilüfer is adapted from and proudly built upon the modern C++20 architecture of [**fcitx5-lotus**](https://github.com/LotusInputMethod/fcitx5-lotus). We express our deepest gratitude and full credit to the fcitx5-lotus development team and maintainers:

- **Nguyen Hoang Ky** ([@nhktmdzhg](https://github.com/nhktmdzhg))
- **Vo Ngo Hoang Thanh** ([@thanhpy2009](https://github.com/thanhpy2009))
- **Weng Xuetian (CSSlayer)** ([@csslayer](https://github.com/wengxt))
- All contributors to the [LotusInputMethod/fcitx5-lotus](https://github.com/LotusInputMethod/fcitx5-lotus) project.

Their outstanding work in creating a clean C++20 input method engine, smooth uinput daemon handling, and seamless Fcitx5 integration laid the foundation that made Nilüfer possible. For complete credits, see [`CREDITS`](CREDITS).

Also acknowledged:
- [bamboo-core](https://github.com/BambooEngine/bamboo-core) — Original Go engine (Luong Thanh Lam, MIT).
- [VMK](https://github.com/thanhpy2009/VMK) — Input method engine (Vo Ngo Hoang Thanh, GPL-3.0-or-later).
- [fcitx5-bamboo](https://github.com/fcitx/fcitx5-bamboo) — Fcitx5 integration glue (CSSlayer, LGPL-2.1).

---

## 📜 License

Nilüfer is licensed under the [GNU General Public License v3.0 (GPL-3.0)](LICENSE).

