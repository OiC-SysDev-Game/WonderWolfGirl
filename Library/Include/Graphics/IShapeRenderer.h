//#ifndef U22_GRAPHICS_ISHAPE_RENDERER_H
//#define U22_GRAPHICS_ISHAPE_RENDERER_H
//
//
//namespace u22::graphics {
//enum class ShapeRendererType {
//    LineCircle,
//    FillCircle,
//    LineRectangle,
//    FillRectangle,
//};
//class IShapeRenderer {
//private:
//public:
//    /// <summary>
//    /// コンストラクタ
//    /// </summary>
//    IShapeRenderer() = default;
//    /// <summary>
//    /// デストラクタ
//    /// </summary>
//    virtual ~IShapeRenderer() = default;
//    /// <summary>
//    /// 初期化
//    /// </summary>
//    /// <param name=""></param>
//    /// <returns></returns>
//    virtual bool Initialize(void) = 0;
//    /// <summary>
//    /// 描画
//    /// </summary>
//    /// <typeparam name="Shape"></typeparam>
//    /// <param name="shape"></param>
//    /// <param name="color"></param>
//    /// <param name="camera"></param>
//    /// <returns></returns>
//    template<typename Shape>
//    bool Render(const Shape& shape, const u22::math::Vector4F& color, const u22::graphics::Camera& camera) const {
//        return true;
//    }
//};
//}
//#endif // !U22_GRAPHICS_ISHAPE_RENDERER_H