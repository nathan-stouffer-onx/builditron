import ProjectDescription
import ProjectDescriptionHelpers

let project = Project(
    name: "ios-sample-device",
    targets: [
        iosSampleTarget(name: "ios-sample-device", platform: "iphoneos", presetName: "dest-ios-device-ninja"),
    ],
    schemes: [
        iosSampleScheme(name: "ios-sample-device", presetName: "dest-ios-device-ninja"),
    ]
)
