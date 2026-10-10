#include "pxt.h"

namespace dht22native {
    static int dataBytes[5] = { 0, 0, 0, 0, 0 };

    static int waitForLevel(MicroBitPin *pin, int level, int timeoutUs) {
        uint64_t started = system_timer_current_time_us();

        while (pin->getDigitalValue() != level) {
            if (system_timer_current_time_us() - started >= (uint64_t)timeoutUs) {
                return 0;
            }
        }

        return 1;
    }

    static int readFrame(MicroBitPin *pin) {
        for (int i = 0; i < 5; ++i) {
            dataBytes[i] = 0;
        }

        // Send start signal before entering the timing-critical section.
        pin->setDigitalValue(0);
        fiber_sleep(2);
        pin->setDigitalValue(1);

        uint64_t releaseStarted = system_timer_current_time_us();
        while (system_timer_current_time_us() - releaseStarted < 30) {
            // Wait 30 microseconds.
        }

        pin->getDigitalValue();

        // Prevent display and runtime interrupts from disturbing DHT22 timing.
        uint32_t previousInterruptState = __get_PRIMASK();
        __disable_irq();

        int status = 0;

        // Sensor response: LOW, HIGH, LOW.
        if (!waitForLevel(pin, 0, 150)) {
            status = -2;
        } else if (!waitForLevel(pin, 1, 150)) {
            status = -3;
        } else if (!waitForLevel(pin, 0, 150)) {
            status = -4;
        }

        // Read 40 data bits.
        if (status == 0) {
            for (int bit = 0; bit < 40; ++bit) {
                if (!waitForLevel(pin, 1, 150)) {
                    status = -10 - bit;
                    break;
                }

                uint64_t highStarted = system_timer_current_time_us();

                if (!waitForLevel(pin, 0, 150)) {
                    status = -60 - bit;
                    break;
                }

                int highUs = (int)(system_timer_current_time_us() - highStarted);
                int byteIndex = bit >> 3;

                dataBytes[byteIndex] = (dataBytes[byteIndex] << 1) & 255;

                if (highUs > 45) {
                    dataBytes[byteIndex] |= 1;
                }
            }
        }

        if (previousInterruptState == 0) {
            __enable_irq();
        }

        return status;
    }

    /**
     * Read one complete DHT22 frame.
     */
    //%
    int read(int pinId) {
        MicroBitPin *pin = pxt::getPin(pinId);

        if (pin == NULL) {
            return -1;
        }

        return readFrame(pin);
    }

    /**
     * Return one byte from the last frame.
     */
    //%
    int byteAt(int index) {
        if (index < 0 || index >= 5) {
            return 0;
        }

        return dataBytes[index];
    }
}
