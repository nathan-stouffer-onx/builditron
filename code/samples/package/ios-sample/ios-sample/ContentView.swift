import SwiftUI

struct ContentView: View {
    var body: some View {
        VStack {
            Text("build type: \(MapitronBridge.buildType())")
            Text("add(3, 4) = \(MapitronBridge.add(3, 4))")
        }
        .padding()
    }
}
