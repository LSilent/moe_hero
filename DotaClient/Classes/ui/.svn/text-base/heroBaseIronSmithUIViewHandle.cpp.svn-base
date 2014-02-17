#include "./ui/heroBaseActivityUIView.h"
#include "./Game.h"

#include "cocos-ext.h"

#include "./event/EventSystem.h"

#include "./datapool/DataPool.h"
#include "./object/ObjectSelf.h"
#include "./object/PlayerData.h"
#include "./game/SendPacket.h"
#include "./base/UtilTools.h"
#include "./ui/element/CCMenuEx.h"
#include "element/LogicTouchItem.h"
#include "./datapool/WoodData.h"
#include "element/FightTips.h"
#include "./Packets/Wood/CGWoodAskPacket.h"
#include "heroBaseActivityUI.h"
#include "./GameResult.h"


using namespace cocos2d;
USING_NS_CC_EXT;

#define MAX_ACT_NUM				 (3)

#define CONTENT_POS_X            (0.100f)
#define CONTENT_POS_Y            (0.858f)//(0.455f)

#define CONTENT_VIEW_SIZE_X      (0.80f)
#define CONTENT_VIEW_SIZE_Y      (0.2f)

#define ITEM_SPACE_DELTA_X       (0.18f)//(0.225f)
#define ITEM_SPACE_DELTA_Y       (0.115f)//(0.127f)//(0.130f)

#define ITEM_START_X			 (0.09f) //(0.111f)
#define ITEM_START_Y             (0.06f)//(0.45f)

#define ITEM_COLUMN_NUM          4
#define ITEM_LINE_NUM            1

