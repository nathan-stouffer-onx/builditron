plugins {
    alias(libs.plugins.android.library)
    alias(libs.plugins.kotlin.android)
}

group = "com.mapitron"
version = "1.0.0"

// rootDir = mapitron-package root, so 4 parentFile calls reach the repo root
val repoRoot = rootDir.parentFile.parentFile.parentFile.parentFile.canonicalFile

android {
    namespace = "com.mapitron"
    compileSdk = 35

    // Use the same NDK that the CMake presets use
    ndkVersion = "27.0.12077973"
    ndkPath = repoRoot.resolve("code/deps/android-ndk/android-ndk-r27").absolutePath

    defaultConfig {
        minSdk = 24

        externalNativeBuild {
            cmake {
                targets("mapitron-jni")
                arguments(
                    "-DCMAKE_TOOLCHAIN_FILE=${repoRoot}/code/deps/vcpkg/scripts/buildsystems/vcpkg.cmake",
                    "-DVCPKG_CHAINLOAD_TOOLCHAIN_FILE=${repoRoot}/code/deps/android-ndk/android-ndk-r27/build/cmake/android.toolchain.cmake",
                    "-DANDROID_PLATFORM=android-24",
                    "-DMAPITRON_IS_DESTINATION_BUILD=true"
                )
                abiFilters("arm64-v8a", "x86_64")
            }
        }
    }

    externalNativeBuild {
        cmake {
            path = repoRoot.resolve("CMakeLists.txt")
        }
    }

    buildTypes {
        debug {
        }
        create("relWithDebInfo") {
            initWith(buildTypes.getByName("debug"))
            externalNativeBuild { cmake { arguments("-DCMAKE_BUILD_TYPE=RelWithDebInfo") } }
        }
        release {
            isMinifyEnabled = false
            consumerProguardFiles("consumer-rules.pro")
        }
    }

    compileOptions {
        sourceCompatibility = JavaVersion.VERSION_11
        targetCompatibility = JavaVersion.VERSION_11
    }

    kotlinOptions {
        jvmTarget = "11"
    }

    sourceSets["main"].java.srcDirs(
        "${repoRoot}/code/src/mapitron/kotlin"
    )
}
