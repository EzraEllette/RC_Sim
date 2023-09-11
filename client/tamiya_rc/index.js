import G29 from 'logitech-g29'
import { SerialPort } from 'serialport'

const ST_CENTER = 140;
const ST_MAX = 255;
const ST_MIN = 0;
const TH_CENTER = 140;
const TH_MAX = 255;
const TH_MIN = 0;

const state = {
    wheel: 50,
    throttle: 0,
    brake: 0,
}

async function main() {
    G29.connect({
        range: 270,
    }, function (err) {
        G29.forceOff()
        if (err) {
            return console.error(err)
        }

        G29.on('wheel-turn', function (data) {
            state.wheel = data
        })

        G29.on('pedals-gas', function (data) {
            state.throttle = data
        })

        G29.on('pedals-brake', function (data) {
            state.brake = data
        })
    })

    const device = new SerialPort({ path: '/dev/tty.usbserial-0001', baudRate: 922190 })

    setInterval(() => {
        let throttle = Math.round(140 + (state.throttle * 140) - (state.brake * 140))
        if (throttle > 255) throttle = 255
        if (state.throttle > 0 && throttle < 140) throttle = 140
        throttle = throttle.toString().padStart(3, '0')
        let steering = Math.round(state.wheel * 2.55).toString().padStart(3, '0')
        const data = `${steering}${throttle}\n`

        device.write(data)
    }, 0.5);
}

main()