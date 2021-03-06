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
  setupTouchEvent();
  setupCharacter();
  setupTerrain();
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
  camera->setPosition3D(playerPos + Vec3(0, 200, 200));
  camera->lookAt(playerPos, Vec3(0.0, 360, 180));
  camera->setAnchorPoint(Vec2(playerPos.x, playerPos.y));
  this->addChild(camera);
}

void HelloWorld::setupCharacter()
{
  // setPosition
  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();
  playerPos = Vec3(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y, 0);

  // Create player
  player = Sprite3D::create("girl.c3b");
  player->setPosition(0, 0);
  player->setScale(0.8f);
  //auto rotation = RotateBy::create(15, Vec3(0, 360, 0));
  //player->runAction(RepeatForever::create(rotation));


  // handle movement and update
  auto listener = cocos2d::EventListenerKeyboard::create();
  listener->onKeyPressed = [=](cocos2d:: EventKeyboard::KeyCode code, cocos2d::Event * event)->void{
	camera->setPosition3D(playerPos + Vec3(-250, 50, 150));
  };

  // handle animation
  auto animation = Animation3D::create("girl.c3b","Take 001");
    if (animation)
    {
        auto animate = Animate3D::create(animation);
        player->runAction(RepeatForever::create(animate));
    }

  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
  this->addChild(player);
}

void HelloWorld::update(float delta)
{
  /*
  auto position = player->getPosition();
  playerPos.y  = playerPos.y + 1;
  player->setPosition(playerPos.x, playerPos.y);
   */
}

bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
  return true;
}

void HelloWorld::onTouchEnded(cocos2d::Touch *touch, cocos2d::Event *event)
{
  auto location = touch->getLocation();
  Vec3 nearP(location.x, location.y, 0.0f), farP(location.x, location.y, 1.0f);
  /*

        // convert screen touch location to the world location on near and far plane                                                                                                          
        auto size = Director::getInstance()->getWinSize();
        camera->unprojectGL(size, &nearP, &nearP);
        camera->unprojectGL(size, &farP, &farP);
        Vec3 dir = farP - nearP;
        dir.normalize();
        Vec3 collisionPoint;
        bool isInTerrain = _terrain->getIntersectionPoint(Ray(nearP, dir), collisionPoint);
        if (!isInTerrain)
        {
            player->idle();
        }
        else
        {
            dir = collisionPoint - player->getPosition3D();
            dir.y = 0;
            dir.normalize();
            player->_headingAngle =  -1 * acos(dir.dot(Vec3(0,0,-1)));
            dir.cross(dir,Vec3(0,0,-1),&player->_headingAxis);
            player->_targetPos=collisionPoint;
            player->forward();
        }
  */
    event->stopPropagation();
  cocos2d::log("touch ended");
}

void HelloWorld::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
  cocos2d::log("touch moved");

}

void HelloWorld::onTouchCancelled(cocos2d::Touch *touch, cocos2d::Event *event)
{
  cocos2d::log("touch cancelled");
}

void HelloWorld::setupTouchEvent()
{
  auto touchListener = EventListenerTouchOneByOne::create();
  labelTouch = Label::create();
  labelTouch->setPosition(Vec2(0, 0));


   // add event
  touchListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
  touchListener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
  touchListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
  touchListener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);

  this->_eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener,this);
  this->addChild(labelTouch);
}

void HelloWorld::setupTerrain()
{
  Terrain::DetailMap r("dirt.jpg");
  Terrain::DetailMap g("Grass1.jpg");
  Terrain::DetailMap b("road.png");
  Terrain::DetailMap a("GreenSkin.jpg");
  Terrain::TerrainData data("heightmap129.jpg","alphamap.png", r, g, b, a, Size(50,50),40.0f,2);
  auto _terrain = Terrain::create(data, Terrain::CrackFixedType::INCREASE_LOWER);
  _terrain->setLODDistance(64,128,192);

  this->addChild(_terrain);
}
