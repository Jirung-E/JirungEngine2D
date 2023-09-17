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
    ball->acceleration = { 0.0f, 3.0f };
    ball->velocity = { 0.0f, 0.0f };

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
        int x = (int)round(pos.x);
        int y = (int)round(pos.y);
        return 0 <= x && x < frame_width && 0 <= y && y < frame_height;
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
        float d = ball->radius * 2.0f / 100.0f;
        for(int i=0; i<d; i++) {
            for(int j=0; j<d; j++) {
                if(d*d/4.0f >(i+0.5f-d/2.0f)*(i+0.5f-d/2.0f) + (j+0.5f-d/2.0f)*(j+0.5f-d/2.0f)) {
                    Point p = { round((ball->position.x - ball->radius) / 100.0f + i + 0.5f), 
                        round((ball->position.y - ball->radius) / 100.0f + j + 0.5f) };
                    if(isInFrame(p)) {
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

        auto end_time = chrono::system_clock::now();
        auto duration = chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count();
        ball->update(duration/1000.0f);

        if(ball->position.y + ball->radius >= world_height) {
            ball->velocity.y *= -1;
        }
        if(ball->position.y - ball->radius < 0) {
            //// 충돌한 시점 t에서 속도, 위치를 구함
            //// t를 이용해서 update(t)
            //float dt = duration/1000.0f;
            //// 이전 속도
            //Vector pv = ball->velocity - ball->acceleration * dt;
            //// 이전 위치
            //Point pp = { ball->position.x - pv.x * dt, ball->position.y - pv.y * dt };

            //// 충돌한 위치
            //Point cp = { ball->position.x - (ball->position.y-ball->radius) * ball->velocity.x / ball->velocity.y, ball->radius };

            //// x는 안변했을수도 있지만 y는 반드시 변했을것이므로 실제 거리 대신에 y값만 비교해서 비율 계산
            //float ratio = (cp.y - pp.y) / (ball->position.y - pp.y);
            //// 충돌한 시점 t
            //float cdt = dt * ratio;
            //// 충돌한 시점 t에서의 속도
            //Vector cv = ball->velocity - ball->acceleration * cdt;
            // -> 이거 필요함..?

            ball->velocity.y *= -1;
            //ball->position.y = ball->radius - ball->position.y;
        }
        if(ball->position.x + ball->radius >= world_width || ball->position.x - ball->radius < 0) {
            ball->velocity.x *= -1;
        }

        if(duration >= 10) {
            printf("\x1b[0;0H");
            cout << "fps: " << fps << "                " << endl;
            cout << "x, y: " << ball->position.x << ", \t" << ball->position.y << "                " << endl;
            drawCircle();
            showFrame();
            fps = 1.0f / duration * 1000;
            start_time = end_time;

        }
    }

    delete ball;

    return 0;
}