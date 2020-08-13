##
##
##

.PHONY: help all linux darwin windows cli

help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := all

bin/:
	@mkdir -p bin

all: ## build linux, darwin & windows
all: linux darwin windows

cli: linux-cli windows-cli darwin-cli

linux: linux-cli
windows: windows-cli
darwin: darwin-cli

linux-cli: bin/ ## build linux binary
	@GOOS=linux GOARCH=amd64 CGO_ENABLED=1 \
		go build \
			-installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-cli-linux-amd64 \
			microjelly.com/beeon/app/cmd/cli

darwin-cli: bin/ ## build darwin binary
	@GOOS=darwin GOARCH=amd64 CGO_ENABLED=1 \
		CC=o64-clang CXX=o64-clang++ \
		LDFLAGS="-linkmode external -s" \
		go build \
			-installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-cli-darwin-amd64 \
			microjelly.com/beeon/app/cmd/cli

windows-cli: bin/ ## build windows binary
	@GOOS=windows GOARCH=amd64 CGO_ENABLED=1 \
		CC=x86_64-w64-mingw32-gcc \
		go build \
			-installsuffix cgo -ldflags=" -s -w" \
			-o bin/beeon-cli-windows-amd64.exe \
			microjelly.com/beeon/app/cmd/cli

mod-tidy:
	@go clean --modcache
	@GOPROXY=direct GOSUMDB=off go mod tidy

clean:
	@rm -rf bin