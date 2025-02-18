#pragma once

namespace Pad
{
	// プロトタイプ宣言

	/// <summary>
	/// パッドの入力状態更新処理
	/// 1フレームに1回のみ呼び出す
	/// </summary>
	void Update();

	/// <summary>
	/// Press判定の取得
	/// </summary>
	/// <param name="button">判定を行いたいボタン</param>
	/// <returns>押されていたらtrue,押されていなかったらfalse</returns>
	bool IsPress(int button);

	/// <summary>
	/// Trigger判定(押された瞬間)の取得
	/// </summary>
	/// <param name="button">判定を行いたいボタン</param>
	/// <returns>ボタンが押された瞬間true,それ以外はfalse</returns>
	bool IsTrigger(int button);
}