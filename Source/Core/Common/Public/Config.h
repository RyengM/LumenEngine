#pragma once

namespace Lumen::Core
{
	struct Config
	{
		// Number of buffer game thread upload frame cmdlists to render thread 
		int frameBufferNum = 3;
	};
}