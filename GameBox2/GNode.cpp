#include "GNode.h"
#include "RenderEngine\DXUtils.h"



GNode::GNode()
	:m_dwFlag(0), m_pParent(nullptr), m_iTag(0), m_strName()
{
	m_mLocalMatrix = m_mParentMatrix = m_mWorldMatrix = m_mFinalMatrix = *dxGetUnitMatrix();
	m_v3LocalPosition = m_v3LocalRotation = m_v3ParentPosition = m_v3ParentRotation
		= m_v3WorldPosition = m_v3WorldRotation = D3DXVECTOR3(0, 0, 0);
	m_v3LocalScaling = m_v3ParentScaling = m_v3WorldScaling = D3DXVECTOR3(1, 1, 1);
}

GNode::~GNode()
{
	clearChild();
}

GNode* GNode::clone() const
{
	GNode* node = new GNode();
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
		node->m_pChildrenSet.insert(*itor);

	node->m_mLocalMatrix = m_mLocalMatrix;
	node->m_mParentMatrix = m_mParentMatrix;
	node->m_mWorldMatrix = m_mWorldMatrix;
	node->m_mFinalMatrix = m_mFinalMatrix;
	node->m_v3LocalPosition = m_v3LocalPosition;
	node->m_v3LocalRotation = m_v3LocalRotation;
	node->m_v3LocalScaling = m_v3LocalScaling;
	node->m_v3ParentPosition = m_v3ParentPosition;
	node->m_v3ParentRotation = m_v3ParentRotation;
	node->m_v3ParentScaling = m_v3ParentScaling;
	node->m_v3WorldPosition = m_v3WorldPosition;
	node->m_v3WorldRotation = m_v3WorldRotation;
	node->m_v3WorldScaling = m_v3WorldScaling;
	node->m_dwFlag = m_dwFlag;
	return node;
}

const D3DXMATRIX* GNode::getMatrix(GTransforType type) const
{
	switch (type)
	{
	case GTS_LOCAL:
		return &m_mLocalMatrix;
	case GTS_PARENT:
		return &m_mParentMatrix;
	case GTS_WORLD:
		return &m_mWorldMatrix;
	default:
		break;
	}
	GASSERT(false, "GTransforType error!");
	return nullptr;
}

const D3DXVECTOR3& GNode::getPosition(GTransforType type) const
{
	switch (type)
	{
	case GTS_LOCAL:
		return m_v3LocalPosition;
	case GTS_PARENT:
		return m_v3ParentPosition;
	case GTS_WORLD:
		return m_v3WorldPosition;
	default:
		break;
	}
	GASSERT(false, "GTransforType error!");
	return m_v3WorldPosition;
}

const D3DXVECTOR3& GNode::getRotation(GTransforType type) const
{
	switch (type)
	{
	case GTS_LOCAL:
		return m_v3LocalRotation;
	case GTS_PARENT:
		return m_v3ParentRotation;
	case GTS_WORLD:
		return m_v3WorldRotation;
	default:
		break;
	}
	GASSERT(false, "GTransforType error!");
	return m_v3WorldRotation;
}

const D3DXVECTOR3& GNode::getScaling(GTransforType type) const
{
	switch (type)
	{
	case GTS_LOCAL:
		return m_v3LocalScaling;
	case GTS_PARENT:
		return m_v3ParentScaling;
	case GTS_WORLD:
		return m_v3WorldScaling;
	default:
		break;
	}
	GASSERT(false, "GTransforType error!");
	return m_v3WorldScaling;
}

const D3DXMATRIX* GNode::getFinalMatrix() const
{
	return &m_mFinalMatrix;
}

const D3DXVECTOR3& GNode::getFinalPosition() const
{
	return *(D3DXVECTOR3*)m_mFinalMatrix.m[3];
}
// 
// const D3DXVECTOR3& GNode::getFinalRotation() const
// {
// 
// }
// 
// const D3DXVECTOR3& GNode::getFinalScaling() const
// {
// 
// }

void GNode::setPosition(GTransforType type, const D3DXVECTOR3* pos)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalPosition = *pos;
		break;
	case GTS_PARENT:
		m_v3ParentPosition = *pos;
		break;
	case GTS_WORLD:
		m_v3WorldPosition = *pos;
		break;
	default:
		break;
	}
}

void GNode::setPositionX(GTransforType type, float x)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalPosition.x = x;
		break;
	case GTS_PARENT:
		m_v3ParentPosition.x = x;
		break;
	case GTS_WORLD:
		m_v3WorldPosition.x = x;
		break;
	default:
		break;
	}
}

void GNode::setPositionY(GTransforType type, float y)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalPosition.y = y;
		break;
	case GTS_PARENT:
		m_v3ParentPosition.y = y;
		break;
	case GTS_WORLD:
		m_v3WorldPosition.y = y;
		break;
	default:
		break;
	}
}

void GNode::setPositionZ(GTransforType type, float z)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalPosition.z = z;
		break;
	case GTS_PARENT:
		m_v3ParentPosition.z = z;
		break;
	case GTS_WORLD:
		m_v3WorldPosition.z = z;
		break;
	default:
		break;
	}
}

void GNode::setRotation(GTransforType type, const D3DXVECTOR3* rotation)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalRotation = *rotation;
		break;
	case GTS_PARENT:
		m_v3ParentRotation = *rotation;
		break;
	case GTS_WORLD:
		m_v3WorldRotation = *rotation;
		break;
	default:
		break;
	}
}

void GNode::setRotationX(GTransforType type, float x)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalRotation.x = x;
		break;
	case GTS_PARENT:
		m_v3ParentRotation.x = x;
		break;
	case GTS_WORLD:
		m_v3WorldRotation.x = x;
		break;
	default:
		break;
	}
}

void GNode::setRotationY(GTransforType type, float y)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalRotation.y = y;
		break;
	case GTS_PARENT:
		m_v3ParentRotation.y = y;
		break;
	case GTS_WORLD:
		m_v3WorldRotation.y = y;
		break;
	default:
		break;
	}
}

void GNode::setRotationZ(GTransforType type, float z)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalRotation.z = z;
		break;
	case GTS_PARENT:
		m_v3ParentRotation.z = z;
		break;
	case GTS_WORLD:
		m_v3WorldRotation.z = z;
		break;
	default:
		break;
	}
}

void GNode::setScaling(GTransforType type, const D3DXVECTOR3* scaling)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalScaling = *scaling;
		break;
	case GTS_PARENT:
		m_v3ParentScaling = *scaling;
		break;
	case GTS_WORLD:
		m_v3WorldScaling = *scaling;
		break;
	default:
		break;
	}
}

void GNode::setScalingX(GTransforType type, float x)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalScaling.x = x;
		break;
	case GTS_PARENT:
		m_v3ParentScaling.x = x;
		break;
	case GTS_WORLD:
		m_v3WorldScaling.x = x;
		break;
	default:
		break;
	}
}

void GNode::setScalingY(GTransforType type, float y)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalScaling.y = y;
		break;
	case GTS_PARENT:
		m_v3ParentScaling.y = y;
		break;
	case GTS_WORLD:
		m_v3WorldScaling.y = y;
		break;
	default:
		break;
	}
}

void GNode::setScalingZ(GTransforType type, float z)
{
	enableFlagByType(type);
	switch (type)
	{
	case GTS_LOCAL:
		m_v3LocalScaling.z = z;
		break;
	case GTS_PARENT:
		m_v3ParentScaling.z = z;
		break;
	case GTS_WORLD:
		m_v3WorldScaling.z = z;
		break;
	default:
		break;
	}
}

void GNode::addChild(GNode* node)
{
	if(m_pChildrenSet.find(node) != m_pChildrenSet.end())
		m_pChildrenSet.insert(node);
}

void GNode::removeChild(GNode* node)
{
	m_pChildrenSet.erase(node);
}

void GNode::removeChildByTag(int tag)
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
	{
		if ((*itor)->m_iTag == tag)
		{
			m_pChildrenSet.erase(itor);
			break;
		}
	}
}

void GNode::removeChildByName(const GString& name)
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
	{
		if ((*itor)->m_strName == name)
		{
			m_pChildrenSet.erase(itor);
			break;
		}
	}
}

void GNode::clearChild()
{
	m_pChildrenSet.clear();
}

GNode* GNode::getParent()
{
	return m_pParent;
}

const GNode* GNode::getParent() const
{
	return m_pParent;
}

GNode* GNode::searchChildByTag(int tag)
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
		if ((*itor)->m_iTag == tag)
			return *itor;
	return nullptr;
}

const GNode* GNode::searchChildByTag(int tag) const
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
		if ((*itor)->m_iTag == tag)
			return *itor;
	return nullptr;
}

GNode* GNode::searchChildByName(const GString& name)
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
		if ((*itor)->m_strName == name)
			return *itor;
	return nullptr;
}

const GNode* GNode::searchChildByName(const GString& name) const
{
	auto itor = m_pChildrenSet.begin();
	for (; itor != m_pChildrenSet.end(); ++itor)
		if ((*itor)->m_strName == name)
			return *itor;
	return nullptr;
}

void GNode::UpdateLocalMatrix()
{
	if (!isEnableFlag(LOCAL_UPDATE))
		return;
	D3DXMatrixIdentity(&m_mLocalMatrix);
	D3DXMATRIX matrix;
	D3DXMatrixRotationYawPitchRoll(&m_mLocalMatrix, m_v3LocalRotation.y, m_v3LocalRotation.x, m_v3LocalRotation.z);
	D3DXMatrixScaling(&matrix, m_v3LocalScaling.x, m_v3LocalScaling.y, m_v3LocalScaling.z);
	m_mLocalMatrix = m_mLocalMatrix * matrix;
	D3DXMatrixTranslation(&matrix, m_v3LocalPosition.x, m_v3LocalPosition.y, m_v3LocalPosition.z);
	m_mLocalMatrix = m_mLocalMatrix * matrix;

	disableFlag(LOCAL_UPDATE);
}

void GNode::UpdateParentMatrix()
{
	if (!isEnableFlag(PARENT_UPDATE))
		return;

	D3DXMatrixIdentity(&m_mParentMatrix);
	D3DXMATRIX matrix;
	D3DXMatrixRotationYawPitchRoll(&m_mParentMatrix, m_v3ParentRotation.y, m_v3ParentRotation.x, m_v3ParentRotation.z);
	D3DXMatrixScaling(&matrix, m_v3ParentScaling.x, m_v3ParentScaling.y, m_v3ParentScaling.z);
	m_mParentMatrix = m_mParentMatrix * matrix;
	D3DXMatrixTranslation(&matrix, m_v3ParentPosition.x, m_v3ParentPosition.y, m_v3ParentPosition.z);
	m_mParentMatrix = m_mParentMatrix * matrix;

	disableFlag(PARENT_UPDATE);
}

void GNode::UpdateWorldMatrix()
{
	if (!isEnableFlag(WORLD_UPDATE))
		return;

	D3DXMatrixIdentity(&m_mWorldMatrix);
	D3DXMATRIX matrix;
	D3DXMatrixRotationYawPitchRoll(&m_mWorldMatrix, m_v3WorldRotation.y, m_v3WorldRotation.x, m_v3WorldRotation.z);
	D3DXMatrixScaling(&matrix, m_v3WorldScaling.x, m_v3WorldScaling.y, m_v3WorldScaling.z);
	m_mWorldMatrix = m_mWorldMatrix * matrix;
	D3DXMatrixTranslation(&matrix, m_v3WorldPosition.x, m_v3WorldPosition.y, m_v3WorldPosition.z);
	m_mWorldMatrix = m_mWorldMatrix * matrix;

	disableFlag(WORLD_UPDATE);
}

void GNode::UpdateFinalMatrix()
{
	if (!isEnableFlag(FINAL_UPDATE))
		return;
	UpdateLocalMatrix();
	UpdateParentMatrix();
	UpdateWorldMatrix();
	//有父亲
	if(m_pParent)
	{
		D3DXMATRIX inverseMatrix;
		D3DXMatrixInverse(&inverseMatrix, nullptr, &m_pParent->m_mFinalMatrix);
		m_mFinalMatrix = 
			m_mLocalMatrix * m_pParent->m_mFinalMatrix *		//本地空间转父亲空间
			m_mParentMatrix *									//父亲空间
			inverseMatrix * m_mWorldMatrix *					//世界空间转父亲空间
			m_pParent->m_mFinalMatrix;							//最终转到世界空间
	}//没有父亲
	else {
		m_mFinalMatrix = 
			m_mLocalMatrix * 									//本地空间转父亲空间
			m_mParentMatrix *									//父亲空间
			m_mWorldMatrix;										//世界空间转父亲空间
	}

	disableFlag(FINAL_UPDATE);
}

void GNode::SetupFinalMatrix() const
{
	dxGetDevice()->SetTransform(D3DTS_WORLD, &m_mFinalMatrix);
}
