namespace pxsim {
    export namespace dht22native {
        export function read(pin: number): number {
            // Fizični DHT22 v simulatorju ni na voljo.
            return -1000
        }

        export function byteAt(index: number): number {
            return 0
        }
    }
}