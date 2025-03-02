# Cờ Caro Game

**Cờ Caro** là một trò chơi truyền thống, nơi hai người chơi thay phiên nhau đánh dấu X và O trên một bàn cờ, mục tiêu là tạo ra một chuỗi 5 ô liên tiếp theo hàng ngang, dọc hoặc đường chéo. Dự án này được xây dựng với ngôn ngữ **C++** và sử dụng thư viện **SFML** để vẽ đồ họa cho trò chơi.

## Phiên bản

- **Version 1.0**: Hiện tại, trò chơi đã hoàn thành với chế độ chơi hai người (2P). Người chơi có thể thay phiên nhau nhấn chuột vào các ô trên bàn cờ, người chơi đầu tiên sẽ điền O và người thứ hai sẽ điền X. Sau mỗi nước đi, trò chơi sẽ kiểm tra xem có ai chiến thắng chưa.
- **Version 2.0 (Sắp ra mắt)**: Trong bản cập nhật tiếp theo, trò chơi sẽ hỗ trợ chế độ chơi với máy tính (AI). Máy tính sẽ tự động tính toán nước đi tiếp theo dựa trên chiến lược AI và đối đầu với người chơi.

## Các tính năng hiện tại (Version 1.0)

- Hiển thị bàn cờ kích thước tùy chỉnh n x m.
- Người chơi có thể click chuột vào các ô để đánh dấu O và X.
- Kiểm tra chiến thắng khi có 5 ô liên tiếp (hàng ngang, hàng dọc hoặc đường chéo).
- Thông báo khi một người chiến thắng và kết thúc trò chơi.

## Công nghệ sử dụng

Dự án này sử dụng các công nghệ và thư viện sau:

- **C++**: Ngôn ngữ chính để phát triển trò chơi.
- **SFML**: Thư viện đồ họa 2D để vẽ bàn cờ và xử lý sự kiện chuột.
- **Git/GitHub**: Để quản lý mã nguồn và lưu trữ dự án.

## Cài đặt

### Yêu cầu

- Cài đặt **C++** compiler (g++, Clang, MSVC, v.v.).
- Cài đặt thư viện **SFML**. Bạn có thể làm theo hướng dẫn cài đặt của SFML tại [sfml-dev.org](https://www.sfml-dev.org/download.php).

### Cài đặt dự án

1. Clone repository về máy:
   ```bash
   git clone https://github.com/username/project-name.git
