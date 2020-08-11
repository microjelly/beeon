##
##
##

MN_VERSION=2.04

.PHONY: help beeon

help: ## This help.
	@awk 'BEGIN {FS = ":.*?## "} /^[a-zA-Z_-]+:.*?## / {printf "\033[36m%-30s\033[0m %s\n", $$1, $$2}' $(MAKEFILE_LIST)

.DEFAULT_GOAL := beeon

work/:
	@mkdir -p work

work/${MN_VERSION}.tar.gz: work/
	@wget -O work/${MN_VERSION}.tar.gz https://github.com/micronucleus/micronucleus/archive/${MN_VERSION}.tar.gz

work/micronucleus-${MN_VERSION}/firmware/Makefile: work/${MN_VERSION}.tar.gz
	@echo "Unpacking/Patching micronucleus-${MN_VERSION}"
	@cd work && tar zxf ${MN_VERSION}.tar.gz
	@cp -r beeon/ work/micronucleus-${MN_VERSION}/firmware/configuration/

beeon: work/micronucleus-${MN_VERSION}/firmware/Makefile ## build bootloader
	@echo "Building"
	@make -C  work/micronucleus-${MN_VERSION}/firmware CONFIG=beeon

clean:
	@rm -rf work