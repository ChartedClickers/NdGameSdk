#pragma once

#include <array>
#include <cstdint>
#include <cstdlib>  // atoi
#include <cstring>  // strchr, strncmp

// ANSI Color Codes
// https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
#define ANSI_BLK   "\x1b[0;30m"
#define ANSI_RED   "\x1b[0;31m"
#define ANSI_GRN   "\x1b[0;32m"
#define ANSI_YEL   "\x1b[0;33m"
#define ANSI_BLU   "\x1b[0;34m"
#define ANSI_MAG   "\x1b[0;35m"
#define ANSI_CYN   "\x1b[0;36m"
#define ANSI_WHT   "\x1b[0;37m"
#define ANSI_RESET "\x1b[0m"

enum class BasicColors {
    Red, Green, Blue, Yellow,
    Black, White, Pink, Cyan,
    Magenta, Orange, Purple, Brown,
    Gray, LightGray, DarkGray,
    LightBlue, LightGreen, LightYellow,
    LightPink, DarkBlue, DarkGreen, DarkRed
};

class Color {
public:
    Color()
        : a(255), r(0), g(0), b(0) {
    }

    Color(BasicColors color)
        : a(255)
    {
        switch (color) {
        case BasicColors::Black:        r = 0; g = 0; b = 0; break;
        case BasicColors::Red:          r = 255; g = 0; b = 0; break;
        case BasicColors::Green:        r = 0; g = 255; b = 0; break;
        case BasicColors::Yellow:       r = 0; g = 255; b = 255; break;
        case BasicColors::Blue:         r = 0; g = 0; b = 255; break;
        case BasicColors::Magenta:      r = 255; g = 0; b = 255; break;
        case BasicColors::Cyan:         r = 255; g = 255; b = 0; break;
        case BasicColors::White:        r = 255; g = 255; b = 255; break;
        case BasicColors::DarkGray:     r = 85; g = 85; b = 85; break;
        case BasicColors::LightBlue:    r = 85; g = 85; b = 255; break; 
        case BasicColors::LightGreen:   r = 85; g = 255; b = 85; break; 
        case BasicColors::LightYellow:  r = 255; g = 255; b = 85; break;
        case BasicColors::Pink:         r = 255; g = 192; b = 203; break;
        case BasicColors::Orange:       r = 255; g = 165; b = 0; break;
        case BasicColors::Purple:       r = 128; g = 0; b = 128; break;
        case BasicColors::Brown:        r = 165; g = 42; b = 42; break;
        case BasicColors::Gray:         r = 128; g = 128; b = 128; break;
        case BasicColors::LightGray:    r = 211; g = 211; b = 211; break;
        case BasicColors::LightPink:    r = 255; g = 182; b = 193; break;
        case BasicColors::DarkBlue:     r = 0; g = 0; b = 139; break;
        case BasicColors::DarkGreen:    r = 0; g = 100; b = 0; break;
        case BasicColors::DarkRed:      r = 139; g = 0; b = 0; break;
        default:                        r = 0; g = 0; b = 0; break;
        }
    }

    Color(uint64_t color) {
        a = static_cast<uint8_t>(color >> 24);
        r = static_cast<uint8_t>(color >> 16);
        g = static_cast<uint8_t>(color >> 8);
        b = static_cast<uint8_t>(color);
    }

    Color(uint32_t color) {
        a = 255;
        r = static_cast<uint8_t>(color >> 16);
        g = static_cast<uint8_t>(color >> 8);
        b = static_cast<uint8_t>(color);
    }

    explicit Color(uint8_t ansiIndex)
        : Color(ANSI_TABLE[ansiIndex < 16 ? ansiIndex : 0]) {
    }

    uint64_t toUint64() const {
        return (static_cast<uint64_t>(a) << 24)
            | (static_cast<uint64_t>(r) << 16)
            | (static_cast<uint64_t>(g) << 8)
            | static_cast<uint64_t>(b);
    }

    uint32_t toUint32() const {
        return (static_cast<uint32_t>(r) << 16)
            | (static_cast<uint32_t>(g) << 8)
            | static_cast<uint32_t>(b);
    }

    uint8_t alpha() const { return a; }
    uint8_t red()   const { return r; }
    uint8_t green() const { return g; }
    uint8_t blue()  const { return b; }

    static Color ansiColor(BasicColors c) {
        return Color(c);
    }

    static uint32_t ansiUint32(BasicColors c) {
        return Color(c).toUint32();
    }

private:
    uint8_t a, r, g, b;

    static constexpr std::array<BasicColors, 16> ANSI_TABLE{ {
        BasicColors::Black,     BasicColors::Red,
        BasicColors::Green,     BasicColors::Yellow,
        BasicColors::Blue,      BasicColors::Magenta,
        BasicColors::Cyan,      BasicColors::White,
        BasicColors::DarkGray,  BasicColors::DarkRed,
        BasicColors::DarkGreen, BasicColors::LightYellow,
        BasicColors::LightBlue, BasicColors::Magenta,
        BasicColors::Cyan,      BasicColors::White
    } };
};
