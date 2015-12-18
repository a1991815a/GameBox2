#ifndef __GAMEHEADER__
#define __GAMEHEADER__
/***************************/
#include <windows.h>
#include <functional>
#include <stdexcept>
#include <d3d9.h>
#include <d3dx9.h>
#include <string>

/*******************************/
//��ѧģ�ͼ�����ģ��
#include "Math/Size.h"
#include "nocopy.h"
//�ڴ��������
#include "Container/Map.hpp"
#include "Container/Vector.hpp"
#include "Container/Set.h"
//���ݽṹ
#include "DataStruct/ObjectPool.hpp"
#include "DataStruct/GQuadTree.h"
#include "DataStruct/GString.h"
//�ص�����
#include "GCALLBACK.h"
//����
#include "SingleInstance.h"
//DEBUG����
#include "DebugUtils.h"


/************************************************************************/
//�궨��
#include "GameMacro.h"

#endif