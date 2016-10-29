#pragma once
class SceneManager
{
public:
	static SceneManager * instance() { return sm_instance; }
	static void initialize();
	SceneManager();

private:
	static SceneManager * sm_instance;

};