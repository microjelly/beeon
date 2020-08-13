TARGETS := $(shell ls scripts)

.dapper:
	@echo Downloading dapper
	@curl -sL https://releases.rancher.com/dapper/latest/dapper-`uname -s`-`uname -m` > .dapper.tmp
	@@chmod +x .dapper.tmp
	@./.dapper.tmp -v
	@mv .dapper.tmp .dapper

$(TARGETS): .dapper
	cd ../ && $(PWD)/.dapper -f build/Dockerfile.dapper $@
	@yes | docker image prune > /dev/null

.PHONY: $(TARGETS)
.DEFAULT_GOAL := cli

clean:
	@rm -rf $(PWD)/bin $(PWD)/.dapper $(PWD)/Dockerfile.dapper[0-9]*
	@docker rmi app:master

shell-bind: .dapper
	cd ../ && $(PWD)/.dapper -f build/Dockerfile.dapper -m bind -s