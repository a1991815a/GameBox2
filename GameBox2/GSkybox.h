#ifndef __GSKYBOX__
#define __GSKYBOX__
#include "GObjectRendable.h"
#include "GCamera.h"

class GSkybox: public GObjectRendable{
public:
	GSkybox();

	static GSkybox* create(float width);

	//��ʼ�� �߳�:width
	bool init(float width);

	virtual GObjectType getType() const override;
	virtual void Draw() override;

	//������������¾���λ��
	void UpdateMatrix(GCamera* camera);
private:
	D3DXMATRIX m_worldMatrix;							//�������()��պв�ʹ�ù���Node
};
#endif