// Native declarations for the DHT22 reader.
declare namespace dht22native {
    //% shim=dht22native::read
    function read(pin: number): number;

    //% shim=dht22native::byteAt
    function byteAt(index: number): number;
}
