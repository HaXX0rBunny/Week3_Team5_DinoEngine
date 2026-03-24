#include "TextureManager.h"
#include <WICTextureLoader.h>
#include "ThirdParty/stb_image.h"

FTextureManager& FTextureManager::Get()
{
	static FTextureManager Instance;
	return Instance;
}

ID3D11ShaderResourceView* FTextureManager::LoadTexture(ID3D11Device* Device, const FString& FilePath)
{
	auto It = TextureCache.find(FilePath);
	if (It != TextureCache.end())
		return It->second;

	ID3D11ShaderResourceView* SRV = nullptr;
	ID3D11Resource* Resource = nullptr;

	// WIC로 시도 (png, jpg, bmp)
	std::wstring WidePath(FilePath.begin(), FilePath.end());
	HRESULT Hr = DirectX::CreateWICTextureFromFile(Device, WidePath.c_str(), &Resource, &SRV);

	if (FAILED(Hr))
		return nullptr;

	if (Resource) Resource->Release();
	TextureCache[FilePath] = SRV;
	return SRV;
}

ID3D11SamplerState* FTextureManager::GetDefaultSampler(ID3D11Device* Device)
{
	if (!DefaultSampler)
	{
		D3D11_SAMPLER_DESC Desc = {};
		Desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
		Desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		Desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		Device->CreateSamplerState(&Desc, &DefaultSampler);
	}
	return DefaultSampler;
}

void FTextureManager::ReleaseAll()
{
	for (auto& [Key, SRV] : TextureCache)
	{
		if (SRV) SRV->Release();
	}
	TextureCache.clear();
	if (DefaultSampler) { DefaultSampler->Release(); DefaultSampler = nullptr; }
}
