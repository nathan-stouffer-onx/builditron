import createMapitronModule from './wasm/mapitron.js';

async function main() {
  const statusEl = document.getElementById('status');

  if (!statusEl) {
    console.error('Status element not found');
    return;
  }

  try {
    statusEl.textContent = 'Loading WebAssembly module...';

    // Load the mapitron WebAssembly module
    const mapitron = await createMapitronModule();

    statusEl.textContent = 'Module loaded! Running tests...';

    // Test the basic add function
    const sum = mapitron.add(5, 3);
    console.log('5 + 3 =', sum);

    // Test loading programs
    const programsLoaded = mapitron.loadPrograms();
    console.log('Programs loaded:', programsLoaded);

    // Test loading font
    const fontInfo = mapitron.loadRoboto();
    console.log('Font info:', fontInfo);

    // Test adding a layer
    const layerJson = JSON.stringify({
      id: 'test-layer',
      type: 'fill',
      source: 'test-source'
    });
    mapitron.addLayer(layerJson);
    console.log('Layer added');

    statusEl.textContent = 'Ready! Check console for test results.';
    statusEl.style.color = 'green';

  } catch (error) {
    console.error('Error loading mapitron:', error);
    statusEl.textContent = `Error: ${error}`;
    statusEl.style.color = 'red';
  }
}

main();
