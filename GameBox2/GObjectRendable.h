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

	//���ؽڵ�
	void attachNode(GNode* node);
	//ж�ؽڵ�
	void deattachNode();

	//�õ��ڵ�(�����޸�)
	const GNode* getAttachNode() const;
	//�õ��ڵ�
	GNode* getAttachNode();

	//��������
	void setTexture(DWORD index, const GString& name);
	//�õ�����
	GTexture* getTexture(DWORD index);
	//�õ�����(����)
	const GTexture* getTexture(DWORD index) const;

	//��������
	void setMesh(ID3DXMesh* mesh);
	//�õ�����
	ID3DXMesh* getMesh() const;
	//������������
	void setNumAttribute(DWORD num);
	//�õ���������
	DWORD getNumnAttribute() const;

	virtual GObjectType getType() const override;
	//���ƺ���
	virtual void Draw();

protected:
	inline Vector<GTexture*>& getTextureList(){return m_pTextureVector;};

private:
	GNode*				m_pAttachNode;					//���صĽڵ�
	size_t				m_uNumAttribute;				//��������(��ʾ���ʸ������������)
	ID3DXMesh*			m_pDrawMesh;					//���ڻ��Ƶ�����
	Vector<GTexture*>	m_pTextureVector;				//����
};
#endif