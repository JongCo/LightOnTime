#include "Arduino.h"
#include "Array.h"

class Button {
    private:
        uint8_t prev;
        uint8_t pressed;
        Array<uint8_t, 8> pinArray;
    public:
        void start(Array<uint8_t, 8> pins);
        void update();
        void setBit(uint8_t& ref, uint8_t position, bool value);
        bool getButtonDown(uint8_t pinIndex);
};