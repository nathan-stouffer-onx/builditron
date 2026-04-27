import ProjectDescription
import ProjectDescriptionHelpers

let project = Project(
    name: "ios-sample-simulator",
    targets: [
        iosSampleTarget(name: "ios-sample-simulator", platform: "iphonesimulator", presetName: "dest-ios-simulator-ninja"),
    ],
    schemes: [
        iosSampleScheme(name: "ios-sample-simulator", presetName: "dest-ios-simulator-ninja"),
    ]
)
