#ifndef __GTERRIAN__
#define __GTERRIAN__
#include "GObjectRendable.h"

#define TERRIAN_TEXSIZE 3

class GTerrian: public GObjectRendable{
public:
	GTerrian();

	static GTerrian* create(float width, float depth, size_t wCount, size_t dCount, float height);

	//初始化地形(宽度,深度, 宽度份数, 高度份数， 高度)
	bool Init(float width, float depth, size_t wCount, size_t dCount, float height);
	virtual void Draw();
	virtual GObjectType getType() const override;

	//设置高度图
	void setHeightTexture(const GString& heightTexture, float MaxHeight);
private:
	float	m_fWidth, m_fDepth, m_fHeight;
	size_t	m_wCount, m_dCount;
	float	m_fMaxHeight;

	
};
#endif