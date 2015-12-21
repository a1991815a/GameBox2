#ifndef __GOBJECT__
#define __GOBJECT__
#include "GameHeader.h"
#include "GObjectType.h"
#include "Ref.h"

#pragma warning(push)
#pragma warning(disable:4800)

//��Ϸ����
class GObject: public Ref{
public:
	GObject()
		:m_dwFlag(0), m_iTag(0), m_strName(), m_bEnable(true), m_bVisable(true)
	{};
	virtual ~GObject();

	//FLAG���û��
	inline DWORD getFlag() const {
		return m_dwFlag;
	};
	//FLAG��������
	inline void setFlag(DWORD flag) {
		m_dwFlag = flag;
	};
	//FLAG�򿪿���
	inline void enableFlag(DWORD flag) {
		m_dwFlag |= flag;
	};
	//FLAG�رտ���
	inline void disableFlag(DWORD flag) {
		m_dwFlag &= ~flag;
	};
	//FLAG�鿴�Ƿ�򿪿���
	inline bool isEnableFlag(DWORD flag) const {
		return m_dwFlag & flag;
	};

	//���ӳ������

	//����TAG
	void setTag(int tag);
	//�õ�TAG
	inline int getTag() const {
		return m_iTag;
	};
	
	//��������
	void setName(const GString& name);
	//�õ�����
	inline const GString& getName() const {
		return m_strName;
	};

	//�õ�����(�麯��)
	virtual GObjectType getType() const {
		return GOT_NONE;
	};

	//���ÿɼ�״̬
	inline void setVisable(bool visiable){
		m_bVisable = visiable;
	};
	//�õ��ɼ�״̬
	inline bool isVisable() const{
		return m_bVisable;
	};
	//���ÿ���״̬
	inline void setEnable(bool enable){
		m_bEnable = enable;
	};
	//�õ�����״̬
	inline bool isEnable() const{
		return m_bEnable;
	};
private:
	DWORD		m_dwFlag;					//flag����
	int			m_iTag;						//���
	GString		m_strName;					//����
	bool		m_bEnable;					//����״̬
	bool		m_bVisable;					//�ɼ�״̬
};


#pragma warning(pop)
#endif