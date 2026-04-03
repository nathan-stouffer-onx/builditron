// swift-tools-version: 5.9
import PackageDescription

let package = Package(
    name: "mapitron",
    products: [
        .library(name: "mapitron", targets: ["mapitron"]),
    ],
    targets: [
        .binaryTarget(name: "mapitron", path: "mapitron.xcframework"),
    ]
)
