#include <iostream>
#include <cmath>
#include <chrono>
#include <conio.h>

#include "Object/Circle.h"

using namespace std;
using namespace Math;
using namespace JirungEngine;


int main() {
    Object* circle = new Circle { { 5, 5 }, 1.0f };
    circle->acceleration = { 0.0f, 0.01f };
    circle->velocity = { 0.5f, 0.0f };

    int world_width = 120;
    int world_height = 28;

    char** frame = new char*[world_height];
    for(int i=0; i<world_height; i++) {
        frame[i] = new char[world_width];
    }

    auto clearFrame = [&]() {
        for(int i=0; i<world_height; i++) {
            for(int j=0; j<world_width; j++) {
                frame[i][j] = ' ';
            }
        }
    };

    auto isInFrame = [&](Point pos) {
        return 0 <= pos.x && pos.x < world_width && 0 <= pos.y && pos.y < world_height;
    };

    auto showFrame = [&]() {
        for(int i=0; i<world_height; i++) {
            for(int j=0; j<world_width; j++) {
                cout << frame[i][j];
            }
            cout << endl;
        }
    };

    auto start_time = chrono::system_clock::now();
    float fps = 0;
    bool repeat = true;

    while(true) {
        clearFrame();

        circle->update();

        if(isInFrame(circle->position)) {
            frame[(int)(circle->position.y)][(int)(circle->position.x)] = 'O';
        }
        else {
            if(circle->position.y >= world_height || circle->position.y < 0) {
                circle->velocity.y *= -1;
            }
            if(circle->position.x >= world_width || circle->position.x < 0) {
                circle->velocity.x *= -1;
            }
        }

        printf("\x1b[0;0H");
        cout << "fps: " << fps << endl;
        showFrame();
        auto end_time = chrono::system_clock::now();
        fps = 1.0f / chrono::duration_cast<chrono::milliseconds>(end_time - start_time).count() * 1000;
        start_time = end_time;
    }

    return 0;
}