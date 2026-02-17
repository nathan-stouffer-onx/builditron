import { describe, it, expect, beforeAll } from 'vitest';

// Get the build type from environment (defaults to Debug)
// @ts-expect-error - BUILD_TYPE is defined by Vite config
const buildType = (import.meta.env.BUILD_TYPE as string).toLowerCase();

describe('Mapitron WASM Module', () => {
  let mapitron: any;

  beforeAll(async () => {
    // Dynamically import the mapitron WebAssembly module based on build type
    const { default: createMapitronModule } = await import(`./wasm/${buildType}/mapitron.js`);
    mapitron = await createMapitronModule();
  });

  it('should load the WASM module', () => {
    expect(mapitron).toBeDefined();
  });

  it('should perform basic addition', () => {
    const result = mapitron.add(5, 3);
    expect(result).toBe(8);
  });

  it('should perform addition with negative numbers', () => {
    const result = mapitron.add(-5, 3);
    expect(result).toBe(-2);
  });

  it('should load shader programs', () => {
    const result = mapitron.loadPrograms();
    expect(result).toBe(true);
  });

  it('should load font', () => {
    const fontInfo = mapitron.loadRoboto();
    expect(fontInfo).toBeDefined();
    expect(typeof fontInfo).toBe('string');
  });

  it('should add a layer', () => {
    const layerJson = JSON.stringify({
      id: 'test-layer',
      type: 'fill',
      source: 'test-source'
    });

    // Should not throw
    expect(() => {
      mapitron.addLayer(layerJson);
    }).not.toThrow();
  });

  it('should handle different layer types', () => {
    const layerTypes = ['fill', 'line', 'symbol'];

    layerTypes.forEach((type, index) => {
      const layerJson = JSON.stringify({
        id: `test-layer-${type}`,
        type,
        source: `test-source-${index}`
      });

      expect(() => {
        mapitron.addLayer(layerJson);
      }).not.toThrow();
    });
  });
});
