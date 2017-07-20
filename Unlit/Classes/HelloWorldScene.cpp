#include "HelloWorldScene.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    return HelloWorld::create();
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Scene::init() )
    {
        return false;
    }

    setupCamera();


  auto visibleSize = Director::getInstance()->getVisibleSize();
  Vec2 origin = Director::getInstance()->getVisibleOrigin();

    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(getDefaultCamera()->getPosition().x, getDefaultCamera()->getPosition().y);

    this->addChild(menu, 1);


    setupCharacter();


    auto label = Label::createWithTTF("Ma Window", "fonts/Marker Felt.ttf", 24);
    
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    this->addChild(label, 2);

    return true;
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    Director::getInstance()->end();
}
  
void HelloWorld::setupCamera()
{

  auto sprite = Sprite3D::create("boss.c3b"); //c3b file, created with the FBX-converter
  auto rotation = RotateBy::create(15, Vec3(0, 360, 0));
  sprite->setScale(5.f); //sets the object scale in float
  sprite->runAction(RepeatForever::create(rotation));
  this->addChild(sprite); //adds sprite to scene, z-index: 1

  Vec2 origin = Director::getInstance()->getVisibleOrigin();

  auto visibleSize = Director::getInstance()->getVisibleSize();
  auto spritePos = Vec3(visibleSize.width/2 + origin.x,
			visibleSize.height/2 + origin.y,
			0);
  sprite->setPosition(spritePos.x, spritePos.y);
  this->setCameraMask((unsigned short) CameraFlag::USER2, true);
  auto camera = Camera::createPerspective(60,  visibleSize.width /
					      visibleSize.height, 1.0, 1000);
  camera->setCameraFlag(CameraFlag::USER2);
  //the calling order matters, we should first call setPosition3D, then call lookAt.
  camera->setPosition3D(spritePos + Vec3(0, 400, 200));
  camera->lookAt(spritePos, Vec3(0.0, 10.0, 1.0));
  this->addChild(camera);
}

void HelloWorld::setupCharacter()
{

}
