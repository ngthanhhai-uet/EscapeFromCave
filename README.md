# **ESCAPE FROM CAVE - ngthanhhai**
## GIỚI THIỆU
**Họ và tên** : `Nguyễn Thanh Hải`

**Mã sinh viên** : `23020057` `K68CD` `Trường Đại học Công nghệ`  `Đại học Quốc gia Hà Nội`

**Ý tưởng** :  Đây là một chủ đề bài tập lớn của môn học `Lập Trình Nâng Cao`. Ý tưởng dựa trên tựa game `Tomb Of The Mask` viết bằng ngôn ngữ lập trình `C++` và sử dụng thư viện `SDL`
## CÀI ĐẶT
1. Sao chép repos này về máy tính của bạn
2. Cài đặt IDE `CodeBlock` và thư viện `SDL` `SDL_image` `SDL_ttf` `SDL_mixer`
3. Mở file `EscapeFromCave.cbp` trong thư mục repos vừa tải về
4. Ấn `F9` trên bàn phím hoặc click chuột vào `Build & Run` để chạy trò chơi
## MỘT SỐ HÌNH ẢNH TRONG GAME
![menu_en](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/c8ac3c09-352a-4534-afba-302fe0d6c847)
![setting_en](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/f14c7c6c-1153-4569-8894-fe31dc489c08)
![selectmap_en](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/d0853b2b-ddf0-42ba-8a6e-820e0d09fe59)
![ezgif-6-ccc2aeb765](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/093053c9-c151-4c30-bb1f-0778c0f85524)

## VẬT THỂ

![test](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/06c938c5-a067-48c2-87e7-9c92e11e371c) `Spike` : Bẫy gai tĩnh, khi người chơi chạm phải sẽ kết thúc màn chơi ngay lập tức

![peak](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/c1ace5d7-e1f0-4e9c-aa57-2321a63e8ef6)   `Peak` : Bẫy gai tự động, có hai trạng thái bật tắt tự động kích hoạt sau một khoảng thời gian, người chơi chạm phải khi ở trạng thái hoạt động sẽ kết thúc màn chơi ngay lập tức

![trap](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/5ef89510-487b-48ea-ae5a-cb078395c43a)   `Trap` : Bẫy gai cảm biến, tự động kích hoạt khi người chơi chạm phải sau khoảng thời gian ngắn, nếu người chơi chạm phải trong trạng thái kích hoạt sẽ kết thúc màn chơi ngay lập tức

![test](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/227c96b8-0e34-4d99-a95b-0a1ff1cf9f0a)  `Trampoline` : Đổi hướng di chuyển của người chơi khi chạm phải

![bat](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/9b36c86e-2797-41bd-ad75-db690b3d9f8c)   `Bat` : Di chuyển theo chiều ngang hoặc chiều dọc, tự động quay lại khi va chạm tường, người chơi va chạm vào dơi sẽ kết thúc màn chơi ngay lập tức

![tele](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/0a0cd478-2231-4f19-a4ee-0083b6f0f612)   `Teleporter` : Dịch chuyển đến một vị trí xác định trước

![coin](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/82a73dbb-ebce-4520-a7d6-4fafa6843455)   `Coin` : Đơn vị giao dịch của trò chơi, xuất hiện ngẫu nhiên trên bản đồ, với mỗi lần thu thập người chơi sẽ được tăng 1 đồng xu

![lava](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/ba9de982-3dbe-4a8a-9686-a1eeb5909cd8)   `Lava` : Trong bản đồ có dung nham, người chơi phải di chuyển liên tục để tránh dung nham thiêu cháy

![canon](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/f418ea31-b4f7-43e3-aa28-4fafbb7aae11)   `Blackgate` : Người chơi sẽ chiến thắng màn chơi khi chạm vào được chiếc cổng này

![canon](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/41501d66-b948-49e4-bceb-b49f763244e7)   `Canon` : Nguồn gốc tạo ra các quả bom xuất hiện trong các màn chơi

![bomb](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/7a2e776c-faf8-453f-82c4-32a5bc1496be)   `Bomb` : Bắn theo một hướng cho trước, khi chạm tường sẽ nghỉ một khoảng thời gian. Người chơi va chạm phải bom sẽ kết thúc màn chơi ngay lập tức

## NHỮNG KIẾN THỨC ĐÃ SỬ DỤNG
+ Sử dụng những kiến thức cơ bản của lập trình: vòng lặp, mảng tĩnh, xâu, mảng động, lớp, cấu trúc, con trỏ, nạp chồng toán tử,...
+ Kiến thức quản lí file: chia thư mục ra các Assest, src, manager, ... và sử dụng .hpp & .cpp để dễ dàng quản lí dự án
+ Sử dụng hoạt ảnh (Animation & Sprite)
+ Sử dụng kĩ thuật Tilemap tạo ra nhiều bản đồ khác nhau
+ Sử dụng kĩ thuật Scrolling View
+ Xuất/nhập file để đọc dữ liệu bản đồ, lưu tiến trình trò chơi
+ Xử lí va chạm giữa người chơi và vật thể, vật thể và vật thể khác

## REFERENCE
### *Hướng dẫn*
[`Lazyfoo`](https://lazyfoo.net/tutorials/SDL/index.php)

[`SDL2.0 Wiki`](https://www.libsdl.org)

[`ChatGPT4`](https://chat.openai.com)

[`Let's Make Game`](https://www.youtube.com/watch?v=44tO977slsU&list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx&index=3) (giúp mình tạo được vòng lặp của một trò chơi, mình drop từ phần Entity Component System do base lập trình kém)
### *Đồ hoạ*
Khoảng 40% đồ hoạ trong trò chơi này lấy từ  [`itch.io`](https://itch.io)

Thiết kế thêm hoặc bổ sung đồ hoạ bằng [`Aseprite`](https://www.aseprite.org/)

Toàn bộ giao diện sảnh tự thiết kế bằng  [`Canva`](https://www.canva.com)
### *Âm thanh*
Nguồn [`Youtube`](https://www.youtube.com)
## TỰ ĐÁNH GIÁ

![image](https://github.com/ngthanhhai-uet/EscapeFromCave/assets/148655084/f7c50dad-d3a3-4a33-a761-06f1de5cfb30)

Dựa trên barem điểm giảng viên đưa ra & một số luận điểm nâng cao band điểm
+ Đây là game làm lại trong quá trình làm bài tập lớn. Sau lần chấm demo của giảng viên, game trước không được đánh giá cao, vì vậy mình đã làm lại một game mới và game này mình hoàn thành trong gần 3 tuần.
+ Ý tưởng game mới so với mặt bằng chung, không tìm được nguồn tham khảo cho kiểu game này do đó 95% tự code, tuy nhiên do tự code và base lập trình không tốt nên khả năng quản lí project không quá hiệu quả.
+ Gameplay của trò chơi so với các game khác sẽ có sự khác nhau lớn ở điểm sau: Đa số game của các bạn sẽ không giới hạn điểm tối đa có thể có nghĩa là có thể chơi bao lâu cũng được, còn game của mình nếu bạn nào có khả năng chỉ cần 5-7 phút là đã hoàn thành tất cả các map hiện có, tuy nhiên về khía cạnh phát triển game thì game của mình có khả năng phát triển rất lớn khi có thể cập nhật thêm các bản đồ và vật thể mới không bị giới hạn.
+ Đồ hoạ game được chăm chút tỉ mỉ, cẩn thận. Mình nghĩ sẽ thuộc top lớp về mặt xử lí đồ hoạ trong trò chơi.
+ Điểm hạn chế lớn của bản thân là không áp dụng được Cấu trúc dữ liệu & Thuật toán nâng cao vào game do hạn chế về mặt thời gian và khả năng của chính mình.

Từ những luận điểm trên mình nghĩ sẽ nhỉnh hơn band điểm 7.5 - 8.5 thậm chí có thể vào band điểm 9 - 9.5 nếu thầy động viên nâng điểm & thuộc top cao của lớp.
## MỘT SỐ LỖI
Khi nhân vật trong trại thái di chuyển, các vật thể động như Bat hoặc Bomb đều sẽ bị delay kha khá nếu bạn để ý.
## CÁC TÍNH NĂNG TRONG TƯƠNG LAI
+ Bản đồ mới (Vd: bản đồ vô hạn)
+ Vật thể mới (Vd: bot tìm đường đi ngắn nhất đến người chơi)
+ Tính năng mới (Vd: cửa hàng vật phẩm, trang phục, nhập tên người chơi có thời gian hoàn thành nhanh nhất)
## LIÊN HỆ
[`Github`](https://github.com/ngthanhhai-uet)  [`Facebook`](https://www.facebook.com/ngthanhhai.official) [`Mail`](optimus1072005@gmail.com)
