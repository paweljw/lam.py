#include "effect/effect.h"
Effect * currentEffect;
#include "effect/clear.h"
#include "effect/helper.h"
#include "effect/failed.h"
#include "effect/success.h"
#include "effect/running.h"
#include "effect/coffee.h"
#include "effect/food_alert.h"

ClearEffect * clearEffect = new ClearEffect();
void runEffect(Effect * toRunEffect, Effect * fromEffect, int duration) {
  transitToEffect(fromEffect, toRunEffect, 1000);
  while(duration >= 0) {
    toRunEffect->update();

    for(byte i=0; i<strip.numPixels(); i++) {
      RGB currentColor = toRunEffect->get(i);

      strip.setPixelColor(i, strip.Color(currentColor.r, currentColor.g, currentColor.b));
    }

    strip.show();
    duration -= TICK_DELAY;
    delay(TICK_DELAY);
  }

  transitToEffect(toRunEffect, fromEffect, 1000);
}

void coffeeEffect() {
  if (!teamOnline) {
    return;
  }
  CoffeeEffect * coffeeEffect = new CoffeeEffect();
  runEffect(coffeeEffect, currentEffect, 1000);
  delete coffeeEffect;
}

void foodAlertEffect() {
  if (!teamOnline) {
    return;
  }
  FoodAlertEffect * foodAlertEffect = new FoodAlertEffect();
  runEffect(foodAlertEffect, currentEffect, 3000);
  delete foodAlertEffect;
}
