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

	//添加节点到世界
	void addToWorld(GNode* node);
	//从世界移除节点
	void removeFromWorld(GNode* node);

	//添加绘制对象
	void addDrawObject(GObjectRendable* object);
	//移除绘制对象
	void removeDrawObject(GObjectRendable* object);

	//设置摄像机
	void setCamera(GCamera* camera);

	virtual GObjectType getType() const override;

	//更新场景数据
	void Update();
	//绘制该场景
	void Draw();

	//添加Tag索引
	void addTagObject(GObject* object);
	//添加名字索引
	void addNameObject(GObject* object);
	//移除Tag索引
	void removeTagObject(int tag);
	//移除名字索引
	void removeNameObject(const GString& name);

	//得到根节点(世界单位矩阵)
	GNode* getRootNode() const;

	//设置天空盒
	void setSkybox(GSkybox* skybox);
	//得到天空盒
	GSkybox* getSkybox() const;

private:
	GNode*						m_pRootNode;					//根节点
	Set<GObjectRendable*>		m_pDrawObjectSet;				//绘制集合


	nameobj_t					m_strNameObject;				//名字映射表
	tagobj_t					m_iTagObject;					//Tag索引映射表
	GCamera*					m_pCamera;						//当前摄像机
private:
	std::vector<GNode*>			node_list;						//用于递归的栈
	GSkybox*					m_pSkybox;						//天空盒
};
#endif