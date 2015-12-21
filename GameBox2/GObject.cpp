#include "GObject.h"
#include "GSceneManager.h"



GObject::~GObject()
{
	auto scene = _sceneManager->getCurrentScene();
	scene->removeTagObject(m_iTag);
	scene->removeNameObject(m_strName);
}

void GObject::setTag( int tag )
{
	auto scene = _sceneManager->getCurrentScene();
	scene->removeTagObject(m_iTag);
	m_iTag = tag;
	scene->addTagObject(this);
}

void GObject::setName( const GString& name )
{
	auto scene = _sceneManager->getCurrentScene();
	scene->removeNameObject(m_strName);
	m_strName = name;
	scene->addNameObject(this);
}
