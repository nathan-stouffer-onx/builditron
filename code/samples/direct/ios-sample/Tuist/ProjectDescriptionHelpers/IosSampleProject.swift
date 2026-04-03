import ProjectDescription

public func iosSampleTarget(platform: String, presetName: String) -> Target {
    .target(
        name: "ios-sample-\(platform)",
        destinations: .iOS,
        product: .app,
        bundleId: "com.example.ios-sample",
        deploymentTargets: .iOS("17.0"),
        sources: ["../ios-sample/**/*.swift"],
        resources: ["../ios-sample/Assets.xcassets"],
        settings: .settings(base: [
            "SDKROOT": SettingValue(stringLiteral: platform),
            "SUPPORTED_PLATFORMS": SettingValue(stringLiteral: platform),
            "SWIFT_VERSION": "5.0",
            "CLANG_CXX_LANGUAGE_STANDARD": "gnu++20",
            "OTHER_SWIFT_FLAGS": "-cxx-interoperability-mode=default",
            "SWIFT_INCLUDE_PATHS": "$(SRCROOT)/../../../../src/mapitron/include/public $(SRCROOT)/../../../../deps/lucid/include/interface",
            "HEADER_SEARCH_PATHS": "$(SRCROOT)/../../../../src/mapitron/include/public",
            "LIBRARY_SEARCH_PATHS": "$(SRCROOT)/../../../../../out/build/\(presetName)/lib/$(CONFIGURATION)",
            "OTHER_LDFLAGS": "-lmapitron-ios",
        ])
    )
}

public func iosSampleScheme(platform: String, presetName: String) -> Scheme {
    let targetRef: TargetReference = .target("ios-sample-\(platform)")
    return .scheme(
        name: "ios-sample-\(platform)",
        buildAction: .buildAction(
            targets: [targetRef],
            preActions: [
                .executionAction(
                    title: "Build mapitron",
                    scriptText: "export PATH=\"$PATH:/usr/local/bin:/opt/homebrew/bin\"; cmake --build \"$SRCROOT/../../../../../out/build/\(presetName)\"",
                    target: targetRef
                )
            ]
        ),
        runAction: .runAction(configuration: .debug)
    )
}
