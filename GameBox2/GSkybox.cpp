#include "GSkybox.h"
#include "RenderEngine\DXUtils.h"

#pragma warning(push)
#pragma warning(disable: 4267)

GSkybox::GSkybox()
	:m_worldMatrix(*dxGetUnitMatrix())
{

}

GSkybox* GSkybox::create(float width)
{
	GSkybox* box = new GSkybox();
	if (box && box->init(width))
	{
		box->autorelease();
		return box;
	}
	delete box;
	return nullptr;
}

bool GSkybox::init(float width)
{
	width = width / 2;
	ID3DXMesh* mesh = nullptr;

	D3DXCreateMeshFVF(12, 24, D3DXMESH_MANAGED, Vertex_p3_n3_c1_t1::fvf, dxGetDevice(), &mesh);
	Vertex_p3_n3_c1_t1* vertexes = nullptr;
	WORD*				indexes = nullptr;
	MESH_LOCK(vertexes, indexes, mesh);

	//顶点初始化
	{
		size_t array_index = 0;
		*vertexes[array_index].getPosition() = D3DXVECTOR3(-width, -width, -width);
		vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
		vertexes[array_index++].setUV(0, 1);

		*vertexes[array_index].getPosition() = D3DXVECTOR3(width, -width, -width);
		vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
		vertexes[array_index++].setUV(1, 1);

		*vertexes[array_index].getPosition() = D3DXVECTOR3(-width, width, -width);
		vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
		vertexes[array_index++].setUV(0, 0);

		*vertexes[array_index].getPosition() = D3DXVECTOR3(width, width, -width);
		vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
		vertexes[array_index++].setUV(1, 0);

		float uAngle = D3DX_PI / 2;
		for (size_t i = 0; i < 5; ++i)
		{
			D3DXMATRIX matrix;
			if(i < 3)
				D3DXMatrixRotationY(&matrix, uAngle * (i + 1));
			else if (i == 3)
				D3DXMatrixRotationX(&matrix, -uAngle);
			else if (i == 4)
				D3DXMatrixRotationX(&matrix, uAngle);
			for (size_t j = 0; j < 4; ++j)
			{
				D3DXVec3TransformCoord(
					vertexes[array_index].getPosition(),
					vertexes[j].getPosition(),
					&matrix);
				vertexes[array_index].color = D3DCOLOR_XRGB(255, 255, 255);
				vertexes[array_index++].setUV(vertexes[j].u, vertexes[j].v);
			}
		}
	}

	//索引初始化
	{
		size_t array_index = 0;
		for (size_t i = 0; i < 6; ++ i)
		{
			size_t bottom_left =  i * 4;
			size_t bottom_right = bottom_left + 1;
			size_t top_left = bottom_left + 2;
			size_t top_right = bottom_left + 3;

			indexes[array_index++] = bottom_left;
			indexes[array_index++] = bottom_right;
			indexes[array_index++] = top_left;

			indexes[array_index++] = top_left;
			indexes[array_index++] = bottom_right;
			indexes[array_index++] = top_right;
		}
	}
	MESH_UNLOCK(mesh);

	setMesh(mesh);

	setNumAttribute(6);
	{
		DWORD* attributes = nullptr;
		mesh->LockAttributeBuffer(0, &attributes);

		size_t array_index = 0;
		{
			attributes[array_index++] = 0;
			attributes[array_index++] = 0;

			attributes[array_index++] = 1;
			attributes[array_index++] = 1;

			attributes[array_index++] = 2;
			attributes[array_index++] = 2;

			attributes[array_index++] = 3;
			attributes[array_index++] = 3;

			attributes[array_index++] = 4;
			attributes[array_index++] = 4;

			attributes[array_index++] = 5;
			attributes[array_index++] = 5;
		}

		mesh->UnlockAttributeBuffer();
	}

	return true;
}

GObjectType GSkybox::getType() const
{
	return GOT_SKYBOX;
}

void GSkybox::Draw()
{
	DWORD lightState = 0;
	dxGetDevice()->GetRenderState(D3DRS_LIGHTING, &lightState);
	dxGetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
	dxGetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
	dxGetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	dxGetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);
	
	//安装矩阵
	dxSetWorld(&m_worldMatrix);
	//设置纹理 并 绘制网格
	for (size_t i = 0; i < getNumnAttribute(); ++i)
	{
		dxSetTexture(0, getTexture(i)->getTexture());
		getMesh()->DrawSubset(i);
	}

	dxGetDevice()->SetRenderState(D3DRS_ZENABLE, TRUE);
	dxGetDevice()->SetRenderState(D3DRS_LIGHTING, lightState);
	dxGetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);
	dxGetDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
}

void GSkybox::UpdateMatrix(GCamera* camera)
{
	D3DXVECTOR3 pos = camera->getPosition();
	const D3DXVECTOR3& m_pos = *(D3DXVECTOR3*)m_worldMatrix.m[3];
	//判断是否需要更新矩阵
	if (pos == m_pos)
		return;
	D3DXMatrixTranslation(&m_worldMatrix, pos.x, pos.y, pos.z);
}


#pragma warning(pop)