package device

import (
	"errors"
	"log"

	"microjelly.com/beeon/app/pkg/device/report3"
	"t0ddz.com/go/hid"
)

var (
	_devices  []Info
	_logLevel LogLevel = LogNone
)

// Version - returns the version of this module
func Version() string {
	return "v1.0.1"
}

// UsbSupported - returns true if usb is supported on this platform
func UsbSupported() bool {
	return hid.Supported()
}

// SetLogLevel - sets the logging level
func SetLogLevel(level LogLevel) {
	_logLevel = level
}

// Enumerate - gets connected devices
func Enumerate(vendorID uint16, productID uint16) ([]Info, error) {

	var (
		_devices []Info = nil
		pSN      string = ""
	)

	for _, dev := range hid.Enumerate(vendorID, productID) {
		if dev.Serial != pSN {
			_devices = append(_devices, Info{
				Serial:       dev.Serial,
				Version:      dev.Release,
				Manufacturer: dev.Manufacturer,
				Product:      dev.Product,
			})
			pSN = dev.Serial
		}
	}

	return _devices, nil
}

func open(vendorID uint16, productID uint16, serial string) (*hid.Device, error) {

	devices := hid.Enumerate(vendorID, productID)
	for _, dev := range devices {
		if (serial != "" && dev.Serial == serial) || serial == "" {
			_log(LogInfo, "opening device [%s]", dev.Serial)
			return dev.Open()
		}
	}
	return nil, errors.New("device not found")
}

// ReadReport3 - get device configuration
func ReadReport3(vendorID uint16, productID uint16, serial string) (*report3.Report, error) {

	report := []byte{0x03, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}
	dev, err := open(vendorID, productID, serial)
	if err != nil {
		return nil, err
	}
	defer dev.Close()
	_, err = dev.GetFeatureReport(report)
	if err != nil {
		return nil, err
	}
	r := report3.New(report)
	_log(LogDebug, "read %v > %v", report, r)
	return r, nil
}

// WriteReport3 - get device configuration
func WriteReport3(vendorID uint16, productID uint16, serial string, report []byte) error {

	dev, err := open(vendorID, productID, serial)
	if err != nil {
		return err
	}
	defer dev.Close()

	_log(LogDebug, "write %v > %v", report, report3.New(report))
	_, err = dev.SendFeatureReport(report)
	if err != nil {
		return err
	}

	return nil
}

func _log(level LogLevel, format string, v ...interface{}) {
	if level >= _logLevel {
		log.Printf(format, v...)
	}
}
