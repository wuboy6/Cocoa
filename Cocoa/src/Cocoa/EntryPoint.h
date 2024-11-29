#pragma once

#ifdef  CO_PLATEFORM_WINDOWS

#include "Log.h"

extern Cocoa::Application* Cocoa::CreateApplication();

int main(int argc,char** argv)
{
	Cocoa::Log::Init();
	CO_CORE_TRACE("Welcome to Coco Engine!");
	CO_CORE_WARN("Initialized Log!");
	const char* name = "Coco";
	CO_INFO("Hello! User: {0}",name);

	auto app = Cocoa::CreateApplication();
	app->Run();
	delete app;
}

#endif //  CO_PLATEFORM_WINDOWS


#include "Core.h"

