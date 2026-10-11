# MB-V2-pxt-DHT11_DHT22

MakeCode extension for reading DHT11 and DHT22/AM2302 temperature and humidity sensors with BBC micro:bit.

This fork adds working DHT22/AM2302 support for **BBC micro:bit V2** by using the native `dht22native` reader for timing-sensitive communication.

## Tested configuration

The micro:bit V2 implementation was tested with a DHT22/AM2302 sensor. During testing, the sensor returned stable readings and correctly reacted to warm, humid exhaled air.

Example stable room readings:

```text
Temperature: 24.3 *C
Humidity: 54.6 %
```

Example response after warm, humid air reached the sensor:

```text
Temperature: 28.0 *C
Humidity: 97.3 %
```

## Import into MakeCode

1. Open [Microsoft MakeCode for micro:bit](https://makecode.microbit.org/).
2. Create or open a project.
3. Select **Extensions**.
4. Paste this repository URL into the search field:

```text
https://github.com/8dan/MB-V2-pxt-DHT11_DHT22
```

5. Select the extension.

## Basic use

Choose the correct sensor type in the query block:

- `DHT11` for a DHT11 sensor
- `DHT22` for a DHT22 or AM2302 sensor

For DHT22, wait at least two seconds between queries.

```typescript
basic.forever(function () {
    dht11_dht22.queryData(
        DHTtype.DHT22,
        DigitalPin.P0,
        true,
        true,
        true
    )

    serial.writeLine(
        "Temperature: "
        + dht11_dht22.readData(dataType.temperature)
        + " *C"
    )

    serial.writeLine(
        "Humidity: "
        + dht11_dht22.readData(dataType.humidity)
        + " %"
    )
})
```

The arguments of `queryData` are:

1. sensor type,
2. data pin,
3. internal pin pull-up,
4. serial output,
5. wait two seconds after the query.

## Wiring

For a three-pin DHT22/AM2302 module:

- `VCC` or `+` to micro:bit `3V`
- `GND` or `-` to micro:bit `GND`
- `DATA` or `OUT` to the selected digital pin, for example `P0`

Some modules use a different pin order. Check the labels printed on the module before connecting power.

For a bare four-pin sensor, use a pull-up resistor between `VCC` and `DATA`, or enable the internal pull-up option in the query block.

## Reading status

The extension verifies the sensor checksum. If a query fails, temperature and humidity are set to `-999`.

Use:

```typescript
dht11_dht22.readDataSuccessful()
```

to check whether the last checksum was valid.

Use:

```typescript
dht11_dht22.sensorrResponding()
```

to check whether the sensor responded.

## micro:bit V2 implementation

DHT communication requires precise pulse timing. This fork uses the native `dht22native` reader for DHT22 queries on micro:bit V2. The original TypeScript reader remains available for DHT11 operation.

## Notes

- Allow the sensor a short startup delay after power-on.
- Do not query a DHT22 more frequently than once every two seconds.
- Moist breath can temporarily raise the humidity reading close to 100%. The reading should gradually return toward room humidity afterward.
- Enable serial output while testing so checksum and measurement results can be inspected in the MakeCode device console.

## Credits

Original extension by Alan Wang (`alankrantas/pxt-DHT11_DHT22`).

This repository is a fork adapted and tested for BBC micro:bit V2.

## License

MIT

## Supported targets

- PXT/microbit
- BBC micro:bit V2
