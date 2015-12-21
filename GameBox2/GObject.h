#ifndef __GOBJECT__
#define __GOBJECT__
#include "GameHeader.h"
#include "GObjectType.h"
#include "Ref.h"

#pragma warning(push)
#pragma warning(disable:4800)

//游戏对象
class GObject: public Ref{
public:
	GObject()
		:m_dwFlag(0), m_iTag(0), m_strName(), m_bEnable(true), m_bVisable(true)
	{};
	virtual ~GObject();

	//FLAG设置获得
	inline DWORD getFlag() const {
		return m_dwFlag;
	};
	//FLAG设置设置
	inline void setFlag(DWORD flag) {
		m_dwFlag = flag;
	};
	//FLAG打开开关
	inline void enableFlag(DWORD flag) {
		m_dwFlag |= flag;
	};
	//FLAG关闭开关
	inline void disableFlag(DWORD flag) {
		m_dwFlag &= ~flag;
	};
	//FLAG查看是否打开开关
	inline bool isEnableFlag(DWORD flag) const {
		return m_dwFlag & flag;
	};

	//标记映射设置

	//设置TAG
	void setTag(int tag);
	//得到TAG
	inline int getTag() const {
		return m_iTag;
	};
	
	//设置名字
	void setName(const GString& name);
	//得到名字
	inline const GString& getName() const {
		return m_strName;
	};

	//得到类型(虚函数)
	virtual GObjectType getType() const {
		return GOT_NONE;
	};

	//设置可见状态
	inline void setVisable(bool visiable){
		m_bVisable = visiable;
	};
	//得到可见状态
	inline bool isVisable() const{
		return m_bVisable;
	};
	//设置可用状态
	inline void setEnable(bool enable){
		m_bEnable = enable;
	};
	//得到可用状态
	inline bool isEnable() const{
		return m_bEnable;
	};
private:
	DWORD		m_dwFlag;					//flag设置
	int			m_iTag;						//标记
	GString		m_strName;					//名字
	bool		m_bEnable;					//可用状态
	bool		m_bVisable;					//可见状态
};


#pragma warning(pop)
#endif