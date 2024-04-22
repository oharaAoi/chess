#pragma once

enum SceneNum {
	SCENE_TITLE,
	SCENE_SELECT,
	SCENE_GAME,
};

class Base_Scene {

protected:

	static int sceneNo_;
	static SceneNum  keepSceneNo_;

	static bool isSceneChange_;

public:

	virtual ~Base_Scene() {};

	virtual void Init() = 0;
	virtual void Update() = 0;
	virtual void Draw() = 0;

	static void SetSceneNo(SceneNum num) { sceneNo_ = num; }
	static int GetSceneNo() { return sceneNo_; }

	static void SetKeepSceneNo(SceneNum num) { keepSceneNo_ = num; }
	static SceneNum  GetKeepSceneNo() { return  keepSceneNo_; }
};