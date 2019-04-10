#include "GunIC.h"
#include "InputHandler.h"
#include "Messages_defs.h"

GunIC::GunIC(const SDL_Keycode key) : key_(key) {}
GunIC::~GunIC() = default;

void GunIC::handleInput(Container* c, Uint32 time) {
  if (!InputHandler::getInstance()->isKeyDown(key_)) return;

  const auto p =
      c->getPosition() + Vector2D(c->getWidth() / 2.0, c->getHeight() / 2.0) +
      Vector2D(0.0, -(c->getHeight() / 2.0 + 5.0)).rotate(c->getRotation());
  const auto d = Vector2D(0, -1).rotate(c->getRotation());
  c->globalSend(this, msg::Shoot(msg::BulletsShooter, msg::Broadcast, p, d, 0));
}
