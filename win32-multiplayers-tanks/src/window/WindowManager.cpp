#include "WindowManager.h"

namespace core { namespace window {

	WindowManager& WindowManager::getInstance()
	{
		static WindowManager instance;
		return instance;
	}

	void WindowManager::add_window(Window* window)
	{
		list.push_back(window);
	}

	void WindowManager::close_window(const HWND& window)
	{
		for (size_t i = 0; i < list.size(); ++i)
		{
			if (list[i]->get_hwnd() == window)
			{
				list[i]->close();
				list.erase(list.begin() + i);
				break;
			}
		}
	}
}}