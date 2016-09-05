#include "CubeShape.h"


float CubeShape::Positions[] = {
	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,0.5f,-0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,-0.5f,0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,

	0.5f,0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f,
	0.5f,0.5f,0.5f,

	-0.5f,0.5f,-0.5f,
	-0.5f,-0.5f,-0.5f,
	-0.5f,-0.5f,0.5f,
	-0.5f,0.5f,0.5f,

	-0.5f,0.5f,0.5f,
	-0.5f,0.5f,-0.5f,
	0.5f,0.5f,-0.5f,
	0.5f,0.5f,0.5f,

	-0.5f,-0.5f,0.5f,
	-0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,-0.5f,
	0.5f,-0.5f,0.5f
};

int CubeShape::Indices[]{
	1,0,3,
	1,3,2,
	4,5,7,
	5,6,7,
	9,8,11,
	10,9,11,
	12,13,15,
	15,13,14,
	16,19,17,
	17,19,18,
	22,20,21,
	22,23,20
};

float CubeShape::TexCoords[]
{
	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 1.0f,
	1.0f, 0.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,

	0.0f, 0.0f,
	0.0f, 1.0f,
	1.0f, 0.0f,
	1.0f, 1.0f,
};

float CubeShape::Normals[]
{
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,
	0.0f,0.0f,-1.0f,

	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,
	0.0f,0.0f,1.0f,

	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,

	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,

	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,
	0.0f,1.0f,0.0f,

	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
	0.0f,-1.0f,0.0f,
};

int CubeShape::GetPositionLength()
{
	return sizeof(CubeShape::Positions)/ sizeof(*CubeShape::Positions);
}

int CubeShape::GetIndexLength()
{
	return sizeof(CubeShape::Indices) / sizeof(*CubeShape::Indices);
}

int CubeShape::GetTexCoordLength()
{
	return sizeof(CubeShape::TexCoords) / sizeof(*CubeShape::TexCoords);
}

int CubeShape::GetNormalLength()
{
	return sizeof(CubeShape::Normals) / sizeof(*CubeShape::Normals);
}
