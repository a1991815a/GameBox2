#ifndef __GSKYBOX__
#define __GSKYBOX__
#include "GObjectRendable.h"
#include "GCamera.h"

class GSkybox: public GObjectRendable{
public:
	GSkybox();

	static GSkybox* create(float width);

	//初始化 边长:width
	bool init(float width);

	virtual GObjectType getType() const override;
	virtual void Draw() override;

	//根据摄像机更新矩阵位置
	void UpdateMatrix(GCamera* camera);
private:
	D3DXMATRIX m_worldMatrix;							//世界矩阵()天空盒不使用挂载Node
};
#endif