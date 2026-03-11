#include <Geode/Geode.hpp>
#include <Geode/modify/PlayLayer.hpp>
#include <Geode/modify/CCDirector.hpp>

using namespace geode::prelude;

// -------------------------------------------------------
//  ScrollClicker — Geode 5.3.0 / GD 2.2081
//  Hooks CCDirector::scrollWheel to inject click events
//  while the player is inside a level.
// -------------------------------------------------------

class $modify(ScrollClickerDirector, CCDirector) {
    // scrollWheel(deltaX, deltaY) is called by Cocos whenever the
    // mouse wheel moves.  deltaY > 0 == scroll up, deltaY < 0 == scroll down.
    void scrollWheel(float x, float y) override {
        // Always let the original handler run first so menus still scroll.
        CCDirector::scrollWheel(x, y);

        auto* pl = PlayLayer::get();
        if (!pl) return; // not in a level

        // Setting: only trigger while actually playing (not dead/paused)
        if (Mod::get()->getSettingValue<bool>("only-in-level")) {
            // m_isPracticeMode is fine to enter; we just skip if the layer
            // itself is not "running" (i.e. during the end screen, etc.)
            if (!pl->m_player1) return;
        }

        bool scrollUpEnabled   = Mod::get()->getSettingValue<bool>("scroll-up-clicks");
        bool scrollDownEnabled = Mod::get()->getSettingValue<bool>("scroll-down-clicks");
        bool bothDirs          = Mod::get()->getSettingValue<bool>("click-both-directions");

        // y > 0  →  scrolled UP
        // y < 0  →  scrolled DOWN
        if (y > 0.f && scrollUpEnabled) {
            pushClick(pl, true);
            if (!bothDirs) scheduleRelease(pl);
        } else if (y < 0.f && scrollDownEnabled) {
            pushClick(pl, true);
            if (!bothDirs) scheduleRelease(pl);
        }
    }

private:
    // Simulate a player press via GJBaseGameLayer::handleButton
    // button 1 = jump / primary action
    static void pushClick(PlayLayer* pl, bool p2 = false) {
        // handleButton(bool hold, int button, bool player1)
        pl->handleButton(true,  1, true);   // player 1 press
    }

    // Release one frame later so it reads as a tap, not a held key
    static void scheduleRelease(PlayLayer* pl) {
        pl->scheduleOnce([](float) {
            auto* p = PlayLayer::get();
            if (p) p->handleButton(false, 1, true);
        }, 0.f, "scroll_release");
    }
};

// -------------------------------------------------------
//  Two-player support: also fire player 2 when dual mode
// -------------------------------------------------------
class $modify(ScrollClickerPlayLayer, PlayLayer) {
    struct Fields {
        bool scrollActive = false;
    };

    // Override update so we can track dual-player state if needed.
    // (Currently a stub — extend here for P2 scroll support.)
    void update(float dt) override {
        PlayLayer::update(dt);
    }
};
