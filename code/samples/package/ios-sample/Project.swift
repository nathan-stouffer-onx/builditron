import ProjectDescription

let buildMapitronPackage = """
    export PATH="$PATH:/usr/local/bin:/opt/homebrew/bin"
    unset IPHONEOS_DEPLOYMENT_TARGET TVOS_DEPLOYMENT_TARGET \\
          WATCHOS_DEPLOYMENT_TARGET XROS_DEPLOYMENT_TARGET \\
          MACOSX_DEPLOYMENT_TARGET DRIVERKIT_DEPLOYMENT_TARGET \\
          SDKROOT
    "${SRCROOT}/../../../packages/ios/mapitron/bin/build_package.sh" "${CONFIGURATION}"
    """

let project = Project(
    name: "ios-sample",
    packages: [
        .local(path: "../../../packages/ios/mapitron")
    ],
    targets: [
        .target(
            name: "ios-sample",
            destinations: .iOS,
            product: .app,
            bundleId: "com.example.ios-sample-package",
            deploymentTargets: .iOS("17.0"),
            sources: ["ios-sample/**/*.swift"],
            resources: ["ios-sample/Assets.xcassets"],
            dependencies: [
                .package(product: "mapitron")
            ],
            settings: .settings(base: [
                "ARCHS": "arm64",
                "CLANG_CXX_LANGUAGE_STANDARD": "gnu++20",
                "OTHER_SWIFT_FLAGS": "-cxx-interoperability-mode=default",
                "SUPPORTED_PLATFORMS": "iphoneos iphonesimulator",
                "SWIFT_VERSION": "5.0",
            ]),
            additionalFiles: [
                "../../../src/**/*.cpp",
                "../../../src/**/*.hpp",
            ]
        )
    ],
    schemes: [
        .scheme(
            name: "ios-sample",
            buildAction: .buildAction(
                targets: [.target("ios-sample")],
                preActions: [
                    .executionAction(
                        title: "Build mapitron XCFramework",
                        scriptText: buildMapitronPackage,
                        target: .target("ios-sample")
                    )
                ]
            ),
            runAction: .runAction(configuration: .debug)
        )
    ]
)
