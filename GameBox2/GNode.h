#ifndef __GNODE__
#define __GNODE__
#include "GameHeader.h"
#include "Ref.h"

#pragma warning(push)
#pragma warning(disable: 4800)

enum GTransforType
{
	GTS_LOCAL,					//���ؿռ�
	GTS_PARENT,					//���׿ռ�
	GTS_WORLD					//����ռ�
};

#define LOCAL_UPDATE		0x00000001
#define PARENT_UPDATE		0x00000002
#define WORLD_UPDATE		0x00000004
#define FINAL_UPDATE		0x00000008

class GNode: public Ref, nocopy{
	friend class GScene;
public:
	GNode();
	~GNode();
	GNode* clone() const;

	CREATEINIT_FUNC(GNode);

	/*����������������ݲ���*******************/
	//�������õ���Ӧ�ı任��������(���������վ���)
	const D3DXMATRIX* getMatrix(GTransforType type) const;
	//�������õ���Ӧλ��
	const D3DXVECTOR3& getPosition(GTransforType type) const;
	//�������õ���Ӧ��ת
	const D3DXVECTOR3& getRotation(GTransforType type) const;
	//�������õ���Ӧ����
	const D3DXVECTOR3& getScaling(GTransforType type) const;

	//�õ����վ���
	const D3DXMATRIX* getFinalMatrix() const;
	//�õ�����λ��
	const D3DXVECTOR3& getFinalPosition() const;
	//�õ�������ת
	const D3DXVECTOR3& getFinalRotation() const;
	//�õ���������
	const D3DXVECTOR3& getFinalScaling() const;

	//���ö�Ӧ�ռ��λ��
	void setPosition(GTransforType type, const D3DXVECTOR3* pos);
	void setPositionX(GTransforType type, float x);
	void setPositionY(GTransforType type, float y);
	void setPositionZ(GTransforType type, float z);
	//���ö�Ӧ�ռ����ת
	void setRotation(GTransforType type, const D3DXVECTOR3* rotation);
	void setRotationX(GTransforType type, float x);
	void setRotationY(GTransforType type, float y);
	void setRotationZ(GTransforType type, float z);
	//���ö�Ӧ�ռ������
	void setScaling(GTransforType type, const D3DXVECTOR3* scaling);
	void setScalingX(GTransforType type, float x);
	void setScalingY(GTransforType type, float y);
	void setScalingZ(GTransforType type, float z);



	/*���ز���*******************/
	//�õ���������
	inline DWORD getFlag() const { return m_dwFlag; };
	//���ÿ���
	inline void setFlag(DWORD dwFlag) { m_dwFlag = dwFlag; };
	//�򿪿���
	inline void enableFlag(DWORD dwFlag) { m_dwFlag |= dwFlag; };
	//�رտ���
	inline void disableFlag(DWORD dwFlag) { m_dwFlag &= ~dwFlag; };
	//�鿴�����Ƿ��
	inline bool isEnableFlag(DWORD dwFlag) const { return m_dwFlag & dwFlag; };
	//��������ռ�򿪿���
	inline void enableFlagByType(GTransforType type) {
		switch (type)
		{
		case GTS_LOCAL:
			enableFlag(LOCAL_UPDATE);
			break;
		case GTS_PARENT:
			enableFlag(PARENT_UPDATE);
			break;
		case GTS_WORLD:
			enableFlag(WORLD_UPDATE);
			break;
		default:
			break;
		}
		enableFlag(FINAL_UPDATE);
	};

	/*���Ӳ���*******************/
	//��Ӻ���
	void addChild(GNode* node);
	//ɾ������
	void removeChild(GNode* node);
	//ɾ������(���)
	void removeChildByTag(int tag);
	//ɾ������(����)
	void removeChildByName(const GString& name);
	//��պ���
	void clearChild();
	//�õ�����
	GNode* getParent();
	//�õ�����(�����޸�)
	const GNode* getParent() const;
	//��������(���)
	GNode* searchChildByTag(int tag);
	//��������(����)
	GNode* searchChildByName(const GString& name);
	//��������(���)
	const GNode* searchChildByTag(int tag) const;
	//��������(����)
	const GNode* searchChildByName(const GString& name) const;

	/*��ǲ���*******************/
	//����Tag���
	inline void setTag(int tag) { m_iTag = tag; };
	//�õ�Tag���
	inline int getTag() const { return m_iTag; };
	//��������
	inline void setName(const GString& name) { m_strName = name; };
	//�õ�����
	inline const GString& getName() const { return m_strName; };

	/*������²���***************/
	//���±��ؿռ�任����
	void UpdateLocalMatrix();
	//���¸��׿ռ�任����
	void UpdateParentMatrix();
	//��������ռ�任����
	void UpdateWorldMatrix();
	//�������ձ任����(ע����Ҫ�ȸ��¸��׵����վ���)
	void UpdateFinalMatrix();

	//��װ����
	void SetupFinalMatrix() const;
private:
	D3DXMATRIX			m_mLocalMatrix;					//���ؿռ�任����
	D3DXMATRIX			m_mParentMatrix;				//���׿ռ�任����
	D3DXMATRIX			m_mWorldMatrix;					//����ռ�任����
	D3DXMATRIX			m_mFinalMatrix;					//���ձ任����

	D3DXVECTOR3			m_v3LocalPosition;				//���ؿռ�λ��
	D3DXVECTOR3			m_v3LocalRotation;				//���ؿռ���ת
	D3DXVECTOR3			m_v3LocalScaling;				//���ؿռ�����

	D3DXVECTOR3			m_v3ParentPosition;				//���׿ռ�λ��
	D3DXVECTOR3			m_v3ParentRotation;				//���׿ռ���ת
	D3DXVECTOR3			m_v3ParentScaling;				//���׿ռ�����

	D3DXVECTOR3			m_v3WorldPosition;				//����ռ�λ��
	D3DXVECTOR3			m_v3WorldRotation;				//����ռ���ת
	D3DXVECTOR3			m_v3WorldScaling; 				//����ռ�����

	DWORD				m_dwFlag;						//Flag��������
	Set<GNode*>			m_pChildrenSet;					//���Ӽ���
	GNode*				m_pParent;						//����ָ��
	int					m_iTag;							//���ֵ
	GString				m_strName;						//�ڵ�����
};

#pragma warning(pop)
#endif