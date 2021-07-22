/**
* @file SpriteAnimationController.h
* @brief 2Dのアニメーション
* @details 得られる矩形は描画時に使用する
*/


#ifndef U22_ANIMATION_SPRITE_MOTION_CONTROLLER_H
#define U22_ANIMATION_SPRITE_MOTION_CONTROLLER_H


#include <string>
#include <vector>
#include <unordered_map>

#include "../Shape/Rectangle.h"
#include "SpriteAnimationCreate.h"


namespace u22::animation {
/// <summary>
/// アニメーション管理クラス
/// </summary>
class SpriteAnimationController {
private:
    //!
	//! 時間
    //!
	float _ideal_frame_time;
	//!
	//! 終了
	//!
	bool _motion_end;
	//! 時間
	float _time;
	//!
	//! 番号
	//!
	uint32_t _current_motion_no;
	//!
	//! 番号
	//!
	uint32_t _current_pattern_no;
	//!
	//! 表示矩形
	//!
	u22::shape::Rectangle _source_rectangle;
	//!
	//! 現在
	//!
	u22::animation::SpriteAnimationCreate* _current_aniamtion;
	//!
	//! アニメーションデータ
	//!
	std::unordered_map<int, u22::animation::SpriteAnimationCreate> _animations;
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	SpriteAnimationController();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~SpriteAnimationController();
	/// <summary>
	/// セッター
	/// </summary>
	/// <param name="loop">フラグ</param>
	void SetMotionLoop(bool loop);
	/// <summary>
	/// ゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns>現在のモーション番号</returns>
	int GetMotionNo(void) const;
	/// <summary>
	/// ゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns>モーションの種類の数</returns>
	std::uint32_t GetMotionCount(void) const;
	/// <summary>
	/// ゲッター
	/// </summary>
	/// <param name=""></param>
	/// <returns>描画矩形</returns>
	u22::shape::Rectangle GetSourceRectangle(void) const;
	/// <summary>
	/// 判定
	/// </summary>
	/// <param name=""></param>
	/// <returns>終了</returns>
	bool IsEndMotion(void) const;
	/// <summary>
	/// 更新
	/// </summary>
	/// <param name="time">時間</param>
	/// <returns>成功</returns>
	bool AddTimer(float time);
	/// <summary>
	/// 変更
	/// </summary>
	/// <param name="no"モーション番号></param>
	/// <returns>成功</returns>
	bool ChangeMotion(int no);
	/// <summary>
	/// 変更
	/// </summary>
	/// <param name="name">モーション名</param>
	/// <returns>成功</returns>
	bool ChangeMotion(const std::string& name);
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="data">生成情報</param>
	/// <param name="size">要素数</param>
	/// <returns></returns>
	bool Create(u22::animation::SpriteAnimationCreate* data, int size);
	/// <summary>
	/// 作成
	/// </summary>
	/// <param name="data">生成情報</param>
	/// <param name="size">要素数</param>
	/// <returns></returns>
	bool Create(const std::vector<u22::animation::SpriteAnimationCreate>& data, int size);
	/// <summary>
	/// 解放
	/// </summary>
	/// <param name=""></param>
	/// <returns>成功</returns>
	bool Release(void);
};
}
#endif // !U22_ANIMATION_SPRITE_MOTION_CONTROLLER_H