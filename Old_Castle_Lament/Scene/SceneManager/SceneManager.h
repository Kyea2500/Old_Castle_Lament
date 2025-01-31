#pragma once
#include "../SceneTitle/SceneTitle.h"
#include "../SceneGame/SceneGame.h"
//#include "../SceneGameOver/SceneGameOver.h"
//#include"../SceneClear/SceneClear.h"
#include <memory>

class SceneTitle;
class SceneGame;
class SceneManager
{
private:

	//SceneKind m_kind�ƈȉ��̏����͓����Ӗ�����
	enum SceneKind
	{
		kSceneTitle,
		kSceneGame,
		/*kSceneGameOver,
		kSceneGameClear*/
	}Kind;

	// �e�V�[���̃|�C���^
	SceneTitle* m_pSceneTitle;
	SceneGame* m_pSceneGame;
	//std::shared_ptr<SceneTitle> m_pSceneTitle;
	//std::shared_ptr<SceneGame> m_pSceneGame;
	/*std::shared_ptr<SceneGameOver> m_pSceneGameOver;
	std::shared_ptr<SceneGameClear> m_pSceneGameClear;*/

public:
	SceneManager();
	~SceneManager();

	void Init();
	void Update();
	void Draw();
	void End();

};
