#pragma once

// system includes
#include <array>
#include <cstdint>

// esp-idf includes
#include <esp32-hal-gpio.h>
#include <esp32-hal-misc.h>

// 3rdparty lib includes
#include <espchrono.h>
#include <screenmanager.h>

// local includes
#include "defines.h"

using namespace std::chrono_literals;

struct Button
{
    bool newState { false };
    bool lastState { false };
    espchrono::millis_clock::time_point debounce { espchrono::millis_clock::now() };
};

template <std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin>, std::array<pin_t, Nout>> class Dpad
{
public:
    Dpad() = default;

    void init();
    void update();

private:
    std::array<Button, Nin * Nout * 2> m_buttons;

    static void outPinModeAll(uint8_t mode);
};

template <std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::init()
{
    m_buttons.fill(Button {});
}

template <std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::update()
{
    constexpr std::size_t num_buttons = Nin * Nout * 2;

    for (std::size_t outI = 0; outI < pinsOut.size(); outI++)
    {
        const auto pinOut = pinsOut[outI];
        outPinModeAll(INPUT);
        pinMode(pinOut, OUTPUT);

        digitalWrite(pinOut, LOW);

        delayMicroseconds(40);

        for (std::size_t inI = 0; inI < pinsIn.size(); inI++)
        {
            const auto pinIn = pinsIn[inI];
            const auto i = (outI * pinsIn.size() + inI) * 2;
            pinMode(pinIn, INPUT_PULLUP);

            delayMicroseconds(40);

            m_buttons[i].newState = !digitalRead(pinIn);
        }

        digitalWrite(pinOut, HIGH);

        delayMicroseconds(40);

        for (std::size_t inI = 0; inI < pinsIn.size(); inI++)
        {
            const auto pinIn = pinsIn[inI];
            const auto i = (outI * pinsIn.size() + inI) * 2;
            pinMode(pinIn, INPUT_PULLDOWN);

            delayMicroseconds(40);

            m_buttons[i + 1].newState = digitalRead(pinIn);
        }
    }

    const auto now = espchrono::millis_clock::now();

    for (std::size_t i = 0; i < num_buttons; i++)
    {
        if (auto &button = m_buttons[i]; button.lastState != button.newState && espchrono::ago(button.debounce) > 30ms)
        {
            button.lastState = button.newState;
            if (espgui::currentDisplay)
            {
                if (button.newState)
                    espgui::currentDisplay->rawButtonPressed(i);
                else
                    espgui::currentDisplay->rawButtonReleased(i);
            }
            button.debounce = now;
        }
    }
}

template <std::size_t Nin, std::size_t Nout, std::array<pin_t, Nin> pinsIn, std::array<pin_t, Nout> pinsOut>
void Dpad<Nin, Nout, pinsIn, pinsOut>::outPinModeAll(const uint8_t mode)
{
    for (std::size_t pinOut = 0; pinOut < pinsOut.size(); pinOut++)
    {
        pinMode(pinsOut[pinOut], mode);
    }
}