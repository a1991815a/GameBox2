#include "GSystemEngine.h"
#include "GTimerSystem.h"



GSystemEngine::GSystemEngine()
{}

GSystemEngine::~GSystemEngine()
{}

void GSystemEngine::InitEngine()
{
	addSystem(_timerSystem);
}

void GSystemEngine::Init()
{
	auto itor = m_pSystemVector.begin();
	for (; itor != m_pSystemVector.end(); ++itor)
	{
		GSystem* system = *itor;
		system->Init();
		LOG_D("启动子系统: %s", system->getSysName().c_str());
	}
}

void GSystemEngine::Destroy()
{
	auto itor = m_pSystemVector.rbegin();
	for (; itor != m_pSystemVector.rend(); ++itor)
	{
		GSystem* system = *itor;
		system->Destroy();
		LOG_D("销毁子系统: %s", system->getSysName().c_str());
	}
	m_pSystemVector.clear();
}

void GSystemEngine::addSystem( GSystem* system )
{
	m_pSystemVector.insert(system);
}

void GSystemEngine::removeSystem( GSystem* system )
{
	auto itor = m_pSystemVector.find(system);
	if(itor != m_pSystemVector.end())
	{
		(*itor)->Destroy();
		m_pSystemVector.erase(itor);
	}
}
