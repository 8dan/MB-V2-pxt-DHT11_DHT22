namespace dht22native {
    //% shim=dht22native::read
    export function read(pin: DigitalPin): number {
        return -1000
    }

    //% shim=dht22native::byteAt
    export function byteAt(index: number): number {
        return 0
    }
}
