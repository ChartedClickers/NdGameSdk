#pragma once

#include <string>
#include <sstream>
#include <iomanip>

enum class BasicColors {
    Red,
    Green,
    Blue,
    Yellow,
    Black,
    White,
    Pink,
    Cyan,
    Magenta,
    Orange,
    Purple,
    Brown,
    Gray,
    LightGray,
    DarkGray,
    LightBlue,
    LightGreen,
    LightYellow,
    LightPink,
    DarkBlue,
    DarkGreen,
    DarkRed
};

class Color {
public:
    // Default constructor: black with full opacity
    Color() : a(255), r(0), g(0), b(0) {}

    // Constructor from uint64_t (ARGB format)
    Color(uint64_t color) {
        r = (color >> 16) & 0xFF;
        g = (color >> 8) & 0xFF;
        b = color & 0xFF;
        a = (color >> 24) & 0xFF;
    }

    Color(BasicColors color) {
        switch (color) {
        case BasicColors::Red:
            a = 255; r = 255; g = 0; b = 0;
            break;
        case BasicColors::Green:
            a = 255; r = 0; g = 255; b = 0;
            break;
        case BasicColors::Blue:
            a = 255; r = 0; g = 0; b = 255;
            break;
        case BasicColors::Yellow:
            a = 255; r = 255; g = 255; b = 0;
            break;
        case BasicColors::Black:
            a = 255; r = 0; g = 0; b = 0;
            break;
        case BasicColors::White:
            a = 255; r = 255; g = 255; b = 255;
            break;
        case BasicColors::Pink:
            a = 255; r = 255; g = 192; b = 203;
            break;
        case BasicColors::Cyan:
            a = 255; r = 0; g = 255; b = 255;
            break;
        case BasicColors::Magenta:
            a = 255; r = 255; g = 0; b = 255;
            break;
        case BasicColors::Orange:
            a = 255; r = 255; g = 165; b = 0;
            break;
        case BasicColors::Purple:
            a = 255; r = 128; g = 0; b = 128;
            break;
        case BasicColors::Brown:
            a = 255; r = 165; g = 42; b = 42;
            break;
        case BasicColors::Gray:
            a = 255; r = 128; g = 128; b = 128;
            break;
        case BasicColors::LightGray:
            a = 255; r = 211; g = 211; b = 211;
            break;
        case BasicColors::DarkGray:
            a = 255; r = 169; g = 169; b = 169;
            break;
        case BasicColors::LightBlue:
            a = 255; r = 173; g = 216; b = 230;
            break;
        case BasicColors::LightGreen:
            a = 255; r = 144; g = 238; b = 144;
            break;
        case BasicColors::LightYellow:
            a = 255; r = 255; g = 255; b = 224;
            break;
        case BasicColors::LightPink:
            a = 255; r = 255; g = 182; b = 193;
            break;
        case BasicColors::DarkBlue:
            a = 255; r = 0; g = 0; b = 139;
            break;
        case BasicColors::DarkGreen:
            a = 255; r = 0; g = 100; b = 0;
            break;
        case BasicColors::DarkRed:
            a = 255; r = 139; g = 0; b = 0;
            break;
        default:
            a = 255; r = 0; g = 0; b = 0;
            break;
        }
    }

    Color(uint8_t alpha, uint8_t red, uint8_t green, uint8_t blue)
        : a(alpha), r(red), g(green), b(blue) {}

    uint64_t toUint64() const {
        return (static_cast<uint64_t>(a) << 24) |
            (static_cast<uint64_t>(r) << 16) |
            (static_cast<uint64_t>(g) << 8) |
            static_cast<uint64_t>(b);
    }

    uint32_t toUint32() const {
        return (static_cast<uint32_t>(r) << 16) |
            (static_cast<uint32_t>(g) << 8) |
            static_cast<uint32_t>(b);
    }

    // Getters for color components
    uint8_t alpha() const { return a; }
    uint8_t red() const { return r; }
    uint8_t green() const { return g; }
    uint8_t blue() const { return b; }

private:
    uint8_t a;
    uint8_t r;
    uint8_t g;
    uint8_t b;
};