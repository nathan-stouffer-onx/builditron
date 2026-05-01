plugins {
    alias(libs.plugins.android.application)
    alias(libs.plugins.kotlin.android)
}

// rootDir = android-sample/, so 4 parentFile calls reach the repo root
val repoRoot = rootDir.parentFile.parentFile.parentFile.parentFile.canonicalFile

android {
    namespace = "com.example.androidsample"
    compileSdk = 35

    // Use the same NDK that the CMake presets use
    ndkVersion = "27.0.12077973"
    ndkPath = repoRoot.resolve("code/deps/android-ndk/android-ndk-r27").absolutePath

    defaultConfig {
        applicationId = "com.example.androidsample"
        minSdk = 24
        targetSdk = 35
        versionCode = 1
        versionName = "1.0"

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
            isDebuggable = true
        }
        release {
            isMinifyEnabled = true
            proguardFiles(
                getDefaultProguardFile("proguard-android-optimize.txt"),
                "proguard-rules.pro"
            )
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
        "src/main/kotlin",
        "${repoRoot}/code/src/mapitron/kotlin"
    )
}

dependencies {
    implementation(libs.androidx.core.ktx)
    implementation(libs.androidx.appcompat)
    implementation(libs.material)
    implementation(libs.androidx.constraintlayout)
}
