#include "GCamera.h"
#include "RenderEngine\DXUtils.h"
D3DXVECTOR3		m_v3Position;
D3DXVECTOR3		m_v3Destination;
D3DXVECTOR3		m_v3Up;
float			m_fDistance;
D3DXMATRIX		m_mLookMatrixInverse;
D3DXMATRIX		m_mLookMatrix;

GCamera::GCamera()
	:m_v3Position(0, 0, 0), m_v3Destination(0, 0, 0), m_v3Up(0, 1, 0),
	m_fDistance(10), 
	m_mLookMatrixInverse(*dxGetUnitMatrix()),
	m_mLookMatrix(*dxGetUnitMatrix())
{

}

GCamera::~GCamera()
{

}

void GCamera::setPosition(const D3DXVECTOR3* pos)
{
	m_v3Position = *pos;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::setDestination(const D3DXVECTOR3* dest)
{
	D3DXVECTOR3 direction = *dest - m_v3Position;
	m_fDistance = D3DXVec3Length(&direction);
	D3DXVec3Normalize(&direction, &direction);
	m_v3Destination = m_v3Position + direction;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::setUp(const D3DXVECTOR3* up)
{
	m_v3Up = *up;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::UpdateLookMatrix()
{
	if (!isEnableFlag(LOOKMATRIX_UPDATE))
		return;

	D3DXMatrixLookAtLH(&m_mLookMatrix, &m_v3Position, &m_v3Destination, &m_v3Up);
	D3DXMatrixInverse(&m_mLookMatrixInverse, nullptr, &m_mLookMatrix);
	disableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::Rotate(float x, float y, float z)
{
	D3DXMATRIX matrix;
	D3DXMATRIX mMatrix;
	D3DXVECTOR3 direction = m_v3Destination - m_v3Position;

	D3DXMatrixRotationAxis(&matrix, &getAxisY(), y);
	D3DXMatrixRotationAxis(&mMatrix, &getAxisX(), x);
	mMatrix = mMatrix * matrix;
	D3DXMatrixRotationAxis(&matrix, &getAxisZ(), z);
	mMatrix = mMatrix * matrix;

	D3DXVec3TransformNormal(&direction, &direction, &mMatrix);
	m_v3Destination = m_v3Position + direction;

	if (!isFixedUp())
		D3DXVec3TransformNormal(&m_v3Up, &m_v3Up, &mMatrix);
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::RotateX(float x)
{
	D3DXVECTOR3 direction = m_v3Destination - m_v3Position;
	if(isFixedUp())
	{
		float angle = dxVec3Angle(&direction, &m_v3Up) + x;
		if (angle <= 0.0001f || angle >= D3DX_PI - 0.0001f)
			return;
	}

	D3DXMATRIX matrix;
	D3DXMatrixRotationAxis(&matrix, &getAxisX(), x);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	m_v3Destination = m_v3Position + direction;
	if (!isFixedUp())
		D3DXVec3TransformNormal(&m_v3Up, &m_v3Up, &matrix);
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::RotateY(float y)
{
	D3DXMATRIX matrix;
	D3DXVECTOR3 direction = m_v3Destination - m_v3Position;
	D3DXMatrixRotationAxis(&matrix, &getAxisY(), y);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	m_v3Destination = m_v3Position + direction;
	if (!isFixedUp())
		D3DXVec3TransformNormal(&m_v3Up, &m_v3Up, &matrix);
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::RotateZ(float z)
{
	D3DXMATRIX matrix;
	D3DXVECTOR3 direction = m_v3Destination - m_v3Position;
	D3DXMatrixRotationAxis(&matrix, &getAxisZ(), z);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	m_v3Destination = m_v3Position + direction;
	if (!isFixedUp())
		D3DXVec3TransformNormal(&m_v3Up, &m_v3Up, &matrix);
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::RotateAxis(const D3DXVECTOR3* axis, float radians)
{
	D3DXMATRIX matrix;
	D3DXVECTOR3 direction = m_v3Destination - m_v3Position;
	D3DXMatrixRotationAxis(&matrix, axis, radians);
	D3DXVec3TransformNormal(&direction, &direction, &matrix);
	m_v3Destination = m_v3Position + direction;
	if (!isFixedUp())
		D3DXVec3TransformNormal(&m_v3Up, &m_v3Up, &matrix);
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::Move(float x, float y, float z)
{
	D3DXVECTOR3 vec = 
		x * getAxisX() + y * getAxisY() + z * getAxisZ();
	m_v3Position += vec;
	m_v3Destination += vec;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::MoveX(float x)
{
	D3DXVECTOR3 vec = x * getAxisX();
	m_v3Position += vec;
	m_v3Destination += vec;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::MoveY(float y)
{
	D3DXVECTOR3 vec = y * getAxisY();
	m_v3Position += vec;
	m_v3Destination += vec;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::MoveZ(float z)
{
	D3DXVECTOR3 vec = z * getAxisZ();
	m_v3Position += vec;
	m_v3Destination += vec;
	enableFlag(LOOKMATRIX_UPDATE);
}

void GCamera::setFixedUp(bool flag)
{
	if (flag)
		enableFlag(UP_FIXED);
	else
		disableFlag(UP_FIXED);
}

bool GCamera::isFixedUp() const
{
	return isEnableFlag(UP_FIXED);
}

const D3DXVECTOR3& GCamera::getPosition() const
{
	return m_v3Position;
}

const D3DXVECTOR3& GCamera::getDestination() const
{
	return m_v3Destination;
}

const D3DXVECTOR3& GCamera::getUp() const
{
	return m_v3Up;
}

const D3DXVECTOR3& GCamera::getAxisX() const
{
	return *(D3DXVECTOR3*)m_mLookMatrixInverse.m[0];
}

const D3DXVECTOR3& GCamera::getAxisY() const
{
	return *(D3DXVECTOR3*)m_mLookMatrixInverse.m[1];
}

const D3DXVECTOR3& GCamera::getAxisZ() const
{
	return *(D3DXVECTOR3*)m_mLookMatrixInverse.m[2];
}

void GCamera::SetupCamera() const
{
	dxSetView(&m_mLookMatrix);
}
