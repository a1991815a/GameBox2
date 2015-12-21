#include "GObjectRendable.h"
#include "RenderEngine\DXUtils.h"



GObjectRendable::~GObjectRendable()
{
	SAFE_RELEASE(m_pAttachNode);
	SAFE_RELEASE_COM(m_pDrawMesh);
}

void GObjectRendable::attachNode(GNode* node)
{
	SAFE_RELEASE(m_pAttachNode);
	m_pAttachNode = node;
	SAFE_RETAIN(m_pAttachNode);
}

void GObjectRendable::deattachNode()
{
	SAFE_RELEASE(m_pAttachNode);
}

const GNode* GObjectRendable::getAttachNode() const
{
	return m_pAttachNode;
}

GNode* GObjectRendable::getAttachNode()
{
	return m_pAttachNode;
}

void GObjectRendable::setTexture(DWORD index, const GString& name)
{
	GTexture*& texture = m_pTextureVector.at(index);
	SAFE_DELETE(texture);
	texture = new GTexture();
	texture->LoadTexture(name.c_str());
}

GTexture* GObjectRendable::getTexture(DWORD index)
{
	return m_pTextureVector.at(index);
}

const GTexture* GObjectRendable::getTexture(DWORD index) const
{
	return m_pTextureVector.at(index);
}

void GObjectRendable::setMesh(ID3DXMesh* mesh)
{
	m_pDrawMesh = mesh;
}

ID3DXMesh* GObjectRendable::getMesh() const
{
	return m_pDrawMesh;
}

void GObjectRendable::setNumAttribute(DWORD num)
{
	if(num > m_pTextureVector.size())
		m_pTextureVector.resize(num);
	m_uNumAttribute = num;
}

DWORD GObjectRendable::getNumnAttribute() const
{
	return m_uNumAttribute;
}

GObjectType GObjectRendable::getType() const
{
	return GOT_RENDABLE;
}

void GObjectRendable::Draw()
{
	//安装矩阵
	if (m_pAttachNode)
		m_pAttachNode->SetupFinalMatrix();
	else
	{
		LOG_W("FILE:%s, LINE:%d, name:%s Type:%d  not attach GNode!", 
			__FILE__, __LINE__,
			getName().c_str(), getType());
		dxSetWorld(dxGetUnitMatrix());
	}
	//设置纹理 并 绘制网格
	for (size_t i = 0; i < m_uNumAttribute; ++i)
	{
		dxSetTexture(0, m_pTextureVector.at(i)->getTexture());
		m_pDrawMesh->DrawSubset(i);
	}
}
