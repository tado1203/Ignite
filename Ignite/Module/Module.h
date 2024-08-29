#pragma once
#include <string>

enum Category
{
	Visual,
	Movement
};

class Module
{
public:
	std::string Name;
	std::string Description;
	Category category;
	int Keybind;
	bool IsEnabled;

	Module(std::string name, std::string desc, Category cat, int keybind, bool isEnabled);

	virtual void OnD2DRender();
	virtual void OnImGuiRender();

	void Toggle();
};