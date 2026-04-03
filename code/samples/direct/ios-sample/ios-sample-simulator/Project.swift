import ProjectDescription
import ProjectDescriptionHelpers

let project = Project(
    name: "ios-sample-simulator",
    targets: [
        iosSampleTarget(platform: "iphonesimulator", presetName: "dest-ios-simulator-xcode"),
    ],
    schemes: [
        iosSampleScheme(platform: "iphonesimulator", presetName: "dest-ios-simulator-xcode"),
    ]
)
