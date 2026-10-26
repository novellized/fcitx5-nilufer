[English](README.md) | [Tiếng Việt](README_vi.md)

<a id="readme-top"></a>

<div align="center">
  <img src="data/fcitx-nilufer-README.svg" alt="Nilüfer Logo" width="80" height="80">

  <h2 align="center">Nilüfer (fcitx5-nilufer)</h2>

  <p align="center">
    <b>Bộ gõ tiếng Thổ Nhĩ Kỳ kiểu Telex nhanh, nhẹ và tiện dụng cho Linux (Fcitx5)</b>
    <br />
    <a href="https://github.com/novellized/fcitx5-nilufer"><strong>Kho lưu trữ GitHub »</strong></a>
    ·
    <a href="https://github.com/novellized/fcitx5-nilufer/issues">Báo lỗi</a>
    ·
    <a href="https://github.com/novellized/fcitx5-nilufer/issues">Yêu cầu tính năng</a>
  </p>
</div>

---

## 🇹🇷 Tổng quan

**Nilüfer** là bộ gõ tiếng Thổ Nhĩ Kỳ theo kiểu gõ Telex dành cho [Fcitx5](https://github.com/fcitx/fcitx5) trên Linux. Bộ gõ cho phép người gõ 10 ngón và lập trình viên sử dụng bàn phím tiêu chuẩn US/QWERTY gõ các ký tự đặc thù của tiếng Thổ Nhĩ Kỳ (`ç`, `ğ`, `ı`, `ö`, `ş`, `ü`, `Ç`, `Ğ`, `İ`, `Ö`, `Ş`, `Ü`) một cách dễ dàng mà không cần phải chuyển đổi sang bố cục bàn phím Turkish Q hay bấm các tổ hợp phím AltGr phức tạp.

### ⌨️ Quy tắc gõ (Quy ước Telex)

Nilüfer sử dụng phím `w` làm phím biến đổi trực quan:

| Phím gõ | Kết quả | Phím gõ in hoa | Kết quả | Mô tả |
| :---: | :---: | :---: | :---: | :--- |
| `cw` | **ç** | `Cw` / `CW` | **Ç** | Chữ C có dấu móc dưới (cedilla) |
| `sw` | **ş** | `Sw` / `SW` | **Ş** | Chữ S có dấu móc dưới (cedilla) |
| `gw` | **ğ** | `Gw` / `GW` | **Ğ** | Chữ G có dấu trăng (yumuşak g) |
| `uw` | **ü** | `Uw` / `UW` | **Ü** | Chữ U có dấu hai chấm trên (diaeresis) |
| `ow` | **ö** | `Ow` / `OW` | **Ö** | Chữ O có dấu hai chấm trên (diaeresis) |
| `iw` | **ı** | `Iw` / `IW` | **İ** | Chữ `ı` không chấm / `İ` có chấm |

#### Khôi phục / Hoàn tác (Undo)
- Bấm phím `w` thêm một lần nữa sau khi biến đổi ký tự sẽ ngay lập tức khôi phục về ký tự gốc + `w` (ví dụ: `ç` + `w` $\rightarrow$ `cw`).
- Phím Backspace xoá ký tự theo chuẩn Unicode code point chính xác.
- Phím Space, Enter, Tab và các dấu câu sẽ commit từ đang gõ một cách gọn gàng.

---

## ✨ Tính năng nổi bật

- **Thuần Unicode**: Xây dựng hoàn toàn trên nền tảng chuẩn UTF-8 Unicode.
- **Tương thích hoàn hảo với môi trường Desktop**:
  - **GNOME Shell**: Hiển thị chỉ báo `tr` trực tiếp trên thanh trạng thái top-bar.
  - **KDE Plasma, XFCE, Wayland (Sway, Hyprland)**: Hỗ trợ đầy đủ biểu tượng khay hệ thống cho cả giao diện sáng/tối.
- **Nhiều chế độ gõ linh hoạt**:
  - **Preedit Mode**: Chế độ gõ gạch chân (preedit) tiêu chuẩn tương thích tốt với hầu hết ứng dụng GUI.
  - **Uinput (Smooth) Mode**: Chế độ thay thế trực tiếp mượt mà thông qua backend bàn phím ảo uinput, hoàn toàn không bị chớp giật preedit.
  - **Select Mode**: Thay thế trực tiếp qua vùng chọn (selection) trên các ứng dụng hỗ trợ.
  - **Emoji Picker**: Tích hợp sẵn bảng chọn emoji nhanh.
  - **Tuỳ biến phím tắt & Gõ tắt (Macro)**: Dễ dàng mở rộng và định nghĩa các cụm từ viết tắt.

---

## 🛠️ Biên dịch & Cài đặt

### Các gói phụ thuộc (Dependencies)

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

### Biên dịch và cài đặt

```bash
git clone https://github.com/novellized/fcitx5-nilufer.git
cd fcitx5-nilufer

mkdir build && cd build
cmake -DCMAKE_INSTALL_PREFIX=/usr ..
make -j$(nproc)
sudo make install
```

### Chạy bộ kiểm thử (Test Suite)

Nilüfer đi kèm bộ kiểm thử tự động toàn diện kiểm tra tất cả các quy tắc gõ Turkish Telex và vòng đời tích hợp:

```bash
ctest --output-on-failure
```

---

## 🚀 Hướng dẫn sử dụng

1. **Khởi động Fcitx5**:
   ```bash
   fcitx5 -d --replace
   ```
2. **Thêm Nilüfer vào cấu hình Fcitx5**:
   - Mở công cụ cấu hình Fcitx5: `fcitx5-configtool`
   - Trong danh sách bộ gõ, tìm kiếm **Nilüfer** (Ngôn ngữ: Turkish / `tr`) và thêm vào.
3. **Chuyển đổi & Gõ phím**:
   - Nhấn phím tắt chuyển bộ gõ (mặc định: `Ctrl + Space`) để chọn Nilüfer.
   - Bắt đầu gõ theo quy tắc Telex (ví dụ: gõ `teswekkuwr` $\rightarrow$ `teşekkür`, `Tuwrkcwe` $\rightarrow$ `Türkçe`).

---

## 🙏 Ghi công & Cảm ơn

Nilüfer được phát triển và kế thừa trực tiếp từ nền tảng kiến trúc C++20 hiện đại của [**fcitx5-lotus**](https://github.com/LotusInputMethod/fcitx5-lotus). Chúng tôi xin gửi lời tri ân sâu sắc và ghi nhận toàn bộ công lao tới nhóm phát triển và duy trì fcitx5-lotus:

- **Nguyễn Hoàng Kỳ** ([@nhktmdzhg](https://github.com/nhktmdzhg))
- **Võ Ngô Hoàng Thành** ([@thanhpy2009](https://github.com/thanhpy2009))
- **Huỳnh Thiện Lộc** ([@hthienloc](https://github.com/hthienloc)) (cho phần logo gốc)
- **Weng Xuetian (CSSlayer)** ([@csslayer](https://github.com/wengxt))
- Toàn thể các lập trình viên và thành viên đã đóng góp cho dự án [LotusInputMethod/fcitx5-lotus](https://github.com/LotusInputMethod/fcitx5-lotus).

Công sức xuất sắc của các tác giả trong việc thiết kế engine C++20 gọn gàng, cơ chế uinput daemon mượt mà và khả năng tích hợp sâu với Fcitx5 đã đặt nền móng vững chắc giúp Nilüfer ra đời. Xem chi tiết ghi công đầy đủ tại [`CREDITS`](CREDITS).

Đồng thời trân trọng ghi công các dự án tiền thân:
- [bamboo-core](https://github.com/BambooEngine/bamboo-core) — Engine gõ gốc bằng Go (Lương Thanh Lam, MIT).
- [VMK](https://github.com/thanhpy2009/VMK) — Engine bộ gõ (Võ Ngô Hoàng Thành, GPL-3.0-or-later).
- [fcitx5-bamboo](https://github.com/fcitx/fcitx5-bamboo) — Phần tích hợp Fcitx5 (CSSlayer, LGPL-2.1).

---

## 📜 Giấy phép

Nilüfer được phát hành dưới giấy phép [GNU General Public License v3.0 (GPL-3.0)](LICENSE).
