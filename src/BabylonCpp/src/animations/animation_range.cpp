#include <babylon/animations/animation_range.h>

namespace BABYLON {

AnimationRange::AnimationRange() : name{""}, from{0.f}, to{0.f}
{
}

AnimationRange::AnimationRange(const std::string& iName, float iFrom, float iTo)
    : name{iName}, from{iFrom}, to{iTo}
{
}

AnimationRange::AnimationRange(const AnimationRange& other)
    : name{other.name}, from{other.from}, to{other.to}
{
}

AnimationRange::~AnimationRange()
{
}

AnimationRange AnimationRange::copy() const
{
  return AnimationRange(name, from, to);
}

std::unique_ptr<AnimationRange> AnimationRange::clone() const
{
  return ::std::make_unique<AnimationRange>(name, from, to);
}

} // end of namespace BABYLON
