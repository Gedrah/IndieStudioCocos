#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

class HelloWorld : public cocos2d::Scene
{
 private: // variables
  cocos2d::Sprite3D* sprite;
  cocos2d::Vec3 spritePos;
  cocos2d::Camera* camera;
 public:
  // main feature to create scene
  static cocos2d::Scene* createScene();
  virtual bool init() override;


  // functions that will
  void setupCamera();
  void setupCharacter();
  void menuCloseCallback(cocos2d::Ref* pSender);

  void update(float) override;

  CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
