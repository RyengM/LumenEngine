#pragma once

namespace Lumen::Core
{
	class Runnable
	{
	public:
		virtual ~Runnable() {};

		virtual bool Init() { return true; };

		virtual void Run() = 0;

		virtual void Stop() = 0;

		virtual void Exit() = 0;
	};
}