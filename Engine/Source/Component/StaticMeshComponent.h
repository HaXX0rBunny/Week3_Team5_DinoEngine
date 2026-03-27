#pragma once
#include"MeshComponent.h"

class ENGINE_API UStaticMeshComp : public UMeshComponent
{
public:
	DECLARE_RTTI(UStaticMeshComp, UMeshComponent)

	void Initialize();

	void LoadStaticMesh(ID3D11Device* Device, const FString& FilePath);
	FString GetStaticMeshAsset() const;

private:
	void LoadTexture(ID3D11Device* Device, const FString& FilePath);
	std::unique_ptr<FMaterial> DynamicMaterialOwner;
};