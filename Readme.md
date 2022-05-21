# 1.Hướng dẫn cài đặt:
## Dưới đây là cách cài đặt:
 Bước 1: fork repo này về github cá nhân 
 Bước 2:mở command port tại tệp muốn lưu code tải về
 Bước 3: clone code về máy bằng dòng lệnh: git clone https://github.com/[tên_github_cá_nhân]/Sliding_Puzzle
 Bước 4: mở folder code vừa được tải về bằng phần mềm
 Bước 5: New Terminal, nhập vào Terminal lệnh: make
 Bước 6: nhập tiếp lệnh: .\main.exe rồi Enter để chạy chương trình

# 2.Mô tả chung về trò chơi, các ý tưởng chính

## Về cách chơi:
    màn hình menu hiện ra, nhấn Enter để chuyển đến phần màn hình bảng chính để chơi
    Sau khi nhấn Enter để đến màn hình chính, nhạc nền sẽ được mở lên
    Trong lúc chơi nếu người chơi muốn mở lại nhạc từ đầu thì có thể nhấn phím Enter 
    để phát lại nhạc từ đầu.
    Game được chơi theo các bước nhấn phím, mỗi lần nhấn phím lên/xuống/trái/phải thì ảnh 
    ngẫu nhiên mới sẽ được sinh ra
    Game sẽ kết thúc khi người chơi không còn có thể di chuyển ảnh cộng vào nhau hoặc khi
    ảnh 2048 xuất hiện.
## Các ý tưởng chính:
    -Mở thiết lập cửa sổ, thiết lập các chức năng load ảnh và sử dụng nhạc( tham khảo tại https://lazyfoo.net/tutorials/SDL/index.php)

    -Đầu tiên sẽ load ảnh BackgroundMenu lên, thêm chức năng nhấn Enter để chuyển đến BackgroundMain là nền chính trò chơi và khởi động nhạc nền
    -Đi vào cơ chế game:
        + Đầu tiên:
            * Khai báo các hằng số const bao gồm StartWidth,StartHeight,WidthABox,HeightABox,Space
             Trong đó : StartWidth và StartHeight lần lượt là tọa độ xuất phát, có nghĩa là tọa độ của ô đầu tiên trong bảng 4x4
                         WidthABox và HeightABox lần lượt là chiều rộng và chiều cao của một ô 
                         Space là khoảng cách giữa tọa độ hai ô, ở đây khoảng cách giữa hai ô theo phương ngang và dọc bằng nhau và bằng 16
             * Khai báo mảng path chứa các địa chỉ ảnh 2,4,8... cần dùng trong bài
             * Sử dụng mảng hai chiều Box để lưu ảnh tại các ô trong bảng, đầu tiên gán cho tất cả ở giá trị NULL
             * Sử dụng mảng hai chiều Board để lưu lại tọa độ của các ô trong bảng và dùng hàm void SetBoard() để thiết lập các tọa độ đó
             * khai báo mảng vector arrboard kiểu SDL_Rect để lưu trữ tọa độ của các ảnh đã được sinh ra
             * dùng pair để tạo ra mảng ArrBoardMain với thành phần đầu tiên là tọa độ các ảnh ngẫu nhiên đã đc sinh ra và thành phần thứ hai là ảnh được sinh ra(arrboard)
             *tạo mảng hai chiều pair arr để lưu lại tọa độ đi kèm vs ảnh tại các ô, thành phần đầu tiên là Board (tọa độ của các ô trong bảng) và 
             thành phần thứ hai là Box(ảnh tại các ô trong bảng)

        +Tiếp theo:
            * về phần cơ chế chính của bài(thiết lập các hàm chính):
            ->hàm sinh số ngẫu nhiên void generateUnoccupiedPostion()
                (): tạo mảng vector pair ArraySaveRect dùng để lưu lại tọa độ của các ô còn trống để sinh ảnh ngẫu nhiên, với hai thành phần lần lượt là số dạng int 
                là hoành độ và tung độ của ô thỏa mãn chưa có ảnh 
                (): tại đây nếu như ArraySaveRect.size()==0 thì biến bool endgame=true(được khởi tạo làm biến toàn cục), biến này sẽ giúp cho máy nhận biết được là trên màn hình chính các ô đều đang có ảnh
                . Còn nếu ArraySaveRect.size() khác 0 thì ta sẽ random một số ngẫu nhiên phạm vi từ 0 đến ArraySaveRect.size(), rồi chuyển nó từ số được random
                về tọa độ bằng phép tính : đối với tung độ:StartHeight+line*HeightABox+line*Space
                                        đối với hoành độ:StartWidth+column*WidthABox+column*Space
                                        trong đó: column và line lần lượt là thứ tự hoành và tung độ của  ArraySaveRect của số mới được random trong khoảng 0 đến ArraySaveRect.size()
                Sau đó lưu tọa độ ảnh mới được sinh ra vào ArrBoardMain với thành phần đầu tiên là tọa độ còn thành phần thứ hai là imageX[0] tức là ảnh chứa hình số 2
            ->hàm kiểm tra xem có di chuyển được không và cho các ảnh di chuyển trong bảng mà không bị lọt ra ngoài :bool CanMove(int i,int j,int NextI, int NextJ)
                (). Khi nhấn phím để di chuyển, vị trí tiếp theo các ô cần tới mang tọa độ NextI NextJ. Kiểm tra xem NextI NextJ có phải tọa độ có trong bảng hay không,
                nếu ở ngoài bảng trả về giá trị false còn ngược lại thì trả về giá trị true.
            ->hàm void Endgame() dùng để soát điều kiện endgame, điều kiện end game ở đây là: khi có đủ ảnh cho 16 ô, các ô không có ô nào liền cạnh hay liền trên hoặc
            liền dưới giống với ảnh ô đó đang chứa, tức là không còn khả năng cộng, và thế là cũng không có khả năng di chuyển tiếp thì hiện màn hình end game, hoặc 
            người chơi thật sự thắng game, chỉ cần hiện ra ảnh 2048 thì sẽ thắng trò chơi.

        + Di chuyển trong game:
        ở đây có một khóa key, khóa key sẽ giúp cho sau khi nhấn enter vào màn hình chính thì sau khi nhấn enter lần nữa không bị lặp lại hành động đó.
            -> Di chuyển xuống:
                Khi nguời chơi ấn phím down trên bàn phím, soát tung độ từ lớn nhất về thấp nhất, hoành độ từ thấp nhất đến lớn nhất.
                Kiểm tra xem ô phía dưới có nằm trong tọa độ bảng hay không, nếu không thì không thực hiện tiếp của ô đó, nếu có thì kiểm tra xem ô phía dưới đó
                có ảnh hay không, nếu không thì di chuyển xuống, nếu có thì lại xem xem nó ảnh đó có giống với nó hay không( kiểm tra khả năng cộng), nếu có thì thực hiện
                kiểm tra xem hai ô đó đồng thời cùng mang ảnh là ảnh mang số gì(dựa vào địa chỉ được lưu trong danh sách path), gán cho cả hai ảnh đó về NULL,ảnh của
                ô mang vị trí lúc chưa di chuyển được tăng lên thêm một nấc( ví dụ, hai vị trí mang ảnh số 2 tức là tương ứng path[0], khi di chuyển được cộng lại, thì
                được xét trước sẽ mang ảnh path[0+1] tức là ảnh số 4)
                Sinh số ngẫu nhiên bằng hàm generateUnoccupiedPostion();
            -> Các di chuyển Up,Right, Left cũng có cơ chế khá tương tự với Down
        
# 3.Mô tả các chức năng đã cài đặt, kèm video minh họa (chèn link video youtube)

phím Enter có chức năng khởi động lại nhạc nền.
Di chuyển lên, xuống,sang trái,sang phải
## Link video: https://youtu.be/RzW8A736RGU
# 4.Các kỹ thuật lập trình được sử dụng trong chương trình (mảng, con trỏ, cấu trúc, lớp, đồ họa ...)

Kĩ thuật được dùng nhiều nhất trong bài là sử dụng mảng, bởi đa phần chỉ cần liên kết ảnh với tọa độ để kiểm tra và sử dụng các hàm.
Bài tập được sử dụng SDL2, sử dụng ảnh và âm thanh.
Trong bài có sử dụng khá nhiều pair để tạo dây xích kết nối giữa tọa độ và ảnh.
# 5.Kết luận, hướng phát triển và các điều tâm đắc rút ra được sau khi hoàn thiện chương trình
Tâm đắc:
+Tự mình code cơ chế
+Hiểu thêm một số cách hoạt động và bản chất của một số hàm SDL2
Hướng phát triển:
+Thêm một số tính năng mới cho game
+kéo thả kích thước cửa sổ

