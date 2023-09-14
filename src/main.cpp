#include <iostream>
#include <cmath>
#include <chrono>
#include <conio.h>

#include "Object/Ball.h"

using namespace std;
using namespace Math;
using namespace JirungEngine;


int main() {
    Ball* ball = new Ball { { 500, 500 }, 250.0f };
    ball->acceleration = { 0.0f, 0.000001f };
    ball->velocity = { 0.05f, 0.0f };

    int world_width = 12000;
    int world_height = 2700;
    int frame_width = 120;
    int frame_height = 27;

    char** frame = new char*[frame_height];
    for(int i=0; i<frame_height; i++) {
        frame[i] = new char[frame_width];
    }

    auto clearFrame = [&]() {
        for(int i=0; i<frame_height; i++) {
            for(int j=0; j<frame_width; j++) {
                frame[i][j] = ' ';
            }
        }
    };

    auto isInFrame = [&](const Point& pos) {
        return 0 <= pos.x && pos.x < frame_width && 0 <= pos.y && pos.y < frame_height;
    };

    auto showFrame = [&]() {
        string str = "";
        str.reserve(frame_height * (frame_width+1));
        for(int i=0; i<frame_height; i++) {
            string s = frame[i];
            s.resize(frame_width);
            str += s;
            str += "\n";
        }
        cout << str;
    };

    auto drawCircle = [&]() {
        float d = ball->radius * 2;
        for(int i=0; i<d; i++) {
            for(int j=0; j<d; j++) {
                Point p = { (ball->position.x - ball->radius + i + 0.5f) / 100, (ball->position.y - ball->radius + j + 0.5f)/100 };
                if(isInFrame(p)) {
                    if(d*d/4.0 >(i+0.5-d/2.0)*(i+0.5-d/2.0) + (j+0.5-d/2.0)*(j+0.5-d/2.0)) {
                        frame[(int)p.y][(int)p.x] = '@';
                    }
                }
            }
        }
    };

    auto start_time = chrono::system_clock::now();
    float fps = 0;
    bool repeat = true;

    while(true) {
        clearFrame();

        ball->update();

        if(ball->position.y + ball->radius >= world_height || ball->position.y - ball->radius < 0) {
            ball->velocity.y *= -1;
        }
        if(ball->position.x + ball->radius >= world_width || ball->position.x - ball->radius < 0) {
            ball->velocity.x *= -1;
        }

        auto end_time = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        if(duration >= 10) {
            printf("\x1b[0;0H");
            cout << "fps: " << fps << "                " << endl;
            drawCircle();
            showFrame();
            fps = 1.0f / duration * 1000;
            start_time = end_time;

        }
    }

    delete ball;

    return 0;
}