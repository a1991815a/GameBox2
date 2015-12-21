#ifndef __GRESOURCE__
#define __GRESOURCE__
#include "GameHeader.h"
#include "Ref.h"

//资源管理类
class GResource: public Ref{
public:
	GResource() {};
	virtual ~GResource() {};
private:
	GString				m_strName;			//资源名字(同时也是路径名)
};
#endif