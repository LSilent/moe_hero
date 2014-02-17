#ifndef __DATABASEDEFINE_H__
#define __DATABASEDEFINE_H__

#include "./base/Global.h"

enum DATABASE_FILE_ID
{
	DBC_FILE_HERO_ATTR = 1,
	DBC_FILE_ATTRIBUTE_DATA,
	DBC_FILE_COMMON_ITEM,
	DBC_FILE_EQUIP_ITEM,
	DBC_FILE_GEM_ITEM,
	DBC_FILE_EQUIP_STRENGTHEN,
	DBC_FILE_HERO_RECRUIT,
	DBC_FILE_IMPACT,
	DBC_FILE_ITEM_RULER,
	DBC_FILE_MONSTER,
	DBC_FILE_QUEST_ITEM,
	DBC_FILE_SKILL,
	DBC_FILE_HERO_EXP,
	DBC_FILE_HUMAN_EXP,
	DBC_FILE_UI,
	DBC_FILE_UIMUTEX,
	DBC_FILE_HEROQUALITY,
	DBC_FILE_SHOP,
	DBC_FILE_FIGHTMONSTER,
	DBC_FILE_DROPBOX,
	DBC_FILE_EQUIP_MANUFACTURE,
	DBC_FILR_COPYSCENE,
	DBC_FILR_COPYSCENE_GROUP,
	DBC_FILR_SACRIFICE,
	DBC_FILR_SACRIFICE_AWARD,
	DBC_FILE_LANG,
	DBC_FILE_GIFT_PACKET,
	DBC_FILE_FILTER,
	DBC_FILE_CHESS,
	DBC_FILE_CHESSBONUS,
	DBC_FILE_HUODONG,
	DBC_FILE_EATCHEESE,
	DBC_FILE_COPYSCENEHUODONG,
	DBC_FILE_BUYBEARPOINT,
	DBC_FILE_CHARGE,
	DBC_FILE_EQUIPGUIDE,
 	DBC_FILE_HERO_EQUIP_RECOMMEND,
	DBC_FILE_ACHIEVE,
	DBC_FILE_GUIDE,
	DBC_FILE_BUYACTIONPOINT,
	DBC_FILE_QUEST,
	DBC_FILE_SELECT_SERVER,
	DBC_FILE_HERO_COLOR,
	DBC_FILE_WOOD,
	DBC_FILE_EXCHANGE,
	DBC_FILE_CONFIG,
	DBC_FILE_QUJING,
	DBC_FILE_STAIRPLUS,
	DBC_FILE_STAIRBONUS,
	DBC_FILE_ACHIEVE_GROUP,
	DBC_FILE_ACCELERATE,
	DBC_FILE_PLACARD,
	
	
};
//HeroAttr.tab
struct stDBC_FILE_HERO_ATTR
{
	//英雄id
	X_INT _id;
	//魂魄
	X_INT _spiritID;
	X_CHAR* _name;  //英雄名字
	X_INT _professional;//职业
	X_INT _quality;
	X_INT _initlevel;
	X_INT _levelLimit;//等级上限
	X_INT _levelUpPlayer;
	X_INT _exp;
	X_INT _takeLevel;//可以携带等级
	X_INT _growupEffectAttack;
	X_INT _growupEffectDefense;
	X_INT _growupEffectHP;
	X_INT _growupEffectMP;

	X_INT _levelEffectAttack;
	X_INT _levelEffectDefense;
	X_INT _levelEffectHP;
	X_INT _levelEffectMP;

	X_INT _attackSpeed;
	X_INT _attack;
	X_INT _magicAttack;
	X_INT _defense;
	X_INT _magicDefense;
	X_INT _hp;
	X_INT _mp;  
	X_INT _hit;
	X_INT _dodge;
	X_INT _crit;
	X_INT _batter;//连击值
	X_INT _fightBack;//反击值
	X_INT _critHurt;//暴击伤害
	X_INT _batterNum;//连击次数
	X_INT _batterHurt;//连击伤害
	X_INT _fightBackHurt;	//反击伤害
	X_INT _reduce;//物理减免
	X_INT _magicReduce;//魔法减免
	X_INT _randomhurt;//英雄浮动伤害
	X_INT _normalskill;
	X_INT _skill1;
	X_INT _skill1Level;
	X_INT _skill2;
	X_INT _skill2Level;
	X_INT _growupLimit;//成长值上限
	X_INT _burden; //初始负重
	X_INT _levelEffecBurden;//承载力随等级的增长系数
	X_CHAR *_icon;
	X_CHAR *_sound;
};
 //AttributeData.tab
struct stDBC_FILE_ATTRIBUTE_DATA
{
	X_INT _id;
	X_CHAR* _desc;
};
 //
struct stDBC_FILE_COMMON_ITEM
{
	X_INT	_id;
	X_CHAR *_name;
	X_CHAR *_color;
	X_CHAR *_icon;
	X_CHAR *_typeTip;
	X_CHAR *_infoTip;
	X_CHAR *_commentary;
	X_INT    _class;
	X_INT    _type;
	X_INT    _index;
	X_INT    _heroLevel;
	X_INT    _exp;
	X_INT	 _skillLevelUpRate;
	X_INT    _skillDoubleGroup;
	X_INT    _layerNum;
	X_INT    _buyPrice;
	X_INT    _saleType;
	X_INT    _salePrice;
	X_INT	 _rule;
	X_INT    _script;
	X_INT    _broadcastId;
};
const int EQUIP_MAX_ATTR_NUM = 4;
struct stItem_Attr
{
	X_INT _id;;
	X_INT _value;
};

struct stDBC_FILE_EQUIP_ITEM
{
		 
	X_INT	_id;
	X_CHAR *_name;
	X_CHAR *_color;
	X_CHAR *_infoTip;
	X_CHAR *_icon;
	X_INT	_heroLevel;//等级需求
	X_INT	_weight;	//装备重量			
	X_INT	_equipPoint;//装备点
	X_INT	_attack;//物理攻击
	X_INT	_defense;
	X_INT	_hp;
	X_INT	_mp;
	stItem_Attr _attr[EQUIP_MAX_ATTR_NUM];
	X_INT   _triggerSkillType;
	X_INT   _triggerSkillId;
	X_INT   _triggerSkillCd;
	X_INT   _triggerSkillRate;
	X_INT   _buyPrice;
	X_INT   _saleType;
	X_INT   _salePrice;
	X_INT	_rule;
	X_INT   _profession;
	X_INT    _broadcastId;
	X_INT    _script;
	X_INT   _levelUpNeed;
	X_INT    _peifangid;
	X_INT    _dropid;
	X_INT   _level;
	X_INT  _canlevelup;

};
const int GEM_MAX_ATTR = 3;

struct stGemMixture
{
	X_INT id;
	X_INT num;
};
const int GEM_MAX_MIXTURE = 3;
struct  stDBC_FILE_GEM_ITEM
{
	X_INT	_id;
	X_CHAR *_name;
	X_CHAR *_color;
	X_CHAR *_icon;
	X_INT	_gemtype;
	X_CHAR *_typeTip;
	X_CHAR *_infoTip;
	X_CHAR *_commentary;//注释
	X_INT    _class;
	X_INT    _type;
	X_INT    _index;
	X_INT    _heroLevel;
	X_INT    _layerNum;
	X_INT    _buyPrice;
	X_INT    _saleType;
	X_INT    _salePrice;
	X_INT	 _rule;
	stItem_Attr _attr[GEM_MAX_ATTR];
	stGemMixture _gems[GEM_MAX_MIXTURE];
	X_INT	 _fragment;
	X_INT    _script;
	X_INT    _broadcastId;
};

struct  stDBC_FILE_EQUIP_STRENGTHEN
{
	X_INT _level;
	X_INT _rate;
	X_INT _lpunishment;//失败惩罚
	X_INT _money;
	X_INT _levelRequest;//等级需求
	X_INT _levelIronsmith;//铁匠铺等级需求
	X_CHAR* _effect;
	X_INT    _broadcastId;
};

//HeroRecruit.tab
struct stDBC_FILE_HERO_RECRUIT
{
	X_INT _posId;
	X_INT _costValue;
};
//Impact.tab
struct stDBC_FILE_IMPACT
{
	X_INT _id;
	X_CHAR *commentary;
	X_INT _logicId;
	X_INT _param[4];
	X_CHAR * _icon;
	X_INT _mutexID;//互斥id
	X_INT _priority;
	X_INT _deadDisappear;
	X_INT _offlineTiming;
	X_INT _script;
	X_CHAR *_info;//无效
	X_CHAR *_name;
	X_CHAR *_desc;
	X_CHAR *_effect;//技能效果
	X_CHAR * _hitEffect;//技能受击效果
	float _sacle;//技能缩放
	float _x;//技能效果x
	float _y;//技能效果y	
	X_CHAR * _sound;//技能音效
	float _hitScale;//受击缩放
	float _hitEffectX;//受击x		
	float _hitEffectY;//受击y
	X_CHAR *_hitSound;//受击音效
	float speed;
	float hitspeed;
	X_INT entire;//全体或者单人
};
//ItemRuler
struct stDBC_FILE_ITEM_RULER
{
	X_INT _id;
	X_CHAR *_name;
	X_INT _discard;
	X_INT _sale;
	X_INT _canUsed;
	X_INT _consume; //是否消耗
	X_INT _getBind;
	X_INT _useBind;
	X_INT _Unique;
	X_INT _warehouse;
};
const X_INT MONSTER_TAKE_HERO = 6;
struct  stDBC_FILE_MONSTER
{
	X_INT _id;
	X_CHAR* _name;
	X_CHAR* _commentary;
	X_CHAR *_model;
	X_INT  _heros[MONSTER_TAKE_HERO];
	X_INT _drop;
};
//QuestItem.tab
struct  stDBC_FILE_QUEST_ITEM
{
	X_INT	_id;
	X_CHAR *_name;
	X_CHAR *_color;
	X_CHAR *_icon;
	X_CHAR *_typeTip;
	X_CHAR *_infoTip;
	X_CHAR *_desc;
	X_INT    _class;
	X_INT    _type;
	X_INT    _index;
	X_INT    _layerNum;
	X_INT	 _rule;
	X_INT    _broadcastId;
	X_INT    _script;
};

const X_INT SKILL_ADD_IMPACT = 4;
struct stSkill_Impact
{
	X_INT _id;
	X_INT _rate;
	X_INT _targetType;

};
//Skill.tab
/*四、技能升级
	技能最大等级MAX_SKILL_LEVEL 改为7级（与4级）

	修改表skill.tab：在列“学习成功率”前 增加4列。
	注：学习类型为0时，表示以前的技能学习；（走commonitem）
	学习类型为1时，表示现在的技能学习；（利用新配置的列：道具消耗id，与道具消耗数量*/
struct stDBC_FILE_SKILL
{
	X_INT _id;
	X_CHAR *_commentary;
	X_CHAR *_name;
	X_INT _level;
	X_CHAR *_desc;
	X_INT _target;
	X_INT _triggerRate;
	X_INT _costMp;
	X_INT _cd;
	X_INT _cdID;
	X_INT _first;
	X_INT _type;
	stSkill_Impact _impact[SKILL_ADD_IMPACT];
	X_INT    _script;
	X_INT _heroLevel;
	X_INT _costMoney;
	X_INT _learntype;
	X_CHAR *items;
	X_CHAR *itemsnum;
	X_INT _costwood;
	X_INT _LearnRate;
	X_INT _effectRateItem;
	X_INT _effectRate;
	X_INT _effectItemNum;
	X_INT _handUpAction;
	X_CHAR *_effect;
	X_CHAR *_effectHit;
	X_CHAR *_icon;
	X_INT	_castPostion;//技能施放位置（0为原地，1为到某一列前，2为到目标前，3为到敌方整体区域）
	X_INT	_hitAction;
	X_CHAR *_casteffect;
	X_INT  _effectType;//特效的类型（0为只有受击，1为点对点，2为发射物体击中目标消失，3为向固定方向发射物体，4为一个区域的大特效）
	float  _ShotEffectScale;// 施放特效缩放比例
	float	_ShotEffectX;//施放特效x偏移量
	float	_ShotEffecty;//施放特效y偏移量
	X_CHAR*	_ShotEffectSound;//施放特效声音
	float	_effectScale;//本体特效缩放比例
	float	_effectX;//本体特效x偏移量
	float	_effectY;//本体特效y偏移量
	float	_effectSpeed;//本体特效速度
	X_CHAR*	_effectSound;//本体特效声音
	float	_hitEffectScale;//受击特效缩放比例
	float	_hitEffectX;//受击特效x偏移量
	float	_hitEffectY;//受击特效y偏移量
	X_CHAR*	_hitEffectSound;//受击特效声音
	float   shotplaySpeeds;
	float   playSpeeds;
	float   hitplaySpeeds;
	
	float   shotoffsetX;
	float   shotoffsetY;
	float   hitoffsetX;
	float   hitoffsetY;
	
};
struct  stDBC_FILE_HERO_EXP
{
	X_INT level;
	X_INT exp;
	X_INT BearPoint[EM_HERO_QUALITY_TYPE6];
};
struct  stDBC_FILE_HUMAN_EXP
{
	X_INT level;
	X_INT exp;
	X_INT siteEXP;

};

struct  stDBC_FILE_UI
{
	X_INT id;
	X_CHAR* name;
	X_INT mutexGroupId;

};
 
//UIMutexTable.tab
//每个界面属于0-9中的一个组，ui组之间存在互斥关系
const  X_INT MAX_MUTEX_GROUP = 10;
struct stDBC_FILE_UIMUTEX
{
	X_INT	   m_GroupId;						//组id
	X_INT      m_MutexGroup[MAX_MUTEX_GROUP];	// 界面组 0-9
};

struct stDBC_FILE_HEROQUALITY
{
	X_INT id;
	X_CHAR *name;
	X_INT BearPointNeed;
	X_INT BearPoint;
	X_INT costItemNum;
};

const X_INT MAX_SHOP_ITEM = 30;

struct stSHOP_ITEM
{
	X_INT id;
	X_INT num;
	X_INT numLimit;
	X_INT price;
	X_INT floatPrice;
	X_CHAR *buyCondition;
	X_CHAR *buyValue;
};

struct stDBC_FILE_SHOP
{
	X_INT id;
	X_CHAR *name;
	X_INT type;
	X_CHAR *info;
	X_INT floatPrice;
	X_INT moneyType;
	X_INT scriptid;
	X_INT timeFresh;
	X_INT freshTime;
	X_INT floatPricetimeBegin;
	X_INT floatPricetimeBeginEnd;
	stSHOP_ITEM items[MAX_SHOP_ITEM];
};
struct stDBC_FILE_FIGHTMONSTER
{
	X_INT _id;
	X_CHAR* _name;  //英雄名字
	X_INT _professional;//职业
	X_INT _quality;
	X_INT _initlevel;

	X_INT _attackSpeed;
	X_INT _attack;
	X_INT _magicAttack;
	X_INT _defense;
	X_INT _magicDefense;
	X_INT _hp;
	X_INT _mp;
	X_INT _hit; //命中
	X_INT _dodge;//闪避
	X_INT _crit;//暴击
	X_INT _batter;//连击值
	X_INT _fightBack;//反击值
	X_INT _critHurt;//暴击伤害
	X_INT _batterNum;//连击次数
	X_INT _batterHurt;//连击伤害
	X_INT _fightBackHurt;	//反击伤害
	X_INT _reduce;//物理减免
	X_INT _magicReduce;//魔法减免
	X_INT _randomhurt;//英雄浮动伤害
	X_INT _normalskill;
	X_INT _skill1;
	X_INT _skill2;
	X_CHAR *_icon;
};
struct stDBC_FILE_DROPBOX
{
	//掉落包ID	名称	说明	概率分母	物品ID(最多5个)	物品分子	元宝	元宝分子
	X_INT id;
	X_CHAR *name;
	X_CHAR *info;
	X_INT rate;
	X_CHAR *items;
	X_CHAR *itemsRate;
	X_INT  gold;
	X_INT  goldRate;
};

struct  ItemMaterial
{
	X_INT id;
	X_INT num;

};
const X_INT MAX_MATERIAL_NUM = 5;
struct stDBC_FILE_EQUIP_MANUFACTURE
{
	X_INT id;
	X_CHAR * name;
	X_INT itemID;
	ItemMaterial items[MAX_MATERIAL_NUM];
	X_INT wood;//消耗木材数量
	X_INT type;
};
struct  stDBC_FILR_COPYSCENE
{
	X_INT id;
	X_CHAR *name;
	X_CHAR *info;
	X_INT type;
	X_INT _preScene;
	X_INT _nextScene;
	X_INT _group;
	X_INT _costAction;
	X_INT _challengeNum;
	X_INT _recommendLevel;
	X_INT _exp;
	X_INT _heroExp;
	X_INT _rewardGold;
	X_INT _monsterId;
	X_CHAR* _icon;
	X_CHAR* _dropInfo;
	X_CHAR* _battleScene;
	X_INT _refreshCost;
};
struct  stDBC_FILR_COPYSCENE_GROUP
{
	X_INT id;
	X_CHAR* name;
	X_CHAR* info;
	X_INT preGroup;
	X_CHAR* scenes; 
};
struct  SACRIFICE_ITEM
{
	X_CHAR * items;
	X_CHAR * rates;

};
const X_INT MAX_AWARD_SACRIFICE_ITEM = 5; 
struct stDBC_FILR_SACRIFICE
{
	X_INT id;
	X_INT openLevel;  //开启等级
 	X_INT effectsill;//显灵阀值
	X_INT costgold;//消耗元宝
	X_INT costItem;
	X_INT constItemNum;
	X_INT killedRate;//击杀概率
	X_INT hurt_s;//最小伤害
	X_INT hurt_m;//最大伤害
	X_INT dropNum;//掉落次数
	X_INT award0;
	X_INT award1;
};
struct stDBC_FILR_SACRIFICE_AWARD
{
	SACRIFICE_ITEM awards[MAX_AWARD_SACRIFICE_ITEM];
};
struct stDBC_FILE_LANG
{
	X_INT id;
	X_CHAR * world;
	X_INT  show;

};

struct stDBC_FILE_GIFT_PACKET
{
	X_INT id;
	X_INT type;
	X_CHAR *info;
	X_INT gold;
	X_INT exp;
	X_INT action;
	X_CHAR *items1;
	X_CHAR *items2;
	X_INT wood;
};

struct stDBC_FILE_FILTER
{
	X_INT id;
	X_CHAR *text;

};

struct stDBC_FILE_CHESS
{
	X_INT id;
	X_INT steps;//总步数
	X_INT start_step;
	X_INT end_step;
	X_INT constAction;//色子消耗rest

	X_INT passGiftId;//通关BOSS礼包


};
struct stDBC_FILE_CHESSBONUS
{
	X_INT stepid;
	X_INT restPonit;
	X_INT award_exp;
	X_INT award_action;
	X_INT item;
	X_INT advanceStep;
	X_INT recedeStep;
	X_INT triggerMonster;
	X_CHAR * icon;
	X_CHAR * tips;
};

struct stDBC_FILE_HUODONG
{
	X_INT id;
	X_CHAR* name;
	X_CHAR* openDay;//开放日期
	X_CHAR* opentime;//开放时间
	X_INT   time;//持续时间
	X_INT   type;
	X_INT   openLevel;
};
struct  stDBC_FILE_EATCHEESE
{
	X_INT id;
	X_CHAR* name;
	X_INT level;
	X_INT actionpoint;
};
struct stDBC_FILE_COPYSCENEHUODONG
{
	X_INT id;
	X_CHAR* name;
	X_INT level;
	X_INT copySceneId;
};
struct stDBC_FILE_BUYBEARPOINT
{
	X_INT id;
	X_INT cost;
	X_INT level;
	X_INT bearPoint;
};

struct stDBC_FILE_CHARGE
{
	X_INT id;
	X_INT gold;
	X_INT costMoney;//
	X_CHAR* des; 
	X_CHAR* name;
	X_INT starttime;
	X_INT endtime;
	X_INT backdays;
	X_INT backGold;
    X_CHAR* Productid;
	X_CHAR* Productid91;
	X_CHAR* icon;

};
const X_INT MAX_EQUIP_FIND = 8;
struct stDBC_FILE_EQUIPGUIDE
{
	X_INT id;
	X_INT equip[MAX_EQUIP_FIND];
	 
};
const X_INT MAX_EQUIP_RECOMMEND = 5;
struct stDBC_FILE_HERO_EQUIP_RECOMMEND
{
	X_INT id;
	X_INT heroid;
	X_INT equip[MAX_EQUIP_RECOMMEND];
};
struct stDBC_FILE_ACHIEVE_GROUP
{
	X_INT id;
	X_CHAR *icon;
	X_CHAR *text;
	X_CHAR *name;
	X_CHAR * group;
	X_CHAR *textBig;
};
struct stDBC_FILE_ACHIEVE
{
	X_INT id;
	X_CHAR *name;
	X_CHAR *icon;
	X_INT group;
	X_INT preId;
	X_INT nextId;
	X_INT type;
	X_INT param1;
	X_INT param2;
	X_INT gold;
	X_CHAR *item;
	X_CHAR *itemnum;
	X_INT bearAward;
	X_CHAR *desc;
	X_INT startTime;
	X_INT endTime;
};

struct stDBC_FILE_GUIDE
{
	X_INT  id;
	X_INT  group;
	X_INT  groupflag;
	X_CHAR* desc;//
	X_CHAR* tipPic;
	X_INT  direction;
	X_CHAR* ui;
	X_FLOAT offsetX;
	X_FLOAT offsetY;
	X_INT guideLevel;
};

struct stDBC_FILE_BUYACTIONPOINT
{
	X_INT id;
	X_INT cost;
	X_INT level;
	X_INT addAction;
};

struct stDBC_FILE_QUEST
{
	X_INT id;
	X_INT copyscene;
	X_INT num;
	X_CHAR *desc;
	X_CHAR * icon;
	X_INT awardgold;
	X_INT awardAction;
	X_CHAR * item;
	X_CHAR * itemNum;
};
struct stDBC_FILE_SELECT_SERVER
{
	X_INT id;
	X_CHAR* name;
	X_CHAR* ip;
	X_INT port;
	X_INT open;
	X_CHAR* upDataIp;
	X_INT states;

};
struct stDBC_FILE_HERO_COLOR
{
	X_INT id;
	X_CHAR* name;
	X_INT bear;
	X_CHAR* color;
	X_CHAR* framecolor;
	X_CHAR* fightercolor;
	X_CHAR* evolvecolor;
};
struct stDBC_FILE_WOOD
{
	X_INT id;
	X_INT product;
	X_INT needLevel;
	X_INT spendMoney;
	X_INT spendTime;
	X_INT total;
	X_INT heroid;

};
struct stDBC_FILE_EXCHANGE
{
	//编号	兑换数量	兑换类型 （1,2）金币或者木材	消耗宝石	说明	名称
	X_INT id;
	X_INT num;
	X_INT type; // 1为金币2为木材
	X_INT costGem;
	X_CHAR *desc;
	X_CHAR *name;
	X_CHAR *icon;
};
struct stDBC_FILE_CONFIG
{
	X_INT id;
	X_CHAR* name;
	X_INT   m_value;
	X_CHAR* desc;
};
struct stDBC_FILE_QUJING
{
	X_INT id;
	X_INT level;
	X_CHAR* name;
	X_CHAR* color;
	X_CHAR  *visual;
	X_INT  time;
	X_INT  exp;
	X_INT  wood;
	X_INT  rate;
	X_INT  failed;
	X_INT  upCost;
	X_INT  LJLimit;
	X_INT  lostGoldPer;
	X_INT  lostWoodPer;
	X_INT  speedUp1;
	X_INT  speedUp2;
	X_INT  awardRate;
	X_CHAR* time1;
	X_CHAR* time2;
	X_CHAR* time3;
	X_INT  speeduptime;
	X_CHAR  *visual_action;
};
struct  stDBC_FILE_STAIRPLUS
{
	X_INT id;
	X_INT addType;//加成类型
	X_INT percent;//加成百分比	
	X_INT cost;//消耗积分

};
struct stDBC_FILE_STAIRBONUS
{
	X_INT layer;
	X_CHAR* item;
	X_CHAR* itemRate;
	X_INT exp;
};

struct stDBC_FILE_ACCELERATE
{
	X_INT  Id;
	char* icon;
	X_FLOAT speed;
	X_INT openLevel;
};
struct stDBC_FILE_PLACARD
{
	X_INT  Id;
	char* img;
};
#endif