#include "GTerrian.h"
#include "RenderEngine\DXUtils.h"



GTerrian::GTerrian()
	:m_fWidth(0), m_fDepth(0), m_fHeight(0), m_wCount(0), m_dCount(0)
{
	getTextureList().resize(TERRIAN_TEXSIZE, nullptr);
}

GTerrian* GTerrian::create(float width, float depth, size_t wCount, size_t dCount, float height)
{
	GTerrian* ret = new GTerrian();
	if (ret && ret->Init(width, depth, wCount, dCount, height))
	{
		ret->autorelease();
		return ret;
	}
	delete ret;
	return nullptr;
}

bool GTerrian::Init(
	float width, float depth, 
	size_t wCount, size_t dCount,
	float height)
{
	m_fWidth = width;
	m_fHeight = height;
	m_fDepth = depth;
	m_wCount = wCount;
	m_dCount = dCount;


	float uWidth = width / wCount;
	float uDepth = depth / dCount;
	ID3DXMesh* mesh = nullptr;
	D3DXCreateMeshFVF(
		wCount * dCount * 2,
		(wCount + 1) * (dCount + 1),
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		Vertex_p3_n3_c1_t3::fvf,
		dxGetDevice(),
		&mesh
		);
	setMesh(mesh);
	setNumAttribute(1);
	Vertex_p3_n3_c1_t3* vertexes = nullptr;
	DWORD*				indexes = nullptr;
	MESH_LOCK(vertexes, indexes, mesh);

	//顶点初始化
	{
		size_t array_index = 0;
		for (size_t dIndex = 0; dIndex < dCount + 1; ++dIndex)
		{
			float zz = dIndex * uDepth;
			for (size_t wIndex = 0; wIndex < wCount + 1; ++wIndex)
			{
				float xx = wIndex * uWidth;
				*vertexes[array_index].getPosition() = D3DXVECTOR3(xx, height, zz);
				vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
				vertexes[array_index++].setUV(
					(float)wIndex / wCount,
					1.0f - (float)dIndex / dCount
					);
			}
		}
	}

	//索引初始化
	{
		size_t array_index = 0;
		for (size_t dIndex = 0; dIndex < dCount; ++dIndex)
		{
			for (size_t wIndex = 0; wIndex < wCount; ++wIndex)
			{
				size_t bottom_left = dIndex * (wCount + 1) + wIndex;
				size_t bottom_right = bottom_left + 1;
				size_t top_left = bottom_left + wCount + 1;
				size_t top_right = top_left + 1;

				indexes[array_index++] = bottom_left;
				indexes[array_index++] = top_left;
				indexes[array_index++] = bottom_right;

				indexes[array_index++] = bottom_right;
				indexes[array_index++] = top_left;
				indexes[array_index++] = top_right;
			}
		}
	}

	MESH_UNLOCK(mesh);
	
	D3DXComputeNormals(mesh, nullptr);
	
	return true;
}

void GTerrian::Draw()
{
	//安装矩阵
	getAttachNode()->SetupFinalMatrix();
	//设置纹理 并 绘制网格
	for (size_t i = 0; i < TERRIAN_TEXSIZE; ++i)
		dxSetTexture(i, getTextureList().at(i)->getTexture());

	dxSetTextureBlend(0, D3DTOP_SELECTARG1, D3DTA_TEXTURE, 0);
	dxSetTextureBlend(1, D3DTOP_MODULATE, D3DTA_TEXTURE, D3DTA_CURRENT);
	dxSetTextureBlend(2, D3DTOP_MODULATE, D3DTA_TEXTURE, D3DTA_CURRENT);
	dxSetTextureBlend(3, D3DTOP_MODULATE, D3DTA_DIFFUSE, D3DTA_CURRENT);

	getMesh()->DrawSubset(0);
	for (size_t i = 0; i < TERRIAN_TEXSIZE; ++i)
		dxSetTexture(i, nullptr);

	dxSetTextureBlend(0, D3DTOP_MODULATE, D3DTA_DIFFUSE, D3DTA_TEXTURE);
	dxSetTextureBlend(1, D3DTOP_DISABLE, 0, 0);
	dxSetTextureBlend(2, D3DTOP_DISABLE, 0, 0);
	dxSetTextureBlend(3, D3DTOP_DISABLE, 0, 0);
}

GObjectType GTerrian::getType() const 
{
	return GOT_TEERIAN;
}

void GTerrian::setHeightTexture( const GString& heightTexture, float MaxHeight )
{
	m_fMaxHeight = MaxHeight;

	GTexture* tex = new GTexture();
	tex->LoadTextureInSysmen(heightTexture.c_str());

	Vertex_p3_n3_c1_t3* vertexes = nullptr;
	getMesh()->LockVertexBuffer(0, (void**)&vertexes);
	size_t numVertex = getMesh()->GetNumVertices();
	for (size_t i = 0; i < numVertex; ++i)
	{
		size_t color_b = tex->getColor(vertexes[i].u1, vertexes[i].v1) & 0x000000FF;
		float height = float(color_b) / 255.0f * (MaxHeight - m_fHeight);
		vertexes[i].y = height;
	}


	getMesh()->UnlockVertexBuffer();

	delete tex;
}
