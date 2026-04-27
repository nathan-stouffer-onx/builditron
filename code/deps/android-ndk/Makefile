# r27 = 27.0.12077973 (r27b, r27c, etc. are separate patch releases)
NDK_RELEASE := r27
NDK_DIR     := android-ndk-$(NDK_RELEASE)

ifeq ($(OS), Windows_NT)
    PLATFORM := windows
    EXTRACT  := tar -xf
else
    UNAME := $(shell uname -s)
    ifeq ($(UNAME), Darwin)
        PLATFORM := darwin
    else
        PLATFORM := linux
    endif
    EXTRACT := unzip -q
endif

ZIP := android-ndk-$(NDK_RELEASE)-$(PLATFORM).zip
URL := https://dl.google.com/android/repository/$(ZIP)

.PHONY: install verify clean

install: $(NDK_DIR)

$(NDK_DIR):
	curl -L -o $(ZIP) $(URL)
	$(EXTRACT) $(ZIP)
	rm -f $(ZIP)

verify:
	@grep -q "Pkg.Revision = 27.0.12077973" $(NDK_DIR)/source.properties \
		&& echo "OK: NDK 27.0.12077973" \
		|| (echo "FAIL: unexpected NDK version"; cat $(NDK_DIR)/source.properties; exit 1)

clean:
	rm -rf $(NDK_DIR)
