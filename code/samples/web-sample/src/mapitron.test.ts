import { describe, it, expect, beforeAll } from 'vitest';
import createMapitronModule, { MainModule } from 'mapitron';

describe('Mapitron WASM Module', () => {
  let mapitron: MainModule;

  beforeAll(async () => {
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
