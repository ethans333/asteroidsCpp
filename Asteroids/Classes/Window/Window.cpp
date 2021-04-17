#include <iostream>
#include "Window.h"
using namespace std;

Window::Window(int _width, int _height){
    width = _width;
    height = _height;
    centerX = width / 2;
    centerY = height / 2;
}

void Window::speak() {
    cout << "Hello, World.";
}