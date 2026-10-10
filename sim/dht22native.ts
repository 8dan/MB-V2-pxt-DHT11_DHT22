namespace pxsim {
    export namespace dht22native {
        export function read(pin: number): number {
            return -1000
        }

        export function byteAt(index: number): number {
            return 0
        }
    }

    // Prepreči odstranitev funkcij med optimizacijo simulatorja.
    dht22native.read(0)
    dht22native.byteAt(0)
}