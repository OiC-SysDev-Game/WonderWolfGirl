/**
 * @file U22.h
 * @brief 各機能の一括インクルード
 *        使いやすいようにエイリアス宣言する
 * @author name
 * @date 2021/07/09
 */


#include "Framework/FrameworkInclude.h"
#include "Math/MathInclude.h"
#include "Shape/ShapeInclude.h"
#include "Collision/CollisionInclude.h"
#include "Clock/Clock.h"
#include "Input/InputInclude.h"
#include "Graphics/GraphicsInclude.h"
#include "Audio/AudioInclude.h"
#include "Animation/AnimationInclude.h"
#include "Utility/UtilityInclude.h"


/** @def
 * フレームワーク情報のポインタ取得
 */
#define g_pFramework (u22::Framework::GetInfomation())
/** @def
 * フレームワークが持つ時間のポインタ取得
 */
#define g_pClock (u22::Framework::GetInfomation()->clock)
/** @def
 * フレームワークが持つウインドウのポインタ取得
 */
#define g_pWindow (u22::Framework::GetInfomation()->window)
/** @def
 * フレームワークが持つ入力のポインタ取得
 */
#define g_pInput (u22::Framework::GetInfomation()->input)
/** @def
 * フレームワークが持つグラフィックスのポインタ取得
 */
#define g_pGraphics (u22::Framework::GetInfomation()->graphics)
/** @def
 * フレームワークが持つオーディオのポインタ取得
 */
#define g_pAidio (u22::Framework::GetInfomation()->aidio)


using namespace u22::utility;
using namespace u22::animation;

//!
//! 入力時に引数として使う
//!
using Keycode = u22::input::KeyCode;
//!
//! 入力時に引数として使う
//!
using MouseButton = u22::input::MouseButton;
//!
//! 要素2のベクトル
//!
using Vector2 = u22::math::Vector2F;
//!
//! 要素3のベクトル
//!
using Vector3 = u22::math::Vector3F;
//!
//! 要素4のベクトル
//!
using Vector4 = u22::math::Vector4F;
//!
//! ゲームカメラ
//!
using CCamera = u22::graphics::Camera;
//!
//! テクスチャクラス、描画機能を持つ
//!
using CTexture = u22::graphics::TextureRenderer;
//!
//! フォントクラス、描画機能を持つ
//!
using CFont = u22::graphics::FontRenderer;
//!
//! スプライト用のアニメーション
//!
using CSpriteAnimationController = u22::animation::SpriteAnimationController;
//!
//! SE用のサウンド
//!
using CSoundBuffer = u22::audio::SoundBuffer;
//!
//! BGM用のサウンド
//!
using CSoundStreamBuffer = u22::audio::SoundStreamBuffer;
//!
//! 円クラス、衝突機能を持つ
//!
using CCircle = u22::collision::CollisionableCircle;
//!
//! 矩形クラス、衝突機能を持つ
//!
using CRectangle = u22::collision::CollisionableRectangle;