namespace dht22native {
    // Native reader. Returns 0 on success and a negative diagnostic code on timeout.
    //% shim=dht22native::read
    export function read(pin: DigitalPin): number {
        return -999
    }

    // Returns one byte from the most recent native reading.
    //% shim=dht22native::byteAt
    export function byteAt(index: number): number {
        return 0
    }
}
