#pragma once
#include "SceneComponent.h"
#include "Mesh/Mesh.h"
#include "Math/Frustum.h"
#include <memory>
class FMaterial;
struct ID3D11Device;

struct FBoxSphereBounds;
class ENGINE_API UMeshComponent : public USceneComponent
{
public:
	DECLARE_RTTI(UMeshComponent, USceneComponent)
};