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
//数学模型及其他模型
#include "Math/Size.h"
#include "nocopy.h"
//内存管理容器
#include "Container/Map.hpp"
#include "Container/Vector.hpp"
#include "Container/Set.h"
//数据结构
#include "DataStruct/ObjectPool.hpp"
#include "DataStruct/GQuadTree.h"
#include "DataStruct/GString.h"
//回调函数
#include "GCALLBACK.h"
//单例
#include "SingleInstance.h"
//DEBUG工具
#include "DebugUtils.h"


/************************************************************************/
//宏定义
#include "GameMacro.h"

#endif