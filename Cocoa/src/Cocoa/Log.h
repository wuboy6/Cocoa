#pragma once

#include "copch.h"

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"//支持自定义流输出


namespace Cocoa {
	class COCOA_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//Core log macros
#define CO_CORE_TRACE(...)    ::Cocoa::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define CO_CORE_INFO(...)     ::Cocoa::Log::GetCoreLogger()->info(__VA_ARGS__)
#define CO_CORE_WARN(...)     ::Cocoa::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define CO_CORE_ERROR(...)    ::Cocoa::Log::GetCoreLogger()->error(__VA_ARGS__)
#define CO_CORE_FATAL(...)    ::Cocoa::Log::GetCoreLogger()->fatal(__VA_ARGS__)

//Client log macros
#define CO_TRACE(...)         ::Cocoa::Log::GetClientLogger()->trace(__VA_ARGS__)
#define CO_INFO(...)          ::Cocoa::Log::GetClientLogger()->info(__VA_ARGS__)
#define CO_WARN(...)          ::Cocoa::Log::GetClientLogger()->warn(__VA_ARGS__)
#define CO_ERROR(...)         ::Cocoa::Log::GetClientLogger()->error(__VA_ARGS__)
#define CO_FATAL(...)         ::Cocoa::Log::GetClientLogger()->fatal(__VA_ARGS__)