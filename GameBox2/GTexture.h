#ifndef __GTEXTURE__
#define __GTEXTURE__
#include "GResource.h"

class GTexture: public GResource{
public:
	GTexture();
	~GTexture();

	//����ͼƬ���Դ�
	void LoadTexture(const char* path);
	//����ͼƬ���ڴ�
	void LoadTextureInSysmen(const char* path);
	//����ͼƬ
	void Attach(IDirect3DTexture9* texture);
	//ж��ͼƬ
	void Deattach();
	//�õ�ͼƬ
	IDirect3DTexture9* getTexture() const;

	//����UV������������ɫ
	D3DCOLOR getColor(float u, float v);
private:
	IDirect3DTexture9*		m_pTexture;
	Size					m_Size;
};
#endif