#include <babylon/cameras/arc_rotate_camera.h>
#include <babylon/interfaces/irenderable_scene.h>
#include <babylon/lights/hemispheric_light.h>
#include <babylon/materials/standard_material.h>
#include <babylon/materials/textures/texture.h>
#include <babylon/meshes/builders/mesh_builder_options.h>
#include <babylon/meshes/mesh_builder.h>
#include <babylon/samples/babylon_register_sample.h>

namespace BABYLON {
namespace Samples {

/**
 * @brief Opacity Texture Scene. Example demonstrating how an image with a transparency gradient can
 * be applied to a material using opacityTexture.
 * @see http://www.babylonjs-playground.com/#20OAV9#24
 */
struct OpacityTextureScene : public IRenderableScene {

  OpacityTextureScene(ICanvas* iCanvas) : IRenderableScene(iCanvas)
  {
  }

  ~OpacityTextureScene() override = default;

  const char* getName() override
  {
    return "Opacity Texture Scene";
  }

  void initializeScene(ICanvas* canvas, Scene* scene) override
  {
    // Camera
    auto camera
      = ArcRotateCamera::New("Camera", -Math::PI_2, Math::PI_2, 5.f, Vector3::Zero(), scene);
    camera->attachControl(canvas, true);

    // Light direction is up and left
    auto light     = HemisphericLight::New("hemiLight", Vector3(-1, 1, 0), scene);
    light->diffuse = Color3::White();

    auto mat0            = StandardMaterial::New("mat0", scene);
    mat0->diffuseColor   = Color3::Red();
    mat0->opacityTexture = Texture::New("textures/transparencyGradient.png", scene);

    auto mat1          = StandardMaterial::New("mat1", scene);
    mat1->diffuseColor = Color3::Magenta();

    // Plane with opacity material
    PlaneOptions planeOptions;
    auto plane      = MeshBuilder::CreatePlane("plane", planeOptions, scene);
    plane->material = mat0;

    // Shere
    SphereOptions sphereOptions;
    auto sphere1          = MeshBuilder::CreateSphere("sphere1", sphereOptions, scene);
    sphere1->material     = mat1;
    sphere1->position().z = 1.5f;
  }

}; // end of struct OpacityTextureScene

BABYLON_REGISTER_SAMPLE("Textures", OpacityTextureScene)

} // end of namespace Samples
} // end of namespace BABYLON
