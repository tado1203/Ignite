#include "Module.h"

Module::Module(std::string name, std::string desc, Category cat, int keybind = 0x0, bool isEnabled = false) :
	Name(name), Description(desc), category(cat), Keybind(keybind), IsEnabled(isEnabled) {}

void Module::OnD2DRender() {}
void Module::OnImGuiRender() {}
void Module::OnUpdate() {}

void Module::Toggle()
{
	IsEnabled = !IsEnabled;
}