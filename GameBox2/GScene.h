#ifndef __GSCENE__
#define __GSCENE__
#include "GObject.h"
#include "GNode.h"
#include "GObjectRendable.h"
#include "GCamera.h"
#include "GSkybox.h"

class GScene: public GObject{
	typedef std::unordered_map<GString, GObject*>	nameobj_t;
	typedef std::unordered_map<int, GObject*>		tagobj_t;
public:
	GScene();
	~GScene();

	CREATEINIT_FUNC(GScene);

	//��ӽڵ㵽����
	void addToWorld(GNode* node);
	//�������Ƴ��ڵ�
	void removeFromWorld(GNode* node);

	//��ӻ��ƶ���
	void addDrawObject(GObjectRendable* object);
	//�Ƴ����ƶ���
	void removeDrawObject(GObjectRendable* object);

	//���������
	void setCamera(GCamera* camera);

	virtual GObjectType getType() const override;

	//���³�������
	void Update();
	//���Ƹó���
	void Draw();

	//���Tag����
	void addTagObject(GObject* object);
	//�����������
	void addNameObject(GObject* object);
	//�Ƴ�Tag����
	void removeTagObject(int tag);
	//�Ƴ���������
	void removeNameObject(const GString& name);

	//�õ����ڵ�(���絥λ����)
	GNode* getRootNode() const;

	//������պ�
	void setSkybox(GSkybox* skybox);
	//�õ���պ�
	GSkybox* getSkybox() const;

private:
	GNode*						m_pRootNode;					//���ڵ�
	Set<GObjectRendable*>		m_pDrawObjectSet;				//���Ƽ���


	nameobj_t					m_strNameObject;				//����ӳ���
	tagobj_t					m_iTagObject;					//Tag����ӳ���
	GCamera*					m_pCamera;						//��ǰ�����
private:
	std::vector<GNode*>			node_list;						//���ڵݹ��ջ
	GSkybox*					m_pSkybox;						//��պ�
};
#endif