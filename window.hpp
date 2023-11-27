/* @Author: Yue lin */

#include <ctime>
#include <iostream>

#include "ai.hpp"
#include "opencv2/opencv.hpp"

#define DEPTH 4

#define PAD 10
#define SIZE 100
#define SCALE 2.0
#define NAME "2048"
#define THICKNESS 3
#define RET think.join(); return;
#define FONT1 cv::FONT_HERSHEY_TRIPLEX
#define FONT2 cv::FONT_HERSHEY_SCRIPT_COMPLEX
#define ESC std::cout << "\rESC            " << std::endl; restart();
#define CHECK if(!running) {RET} if(key == 27) {mode = WAIT; ESC RET}

#define swap(a, b) a += b; b = a - b; a -= b;

class Window
{
    public:
        Window();
        ~Window();
        ull score();
        bool over();
        void show();
        void restart();
        void move(enum Action);
        enum Mode{WAIT, AUTO, KEYBOARD, OVER} mode;
    
    private:
        Game game;
        uint step;
        bool running;
        cv::Mat image;
        enum Action cache;
        AI ai = AI(DEPTH);
        cv::Scalar colors[S2 + 2] = {
            cv::Scalar::all(0),
            cv::Scalar(101, 110, 119),
            cv::Scalar(101, 110, 119),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249),
            cv::Scalar(101, 110, 119),
            cv::Scalar(242, 246, 249),
            cv::Scalar(101, 110, 119),
            cv::Scalar(101, 110, 119),
            cv::Scalar(242, 246, 249),
            cv::Scalar(242, 246, 249)
        };
        cv::Scalar backgrounds[S2 + 2] = {
            cv::Scalar(138, 148, 158),
            cv::Scalar(218, 228, 238),
            cv::Scalar(200, 224, 237),
            cv::Scalar(121, 177, 242),
            cv::Scalar( 99, 149, 245),
            cv::Scalar( 95, 124, 246),
            cv::Scalar( 59,  94, 246),
            cv::Scalar(114, 207, 237),
            cv::Scalar( 97, 204, 237),
            cv::Scalar( 80, 200, 237),
            cv::Scalar( 63, 197, 237),
            cv::Scalar( 46, 194, 237),
            cv::Scalar(218, 228, 238),
            cv::Scalar( 46, 194, 237),
            cv::Scalar(121, 177, 242),
            cv::Scalar( 99, 149, 245),
            cv::Scalar( 95, 124, 246),
            cv::Scalar( 59,  94, 246)
        };
        std::string actions[4] = {"left ", "up   ", "right", "down "};

        void clear();
        void update();
        void update(int, float);
        uint8 show(cv::Mat&, uint8);
};

void callback(int event, int x, int y, int _, void* data)
{
    Window* window = (Window*)data;
    if(event == 1 && window->mode == Window::WAIT)
    {
        if(y < (SIZE + PAD) * (S >> 1))
        {
            std::cout << "AI" << std::endl;
            window->mode = Window::AUTO;
        }
        else
        {
            std::cout << "Start by keyboard" << std::endl;
            window->mode = Window::KEYBOARD;
        }
        window->restart();
    }
    else if(event == 4 && window->mode == Window::OVER)
    {
        window->mode = Window::WAIT;
        window->restart();
    }
}

Window::Window()
{
    mode = WAIT;
    running = true;
    srand(time(0));
    int size = S * SIZE + (S + 1) * PAD;
    image = cv::Mat(size, size, CV_8UC3);
    std::cout << "Welcome to 2048 game!" << std::endl;
}

Window::~Window()
{
    running = false;
    cv::destroyAllWindows();
    std::cout << "\rQuit               " << std::endl;
}

ull Window::score()
{
    return game.score;
}

bool Window::over()
{
    return game.over();
}

void Window::show()
{
    update();
    uint8 key;
    cv::namedWindow(NAME);
    cv::setMouseCallback(NAME, callback, this);
    while(running)
    {
        key = show(image, 10);
        if(!running)
            break;
        if(key == 27)
        {
            if(mode != WAIT)
            {
                mode = WAIT;
                ESC continue;
            }
        }
        else if(mode == AUTO)
        {
            if(!step++)
                cache = ai.inference(game);
            move(cache);
        }
        else if(mode == KEYBOARD && 0x51 <= key && key <= 0x54)
            move((enum Action)(key - 0x51));
    }
}

void Window::clear()
{
    const uint d = PAD + SIZE;
    image.setTo(cv::Scalar(125, 135, 146));
    if(mode == AUTO || mode == KEYBOARD) FOR
        cv::rectangle(image, cv::Rect(
            PAD + i * d, PAD + j * d, SIZE, SIZE
        ), backgrounds[0], -1);
}

void Window::update()
{
    update(-1, 1);
}

void Window::restart()
{
    step = 0; game.restart(); update();
}

void Window::move(enum Action action)
{
    uint8 board[S][S];
    FOR board[i][j] = game.board[i][j];
    std::cout << "Action: " << actions[action];
    if(game.move(action))
    {
        uint8 key;
        float progress;
        std::thread think;
        Game copy = game.copy();
        bool end = (copy.fill(), copy.over());
        if(mode == AUTO && !end)
            think = std::thread([&]{cache = ai.inference(copy.copy());});
        else
            think = std::thread([]{;});
        FOR{swap(game.board[i][j], board[i][j])}
        for(progress = 0; progress <= 1; progress += 0.01)
        {
            update(action, progress);
            key = show(image, 1); CHECK
        }
        key = show(image, 5); CHECK
        FOR game.board[i][j] = board[i][j];
        cv::Mat img = image.clone(); update();
        for(progress = 0; progress <= 1; progress += 0.1)
        {
            cv::Mat p = progress * image + (1 - progress) * img;
            key = show(p, 10); CHECK
        }
        img = image.clone(); FOR game.board[i][j] = copy.board[i][j];
        for(update(), progress = 0; progress <= 1; progress += 0.1)
        {
            cv::Mat p = progress * image + (1 - progress) * img;
            key = show(p, 10); CHECK
        }
        std::cout << "\tScore: " << score() << std::endl;
        if(end)
        {
            mode = OVER;
            std::cout << "Game over. Score: " << score() << std::endl;
        }
        think.join();
    }
    else
        std::cout << "\tcannot move" << std::endl;
}

uint8 Window::show(cv::Mat& img, uint8 t)
{
    cv::imshow(NAME, img);
    uint8 key = cv::waitKey(t) & 0xFF;
    running = cv::getWindowProperty(NAME, cv::WND_PROP_AUTOSIZE) == 1;
    return key;
}

void Window::update(int action, float progress)
{
    clear();
    int down;
    cv::Size size;
    std::string text;
    switch(mode)
    {
        case WAIT:
            text = "AI";
            size = cv::getTextSize(text, FONT1, SCALE, THICKNESS, &down);
            cv::putText(image, text, cv::Point(
                (image.cols - size.width) >> 1,
                (((image.rows >> 1) - size.height) >> 1) + down
            ), FONT1, SCALE, colors[0], THICKNESS);
            text = "Keyboard";
            size = cv::getTextSize(text, FONT1, SCALE, THICKNESS, &down);
            cv::putText(image, text, cv::Point(
                (image.cols - size.width) >> 1,
                ((image.rows + (image.rows >> 1) - size.height) >> 1) + down
            ), FONT1, SCALE, colors[0], THICKNESS); break;
        case AUTO:
        case KEYBOARD:
            uint y = PAD;
            const int dxy = PAD + SIZE;
            for(uint8 r = 0; r < S; y += (r++, dxy))
            {
                uint x = PAD;
                uint8* line = game.board[r];
                for(uint8 c = 0; c < S; x += (c++, dxy))
                    if(uint8 num = line[c])
                    {
                        int dx = 0, dy = 0;
                        if(action >= 0 && game.moved[r][c])
                            if(action % 2)
                            {
                                dy = (action == UP? -1: 1)
                                *dxy *progress *(game.moved[r][c] - 1);
                            }
                            else
                            {
                                dx = (action == LEFT? -1: 1)
                                *dxy *progress *(game.moved[r][c] - 1);
                            }
                        cv::rectangle(image, cv::Rect(
                            x + dx, y + dy, SIZE, SIZE
                        ), backgrounds[num], -1);
                        text = std::to_string(POW[num]);
                        float scale = SCALE - (text.length() - 1) / 3.0;
                        size = cv::getTextSize(text, FONT2, scale, THICKNESS, &down);
                        cv::putText(image, text, cv::Point(
                            x + dx + (SIZE - size.width >> 1),
                            y + dy + down + (SIZE - size.height) / 2 + size.height / 2
                        ), FONT2, scale, colors[num], THICKNESS);
                    }
            }
    }
}
