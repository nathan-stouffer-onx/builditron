REPO_ROOT   := $(realpath ../../../..)
LOCAL_PROPS := local.properties
CMAKE_BIN   := $(shell which cmake 2>/dev/null)
CMAKE_DIR   := $(patsubst %/bin/,%,$(dir $(CMAKE_BIN)))

.PHONY: init ndk

init: ndk $(LOCAL_PROPS)

ndk:
	$(MAKE) -C "$(REPO_ROOT)/code/deps/android-ndk" install

$(LOCAL_PROPS):
	@printf 'cmake.dir=%s\n' "$(CMAKE_DIR)" > $@
	@echo "Created local.properties"
