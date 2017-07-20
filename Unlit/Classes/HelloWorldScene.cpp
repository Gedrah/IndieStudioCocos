#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
  auto scene = Scene::create();
  auto layer = HelloWorld::create();
  scene->addChild(layer);
  return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
  setupCharacter();
  setupCamera();
  this->scheduleUpdate();
  return true;
}


/*
void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
};
  */
void HelloWorld::setupCamera()
{
  auto visibleSize = Director::getInstance()->getVisibleSize();

  this->setCameraMask((unsigned short) CameraFlag::USER2, true);
  camera = Camera::createPerspective(60,  visibleSize.width / visibleSize.height, 1.0, 1000);
  camera->setCameraFlag(CameraFlag::USER2);
  camera->setPosition3D(spritePos + Vec3(0, 200, 200));
  camera->lookAt(spritePos, Vec3(0.0, 50.0, 100.0));
  this->addChild(camera);
}

void HelloWorld::setupCharacter()
{
  // setPosition
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  spritePos = Vec3(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, 0);

  //Create sprite
  sprite = Sprite3D::create("boss.c3b");
  sprite->setPosition(0, 0);
  sprite->setScale(5.f);
  auto rotation = RotateBy::create(15, Vec3(0, 360, 0));
  sprite->runAction(RepeatForever::create(rotation));
  this->addChild(sprite);
}

void HelloWorld::update(float delta)
{
  auto position = sprite->getPosition();
  spritePos.y  = spritePos.y - 1;
  sprite->setPosition(spritePos.x, spritePos.y);
}

