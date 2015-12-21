#ifndef __GCAMERA__
#define __GCAMERA__
#include "GObject.h"

#define UP_FIXED			0x00000100
#define LOOKMATRIX_UPDATE	0x00000200

class GCamera: public GObject{
public:
	GCamera();
	~GCamera();

	CREATEINIT_FUNC(GCamera);

	//设置摄像机位置
	void setPosition(const D3DXVECTOR3* pos);
	//设置目标位置
	void setDestination(const D3DXVECTOR3* dest);
	//设置UP轴
	void setUp(const D3DXVECTOR3* up);
	//更新摄像机矩阵
	void UpdateLookMatrix();

	//旋转
	void Rotate(float x, float y, float z);
	//旋转X轴
	void RotateX(float x);
	//旋转Y轴
	void RotateY(float y);
	//旋转Z轴
	void RotateZ(float z);
	//旋转 自定义轴
	void RotateAxis(const D3DXVECTOR3* axis, float radians);
	//平移
	void Move(float x, float y, float z);
	//平移X
	void MoveX(float x);
	//平移Y
	void MoveY(float y);
	//平移Z
	void MoveZ(float z);

	//固定Up轴
	void setFixedUp(bool flag);
	//查看Up轴是否固定
	bool isFixedUp() const;

	//得到坐标
	const D3DXVECTOR3& getPosition() const;
	//得到目标点
	const D3DXVECTOR3& getDestination() const;
	//得到Up轴
	const D3DXVECTOR3& getUp() const;

	//得到X轴
	const D3DXVECTOR3& getAxisX() const;
	//得到Y轴
	const D3DXVECTOR3& getAxisY() const;
	//得到Z轴
	const D3DXVECTOR3& getAxisZ() const;

	void SetupCamera() const;
private:
	D3DXVECTOR3		m_v3Position;
	D3DXVECTOR3		m_v3Destination;
	D3DXVECTOR3		m_v3Up;
	float			m_fDistance;
	D3DXMATRIX		m_mLookMatrixInverse;
	D3DXMATRIX		m_mLookMatrix;
};
#endif