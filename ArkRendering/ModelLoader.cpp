#include "ModelLoader.h"

bool ModelLoading::loadOBJ(ArkString path, std::vector<Vec3>& outVertices, std::vector<Vec2>& outUVs, std::vector<Vec3>& outNormals)
{
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;

	std::vector<Vec3> tempVertices, tempNormals;
	std::vector<Vec2> tempUVs;

	FILE * file;

	fopen_s(&file, path.c_str(), "r");

	if ( !file )
	{
		printf("Impossible to open the file! \n");
		return false;
	}

	while ( 1 )
	{
		char lineHeader[128];	// silly assumption that a header is always < 128 chars

		int res = fscanf_s(file, "%s", lineHeader, 128);
		if ( res == EOF )
			break;

		if ( strcmp(lineHeader, "v") == 0 )
		{
			Vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			tempVertices.push_back(vertex);
		}
		else if ( strcmp(lineHeader, "vt") == 0 )
		{
			Vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			tempUVs.push_back(uv);
		}
		else if ( strcmp(lineHeader, "vn") == 0 )
		{
			Vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			tempNormals.push_back(normal);
		}
		else if ( strcmp(lineHeader, "f") == 0 )
		{
			ArkString vertex1, vertex2, vertex3;

			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&vertexIndex[0], &uvIndex[0], &normalIndex[0],
				&vertexIndex[1], &uvIndex[1], &normalIndex[1],
				&vertexIndex[2], &uvIndex[2], &normalIndex[2]);

			if ( matches != 9 )
			{
				printf("File cannot be read by the simple parser. Try exporting with other options");
				return false;
			}

			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);

			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);

			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for ( unsigned int i = 0 ; i < vertexIndices.size() ; i++ )
	{
		unsigned int ind = vertexIndices[i];
		Vec3 vertex = tempVertices[ind - 1];
		outVertices.push_back(vertex);

		ind = uvIndices[i];
		Vec2 uv = tempUVs[ind - 1];
		outUVs.push_back(uv);

		ind = normalIndices[i];
		Vec3 normal = tempNormals[ind - 1];
		outNormals.push_back(normal);
	}

	return true;
}
