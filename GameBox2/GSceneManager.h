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

	//��ӽڵ㵽��ǰ����
	void addToWorld(GNode* node);
	//�ӵ�ǰ�����Ƴ��ڵ�
	void removeFromWorld(GNode* node);

	//��ӻ���Ŀ�굽��ǰ����
	void addDrawObject(GObjectRendable* object);
	//�ӵ�ǰ�����Ƴ�����Ŀ��
	void removeDrawObject(GObjectRendable* object);
	
	//��ӳ���
	void addScene(const GString& name, GScene* scene);
	//�Ƴ�����
	void removeScene(const GString& name);
	//���õ�ǰ����
	void setCurrentScene(GScene* scene);
	//���õ�ǰ����
	void setCurrentScene(const GString& name);
	//�õ���ǰ����
	GScene* getCurrentScene() const;

	//���õ�ǰ�����������
	void setCamera(GCamera* camera);

	//������պ�
	void setSkybox(GSkybox* box);
	//�õ���պ�
	void getSkybox() const;

	//��ѭ��
	void Loop();
private:
	GScene*					m_pCurrentScene;				//��ǰ����
	Map<GString, GScene*>	m_pSceneMap;					//��������
};
#endif