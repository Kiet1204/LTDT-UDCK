#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
using namespace std;

const int MAX = 100;
struct GRAPH {
    int sodinh;
    int a[MAX][MAX];
    int visited[MAX];
    int luuvet[MAX];
    int mienlt;
};

void readGRAPH(const string& fn, GRAPH& g) {
    ifstream f(fn); // Mở file đầu vào để đọc dữ liệu đồ thị.
    if (f.is_open()) { // Kiểm tra xem file có mở thành công không.
        f >> g.sodinh; // Đọc số lượng đỉnh của đồ thị.
        for (int i = 0; i < g.sodinh; i++) {
            for (int j = 0; j < g.sodinh; j++) {
                f >> g.a[i][j]; // Đọc ma trận kề của đồ thị.
            }
        }
        f.close(); // Đóng file sau khi đọc.
    }
    else {
        cout << "Khong mo duoc file." << endl; // Thông báo lỗi nếu không mở được file.
    }
}

void visit(int s, GRAPH& g, int nlt) {
    g.visited[s] = nlt; // Đánh dấu đỉnh s thuộc miền liên thông nlt.
    for (int i = 0; i < g.sodinh; i++) {
        if (g.visited[i] == 0 && g.a[s][i] != 0) { // Nếu đỉnh i chưa được thăm và có cạnh từ s đến i.
            visit(i, g, nlt); // Gọi đệ quy thăm đỉnh i.
        }
    }
}

void xetlt(GRAPH& g) {
    for (int i = 0; i < g.sodinh; i++) {
        g.visited[i] = 0; // Đặt tất cả các đỉnh chưa được duyệt.
    }
    g.mienlt = 0; // Khởi tạo số miền liên thông.
    for (int i = 0; i < g.sodinh; i++) {
        if (g.visited[i] == 0) { // Nếu đỉnh i chưa được duyệt.
            g.mienlt++; // Tăng số miền liên thông.
            visit(i, g, g.mienlt); // Duyệt miền liên thông mới bắt đầu từ đỉnh i.
        }
    }
}

void inthanhphanlt(const GRAPH& g) {
    for (int i = 1; i <= g.mienlt; i++) { // Lặp qua từng miền liên thông.
        cout << "mien lien thong thu " << i << ": ";
        for (int j = 0; j < g.sodinh; j++) {
            if (g.visited[j] == i) // Nếu đỉnh j thuộc miền liên thông i.
                cout << j << " "; // In ra đỉnh đó.
        }
        cout << endl;
    }
}

void DFS(int s, GRAPH& g) {
    g.visited[s] = 1; // Đánh dấu đỉnh s đã được duyệt.
    for (int i = 0; i < g.sodinh; i++) {
        if (g.visited[i] == 0 && g.a[s][i] != 0) { // Nếu đỉnh i chưa được duyệt và có cạnh từ s đến i.
            g.luuvet[i] = s; // Lưu vết đường đi từ s đến i.
            DFS(i, g); // Gọi đệ quy để duyệt đỉnh i.
        }
    }
}

void duyetDFS(int s, int f, GRAPH& g) {
    for (int i = 0; i < g.sodinh; i++) {
        g.visited[i] = 0; // Đặt tất cả các đỉnh chưa được duyệt.
        g.luuvet[i] = -1; // Khởi tạo mảng lưu vết.
    }
    DFS(s, g); // Thực hiện DFS từ đỉnh s.

    if (g.visited[f] == 1) { // Nếu đỉnh f đã được duyệt.
        int j = f;
        while (j != s) { // Truy ngược đường đi từ f về s.
            cout << j << " <- ";
            j = g.luuvet[j];
        }
        cout << s << endl; // In đỉnh đầu tiên.
    }
    else {
        cout << "Khong co duong di." << endl; // Thông báo nếu không có đường đi từ s đến f.
    }
}

struct QUEUE {
    int size; // Kích thước hiện tại của hàng đợi.
    int a[MAX]; // Mảng chứa các phần tử trong hàng đợi.
};

void KhoiTao(QUEUE& q) { q.size = 0; } // Khởi tạo hàng đợi rỗng.

bool Them(int k, QUEUE& q) {
    if (q.size + 1 > MAX) return false; // Kiểm tra tràn hàng đợi.
    q.a[q.size] = k; // Thêm phần tử k vào cuối hàng đợi.
    q.size++; // Tăng kích thước hàng đợi.
    return true;
}

bool KiemTraRong(QUEUE q) {
    return (q.size == 0); // Kiểm tra hàng đợi có rỗng hay không.
}

bool Lay(int& v, QUEUE& q) {
    if (KiemTraRong(q)) return false; // Kiểm tra nếu hàng đợi rỗng.
    v = q.a[0]; // Lấy phần tử đầu tiên.
    for (int i = 0; i < q.size - 1; i++)
        q.a[i] = q.a[i + 1]; // Dịch các phần tử trong hàng đợi.
    q.size--; // Giảm kích thước hàng đợi.
    return true;
}

void BFS(int s, GRAPH& g) {
    QUEUE q;
    KhoiTao(q); // Khởi tạo hàng đợi.
    Them(s, q); // Thêm đỉnh bắt đầu s vào hàng đợi.
    while (!KiemTraRong(q)) { // Duyệt khi hàng đợi không rỗng.
        Lay(s, q); // Lấy đỉnh s từ hàng đợi.
        g.visited[s] = 1; // Đánh dấu đỉnh s đã được duyệt.
        for (int i = 0; i < g.sodinh; i++)
            if (g.visited[i] == 0 && g.a[s][i] != 0) { // Nếu đỉnh i chưa được duyệt và có cạnh từ s đến i.
                Them(i, q); // Thêm đỉnh i vào hàng đợi.
                g.luuvet[i] = s; // Lưu vết đường đi.
            }
    }
}

void duyetBFS(int s, int f, GRAPH& g) {
    for (int i = 0; i < g.sodinh; i++) {
        g.visited[i] = 0; // Đặt tất cả các đỉnh chưa được duyệt.
        g.luuvet[i] = -1; // Khởi tạo mảng lưu vết.
    }
    BFS(s, g); // Thực hiện BFS từ đỉnh s.
    if (g.visited[f] == 1) { // Nếu đỉnh f đã được duyệt.
        int j = f;
        while (j != s) { // Truy ngược đường đi từ f về s.
            cout << j << "<---";
            j = g.luuvet[j];
        }
        cout << s;
        cout << endl; // In đường đi từ s đến f.
    }
    else {
        cout << "Khong co duong di"; // Thông báo nếu không có đường đi.
        cout << endl;
    }
}

void displayResults(sf::Text& resultText) {
    std::ifstream inFile("ketqua.txt"); // Mở file kết quả để đọc.
    std::string line;
    std::string results;
    while (std::getline(inFile, line)) { // Đọc từng dòng trong file.
        results += line + "\n"; // Ghép các dòng vào một chuỗi kết quả.
    }
    resultText.setString(results); // Cập nhật nội dung vào đối tượng `sf::Text`.
}

int main() 
{
    // Tạo cửa sổ hiển thị có kích thước 1200x1000 pixel, tiêu đề "DFS - BFS - LIENTHONG".
    sf::RenderWindow window(sf::VideoMode(1200, 1000), "DFS - BFS - LIENTHONG");
    // Xóa cửa sổ với màu trắng.
    window.clear(sf::Color::White);
    // Tạo một khung hình chữ nhật ở góc trên bên trái, kích thước 400x700, màu nền trắng, viền đen dày 2 pixel.
    sf::RectangleShape topLeftFrame(sf::Vector2f(400, 700));
    topLeftFrame.setPosition(20, 20);
    topLeftFrame.setFillColor(sf::Color::White);
    topLeftFrame.setOutlineThickness(2);
    topLeftFrame.setOutlineColor(sf::Color::Black);
    // Thiết lập font chữ từ file "arial.ttf".
    sf::Font font;
    font.loadFromFile("arial.ttf");
    // Tạo văn bản hiển thị ở góc trên trái "Nhap dinh va ma tran cua do thi", font 20, màu đen.
    sf::Text topLeftText("Nhap dinh va ma tran cua do thi", font, 20);
    topLeftText.setPosition(65, 20);
    topLeftText.setFillColor(sf::Color::Black);
   
    std::string inputText; // Chuỗi nhập liệu và văn bản hiển thị đầu vào.
    sf::Text inputDisplay("", font, 20);
    inputDisplay.setPosition(65, 50);
    inputDisplay.setFillColor(sf::Color::Black);

    // Tạo khung hình chữ nhật nhỏ ở góc dưới bên phải, kích thước 200x100, màu nền trắng, viền đen dày 2 pixel.
    sf::RectangleShape bottomRightFrame(sf::Vector2f(200, 100));
    bottomRightFrame.setPosition(920, 890);
    bottomRightFrame.setFillColor(sf::Color::White);
    bottomRightFrame.setOutlineThickness(2);
    bottomRightFrame.setOutlineColor(sf::Color::Black);

    // Tạo văn bản nút "Start", đặt ở góc dưới bên phải.
    sf::Text bottomRightText("Start", font, 20);
    bottomRightText.setPosition(1040, 900);
    bottomRightText.setFillColor(sf::Color::Black);

    // Tạo một khung hình chữ nhật ở góc dưới bên trái, kích thước 400x700, màu nền trắng, viền đen dày 2 pixel.
    sf::RectangleShape bottomLeftFrame(sf::Vector2f(400, 700));
    bottomLeftFrame.setPosition(500, 20);
    bottomLeftFrame.setFillColor(sf::Color::White);
    bottomLeftFrame.setOutlineThickness(2);
    bottomLeftFrame.setOutlineColor(sf::Color::Black);

    // Tạo văn bản tiêu đề "Result" ở khung dưới bên trái.
    sf::Text bottomLeftText("Result", font, 20);
    bottomLeftText.setPosition(520, 20);
    bottomLeftText.setFillColor(sf::Color::Black);

    // Tạo văn bản kết quả trống ban đầu.
    sf::Text resultText("", font, 20);
    resultText.setPosition(540, 60);
    resultText.setFillColor(sf::Color::Black);

    // Vòng lặp chính để xử lý sự kiện và vẽ giao diện.
    while (window.isOpen()) {
        sf::Event event;
        // Lắng nghe sự kiện.
        while (window.pollEvent(event)) {
            // Nếu người dùng đóng cửa sổ, thoát chương trình.
            if (event.type == sf::Event::Closed)
                window.close();

            // Xử lý nhập liệu từ bàn phím.
            if (event.type == sf::Event::TextEntered) {
                if (event.text.unicode < 128) { // Chỉ xử lý ký tự ASCII.
                    if (event.text.unicode == 8) { // Xóa ký tự (phím Backspace).
                        if (!inputText.empty())
                            inputText.pop_back();
                    }
                    else if (event.text.unicode == 13) { // Thêm dòng mới (Enter).
                        inputText += "\n";
                    }
                    else { // Thêm ký tự mới.
                        inputText += static_cast<char>(event.text.unicode);
                    }
                }
            }

            // Xử lý nhấn chuột.
            if (event.type == sf::Event::MouseButtonPressed) {
                if (event.mouseButton.button == sf::Mouse::Left) { // Nhấn chuột trái.
                    sf::Vector2f mousePos(event.mouseButton.x, event.mouseButton.y);
                    // Kiểm tra nếu chuột nằm trong khung "Start".
                    if (bottomRightFrame.getGlobalBounds().contains(mousePos)) {
                        // Ghi dữ liệu nhập vào file "dothi.txt".
                        std::ofstream outFile("dothi.txt");
                        outFile << inputText;
                        outFile.close();

                        // Xử lý đồ thị.
                        GRAPH g;
                        ofstream out("ketqua.txt");
                        streambuf* coutbuf = cout.rdbuf(); // Lưu buffer hiện tại.
                        cout.rdbuf(out.rdbuf());

                        // Đọc đồ thị từ file và xử lý liên thông.
                        readGRAPH("dothi.txt", g);
                        xetlt(g);
                        inthanhphanlt(g);

                        // In kết quả kiểm tra liên thông vào file.
                        if (g.mienlt == 1) {
                            cout << "Do thi lien thong." << std::endl;
                        }
                        else {
                            cout << "Do thi khong lien thong." << std::endl;
                            cout << "So do thi khong lien thong: " << g.mienlt << std::endl;
                        }
                        cout << "duong di DFS:";
                        duyetDFS(0, g.sodinh - 1, g);
                        cout << "duong di BFS:";
                        duyetBFS(0, g.sodinh - 1, g);

                        cout.rdbuf(coutbuf); // Phục hồi buffer.
                        displayResults(resultText); // Hiển thị kết quả.
                    }
                }
            }
        }

        // Cập nhật chuỗi nhập liệu hiển thị trên giao diện.
        inputDisplay.setString(inputText);

        // Vẽ lại các thành phần giao diện.
        window.clear(sf::Color::White);
        window.draw(topLeftFrame);
        window.draw(topLeftText);
        window.draw(inputDisplay);
        window.draw(bottomRightFrame);
        window.draw(bottomRightText);
        window.draw(bottomLeftFrame);
        window.draw(bottomLeftText);
        window.draw(resultText);
        window.display();
    }
    return 0; // Kết thúc chương trình.
}
