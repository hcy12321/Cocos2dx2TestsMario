#include "LayerStart.h"
#include "LayerMenu.h"

bool LayerStart::init()
{
	CCLayer::init();
	
	CCSprite * bg = CCSprite::create("background.png");
	bg->setPosition(POINTET_HALFWINDOW);
	addChild(bg);
	CCMenu * menu = CCMenu::create();
	addChild(menu);

	CCMenuItemImage * start = CCMenuItemImage::create("startgame_normal.png", "startgame_select.png", this, menu_selector(LayerStart::Start));
	menu->addChild(start);

	CCMenuItemImage * setup = CCMenuItemImage::create("Setting_n.png", "Setting_s.png", this, menu_selector(LayerStart::Setup));
	menu->addChild(setup);

	CCMenuItemImage * quit = CCMenuItemImage::create("quitgame_normal.png", "quitgame_select.png", this, menu_selector(LayerStart::Quit));
	menu->addChild(quit);

	CCMenuItemImage * about = CCMenuItemImage::create("about_normal.png", "about_select.png", this, menu_selector(LayerStart::About));
	menu->addChild(about);
	// ÉèÖÃ°´Å¥Î»ÖÃ
	// menu->alignItemsVerticallyWithPadding(10);
	Common::moveNode(setup, ccp(0, -40));
	Common::moveNode(quit, ccp(0, -80));
	Common::moveNode(about, ccp(150, -120));

	return true;
}

void LayerStart::Start(CCObject *)
{
	CCDirector::sharedDirector()->replaceScene(Common::scene(LayerMenu::create()));
}

void LayerStart::Setup(CCObject *)
{

}

void LayerStart::Quit(CCObject *)
{

}

void LayerStart::About(CCObject *)
{

}