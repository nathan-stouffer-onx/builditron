import SwiftUI

struct ContentView: View {
    @State private var result: String = "tap to call into mapitron"

    var body: some View {
        VStack(spacing: 20) {
            Text("mapitron package sample")
                .font(.headline)
            Text("build: \(MapitronBridge.buildType())")
                .font(.subheadline)
                .foregroundStyle(.secondary)
            Text(result)
                .font(.body)
                .padding()
                .background(.quaternary, in: RoundedRectangle(cornerRadius: 8))
            Button("add(3, 4)") {
                result = "3 + 4 = \(MapitronBridge.add(3, 4))"
            }
            .buttonStyle(.borderedProminent)
        }
        .padding()
    }
}

#Preview {
    ContentView()
}
