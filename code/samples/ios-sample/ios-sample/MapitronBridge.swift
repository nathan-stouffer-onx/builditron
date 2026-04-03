import mapitron

struct MapitronBridge {
    static func buildType() -> String {
        // std::string -> Swift String via string interpolation
        "\(mapitron.build_type())"
    }

    static func shutdown() {
        mapitron.shutdown()
    }

    static func add(_ lhs: Int32, _ rhs: Int32) -> Int32 {
        mapitron.add(lhs, rhs)
    }

    static func addLayer(_ json: String) {
        // Swift String -> std::string via withCString
        json.withCString { mapitron.add_layer(std.string($0)) }
    }

    static func loadPrograms() -> Bool {
        mapitron.load_programs()
    }
}
