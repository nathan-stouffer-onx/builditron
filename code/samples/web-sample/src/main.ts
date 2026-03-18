import { MainModule } from 'mapitron';

const modules = {
  // TODO (stouff) ask web people if this is undesirable
  Debug:          () => import(/* @vite-ignore */ 'mapitron/Debug'),
  Release:        () => import(/* @vite-ignore */ 'mapitron/Release'),
  RelWithDebInfo: () => import(/* @vite-ignore */ 'mapitron/RelWithDebInfo'),
  MinSizeRel:     () => import(/* @vite-ignore */ 'mapitron/MinSizeRel'),
};

type BuildType = keyof typeof modules;

function getBuildType(): BuildType {
  const param = new URLSearchParams(window.location.search).get('build');
  return (param && param in modules) ? param as BuildType : 'MinSizeRel';
}

async function main() {
  const statusEl = document.getElementById('status');

  if (!statusEl) {
    console.error('Status element not found');
    return;
  }

  const build = getBuildType();

  try {
    statusEl.textContent = `Loading WebAssembly module (${build})...`;

    const { default: createMapitronModule } = await modules[build]();
    // TODO (stouff) see if we can rename this type
    const mapitron: MainModule = await createMapitronModule();

    statusEl.textContent = 'Module loaded! Running tests...';

    const buildType = mapitron.build_type();
    console.log('Build type:', buildType);

    const sum = mapitron.add(5, 3);
    console.log('5 + 3 =', sum);

    const programsLoaded = mapitron.load_programs();
    console.log('Programs loaded:', programsLoaded);

    const fontInfo = mapitron.load_roboto();
    console.log('Font info:', fontInfo);

    const layerJson = JSON.stringify({
      id: 'test-layer',
      type: 'fill',
      source: 'test-source'
    });
    mapitron.add_layer(layerJson);
    console.log('Layer added');

    statusEl.textContent = `Ready (${build})! Check console for test results.`;
    statusEl.style.color = 'green';

  } catch (error) {
    console.error('Error loading mapitron:', error);
    statusEl.textContent = `Error: ${error}`;
    statusEl.style.color = 'red';
  }
}

main();
