#include "pxt.h"

namespace dht22native {
    static uint8_t bytes[5];

    static bool waitForValue(MicroBitPin *pin, int value, uint32_t timeoutUs) {
        uint32_t start = system_timer_current_time_us();
        while (pin->getDigitalValue() != value) {
            if (system_timer_current_time_us() - start > timeoutUs)
                return false;
        }
        return true;
    }

    //% shim=dht22native::read
    int read(int pinId) {
        MicroBitPin *pin = getPin(pinId);
        if (!pin)
            return -1;

        for (int i = 0; i < 5; i++)
            bytes[i] = 0;

        // Start signal: LOW for at least 1 ms; 18 ms also supports DHT11.
        pin->setDigitalValue(0);
        fiber_sleep(18);
        pin->setDigitalValue(1);
        wait_us(30);
        pin->getDigitalValue(); // switch pin to digital input

        // Sensor response: LOW, HIGH, then first data LOW.
        if (!waitForValue(pin, 0, 120)) return -2;
        if (!waitForValue(pin, 1, 120)) return -3;
        if (!waitForValue(pin, 0, 120)) return -4;

        for (int bit = 0; bit < 40; bit++) {
            // Each data bit starts LOW and then goes HIGH.
            if (!waitForValue(pin, 1, 100)) return -10 - bit;

            uint32_t highStart = system_timer_current_time_us();
            if (!waitForValue(pin, 0, 120)) return -60 - bit;
            uint32_t highLength = system_timer_current_time_us() - highStart;

            bytes[bit >> 3] <<= 1;
            if (highLength > 45)
                bytes[bit >> 3] |= 1;
        }

        return 0;
    }

    //% shim=dht22native::byteAt
    int byteAt(int index) {
        if (index < 0 || index > 4)
            return 0;
        return bytes[index];
    }
}
