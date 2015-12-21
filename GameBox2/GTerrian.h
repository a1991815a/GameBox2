#ifndef __GTERRIAN__
#define __GTERRIAN__
#include "GObjectRendable.h"

#define TERRIAN_TEXSIZE 3

class GTerrian: public GObjectRendable{
public:
	GTerrian();

	static GTerrian* create(float width, float depth, size_t wCount, size_t dCount, float height);

	//��ʼ������(���,���, ��ȷ���, �߶ȷ����� �߶�)
	bool Init(float width, float depth, size_t wCount, size_t dCount, float height);
	virtual void Draw();
	virtual GObjectType getType() const override;

	//���ø߶�ͼ
	void setHeightTexture(const GString& heightTexture, float MaxHeight);
private:
	float	m_fWidth, m_fDepth, m_fHeight;
	size_t	m_wCount, m_dCount;
	float	m_fMaxHeight;

	
};
#endif