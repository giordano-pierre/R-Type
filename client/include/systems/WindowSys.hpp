/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** WindowSys
*/

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <utility>

#include "ECS/ECS.hpp"
#include "components/Configs.hpp"
#include "components/Drawable.hpp"
#include "components/Hitbox.hpp"
#include "components/Position.hpp"
#include "components/SFMLObjects.hpp"
#include "components/Selectable.hpp"
#include "components/Text.hpp"
#include "events/CaptureInputEvent.hpp"
#include "events/ChangeKey.hpp"
#include "events/FrameEvent.hpp"

namespace rtype::client {
class WindowSys {
  public:
    WindowSys(sf::VideoMode mode, const sf::String &title,
              sf::Uint32 style = 7U,
              const sf::ContextSettings &settings = sf::ContextSettings());
    ~WindowSys() = default;

    void operator()(ECS &ecs, const FrameEvent &e_frame,
                    const SparseArray<Configs> &configs,
                    const SparseArray<SFMLObjects> &SFMLObjs,
                    SparseArray<Position> &positions,
                    SparseArray<Hitbox> &hitboxs,
                    SparseArray<Drawable> &sprites, SparseArray<Text> &texts,
                    SparseArray<Selectable> &selectables);
    void operator()(ECS &ecs, const ChangeKey &e_changeK,
                    SparseArray<Configs> &configs);
    void operator()(ECS &ecs, const CaptureInputEvent &e_capture,
                    const SparseArray<Configs> &configs,
                    const SparseArray<SFMLObjects> &SFMLObjs,
                    SparseArray<Position> &positions,
                    SparseArray<Hitbox> &hitboxs,
                    SparseArray<Drawable> &sprites, SparseArray<Text> &texts,
                    SparseArray<Selectable> &selectables);

  private:
    sf::RenderWindow _window;
    sf::String _title;

    void resizeWindow(TupleUInt, bool &);
    void updateInfo(SparseArray<Position> &positions,
                    SparseArray<Hitbox> &hitboxs, bool isResize,
                    sf::Vector2u sizeClient, TupleUInt serverSize);
    void drawSprite(SparseArray<Position> &positions,
                    SparseArray<Hitbox> &hitboxs,
                    SparseArray<Drawable> &sprites, int order,
                    const Configs &myConfig, const SFMLObjects &SFMLObj);
    void drawSel(SparseArray<Position> &positions, SparseArray<Hitbox> &hitboxs,
                 SparseArray<Selectable> &selectables, const Configs &myConfig,
                 const SFMLObjects &SFMLObj);
    void drawText(SparseArray<Position> &positions,
                  SparseArray<Hitbox> &hitboxs, SparseArray<Text> &texts,
                  bool isResize, sf::Vector2u sizeClient,
                  const Configs &myConfig, const SFMLObjects &SFMLObj);
    void drawHitboxes(SparseArray<Position> &positions,
                      SparseArray<Hitbox> &hitboxs, const Configs &myConfig,
                      const SFMLObjects &SFMLObj);
    void draw(ECS &ecs, const SparseArray<Configs> &configs,
              const SparseArray<SFMLObjects> &SFMLObjs,
              SparseArray<Position> &positions, SparseArray<Hitbox> &hitboxs,
              SparseArray<Drawable> &sprites, SparseArray<Text> &texts,
              SparseArray<Selectable> &selectables);
};
} // namespace rtype::client
