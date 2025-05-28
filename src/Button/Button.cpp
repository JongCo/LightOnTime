#include "Button.h"

/**
 * @brief Initialize Button
 * 
 * @param pins An array of up to 8 pin numbers representing buttons.  
 *             Each element should be a valid GPIO pin number or 255 to indicate an unused button slot.
 */
void Button::start(Array<uint8_t, 8> pins)
{
    pressed = 0;

    for(uint8_t i = 0; i < 8; i++) {
        pinArray[i] = pins[i];

        if (pins[i] == 255) {
            continue;
        }
        pinMode(pins[i], INPUT);
    }
}

void Button::update()
{
    uint8_t readPins = 0;
    for(uint8_t i = 0; i < 8; i++) {
        if (pinArray[i] == 255) {
            continue;
        }

        setBit(readPins, i, digitalRead(pinArray[i]));
    }
    pressed = ~prev & readPins;
    prev = readPins;
}

void Button::setBit(uint8_t &ref, uint8_t position, bool value)
{
    if (value) {
        ref |= (1 << position);
    } else {
        ref &= ~(1 << position);
    }
}

bool Button::getButtonDown(uint8_t pinIndex)
{
    return (pressed >> pinIndex) % 2;
}
