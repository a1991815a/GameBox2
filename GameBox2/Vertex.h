#ifndef __VERTEX__
#define __VERTEX__
#include <d3d9.h>
#include <d3dx9.h>

struct Vertex_p3_c1{
	Vertex_p3_c1() 
		:x(0), y(0), z(0), color(0)
	{};
	Vertex_p3_c1(float x, float y, float z, D3DCOLOR color)
		:x(x), y(y), z(z), color(color)
	{};
	float x, y, z;
	D3DCOLOR color;
	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_DIFFUSE;

	D3DXVECTOR3* getPosition() {
		return (D3DXVECTOR3*)&x;
	};

	const D3DXVECTOR3* getPosition() const {
		return (D3DXVECTOR3*)&x;
	};
};

struct Vertex_p3_n3_c1
{
	Vertex_p3_n3_c1() 
		:x(0), y(0), z(0),
		nx(0), ny(0), nz(0),
		color(0)
	{};
	Vertex_p3_n3_c1(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:x(pos->x), y(pos->y), z(pos->z), 
		nx(normal->x), ny(normal->y), nz(normal->z),
		color(color)
	{};

	float x, y, z;
	float nx, ny, nz;
	D3DCOLOR color;
	static const DWORD fvf = D3DFVF_XYZ | D3DFVF_NORMAL | D3DFVF_DIFFUSE;

	D3DXVECTOR3* getPosition() {
		return (D3DXVECTOR3*)&x;
	};

	const D3DXVECTOR3* getPosition() const {
		return (D3DXVECTOR3*)&x;
	};
};

struct Vertex_p3_n3_c1_t1 : public Vertex_p3_n3_c1 {
	Vertex_p3_n3_c1_t1() 
		:Vertex_p3_n3_c1(),
		u(0), v(0)
	{};
	Vertex_p3_n3_c1_t1(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:Vertex_p3_n3_c1(pos, normal, color),
		u(0), v(0)
	{};

	float u, v;
	static const DWORD fvf = Vertex_p3_n3_c1::fvf | D3DFVF_TEX1;

	void setUV(float u, float v) {
		this->u = u;
		this->v = v;
	};
};

struct Vertex_p3_n3_c1_t2 : public Vertex_p3_n3_c1 {

	Vertex_p3_n3_c1_t2()
		:Vertex_p3_n3_c1(),
		u1(0), v1(0), u2(0), v2(0)
	{};
	Vertex_p3_n3_c1_t2(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:Vertex_p3_n3_c1(pos, normal, color),
		u1(0), v1(0), u2(0), v2(0)
	{};

	float u1, v1;
	float u2, v2;
	static const DWORD fvf = Vertex_p3_n3_c1::fvf | D3DFVF_TEX2;
	void setUV(float u, float v) {
		u1 = u2 = u;
		v1 = v2 = v;
	};
};

struct Vertex_p3_n3_c1_t3 : public Vertex_p3_n3_c1 {

	Vertex_p3_n3_c1_t3()
		:Vertex_p3_n3_c1(),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0)
	{};
	Vertex_p3_n3_c1_t3(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:Vertex_p3_n3_c1(pos, normal, color),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0)
	{};

	float u1, v1;
	float u2, v2;
	float u3, v3;
	static const DWORD fvf = Vertex_p3_n3_c1::fvf | D3DFVF_TEX3;
	void setUV(float u, float v) {
		u1 = u2 = u3 = u;
		v1 = v2 = v3 = v;
	};
};

struct Vertex_p3_n3_c1_t4 : public Vertex_p3_n3_c1 {

	Vertex_p3_n3_c1_t4()
		:Vertex_p3_n3_c1(),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0), u4(0), v4(0)
	{};
	Vertex_p3_n3_c1_t4(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:Vertex_p3_n3_c1(pos, normal, color),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0), u4(0), v4(0)
	{};

	float u1, v1;
	float u2, v2;
	float u3, v3;
	float u4, v4;
	static const DWORD fvf = Vertex_p3_n3_c1::fvf | D3DFVF_TEX3;
	void setUV(float u, float v) {
		u1 = u2 = u3 = u4 = u;
		v1 = v2 = v3 = v4 = v;
	};
};

struct Vertex_p3_n3_c1_t5 : public Vertex_p3_n3_c1 {

	Vertex_p3_n3_c1_t5()
		:Vertex_p3_n3_c1(),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0), u4(0), v4(0), u5(0), v5(0)
	{};
	Vertex_p3_n3_c1_t5(
		const D3DXVECTOR3* pos,
		const D3DXVECTOR3* normal,
		D3DCOLOR color)
		:Vertex_p3_n3_c1(pos, normal, color),
		u1(0), v1(0), u2(0), v2(0), u3(0), v3(0), u4(0), v4(0), u5(0), v5(0)
	{};

	float u1, v1;
	float u2, v2;
	float u3, v3;
	float u4, v4;
	float u5, v5;
	static const DWORD fvf = Vertex_p3_n3_c1::fvf | D3DFVF_TEX3;
	void setUV(float u, float v) {
		u1 = u2 = u3 = u4 = u5 = u;
		v1 = v2 = v3 = v4 = v5 = v;
	};
};

#endif