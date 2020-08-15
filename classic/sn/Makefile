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
	@GOOS=linux GOARCH=amd64 \
		go build -installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-classic-sn-linux-amd64 \
			sn.go

darwin: bin/ ## build darwin binary
	@go get github.com/marcinbor85/gohex
	@GOOS=darwin GOARCH=amd64 \
		go build -installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-classic-sn-darwin-amd64 \
			sn.go

windows: bin/ ## build windows binary
	@go get github.com/marcinbor85/gohex
	@GOOS=windows GOARCH=amd64 \
		go build -installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-classic-sn-windows-amd64.exe \
			sn.go

mod-tidy:
	@go clean --modcache
	@GOPROXY=direct GOSUMDB=off go mod tidy

clean:
	@rm -rf bin