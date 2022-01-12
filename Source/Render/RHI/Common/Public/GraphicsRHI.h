#pragma once

// Abstraction of concrere backend implementation
class GraphicsRHI
{
public:
	// Invoked at the start of render frame, wait for GPU fence
	virtual void NewFrame() = 0;
	// Invoked at the end of render frame, swap buffer and set a new fence point
	virtual void EndFrame() = 0;
	// Resize window buffer
	virtual void OnResize() = 0;

	// DX realted methods
	virtual bool InitDirect3D(void* hWnd) = 0;
	virtual void DrawUI(void* drawData) = 0;
	virtual void SetClientResolution(int width, int height) = 0;
	// Wait until frame commands are complete
	virtual void FlushCommandQueue() = 0;

	// UI related methods
	virtual void InitUI() = 0;
	virtual void CreateUIDeviceObject() = 0;
	
	// RHI methods

};