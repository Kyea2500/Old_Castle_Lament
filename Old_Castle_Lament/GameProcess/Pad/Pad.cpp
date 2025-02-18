#include "Pad.h"
#include "DxLib.h"

namespace
{
	int padInput = 0;  // 現在のフレームのパッド入力
	int lastInput = 0; // ひとつ前のフレームのパッド入力
}

namespace Pad
{
	void Update()
	{
		// 前のフレームに押されていたボタンの情報を覚えておく
		lastInput = padInput;
		// 個のフレームに押されているボタンの情報を取得する
		padInput = GetJoypadInputState(DX_INPUT_KEY_PAD1);
	}
#if false
	// Press判定の取得
	// 戻り値:押されていたらtrue,押されていなかったらfalse
	// 引数:判定を行いたいボタン
	bool IsPress(int button)
	{
		if (padInput & button)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	// Trigger判定の取得
	bool Pad::IsTrigger(int button)
	{
		// そもそも現在のフレームにボタンが押されていない
		if (!(padInput & button))
		{
			return false;
		}

		// ここまで処理が来たということは
		// このフレームにボタンが押されてはいる

		// 前のフレームにボタンが押されていなければTriggerと判定できる
		if (lastInput & button)
		{
			return false;
		}
		else
		{
			// 前のフレームに押されていなくて
			// 現在のフレームに押されているということは
			// このフレームが押されてた瞬間
			return true;
		}
	}
#else
	bool IsPress(int button)
	{
		return (padInput & button);
	}

	bool IsTrigger(int button)
	{
		// (padInput & button) == 0の場合false
		// それ以外の場合はtrueが入る
		bool isNow = (padInput & button);
		bool isLast = (lastInput & button);
		return (isNow && !isLast);
	}
#endif
}