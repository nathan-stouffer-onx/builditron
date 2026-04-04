import ProjectDescription

public func iosSampleTarget(name: String, platform: String, presetName: String) -> Target {
    .target(
        name: name,
        destinations: .iOS,
        product: .app,
        bundleId: "com.example.ios-sample",
        deploymentTargets: .iOS("17.0"),
        sources: ["../ios-sample/**/*.swift"],
        resources: ["../ios-sample/Assets.xcassets"],
        settings: .settings(base: [
            "ARCHS": "arm64",
            "SDKROOT": SettingValue(stringLiteral: platform),
            "SUPPORTED_PLATFORMS": SettingValue(stringLiteral: platform),
            "SWIFT_VERSION": "5.0",
            "CLANG_CXX_LANGUAGE_STANDARD": "gnu++20",
            "OTHER_SWIFT_FLAGS": "-cxx-interoperability-mode=default",
            "SWIFT_INCLUDE_PATHS": "$(SRCROOT)/../../../../src/mapitron/include/public $(SRCROOT)/../../../../deps/lucid/include/interface",
            "HEADER_SEARCH_PATHS": "$(SRCROOT)/../../../../src/mapitron/include/public",
            "LIBRARY_SEARCH_PATHS": "$(SRCROOT)/../../../../../build/\(presetName)/lib/$(CONFIGURATION)",
            "OTHER_LDFLAGS": "-lmapitron-ios",
        ]),
        additionalFiles: [
            "../../../../../code/src/**/*.cpp",
            "../../../../../code/src/**/*.hpp",
        ]
    )
}

public func iosSampleScheme(name: String, presetName: String) -> Scheme {
    let targetRef: TargetReference = .target(name)
    let buildMapitron = """
        export PATH="$PATH:/usr/local/bin:/opt/homebrew/bin"
        unset IPHONEOS_DEPLOYMENT_TARGET TVOS_DEPLOYMENT_TARGET \\
              WATCHOS_DEPLOYMENT_TARGET XROS_DEPLOYMENT_TARGET \\
              MACOSX_DEPLOYMENT_TARGET DRIVERKIT_DEPLOYMENT_TARGET \\
              SDKROOT
        cmake --build "$SRCROOT/../../../../../build/\(presetName)" \\
              --config "$CONFIGURATION" \\
              --target mapitron
        """
    return .scheme(
        name: name,
        buildAction: .buildAction(
            targets: [targetRef],
            preActions: [
                .executionAction(
                    title: "Build mapitron",
                    scriptText: buildMapitron,
                    target: targetRef
                )
            ]
        ),
        runAction: .runAction(configuration: .debug)
    )
}
