##
##
##

.PHONY: help all

help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := all

bin/:
	@mkdir -p bin

all: ## build linux, darwin & windows
all: linux darwin windows

linux: bin/ ## build linux binary
	@go get github.com/marcinbor85/gohex
	@go build -installsuffix cgo -ldflags=" -s -w" -o bin/linux-beeon-sn sn.go

darwin: bin/ ## build darwin binary
	@go get github.com/marcinbor85/gohex
	@GOOS=darwin GOARCH=amd64 \
		go build -installsuffix cgo -ldflags=" -s -w" -o bin/darwin-beeon-sn sn.go

windows: bin/ ## build windows binary
	@go get github.com/marcinbor85/gohex
	@GOOS=windows GOARCH=amd64 \
		go build -installsuffix cgo -ldflags=" -s -w" -o bin/beeon-sn.exe sn.go

clean:
	@rm -rf bin