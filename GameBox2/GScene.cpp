#include "GScene.h"
#include "RenderEngine\DXUtils.h"



GScene::GScene()
	:m_pRootNode(nullptr), m_pCamera(nullptr), m_pSkybox(nullptr)
{
	m_pRootNode = new GNode();
	node_list.reserve(160);
}

GScene::~GScene()
{
	SAFE_DELETE(m_pRootNode);
}

void GScene::addToWorld( GNode* node )
{
	m_pRootNode->addChild(node);
}

void GScene::removeFromWorld( GNode* node )
{
	m_pRootNode->removeChild(node);
}

void GScene::addDrawObject( GObjectRendable* object )
{
	m_pDrawObjectSet.insert(object);
}

void GScene::removeDrawObject( GObjectRendable* object )
{
	m_pDrawObjectSet.erase(object);
}

void GScene::setCamera( GCamera* camera )
{
	SAFE_RELEASE(m_pCamera);
	m_pCamera = camera;
	SAFE_RETAIN(m_pCamera);
}

GObjectType GScene::getType() const
{
	return GOT_SCENE;
}

void GScene::Update()
{
	GTHROW_RUNTIME(m_pCamera, "Camera isn't Set!");
	//�������������
	m_pCamera->UpdateLookMatrix();
	//�����ڵ���ӵ�ջ
	node_list.push_back(m_pRootNode);
	//��ջ���������к��� ����������Node�ڵ�
	while (!node_list.empty())
	{
		GNode* node = node_list.back();
		node_list.pop_back();
		node->UpdateFinalMatrix();
		auto itor = node->m_pChildrenSet.begin();
		for (; itor != node->m_pChildrenSet.end(); ++itor)
			node_list.push_back(*itor);
	}
// 	//���ջ
//	ջ�ǿջ������ѭ������������뵽��һ�������Բ���Ҫ�ٴ��ֶ����
// 	node_list.clear();

	//��պи���
	if (m_pSkybox)
		m_pSkybox->UpdateMatrix(m_pCamera);
}

void GScene::Draw()
{
	//��ʼ����
	dxBeginScene();
	GTHROW_RUNTIME(m_pCamera, "Camera isn't Set!");
	//��װ�����
	m_pCamera->SetupCamera();

	//��պл���
	if (m_pSkybox)
		m_pSkybox->Draw();

	//�������л��ƶ���
	auto itor = m_pDrawObjectSet.begin();
	for (; itor != m_pDrawObjectSet.end(); ++itor)
	{
		GObjectRendable* object = *itor;
		if(!object->isVisable())
			continue;
		object->Draw();
	}
	dxEndScene();
}

void GScene::addTagObject( GObject* object )
{
	if(object->getTag() == 0)
		return;
	auto itor = m_iTagObject.find(object->getTag());
	if(itor == m_iTagObject.end())
		m_iTagObject.insert(tagobj_t::value_type(object->getTag(), object));
}

void GScene::addNameObject( GObject* object )
{
	if(object->getName().empty())
		return;
	auto itor = m_strNameObject.find(object->getName());
	if(itor == m_strNameObject.end())
		m_strNameObject.insert(nameobj_t::value_type(object->getName(), object));
}

void GScene::removeTagObject( int tag )
{
	if(tag == 0)
		return;
	auto itor = m_iTagObject.find(tag);
	if(itor != m_iTagObject.end())
		m_iTagObject.erase(itor);
}

void GScene::removeNameObject( const GString& name )
{
	if(name.empty())
		return;
	auto itor = m_strNameObject.find(name);
	if(itor != m_strNameObject.end())
		m_strNameObject.erase(itor);
}

GNode* GScene::getRootNode() const
{
	return m_pRootNode;
}

void GScene::setSkybox(GSkybox* skybox)
{
	SAFE_RELEASE(m_pSkybox);
	m_pSkybox = skybox;
	SAFE_RETAIN(skybox);
}

GSkybox* GScene::getSkybox() const
{
	return m_pSkybox;
}
