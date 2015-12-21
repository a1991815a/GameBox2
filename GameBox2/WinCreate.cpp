#include "GameHeader.h"
#include "RenderEngine\DXUtils.h"
#include "GSystemEngine.h"
#include "GKeyboardListener.h"
#include "GDispatchSystem.h"
#include "GMouseListener.h"
#include "GScene.h"
#include "GSceneManager.h"
#include "GSkybox.h"
#include <dinput.h>
#include "GTerrian.h"

void SceneInit();

bool WinCreate(HWND hwnd)
{
	GSystemEngine::getInstance()->InitEngine();
	GSystemEngine::getInstance()->Init();
	dxInit(hwnd);

// 	//关闭灯光
// 	dxGetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);

	SceneInit();

	return true;
};

void SceneInit(){
	//场景
	GScene* scene = GScene::create();
	_sceneManager->setCurrentScene(scene);

	//摄像机初始化
	GCamera* camera = GCamera::create();
	camera->setPosition(&D3DXVECTOR3(0, 0, -10));
	camera->setDestination(&D3DXVECTOR3(0, 0, 0));
	camera->setUp(&D3DXVECTOR3(0, 1, 0));
	scene->setCamera(camera);
	camera->setFixedUp(true);


	//天空盒初始化
	{
		GSkybox* box = GSkybox::create(50);
		box->setTexture(0, "../res/skybox/front.jpg");
		box->setTexture(1, "../res/skybox/right.jpg");
		box->setTexture(2, "../res/skybox/back.jpg");
		box->setTexture(3, "../res/skybox/left.jpg");
		box->setTexture(4, "../res/skybox/down.jpg");
		box->setTexture(5, "../res/skybox/up.jpg");
		scene->setSkybox(box);
	}
	
	//地形初始化
	{
		GTerrian* terrian = GTerrian::create(128, 128, 128, 128, 0);
		terrian->setHeightTexture("../res/terrian/map128.bmp", 20);
		terrian->setTexture(0, "../res/terrian/grass1.dds");
		scene->addDrawObject(terrian);
		terrian->attachNode(scene->getRootNode());
	}

	//添加监听
	GMouseListener* listenre = GMouseListener::create();
	listenre->OnRButtonDown = [camera](GEvent* e) {
		Point point = e->getMouseMove();
		camera->RotateY(point.x * 0.007f);
		camera->RotateX(point.y * 0.007f);
		return false;
	};
	_dispatchSystem->addListener(listenre);

	GKeyboardListener* listener2 = GKeyboardListener::create();
	listener2->OnKeyDown = [camera](GEvent* e) {
		switch (e->getLOData())
		{
		case DIK_W:
			camera->MoveZ(1);
			break;
		case DIK_S:
			camera->MoveZ(-1);
			break;
		case DIK_A:
			camera->MoveX(-1);
			break;
		case DIK_D:
			camera->MoveX(1);
			break;
		default:
			break;
		}
		return false;
	};
	_dispatchSystem->addListener(listener2);

};


