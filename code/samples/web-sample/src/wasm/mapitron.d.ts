// TypeScript definitions for the mapitron WebAssembly module

export interface MapitronModule {
  shutdown(): void;
  add(lhs: number, rhs: number): number;
  addLayer(layerJson: string): void;
  loadRoboto(): string;
  loadPrograms(): boolean;
}

declare function createMapitronModule(): Promise<MapitronModule>;

export default createMapitronModule;
