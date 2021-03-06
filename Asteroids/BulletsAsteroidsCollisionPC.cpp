#include "BulletsAsteroidsCollisionPC.h"
#include "Asteroid.h"
#include "Asteroids.h"
#include "AsteroidsGame.h"
#include "Bullet.h"
#include "Collisions.h"
#include "GameManager.h"
#include "Messages_defs.h"

void BulletsAsteroidsCollisionPC::update(Container* c, Uint32) {
  const auto gameManager = static_cast<GameManager*>(c);  // NOLINT

  // If the game is not running, exit immediately from the update
  if (!gameManager->isRunning()) return;

  for (auto bullet : *bullets_) {
    if (!bullet->isActive()) continue;

    for (auto asteroid : *asteroids_) {
      // If the asteroid is not active, skip
      if (!asteroid->isActive()) continue;
      // If there are no collisions, skip
      if (!Collisions::collidesWithRotation(bullet, asteroid)) continue;

      c->globalSend(this, msg::BulletAsteroidCollision(
                              msg::None, msg::Broadcast, bullet, asteroid));
    }
  }
}

void BulletsAsteroidsCollisionPC::receive(Container*, const msg::Message& msg) {
  switch (msg.type_) {
    case msg::ASTEROIDS_INFO: {
      const auto info = reinterpret_cast<const msg::AsteroidsInfo&>(msg);
      asteroids_ = info.asteroids_;
      break;
    }
    case msg::BULLETS_INFO: {
      const auto info = reinterpret_cast<const msg::BulletsInfo&>(msg);
      bullets_ = info.bullets_;
      break;
    }
    default:
      break;
  }
}
