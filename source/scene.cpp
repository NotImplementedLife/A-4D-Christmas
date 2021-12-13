#include "scene.hpp"

#include "title_scene.hpp"
#include "credits_scene.hpp"
#include "main_scene.hpp"
#include "tutorial_scene.hpp"

Scene* next_TitleScene() { return new TitleScene(); }
Scene* next_CreditsScene() { return new CreditsScene(); }
Scene* next_MainScene() { return new MainScene(); }
Scene* next_TutorialScene() { return new TutorialScene(); }

