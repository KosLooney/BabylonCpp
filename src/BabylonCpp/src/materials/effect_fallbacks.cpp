#include <babylon/materials/effect_fallbacks.h>

#include <babylon/core/logging.h>
#include <babylon/core/string.h>
#include <babylon/engine/scene.h>
#include <babylon/mesh/abstract_mesh.h>
#include <babylon/tools/tools.h>

namespace BABYLON {

EffectFallbacks::EffectFallbacks() : _currentRank{32}, _maxRank{0}
{
}

EffectFallbacks::EffectFallbacks(const EffectFallbacks& other)
    : _defines{other._defines}
    , _currentRank{other._currentRank}
    , _maxRank{other._maxRank}
    , _mesh{other._mesh}
    , _meshRank{other._meshRank}
{
}

EffectFallbacks::EffectFallbacks(EffectFallbacks&& other)
    : _defines{::std::move(other._defines)}
    , _currentRank{::std::move(other._currentRank)}
    , _maxRank{::std::move(other._maxRank)}
    , _mesh{::std::move(other._mesh)}
    , _meshRank{::std::move(other._meshRank)}
{
}

EffectFallbacks& EffectFallbacks::operator=(const EffectFallbacks& other)
{
  if (&other != this) {
    _defines     = other._defines;
    _currentRank = other._currentRank;
    _maxRank     = other._maxRank;
    _mesh        = other._mesh;
    _meshRank    = other._meshRank;
  }

  return *this;
}

EffectFallbacks& EffectFallbacks::operator=(EffectFallbacks&& other)
{
  if (&other != this) {
    _defines     = ::std::move(other._defines);
    _currentRank = ::std::move(other._currentRank);
    _maxRank     = ::std::move(other._maxRank);
    _mesh        = ::std::move(other._mesh);
    _meshRank    = ::std::move(other._meshRank);
  }

  return *this;
}

EffectFallbacks::~EffectFallbacks()
{
}

bool EffectFallbacks::operator==(const EffectFallbacks& other) const
{
  return (_defines == other._defines) && (_currentRank == other._currentRank)
         && (_maxRank == other._maxRank) && (_mesh == other._mesh)
         && (_meshRank == other._meshRank);
}

bool EffectFallbacks::operator!=(const EffectFallbacks& other) const
{
  return !(operator==(other));
}

void EffectFallbacks::addFallback(unsigned int rank, const std::string& define)
{
  if (_defines.find(rank) == _defines.end()) {
    if (rank < _currentRank) {
      _currentRank = rank;
    }

    if (rank > _maxRank) {
      _maxRank = rank;
    }
  }

  _defines[rank].emplace_back(define);
}

void EffectFallbacks::addCPUSkinningFallback(unsigned int rank,
                                             AbstractMesh* mesh)
{
  _meshRank = rank;
  _mesh     = mesh;

  if (rank < _currentRank) {
    _currentRank = rank;
  }
  if (rank > _maxRank) {
    _maxRank = rank;
  }
}

bool EffectFallbacks::isMoreFallbacks() const
{
  return _currentRank <= _maxRank;
}

std::string EffectFallbacks::reduce(const std::string& currentDefines)
{
  // First we try to switch to CPU skinning
  std::string currentDefinesCpy(currentDefines);
  if (_mesh && _mesh->computeBonesUsingShaders()
      && _mesh->numBoneInfluencers() > 0) {
    _mesh->setComputeBonesUsingShaders(false);
    const std::string toReplace
      = std::string("#define NUM_BONE_INFLUENCERS ")
        + ::std::to_string(_mesh->numBoneInfluencers());
    String::replaceInPlace(currentDefinesCpy, toReplace,
                           "#define NUM_BONE_INFLUENCERS 0");
    BABYLON_LOGF_DEBUG("EffectFallbacks", "Falling back to CPU skinning for %s",
                       _mesh->name.c_str());

    auto scene = _mesh->getScene();
    for (auto& otherMesh : scene->meshes) {
      if (otherMesh->material() == _mesh->material()
          && otherMesh->computeBonesUsingShaders()
          && otherMesh->numBoneInfluencers() > 0) {
        otherMesh->setComputeBonesUsingShaders(false);
      }
    }
  }
  else {
    if (_defines.find(_currentRank) != _defines.end()
        && !_defines[_currentRank].empty()) {
      for (auto& currentFallback : _defines[_currentRank]) {
        String::replaceInPlace(currentDefinesCpy, "#define " + currentFallback,
                               "");
      }
    }
    ++_currentRank;
  }

  return currentDefinesCpy;
}

} // end of namespace BABYLON
