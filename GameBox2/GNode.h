#ifndef __GNODE__
#define __GNODE__
#include "GameHeader.h"
#include "Ref.h"

#pragma warning(push)
#pragma warning(disable: 4800)

enum GTransforType
{
	GTS_LOCAL,					//本地空间
	GTS_PARENT,					//父亲空间
	GTS_WORLD					//世界空间
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

	/*矩阵和其他坐标数据操作*******************/
	//按参数得到相应的变换矩阵类型(不包括最终矩阵)
	const D3DXMATRIX* getMatrix(GTransforType type) const;
	//按参数得到相应位移
	const D3DXVECTOR3& getPosition(GTransforType type) const;
	//按参数得到相应旋转
	const D3DXVECTOR3& getRotation(GTransforType type) const;
	//按参数得到相应缩放
	const D3DXVECTOR3& getScaling(GTransforType type) const;

	//得到最终矩阵
	const D3DXMATRIX* getFinalMatrix() const;
	//得到最终位移
	const D3DXVECTOR3& getFinalPosition() const;
	//得到最终旋转
	const D3DXVECTOR3& getFinalRotation() const;
	//得到最终缩放
	const D3DXVECTOR3& getFinalScaling() const;

	//设置对应空间的位移
	void setPosition(GTransforType type, const D3DXVECTOR3* pos);
	void setPositionX(GTransforType type, float x);
	void setPositionY(GTransforType type, float y);
	void setPositionZ(GTransforType type, float z);
	//设置对应空间的旋转
	void setRotation(GTransforType type, const D3DXVECTOR3* rotation);
	void setRotationX(GTransforType type, float x);
	void setRotationY(GTransforType type, float y);
	void setRotationZ(GTransforType type, float z);
	//设置对应空间的缩放
	void setScaling(GTransforType type, const D3DXVECTOR3* scaling);
	void setScalingX(GTransforType type, float x);
	void setScalingY(GTransforType type, float y);
	void setScalingZ(GTransforType type, float z);



	/*开关操作*******************/
	//得到开关设置
	inline DWORD getFlag() const { return m_dwFlag; };
	//设置开关
	inline void setFlag(DWORD dwFlag) { m_dwFlag = dwFlag; };
	//打开开关
	inline void enableFlag(DWORD dwFlag) { m_dwFlag |= dwFlag; };
	//关闭开关
	inline void disableFlag(DWORD dwFlag) { m_dwFlag &= ~dwFlag; };
	//查看开关是否打开
	inline bool isEnableFlag(DWORD dwFlag) const { return m_dwFlag & dwFlag; };
	//根据坐标空间打开开关
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

	/*父子操作*******************/
	//添加孩子
	void addChild(GNode* node);
	//删除孩子
	void removeChild(GNode* node);
	//删除孩子(标记)
	void removeChildByTag(int tag);
	//删除孩子(名字)
	void removeChildByName(const GString& name);
	//清空孩子
	void clearChild();
	//得到父亲
	GNode* getParent();
	//得到父亲(不可修改)
	const GNode* getParent() const;
	//搜索孩子(标记)
	GNode* searchChildByTag(int tag);
	//搜索孩子(名字)
	GNode* searchChildByName(const GString& name);
	//搜索孩子(标记)
	const GNode* searchChildByTag(int tag) const;
	//搜索孩子(名字)
	const GNode* searchChildByName(const GString& name) const;

	/*标记操作*******************/
	//设置Tag标记
	inline void setTag(int tag) { m_iTag = tag; };
	//得到Tag标记
	inline int getTag() const { return m_iTag; };
	//设置名字
	inline void setName(const GString& name) { m_strName = name; };
	//得到名字
	inline const GString& getName() const { return m_strName; };

	/*矩阵更新操作***************/
	//更新本地空间变换矩阵
	void UpdateLocalMatrix();
	//更新父亲空间变换矩阵
	void UpdateParentMatrix();
	//更新世界空间变换矩阵
	void UpdateWorldMatrix();
	//更新最终变换矩阵(注意需要先更新父亲的最终矩阵)
	void UpdateFinalMatrix();

	//安装矩阵
	void SetupFinalMatrix() const;
private:
	D3DXMATRIX			m_mLocalMatrix;					//本地空间变换矩阵
	D3DXMATRIX			m_mParentMatrix;				//父亲空间变换矩阵
	D3DXMATRIX			m_mWorldMatrix;					//世界空间变换矩阵
	D3DXMATRIX			m_mFinalMatrix;					//最终变换矩阵

	D3DXVECTOR3			m_v3LocalPosition;				//本地空间位移
	D3DXVECTOR3			m_v3LocalRotation;				//本地空间旋转
	D3DXVECTOR3			m_v3LocalScaling;				//本地空间缩放

	D3DXVECTOR3			m_v3ParentPosition;				//父亲空间位移
	D3DXVECTOR3			m_v3ParentRotation;				//父亲空间旋转
	D3DXVECTOR3			m_v3ParentScaling;				//父亲空间缩放

	D3DXVECTOR3			m_v3WorldPosition;				//世界空间位移
	D3DXVECTOR3			m_v3WorldRotation;				//世界空间旋转
	D3DXVECTOR3			m_v3WorldScaling; 				//世界空间缩放

	DWORD				m_dwFlag;						//Flag开关设置
	Set<GNode*>			m_pChildrenSet;					//孩子集合
	GNode*				m_pParent;						//父亲指针
	int					m_iTag;							//标记值
	GString				m_strName;						//节点名字
};

#pragma warning(pop)
#endif