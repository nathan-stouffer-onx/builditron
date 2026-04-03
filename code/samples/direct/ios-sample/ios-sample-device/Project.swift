import ProjectDescription
import ProjectDescriptionHelpers

let project = Project(
    name: "ios-sample-device",
    targets: [
        iosSampleTarget(platform: "iphoneos", presetName: "dest-ios-device-xcode"),
    ],
    schemes: [
        iosSampleScheme(platform: "iphoneos", presetName: "dest-ios-device-xcode"),
    ]
)
