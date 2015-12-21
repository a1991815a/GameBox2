#ifndef __GSCENEMANAGER__
#define __GSCENEMANAGER__
#include "GameHeader.h"
#include "GSystem.h"
#include "GNode.h"
#include "GObjectRendable.h"
#include "GScene.h"

#define _sceneManager GSceneManager::getInstance()

class GSceneManager: 
	public GSystem,
	public SingleInstance<GSceneManager>{
public:
	GSceneManager();
	~GSceneManager();

	virtual bool Init();
	virtual void Destroy();

	//添加节点到当前世界
	void addToWorld(GNode* node);
	//从当前世界移除节点
	void removeFromWorld(GNode* node);

	//添加绘制目标到当前场景
	void addDrawObject(GObjectRendable* object);
	//从当前场景移除绘制目标
	void removeDrawObject(GObjectRendable* object);
	
	//添加场景
	void addScene(const GString& name, GScene* scene);
	//移除场景
	void removeScene(const GString& name);
	//设置当前场景
	void setCurrentScene(GScene* scene);
	//设置当前场景
	void setCurrentScene(const GString& name);
	//得到当前场景
	GScene* getCurrentScene() const;

	//设置当前场景的摄像机
	void setCamera(GCamera* camera);

	//设置天空盒
	void setSkybox(GSkybox* box);
	//得到天空盒
	void getSkybox() const;

	//主循环
	void Loop();
private:
	GScene*					m_pCurrentScene;				//当前场景
	Map<GString, GScene*>	m_pSceneMap;					//场景集合
};
#endif