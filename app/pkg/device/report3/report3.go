package report3

import (
	"fmt"

	"microjelly.com/beeon/app/pkg/device/keycodes"
)

type State uint8

const (
	StateIdle   = State(10)
	StateActive = State(20)
	StateUnset  = State(255)
)

func (r State) String() string {
	switch r {
	case StateActive:
		return "active"
	case StateIdle:
		return "idle"
	case StateUnset:
		return "unset"
	default:
		return "unknown"
	}
}

type Mode uint8

const (
	ModeMouse    = Mode(10)
	ModeKeyboard = Mode(20)
	ModeUnset    = Mode(255)
)

func (r Mode) String() string {
	switch r {
	case ModeMouse:
		return "mouse"
	case ModeKeyboard:
		return "keyboard"
	case ModeUnset:
		return "unset"
	default:
		return "unknown"
	}
}

type Rate uint8

const (
	RateFast      = Rate(1)
	RateNormal    = Rate(8)
	RateSlow      = Rate(16)
	RateExtraSlow = Rate(32)
	RateUnset     = Rate(255)
)

func (r Rate) String() string {
	switch r {
	case RateFast:
		return "fast"
	case RateNormal:
		return "normal"
	case RateSlow:
		return "slow"
	case RateExtraSlow:
		return "extra-slow"
	case RateUnset:
		return "unset"
	default:
		return fmt.Sprintf("custom (%d)", r)
	}
}

type MouseMode uint8

const (
	MouseModeCircle = MouseMode(10)
	MouseModeRandom = MouseMode(20)
	MouseModeUnset  = MouseMode(255)
)

func (r MouseMode) String() string {
	switch r {
	case MouseModeCircle:
		return "circle"
	case MouseModeRandom:
		return "random"
	case MouseModeUnset:
		return "unset"
	default:
		return "unknown"
	}
}

type Report struct {
	State     State
	Mode      Mode
	Rate      Rate
	KeyCode   keycodes.KeyCode
	MouseMode MouseMode
}

func (r Report) String() string {
	switch r.Mode {
	case ModeMouse:
		return fmt.Sprintf("{Mode: %s, MouseMode: %s, Rate: %s, State: %s}", r.Mode, r.MouseMode, r.Rate, r.State)
	case ModeKeyboard:
		return fmt.Sprintf("{Mode: %s, KeyCode: %s, Rate: %s, State: %s}", r.Mode, r.KeyCode, r.Rate, r.State)
	case ModeUnset:
		return fmt.Sprintf("{Mode: %s, MouseMode: %s, KeyCode: %s, Rate: %s, State: %s}", r.Mode, r.MouseMode, r.KeyCode, r.Rate, r.State)
	default:
		return "{invalid}"
	}
}

func New(b []byte) *Report {
	r := new(Report)
	r.State = State(b[1])
	r.Mode = Mode(b[2])
	r.Rate = Rate(b[3])
	r.KeyCode = keycodes.KeyCode(b[4])
	r.MouseMode = MouseMode(b[5])
	return r
}

func (r Report) Bytes() []byte {
	b := make([]byte, 6)
	b[0] = 3
	b[1] = uint8(r.State)
	b[2] = uint8(r.Mode)
	b[3] = uint8(r.Rate)
	b[4] = uint8(r.KeyCode)
	b[5] = uint8(r.MouseMode)
	return b
}
