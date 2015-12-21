#ifndef __GTEXTURE__
#define __GTEXTURE__
#include "GResource.h"

class GTexture: public GResource{
public:
	GTexture();
	~GTexture();

	//读入图片到显存
	void LoadTexture(const char* path);
	//读入图片到内存
	void LoadTextureInSysmen(const char* path);
	//挂在图片
	void Attach(IDirect3DTexture9* texture);
	//卸载图片
	void Deattach();
	//得到图片
	IDirect3DTexture9* getTexture() const;

	//根据UV纹理坐标获得颜色
	D3DCOLOR getColor(float u, float v);
private:
	IDirect3DTexture9*		m_pTexture;
	Size					m_Size;
};
#endif