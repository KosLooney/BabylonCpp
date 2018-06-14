#include <babylon/loading/plugins/babylon/babylon_file_loader.h>

#include <babylon/actions/action_manager.h>
#include <babylon/animations/animation.h>
#include <babylon/babylon_stl_util.h>
#include <babylon/bones/skeleton.h>
#include <babylon/cameras/camera.h>
#include <babylon/core/json.h>
#include <babylon/core/logging.h>
#include <babylon/engine/scene.h>
#include <babylon/lensflare/lens_flare_system.h>
#include <babylon/lights/light.h>
#include <babylon/lights/shadows/shadow_generator.h>
#include <babylon/loading/scene_loader.h>
#include <babylon/materials/material.h>
#include <babylon/materials/multi_material.h>
#include <babylon/mesh/geometry.h>
#include <babylon/mesh/mesh.h>
#include <babylon/mesh/primitive_geometries.h>
#include <babylon/morph/morph_target_manager.h>
#include <babylon/particles/particle_system.h>
#include <babylon/tools/tools.h>

namespace BABYLON {

BabylonFileLoader::BabylonFileLoader()
{
  extensions.mapping.emplace(::std::make_pair(".babylon", false));
}

BabylonFileLoader::~BabylonFileLoader()
{
}

Material* BabylonFileLoader::parseMaterialById(const string_t& id,
                                               const Json::value& parsedData,
                                               Scene* scene,
                                               const string_t& rootUrl) const
{
  for (const auto& parsedMaterial : Json::GetArray(parsedData, "materials")) {
    if (Json::GetString(parsedData, "id") == id) {
      return Material::Parse(parsedMaterial, scene, rootUrl);
    }
  }
  return nullptr;
}

bool BabylonFileLoader::isDescendantOf(const Json::value& mesh,
                                       const vector_t<string_t>& names,
                                       vector_t<string_t>& hierarchyIds) const
{
  for (auto& name : names) {
    if (Json::GetString(mesh, "name") == name) {
      hierarchyIds.emplace_back(Json::GetString(mesh, "id"));
      return true;
    }
  }
  if (mesh.contains("parentId")
      && stl_util::contains(hierarchyIds, Json::GetString(mesh, "parentId"))) {
    hierarchyIds.emplace_back(Json::GetString(mesh, "id"));
    return true;
  }
  return false;
}

string_t BabylonFileLoader::logOperation(const string_t& operation) const
{
  return operation + " of unknown";
}

string_t BabylonFileLoader::logOperation(const string_t& operation,
                                         const Json::value& producer) const
{
  return operation + " of " + Json::GetString(producer, "file") + " from "
         + Json::GetString(producer, "name") + " version: "
         + Json::GetString(producer, "version") + ", exporter version: "
         + Json::GetString(producer, "exporter_version");
}

bool BabylonFileLoader::importMesh(
  const vector_t<string_t>& meshesNames, Scene* scene, const string_t& data,
  const string_t& rootUrl, vector_t<AbstractMesh*>& meshes,
  vector_t<ParticleSystem*>& particleSystems, vector_t<Skeleton*>& skeletons,
  const ::std::function<void(const string_t& message,
                             const string_t& exception)>& /*onError*/) const
{
  Json::value parsedData;
  string_t err = Json::Parse(parsedData, data);
  if (!err.empty()) {
    string_t log = "importMesh has failed JSON parse";
    BABYLON_LOGF_ERROR("BabylonFileLoader", "%s", log.c_str());
    return false;
  }
  std::ostringstream log;

  bool fullDetails
    = SceneLoader::LoggingLevel() == SceneLoader::DETAILED_LOGGING();

  vector_t<string_t> loadedSkeletonsIds;
  vector_t<string_t> loadedMaterialsIds;
  vector_t<string_t> hierarchyIds;

  for (auto& parsedMesh : Json::GetArray(parsedData, "meshes")) {
    if (meshesNames.empty()
        || isDescendantOf(parsedMesh, meshesNames, hierarchyIds)) {

      // Id
      const string_t parsedMeshId = Json::GetString(parsedMesh, "id", "");

      // Geometry ?
      if (parsedMesh.contains("geometryId")) {
        const auto parsedMeshGeometryId
          = Json::GetString(parsedMesh, "geometryId");
        // Does the file contain geometries?
        if (parsedData.contains("geometries")) {
          auto& geometries = parsedData.get("geometries");
          // find the correct geometry and add it to the scene
          bool found = false;
          const array_t<string_t, 8> geometryTypes{
            {"boxes", "spheres", "cylinders", "toruses", "grounds", "planes",
             "torusKnots", "vertexData"}};
          for (const auto& geometryType : geometryTypes) {
            if (found || !geometries.contains(geometryType)
                || !(geometries.get(geometryType).is<Json::array>())) {
              break;
            }
            else {
              for (const auto& parsedGeometryData :
                   Json::GetArray(geometries, geometryType)) {
                const string_t parsedGeometryDataId
                  = Json::GetString(parsedGeometryData, "id");
                if (!parsedGeometryDataId.empty()
                    && (parsedGeometryDataId == parsedMeshGeometryId)) {
                  if (geometryType == "boxes") {
                    BoxGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "spheres") {
                    SphereGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "cylinders") {
                    CylinderGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "toruses") {
                    TorusGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "grounds") {
                    GroundGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "planes") {
                    PlaneGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "torusKnots") {
                    TorusKnotGeometry::Parse(parsedGeometryData, scene);
                  }
                  else if (geometryType == "vertexData") {
                    Geometry::Parse(parsedGeometryData, scene, rootUrl);
                  }
                  found = true;
                }
              }
            }
          }
          if (!found) {
            BABYLON_LOGF_WARN("BabylonFileLoader",
                              "Geometry not found for mesh %s",
                              parsedMeshId.c_str());
          }
        }
      }

      // Material ?
      if (parsedMesh.contains("materialId")) {
        const string_t parsedMeshMaterialId
          = Json::GetString(parsedMesh, "materialId");
        bool materialFound
          = stl_util::contains(loadedMaterialsIds, parsedMeshMaterialId);
        if (!parsedMeshMaterialId.empty() && !materialFound
            && parsedData.contains("multiMaterials")
            && parsedData.get("multiMaterials").is<Json::array>()) {
          for (const auto& parsedMultiMaterial :
               Json::GetArray(parsedData, "multiMaterials")) {
            const string_t parsedMultiMaterialId
              = Json::GetString(parsedMultiMaterial, "id", "");
            if ((!parsedMultiMaterialId.empty())
                && (parsedMultiMaterialId == parsedMeshMaterialId)) {
              if (parsedMultiMaterial.contains("materials")
                  && parsedMultiMaterial.get("materials").is<Json::array>()) {
                for (const auto& subMatId :
                     Json::GetArray(parsedMultiMaterial, "materials")) {
                  loadedMaterialsIds.emplace_back(subMatId.get<string_t>());
                  auto mat = parseMaterialById(subMatId.get<string_t>(),
                                               parsedData, scene, rootUrl);
                  log << "\n\tMaterial " << mat->toString(fullDetails);
                }
              }
              loadedMaterialsIds.emplace_back(parsedMultiMaterialId);
              auto mmat
                = Material::ParseMultiMaterial(parsedMultiMaterial, scene);
              materialFound = true;
              log << "\n\tMulti-Material " << mmat->toString(fullDetails);
              break;
            }
          }
        }

        if (!materialFound) {
          loadedMaterialsIds.emplace_back(parsedMeshMaterialId);
          auto mat = parseMaterialById(parsedMeshMaterialId, parsedData, scene,
                                       rootUrl);
          if (!mat) {
            BABYLON_LOGF_WARN("BabylonFileLoader",
                              "Material not found for mesh %s",
                              parsedMeshId.c_str());
          }
          else {
            log << "\n\tMaterial " << mat->toString(fullDetails);
          }
        }
      }

      // Skeleton ?
      if (parsedMesh.contains("skeletonId")) {
        const string_t parsedMeshSkeletonId
          = Json::GetString(parsedMesh, "skeletonId");
        bool skeletonAlreadyLoaded
          = stl_util::contains(loadedSkeletonsIds, parsedMeshSkeletonId);
        if (!parsedMeshSkeletonId.empty() && !skeletonAlreadyLoaded
            && parsedData.contains("skeletons")
            && parsedData.get("skeletons").is<Json::array>()) {
          for (const auto& parsedSkeleton :
               Json::GetArray(parsedData, "skeletons")) {
            const string_t parsedSkeletonId
              = Json::GetString(parsedSkeleton, "id", "");
            if ((!parsedSkeletonId.empty())
                && (parsedSkeletonId == parsedMeshSkeletonId)) {
              auto skeleton = Skeleton::Parse(parsedSkeleton, scene);
              skeletons.emplace_back(skeleton);
              loadedSkeletonsIds.emplace_back(parsedSkeletonId);
              log << "\n\tSkeleton " << skeleton->toString(fullDetails);
            }
          }
        }
      }

      // Morph targets ?
      if (parsedData.contains("morphTargetManagers")
          && parsedData.get("morphTargetManagers").is<Json::array>()) {
        for (const auto& managerData :
             Json::GetArray(parsedData, "morphTargetManagers")) {
          MorphTargetManager::Parse(managerData, scene);
        }
      }

      auto mesh = Mesh::Parse(parsedMesh, scene, rootUrl);
      meshes.emplace_back(mesh);
      log << "\n\tMesh " << mesh->toString(fullDetails);
    }
  }

  // Connecting parents
  for (auto& currentMesh : scene->meshes) {
    if (!currentMesh->_waitingParentId.empty()) {
      static_cast<Node*>(currentMesh.get())->parent
        = scene->getLastEntryByID(currentMesh->_waitingParentId);
      currentMesh->_waitingParentId = "";
    }
  }

  // freeze and compute world matrix application
  for (auto& currentMesh : scene->meshes) {
    if (currentMesh->_waitingFreezeWorldMatrix) {
      currentMesh->freezeWorldMatrix();
      currentMesh->_waitingFreezeWorldMatrix = false;
    }
    else {
      currentMesh->computeWorldMatrix(true);
    }
  }

  // Particles ?
  if (parsedData.contains("particleSystems")
      && parsedData.get("particleSystems").is<Json::array>()) {
    for (const auto& parsedParticleSystem :
         Json::GetArray(parsedData, "particleSystems")) {
      const string_t parsedParticleSystemEmitterId
        = Json::GetString(parsedParticleSystem, "emitterId");
      if (!parsedParticleSystemEmitterId.empty()
          && stl_util::contains(hierarchyIds, parsedParticleSystemEmitterId)) {
        particleSystems.emplace_back(
          ParticleSystem::Parse(parsedParticleSystem, scene, rootUrl));
      }
    }
  }

  const auto _log = log.str();
  if (!_log.empty()
      && SceneLoader::LoggingLevel() != SceneLoader::NO_LOGGING()) {
    string_t msg = parsedData.contains("producer") ?
                     logOperation("importMesh", parsedData.get("producer")) :
                     logOperation("importMesh");
    string_t logStr
      = SceneLoader::LoggingLevel() != SceneLoader::MINIMAL_LOGGING() ? _log :
                                                                        "";
    BABYLON_LOGF_INFO("BabylonFileLoader", "%s%s", msg.c_str(), logStr.c_str());
    return false;
  }

  return true;
} // namespace BABYLON

bool BabylonFileLoader::load(
  Scene* scene, const string_t& data, const string_t& rootUrl,
  const ::std::function<void(const string_t& message,
                             const string_t& exception)>& /*onError*/) const
{
  Json::value parsedData;
  string_t err = Json::Parse(parsedData, data.c_str());
  if (!err.empty()) {
    string_t log = "importScene has failed JSON parse";
    BABYLON_LOGF_ERROR("BabylonFileLoader", "%s", log.c_str());
    return false;
  }
  std::ostringstream log;
  bool fullDetails
    = SceneLoader::LoggingLevel() == SceneLoader::DETAILED_LOGGING();

  // Scene
  scene->useDelayedTextureLoading
    = Json::GetBool(parsedData, "useDelayedTextureLoading")
      && !SceneLoader::ForceFullSceneLoadingForIncremental();
  scene->autoClear = Json::GetBool(parsedData, "autoClear", true);
  scene->clearColor
    = Color4::FromArray(Json::ToArray<float>(parsedData, "clearColor"));
  scene->ambientColor
    = Color3::FromArray(Json::ToArray<float>(parsedData, "ambientColor"));
  if (parsedData.contains("gravity")) {
    scene->gravity
      = Vector3::FromArray(Json::ToArray<float>(parsedData, "gravity"));
  }

  // Fog
  auto fogMode = Json::GetNumber(parsedData, "fogMode", Scene::FOGMODE_NONE());
  if (fogMode != Scene::FOGMODE_NONE()) {
    scene->setFogMode(fogMode);
    scene->fogColor
      = Color3::FromArray(Json::ToArray<float>(parsedData, "fogColor"));
    scene->fogStart   = Json::GetNumber(parsedData, "fogStart", 0.f);
    scene->fogEnd     = Json::GetNumber(parsedData, "fogEnd", 1000.f);
    scene->fogDensity = Json::GetNumber(parsedData, "fogDensity", 0.1f);
    log << "\tFog mode for scene:  ";
    switch (fogMode) {
      case Scene::FOGMODE_EXP():
        log << "exp\n";
        break;
      case Scene::FOGMODE_EXP2():
        log << "exp2\n";
        break;
      case Scene::FOGMODE_LINEAR():
        log << "linear\n";
        break;
      default:
        log << "unknown\n";
    }
  }

  // Physics
  if (Json::GetBool(parsedData, "physicsEnabled")) {
  }

  // Metadata
  // if (parsedData.metadata !== undefined) {
  //    scene.metadata = parsedData.metadata;
  // }

  // Collisions, if defined. otherwise, default is true
  scene->collisionsEnabled = Json::GetBool(parsedData, "physicsEnabled", true);
  scene->setWorkerCollisions(Json::GetBool(parsedData, "workerCollisions"));

  // Lights
  unsigned int index = 0;
  for (const auto& parsedLight : Json::GetArray(parsedData, "lights")) {
    auto light = Light::Parse(parsedLight, scene);
    log << (index == 0 ? "\n\tLights:" : "");
    log << "\n\t\t" << light->toString(fullDetails);
    ++index;
  }

  // Animations
  index = 0;
  for (const auto& parsedAnimation : Json::GetArray(parsedData, "animations")) {
    auto animation = Animation::Parse(parsedAnimation);
    scene->animations.emplace_back(animation);
    log << (index == 0 ? "\n\tAnimations:" : "");
    log << "\n\t\t" << animation->toString(fullDetails);
    ++index;
  }

  if (Json::GetBool(parsedData, "autoAnimate", false)) {
    scene->beginAnimation(scene,
                          Json::GetNumber(parsedData, "autoAnimateFrom", 0),
                          Json::GetNumber(parsedData, "autoAnimateTo", 0),
                          Json::GetBool(parsedData, "autoAnimateLoop"),
                          Json::GetNumber(parsedData, "autoAnimateFrom", 1.f));
  }

  // Materials
  index = 0;
  for (const auto& parsedMaterial : Json::GetArray(parsedData, "materials")) {
    auto mat = Material::Parse(parsedMaterial, scene, rootUrl);
    log << (index == 0 ? "\n\tMaterials:" : "");
    log << "\n\t\t" << mat->toString(fullDetails);
    ++index;
  }

  // Multi materials
  index = 0;
  for (const auto& parsedMultiMaterial :
       Json::GetArray(parsedData, "multiMaterials")) {
    auto mmat = Material::ParseMultiMaterial(parsedMultiMaterial, scene);
    log << (index == 0 ? "\n\tMultiMaterials:" : "");
    log << "\n\t\t" << mmat->toString(fullDetails);
    ++index;
  }

  // Skeletons
  index = 0;
  for (const auto& parsedSkeleton : Json::GetArray(parsedData, "skeletons")) {
    auto skeleton = Skeleton::Parse(parsedSkeleton, scene);
    log << (index == 0 ? "\n\tSkeletons:" : "");
    log << "\n\t\t" << skeleton->toString(fullDetails);
    ++index;
  }

  if (parsedData.contains("geometries")) {
    const auto& geometries = parsedData.get("geometries");

    // Boxes
    for (const auto& parsedBox : Json::GetArray(geometries, "boxes")) {
      BoxGeometry::Parse(parsedBox, scene);
    }

    // Spheres
    for (const auto& parsedSphere : Json::GetArray(geometries, "spheres")) {
      SphereGeometry::Parse(parsedSphere, scene);
    }

    // Cylinders
    for (const auto& parsedCylinder : Json::GetArray(geometries, "cylinders")) {
      CylinderGeometry::Parse(parsedCylinder, scene);
    }

    // Toruses
    for (const auto& parsedTorus : Json::GetArray(geometries, "toruses")) {
      TorusGeometry::Parse(parsedTorus, scene);
    }

    // Grounds
    for (const auto& parsedGround : Json::GetArray(geometries, "grounds")) {
      GroundGeometry::Parse(parsedGround, scene);
    }

    // Planes
    for (const auto& parsedPlane : Json::GetArray(geometries, "planes")) {
      PlaneGeometry::Parse(parsedPlane, scene);
    }

    // TorusKnots
    for (const auto& parsedTorusKnot :
         Json::GetArray(geometries, "torusKnots")) {
      TorusKnotGeometry::Parse(parsedTorusKnot, scene);
    }

    // VertexData
    for (const auto& parsedVertexData :
         Json::GetArray(geometries, "vertexData")) {
      Geometry::Parse(parsedVertexData, scene, rootUrl);
    }
  }

  // Meshes
  index = 0;
  for (const auto& parsedMesh : Json::GetArray(parsedData, "meshes")) {
    auto mesh = Mesh::Parse(parsedMesh, scene, rootUrl);
    log << (index == 0 ? "\n\tMeshes:" : "");
    log << "\n\t\t" << mesh->toString(fullDetails);
    ++index;
  }

  // Cameras
  index = 0;
  for (const auto& parsedCamera : Json::GetArray(parsedData, "cameras")) {
    auto camera = Camera::Parse(parsedCamera, scene);
    log << (index == 0 ? "\n\tCameras:" : "");
    log << "\n\t\t" << camera->toString(fullDetails);
    ++index;
  }
  if (parsedData.contains("activeCameraID")) {
    scene->setActiveCameraByID(Json::GetString(parsedData, "activeCameraID"));
  }

  // Browsing all the graph to connect the dots
  for (auto& camera : scene->cameras) {
    if (!camera->_waitingParentId.empty()) {
      camera->parent = scene->getLastEntryByID(camera->_waitingParentId);
      camera->_waitingParentId.clear();
    }
  }

  for (auto& light : scene->lights) {
    if (!light->_waitingParentId.empty()) {
      light->parent = scene->getLastEntryByID(light->_waitingParentId);
      light->_waitingParentId.clear();
    }
  }

  // Sounds

  // Connect parents & children and parse actions
  for (auto& mesh : scene->meshes) {
    if (!mesh->_waitingParentId.empty()) {
      static_cast<Node*>(mesh.get())->parent
        = scene->getLastEntryByID(mesh->_waitingParentId);
      mesh->_waitingParentId.clear();
    }
    if (!mesh->_waitingActions.empty()) {
      ActionManager::Parse(mesh->_waitingActions, mesh.get(), scene);
      mesh->_waitingActions.clear();
    }
  }

  // Freeze world matrix application
  for (auto& currentMesh : scene->meshes) {
    if (currentMesh->_waitingFreezeWorldMatrix) {
      currentMesh->freezeWorldMatrix();
      currentMesh->_waitingFreezeWorldMatrix = false;
    }
    else {
      currentMesh->computeWorldMatrix(true);
    }
  }

  // Particles Systems
  for (const auto& parsedParticleSystem :
       Json::GetArray(parsedData, "particleSystems")) {
    ParticleSystem::Parse(parsedParticleSystem, scene, rootUrl);
  }

  // Lens flares
  for (const auto& parsedLensFlareSystem :
       Json::GetArray(parsedData, "lensFlareSystems")) {
    LensFlareSystem::Parse(parsedLensFlareSystem, scene, rootUrl);
  }

  // Shadows
  for (const auto& parsedShadowGenerator :
       Json::GetArray(parsedData, "shadowGenerators")) {
    ShadowGenerator::Parse(parsedShadowGenerator, scene);
  }

  // Actions (scene)
  if (parsedData.contains("actions")
      && (parsedData.get("actions").is<Json::array>())) {
    ActionManager::Parse(parsedData.get("actions").get<Json::array>(), nullptr,
                         scene);
  }

  const auto _log = log.str();
  if (!_log.empty()
      && SceneLoader::LoggingLevel() != SceneLoader::NO_LOGGING()) {
    string_t msg = parsedData.contains("producer") ?
                     logOperation("importScene", parsedData.get("producer")) :
                     logOperation("importScene");
    string_t logStr
      = SceneLoader::LoggingLevel() != SceneLoader::MINIMAL_LOGGING() ? _log :
                                                                        "";
    BABYLON_LOGF_INFO("BabylonFileLoader", "%s%s", msg.c_str(), logStr.c_str());
  }

  // Finish
  return true;
}

} // end of namespace BABYLON
