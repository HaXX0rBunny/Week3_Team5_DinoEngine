#pragma once
#include "Mesh.h"

class ENGINE_API FStaticMesh : public FMesh
{
public:
	FStaticMesh() = default;
	void SetMeshData(const std::shared_ptr<FMeshData>& InData) { MeshData = InData; }

};