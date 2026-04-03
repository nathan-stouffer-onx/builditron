import ProjectDescription

let project = Project(
    name: "ios-sample",
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
                .xcframework(path: "../../../packages/ios/mapitron/mapitron.xcframework"),
            ],
            settings: .settings(base: [
                "ARCHS": "arm64",
                "SWIFT_VERSION": "5.0",
                "OTHER_SWIFT_FLAGS": "-cxx-interoperability-mode=default",
            ])
        ),
    ]
)
