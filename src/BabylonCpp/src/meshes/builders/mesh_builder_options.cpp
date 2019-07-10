#include <babylon/meshes/builders/mesh_builder_options.h>

namespace BABYLON {

//------------------------------------------------------------------------------
// Box mesh options
//------------------------------------------------------------------------------

BoxOptions::BoxOptions()
    : size{std::nullopt}
    , width{std::nullopt}
    , height{std::nullopt}
    , depth{std::nullopt}
    , faceUV{{Vector4(0.f, 0.f, 1.f, 1.f), Vector4(0.f, 0.f, 1.f, 1.f),
              Vector4(0.f, 0.f, 1.f, 1.f), Vector4(0.f, 0.f, 1.f, 1.f),
              Vector4(0.f, 0.f, 1.f, 1.f), Vector4(0.f, 0.f, 1.f, 1.f)}}
    , faceColors{{Color4(1.f, 1.f, 1.f, 1.f), Color4(1.f, 1.f, 1.f, 1.f),
                  Color4(1.f, 1.f, 1.f, 1.f), Color4(1.f, 1.f, 1.f, 1.f),
                  Color4(1.f, 1.f, 1.f, 1.f), Color4(1.f, 1.f, 1.f, 1.f)}}
    , sideOrientation{std::nullopt}
    , frontUVs{std::nullopt}
    , backUVs{std::nullopt}
    , wrap{std::nullopt}
    , topBaseAt{std::nullopt}
    , bottomBaseAt{std::nullopt}
    , updatable{std::nullopt}
{
}

BoxOptions::~BoxOptions()
{
}

//------------------------------------------------------------------------------
// Cylinder or cone mesh options
//------------------------------------------------------------------------------

CylinderOptions::CylinderOptions()
    : height{std::nullopt}
    , diameterTop{std::nullopt}
    , diameterBottom{std::nullopt}
    , diameter{std::nullopt}
    , tessellation{std::nullopt}
    , subdivisions{std::nullopt}
    , arc{std::nullopt}
    , faceColors{Color4(1.f, 1.f, 1.f, 1.f), Color4(1.f, 1.f, 1.f, 1.f),
                 Color4(1.f, 1.f, 1.f, 1.f)}
    , faceUV{Vector4(0.f, 0.f, 1.f, 1.f), Vector4(0.f, 0.f, 1.f, 1.f),
             Vector4(0.f, 0.f, 1.f, 1.f)}
    , updatable{std::nullopt}
    , hasRings{std::nullopt}
    , enclose{std::nullopt}
    , sideOrientation{std::nullopt}
    , frontUVs{std::nullopt}
    , backUVs{std::nullopt}
{
}

CylinderOptions::~CylinderOptions()
{
}

//------------------------------------------------------------------------------
// Decal mesh options
//------------------------------------------------------------------------------

DecalOptions::DecalOptions()
    : position{std::nullopt}
    , normal{std::nullopt}
    , size{std::nullopt}
    , angle{std::nullopt}
{
}

DecalOptions::~DecalOptions()
{
}

//------------------------------------------------------------------------------
// Disc mesh options
//------------------------------------------------------------------------------

DiscOptions::DiscOptions()
    : radius{std::nullopt}
    , tessellation{std::nullopt}
    , arc{std::nullopt}
    , updatable{std::nullopt}
    , sideOrientation{std::nullopt}
    , frontUVs{std::nullopt}
    , backUVs{std::nullopt}
{
}

DiscOptions::~DiscOptions()
{
}

} // end of namespace BABYLON