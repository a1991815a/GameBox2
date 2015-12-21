#include "GSceneManager.h"



GSceneManager::GSceneManager()
	:GSystem(1, "SceneManager: ³¡¾°¹ÜÀíÆ÷"), m_pCurrentScene(nullptr)
{

}

GSceneManager::~GSceneManager()
{
	SAFE_RELEASE(m_pCurrentScene);
}

bool GSceneManager::Init()
{
	
	return true;
}

void GSceneManager::Destroy()
{
	m_pSceneMap.clear();
}

void GSceneManager::addToWorld( GNode* node )
{
	m_pCurrentScene->addToWorld(node);
}

void GSceneManager::removeFromWorld( GNode* node )
{
	m_pCurrentScene->removeFromWorld(node);
}

void GSceneManager::addDrawObject( GObjectRendable* object )
{
	m_pCurrentScene->addDrawObject(object);
}

void GSceneManager::removeDrawObject( GObjectRendable* object )
{
	m_pCurrentScene->removeDrawObject(object);
}

void GSceneManager::addScene( const GString& name, GScene* scene )
{
	m_pSceneMap.insert(name, scene);
}

void GSceneManager::removeScene( const GString& name )
{
	m_pSceneMap.erase(name);
}

void GSceneManager::setCurrentScene( GScene* scene )
{
	SAFE_RELEASE(m_pCurrentScene);
	m_pCurrentScene = scene;
	SAFE_RETAIN(m_pCurrentScene);
}

void GSceneManager::setCurrentScene( const GString& name )
{
	SAFE_RELEASE(m_pCurrentScene);
	m_pCurrentScene = m_pSceneMap.at(name);
	SAFE_RETAIN(m_pCurrentScene);
}

GScene* GSceneManager::getCurrentScene() const
{
	return m_pCurrentScene;
}

void GSceneManager::setCamera( GCamera* camera )
{
	GTHROW_RUNTIME(m_pCurrentScene, "CurrentScene isn't Set!");
	m_pCurrentScene->setCamera(camera);
}

void GSceneManager::Loop()
{
	GTHROW_RUNTIME(m_pCurrentScene, "CurrentScene isn't Set!");
	m_pCurrentScene->Update();
	m_pCurrentScene->Draw();
}
