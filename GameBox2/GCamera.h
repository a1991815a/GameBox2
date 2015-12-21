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

	//���������λ��
	void setPosition(const D3DXVECTOR3* pos);
	//����Ŀ��λ��
	void setDestination(const D3DXVECTOR3* dest);
	//����UP��
	void setUp(const D3DXVECTOR3* up);
	//�������������
	void UpdateLookMatrix();

	//��ת
	void Rotate(float x, float y, float z);
	//��תX��
	void RotateX(float x);
	//��תY��
	void RotateY(float y);
	//��תZ��
	void RotateZ(float z);
	//��ת �Զ�����
	void RotateAxis(const D3DXVECTOR3* axis, float radians);
	//ƽ��
	void Move(float x, float y, float z);
	//ƽ��X
	void MoveX(float x);
	//ƽ��Y
	void MoveY(float y);
	//ƽ��Z
	void MoveZ(float z);

	//�̶�Up��
	void setFixedUp(bool flag);
	//�鿴Up���Ƿ�̶�
	bool isFixedUp() const;

	//�õ�����
	const D3DXVECTOR3& getPosition() const;
	//�õ�Ŀ���
	const D3DXVECTOR3& getDestination() const;
	//�õ�Up��
	const D3DXVECTOR3& getUp() const;

	//�õ�X��
	const D3DXVECTOR3& getAxisX() const;
	//�õ�Y��
	const D3DXVECTOR3& getAxisY() const;
	//�õ�Z��
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