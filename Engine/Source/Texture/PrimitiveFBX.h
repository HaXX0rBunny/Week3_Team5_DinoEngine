#pragma once
#include "CoreMinimal.h"
#include "EngineAPI.h"
#include "Primitive/PrimitiveBase.h"
struct FLoadedMesh
{
	FMeshData* MeshData;
	FString MaterialName;
	FString DiffuseTexturePath;
};

class ENGINE_API CPrimitiveFBX : public CPrimitiveBase
{
public:
	bool LoadFromFile(ID3D11Device* Device, const FString& FilePath);
	const TArray<FLoadedMesh>& GetLoadedMeshes() const { return LoadedMeshes; }

private:
	TArray<FLoadedMesh> LoadedMeshes;
};
