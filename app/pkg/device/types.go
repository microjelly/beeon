package device

// Info - short list of details
type Info struct {
	Serial       string
	Manufacturer string
	Version      uint16
	Product      string
}

// LogLevel - something
type LogLevel uint

// LogNone - disabled logging
// LogInfo - basic logging
// LogDebug - even more
const (
	LogDebug LogLevel = iota
	LogInfo
	LogNone
)
