import createMapitronModule from 'mapitron';

async function main() {
  const statusEl = document.getElementById('status');

  if (!statusEl) {
    console.error('Status element not found');
    return;
  }

  try {
    statusEl.textContent = 'Loading WebAssembly module...';

    const mapitron = await createMapitronModule();

    statusEl.textContent = 'Module loaded! Running tests...';

    const sum = mapitron.add(5, 3);
    console.log('5 + 3 =', sum);

    const programsLoaded = mapitron.loadPrograms();
    console.log('Programs loaded:', programsLoaded);

    const fontInfo = mapitron.loadRoboto();
    console.log('Font info:', fontInfo);

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
