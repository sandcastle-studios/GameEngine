#include "stdafx.h"
#include "CubeModel.h"
#include "VertexPosColUV.h"
#include "Mesh.h"

CubeModel::CubeModel(const std::shared_ptr<Effect> & aEffect, const std::shared_ptr<Texture> & aTexture)
	: Model(aEffect)
{
	std::array<VertexPosColUV, 8> verticies;
	std::array<unsigned int, 36> indicies;

	verticies[0].position.x = -0.5f;
	verticies[0].position.y = 0.5f;
	verticies[0].position.z = -0.5f;
	verticies[0].position.w = 1.0f;

	verticies[0].color.x = 1.0f;
	verticies[0].color.y = 1.0f;
	verticies[0].color.z = 1.0f;
	verticies[0].color.w = 1.0f;

	verticies[0].uv.x = 0.0f;
	verticies[0].uv.y = 0.0f;


	verticies[1].position.x = -0.5f;
	verticies[1].position.y = 0.5f;
	verticies[1].position.z = 0.5f;
	verticies[1].position.w = 1.0f;

	verticies[1].color.x = 1.0f;
	verticies[1].color.y = 1.0f;
	verticies[1].color.z = 1.0f;
	verticies[1].color.w = 1.0f;

	verticies[1].uv.x = 1.0f;
	verticies[1].uv.y = 0.0f;


	verticies[2].position.x = 0.5f;
	verticies[2].position.y = 0.5f;
	verticies[2].position.z = 0.5f;
	verticies[2].position.w = 1.0f;

	verticies[2].color.x = 1.0f;
	verticies[2].color.y = 1.0f;
	verticies[2].color.z = 1.0f;
	verticies[2].color.w = 1.0f;

	verticies[2].uv.x = 0.0f;
	verticies[2].uv.y = 0.0f;


	verticies[3].position.x = 0.5f;
	verticies[3].position.y = 0.5f;
	verticies[3].position.z = -0.5f;
	verticies[3].position.w = 1.0f;

	verticies[3].color.x = 1.0f;
	verticies[3].color.y = 1.0f;
	verticies[3].color.z = 1.0f;
	verticies[3].color.w = 1.0f;

	verticies[3].uv.x = 1.0f;
	verticies[3].uv.y = 0.0f;

	// BOT
	verticies[4].position.x = -0.5f;
	verticies[4].position.y = -0.5f;
	verticies[4].position.z = -0.5f;
	verticies[4].position.w = 1.0f;

	verticies[4].color.x = 1.0f;
	verticies[4].color.y = 1.0f;
	verticies[4].color.z = 1.0f;
	verticies[4].color.w = 1.0f;

	verticies[4].uv.x = 0.0f;
	verticies[4].uv.y = 1.0f;


	verticies[5].position.x = -0.5f;
	verticies[5].position.y = -0.5f;
	verticies[5].position.z = 0.5f;
	verticies[5].position.w = 1.0f;

	verticies[5].color.x = 1.0f;
	verticies[5].color.y = 1.0f;
	verticies[5].color.z = 1.0f;
	verticies[5].color.w = 1.0f;

	verticies[5].uv.x = 1.0f;
	verticies[5].uv.y = 1.0f;


	verticies[6].position.x = 0.5f;
	verticies[6].position.y = -0.5f;
	verticies[6].position.z = 0.5f;
	verticies[6].position.w = 1.0f;

	verticies[6].color.x = 1.0f;
	verticies[6].color.y = 1.0f;
	verticies[6].color.z = 1.0f;
	verticies[6].color.w = 1.0f;

	verticies[6].uv.x = 0.0f;
	verticies[6].uv.y = 1.0f;


	verticies[7].position.x = 0.5f;
	verticies[7].position.y = -0.5f;
	verticies[7].position.z = -0.5f;
	verticies[7].position.w = 1.0f;

	verticies[7].color.x = 1.0f;
	verticies[7].color.y = 1.0f;
	verticies[7].color.z = 1.0f;
	verticies[7].color.w = 1.0f;

	verticies[7].uv.x = 1.0f;
	verticies[7].uv.y = 1.0f;
	

	indicies[0] = 0;
	indicies[1] = 1;
	indicies[2] = 2;
	indicies[3] = 0;
	indicies[4] = 2;
	indicies[5] = 3;

	indicies[6] = 4;
	indicies[7] = 6;
	indicies[8] = 5;
	indicies[9] = 4;
	indicies[10] = 7;
	indicies[11] = 6;

	indicies[12] = 4;
	indicies[13] = 5;
	indicies[14] = 1;
	indicies[15] = 4;
	indicies[16] = 1;
	indicies[17] = 0;

	indicies[18] = 6;
	indicies[19] = 7;
	indicies[20] = 3;
	indicies[21] = 6;
	indicies[22] = 3;
	indicies[23] = 2;

	indicies[24] = 4;
	indicies[25] = 0;
	indicies[26] = 3;
	indicies[27] = 4;
	indicies[28] = 3;
	indicies[29] = 7;

	indicies[30] = 6;
	indicies[31] = 2;
	indicies[32] = 1;
	indicies[33] = 6;
	indicies[34] = 1;
	indicies[35] = 5;

	AddMesh(std::make_shared<Mesh<VertexPosColUV>>(aTexture, verticies, indicies));
}

CubeModel::~CubeModel()
{
}
