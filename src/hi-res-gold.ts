import * as THREE from "three";

// Finish the existing Blender side rails; the transmitting panels and print
// keep their geometry and material. Colors match the supplied Hi-Res SVG.
const pale = new THREE.Color("#ddc77c").toArray().map(n => n.toFixed(8)).join(", ");
const deep = new THREE.Color("#b4802c").toArray().map(n => n.toFixed(8)).join(", ");
type Shader = Parameters<THREE.Material["onBeforeCompile"]>[0];

export function shadeHiResGold(shader: Shader, amount?: { value: number }) {
  const input = amount ? "uniform float hiResAlbum;" : "attribute float hiResAlbum;";
  if (amount) shader.uniforms.hiResAlbum = amount;
  shader.vertexShader = `${input}\nvarying float vHiResAlbum;\nvarying vec2 vHiResPosition;\n` + shader.vertexShader;
  shader.vertexShader = shader.vertexShader.replace("#include <begin_vertex>",
    "#include <begin_vertex>\nvHiResAlbum = hiResAlbum;\nvHiResPosition = position.xy;");
  shader.fragmentShader = "varying float vHiResAlbum;\nvarying vec2 vHiResPosition;\n" + shader.fragmentShader;
  shader.fragmentShader = shader.fragmentShader.replace("#include <color_fragment>",
    `#include <color_fragment>
float hiResRail = clamp(vHiResAlbum, 0.0, 1.0) * (1.0 - step(-1.9703, vHiResPosition.x) + step(2.1685, vHiResPosition.x));
vec3 hiResGold = mix(vec3(${deep}), vec3(${pale}), clamp((vHiResPosition.y - 0.175) / 3.35, 0.0, 1.0));
diffuseColor.rgb = mix(diffuseColor.rgb, hiResGold, hiResRail);`);
  shader.fragmentShader = shader.fragmentShader.replace("#include <roughnessmap_fragment>",
    "#include <roughnessmap_fragment>\nroughnessFactor = mix(roughnessFactor, 0.24, hiResRail);");
  shader.fragmentShader = shader.fragmentShader.replace("#include <metalnessmap_fragment>",
    "#include <metalnessmap_fragment>\nmetalnessFactor = mix(metalnessFactor, 0.68, hiResRail);");
  shader.fragmentShader = shader.fragmentShader.replace("#include <emissivemap_fragment>",
    "#include <emissivemap_fragment>\ntotalEmissiveRadiance += hiResGold * hiResRail * 0.055;");
  shader.fragmentShader = shader.fragmentShader.replace("#include <transmission_fragment>",
    THREE.ShaderChunk.transmission_fragment.replace("material.transmission = transmission;",
      "material.transmission = transmission * (1.0 - hiResRail);"));
}

export function setHiResGold(group: THREE.Group, enabled: boolean) {
  group.userData.hiResGold = enabled;
  group.traverse(child => {
    if (!(child instanceof THREE.Mesh) || child.userData.surface !== "Ivory_Edges" || !child.userData.musicShell) return;
    child.userData.hiResGold = enabled;
    if (child.userData.hiResGoldUniform) child.userData.hiResGoldUniform.value = enabled ? 1 : 0;
  });
}
