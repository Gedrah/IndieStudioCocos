#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
 private: // variables
  cocos2d::Sprite3D* player;
  cocos2d::Vec3 playerPos;
  cocos2d::Vec3 spriteDest;
  cocos2d::Vec2 distance;
  cocos2d::Camera* camera;
  cocos2d::Vec2 clickPos;
  cocos2d::Label* labelTouch;
 public:
  // main feature to create scene
  static cocos2d::Scene* createScene();
  virtual bool init() override;


  // functions that will init datas
  void setupCamera();
  void setupCharacter();
  void setupTerrain();
  void setupTouchEvent();
  void menuCloseCallback(cocos2d::Ref* pSender);


  // touch events
  virtual bool onTouchBegan(cocos2d::Touch*, cocos2d::Event*);
  virtual void onTouchEnded(cocos2d::Touch*, cocos2d::Event*);
  virtual void onTouchMoved(cocos2d::Touch*, cocos2d::Event*);
  virtual void onTouchCancelled(cocos2d::Touch*, cocos2d::Event*);


  // refresh
  void update(float) override;

  CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
