#include "PrimitiveFBX.h"
#include <ThirdParty/assimp/Importer.hpp>
#include <ThirdParty/assimp/scene.h>
#include <ThirdParty/assimp/postprocess.h>

bool CPrimitiveFBX::LoadFromFile(ID3D11Device* Device, const FString& FilePath)
{
	Assimp::Importer Importer;
	const aiScene* AiScene = Importer.ReadFile(FilePath,
		aiProcess_Triangulate |
		aiProcess_FlipUVs |
		aiProcess_GenNormals |
		aiProcess_CalcTangentSpace);

	if (!AiScene || !AiScene->mRootNode)
		return false;

	for (uint32 i = 0; i < AiScene->mNumMeshes; i++)
	{
		aiMesh* AiMesh = AiScene->mMeshes[i];

		FMeshData* MeshData = new FMeshData();
		MeshData->Topology = EMeshTopology::EMT_TriangleList;

		// 버텍스
		for (uint32 v = 0; v < AiMesh->mNumVertices; v++)
		{
			FPrimitiveVertex Vertex;
			Vertex.Position = { AiMesh->mVertices[v].x, AiMesh->mVertices[v].y, AiMesh->mVertices[v].z };
			Vertex.Color = { 1, 1, 1, 1 };

			if (AiMesh->HasNormals())
				Vertex.Normal = { AiMesh->mNormals[v].x, AiMesh->mNormals[v].y, AiMesh->mNormals[v].z };

			if (AiMesh->HasTextureCoords(0))
				Vertex.UV = { AiMesh->mTextureCoords[0][v].x, AiMesh->mTextureCoords[0][v].y };
			else
				Vertex.UV = { 0, 0 };

			MeshData->Vertices.push_back(Vertex);
		}

		// 인덱스
		for (uint32 f = 0; f < AiMesh->mNumFaces; f++)
		{
			aiFace& Face = AiMesh->mFaces[f];
			for (uint32 idx = 0; idx < Face.mNumIndices; idx++)
				MeshData->Indices.push_back(Face.mIndices[idx]);
		}

		// GPU 버퍼 생성
		MeshData->CreateVertexAndIndexBuffer(Device);

		// 텍스처 경로 추출
		FLoadedMesh Loaded;
		Loaded.MeshData = MeshData;
		if (AiMesh->mMaterialIndex < AiScene->mNumMaterials)
		{
			aiMaterial* AiMat = AiScene->mMaterials[AiMesh->mMaterialIndex];
			aiString TexPath;
			if (AiMat->GetTexture(aiTextureType_DIFFUSE, 0, &TexPath) == AI_SUCCESS)
				Loaded.DiffuseTexturePath = TexPath.C_Str();
		}
		LoadedMeshes.push_back(Loaded);
	}
	return true;
}
