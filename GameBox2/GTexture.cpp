#include "GTexture.h"
#include "RenderEngine\DXUtils.h"

#pragma warning(push)
#pragma warning(disable: 4244)


GTexture::GTexture()
	:m_pTexture(nullptr)
{

}

GTexture::~GTexture()
{
	SAFE_RELEASE_COM(m_pTexture);
}

void GTexture::LoadTexture(const char* path)
{
	Deattach();
	D3DXIMAGE_INFO info = { 0 };

	D3DXCreateTextureFromFileExA(
		dxGetDevice(),
		path,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_DEFAULT,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		&info,
		nullptr,
		&m_pTexture
		);
	GTHROW_RUNTIME(m_pTexture, "LoadImage: failure!");
	m_Size.width = info.Width;
	m_Size.height = info.Height;
}

void GTexture::LoadTextureInSysmen( const char* path )
{
	Deattach();
	D3DXIMAGE_INFO info = { 0 };

	D3DXCreateTextureFromFileExA(
		dxGetDevice(),
		path,
		D3DX_DEFAULT_NONPOW2, D3DX_DEFAULT_NONPOW2,
		0, 0,
		D3DFMT_A8R8G8B8,
		D3DPOOL_SYSTEMMEM,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		D3DCOLOR_ARGB(0, 0, 0, 0),
		&info,
		nullptr,
		&m_pTexture
		);
	GTHROW_RUNTIME(m_pTexture, "LoadImage: failure!");
	m_Size.width = info.Width;
	m_Size.height = info.Height;
}

void GTexture::Attach(IDirect3DTexture9* texture)
{
	Deattach();
	m_pTexture = texture;
}

void GTexture::Deattach()
{
	SAFE_RELEASE_COM(m_pTexture);
}

IDirect3DTexture9* GTexture::getTexture() const
{
	if (this == nullptr)
		return nullptr;
	return m_pTexture;
}

D3DCOLOR GTexture::getColor( float u, float v )
{
	//³¬³ö·¶Î§
	if(u < 0 || v < 0 || u > 1.0f || v > 1.0f)
		return D3DCOLOR_ARGB(0, 0, 0, 0);

	size_t x = u * m_Size.width;
	size_t y = v * m_Size.height;

	D3DCOLOR retColor = D3DCOLOR_ARGB(0, 0, 0, 0);
	D3DCOLOR* colorPtr = nullptr;
	D3DLOCKED_RECT lockRect = { 0 };
	m_pTexture->LockRect(0, &lockRect, nullptr, D3DLOCK_READONLY);

	colorPtr = (D3DCOLOR*)lockRect.pBits;
	GMOVE_POINTER(colorPtr, y * lockRect.Pitch + x * sizeof(D3DCOLOR));
	retColor = *colorPtr;
	m_pTexture->UnlockRect(0);

	return retColor;
}

#pragma warning(pop)