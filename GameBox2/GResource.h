#ifndef __GRESOURCE__
#define __GRESOURCE__
#include "GameHeader.h"
#include "Ref.h"

//��Դ������
class GResource: public Ref{
public:
	GResource() {};
	virtual ~GResource() {};
private:
	GString				m_strName;			//��Դ����(ͬʱҲ��·����)
};
#endif