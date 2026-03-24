#pragma once
#include "CoreMinimal.h"
#include "EngineAPI.h"
#include <d3d11.h>
#include <unordered_map>

class ENGINE_API FTextureManager
{
public:
    static FTextureManager& Get();

    // 텍스처 로드 (캐싱)
    ID3D11ShaderResourceView* LoadTexture(ID3D11Device* Device, const FString& FilePath);
    ID3D11SamplerState* GetDefaultSampler(ID3D11Device* Device);
    void ReleaseAll();

private:
    std::unordered_map<FString, ID3D11ShaderResourceView*> TextureCache;
    ID3D11SamplerState* DefaultSampler = nullptr;
};
