package main

import (
	"flag"
	"fmt"
	"log"
	"os"
	"strings"

	"microjelly.com/beeon/app/pkg/device/keycodes"

	"microjelly.com/beeon/app/pkg/device/report3"

	"microjelly.com/beeon/app/pkg/device"
)

var (
	appVersion string = "1.01"
	vendorID   uint16 = 0x16d0
	productID  uint16 = 0x09fa
)

func main() {

	var (
		action       string            = "none"
		serialNumber string            = ""
		inState      string            = ""
		newState     report3.State     = report3.StateUnset
		inRate       string            = ""
		newRate      report3.Rate      = report3.RateUnset
		newMode      report3.Mode      = report3.ModeUnset
		inMouseMode  string            = ""
		newMouseMode report3.MouseMode = report3.MouseModeUnset
		inKeyCode    uint              = 255
		newKeyCode   keycodes.KeyCode  = keycodes.KeyUnset
	)

	debugFlag := flag.Bool("debug", false, "enable debug logging")
	listFlag := flag.Bool("list", false, "list connected devices")
	readFlag := flag.Bool("read", false, "read device config")
	flag.StringVar(&serialNumber, "serial", "", "target specific device by serial_number")
	flag.StringVar(&inState, "state", "", "change device state <idle|active>")
	flag.StringVar(&inRate, "rate", "", "change device rate <extra-slow|slow|normal|fast>")
	flag.StringVar(&inMouseMode, "mouse", "", "change to mouse mode and set mode <circle|random>")
	flag.UintVar(&inKeyCode, "keyboard", 256, "change to keyboard mode and set keycod")
	flag.Parse()

	if *debugFlag {
		device.SetLogLevel(device.LogDebug)
	}

	if *listFlag {
		action = "list"
	} else if *readFlag {
		action = "read"
	}

	log.Printf("beeon-cli core:%s usb:%t", device.Version(), device.UsbSupported())

	if serialNumber != "" {
		log.Printf("serial:%s", serialNumber)
	}

	if action == "list" {
		devs, err := device.Enumerate(vendorID, productID)
		if err != nil {
			panic(err)
		}
		for i, _dev := range devs {
			log.Printf("[%d] %s:v%s:%s:%s",
				i,
				_dev.Serial,
				fmt.Sprintf("%d.%02d", (_dev.Version&0xff00)>>8, (_dev.Version&0x00ff)),
				_dev.Manufacturer,
				_dev.Product,
			)
		}
		os.Exit(0)
	}

	if action == "read" {
		r3, err := device.ReadReport3(vendorID, productID, serialNumber)
		if err != nil {
			log.Printf(err.Error())
			os.Exit(1)
		}
		log.Printf("%+v", r3)
	}

	if inMouseMode != "" {
		switch strings.ToLower(inMouseMode) {
		case "circle":
			newMouseMode = report3.MouseModeCircle
			newMode = report3.ModeMouse
			action = "write"
		case "random":
			newMouseMode = report3.MouseModeRandom
			newMode = report3.ModeMouse
			action = "write"
		default:
			log.Printf("invalid mouse-mode %s", inMouseMode)
		}
	}

	if inKeyCode != 256 && action == "none" {
		newKeyCode = keycodes.KeyCode(inKeyCode)
		newMode = report3.ModeKeyboard
		action = "write"
	}

	if inState != "" {
		switch strings.ToLower(inState) {
		case "idle":
			newState = report3.StateIdle
			action = "write"
		case "active":
			newState = report3.StateActive
			action = "write"
		default:
			log.Printf("invalid state %s", inState)
		}
	}

	if inRate != "" {
		switch strings.ToLower(inRate) {
		case "extra-slow":
			newRate = report3.RateExtraSlow
			action = "write"
		case "slow":
			newRate = report3.RateSlow
			action = "write"
		case "normal":
			newRate = report3.RateNormal
			action = "write"
		case "fast":
			newRate = report3.RateFast
			action = "write"
		default:
			log.Printf("invalid rate %s", inRate)
		}
	}

	if action == "none" {
		//flag.PrintDefaults()
		os.Exit(1)
	}

	if action == "write" {
		hasChange := false
		r3, err := device.ReadReport3(vendorID, productID, serialNumber)
		if err != nil {
			log.Printf(err.Error())
			os.Exit(1)
		}

		if (newMode != report3.ModeUnset) && (r3.Mode != newMode) {
			r3.Mode = newMode
			hasChange = true
		} else {
			r3.Mode = report3.ModeUnset
		}

		if newKeyCode != keycodes.KeyUnset && (newKeyCode != r3.KeyCode) {
			r3.KeyCode = newKeyCode
			hasChange = true
		} else {
			r3.KeyCode = keycodes.KeyUnset
		}

		if newMouseMode != report3.MouseModeUnset && (newMouseMode != r3.MouseMode) {
			r3.MouseMode = newMouseMode
			hasChange = true
		} else {
			r3.MouseMode = report3.MouseModeUnset
		}

		if newState != report3.StateUnset && (newState != r3.State) {
			r3.State = newState
			hasChange = true
		} else {
			r3.State = report3.StateUnset
		}

		if newRate != report3.RateUnset && (newRate != r3.Rate) {
			r3.Rate = newRate
			hasChange = true
		} else {
			r3.Rate = report3.RateUnset
		}

		if hasChange {
			err := device.WriteReport3(vendorID, productID, serialNumber, r3.Bytes())
			if err != nil {
				log.Printf(err.Error())
				os.Exit(1)
			}
			log.Printf("changes made")
		} else {
			log.Printf("no changes")
		}
	}

}
