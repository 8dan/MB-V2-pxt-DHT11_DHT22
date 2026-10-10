#include "pxt.h"

namespace dht22native {
    static int dataBytes[5] = { 0, 0, 0, 0, 0 };

    static int waitForLevel(MicroBitPin *pin, int level, int timeoutUs) {
        uint64_t started = system_timer_current_time_us();
        while (pin->getDigitalValue() != level) {
            if (system_timer_current_time_us() - started >= (uint64_t)timeoutUs)
                return 0;
        }
        return 1;
    }

    /**
     * Read one complete DHT22 frame.
     */
    //%
    int read(int pinId) {
        MicroBitPin *pin = pxt::getPin(pinId);
        if (pin == NULL)
            return -1;

        for (int i = 0; i < 5; ++i)
            dataBytes[i] = 0;

        pin->setDigitalValue(0);
        fiber_sleep(2);
        pin->setDigitalValue(1);
        wait_us(30);
        pin->getDigitalValue();

        if (!waitForLevel(pin, 0, 150)) return -2;
        if (!waitForLevel(pin, 1, 150)) return -3;
        if (!waitForLevel(pin, 0, 150)) return -4;

        for (int bit = 0; bit < 40; ++bit) {
            if (!waitForLevel(pin, 1, 100)) return -10 - bit;

            uint64_t highStarted = system_timer_current_time_us();
            if (!waitForLevel(pin, 0, 120)) return -60 - bit;
            int highUs = (int)(system_timer_current_time_us() - highStarted);

            int byteIndex = bit >> 3;
            dataBytes[byteIndex] = (dataBytes[byteIndex] << 1) & 255;
            if (highUs > 45)
                dataBytes[byteIndex] |= 1;
        }

        return 0;
    }

    /**
     * Return one byte from the last frame.
     */
    //%
    int byteAt(int index) {
        if (index < 0 || index >= 5)
            return 0;
        return dataBytes[index];
    }
}
