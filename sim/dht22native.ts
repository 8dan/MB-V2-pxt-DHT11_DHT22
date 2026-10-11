// Simulator implementation for the native DHT22 reader.
//
// On the physical micro:bit V2, MakeCode uses the native C++
// implementation from dht22native.cpp.
//
// In the browser simulator, this file returns fixed test values:
// temperature 24.0 C and humidity 55.0 %.

namespace pxsim.dht22native {

    // DHT22 data format:
    // byte 0: humidity high byte
    // byte 1: humidity low byte
    // byte 2: temperature high byte
    // byte 3: temperature low byte
    // byte 4: checksum
    //
    // Humidity:
    // 55.0 % = 550 = 0x0226
    //
    // Temperature:
    // 24.0 C = 240 = 0x00F0
    //
    // Checksum:
    // (2 + 38 + 0 + 240) & 0xFF = 24

    const simulatedData: number[] = [
        2,
        38,
        0,
        240,
        24
    ]

    export function read(dataPin: number): number {
        // Status 0 means that the simulated read succeeded.
        return