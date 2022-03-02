#pragma once

#include "Retro/Core.h"

#ifdef Rtro_PLATFORM_WINDOWS
#include "Retro/Window.h"

#include <GLFW/glfw3.h>

namespace Retro
{
	class Win32Window : public Window
	{
	public:
		Win32Window(const WindowProps& props);
		virtual ~Win32Window();

		void OnUpdate() override;

		inline unsigned int GetWidth() const override { return m_Data.Width; }
		inline unsigned int GetHeight() const override { return m_Data.Height; }

		// Window attributes
		inline void SetEventCallBack(const EventCallbackFn& callback) override { m_Data.EventCallBack = callback; }
		void SetVSync(bool enabled) override;
		bool IsVSync() const override;

		inline virtual void* GetNativeWindow() const { return m_Window; }
	private:
		virtual void Init(const WindowProps& props);
		virtual void ShutDown();
	private:
		GLFWwindow* m_Window;

		struct WindowData
		{
			std::string Title;
			unsigned int Width, Height;
			bool VSync;

			EventCallbackFn EventCallBack;
		};

		WindowData m_Data;
	};
}
#endif