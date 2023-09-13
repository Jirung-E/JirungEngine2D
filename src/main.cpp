#include <iostream>
#include <cmath>
#include <chrono>
#include <conio.h>

#include "Object/Circle.h"

using namespace std;
using namespace Math;
using namespace JirungEngine;


int main() {
    Circle* circle = new Circle { { 500, 500 }, 250.0f };
    circle->acceleration = { 0.0f, 0.000001f };
    circle->velocity = { 0.05f, 0.0f };

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
        for(int i=0; i<frame_height; i++) {
            string s = frame[i];
            s.resize(frame_width);
            cout << s << endl;
            //for(int j=0; j<frame_width; j++) {
            //    cout << frame[i][j];
            //}
            //cout << endl;
        }
    };

    auto drawCircle = [&]() {
        float d = circle->radius * 2;
        for(int i=0; i<d; i++) {
            for(int j=0; j<d; j++) {
                Point p = { (circle->position.x - circle->radius + i + 0.5f) / 100, (circle->position.y - circle->radius + j + 0.5f)/100 };
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

        circle->update();

        if(circle->position.y + circle->radius >= world_height || circle->position.y - circle->radius < 0) {
            circle->velocity.y *= -1;
        }
        if(circle->position.x + circle->radius >= world_width || circle->position.x - circle->radius < 0) {
            circle->velocity.x *= -1;
        }

        auto end_time = chrono::system_clock::now();
        if(chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() >= 10) {       // ????????
            printf("\x1b[0;0H");
            cout << "fps: " << fps << "                " << endl;
            drawCircle();
            showFrame();
            fps = 1.0f / chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() * 1000;
            start_time = end_time;

        }
    }

    delete circle;

    return 0;
}