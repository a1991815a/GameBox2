#ifndef __GOBJECTRENDABLE__
#define __GOBJECTRENDABLE__
#include "GObject.h"
#include "GNode.h"
#include "GTexture.h"

#define MESH_LOCK(VERTEX, INDEX, MESH) \
MESH->LockVertexBuffer(0, (void**)&VERTEX); \
MESH->LockIndexBuffer(0, (void**)&INDEX)

#define MESH_UNLOCK(MESH) \
MESH->UnlockVertexBuffer(); \
MESH->UnlockIndexBuffer()

class GObjectRendable: public GObject{
public:
	GObjectRendable() 
		:m_pAttachNode(nullptr)
	{};


	~GObjectRendable();

	//挂载节点
	void attachNode(GNode* node);
	//卸载节点
	void deattachNode();

	//得到节点(不可修改)
	const GNode* getAttachNode() const;
	//得到节点
	GNode* getAttachNode();

	//设置纹理
	void setTexture(DWORD index, const GString& name);
	//得到纹理
	GTexture* getTexture(DWORD index);
	//得到纹理(常量)
	const GTexture* getTexture(DWORD index) const;

	//设置网格
	void setMesh(ID3DXMesh* mesh);
	//得到网格
	ID3DXMesh* getMesh() const;
	//设置属性总数
	void setNumAttribute(DWORD num);
	//得到属性总数
	DWORD getNumnAttribute() const;

	virtual GObjectType getType() const override;
	//绘制函数
	virtual void Draw();

protected:
	inline Vector<GTexture*>& getTextureList(){return m_pTextureVector;};

private:
	GNode*				m_pAttachNode;					//挂载的节点
	size_t				m_uNumAttribute;				//属性总数(表示材质个数，纹理个数)
	ID3DXMesh*			m_pDrawMesh;					//用于绘制的网格
	Vector<GTexture*>	m_pTextureVector;				//纹理
};
#endif