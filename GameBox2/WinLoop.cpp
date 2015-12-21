#include "GameHeader.h"
#include "RenderEngine\DXUtils.h"
#include "GTimerSystem.h"
#include "GInputSystem.h"
#include "GDispatchSystem.h"
#include "MemorySystem.h"
#include "GSkybox.h"
#include "GCamera.h"
#include "GTerrian.h"
#include "GSceneManager.h"

#define CUBE_LEN 2.0f

ID3DXMesh* pMesh = nullptr;

D3DXMATRIX finalMatrix[2] = {*dxGetUnitMatrix(), *dxGetUnitMatrix()};

D3DXVECTOR3 local_position(0, 0, 0);
D3DXVECTOR3 local_rotation(0, 0, 0);

D3DXVECTOR3 parent_position(0, 0, 0);
D3DXVECTOR3 parent_rotation(0, 0, 0);

D3DXVECTOR3 world_position(0, 0, 0);
D3DXVECTOR3 world_rotation(0, 0, 0);

D3DXMATRIX localMatrix = *dxGetUnitMatrix();
D3DXMATRIX parentMatrix = *dxGetUnitMatrix();
D3DXMATRIX worldMatrix = *dxGetUnitMatrix();

GCamera* camera = nullptr;

Vertex_p3_c1 vertex[8] = {
	Vertex_p3_c1(-CUBE_LEN, -CUBE_LEN, -CUBE_LEN, D3DCOLOR_XRGB(255, 0, 0)),
	Vertex_p3_c1(CUBE_LEN, -CUBE_LEN, -CUBE_LEN, D3DCOLOR_XRGB(0, 255, 0)),
	Vertex_p3_c1(-CUBE_LEN, CUBE_LEN, -CUBE_LEN, D3DCOLOR_XRGB(0, 0, 255)),
	Vertex_p3_c1(CUBE_LEN, CUBE_LEN, -CUBE_LEN, D3DCOLOR_XRGB(255, 255, 0)),

	Vertex_p3_c1(-CUBE_LEN, -CUBE_LEN, CUBE_LEN, D3DCOLOR_XRGB(255, 0, 255)),
	Vertex_p3_c1(CUBE_LEN, -CUBE_LEN, CUBE_LEN, D3DCOLOR_XRGB(0, 255, 255)),
	Vertex_p3_c1(-CUBE_LEN, CUBE_LEN, CUBE_LEN, D3DCOLOR_XRGB(125, 80, 220)),
	Vertex_p3_c1(CUBE_LEN, CUBE_LEN, CUBE_LEN, D3DCOLOR_XRGB(50, 220, 80)),
};

WORD indexs[36] = {
	0, 2, 1, 1, 2, 3,
	4, 0, 5, 5, 0, 1,
	5, 1, 7, 7, 1, 3,
	7, 3, 6, 6, 3, 2,
	6, 2, 4, 4, 2, 0,
	6, 4, 7, 7, 4, 5
};

void WinLoop(){
	_timerSystem->Loop();
	_inputSystem->Loop();
	_dispatchSystem->Loop();
	_sceneManager->Loop();
	_memorySystem->Loop();
	

	dxEndScene();
};