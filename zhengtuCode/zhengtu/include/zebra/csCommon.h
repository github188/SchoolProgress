
#pragma once
#ifndef _INC_CSCOMMON_H_
#define _INC_CSCOMMON_H_

#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1

/**
 * \brief 定义空的指令
 *
 * 负责服务器内部交换使用，和客户端交互的指令需要另外定义
 * 
 */


/**
 * \brief 定义基本类型
 *
 * 
 */
//#define _MSGPARSE_

#define _X86
#define BGDWIN32
#define XMD_H
#define __LCC__
 
#include <config.h>
#include <version.h>
#include <winsock2.h>
#include <windows.h>
#include <time.h>

#ifdef HAVE_STRINGS_H
#include <string>
#endif //HAVE_STRINGS_H

#ifdef ZEBRA_RELEASE
#include <epesdk.h>
#else //ZEBRA_RELEASE
//#include <openssl/rc5.h>
#define MINI_RC5
#endif //ZEBRA_RELEASE

#include <miniCrypt.h>

#define __CAT(x)    #x

#define SAFE_DELETE(x) { if (NULL != x) { delete (x); (x) = NULL; } }
#define SAFE_DELETE_VEC(x) { if (NULL != x) { delete [] (x); (x) = NULL; } }

/**
 * \brief 双字节符号整数
 *
 */
typedef signed short SWORD;

/**
 * \brief 四字节符号整数
 *
 */
typedef long int SDWORD;

#ifdef _MSC_VER

typedef unsigned __int64 QWORD;
typedef signed __int64 SQWORD;

#else //_MSC_VER

/**
 * \brief 八字节无符号整数
 *
 */
typedef unsigned long long QWORD;

/**
 * \brief 八字节符号整数
 *
 */
typedef signed long long SQWORD;

#endif //_MSC_VER

/**
 * \brief 名字的最大长度
 */
#define MAX_NAMESIZE 32

/**
 * \brief 账号最大长度
 */
#define MAX_ACCNAMESIZE  48

/**
 * \brief IP地址最大长度
 *
 */
#define MAX_IP_LENGTH  16

/**
 * \brief 网关最大容纳用户数目
 *
 */
#define MAX_GATEWAYUSER 4000  

/**
 * \brief 密码最大长度
 *
 */
#define MAX_PASSWORD  16

/**
 * \brief 屏宽
 */
#define SCREEN_WIDTH 13

/**
 * \brief 屏高
 */
#define SCREEN_HEIGHT 19

/**
* \brief sky 最大孔数量
*/
#define SOCKET_MAXNUM	6

//[Shx Add] 商店广告
#define MAX_SHOPADV		32

//sky 战场国家的特殊判断ID
#define BATTLEFIELD_SCENE_ID	100

/**
 * \brief 连接线程池的状态标记位
 *
 */
enum{
  state_none    =  0,          /**< 空的状态 */
  state_maintain  =  1            /**< 维护中，暂时不允许建立新的连接 */
};

#define MAX_CHATINFO  256

/**
 * \brief 数字密码
 */
#define MAX_NUMPASSWORD  32

//sky 队伍最大人数
#define MAX_TEAM_NUM	10

//Shx 套装最大组成部分数
#define MAX_SUIT_NUM	10

//sky 队员离线或者跨场景状态
#define MEMBER_BEING_OFF 0xffffffff

//sky ROLL选择的等待时间(秒级)
#define ROLL_MAX_TIME	60

/**
 * \brief 性别
 */
enum
{
  MALE  = 0,
  FEMALE  = 1
};

/**
 * \brief 五行属性
 */
enum
{
  FIVE_METAL = 0,    /// 金
  FIVE_WOOD = 1,    /// 木
  FIVE_SOIL = 2,    /// 土
  FIVE_WATER = 3,    /// 水
  FIVE_FIRE = 4,    /// 火
  FIVE_NONE = 5      /// 无
};

//sky 前期保持兼容(后期去掉)
enum
{
	PROFESSION_NONE = 0,
	PROFESSION_1	= 1,    //侠客
	PROFESSION_2	= 2,    //侠女
	PROFESSION_3	= 3,    //箭侠
	PROFESSION_4	= 4,    //箭灵
	PROFESSION_5	= 5,    //天师
	PROFESSION_6	= 6,    //美女
	PROFESSION_7	= 7,    //法师
	PROFESSION_8	= 8,    //仙女
};

// sky 新的职业枚举
enum
{
  JOB_NULL		= 0,		//无业
  JOB_FIGHTER	= 1,		//战士
  JOB_THIEVES	= 2,		//盗贼
  JOB_MASTER	= 3,		//法师
  JOB_PASTOR	= 4,		//牧师
};
// sky end

#define ZEBRA_CLIENT_VERSION    20060807

inline void mymemcpy(void* pDst, DWORD dwDstSize, void* pScr, DWORD dwCpSize )
{
	if(dwCpSize>dwDstSize)
	{
		MessageBox(NULL,"内存操作将越界","错误",MB_ICONERROR);
	}
	memcpy_s(pDst,dwDstSize,pScr,dwCpSize);
}

#define memcpy(d,s,size,dsize) mymemcpy((void*)(d),dsize,(void*)(s),size)

#ifndef HAVE_BZERO
#define bzero(p,s)      memset(p,0,s)
#define bcopy(s,d,ss,ds) memcpy(d,s,ss,ds)
#endif //HAVE_BZERO

class CEncrypt
{
public:
  CEncrypt();
  enum encMethod
  {
    ENCDEC_NONE,
    ENCDEC_DES,
    ENCDEC_RC5
  };
  void random_key_des(ZES_cblock *ret);
  void set_key_des(const_ZES_cblock *key);
  void set_key_rc5(const BYTE *data,int nLen,int rounds);
  int encdec(void *data,DWORD nLen,bool enc);

  void setEncMethod(encMethod method);
  encMethod getEncMethod() const;

private:
  void ZES_random_key(ZES_cblock *ret);
  void ZES_set_key(const_ZES_cblock *key,ZES_key_schedule *schedule);
  void ZES_encrypt1(ZES_LONG *data,ZES_key_schedule *ks,int enc);

  void RC5_32_set_key(RC5_32_KEY *key,int len,const BYTE *data,int rounds);
  void RC5_32_encrypt(RC5_32_INT *d,RC5_32_KEY *key);
  void RC5_32_decrypt(RC5_32_INT *d,RC5_32_KEY *key);

  int encdec_des(BYTE *data,DWORD nLen,bool enc);
  int encdec_rc5(BYTE *data,DWORD nLen,bool enc);

  ZES_key_schedule key_des;
  RC5_32_KEY key_rc5;
  bool haveKey_des;
  bool haveKey_rc5;

  encMethod method;

};

/**
 * \brief 定义家族的基本结构
 *
 */
#pragma pack(1)

namespace SeptDef
{

//#define DWORD CREATE_SEPT_NEED_ITEM_ID    = 0  // 建立家族所需要的道具ID 为0表示不需要
const DWORD CREATE_SEPT_NEED_PRICE_GOLD = 10;  // 建立家族需要金钱20两
const DWORD CREATE_SEPT_NEED_LEVEL     = 1;  // 建立家族需要的人物等级
const DWORD JOIN_SEPT_NEED_LEVEL    = 1;  // 加入家族需要的人物等级
const DWORD PER_LEVEL_MAN_NUM    = 100;    // 每级别增加人数
const DWORD DESTROYTIME          = 60;// 30*24*60*60; //投票有效期 一个月的秒数
const DWORD  CREATE_SEPT_NEED_MAN_NUM = 15;    // 建立家族
    
struct stSeptInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD    dwSeptID;                    // 家族的ID
  char    name[MAX_NAMESIZE+1];       // 家族名称
  DWORD    dwCharID;                   // 会长的角色ID
  char    masterName[MAX_NAMESIZE+1];    // 会长的名字
  BYTE    byVote;          // 投票标志为1表示处于投票期间
  DWORD    dwCrTime;        // 家族创立时间
  DWORD     dwRepute;        // 声望
  DWORD     dwCountryID;        // 家族所属国家（以族长国籍为根据）
  DWORD     dwUnionID;        // 家族所属帮会
  DWORD     dwLevel;        // 家族等级
  DWORD     dwSpendGold;        // 家族消费金币
  DWORD     dwIsExp;        // 是否领取家族经验
  char    note[254+1];        // 家族介绍
  DWORD    calltimes;        // 令牌使用次数
  DWORD    calldaytime;        // 令牌使用天数
  DWORD    normalexptime;        // 令牌使用天数
  char		ExterData[512];			// Shx Add 权限和职位
};

struct stSeptMemberInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD  dwCharID;        // 会员角色ID
  char  name[MAX_NAMESIZE+1];      // 会员角色名称    
  char    aliasname[MAX_NAMESIZE+1];    // 别名
  WORD    wdOccupation;        // 会员的职业
  WORD	nRight;				//职位序号.
};

}

/**
 * \brief 定义门派的基本结构
 *
 */
namespace School
{

#define MAX_BULLETIN_CHAR_NUMBER 1000          // 公告牌上允许的最大字符数
#define MAX_PRENTICE 20              // 一个人最多可以招收的徒弟数目
#define TEACHER_LEVEL 30            // 招收徒弟需要等级
#define CREATE_SCHOOL_REQUEST_LEVEL 60      // 创建门派等级需要 60
#define CREATE_SCHOOL_REQUEST_ITEM_ID 684      // 创建门派需要道具目前为天羽令
#define CREATE_SCHOOL_REQUEST_PRICE_GOLD 100000 // 创建门派需要的金钱数目
#define FIRST_LAYER_PRENTICE_REQUEST_LEVEL 50   // 创建门派者的第一层徒弟需要的角色级别
#define SECOND_LAYER_PRENTICE_REQUEST_LEVEL 40  // 创建门派者的第二层徒孙需要的角色级别

struct stSchoolInfo
{
  DWORD dwSchoolID;
  char  name[MAX_NAMESIZE+1];
  DWORD dwMasterSerialID;
  DWORD  size;
};
  
struct stSchoolMemberInfo
{
  DWORD dwSerialID;
  DWORD dwMasterID;
  DWORD dwPreSerialID;
  DWORD dwCharID;
  char  name[MAX_NAMESIZE+1];
  WORD  wdLevel;
  DWORD dwJoinTime;
  WORD  wdDegree;
  DWORD dwLastTime;
  DWORD dwSchoolID;
  BYTE  byTag;
  WORD  wdOccupation;
  DWORD master_total;
  DWORD master_balance;
  DWORD prentice_lastlevel;
  DWORD prentice_total;
};

}

#pragma pack()

/**
 * \brief 定义帮会的基本结构
 *
 */
#pragma pack(1)

namespace UnionDef
{

#define WD2BA(wd,ba)       \
do                         \
{                          \
  ba[0]= (wd >>8)&0xFF;     \
  ba[1]= wd& 0xFF;         \
}while(false)

#define BA2WD(ba,wd)      \
do                        \
{                          \
    wd   = ba[0];              \
    wd <<= 8;          \
    wd  |= ba[1];            \
}while(false)
    
#define SETMEMBERPOWER(ba) Cmd::set_state(ba,Cmd::GENERAL)

#define SETMASTERPOWER(ba)                \
do                                        \
{                                         \
  Cmd::set_state(ba,Cmd::CHANGE_ALIAS);   \
  Cmd::set_state(ba,Cmd::ADD_MEMBER);     \
  Cmd::set_state(ba,Cmd::FIRE_MEMBER);    \
  Cmd::set_state(ba,Cmd::GENERAL);        \
  Cmd::set_state(ba,Cmd::MASTER);        \
  Cmd::set_state(ba,Cmd::DARE);        \
  Cmd::set_state(ba,Cmd::NOTIFY);        \
}while(false)

#define SETSECONDPOWER(ba)                \
do                                        \
{                                         \
  Cmd::set_state(ba,Cmd::CHANGE_ALIAS);   \
  Cmd::set_state(ba,Cmd::ADD_MEMBER);     \
  Cmd::set_state(ba,Cmd::FIRE_MEMBER);    \
  Cmd::set_state(ba,Cmd::GENERAL);        \
  Cmd::set_state(ba,Cmd::NOTIFY); \
}while(false)

#define SETMEMBERPOWER_WD(WD) \
do                            \
{                             \
  BYTE temp[2];               \
  temp[0] = 0x00;      \
  temp[1] = 0x00;      \
  SETMEMBERPOWER(temp);       \
  BA2WD(temp,WD);             \
}while(false)


#define SETMASTERPOWER_WD(WD) \
do                            \
{                             \
  BYTE temp[2];               \
  temp[0] = 0x00;      \
  temp[1] = 0x00;      \
  SETMASTERPOWER(temp);       \
  BA2WD(temp,WD);             \
}while(false)


const DWORD CREATE_UNION_NEED_PRICE_GOLD = 50000; // 建立帮会需要金钱10万
const DWORD CREATE_UNION_NEED_ITEM_ID    = 684;     // 建立帮会所需要的道具ID 天羽令
const DWORD CREATE_UNION_NEED_LEVEL      = 45;      // 建立帮会需要的人物等级
const DWORD DESTROYTIME        = 30*24*60*60; //投票有效期 一个月的秒数
const DWORD CREATE_UNION_NEED_VOTE       =  2;
const DWORD CREATE_UNION_NEED_MAN_NUM    =30;  // 帮会成立需要人数
    
#define DEFAULTMASTERALIAS "帮主"
#define DEFAULTMEMBERALIAS "帮众"

struct stUnionInfo             // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD    dwUnionID;        // 帮会的ID
  char    name[MAX_NAMESIZE+1];       // 帮会名称
  DWORD    dwCharID;                   // 帮主的角色ID
  char    masterName[MAX_NAMESIZE+1];    // 帮主的名字
  BYTE    byVote;          // 签名标志为1表示处于签名期间
  DWORD    dwCrTime;        // 帮会创立时间
  WORD    wdLevel;                        // 帮会级别
  QWORD    qwExp;                       // 帮会经验
  DWORD     dwMana;          // 帮会威望
  DWORD    dwCountryID;        // 所属国家
  DWORD    dwActionPoint;        // 帮会行动力
  DWORD     dwMoney;        // 帮会资金
  char    note[254+1];        // 帮会介绍
  DWORD    calltimes;        // 令牌使用次数
};

struct stUnionMemberInfo                      // 数据库读取结构，请不要随意修改，修改注意更新所有代码
{
  DWORD  dwCharID;          // 会员角色ID
  char  name[MAX_NAMESIZE+1];        // 会员角色名称    
  char    aliasname[MAX_NAMESIZE+1];       // 会员别名
  WORD    wdPower;          // 会员权限
  WORD    wdOccupation;          // 会员的职业
  DWORD   dwSeptID;          // 会员所属家族
};

}

#pragma pack()

#ifdef _MSC_VER
#pragma warning(disable:4200)
#endif //_MSC_VER

class SceneUser;
struct zLiveSkillB;

typedef DWORD tItemThisID;
#define INVALID_THISID 0xffffffff

// 道具的类型
enum enumItemType
{
  ItemType_None,

  ItemType_Resource = 16,//16代表原料类

  ItemType_Leechdom,//17代表药品类
  ItemType_FoodRes,//18代表食物原料类
  ItemType_Food,  //19代表食物类
  ItemType_Tools,  //20代表劳动工具类
  ItemType_Arrow,  //21代表配合弓使用的箭支类
  ItemType_BattleHorse,//22战马
  ItemType_Pack,  //23代表包裹类
  ItemType_Money,  //24代表金钱类
  ItemType_Scroll,//25代表转移卷轴类
  ItemType_Move,  //26代表特殊移动道具类
  ItemType_LevelUp,//27代表道具升级需要的材料类
  ItemType_CaptureWeapon,//28代表驯服宠物用武器
  ItemType_Union,//29代表创建帮会需要的道具.
  ItemType_Tonic,//30表示自动补药类道具.
  ItemType_Gift,//31代表礼品类物品.
  ItemType_Other,
  ItemType_MASK = 33,//33代表蒙面巾
  ItemType_Quest = 34,
  ItemType_HORSE = 35,
  ItemType_SOULSTONE = 37,//37代表魂魄石类
  ItemType_Wedding = 38,//38代表婚礼类
  ItemType_Change = 41,//41 代表合成道具
  ItemType_Auto = 42,//42 代表自动练功
  ItemType_SkillUp = 43,//43 代表技能升级道具
  ItemType_Book = 44,//44代表书籍
  ItemType_Store = 45,//45 代表仓库
  ItemType_Renew = 46,//46 代表洗点道具
  ItemType_Repair = 47,//47代表修复宝石类
  ItemType_DoubleExp = 52,//52代表双倍经验类型
  ItemType_Honor = 53,//53代表荣誉之星类型
  ItemType_TONG = 54,//帮主令  
  ItemType_FAMILY = 55,//家族令
  ItemType_Adonment = 56,//56代表装饰品
  ItemType_SpecialBook = 57,//57代表特殊书籍
  ItemType_GreatLeechdom = 58,//58大计量药品
  ItemType_ClearProperty = 59,//59洗点道具
  ItemType_UseSkill = 60,// 附带技能类道具
  ItemType_Amulet = 61,// 护身符类道具
  ItemType_GreatLeechdomMp = 62,//62大计量自动补兰道具
  ItemType_KING = 65,//国王令

  ItemType_DoubleExpZ =  66,  //中级经验倍率物品
  ItemType_DoubleExpC =  67,  //初级经验倍率物品
  ItemType_DoubleExpG = 68,   //高级经验倍率物品

  ItemType_Blade =104,		// sky 104代表单手刀
  ItemType_Sword =105,		// sky 105代表左手剑
  ItemType_Axe =106,		// sky 106代表双手类武器
  ItemType_Hammer =107,		// sky 107代表匕首类武器
  ItemType_Staff =108,		// sky 108代表飞标类武器
  ItemType_Crossbow =109,	// sky 109代表法杖类武器
  ItemType_Fan =110,		// sky 110代表盾牌类
  ItemType_Stick =111,		// sky 111预留武器位
  ItemType_Shield =112,		// sky 112预留武器位

  ItemType_ClothBody =101,  // sky 101代表布质服装
  ItemType_Helm =113,		//sky 113代表角色头盔类(布)
  ItemType_Caestus =114,	//sky 114代表角色腰带类(布)
  ItemType_Cuff = 115,		//sky 115代表角色护腕类(布)
  ItemType_Shoes = 116,		//sky 116代表角色鞋子类(布)

  tyItemType_Shoulder = 131,		//131代表角色肩膀（布）
  tyItemType_Gloves = 132,			//132代表角色手套（布）
  tyItemType_Pants = 133,  			//133代表角色裤子（布）

  ItemType_Necklace = 117,	//sky 117代表角色项链类
  ItemType_Fing = 118,		//sky 118代表角色戒指类

  /*sky 新增板和皮类型防具支持*/
  ItemType_FellBody =102,			//sky 102代表皮甲类服装
  ItemType_Helm_Paper = 119,		//sky 119代表角色头盔类(皮)
  ItemType_Caestus_Paper =120,		//sky 120代表角色腰带类(皮)
  ItemType_Cuff_Paper = 121,		//sky 121代表角色护腕类(皮)
  ItemType_Shoes_Paper = 122,		//sky 122代表角色鞋子类(皮)
  ItemType_Shoulder_Paper = 134,    //sky 134代表角色肩膀（皮）
  ItemType_Gloves_Paper = 135,		//sky 135代表角色手套（皮）
  ItemType_Pants_Paper = 136,		//sky 136代表角色裤子（皮）

  ItemType_MetalBody =103,			//sky 103代表板甲类服装
  ItemType_Helm_Plate = 123,		//sky 123代表角色头盔类(板)
  ItemType_Caestus_Plate =124,		//sky 124代表角色腰带类(板)
  ItemType_Cuff_Plate = 125,		//sky 125代表角色护腕类(板)
  ItemType_Shoes_Plate = 126,		//sky 126代表角色鞋子类(板)

  ItemType_FashionBody = 127,  //119代表时装
  ItemType_HighFashionBody = 128, //124代表高级时装（SKY新增）
  ItemType_Flower = 129,  //120代表鲜花,采集手套...
  ItemType_BMW = 130,  //119代表宝马

  ItemType_Shoulder_Plate = 137,    //sky 137代表角色肩膀（板）
  ItemType_Gloves_Plate = 138,		//sky 138代表角色手套（板）
  ItemType_Pants_Plate = 139,		//sky 139代表角色裤子（板）

  //lxb begin 08.12.29
  ItemType_Bangle = 140,				//手镯
  ItemType_Jade = 141,				//玉佩
  ItemType_Manteau = 142,				//披风
  ItemType_Earrings=143,				//耳环	//Shx Add;
  //lxb end  
  ItemType_Building = 199,	//sky  建筑物品
  ItemType_SkillItem = 200, //sky  技能物品
  ItemType_MAX		 = 256, //sky  不可用最大值

};

#define BOW_ARROW_ITEM_TYPE 21

namespace Object
{

enum {
  INVALID_LOC = (DWORD) -1,
  INVALID_TAB = (DWORD) -1,
  INVALID_X = (WORD) -1,
  INVALID_Y = (WORD) -1,
};

}

#pragma pack(1)

struct stObjectLocation{

private:
  DWORD dwLocation;  // 格子类型
  DWORD dwTableID;  // 包袱ID
  WORD  x;
  WORD  y;

  friend class Package;
public:
  stObjectLocation() 
    : dwLocation(Object::INVALID_LOC),dwTableID(Object::INVALID_TAB),
    x(Object::INVALID_X),y(Object::INVALID_Y)
  {

  }

  stObjectLocation(const stObjectLocation& loc) 
    : dwLocation(loc.dwLocation),dwTableID(loc.dwTableID),x(loc.x),y(loc.y)
  {

  }

  stObjectLocation(DWORD loc,DWORD tab,WORD _x,WORD _y) 
    : dwLocation(loc),dwTableID(tab),x(_x),y(_y)
  {

  }
  
  void operator = (const stObjectLocation& loc)
  {
    dwLocation =loc.dwLocation;
    dwTableID = loc.dwTableID;
    x = loc.x;
    y = loc.y;
  }
  
  bool operator == (const stObjectLocation & st) const
  {
    return dwLocation == st.dwLocation && dwTableID == st.dwTableID && x == st.x && y == st.y;
  }

  bool operator != (const stObjectLocation & st) const
  {
    return !(*this == st);
  }

  DWORD tab() const
  {
    return dwTableID;
  }

  void tab(DWORD t) 
  {
    dwTableID = t;
  }

  DWORD loc() const
  {
    return dwLocation;
  }

  WORD xpos() const
  {
    return x;
  }

  WORD ypos() const
  {
    return y;
  }
};

struct oskill
{
  DWORD id;
  BYTE level;
  BYTE count;
  BYTE maxcount;
  BYTE other;
};

//lxb begin 08.12.30
const DWORD INVALID_HOLE = 0xffffffff;	//没有孔
const DWORD EMPTY_HOLE = 0;	//孔是空的
//lxb end

const BYTE HOLE_ACTIVVATED_OFF = 0;

//sky 新增宝石等相关结构
typedef struct Gem_Pop 
{
	bool	M_State;	//激活状态(true:激活 false:未激活)
	DWORD	GemID;		//宝石ID用来在客户端显示宝石的图标

	WORD	gem_str;	//力量
	WORD	gem_inte;	//智力
	WORD	gem_dex;	//敏捷
	WORD	gem_spi;	//精神
	WORD	gem_con;	//耐力
	WORD	gem_def;	//物理防御
	WORD	gem_mdef;	//魔法防御
	WORD	gem_dhpp;	//物理免伤
	WORD	gem_dmpp;	//魔法免伤
	WORD	gem_atk;	//物理攻击力
	WORD	gem_mkt;	//魔法攻击力

} GemPop;
//sky 宝石结构 end


typedef struct _Object
{
	 DWORD qwThisID;   //物品唯一id
	 DWORD dwObjectID;  ////物品类别id
	 char strName[MAX_NAMESIZE]; //名称
	 
	 stObjectLocation pos;  // 位置
	 DWORD dwNum;  // 数量
	 BYTE upgrade;//物品升级等级
	 BYTE kind;  //物品类型,0普通,1蓝色,2绿装,4紫装,8橙装
	 DWORD exp;  //道具经验
	 
	 WORD needlevel;        // 需要等级

	 DWORD maxhp;          // 最大生命值
	 DWORD maxmp;          // 最大法术值
	 DWORD maxsp;          // 最大体力值

	 DWORD pdamage;        // 最小攻击力
	 DWORD maxpdamage;      // 最大攻击力
	 DWORD mdamage;        // 最小法术攻击力
	 DWORD maxmdamage;      // 最大法术攻击力

	 DWORD pdefence;        // 物防
	 DWORD mdefence;        // 魔防
	 BYTE damagebonus;      // 伤害加成 x% from 道具基本表
	 BYTE damage;        // 增加伤害值x％ from 神圣装备表
	   
	 WORD akspeed;        // 攻击速度
	 WORD mvspeed;        // 移动速度
	 WORD atrating;        // 命中率
	 WORD akdodge;        // 躲避率

	 DWORD color;        // 颜色  

	 WORD str;  // 力量
	 WORD inte;  // 智力
	 WORD dex;  // 敏捷
	 WORD spi;  // 精神
	 WORD con;  // 体质
	 
	 WORD fivetype;  // 五行属性
	 WORD fivepoint; // 五行属性
	 
	 WORD hpr;  // 生命值恢复----
	 WORD mpr;  // 法术值恢复----
	 WORD spr;  // 体力值恢复----

	 WORD holy;  //神圣一击  
	 WORD bang;  //重击

	 WORD pdam;  // 增加物理攻击力----
	 WORD pdef;  // 增加物理防御力----
	 WORD mdam;  // 增加魔法攻击力----
	 WORD mdef;  // 增加魔法防御力----
	 
	 WORD poisondef; //抗毒增加
	 WORD lulldef; //抗麻痹增加
	 WORD reeldef; //抗眩晕增加
	 WORD evildef; //抗噬魔增加
	 WORD bitedef; //抗噬力增加
	 WORD chaosdef; //抗混乱增加
	 WORD colddef; //抗冰冻增加
	 WORD petrifydef; //抗石化增加
	 WORD blinddef; //抗失明增加
	 WORD stabledef; //抗定身增加
	 WORD slowdef; //抗减速增加
	 WORD luredef; //抗诱惑增加

	 WORD durpoint; //恢复装备耐久度点数
	 WORD dursecond; //恢复装备耐久度时间单位

	 struct skillbonus {
	   WORD id; //技能 id
	   WORD point; // 技能点数
	 } skill[10]; //技能加成

	 struct skillsbonus {
	   WORD id; //技能 id
	   WORD point; // 技能点数
	 } skills;  //全系技能加成

	 WORD poison; //中毒增加
	 WORD lull; //麻痹增加
	 WORD reel; //眩晕增加
	 WORD evil; //噬魔增加
	 WORD bite; //噬力增加
	 WORD chaos; //混乱增加
	 WORD cold; //冰冻增加
	 WORD petrify; //石化增加
	 WORD blind; //失明增加
	 WORD stable; //定身增加
	 WORD slow; //减速增加
	 WORD lure; //诱惑增加

	 //lxb begin 08.12.30
	 WORD giddy;		//眩晕
	 WORD coma;		//昏迷
	 WORD halt;		//定身
	 WORD dread;		//恐惧
	 WORD slowdown;	//减速
	 WORD banish;	//放逐

	 WORD giddy_def;		//防眩晕
	 WORD coma_def;		//防昏迷
	 WORD halt_def;		//防定身
	 WORD dread_def;		//防恐惧
	 WORD slowdown_def;	//防减速
	 WORD banish_def;	//防放逐
	 //lxb end
	 
	 struct leech
	 {
	   BYTE odds;    //x
	   WORD effect;  //y
	 };
	 leech hpleech; //x%吸收生命值y
	 leech mpleech; //x%吸收法术值y
	 
	 BYTE hptomp; //转换生命值为法术值x％
	 BYTE dhpp; //物理伤害减少x%  
	 BYTE dmpp; //法术伤害值减少x%    

	 BYTE incgold; //增加金钱掉落x%
	 BYTE doublexp; //x%双倍经验    
	 BYTE mf; //增加掉宝率x%
	 
	 BYTE bind;  //装备是否绑定

	 union {
	   BYTE _five_props[5];
	   struct {
	     //五行套装相关属性
	     BYTE dpdam; //物理伤害减少%x
	     BYTE dmdam; //法术伤害减少%x
	     BYTE bdam; //增加伤害x%
	     BYTE rdam; //伤害反射%x
	     BYTE ignoredef; //%x忽视目标防御
	   };
	 };

	 WORD fiveset[5]; //五行套装,按顺序排列

	 //...
	 BYTE width;  //宽度
	 BYTE height; //高度
	 WORD dur;    //当前耐久
	 WORD maxdur; //最大耐久
	 
	 GemPop Hsocket[SOCKET_MAXNUM]; //sky 宝石孔
	 DWORD price;     //价格
	 DWORD cardpoint; //点卡

	 char maker[MAX_NAMESIZE]; //打造者

	 //Sky新增自由加点结构
	struct Freedom_Attribute {
		WORD Surplus_Attribute;	//当前剩余属性点
		//用于洗点用的记录
		WORD str_Attribute;		// 力量已经加过的自由点
		WORD inte_Attribute;	// 智力已经加过的自由点
		WORD dex_Attribute;		// 敏捷已经加过的自由点
		WORD spi_Attribute;		// 精神已经加过的自由点
		WORD con_Attribute;		// 体质已经加过的自由点

	} Freedom;

//[Shx Add 套装属性]************************************
//#pragma pack(1)
	struct Suit_Attribute
	{
		struct __Attr
		{
			BYTE eRequire;		//激活条件
			BYTE eKey;			//激活属性			
			WORD eValue;		//值			
		};

		char	Suit_name[MAX_NAMESIZE];	//套装名称;
		WORD	Suit_ID;	//套装ID;
		BYTE	nPart;
		BYTE    nEffect;
		DWORD	PartList[MAX_SUIT_NUM];	//套装成员ID;
		__Attr	EffectList[MAX_SUIT_NUM];
	} SuitAttribute;
//#pragma pack(4)
	//End 套装属性;
}t_Object;

#pragma pack()

namespace Object
{
  static stObjectLocation INVALID_POS;
}

//#define BINARY_VERSION   0
//#define BINARY_VERSION   20051018
//#define BINARY_VERSION  20051225
//#define BINARY_VERSION     20060124
#define BINARY_VERSION     20060313

struct ZlibObject
{
  DWORD   version;
  DWORD  count;
  BYTE data[0];
  ZlibObject()
  {
    count = 0;
    version = 0;
  }
};

struct SaveObject
{
  union
  {
    struct 
    {
      DWORD createtime;
      DWORD dwCreateThisID;  
    };
    QWORD createid;
  };
  // */
  t_Object object;
};

/**
 * \brief 技能压缩结构
 */
struct ZlibSkill
{
  DWORD count;
  BYTE data[0];
  ZlibSkill()
  {
    count = 0;
  }
};

/**
 * \brief 技能存档单元
 */
struct SaveSkill
{
  DWORD type;
  DWORD level;
};

/**
 * \brief 技能分类
 *
 */
enum SkillType
{
  SKILL_TYPE_DAMAGE = 1, ///直接伤害
  SKILL_TYPE_RECOVER, ///恢复系
  SKILL_TYPE_BUFF, ///增益效果
  SKILL_TYPE_DEBUFF, ///负面效果
  SKILL_TYPE_SUMMON, ///召唤
  SKILL_TYPE_RELIVE  ///复活
};

struct LiveSkill
{
public:
  WORD id; //技能标识
  WORD level; //等级
  DWORD point; //等级后值,小点

  enum {
    DEFAULT_START_LEVEL  = 1,//生活技能默认开始等级
    WORKING_TIME = 5,//工作时间
    ADVANCE_WORK_BONUS = 500,//获得物品概率加成
    MIN_NEED_SP = 4,
    MAX_NEED_SP = 8,
    ADVANCE_LEVEL = 22,//进阶技能需要等级
    ODDS_BENCHMARK = 10000,
  };

  enum {
    BASIC_WORK = 1,
    MAKE_WORK = 2,
    ADVANCE_WORK = 3,
  };

  int bonus(SceneUser* user,int points = 0);
  int bonus_items(SceneUser* user,zLiveSkillB* base_skill);
  static int bonus_exp(SceneUser* user,DWORD exp);
  
  static int consume_sp();
  
  const static int odds[];
};

#pragma pack(1)

typedef struct _Skill
{
  DWORD  skillid;          //技能ID
  DWORD  level;            //技能等级
//  DWORD  maxlevel;          //技能等级
//  DWORD  nextlevel;          //需要角色等级
//  DWORD  needtype;          // 需要职业
//  DWORD  five;            // 五行属性
//  DWORD  firstfive;          // 最初五行点数
  //DWORD  nextfive;          // 五行点数
}t_Skill;
#pragma pack()

namespace SkillDef
{
  enum ATTACK_TYPE
  {
    AttackNear = 0,
    AttackFly = 1,
    AttackDirect = 2
  };

  enum
  {
    AttackNine = 1,
    AttackEight = 2,
    AttackThree = 3,
    AttackFive_1 = 4,
    AttackFive_2 = 5,
    AttackFive_3 = 6,
    AttackCross = 7

  };
  enum   SKILL_STATUS
  {
    SKILL_default,//0默认为错误类型
    SKILL_dvalue,//伤害值
    SKILL_reflect,//反弹
    SKILL_sdam,//技能攻击力
    SKILL_mdam,//法术攻击力
    SKILL_maxmp,//法术值上限
    SKILL_mpspeed,//法术值回复速度
    SKILL_mppersist,//法术值持续
    SKILL_mp,     //法术值
    SKILL_mpdef, //法术防御
    SKILL_sp,     //体力值
    SKILL_maxsp,//体力值上限
    SKILL_sppersist,//体力值持续
    SKILL_spspeed,//体力值回复速度
    SKILL_hp,     //生命值
    SKILL_maxhp, //生命值上限
    SKILL_hppersist,//生命值持续
    SKILL_hpspeed,//生命值回复速度
    SKILL_mvspeed,//移动速度
    SKILL_pdam,   //物理攻击力
    SKILL_atrating,//命中率
    SKILL_skillrating,//技能命中率
    SKILL_akdodge,//闪避率
    SKILL_cancel,//状态消除
    SKILL_aspeed,//攻击速度
    SKILL_relive,//复活
    SKILL_hitback,//击退
    SKILL_change,//攻击目标变为施法者
    SKILL_topet,//变为随机小动物
    SKILL_dam2ddef,//攻防转换
    SKILL_poison,//中毒状态
    SKILL_petrify,//石化状态
    SKILL_blind,//失明状态
    SKILL_chaos,//混乱状态
    SKILL_cold,//冰冻状态
    SKILL_palsy,//麻痹状态
    SKILL_bleeding,//流血状态
    SKILL_sevenp,//降低陷入七大状态几率
    SKILL_coldp,//减少陷入冰冻状态几率
    SKILL_poisonp,//减少陷入中毒状态几率
    SKILL_petrifyp,//减少陷入石化状态几率
    SKILL_blindp,//减少陷入失明状态几率
    SKILL_chaosp,//减少陷入混乱状态几率
    SKILL_mgspeed,//减少技能施放间隔
    SKILL_cancelatt //不能攻击施法者
  };

//sky  技能目标定义
#define TARGET_SELF 1      //自己
#define TARGET_FRIEND 2		//友方
#define TARGET_ENEMY 4		//敌人
#define TARGET_NPC 8		//NPC
#define TARGET_TERRASURFACE 16	//地表
#define TARGET_PET 32			//宠物
#define TARGET_SUMMON 64		//召唤兽

// sky 技能中心点定义
#define SKILL_CENTER_TYPE_SELF  2
#define SKILL_CENTER_TYPE_MOUSE 1

#define SKILLINVALID 0 
#define SERVER_SKILL_ATTACK_NORMAL 78		//单手武器普通攻击
#define	SERVER_SKILL_DAGGER_ATTACK_NORMAL 79 //双持武器(匕首)普通攻击
#define	SERVER_SKILL_DART_ATTACK_NORMAL 80	//飞镖武器普通攻击
#define	SERVER_SKILL_HANDS_ATTACK_NORMAL 77	//双手武器普通攻击
#define MAX_SKILLLEVEL 10

};

/**
 * \brief 使所有的子类禁用拷贝构造函数和赋值符号
 *
 */
class zNoncopyable
{

  protected:

    /**
     * \brief 缺省构造函数
     *
     */
    zNoncopyable() {};

    /**
     * \brief 缺省析构函数
     *
     */
    ~zNoncopyable() {};

  private:

    /**
     * \brief 拷贝构造函数，没有实现，禁用掉了
     *
     */
    zNoncopyable(const zNoncopyable&);

    /**
     * \brief 赋值操作符号，没有实现，禁用掉了
     *
     */
    const zNoncopyable & operator= (const zNoncopyable &);

};

template <typename T>
class SingletonFactory
{
  public:
    static T* instance()
    {
      return new T();
    }
};

template <typename T,typename MANA = SingletonFactory<T> > 
class Singleton
{
  private:
    /**
     * \brief 拷贝构造函数，没有实现，禁用掉了
     *
     */
    Singleton(const Singleton&);

    /**
     * \brief 赋值操作符号，没有实现，禁用掉了
     *
     */
    const Singleton & operator= (const Singleton &);
  protected:

    static T* ms_Singleton;
    Singleton( void )
    {
    }

    ~Singleton( void )
    {
    }

  public:
  
    static void delMe(void)
    {//可以在子类的destoryMe中被调用
      if (ms_Singleton)
      {
        delete ms_Singleton;
        ms_Singleton = 0;
      }
    }

    static T* instance( void )
    {
      if (!ms_Singleton)
      {
        ms_Singleton = MANA::instance();
      }
      
      return ms_Singleton;
    }

    static T& getMe(void)
    {
      return *instance();
    }

};

template <typename T,typename MANA>
T* Singleton<T,MANA>::ms_Singleton = 0;

/**
 * \brief 定义人物角色相关信息
 */


#pragma pack(1)

#define HAIRTYPE_MASK  0xff000000    /// 头发发型
#define HAIRRGB_MASK  0x00ffffff    /// 头发颜色
const int exploit_arg = 100;      // 功勋值同比放大系数

//---------------------------------
#define LEVELUP_HP_N      15
#define LEVELUP_MP_N      1
#define LEVELUP_SP_N      5

#define LEVELUP_RESUMEHP_N    0
#define  LEVELUP_RESUMEMP_N    0
#define LEVELUP_RESUMESP_N    0

#define LEVELUP_ATTACKRATING_N  1
#define LEVELUP_ATTACKDODGE_N  1

#define LEVELUP_MOVESPEED_N    0
#define LEVELUP_ATTACKSPEED_N  0

#define LEVELUP_PDAMAGE_N    0
#define LEVELUP_MDAMAGE_N    0
#define LEVELUP_PDEFENCE_N    0
#define LEVELUP_MDEFENCE_N    0

#define LEVELUP_BANG_N    0
//----------------------------------
#define BASEDATA_M_HP      500
#define BASEDATA_M_MP      60
#define BASEDATA_M_SP      100

#define BASEDATA_M_RESUMEHP    1
#define  BASEDATA_M_RESUMEMP    1
#define BASEDATA_M_RESUMESP    1

#define BASEDATA_M_ATTACKRATING  1
#define BASEDATA_M_ATTACKDODGE  1

#define BASEDATA_M_MOVESPEED  0
#define BASEDATA_M_ATTACKSPEED  0

#define BASEDATA_M_PDAMAGE    11
#define BASEDATA_M_MDAMAGE    11
#define BASEDATA_M_PDEFENCE    1
#define BASEDATA_M_MDEFENCE    1

#define BASEDATA_M_BANG    1
//----------------------------------
#define BASEDATA_F_HP      500
#define BASEDATA_F_MP      60
#define BASEDATA_F_SP      90

#define BASEDATA_F_RESUMEHP    1
#define  BASEDATA_F_RESUMEMP    1
#define BASEDATA_F_RESUMESP    1

#define BASEDATA_F_ATTACKRATING  1
#define BASEDATA_F_ATTACKDODGE  1

#define BASEDATA_F_MOVESPEED  0
#define BASEDATA_F_ATTACKSPEED  0

#define BASEDATA_F_PDAMAGE    11
#define BASEDATA_F_MDAMAGE    11
#define BASEDATA_F_PDEFENCE    1
#define BASEDATA_F_MDEFENCE    1

#define BASEDATA_F_BANG    1
//----------------------------------

struct CharBase
{
  DWORD accid;            /// 账号
  DWORD id;              /// 角色编号
  char  name[MAX_NAMESIZE + 1];    /// 角色名称
  WORD  type;              /// 性别
  WORD  level;            /// 角色等级
  WORD  face;              /// 头像
  DWORD hair;              /// 头发，发型和颜色
  DWORD bodyColor;              /// 光身颜色
  DWORD goodness;            /// 善恶度
  DWORD mapid;            /// 角色所在地图编号
  char  mapName[MAX_NAMESIZE + 1];  /// 角色所在地图名称
  DWORD x;              /// 角色所在坐标x
  DWORD y;              /// 角色所在坐标y
  DWORD unionid;            /// 帮会ID
  DWORD schoolid;            /// 门派ID
  DWORD septid;            /// 家族ID
  DWORD hp;              /// 当前生命值
  DWORD mp;              /// 当前法术值
  DWORD sp;              /// 当前体力值
  QWORD exp;              /// 当前经验值
  char OldMap[MAX_PATH];	///sky 移动到新地图前的老地图位置数据
  WORD  skillpoint;          /// 技能点数
  WORD  points;            /// 未分配人物属性点数
  DWORD  country;            /// 国家
  DWORD  consort;              /// 配偶
 
  QWORD forbidtalk;          ///禁言
  DWORD bitmask;            /// 标志掩码
  DWORD onlinetime;          /// 在线时间统计
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };
  WORD reliveWeakTime;      /// 复活虚弱剩余时间
  DWORD useJob;        // sky 角色职业(数据库位置使用原文采"GRACE"段)
  DWORD exploit;        /// 功勋值
  char tiretime[36+1];      /// 疲劳时间标记
  DWORD offlinetime;        /// 上次下线时间
  DWORD fivetype;          /// 五行类型
  DWORD fivelevel;        /// 五行点数
  DWORD pkaddition;        /// 善恶追加值
  DWORD money;        /// 当前银子,只存储维护,不能使用
  DWORD answerCount;      /// 当天答题次数
  DWORD honor;        //荣誉值
  DWORD maxhonor;        //最大荣誉值
  DWORD gomaptype;      //跳地图类型
  DWORD msgTime;        //下次发送GM留言的时间
  DWORD accPriv;      //帐号权限
  DWORD gold;          /// 金币
  DWORD ticket;         //点券数
  DWORD createtime;      /// 角色创建时间
  DWORD goldgive;        /// 金币冲值赠品数量
  BYTE petPack;        /// 宠物包裹大小
  DWORD petPoint;        /// 奖励的宠物修炼时间
  DWORD levelsept;      /// 离开家族的时间
  DWORD punishTime;      /// 杀人被抓的时间，分钟为单位
  DWORD trainTime;      /// 在练级地图逗留的时间
  DWORD  zs;                   ///转生次数
  DWORD doubletime;          ///双倍物品剩余时间
};

struct CharState
{
  DWORD maxhp;            /// 最大生命值 *
  DWORD resumehp;            /// 生命值恢复 *
  DWORD maxmp;            /// 最大法术值 *
  DWORD resumemp;            /// 法术值恢复 *
  DWORD maxsp;                     /// 最大体力值 *
  DWORD resumesp;                  /// 体力恢复值 *

  DWORD pdamage;                   /// 最小物理攻击力 *
  DWORD maxpdamage;          /// 最大物理攻击力 *
  DWORD mdamage;            /// 最小法术攻击力 *
  DWORD maxmdamage;          /// 最大法术攻击力 *
  DWORD pdefence;            /// 物理防御力 *
  DWORD mdefence;            /// 法术防御力 *
  QWORD nextexp;            /// 升级经验值 *
  WORD  attackspeed;          /// 攻击速度 *
  WORD  movespeed;          /// 移动速度 *
  SWORD  attackrating;        /// 攻击命中 *
  SWORD  attackdodge;          /// 攻击躲避 *
  WORD  bang;              /// 重击 *
  WORD  charm;                     /// 魅力值 *
  BYTE  attackfive;          /// 攻击五行 *
  BYTE  defencefive;          /// 防御五行 *
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };

  DWORD stdpdamage;          /// 标准物理攻击力
  DWORD stdmdamage;          /// 标准法术攻击力
  DWORD stdpdefence;          /// 标准物理防御力
  DWORD stdmdefence;          /// 标准法术防御力
  WORD  stdbang;            /// 标准重击率
};

#ifdef _TEST_DATA_LOG
struct CharTest
{
  DWORD upgrade_time;//升级时间
  DWORD upgrade_usetime;//本级使用时间
  DWORD death_times;//死亡次数
  DWORD hp_leechdom;//使用生命值药品个数
  DWORD mp_leechdom;//使用法术值药品个数
  DWORD sp_leechdom;//使用体力值药品个数
  DWORD get_money;//得到银子数
  DWORD get_heigh;//得到高级装备个数
  DWORD get_socket;//得到带孔装备个数
  DWORD get_material;//得到原料个数
  DWORD get_stone;//得到宝石个数
  DWORD get_scroll;//得到卷轴个数
  DWORD money;//当前银子数
};
#endif

struct CharSave
{
  CharBase   charbase;
  DWORD    dataSize;
  char     data[0];
};

#define MAX_TEMPARCHIVE_SIZE 0x10000
struct TempArchiveMember
{
  DWORD type;
  DWORD size;
  char data[0];
};

enum TempArchiveType
{
  TEAM,//队伍
  ENTRY_STATE,//队伍
  PET,//宠物
  SAFETY_STATE,// 临时关闭密码保护
  ITEM_COOLTIME,// sky 物品冷却时间
};

struct BinaryArchiveMember
{
  DWORD type;
  DWORD size;
  char data[0];
};

enum BinaryArchiveType
{
  BINARY_DOUBLE_EXP_OBJ,///双倍经验道具
  BINARY_TONG_OBJ,///帮会令牌类道具
  BINARY_KING_OBJ,///国王令牌类道具
  BINARY_FAMILY_OBJ,///家族令牌类道具
  BINARY_CHANGE_COUNTRY_TIME,/// 最后一次叛国的时间
  BINARY_SAFETY,/// 是否进行财产保护
  BINARY_GIVE_MATARIAL_NUM,//道具卡兑换材料的组数
  BINARY_CARD_NUM,     //道具卡张数
  BINARY_SAFETY_SETUP,/// 保护设置
  BINARY_MAX, ///最大数值(占位用)
};

const WORD  MAX_LEVEL      = 150;          /// 最大角色等级
const DWORD MAX_GOODNESS    = 9999;          /// 最大善恶度
const DWORD MAX_HP      = 999999;        /// 最大生命值
const DWORD MAX_RESUMEHP    = 1000;          /// 生命值恢复
const DWORD MAX_MP      = 999999;        /// 最大法术值
const DWORD MAX_RESUMEMP    = 1000;          /// 法术值恢复
const DWORD MAX_SP      = 999999;        /// 最大体力值
const DWORD MAX_RESUMESP    = 1000;          /// 体力值恢复
const DWORD MAX_PDAMAGE      = 999999;        /// 最大物理攻击力
const DWORD MAX_RDAMAGE      = 999999;        /// 最大远程攻击力
const DWORD MAX_TDAMAGE     = 999999;        /// 最大仙术攻击力
const DWORD MAX_MDAMAGE      = 999999;        /// 最大法术攻击力
const DWORD MAX_PDEFENCE    = 999999;        /// 最大物理防御力
const DWORD MAX_MDEFENCE    = 999999;        /// 最大法术防御力
#ifdef _MSC_VER
const QWORD MAX_EXP      = 9999999999i64;
#else //!_MSC_VER
const QWORD MAX_EXP      = 9999999999LL;      /// 最大经验值
#endif //_MSC_VER
const WORD  MAX_ATTACKSPEED    = 100;          /// 攻击速度
const WORD  MAX_MAGICSPEED    = 100;          /// 施法速度
const WORD  MAX_MOVESPEED    = 200;          /// 移动速度
const WORD  MAX_ATTACKRATING    = 999;          /// 攻击命中
const WORD  MAX_ATTACKDODGE    = 999;          /// 攻击躲避
const WORD  MAX_MAGICRATING    = 999;          /// 法术命中
const WORD  MAX_MAGICDODGE    = 999;          /// 法术躲避
const WORD  MAX_LUCKY      = 999;          /// 幸运值
const WORD  MAX_METAL      = 999;          /// 金
const WORD  MAX_WOOD      = 999;          /// 木
const WORD  MAX_WATER      = 999;          /// 水
const WORD  MAX_FIRE      = 999;          /// 火
const WORD  MAX_SOIL      = 999;          /// 土
const WORD  MAX_METALRESISTANCE    = 10000;        /// 金系抵抗
const WORD  MAX_WOODRESISTANCE    = 10000;        /// 木系抵抗
const WORD  MAX_WATERRESISTANCE    = 10000;        /// 水系抵抗
const WORD  MAX_FIRERESISTANCE    = 10000;        /// 火系抵抗
const WORD  MAX_SOILRESISTANCE    = 10000;        /// 土系抵抗
const WORD  MAX_POINTS      = 1500;          /// 点数

const DWORD PUBLIC_COUNTRY = 6;

///得到另一只手
#define otherHand(hand)         ((hand)^3)

///得到另一只手镯
#define otherBangle(bangle)     ((bangle)^1)

namespace Cmd{

//BEGIN_ONE_CMD

/// 空指令
const BYTE NULL_USERCMD      = 0;
/// 登陆指令
const BYTE LOGON_USERCMD    = 1;
/// 时间指令
const BYTE TIME_USERCMD      = 2;
/// 数据指令
const BYTE DATA_USERCMD      = 3;
/// 道具指令
const BYTE PROPERTY_USERCMD    = 4;
/// 地图指令
const BYTE MAPSCREEN_USERCMD    = 5;
/// 移动指令
const BYTE MOVE_USERCMD      = 6;
/// 建造指令
const BYTE BUILD_USERCMD    = 8;
/// 打造指令
const BYTE MAKEOBJECT_USERCMD    = 10;
/// 复活指令
const BYTE RELIVE_USERCMD    = 12;
/// 聊天指令
const BYTE CHAT_USERCMD      = 14;
/// 离开指令
const BYTE LEAVEONLINE_USERCMD    = 15;
/// 交易指令
const BYTE TRADE_USERCMD    = 17;
/// 魔法指令
const BYTE MAGIC_USERCMD    = 18;
/// 帮会指令
const BYTE UNION_USERCMD    = 21;
/// 国家指令
const BYTE COUNTRY_USERCMD    = 22;
/// 任务指令
const BYTE TASK_USERCMD      = 23;
/// 选择指令
const BYTE SELECT_USERCMD    = 24;
//  社会关系指令
const BYTE RELATION_USERCMD        = 25;
//  门派关系指令
const BYTE SCHOOL_USERCMD    = 26;
//  家族关系指令
const BYTE SEPT_USERCMD      = 27;
// 战斗指令
const BYTE DARE_USERCMD                 = 28;
// 宠物指令
const BYTE PET_USERCMD                  = 29;
// 获取服务器列表
const BYTE PING_USERCMD      = 30;
// 金币指令
const BYTE GOLD_USERCMD      = 31;
// 答题指令
const BYTE QUIZ_USERCMD      = 32;
// NPC争夺战指令
const BYTE NPCDARE_USERCMD    = 33;
// 与GM工具交互的指令
const BYTE GMTOOL_USERCMD    = 34;
// 邮件指令
const BYTE MAIL_USERCMD      = 35;
// 拍卖指令
const BYTE AUCTION_USERCMD    = 36;
// 卡通宠物指令
const BYTE CARTOON_USERCMD    = 37;
// 股票指令
const BYTE STOCK_SCENE_USERCMD    = 38;
const BYTE STOCK_BILL_USERCMD    = 39;
// 投票指令
const BYTE VOTE_USERCMD      = 40;
// 军队指令
const BYTE ARMY_USERCMD      = 41;
// 护宝任务指令
const BYTE GEM_USERCMD      = 42;
// 监狱系统指令
const BYTE PRISON_USERCMD    = 43;
// 礼官指令
const BYTE GIFT_USERCMD      = 44;
// 国家同盟指令
const BYTE ALLY_USERCMD      = 45;
// 小游戏指令
const BYTE MINIGAME_USERCMD    = 46;
// 推荐人系统指令
const BYTE RECOMMEND_USERCMD  = 47;
// 财产保护系统指令
const BYTE SAFETY_USERCMD    = 48;
//箱子指令
const BYTE SAFETY_COWBOX = 49;

//转生指令

const BYTE TURN_USERCMD = 50;

const BYTE HOTSPRING_USERCMD = 51;

const BYTE REMAKEOBJECT_USERCMD	= 52;

//训马指令 [sky]
const BYTE HORSETRAINING_USERCMD	= 53;

//自由加点指令 [sky]
const BYTE SURPLUS_ATTRIBUTE_USERCMD	= 54;

// sky 战场-副本-竞技场指令
const BYTE ARENA_USERCMD	= 55;

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 空指令定义开始
//////////////////////////////////////////////////////////////
const BYTE NULL_USERCMD_PARA = 0;
struct stNullUserCmd{
  stNullUserCmd()
  {
    dwTimestamp=0;
  }
  union{
    struct {
      BYTE  byCmd;
      BYTE  byParam;
    };
    struct {
      BYTE  byCmdType;
      BYTE  byParameterType;
    };
  };
  //BYTE  byCmdSequence;
  DWORD  dwTimestamp;
};
//////////////////////////////////////////////////////////////
// 空指令定义结束
//////////////////////////////////////////////////////////////

enum enumMapDataType{
  MAPDATATYPE_NPC,
  MAPDATATYPE_USER,
  MAPDATATYPE_BUILDING,
  MAPDATATYPE_ITEM,
  MAPDATATYPE_PET
};

struct MapData_ItemHeader {
  WORD size;// 数量
  BYTE type;// 类型  enumMapDataType
};

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 登陆指令定义开始
//////////////////////////////////////////////////////////////
struct stLogonUserCmd : public stNullUserCmd
{
  stLogonUserCmd()
  {
    byCmd = LOGON_USERCMD;
  }
};

/// 客户端验证版本
const BYTE USER_VERIFY_VER_PARA = 1;
const DWORD GAME_VERSION = 1999;
struct stUserVerifyVerCmd  : public stLogonUserCmd
{
  stUserVerifyVerCmd()
  {
    byParam = USER_VERIFY_VER_PARA;
    version = GAME_VERSION;
  }

  DWORD version;
};

/// 客户端登陆登陆服务器
const BYTE USER_REQUEST_LOGIN_PARA = 2;
struct stUserRequestLoginCmd : public stLogonUserCmd
{
  stUserRequestLoginCmd()
  {
    byParam = USER_REQUEST_LOGIN_PARA;
  }
  char pstrName[MAX_ACCNAMESIZE];    /**< 帐号 */
  char pstrPassword[MAX_PASSWORD];  /**< 用户密码 */
  WORD game;              /**< 游戏类型编号，目前一律添0 */
  WORD zone;              /**< 游戏区编号 */
  char jpegPassport[7];        /**< 图形验证码 */
};

enum{
  LOGIN_RETURN_UNKNOWN,   /// 未知错误
  LOGIN_RETURN_VERSIONERROR, /// 版本错误
  LOGIN_RETURN_UUID,     /// UUID登陆方式没有实现
  LOGIN_RETURN_DB,     /// 数据库出错
  LOGIN_RETURN_PASSWORDERROR,/// 帐号密码错误
  LOGIN_RETURN_CHANGEPASSWORD,/// 修改密码成功
  LOGIN_RETURN_IDINUSE,   /// ID正在被使用中
  LOGIN_RETURN_IDINCLOSE,   /// ID被封
  LOGIN_RETURN_GATEWAYNOTAVAILABLE,/// 网关服务器未开
  LOGIN_RETURN_USERMAX,   /// 用户满
  LOGIN_RETURN_ACCOUNTEXIST, /// 账号已经存在
  LOGON_RETURN_ACCOUNTSUCCESS,/// 注册账号成功

  LOGIN_RETURN_CHARNAMEREPEAT,/// 角色名称重复
  LOGIN_RETURN_USERDATANOEXIST,/// 用户档案不存在
  LOGIN_RETURN_USERNAMEREPEAT,/// 用户名重复
  LOGIN_RETURN_TIMEOUT,   /// 连接超时
  LOGIN_RETURN_PAYFAILED,   /// 计费失败
  LOGIN_RETURN_JPEG_PASSPORT, /// 图形验证码输入错误
  LOGIN_RETURN_LOCK,         /// 帐号被锁定
  LOGIN_RETURN_WAITACTIVE, /// 帐号待激活
  LOGIN_RETURN_NEWUSER_OLDZONE      ///新账号不允许登入旧的游戏区 
};
/// 登陆失败后返回的信息
const BYTE SERVER_RETURN_LOGIN_FAILED = 3;
struct stServerReturnLoginFailedCmd : public stLogonUserCmd
{
  stServerReturnLoginFailedCmd()
  {
    byParam = SERVER_RETURN_LOGIN_FAILED;
  }
  BYTE byReturnCode;      /**< 返回的子参数 */
} ;

/// 登陆成功，返回网关服务器地址端口以及密钥等信息
const BYTE SERVER_RETURN_LOGIN_OK = 4;
struct stServerReturnLoginSuccessCmd : public stLogonUserCmd 
{
  stServerReturnLoginSuccessCmd()
  {
    byParam = SERVER_RETURN_LOGIN_OK;
  }

  DWORD dwUserID;
  DWORD loginTempID;
  char pstrIP[MAX_IP_LENGTH];
  WORD wdPort;

  union{
    struct{
      BYTE randnum[58];
      BYTE keyOffset;  // 密匙在 key 中的偏移
    };
    BYTE key[256];  // 保存密匙，整个数组用随机数填充
  };
};

/// 客户登陆网关服务器发送账号和密码
const BYTE PASSWD_LOGON_USERCMD_PARA = 5;
struct stPasswdLogonUserCmd : public stLogonUserCmd
{
  stPasswdLogonUserCmd()
  {
    byParam = PASSWD_LOGON_USERCMD_PARA;
  }

  DWORD loginTempID;
  DWORD dwUserID;
  char pstrName[MAX_ACCNAMESIZE];    /**< 帐号 */
  char pstrPassword[MAX_PASSWORD];
};

/// 请求创建账号
const BYTE ACCOUNT_LOGON_USERCMD_PARA = 7;
struct stAccountLogonUserCmd : public stLogonUserCmd 
{
  stAccountLogonUserCmd()
  {
    byParam = ACCOUNT_LOGON_USERCMD_PARA;
  }

  char strName[MAX_ACCNAMESIZE];
  char strPassword[MAX_PASSWORD];
};

/// 请求更改密码
const BYTE PASSWORD_LOGON_USERCMD_PARA = 9;
  struct stPasswordLogonUserCmd : public stLogonUserCmd {
    stPasswordLogonUserCmd()
    {
      byParam = PASSWORD_LOGON_USERCMD_PARA;
    }

    char strName[MAX_ACCNAMESIZE];
    char strPassword[MAX_PASSWORD];
    char strNewPassword[MAX_PASSWORD];
  };

/// 请求返回选择人物界面
const BYTE BACKSELECT_USERCMD_PARA = 10;
struct stBackSelectUserCmd : public stLogonUserCmd
{
  stBackSelectUserCmd()
  {
    byParam = BACKSELECT_USERCMD_PARA;
  }
};

/// 发送图形验证码到客户端
const BYTE JPEG_PASSPORT_USERCMD_PARA = 11;
struct stJpegPassportUserCmd : public stLogonUserCmd
{
  stJpegPassportUserCmd()
  {
    byParam = JPEG_PASSPORT_USERCMD_PARA;
    size = 0;
  }
  WORD size;
  BYTE data[0];
};
// [ranqd] Add 服务器状态
enum SERVER_STATE 
{
	STATE_SERVICING	=	0, // 维护
	STATE_NOMARL	=	1, // 正常
	STATE_GOOD		=	2, // 良好
	STATE_BUSY		=	3, // 繁忙
	STATE_FULL		=	4, // 爆满
};
// [ranqd] Add 服务器类型
enum SERVER_TYPE
{
	TYPE_GENERAL		=	0, // 普通
	TYPE_PEACE		=	1,     // 和平
};

//发送国家信息
struct  Country_Info
{
  DWORD id;//国家id
  BYTE  enableRegister; //允许注册为1 不允许为0
  BYTE  enableLogin;    //允许登陆为1 不允许为0
  BYTE  Online_Statue;  // [ranqd] add 在线情况 参考 enum SERVER_STATE 
  BYTE  type;           // [ranqd] add 服务器类型 参考 enum SERVER_TYPE
  char pstrName[MAX_NAMESIZE];//国家名称
  Country_Info()
  {
    enableRegister = 0;
    enableLogin = 0;
  }
};
const BYTE SERVER_RETURN_COUNTRY_INFO = 12;
struct stCountryInfoUserCmd : public stLogonUserCmd
{
  stCountryInfoUserCmd()
  {
    byParam = SERVER_RETURN_COUNTRY_INFO;
    size = 0;
  }
  WORD size;
  Country_Info countryinfo[0];
};
// [ranqd] add 用户选择服务器命令
const BYTE CLIENT_SELETCT_COUNTRY = 13;
struct stSelectCountryUserCmd : public stLogonUserCmd
{
	stSelectCountryUserCmd()
	{
		byParam = CLIENT_SELETCT_COUNTRY;
		id = 0;
	}
	DWORD id;  // 选择的国家id 
};
//////////////////////////////////////////////////////////////
// 登陆指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 时间指令定义开始
//////////////////////////////////////////////////////////////
struct stTimerUserCmd : public stNullUserCmd
{
  stTimerUserCmd()
  {
    byCmd = TIME_USERCMD;
  }
};

/// 网关向用户发送游戏时间
const BYTE GAMETIME_TIMER_USERCMD_PARA = 1;
struct stGameTimeTimerUserCmd : public stTimerUserCmd 
{
  stGameTimeTimerUserCmd()
  {
    byParam = GAMETIME_TIMER_USERCMD_PARA;
  }

  QWORD qwGameTime;      /**< 游戏时间 */
};

/// 网关向用户请求时间
const BYTE REQUESTUSERGAMETIME_TIMER_USERCMD_PARA = 2;
struct stRequestUserGameTimeTimerUserCmd : public stTimerUserCmd
{
  stRequestUserGameTimeTimerUserCmd()
  {
    byParam = REQUESTUSERGAMETIME_TIMER_USERCMD_PARA;
  }

};

/// 用户向网关发送当前游戏时间
const BYTE USERGAMETIME_TIMER_USERCMD_PARA  = 3;
struct stUserGameTimeTimerUserCmd : public stTimerUserCmd
{
  stUserGameTimeTimerUserCmd()
  {
    byParam = USERGAMETIME_TIMER_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 用户临时ID */
  QWORD qwGameTime;      /**< 用户游戏时间 */
};

/// 用户ping命令(服务器原样返回)
const BYTE PING_TIMER_USERCMD_PARA = 4;
struct stPingTimeTimerUserCmd : public stTimerUserCmd
{
  stPingTimeTimerUserCmd()
  {
    byParam = PING_TIMER_USERCMD_PARA;
  }

};
//////////////////////////////////////////////////////////////
/// 时间指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 数据指令定义开始
//////////////////////////////////////////////////////////////
/// 定义人物状态
enum {
  USTATE_DEATH    = 0,//  死亡
  USTATE_UNARM =1,// 缴械
  USTATE_SUNDERARMOR =2,//破甲
  USTATE_BRANDISH =3,//刀光剑影
  USTATE_IMPREGNABLE =4,//固若金汤
  USTATE_CELENRITY_CHOP =5,//大卸八块
  USTATE_PHYSICS_ECHO =6 ,//物理反射
  USTATE_MAGIC_ECHO =7,//魔法反射
  USTATE_FURY =8,//狂暴
  USTATE_CRACK =9,//地裂斩
  USTATE_BOUNCE =10,//撞击
  USTATE_SEVER_MUSCLE =11,//断筋
  USTATE_BELLOW =12,//狮子吼
  USTATE_HALE_AND_HEARTY =13,//宝刀不老
  USTATE_GALLOW =14,//破胆
  USTATE_TERRIFIC =15,//翻江倒海
  USTATE_SANGUINARY =16,//嗜血
  USTATE_OFFER =17,//献祭
  USTATE_BOMB =18,//火蛋
  USTATE_WINDMILL =19,//风火轮
  USTATE_BLAZE_SHIELD =20,//火盾
  USTATE_EMBLAZE =21,//点燃
  USTATE_WISDOM =22,//智慧祷言
  USTATE_ICY_WATER =23,//冰霜结界
  USTATE_FROST =24,//冰冻
  USTATE_DECELERATE =25,//冰减速
  USTATE_ICE_SHIELD =26,//冰盾
  USTATE_SPUNK =27,//精神祷言
  USTATE_REJUVENATION =28,//回春
  USTATE_MAGIC_SHIELD =29,//护盾
  USTATE_INVINCIBLE =30,//无敌
  USTATE_GROW_ON =31,//伤害加深
  USTATE_VAMPIRE =32,//吸血
  USTATE_DREAD =33,//恐惧
  USTATE_MUM =34,//沉默
  USTATE_WEAKNESS =35,//虚弱
  USTATE_PAIN =36,//痛苦
  USTATE_COMA =37,//昏迷
  USTATE_BANISH =38,//放逐
  USTATE_ENTHRALL_TOXICANT =39,//迷魂散
  USTATE_TOXICANT =40,//致伤毒药
  USTATE_DEADLINESS_TOXICANT =41,//致命毒药
  USTATE_ABLEPSIA =42,//石灰粉
  USTATE_LULL_TOXICANT =43,//麻痹毒药
  USTATE_INCISE =44,//切割
  USTATE_AT_FULL_SPLIT =45,//玩命
  USTATE_ALERTNESS =46,//机敏
  USTATE_SCOUR =47,//疾跑

  //sky 新增建筑类NPC的建造状态(建筑类NPC专用)
  NPCSTATE_MAKE = 100,

  //sky 保持兼容
  USTATE_WAR				 = 265,
  USTATE_HIDE				 = 266,
  USTATE_PK					 = 267,
  USTATE_GUARD				 = 268, //新人保护状态
  USTATE_TOGETHER_WITH_TIGER = 269,
  USTATE_TOGETHER_WITH_DRAGON = 270,
  USTATE_DAOJISHI      = 271,
  USTATE_RELIVEWEAK    = 272,
  USTATE_START_QUEST   = 273,
  USTATE_FINISH_QUEST  = 274,
  USTATE_DOING_QUEST   = 275,
  USTATE_SITDOWN	   = 276,	//坐下
  USTATE_PRIVATE_STORE = 277,	//摆摊
  USTATE_ULTRA_EQUIPMENT = 278,
  USTATE_TEAM_ATTACK_ONE_DIM = 279,
  USTATE_TEAM_ATTACK_FLOW_CLOUD = 280,
  USTATE_TEAM_ATTACK_BIRD_FLAG = 281,

  USTATE_EXP_125       = 283, //经验1.25倍率状态
  USTATE_EXP_150       = 284, //经验1.50倍率状态
  USTATE_EXP_175       = 285, //经验1.75倍率状态
  //sky 新增战斗状态
  USTATE_PVE	= 286,	//sky PVE状态
  USTATE_PVP	= 287,	//sky PVP状态
  USTATE_RIDE	= 288,	//sky 骑马状态
  USTATE_SOUL	= 289,	//sky 灵魂状态

  MAX_STATE = 320                         /// 最大状态数
};

/// 定义善恶度
enum
{
  GOODNESS_0    = -120 & 0x0000FFFF,//英雄
  GOODNESS_1    = -60 & 0x0000FFFF, //侠士
  GOODNESS_2_1  = 0,       //普通1
  GOODNESS_2_2  = 0xFF000000,   //普通2
  GOODNESS_3    = 60,       //歹徒
  GOODNESS_4    = 120,       //恶徒
  GOODNESS_5    = 180,       //恶魔
  GOODNESS_6    = 300,       //魔头
  GOODNESS_7    = 10000,     //叛国
  
  GOODNESS_ATT  = 0x00010000,   //主动伤害别人
  GOODNESS_DEF  = 0x00010000 << 1        //自卫方
};

///定义善恶度结束

/// 检查某个状态是否设置
inline bool isset_state(const BYTE *state,const int teststate)
{
  return 0 != (state[teststate / 8] & (0xff & (1 << (teststate % 8))));
}

/// 设置某个状态
inline void set_state(BYTE *state,const int teststate)
{
  state[teststate / 8] |= (0xff & (1 << (teststate % 8)));
}

/// 清除某个状态
inline void clear_state(BYTE *state,const int teststate)
{
  state[teststate / 8] &= (0xff & (~(1 << (teststate % 8))));
}

struct t_MapBuildingData{
  DWORD dwMapBuildingTempID;      /**< 建筑物的临时ID */
  DWORD dwBuildingDataID;        /**< 建筑物的数据ID */
  DWORD x;
  DWORD y;
  DWORD dwContract;          /**< 地契编号 */
  char pstrName[MAX_NAMESIZE];    /**< 建筑物的名称 */
  char pstrUserName[MAX_NAMESIZE];  /**< 建筑物的所有者名称 */
};

struct t_MapObjectData {
  DWORD dwMapObjectTempID;        /**< 物品的临时ID */
  DWORD dwObjectID;                       /**< 物品的数据ID */
  char pstrName[MAX_NAMESIZE];      /**<  物品名 */
  DWORD x;
  DWORD y;
  DWORD wdNumber;                         /**< 数量 */
  WORD  wdLevel;                          /**< 等级 */
  BYTE upgrade;
  BYTE kind;
  DWORD dwOwner;
  //sky 物品拾取保护者的名字
  char	 strName[MAX_NAMESIZE+1];
};

//宠物的类型
enum petType
{
  PET_TYPE_NOTPET			= 0,//不是宠物
  PET_TYPE_RIDE				= 1,//坐骑
  PET_TYPE_PET				= 2,//宠物
  PET_TYPE_SUMMON			= 3,//召唤兽
  PET_TYPE_TOTEM			= 4,//图腾
  PET_TYPE_GUARDNPC			= 5,//要护卫的npc
  PET_TYPE_SEMI				= 6,//半宠物，跟主人同生同死，AI完全没关系
  PET_TYPE_CARTOON			= 7,//卡通宝宝
  PET_TYPE_TURRET			= 8	//sky 炮塔
};

struct t_NpcData {
	DWORD MaxHp;				//sky Npc最大HP
	DWORD NowHp;				//sky Npc当前HP
	DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
	DWORD dwNpcDataID;      /**< npc的数据ID */
	WORD  movespeed;    /// 移动速度

	BYTE byDirect;        /**< Npc的方向 */
	BYTE level;///等级
};
struct t_MapNpcData :public t_NpcData
{
  BYTE byState[(MAX_STATE + 7) / 8];      /**< Npc的状态 */
};
struct t_MapNpcDataState :public t_NpcData
{
  t_MapNpcDataState()
  {
    num=0;
  }
  BYTE num;     ///带状态的数量
  WORD state[0];    ///状态列表
};

struct t_MapPetData {
  DWORD tempID;//npc的临时ID

  char name[MAX_NAMESIZE]; //npc的名称
  BYTE masterType;  ///主人的类型  0：玩家 1：npc
  DWORD masterID;  ///主人的id -1：没有主人
  char masterName[MAX_NAMESIZE];///主任的名字
  BYTE pet_type;//宠物类型
};

struct t_MapUserSculpt{
  DWORD dwHorseID;          /// 马牌编号
  DWORD dwHairID;            /// 头发类型
  DWORD dwBodyID;            /// 身体物品ID
  DWORD dwLeftHandID;          /// 左手物品ID
  DWORD dwRightHandID;        /// 右手物品ID
};

//队伍标志
enum{
  TEAD_STATE_NONE,
  TEAD_STATE_MEMBER,
  TEAM_STATE_LEADER,
};

/// 用户本身的数据，不包括状态
struct t_UserData
{
  DWORD dwUserTempID;          //// 用户临时ID

  char  name[MAX_NAMESIZE + 1];    /// 角色名称
  WORD  type;              /// 职业类型
  //WORD  sex;              /// 性别
  WORD  face;              /// 头象
  DWORD goodness;            /// 善恶度

  t_MapUserSculpt sculpt;
  DWORD dwHairRGB;          /// 头发颜色0xffrrggbb
  DWORD dwBodyColorSystem;      /// 衣服系统颜色0xffrrggbb
  DWORD dwBodyColorCustom;      /// 衣服定制颜色0xffrrggbb
  DWORD dwLeftWeaponColor;      /// 左手武器颜色0xffrrggbb
  DWORD dwRightWeaponColor;      /// 右手武器颜色0xffrrggbb
  WORD  attackspeed;          /// 攻击速度
  WORD  movespeed;          /// 移动速度
  BYTE country;            /// 国家
  DWORD dwChangeFaceID;        //易容后的NPC的类型ID
  //BYTE live_skills[6];         //生活技能等级
  BYTE level;              //Level : 1(<10)   11(>=10)
  DWORD exploit;        // 功勋值
  DWORD useJob;        // sky 角色职业
  
  DWORD dwUnionID;      // 帮会ID
  DWORD dwSeptID;        // 家族ID
  
  char  caption[MAX_NAMESIZE];    // 顶部头衔（某城城主或某国国王）
  DWORD dwTeamState;          // 队伍状态
  DWORD dwArmyState;      //1为队长，2为将军,0为未加入军队
};

struct t_MapUserData : public t_UserData 
{
  BYTE state[(MAX_STATE + 7) / 8];  /// 角色状态
};
struct t_MapUserDataState : public t_UserData 
{
  t_MapUserDataState()
  {
    num=0;
  }
  BYTE num;     ///带状态的数量
  WORD state[0];    ///状态列表
};

struct t_MainUserData 
{
  DWORD dwUserTempID;        /// 用户临时ID
  WORD  level;          /// 角色等级
  DWORD hp;            /// 当前生命值
  DWORD maxhp;          /// 最大生命值
  DWORD resumehp;          /// 生命值恢复
  DWORD mp;            /// 当前法术值
  DWORD maxmp;          /// 最大法术值
  DWORD resumemp;          /// 法术值恢复
  DWORD sp;            /// 当前体力值
  DWORD maxsp;          /// 最大体力值
  DWORD resumesp;          /// 体力值恢复
  DWORD pdamage;          /// 最小物理攻击力
  DWORD maxpdamage;        /// 最大物理攻击力
  DWORD mdamage;          /// 最小法术攻击力
  DWORD maxmdamage;        /// 最大法术攻击力
  DWORD pdefence;          /// 物理防御力
  DWORD mdefence;          /// 法术防御力
  QWORD exp;            /// 当前经验值
  QWORD nextexp;          /// 升级经验值
  WORD  attackrating;        /// 攻击命中
  WORD  attackdodge;        /// 攻击躲避
  WORD  bang;            /// 重击
  WORD  charm;          /// 魅力值
  DWORD  zs;             /// 转身
  union {
    struct {
      WORD wdCon;  //体质
      WORD wdStr;  //体力
      WORD wdDex;  //敏捷
      WORD wdInt;  //智力
      WORD wdMen;  //精神
    };
    WORD wdProperty[5];
  };
  WORD  skillPoint;                   /// 技能点数
  WORD  points;                       /// 点数
  DWORD country;            /// 国家
  WORD  pkmode;                       /// pk模式


  DWORD stdpdamage;          /// 标准物理攻击力
  DWORD stdmdamage;          /// 标准法术攻击力
  DWORD stdpdefence;          /// 标准物理防御力
  DWORD stdmdefence;          /// 标准法术防御力
  WORD  stdbang;            /// 标准重击率
  union {
    struct {
      WORD wdStdCon;  //体质
      WORD wdStdStr;  //体力
      WORD wdStdDex;  //敏捷
      WORD wdStdInt;  //智力
      WORD wdStdMen;  //精神
    };
    WORD wdStdProperty[5];
  };
  WORD wdTire; /// 疲劳状态 0为非 1为疲劳
  DWORD fivetype;  ///五行类型
  DWORD fivepoint;///五行点数
  DWORD honor;///荣誉值
  DWORD maxhonor;///最大荣誉值
  DWORD gold;  ///金币数
  DWORD ticket; //点券数
  DWORD bitmask;          /// 角色掩码
};

struct stDataUserCmd : public stNullUserCmd
{
  stDataUserCmd()
  {
    byCmd = DATA_USERCMD;
  }
};

/// 主用户数据
const BYTE MAIN_USER_DATA_USERCMD_PARA = 1;
  struct stMainUserDataUserCmd : public stDataUserCmd {
    stMainUserDataUserCmd()
    {
      byParam = MAIN_USER_DATA_USERCMD_PARA;
    }

    t_MainUserData data;
  };
/*
enum {
  DECTYPE_POWER, /// 体力
  DECTYPE_STRENGTH,/// 力量
  DECTYPE_INTELLECTUALITY,/// 智力
  DECTYPE_CORPOREITY,/// 体质
  DECTYPE_DEXTERITY      /// 敏捷
};
/// 减少剩余点数，增加到体力等中
const BYTE DECREMAINDER_DATA_USERCMD_PARA = 2;
  struct stDecRemainderDataUserCmd : public stDataUserCmd{
    stDecRemainderDataUserCmd()
    {
      byParam = DECREMAINDER_DATA_USERCMD_PARA;
    }

    BYTE byDecType;        **< 加点类型 *
  };

*/

/// 设置用户生命和魔法
const BYTE SETHPANDMP_DATA_USERCMD_PARA = 3;
  struct stSetHPAndMPDataUserCmd : public stDataUserCmd{
    stSetHPAndMPDataUserCmd()
    {
      byParam = SETHPANDMP_DATA_USERCMD_PARA;
    }

    DWORD dwHP;          /**< HP */
    DWORD dwMP;          /**< MP */
    //DWORD dwSP;          /**< SP */
  };

enum {
  MAP_SETTING_RIDE  = 0x00000001,/// 大陆可以骑马
  MAP_SETTING_WEATHER  = 0x00000002  /// 大陆有雨雪天气变化
};
/// 地图信息
const BYTE MAPSCREENSIZE_DATA_USERCMD_PARA = 28;
  struct stMapScreenSizeDataUserCmd : public stDataUserCmd{
    stMapScreenSizeDataUserCmd()
    {
      byParam = MAPSCREENSIZE_DATA_USERCMD_PARA;
    }

    DWORD width;    /**< 场景宽 */
    DWORD height;    /**< 场景高 */
    char pstrMapName[MAX_NAMESIZE];  /**< 大陆名称 */
    char pstrFilename[MAX_NAMESIZE];  /**< 文件名称 */
    DWORD setting;        /**< 大陆标志 */
    DWORD rgb;          /**< 颜色标志0x00rrggbb */
    char pstrGroupName[MAX_NAMESIZE];  /**< 服务器组名称 */
    char pstrCountryName[MAX_NAMESIZE];  /**< 国家名称 */
    char pstrCityName[MAX_NAMESIZE];  /**< 城市名称 */
    int mainRoleX;  
    int mainRoleY;
    short npc_count;
    struct {
      DWORD id,x,y;
    } npc_list[0];
  };

//客户端加载地图完成
const BYTE LOADMAPOK_DATA_USERCMD_PARA = 29;
  struct stLoadMapOKDataUserCmd : public stDataUserCmd{
    stLoadMapOKDataUserCmd()
    {
      byParam = LOADMAPOK_DATA_USERCMD_PARA;
    }
  };

/// 角色的等级排名
const BYTE LEVELDEGREE_DATA_USERCMD_PARA = 30;
  struct stLevelDegreeDataUserCmd : public stDataUserCmd{
    stLevelDegreeDataUserCmd()
    {
      byParam = LEVELDEGREE_DATA_USERCMD_PARA;
    }
    WORD degree; // 1-2000名
  };

/// 发送特征码文件
const BYTE STAMP_DATA_USERCMD_PARA = 51;
struct stStampDataUserCmd : public stDataUserCmd
{
  bool check;//是否进行外挂检测
  DWORD size;
  BYTE bin[0];//特征码文件
  stStampDataUserCmd()
  {
    byParam = STAMP_DATA_USERCMD_PARA;

    check = false;
    size = 0;
  }
};

/// 客户端进行外挂检测
const BYTE STAMP_CHECK_USERCMD_PARA = 52;
struct stStampCheckUserCmd : public stDataUserCmd
{
  DWORD flag;//0 关; 1 开
  stStampCheckUserCmd()
  {
    byParam = STAMP_CHECK_USERCMD_PARA;

    flag = 0;
  }
};

/// 发送当前合并版本号
const BYTE MERGE_VERSION_CHECK_USERCMD_PARA = 53;
struct stMergeVersionCheckUserCmd : public stDataUserCmd
{
  stMergeVersionCheckUserCmd()
  {
    byParam = MERGE_VERSION_CHECK_USERCMD_PARA;
    dwMergeVersion = 0;
  }

  DWORD dwMergeVersion;
};

/// 发送初始化信息结束
const BYTE ENDOFINITDATA_DATA_USERCMD_PARA = 255;
  struct stEndOfInitDataDataUserCmd : public stDataUserCmd{
    stEndOfInitDataDataUserCmd()
    {
      byParam = ENDOFINITDATA_DATA_USERCMD_PARA;
    }
  };

//////////////////////////////////////////////////////////////
/// 数据指令定义完成
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 地图数据指令定义开始
//////////////////////////////////////////////////////////////
  struct stMapScreenUserCmd : public stNullUserCmd{
    stMapScreenUserCmd()
    {
      byCmd = MAPSCREEN_USERCMD;
    }
  };


/// 地图上增加人物
const BYTE ADDUSER_MAPSCREEN_USERCMD_PARA = 10;
  struct stAddUserMapScreenUserCmd : public stMapScreenUserCmd {
    stAddUserMapScreenUserCmd()
    {
      byParam = ADDUSER_MAPSCREEN_USERCMD_PARA;
    }
    t_MapUserData data;
  };

/// 地图上面删除人物
const BYTE REMOVEUSER_MAPSCREEN_USERCMD_PARA = 11;
  struct stRemoveUserMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveUserMapScreenUserCmd()
    {
      byParam = REMOVEUSER_MAPSCREEN_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
  };

/// 用户请求其他用户数据
const BYTE REQUESTUSERDATA_MAPSCREEN_USERCMD_PARA = 12;
  struct stRequestUserDataMapScreenUserCmd : public stMapScreenUserCmd{
    stRequestUserDataMapScreenUserCmd()
    {
      byParam = REQUESTUSERDATA_MAPSCREEN_USERCMD_PARA;
    }

    WORD size;
    DWORD dwUserTempID[0];  //临时编号列表(DWORD)
  };

/// 用户骑马
const BYTE RIDE_MAPSCREEN_USERCMD_PARA = 13;
struct stRideMapScreenUserCmd : public stMapScreenUserCmd
{
  stRideMapScreenUserCmd()
  {
    byParam = RIDE_MAPSCREEN_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 用户临时ID */
  BYTE bySwitch;        /**< 骑马开关：１是骑马，０是下马 */
};

/// 刷新角色状态
const BYTE REFRESHSTATE_MAPSCREEN_USERCMD_PARA = 14;
struct stRefreshStateMapScreenUserCmd : public stMapScreenUserCmd{
  stRefreshStateMapScreenUserCmd()
  {
    byParam = REFRESHSTATE_MAPSCREEN_USERCMD_PARA;
    bzero(state,sizeof(state));
  }
  DWORD dwUserTempID;      /**< 用户临时ID */
  BYTE state[(MAX_STATE + 7) / 8];  /// 角色状态
  
};

/// 定义物品动作类型
enum{
    OBJECTACTION_DROP,/// 掉落物品
      OBJECTACTION_UPDATE,/// 更新物品数据
};
/// 在地图上增加物品
const BYTE ADDMAPOBJECT_MAPSCREEN_USERCMD_PARA = 20;
  struct stAddMapObjectMapScreenUserCmd  : public stMapScreenUserCmd{
    stAddMapObjectMapScreenUserCmd()
    {
      byParam = ADDMAPOBJECT_MAPSCREEN_USERCMD_PARA;
      bzero(&data,sizeof(data));
    }
    BYTE  action;
    t_MapObjectData data;
  };

/// 在地图上删除物品
const BYTE REMOVEMAPOBJECT_MAPSCREEN_USERCMD_PARA = 21;
  struct stRemoveMapObjectMapScreenUserCmd  : public stMapScreenUserCmd{
    stRemoveMapObjectMapScreenUserCmd()
    {
      byParam = REMOVEMAPOBJECT_MAPSCREEN_USERCMD_PARA;
    }
    DWORD dwMapObjectTempID;  /**< 物品的临时ID */
  };

/// 在地图上增加建筑物
const BYTE ADDMAPBUILDING_MAPSCREEN_USERCMD_PARA = 30;
  struct stAddMapBuildingMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapBuildingMapScreenUserCmd()
    {
      byParam = ADDMAPBUILDING_MAPSCREEN_USERCMD_PARA;
    }

    t_MapBuildingData data;
  };


/// 在地图上删除建筑物
const BYTE REMOVEMAPBUILDING_MAPSCREEN_USERCMD_PARA = 31;
  struct stRemoveMapBuildingMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveMapBuildingMapScreenUserCmd()
    {
      byParam = REMOVEMAPBUILDING_MAPSCREEN_USERCMD_PARA;
    }

    DWORD dwMapBuildingTempID;  /**< 建筑物的临时ID */
  };

///人物使用易容术
const BYTE CHANGEFACE_MAPSCREEN_USERCMD_PARA = 32;
  struct stChangeFaceMapScreenUserCmd : public stMapScreenUserCmd{
    stChangeFaceMapScreenUserCmd()
    {
      byParam = CHANGEFACE_MAPSCREEN_USERCMD_PARA;
    }

    DWORD  dwUserTempID;    //用户临时ID
        DWORD  dwChangeFaceID;    //易容后的NPC的类型ID
  };

/// 在地图上增加NPC
const BYTE ADDMAPNPC_MAPSCREEN_USERCMD_PARA = 50;
  struct stAddMapNpcMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapNpcMapScreenUserCmd()
    {
      byParam = ADDMAPNPC_MAPSCREEN_USERCMD_PARA;
    }

    t_MapNpcData data;
  };

/// 在地图上删除NPC
const BYTE REMOVEMAPNPC_MAPSCREEN_USERCMD_PARA = 51;
  struct stRemoveMapNpcMapScreenUserCmd : public stMapScreenUserCmd{
    stRemoveMapNpcMapScreenUserCmd()
    {
      byParam = REMOVEMAPNPC_MAPSCREEN_USERCMD_PARA;
    }
    DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
  };

/// 请求Npc数据
const BYTE REQUESTMAPNPCDATA_MAPSCREEN_USERCMD_PARA = 52;
  struct stRequestMapNpcDataMapScreenUserCmd : public stMapScreenUserCmd{
    stRequestMapNpcDataMapScreenUserCmd()
    {
      byParam = REQUESTMAPNPCDATA_MAPSCREEN_USERCMD_PARA;
    }

    WORD size;
    DWORD dwNpcTempID[0];  //临时编号列表(DWORD)
  };

/// Npc血槽
const BYTE NPCHP_MAPSCREEN_USERCMD_PARA = 53;
  struct stNPCHPMapScreenUserCmd : public stMapScreenUserCmd{
    stNPCHPMapScreenUserCmd()
    {
      byParam = NPCHP_MAPSCREEN_USERCMD_PARA;
    }
//BEGIN_MUTABLE_VARS
    DWORD dwMapNpcDataPosition;  /**< npc的数据位置 */
    DWORD dwHP;          /**< HP */
    DWORD dwMaxHP;        /**< MaxHP */
//END_MUTABLE_VARS
  };

// NPC 人物 位置信息
struct stNpcPosition{
  DWORD dwTempID;        //目标编号
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};

// NPC 人物 TEMPID信息
struct stNpcTempID{
  DWORD dwTempID;        //目标编号
};

/// 对9屏用户和NPC
const BYTE ALL_MAPSCREEN_USERCMD_PARA = 54;
  struct stAllMapScreenUserCmd : public stMapScreenUserCmd{
    stAllMapScreenUserCmd()
    {
      byParam = ALL_MAPSCREEN_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    stNpcTempID psi[0];
  };

struct t_MapUserDataPos :public t_MapUserData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};
struct t_MapUserDataPosState :public t_UserData
{
/*
  t_MapUserDataPosState()
  {
    num=0;
  } 
// */
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
  BYTE num;     ///带状态的数量
  WORD state[1];    ///状态列表
};
struct t_MapNpcDataPos :public t_MapNpcData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};
struct t_MapNpcDataPosState :public t_NpcData
{
/*
  t_MapNpcDataPosState()
  {
    num=0;
  } 
// */
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
  BYTE num;     ///带状态的数量
  WORD state[1];    ///状态列表
};
struct t_MapBuildingDataPos :public t_MapBuildingData
{
  WORD x;          /**< 坐标*/
  WORD y;        
  BYTE byDir;          // 方向（如果为 -1 则不确定方向）
};

// 地图数据打包发送
const BYTE MAPDATA_MAPSCREEN_USERCMD_PARA = 55;
  struct stMapDataMapScreenUserCmd : public stMapScreenUserCmd{
    stMapDataMapScreenUserCmd()
    {
      byParam = MAPDATA_MAPSCREEN_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    union
    {
      t_MapUserDataPos mud[1];
      t_MapNpcDataPos mnd[1];
      t_MapBuildingDataPos mbd[1];
      t_MapPetData mpd[1];
    };
  };

#define SELECTED_HPMP_PROPERTY_USERCMD_PARA 56//通知选择自己的玩家hp和mp的变化
struct stRTSelectedHpMpPropertyUserCmd : public stMapScreenUserCmd
{
  stRTSelectedHpMpPropertyUserCmd()
  {
    byParam = SELECTED_HPMP_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
//BEGIN_MUTABLE_VARS
  DWORD dwTempID;//临时编号
  DWORD dwHP;//当前血
  DWORD dwMaxHp;//最大hp
  DWORD dwMP;//当前mp
  DWORD dwMaxMp;//最大mp
//END_MUTABLE_VARS  
};
/// sky 修改为跟改地图上物品保护(消息不再是只删除拉有可能只是要跟改保护对象)
const BYTE CLEAR_OBJECTOWNER_MAPSCREEN_USERCMD_PARA = 58;
struct stClearObjectOwnerMapScreenUserCmd  : public stMapScreenUserCmd{
	stClearObjectOwnerMapScreenUserCmd()
	{
		byParam = CLEAR_OBJECTOWNER_MAPSCREEN_USERCMD_PARA;
		tempid = 0;  //sky为0的时候就是要删除这个物品的保护
		strName[0] = 0;
	}
	DWORD dwMapObjectTempID;  /**< 物品的临时ID */
	DWORD tempid;
	char  strName[MAX_NAMESIZE+1];
};
/// 在地图上增加NPC和坐标
const BYTE ADDMAPNPC_AND_POS_MAPSCREEN_USERCMD_PARA = 59;
struct stAddMapNpcAndPosMapScreenUserCmd : public stMapScreenUserCmd{
	stAddMapNpcAndPosMapScreenUserCmd()
	{
		byParam = ADDMAPNPC_AND_POS_MAPSCREEN_USERCMD_PARA;
	}

	t_MapNpcDataPos data;
};

/// 地图上增加人物和坐标
const BYTE ADDUSER_AND_POS_MAPSCREEN_USERCMD_PARA = 60;
  struct stAddUserAndPosMapScreenUserCmd : public stMapScreenUserCmd {
    stAddUserAndPosMapScreenUserCmd()
    {
      byParam = ADDUSER_AND_POS_MAPSCREEN_USERCMD_PARA;
    }
    t_MapUserDataPos data;
  };
/// 批量删除NPC指令
const BYTE BATCHREMOVENPC_MAPSCREEN_USERCMD_PARA = 61;
  struct stBatchRemoveNpcMapScreenUserCmd : public stMapScreenUserCmd {
    stBatchRemoveNpcMapScreenUserCmd()
    {       
      byParam = BATCHREMOVENPC_MAPSCREEN_USERCMD_PARA;
    }
    WORD  num;
    DWORD   id[0];
  };

/// 批量删除USER指令
const BYTE BATCHREMOVEUSER_MAPSCREEN_USERCMD_PARA = 62;
  struct stBatchRemoveUserMapScreenUserCmd : public stMapScreenUserCmd {
    stBatchRemoveUserMapScreenUserCmd()
    {       
      byParam = BATCHREMOVEUSER_MAPSCREEN_USERCMD_PARA;
    }
    WORD  num;
    DWORD   id[0];
  };
/// 设置角色状态
const BYTE SETSTATE_MAPSCREEN_USERCMD_PARA = 63;
struct stSetStateMapScreenUserCmd : public stMapScreenUserCmd{
  stSetStateMapScreenUserCmd()
  {
    byParam = SETSTATE_MAPSCREEN_USERCMD_PARA;
  }
  BYTE  type;    /**<类型 enumMapDataType*/
  DWORD  dwTempID;      /**< 用户临时ID */
  WORD  wdState;  /// 需要设置的状态
};
/// 取消角色状态
const BYTE CLEARSTATE_MAPSCREEN_USERCMD_PARA = 64;
struct stClearStateMapScreenUserCmd : public stMapScreenUserCmd{
  stClearStateMapScreenUserCmd()
  {
    byParam = CLEARSTATE_MAPSCREEN_USERCMD_PARA;
  }
  BYTE  type;    /**<类型 enumMapDataType*/
  DWORD  dwTempID;      /**< 用户临时ID */
  WORD  wdState;  /// 需要取消的状态
};
/// 在地图上增加Npc和宠物数据
const BYTE ADDMAPNPCPET_MAPSCREEN_USERCMD_PARA = 65;
  struct stAddMapNpcPetMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapNpcPetMapScreenUserCmd()
    {
      byParam = ADDMAPNPCPET_MAPSCREEN_USERCMD_PARA;
    }

    t_MapNpcDataPos data;
    t_MapPetData pet; 
  };
/// 在地图上增加宠物数据
const BYTE ADDMAPPET_MAPSCREEN_USERCMD_PARA = 66;
  struct stAddMapPetMapScreenUserCmd : public stMapScreenUserCmd{
    stAddMapPetMapScreenUserCmd()
    {
      byParam = ADDMAPPET_MAPSCREEN_USERCMD_PARA;
    }

    t_MapPetData pet; 
  };
/// 设置角色善恶值
const BYTE GOODNESS_MAPSCREEN_USERCMD_PARA = 67;
struct stGoodnessStateMapScreenUserCmd : public stMapScreenUserCmd{
  stGoodnessStateMapScreenUserCmd()
  {
    byParam = GOODNESS_MAPSCREEN_USERCMD_PARA;
  }
  DWORD  dwTempID;      /**< 用户临时ID */
  DWORD  dwGoodness;  /// 善恶值
};
/// 地图上增加人物
const BYTE ADDUSER_MAPSCREEN_STATE_USERCMD_PARA = 68;
  struct stAddUserMapScreenStateUserCmd : public stMapScreenUserCmd {
    stAddUserMapScreenStateUserCmd()
    {
      byParam = ADDUSER_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapUserDataState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加NPC
const BYTE ADDMAPNPC_MAPSCREEN_STATE_USERCMD_PARA = 69;
  struct stAddMapNpcMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPC_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapNpcDataState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 地图上增加人物和坐标
const BYTE ADDUSER_AND_POS_MAPSCREEN_STATE_USERCMD_PARA = 70;
  struct stAddUserAndPosMapScreenStateUserCmd : public stMapScreenUserCmd {
    stAddUserAndPosMapScreenStateUserCmd()
    {
      byParam = ADDUSER_AND_POS_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapUserDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加NPC和坐标
const BYTE ADDMAPNPC_AND_POS_MAPSCREEN_STATE_USERCMD_PARA = 71;
  struct stAddMapNpcAndPosMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcAndPosMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPC_AND_POS_MAPSCREEN_STATE_USERCMD_PARA;
    }
    t_MapNpcDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };
/// 在地图上增加Npc和宠物数据
const BYTE ADDMAPNPCPET_MAPSCREEN_STATE_USERCMD_PARA = 72;
  struct stAddMapNpcPetMapScreenStateUserCmd : public stMapScreenUserCmd{
    stAddMapNpcPetMapScreenStateUserCmd()
    {
      byParam = ADDMAPNPCPET_MAPSCREEN_STATE_USERCMD_PARA;
    }

    t_MapPetData pet; 
    t_MapNpcDataPosState data;
    int size()
    {
      return sizeof(*this) + data.num * sizeof(data.state[0]);
    }
  };


// 地图数据打包发送
const BYTE MAPDATA_MAPSCREEN_STATE_USERCMD_PARA = 73;
  struct stMapDataMapScreenStateUserCmd : public stMapScreenUserCmd{
    stMapDataMapScreenStateUserCmd()
    {
      byParam = MAPDATA_MAPSCREEN_STATE_USERCMD_PARA;
    }

    MapData_ItemHeader mdih;
    union
    {
      t_MapUserDataPosState mud[1];
      t_MapNpcDataPosState mnd[1];
      t_MapBuildingDataPos mbd[1];
      t_MapPetData mpd[1];
    };
  };


/*
/// 刷新宠物信息
const BYTE ADD_PET_MAPSCREEN_USERCMD_PARA = 61;
  struct stAddPetMapScreenUserCmd : public stMapScreenUserCmd {
    stAddPetMapScreenUserCmd()
    {
      byParam = ADD_PET_MAPSCREEN_USERCMD_PARA;
    }
    BYTE size;
    t_MapPetData data[0];
  };
  */
//////////////////////////////////////////////////////////////
/// 地图数据指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 魔法指令定义开始
//////////////////////////////////////////////////////////////
  struct stMagicUserCmd : public stNullUserCmd{
    stMagicUserCmd()
    {
      byCmd = MAGIC_USERCMD;
    }
  };

/// 定义攻击类型
enum ATTACKTYPE{
  ATTACKTYPE_U2U,/// 用户攻击用户
  ATTACKTYPE_U2N,/// 用户攻击Npc
  ATTACKTYPE_N2U,/// Npc攻击用户
  ATTACKTYPE_U2B,/// 用户攻击建筑
  ATTACKTYPE_U2P,/// 用户攻击点
  ATTACKTYPE_N2N  /// Npc攻击Npc
};

enum AniTypeEnum
{
Ani_Null = 0,

  Ani_Wait,Ani_Stand = Ani_Wait,// 站立
  Ani_Walk,     // 走
  Ani_Run,     // 跑

  Ani_Attack,     // 攻击
  Ani_Attack2,   // 攻击2
  Ani_Attack3,   // 攻击3

  Ani_Magic,     // 魔法攻击
  Ani_Magic2,     // 魔法攻击2
  Ani_Magic3,     // 魔法攻击3

  Ani_Bow,     // 射箭
  Ani_Bow2,     // 努攻击

  Ani_Hurt,     // 受伤(被击)
  Ani_Die,     // 死亡

  Ani_Sit,     // 打坐

  Ani_Ride_Wait,   // 骑马站立
  Ani_Ride_Walk,   // 骑马走
  Ani_Ride_Run,   // 骑马跑

  Ani_Ride_Attack, // 骑马攻击
  Ani_Ride_Magic,   // 骑马施法

  Ani_Ride_Hurt,   // 受伤(被击)
  Ani_Ride_Die,   // 骑马死亡

  Ani_Appear,     // 出现(重生)

  Ani_Attack_Stand, // 攻击站立
  Ani_Attack2_Stand, // 攻击2站立
  Ani_Attack3_Stand, // 攻击2站立

  Ani_Magic_Stand, // 魔法攻击站立
  Ani_Magic2_Stand, // 魔法2攻击站立
  Ani_Magic3_Stand, // 魔法3攻击站立

  Ani_Bow_Stand,   // 弓箭攻击站立
  Ani_Bow2_Stand,   // 努攻击站立

  Ani_Ride_Attack_Stand,// 骑马攻击站立
  Ani_Ride_Magic_Stand,// 骑马施法站立

  Ani_Back,     // 后退
  Ani_Ride_Back,   // 骑马后退

  Ani_Ride_Bow,   // 骑马射箭
  Ani_Ride_Bow_Stand, // 骑马射箭站立

  Ani_Fly_Walk,   // 飞行慢速
  Ani_Fly_Run,   // 飞行快速

  Ani_Fly_Hurt,   // 飞行被击
  Ani_Fly_Die,   // 飞行死亡

  Ani_Gather,     // 采药

  Ani_FirstRun,   // 第一次走

  Ani_Idle0,
  Ani_Idle1,
  Ani_Idle2,
  Ani_Idle3,

  Ani_Gather_Stand,
  Ani_OpenBox_Stand,
  Ani_Num
};

/// 攻击指令
const BYTE MAGIC_USERCMD_PARA = 5;
struct stAttackMagicUserCmd : public stMagicUserCmd{

  stAttackMagicUserCmd()
  {
    byParam = MAGIC_USERCMD_PARA;
  }

//BEGIN_MUTABLE_VARS
  DWORD dwUserTempID;      /**< 攻击临时编号 */
  DWORD dwDefenceTempID;    /**< 防御临时编号 */

  WORD wdMagicType;      /**< 魔法编号 */

  WORD xDes;          /**< 目标点 */
  WORD yDes;          /**< 目标点 */
//END_MUTABLE_VARS  
  
  BYTE byDirect;        /**< 攻击方向 */
  BYTE byAttackType;      /**< 攻击类型：ATTACKTYPE_U2U,ATTACKTYPE_U2N,ATTACKTYPE_N2U */
  BYTE byAction;        // 攻击动作  AniTypeEnum ( Ani_Null 为不确定的，由客户端确定 )
  DWORD dwTempIDList[1];    // 攻击目标列表
};

enum {
  RTMAGIC_FAILURE,/// 攻击失败
  RTMAGIC_DUCK,/// 防御闪避
  RTMAGIC_FREEZE,/// 冰冻
  RTMAGIC_SPEEDUP,/// 加速
  RTMAGIC_POISON,/// 中毒
  RTMAGIC_PLAGUE,/// 瘟疫
  RTMAGIC_LANDIFICATION,/// 石化
  RTMAGIC_VAMPIRE,/// 吸血
  RTMAGIC_VAMPIREMAGIC,/// 吸魔
  RTMAGIC_HIDE,/// 隐身
  RTMAGIC_BLANKSCREEN,/// 黑屏
  RTMAGIC_SUCCESS,/// 攻击成功
  RTMAGIC_ATTACKED,/// 被击
  RTMAGIC_DEFENCE      /// 格挡
};

/// 攻击返回给自己
const BYTE RTMAGIC_USERCMD_PARA = 6;
struct stRTMagicUserCmd : public stMagicUserCmd{

  stRTMagicUserCmd()
  {
    byParam = RTMAGIC_USERCMD_PARA;
  }

  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  BYTE byRetcode;        /**< 返回代码：RTMAGIC_SUCCESS,RTMAGIC_FAILURE... */
  BYTE byDirect;        /**< 方向 */
  BYTE bySrc;          /**< 攻击者类型：enumMapDataType */

  DWORD dwSrcTempID;      /**< 攻击者临时编号 */

  DWORD dwHP;          // 当前血
  SDWORD sdwHP;          /**< 扣血 */
  BYTE byLuck;        //幸运，为1表示这是幸运攻击，为0表示普通攻击结果
};

enum enumPopEffect
{
  POP_HP,
  POP_MP,
  POP_NUM,
};

/// 返回目标坐标伤血通知
const BYTE OBJECT_HPMP_POP_PARA = 11;
struct stObjectHpMpPopUserCmd : public stMagicUserCmd{

  stObjectHpMpPopUserCmd()
  {
    byParam = OBJECT_HPMP_POP_PARA;
  }

  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE byTarget;        /**< 目标类型：enumMapDataType */

  int vChange;        /**< >0 :加    <0 :扣*/
  enumPopEffect  type;
};

/// 返回目标坐标
const BYTE RTMAGIC_POS_USERCMD_PARA  = 12;
struct stRTMagicPosUserCmd : public stMagicUserCmd{

  stRTMagicPosUserCmd()
  {
    byParam = RTMAGIC_POS_USERCMD_PARA;
  }
  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  stNpcPosition pos;
};

/// 防御方后退
const BYTE BACKOFF_USERCMD_PARA  = 7;
  struct stBackOffMagicUserCmd : public stMagicUserCmd {
    stBackOffMagicUserCmd()
    {
      byParam = BACKOFF_USERCMD_PARA;
    }

    DWORD dwTempID;        /**< 防御方临时编号 */
    BYTE byType;        /**< 目标类型 enumMapDataType */
    BYTE byDirect;        /**< 后退的方向 */
    DWORD x;
    DWORD y;
  };

/// 攻击Npc得到经验
const BYTE OBTAINEXP_USERCMD_PARA = 8;
  struct stObtainExpUserCmd : public stMagicUserCmd{
    stObtainExpUserCmd()
    {
      byParam = OBTAINEXP_USERCMD_PARA;
    }

    DWORD dwTempID;        /**< 经验值来源临时编号 */
    BYTE byType;        /**< 经验值来源 enumMapDataType */
    DWORD dwExp;        /**< 得到的经验 */
    QWORD dwUserExp;      /**< 人物当前经验值的经验 */
  };

/// Npc死亡
const BYTE NPCDEATH_USERCMD_PARA = 9;
  struct stNpcDeathUserCmd : public stMagicUserCmd{
    stNpcDeathUserCmd()
    {
      byParam = NPCDEATH_USERCMD_PARA;
    }

    DWORD dwNpcTempID;      /**< Npc临时编号 */
  };

/// 人物等级提升
const BYTE LEVELUP_USERCMD_PARA  = 10;
  struct stLevelUpUserCmd : public stMagicUserCmd{
    stLevelUpUserCmd()
    {
      byParam = LEVELUP_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时编号 */
  };

//PK模式切换
enum {
  PKMODE_NORMAL,//和平模式
  PKMODE_ENTIRE,//全体模式
  PKMODE_TEAM,//组队模式
  PKMODE_TONG,//帮会模式
  PKMODE_SEPT,//家族模式
  //  PKMODE_SCHOOL,//师门模式
  PKMODE_COUNTRY,//国家模式
  //  PKMODE_CHALLENGE,//挑战模式
  PKMODE_GOODNESS,//善恶模式
  PKMODE_ALLY,//国家联盟
  PKMODE_MAX,//最大值
};

const BYTE PKMODE_USERCMD_PARA = 20;
  struct stPKModeUserCmd : public stMagicUserCmd{
    stPKModeUserCmd()
    {
      byParam = PKMODE_USERCMD_PARA;
    }
    BYTE byPKMode;
  };
const BYTE OBJECT_EXP_USERCMD_PARA = 22;
  struct stObjectExpUserCmd : public stMagicUserCmd{
    stObjectExpUserCmd()
    {
      byParam = OBJECT_EXP_USERCMD_PARA;
    }
    DWORD id;  
    DWORD exp;  
  };

enum enmUnStateType{
  UN_STATE_COMBIN,
  UN_STATE_CHANGE_FACE,
  UN_STATE_TEAM_ATTACK_BIRD = USTATE_TEAM_ATTACK_BIRD_FLAG,
  UN_STATE_TEAM_ATTACK_FLOW = USTATE_TEAM_ATTACK_FLOW_CLOUD,
  UN_STATE_TEAM_ATTACK_ONE_DIM = USTATE_TEAM_ATTACK_ONE_DIM,
  UN_STATE_NUM
};

//解除合体状态
const BYTE UNCOMBIN_USERCMD_PARA = 23;
  struct stUnCombinUserCmd : public stMagicUserCmd{
    stUnCombinUserCmd()
    {
      byParam = UNCOMBIN_USERCMD_PARA;
    }
    enum enmUnStateType type;
  };

//燃放焰火
const BYTE FIREWORK_USERCMD_PARA = 24;
struct stFireWorkUserCmd : public stMagicUserCmd{
  stFireWorkUserCmd()
  {
    byParam = FIREWORK_USERCMD_PARA;
  }

  QWORD qwObjectTempID;  //焰火道具ID
  BYTE byType;    //
  DWORD dwUserID;    //焰火燃放者ID
  DWORD dwFireID;    //焰火ID
};

//时间同步消息
const BYTE TIMESYNC_USERCMD_PARA = 25;
struct stTimeSyncUserCmd : public stMagicUserCmd{
  stTimeSyncUserCmd()
  {
    byParam = TIMESYNC_USERCMD_PARA;
  }

  time_t serverTime;  //服务器时间
};

//GM command: Switch character obstacle state
const BYTE SWITCH_CHARACTER_OBSTACLE_USERCMD_PARA      = 26;
struct stSwitchCharacterObstacleUserCmd : public stMagicUserCmd{
       stSwitchCharacterObstacleUserCmd()
       {
               byParam = SWITCH_CHARACTER_OBSTACLE_USERCMD_PARA;
       }

       bool bOn;               //true: Use obstacle
};
/// 攻击返回给其他人
const BYTE RT_OTHER_MAGIC_USERCMD_PARA = 27;
struct stRTOtherMagicUserCmd : public stMagicUserCmd{

  stRTOtherMagicUserCmd()
  {
    byParam = RT_OTHER_MAGIC_USERCMD_PARA;
  }

  BYTE byTarget;        /**< 目标类型：enumMapDataType */
  DWORD dwUserTempID;      /**< 目标临时编号 */
  BYTE bySrc;          /**< 攻击者类型：enumMapDataType */
  DWORD dwSrcTempID;      /**< 攻击者临时编号 */
};

//////////////////////////////////////////////////////////////
/// 魔法指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 复活指令定义开始
//////////////////////////////////////////////////////////////
  struct stReliveUserCmd : public stNullUserCmd{
    stReliveUserCmd()
    {
      byCmd = RELIVE_USERCMD;
    }
  };

/// 主用户死亡指令
const BYTE MAINUSERDEATH_RELIVE_USERCMD_PARA = 1;
  struct stMainUserDeathReliveUserCmd : public stReliveUserCmd{
    stMainUserDeathReliveUserCmd()
    {
      byParam = MAINUSERDEATH_RELIVE_USERCMD_PARA;

      dwUserTempID = 0;
      deathType = 0;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
    DWORD deathType;
  };

/// 主用户复活指令
const BYTE MAINUSERRELIVE_RELIVE_USERCMD_PARA = 2;
  struct stMainUserReliveReliveUserCmd : public stReliveUserCmd{
    stMainUserReliveReliveUserCmd()
    {
      byParam = MAINUSERRELIVE_RELIVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */

    DWORD x,y;          // 坐标
  };

//复活方式
enum
{
  ReliveHome,//回城复活
  ReliveMoney,//金钱复活
  ReliveSkill,//技能复活
  ReliveBattle,	//sky 战场复活
  Relive_1_min,//追捕凶犯1分钟
  Relive_5_min,//追捕凶犯5分钟
  Relive_10_min//追捕凶犯10分钟
};
/// 死亡动画播放完毕
const BYTE OK_RELIVE_USERCMD_PARA = 3;
  struct stOKReliveUserCmd : public stReliveUserCmd{
    stOKReliveUserCmd()
    {
      byParam = OK_RELIVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */
    BYTE  byType;        /**< 复活方式 */
  };
//////////////////////////////////////////////////////////////
/// 复活指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 用户移动指令定义开始
//////////////////////////////////////////////////////////////
  struct stMoveUserCmd : public stNullUserCmd{
    stMoveUserCmd()
    {
      byCmd = MOVE_USERCMD;
    }
  };

/// 移动方向的定义
enum {
  _DIR_UP      = 0,/// 向上
  _DIR_UPRIGHT  = 1,/// 右上
  _DIR_RIGHTUP  = 1,/// 右上
  _DIR_RIGHT    = 2,/// 向右
  _DIR_RIGHTDOWN  = 3,/// 右下
  _DIR_DOWNRIGHT  = 3,/// 右下
  _DIR_DOWN    = 4,/// 向下
  _DIR_DOWNLEFT  = 5,/// 左下
  _DIR_LEFTDOWN  = 5,/// 左下
  _DIR_LEFT    = 6,/// 向左
  _DIR_LEFTUP    = 7,/// 左上
  _DIR_UPLEFT    = 7,/// 左上
  _DIR_WRONG    = 8    /// 错误方向
};
/// 用户移动
const BYTE USERMOVE_MOVE_USERCMD_PARA = 2;
  struct stUserMoveMoveUserCmd : public stMoveUserCmd {
    stUserMoveMoveUserCmd()
    {
      byParam = USERMOVE_MOVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时编号 */

    BYTE byDirect;        /**< 移动方向 */
    BYTE bySpeed;        /**< 移动速度 */
    WORD x;          /**< 目的坐标 */
    WORD y;
  };

/// 网关向主用户发送的瞬移指令
const BYTE USERINSTANTJUMP_MOVE_USERCMD_PARA = 10;
  struct stUserInstantJumpMoveUserCmd : public stMoveUserCmd{
    stUserInstantJumpMoveUserCmd()
    {
      byParam = USERINSTANTJUMP_MOVE_USERCMD_PARA;
    }

    DWORD dwUserTempID;      /**< 用户临时ID */

    DWORD dwNextScreenPosition;  /**< 人所到达的屏位置 */
    WORD wdNextOffsetX;      /**< 人所到达的屏的偏移X */
    WORD wdNextOffsetY;      /**< 人所到达的屏的偏移Y */
  };

/// 用户进入地图指令命令
/// 目前只应用于进出总坛
const BYTE USERGOTOMAP_MOVE_USERCMD_PARA = 12;
struct stUserGotoMapMoveUserCmd : public stMoveUserCmd
{
  stUserGotoMapMoveUserCmd()
  {
    byParam = USERGOTOMAP_MOVE_USERCMD_PARA;
  }
  WORD IsBackToCity;
  DWORD dwMapType;
  char mapName[MAX_NAMESIZE];
};

/// Npc移动指令
const BYTE NPCMOVE_MOVE_USERCMD_PARA = 20;
  struct stNpcMoveMoveUserCmd : public stMoveUserCmd{
    stNpcMoveMoveUserCmd()
    {
      byParam = NPCMOVE_MOVE_USERCMD_PARA;
    }

    DWORD dwNpcTempID;      /**< Npc临时编号 */

    BYTE byDirect;        /**< 移动方向 */
    BYTE bySpeed;        /**< 移动的速度 */
    WORD x;          /**< 目的坐标 */
    WORD y;
  };

/// 请求获取大陆列表
const BYTE REQUESTLANDMASS_MOVE_USERCMD_PARA = 30;
  struct stRequestLandMassMoveUserCmd : public stMoveUserCmd{
    stRequestLandMassMoveUserCmd()
    {
      byParam = REQUESTLANDMASS_MOVE_USERCMD_PARA;
    }
  };

struct t_LandMass {
  BYTE groupName[MAX_NAMESIZE];   /**< 大陆名称 */
  BYTE countryName[MAX_NAMESIZE]; /**< 国家名称 */
  BYTE cityName[MAX_NAMESIZE];    /**< 城市名称 */
  WORD wdOnlineUser;          /**< 大陆在线人数 */
  BYTE byAvailable;           /**< 大陆是否可用 */
  DWORD price;        // 跳转费用
};

/// 服务器返回大陆列表
const BYTE RESPONSELANDMASS_MOVE_USERCMD_PARA = 31;
  struct stResponseLandMassMoveUserCmd : public stMoveUserCmd{
    stResponseLandMassMoveUserCmd()
    {
      byParam = RESPONSELANDMASS_MOVE_USERCMD_PARA;
    }

    int size;
    //列表
  };

/// 跳转大陆
const BYTE LANDMASSJUMP_MOVE_USERCMD_PARA = 32;
  struct stLandMassJumpMoveUserCmd : public stMoveUserCmd{
    stLandMassJumpMoveUserCmd()
    {
      byParam = LANDMASSJUMP_MOVE_USERCMD_PARA;
    }
  };

/// 坐下起来指令，至于是坐下还是起来跟当前状态有关
const BYTE SITDOWN_MOVE_USERCMD_PARA = 33;
  struct stSitDownMoveUserCmd : public stMoveUserCmd{
    stSitDownMoveUserCmd()
    {
      byParam = SITDOWN_MOVE_USERCMD_PARA;
    }
  };
//////////////////////////////////////////////////////////////
/// 用户移动指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 选择指令定义开始
//////////////////////////////////////////////////////////////
struct stSelectUserCmd : public stNullUserCmd
{
  stSelectUserCmd()
  {
    byCmd = SELECT_USERCMD;
  }
};

/**
 * \brief 角色状态标志位
 *
 */
#define CHARBASE_OK			1	///已经登陆过游戏
#define CHARBASE_FORBID		2	///角色被封
#define CHARBASE_VIP		4	///收费用户(充过值)
#define CHARBASE_EXP125		8	///1.25倍经验状态
#define CHARBASE_EXP150		16	///1.50倍经验状态
#define CHARBASE_EXP175		32	///1.75倍经验状态
#define CHARBASE_DITAO		64	///地之套装效果
#define CHARBASE_TIANTAO	128	///天之套装效果
#define CHARBASE_SHENTAO	256	///神之套装效果
/// 最大角色信息个数
const WORD MAX_CHARINFO = 2;
/// 角色信息
struct SelectUserInfo
{
  DWORD id;            /// 角色编号
  char  name[MAX_NAMESIZE+1];    /// 角色名称
  WORD	JobType;			//[shx Add 职业]
  WORD type;            /// 角色类型
  WORD level;            /// 角色等级
  DWORD mapid;          /// 角色所在地图编号
  char  mapName[MAX_NAMESIZE+1];  /// 角色所在地图名称
  WORD country;          ///  国家ID
  WORD face;
  WORD hair;             /// [shx Add] 发型
  char OldMap[MAX_PATH];	///sky 移动到该地图前的地图位置
  char  countryName[MAX_NAMESIZE+1];  /// 国家名称
  DWORD bitmask;          /// 角色掩码
};

const BYTE USERINFO_SELECT_USERCMD_PARA = 1;
struct stUserInfoUserCmd : public stSelectUserCmd
{
  stUserInfoUserCmd()
  {
    byParam = USERINFO_SELECT_USERCMD_PARA;
    bzero(charInfo,sizeof(charInfo));
    size = 0;
  }
  SelectUserInfo charInfo[MAX_CHARINFO];
  WORD size;
  BYTE data[0];
};

// 判断头象的性别
inline bool IsMaleFace(int face)
{
  return (face & 0x1) == 1;
}

inline bool IsFemaleFace(int face)
{
  return !IsMaleFace(face);
}

inline int getCharTypeByFace(int face)
{
  if (IsMaleFace(face)) return PROFESSION_1;
  return PROFESSION_2;
}

/// 请求创建用户档案
const BYTE CREATE_SELECT_USERCMD_PARA = 2;
struct stCreateSelectUserCmd : public stSelectUserCmd
{
  stCreateSelectUserCmd()
  {
    byParam = CREATE_SELECT_USERCMD_PARA;
  }

  char strUserName[MAX_NAMESIZE];  /**< 用户名字  */
  WORD	JobType;			//[shx Add 职业]
  WORD  Face;               //[shx Add 头像]
  WORD charType;
  BYTE byHairType;      /**< 头发类型 */
  DWORD byRGB;        /**< 颜色RGB */
  WORD country;        /**< 国家ID */
  WORD five;          /**< 五行主属性 */
};

/// 请求登陆
const BYTE LOGIN_SELECT_USERCMD_PARA = 3;
struct stLoginSelectUserCmd : public stSelectUserCmd
{
  stLoginSelectUserCmd()
  {
    byParam = LOGIN_SELECT_USERCMD_PARA;
  }

  DWORD charNo;
  char jpegPassport[7];        /**< 图形验证码 */
};

/// 请求删除帐号
const BYTE DELETE_SELECT_USERCMD_PARA = 4;
struct stDeleteSelectUserCmd : public stSelectUserCmd
{
  stDeleteSelectUserCmd()
  {
    byParam = DELETE_SELECT_USERCMD_PARA;
    bzero(numPassword,sizeof(numPassword));
  }

  DWORD  charNo;
  char  numPassword[MAX_NUMPASSWORD];
};

/// 请求检查角色名
const BYTE CHECKNAME_SELECT_USERCMD_PARA = 5;
struct stCheckNameSelectUserCmd : public stSelectUserCmd
{
  stCheckNameSelectUserCmd()
  {
    byParam = CHECKNAME_SELECT_USERCMD_PARA;
    name[0] = 0;
    err_code = 0;
  }

  char name[MAX_NAMESIZE];  /**< 用户名字  */
  BYTE err_code; //返回时的信息 0 没有错误 1 名字重复 2 名字包含不合法的内容
};

/// 返回删除角色失败
const BYTE RETURN_DELETE_SELECT_USERCMD_PARA = 6;
struct stReturnDeleteSelectUserCmd : public stSelectUserCmd
{
  stReturnDeleteSelectUserCmd()
  {
    byParam = RETURN_DELETE_SELECT_USERCMD_PARA;
  }

  char name[MAX_NAMESIZE];  /**< 角色名字  */
  BYTE err_code; //返回时的信息 1: 您是帮主，请解散帮会后再删除角色
                 //             2: 您是师尊，请解散师门后再删除角色
                 //             3: 您是族长，请解散家族后再删除角色
           //             4: 操作异常，请重试
};

/// 请求国家列表
const BYTE REQUEST_COUNTRY_SELECT_USERCMD_PARA = 7;
struct stRequestSelectUserCmd : public stSelectUserCmd
{
  stRequestSelectUserCmd()
  {
    byParam = REQUEST_COUNTRY_SELECT_USERCMD_PARA;
  }

};
/// 请求删除帐号时数字密码错误
const BYTE DELETE_ERROR_SELECT_USERCMD_PARA = 8;
struct stDeleteErrorSelectUserCmd : public stSelectUserCmd
{
  stDeleteErrorSelectUserCmd()
  {
    byParam = DELETE_ERROR_SELECT_USERCMD_PARA;
  }

};
//////////////////////////////////////////////////////////////
// 选择指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 用户属性指令定义开始
//////////////////////////////////////////////////////////////

  struct stPropertyUserCmd : public stNullUserCmd{
    stPropertyUserCmd()
    {
      byCmd = PROPERTY_USERCMD;
    }
  };

/// 定义装备格子类型
enum {
  EQUIPCELLTYPE_NONE=0,/// 不能装备
  EQUIPCELLTYPE_HELM=1,/// 头盔
  EQUIPCELLTYPE_BODY=2,/// 服装
  EQUIPCELLTYPE_HANDR=3,/// 右手
  EQUIPCELLTYPE_HANDL=4,/// 左手
  EQUIPCELLTYPE_NECKLACE=5,/// 项链
  EQUIPCELLTYPE_GLOVES=6,/// 手套,手镯
  EQUIPCELLTYPE_RING=7,/// 戒指
  EQUIPCELLTYPE_BELT=8,/// 腰带
  EQUIPCELLTYPE_SHOES=9,/// 鞋子
  EQUIPCELLTYPE_OTHER=10,/// 特殊物品,比如马牌
  EQUIPCELLTYPE_PACKAGE=11,/// 装备的包裹
  EQUIPCELLTYPE_MAKE=12,/// 合成、升级，镶嵌的包裹
  EQUIPCELLTYPE_ADORN=13,/// 装饰品
  //[xq]加几个类型
  EQUIPCELLTYPE_TROUSERS=14,				//裤子
  EQUIPCELLTYPE_GLOVE=15,				//手套
  EQUIPCELLTYPE_CUFF=16,				//护腕
  EQUIPCELLTYPE_MANTEAU=17,					//披风
  EQUIPCELLTYPE_SHOULDER=18,				//肩膀
  EQUIPCELLTYPE_BOWLDER=19,			//玉佩
  EQUIPCELLTYPE_FASHION=20,				//时装
  EQUIPCELLTYPE_AUTOADDBLOOD=21				//自动加血
};

enum{
  EQUIPCELLTYPE_LEFT,///左边
  EQUIPCELLTYPE_RIGHT,///右边
};

/// 定义装备动作类型
enum{
  EQUIPACTION_INIT,/// 初始装备
  EQUIPACTION_MOVE,/// 移动装备
  EQUIPACTION_SHATTER,/// 装备损坏
  EQUIPACTION_OBTAIN,/// 装备获得
  EQUIPACTION_DROP,/// 装备丢弃
  EQUIPACTION_REFRESH,/// 刷新装备
};

/// 定义物品格子类型
enum{
  OBJECTCELLTYPE_NONE,/// 不是格子，用于丢弃或捡到物品
  OBJECTCELLTYPE_COMMON,/// 普通物品格子
  OBJECTCELLTYPE_EQUIP,/// 装备
  OBJECTCELLTYPE_MOUSE,/// 鼠标
  OBJECTCELLTYPE_TRADE,/// 自己的交易格子
  OBJECTCELLTYPE_OTHERTRADE,/// 对方的交易格子
  OBJECTCELLTYPE_BANK,/// 银行
  OBJECTCELLTYPE_SELL,/// 卖
  OBJECTCELLTYPE_STORE,/// 仓库
  OBJECTCELLTYPE_EQUIPSHOW,/// 非自己穿着的装备
  OBJECTCELLTYPE_PACKAGE,/// 包裹的格子
  OBJECTCELLTYPE_MAKE,/// 合成、升级，镶嵌的格子
  OBJECTCELLTYPE_MYSHOP,/// 自己摊位的格子
  OBJECTCELLTYPE_OTHERSSHOP,/// 别的玩家摊位的格子
  OBJECTCELLTYPE_MAIL,/// 邮件系统的格子
  OBJECTCELLTYPE_COUNTRY_SAVEBOX,/// 国家倉库
  OBJECTCELLTYPE_PET,/// 宠物包裹
};

/// 定义升级格子类型
enum {
  MAKECELLTYPE_EQUIP=0, /// 被合成、升级，镶嵌的物品
  MAKECELLTYPE_MATERIAL1=1,/// 材料1
  MAKECELLTYPE_MATERIAL2=2,/// 材料2
  MAKECELLTYPE_MATERIAL3=3,/// 材料3
  MAKECELLTYPE_MATERIAL4=4,/// 材料4
};

/// 定义升级格子类型
enum {
  UPGRADECELLTYPE_UPER=0,/// 被升级的物品
  UPGRADECELLTYPE_JEWEL1=1,/// 升级宝石格子1
  UPGRADECELLTYPE_JEWEL2=2,/// 升级宝石格子2
};

/// 用户道具数据
#define ADDUSEROBJECT_PROPERTY_USERCMD_PARAMETER 1
  struct stAddObjectPropertyUserCmd : public stPropertyUserCmd{
    stAddObjectPropertyUserCmd()
    {
      byParam = ADDUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    BYTE byActionType;      /**< 物品动作类型 */
    t_Object object;      /**< 物品数据 */
  };

/// 删除道具数据
#define REMOVEUSEROBJECT_PROPERTY_USERCMD_PARAMETER 2
  struct stRemoveObjectPropertyUserCmd : public stPropertyUserCmd {
    stRemoveObjectPropertyUserCmd()
    {
      byParam = REMOVEUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
  };

/// 交换（移动）用户物品
#define SWAPUSEROBJECT_PROPERTY_USERCMD_PARAMETER 3
  struct stSwapObjectPropertyUserCmd : public stPropertyUserCmd{
    stSwapObjectPropertyUserCmd()
    {
      byParam = SWAPUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    stObjectLocation  dst;  /**< 物品目的位置 如果目的位置上有物品，则交换*/
  };

/// 分裂物品指令（客户端自动减少源物品的数量）
#define SPLITUSEROBJECT_PROPERTY_USERCMD_PARAMETER 4
  struct stSplitObjectPropertyUserCmd : public stPropertyUserCmd{
    stSplitObjectPropertyUserCmd()
    {
      byParam = SPLITUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD qwNewThisID;      /**< 新物品的唯一ID */
    DWORD dwNum;        /**< 分裂的数量 */
    stObjectLocation  dst;  /**< 物品目的位置*/
  };

/// 合并物品
#define UNIONUSEROBJECT_PROPERTY_USERCMD_PARAMETER 5
  struct stUnionObjectPropertyUserCmd : public stPropertyUserCmd{
    stUnionObjectPropertyUserCmd()
    {
      byParam = UNIONUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwSrcThisID;      /**< 源物品唯一ID */
    DWORD qwDstThisID;      /**< 目标物品唯一ID */
  };

/// 设置格子中的物品数量（用于合并物品）
#define REFCOUNTOBJECT_PROPERTY_USERCMD_PARAMETER 6
  struct stRefCountObjectPropertyUserCmd : public stPropertyUserCmd{
    stRefCountObjectPropertyUserCmd()
    {
      byParam = REFCOUNTOBJECT_PROPERTY_USERCMD_PARAMETER;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD dwNum;        /**< 数量 */
  };

/// 用户使用物品
#define USEUSEROBJECT_PROPERTY_USERCMD_PARAMETER 7
  struct stUseObjectPropertyUserCmd : public  stPropertyUserCmd{
    stUseObjectPropertyUserCmd()
    {
      byParam = USEUSEROBJECT_PROPERTY_USERCMD_PARAMETER;
	  preUseUserID = 0;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD dwNumber;        /**< 使用的数量 */
	DWORD preUseUserID;	   /**< sky 被使用物品方 */
  };

/// 用户捡地图上的物品
#define PICKUPITEM_PROPERTY_USERCMD_PARA 8
  struct stPickUpItemPropertyUserCmd : public stPropertyUserCmd {
    stPickUpItemPropertyUserCmd()
    {
      byParam = PICKUPITEM_PROPERTY_USERCMD_PARA;
    }

    DWORD x;
    DWORD y;
  };

#define FOUNDITEM_PROPERTY_USERCMD_PARA  9
  struct stFoundItemPropertyUserCmd : public stPropertyUserCmd {
    stFoundItemPropertyUserCmd()
    {
      byParam = FOUNDITEM_PROPERTY_USERCMD_PARA;
    }

    DWORD up_id;  //待打造物品ID,物品唯一id
    DWORD count; //材料个数
    struct material{
      DWORD gem_id; //材料id,类别id
      BYTE gem_level; //材料等级
      BYTE gem_num; //材料数量
    } list[0];
  };

#define UPGRADEITEM_PROPERTY_USERCMD_PARA 10
  struct stUpgradeItemPropertyUserCmd : public stPropertyUserCmd {
    stUpgradeItemPropertyUserCmd() 
    {
      byParam = UPGRADEITEM_PROPERTY_USERCMD_PARA;
    }
    BYTE location; //位置，0 左手 1 右手
  };

#define COMPOSEITEM_PROPERTY_USERCMD_PARA 11
  struct stComposeItemPropertyUserCmd : public stPropertyUserCmd {
    stComposeItemPropertyUserCmd()
    {
      byParam = COMPOSEITEM_PROPERTY_USERCMD_PARA;
    }
    BYTE per_num; //单次合成数量
    BYTE location; //位置，0 左手 1 右手
  };

enum enumGameAccelKeyType{
  GameAccelKeyType_None = 0,
  GameAccelKeyType_Item,// 使用物品
  GameAccelKeyType_Skill,// 技能
  GameAccelKeyType_Face,// 表情
  GameAccelKeyType_Num,
};

#define MAIN_ACCESS_KEY_NUM    12
#define MAIN_ACCESS_KEY_GROUP  4
struct stGameAccelKey {
  BYTE szAccelKey[4];
  enumGameAccelKeyType type;
  DWORD dwID;
  BYTE mGroup;
  stGameAccelKey()
  {
    mGroup = MAIN_ACCESS_KEY_GROUP;
  }
};
// 更新用户快捷键
const BYTE ACCELKEY_PROPERTY_USERCMD_PARA = 12;
  struct stAccekKeyPropertyUserCmd : public stPropertyUserCmd{
    stAccekKeyPropertyUserCmd()
    {
      byParam = ACCELKEY_PROPERTY_USERCMD_PARA;
    }
    WORD  accelNum;
    BYTE  activeGroup;
    stGameAccelKey accelKeys[0];
  };
/// 添加用户技能数据
#define ADDUSERSKILL_PROPERTY_USERCMD_PARA 13
struct stAddUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stAddUserSkillPropertyUserCmd()
  {
    byParam = ADDUSERSKILL_PROPERTY_USERCMD_PARA;
  }

  DWORD dwSkillID;      /**< 技能ID */
  WORD wdLevel;        /**< 技能等级 */
  WORD wdUpNum;        /**< 技能等级提升点数 */
  DWORD dwExperience;      /**< 当前经验 */
  DWORD dwMaxExperience;    /**< 升级经验 */
};

/// 技能升级指令
#define UPGRADEUSERSKILL_PROPERTY_USERCMD_PARA 14
struct stUpgradeUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stUpgradeUserSkillPropertyUserCmd()
  {
    byParam = UPGRADEUSERSKILL_PROPERTY_USERCMD_PARA;
  }

  DWORD dwSkillID;      /**< 技能ID */
  WORD wdLevel;        /**< 技能等级 */
};

/// 删除用户技能
#define REMOVEUSERSKILL_PROPERTY_USERCMD_PARAMETER 15
struct stRemoveUserSkillPropertyUserCmd : public stPropertyUserCmd
{
  stRemoveUserSkillPropertyUserCmd()
  {
    byParam = REMOVEUSERSKILL_PROPERTY_USERCMD_PARAMETER;
  }

  DWORD dwSkillID;        /**< 用户技能编号 */
};

/// 系统设置指令 
enum  enumUserSetting          
{       
  USER_SETTING_TEAM = 8,  // 允许组队标志
  USER_SETTING_TRADE,     // 允许交易标志
  USER_SETTING_AUTOFINDPATH,// 自动寻路
  USER_SETTING_FAMILY,    // 允许加入家族标志
  USER_SETTING_UNION,     // 允许加入帮会标志

  USER_SETTING_SHOW_HEADPORTRAIT,//显示小头像
  USER_SETTING_SHOW_MIMIMAP,//显示小地图
  USER_SETTING_AUTO_KILL_SUMMON,//自动打怪
  USER_SETTING_SHOW_PLAYERNAME,//显示玩家名字
  USER_SETTING_SHOW_HELPTIP,//显示帮助教程
  USER_SETTING_SHOW_ALLMINIMAP,//小地图全显示
  USER_SETTING_SHOW_ITEM,//地面显示物品

  USER_SETTING_SHOW_COUNTRYNAME,//显示国家名称
  USER_SETTING_SHOW_UNIONNAME,//显示帮会名称
  USER_SETTING_SHOW_SEPTNAME,//显示家族名称
  USER_SETTING_SHOW_OFFICENAME,//显示官职
  USER_SETTING_SHOW_GRACENAME,//显示文采

  USER_SETTING_CHAT_NINE,//公聊
  USER_SETTING_CHAT_COUNTRY,//国家
  USER_SETTING_CHAT_AREA,//区域
  USER_SETTING_CHAT_WHISPER,//密聊
  USER_SETTING_CHAT_UNION,//帮会
  USER_SETTING_CHAT_TEAM,//组队
  USER_SETTING_CHAT_FAMILY,//家族
  USER_SETTING_CHAT_PRIVATE,//私聊
  USER_SETTING_CHAT_FRIEND,//好友
  USER_SETTING_CHAT_SCHOOL,//师门
  USER_SETTING_CHAT_WORLD,//世界
  //USER_SETTING_CHAT_ALL,//全部

  USER_SETTING_HELP_MOVE,             //移动
  USER_SETTING_HELP_NPC,              //NPC
  USER_SETTING_HELP_NPCDIALOG,        //NPC对话
  USER_SETTING_HELP_ATTACK,           //攻击
  USER_SETTING_HELP_PK,               //PK
  USER_SETTING_HELP_CLEARREDNAME,     //消除红名
  USER_SETTING_HELP_TASK,             //任务
  USER_SETTING_HELP_RIGHTBTN,         //右键选项
  USER_SETTING_HELP_TRADE,            //交易
  USER_SETTING_HELP_TEAM,             //组队
  USER_SETTING_HELP_MEMBERHEAD,       //队员头像
  USER_SETTING_HELP_ACCELKEY,         //快捷使用物品
  USER_SETTING_HELP_PACK,             //包裹
  USER_SETTING_HELP_EQUIP,            //如何装备物品
  USER_SETTING_HELP_EXPACK,           //额外包裹
  USER_SETTING_HELP_SKILL,            //技能
  USER_SETTING_HELP_ADDPROPPOINT,     //加点属性
  USER_SETTING_HELP_STUDY,            //学习
  USER_SETTING_HELP_AUTO_FIND_PATH,//自动寻路
  USER_SETTING_HELP_ITEM_LINK, //物品链接
  USER_SETTING_HELP_PRIVATE_CHAT, //悄悄话
  USER_SETTING_HELP_MATERIAL_COMPOSE,//原料合成
  USER_SETTING_HELP_SOULSTONEL_COMPOSE,//魂魄合成
  USER_SETTING_HELP_SOULSTONE_MAKE,//魂魄镶嵌
  USER_SETTING_HELP_ITEM_UPGRID, //道具升级
  USER_SETTING_HELP_ATTACK_MODE_CHANGE,//攻击模式切换
  USER_SETTING_HELP_CHAT,     //聊天
  USER_SETTING_HELP_SELECT,   //选择目标
  USER_SETTING_HELP_ALT_SELECT_NPC,//alt选中npc

  USER_SETTING_FRIEND,     // 允许加为好友
  USER_SETTING_SCHOOL,     // 允许加入师门标志

  USER_SETTING_MINIGAME,// 允许小游戏
  USER_SETTING_EFFECT      // 开关特效
};

struct stSystemSettings
{
  BYTE bySettings[20];  // 使用 set_state 设置标志
  DWORD dwChatColor[8];  //颜色设置
};

#define SYSTEMSETTINGS_PROPERTY_USERCMD_PARA 16
struct stSystemSettingsUserCmd : public stPropertyUserCmd
{
  stSystemSettingsUserCmd()
  {
    byParam = SYSTEMSETTINGS_PROPERTY_USERCMD_PARA;
  }
  stSystemSettings data;
};

enum{
  PROPERTY_CON = 0,//体质
  PROPERTY_STR = 1,//力量
  PROPERTY_DEX = 2,//敏捷
  PROPERTY_INT = 3,//智力
  PROPERTY_MEN = 4  //精神
};

/// 分配用户属性点数
#define DISTRIBUTEUPOINT_PROPERTY_USERCMD_PARA 17
struct stDistributePointPropertyUserCmd : public stPropertyUserCmd
{
  stDistributePointPropertyUserCmd()
  {
    byParam = DISTRIBUTEUPOINT_PROPERTY_USERCMD_PARA;
  }
  WORD type;

};

// 增加技能点数
#define ADDSKILLPOINT_PROPERTY_USERCMD 18
struct stAddSkillPointPropertyUserCmd : public stPropertyUserCmd
{
  stAddSkillPointPropertyUserCmd()
  {
    byParam = ADDSKILLPOINT_PROPERTY_USERCMD;
  }
  DWORD dwSkillID;
};

/// 清除用户属性点数
#define CLEARPOINT_PROPERTY_USERCMD_PARA 19
struct stClearPointPropertyUserCmd : public stPropertyUserCmd
{
  stClearPointPropertyUserCmd()
  {
    byParam = CLEARPOINT_PROPERTY_USERCMD_PARA;
  }
  DWORD dwItemID;
};

/// 清除用户技能点数
#define CLEARUSERSKILLPOINT_PROPERTY_USERCMD_PARAMETER 20
struct stClearUserSkillPointPropertyUserCmd : public stPropertyUserCmd
{
  stClearUserSkillPointPropertyUserCmd()
  {
    byParam = CLEARUSERSKILLPOINT_PROPERTY_USERCMD_PARAMETER;
  }
  DWORD dwItemID;
};

/*
#define MAKE_ODDS_PROPERTY_USERCMD_PARA 19
struct stMakeOddsPropertyUserCmd : public stPropertyUserCmd
{
  stMakeOddsPropertyUserCmd()
  {
    byParam = MAKE_ODDS_PROPERTY_USERCMD_PARA;
  }
  
  DWORD odds;
};

#define MAKE_SELECT_PROPERTY_USERCMD_PARA 20
struct stMakeSelectPropertyUserCmd : public stPropertyUserCmd
{
  stMakeSelectPropertyUserCmd()
  {
    byParam = MAKE_SELECT_PROPERTY_USERCMD_PARA;
  }
  
  DWORD id; //物品id
};
*/
#define COMPOSE_SOUL_STONE_PROPERTY_USERCMD_PARA 21
struct stComposeSoulStonePropertyUserCmd : public stPropertyUserCmd {
  stComposeSoulStonePropertyUserCmd()
  {
    byParam = COMPOSE_SOUL_STONE_PROPERTY_USERCMD_PARA;
  }
  BYTE location; //位置，0 左手 1 右手

};

#define ENCHASEL_PROPERTY_USERCMD_PARA 22
struct stEnchasePropertyUserCmd : public stPropertyUserCmd {
  stEnchasePropertyUserCmd()
  {
    byParam = ENCHASEL_PROPERTY_USERCMD_PARA;
  }
  BYTE location; //位置，0 左手 1 右手
};

#define HOLE_PROPERTY_USERCMD_PARA 23
struct stHolePropertyUserCmd : public stPropertyUserCmd {
  stHolePropertyUserCmd()
  {
    byParam = HOLE_PROPERTY_USERCMD_PARA;
  }
  DWORD up_id; //待打孔装备id,物品唯一id
  DWORD gem_id; //天魔石id，物品类别id
  BYTE gem_level; //天魔石等级
  BYTE gem_num; //天魔石数量
};

enum enumHairStyle
{
  HairStype_1,//粗旷型
  HairStype_2,//潇洒型
  HairStype_3,//豪放型
  HairStype_4,//靓丽型
  HairStype_5,//清秀型
  HairStype_6//高贵型
};
enum enumHairColor
{
  HairColor_black = 0x00001900,//黑色
  HairColor_drink = 0x00C9004C,//酒红
  HairColor_purple = 0x009300DD//酱紫
};

#define DECOMPOSE_PROPERTY_USERCMD_PARA 24
struct stDecomposePropertyUserCmd : public stPropertyUserCmd {
  stDecomposePropertyUserCmd()
  {
    byParam = DECOMPOSE_PROPERTY_USERCMD_PARA;
  }
  DWORD up_id; //待分解装备id,物品唯一id
};

#define BODYCOLOR_PROPERTY_USERCMD_PARA 25//衣服换色
struct stBodyColorPropertyUserCmd : public stPropertyUserCmd
{
  stBodyColorPropertyUserCmd()
  {
    byParam = BODYCOLOR_PROPERTY_USERCMD_PARA;
  }
  DWORD dwBodyColorCustom;//换色的颜色
};

#define HAIR_PROPERTY_USERCMD_PARA 26//换发型
struct stHairPropertyUserCmd : public stPropertyUserCmd
{
  stHairPropertyUserCmd()
  {
    byParam = HAIR_PROPERTY_USERCMD_PARA;
  }
  BYTE byHairType;//头发发型
  DWORD dwHairColor;//头发颜色值
};

#define SELECT_PROPERTY_USERCMD_PARA 27//选中某个对象
struct stSelectPropertyUserCmd : public stPropertyUserCmd
{
  stSelectPropertyUserCmd()
  {
    byParam = SELECT_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
  BYTE byOldType;//enumMapDataType
  DWORD dwOldTempID;//临时编号
};

#define SELECT_MAINUSER_PROPERTY_USERCMD_PARA 29//请求观察选中人的属性
struct stSelectMainUserPropertyUserCmd : public stPropertyUserCmd
{
  stSelectMainUserPropertyUserCmd()
  {
    byParam = SELECT_MAINUSER_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
};

enum enumEquipType{
  Equip_head,
  Equip_necklace,
  Equip_body,
  Equip_handL,
  Equip_handR,
  Equip_belt,
  Equip_ringL,
  Equip_ringR,
  Equip_bangleL,
  Equip_bangleR,
  Equip_boots,
  Equip_others1,
  Equip_others2,
  Equip_others3,
  Equip_others4,
  Equip_others5
};
struct EquipedObject
{
  BYTE byWhere;//位置enumEquipType
  t_Object object;//物品

};
#define SELECT_RETURN_MAINUSER_PROPERTY_USERCMD_PARA 30//回答观察选中人的属性
struct stSelectReturnMainUserPropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnMainUserPropertyUserCmd()
  {
    byParam = SELECT_RETURN_MAINUSER_PROPERTY_USERCMD_PARA;
  }
  DWORD dwTempID;//临时编号
  t_MainUserData mainuser_data;
  t_MapUserData mapuser_data;
  DWORD dwSize; //已装备物品个数
  EquipedObject object_data[0];
};

//耐久度变化
const BYTE DURABIILTY_USERCMD_PARA = 31;
  struct stDurabilityUserCmd : public stPropertyUserCmd{
    stDurabilityUserCmd()
    {
      byParam = DURABIILTY_USERCMD_PARA;
    }
    DWORD dwThisID;  /*装备ID */
    DWORD dwDur;  /*当前耐久度*/
    DWORD dwMaxDur;  /*最大耐久度*/
  };

#define SELECT_RETURN_STATES_PROPERTY_USERCMD_PARA 32//被选中人的状态
struct stSelectReturnStatesPropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnStatesPropertyUserCmd()
  {
    byParam = SELECT_RETURN_STATES_PROPERTY_USERCMD_PARA;
  }
  BYTE byType;//enumMapDataType
  DWORD dwTempID;//临时编号
  DWORD size;//状态个数
  struct
  {
    DWORD state;
    union{
      struct{
        WORD result;//数值
        WORD time;//时间
      };
      DWORD value;
    };
  }states[0];
};

//清除技能
const BYTE CLEARSKILL_USERCMD_PARA = 33;
  struct stClearSkillUserCmd : public stPropertyUserCmd{
    stClearSkillUserCmd()
    {
      byParam = CLEARSKILL_USERCMD_PARA;
    }
  };

#define FACE_PROPERTY_USERCMD_PARA 34//更换头像
struct stFacePropertyUserCmd : public stPropertyUserCmd
{
  stFacePropertyUserCmd()
  {
    byParam = FACE_PROPERTY_USERCMD_PARA;
  }
  DWORD dwFace;//目标头像类型
};
#define HONOR_TO_PKVALUE_PROPERTY_USERCMD_PARA 35//荣誉点洗pk值
struct stHonorToPkValuePropertyUserCmd : public stPropertyUserCmd
{
  stHonorToPkValuePropertyUserCmd()
  {
    byParam = HONOR_TO_PKVALUE_PROPERTY_USERCMD_PARA;
  }
};
// 使用血如意和玉如意时需要发送地图信息下去
const BYTE SCROLL_MAP_PROPERTY_USERCMD_PARA = 36;
  struct stScrollMapPropertyUserCmd : public stPropertyUserCmd{
    stScrollMapPropertyUserCmd()
    {
      byParam = SCROLL_MAP_PROPERTY_USERCMD_PARA;
    }
    DWORD qwThisID;        /**< 物品唯一ID */
    DWORD  size;
    struct
    {
      char strMapName[MAX_NAMESIZE];
    }mapname[0];
    
  };

/// 清除用户属性点数只限5点
#define CLEARPOINT_LIMIT_PROPERTY_USERCMD_PARA 37
struct stClearPointLimitPropertyUserCmd : public stPropertyUserCmd
{
  stClearPointLimitPropertyUserCmd()
  {
    byParam = CLEARPOINT_LIMIT_PROPERTY_USERCMD_PARA;
  }
  QWORD qwThisID;
  BYTE  byProperty;
};

// 请求增值地图列表
const BYTE REQUEST_INC_MAP_PROPERTY_USERCMD_PARA = 38;
  struct stRequestIncMapPropertyUserCmd : public stPropertyUserCmd{
    stRequestIncMapPropertyUserCmd()
    {
      byParam = REQUEST_INC_MAP_PROPERTY_USERCMD_PARA;
    }
  };

enum horseState
{
  HORSE_STATE_PUTUP,//收起
  HORSE_STATE_FOLLOW,//跟随
  HORSE_STATE_RIDE  //骑乘
};

enum horseSkill
{
  HORSE_SKILL_DEF_UP = 1,//提高物防魔防
  HORSE_SKILL_PATK_UP,//提高物攻
  HORSE_SKILL_MATK_UP,//提高魔攻
  HORSE_SKILL_HP_UP,//提高生命上限
  HORSE_SKILL_MP_UP,//提高魔法上限
  HORSE_SKILL_DMG_UP,//附加伤害
  HORSE_SKILL_DMG_DOWN,//减少自身伤害
};

//马的数据
struct t_HorseData
{
  DWORD id;    //npcid
  char name[MAX_NAMESIZE];//名字
  DWORD lv;    //等级
  WORD str;    //力量
  WORD intel;    //智力
  WORD dex;    //敏捷
  WORD men;    //精神
  WORD con;    //体质
  WORD speed;    //速度
  BYTE pdam;    //增加物理攻击力%
  BYTE pdef;    //增加物理防御力%
  BYTE mdam;    //增加魔法攻击力%
  BYTE mdef;    //增加魔法防御力%
  WORD maxhp;    //最大HP
  WORD maxmp;    //最大MP
  DWORD callTime;    //召唤间隔
  horseState state;  //马的状态
  WORD poisonRes;    //抗毒
  WORD lullRes;    //抗麻痹
  WORD faintRes;    //抗晕眩
  WORD chaosRes;    //抗混乱
  WORD freezeRes;    //抗冰冻
  WORD petrifyRes;  //抗石化
  WORD blindRes;    //抗失明
  WORD slowRes;    //抗减速
  DWORD horseid;    //马的id（道具id）

  //[sky 增加马匹训练相关变量]
  WORD horseXLlevel;  //马匹训练等级
  DWORD horseXLtime;  //马匹训练剩余时间
};

#define SELECT_RETURN_HORSE_PROPERTY_USERCMD_PARA 39//回答观察选中人的属性
struct stSelectReturnHorsePropertyUserCmd : public stPropertyUserCmd
{
  stSelectReturnHorsePropertyUserCmd()
  {
    byParam = SELECT_RETURN_HORSE_PROPERTY_USERCMD_PARA;
  }
  t_HorseData data;
};

#define GO_TRAIN_PROPERTY_USERCMD_PARA 40//请求进入练级地图
struct stGoTrainPropertyUserCmd : public stPropertyUserCmd
{
  stGoTrainPropertyUserCmd()
  {
    byParam = GO_TRAIN_PROPERTY_USERCMD_PARA;
  }
  DWORD level;//去第几层
};

//#ifndef _MSC_VER
/// 批量添加用户道具数据
#define ADDUSEROBJECT_LIST_PROPERTY_USERCMD_PARAMETER 41
  struct stAddObjectListPropertyUserCmd : public stPropertyUserCmd{
    stAddObjectListPropertyUserCmd()
    {
      byParam = ADDUSEROBJECT_LIST_PROPERTY_USERCMD_PARAMETER;
      num=0;
	  TabNum = 0;
    }
	BYTE TabNum; //sky 用户可使用的包袱页数
    WORD num;
    struct
    {
      BYTE byActionType;      /**< 物品动作类型 */
      t_Object object;      /**< 物品数据 */
    }list[0];
  };
//#endif //_MSC_VER

/*can not be processed by make cmd */#define RESPONSE_PROPERTY_USERCMD_PARA 0x81
struct stResponsePropertyUserCmd : public stPropertyUserCmd
{
  stResponsePropertyUserCmd()
  {
    byParam = RESPONSE_PROPERTY_USERCMD_PARA;
  }
  
  BYTE kind; //类别，1:合成 2:打造 3:升级
  BYTE status; //结果 0 成功 非0 失败
};

//////////////////////////////////////////////////////////////
// 用户属性指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 用户聊天指令定义开始
//////////////////////////////////////////////////////////////

struct stChatUserCmd : public stNullUserCmd
{
  stChatUserCmd()
  {
    byCmd = CHAT_USERCMD;
  }
};

enum enumChatType{
  CHAT_TYPE_PRIVATE  = 1,/// 私聊频道
  CHAT_TYPE_NINE,/// 轻聊频道
  CHAT_TYPE_TEAM,         /// 队伍频道
  CHAT_TYPE_FRIEND,       /// 好友频道
  CHAT_TYPE_GM,           /// GM聊频道
  CHAT_TYPE_SYSTEM,       /// 系统频道
  CHAT_TYPE_UNION,        /// 帮会频道
  CHAT_TYPE_POP,          /// 弹出式系统提示
  CHAT_TYPE_PERSON,       /// 个人频道
  CHAT_TYPE_WHISPER,      ///悄悄话
  CHAT_TYPE_WHISPERTOME,///悄悄话
  CHAT_TYPE_COUNTRY,      /// 国家频道
  CHAT_TYPE_AREA,///区域频道
  CHAT_TYPE_FAMILY,       /// 家族频道

  CHAT_TYPE_FRIEND_AFFICHE,/// 好友公告
  CHAT_TYPE_UNION_AFFICHE,/// 帮会公告
  CHAT_TYPE_OVERMAN_AFFICHE,/// 师门公告
  CHAT_TYPE_FAMILY_AFFICHE,/// 家族公告

  CHAT_TYPE_FRIEND_PRIVATE,/// 好友私聊
  CHAT_TYPE_UNION_PRIVATE,/// 帮会私聊
  CHAT_TYPE_OVERMAN_PRIVATE,/// 师门私聊
  CHAT_TYPE_FAMILY_PRIVATE,/// 家族私聊

  CHAT_TYPE_NPC,///npc说话

  CHAT_TYPE_EMOTION,///表情
  CHAT_TYPE_SHOPADV,///摆摊广告
  CHAT_TYPE_WORLD,///世界频道
  CHAT_TYPE_OVERMAN,/// 师门频道
  CHAT_TYPE_AUTO,/// 自动回复
  CHAT_TYPE_COUNTRY_PK,/// 外国人入侵PK消息
  CHAT_TYPE_BLESS_MSG,/// 个人祝福消息
  CHAT_TYPE_COUNTRY_MARRY,/// 结婚消息广播
  CHAT_TYPE_ERROR_GM,///发送到GM工具的警告信息
  CHAT_TYPE_MINIGAME  /// 玩小游戏聊天
};


enum enumSysInfoType{
  INFO_TYPE_SYS   =       1,/// 系统信息、GM信息，在聊天窗口
  INFO_TYPE_GAME, /// 游戏信息，屏幕左上
  INFO_TYPE_STATE,        /// 状态转换，屏幕左上
  INFO_TYPE_FAIL,         /// 失败信息，屏幕左上
  INFO_TYPE_EXP,  /// 特殊信息,获得经验、物品，在人物头上
  INFO_TYPE_MSG,  /// 弹出用户确认框的系统消息
  INFO_TYPE_KING, /// 国王发出的聊天消息
  INFO_TYPE_CASTELLAN,/// 城主发出的聊天消息
  INFO_TYPE_EMPEROR,/// 皇帝发出的聊天消息
  INFO_TYPE_SCROLL,/// 屏幕上方滚动的系统信息
  INFO_TYPE_ADDFRIEND,/// 加好友任务显示和动画播放
  INFO_TYPE_BREAKFRIEND,/// 割袍断义任务显示和动画播放
  INFO_TYPE_SKYROCKET1,/// 焰火类型1
  INFO_TYPE_SKYROCKET2,/// 焰火类型2
  INFO_TYPE_ATT_FLAG,/// 旗子被攻击
};

#define ALL_CHAT_USERCMD_PARAMETER 1
struct stTradeObject
{
  DWORD dwObjectID;
  DWORD dwObjectTempID;
  char strName[MAX_NAMESIZE];
  BYTE upgrade;                         // 等级
  BYTE kind;      //物品类型,0普通,1蓝色,2金色,4神圣,8套装
};

///客户端发送到服务器的消息
struct  stChannelChatUserCmd: public stChatUserCmd
{
  DWORD dwType;      /**< 消息类型 */
  DWORD dwSysInfoType;    /**< 系统消息的类型 */ //表情类型
  DWORD dwCharType;    /**< 角色类型 */
  DWORD dwChannelID;
  DWORD dwFromID;      ///发送者的ID,是临时id
  DWORD dwChatTime;      // 谈话时间
  BYTE size;        // 物品数量
  char pstrName[MAX_NAMESIZE];  /**< 名字 */ 
  char pstrChat[MAX_CHATINFO];  /**< 对话 */
  stTradeObject tobject_array[0]; // 交易物品列表
  stChannelChatUserCmd()
  {
    bzero(pstrChat,sizeof(pstrChat));
    bzero(pstrName,sizeof(pstrName));
    byParam = ALL_CHAT_USERCMD_PARAMETER;
    dwChannelID=0;
    dwSysInfoType =1;
    dwCharType = 1;
    size = 0;
  }
};
struct  stServerChannelChatUserCmd: public stChatUserCmd
{
  DWORD dwType;      /**< 消息类型 */
  DWORD dwSysInfoType;    /**< 系统消息的类型 */ //表情类型
  DWORD dwCharType;    /**< 角色类型 */
  DWORD dwChannelID;
  DWORD dwFromID;      ///发送者的ID,是临时id
  DWORD dwChatTime;      // 谈话时间
  BYTE size;        // 物品数量
  char info[0];
  stServerChannelChatUserCmd()
  {
    byParam = ALL_CHAT_USERCMD_PARAMETER;
    dwChannelID=0;
    dwSysInfoType =1;
    dwCharType = 1;
    size = 0;
  }
};

// 解散队伍
#define REMOVE_TEAM_USERCMD_PARA 2
struct stRemoveTeamUserCmd : public stChatUserCmd
{
  stRemoveTeamUserCmd()
  {
    byParam = REMOVE_TEAM_USERCMD_PARA;
  }
};

// 添加队员，刷新队员数据 指令
#define ADD_TEAMMEMBER_USERCMD_PARA 3
struct stTeamMemberData
{
  char pstrName[MAX_NAMESIZE];  // 队员名字
  BYTE byHead;          // 是否是队长
  DWORD dwTempID;          //成员tempid
  DWORD dwMaxHealth;        // HP
  DWORD dwHealth;
  DWORD dwMaxMp;          //MP
  DWORD dwMp;
  WORD wdFace;          //肖像
};
struct stAddTeamMemberUserCmd: public stChatUserCmd
{
  stAddTeamMemberUserCmd()
  {
    byParam = ADD_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTeamID;          // 队伍ID
  DWORD dwHeadID;			//sky 队长ID
  stTeamMemberData data;
};

// 删除队员指令
#define REMOVE_TEAMMEMBER_USERCMD_PARA 4
struct stRemoveTeamMemberUserCmd: public stChatUserCmd
{
  stRemoveTeamMemberUserCmd()
  {
    byParam = REMOVE_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTeamID;          // 队伍ID
  char pstrName[MAX_NAMESIZE];  // 队员名字
  //DWORD dwTempID;          //队员tempid
};

/**
 * 队伍模式
 */
enum
{
  TEAM_NORMAL,//普通模式
  TEAM_HONOR,//荣誉模式
  TEAM_MAX,//无效模式
};
// 请求组队指令,该指令需要发给被请求者
 #define REQUEST_TEAM_USERCMD_PARA 5
 struct stRequestTeamUserCmd: public stChatUserCmd
{
  stRequestTeamUserCmd()
  {
    byParam = REQUEST_TEAM_USERCMD_PARA;
  }
  DWORD dwAnswerUserID;    // 回答者ID,返回给客户端是请求者ID
  DWORD dwTeamMode;      // 队伍模式
};

// 回答组队指令
#define ANSWER_TEAM_USERCMD_PARA 6
struct stAnswerTeamUserCmd: public stChatUserCmd
{
  stAnswerTeamUserCmd()
  {
    byParam = ANSWER_TEAM_USERCMD_PARA;
  }
  DWORD dwRequestUserID;    // 请求者ID
  DWORD dwAnswerUserID;    // 回答者ID
  BYTE  byAgree;        // 是否同意
  DWORD dwTeamMode;      // 队伍模式
};

#define CREATE_CHANNEL_USERCMD_PARAMETER 7
struct  stCreateChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  DWORD dwClientID;
  char name[MAX_NAMESIZE];
  char name2[MAX_NAMESIZE];

  stCreateChannelUserCmd()
  {
    byParam = CREATE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define INVITE_CHANNEL_USERCMD_PARAMETER 8
struct  stInvite_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE];
  DWORD   dwCharType;

  stInvite_ChannelUserCmd()
  {
    byParam = INVITE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define JOIN_CHANNEL_USERCMD_PARAMETER 9
struct  stJoin_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE];

  stJoin_ChannelUserCmd()
  {
    byParam = JOIN_CHANNEL_USERCMD_PARAMETER;
  }
};

#define LEAVE_CHANNEL_USERCMD_PARAMETER 10
struct  stLeave_ChannelUserCmd: public stChatUserCmd
{
  DWORD dwChannelID;
  char name[MAX_NAMESIZE];

  stLeave_ChannelUserCmd()
  {
    byParam = LEAVE_CHANNEL_USERCMD_PARAMETER;
  }
};

#define REQUEST_TEAMMEMBER_POSITION_USERCMD_PARA 11

// 请求队员位置
struct stRequestTeamMemberPosition : public stChatUserCmd
{
  stRequestTeamMemberPosition()
  {
    byParam = REQUEST_TEAMMEMBER_POSITION_USERCMD_PARA;
  }
};
// 服务器返回队员位置
#define RETURN_TEAMMEMBER_POSITION_USERCMD_PARA 11
struct stTeamMemberPosition
{
  char szName[MAX_NAMESIZE];
  char szMapName[MAX_NAMESIZE];
  int x,y;
};
struct stReturnTeamMemberPosition : public stChatUserCmd
{
  stReturnTeamMemberPosition()
  {
    byParam = RETURN_TEAMMEMBER_POSITION_USERCMD_PARA;
  }
  DWORD size;
  stTeamMemberPosition memberPos[0];
};

#define QUESTION_OBJECT_USERCMD_PARA 12
struct stQuestionObject : public stChatUserCmd
{
  stQuestionObject()
  {
    byParam = QUESTION_OBJECT_USERCMD_PARA;
  }
  
  char name[MAX_NAMESIZE];  /**< 物品拥有者的名字 */
  DWORD dwObjectTempID;          /// 物品临时ID
};

#define RETURN_QUESTION_OBJECT_USERCMD_PARA 13
struct stReturnQuestionObject : public stChatUserCmd
{
  stReturnQuestionObject()
  {
    byParam = RETURN_QUESTION_OBJECT_USERCMD_PARA; 
  }
  
  char name[MAX_NAMESIZE];  /**< 物品拥有者的名字 */
  t_Object object;               /// 物品资料
};

// 队员离线消息                
#define TEAMMEMBER_OFFLINE_USERCMD_PARA 14
struct stTeamMemberOfflineUserCmd : public stChatUserCmd
{                                       
        stTeamMemberOfflineUserCmd()
        {               
                byParam = TEAMMEMBER_OFFLINE_USERCMD_PARA; 
        }       
        DWORD dwTempID;                                 //队员tempid
};

// 设置自动消息                
#define AUTO_REPLY_USERCMD_PARA 15
struct stAutoReplyUserCmd : public stChatUserCmd
{                                       
        stAutoReplyUserCmd()
        {               
                byParam = AUTO_REPLY_USERCMD_PARA; 
        }
  char text[MAX_CHATINFO];
};

enum
{
  TEAM_EXP_MODE_NORMAL,//普通分配经验模式
  TEAM_EXP_MODE_SPECIAL,//特殊分配经验模式
};
enum
{
  TEAM_OBJ_MODE_NORMAL,		//普通物品分配模式
  TEAM_OBJ_MODE_SPECIAL,	//轮流物品分配模式
  TEAM_OBJ_MODE_CAPTAIN,	//sky 队长分配模式
};

// 请求(设置)队伍经验分配模式
#define EXPMODE_TEAMMEMBER_USERCMD_PARA 16
struct stExpModeTeamMemberUserCmd: public stChatUserCmd
{
  stExpModeTeamMemberUserCmd()
  {
    byParam = EXPMODE_TEAMMEMBER_USERCMD_PARA;
  }
  BYTE byType;
};
// 请求(设置)队伍物品分配模式
#define OBJMODE_TEAMMEMBER_USERCMD_PARA 17
struct stObjModeTeamMemberUserCmd: public stChatUserCmd
{
  stObjModeTeamMemberUserCmd()
  {
    byParam = OBJMODE_TEAMMEMBER_USERCMD_PARA;
  }
  BYTE byType;
};
// 设置组队模式
#define TEAM_MODE_USERCMD_PARA 18
struct stTeamModeUserCmd: public stChatUserCmd
{
  stTeamModeUserCmd()
  {
    byParam = TEAM_MODE_USERCMD_PARA;
  }
  BYTE byType;
};
// 刷新队员HP,MP 指令
#define FRESH_TEAMMEMBER_USERCMD_PARA 19
struct stFreshTeamMemberUserCmd: public stChatUserCmd
{
  stFreshTeamMemberUserCmd()
  {
    byParam = FRESH_TEAMMEMBER_USERCMD_PARA;
  }
  DWORD dwTempID;          //成员tempid
  DWORD dwMaxHealth;        // HP
  DWORD dwHealth;
  /*
   * 这里为了防止8自己对齐,将DWORD改成WORD,如果不够,可以将数据改成3字节的也可以,不会增加流量
   */
  WORD dwMaxMp;          //MP
  WORD dwMp;
};

// 检测到非法用户
#define DIRTY_USER_USERCMD_PARA 20
enum DIRTYUSER_TYPE{
    DIRTYUSER_DLL_CALL = 1,// 外部DLL调用本进程函数，一般外挂用户
    DIRTYUSER_DEBUGGER = 2,// 启用调试器调试本进程，可能是外挂制作者
};
struct stDirtyUserUserCmd : public stChatUserCmd
{
    stDirtyUserUserCmd()
    {
        byParam = DIRTY_USER_USERCMD_PARA;
    }
    BYTE type;
};
// 回答组队指令
#define ANSWER_NAME_TEAM_USERCMD_PARA 21
struct stAnswerNameTeamUserCmd: public stChatUserCmd
{
  stAnswerNameTeamUserCmd()
  {
    byParam = ANSWER_NAME_TEAM_USERCMD_PARA;
  }
  char byRequestUserName[MAX_NAMESIZE];    // 请求者名字
  char byAnswerUserName[MAX_NAMESIZE];    // 回答者名字
  BYTE  byAgree;        // 是否同意
  DWORD dwTeamMode;      // 队伍模式
};
// 请求组队指令,该指令需要发给被请求者
 #define REQUEST_NAME_TEAM_USERCMD_PARA 22
 struct stRequestNameTeamUserCmd: public stChatUserCmd
{
  stRequestNameTeamUserCmd()
  {
    byParam = REQUEST_NAME_TEAM_USERCMD_PARA;
  }
  char byAnswerUserName[MAX_NAMESIZE];    // 回答者名字,返回给客户端是请求者名字
  DWORD dwTeamMode;      // 队伍模式
};
 #define REQUEST_COUNTRY_HELP_USERCMD_PARA 23
 struct stRequestCountryHelpUserCmd: public stChatUserCmd
{
  stRequestCountryHelpUserCmd()
  {
    byParam = REQUEST_COUNTRY_HELP_USERCMD_PARA;
  }
  char mapName[MAX_NAMESIZE];    //请求支援的地图名称
  WORD x;
  WORD y;
};
 #define KILL_FOREIGNER_USERCMD_PARA 24
 struct stKillForeignerUserCmd: public stChatUserCmd
{
  stKillForeignerUserCmd()
  {
    byParam = KILL_FOREIGNER_USERCMD_PARA;
  }
  char heroName[MAX_NAMESIZE];  //英雄人物
  char mapName[MAX_NAMESIZE];    //立功地图
};

 // BOSS刷新提示消息
#define REFRESH_BOSS_USERCMD_PARA 25
 struct stRefreshBossUserCmd: public stChatUserCmd
{
  stRefreshBossUserCmd()
  {
    byParam = REFRESH_BOSS_USERCMD_PARA;
  }
  DWORD npcid;
  BYTE country; //国家
  char mapName[MAX_NAMESIZE];    //BOSS刷新的地图名称
  BYTE time;     // 剩余的刷新时间，如果为0表示刷出
  //WORD x;
  //WORD y;
};

 // BOSS被杀提示消息
#define KILL_BOSS_USERCMD_PARA 26
 struct stKillBossUserCmd: public stChatUserCmd
{
  stKillBossUserCmd()
  {
    byParam = KILL_BOSS_USERCMD_PARA;
  }
  DWORD npcid;
  char name[MAX_NAMESIZE];    //玩家名称
  char mapName[MAX_NAMESIZE];    //BOSS刷新的地图名称
  WORD x;
  WORD y;
};


// sky新增跟换队长消息
#define REMOVE_TEAM_GHAGELEADER_USERCMD_PARA 27
 struct stRemoveTeamChangeLeaderUserCmd: public stChatUserCmd
 {
	 stRemoveTeamChangeLeaderUserCmd()
	 {
		 byParam = REMOVE_TEAM_GHAGELEADER_USERCMD_PARA;
	 }
	 char LeaderName[MAX_NAMESIZE];			// 新队长ID
 };

//////////////////////////////////////////////////////////////
// 用户聊天指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 交易指令定义开始
//////////////////////////////////////////////////////////////
struct stTradeUserCmd : public stNullUserCmd
{
  stTradeUserCmd()
  {
    byCmd = TRADE_USERCMD;
  }
};

#define REQUEST_TRADE_USERCMD_PARAMETER 0
struct stRequestTradeUserCmd :public stTradeUserCmd
{
  stRequestTradeUserCmd()
  {
    byParam = REQUEST_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 回应交易请求
#define ANSWER_TRADE_USERCMD_PARAMETER 1
struct stAnswerTradeUserCmd:public stTradeUserCmd
{
  stAnswerTradeUserCmd()
  {
    byParam = ANSWER_TRADE_USERCMD_PARAMETER;
  }

  BYTE byAgree;        /**< 是否同意交易 */
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 开始交易
#define BEGIN_TRADE_USERCMD_PARAMETER 2
struct stBeginTradeUserCmd:public stTradeUserCmd
{
  stBeginTradeUserCmd()
  {
    byParam = BEGIN_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwAskerTempID;  /**< 请求者 */
  DWORD dwAnswerTempID;  /**< 回答者 */
};

/// 确定交易
#define COMMIT_TRADE_USERCMD_PARAMETER 5
struct stCommitTradeUserCmd:public stTradeUserCmd
{
  stCommitTradeUserCmd()
  {
    byParam = COMMIT_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwUserTempID;
};

/// 取消交易
#define CANCEL_TRADE_USERCMD_PARAMETER 6
struct stCancelTradeUserCmd:public stTradeUserCmd
{
  stCancelTradeUserCmd()
  {
    byParam = CANCEL_TRADE_USERCMD_PARAMETER;
  }
  DWORD dwUserTempID;
};

/// 交易完成
#define FINISH_TRADE_USERCMD_PARAMETER 7
struct stFinishTradeUserCmd:public stTradeUserCmd
{
  stFinishTradeUserCmd()
  {
    byParam = FINISH_TRADE_USERCMD_PARAMETER;
  }
};

/// 添加交易物品
#define ADD_OBJECT_TRADE_USERCMD_PARAMETER 8
struct stAddObjectTradeUserCmd:public stTradeUserCmd
{
  stAddObjectTradeUserCmd()
  {
    byParam = ADD_OBJECT_TRADE_USERCMD_PARAMETER;
  }
  DWORD user_id; //用户临时id
//  DWORD object_id; //物品唯一id
  t_Object object; //物品数据
  BYTE x;  //物品放置位置x坐标
  BYTE y; //物品放置位置y坐标
};

/// 删除交易物品
#define REMOVE_OBJECT_TRADE_USERCMD_PARAMETER 9
struct stRemoveObjectTradeUserCmd:public stTradeUserCmd
{
  stRemoveObjectTradeUserCmd()
  {
    byParam = REMOVE_OBJECT_TRADE_USERCMD_PARAMETER;
  }
  DWORD user_id; //用户临时id
  DWORD object_id; //物品唯一id
};

/// 访问Npc
#define VISITNPC_TRADE_USERCMD_PARAMETER 10
struct stVisitNpcTradeUserCmd:public stTradeUserCmd
{
  stVisitNpcTradeUserCmd()
  {
    byParam = VISITNPC_TRADE_USERCMD_PARAMETER;
    menuTxt[0] = '\0';
    byReturn = 0;
  }
  DWORD dwNpcTempID;
  BYTE byReturn;
  char menuTxt[1];
};

/// 买物品
#define BUYOBJECT_NPCTRADE_USERCMD_PARAMETER 11
struct stBuyObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stBuyObjectNpcTradeUserCmd()
  {
    byParam = BUYOBJECT_NPCTRADE_USERCMD_PARAMETER;

    dwObjectID = 0;
    dwNum = 1;
    itemLevel = 0;
  }
  DWORD dwObjectID;
  DWORD dwNum;
  BYTE itemLevel;
};

/// 卖物品
#define SELLOBJECT_NPCTRADE_USERCMD_PARAMETER 12
struct stSellObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stSellObjectNpcTradeUserCmd()
  {
    byParam = SELLOBJECT_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD qwThisID;        /**< 物品唯一ID */
};

/// 修理物品
#define REPAIROBJECT_NPCTRADE_USERCMD_PARAMETER 13
struct stRepairObjectNpcTradeUserCmd:public stTradeUserCmd
{
  stRepairObjectNpcTradeUserCmd()
  {
    byParam = REPAIROBJECT_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD id;  //修理物品id，全部修理时为0
  DWORD gem_id;  //修复宝石的唯一id，普通修理填0
};

/// 卖马
#define SELLHORSE_NPCTRADE_USERCMD_PARAMETER 14
struct stSellHorseNpcTradeUserCmd:public stTradeUserCmd
{
  stSellHorseNpcTradeUserCmd()
  {
    byParam = SELLHORSE_NPCTRADE_USERCMD_PARAMETER;
  }

  BYTE action; //action 0:卖,action 1: 放逐
};

/// 仓库信息
#define STORE_INFO_NPCTRADE_USERCMD_PARAMETER 15
struct stStoreInfoNpcTradeUserCmd:public stTradeUserCmd
{
  stStoreInfoNpcTradeUserCmd()
  {
    byParam = STORE_INFO_NPCTRADE_USERCMD_PARAMETER;
  }
  
  BYTE page; //页数
};

/// 开始摆摊
#define START_SELL_USERCMD_PARAMETER 16
struct stSellTradeUserCmd:public stTradeUserCmd
{
  stSellTradeUserCmd()
  {
    byParam = START_SELL_USERCMD_PARAMETER;
  }
};

/// 完成摆摊
#define FINISH_SELL_USERCMD_PARAMETER 17
struct stFinishSellUserCmd:public stTradeUserCmd
{
  stFinishSellUserCmd()
  {
    byParam = FINISH_SELL_USERCMD_PARAMETER;
  }
};

/// 添加物品
#define ADD_OBJECT_SELL_USERCMD_PARAMETER 18
struct stAddObjectSellUserCmd:public stTradeUserCmd
{
  stAddObjectSellUserCmd()
  {
    byParam = ADD_OBJECT_SELL_USERCMD_PARAMETER;
  }
  t_Object object; //物品数据
  DWORD price; //物品价钱
  BYTE x;  //物品放置位置x坐标
  BYTE y; //物品放置位置y坐标
};

/// 删除物品
#define REMOVE_OBJECT_SELL_USERCMD_PARAMETER 19
struct stRemoveObjectSellUserCmd:public stTradeUserCmd
{
  stRemoveObjectSellUserCmd()
  {
    byParam = REMOVE_OBJECT_SELL_USERCMD_PARAMETER;
  }
  DWORD object_id; //物品唯一id
};

/// 请求某人的摆摊信息
#define REQUEST_SELL_INFO_USERCMD_PARAMETER 20
struct stRequestSellInfoUserCmd:public stTradeUserCmd
{
  stRequestSellInfoUserCmd()
  {
    byParam = REQUEST_SELL_INFO_USERCMD_PARAMETER;
  }
  DWORD temp_id; //用户临时ID
};

/// 请求购买物品
#define REQUEST_SELL_BUY_USERCMD_PARAMETER 21
struct stRequestSellBuyUserCmd:public stTradeUserCmd
{
  stRequestSellBuyUserCmd()
  {
    byParam = REQUEST_SELL_BUY_USERCMD_PARAMETER;
  }
  DWORD temp_id; //用户临时ID
  DWORD object_id; //物品唯一ID
};

/// 修改仓库密码
#define UPDATE_STORE_PASS_USERCMD_PARAMETER 22
struct stUpdateStorePassUserCmd:public stTradeUserCmd
{
  stUpdateStorePassUserCmd()
  {
    byParam = UPDATE_STORE_PASS_USERCMD_PARAMETER;
  }
  char oldpass[8]; //旧密码
  char newpass[8]; //新密码
};

/// 能否摆摊
#define CAN_SELL_USERCMD_PARAMETER 23
struct stCanSellTradeUserCmd:public stTradeUserCmd
{
  stCanSellTradeUserCmd()
  {
    byParam = CAN_SELL_USERCMD_PARAMETER;
  }
  BYTE status; // 0 success,1 fail
};

enum
{
  STORN = 1,//升级宝石
  SIVER =2,//银
  SILK  =3,//丝绸
  CRYSTAL =4,//水晶
  EBONY  =5,//乌木
  YINGPI =6,//硬皮
};
/// 领赠品品精致升级宝石
#define GOLD_GIVE_USERCMD_PARAMETER 24
struct stGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stGoldGiveTradeUserCmd()
  {
    byParam = GOLD_GIVE_USERCMD_PARAMETER;
  }
  BYTE type;
};
/// 金币修理物品
#define REPAIROBJECT_GOLD_NPCTRADE_USERCMD_PARAMETER 25
struct stRepairObjectGoldNpcTradeUserCmd:public stTradeUserCmd
{
  stRepairObjectGoldNpcTradeUserCmd()
  {
    byParam = REPAIROBJECT_GOLD_NPCTRADE_USERCMD_PARAMETER;
  }
  DWORD id;  //修理物品id，全部修理时为0
};
/// 请求精致升级宝石个数
#define REQUEST_GOLD_GIVE_USERCMD_PARAMETER 26
struct stRequestGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stRequestGoldGiveTradeUserCmd()
  {
    byParam = REQUEST_GOLD_GIVE_USERCMD_PARAMETER;
  }
};
/// 返回精致升级宝石个数
#define RETURN_GOLD_GIVE_USERCMD_PARAMETER 27
struct stReturnGoldGiveTradeUserCmd:public stTradeUserCmd
{
  stReturnGoldGiveTradeUserCmd()
  {
    byParam = RETURN_GOLD_GIVE_USERCMD_PARAMETER;
  }
  DWORD Storn_num;//宝石个数
  DWORD Matarial_num; //材料组数
  DWORD Card_num;    //道具卡张数
};

//#ifndef _MSC_VER
/// 批量添加物品
#define ADD_OBJECT_SELL_LIST_USERCMD_PARAMETER 28
struct stAddObjectSellListUserCmd:public stTradeUserCmd
{
  stAddObjectSellListUserCmd()
  {
    byParam = ADD_OBJECT_SELL_LIST_USERCMD_PARAMETER;
    num=0;
  }
  WORD num;
  struct
  {
    t_Object object; //物品数据
    DWORD price; //物品价钱
    BYTE x;  //物品放置位置x坐标
    BYTE y; //物品放置位置y坐标
  }list[0];
};
//#endif //_MSC_VER

/// 用户请求添加物品id列表
#define REQUEST_ADD_OBJECT_SELL_USERCMD_PARAMETER 29
struct stRequestAddObjectSellUserCmd:public stTradeUserCmd
{
  stRequestAddObjectSellUserCmd()
  {
    byParam = REQUEST_ADD_OBJECT_SELL_USERCMD_PARAMETER;
    num=0;
  }
  WORD num;
  struct
  {
    DWORD qwThisID; //物品id
    DWORD price; //物品价钱
    BYTE x;  //物品放置位置x坐标
    BYTE y; //物品放置位置y坐标
  }list[0];
};

// [Shx Add 修改摆摊广告， 上下行通用]
#define UPDATE_SHOP_ADV_USERCMD_PARAMETER 30
struct stUpdateShopAdvcmd:public stTradeUserCmd
{
	stUpdateShopAdvcmd()
	{
		byParam = UPDATE_SHOP_ADV_USERCMD_PARAMETER;	
		size    = 0;
	}
	WORD size;
	struct stAdv
	{
		DWORD dwID;		//上行 时无用
		char strShopAdv[MAX_SHOPADV];
	} Datas[0];
};

//[Shx Add 交易时通知对方修改金钱]
#define UPDATE_TRADE_MONEY_USERCMD	31
struct stUpdateTradeMoneycmd:public stTradeUserCmd
{
	stUpdateTradeMoneycmd()
	{
		byParam = UPDATE_TRADE_MONEY_USERCMD;
	}
	DWORD dwMyID;
	DWORD dwOtherID;
	DWORD dwMoney;
};

/*
/// 领赠品材料
#define MATARIAL_GIVE_USERCMD_PARAMETER 30
struct stMatarialgiveTradeUserCmd:public stTradeUserCmd
{
        stMatarialgiveTradeUserCmd()
        {
                byParam = MATARIAL_GIVE_USERCMD_PARAMETER;
        }
};

#define REQUEST_MATARIAL_GIVE_USERCMD_PARAMETER 31
struct stRequestMatarialGiveTradeUserCmd:public stTradeUserCmd
{
        stRequestGoldGiveTradeUserCmd()
        {
                byParam = REQUEST_GOLD_GIVE_USERCMD_PARAMETER;
        }
};

#define RETURN_MATARIAl_GIVEL_USERCMD_PARAMETER 32
struct stReturnMatarialGiveTradeUserCmd:public stTradeUserCmd
{
        stReturnGoldGiveTradeUserCmd()
        {
                byParam = RETURN_GOLD_GIVE_USERCMD_PARAMETER;
        }
        DWORD num;//个数
};
*/

//////////////////////////////////////////////////////////////
// 交易指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 帮会指令定义开始
//////////////////////////////////////////////////////////////

struct stUnionUserCmd : public stNullUserCmd
{
  stUnionUserCmd()
  {
    byCmd = UNION_USERCMD;
  }
};

/// 帮会创建前的用户状态检查消息
const BYTE UNION_STATUS_CHECK_PARA = 1;
struct stUnionStatusCheckCmd  : public stUnionUserCmd
{
  stUnionStatusCheckCmd()
  {
    byParam = UNION_STATUS_CHECK_PARA;
  }
};

// 帮会创建命令
const BYTE CREATE_UNION_PARA = 2;
struct stCreateUnionCmd: public stUnionUserCmd
{
  stCreateUnionCmd()
  {
    byParam = CREATE_UNION_PARA;
  }
  char UnionName[MAX_NAMESIZE];  // 帮会名称
};

// 帮会创建成功通知指令
const BYTE SERVER_RETURN_UNION_CREATE_FAILED = 3;
struct stServerReturnUnionCheckCmd : public stUnionUserCmd
{
  stServerReturnUnionCheckCmd()
  {
    byParam = SERVER_RETURN_UNION_CREATE_FAILED;
  }
};

struct stUnionRember{
  char  memberName[MAX_NAMESIZE];      // 帮会成员名称
  char  aliasname[MAX_NAMESIZE];      // 成员别名[职务名称]
  WORD  level;          // 成员等级
  BYTE  byOnline;                          // 成员在线标志 0 为不在线 非0为在线
  WORD  occupation;        // 职业类型
  DWORD exploit;          // 功勋值
  char  septName[MAX_NAMESIZE];      // 所属家族
  BYTE  bySeptMaster;        // 0不是族长，1是族长
};

// 服务器返回帮会成员列表，及请求者的个人帮会信息
const BYTE ALL_UNION_MEMBER_PARA = 5;
struct stAllUnionMemberCmd : public stUnionUserCmd
{
  stAllUnionMemberCmd()
  {
    byParam = ALL_UNION_MEMBER_PARA;
  }
  WORD size;                     // 数量
  stUnionRember memberList[0];   // 成员列表
};


// 帮会的权限定义
enum UNIONPOWER {
  CHANGE_ALIAS,      // 改变称号
  ADD_MEMBER,        // 招收成员
  FIRE_MEMBER,       // 开除成员
  GENERAL,           // 普通会员
  MASTER,  // 帮主权限
  SECOND,  // 副帮主权限
        DARE,  // 发起或接受帮会战
  NOTIFY,  // 发公告
};


// 返回帮会成员的个人信息
const BYTE RETURN_UNION_MEMBER_INFO_PARA = 6;
struct stReturnUnionMemberInfoCmd : public stUnionUserCmd
{
  stReturnUnionMemberInfoCmd()
  {
    byParam = RETURN_UNION_MEMBER_INFO_PARA;
  }

  char alias[MAX_NAMESIZE];      // 消息接收者的别名
  BYTE byPower[2];                    // 消息接收者的权限信息
};

enum UNION_ADD_MEMBER{
      QUESTION,  // 发出邀请某人的询问
      ANSWER_YES,// 确认邀请
      ANSWER_NO          // 否定邀请
};

// 邀请他人加入帮会
const BYTE ADD_MEMBER_TO_UNION_PARA = 7;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToUnionCmd : public stUnionUserCmd
{
  stAddMemberToUnionCmd()
  {
    byParam = ADD_MEMBER_TO_UNION_PARA;
  }
  char   memberName[MAX_NAMESIZE];   // 被邀请的人
  DWORD memberID;                   // 被邀请人ID
  char   unionName[MAX_NAMESIZE];    // 工会名称
  BYTE   byState;                    // 参见 enum UNION_ADD_MEMBER
};

// 开除帮会成员
const BYTE FIRE_MEMBER_FROM_UNION_PARA = 8;
struct stFireMemberFromUnionCmd : public stUnionUserCmd
{
  stFireMemberFromUnionCmd()
  {
    byParam = FIRE_MEMBER_FROM_UNION_PARA ;
  }
  char memberName[MAX_NAMESIZE];
};

enum{
  UNION_MEMBER_STATUS_ONLINE,// 帮会成员上线
  UNION_MEMBER_STATUS_OFFLINE,// 帮会成员下线
  UNION_MEMBER_STATUS_FIRE, // 帮会成员被开除
  UNION_MEMBER_STATUS_NEWMEMBER,// 新增加帮会成员
  UNION_MEMBER_STATUS_ALIASCHANGE    // 成员别名改变
};

// 服务端更新帮会成员状态及信息通知消息 状态见上表
const BYTE BROADCAST_MEMBER_INFO_PARA = 10;
struct stBroadcastMemberInfo : public stUnionUserCmd
{
  stBroadcastMemberInfo()
  {
    byParam = BROADCAST_MEMBER_INFO_PARA;
    level = 0;
    bzero(name,MAX_NAMESIZE);
    bzero(septName,MAX_NAMESIZE);
    bySeptMaster = 0;
  }
  BYTE byStatus;          // 成员状态
  char name[MAX_NAMESIZE];      // 成员名称
  char aliasname[MAX_NAMESIZE];      // 成员别名
  WORD wdOccupation;        // 成员职业
  WORD level;          // 成员等级
  DWORD exploit;          // 功勋值
  char  septName[MAX_NAMESIZE];      // 所属家族
  BYTE bySeptMaster;        // 0,不是族长，1为族长
};

// 服务器端发送帮会信息
const BYTE UNION_BASE_INFO_PARA = 11;
struct stUnionBaseInfoCmd : public stUnionUserCmd
{
  stUnionBaseInfoCmd()
  {
    byParam = UNION_BASE_INFO_PARA;
  }
  char  unionName[MAX_NAMESIZE];         // 帮会名称
  char  master[MAX_NAMESIZE];        // 帮会会长
  WORD  wdLevel;                       // 帮会级别
  QWORD qwExp;                         // 帮会经验
  char  note[255];            // 帮会介绍
  DWORD dwMana;        // 帮会威望
  DWORD dwAction;        // 行动力
};

// 帮会成员申请退会
const BYTE UNIONMEMBER_LEAVE_UNION_PARA = 12;
struct stUnionMemberLeaveUnionCmd : public stUnionUserCmd
{
  stUnionMemberLeaveUnionCmd()
  {
    byParam = UNIONMEMBER_LEAVE_UNION_PARA;
  }
};

struct stUnionVoteRecord{
  char unionName [MAX_NAMESIZE];
  char master[MAX_NAMESIZE];
  WORD wdVoteNumber;
  char note[255];
};

// 帮会投票列表
const BYTE VOTELIST_UNION_PARA = 13;
struct stVoteListUnionCmd : public stUnionUserCmd
{
  stVoteListUnionCmd()
  {
    byParam = VOTELIST_UNION_PARA;
  }
  char unionName[MAX_NAMESIZE];
  DWORD dwSize;
  BYTE flag; // 0为消息头1为后续消息
  stUnionVoteRecord data[0];
};

// 帮会投票消息
const BYTE VOTE_UNION_PARA = 14;
struct stVoteUnionCmd : public stUnionUserCmd
{
  stVoteUnionCmd()
  {
    byParam = VOTE_UNION_PARA;
  }
  char unionName[MAX_NAMESIZE];
  BYTE bySuccess;   // 为1为成功 为0为失败
};

// 帮会设置帮会说明
const BYTE NOTE_UNION_PARA = 15;
struct stNoteUnionCmd : public stUnionUserCmd
{
  stNoteUnionCmd()
  {
    byParam = NOTE_UNION_PARA;
  }
  char noteBuf[255];
};

// 帮会成员别名设置
const BYTE CHANGE_UNION_MEMBER_ALIASNAME_PARA = 16;
struct stChangeUnionMemberAliasName : public stUnionUserCmd
{
  stChangeUnionMemberAliasName()
  {
    byParam = CHANGE_UNION_MEMBER_ALIASNAME_PARA;
  }

  char name[MAX_NAMESIZE];             // 帮众姓名
  char aliasname[MAX_NAMESIZE];        // 帮众别名
};

// 进入城主的帮会领地
const BYTE ENTER_UNION_CITY_AREA_PARA = 17;
struct stEnterUnionCityArea : public stUnionUserCmd
{
  stEnterUnionCityArea()
  {
    byParam = ENTER_UNION_CITY_AREA_PARA;
  }
};

enum
{
  QUESTION_UNION_MEMBER_POWER,// 请求发送权限
  RESPOND_UNION_MEMBER_POWER,//  返回某帮众权限
  SET_UNION_MEMBER_POWER,//  设置某帮众权限
};

// 请求(设置)帮众权限
const BYTE UNION_MEMBER_POWER_PARA = 18;
struct stUnionMemberPower : public stUnionUserCmd
{
  stUnionMemberPower()
  {
    byParam = UNION_MEMBER_POWER_PARA;
  }
  
  char name[MAX_NAMESIZE]; // 帮众姓名
  BYTE byPower[2]; // 权限
  BYTE byType; // 消息类型
};

enum
{
  QUESTION_CITY_HOLD,// 查询城市所属
  QUESTION_CITY_DARE,// 当天城市争夺战
};

// 查询问城市帮会信息
const BYTE QUESTION_UNION_CITY_INFO_PARA = 19;
struct stQuestionUnionCityInfo : public stUnionUserCmd
{
  stQuestionUnionCityInfo()
  {
    byParam = QUESTION_UNION_CITY_INFO_PARA;
  }
  
  BYTE byType;  
};

enum
{
  COUNTRY_UNION_SORT,// 本国帮会排行榜
  WORLD_UNION_SORT,// 世界帮会排行榜
};

// 查询家族排行榜（根据声望）
const BYTE REQ_UNION_SORT_PARA = 20;
struct stReqUnionSort : public stUnionUserCmd
{
  stReqUnionSort()
  {
    byParam = REQ_UNION_SORT_PARA;
    byType = COUNTRY_UNION_SORT;
  }
  
  BYTE byType;
};

struct stUnionSortInfo
{
  char  unionName[MAX_NAMESIZE];         // 帮会名称
  DWORD dwMana;        // 帮会威望
  DWORD dwOrder;        // 帮会排名
  DWORD dwCountryID;      // 国家ID
};

// 返回帮会排行榜（根据威望）
const BYTE RTN_UNION_SORT_PARA = 21;
struct stRtnUnionSort : public stUnionUserCmd
{
  stRtnUnionSort()
  {
    byParam = RTN_UNION_SORT_PARA;
    dwSize = 0;
  }
  
  BYTE byType;
  DWORD dwSize;
  stUnionSortInfo data[0];
};

// 帮会资金捐献
const BYTE CONTRIBUTE_UNION_PARA = 22;
struct stContributeUnion : public stUnionUserCmd
{
  stContributeUnion()
  {
    byParam = CONTRIBUTE_UNION_PARA;
  }
  
  DWORD dwMoney;
};

// 帮会资金查询
const BYTE REQ_UNION_MONEY_PARA = 23;
struct stReqUnionMoney : public stUnionUserCmd
{
  stReqUnionMoney()
  {
    byParam = REQ_UNION_MONEY_PARA;
  }
};

struct stUnionRecord{
  char unionName [MAX_NAMESIZE];
  char master[MAX_NAMESIZE];
  char note[255];
};

// 帮会投票列表
const BYTE LIST_UNION_PARA = 24;
struct stListUnionCmd : public stUnionUserCmd
{
  stListUnionCmd()
  {
    byParam = LIST_UNION_PARA;
  }
  DWORD dwSize;
  BYTE flag; // 0为消息头1为后续消息
  stUnionRecord data[0];
};

// 请求加入帮会消息
const BYTE REQUEST_JOIN_UNION_PARA = 25;
struct stRequestJoinUnionCmd : public stUnionUserCmd
{
  stRequestJoinUnionCmd()
  {
    byParam = REQUEST_JOIN_UNION_PARA;
  }
  char name[MAX_NAMESIZE]; //发给服务器的时候填对方会长的名字，服务器发出来的时候填的是请求人的名字
  BYTE status;
};

// 放弃占领城市
const BYTE REQUEST_ABJURATION_CITY_PARA = 26;
struct stRequestAbjurationCitynCmd : public stUnionUserCmd
{
  stRequestAbjurationCitynCmd()
  {
    byParam = REQUEST_ABJURATION_CITY_PARA;
  }
};

// 请求帮会名称
const BYTE REQ_UNION_NAME_PARA = 27;
struct stReqUnionNameCmd : public stUnionUserCmd
{
  stReqUnionNameCmd()
  {
    byParam = REQ_UNION_NAME_PARA;
    dwUnionID = 0;
  }

  DWORD dwUnionID;
};

// 返回帮会名称
const BYTE RTN_UNION_NAME_PARA = 28;
struct stRtnUnionNameCmd : public stUnionUserCmd
{
  stRtnUnionNameCmd()
  {
    byParam = RTN_UNION_NAME_PARA;
    bzero(name,MAX_NAMESIZE);
    dwUnionID = 0;
  }

  DWORD dwUnionID;
  char name[MAX_NAMESIZE];
};

// 请求帮会名称列表
const BYTE REQ_UNION_NAME_LIST_PARA = 29;
struct stReqUnionNameLlistCmd : public stUnionUserCmd
{
  stReqUnionNameLlistCmd()
  {
    byParam = REQ_UNION_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  DWORD dwUnionID[0];
};

// 返回帮会名称列表
const BYTE RTN_UNION_NAME_LIST_PARA = 30;
struct stRtnUnionNameListCmd : public stUnionUserCmd
{
  stRtnUnionNameListCmd()
  {
    byParam = RTN_UNION_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  struct
  {
    DWORD dwUnionID;
    char name[MAX_NAMESIZE];
  } list[0];
};

// 城主任命捕头
#define APPOINT_CITY_CATCHER_PARA  31
struct stAppointCityCatcherCmd : public stUnionUserCmd
{
  stAppointCityCatcherCmd()
  {
    byParam = APPOINT_CITY_CATCHER_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE];
};

// 撤消捕头
#define CANCEL_CITY_CATCHER_PARA  32
struct stCancelCityCatcherCmd : public stUnionUserCmd 
{
  stCancelCityCatcherCmd()
  {
    byParam = CANCEL_CITY_CATCHER_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 帮会指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 国家指令定义开始
//////////////////////////////////////////////////////////////

struct stCountryUserCmd : public stNullUserCmd
{
  stCountryUserCmd()
  {
    byCmd = COUNTRY_USERCMD;
  }
};

// 变更国籍
const BYTE CHANGE_COUNTRY_PARA = 1;
struct stChangeCountryCmd : public stCountryUserCmd
{
    stChangeCountryCmd()
    {
      byParam = CHANGE_COUNTRY_PARA;
    }

    DWORD dwToCountryID; // 变更到国家的ID
};

enum 
{
  REQUEST_BATTLEFIELD_COUNTRY_LIST,// 请求战场列表
  REQUEST_DARE_COUNTRY_LIST,// 请求战场列表
};

// 请求战场列表
const BYTE REQUEST_DARE_COUNTRY_PARA =2;
struct stRequestDareCountryCmd : public stCountryUserCmd
{
  stRequestDareCountryCmd()
  {
    byParam = REQUEST_DARE_COUNTRY_PARA;
  }

  BYTE byType; // 0,请求战场列表，1，请求挑战列表
};

struct stCountryInfo
{
  DWORD dwID;   // 国家ID
  BYTE  byType;  // 0,参战国，1，第三方国
};

// 返回战场列表
const BYTE RETURN_DARE_COUNTRY_PARA = 3;
struct stReturnDareCountryCmd : public stCountryUserCmd
{
  stReturnDareCountryCmd()
  {
    byParam = RETURN_DARE_COUNTRY_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize; // 战场个数
  BYTE  byType; // 0,战场列表，挑战列表
  
  stCountryInfo country_list[0]; //战场国家ID数组
};

// 请求传送到指定战场
const BYTE TRANS_DARE_COUNTRY_PARA = 4;
struct stTransDareCountryCmd : public stCountryUserCmd
{
  stTransDareCountryCmd()
  {
    byParam = TRANS_DARE_COUNTRY_PARA;
    dwCountryID = 0;
  }

  DWORD dwCountryID;
};

// 请求国战挑战
const BYTE DARE_COUNTRY_FORMAL_PARA = 5;
struct stDareCountryFormalCmd : public stCountryUserCmd
{
  stDareCountryFormalCmd()
  {
    byParam = DARE_COUNTRY_FORMAL_PARA;
  }

  DWORD dwCountryID; // 要挑战的国家
};

enum
{
  DARE_RECORD_RESULT,// 对战结果记录
  DARE_RECORD_STAT,// 对战结果统计
  DARE_RECORD_PLAN,// 当天对战安排
};

// 请求记录
const BYTE REQUEST_DARE_RECORD_PARA = 6;
struct stRequestDareRecordCmd : public stCountryUserCmd
{
  stRequestDareRecordCmd()
  {
    byParam = REQUEST_DARE_RECORD_PARA;
  }

  BYTE byType;  // 查询类型
};

struct stDareResult
{
  DWORD  dareTime;      // 对战时间
  DWORD  attCountry;    // 挑战国ID
  DWORD  defCountry;    // 防御国ID
  BYTE   byResult;      // 0,挑战国胜(攻陷对方皇城)，1,挑战国败(时间到了，却未攻陷)，2,防御国反攻成功(攻陷挑战国皇城)
  char   attKingName[MAX_NAMESIZE];
  char   defKingName[MAX_NAMESIZE];
};

// 对战结果
const BYTE RETURN_DARE_RECORD_RESULT_PARA = 7;
struct stReturnDareRecordResultCmd : public stCountryUserCmd
{
  stReturnDareRecordResultCmd()
  {
    byParam = RETURN_DARE_RECORD_RESULT_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDareResult dare_result[0];
};

struct stDareStat
{
  DWORD dwCountry;  // 国家ID
  DWORD dwFormalWin;  // 正式国战胜利次数
  DWORD dwFormalFail;  // 正式国战失败次数
  DWORD dwAnnoyWin;  // 骚扰国战胜利次数
  DWORD dwAnnoyFail;  // 骚扰国战失败次数
};
// 对战统计
const BYTE RETURN_DARE_RECORD_STAT_PARA =8;
struct stReturnDareRecordStatCmd : public stCountryUserCmd
{
  stReturnDareRecordStatCmd()
  {
    byParam = RETURN_DARE_RECORD_STAT_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDareStat dare_stat[0];
};

struct stDarePlan
{
  DWORD planTime;
  DWORD attCountry;  // 挑战国
  DWORD defCountry;  // 防御国
};

// 对战计划
const BYTE RETURN_DARE_RECORD_PLAN_PARA =9;
struct stReturnDareRecordPlanCmd : public stCountryUserCmd
{
  stReturnDareRecordPlanCmd()
  {
    byParam = RETURN_DARE_RECORD_PLAN_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stDarePlan dare_plan[0];
};

// 叛国（变为无国籍）
const BYTE CANCEL_COUNTRY_PARA = 10;
struct stCancelCountryCmd : public stCountryUserCmd
{
    stCancelCountryCmd()
    {
      byParam = CANCEL_COUNTRY_PARA;
    }
};

// 申请加入国籍
const BYTE APPLY_COUNTRY_PARA = 11;
struct stApplyCountryCmd : public stCountryUserCmd
{
    stApplyCountryCmd()
    {
      byParam = APPLY_COUNTRY_PARA;
    }

    DWORD dwToCountryID; // 申请加入的国籍
};

/// 税率查询
const BYTE TAX_COUNTRY_PARA = 12;
struct stTaxCountryUserCmd:public stCountryUserCmd
{
  stTaxCountryUserCmd()
  {
    byParam = TAX_COUNTRY_PARA;
  }
  DWORD dwCountry;
  BYTE byTax; 
};

/// 国库查询
const BYTE FISK_COUNTRY_PARA = 13;
struct stFiskCountryUserCmd:public stCountryUserCmd
{
  stFiskCountryUserCmd()
  {
    byParam = FISK_COUNTRY_PARA;
    qwGold = 0;
    qwMaterial = 0;  
    qwStock = 0;
  }
  
  DWORD dwCountry;
  QWORD qwGold; 
  QWORD qwMaterial; // 物资
  QWORD qwStock;    // 原料
};

/// 税率设置
const BYTE SETTAX_COUNTRY_PARA = 14;
struct stSetTaxCountryUserCmd:public stCountryUserCmd
{
  stSetTaxCountryUserCmd()
  {
    byParam = SETTAX_COUNTRY_PARA;
  }
  DWORD dwCountry;
  BYTE byTax; 
};

struct stCountryStar
{
  DWORD dwCountry;
  DWORD dwStar;
};

/// 设置国家星号
const BYTE UPDATE_COUNTRY_STAR = 15;
struct stUpdateCountryStarCmd : public stCountryUserCmd
{
  stUpdateCountryStarCmd()
  {
    byParam = UPDATE_COUNTRY_STAR;
    dwSize = 0;
  }
  DWORD dwSize;
  stCountryStar data[0];
};


/// 国家捐献
const BYTE CONTRIBUTE_COUNTRY_MATERIAL = 16;
struct stContributeCountryMaterialCmd : public stCountryUserCmd
{
  stContributeCountryMaterialCmd()
  {
    byParam = CONTRIBUTE_COUNTRY_MATERIAL;
    itemID = 0;
  }
  DWORD itemID;
};

/// 国战状态设置
const BYTE SETCOUNTRY_DARE_PARA = 17;
struct stSetCountryDareUserCmd:public stCountryUserCmd
{       
  stSetCountryDareUserCmd()
  {
    byParam = SETCOUNTRY_DARE_PARA;
    dwCountry = 0;
    byStatus = 0;
    byResult = 0;
  }

  
  DWORD dwCountry; // 敌对国家ID
  BYTE  byStatus; // 1为进入国战，0为退出国战
  BYTE  byResult; // 对战结果，1为胜方，0为失败方,当byStatus为0时，该字段有意义
};      

/// 更新国王信息
const BYTE UPDATE_COUNTRY_KING = 18;
struct stUpdateCountryKingUserCmd : public stCountryUserCmd
{
  stUpdateCountryKingUserCmd()
  {
    byParam = UPDATE_COUNTRY_KING;
    bzero(kingName,sizeof(kingName));
    isEmperor = 0;
  }
  char   kingName[MAX_NAMESIZE];
  BYTE   isEmperor; // 0不是皇帝所在国,1是皇帝所在国
};

enum
{
  ANSWER_COUNTRY_DARE_QUESTION,
  ANSWER_COUNTRY_DARE_NO,
  ANSWER_COUNTRY_DARE_YES
};
/// 国战应答
const BYTE ANSWER_COUNTRY_DARE_PARA= 19;
struct stAnswerCountryDareUserCmd : public stCountryUserCmd
{
  stAnswerCountryDareUserCmd()
  {
    byParam = ANSWER_COUNTRY_DARE_PARA;
    byStatus = ANSWER_COUNTRY_DARE_QUESTION;
  }
  
  BYTE byStatus;
};

/// 选择要在国战时传送到边境的玩家等级
const BYTE SELECT_TRANS_LEVEL= 20;
struct stSelectTransLevelUserCmd : public stCountryUserCmd
{
  stSelectTransLevelUserCmd()
  {
    byParam = SELECT_TRANS_LEVEL;
    dwLevel = 0;
  }

  DWORD dwLevel;//大于等于该等级
};

//国王禁言一个玩家
#define FORBID_TALK_COUNTRY_PARA 21
struct stForbidTalkCountryUserCmd : public stCountryUserCmd
{
  stForbidTalkCountryUserCmd()
  {
    byParam = FORBID_TALK_COUNTRY_PARA;
    bzero(name,MAX_NAMESIZE);
  }
  char name[MAX_NAMESIZE];
};

enum
{
  WAIT_TECH_TYPE = 1,// 投票选出的科技，等待国王选择官员
  ACTIVE_TECH_TYPE = 2,// 正在进行升级
  FINISH_TECH = 3,// 已经完成升级，可以打造相应装备(包括等级大于0的所有状态的科技)
};

// 获取指定类型科技列表
#define REQ_TECH_PARA 22
struct stReqTechUserCmd : public stCountryUserCmd
{
  stReqTechUserCmd()
  {
    byParam = REQ_TECH_PARA;
    dwType = 0;
  }
  
  DWORD dwType; // 1为等研究的科技，2，正在升级的科技,3，已完成的科技
};

struct stTechItem
{
  DWORD dwOption;
  char  szOptionDesc[MAX_NAMESIZE];
  char  szResearchName[MAX_NAMESIZE];
  DWORD dwLevel;
  DWORD dwProgress;
};

// 返回指定类型科技列表
#define RTN_TECH_PARA 23
struct stRtnTechUserCmd : public stCountryUserCmd
{
  stRtnTechUserCmd()
  {
    byParam = RTN_TECH_PARA;
    dwSize = 0;
    dwType = 0;
  }
  
  DWORD dwType;
  DWORD dwSize;
  stTechItem data[0];
};

// 获取待选官员列表
#define REQ_WAIT_OFFICIAL_PARA 24
struct stReqWaitOfficialUserCmd : public stCountryUserCmd
{
  stReqWaitOfficialUserCmd()
  {
    byParam = REQ_WAIT_OFFICIAL_PARA;
  }
};

struct stWaitOfficialItem
{
  DWORD dwCharID;
  char  szName[MAX_NAMESIZE];
};

// 返回待选官员列表
#define RTN_WAIT_OFFICIAL_PARA 25
struct stRtnWaitOfficialUserCmd : public stCountryUserCmd
{
  stRtnWaitOfficialUserCmd()
  {
    byParam = RTN_WAIT_OFFICIAL_PARA;
    dwSize = 0;
  }
  
  DWORD dwSize;
  stWaitOfficialItem data[0];
};

// 设置科技研究员
#define SET_TECH_SEARCH_PARA 26
struct stSetTechSearchUserCmd : public stCountryUserCmd
{
  stSetTechSearchUserCmd()
  {
    byParam = SET_TECH_SEARCH_PARA;
    dwOption = 0;
    dwCharID = 0;
  }

  DWORD dwOption;
  DWORD dwCharID;
};

// 提升科技完成度
#define UP_TECH_DEGREE_PARA 27
struct stUpTechDegreeUserCmd : public stCountryUserCmd
{
  stUpTechDegreeUserCmd()
  {
    byParam = UP_TECH_DEGREE_PARA;
    dwOption = 0;
  }

  DWORD dwOption;
};

enum
{
  QUESTION_CONFIRM_SEARCHER,// 询问是否同意成为研究员
  YES_CONFIRM_SEARCHER,// 同意成为研究员
  NO_CONFIRM_SEARCHER // 不同意成为研究员
};

// 询问是否同意成为研究员
#define CONFIRM_SEARCHER_PARA 28
struct stConfirmSearcherUserCmd : public stCountryUserCmd
{
  stConfirmSearcherUserCmd()
  {
    byParam = CONFIRM_SEARCHER_PARA;
    byStatus = QUESTION_CONFIRM_SEARCHER;
    dwOption = 0;
  }
      
  DWORD dwOption;  // 科技ID  
  BYTE byStatus;
};

// 该国人不能登陆
#define  DISENABLEL_OGIN_COUNTRY_PARA  29 
enum  FALSE_COUNTRY_STATUS
{
  FALSE_REGISTER_COUNTRY,//return when register fail 
  FALSE_LOGIN_COUNTRY     // return when login fail 
};
struct stDisableLoginCountryCmd : public stCountryUserCmd
{
  stDisableLoginCountryCmd()
  {
    byParam = DISENABLEL_OGIN_COUNTRY_PARA;
  }
  FALSE_COUNTRY_STATUS status;
};

// 取消科技研究员
#define CANCEL_TECH_SEARCH_PARA 30
struct stCancelTechSearchUserCmd : public stCountryUserCmd
{
  stCancelTechSearchUserCmd()
  {
    byParam = CANCEL_TECH_SEARCH_PARA;
    dwOption = 0;
  }

  DWORD dwOption;
};

// 申请国战反攻
#define ANTI_DARE_COUNTRY_FORMAL_PARA  31
struct stAntiDareCountryFormalCmd : public stCountryUserCmd
{
  stAntiDareCountryFormalCmd()
  {
    byParam = ANTI_DARE_COUNTRY_FORMAL_PARA;
  }

  DWORD dwCountryID; // 要挑战的国家
};

// 发布国家公告
#define COUNTRY_NOTE_PARA  32
struct stCountryNoteCmd : public stCountryUserCmd
{
  stCountryNoteCmd()
  {
    byParam = COUNTRY_NOTE_PARA;
  }

  char note[255];
};

// 请求国家公告
#define REQ_COUNTRY_NOTE_PARA  33
struct stReqCountryNoteCmd : public stCountryUserCmd
{
  stReqCountryNoteCmd()
  {
    byParam = REQ_COUNTRY_NOTE_PARA;
  }
};

// 国王处罚玩家
#define KING_PUNISH_COUNTRY_PARA  34
struct stKingPunishCountryCmd : public stCountryUserCmd
{
  stKingPunishCountryCmd()
  {
    byParam = KING_PUNISH_COUNTRY_PARA;
  }
  char name[MAX_NAMESIZE];//指定玩家名字
  DWORD method;//处罚方式 1:禁言 2:关监狱
};

// 皇帝处罚玩家
#define EMPEROR_PUNISH_COUNTRY_PARA  35
struct stEmperorPunishCountryCmd : public stCountryUserCmd
{
  stEmperorPunishCountryCmd()
  {
    byParam = EMPEROR_PUNISH_COUNTRY_PARA;
  }
  char name[MAX_NAMESIZE];//指定玩家名字
  DWORD method;//处罚方式 1:禁言 2:关监狱
};

// 请求大将军的信息
#define REQ_GEN_COUNTRY_PARA  36
struct stReqGenCountryCmd : public stCountryUserCmd
{
  stReqGenCountryCmd()
  {
    byParam = REQ_GEN_COUNTRY_PARA;
  }
};

// 返回大将军的信息
#define RET_GEN_COUNTRY_PARA  37
struct stRetGenCountryCmd : public stCountryUserCmd
{
  stRetGenCountryCmd()
  {
    byParam = RET_GEN_COUNTRY_PARA;
  }
  DWORD level;
  DWORD exp;
  DWORD maxExp;
};

// 任命捕头
#define APPOINT_CATCHER_PARA  38
struct stAppointCatcherCmd : public stCountryUserCmd
{
  stAppointCatcherCmd()
  {
    byParam = APPOINT_CATCHER_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE];
};

// 撤消捕头
#define CANCEL_CATCHER_PARA  39
struct stCancelCatcherCmd : public stCountryUserCmd
{
  stCancelCatcherCmd()
  {
    byParam = CANCEL_CATCHER_PARA;
  }
};

// 任命外交官
#define APPOINT_DIPLOMAT_PARA  40
struct stAppointDiplomatCmd : public stCountryUserCmd
{
  stAppointDiplomatCmd()
  {
    byParam = APPOINT_DIPLOMAT_PARA;
    bzero(name,sizeof(name));
  }

  char name[MAX_NAMESIZE];
};

// 撤消外交官
#define CANCEL_DIPLOMAT_PARA  41
struct stCancelDiplomatCmd : public stCountryUserCmd
{
  stCancelDiplomatCmd()
  {
    byParam = CANCEL_DIPLOMAT_PARA;
  }
};

// 查询国家强弱
#define REQUEST_COUNTRY_POWER_PARA  42
struct stRequestCountryPowerCmd : public stCountryUserCmd
{
  stRequestCountryPowerCmd()
  {
    byParam = REQUEST_COUNTRY_POWER_PARA;
  }
};

// 返回国家强弱
#define RETURN_COUNTRY_POWER_PARA  43
struct stReturnCountryPowerCmd : public stCountryUserCmd
{
  stReturnCountryPowerCmd()
  {
    byParam = RETURN_COUNTRY_POWER_PARA;
  }
  BYTE country[2];
};

// 领取每日皇帝的奖励
#define REQ_DAILY_EMPEROR_MONEY 44
struct stReqDailyEmperorMoneyCmd : public stCountryUserCmd
{
  stReqDailyEmperorMoneyCmd()
  {
    byParam = REQ_DAILY_EMPEROR_MONEY;
  }
};

// 请求国王排行榜
#define REQ_KING_LIST_PARA  45
struct stReqKingListCmd : public stCountryUserCmd
{
  stReqKingListCmd()
  {
    byParam = REQ_KING_LIST_PARA;
  }
};

struct _KingListItem
{
  char  king_name[MAX_NAMESIZE]; // 国王名称
  WORD  online_time; //在线时间 单位为小时
  DWORD country_id; // 国家ID
};

// 返回国王排行榜
#define RTN_KING_LIST_PARA  46
struct stRtnKingListCmd : public stCountryUserCmd
{
  stRtnKingListCmd()
  {
    byParam = RTN_KING_LIST_PARA;
    size = 0;
  }
  BYTE size;
  _KingListItem data[0];
};
 
// 请求城市占领者
#define REQ_CITY_OWNER_LIST_PARA  47
struct stReqCityOwnerListCmd : public stCountryUserCmd
{
  stReqCityOwnerListCmd()
  {
    byParam = REQ_CITY_OWNER_LIST_PARA;
  }
};

// 返回城市占领者列表
#define RTN_CITY_OWNER_LIST_PARA  48
struct stRtnCityOwnerListCmd : public stCountryUserCmd
{
  stRtnCityOwnerListCmd()
  {
    byParam = RTN_CITY_OWNER_LIST_PARA;
    size = 0;
  }
  WORD size;
  struct
  {
    char cityName[MAX_NAMESIZE];
    char unionName[MAX_NAMESIZE];
  }list[0];
};
 
// 请求城市占领者
#define REQ_NPC_OWNER_LIST_PARA  49
struct stReqNpcOwnerListCmd : public stCountryUserCmd
{
  stReqNpcOwnerListCmd()
  {
    byParam = REQ_NPC_OWNER_LIST_PARA;
  }
};
// 返回城市占领者
#define RTN_NPC_OWNER_LIST_PARA  50
struct stRtnNpcOwnerListCmd : public stCountryUserCmd
{
  stRtnNpcOwnerListCmd()
  {
    byParam = RTN_NPC_OWNER_LIST_PARA;
    size=0;
  }
  WORD size;
  struct
  {
    DWORD npcID;//npc的数据id
    char mapName[MAX_NAMESIZE];//地图名称
    WORD x;    //所在位置
    WORD y;    //所在位置
    char septName[MAX_NAMESIZE];//占领的家族名称
  }list[0];
};
//////////////////////////////////////////////////////////////
// 国家指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 投票指令定义开始
//////////////////////////////////////////////////////////////
enum
{
  TECH_VOTE // 科技投票
};

struct stVoteUserCmd : public stNullUserCmd
{
    stVoteUserCmd()
    {
        byCmd = VOTE_USERCMD;
    }
};

// 请求投票列表
#define REQUEST_VOTE_LIST_PARA 1
struct stRequestVoteListUserCmd : public stVoteUserCmd
{
  stRequestVoteListUserCmd()
  {
    byParam = REQUEST_VOTE_LIST_PARA;
    byType = TECH_VOTE;
  }

  BYTE byType; // 投票类型
};

struct stVoteItem
{
  DWORD dwOption; // 选项编号
  DWORD dwBallot; // 选项当前投票数
  char  szOptionDesc[MAX_NAMESIZE];
};

// 返回投票列表
#define RETURN_VOTE_LIST_PARA 2
struct stReturnVoteListUserCmd : public stVoteUserCmd
{
  stReturnVoteListUserCmd()
  {
    byParam = RETURN_VOTE_LIST_PARA;
    dwSize = 0;
    byType = TECH_VOTE;
    dwVoteID = 0;
  }

  DWORD dwVoteID;
  BYTE byType;
  DWORD dwSize;
  stVoteItem data[0];
};

// 提交投票
#define COMMIT_VOTE_PARA 3
struct stCommitVoteUserCmd : public stVoteUserCmd
{
  stCommitVoteUserCmd()
  {
    byParam = COMMIT_VOTE_PARA;
    dwVoteID = 0;
    dwOption = 0;
  }

  DWORD dwVoteID; // 该次投票的ID
  DWORD dwOption; // 该次提交的选项
};
//////////////////////////////////////////////////////////////
// 投票指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 军队指令定义开始
//////////////////////////////////////////////////////////////
struct stArmyUserCmd : public stNullUserCmd
{
    stArmyUserCmd()
    {
        byCmd = ARMY_USERCMD;
    }
};

// 创建军队
#define CREATE_ARMY_PARA 1
struct stCreateArmyUserCmd : public stArmyUserCmd
{
  stCreateArmyUserCmd()
  {
    byParam = CREATE_ARMY_PARA;
    bzero(armyName,sizeof(armyName));
    bzero(genName,sizeof(genName));
  }

  char armyName[8+1]; // 军队名称限定为4个汉字
  char genName[MAX_NAMESIZE];
};

// 请求待选将军列表
#define REQ_WAIT_GEN_PARA 2
struct stReqWaitGenUserCmd : public stArmyUserCmd
{
  stReqWaitGenUserCmd()
  {
    byParam = REQ_WAIT_GEN_PARA;
  }
};

struct stWaitGenItem
{
  DWORD dwCharID;
  char  szName[MAX_NAMESIZE];
};

// 返回候选将军列表
#define RTN_WAIT_GEN_PARA 3
struct stRtnWaitGenUserCmd : public stArmyUserCmd
{
  stRtnWaitGenUserCmd()
  {
    byParam = REQ_WAIT_GEN_PARA;
    dwSize = 0;
  }

  DWORD dwSize;
  stWaitGenItem data[0];
};

enum
{
  QUESTION_ARMY_GEN,// 询问是否愿意成为将军
  YES_ARMY_GEN,// 同意成为将军
  NO_ARMY_GEN,// 拒绝成为将军
};

// 询问是否同意成为将军
#define REQ_ARMY_GEN_PARA 4
struct stReqArmyGenUserCmd : public stArmyUserCmd
{
  stReqArmyGenUserCmd()
  {
    byParam = REQ_ARMY_GEN_PARA;
    byStatus = QUESTION_ARMY_GEN;
  }

  BYTE byStatus;
  
};

enum
{
  COUNTRY_ARMY_LIST,// 用于国家对话框，显示全国军队列表
  CITY_ARMY_LIST,// 用于NPC对话，显示本城军队列表
};
// 请求军队列表
#define REQ_ARMY_LIST_PARA 5
struct stReqArmyListUserCmd : public stArmyUserCmd
{
  stReqArmyListUserCmd()
  {
    byParam = REQ_ARMY_LIST_PARA;
    byType = COUNTRY_ARMY_LIST;
  }

  BYTE byType;
};

struct stArmyBaseInfo
{
  DWORD dwArmyID;
  char  name[MAX_NAMESIZE]; // 军队名称
  char  cityname[MAX_NAMESIZE]; // 所属城市
  char  genname[MAX_NAMESIZE]; // 将军姓名
  DWORD dwCapNum; // 队长人数
};

// 返回军队列表
#define RTN_ARMY_LIST_PARA 6
struct stRtnArmyListUserCmd : public stArmyUserCmd
{
  stRtnArmyListUserCmd()
  {
    byParam = RTN_ARMY_LIST_PARA;
    dwSize = 0;
  }

  DWORD dwSize;
  BYTE  byType;
  stArmyBaseInfo data[0];
};

// 请求军队详细信息
#define REQ_ARMY_SPEC_PARA 7
struct stReqArmySpecUserCmd : public stArmyUserCmd
{
  stReqArmySpecUserCmd()
  {
    byParam = REQ_ARMY_SPEC_PARA;
    dwArmyID = 0;
  }
  
  DWORD dwArmyID;
};

struct stCaptainBase
{
  char name[MAX_NAMESIZE];
  DWORD dwCharID;
};
// 返回军队详细信息
#define RTN_ARMY_SPEC_PARA 8
struct stRtnArmySpecUserCmd : public stArmyUserCmd
{
  stRtnArmySpecUserCmd()
  {
    byParam = RTN_ARMY_SPEC_PARA;
    dwSize = 0;
    bzero(name,MAX_NAMESIZE);
    bzero(cityname,MAX_NAMESIZE);
    bzero(genname,MAX_NAMESIZE);
  }

  char name[MAX_NAMESIZE]; // 军队名
  char cityname[MAX_NAMESIZE]; // 城市名
  char genname[MAX_NAMESIZE]; // 将军名
  DWORD dwSize;
  stCaptainBase data[0];
};

// 离开军队
#define EXIT_ARMY_PARA 9
struct stExitArmyUserCmd : public stArmyUserCmd
{
  stExitArmyUserCmd()
  {
    byParam = EXIT_ARMY_PARA;
  }
};  

// 解散军队
#define REMOVE_ARMY_PARA 10
struct stRemoveArmyUserCmd : public stArmyUserCmd
{
  stRemoveArmyUserCmd()
  {
    byParam = REMOVE_ARMY_PARA;
    dwArmyID = 0;
  }

  DWORD dwArmyID;
};

// 更改军队名称
#define CHANGE_ARMY_NAME_PARA 11
struct stChangeArmyNameUserCmd : public stArmyUserCmd
{
  stChangeArmyNameUserCmd()
  {
    byParam = CHANGE_ARMY_NAME_PARA;
    dwArmyID = 0;
    bzero(newArmyName,MAX_NAMESIZE);
  }

  DWORD dwArmyID;
  char  newArmyName[MAX_NAMESIZE];
};

enum ADD_ARMY_CAPTAIN{
  QUESTION_CAPTAIN,// 发出询问
  ANSWER_CAPTAIN_YES,// 确认邀请
  ANSWER_CAPTAIN_NO,// 拒绝邀请
};
// 招收队长
#define ADD_ARMY_CAPTAIN_PARA 12
struct stAddArmyCaptainUserCmd : public stArmyUserCmd
{
  stAddArmyCaptainUserCmd()
  {
    byParam = ADD_ARMY_CAPTAIN_PARA;
    bzero(capName,MAX_NAMESIZE);
    bzero(armyName,MAX_NAMESIZE);
    capID = 0;
    armyID = 0;
    byState = QUESTION_CAPTAIN;
  }

  char capName[MAX_NAMESIZE]; // 被邀请的人
  char armyName[MAX_NAMESIZE]; // 邀请的军队名称
  DWORD armyID; // 军队ID
  DWORD capID; // 被邀请人ID
  BYTE byState; // 参见 enum ADD_ARMY_CAPTAIN
};

// 开除队长
#define FIRE_ARMY_CAPTAIN_PARA 13
struct stFireArmyCaptainUserCmd : public stArmyUserCmd
{
  stFireArmyCaptainUserCmd()
  {
    byParam = FIRE_ARMY_CAPTAIN_PARA;
    dwUserID = 0;
  }

  DWORD dwUserID; // 待开除的队长ID,通过军队详细信息获得
};

/*// 更改军队将军
#define CHANGE_ARMY_GEN_PARA 12
struct stChangeArmyGenUserCmd : public stArmyUserCmd
{
  stChangeArmyGenUserCmd()
  {
    byParam = CHANGE_ARMY_GEN_PARA;
    dwArmyID = 0;
    bzero(newArmyGen,MAX_NAMESIZE);
  }

  DWORD dwArmyID;
  char  newArmyGen[MAX_NAMESIZE];
};
*/
//////////////////////////////////////////////////////////////
// 军队指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
// 护宝指令定义开始
//////////////////////////////////////////////////////////////
struct stGemUserCmd : public stNullUserCmd
{
    stGemUserCmd()
    {
        byCmd = GEM_USERCMD;
    }
};

// 领取龙精
#define REQUEST_DRAGON_PARA 1
struct stReqDragonUserCmd : public stGemUserCmd
{
  stReqDragonUserCmd()
  {
    byParam = REQUEST_DRAGON_PARA;
  }
};

// 领取虎魄
#define REQUEST_TIGER_PARA 2
struct stReqTigerUserCmd : public stGemUserCmd
{
  stReqTigerUserCmd()
  {
    byParam = REQUEST_TIGER_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 护宝指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 战斗指令定义开始
//////////////////////////////////////////////////////////////

// 对战类型定义
enum
{
  UNION_DARE  = 0,// 帮会对战 
  SCHOOL_DARE  = 1,// 师门对战
  SEPT_DARE  = 2,// 家族对战
  SEPT_NPC_DARE   = 3,// 家族NPC争夺战
  UNION_CITY_DARE  = 4,// 帮会夺城战
  COUNTRY_FORMAL_DARE = 5,// 正式国战
  COUNTRY_FORMAL_ANTI_DARE = 6,// 正式国战反攻
  EMPEROR_DARE  = 7,// 皇城争夺战
};

struct stDareUserCmd : public stNullUserCmd
{
    stDareUserCmd()
    {
        byCmd = DARE_USERCMD;
    }
};

enum 
{
  DARE_QUESTION,// 发起或询问挑战
  DARE_YES,// 接受挑战
  DARE_NO         // 拒绝挑战
};

enum
{
  DARE_REPUTE_ONE = 1,
  DARE_REPUTE_TWO = 2,
  DARE_REPUTE_THREE = 3,
  DARE_REPUTE_FOUR = 4,
};

// 发起挑战
const BYTE ACTIVE_DARE_PARA = 1;
struct stActiveDareCmd : public stDareUserCmd
{
    stActiveDareCmd()
    {
      byParam = ACTIVE_DARE_PARA;
      dwWarID = 0;
      dwMsgType = DARE_QUESTION;
      byDareRepute = 0;
    }
    
    char name[MAX_NAMESIZE]; // 挑战者姓名
    char fromRelationName[MAX_NAMESIZE]; // 挑战者帮会或师门或家族名称
    char toRelationName[MAX_NAMESIZE];  //被挑战者帮会或师门或家族名称
    DWORD dwWarID;    // 交战ID
    DWORD dwDareType; // 挑战类型: 帮会、师门、家族
    DWORD dwMsgType;  // 挑战者发起挑战者无意义。服务器收到该命令后，置为DARE_QUESTION，转发给有权限的相应玩家。
                      // 客户端对玩家提问后，返回DARE_YES或DARE_NO.结构其它信息保留。
    BYTE byDareRepute; // 家族随意战时，下多少声望做为赌资类型，类型有四种:1,2,3,4 分别对应1、5、10、20声望
};


enum
{
    NOTIFY_NO_EXIST,// 帮会或师门或家族名不存在
};

// 通知消息
const BYTE NOTIFY_DARE_PARA = 2;
struct stNotifyDare : public stDareUserCmd
{
    stNotifyDare()
    {
      byParam = NOTIFY_DARE_PARA;
    }

    DWORD dwType;       // 战斗类型
    DWORD dwNotify;     // 通知类型
};

// 通知国战胜利次数的改变
const BYTE CHANGE_COUNTRY_STAR_PARA = 3;
struct stChangeCountryStar : public stDareUserCmd
{
  stChangeCountryStar()
  {
    byParam = CHANGE_COUNTRY_STAR_PARA;
  }
  
  DWORD dwStar; // 当前胜利次数
};

// 请求挑战列表
const BYTE QUERY_DARE_LIST_PARA = 4;
struct stQueryDareList : public stDareUserCmd
{
  stQueryDareList()
  {
    byParam = QUERY_DARE_LIST_PARA;
  }
  
  BYTE byType; // UNION_DARE,SEPT_DARE
};

struct stDareList
{
  char name[MAX_NAMESIZE];
};

// 通知可以挑战的社会关系列表
const BYTE SEND_DARE_LIST_PARA = 5;
struct stSendDareList : public stDareUserCmd
{
  stSendDareList()
  {
    byParam = SEND_DARE_LIST_PARA;
  }

  DWORD dwSize;
  BYTE  byType;
  struct stDareList dare_list[0];
};

// 发起帮会夺城挑战
const BYTE ACTIVE_UNION_CITY_DARE_PARA = 6;
struct stActiveUnionCityDare : public stDareUserCmd
{
  stActiveUnionCityDare()
  {
    byParam = ACTIVE_UNION_CITY_DARE_PARA;
    toCountryID = 0;
  }

  DWORD toCountryID;
};

// 领取当天税收
const BYTE GET_UNION_CITY_TAX_PARA = 7;
struct stGetUnionCityTax : public stDareUserCmd
{
  stGetUnionCityTax()
  {
    byParam = GET_UNION_CITY_TAX_PARA;
  }
};

// 通知客户端进入皇城争夺战区域
const BYTE ENTER_EMPEROR_DARE_ZONE = 8;
struct stEnterEmperorDareZone : public stDareUserCmd
{
  stEnterEmperorDareZone()
  {
    byParam = ENTER_EMPEROR_DARE_ZONE;
    dwDefCountryID = 0;
    state = 0;
  }

  DWORD dwDefCountryID; // 守方国家ID
  BYTE state; // 0,为退出,1,为进入
};

// 用户上线,通知客户端,正在进行皇城争夺战
const BYTE ENTER_EMPEROR_DARE_ACTIVE = 9;
struct stEnterEmperorDareActive : public stDareUserCmd
{
  stEnterEmperorDareActive()
  {
    byParam = ENTER_EMPEROR_DARE_ACTIVE;
  }
};

enum enmCallDutyType
{
  CALL_DUTY_KING,//国王
  CALL_DUTY_UNION,//帮主
  CALL_DUTY_SEPT,//族长
  CALL_DUTY_NUM
};
enum enmCallDutyPipeline
{
  PIPELINE_CALL = 0,//召唤
  PIPELINE_REFUSE,//拒绝
  PIPELINE_AGREE,//同意
  PIPELINE_NUM
};

//国王、帮主、族长拉人
const BYTE DARE_CALL_DUTY = 10;
struct stDareCallDuty : public stDareUserCmd
{
  stDareCallDuty()
  {
    leaderTempID=0;
    byParam = DARE_CALL_DUTY;
    byCallerType = CALL_DUTY_NUM;
    byPipeline = PIPELINE_NUM;
  }
  DWORD  leaderTempID;      //领导tempid
  BYTE  byCallerType;      //enmCallDutyType
  BYTE  byPipeline;        //enmCallDutyPipeline
  char  mapName[MAX_NAMESIZE];  //目标地图名称
  WORD  x;            //坐标x
  WORD  y;            //坐标y
};

///////////////////////////////////////////////////////////////
// 战斗指令定义结束
///////////////////////////////////////////////////////////////


//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 社会关系指令定义开始
//////////////////////////////////////////////////////////////
struct stRelationUserCmd : public stNullUserCmd
{
  stRelationUserCmd()
  {
    byCmd = RELATION_USERCMD;
  }
};

enum {
  RELATION_TYPE_LOVE,// 夫妻关系
  RELATION_TYPE_TEACHER,// 师徒关系
  RELATION_TYPE_FRIEND,// 好友关系
  RELATION_TYPE_BAD,// 黑名单
  RELATION_TYPE_OVER,// 关系已经断绝，主要是用在数据库中传达离线通知，当人物上线后会根据状态向客户端发消息。
  RELATION_TYPE_ENEMY      // 仇人关系
};
struct stRelation
{
  char  name[MAX_NAMESIZE];  //  关系人名字
  BYTE  type;          //  关系类型 
  WORD  level;        //  关系级别
  WORD  user_level;              // 关系人等级
  BYTE  online;             //  在线状态 0为不在线，1为在线
  WORD  occupation;      // 职业类型
  DWORD exploit;    // 功勋值
  DWORD country;    // 国籍
  char  unionName[MAX_NAMESIZE];  // 所属帮会
};

// 发送社会关系列表
const BYTE RELATION_SEND_RELATIONLIST_PARA = 1;
struct stSendRelationListCmd : public stRelationUserCmd
{
  WORD size;
  stRelation member[0];
  stSendRelationListCmd()
  {
    byParam = RELATION_SEND_RELATIONLIST_PARA;
  }
};

enum RELATION{
  RELATION_ADD, // 添加状态
  RELATION_QUESTION, // 发出邀请某人的询问
  RELATION_ANSWER_YES,// 确认邀请
  RELATION_ANSWER_NO,// 否定邀请
  RELATION_ONLINE,// 在线状态
  RELATION_OFFLINE,// 离线状态
  RELATION_TYPECHANGE,// 类型改变
  RELATION_REMOVE        // 删除状态
};

// 关系状态变更，以及邀请交互
const BYTE RELATION_STATUS_PARA =3;
struct stRelationStatusCmd : public stRelationUserCmd
{
  char  name[MAX_NAMESIZE];
  BYTE  type;
  WORD  occupation;
  WORD    user_level;

  union {
    WORD level;
    DWORD userid;
  };

  BYTE  byState;      //  参见 enum RELATION
  DWORD   exploit;      // 功勋值
  DWORD   country;
    
  char  unionName[MAX_NAMESIZE];  // 所属帮会
  
  stRelationStatusCmd()
  {
    byParam = RELATION_STATUS_PARA;
    user_level = 0;
    exploit = 0;
    country = 0;
    bzero(unionName,MAX_NAMESIZE);
  }
};


enum{
  MARRY_AHEAD_CHECK,
  MARRY_AHEAD_CHECK_FAIL,
  MARRY_ITEM_CHECK,
  MARRY_NO_ITEM,
  MARRY_ANSWER,
  MARRY_REFUSE,
  MARRY_AGREE,
  MARRY_PAY_MONEY,
  MARRY_PAY_MONEY1,
  MARRY_PAY_MONEY2,
  MARRY_NO_MONEY
};

/// 结婚前的用户状态检查消息
const BYTE MARRY_STATUS_CHECK_PARA = 4;
struct stMarryStatusCheckCmd  : public stRelationUserCmd
{
  stMarryStatusCheckCmd()
  {
    byParam = MARRY_STATUS_CHECK_PARA;

  }
  BYTE byStep;
};

/// 离婚消息
#define UNMARRY_PARA 5
struct stUnmarryCmd  : public stRelationUserCmd
{
  stUnmarryCmd()
  {
    byParam = UNMARRY_PARA;

  }
};

//////////////////////////////////////////////////////////////
// 社会关系指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 师徒门派关系指令定义开始
//////////////////////////////////////////////////////////////
struct stSchoolUserCmd : public stNullUserCmd
{
  stSchoolUserCmd()
  {
    byCmd = SCHOOL_USERCMD;
  }
};

enum SCHOOL_ADD_MEMBER{
      TEACHER_QUESTION, // 发出邀请某人加入师门的询问
      TEACHER_ANSWER_YES,// 确认邀请加入师门
      TEACHER_ANSWER_NO         // 否定邀请加入师门
};

// 邀请他人加入门派，兼任新人加入通知消息
const BYTE ADD_MEMBER_TO_SCHOOL_PARA = 1;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToSchoolCmd : public stSchoolUserCmd
{
  stAddMemberToSchoolCmd()
  {
    byParam = ADD_MEMBER_TO_SCHOOL_PARA;
    level = 0;
  }
  char   memberName[MAX_NAMESIZE];      // 被邀请的人
  union {
      DWORD  memberID;          // 被邀请人ID
      DWORD  degree;            // 向客户端发送的时候告诉客户端新成员处于那一个层级之中
  };
  union {
      char   schoolName[MAX_NAMESIZE];  // 门派名称，如果没有门派为空
      char    prename[MAX_NAMESIZE];    // 他的师兄
  };
  BYTE   byState;              // 参见 enum SCHOOL_ADD_MEMBER
  WORD  wdOccupation;            // 新成员职业
  WORD    level;          // 加入成员的等级
};

// 将指定的人开除出师门或者门派
const BYTE FIRE_MEMBER_FROM_SCHOOL_PARA = 2;
struct stFireMemberFromSchoolCmd : public stSchoolUserCmd
{
  stFireMemberFromSchoolCmd()
  {
    byParam = FIRE_MEMBER_FROM_SCHOOL_PARA ;
  }
  char memberName[MAX_NAMESIZE];
};

/// 门派创建前的用户状态检查消息
const BYTE SCHOOL_STATUS_CHECK_PARA = 3;
struct stSchoolStatusCheckCmd  : public stSchoolUserCmd
{
  stSchoolStatusCheckCmd()
  {
    byParam = SCHOOL_STATUS_CHECK_PARA;
  }
};

// 门派创建命令
const BYTE CREATE_SCHOOL_PARA = 4;
struct stCreateSchoolCmd: public stSchoolUserCmd
{
  stCreateSchoolCmd()
  {
    byParam = CREATE_SCHOOL_PARA;
  }
  char SchoolName[MAX_NAMESIZE];
};

// 门派或师门成员申请脱离关系
const BYTE SCHOOLMEMBER_LEAVE_SCHOOL_PARA = 5;
struct stSchoolMemberLeaveSchoolCmd : public stSchoolUserCmd
{
  stSchoolMemberLeaveSchoolCmd()
  {
    byParam = SCHOOLMEMBER_LEAVE_SCHOOL_PARA;
  }
};

enum SCHOOL_PACKAGE_TAG{
  SCHOOL_PACKAGE_BODY=0,// 消息包体
  SCHOOL_PACKAGE_HEAD=1,// 消息包头
  SCHOOL_PACKAGE_TAIL=2  // 消息包尾
};

enum SCHOOL_LAYER {
  SCHOOL_NEWLAYER,// 换一新层
  SCHOOL_NEWLINE,// 换一新行
  SCHOOL_NONE        // 无动作
};

struct stSchoolMember{
  char name[MAX_NAMESIZE];
  BYTE tag;    // enum SCHOOL_LAYER
  WORD level;             // 成员等级
  BYTE online;  // 0 为再不在线
  WORD occupation;// 职业类型
};

struct stTeacherMember{
  stTeacherMember()
  {
    level = 0;
  }
  char name[MAX_NAMESIZE];
  WORD degree;   // 友好度
  BYTE tag;  // enum SCHOOL_MEMBER_TAG
  WORD level;     // 成员等级
  BYTE online;  // 0 为再不在线
  WORD occupation;// 职业类型
  DWORD country;          // 国籍
  char  unionName[MAX_NAMESIZE];  // 所属帮会
  char  septName[MAX_NAMESIZE];  // 所属家族
};

// 门派信息列表
const BYTE SENDLIST_SCHOOL_PARA = 6;
struct stSendListSchoolCmd : public stSchoolUserCmd
{
  stSendListSchoolCmd()
  {
    byParam = SENDLIST_SCHOOL_PARA;
  }
  DWORD dwMasterTempID;
  BYTE byPackageTag; //enum SCHOOL_PACKAGE_TAG
  WORD size;
  stSchoolMember list[0];
};

enum SCHOOL_MEMBER_TAG{
  TEACHER, // 师傅
  BIGBROTHER, // 师兄
  LITTLEBROTHER,// 师弟
  PRENTICE        // 徒弟
  
};

// 师门信息列表
const BYTE SENDMEMBERINFO_SCHOOL_PARA = 7;
struct stSendMemberInfoCmd : public stSchoolUserCmd
{
  stSendMemberInfoCmd()
  {
    byParam = SENDMEMBERINFO_SCHOOL_PARA;
  }
  WORD size; //大小
  stTeacherMember list[0]; // list里成员的tag使用 enum SCHOOL_MEMBER_TAG
};

enum {
  SCHOOL_STATUS_NONE,
  SCHOOL_STATUS_TEACHER,
  SCHOOL_STATUS_SCHOOL
};

// 初始化通知
const BYTE MEMBER_STATUS_SCHOOL_PARA = 8;
struct stMemberStatusSchool : public stSchoolUserCmd
{
  stMemberStatusSchool()
  {
    byParam = MEMBER_STATUS_SCHOOL_PARA;
  }
  char schoolName[MAX_NAMESIZE]; // 门派名字
  BYTE byStatus; //  SCHOOL_STATUS_NONE,SCHOOL_STATUS_TEACHER,SCHOOL_STATUS_SCHOOL
};

enum {
  SCHOOL_MEMBER_OFFLINE=0,// 离线状态
  SCHOOL_MEMBER_ONLINE=1      // 在线状态
};

const BYTE SCHOOL_MEMBER_STATUS_PARA =9;
struct stSchoolMemberStatusCmd : public stSchoolUserCmd
{
  char  name[MAX_NAMESIZE];
  BYTE  byState;            //  参见 SCHOOL_MEMBER_ONLINE SCHOOL_MEMBER_OFFLINE
  WORD    level;              //  成员等级
  DWORD  country;            //  国籍
  char  unionName[MAX_NAMESIZE];    //  所属帮会
  char  septName[MAX_NAMESIZE];      //  所属家族
  stSchoolMemberStatusCmd()
  {
    byParam = SCHOOL_MEMBER_STATUS_PARA;
  }
};

#define BULLETIN_MAX_SIZE 1000

enum {
  SCHOOL_BULLETIN_SET,// 设置公告
  SCHOOL_BULLETIN_GET,// 请求公告内容
  SCHOOL_BULLETIN_EDIT    // 编辑请求
};

const BYTE SCHOOL_BULLETIN__PARA =10;
struct stSchoolBulletinCmd : public stSchoolUserCmd
{
  BYTE byState; // SCHOOL_BULLETIN_SET SCHOOL_BULLETIN_GET
  WORD wdSize;  // 无内容设0
  char data[0];
  stSchoolBulletinCmd()
  {
    byParam = SCHOOL_BULLETIN__PARA;
  }
};

// 门派解散指令
const BYTE DESTROY_SCHOOL_PARA = 11;
struct stDestroySchoolCmd: public stSchoolUserCmd
{
  stDestroySchoolCmd()
  {
    byParam = DESTROY_SCHOOL_PARA;
  }
};

const BYTE SCHOOL_BULLETIN_NOTIFY_PARA = 12;
struct stSchoolBulletinNotifyCmd : public stSchoolUserCmd
{
  stSchoolBulletinNotifyCmd()
  {
    byParam = SCHOOL_BULLETIN_NOTIFY_PARA;
  }
};

enum
{
  QUERY_SCHOOL_BOUNTY,// 查询
  GET_SCHOOL_BOUNTY,// 提取
  PUT_SCHOOL_BOUNTY,// 进贡
};

// 做为师傅查询或领取进贡
#define REQ_MASTER_BOUNTY_PARA 13
struct stReqMasterBountyUserCmd : public stSchoolUserCmd
{
  stReqMasterBountyUserCmd()
  {
    byParam = REQ_MASTER_BOUNTY_PARA;
  }

  BYTE byState;
};

// 做为徒弟查询和进行进贡
#define REQ_PRENTICE_BOUNTY_PARA 14
struct stReqPrenticeBountyUserCmd : public stSchoolUserCmd
{
  stReqPrenticeBountyUserCmd()
  {
    byParam = REQ_PRENTICE_BOUNTY_PARA;
  }

  BYTE byState;
};

// 返回师傅查询
#define RTN_MASTER_BOUNTY_PARA 15
struct stRtnMasterBountyUserCmd : public stSchoolUserCmd
{
  stRtnMasterBountyUserCmd()
  {
    byParam = RTN_MASTER_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
  }

  DWORD dwBalance; // 可领取的金额
  DWORD dwTotal;  // 累计已领取的金额
};

// 返回徒弟查询
#define RTN_PRENTICE_BOUNTY_PARA 16
struct stRtnPrenticeBountyUserCmd : public stSchoolUserCmd
{
  stRtnPrenticeBountyUserCmd()
  {
    byParam = RTN_PRENTICE_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwLastLevel = 0;
    bzero(name,sizeof(name));
  }
  
  DWORD dwBalance; // 可进贡的金额
  DWORD dwTotal;   // 累计已领取的金额
  DWORD dwLastLevel; // 上次领取时的等级
  char name[MAX_NAMESIZE]; // 师傅的姓名
};

//////////////////////////////////////////////////////////////
// 师徒门派关系指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
/************************************************************
************************任务指令定义开始*********************
*************************************************************/
struct stQuestUserCmd : public stNullUserCmd
{
  stQuestUserCmd()
  {
    byCmd = TASK_USERCMD;  
  }
  DWORD id; //任务id
};

static const BYTE QUEST_INFO_PARA = 1;
struct stQuestInfoUserCmd : public stQuestUserCmd
{
  stQuestInfoUserCmd()
  {
    byParam = QUEST_INFO_PARA;
  }

  BYTE name[64];
  DWORD start;
  BYTE info[0];
};

static const BYTE QUEST_VARS_PARA = 2;
struct stQuestVarsUserCmd : public stQuestUserCmd
{
  enum {
    MAX_NSIZE = 32,
    MAX_VSIZE = 128,
  };

  stQuestVarsUserCmd()
  {
    byParam = QUEST_VARS_PARA;  
  }
  BYTE count; //变量数量
  struct Var {
    BYTE name[MAX_NSIZE];
    BYTE value[MAX_VSIZE];  
  } vars_list[0]; //变量列表
};

static const BYTE REQUEST_QUEST_PARA = 3;
struct stRequestQuestUserCmd : public stQuestUserCmd
{
  stRequestQuestUserCmd()
  {
    byParam = REQUEST_QUEST_PARA;
  }
  char target[16];
  BYTE offset; //任务分支
};

static const BYTE ABANDON_QUEST_PARA = 4;
struct stAbandonQuestUserCmd : public stQuestUserCmd
{
  stAbandonQuestUserCmd()
  {
    byParam = ABANDON_QUEST_PARA;
  }
};

static const BYTE CART_CONTROL_QUEST_PARA = 5;//控制镖车走和停
struct stCartControlQuestUserCmd : public stQuestUserCmd
{
  stCartControlQuestUserCmd()
  {
    byParam = CART_CONTROL_QUEST_PARA;
  }
};

static const BYTE CHECK_VALID_QUEST_PARA = 6;//检查可以接的任务列表
struct stCheckValidQuestUserCmd : public stQuestUserCmd
{
  stCheckValidQuestUserCmd()
  {
    byParam = CHECK_VALID_QUEST_PARA;
  }
};

static const BYTE REQ_VALID_QUEST_PARA = 7;//检查可以接的任务列表
struct stReqValidQuestUserCmd : public stQuestUserCmd
{
  stReqValidQuestUserCmd()
  {
    byParam = REQ_VALID_QUEST_PARA;
  }
};

static const BYTE RET_VALID_QUEST_PARA = 8;//返回可以接的任务列表
struct stRetValidQuestUserCmd : public stQuestUserCmd
{
  stRetValidQuestUserCmd()
  {
    byParam = RET_VALID_QUEST_PARA;
    size = 0;
  }
  DWORD size;
  char content[0];
};

/************************************************************
************************任务指令定义结束*********************
*************************************************************/

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 家族指令定义开始
//////////////////////////////////////////////////////////////
struct stSeptUserCmd : public stNullUserCmd
{
  stSeptUserCmd()
  {
    byCmd = SEPT_USERCMD;
  }
};

/// 家族创建前的用户状态检查消息
const BYTE SEPT_STATUS_CHECK_PARA = 1;
struct stSeptStatusCheckCmd  : public stSeptUserCmd
{
  stSeptStatusCheckCmd()
  {
    byParam = SEPT_STATUS_CHECK_PARA;

  }
};

// 家族创建命令
const BYTE CREATE_SEPT_PARA = 2;
struct stCreateSeptCmd: public stSeptUserCmd
{
  stCreateSeptCmd()
  {
    byParam = CREATE_SEPT_PARA;
  }
  char SeptName[MAX_NAMESIZE];  // 家族名称
};

// 家族创建成功通知指令
const BYTE SERVER_RETURN_SEPT_CREATE_FAILED = 3;
struct stServerReturnSeptCheckCmd : public stSeptUserCmd
{
  stServerReturnSeptCheckCmd()
  {
    byParam = SERVER_RETURN_SEPT_CREATE_FAILED;
  }
};

struct stSeptRember{
  char  memberName[MAX_NAMESIZE];        // 家族成员名称
  WORD  level;            // 成员等级
  BYTE  byOnline;            // 成员在线标志 0 为不在线 非0为在线
  WORD  occupation;          // 职业类型
  DWORD exploit;            // 功勋值
  DWORD useJob;				// sky 职业
  char memberAliasName[MAX_NAMESIZE];      // 族员别名
  WORD nRight;
};

// 服务器返回家族成员列表，及请求者的个人家族信息
const BYTE ALL_SEPT_MEMBER_PARA = 5;
struct stAllSeptMemberCmd : public stSeptUserCmd
{
  stAllSeptMemberCmd()
  {
    byParam = ALL_SEPT_MEMBER_PARA;
  }
  WORD size;                     // 数量
  stSeptRember memberList[0];   // 成员列表
};


enum SEPT_ADD_MEMBER{
      SEPT_QUESTION,  // 发出邀请某人的询问
      SEPT_ANSWER_YES,// 确认邀请
      SEPT_ANSWER_NO          // 否定邀请
};

// 邀请他人加入家族
const BYTE ADD_MEMBER_TO_SEPT_PARA = 7;  // 这个消息由客户端发到服务端是邀请某人，由服务端发到客户端是询问某人是否接受邀请
struct stAddMemberToSeptCmd : public stSeptUserCmd
{
  stAddMemberToSeptCmd()
  {
    byParam = ADD_MEMBER_TO_SEPT_PARA;
  }
  char   memberName[MAX_NAMESIZE];   // 被邀请的人
  DWORD memberID;                   // 被邀请人ID
  char   septName[MAX_NAMESIZE];    // 家族名称
  BYTE   byState;                    // 参见 enum SEPT_ADD_MEMBER
};

// 开除家族成员
const BYTE FIRE_MEMBER_FROM_SEPT_PARA = 8;
struct stFireMemberFromSeptCmd : public stSeptUserCmd
{
  stFireMemberFromSeptCmd()
  {
    byParam = FIRE_MEMBER_FROM_SEPT_PARA ;
  }
  char memberName[MAX_NAMESIZE];
};

enum{
     SEPT_MEMBER_STATUS_ONLINE,  // 家族成员上线
     SEPT_MEMBER_STATUS_OFFLINE, // 家族成员下线
     SEPT_MEMBER_STATUS_FIRE,    // 家族成员被开除
     SEPT_MEMBER_STATUS_NEWMEMBER,// 新增加家族成员
     SEPT_MEMBER_STATUS_ALIASCHANGE,// 更改别名
};

// 服务端更新家族成员状态及信息通知消息 状态见上表
const BYTE BROADCAST_SEPT_MEMBER_INFO_PARA = 10;
struct stBroadcastSeptMemberInfo : public stSeptUserCmd
{
  stBroadcastSeptMemberInfo()
  {
    byParam = BROADCAST_SEPT_MEMBER_INFO_PARA;
    level = 0;
    bzero(name,sizeof(name));
    bzero(aliasName,sizeof(name));
    exploit = 0;
    useJob = 0;
  }
  BYTE byStatus;                       // 成员状态
  WORD wdOccupation;          // 成员职业
  WORD level;           // 成员等级
  char name[MAX_NAMESIZE];             // 成员名称
  char aliasName[MAX_NAMESIZE];       // 成员别名
  DWORD exploit;           // 功勋值
  DWORD useJob;           // sky 职业
  //[Shx Add 职位ID]
  WORD  nRight;
};

// 服务器端发送家族信息
const BYTE SEPT_BASE_INFO_PARA = 11;
struct stSeptBaseInfoCmd : public stSeptUserCmd
{
  stSeptBaseInfoCmd()
  {
    byParam = SEPT_BASE_INFO_PARA;
    dwLevel = 0;
  }
  DWORD dwMasterTempID;
  char  septName[MAX_NAMESIZE];         // 家族名称
  char  master[MAX_NAMESIZE];            // 家族族长
  char  note[255];
  DWORD dwRepute;      // 家族声望
  DWORD dwLevel;      // 家族等级
  struct stStepRight
  {
	  char	RightName[MAX_NAMESIZE];
	  DWORD	dwRight;
  } RightList[10];
};

// 家族成员申请退族
const BYTE SEPTMEMBER_LEAVE_SEPT_PARA = 12;
struct stSeptMemberLeaveSeptCmd : public stSeptUserCmd
{
  stSeptMemberLeaveSeptCmd()
  {
    byParam = SEPTMEMBER_LEAVE_SEPT_PARA;
  }
};

struct stSeptVoteRecord{
  char septName [MAX_NAMESIZE];
  char master[MAX_NAMESIZE];
  WORD wdVoteNumber;
  char note[255];
};

// 家族投票列表
const BYTE VOTELIST_SEPT_PARA = 13;
struct stVoteListSeptCmd : public stSeptUserCmd
{
  stVoteListSeptCmd()
  {
    byParam = VOTELIST_SEPT_PARA;
  }
  char septName[MAX_NAMESIZE];
  DWORD dwSize;
  BYTE flag; // 0为消息头 1为后续消息
  stSeptVoteRecord data[0];
};

// 家族投票消息
const BYTE VOTE_SEPT_PARA = 14;
struct stVoteSeptCmd : public stSeptUserCmd
{
  stVoteSeptCmd()
  {
    byParam = VOTE_SEPT_PARA;
  }
  char septName[MAX_NAMESIZE];
  BYTE bySuccess;   // 为1为成功 为0为失败
};

// 家族设置帮会说明
const BYTE NOTE_SEPT_PARA = 15;
struct stNoteSeptCmd : public stSeptUserCmd
{
  stNoteSeptCmd()
  {
    byParam = NOTE_SEPT_PARA;
  }
  char noteBuf[255];
};

// 家族成员别名设置
const BYTE CHANGE_SEPT_MEMBER_ALIASNAME_PARA = 16;
struct stChangeSeptMemberAliasName : public stSeptUserCmd
{
  stChangeSeptMemberAliasName()
  {
    byParam = CHANGE_SEPT_MEMBER_ALIASNAME_PARA;
  }

  char name[MAX_NAMESIZE];             // 族员姓名
  char aliasname[MAX_NAMESIZE];        // 族员别名
};

// 家族成员捐献荣誉点
const BYTE DONATE_HONOR_PARA = 17;
struct stDonateHonor : public stSeptUserCmd
{
  stDonateHonor()
  {
    byParam = DONATE_HONOR_PARA;
    dwHonor = 0;
  }
  
  DWORD dwHonor;
};

enum
{
  COUNTRY_SEPT_SORT,// 本国家族排行榜
  WORLD_SEPT_SORT,// 世界家族排行榜
};

// 查询家族排行榜（根据声望）
const BYTE REQ_SEPT_SORT_PARA = 18;
struct stReqSeptSort : public stSeptUserCmd
{
  stReqSeptSort()
  {
    byParam = REQ_SEPT_SORT_PARA;
    byType = COUNTRY_SEPT_SORT;
  }
  
  BYTE byType;
};

struct stSeptSortInfo
{
  char  septName[MAX_NAMESIZE];           // 家族名称
  DWORD dwRepute;        // 家族声望
  DWORD dwOrder;        // 家族排名
  DWORD dwCountryID;      // 国家ID
};

// 返回家族排行榜（根据声望）
const BYTE RTN_SEPT_SORT_PARA = 19;
struct stRtnSeptSort : public stSeptUserCmd
{
  stRtnSeptSort()
  {
    byParam = RTN_SEPT_SORT_PARA;
    dwSize = 0;
  }
  
  BYTE byType;
  DWORD dwSize;
  stSeptSortInfo data[0];
};

struct stSeptRecord{
  char septName [MAX_NAMESIZE];
  char master[MAX_NAMESIZE];
  char note[255];
};

// 家族投票列表
const BYTE LIST_SEPT_PARA = 20;
struct stListSeptCmd : public stSeptUserCmd
{
  stListSeptCmd()
  {
    byParam = LIST_SEPT_PARA;
  }
  DWORD dwSize;
  BYTE flag; // 0为消息头 1为后续消息
  stSeptRecord data[0];
};

enum {
  REQUEST_JOIN_OK,
  REQUEST_JOIN_CANCEL,
  REQUEST_JOIN_TIMEOUT
};

// 请求加入家族消息
const BYTE REQUEST_JOIN_SEPT_PARA = 21;
struct stRequestJoinSeptCmd : public stSeptUserCmd
{
  stRequestJoinSeptCmd()
  {
    byParam = REQUEST_JOIN_SEPT_PARA;
  }
  char name[MAX_NAMESIZE]; //发给服务器的时候填对方族长的名字，服务器发出来的时候填的是请求人的名字
  BYTE status;
};

// 请求家族占领NPC信息
const BYTE REQUEST_NPCINFO_SEPT_PARA = 22;
struct stRequestNpcInfoSeptCmd : public stSeptUserCmd
{
  stRequestNpcInfoSeptCmd()
  {
    byParam = REQUEST_NPCINFO_SEPT_PARA;
  }
};

// 请求领取家族经验
const BYTE REQUEST_SEPT_EXP_PARA = 23;
struct stRequestSeptExpCmd : public stSeptUserCmd
{
  stRequestSeptExpCmd()
  {
    byParam = REQUEST_SEPT_EXP_PARA;
  }
};

// 请求放弃占领该NPC
const BYTE REQUEST_ABJURATION_SEPTNPC_PARA = 24;
struct stRequestAbjurationSeptNpcSeptCmd : public stSeptUserCmd
{
  stRequestAbjurationSeptNpcSeptCmd()
  {
    byParam = REQUEST_ABJURATION_SEPTNPC_PARA;
  }
};

// 请求家族名称
const BYTE REQ_SEPT_NAME_PARA = 25;
struct stReqSeptNameCmd : public stSeptUserCmd
{
  stReqSeptNameCmd()
  {
    byParam = REQ_SEPT_NAME_PARA;
    dwSeptID = 0;
  }

  DWORD dwSeptID;
};

// 请求家族名称
const BYTE RTN_SEPT_NAME_PARA = 26;
struct stRtnSeptNameCmd : public stSeptUserCmd
{
  stRtnSeptNameCmd()
  {
    byParam = RTN_SEPT_NAME_PARA;
    dwSeptID = 0;
    bzero(name,MAX_NAMESIZE);
  }

  DWORD dwSeptID;
  char name[MAX_NAMESIZE];
};
// 请求家族名称列表
const BYTE REQ_SEPT_NAME_LIST_PARA = 27;
struct stReqSeptNameListCmd : public stSeptUserCmd
{
  stReqSeptNameListCmd()
  {
    byParam = REQ_SEPT_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  DWORD dwSeptID[0];
};

// 请求家族名称列表
const BYTE RTN_SEPT_NAME_LIST_PARA = 28;
struct stRtnSeptNameListCmd : public stSeptUserCmd
{
  stRtnSeptNameListCmd()
  {
    byParam = RTN_SEPT_NAME_LIST_PARA;
    num=0;
  }
  BYTE num;
  struct
  {
    DWORD dwSeptID;
    char name[MAX_NAMESIZE];
  } list[0];
};

// 请求领取家族经验
const BYTE REQUEST_SEPT_NORMAL_EXP_PARA = 29;
struct stRequestSeptNormalExpCmd : public stSeptUserCmd
{
  stRequestSeptNormalExpCmd()
  {
    byParam = REQUEST_SEPT_NORMAL_EXP_PARA;
  }
};

//////////////////////////////////////////////////////////////
// 家族指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 宠物指令定义开始
//////////////////////////////////////////////////////////////
struct stPetUserCmd : public stNullUserCmd
{
  stPetUserCmd()
  {
    byCmd = PET_USERCMD;
  }
};

//宠物AI模式
enum petAIMode
{
  PETAI_MOVE_FOLLOW  = 0x0001,//跟随
  PETAI_MOVE_STAND  = 0x0002,//站立不动
  PETAI_ATK_ACTIVE  = 0x0100,//攻击所有敌人
  PETAI_ATK_PASSIVE  = 0x0200,//攻击正在攻击主人的敌人
  PETAI_ATK_NOATK    = 0x0400  //不战斗
};
// 设置宠物的AI模式
const BYTE SETAI_PET_PARA = 1;
struct stSetAIPetCmd : public stPetUserCmd
{
  stSetAIPetCmd()
  {
    byParam = SETAI_PET_PARA;
  }
  petType type;
  petAIMode mode;
};

//宠物状态
enum petState
{
  PET_STATE_NOPET    = 0,//没有宠物
  PET_STATE_NORMAL  = 1,//普通
  PET_STATE_PUTUP    = 2,//收起
  PET_STATE_DEAD    = 3,//死亡
  PET_STATE_CONSIGN  = 4    //寄存
};

//宠物的数据
//struct t_PetData
//{
//  DWORD id;    //npcid
//  char name[MAX_NAMESIZE];//名字
//  BYTE lv;    //等级
//  DWORD hp;    //生命
//  DWORD maxhp;    //最大生命
//  WORD str;    //力量
//  WORD intel;    //智力
//  WORD agi;    //敏捷
//  WORD men;    //精神
//  WORD vit;    //体质
//  DWORD exp;    //经验
//  DWORD maxexp;    //最大经验
//  DWORD atk;    //攻击力
//  DWORD maxatk;    //最大攻击力
//  DWORD matk;    //魔攻
//  DWORD maxmatk;    //最大魔攻
//  DWORD def;    //物防
//  DWORD mdef;    //魔防
//  WORD cri;    //爆击
//  DWORD skills[4];  //技能
//  WORD ai;    //AI
//  DWORD maxhp_plus;  //附加最大生命
//  WORD atk_plus;    //附加物理攻击力
//  WORD maxatk_plus;  //附加最大物理攻击力
//  WORD matk_plus;    //附加魔法攻击力
//  WORD maxmatk_plus;  //附加最大魔法攻击力
//  WORD pdef_plus;    //附加物防
//  WORD mdef_plus;    //附加魔防
//  petType type;    //类型
//  petState state;    //状态
//};

struct t_PetData
{
	DWORD id;               //npcid
	char name[MAX_NAMESIZE];//名字
	BYTE lv;                //等级
	DWORD hp;               //生命
	DWORD maxhp;            //最大生命
	DWORD str;               //力量
	DWORD intel;             //智力
	DWORD agi;               //敏捷
	DWORD men;               //精神
	DWORD vit;               //体质
	DWORD exp;              //经验
	DWORD maxexp;           //最大经验
	DWORD atk;              //攻击力
	DWORD maxatk;           //最大攻击力
	DWORD matk;             //魔攻
	DWORD maxmatk;          //最大魔攻
	DWORD def;              //物防
	DWORD mdef;             //魔防
	WORD cri;               //爆击
	DWORD skills[4];        //技能
	WORD ai;                //AI
	DWORD maxhp_plus;       //附加最大生命
	WORD atk_plus;          //附加物理攻击力
	WORD maxatk_plus;       //附加最大物理攻击力
	WORD matk_plus;         //附加魔法攻击力
	WORD maxmatk_plus;      //附加最大魔法攻击力
	WORD pdef_plus;         //附加物防
	WORD mdef_plus;         //附加魔防
	petType type;           //类型
	petState state;         //状态
};

// 请求宠物的数据
const BYTE REQUESTDATA_PET_PARA = 2;
struct stRequestDataPetCmd : public stPetUserCmd
{
  stRequestDataPetCmd()
  {
    byParam = REQUESTDATA_PET_PARA;
  }
  petType type;
};

//返回宠物的数据
const BYTE REFRESHDATA_PET_PARA = 3;
struct stRefreshDataPetCmd : public stPetUserCmd
{
  stRefreshDataPetCmd()
  {
    byParam = REFRESHDATA_PET_PARA;
    bzero(&data,sizeof(data));
  }
  petType type;
  DWORD id;

  t_PetData data;
};

//改宠物名字
const BYTE CHANGENAME_PET_PARA = 4;
struct stChangeNamePetCmd : public stPetUserCmd
{
  stChangeNamePetCmd()
  {
    byParam = CHANGENAME_PET_PARA;
  }
  petType type;
  char name[MAX_NAMESIZE];
};

//增加宠物
const BYTE ADDPET_PET_PARA = 5;
struct stAddPetPetCmd : public stPetUserCmd
{
  stAddPetPetCmd()
  {
    byParam = ADDPET_PET_PARA;
  }
  petType type;
  DWORD id;
};

//删除宠物
const BYTE DELPET_PET_PARA = 6;
struct stDelPetPetCmd : public stPetUserCmd
{
  stDelPetPetCmd()
  {
    byParam = DELPET_PET_PARA;
  }
  petType type;
  DWORD id;
};

//删除技能
const BYTE DELSKILL_PET_PARA = 7;
struct stDelSkillPetCmd : public stPetUserCmd
{
  stDelSkillPetCmd()
  {
    byParam = DELSKILL_PET_PARA;
  }
  petType type;///宠物类型
  DWORD id;///技能id
};

//召唤马出来跟随
const BYTE CALLHORSE_PET_PARA = 8;
struct stCallHorsePetCmd : public stPetUserCmd
{
  stCallHorsePetCmd()
  {
    byParam = CALLHORSE_PET_PARA;
  }
};

//收起马匹
const BYTE PUTHORSE_PET_PARA = 9;
struct stPutHorsePetCmd : public stPetUserCmd
{
  stPutHorsePetCmd()
  {
    byParam = PUTHORSE_PET_PARA;
  }
};

//刷新马的数据
const BYTE HORSEDATA_PET_PARA = 10;
struct stHorseDataPetCmd : public stPetUserCmd
{
  stHorseDataPetCmd()
  {
    byParam = HORSEDATA_PET_PARA;
    type = PET_TYPE_RIDE;
  }
  petType type;
  DWORD id;
  t_HorseData data;
};

//强制宠物攻击目标
const BYTE SETTARGET_PET_PARA = 11;
struct stSetTargetPetCmd : public stPetUserCmd
{
  stSetTargetPetCmd()
  {
    byParam = SETTARGET_PET_PARA;
  }
  petType type;///宠物类型
  DWORD targetType;///目标类型 0:玩家 1:NPC
  DWORD id;///目标的临时ID
};

//同步宠物的血和经验
const BYTE HP_EXP_PET_PARA = 12;
struct stHpExpPetCmd : public stPetUserCmd
{
  stHpExpPetCmd()
  {
    byParam = HP_EXP_PET_PARA;
  }
  petType type;
  DWORD id;//tempid
  DWORD hp;
  DWORD exp;
};

/*
//换马
const BYTE CHANGEHORSE_PET_PARA = 11;
struct stChangeHorsePetCmd : public stPetUserCmd
{
  stChangeHorsePetCmd()
  {
    byParam = CHANGEHORSE_PET_PARA;
  }
  DWORD id;
};
*/

//////////////////////////////////////////////////////////////
// 宠物指令定义结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义与客户端PING工具的命令
//////////////////////////////////////////////////////////////
struct stPingUserCmd : public stNullUserCmd
{
  stPingUserCmd()
  {
    byCmd = PING_USERCMD;
  }
};

struct ping_element
{
  BYTE gateway_ip[15+1];
  /**
    * EMPTY = 0,人数0-399,
    * VERYIDLE = 1,人数400-799,
    * IDLE = 2,人数800-1199,
    * BUSY = 3,人数1200-1599
    * VERYBUSY= 4     人数1600-1999
    */
  BYTE state;
  ping_element()
  {
    bzero(gateway_ip,sizeof(gateway_ip));
  }
};

const BYTE PING_LIST_PARA = 1;
struct stPingList : public stPingUserCmd
{
  DWORD zone_id;
  struct ping_element ping_list;

  stPingList()
  {
    byParam = PING_LIST_PARA;
  };
};

const BYTE REQUEST_PING_LIST_PARA = 2;
struct stRequestPingList : public stPingUserCmd
{
  DWORD id;  //游戏区号

  stRequestPingList() 
  {
    byParam = REQUEST_PING_LIST_PARA;
  }
};

const BYTE LOGIN_PING_PARA = 3;
struct stLoginPing : public stPingUserCmd
{
  stLoginPing() 
  {
    byParam = LOGIN_PING_PARA;
  }
};


//////////////////////////////////////////////////////////////
/// 定义与客户端PING工具的命令
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义金币命令开始
//////////////////////////////////////////////////////////////

enum enumBuyType{
  eBuySilver = 1,
  eBuyGold = 2,
  eBuyTicket = 4,
};

struct stGoldUserCmd : public stNullUserCmd
{
  stGoldUserCmd()
  {
    byCmd = GOLD_USERCMD;
  }
};

const BYTE QUERY_GOLD_PARA = 1;
struct stQueryGold : public stGoldUserCmd
{
  stQueryGold() 
  {
    byParam = QUERY_GOLD_PARA;
  }
};

enum
{
  REDEEM_SUCCESS,// 兑换成功 
  REDEEM_BUSY,// 服务器忙
  REDEEM_STOP,// 兑换系统停止服务
  REDEEM_FAIL,// 失败
};
#define REDEEM_RATE_GOLD 1 //兑换金币比率1:1
#define  REDEEM_RATE_MONTH_CARD 18//兑换月卡比率1:18
//请求兑换金币
const BYTE REQUEST_REDEEM_GOLD_PARA = 2;
struct stRequestRedeemGold : public stGoldUserCmd
{
  stRequestRedeemGold()
  {
    byParam = REQUEST_REDEEM_GOLD_PARA;
  }
  DWORD dwNum;  //需要兑换的点数
};
//兑换金币返回
const BYTE REDEEM_GOLD_PARA = 3;
struct stRedeemGold : public stGoldUserCmd
{
  stRedeemGold()
  {
    byParam = REDEEM_GOLD_PARA;
  }
  DWORD dwNum;  //返回当前金币数
  DWORD dwBalance;      /// 点卡余额
  BYTE byReturn;  //返回类型
};
 
//请求兑换月卡
const BYTE REQUEST_REDEEM_MONTH_CARD_PARA = 4;
struct stRequestRedeemMonthCard : public stGoldUserCmd
{
  stRequestRedeemMonthCard()
  {
    byParam = REQUEST_REDEEM_MONTH_CARD_PARA;
  }
};

//兑换月卡返回
const BYTE REDEEM_MONTH_CARD_PARA = 5;
struct stRedeemMonthCard : public stGoldUserCmd
{
  stRedeemMonthCard()
  {
    byParam = REDEEM_MONTH_CARD_PARA;
  }
  DWORD dwNum;  //到期时间(time_t,4字节结构)
  DWORD dwBalance;      /// 点卡余额
  BYTE byReturn;  //返回类型
};

//查询月卡和金币
const BYTE REQUEST_CARD_AND_GOLD_PARA = 6;
struct stRequestCardAndGold :  public stGoldUserCmd
{
  stRequestCardAndGold()
  {
    byParam = REQUEST_CARD_AND_GOLD_PARA;
  }
};

//查询返回
const BYTE RETURN_CARD_AND_GOLD_PARA = 7;
struct stReturnCardAndGold :  public stGoldUserCmd
{
  stReturnCardAndGold()
  {
    byParam = RETURN_CARD_AND_GOLD_PARA;
  }
  DWORD dwMonthCard;//月卡
  DWORD dwGold;//金币
  BYTE byReturn;//返回类型
};
//查询点卡
const BYTE REQUEST_POINT_PARA = 8;
struct stRequestPoint :  public stGoldUserCmd
{
  stRequestPoint()
  {
    byParam = REQUEST_POINT_PARA;
  }
};
//查询点卡返回
const BYTE RETURN_REQUEST_POINT_PARA = 9;
struct stReturnRequestPoint :  public stGoldUserCmd
{
  stReturnRequestPoint()
  {
    byParam = RETURN_REQUEST_POINT_PARA;
  }
  DWORD dwPoint;//剩余点数
  BYTE byReturn;//查询返回类型
};
//金币系停止服务
const BYTE STOP_SERVICE_GOLD_PARA = 10;
struct stStopServiceGold :  public stGoldUserCmd
{
  stStopServiceGold()
  {
    byParam = STOP_SERVICE_GOLD_PARA;
  }
};
#define CARDID_LENGTH_PARA 32
///消费卡的区类型
enum
{
  ZONE_CARD_OBJECT=1,///道具卡 
  ZONE_CARD_PROFRESSION=2,///专区卡
};
//消费卡消费
const BYTE CONSUME_CARD_PARA = 11;
struct stConSumeCardCard : public stGoldUserCmd
{
  stConSumeCardCard()
  {
    byParam = CONSUME_CARD_PARA;
    bzero(cardid,sizeof(cardid));
  }
  DWORD type;
  char cardid[CARDID_LENGTH_PARA];
};
/// 消费子类型
enum
{
  OBJ_GOLD_STONE = 1,//送精致升级宝石
  OBJ_GOLD_OBJECT = 2,//送金色装备
  OBJ_GREEN_OBJECT = 3,//送神圣装备
  SUBAT_GOLD = 4,//专区卡充值返回子类型//道具卡的子类型不能于该值重复
};
//消费卡消费返回
const BYTE RETURN_CONSUME_CARD_PARA = 12;
struct stReturnConSumeCardCard : public stGoldUserCmd
{
  stReturnConSumeCardCard()
  {
    byParam = RETURN_CONSUME_CARD_PARA;
  }
  BYTE byType;  //消费类型
  BYTE byReturn;  //返回类型
  DWORD balance;  //专区卡所带点数
};
/*
enum
{
  QUERY_SUCCESS,// 查询成功
  QUERY_BUSY,// 服务器忙
  QUERY_FAIL,// 查询失败
  QUERY_EMPTY,// 该帐号，没有记录
};

enum
{
  TYPE_QUERY,// 查询的返回
  TYPE_CHANGE    // 点数换金币的返回
};

const BYTE RETURN_QUERY_GOLD_PARA = 2;
struct stReturnQueryGold : public stGoldUserCmd
{
  double gold;        /// 帐户余额
  BYTE   state;                           /// 查询状态
  BYTE   type;                            /// 返回类型

  stReturnQueryGold()
  {
    gold = 0;
    type = TYPE_QUERY;
    byParam = RETURN_QUERY_GOLD_PARA;
  };
};

const BYTE CHANGE_POINTTOGOLD_PARA = 3;
struct stChangePointGold : public stGoldUserCmd
{
  DWORD point;        /// 要兑换的点数

  stChangePointGold()
  {
    point = 0;
    byParam = CHANGE_POINTTOGOLD_PARA;
  };
};
// */

//////////////////////////////////////////////////////////////
/// 定义金币命令结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义股票命令开始
//////////////////////////////////////////////////////////////
//STOCK_USERCMD
struct stStockSceneUserCmd : public stNullUserCmd
{
  stStockSceneUserCmd()
  {
    byCmd = STOCK_SCENE_USERCMD;
  }
};
struct stStockBillUserCmd : public stNullUserCmd
{
  stStockBillUserCmd()
  {
    byCmd = STOCK_BILL_USERCMD;
  }
};
/// 股票密码
#define PASSWORD_STOCKPARA 1
struct stPassowrdStockUserCmd : public stStockBillUserCmd
{
  stPassowrdStockUserCmd()
  {
    byParam = PASSWORD_STOCKPARA;
    bzero(byPawword,sizeof(byPawword));
    bzero(byNew1,sizeof(byNew1));
    bzero(byNew2,sizeof(byNew2));
  }
  char byPawword[MAX_PASSWORD];  /// 当前密码
  char byNew1[MAX_PASSWORD];    /// 新密码
  char byNew2[MAX_PASSWORD];    /// 确认密码
};

/// 设置股票密码返回
enum
{
  STOCK_LOGIN_OK,/// 登陆ok
  STOCK_LOGIN_NOTLOGIN,/// 未登陆(提示请先登陆)
  STOCK_OPEN_OK,/// 启用帐号ok
  STOCK_CHANGE_OK,/// 修改密码
  STOCK_ERROR,/// 密码不对
  STOCK_DIFF,/// 两次输入密码不一致
  STOCK_NONE,/// 密码不能为空
  STOCK_SHORT,/// 密码太短
  STOCK_EXIST,/// 帐号已经存在
  STOCK_SERVER_WRONG,/// 服务器错误
  STOCK_GOLDLIST_MAX,/// 股票卖单满
  STOCK_MONEYLIST_MAX,/// 股票卖单满
};
#define RETUEN_PASSWORD_STOCKPARA 2
struct stReturnPasswordStockIserCmd : public stStockBillUserCmd
{
  stReturnPasswordStockIserCmd()
  {
    byParam = RETUEN_PASSWORD_STOCKPARA;
  }
  BYTE byReturn;  ///密码设置返回类型
};
/// 请求股票帐号余额
#define QUERY_FUND_STOCKPARA 3
struct stQueryFundStockUserCmd : public stStockBillUserCmd
{
  stQueryFundStockUserCmd() 
  {
    byParam = QUERY_FUND_STOCKPARA;
  }
  
};

/// 返回当前股票帐号余额
#define RETURN_FUND_STOCKPARA 4 
struct stReturnFundStockUserCmd : public stStockBillUserCmd
{
  stReturnFundStockUserCmd() 
  {
    byParam = RETURN_FUND_STOCKPARA;
  }
  DWORD dwGold;/// 当前帐号金币
  DWORD dwMoney;/// 当前帐号银币
};
 
/// 向股票帐号注入资金
#define TRANSFER_FUND_SAVE_STOCKPARA 5
struct stTransferFundStockSaveUserCmd : public stStockSceneUserCmd
{
  stTransferFundStockSaveUserCmd() 
  {
    byParam = TRANSFER_FUND_SAVE_STOCKPARA;
  }
  DWORD dwGold;/// 操作金币数量
  DWORD dwMoney;/// 操作银币数量
};

/// 从股票帐号提取资金
#define TRANSFER_FUND_FETCH_STOCKPARA 6 
struct stTransferFundStockFetchUserCmd : public stStockBillUserCmd
{
  stTransferFundStockFetchUserCmd() 
  {
    byParam = TRANSFER_FUND_FETCH_STOCKPARA;
  }
  DWORD dwGold;/// 操作金币数量
  DWORD dwMoney;/// 操作银币数量
};
 
/// 委托卖单
#define CONSIGN_GOLD_STOCKPARA 7 
struct stConsignGoldStockUserCmd : public stStockBillUserCmd
{
  stConsignGoldStockUserCmd() 
  {
    byParam = CONSIGN_GOLD_STOCKPARA;
  }
  DWORD dwNum;/// 金币数量
};
 
/// 委托买单
#define CONSIGN_MONEY_STOCKPARA 8
struct stConsignMoneyStockUserCmd : public stStockBillUserCmd
{
  stConsignMoneyStockUserCmd() 
  {
    byParam = CONSIGN_MONEY_STOCKPARA;
  }
  DWORD dwNum;/// 银币数量
};
/// 撤销卖单
#define CONSIGN_CANCEL_GOLD_STOCKPARA 9
struct stConsignCancelGoldStockUserCmd : public stStockBillUserCmd
{
  stConsignCancelGoldStockUserCmd() 
  {
    byParam = CONSIGN_CANCEL_GOLD_STOCKPARA;
  }
  DWORD dwNum;/// 卖单流水号
};

/// 撤销买单
#define CONSIGN_CANCEL_MONEY_STOCKPARA 10
struct stConsignCancelMoneyStockUserCmd : public stStockBillUserCmd
{
  stConsignCancelMoneyStockUserCmd() 
  {
    byParam = CONSIGN_CANCEL_MONEY_STOCKPARA;
  }
  DWORD dwNum;/// 卖单流水号
};
enum StockType
{
  STOCK_GOLD,
  STOCK_MONEY,
};
struct StockList
{
  DWORD id;      /// 流水号
  DWORD dwNum;    /// 数量
  DWORD dwPrice;  /// 委托价格
  DWORD dwTime;/// 委托时间
};
/// 请求未成交委托单
#define REQUEST_CONSIGN_LIST_STOCKPARA 11
struct stRequestConsignListStockUserCmd : public stStockBillUserCmd
{
  stRequestConsignListStockUserCmd() 
  {
    byParam = REQUEST_CONSIGN_LIST_STOCKPARA;
  }
};

/// 未成交的金币委托单
#define CONSIGN_GOLD_LIST_STOCKPARA 12
struct stConsignGoldListStockUserCmd : public stStockBillUserCmd
{
  stConsignGoldListStockUserCmd() 
  {
    byParam = CONSIGN_GOLD_LIST_STOCKPARA;
  }
  DWORD size;
  StockList list[0];
};
/// 未成交的银币委托单
#define CONSIGN_MONEY_LIST_STOCKPARA 13
struct stConsignMoneyListStockUserCmd : public stStockBillUserCmd
{
  stConsignMoneyListStockUserCmd() 
  {
    byParam = CONSIGN_MONEY_LIST_STOCKPARA;
  }
  DWORD size;
  StockList list[0];
};
/// 请求撤单
#define REQUEST_CANCEL_LIST_STOCKPARA 14
struct stRequestCancelListStockUserCmd : public stStockBillUserCmd
{
  stRequestCancelListStockUserCmd() 
  {
    byParam = REQUEST_CANCEL_LIST_STOCKPARA;
  }
  DWORD id;
  BYTE byType;
};
enum
{
  STOCK_CANCEL_ERROR,
  STOCK_CANCEL_OK,
};
/// 应答撤单
#define RETURN_CANCEL_LIST_STOCKPARA 15
struct stReturnCancelListStockUserCmd : public stStockBillUserCmd
{
  stReturnCancelListStockUserCmd() 
  {
    byParam = RETURN_CANCEL_LIST_STOCKPARA;
  }
  DWORD id;
  BYTE byType;
  BYTE byReturn;/*0表示失败,1表示成功*/
};
/// 请求排行前10位的单子
#define REQUEST_FIRSTTEN_LIST_STOCKPARA 16
struct stRequestFirstTenListStockUserCmd : public stStockBillUserCmd
{
  stRequestFirstTenListStockUserCmd() 
  {
    byParam = REQUEST_FIRSTTEN_LIST_STOCKPARA;
  }
};

struct FirstTen
{
  DWORD dwNum;
  DWORD dwPrice;
};
/// 排行前5位的价格和数量
#define FIRSTFIVE_LIST_STOCKPARA 17
struct stFirstFiveListStockUserCmd : public stStockBillUserCmd
{
  stFirstFiveListStockUserCmd() 
  {
    byParam = FIRSTFIVE_LIST_STOCKPARA;
  }
  BYTE byType;//买或卖
  DWORD size;
  FirstTen list[0];
};

/// 提交委托单
#define PUT_LIST_STOCKPARA 18
struct stPutListStockUserCmd : public stStockBillUserCmd
{
  stPutListStockUserCmd() 
  {
    byParam = PUT_LIST_STOCKPARA;
  }
  DWORD dwNum;  //金币或者银币数量
  DWORD dwPrice;  //单价(银币/金币)
  BYTE  byType;  //单子类型,金币或银币
};
/// 返回提交的委托单
#define RETURN_PUT_LIST_STOCKPARA 19
struct stReturnPutListStockUserCmd : public stStockBillUserCmd
{
  stReturnPutListStockUserCmd() 
  {
    byParam = RETURN_PUT_LIST_STOCKPARA;
  }
  StockList list;
};
//股票历史数据结构
struct ConsignHistoryType
{
  ConsignHistoryType()
  {
    dwTime=0;
    dwPrice=0;
    dwTotal=0;
  }
  DWORD dwTime;
  WORD dwPrice;
  WORD dwTotal;
};
/// 玩家请求大盘历史交易数据
#define REQUEST_HISTORY_STOCKPARA 20
struct stRequstHistoryStockUserCmd : public stStockBillUserCmd
{
  stRequstHistoryStockUserCmd() 
  {
    byParam = REQUEST_HISTORY_STOCKPARA;
    begintime=0;
    num=0;
  }
  DWORD begintime;
  DWORD num;
};
/// 返回最新大盘历史数据(当前一分钟的统计数据)
#define NEW_HISTORY_STOCKPARA 21
struct stNewHistoryStockUserCmd : public stStockBillUserCmd
{
  stNewHistoryStockUserCmd() 
  {
    byParam = NEW_HISTORY_STOCKPARA;
  }
  ConsignHistoryType gold;
  ConsignHistoryType money;
};
/// 返回大盘历史金币数据(不定长)
#define HISTORY_GOLD_STOCKPARA 22
struct stHistoryGoldStockUserCmd : public stStockBillUserCmd
{
  stHistoryGoldStockUserCmd() 
  {
    byParam = HISTORY_GOLD_STOCKPARA;
  }
  DWORD size;
  ConsignHistoryType list[0];
};
/// 返回大盘历史银币数据(不定长)
#define HISTORY_MONEY_STOCKPARA 23
struct stHistoryMoneyStockUserCmd : public stStockBillUserCmd
{
  stHistoryMoneyStockUserCmd() 
  {
    byParam = HISTORY_MONEY_STOCKPARA;
  }
  DWORD size;
  ConsignHistoryType list[0];
};
/// 玩家请求自己历史交易数据
#define REQUEST_SELF_HISTORY_STOCKPARA 24
struct stRequstSelfHistoryStockUserCmd : public stStockBillUserCmd
{
  stRequstSelfHistoryStockUserCmd() 
  {
    byParam = REQUEST_SELF_HISTORY_STOCKPARA;
    begintime=0;
    num=0;
  }
  DWORD begintime;
  DWORD num;
};
//个人委托单历史数据
struct ConsignSelfHistoryType
{
  ConsignSelfHistoryType()
  {
  }
  DWORD dwID;
  DWORD wdNum;
  DWORD wdCommitPrice;
  DWORD wdPrice;
  DWORD dwCommitTime;
  DWORD dwOkTime;
};
/// 返回自己历史金币数据(不定长)
#define SELF_HISTORY_GOLD_STOCKPARA 25
struct stSelfHistoryGoldStockUserCmd : public stStockBillUserCmd
{
  stSelfHistoryGoldStockUserCmd() 
  {
    byParam = SELF_HISTORY_GOLD_STOCKPARA;
  }
  DWORD size;
  ConsignSelfHistoryType list[0];
};
/// 返回自己历史银币数据(不定长)
#define SELF_HISTORY_MONEY_STOCKPARA 26
struct stSelfHistoryMoneyStockUserCmd : public stStockBillUserCmd
{
  stSelfHistoryMoneyStockUserCmd() 
  {
    byParam = SELF_HISTORY_MONEY_STOCKPARA;
  }
  DWORD size;
  ConsignSelfHistoryType list[0];
};
/// 股票系统停止服务
#define STOP_SERVICE_STOCKPARA 27
struct stStopServiceStockUserCmd : public stStockBillUserCmd
{
  stStopServiceStockUserCmd() 
  {
    byParam = STOP_SERVICE_STOCKPARA;
  }
};
 
/// 清除未成交委托单
#define CONSIGN_CLEAN_LIST_STOCKPARA 28
struct stConsignCleanListStockUserCmd : public stStockBillUserCmd
{
  stConsignCleanListStockUserCmd() 
  {
    byParam = CONSIGN_CLEAN_LIST_STOCKPARA;
  }
};

/// 请求得到当前用户的激活和登陆状态
#define REQUEST_STATE_STOCKPARA 29
struct stRequestStateStockUserCmd : public stStockBillUserCmd
{
  stRequestStateStockUserCmd() 
  {
    byParam = REQUEST_STATE_STOCKPARA;
  }
  bool  active;
  bool  login;
};
//股票系统控制指令
#define PARA_CANCELLISTALL_STOCKPARA  30
struct t_CancelListAllStock_GateScene : public stStockBillUserCmd
{
  t_CancelListAllStock_GateScene()
    {
      byParam = PARA_CANCELLISTALL_STOCKPARA;
    }
};
//////////////////////////////////////////////////////////////
/// 定义股票命令结束
//////////////////////////////////////////////////////////////


//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义答题命令开始
//////////////////////////////////////////////////////////////
struct stQuizUserCmd : public stNullUserCmd
{
  stQuizUserCmd()
  {
    byCmd = QUIZ_USERCMD;
  }
};

enum
{
  QUIZ_WORLD,
  QUIZ_PERSONAL
};

enum 
{
  QUIZ_QUESTION,// 询问是否接受问答竞赛
  QUIZ_YES,// 参与竞赛
  QUIZ_NO         // 拒绝竞赛
};

const BYTE QUERY_QUIZ_PARA = 1;
struct stQueryQuiz : public stQuizUserCmd
{
  stQueryQuiz() 
  {
    byParam = QUERY_QUIZ_PARA;
    byMsgType = QUIZ_QUESTION;
    byQuizType = 0;
  }
  
  BYTE byMsgType;
  BYTE byQuizType; // 1是普通全国，2是活动
};

enum
{
  CREATE_QUESTION,// 请求进行智力问答
  CREATE_YES,// 请求成功
  CREATE_FAIL   // 金钱不足，失败
};

const BYTE CREATE_QUIZ_PARA = 2;
struct stCreateQuiz : public stQuizUserCmd
{
  stCreateQuiz() 
  {
    byParam = CREATE_QUIZ_PARA;
    byType  = CREATE_QUESTION;
    dwMoney = 100;
  }

  DWORD dwMoney;  // 个人问答时，所需银两
  BYTE byType;
};

const BYTE QUESTION_QUIZ_PARA = 3;
struct stQuestionQuiz : public stQuizUserCmd
{
  stQuestionQuiz()
  {
    byParam = QUESTION_QUIZ_PARA;
    dwSize = 7;
    dwTotal = 0;
  }

  DWORD dwID;  // 题目序号
  BYTE  bySpareTime; // 剩余时间
  BYTE  byNextStartTime;
  BYTE  dwSize; // 题目条数
  DWORD dwTotal;  // 总人数
  
  char subject[0]; // 题目 答案一 答案二 答案三....，中间以0做为分隔
};

const BYTE ANSWER_QUIZ_PARA = 4;
struct stAnswerQuiz : public stQuizUserCmd
{
  stAnswerQuiz()
  {
    byParam = ANSWER_QUIZ_PARA;
    byLuck = 0;
  }

  DWORD dwID;   // 题目序号
  BYTE byType;   // 竞赛类型
  BYTE  byLuck;  // 是否使用幸运星,1使用，其它值是不使用
  DWORD dwScore;  // 得分

  DWORD answerID; // 答案
};

const BYTE ANSWER_RETURN_QUIZ_PARA = 5;
struct stAnswerReturnQuiz : public stQuizUserCmd
{
  stAnswerReturnQuiz()
  {
    byParam = ANSWER_RETURN_QUIZ_PARA;
    byAnswerStatus = -1;
  }

  int byAnswerStatus; // -1:放弃，0:回答正确,1:回答错误
};

struct rank_elem
{
  char name[MAX_NAMESIZE];   // 玩家姓名
  char countryName[MAX_NAMESIZE]; // 国家名称
  int  score;  // 得分
  int  useJob; //sky 职业
  int  rank; // 玩家排名
};

const BYTE QUIZ_POS_LIST_PARA = 6;
struct stQuizPosList : public stQuizUserCmd
{
  stQuizPosList()
  {
    byParam = QUIZ_POS_LIST_PARA;
    bzero(rank_list,sizeof(rank_list));
    dwSize = 1;
  }
  
  DWORD dwSize;
  rank_elem rank_list[21];
};

const BYTE QUIZ_CUR_SCORE_PARA = 7;
struct stQuizCurScore : public stQuizUserCmd
{
  stQuizCurScore()
  {
    byParam = QUIZ_CUR_SCORE_PARA;
    dwScore = 0;
    dwGrace = 0;
  }

  DWORD dwScore; // 本次答题累积分数
  DWORD dwGrace; // 本次答题累积文采
};

const BYTE QUIZ_EXIT_PARA = 8;
struct stQuizExit : public stQuizUserCmd
{
  stQuizExit()
  {
    byParam = QUIZ_EXIT_PARA;
  }
};

const BYTE QUIZ_PARAM_PARA = 9;
struct stQuizParam : public stQuizUserCmd
{
  stQuizParam() 
  {
    byParam = QUIZ_PARAM_PARA;
    byReadQuestionTime = 10;
    byAnswerQuestionTime = 10;
    byCalcTime = 5;
    bySubjectNumber = 90;
  }

  BYTE byReadQuestionTime;  // 读题时间
  BYTE byAnswerQuestionTime;  // 答题时间
  BYTE byCalcTime;    // 计算答案时间
  BYTE bySubjectNumber;    // 总题数
  BYTE byType;      // 竞赛类型
  BYTE byStartTime;    // 竞赛开始剩余时间
};

//////////////////////////////////////////////////////////////
/// 定义答题命令结束
//////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////
/// 定义NPC争夺命令开始
//////////////////////////////////////////////////////////////
struct stNpcDareUserCmd : public stNullUserCmd
{
  stNpcDareUserCmd()
  {
    byCmd = NPCDARE_USERCMD;
  }
};

const BYTE NPCDARE_DARE_PARA = 1;
struct stDareNpcDare : public stNpcDareUserCmd
{
  stDareNpcDare() 
  {
    byParam = NPCDARE_DARE_PARA;
  }
  DWORD dwNpcID;
};

const BYTE NPCDARE_GETGOLD_PARA = 2;
struct stDareNpcGetGold : public stNpcDareUserCmd
{
  stDareNpcGetGold() 
  {
    byParam = NPCDARE_GETGOLD_PARA;
  }
  DWORD dwNpcID;
};

enum
{
  QUESTION_NPCDARE_HOLD,// 查询城市所属
  QUESTION_NPCDARE_DARE,// 当天城市争夺战
};

// 查询问NPC争夺战信息
const BYTE QUESTION_NPCDARE_INFO_PARA = 3;
struct stQuestionNpcDareInfo : public stNpcDareUserCmd
{
  stQuestionNpcDareInfo()
  {
    byParam = QUESTION_NPCDARE_INFO_PARA;
  }
  BYTE byType;  
  DWORD dwNpcID;
};
//////////////////////////////////////////////////////////////
/// 定义NPC争夺命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义与GM工具交互的命令开始
//////////////////////////////////////////////////////////////
struct stGmToolUserCmd : public stNullUserCmd
{
  stGmToolUserCmd()
  {
    byCmd = GMTOOL_USERCMD;
  }
};

const BYTE CHAT_GMTOOL_PARA = 1;
struct stChatGmTool : public stGmToolUserCmd
{
  char userName[MAX_NAMESIZE];
  DWORD countryID;
  DWORD sceneID;
  stChannelChatUserCmd chat_cmd;
  stChatGmTool() 
  {
    byParam = CHAT_GMTOOL_PARA;
    countryID = 0;
    sceneID = 0;
  }
};

const BYTE MSG_GMTOOL_PARA = 2;
struct stMsgGmTool : public stGmToolUserCmd
{
  BYTE type;//定单类型
  char content[512];//主要内容
  BYTE contact;//联系方式
  char tele[64];//地址、电话
  char hisName[MAX_NAMESIZE];//被举报者
  char bugCountry[8];//bug发生国家
  char bugMap[16];//bug发生地图
  char bugPos[8];//bug发生位置
  char bugTime[64];//发生时间
  char progName[64];//疑似外挂名称
  BYTE behavior;//不良游戏现象
  stMsgGmTool()
  {

    type = 0;
    bzero(content,sizeof(content));
    contact = 0;
    bzero(tele,sizeof(tele));
    bzero(hisName,sizeof(hisName));
    bzero(bugCountry,sizeof(bugCountry));
    bzero(bugMap,sizeof(bugMap));
    bzero(bugPos,sizeof(bugPos));
    bzero(bugTime,sizeof(bugTime));
    bzero(progName,sizeof(progName));
    behavior = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义与GM工具交互的命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
// 卡通宠物指令定义开始
//////////////////////////////////////////////////////////////

//宝宝的状态
enum cartoonState
{
  CARTOON_STATE_PUTAWAY,//收起
  CARTOON_STATE_FOLLOW,//跟随主人
  CARTOON_STATE_WAITING,//等待领养
  CARTOON_STATE_ADOPTED  //被领养
};

//宝宝的数据
struct t_CartoonData
{
  //DWORD cartoonID;    //宝宝id
  char name[MAX_NAMESIZE];  //名字
  DWORD npcID;      //npcid
  DWORD masterID;      //主人id
  char masterName[MAX_NAMESIZE];  //主人名字
  BYTE lv;      //等级
  DWORD exp;      //经验
  DWORD maxExp;      //升级经验
  DWORD addExp;      //给主人增加的经验
  BYTE state;    //状态
  char adopter[MAX_NAMESIZE];  //领养人
  DWORD time;      //挂机剩余时间(秒)
  DWORD sp;      //精气值
  DWORD maxSp;      //最大精气值
  DWORD masterLevel;    //主人等级
  BYTE repair;      //自动修理主人装备

  t_CartoonData & operator = (const t_CartoonData& reg)
  {
    bcopy(&reg,this,sizeof(t_CartoonData),sizeof(t_CartoonData));

    return *this;
  }

  t_CartoonData & operator << (const t_CartoonData& reg)
  {
    addExp += reg.addExp;
    state = reg.state;
    bcopy(reg.adopter,adopter,MAX_NAMESIZE,sizeof(adopter));
    time = reg.time;
    /*
    DWORD e = addExp;
    bcopy(&reg,this,sizeof(t_CartoonData));
    addExp += e;
    */

    return *this;
  }
};

struct stCartoonUserCmd : public stNullUserCmd
{
  stCartoonUserCmd()
  {
    byCmd = CARTOON_USERCMD;
  }
};

#define BUY_CARTOON_PARA 1  //购买
struct stBuyCartoonCmd : public stCartoonUserCmd
{
  stBuyCartoonCmd()
  {
    byParam = BUY_CARTOON_PARA;
  }
  DWORD npcID;
};

#define ADD_CARTOON_PARA 2  //添加列表
struct stAddCartoonCmd : public stCartoonUserCmd
{
  stAddCartoonCmd()
  {
    byParam = ADD_CARTOON_PARA;
  }
  bool isMine;
  DWORD cartoonID;
  t_CartoonData data;
};

#define REMOVE_CARTOON_PARA 3  //移除列表
struct stRemoveCartoonCmd : public stCartoonUserCmd
{
  stRemoveCartoonCmd()
  {
    byParam = REMOVE_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define FOLLOW_CARTOON_PARA 4  //跟随/取消跟随
struct stFollowCartoonCmd : public stCartoonUserCmd
{
  stFollowCartoonCmd()
  {
    byParam = FOLLOW_CARTOON_PARA;
  }
  DWORD cartoonID;//取消跟随填0
};

#define LETOUT_CARTOON_PARA 5  //放出，使别人可以领养
struct stLetOutCartoonCmd : public stCartoonUserCmd
{
  stLetOutCartoonCmd()
  {
    byParam = LETOUT_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define ADOPT_CARTOON_PARA 6  //领养宠物
struct stAdoptCartoonCmd : public stCartoonUserCmd
{
  stAdoptCartoonCmd()
  {
    byParam = ADOPT_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define RETURN_CARTOON_PARA 7  //归还宠物
struct stReturnCartoonCmd : public stCartoonUserCmd
{
  stReturnCartoonCmd()
  {
    byParam = RETURN_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define GETBACK_CARTOON_PARA 8  //收回宠物
struct stGetBackCartoonCmd : public stCartoonUserCmd
{
  stGetBackCartoonCmd()
  {
    byParam = GETBACK_CARTOON_PARA;
  }
};

#define DRAWEXP_CARTOON_PARA 9  //提取经验
struct stDrawExpCartoonCmd : public stCartoonUserCmd
{
  stDrawExpCartoonCmd()
  {
    byParam = DRAWEXP_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define CHANGENAME_CARTOON_PARA 10  //改名字
struct stChangeNameCartoonCmd : public stCartoonUserCmd
{
  stChangeNameCartoonCmd()
  {
    byParam = CHANGENAME_CARTOON_PARA;
  }
  DWORD cartoonID;
  char name[MAX_NAMESIZE];
};

#define ADD_WAITING_CARTOON_PARA 11  //添加等待列表
struct stAddWaitingCartoonCmd : public stCartoonUserCmd
{
  stAddWaitingCartoonCmd()
  {
    byParam = ADD_WAITING_CARTOON_PARA;
  }
  DWORD cartoonID;    //宝宝id
  DWORD npcID;    //NPC ID
  char name[MAX_NAMESIZE];  //名字
  char masterName[MAX_NAMESIZE];  //主人名字
  BYTE state;    //状态
  DWORD time;      //挂机剩余时间(秒)

  void operator = (const t_CartoonData& reg)
  {
    npcID = reg.npcID;
    strcpy_s(name,reg.name);
    strcpy_s(masterName,reg.masterName);
    state = reg.state;
    time = reg.time;
  }
};

#define REMOVE_WAITING_CARTOON_PARA 12  //移除等待列表
struct stRemoveWaitingCartoonCmd : public stCartoonUserCmd
{
  stRemoveWaitingCartoonCmd()
  {
    byParam = REMOVE_WAITING_CARTOON_PARA;
  }
  DWORD cartoonID;
};

#define REQUEST_LIST_CARTOON_PARA 13  //请求等待列表
struct stRequestListCartoonCmd : public stCartoonUserCmd
{
  stRequestListCartoonCmd()
  {
    byParam = REQUEST_LIST_CARTOON_PARA;
  }
};

#define SALE_CARTOON_PARA 14  //卖出宠物
struct stSaleCartoonCmd : public stCartoonUserCmd
{
  DWORD cartoonID;
  stSaleCartoonCmd()
  {
    byParam = SALE_CARTOON_PARA;

    cartoonID = 0;
  }
};

#define CHARGE_CARTOON_PARA 15  //充值
struct stChargeCartoonCmd : public stCartoonUserCmd
{
  stChargeCartoonCmd()
  {
    byParam = CHARGE_CARTOON_PARA;
  }
  DWORD cartoonID;
  DWORD time;//充多长时间(秒)
};

#define HP_EXP_CARTOON_PARA 16  //同步sp和经验
struct stHpExpCartoonCmd : public stCartoonUserCmd
{
  stHpExpCartoonCmd()
  {
    byParam = HP_EXP_CARTOON_PARA;
  }
  DWORD cartoonID;
  DWORD sp;
  DWORD exp;
};

#define SELL_ALL_CARTOON_PARA 17  //卖包裹里所有物品
struct stSellAllCartoonCmd : public stCartoonUserCmd
{
  stSellAllCartoonCmd()
  {
    byParam = SELL_ALL_CARTOON_PARA;
  }
};

#define CONSIGN_CARTOON_PARA 18  //委托领养
struct stConsignCartoonCmd : public stCartoonUserCmd
{
  stConsignCartoonCmd()
  {
    byParam = CONSIGN_CARTOON_PARA;
  }
  DWORD cartoonID;
  char name[MAX_NAMESIZE];//请求时是被委托人，被请求时是委托人
};

#define CONSIGN_RET_CARTOON_PARA 19  //确认委托领养
struct stConsignRetCartoonCmd : public stCartoonUserCmd
{
  stConsignRetCartoonCmd()
  {
    byParam = CONSIGN_RET_CARTOON_PARA;
  }
  DWORD cartoonID;
  BYTE ret;//0：拒绝 1：同意
};

#define REPAIR_CARTOON_PARA 20  //设置自动修理
struct stRepairCartoonCmd : public stCartoonUserCmd
{
  stRepairCartoonCmd()
  {
    byParam = REPAIR_CARTOON_PARA;
  }
  DWORD cartoonID;
  BYTE repair;//0：关闭 1：打开
};

//////////////////////////////////////////////////////////////
// 卡通宠物指令定义结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义邮件命令开始
//////////////////////////////////////////////////////////////
const DWORD mail_postage = 50;  ///邮资50文

struct stMailUserCmd : public stNullUserCmd
{
  stMailUserCmd()
  {
    byCmd = MAIL_USERCMD;
  }
};

/*
const BYTE CHECK_ITEM_MAIL_PARA = 1;
struct stCheckItemMail : public stMailUserCmd
{
  DWORD itemID;
  stCheckItemMail()
  {
    byParam = CHECK_ITEM_MAIL_PARA;
  }
};

enum CheckReturn
{
  CHECK_RETURN_SUCCESS = 1,
  CHECK_RETURN_FAIL = 2
};
const BYTE CHECK_RETURN_MAIL_PARA = 2;
struct stCheckReturnMail : public stMailUserCmd
{
  CheckReturn retCode;
  stCheckReturnMail()
  {
    byParam = CHECK_RETURN_MAIL_PARA;
  }
};
*/

//发送邮件
const BYTE SEND_MAIL_PARA = 3;
struct stSendMail : public stMailUserCmd
{
  char toName[MAX_NAMESIZE];
  char title[MAX_NAMESIZE];
  char text[256];
  DWORD sendMoney;
  DWORD recvMoney;
  DWORD sendGold;
  DWORD recvGold;
  DWORD itemID;
  stSendMail() 
  {
    byParam = SEND_MAIL_PARA;
    sendMoney = 0;
    recvMoney = 0;
    sendGold = 0;
    recvGold = 0;
    itemID = 0;
  }
};

/*
enum sendReturn
{
  SEND_RETURN_SUCCESS = 1,
  SEND_RETURN_FAIL = 2
};
const BYTE SEND_RETURN_MAIL_PARA = 4;
struct stSendReturnMail : public stMailUserCmd
{
  sendReturn retCode;
  stSendReturnMail()
  {
    byParam = SEND_RETURN_MAIL_PARA;
  }
};
*/

//请求邮件列表
const BYTE GET_LIST_MAIL_PARA = 5;
struct stGetListMail : public stMailUserCmd
{
  stGetListMail()
  {
    byParam = GET_LIST_MAIL_PARA;
  }
};

//添加邮件列表
const BYTE ADD_LIST_MAIL_PARA = 6;
struct stAddListMail : public stMailUserCmd
{
  DWORD id;
  BYTE state;
  char fromName[MAX_NAMESIZE];
  bool accessory;
  DWORD endTime;
  BYTE type;  //0:普通 1：系统
  stAddListMail()
  {
    byParam = ADD_LIST_MAIL_PARA;
    id = 0;
    state = 0;
    accessory = 0;
    endTime = 0;
    bzero(fromName,sizeof(fromName));
    type = 0;
  }
};

//请求邮件内容
const BYTE OPEN_MAIL_PARA = 7;
struct stOpenMail : public stMailUserCmd
{
  DWORD mailID;
  stOpenMail()
  {
    byParam = OPEN_MAIL_PARA;
  }
};

//邮件内容
const BYTE CONTENT_MAIL_PARA = 8;
struct stContentMail : public stMailUserCmd
{
  DWORD mailID;
  char title[MAX_NAMESIZE];
  bool accessory;
  char text[256];
  DWORD sendMoney;
  DWORD recvMoney;
  DWORD sendGold;
  DWORD recvGold;
  t_Object item;
  stContentMail()
  {
    byParam = CONTENT_MAIL_PARA;
    mailID = 0;
    bzero(title,sizeof(title));
    accessory = false;
    bzero(text,sizeof(text));
    sendMoney = recvMoney = 0;
    sendGold = 0;
    recvGold = 0;
    bzero(&item,sizeof(item));
  }
};

//取得邮件附件
const BYTE GET_ITEM_MAIL_PARA = 9;
struct stGetItemMail : public stMailUserCmd
{
  DWORD mailID;
  stGetItemMail()
  {
    byParam = GET_ITEM_MAIL_PARA;
  }
};

//删除邮件附件
const BYTE REMOVE_ITEM_MAIL_PARA = 10;
struct stRemoveItemMail : public stMailUserCmd
{
  DWORD mailID;
  stRemoveItemMail()
  {
    byParam = REMOVE_ITEM_MAIL_PARA;
  }
};

//删除邮件
const BYTE DEL_MAIL_PARA = 11;
struct stDelMail : public stMailUserCmd
{
  DWORD mailID;
  stDelMail()
  {
    byParam = DEL_MAIL_PARA;
  }
};

//新邮件提示
const BYTE NOTIFY_NEW_MAIL_PARA = 12;
struct stNotifyNewMail : public stMailUserCmd
{
  stNotifyNewMail()
  {
    byParam = NOTIFY_NEW_MAIL_PARA;
  }
};

//退回邮件
const BYTE TURN_BACK_MAIL_PARA = 13;
struct stTurnBackMail : public stMailUserCmd
{
  DWORD mailID;
  stTurnBackMail()
  {
    byParam = TURN_BACK_MAIL_PARA;
  }
};

/*
*/
//////////////////////////////////////////////////////////////
/// 定义邮件命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义拍卖命令开始
//////////////////////////////////////////////////////////////
//const DWORD mail_postage = 50;  ///邮资50文

struct stAuctionUserCmd : public stNullUserCmd
{
  stAuctionUserCmd()
  {
    byCmd = AUCTION_USERCMD;
  }
};

enum
{
  AUCTION_WEAPOM_SWORD = 1,
  AUCTION_WEAPOM_AXE = 2,
  AUCTION_WEAPOM_BOW = 3,
  AUCTION_WEAPOM_STICK = 4,
  AUCTION_WEAPOM_WAND = 5,
  AUCTION_WEAPOM_FAN = 6,
  AUCTION_EQUIP_HEAD = 11,
  AUCTION_EQUIP_BODY = 12,
  AUCTION_EQUIP_WRIST = 13,
  AUCTION_EQUIP_SHIELD = 14,
  AUCTION_EQUIP_WAIST = 15,
  AUCTION_EQUIP_FOOT = 16,
  AUCTION_ACCESSORY_NECKLACE = 21,
  AUCTION_ACCESSORY_RING = 22,
  AUCTION_ACCESSORY_ADORNMENT = 23,
  AUCTION_BOOK_FIGHTER = 31,
  AUCTION_BOOK_ARCHER = 32,
  AUCTION_BOOK_WIZARD = 33,
  AUCTION_BOOK_SUMMONER = 34,
  AUCTION_BOOK_PRIEST = 35,
  AUCTION_BOOK_SPECIAL = 36,
  AUCTION_OTHER_GEM = 41,
  AUCTION_OTHER_ITEM = 42,
  AUCTION_OTHER_MATERIAL = 43,
  AUCTION_OTHER_LEECHDOM = 44
};

const BYTE AUCTION_BID_TYPE_MONEY = 0;
const BYTE AUCTION_BID_TYPE_GOLD = 1;

//拍卖一件物品
const BYTE SALE_AUCTION_PARA = 1;
struct stSaleAuction : public stAuctionUserCmd
{
  DWORD itemID;
  DWORD minMoney;
  DWORD maxMoney;
  DWORD minGold;
  DWORD maxGold;
  BYTE bidType;
  stSaleAuction()
  {
    byParam = SALE_AUCTION_PARA;
    itemID = 0xffffffff;
    minMoney = 0;
    maxMoney = 0;
    minGold = 0;
    maxGold = 0;
    bidType = 0;
  }
};

//竞价
const BYTE BID_AUCTION_PARA = 2;
struct stBidAuction : public stAuctionUserCmd
{
  DWORD auctionID;
  DWORD money;
  DWORD gold;
  stBidAuction()
  {
    byParam = BID_AUCTION_PARA;
    auctionID = 0;
    money = 0;
    gold = 0;
  }
};

//添加列表
const BYTE ADD_LIST_AUCTION_PARA = 3;
struct stAddListAuction : public stAuctionUserCmd
{
  BYTE list;//1:查看列表 2:竞标列表 3:拍卖列表 4:所有列表
  DWORD auctionID;
  DWORD minMoney;
  DWORD maxMoney;
  DWORD minGold;
  DWORD maxGold;
  DWORD endTime;
  t_Object item;
  bool mine;//是否我的价格最高
  char owner[MAX_NAMESIZE];//拍卖者
  DWORD max;//总共多少个
  BYTE bidType;
  stAddListAuction()
  {
    byParam = ADD_LIST_AUCTION_PARA;

    list = 0;
    auctionID = 0;
    minMoney = 0;
    maxMoney = 0;
    minGold = 0;
    maxGold = 0;
    bzero(&item,sizeof(item));
    mine = false;
    bzero(owner,sizeof(owner));
    max = 0;
    bidType = 0;
  }
};

//移除列表
const BYTE REMOVE_LIST_AUCTION_PARA = 4;
struct stRemoveListAuction : public stAuctionUserCmd
{
  BYTE list;//1:查看列表 2:竞标列表 3:拍卖列表 4:所有列表
  DWORD auctionID;
  stRemoveListAuction()
  {
    byParam = REMOVE_LIST_AUCTION_PARA;

    list = 0;
    auctionID = 0;
  }
};

//搜索
const BYTE QUERY_AUCTION_PARA = 5;
struct stQueryAuction : public stAuctionUserCmd
{
  BYTE type;
  char name[MAX_NAMESIZE];
  BYTE quality;//1普通,2蓝色,3金色,5神圣
  WORD level;
  WORD page;
  stQueryAuction()
  {
    byParam = QUERY_AUCTION_PARA;

    type = 0;
    bzero(name,sizeof(name));
    quality = 0;
    level = (DWORD)-1;
    page = 0;
  }
};

//取消拍卖
const BYTE CANCEL_SALE_AUCTION_PARA = 6;
struct stCancelSaleAuction : public stAuctionUserCmd
{
  DWORD auctionID;
  stCancelSaleAuction()
  {
    byParam = CANCEL_SALE_AUCTION_PARA;

    auctionID = 0;
  }
};

//请求列表
const BYTE GET_LIST_AUCTION_PARA = 7;
struct stGetListAuction : public stAuctionUserCmd
{
  BYTE list;//2:竞标列表 3:拍卖列表 
  stGetListAuction()
  {
    byParam = GET_LIST_AUCTION_PARA;

    list = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义拍卖命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义监狱命令开始
//////////////////////////////////////////////////////////////

struct stPrisonUserCmd : public stNullUserCmd
{
  stPrisonUserCmd()
  {
    byCmd = PRISON_USERCMD;
  }
};

//请求出狱
const BYTE OUT_PRISON_PARA = 1;
struct stOutPrison : public stPrisonUserCmd
{
  stOutPrison()
  {
    byParam = OUT_PRISON_PARA;
  }
};

//贿赂
const BYTE BRIBE_PRISON_PARA = 2;
struct stBribePrison : public stPrisonUserCmd
{
  DWORD money;
  stBribePrison()
  {
    byParam = BRIBE_PRISON_PARA;

    money = 0;
  }
};

//取保就医(帮别人洗PK值)
const BYTE BAIL_PRISON_PARA = 3;
struct stBailPrison : public stPrisonUserCmd
{
  char name[MAX_NAMESIZE];
  DWORD money;
  stBailPrison()
  {
    byParam = BAIL_PRISON_PARA;

    bzero(name,sizeof(name));
    money = 0;
  }
};

//请求出牢狱
const BYTE LEAVE_PRISON_PARA = 4;
struct stLeavePrison : public stPrisonUserCmd
{
  stLeavePrison()
  {
    byParam = LEAVE_PRISON_PARA;
  }
};

//////////////////////////////////////////////////////////////
/// 定义监狱命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义礼官命令开始
//////////////////////////////////////////////////////////////

struct stGiftUserCmd : public stNullUserCmd
{
  stGiftUserCmd()
  {
    byCmd = GIFT_USERCMD;
  }
};

//请求活动列表
const BYTE GET_LIST_GIFT_PARA = 1;
struct stGetListGift : public stGiftUserCmd
{
  stGetListGift()
  {
    byParam = GET_LIST_GIFT_PARA;
  }
};

struct actTitle
{
  DWORD id;
  char name[MAX_NAMESIZE];
  BYTE state;
};

//发送活动列表
const BYTE LIST_GIFT_PARA = 2;
struct stListGift : public stGiftUserCmd
{
  DWORD num;
  actTitle titles[0];
  stListGift()
  {
    byParam = LIST_GIFT_PARA;
    num = 0;
  }
};

//请求活动内容
const BYTE GET_DETAIL_GIFT_PARA = 3;
struct stGetDetailGift : public stGiftUserCmd
{
  DWORD id;
  stGetDetailGift()
  {
    byParam = GET_DETAIL_GIFT_PARA;
    id = 0;
  }
};

//发送活动内容
const BYTE DETAIL_GIFT_PARA = 4;
struct stDetailGift : public stGiftUserCmd
{
  DWORD id;//活动ID
  char text[MAX_CHATINFO];
  stDetailGift()
  {
    byParam = DETAIL_GIFT_PARA;
    id = 0;
    bzero(text,sizeof(text));
  }
};

//领取奖品
const BYTE GET_ITEM_GIFT_PARA = 5;
struct stGetItemGift : public stGiftUserCmd
{
  DWORD id;
  stGetItemGift()
  {
    byParam = GET_ITEM_GIFT_PARA;
    id = 0;
  }
};

//请求获奖名单
const BYTE GET_WINNER_GIFT_PARA = 6;
struct stGetWinnerGift : public stGiftUserCmd
{
  DWORD id;//活动ID
  stGetWinnerGift()
  {
    byParam = GET_WINNER_GIFT_PARA;
    id = 0;
  }
};

//发送获奖名单
const BYTE WINNER_GIFT_PARA = 7;
struct stWinnerGift : public stGiftUserCmd
{
  DWORD num;
  char winners[0];
  stWinnerGift()
  {
    byParam = WINNER_GIFT_PARA;
    num = 0;
  }
};

//////////////////////////////////////////////////////////////
/// 定义礼官命令结束
//////////////////////////////////////////////////////////////

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义国家联盟命令开始
//////////////////////////////////////////////////////////////

struct stAllyUserCmd : public stNullUserCmd
{
  stAllyUserCmd()
  {
    byCmd = ALLY_USERCMD;
  }
};

enum
{
  QUESTION_COUNTRY_ALLY,// 发起请求
  YES_COUNTRY_ALLY,// 同意请求
  NO_COUNTRY_ALLY,// 拒绝请求
};

//请求结盟
#define REQ_COUNTRY_ALLY_PARA  1
struct stReqCountryAlly : public stAllyUserCmd
{
  stReqCountryAlly()
  {
    byParam = REQ_COUNTRY_ALLY_PARA;
    dwCountryID = 0;
    dwAllyCountryID = 0;
    byStatus = QUESTION_COUNTRY_ALLY;
  }
  
  DWORD dwCountryID; // 发起请求的国家,发起时不用填写
  DWORD dwAllyCountryID; // 被邀请的国家
  BYTE  byStatus;
};

// 设置盟国信息
#define UPDATE_COUNTRY_ALLY_PARA 2
struct stUpdateCountryAlly : public stAllyUserCmd
{
  stUpdateCountryAlly()
  {
    byParam = UPDATE_COUNTRY_ALLY_PARA;
    dwAllyCountryID = 0;
  }

  DWORD dwAllyCountryID;
};

// 取缔盟约
#define CANCEL_COUNTRY_ALLY_PARA 3
struct stCancelCountryAlly : public stAllyUserCmd
{
  stCancelCountryAlly()
  {
    byParam = CANCEL_COUNTRY_ALLY_PARA;
    dwAllyCountryID = 0;
  }

  DWORD dwAllyCountryID;
};

// 请求国家联盟信息
#define REQ_COUNTRY_ALLY_INFO_PARA 4
struct stReqCountryAllyInfo : public stAllyUserCmd
{
  stReqCountryAllyInfo()
  {
    byParam = REQ_COUNTRY_ALLY_INFO_PARA;
  }
};

// 返回国家联盟信息
#define RTN_COUNTRY_ALLY_INFO_PARA 5
struct stRtnCountryAllyInfo : public stAllyUserCmd
{
  stRtnCountryAllyInfo()
  {
    byParam = RTN_COUNTRY_ALLY_INFO_PARA;
    dwAllyCountryID = 0;
    dwFriendDegree = 0;
  }
  
  DWORD dwAllyCountryID;
  DWORD dwFriendDegree;
};

//////////////////////////////////////////////////////////////
/// 定义国家联盟命令结束
//////////////////////////////////////////////////////////////

/*
//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义小游戏命令开始
//////////////////////////////////////////////////////////////

struct stMiniGameUserCmd : public stNullUserCmd
{
  stMiniGameUserCmd()
  {
    byCmd = MINIGAME_USERCMD;
  }
};

// 邀请
#define INVITE_MINI_PARA 1
struct stInviteMiniGame : public stMiniGameUserCmd
{
  stInviteMiniGame()
  {
    byParam = INVITE_MINI_PARA;
  }
  DWORD tempid;//邀请者/被邀请者的临时ID
  DWORD money;//赌注
};

// 邀请回复
#define INVITE_RET_MINI_PARA 2
struct stInviteRetMiniGame : public stMiniGameUserCmd
{
  stInviteRetMiniGame()
  {
    byParam = INVITE_RET_MINI_PARA;
  }
  DWORD tempid;//邀请者的临时ID
  DWORD money;//赌注
  DWORD ret;//1:同意 0:不同意
};

// 开始游戏
#define START_MINI_PARA 3
struct stStartMiniGame : public stMiniGameUserCmd
{
  stStartMiniGame()
  {
    byParam = START_MINI_PARA;
  }
  DWORD tempid;//对方的临时ID
  DWORD money;//赌注
};

// 停止色子
#define STOP_DICE_MINI_PARA 4
struct stStopDiceMiniGame : public stMiniGameUserCmd
{
  stStopDiceMiniGame()
  {
    byParam = STOP_DICE_MINI_PARA;
  }
};

// 色子数字
#define DICE_NUM_MINI_PARA 5
struct stDiceNumMiniGame : public stMiniGameUserCmd
{
  stDiceNumMiniGame()
  {
    byParam = DICE_NUM_MINI_PARA;
  }
  DWORD tempid;//掷色子人的临时ID
  DWORD num;
};

// 结果
#define RESULT_MINI_PARA 6
struct stResultMiniGame : public stMiniGameUserCmd
{
  stResultMiniGame()
  {
    byParam = RESULT_MINI_PARA;
  }
  DWORD res;//0:输 1:赢 2:平
};

// 游戏结束 //主动离开游戏
#define END_MINI_PARA 7
struct stEndMiniGame : public stMiniGameUserCmd
{
  stEndMiniGame()
  {
    byParam = END_MINI_PARA;

    reason = 0;
  }
  DWORD reason;//结束原因 0:正常结束 1:对方离开
};

// 继续游戏
#define CONTINUE_MINI_PARA 8
struct stContinueMiniGame : public stMiniGameUserCmd
{
  stContinueMiniGame()
  {
    byParam = CONTINUE_MINI_PARA;
  }
  DWORD ret;//0:不继续 1:继续
};

// 通知客户端进入游戏
#define ENTER_MINI_PARA 9
struct stEnterMiniGame : public stMiniGameUserCmd
{
  stEnterMiniGame()
  {
    byParam = ENTER_MINI_PARA;
  }
};

//////////////////////////////////////////////////////////////
/// 定义小游戏命令结束
//////////////////////////////////////////////////////////////
*/

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义推荐人系统命令开始
//////////////////////////////////////////////////////////////

struct stRecommendUserCmd : public stNullUserCmd
{
  stRecommendUserCmd()
  {
    byCmd = RECOMMEND_USERCMD;
  }
};

// 填写自己的推荐人,<=15级的玩家才能填写
#define SET_RECOMMEND_PARA 1
struct stSetRecommendUserCmd : public stRecommendUserCmd
{
  stSetRecommendUserCmd()
  {
    byParam = SET_RECOMMEND_PARA;
    bzero(name,MAX_NAMESIZE);
  }

  char name[MAX_NAMESIZE];
};

enum
{
  QUERY_BOUNTY,// 查询当前奖励金
  GET_BOUNTY,// 提取当前奖励金
};

// 推荐人查询或领取奖励
#define REQ_RECOMMEND_BOUNTY_PARA 2
struct stReqRecommendBountyUserCmd : public stRecommendUserCmd
{
  stReqRecommendBountyUserCmd()
  {
    byParam = REQ_RECOMMEND_BOUNTY_PARA;
  }

  BYTE byState;
};

// 被推荐人查询或领取奖励
#define REQ_RECOMMENDED_BOUNTY_PARA 3
struct stReqRecommendedBountyUserCmd : public stRecommendUserCmd
{
  stReqRecommendedBountyUserCmd()
  {
    byParam = REQ_RECOMMENDED_BOUNTY_PARA;
  }

  BYTE byState;
};

struct stRecommendItem
{
  char name[MAX_NAMESIZE]; // 被推荐人姓名
  DWORD dwLevel;  // 最后一次提取时的等级
  DWORD dwTotal;  // 累计贡献多少金额
};

// 返回推荐人奖励
#define RTN_RECOMMEND_BOUNTY_PARA 4
struct stRtnRecommendBountyUserCmd : public stRecommendUserCmd
{
  stRtnRecommendBountyUserCmd()
  {
    byParam = RTN_RECOMMEND_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwSize = 0;
  }

  DWORD dwBalance; // 可领取的金额
  DWORD dwTotal;  // 累计已领取的金额
  DWORD dwSize;  // 被推荐人数目,有可能有很多,如果超过窗口大小,能不能做成可以拉动
  stRecommendItem data[0];
};

// 返回被推荐人奖励
#define RTN_RECOMMENDED_BOUNTY_PARA 5
struct stRtnRecommendedBountyUserCmd : public stRecommendUserCmd
{
  stRtnRecommendedBountyUserCmd()
  {
    byParam = RTN_RECOMMENDED_BOUNTY_PARA;
    dwBalance = 0;
    dwTotal = 0;
    dwLastLevel = 0;
    bzero(name,sizeof(name));
  }
  
  DWORD dwBalance; // 可领取的余额
  DWORD dwTotal;   // 累计已领取的金额
  DWORD dwLastLevel; // 上次领取时的等级
  char name[MAX_NAMESIZE]; // 推荐人姓名
};

//////////////////////////////////////////////////////////////
/// 定义推荐人系统命令结束
//////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////
/// 定义财产保护系统指令开始
//////////////////////////////////////////////////////////////
struct stSafetyUserCmd : public stNullUserCmd
{
  stSafetyUserCmd()
  {
    byCmd = SAFETY_USERCMD;
  }
};

// 玩家设置保护状态
#define SET_SAFETY_PARA 1
struct stSetSafetyUserCmd : public stSafetyUserCmd
{
  stSetSafetyUserCmd()
  {
    byParam = SET_SAFETY_PARA;
    pwd = 0;
    state = 0;
  }

  DWORD pwd; // 数字密码
  BYTE  state; // 保护状态,0为关闭,1为开启,两个操作都需要输入数字密码
};

enum
{
  SAFETY_OPEN,// 保护状态,该状态下,不能进行拆装备操作
  SAFETY_TEMP_CLOSE,// 本次登录,暂时关闭状态,可以进行任何操作
};

// 玩家上线时,服务器通知客户端,玩家是否在保护状态
#define NOTIFY_SAFETY_PARA 2
struct stNotifySafetyUserCmd : public stSafetyUserCmd
{
  stNotifySafetyUserCmd()
  {
    byParam = NOTIFY_SAFETY_PARA;
    safe_setup = 0;
    byState = 0;
  }

  BYTE byState;
  BYTE safe_setup; 
};

// 玩家进入临时未保护状态,只在一次登录中有效,小退和关客户端后,无效
#define SET_TEMP_UNSAFETY_PARA 3
struct stSetTempUnSafetyUserCmd : public stSafetyUserCmd
{
  stSetTempUnSafetyUserCmd()
  {
    byParam = SET_TEMP_UNSAFETY_PARA;
    pwd = 0;
  }
  
  DWORD pwd;
};

enum
{
  SAFE_SPLIT_OBJECT,// 拆装备时,需要验证
  SAFE_THIRD_PACK,// 从第二,三个包裹中拿出物品,需要验证
  SAFE_GOLD_STOCK,// 金币购买股票
};
// 设置需要保护的功能
// 用,set_state,clear_state,来操作
#define SET_SAFETY_DETAIL_PARA 4
struct stSetSafetyDetailUserCmd : public stSafetyUserCmd
{
  stSetSafetyDetailUserCmd()
  {
    byParam = SET_SAFETY_DETAIL_PARA;
    safe_setup=0;
    pwd = 0;
  }
  
  DWORD pwd;
  BYTE safe_setup;
};

//////////////////////////////////////////////////////////////
/// 定义财产保护系统指令结束
//////////////////////////////////////////////////////////////

};

/**
 * \brief 定义游戏区
 * 对游戏进行分类，然后在同种游戏中再分区
 */
struct GameZone_t
{

  operator int() const
	  {
		return id;
	  }

  union
  {
    /**
     * \brief 唯一编号
     */
    DWORD id;
    struct
    {
      /**
       * \brief 游戏分区编号
       */
      WORD zone;
      /**
       * \brief 游戏种类编号
       */
      WORD game;
    };
  };

  GameZone_t()
  {
    this->game = 0;
    this->zone = 0;
  }
  GameZone_t(const GameZone_t &gameZone)
  {
    this->id = gameZone.id;
  }
  GameZone_t & operator= (const GameZone_t &gameZone)
  {
    this->id = gameZone.id;
    return *this;
  }
  bool operator== (const GameZone_t &gameZone) const
  {
    return this->id == gameZone.id;
  }
};

struct t_NewLoginSession
{
  WORD wdLoginID;
  WORD wdGatewayID;
  DWORD loginTempID;
  char pstrIP[MAX_IP_LENGTH];
  WORD wdPort;
  GameZone_t gameZone;
  union{
    DWORD accid;
    DWORD uid;
  };
  BYTE state;
  //BYTE type;
  DWORD type;
  union{
    char name[48];
    char account[48];
  };
  char passwd[MAX_PASSWORD];
  ZES_cblock des_key;//des密钥
  char client_ip[MAX_IP_LENGTH];
  char numpasswd[MAX_NUMPASSWORD];

  t_NewLoginSession()
  {
    //wdLoginID = 0;
    //wdGatewayID = 0;
    //loginTempID = 0;
    //bzero(pstrIP,sizeof(pstrIP));
    //wdPort = 0;
    //accid = 0;
    //state = 0;
    //type = 0;
    //bzero(name,sizeof(name));
    //bzero(passwd,sizeof(passwd));
    bzero(numpasswd,sizeof(numpasswd));
  }
  t_NewLoginSession(const t_NewLoginSession& session)
  {
    wdLoginID = session.wdLoginID;
    wdGatewayID = session.wdGatewayID;
    loginTempID = session.loginTempID;
    bcopy(session.pstrIP,pstrIP,sizeof(pstrIP),sizeof(pstrIP));
    wdPort = session.wdPort;
    gameZone = session.gameZone;
    accid = session.accid;
    state = session.state;
    type = session.type;
    bcopy(session.name,name,sizeof(name),sizeof(name));
    bcopy(session.passwd,passwd,sizeof(passwd),sizeof(passwd));
    bcopy(session.des_key,des_key,sizeof(des_key),sizeof(des_key));
    bcopy(session.client_ip,client_ip,sizeof(client_ip),sizeof(client_ip));
    bcopy(session.numpasswd,numpasswd,sizeof(numpasswd),sizeof(numpasswd));
  }
  t_NewLoginSession & operator= (const t_NewLoginSession &session)
  {
    wdLoginID = session.wdLoginID;
    wdGatewayID = session.wdGatewayID;
    loginTempID = session.loginTempID;
    bcopy(session.pstrIP,pstrIP,sizeof(pstrIP),sizeof(pstrIP));
    wdPort = session.wdPort;
    gameZone = session.gameZone;
    accid = session.accid;
    state = session.state;
    type = session.type;
    bcopy(session.name,name,sizeof(name),sizeof(name));
    bcopy(session.passwd,passwd,sizeof(passwd),sizeof(passwd));
    bcopy(session.des_key,des_key,sizeof(des_key),sizeof(des_key));
    bcopy(session.client_ip,client_ip,sizeof(client_ip),sizeof(client_ip));
    bcopy(session.numpasswd,numpasswd,sizeof(numpasswd),sizeof(numpasswd));
    return *this;
  }
};

namespace Cmd
{
  const BYTE CMD_NULL = 0;    /**< 空的指令 */
  const BYTE PARA_NULL = 0;  /**< 空的指令参数 */

  /**
   * \brief 空操作指令，测试信号和对时间指令
   *
   */
  struct t_NullCmd
  {
    BYTE cmd;          /**< 指令代码 */
    BYTE para;          /**< 指令代码子编号 */
    /**
     * \brief 构造函数
     *
     */
    t_NullCmd(const BYTE cmd = CMD_NULL,const BYTE para = PARA_NULL) : cmd(cmd),para(para) {};
  };
};

/**
 * \brief 定义服务器信息采集指令
 */

namespace Cmd
{
  namespace Info
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_INFO = 2;
    const BYTE CMD_GMTOOL = 3;

    ///////////////////////////////////////
    ///登入服务器指令
    //////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginCmd : t_NullCmd
    {
      char strIP[MAX_IP_LENGTH];
      WORD port;

      t_LoginCmd() : t_NullCmd(CMD_LOGIN,PARA_LOGIN) { }
    };
    const BYTE PARA_LOGIN_OK = 2;
    struct t_LoginCmd_OK : t_NullCmd
    {
      GameZone_t gameZone;
      char name[MAX_NAMESIZE];
      BYTE netType;

      t_LoginCmd_OK()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN_OK) {};
    };
    ///////////////////////////////////////
    ///登入服务器指令
    ///////////////////////////////////////

        //////////////////////////////////////
    //请求服务器信息
    const BYTE PARA_REQUEST_SERVERINFO = 1;
    struct t_Request_ServerInfo : t_NullCmd
    {
      QWORD     rTimestamp;              //请求时间戳

      t_Request_ServerInfo() : t_NullCmd(CMD_INFO,PARA_REQUEST_SERVERINFO) { }
    };
    //服务器信息
    const BYTE PARA_SERVERINFO = 2;
    struct t_ServerInfo : t_NullCmd
    {
      QWORD     rTimestamp;              //请求时间戳
      WORD       ServerID;              //服务器编号
      WORD       ServerType;              //服务器类型
      GameZone_t  GameZone;              //游戏区编号
      char       ZoneName[MAX_NAMESIZE];      //游戏区名字
      DWORD     ConnNum;                //连接数
      char       xml[1];

      t_ServerInfo() : t_NullCmd(CMD_INFO,PARA_SERVERINFO)
      {
        xml[0] = '\0';
      }
    };
    //////////////////////////////////////
    ///服务器信息指令
    //////////////////////////////////////

    //请求在线人数信息
    const BYTE PARA_REQUEST_ONLINENUM = 3;
    struct t_Request_OnlineNum : t_NullCmd
    {
      QWORD      rTimestamp;
      
      t_Request_OnlineNum() : t_NullCmd(CMD_INFO,PARA_REQUEST_ONLINENUM) { }
    };
    //区的总人数
    const BYTE PARA_ONLINENUM =4;
    struct t_OnlineNum : t_NullCmd
    {
      QWORD      rTimestamp;
      WORD      ServerID;
      WORD      ServerType;
      GameZone_t    GameZone;
      char      ZoneName[MAX_NAMESIZE];
      DWORD      OnlineNum;
      
      t_OnlineNum() : t_NullCmd(CMD_INFO,PARA_ONLINENUM) { }  
    };
    //区中每个国家的人数
    const BYTE PARA_COUNTRY_ONLINENUM = 5;
    struct t_Country_OnlineNum : t_NullCmd
    {
      QWORD      rTimestamp;
      GameZone_t    GameZone;
      DWORD      OnlineNum;
      struct Online
      {
        DWORD country;
        DWORD num;
      }
      CountryOnline[0];

      t_Country_OnlineNum() : t_NullCmd(CMD_INFO,PARA_COUNTRY_ONLINENUM)
      {
        OnlineNum = 0;
      }
    };
  };
};

/**
 * \brief 定义统一用户平台登陆服务器指令
 */

namespace Cmd
{
  namespace FL
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_GYLIST = 2;
    const BYTE CMD_SESSION = 3;


    //////////////////////////////////////////////////////////////
    /// 登陆FL服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginFL : t_NullCmd
    {
      char strIP[MAX_IP_LENGTH];
      WORD port;

      t_LoginFL()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };

    const BYTE PARA_LOGIN_OK = 2;
    struct t_LoginFL_OK : t_NullCmd
    {
      GameZone_t gameZone;
      char name[MAX_NAMESIZE];
      BYTE netType;

      t_LoginFL_OK()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN_OK) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆FL服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 定义网关信息相关指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_FL_GYLIST = 1;
    struct t_GYList_FL : t_NullCmd
    {
      WORD wdServerID;      /**< 服务器编号 */
      char pstrIP[MAX_IP_LENGTH];  /**< 服务器地址 */
      WORD wdPort;        /**< 服务器端口 */
      WORD wdNumOnline;      /**< 网关在线人数 */
      int  state;          /**< 服务器状态 */
      DWORD zoneGameVersion;
      t_GYList_FL()
        : t_NullCmd(CMD_GYLIST,PARA_FL_GYLIST) {};
    };

    const BYTE PARA_FL_RQGYLIST = 2;
    struct t_RQGYList_FL : t_NullCmd
    {
      t_RQGYList_FL()
        : t_NullCmd(CMD_GYLIST,PARA_FL_RQGYLIST) {};
    };
    //////////////////////////////////////////////////////////////
    /// 定义网关信息相关指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 定义与登陆session相关指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_SESSION_NEWSESSION = 1;
    struct t_NewSession_Session : t_NullCmd
    {
      t_NewLoginSession session;

      t_NewSession_Session()
        : t_NullCmd(CMD_SESSION,PARA_SESSION_NEWSESSION) {};
    };

    const BYTE PARA_SESSION_IDINUSE = 2;
    struct t_idinuse_Session : t_NullCmd
    {
      DWORD accid;
      DWORD loginTempID;
      WORD wdLoginID;
      char name[48];

      t_idinuse_Session()
        : t_NullCmd(CMD_SESSION,PARA_SESSION_IDINUSE) { bzero(name,sizeof(name)); };
    };
    //////////////////////////////////////////////////////////////
    /// 定义与登陆session相关指令
    //////////////////////////////////////////////////////////////
  };
};

/**
 * \brief 定义管理服务器的指令
 */

namespace Cmd
{

  namespace Super
  {
    const BYTE CMD_STARTUP  = 1;
    const BYTE CMD_BILL    = 3;
    const BYTE CMD_GATEWAY  = 4;
    //const BYTE CMD_GMTOOL  = 5;
    const BYTE CMD_SESSION  = 5;
    const BYTE CMD_COUNTRYONLINE  = 166;


    //////////////////////////////////////////////////////////////
    // 定义启动相关指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_STARTUP_REQUEST = 1;
    struct t_Startup_Request : t_NullCmd
    {
      WORD wdServerType;
      char pstrIP[MAX_IP_LENGTH];
      t_Startup_Request()
        : t_NullCmd(CMD_STARTUP,PARA_STARTUP_REQUEST) {};
    };

    const BYTE PARA_STARTUP_RESPONSE = 2;
    struct t_Startup_Response : t_NullCmd
    {
      WORD wdServerID;
      char pstrIP[MAX_IP_LENGTH];
      WORD wdPort;
      t_Startup_Response()
        : t_NullCmd(CMD_STARTUP,PARA_STARTUP_RESPONSE) {};
    };

    struct ServerEntry
    {


      WORD wdServerID;




      WORD wdServerType;
      char pstrIP[MAX_IP_LENGTH];
      WORD wdPort;
      WORD state;
      ServerEntry()
      {
        wdServerID = 0;
        wdServerType = 0;
        bzero(pstrIP,sizeof(pstrIP));
        wdPort = 0;
        state = 0;
      }
      ServerEntry(const ServerEntry& se)
      {
        wdServerID = se.wdServerID;
        wdServerType = se.wdServerType;
        strcpy_s(pstrIP,se.pstrIP);
        wdPort = se.wdPort;
        state = se.state;
      }
      ServerEntry & operator= (const ServerEntry &se)
      {
        wdServerID = se.wdServerID;
        wdServerType = se.wdServerType;
        strcpy_s(pstrIP,se.pstrIP);
        wdPort = se.wdPort;
        state = se.state;
        return *this;
      }

	  
	   operator int() const 
	  {
		return (int)wdServerID;
      }


    };
    const BYTE PARA_STARTUP_SERVERENTRY_NOTIFYME = 3;
    struct t_Startup_ServerEntry_NotifyMe : t_NullCmd
    {
      WORD size;
      ServerEntry entry[1];
      t_Startup_ServerEntry_NotifyMe()
        : t_NullCmd(CMD_STARTUP,PARA_STARTUP_SERVERENTRY_NOTIFYME),size(0) {};
    };
    const BYTE PARA_STARTUP_SERVERENTRY_NOTIFYOTHER = 4;
    struct t_Startup_ServerEntry_NotifyOther : t_NullCmd
    {
      WORD srcID;
      ServerEntry entry;
      t_Startup_ServerEntry_NotifyOther()
        : t_NullCmd(CMD_STARTUP,PARA_STARTUP_SERVERENTRY_NOTIFYOTHER) {};
    };

    const BYTE PARA_STARTUP_OK = 5;
    struct t_Startup_OK : t_NullCmd
    {
      WORD wdServerID;
      t_Startup_OK()
        : t_NullCmd(CMD_STARTUP,PARA_STARTUP_OK) {};
    };

    const BYTE PARA_GAMETIME = 6;
    struct t_GameTime : t_NullCmd
    {
      QWORD qwGameTime;
      t_GameTime()
        : t_NullCmd(CMD_STARTUP,PARA_GAMETIME) {};
    };

    const BYTE PARA_RESTART_SERVERENTRY_NOTIFYOTHER = 9;
    struct t_restart_ServerEntry_NotifyOther : t_NullCmd
    {
      WORD srcID;
      WORD dstID;
      t_restart_ServerEntry_NotifyOther()
        : t_NullCmd(CMD_STARTUP,PARA_RESTART_SERVERENTRY_NOTIFYOTHER) {};
    };
    //////////////////////////////////////////////////////////////
    // 定义启动相关指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    // 定义管理服务器与计费服务器交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_BILL_NEWSESSION = 1;
    struct t_NewSession_Bill : t_NullCmd
    {
      t_NewLoginSession session;

      t_NewSession_Bill()
        : t_NullCmd(CMD_BILL,PARA_BILL_NEWSESSION) {};
    };

    const BYTE PARA_BILL_IDINUSE = 2;
    struct t_idinuse_Bill : t_NullCmd
    {
      DWORD accid;
      DWORD loginTempID;
      WORD wdLoginID;
      char name[48];

      t_idinuse_Bill()
        : t_NullCmd(CMD_BILL,PARA_BILL_IDINUSE) { bzero(name,sizeof(name)); };
    };
    //////////////////////////////////////////////////////////////
    // 定义管理服务器与计费服务器交互的指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    // 定义管理服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_GATEWAY_GYLIST = 1;
    struct t_GYList_Gateway : t_NullCmd
    {
      WORD wdServerID;      /**< 服务器编号 */
      char pstrIP[MAX_IP_LENGTH];  /**< 服务器地址 */
      WORD wdPort;        /**< 服务器端口 */
      WORD wdNumOnline;      /**< 网关在线人数 */
      int  state;          /**< 服务器状态 */
      DWORD zoneGameVersion;
      t_GYList_Gateway()
        : t_NullCmd(CMD_GATEWAY,PARA_GATEWAY_GYLIST) {};
    };

    const BYTE PARA_GATEWAY_RQGYLIST = 2;
    struct t_RQGYList_Gateway : t_NullCmd
    {
      t_RQGYList_Gateway()
        : t_NullCmd(CMD_GATEWAY,PARA_GATEWAY_RQGYLIST) {};
    };

    const BYTE PARA_GATEWAY_NEWSESSION = 3;
    struct t_NewSession_Gateway : t_NullCmd
    {
      t_NewLoginSession session;

      t_NewSession_Gateway()
        : t_NullCmd(CMD_GATEWAY,PARA_GATEWAY_NEWSESSION) {};
    };

    const WORD ROLEREG_STATE_TEST    = 1;  //测试
    const WORD ROLEREG_STATE_WRITE    = 2;  //回写
    const WORD ROLEREG_STATE_CLEAN    = 4;  //清除
    const WORD ROLEREG_STATE_HAS    = 8;  //测试有
    const WORD ROLEREG_STATE_OK      = 16;  //清除或回写成功

    const BYTE PARA_CHARNAME_GATEWAY = 4;
    struct t_Charname_Gateway : t_NullCmd
    {
      WORD wdServerID;      /**< 服务器编号 */
      DWORD accid;        /**< 账号编号 */
      char name[MAX_NAMESIZE];  /**< 角色名称 */
      WORD state;          /**< 上面各种状态的位组合 */

      t_Charname_Gateway()
        :t_NullCmd(CMD_GATEWAY,PARA_CHARNAME_GATEWAY) { }
    };

	const BYTE PARA_NOTIFYGATE_FINISH = 5;
	struct t_notifyFinish_Gateway : t_NullCmd
	{
      t_notifyFinish_Gateway()
        :t_NullCmd(CMD_GATEWAY,PARA_NOTIFYGATE_FINISH) { }
	};
    //////////////////////////////////////////////////////////////
    // 定义管理服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////
    ///国家在线人数相关指令
    //////////////////////////////////////
    //请求国家在线人数信息
    const BYTE PARA_REQUEST_COUNTRYONLINE = 0;
    struct t_Request_CountryOnline : t_NullCmd
    {
      QWORD     rTimestamp;              //请求时间戳
      DWORD    infoTempID;
      t_Request_CountryOnline()
        : t_NullCmd(CMD_COUNTRYONLINE,PARA_REQUEST_COUNTRYONLINE) {};
    };
    //国家在线人数信息
    const BYTE PARA_COUNTRYONLINE = 1;
    struct t_CountryOnline : t_NullCmd
    {
      QWORD     rTimestamp;              //请求时间戳
      DWORD    infoTempID;
      DWORD    OnlineNum;
      struct Online
      {
        DWORD country;
        DWORD num;
      }
      CountryOnline[0];

      t_CountryOnline() : t_NullCmd(CMD_COUNTRYONLINE,PARA_COUNTRYONLINE)
      {
        OnlineNum = 0;
      }
    };
    //////////////////////////////////////
    ///国家在线人数相关指令
    //////////////////////////////////////
    //请求国家在线人数信息
    
    const BYTE PARA_SHUTDOWN =1;
    struct t_shutdown_Super : t_NullCmd
    {
      t_shutdown_Super(): t_NullCmd(CMD_SESSION,PARA_SHUTDOWN)
      {
      }
    };
  };

};

/**
 * \brief 定义档案服务器相关指令
 */

namespace Cmd
{

  namespace Record
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_GATE = 2;
    const BYTE CMD_SCENE = 3;
    const BYTE CMD_SESSION = 4;

    //////////////////////////////////////////////////////////////
    /// 登陆档案服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginRecord : t_NullCmd
    {
      WORD wdServerID;
      WORD wdServerType;
      t_LoginRecord()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆档案服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 档案服务器和网关交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_GATE_GET_SELECTINFO = 1;
    struct t_Get_SelectInfo_GateRecord : t_NullCmd
    {
		DWORD accid;          /// 账号
		DWORD countryid;      /// [ranqd] add 服务器id
      t_Get_SelectInfo_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_GET_SELECTINFO) {};
    };

    const BYTE PARA_GATE_RET_SELECTINFO = 2;
    struct t_Ret_SelectInfo_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      WORD num;              /// 有效角色信息计数
      SelectUserInfo info[MAX_CHARINFO];  /// 角色信息列表
      t_Ret_SelectInfo_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_RET_SELECTINFO)
        {
          num = 0;
          bzero(info,sizeof(info));
        }
    };

    const BYTE PARA_GATE_CREATECHAR = 3;
    struct t_CreateChar_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      char  name[MAX_NAMESIZE+1];    /// 角色名称
	  WORD	JobType;			//[shx Add 职业]
	  WORD  Face;            /// [shx Add 头像]
      WORD  type;            /// 角色类型
      DWORD hair;            /// 角色发型以及颜色
      WORD country;        /// 国家ID
      WORD five;          /// 五行主属性
      char mapName[MAX_NAMESIZE];  /**< 用户地图名字  */
      DWORD createip;        /// 创建角色时的ip
      t_CreateChar_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_CREATECHAR) {};
    };

    const BYTE PARA_GATE_CREATECHAR_RETURN = 4;
    struct t_CreateChar_Return_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      BYTE retcode;            /// 返回代码，0表示失败，角色名称重复，1表示创建角色成功
      SelectUserInfo charinfo;      /// 角色信息
      DWORD dwFace;          // 角色脸型
      t_CreateChar_Return_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_CREATECHAR_RETURN) {};
    };

    const BYTE PARA_GATE_DELCHAR = 5;
    struct t_DelChar_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      DWORD id;              /// 角色编号
	  DWORD countryid;       // 国家编号，用于返回剩余角色使用
      char name[MAX_NAMESIZE+1];
      t_DelChar_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_DELCHAR) {};
    };

    const BYTE PARA_GATE_DELCHAR_RETURN = 6;
    struct t_DelChar_Return_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      DWORD id;              /// 角色编号
      BYTE retcode;            /// 返回代码，0表示删除角色失败，1表示删除角色成功
      char name[MAX_NAMESIZE+1];
      t_DelChar_Return_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_DELCHAR_RETURN) {};
    };

    const BYTE PARA_GATE_CHECKNAME = 7;
    struct t_CheckName_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      char name[MAX_NAMESIZE+1];
      t_CheckName_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_CHECKNAME) {};
    };

    const BYTE PARA_GATE_CHECKNAME_RETURN = 8;
    struct t_CheckName_Return_GateRecord : t_NullCmd
    {
      DWORD accid;            /// 账号
      BYTE err_code;            /// 返回代码 0: 可以使用 1:角色名重复
      char name[MAX_NAMESIZE+1];
      t_CheckName_Return_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_CHECKNAME_RETURN) {};
    };
    /// 请求国家档案人数排序
    const BYTE REQUEST_GATE_COUNTRY_ORDER = 9;
    struct t_request_Country_GateRecord : t_NullCmd
    {
      t_request_Country_GateRecord()
        : t_NullCmd(CMD_GATE,REQUEST_GATE_COUNTRY_ORDER) {};
    };
    struct CountrOrder
    {
      DWORD size;          //数量
      struct {
      DWORD country;        //国家  
      DWORD count;    //已经排序好的国家id
      } order[0];
    };
    /// 国家档案人数排序
    const BYTE PARA_GATE_COUNTRY_ORDER = 10;
    struct t_order_Country_GateRecord : t_NullCmd
    {
      DWORD dwID;          //用户id
      CountrOrder order;      //排序的国家 
      t_order_Country_GateRecord()
        : t_NullCmd(CMD_GATE,PARA_GATE_COUNTRY_ORDER) {};
    };
    //////////////////////////////////////////////////////////////
    /// 档案服务器和网关交互的指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 档案服务器和场景交互的指令
    //////////////////////////////////////////////////////////////
#define PARA_SCENE_USER_READ_ERROR -1
    const BYTE PARA_SCENE_USER_READ = 1;
    struct t_ReadUser_SceneRecord : t_NullCmd
    {
      DWORD accid;
      DWORD id;            /// 角色
      DWORD dwMapTempID;        /// 地图临时ID
	  BYTE RegMapType;			/// sky
      t_ReadUser_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USER_READ) {};
    };

    enum WriteBack_Type
    {
      TIMETICK_WRITEBACK,/// 定时回写档案
      LOGOUT_WRITEBACK,/// 退出回写档案
      CHANGE_SCENE_WRITEBACK,//切换场景时回写档案
      OPERATION_WRITEBACK,/// 操作回写档案
    };
    const BYTE PARA_SCENE_USER_WRITE = 2;
    struct t_WriteUser_SceneRecord : t_NullCmd
    {
      DWORD accid;
      DWORD id;              /// 角色
      DWORD dwMapTempID;          /// 地图临时ID
      DWORD writeback_type;        /// 回写档案类型
      CharBase    charbase;        ///存档的基本信息
      DWORD      dataSize;        ///存档二进制的大小
      char        data[0];        ///存档的二进制数据
      t_WriteUser_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USER_WRITE)
        {
          bzero(&charbase,sizeof(charbase));
          dataSize = 0;
        }
    };

    const BYTE PARA_SCENE_USERINFO = 3;
    struct t_UserInfo_SceneRecord : t_NullCmd
    {
      DWORD id;              /// 角色
      DWORD dwMapTempID;          /// 地图临时ID
	  BYTE	RegMapType;				/// sky
      CharBase    charbase;        ///存档的基本信息
      DWORD      dataSize;        ///存档二进制的大小
      char        data[0];        ///存档的二进制数据
      t_UserInfo_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USERINFO)
        {
          bzero(&charbase,sizeof(charbase));
          dataSize = 0;
        }
    };

    //删除档案服务器用户数据,如果新用户注册后档案服务器未返回而收到退出指令时需要使用
    const BYTE PARA_SCENE_USER_REMOVE = 4;
    struct t_RemoveUser_SceneRecord : t_NullCmd
    {
      DWORD accid;
      DWORD id;
      t_RemoveUser_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USER_REMOVE)
        {
        }
    };

    //检查用户是否存在
    const BYTE PARA_SCENE_USER_EXIST = 5;
    struct t_userExist_SceneRecord : t_NullCmd
    {
      DWORD fromID;//临时ID
      DWORD toID;
      Cmd::stSendMail sm;
      t_userExist_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USER_EXIST)
        {
          fromID = 0;
          toID = 0;
          bzero(&sm,sizeof(sm));
        }
    };
    const BYTE PARA_SCENE_USER_WRITE_OK = 6;
    struct t_WriteUser_SceneRecord_Ok : t_NullCmd
    {
      DWORD type;            /// 卸载类型
      DWORD accid;
      DWORD id;            /// 角色
      t_WriteUser_SceneRecord_Ok()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_USER_WRITE_OK) {};
    };

#ifdef _TEST_DATA_LOG
    enum enumWriteBackTest_Type
    {
      NEWCHAR_WRITEBACK,//新角色插入
      LEVELUP_WRITEBACK,//升级
      DEATH_WRITEBACK,//死亡
      HP_WRITEBACK,//HP
      MP_WRITEBACK,//MP
      SP_WRITEBACK,//SP
    };
    const BYTE PARA_SCENE_INSERT_CHARTEST = 4;
    struct t_Insert_CharTest_SceneRecord : t_NullCmd
    {
      char name[MAX_NAMESIZE];        /// 角色名称
      DWORD level;              /// 角色等级
      CharTest    chartest;        ///存档数据
      t_Insert_CharTest_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_INSERT_CHARTEST)
        {
          bzero(&chartest,sizeof(chartest));
        }
    };
    const BYTE PARA_SCENE_UPDATE_CHARTEST = 5;
    struct t_Update_CharTest_SceneRecord : t_NullCmd
    {
      char name[MAX_NAMESIZE];        /// 角色名称
      DWORD level;              /// 角色等级
      CharTest    chartest;        ///存档数据
      t_Update_CharTest_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_UPDATE_CHARTEST)
        {
          bzero(&chartest,sizeof(chartest));
        }
    };
    const BYTE PARA_SCENE_DELETE_CHARTEST = 6;
    struct t_Delete_CharTest_SceneRecord : t_NullCmd
    {
      char name[MAX_NAMESIZE];        /// 角色名称
      DWORD level;              /// 角色等级
      t_Delete_CharTest_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_DELETE_CHARTEST)
        {
        }
    };
    const BYTE PARA_SCENE_READ_CHARTEST = 7;
    struct t_Read_CharTest_SceneRecord : t_NullCmd
    {
      char name[MAX_NAMESIZE];        /// 角色名称
      DWORD level;              /// 角色等级
      CharTest    chartest;        ///存档数据
      t_Read_CharTest_SceneRecord()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_READ_CHARTEST)
        {
          bzero(&chartest,sizeof(chartest));
        }
    };
#endif

    //////////////////////////////////////////////////////////////
    /// 档案服务器和场景交互的指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    /// 档案服务器和会话交互的指令开始
    //////////////////////////////////////////////////////////////
    //检查用户是否存在
    const BYTE PARA_CHK_USER_EXIST = 1;
    struct t_chkUserExist_SessionRecord : t_NullCmd
    {
      char  name[MAX_NAMESIZE+1];    /// 角色名称
      DWORD user_id;          /// 推荐人ID
      DWORD  from_id;          /// 被推荐人ID
      DWORD user_level;        /// 推荐人等级

      t_chkUserExist_SessionRecord()
        : t_NullCmd(CMD_SESSION,PARA_CHK_USER_EXIST)
        {
          bzero(name,sizeof(name));
          user_id = 0;
          user_level = 0;
          from_id = 0;
        }
    };

    //////////////////////////////////////////////////////////////
    /// 档案服务器和会话交互的指令结束
    //////////////////////////////////////////////////////////////

  };

};

/**
 * \brief 定义小游戏服务器相关指令
 */

namespace Cmd
{
  namespace Mini
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_GATE = 2;
    const BYTE CMD_FORWARD = 3;
    const BYTE CMD_SCENE = 4;

    //////////////////////////////////////////////////////////////
    /// 登陆小游戏服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginMini : t_NullCmd
    {
      WORD wdServerID;
      WORD wdServerType;
      t_LoginMini()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆小游戏服务器指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 场景服务器和Mini交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_SCENE_SET_SCENE = 1;
    struct t_Scene_SetScene : t_NullCmd
    {
      DWORD userID;
      WORD serverID;
      t_Scene_SetScene()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SET_SCENE) {};
    };

    const BYTE PARA_SCENE_DEPOSIT = 2;
    struct t_Scene_Deposit : t_NullCmd
    {
      DWORD userID;
      DWORD num;
      t_Scene_Deposit()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_DEPOSIT) {};
    };

    const BYTE PARA_SCENE_DEPOSIT_RET = 3;
    struct t_Scene_Deposit_Ret : t_NullCmd
    {
      DWORD userID;
      BYTE ret;
      t_Scene_Deposit_Ret()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_DEPOSIT_RET) {};
    };

    const BYTE PARA_SCENE_CHECK_DRAW = 4;
    struct t_Scene_Check_Draw : t_NullCmd
    {
      DWORD userID;
      DWORD num;
      t_Scene_Check_Draw()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CHECK_DRAW) {};
    };

    const BYTE PARA_SCENE_DRAW_RET = 5;
    struct t_Scene_Draw_Ret : t_NullCmd
    {
      DWORD userID;
      DWORD num;
      DWORD ret;//0失败 1成功 2玩家不在线
      t_Scene_Draw_Ret()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_DRAW_RET) {};
    };

    //////////////////////////////////////////////////////////////
    /// 场景服务器和Mini交互的指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 小游戏服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_GATE_USER_LOGIN = 1;
    struct t_UserLogin_Gateway : t_NullCmd
    {
      t_UserLogin_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_USER_LOGIN) {};
      DWORD userID;
      char name[MAX_NAMESIZE];
      WORD countryID;
      WORD face;
      WORD gateServerID;
      WORD sceneServerID;
    };

    const BYTE PARA_GATE_USER_LOGOUT = 2;
    struct t_UserLogout_Gateway : t_NullCmd
    {
      t_UserLogout_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_USER_LOGOUT) {};
      DWORD userID;
    };

    const BYTE PARA_GATE_USER_DELETE = 3;
    struct t_UserDelete_Gateway : t_NullCmd
    {
      t_UserDelete_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_USER_DELETE) {};
      DWORD userID;
    };
    //////////////////////////////////////////////////////////////
    /// 小游戏服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    /// 服务器转发指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_MINI_FORWARD_USER = 1;
    struct t_Mini_ForwardUser : t_NullCmd
    {
      DWORD id;
      WORD  size;
      BYTE  data[0];
      t_Mini_ForwardUser()
        : t_NullCmd(CMD_FORWARD,PARA_MINI_FORWARD_USER) {};
    };

    const BYTE PARA_USER_FORWARD_MINI = 2;
    struct t_Mini_UserForwardMini : t_NullCmd
    {
      DWORD id;
      WORD  size;
      BYTE  data[0];
      t_Mini_UserForwardMini()
        : t_NullCmd(CMD_FORWARD,PARA_USER_FORWARD_MINI) {};
    };

    const BYTE PARA_FORWARD_MINI_TO_SCENE = 3;
    struct t_Mini_ForwardMiniToScene : t_NullCmd
    {
      DWORD id;
      WORD  size;
      BYTE  data[0];
      t_Mini_ForwardMiniToScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_MINI_TO_SCENE) {};
    };

    const BYTE PARA_FORWARD_SCENE_TO_MINI = 4;
    struct t_Scene_ForwardMini : t_NullCmd
    {
      DWORD id;
      WORD  size;
      BYTE  data[0];
      t_Scene_ForwardMini()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_SCENE_TO_MINI) {};
    };
  };

};

namespace Cmd
{ 

//BEGIN_ONE_CMD
//////////////////////////////////////////////////////////////
/// 定义小游戏命令开始
//////////////////////////////////////////////////////////////

struct stMiniGameUserCmd : public stNullUserCmd
{
  stMiniGameUserCmd()
  {
    byCmd = MINIGAME_USERCMD;
    subParam = 0;
  }
  BYTE subParam;
};

/*公共指令开始***************************************/

enum MiniGameType
{
  DOUDIZHU  = 1,
  CAISHUZI  = 2,
  MAX_GAMETYPE
};

struct MiniUserPosition
{
  BYTE type;
  BYTE room;
  BYTE game;
  BYTE seat;

  MiniUserPosition(DWORD t=0,DWORD r=0,DWORD g=0,DWORD s=0):type(t),room(r),game(g),seat(s){}
  MiniUserPosition(const MiniUserPosition &p):type(p.type),room(p.room),game(p.game),seat(p.seat){}
  MiniUserPosition & operator =(const MiniUserPosition &p)
  {
    type = p.type;
    room = p.room;
    game = p.game;
    seat = p.seat;
    return *this;
  }
  bool operator ==(const MiniUserPosition &p)
  {
    return type==p.type && room==p.room && game==p.game && seat==p.seat;
  }

  DWORD roomID() const{return (type<<24)+(room<<16);}
  DWORD gameID() const{return (type<<24)+(room<<16)+(game<<8);}
  DWORD id() const{return (type<<24)+(room<<16)+(game<<8)+seat;}
};

typedef MiniUserPosition MiniGameID;
typedef MiniUserPosition MiniRoomID;
typedef MiniUserPosition MiniSeatID;

struct MiniGameScore
{
  BYTE gameType;
  DWORD win;
  DWORD lose;
  DWORD draw;
  int score;
  int money;

  MiniGameScore():gameType(0),win(0),lose(0),draw(0),score(0),money(0){}
  MiniGameScore & operator=(const MiniGameScore &s)
  {
    win = s.win;
    lose = s.lose;
    draw = s.draw;
    score = s.score;
    money = s.money;
    return *this;
  }

  MiniGameScore & operator+=(const MiniGameScore &s)
  {
    win += s.win;
    lose += s.lose;
    draw += s.draw;
    score += s.score;
    money += s.money;
    return *this;
  }
  bool operator==(const MiniGameScore &s) const
  {
    return score==s.score && win==s.win && draw==s.draw && lose==s.lose;
  }
  bool operator<(const MiniGameScore &s) const
  {
    if (score==s.score)
      if (win==s.win)
        if (draw==s.draw)
          return lose>s.lose;
        else
          return draw<s.draw;
      else
        return win<s.win;
    else
      return score<s.score;
  }
  bool operator>(const MiniGameScore &s) const
  {
    return !(*this==s) && !(*this<s);
  }
};

enum MiniGameState
{
  MGS_PREPARE = 1,
  MGS_PLAY    = 2
};

#define COMMON_MINI_PARA 1
struct stCommonMiniGameCmd : public stMiniGameUserCmd
{
  stCommonMiniGameCmd() : stMiniGameUserCmd()
  {
    byParam = COMMON_MINI_PARA;
  }
};

/*
#define INVIT_COMMON_MINI_PARA 1
struct stInvitCommonMiniGameCmd : public stCommonMiniGameCmd
{
stInvitCommonMiniGameCmd() : stCommonMiniGameCmd()
{
subParam = INVIT_COMMON_MINI_PARA;
}
DWORD tempID;//被邀请者/邀请者 临时ID
DWORD gameID;//游戏类型
};

#define INVIT_RET_COMMON_MINI_PARA 2
struct stInvitRetCommonMiniGameCmd : public stCommonMiniGameCmd
{
stInvitRetCommonMiniGameCmd() : stCommonMiniGameCmd()
{
subParam = INVIT_RET_COMMON_MINI_PARA;
}
DWORD tempid;//邀请者临时ID
BYTE ret;//0:不同意 1:同意 2:屏蔽
};
*/

#define LOGIN_COMMON_MINI_PARA 3
struct stLoginCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stLoginCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = LOGIN_COMMON_MINI_PARA;
  }
  DWORD ret;//参数/登陆是否成功
};

#define LOGOUT_COMMON_MINI_PARA 4
struct stLogoutCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stLogoutCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = LOGOUT_COMMON_MINI_PARA;
  }
};

struct MiniRoomData
{
  MiniRoomID roomID;
  WORD gameNum;
  WORD oneGameUserNum;
  DWORD userNum;
  DWORD money;//游戏币基数
};
//房间列表
#define GAME_LIST_COMMON_MINI_PARA 5
struct stGameListCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stGameListCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = GAME_LIST_COMMON_MINI_PARA;
  }
  DWORD num;//房间数量
  MiniRoomData data[0];
};

//进入房间
#define ENTER_ROOM_COMMON_MINI_PARA 6
struct stEnterRoomCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stEnterRoomCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ENTER_ROOM_COMMON_MINI_PARA;
  }
  MiniRoomID roomID;//房间号
};

enum MiniUserState
{
  MUS_NOTPLAY  = 0,
  MUS_HALL  = 1,
  MUS_ROOM  = 2,
  MUS_SEAT  = 3,
  MUS_READY  = 4,
  MUS_PLAY  = 5
};
struct MiniUserData
{
  DWORD id;
  char name[MAX_NAMESIZE];
  WORD face;//头像
  DWORD countryID;
  MiniUserPosition pos;
  BYTE state;
  MiniGameScore score;
  MiniUserData():id(0),face(0),countryID(0),state(0){bzero(name,MAX_NAMESIZE);}
  MiniUserData(const MiniUserData &d)
  {
    id = d.id;
    strcpy_s(name,d.name);
    face = d.face;
    countryID = d.countryID;
    pos = d.pos;
    state = d.state;
    score = d.score;
  }

  MiniUserData & operator=(const MiniUserData &d)
  {
    id = d.id;
    strcpy_s(name,d.name);
    face = d.face;
    countryID = d.countryID;
    pos = d.pos;
    state = d.state;
    score = d.score;
    return *this;
  }
};
//添加/更新房间玩家列表
#define ADD_ROOM_USER_COMMON_MINI_PARA 7
struct stAddRoomUserCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stAddRoomUserCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ADD_ROOM_USER_COMMON_MINI_PARA;
    num = 0;
  }
  MiniRoomID roomID;
  DWORD num;
  MiniUserData data[0];
};
//添加/更新一个房间玩家列表
#define ADD_ONE_ROOM_USER_COMMON_MINI_PARA 7
struct stAddOneRoomUserCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stAddOneRoomUserCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ADD_ONE_ROOM_USER_COMMON_MINI_PARA;
    num = 1;
  }
  MiniRoomID roomID;
  DWORD num;
  MiniUserData data;
};

struct MiniSeatData
{
  MiniSeatID seatID;
  BYTE state;//0关闭 1打开
  BYTE isHost;//0否 1是 
};
//刷新座位开关状态
#define SEAT_STATE_COMMON_MINI_PARA 8
struct stSeatStateCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stSeatStateCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = SEAT_STATE_COMMON_MINI_PARA;
    num = 0;
  }
  DWORD num;
  MiniSeatData data[0];
};
//刷新一个座位开关状态
#define ONE_SEAT_STATE_COMMON_MINI_PARA 8
struct stOneSeatStateCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stOneSeatStateCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ONE_SEAT_STATE_COMMON_MINI_PARA;
    num = 1;
  }
  DWORD num;
  MiniSeatData data;
};

//离开房间
#define LEAVE_ROOM_COMMON_MINI_PARA 9
struct stLeaveRoomCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stLeaveRoomCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = LEAVE_ROOM_COMMON_MINI_PARA;
  }
  MiniRoomID roomID;
};

//坐桌子
#define ENTER_GAME_COMMON_MINI_PARA 10
struct stEnterGameCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stEnterGameCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ENTER_GAME_COMMON_MINI_PARA;
  }
  MiniSeatID seatID;//座位号
};

/*
//添加/更新游戏玩家列表
#define ADD_GAME_USER_COMMON_MINI_PARA 11
struct stAddGameUserCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stAddGameUserCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ADD_GAME_USER_COMMON_MINI_PARA;
    num = 0;
  }
  MiniGameID gameID;
  DWORD num;
  MiniUserData data[0];
};

//添加/更新一个游戏玩家列表
#define ADD_ONE_GAME_USER_COMMON_MINI_PARA 11
struct stAddOneGameUserCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stAddOneGameUserCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ADD_ONE_GAME_USER_COMMON_MINI_PARA;
    num = 1;
  }
  MiniGameID gameID;
  DWORD num;
  MiniUserData data;
};
*/

//离开桌子
#define LEAVE_GAME_COMMON_MINI_PARA 12
struct stLeaveGameCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stLeaveGameCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = LEAVE_GAME_COMMON_MINI_PARA;
  }
  MiniGameID gameID;
};

/*
//成为游戏主持者
#define HOST_GAME_COMMON_MINI_PARA 13
struct stHostGameCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stHostGameCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = HOST_GAME_COMMON_MINI_PARA;
    hostID = 0;
  }
  MiniGameID gameID;
  DWORD hostID;
};
*/

//打开/关闭某个位子
#define TOGGLE_SEAT_COMMON_MINI_PARA 14
struct stToggleSeatCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stToggleSeatCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = TOGGLE_SEAT_COMMON_MINI_PARA;
    open = 1;
  }
  MiniSeatID seatID;
  BYTE open;//0关闭 1打开
};

//踢某人
#define KICK_USER_COMMON_MINI_PARA 15
struct stKickUserCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stKickUserCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = KICK_USER_COMMON_MINI_PARA;
    userID = 0;
  }
  MiniGameID gameID;
  DWORD userID;
};

//切换准备/未准备状态
#define TOGGLE_READY_COMMON_MINI_PARA 16
struct stToggleReadyCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stToggleReadyCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = TOGGLE_READY_COMMON_MINI_PARA;
  }
  MiniGameID gameID;
};

//进入大厅确认消息
#define LOGIN_RET_COMMON_MINI_PARA 17
struct stLoginRetCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stLoginRetCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = LOGIN_RET_COMMON_MINI_PARA;
    ret = 0;
  }
  BYTE ret;//1成功 0失败
};

//进入房间确认消息
#define ENTER_ROOM_RET_COMMON_MINI_PARA 18
struct stEnterRoomRetCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stEnterRoomRetCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ENTER_ROOM_RET_COMMON_MINI_PARA;
    ret = 0;
  }
  BYTE ret;//1成功 0失败 2房间已满 3已经参加该类型的游戏
  MiniRoomID roomID;
};

//进入游戏确认消息
#define ENTER_GAME_RET_COMMON_MINI_PARA 19
struct stEnterGameRetCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stEnterGameRetCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = ENTER_GAME_RET_COMMON_MINI_PARA;
    ret = 0;
  }
  BYTE ret;//1成功 0失败 2人数已满 3游戏已开始 4座位已有人 5豆子不足 
  MiniSeatID seatID;
};

//刷新玩家状态
#define UPDATE_USER_STATE_COMMON_MINI_PARA 20
struct stUpdateUserStateCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stUpdateUserStateCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = UPDATE_USER_STATE_COMMON_MINI_PARA;
    userID = 0;
    state = MUS_NOTPLAY;
  }
  DWORD userID;//玩家ID
  BYTE state;//玩家状态
  MiniUserPosition pos;//当前位置
};

//游戏开始
#define GAME_START_COMMON_MINI_PARA 21
struct stGameStartCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stGameStartCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = GAME_START_COMMON_MINI_PARA;
  }
  MiniGameID gameID;
};

//游戏结束
#define GAME_END_COMMON_MINI_PARA 22
struct stGameEndCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stGameEndCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = GAME_END_COMMON_MINI_PARA;
  }
  MiniGameID gameID;
};

//通知游戏结果/分数
#define GAME_RESULT_COMMON_MINI_PARA 23
struct stGameResultCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stGameResultCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = GAME_RESULT_COMMON_MINI_PARA;
    userID = 0;
  }
  MiniGameID gameID;
  DWORD userID;
  MiniGameScore score;
};

/*
//请求玩家的分数
#define REQ_SCORE_COMMON_MINI_PARA 24
struct stReqScoreCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stReqScoreCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = REQ_SCORE_COMMON_MINI_PARA;
    userID = 0;
    gameType = 1;
  }
  DWORD userID;
  BYTE gameType;
};
*/

//发送玩家的分数
#define USER_SCORE_COMMON_MINI_PARA 25
struct stUserScoreCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stUserScoreCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = USER_SCORE_COMMON_MINI_PARA;
    userID = 0;
  }
  DWORD userID;
  MiniGameScore score;
};

enum MiniChatType
{
  MCT_NORMAL,//普通
  MCT_SYS,//系统
  MCT_POPUP//弹出窗口
};

//聊天
#define CHAT_COMMON_MINI_PARA 26
struct stChatCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stChatCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = CHAT_COMMON_MINI_PARA;
    userID = 0;
    type = MCT_NORMAL;
    bzero(content,sizeof(content));
  }
  DWORD userID;
  MiniUserPosition pos;//说话位置
  BYTE type;//聊天类型
  char content[64];
};

//请求各房间数据
#define REQ_ROOM_DATA_COMMON_MINI_PARA 27
struct stReqRoomDataCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stReqRoomDataCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = REQ_ROOM_DATA_COMMON_MINI_PARA;
  }
};

//请求排行榜
#define REQ_TOP_COMMON_MINI_PARA 28
struct stReqTopCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stReqTopCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = REQ_TOP_COMMON_MINI_PARA;
  }
};

//发送排行榜
#define RET_TOP_COMMON_MINI_PARA 29
struct stRetTopCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stRetTopCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = RET_TOP_COMMON_MINI_PARA;
    num = 0;
  }
  DWORD num;
  MiniUserData data[0];
};

//充游戏币
#define DEPOSIT_COMMON_MINI_PARA 30
struct stDepositCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stDepositCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = DEPOSIT_COMMON_MINI_PARA;
    num = 0;
  }
  DWORD num;
};

//兑换银两
#define DRAW_COMMON_MINI_PARA 31
struct stDrawCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stDrawCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = DRAW_COMMON_MINI_PARA;
    num = 0;
  }
  DWORD num;
};

//兑换银两返回
#define DRAW_RET_COMMON_MINI_PARA 32
struct stDrawRetCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stDrawRetCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = DRAW_RET_COMMON_MINI_PARA;
    ret = 0;
  }
  BYTE ret;//0失败 1成功 2不足 3包裹满
};

//发送玩家自己的信息
#define USER_DATA_COMMON_MINI_PARA 33
struct stUserDataCommonMiniGameCmd : public stCommonMiniGameCmd
{
  stUserDataCommonMiniGameCmd() : stCommonMiniGameCmd()
  {
    subParam = USER_DATA_COMMON_MINI_PARA;
  }
  MiniUserData data;
};

/*公共指令结束****************************************/

/*牌类指令开始**************************************/
class Card
{
  public:
    enum Suit
    {
      Diamond = 0x10,
      Club = 0x20,
      Heart = 0x30,
      Spade = 0x40,
      Joker = 0x50
    };

    Card():value(0){}
    Card(const Card &c):value(c.value){}
    Card(const BYTE v):value(v){}
    Card(const Suit s,const BYTE n):value(s|n){}

    BYTE suit() const {return value & 0xf0;}
    BYTE number() const {return value & 0x0f;}

    bool valid()
    {
      if (!suit() || suit()>5) return false;
      if (!number() || number()>13) return false;
      if (Joker==suit() && number()<14) return false;
      return true;
    }

    bool operator==(const Card &c) const{return number()==c.number();}
    bool operator<(const Card &c) const{return number()<c.number();}
    bool operator>(const Card &c) const{return number()>c.number();}
  private:
    BYTE value;
};

#define CARD_MINI_PARA 2
struct stCardMiniGameCmd : public stMiniGameUserCmd
{
  stCardMiniGameCmd() : stMiniGameUserCmd()
  {
    byParam = CARD_MINI_PARA;
  }
  MiniGameID gameID;
};

//发牌
#define DEAL_CARD_MINI_PARA 1
struct stDealCardMiniGameCmd : public stCardMiniGameCmd
{
  stDealCardMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = DEAL_CARD_MINI_PARA;
    num = 0;
  }
  BYTE num;
  Card cards[0];
};

//通知某人出牌
#define NOTIFY_PUT_CARD_MINI_PARA 2
struct stNotifyPutCardMiniGameCmd : public stCardMiniGameCmd
{
  stNotifyPutCardMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = NOTIFY_PUT_CARD_MINI_PARA;
    userID = 0;
  }
  DWORD userID;
};

//出牌
#define PUT_CARD_MINI_PARA 3
struct stPutCardMiniGameCmd : public stCardMiniGameCmd
{
  stPutCardMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = PUT_CARD_MINI_PARA;
    userID = 0;
    num = 0;
  }
  DWORD userID;
  BYTE num;
  Card cards[0];
};

//通知某人叫分
#define NOTIFY_POINT_DDZ_MINI_PARA 4
struct stNotifyPointDDZMiniGameCmd : public stCardMiniGameCmd
{
  stNotifyPointDDZMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = NOTIFY_POINT_DDZ_MINI_PARA;
    userID = 0;
  }
  DWORD userID;
};

//斗地主叫分
#define POINT_DDZ_MINI_PARA 5
struct stPointDDZMiniGameCmd : public stCardMiniGameCmd
{
  stPointDDZMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = POINT_DDZ_MINI_PARA;
    userID = 0;
    num = 0;
  }
  DWORD userID;
  BYTE num;
};

//显示底牌
#define RESERVE_CARDS_DDZ_MINI_PARA 6
struct stReserveCardsDDZMiniGameCmd : public stCardMiniGameCmd
{
  stReserveCardsDDZMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = RESERVE_CARDS_DDZ_MINI_PARA;
    userID = 0;
    num = 0;
  }
  DWORD userID;
  BYTE num;
  Card cards[0];
};

//摊牌
#define SHOW_HAND_DDZ_MINI_PARA 6
struct stShowHandDDZMiniGameCmd : public stCardMiniGameCmd
{
  stShowHandDDZMiniGameCmd() : stCardMiniGameCmd()
  {
    subParam = SHOW_HAND_DDZ_MINI_PARA;
    userID = 0;
    num = 0;
  }
  DWORD userID;
  BYTE num;
  Card cards[0];
};

/*牌类指令结束****************************************/

/*******************************************************/
// 邀请
#define INVITE_MINI_PARA 11
struct stInviteMiniGame : public stMiniGameUserCmd
{
  stInviteMiniGame()
  {
    byParam = INVITE_MINI_PARA;
  }
  DWORD tempid;//邀请者/被邀请者的临时ID
  DWORD money;//赌注
};

// 邀请回复
#define INVITE_RET_MINI_PARA 12
struct stInviteRetMiniGame : public stMiniGameUserCmd
{
  stInviteRetMiniGame()
  {
    byParam = INVITE_RET_MINI_PARA;
  }
  DWORD tempid;//邀请者的临时ID
  DWORD money;//赌注
  DWORD ret;//1:同意 0:不同意
};

// 开始游戏
#define START_MINI_PARA 13
struct stStartMiniGame : public stMiniGameUserCmd
{
  stStartMiniGame()
  {
    byParam = START_MINI_PARA;
  }
  DWORD tempid;//对方的临时ID
  DWORD money;//赌注
};

// 停止色子
#define STOP_DICE_MINI_PARA 14
struct stStopDiceMiniGame : public stMiniGameUserCmd
{
  stStopDiceMiniGame()
  {
    byParam = STOP_DICE_MINI_PARA;
  }
};

// 色子数字
#define DICE_NUM_MINI_PARA 15
struct stDiceNumMiniGame : public stMiniGameUserCmd
{
  stDiceNumMiniGame()
  {
    byParam = DICE_NUM_MINI_PARA;
  }
  DWORD tempid;//掷色子人的临时ID
  DWORD num;
};

// 结果
#define RESULT_MINI_PARA 16
struct stResultMiniGame : public stMiniGameUserCmd
{
  stResultMiniGame()
  {
    byParam = RESULT_MINI_PARA;
  }
  DWORD res;//0:输 1:赢 2:平
};

// 游戏结束 //主动离开游戏
#define END_MINI_PARA 17
struct stEndMiniGame : public stMiniGameUserCmd
{
  stEndMiniGame()
  {
    byParam = END_MINI_PARA;

    reason = 0;
  }
  DWORD reason;//结束原因 0:正常结束 1:对方离开
};

// 继续游戏
#define CONTINUE_MINI_PARA 18
struct stContinueMiniGame : public stMiniGameUserCmd
{
  stContinueMiniGame()
  {
    byParam = CONTINUE_MINI_PARA;
  }
  DWORD ret;//0:不继续 1:继续
};

// 通知客户端进入游戏
#define ENTER_MINI_PARA 19
struct stEnterMiniGame : public stMiniGameUserCmd
{
  stEnterMiniGame()
  {
    byParam = ENTER_MINI_PARA;
  }
};
/*******************************************************/

//////////////////////////////////////////////////////////////
/// 定义小游戏命令结束
//////////////////////////////////////////////////////////////

};

/**
 * \brief 定义会话服务器相关指令
 */

namespace Cmd
{

  namespace Session
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_SCENE = 2;
    const BYTE CMD_GATE = 3;
    const BYTE CMD_FORWARD = 4;
    const BYTE CMD_SESSION = 5;
    const BYTE CMD_GMTOOL = 6;
    const BYTE CMD_SCENE_SHUTDOWN = 7;
    const BYTE CMD_SCENE_TMP = 8;  // 临时指令
    const BYTE CMD_SCENE_SEPT = 9;  // 家族指令
    const BYTE CMD_SCENE_COUNTRY = 10; // 国家指令
    const BYTE CMD_SCENE_DARE = 11; // 对战指令
    const BYTE CMD_SCENE_UNION = 12; // 帮会指令
    const BYTE CMD_SCENE_ARMY = 13; // 军队指令
    const BYTE CMD_SCENE_GEM = 14;  // 护宝指令
    const BYTE CMD_SCENE_RECOMMEND = 15; // 推荐系统指令
	const BYTE CMD_SCENE_SPORTS	= 16;	//sky 战场竞技副本类指令

    //////////////////////////////////////////////////////////////
    /// 登陆会话服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginSession : t_NullCmd
    {
      WORD wdServerID;
      WORD wdServerType;
      t_LoginSession()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆会话服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 场景服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_SCENE_REGSCENE = 1;
    struct t_regScene_SceneSession : t_NullCmd
    {
      DWORD dwID;
      DWORD dwTempID;
      char byName[MAX_NAMESIZE+1];
      char fileName[MAX_NAMESIZE+1];
      DWORD dwCountryID;
      BYTE byLevel;

      t_regScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REGSCENE) {};
    };

    const BYTE PARA_SCENE_UNREGSCENE = 2;
    struct t_unregScene_SceneSession : t_NullCmd
    {
      DWORD dwTempID;
      t_unregScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_UNREGSCENE) {};
    };

    const BYTE PARA_SCENE_REGSCENE_RET = 3;
    const BYTE REGSCENE_RET_REGOK=  0;
    const BYTE REGSCENE_RET_REGERR=  2;
    struct t_regScene_ret_SceneSession : t_NullCmd
    {
      DWORD dwTempID;
      BYTE byValue;
      t_regScene_ret_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REGSCENE_RET) {};
    };

    const BYTE PARA_SCENE_REGUSER = 4;
    struct t_regUser_SceneSession : t_NullCmd
    {
      DWORD accid;
      DWORD dwID;
      DWORD dwTempID;
      DWORD dwMapID;
      BYTE byName[MAX_NAMESIZE+1];
      BYTE byMapName[MAX_NAMESIZE+1];
      DWORD dwGatewayServerID;
	  BYTE	RegMapType;			//sky 登陆形式(0:登陆现存地图位置 1:登陆老地图位置 )
      t_regUser_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REGUSER) {};
    };

    const BYTE PARA_SCENE_UNREGUSER = 5;
    const BYTE UNREGUSER_RET_LOGOUT=0;
    const BYTE UNREGUSER_RET_ERROR=1;
    struct t_unregUser_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      BYTE retcode;
      t_unregUser_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_UNREGUSER) {};
    };

    const BYTE PARA_SCENE_REGUSERSUCCESS = 6;  // 注册成功通知会话服务器
    struct t_regUserSuccess_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwUnionID;
      DWORD dwSchoolID;
      DWORD dwSeptID;
      DWORD dwCountryID;
      DWORD dwUseJob;
      DWORD dwExploit;
      QWORD qwExp;
      t_regUserSuccess_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REGUSERSUCCESS) {};
    };

    const BYTE PARA_SCENE_LEVELUPNOTIFY = 7;  // 玩家升级通知会话服务器
    struct t_levelupNotify_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      WORD level;
      QWORD qwExp;
      t_levelupNotify_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_LEVELUPNOTIFY) {};
    };


    const BYTE PARA_SCENE_CHANEG_SCENE = 8;  //切换场景
    struct t_changeScene_SceneSession : t_NullCmd
    {
      DWORD id;
      DWORD temp_id;
      DWORD x;
      DWORD y;
      DWORD map_id;
      BYTE map_file[MAX_NAMESIZE];
      BYTE map_name[MAX_NAMESIZE];      
      t_changeScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CHANEG_SCENE)
        {
          bzero(map_file,sizeof(map_file));
          bzero(map_name,sizeof(map_name));
        }
    };

    const BYTE PARA_SCENE_GM_COMMAND = 9;  //GM指令
    const BYTE GM_COMMAND_FINDUSER = 1;  //指令finduser
    const BYTE GM_COMMAND_GOTOUSER = 2;  //指令gotouser
    const BYTE GM_COMMAND_CATCHUSER = 3;  //指令catchuser
    const BYTE GM_COMMAND_DONTTALK = 4;  //指令donttalk
    const BYTE GM_COMMAND_TALK = 5;  //指令talk
    const BYTE GM_COMMAND_KICK = 6;  //指令kick
    const BYTE GM_COMMAND_SETPRIV = 7;  //指令setpriv
    const BYTE GM_COMMAND_LOCKVALUE = 8;  //指令lockvalue
    const BYTE GM_COMMAND_LEVELUP = 9;  //指令levelup
    const BYTE GM_COMMAND_LOAD_GIFT = 10;  //指令loadgift
    const BYTE GM_COMMAND_LOAD_PROCESS = 11;  //指令loadprocess
    const BYTE GM_COMMAND_EMBAR = 12;  //指令embar
    const BYTE GM_COMMAND_NEWZONE = 13;  //配置重生点
    const BYTE GM_COMMAND_REFRESH_GENERAL = 14;  //刷新大将军

    const BYTE GM_COMMAND_STATE_REQ = 1;  //指令状态req表示请求
    const BYTE GM_COMMAND_STATE_RET = 2;  //指令状态ret表示返回结果

    const BYTE GM_COMMAND_ERR_NOERR = 0;  //没有错误
    const BYTE GM_COMMAND_ERR_NOUSER = 1;  //玩家不在线
    const BYTE GM_COMMAND_ERR_PRIV = 2;  //权限不足
    const BYTE GM_COMMAND_ERR_PARAM = 3;  //参数错误
    const BYTE GM_COMMAND_ERR_FAIL = 4;  //指令执行失败
    struct t_gmCommand_SceneSession : t_NullCmd
    {
      BYTE gm_cmd;//GM指令
      BYTE cmd_state;//指令执行状态
      BYTE err_code;//错误信息
      DWORD id;//用户ID
      BYTE src_priv;//使用指令者权限
      DWORD x;//xy用来传递附加的参数
      DWORD y;
      BYTE src_name[MAX_NAMESIZE];
      BYTE dst_name[MAX_NAMESIZE];
      BYTE map_file[MAX_NAMESIZE];
      BYTE map_name[MAX_NAMESIZE];      
      t_gmCommand_SceneSession() 
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GM_COMMAND),
      gm_cmd(0),cmd_state(1),err_code(0),id(0),src_priv(1),x(0),y(0)
      {
        src_name[0] = 0;
        dst_name[0] = 0;
        map_file[0] = 0;
        map_name[0] = 0;
      };
    };

    const BYTE PARA_SCENE_PRIVATE_CHAT = 10;  //跨场景私聊
    const BYTE PRIVATE_CHAT_ERR_NOUSER = 1;  //玩家不在线
    const BYTE PRIVATE_CHAT_ERR_FILTER = 2;  //对方没开启私聊
    const BYTE PRIVATE_CHAT_ACT_INVITE = 1;  //邀请
    const BYTE PRIVATE_CHAT_ACT_JOIN = 2;  //加入
    const BYTE PRIVATE_CHAT_ACT_LEAVE = 3;  //离开
    struct t_privateChat_SceneSession : t_NullCmd
    {
      BYTE act;//动作
      BYTE err_code;//错误信息
      BYTE src_name[MAX_NAMESIZE];
      BYTE dst_name[MAX_NAMESIZE];
      DWORD cmd_size;
      BYTE chat_cmd[0];
      t_privateChat_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_PRIVATE_CHAT) {};
    };

    const BYTE PARA_SCENE_UNLOAD_SCENE = 11;  //停止注册
    struct t_unloadScene_SceneSession : t_NullCmd
    {
      DWORD map_id;
      t_unloadScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_UNLOAD_SCENE) {};
    };

    const BYTE PARA_SCENE_SYS_SETTING = 12;  //系统设置
    struct t_sysSetting_SceneSession : t_NullCmd
    {
      BYTE name[MAX_NAMESIZE];
      BYTE sysSetting[20];
      DWORD face;
      t_sysSetting_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SYS_SETTING) {};
    };

    const BYTE PARA_SCENE_CITY_RUSH = 13;  //怪物攻城的通知
    struct t_cityRush_SceneSession : t_NullCmd
    {
      char bossName[MAX_NAMESIZE];
      char rushName[MAX_NAMESIZE];
      char mapName[MAX_NAMESIZE];
      DWORD delay;
      DWORD countryID;
      t_cityRush_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CITY_RUSH) {};
    };

    const BYTE PARA_SCENE_CREATE_SCHOOL = 16;  //GM指令创建门派
    struct t_createSchool_SceneSession : t_NullCmd
    {
      char masterName[MAX_NAMESIZE];
      char schoolName[MAX_NAMESIZE];
      t_createSchool_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CREATE_SCHOOL) {};
    };
    
    

    const BYTE PARA_SCENE_CREATE_DARE = 17;  //创建对战指令
    struct t_createDare_SceneSession : t_NullCmd
    {
      //char relation1[MAX_NAMESIZE];  // 挑战方社会关系名称
      //char relation2[MAX_NAMESIZE];  // 应战方社会关系名称
      //DWORD relationID1;    // 挑战方社会关系ID(挑战方将用一个向量代替)
      DWORD relationID2;    // 应战方社会关系ID

      DWORD ready_time;    // 对战前的等待时间
      DWORD active_time;    // 对战进行时间
      BYTE type;        //对战类型
      
      t_createDare_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CREATE_DARE) 
        {
          ready_time = 0;
          active_time = 0;
        };
    };

    const BYTE PARA_SCENE_CREATE_QUIZ = 19;
    struct t_createQuiz_SceneSession : t_NullCmd
    {
      DWORD ready_time;
      DWORD active_time;
      DWORD dwUserID;    
      DWORD dwSubjects; // 总题目数
      BYTE  type;    // 竞赛类型
      BYTE  subject_type; // 题库类型
      
      t_createQuiz_SceneSession() : t_NullCmd(CMD_SCENE,PARA_SCENE_CREATE_QUIZ)
      {
        ready_time = 0;
        active_time = 0;
        dwUserID = 0;
        type = 0;
        subject_type = 0;
      }
    };

    //////////////////////////////////////////////////////////////
    ///  场景服务器之对战指令
    //////////////////////////////////////////////////////////////

    const BYTE PARA_SCENE_REMOVE_SCENE = 14;  //卸载地图
    struct t_removeScene_SceneSession : t_NullCmd
    {
      DWORD map_id;
      t_removeScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REMOVE_SCENE) {};
    };

    const BYTE PARA_SCENE_REQ_ADD_SCENE = 15;
    struct t_reqAddScene_SceneSession : t_NullCmd
    {
      DWORD dwServerID;
      DWORD dwCountryID;
      DWORD dwMapID;
      t_reqAddScene_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_REQ_ADD_SCENE) {};
    };

    ///直接转发到用户的指令
    const BYTE PARA_SCENE_FORWARD_USER = 18;
    struct t_forwardUser_SceneSession : t_NullCmd
    {
      DWORD id;
      DWORD tempid;
      char name[MAX_NAMESIZE];
      DWORD cmd_len;
      BYTE cmd[0];
      t_forwardUser_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_FORWARD_USER)
        {
          id = 0;
          tempid = 0;
          bzero(name,MAX_NAMESIZE);
        }
    };

    ///通知场景处罚一个玩家
    const BYTE PARA_SCENE_FORBID_TALK = 20;
    struct t_forbidTalk_SceneSession : t_NullCmd
    {
      char name[MAX_NAMESIZE];
      char reason[128];
      WORD operation;
      int delay;
      char gm[MAX_NAMESIZE];
      t_forbidTalk_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_FORBID_TALK)
        {
          bzero(name,sizeof(name));
          bzero(reason,sizeof(reason));
          operation = 0;
          delay = 0;
          bzero(gm,sizeof(gm));
        }
    };

    ///通知玩家运镖失败
    const BYTE PARA_SCENE_GUARD_FAIL = 21;
    struct t_guardFail_SceneSession : t_NullCmd
    {
      DWORD userID;
      BYTE type;//0: 被抢劫 1:时间结束 
      t_guardFail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GUARD_FAIL)
        {
          userID = 0;
        }
    };

    // 场景通知session玩家消费金币
    const BYTE PARA_SPEND_GOLD = 22;
    struct t_SpendGold_SceneSession : t_NullCmd
    {
      DWORD userID;
      DWORD gold;
      t_SpendGold_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SPEND_GOLD) {}
    };

    // 场景通知session开关各种服务
    const DWORD SERVICE_MAIL = 1;
    const DWORD SERVICE_AUCTION = 2;
    const DWORD SERVICE_PROCESS = 4;
    const DWORD SERVICE_HORSE = 8;
    const BYTE PARA_SET_SERVICE = 23;
    struct t_SetService_SceneSession : t_NullCmd
    {
      DWORD flag;
      t_SetService_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SET_SERVICE)
        {
          flag = 0;
        }
    };

    const BYTE PARA_SCENE_CITY_RUSH_CUST = 24;  //自定义怪物攻城的通知
    struct t_cityRushCust_SceneSession : t_NullCmd
    {
      char text[128];
      DWORD countryID;
      t_cityRushCust_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CITY_RUSH_CUST) {};
    };

    const BYTE PARA_SCENE_BAIL_CHECK = 25;  //取保就医的检查
    struct t_bailCheck_SceneSession : t_NullCmd
    {
      char name[MAX_NAMESIZE];
      DWORD money;
      t_bailCheck_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_BAIL_CHECK) {};
    };

    /*
    const BYTE PARA_SCENE_LOAD_PROCESS = 26;  //加载特征码文件
    struct t_loadProcess_SceneSession : t_NullCmd
    {
      t_loadProcess_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_LOAD_PROCESS) {};
    };
    */

    struct giftInfo
    {
      DWORD actID;
      DWORD charID;
      char name[MAX_NAMESIZE];
      BYTE itemGot;
      char mailText[MAX_CHATINFO];
      DWORD money;
      DWORD itemID;
      BYTE itemType;
      DWORD itemNum;
      BYTE bind;
    };
    const BYTE PARA_SCENE_SEND_GIFT = 27;  //发送物品邮件，session到场景获得物品
    struct t_sendGift_SceneSession : t_NullCmd
    {
      giftInfo info;
      t_sendGift_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SEND_GIFT) {};
    };

    // 发送全服通知
    const BYTE PARA_SERVER_NOTIFY = 28;
    struct t_serverNotify_SceneSession : t_NullCmd
    {
      int infoType;
      char info[MAX_CHATINFO];

      t_serverNotify_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SERVER_NOTIFY)
        {
          infoType = Cmd::INFO_TYPE_GAME;
          bzero(info,sizeof(info));
        }
    };

    // 发送一个场景的GM公告
    const BYTE PARA_BROADCAST_SCENE = 29;
    struct t_broadcastScene_SceneSession : t_NullCmd
    {
      int infoType;
      DWORD mapID;
      char GM[MAX_NAMESIZE];
      char info[MAX_CHATINFO];

      t_broadcastScene_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_BROADCAST_SCENE)
        {
          infoType = Cmd::INFO_TYPE_SCROLL;
          mapID = 0;
          bzero(info,sizeof(info));
          bzero(GM,sizeof(GM));
        }
    };

    const BYTE PARA_SCENE_SEND_CMD = 30;
    struct t_sendCmd_SceneSession : t_NullCmd
    {
      DWORD mapID;
      DWORD len;
      BYTE cmd[0];
      
      t_sendCmd_SceneSession() : t_NullCmd(CMD_SCENE,PARA_SCENE_SEND_CMD)
      {
        mapID = 0;
        len = 0;
      }
    };

    //////////////////////////////////////////////////////////////
    /// 场景服务器之社会关系公共指令
    //////////////////////////////////////////////////////////////
    enum{
      RELATION_TYPE_COUNTRY,
      RELATION_TYPE_SEPT,
      RELATION_TYPE_SCHOOL,
      RELATION_TYPE_UNION,
      RELATION_TYPE_NOTIFY
    };
    /// 角色成功加入或退出团体通知场景更新其对应的社会关系ID的值
    const BYTE PARA_SEND_USER_RELATION_ID = 50;
    struct t_sendUserRelationID : t_NullCmd
    {
      DWORD dwUserID;      /// 角色ID
      BYTE type;      /// 社会关系类型
      DWORD dwID;      /// 社会关系ID
      char name[MAX_NAMESIZE];  /// 社会关系名称
      DWORD caption;      /// 头衔，帮会所在城MAPID,当社会关系类型师徒的时候这个字段放师傅的CHARID
      bool  unionmaster;    /// 是否为帮主
      bool  septmaster;    /// 是否为族长
      bool  king;      /// 是否为国王
      DWORD dwActionPoint;    /// 行动力
      DWORD dwRepute;      /// 家族声望
      DWORD dwSeptLevel;    /// 家族等级
      bool  emperor;      /// 是否为皇帝

      t_sendUserRelationID()
        : t_NullCmd(CMD_SCENE,PARA_SEND_USER_RELATION_ID) {
          dwActionPoint = 0;
          dwRepute = 0;
          king = false;
          emperor = false;
          septmaster = false;
          unionmaster = false;
          bzero(name,MAX_NAMESIZE);
        };
    };
    
    /// 用户上线时，更新其配偶关系
    const BYTE PARA_UPDATE_CONSORT = 51;
    struct t_updateConsort : t_NullCmd
    {
      DWORD dwConsort;
      DWORD dwUserID;
      BYTE  byKingConsort;
      t_updateConsort() : t_NullCmd(CMD_SCENE,PARA_UPDATE_CONSORT) 
      {
        byKingConsort = 0;
      };
    };
    
    /// 用户上线时，更新其国家星号
    const BYTE PARA_UPDATE_COUNTRY_STAR = 52;
    struct t_updateCountryStar : t_NullCmd
    {
      DWORD dwCountryStar;
      DWORD dwUserID;
      
      t_updateCountryStar() : t_NullCmd(CMD_SCENE,PARA_UPDATE_COUNTRY_STAR) {};
    };

    /// 增加仇人
    const BYTE PARA_ADD_RELATION_ENEMY = 53;
    struct t_addRelationEnemy : t_NullCmd
    {
      DWORD dwUserID;
      char name[MAX_NAMESIZE];
      
      t_addRelationEnemy() : t_NullCmd(CMD_SCENE,PARA_ADD_RELATION_ENEMY) {};
    };

    /// 通知上线角色所占领的NPC情况
    const BYTE PARA_NOTIFY_NPC_HOLD_DATA = 54;
    struct t_notifyNpcHoldData : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwMapID;
      DWORD dwPosX;
      DWORD dwPosY;
      t_notifyNpcHoldData() : t_NullCmd(CMD_SCENE,PARA_NOTIFY_NPC_HOLD_DATA) {};
    };

    /// 通知上线角色所占领的NPC情况
    const BYTE PARA_NOTIFY_ADD_INTEGRAL = 55;
    struct t_notifyAddIntegral : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwGoldUser;
      DWORD dwNum;
      t_notifyAddIntegral() : t_NullCmd(CMD_SCENE,PARA_NOTIFY_ADD_INTEGRAL) {};
    };

    //////////////////////////////////////////////////////////////
    /// 场景服务器之社会关系公共指令
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    /// 场景服务器之帮会指令
    //////////////////////////////////////////////////////////////
    // 增加帮会
    const BYTE PARA_UNION_ADDUNION = 101;
    struct t_addUnion_SceneSession : t_NullCmd
    {
      DWORD dwItemID;             /// 道具物品的对象id 成功以后删除
      DWORD byRetcode;            /// 创建返回时：0 表示创建失败名称重复， 1表示成功
      DWORD dwMapTempID;          /// 地图临时编号
      UnionDef::stUnionInfo info;
      t_addUnion_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_UNION_ADDUNION) {};
    };

    // 增加成员
    const BYTE PARA_UNION_ADDMEMBER = 102;
    struct t_addUnionMember_SceneSession : t_NullCmd
    {
      DWORD dwUnionID;
      UnionDef::stUnionMemberInfo member;
      t_addUnionMember_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_UNION_ADDMEMBER) {};
    };
    // 开除成员
    const BYTE PARA_UNION_FIREMEMBER = 103;
    struct t_fireUnionMember_SceneSession : t_NullCmd
    {
      DWORD dwCharID;
      DWORD dwMapTempID;
      t_fireUnionMember_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_UNION_FIREMEMBER) {}
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器之帮会指令
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    /// 场景服务器之家族指令
    //////////////////////////////////////////////////////////////
    // 增加帮会
    const BYTE PARA_SEPT_ADDSEPT = 121;
    struct t_addSept_SceneSession : t_NullCmd
    {
      DWORD byRetcode;            /// 创建返回时：0 表示创建失败名称重复， 1表示成功
      DWORD dwMapTempID;          /// 地图临时编号
      SeptDef::stSeptInfo info;
      t_addSept_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SEPT_ADDSEPT) 
        {
          byRetcode = 0;
          bzero(&info,sizeof(info));
        };
    };

    // 增加成员
    const BYTE PARA_SEPT_ADDMEMBER = 122;
    struct t_addSeptMember_SceneSession : t_NullCmd
    {
      DWORD dwSeptID;
      SeptDef::stSeptMemberInfo member;
      t_addSeptMember_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SEPT_ADDMEMBER) {};
    };
    // 开除成员
    const BYTE PARA_SEPT_FIREMEMBER = 123;
    struct t_fireSeptMember_SceneSession : t_NullCmd
    {
      DWORD dwCharID;
      DWORD dwMapTempID;
      t_fireSeptMember_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_FIREMEMBER) {}
    };
    
    // 经验分配
    const BYTE PARA_SEPT_EXP_DISTRIBUTE = 124;
    struct t_distributeSeptExp_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwExp;
      t_distributeSeptExp_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_EXP_DISTRIBUTE) {}
    };

    // 发送全国通知
    const BYTE PARA_COUNTRY_NOTIFY = 125;
    struct t_countryNotify_SceneSession : t_NullCmd
    {
      int infoType;
      DWORD dwCountryID;
      char info[MAX_CHATINFO];

      t_countryNotify_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_COUNTRY_NOTIFY)
        {
          infoType = Cmd::INFO_TYPE_GAME;
        }
    };

    
    // 家族争夺NPC之对战请求
    const BYTE PARA_SEPT_NPCDARE_DARE = 127;
    struct t_NpcDare_Dare_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwCountryID;
      DWORD dwMapID;
      DWORD dwNpcID;
      t_NpcDare_Dare_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_DARE) {}
    };

    // 家族争夺NPC之场景通知
    const BYTE PARA_SEPT_NPCDARE_NOTIFYSCENE = 128;
    struct t_NpcDare_NotifyScene_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwCountryID;
      DWORD dwMapID;
      DWORD dwNpcID;
      DWORD dwPosX;
      DWORD dwPoxY;
      t_NpcDare_NotifyScene_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_NOTIFYSCENE) {}
    };

    // 家族争夺NPC之结果反馈
    const BYTE PARA_SEPT_NPCDARE_RESULT = 129;
    struct t_NpcDare_Result_SceneSession : t_NullCmd
    {
      DWORD dwSeptID;
      t_NpcDare_Result_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_RESULT) {}
    };

    // 家族争夺NPC之结果反馈
    const BYTE PARA_SEPT_NPCDARE_GETGOLD = 130;
    struct t_NpcDare_GetGold_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwGold;
      DWORD dwNpcID;
      DWORD dwMapID;
      DWORD dwCountryID;

      t_NpcDare_GetGold_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_GETGOLD) {}
    };

    // 家族争夺NPC之道具返还
    const BYTE PARA_SEPT_NPCDARE_ITEMBACK = 131;
    struct t_NpcDare_ItemBack_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      t_NpcDare_ItemBack_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_ITEMBACK) {}
    };

    // 家族争夺NPC之GM指令，立即触发开战
    const BYTE PARA_SEPT_NPCDARE_GMCMD = 132;
    struct t_NpcDare_GMCmd_SceneSession : t_NullCmd
    {
      t_NpcDare_GMCmd_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SEPT_NPCDARE_GMCMD) {}
    };

    
    // 由场景发往会话，查询城市所属
    const BYTE PARA_QUESTION_NPCDARE = 135;
    struct t_questionNpcDare_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwCountryID;
      DWORD dwMapID;
      DWORD dwNpcID;
      BYTE  byType;

      t_questionNpcDare_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_QUESTION_NPCDARE) {};
    };

    // 由会话发往场景，通知国家税率
    const BYTE PARA_TAX_COUNTRY = 136;
    struct t_taxCountry_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;
      DWORD dwTempID;
      BYTE  byTax;

      t_taxCountry_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_TAX_COUNTRY) {};
    };

    // 由场景发会话，通知国家税收增加
    const BYTE PARA_TAXADD_COUNTRY = 137;
    struct t_taxAddCountry_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;
      QWORD qwTaxMoney;
      t_taxAddCountry_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_TAXADD_COUNTRY) {};
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器之家族指令
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    /// 场景服务器之好友度指令
    //////////////////////////////////////////////////////////////
    struct stCountMember
    {
      DWORD  dwUserID;
      WORD  wdDegree;
      BYTE  byType;
    };

    struct stRequestMember
    {
      char name[MAX_NAMESIZE];
    };

    enum{
      TYPE_FRIEND,// 朋友类型
      TYPE_CONSORT,// 夫妻类型
      TYPE_TEACHER,// 师傅类型
      TYPE_PRENTICE,// 徒弟类型
    };
    struct stRequestReturnMember
    {
      DWORD dwUserID;
      WORD  wdDegree;
      BYTE  byType; // 使用枚举 RELATION_TYPE
    };

    // 向会话服务器请求计算所有的友好度
    const BYTE PARA_FRIENDDEGREE_COUNT = 150;
    struct t_CountFriendDegree_SceneSession : t_NullCmd
    {
      char    name[MAX_NAMESIZE];  // 玩家名称
      WORD    size;        // 团队列表的大小
      stCountMember  namelist[0];    // 剩余团队列表
      t_CountFriendDegree_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_FRIENDDEGREE_COUNT) {}
    };

    // 向会话服务器重新请求友好度关系列表，将会分发到各个队员身上
    const BYTE PARA_FRIENDDEGREE_REQUEST = 151;
    struct t_RequestFriendDegree_SceneSession : t_NullCmd
    {
      WORD  size;        // 队伍人数
      stRequestMember namelist[0];  // 团队列表
      t_RequestFriendDegree_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_FRIENDDEGREE_REQUEST) {}
    };


    // 会话服务器想场景服务器中的组队队员分发友好度关系列表。
    const BYTE PARA_FRIENDDEGREE_RETURN = 152;
    struct t_ReturnFriendDegree_SceneSession : t_NullCmd
    {
      DWORD dwID;        // 队长的tempID
      DWORD dwMapTempID;    // 地图的tempID
      WORD  size;        // 队伍人数
      stRequestReturnMember memberlist[0];  // 团队列表
      t_ReturnFriendDegree_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_FRIENDDEGREE_RETURN) {}
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器之好友度指令
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    /// 场景服务器之门派指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_SCHOOL_CREATE_SUCCESS = 170;
    struct t_SchoolCreateSuccess_SceneSession : t_NullCmd
    {
      DWORD  dwID;            // 师尊的ID
      DWORD  dwSchoolID;          // 门派ID
      char  schoolName[MAX_NAMESIZE];  // 门派名称
      t_SchoolCreateSuccess_SceneSession()
        :  t_NullCmd(CMD_SCENE,PARA_SCHOOL_CREATE_SUCCESS) {}
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器之门派指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    ///  场景服务器之卡通宝宝指令开始
    //////////////////////////////////////////////////////////////

    const BYTE PARA_CARTOON_CMD = 179;
    struct t_CartoonCmd : t_NullCmd
    {
      BYTE cartoonPara;
      t_CartoonCmd()
        : t_NullCmd(CMD_SCENE,PARA_CARTOON_CMD) 
        {
          cartoonPara = 0;
        };
    };

    const BYTE PARA_CARTOON_BUY = 1;
    struct t_buyCartoon_SceneSession : t_CartoonCmd
    {
      Cmd::t_CartoonData data;
      t_buyCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_BUY;

          bzero(&data,sizeof(data));
        };
    };

    const BYTE PARA_CARTOON_ADD = 2;
    struct t_addCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//ID
      DWORD cartoonID;
      Cmd::t_CartoonData data;
      t_addCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_ADD;

          userID = 0;
          cartoonID = 0;
          bzero(&data,sizeof(Cmd::t_CartoonData));
        };
    };

    const BYTE PARA_CARTOON_GET_LIST = 3;
    struct t_getListCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//ID
      t_getListCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_GET_LIST;

          userID = 0;
        };
    };

    enum saveType
    {
      SAVE_TYPE_DONTSAVE,
      SAVE_TYPE_PUTAWAY,
      SAVE_TYPE_LETOUT,
      SAVE_TYPE_ADOPT,
      SAVE_TYPE_RETURN,
      SAVE_TYPE_TIMEOVER,
      SAVE_TYPE_TIMETICK,
      //SAVE_TYPE_CHARGE,
      SAVE_TYPE_SYN
    };
    const BYTE PARA_CARTOON_SAVE = 4;
    struct t_saveCartoon_SceneSession : t_CartoonCmd
    {
      char userName[MAX_NAMESIZE];
      saveType type;
      DWORD cartoonID;//ID
      Cmd::t_CartoonData data;
      t_saveCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_SAVE;

          bzero(userName,MAX_NAMESIZE);
          type = SAVE_TYPE_DONTSAVE;
          cartoonID = 0;
          bzero(&data,sizeof(Cmd::t_CartoonData));
        };
    };

    const BYTE PARA_CARTOON_ADOPT = 5;
    struct t_adoptCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//ID
      DWORD cartoonID;
      BYTE masterState;//领养时，其主人的状态 0:不在线 1:在线
      Cmd::t_CartoonData data;
      t_adoptCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_ADOPT;

          userID = 0;
          cartoonID = 0;
          masterState = 0;
          bzero(&data,sizeof(Cmd::t_CartoonData));
        };
    };

    const BYTE PARA_CARTOON_GET_BACK = 6;
    struct t_getBackCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//ID
      DWORD cartoonID;
      t_getBackCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_GET_BACK;

          userID = 0;
          cartoonID = 0;
        };
    };

    const BYTE PARA_CARTOON_NOTIFY = 7;//通知领养者主人上下线
    struct t_notifyCartoon_SceneSession : t_CartoonCmd
    {
      char adopter[MAX_NAMESIZE];
      BYTE state;//0:下线 1:上线
      DWORD cartoonID;
      t_notifyCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_NOTIFY;

          bzero(adopter,MAX_NAMESIZE);
          state = 0;
          cartoonID = 0;
        };
    };

    const BYTE PARA_CARTOON_LOAD = 8;//上线时，获取宠物列表
    struct t_loadCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;
      t_loadCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_LOAD;

          userID = 0;
        };
    };

    const BYTE PARA_CARTOON_CORRECT = 9;//纠错，标记为被领养但是领养者没有宠物时，改为等待
    struct t_correctCartoon_SceneSession : t_CartoonCmd
    {
      DWORD cartoonID;
      t_correctCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_CORRECT;

          cartoonID = 0;
        };
    };

    const BYTE PARA_CARTOON_SALE = 10;//上线时，获取宠物列表
    struct t_saleCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;
      DWORD cartoonID;
      t_saleCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_SALE;

          userID = 0;
          cartoonID = 0;
        };
    };

    const BYTE PARA_CARTOON_CHARGE = 11;//充值
    struct t_chargeCartoon_SceneSession : t_CartoonCmd
    {
      DWORD masterID;
      DWORD cartoonID;
      DWORD time;//秒数
      t_chargeCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_CHARGE;

          masterID = 0;
          cartoonID = 0;
          time = 0;
        };
    };

    const BYTE PARA_CARTOON_CHARGE_NOTIFY = 12;//通知领养者宠物充值
    struct t_chargeNotifyCartoon_SceneSession : t_CartoonCmd
    {
      char adopter[MAX_NAMESIZE];
      DWORD cartoonID;
      DWORD time;//秒数
      t_chargeNotifyCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_CHARGE_NOTIFY;

          bzero(adopter,MAX_NAMESIZE);
          cartoonID = 0;
          time = 0;
        };
    };

    const BYTE PARA_CARTOON_LEVEL_NOTIFY = 13;//通知领养者宠物充值
    struct t_levelNotifyCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;
      DWORD cartoonID;
      DWORD level;
      t_levelNotifyCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_LEVEL_NOTIFY;

          userID = 0;
          cartoonID = 0;
          level = 0;
        };
    };

    const BYTE PARA_CARTOON_DRAW = 14;//提取经验
    struct t_drawCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;
      DWORD cartoonID;
      DWORD num;
      t_drawCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_DRAW;

          userID = 0;
          cartoonID = 0;
          num = 0;
        };
    };

    const BYTE PARA_CARTOON_CONSIGN = 15;//委托领养
    struct t_consignCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//委托人ID
      DWORD cartoonID;//委托的宠物ID
      char name[MAX_NAMESIZE];//被委托人名字 发给玩家时是委托人的名字
      t_consignCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_CONSIGN;

          userID = 0;
          cartoonID = 0;
          bzero(name,sizeof(name));
        };
    };

    const BYTE PARA_CARTOON_CONSIGN_RET = 16;//委托领养返回
    struct t_consignRetCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//被委托人ID
      DWORD cartoonID;
      BYTE ret;//0：拒绝 1：同意 2：已经领养5个了
      t_consignRetCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_CONSIGN_RET;

          userID = 0;
          ret = 0;
          cartoonID = 0;
        };
    };

    const BYTE PARA_CARTOON_SET_REPAIR = 17;//设置自动修理
    struct t_setRepairCartoon_SceneSession : t_CartoonCmd
    {
      DWORD userID;//主人ID
      DWORD cartoonID;
      BYTE repair;//0：关闭 1：打开
      t_setRepairCartoon_SceneSession()
        : t_CartoonCmd()
        {
          cartoonPara = PARA_CARTOON_SET_REPAIR;

          userID = 0;
          cartoonID = 0;
          repair = 0;
        };
    };

    //////////////////////////////////////////////////////////////
    ///  场景服务器之卡通宝宝指令结束
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    ///  场景服务器之邮件指令开始
    //////////////////////////////////////////////////////////////
    // 由场景往服务器发送，给玩家发邮件

    enum mailType
    {
      MAIL_TYPE_MAIL    = 1,//邮件
      MAIL_TYPE_MSG     = 2,//留言
      MAIL_TYPE_RETURN  =3,//退回的邮件
      MAIL_TYPE_AUCTION  =4,//拍卖用邮件
      MAIL_TYPE_SYS    =5  //系统邮件，不可退回
    };
    enum mailState
    {
      MAIL_STATE_NEW    = 1,
      MAIL_STATE_OPENED  = 2,
      MAIL_STATE_DEL    = 3
    };

    struct mailInfo
    {
      //DWORD id;
      BYTE state;
      char fromName[MAX_NAMESIZE+1];
      char toName[MAX_NAMESIZE+1];
      char title[MAX_NAMESIZE+1];
      BYTE type;
      DWORD createTime;
      DWORD delTime;
      BYTE accessory;
      BYTE itemGot;
      char text[256];
      DWORD sendMoney;
      DWORD recvMoney;
      DWORD sendGold;
      DWORD recvGold;
      DWORD fromID;
      DWORD toID;
      DWORD itemID;
    };

    const BYTE PARA_SCENE_CHECKSEND = 180;
    struct t_checkSend_SceneSession : t_NullCmd
    {
      mailInfo mail;
      DWORD itemID;
      //BYTE retCode;
      t_checkSend_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CHECKSEND) 
        {
          bzero(&mail,sizeof(mail));
          itemID = 0;
          //retCode = CHECKSEND_RETURN_FAILED;
        };
    };
    /*
    const BYTE PARA_SCENE_CHECKRETURN = 301;
    struct t_checkReturn_SceneSession : t_NullCmd
    {
      mailInfo mail;
      DWORD itemID;
      BYTE retCode;
      t_checkReturn_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CHECKRETURN) 
        {
          bzero(&mail,sizeof(mail));
          itemID = 0;
          retCode = CHECKSEND_RETURN_FAILED;
        };
    };
    */

    struct SessionObject
    {
      time_t createtime;
      t_Object object;
    };
    const BYTE PARA_SCENE_SENDMAIL = 181;
    struct t_sendMail_SceneSession : t_NullCmd
    {
      mailInfo mail;
      SessionObject item;
      t_sendMail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SENDMAIL) 
        {
          bzero(&mail,sizeof(mail)+sizeof(SessionObject));
        };
    };

    /*
    enum
    {
      SENDMAIL_RETURN_OK,
      SENDMAIL_RETURN_FAILED,
      SENDMAIL_RETURN_NOPLAYER
    };
    const BYTE PARA_SCENE_SENDMAIL_RETURN = 303;
    struct t_sendMailReturn_SceneSession : t_NullCmd
    {
      BYTE retCode;
      t_sendMailReturn_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SENDMAIL_RETURN) 
        {
          retCode = SENDMAIL_RETURN_FAILED;
        };
    };
    */

    const BYTE PARA_SCENE_GET_MAIL_LIST = 182;
    struct t_getMailList_SceneSession : t_NullCmd
    {
      DWORD tempID;
      t_getMailList_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GET_MAIL_LIST) 
        {
          tempID = 0;
        };
    };

    const BYTE PARA_SCENE_OPEN_MAIL = 183;
    struct t_openMail_SceneSession : t_NullCmd
    {
      DWORD tempID;
      DWORD mailID;
      t_openMail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_OPEN_MAIL) 
        {
          tempID = 0;
          mailID = 0;
        };
    };

    const BYTE PARA_SCENE_GET_MAIL_ITEM = 184;
    struct t_getMailItem_SceneSession : t_NullCmd
    {
      DWORD tempID;
      DWORD mailID;
      WORD space;
      DWORD money;
      DWORD gold;
      t_getMailItem_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GET_MAIL_ITEM) 
        {
          tempID = 0;
          mailID = 0;
          space = 0;
          money = 0;
          gold = 0;
        };
    };

    const BYTE PARA_SCENE_GET_MAIL_ITEM_RETURN = 185;
    struct t_getMailItemReturn_SceneSession : t_NullCmd
    {
      DWORD userID;
      DWORD mailID;
      DWORD sendMoney;
      DWORD recvMoney;
      DWORD sendGold;
      DWORD recvGold;
      SessionObject item;
      t_getMailItemReturn_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GET_MAIL_ITEM_RETURN) 
        {
          userID = 0;
          mailID = 0;
          sendMoney = 0;
          recvMoney = 0;
          sendGold = 0;
          recvGold = 0;
          bzero(&item,sizeof(SessionObject));
        };
    };

    const BYTE PARA_SCENE_GET_MAIL_ITEM_CONFIRM = 186;
    struct t_getMailItemConfirm_SceneSession : t_NullCmd
    {
      DWORD userID;
      DWORD mailID;
      t_getMailItemConfirm_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_GET_MAIL_ITEM_CONFIRM) 
        {
          userID = 0;
          mailID = 0;
        };
    };

    const BYTE PARA_SCENE_DEL_MAIL = 187;
    struct t_delMail_SceneSession : t_NullCmd
    {
      DWORD tempID;
      DWORD mailID;
      t_delMail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_DEL_MAIL) 
        {
          tempID = 0;
          mailID = 0;
        };
    };

    const BYTE PARA_SCENE_CHECK_NEW_MAIL = 188;
    struct t_checkNewMail_SceneSession : t_NullCmd
    {
      DWORD userID;
      t_checkNewMail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CHECK_NEW_MAIL) 
        {
          userID = 0;
        };
    };

    const BYTE PARA_SCENE_TURN_BACK_MAIL = 189;
    struct t_turnBackMail_SceneSession : t_NullCmd
    {
      DWORD userID;
      DWORD mailID;
      t_turnBackMail_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_TURN_BACK_MAIL) 
        {
          userID = 0;
        };
    };
    //////////////////////////////////////////////////////////////
    ///  场景服务器之邮件指令结束
    //////////////////////////////////////////////////////////////

    //从session发起的怪物攻城
    const BYTE PARA_SCENE_CREATE_RUSH = 198;
    struct t_createRush_SceneSession : t_NullCmd
    {
      DWORD rushID;
      DWORD delay;
      DWORD countryID;
      t_createRush_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_CREATE_RUSH) 
        {
          rushID = 0;
          delay = 0;
          countryID = 0;
        };
    };

    //////////////////////////////////////////////////////////////
    ///  场景服务器之拍卖指令开始
    //////////////////////////////////////////////////////////////
    enum auctionState
    {
      AUCTION_STATE_NEW  = 1,
      AUCTION_STATE_DEAL  = 2,
      AUCTION_STATE_CANCEL  = 3,
      AUCTION_STATE_TIMEOVER  = 4,
      AUCTION_STATE_DEL  = 5
    };

    struct auctionInfo
    {
      DWORD ownerID;
      char owner[MAX_NAMESIZE+1];
      BYTE state;
      DWORD charge;
      DWORD itemID;
      char itemName[MAX_NAMESIZE+1];
      BYTE type;
      BYTE quality;
      WORD needLevel;
      DWORD minMoney;
      DWORD maxMoney;
      DWORD minGold;
      DWORD maxGold;
      DWORD startTime;
      DWORD endTime;
      BYTE bidType;
    };

    const BYTE PARA_AUCTION_CMD = 199;
    struct t_AuctionCmd : t_NullCmd
    {
      BYTE auctionPara;
      t_AuctionCmd()
        : t_NullCmd(CMD_SCENE,PARA_AUCTION_CMD) 
        {
          auctionPara = 0;
        };
    };

    const BYTE PARA_AUCTION_SALE = 1;
    struct t_saleAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      auctionInfo info;
      SessionObject item;
      t_saleAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_SALE;

          bzero(&info,sizeof(info));
          bzero(&item,sizeof(item));
        };
    };

    const BYTE PARA_AUCTION_CHECK_BID = 2;
    struct t_checkBidAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      DWORD auctionID;
      DWORD money;
      DWORD gold;
      BYTE bidType;
      t_checkBidAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_CHECK_BID;

          userID = 0;
          auctionID = 0;
          money = 0;
          gold = 0;
          bidType = 0;
        };
    };

    const BYTE PARA_AUCTION_BID = 3;
    struct t_bidAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      DWORD auctionID;
      DWORD money;
      DWORD gold;
      t_bidAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_BID;

          userID = 0;
          auctionID = 0;
          money = 0;
          gold = 0;
        };
    };

    const BYTE PARA_AUCTION_QUERY = 4;
    struct t_queryAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      BYTE type;
      char name[MAX_NAMESIZE];
      BYTE quality;
      WORD level;
      WORD page;
      t_queryAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_QUERY;

          userID = 0;
          type = 0;
          bzero(name,sizeof(name));
          quality = 0;
          level = 0;
          page = 0;
        };
    };

    const BYTE PARA_AUCTION_CHECK_CANCEL = 5;
    struct t_checkCancelAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      DWORD auctionID;
      DWORD charge;
      t_checkCancelAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_CHECK_CANCEL;

          userID = 0;
          auctionID = 0;
          charge = 0;
        };
    };

    const BYTE PARA_AUCTION_CANCEL = 6;
    struct t_cancelAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      DWORD auctionID;
      DWORD charge;
      t_cancelAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_CANCEL;

          userID = 0;
          auctionID = 0;
          charge = 0;
        };
    };

    const BYTE PARA_AUCTION_GET_LIST = 7;
    struct t_getListAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      BYTE list;
      t_getListAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_GET_LIST;

          userID = 0;
          list = 0;
        };
    };

    /*
    const BYTE PARA_AUCTION_BID_LIST = 7;
    struct t_bidListAuction_SceneSession : t_AuctionCmd
    {
      DWORD userID;//临时ID
      DWORD bidList[100];
      t_bidListAuction_SceneSession()
        : t_AuctionCmd()
        {
          auctionPara = PARA_AUCTION_BID_LIST;

          bzero(&bidList[0],sizeof(bidList));
        };
    };
    */

    //////////////////////////////////////////////////////////////
    ///  场景服务器之拍卖指令结束
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 场景服务器之临时档案
    //////////////////////////////////////////////////////////////
    const BYTE PARA_USER_ARCHIVE_REQ = 200;
    struct t_ReqUser_SceneArchive : t_NullCmd
    {
      DWORD id;            /// 角色
      DWORD dwMapTempID;        /// 地图临时ID
      t_ReqUser_SceneArchive()
        : t_NullCmd(CMD_SCENE,PARA_USER_ARCHIVE_REQ) 
        {
          id = 0;
          dwMapTempID = 0;
        };
    };
    const BYTE PARA_USER_ARCHIVE_READ = 201;
    struct t_ReadUser_SceneArchive : t_NullCmd
    {
      DWORD id;            /// 角色
      DWORD dwMapTempID;        /// 地图临时ID
      DWORD dwSize;
      char data[0];
      t_ReadUser_SceneArchive()
        : t_NullCmd(CMD_SCENE,PARA_USER_ARCHIVE_READ) 
        {
          id = 0;
          dwMapTempID = 0;
          dwSize = 0;
        };
    };
    const BYTE PARA_USER_ARCHIVE_WRITE = 202;
    struct t_WriteUser_SceneArchive : t_NullCmd
    {
      DWORD id;            /// 角色
      DWORD dwMapTempID;        /// 地图临时ID
      DWORD dwSize;
      char data[0];
      t_WriteUser_SceneArchive()
        : t_NullCmd(CMD_SCENE,PARA_USER_ARCHIVE_WRITE) 
        {
          id = 0;
          dwMapTempID = 0;
          dwSize = 0;
        };
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器之临时档案
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 场景服务器之队伍指令
    //////////////////////////////////////////////////////////////
	struct stMember
	{
		DWORD dwID;					//sky 用户ID
		char  name[MAX_NAMESIZE];	//sky 用户名
		DWORD face;					//sky 头像
		bool leaber;				//sky 是否是队长
		stMember()
		{
			dwID = 0;
			face = 0;
			name[0] = 0;
			leaber = false;
		}
	};

    const BYTE PARA_USER_TEAM_ADDMEMBER = 203;
    struct t_Team_AddMember : t_NullCmd
    {
		DWORD dwLeaderID;			/// sky 队长ID
		DWORD dwTeam_tempid;		/// sky 队伍唯一ID
		stMember AddMember;			/// sky 添加队员信息
		t_Team_AddMember()
			: t_NullCmd(CMD_SCENE,PARA_USER_TEAM_ADDMEMBER) 
		{
			dwLeaderID = 0;
			dwTeam_tempid = 0;
		};
	};

    const BYTE PARA_USER_TEAM_DELMEMBER = 204;
	struct t_Team_DelMember : t_NullCmd
	{
		DWORD dwTeam_tempid;		/// sky 队伍唯一ID
		char MemberNeam[MAX_NAMESIZE];			/// 要删除角色							
		t_Team_DelMember()
			: t_NullCmd(CMD_SCENE,PARA_USER_TEAM_DELMEMBER) 
		{
			dwTeam_tempid = 0;
			MemberNeam[0] = 0;
		};
    };
    const BYTE PARA_USER_TEAM_REQUEST = 205;
    struct t_Team_Request : t_NullCmd
    {
      DWORD dwUserID;            /// 角色
      t_Team_Request()
        : t_NullCmd(CMD_SCENE,PARA_USER_TEAM_REQUEST) 
        {
          dwUserID = 0;
        };
    };

    const BYTE PARA_USER_TEAM_DATA = 206;
	struct t_Team_Data : t_NullCmd
	{
		DWORD dwTeamThisID;	/// sky 队伍唯一ID
		DWORD LeaderID;		/// sky 队长ID
		WORD dwSize;		/// 队伍人数
		stMember Member[0];	/// 队员列表
		t_Team_Data()
			: t_NullCmd(CMD_SCENE,PARA_USER_TEAM_DATA) 
		{
			LeaderID = 0;
			dwTeamThisID = 0;
			dwSize = 0;
		};
    };

	//sky 新增场景服务器之队伍指令-跟换队长
	const BYTE PARA_USER_TEAM_CHANGE_LEADER = 207;
    struct t_Team_ChangeLeader : t_NullCmd
    {
		DWORD dwTeam_tempid;		/// sky 队伍唯一ID
		char NewLeaderName[MAX_NAMESIZE];			/// 设置为队长的人物ID
		t_Team_ChangeLeader() 
			: t_NullCmd(CMD_SCENE,PARA_USER_TEAM_CHANGE_LEADER)
		{
			dwTeam_tempid = 0;
			NewLeaderName[0] = 0;
		}
    };

	//sky 请求组队指令
	const BYTE PARA_USER_TEAM_REQUEST_TEAM = 208;
	struct t_Team_RequestTeam : t_NullCmd
	{
		char byRequestUserName[MAX_NAMESIZE];	/// sky 请求者的名字
		char byAnswerUserName[MAX_NAMESIZE];	/// sky 回答者的名字

		t_Team_RequestTeam()
			: t_NullCmd(CMD_SCENE,PARA_USER_TEAM_REQUEST_TEAM)
		{
			byAnswerUserName[0] = 0;
			byRequestUserName[0] = 0;
		}
	};

	//sky 回答组队指令
	const BYTE PARA_USE_TEAM_ANSWER_TEAM = 209;
	struct t_Team_AnswerTeam : t_NullCmd
	{
		char byRequestUserName[MAX_NAMESIZE];	/// sky 请求者的名字
		char byAnswerUserName[MAX_NAMESIZE];	/// sky 回答者的名字
		DWORD dwAnswerID;						/// sky 回答者ID
		DWORD face;								/// sky 回答者头像
		BYTE  byAgree;							/// sky 是否同意(0:否 1:是)

		t_Team_AnswerTeam()
			: t_NullCmd(CMD_SCENE,PARA_USE_TEAM_ANSWER_TEAM)
		{
			byAnswerUserName[0] = 0;
			byRequestUserName[0] = 0;
			byAgree = 0;
		}
	};

	//sky 通知用户把自己添加到队伍中
	const BYTE PARA_USE_TEAM_ADDME = 210;
	struct t_Team_AddMe : t_NullCmd
	{
		DWORD MeID;		//用户自己的ID
		DWORD TeamThisID; //队伍唯一ID
		DWORD LeaberID; //队长ID

		t_Team_AddMe()
			: t_NullCmd(CMD_SCENE,PARA_USE_TEAM_ADDME)
		{
			TeamThisID = 0;
			MeID = 0;
			LeaberID = 0;
		}
	};

	//sky 删除队伍
	const BYTE PARA_USE_TEAM_DELTEAM = 211;
	struct t_Team_DelTeam : t_NullCmd
	{
		DWORD TeamThisID;
		t_Team_DelTeam()
			: t_NullCmd(CMD_SCENE,PARA_USE_TEAM_DELTEAM)
		{
			TeamThisID = 0;
		}
	};

	//sky 队员下线通知session添加自己到临时容器消息
	const BYTE PARA_USE_TEAM_ADDMOVESCENEMAMBER = 212;
	struct t_Team_AddMoveSceneMember : t_NullCmd
	{
		DWORD TeamThisID;		//sky 队伍唯一ID
		DWORD MemberID;			//sky 要加到容器的用户ID
		t_Team_AddMoveSceneMember()
			: t_NullCmd(CMD_SCENE, PARA_USE_TEAM_ADDMOVESCENEMAMBER)
		{
			TeamThisID = 0;
			MemberID = 0;
		}
	};

    //////////////////////////////////////////////////////////////
    /// 场景服务器之队伍指令
    //////////////////////////////////////////////////////////////

	//////////////////////////////////////////////////////////////
	/// sky 场景服务器战场副本竞技场指令
	//////////////////////////////////////////////////////////////
	//sky 排队消息(通知sess把排队的用户放到管理器中处理)
	const BYTE PARA_USE_SPORTS_ADDMETOQUEUING = 1;
	struct t_Sports_AddMeToQueuing : t_NullCmd
	{
		DWORD UserID;			//sky 用户ID(type为队伍时候该ID为队伍唯一ID)
		BYTE  Type;				//sky 排队类型(0:个人 1:队伍)
		WORD  AddMeType;		//sky 排队的战场类型  

		t_Sports_AddMeToQueuing()
			: t_NullCmd(CMD_SCENE_SPORTS, PARA_USE_SPORTS_ADDMETOQUEUING)
		{
			UserID = 0;
			Type = 0;
			AddMeType = 0;
		}
	};
	
	//sky 通知排队用户跳到战场或者副本或者竞技场场景
	const BYTE PARA_USE_SPORTS_MOVESECEN = 2;
	struct t_Sports_MoveSecen : t_NullCmd
	{
		DWORD UserID;					//sky 被通知的用户
		DWORD map_id;					//sky 被传送的地图的ID
		int  CampIndex;				//sky 阵营索引
		t_Sports_MoveSecen()
			: t_NullCmd(CMD_SCENE_SPORTS, PARA_USE_SPORTS_MOVESECEN)
		{
			UserID = 0;
			map_id = 0;
			CampIndex = -1;
		}

	};

	//sky 通知ScensServer提供一个可用的战场地图
	const BYTE PARA_USE_SPORTS_REQUESTMAP = 3;
	struct t_Sports_RequestMap : t_NullCmd
	{
		DWORD MapBaseID;				//sky 地图源ID
		WORD AddMeType;					//sky 提出通知的排队管理器索引

		t_Sports_RequestMap()
			: t_NullCmd(CMD_SCENE_SPORTS, PARA_USE_SPORTS_REQUESTMAP)
		{
			MapBaseID = 0;
			AddMeType = 0;
		}

	};

	struct  CampPos
	{
		DWORD x;
		DWORD y;

		CampPos()
		{
			x = 0;
			y = 0;
		}
	};

	//sky 场景找到可用的战场地图后通知session地图ID
	const BYTE PARA_USE_SPORTS_RETURNMAPID = 4;
	struct t_Sports_ReturnMapID : t_NullCmd
	{
		DWORD dwID;						//sky id为0时候为生成地图失败
		DWORD dwTempID;
		char byName[MAX_NAMESIZE+1];
		char fileName[MAX_NAMESIZE+1];
		DWORD dwCountryID;
		BYTE byLevel;
		WORD AddMeType;					//sky 提出通知的排队管理器索引
		CampPos pos[20];				//sky 传送位置

		t_Sports_ReturnMapID()
			: t_NullCmd(CMD_SCENE_SPORTS, PARA_USE_SPORTS_RETURNMAPID)
		{
			dwID = 0;
			dwTempID = 0;
			dwCountryID = 0;
			dwCountryID = 0;
			byLevel = 0;
			bzero(byName, sizeof(byName));
			bzero(fileName, sizeof(fileName));
			AddMeType = 0;
		}
	};

	//sky 场景通知session自己为战场服务器
	const BYTE PARA_SCENE_MEISBATTLEFIELD = 5;
	struct t_Scene_MeIsBattlefield : t_NullCmd
	{
		DWORD  SceneID;
		t_Scene_MeIsBattlefield()
			: t_NullCmd(CMD_SCENE_SPORTS, PARA_SCENE_MEISBATTLEFIELD)
		{
			SceneID = 0;		
		}
	};
	//////////////////////////////////////////////////////////////
	/// sky end
	//////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    ///  场景服务器之对战指令开始
    //////////////////////////////////////////////////////////////
        
    // 由会话发向场景，通知其在某玩家上进行竞赛奖励
    const BYTE  PARA_QUIZ_AWARD = 214;
    struct t_quizAward_SceneSession : t_NullCmd
    {
      DWORD dwUserID;      /// 角色ID
      DWORD dwExp;      /// 奖励经验
      DWORD dwMoney;      /// 奖励银两
      DWORD dwGrace;      /// 本次所获文采点数
      BYTE  byType;      /// 竞赛类型,默认为全国
      
      t_quizAward_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_QUIZ_AWARD) 
        {
          byType = 0;
        };
    };

    
    // 改变国籍，场景通知会话
    const BYTE  PARA_CHANGE_COUNTRY = 215;
    struct t_changeCountry_SceneSession : t_NullCmd
    {
      DWORD dwUserID;      /// 角色ID
      DWORD dwToCountryID;    /// 改变到的国家
      t_changeCountry_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_CHANGE_COUNTRY) {};
    };

    // 改变国籍，会话通知场景
    const BYTE  PARA_RETURN_CHANGE_COUNTRY = 216;
    struct t_returnChangeCountry_SceneSession : t_NullCmd
    {
      DWORD dwUserID;      /// 角色ID

      t_returnChangeCountry_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_RETURN_CHANGE_COUNTRY) {};
    };

    // 会话发向场景，让玩家跳到战场所在城市
    const BYTE PARA_TRANS_DARE_COUNTRY = 217;
    struct t_transDareCountry_SceneSession : t_NullCmd
    {
      DWORD dwUserID;  /// 角色ID
      DWORD dwMoney;  /// 需要扣除金额
      DWORD dwCountry; /// 要去的国家ID
      
      t_transDareCountry_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_TRANS_DARE_COUNTRY){};
    };

    // 由场景发往会话，确认该人能否跳往指定城市的帮会领地
    const BYTE PARA_ENTER_UNION_MANOR = 218;
    struct t_enterUnionManor_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 申请人的ID
      DWORD dwCountryID; // 跳去的国家ID
      DWORD dwCityID;  // 所在城市ID

      t_enterUnionManor_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_ENTER_UNION_MANOR) {};
    };
    
    // 由会话发往场景，让玩家跳到自己帮会的属地
    const BYTE PARA_RETURN_ENTER_UNION_MANOR = 219;
    struct t_returnEnterUnionManor_SceneSession : t_NullCmd
    {
      DWORD dwUserID;     // 申请人的ID
      DWORD dwCountryID;  // 要跳去的国家ID
      DWORD dwAreaID;     // 属地ID:只含有计算出来的REALID，需要场景通过COUNTRYID进行计算

      t_returnEnterUnionManor_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_RETURN_ENTER_UNION_MANOR) {};
    };
    
    // 由会话发往场景,清除帮会领地里非帮会成员
    const BYTE PARA_CLEAR_UNION_MANOR = 220;
    struct t_clearUnionManor_SceneSession : t_NullCmd
    {
      DWORD dwUnionID;  // 该场景上的所有人，除了指定帮会的人，其余全relive
      DWORD dwCountryID;  // 要跳去的国家ID
      DWORD dwAreaID;     // 属地ID:只含有计算出来的REALID，需要场景通过COUNTRYID进行计算

      t_clearUnionManor_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_CLEAR_UNION_MANOR) {};
    };
    
    // 由场景发往会话，查询城市所属
    const BYTE PARA_QUESTION_UNION_CITY = 221;
    struct t_questionUnionCity_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwCountryID;
      DWORD dwCityID;
      BYTE  byType;

      t_questionUnionCity_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_QUESTION_UNION_CITY) 
        {
          dwUserID = 0;
          dwCountryID = 0;
          dwCityID = 0;
          byType = 0;
        };
    };
    
        
    
    // 由场景发往会话，通知其用户数据变更
    const BYTE PARA_CHANGE_USER_DATA = 224;
    struct t_changeUserData_SceneSession : t_NullCmd
    {
      WORD  wdLevel;      // 类型，0为接受挑战的，1可接受挑战的,3,所有国家挑战信息
      DWORD dwExploit;    // 功勋值
      DWORD dwUserID;      // 玩家ID
      
      t_changeUserData_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_CHANGE_USER_DATA) {};
    };
    
    // 通知场景帮会战开始和结束
    const BYTE PARA_UNION_DARE_NOTIFY = 225;
    struct t_unionDareNotify_SceneSession : t_NullCmd
    {
      DWORD sceneID;
      BYTE state;//1 开始 0 结束

      t_unionDareNotify_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_UNION_DARE_NOTIFY) {};
    };
    
    // 会话发往场景,师傅领取进贡
    const BYTE PICKUP_MASTER_SCENE_PARA = 226;
    struct t_PickupMaster_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwMoney;

      t_PickupMaster_SceneSession()
        : t_NullCmd(CMD_SCENE,PICKUP_MASTER_SCENE_PARA)
        {
          dwUserID = 0;
          dwMoney = 0;
        }
    };


	const BYTE GLOBAL_MESSAGE_PARA = 227;
	struct t_GlobalMessage_SceneSession : t_NullCmd
	{
		DWORD dwUserID;
		char  msg[1];
		t_GlobalMessage_SceneSession()
			: t_NullCmd(CMD_SCENE,GLOBAL_MESSAGE_PARA)
			{
				dwUserID = 0;
			}
    };

    //////////////////////////////////////////////////////////////
    ///  场景服务器之对战指令结束
    //////////////////////////////////////////////////////////////
  
    /************************************************************
    ***********场景服务器之任务相关开始************
    ************************************************************/
    // 公告      
    const BYTE QUEST_BULLETIN_USERCMD_PARA = 240;
    struct t_QuestBulletinUserCmd : public t_NullCmd
    {
      t_QuestBulletinUserCmd(): t_NullCmd(CMD_SCENE,QUEST_BULLETIN_USERCMD_PARA)
      {
      }

      BYTE kind; // 0: reserve 1: tong 2 : family
      DWORD id; //family id or tong id
      char content[MAX_CHATINFO]; //chat msg
    };

    const BYTE QUEST_CHANGE_AP = 241;
    struct t_ChangeAP : public t_NullCmd //更改行动力
    {
      t_ChangeAP(): t_NullCmd(CMD_SCENE,QUEST_CHANGE_AP)
      {
      }
      DWORD id; 
      int point; 
    };

    const BYTE QUEST_CHANGE_RP = 242; //更改威望
    struct t_ChangeRP : public t_NullCmd
    {
      t_ChangeRP(): t_NullCmd(CMD_SCENE,QUEST_CHANGE_RP)
      {
      }
      BYTE kind; // 1: tong 2 :fam
      int point; 
    };
     
    // 寻找师父,分配点券
    const BYTE OVERMAN_TICKET_ADD = 243; 
    struct t_OvermanTicketAdd : public t_NullCmd
    {
      t_OvermanTicketAdd(): t_NullCmd(OVERMAN_TICKET_ADD,QUEST_CHANGE_RP)
      {
      }
      DWORD id;//  师父id
      DWORD ticket;//  应该得到的点券
      char name[MAX_NAMESIZE+1];//徒弟名字
    };
    
    /************************************************************
    ***********场景服务器之任务相关结束************
    ************************************************************/
    

    //////////////////////////////////////////////////////////////
    ///  GM维护指令
    //////////////////////////////////////////////////////////////
    // GM停机维护指令
    const BYTE PARA_SHUTDOWN = 1;
    struct t_shutdown_SceneSession : t_NullCmd
    {
      time_t time;
      char info[MAX_CHATINFO];
      t_shutdown_SceneSession()
        : t_NullCmd(CMD_SCENE_SHUTDOWN,PARA_SHUTDOWN) {
          bzero(&time,sizeof(time));
          bzero(info,sizeof(info));
        };
    };
    //////////////////////////////////////////////////////////////
    ///  GM维护指令结束
    //////////////////////////////////////////////////////////////



    //////////////////////////////////////////////////////////////
    /// 场景服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 网关服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_GATE_REGUSER = 1;
    struct t_regUser_GateSession : t_NullCmd
    {
      DWORD accid;
      DWORD dwID;
      DWORD dwTempID;
      DWORD dwMapID;
      WORD wdLevel;
      WORD wdOccupation;
      WORD wdCountry;
      BYTE byCountryName[MAX_NAMESIZE+1];
      BYTE byName[MAX_NAMESIZE+1];
      BYTE byMapName[MAX_NAMESIZE+1];
	  char OldMap[MAX_PATH];			//sky 老的地图位置
      t_regUser_GateSession()
        : t_NullCmd(CMD_GATE,PARA_GATE_REGUSER) {};
    };
    const BYTE PARA_GATE_UNREGUSER = 2;
    struct t_unregUser_GateSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      BYTE retcode;
      t_unregUser_GateSession()
        : t_NullCmd(CMD_GATE,PARA_GATE_UNREGUSER) {};
    };
    const BYTE PARA_GATE_CHANGE_SCENE_USER = 3;
    struct t_changeUser_GateSession : t_NullCmd
    {
      DWORD accid;
      DWORD dwID;
      DWORD dwTempID;
      BYTE byName[MAX_NAMESIZE+1];
      BYTE byMapFileName[MAX_NAMESIZE+1];	//sky 地图文件名
	  BYTE byMapName[MAX_NAMESIZE+1];		//sky 地图名字
      t_changeUser_GateSession()
		  : t_NullCmd(CMD_GATE,PARA_GATE_CHANGE_SCENE_USER) {};
    };
	struct Country_Online
	{
		DWORD country_id;
		DWORD Online_Now;
		Country_Online()
		{
			country_id = 0;
			Online_Now = 0;
		}
	};
	// [ranqd Add] 会话通知网关更新国家在线状态
	const BYTE PARA_GATE_UPDATEONLINE = 4;
	struct t_updateOnline_SessionGate : t_NullCmd
	{
		t_updateOnline_SessionGate()
			: t_NullCmd(CMD_GATE,PARA_GATE_UPDATEONLINE) {};
		WORD size;
		Country_Online info[0];
	};

    /// 请求国家在线人数排序
    const BYTE REQUEST_GATE_COUNTRY_ORDER = 5;
    struct t_request_Country_GateSession : t_NullCmd
    {
      t_request_Country_GateSession()
        : t_NullCmd(CMD_GATE,REQUEST_GATE_COUNTRY_ORDER) {};
    };
    struct CountrOrder
    {
      DWORD size;          //数量
      struct {
      DWORD country;        //国家  
      DWORD count;    //已经排序好的国家id
      } order[0];
    };
    /// 国家在线人数排序
    const BYTE PARA_GATE_COUNTRY_ORDER = 6;
    struct t_order_Country_GateSession : t_NullCmd
    {
      DWORD dwID;          //id
      CountrOrder order;      //排序的国家 
      t_order_Country_GateSession()
        : t_NullCmd(CMD_GATE,PARA_GATE_COUNTRY_ORDER) {};
    };

    ///直接转发到用户的指令
    const BYTE PARA_GATE_FORWARD_USER = 7;
    struct t_forwardUser_GateSession : t_NullCmd
    {
      DWORD id;
      DWORD tempid;
      char name[MAX_NAMESIZE];
      DWORD cmd_len;
      BYTE cmd[0];
      t_forwardUser_GateSession()
        : t_NullCmd(CMD_GATE,PARA_GATE_FORWARD_USER)
        {
          id = 0;
          tempid = 0;
          bzero(name,MAX_NAMESIZE);
        }
    };

    const BYTE PARA_UNION_DISBAND = 100;
    struct t_disbandUnion_GateSession : t_NullCmd
    {
      DWORD dwCharID;
      DWORD dwUnionID;
      t_disbandUnion_GateSession()
        : t_NullCmd(CMD_GATE,PARA_UNION_DISBAND) {};
    };
    const BYTE PARA_SEPT_DISBAND = 101;
    struct t_disbandSept_GateSession : t_NullCmd
    {
      DWORD dwCharID;
      DWORD dwSeptID;
      t_disbandSept_GateSession()
        : t_NullCmd(CMD_GATE,PARA_SEPT_DISBAND) {};
    };
    
    const BYTE PARA_GATE_DELCHAR = 102;
    struct t_DelChar_GateSession : t_NullCmd
    {
      DWORD accid;            /// 账号
      DWORD id;              /// 角色编号
	  DWORD countryid;       // 国家编号，用于删除角色后返回剩余角色
      char name[MAX_NAMESIZE+1];
      DWORD status;
      t_DelChar_GateSession()
        : t_NullCmd(CMD_GATE,PARA_GATE_DELCHAR) {};
    };    

    const BYTE PARA_EXIT_QUIZ = 103;
    struct t_exitQuiz_GateSession : t_NullCmd
    {
      DWORD dwUserID;
      BYTE  type; // type=0，退出.type=1,进入

      t_exitQuiz_GateSession()
        : t_NullCmd(CMD_GATE,PARA_EXIT_QUIZ)
        {
          type = 0;
        };
    };
    
    //////////////////////////////////////////////////////////////
    /// 查询类指令
    //////////////////////////////////////////////////////////////

    const BYTE PARA_QUESTION_OBJECT = 244;
    struct t_questionObject_SceneSession  : t_NullCmd
    {
      char from_name[MAX_NAMESIZE+1];  // 物品拥有者姓名
      char to_name[MAX_NAMESIZE+1];    // 物品查询者姓名
      DWORD dwObjectTempID;
      
      t_questionObject_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_QUESTION_OBJECT) {};
    };    

    const BYTE PARA_RETURN_OBJECT = 245;
    struct t_returnObject_SceneSession  : t_NullCmd
    {
      char from_name[MAX_NAMESIZE+1]; // 物品拥有者姓名
      char to_name[MAX_NAMESIZE+1];   // 物品查询者姓名

      t_Object object;
      
      t_returnObject_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_RETURN_OBJECT) {};
    };    

    const BYTE PARA_CLOSE_NPC = 246;
    struct t_CloseNpc_SceneSession  : t_NullCmd
    {
      t_CloseNpc_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_CLOSE_NPC) {};
    };

    const BYTE PARA_DEBUG_COUNTRYPOWER = 247;
    struct t_DebugCountryPower_SceneSession  : t_NullCmd
    {
      t_DebugCountryPower_SceneSession()
        : t_NullCmd(CMD_SCENE,PARA_DEBUG_COUNTRYPOWER) {};
    };

    //////////////////////////////////////////////////////////////
    /// 网关服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 会话服务器转发指令
    //////////////////////////////////////////////////////////////
    /// 网关到Session
    const BYTE PARA_FORWARD_USER = 1;
    struct t_Session_ForwardUser : t_NullCmd
    {
      DWORD dwID;
      WORD  size;
      BYTE  data[0];
      t_Session_ForwardUser()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_USER) {};
    };
    /// Session到全世界
    const BYTE PARA_FORWARD_WORLD = 2;
    struct t_Session_ForwardWorld : t_NullCmd
    {
      WORD  size;
      BYTE  data[0];
      t_Session_ForwardWorld()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_WORLD) {};
    };
    /// Session到国家
    const BYTE PARA_FORWARD_COUNTRY = 3;
    struct t_Session_ForwardCountry : t_NullCmd
    {
      DWORD dwCountry;
      WORD  size;
      BYTE  data[0];
      t_Session_ForwardCountry()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_COUNTRY) {};
    };
    //////////////////////////////////////////////////////////////
    /// 会话服务器转发指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 会话服务器指令
    //////////////////////////////////////////////////////////////
    // 会话服务器向Gateway发送黑名单管理消息。
    enum{
      BLACK_LIST_REMOVE,
      BLACK_LIST_ADD
    };
    const BYTE HANDLE_BLACK_LIST_PARA = 1;
    struct t_Session_HandleBlackList : t_NullCmd
    {
      DWORD dwID;
      char name[MAX_NAMESIZE+1];
      BYTE byOper;   // 0为删除 1为增加
      t_Session_HandleBlackList()
        : t_NullCmd(CMD_SESSION,HANDLE_BLACK_LIST_PARA) {};
    };
    //////////////////////////////////////////////////////////////
    /// 会话服务器指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// GM工具指令
    //////////////////////////////////////////////////////////////

    const BYTE MSGTIME_GMTOL_PARA = 1;
    struct t_MsgTime_GmTool : t_NullCmd
    {
      DWORD id;
      DWORD time;
      t_MsgTime_GmTool()
        : t_NullCmd(CMD_GMTOOL,MSGTIME_GMTOL_PARA)
        {
          id = 0;
          time = 0;
        }
    };

    //////////////////////////////////////////////////////////////
    /// GM工具指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    ///  临时指令开始
    //////////////////////////////////////////////////////////////
    // 临时指令
    // 场景发往会话，清除所有帮会，清除所有家族成员，以适应新的家族帮会合并模式
    const BYTE CLEARRELATION_PARA = 1;
    struct t_ClearRelation_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      
      t_ClearRelation_SceneSession()
        : t_NullCmd(CMD_SCENE_TMP,CLEARRELATION_PARA)
        {
          dwUserID = 0;
        }
    };

    // 会话发往场景，获取一个天羽令
    const BYTE GET_CREATE_UNION_ITEM_PARA = 2;
    struct t_GetCreateUnionItem_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 给指定的玩家
      
      t_GetCreateUnionItem_SceneSession()
        : t_NullCmd(CMD_SCENE_TMP,GET_CREATE_UNION_ITEM_PARA)
        {
          dwUserID = 0;
        }
    };
    
    // 场景发往会话，返回一个天羽令
    const BYTE RETURN_CREATE_UNION_ITEM_PARA = 3;
    struct t_ReturnCreateUnionItem_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 给指定的玩家
      SessionObject item;

      t_ReturnCreateUnionItem_SceneSession()
        : t_NullCmd(CMD_SCENE_TMP,RETURN_CREATE_UNION_ITEM_PARA)
        {
        }
    };

    //////////////////////////////////////////////////////////////
    ///  临时指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  家族指令开始
    //////////////////////////////////////////////////////////////
    // 场景发往会话，增加声望
    const BYTE OP_REPUTE_PARA = 1;
    struct t_OpRepute_SceneSession : t_NullCmd
    {
      DWORD dwSeptID; // 家族ID
      int dwRepute; //  声望值
      
      t_OpRepute_SceneSession()
        : t_NullCmd(CMD_SCENE_SEPT,OP_REPUTE_PARA)
        {
          dwSeptID = 0;
          dwRepute = 0;
        }
    };
    
    // 场景发往会话，更改家族等级
    const BYTE OP_LEVEL_PARA = 2;
    struct t_OpLevel_SceneSession : t_NullCmd
    {
      DWORD dwSeptID; // 家族ID
      int   dwLevel; //  家族值
      
      t_OpLevel_SceneSession()
        : t_NullCmd(CMD_SCENE_SEPT,OP_LEVEL_PARA)
        {
          dwSeptID = 0;
          dwLevel = 0;
        }
    };
    
    // 会话发往场景，提取家族经验
    const BYTE GET_SEPT_EXP_PARA = 3;
    struct t_GetSeptExp_SceneSession : t_NullCmd
    {
      DWORD dwSeptID; // 家族ID
      DWORD dwUserID; // 族长ID
      
      t_GetSeptExp_SceneSession()
        : t_NullCmd(CMD_SCENE_SEPT,GET_SEPT_EXP_PARA)
        {
          dwSeptID = 0;
          dwUserID = 0;
        }
    };

    // 会话发往场景，更新有关家族的普通信息，不用存档
    const BYTE SEND_SEPT_NORMAL_PARA = 4;
    struct t_SendSeptNormal_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 族长ID
      DWORD dwRepute; // 家族声望
      
      t_SendSeptNormal_SceneSession()
        : t_NullCmd(CMD_SCENE_SEPT,SEND_SEPT_NORMAL_PARA)
        {
          dwUserID = 0;
          dwRepute = 0;
        }
    };

    // 会话发往场景，提取家族经验
    const BYTE GET_SEPT_NORMAL_EXP_PARA = 5;
    struct t_GetSeptNormalExp_SceneSession : t_NullCmd
    {
      DWORD dwSeptID; // 家族ID
      DWORD dwUserID; // 族长ID

      t_GetSeptNormalExp_SceneSession()
        : t_NullCmd(CMD_SCENE_SEPT,GET_SEPT_NORMAL_EXP_PARA)
        {
          dwSeptID = 0;
          dwUserID = 0;
        }
    };


    //////////////////////////////////////////////////////////////
    ///  家族指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  国家指令
    //////////////////////////////////////////////////////////////
    // 由场景发往会话，查看国家对战信息
    const BYTE PARA_VIEW_COUNTRY_DARE = 1;
    struct t_viewCountryDare_SceneSession : t_NullCmd
    {
      BYTE  byType;      // 类型，0为接受挑战的，1可接受挑战的,3,所有国家挑战信息
      DWORD dwUserID;      // 查询者
      
      t_viewCountryDare_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_VIEW_COUNTRY_DARE) {};
    };

    // 由场景发往会话，进行国家捐献
    const BYTE PARA_CONTRIBUTE_COUNTRY = 2;
    struct t_ContributeCountry_SceneSession : t_NullCmd
    {
      BYTE byType; // 0,普通物资，1,丝线,2,矿石,3,矿产,4,木材，5,皮毛,6,草药
      DWORD dwValue;  // 捐献度
      DWORD dwCountry;

      t_ContributeCountry_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_CONTRIBUTE_COUNTRY){};
    };
    
    // 国战结果
    enum
    {
      COUNTRY_FORMAL_DARE,// 正式国战
      COUNTRY_ANNOY_DARE,// 骚扰国战
      EMPEROR_DARE,// 皇城争夺战
      COUNTRY_FORMAL_ANTI_DARE,// 国战反攻
    };
    
    const BYTE PARA_COUNTRY_DARE_RESULT = 3;
    struct t_countryDareResult_SceneSession : t_NullCmd
    {
      DWORD dwAttCountryID;
      DWORD dwDefCountryID;

      char attCountryName[MAX_NAMESIZE];  // 挑战者国家名称
      char defCountryName[MAX_NAMESIZE];  // 防御方国家名称
      DWORD dwAttUserID;      // 打死大将军的玩家ID
      
      BYTE byType;  // 国战类型
      
      t_countryDareResult_SceneSession()
        :  t_NullCmd(CMD_SCENE_COUNTRY,PARA_COUNTRY_DARE_RESULT) {}
    };

    // 由会话发往场景，让设置王城场景为战场
    const BYTE PARA_SET_COUNTRY_WAR = 4;
    struct t_setCountryWar_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;  // 要设置战场的国家ID // 防守方
      //DWORD dwAttCountryID; // 攻击方国家ID
      DWORD dwAreaID;     // 战场
      BYTE  byStatus;      // 类型，0为退出，1,为进入
      
      t_setCountryWar_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SET_COUNTRY_WAR) 
        {
            this->dwCountryID = 0;
            //this->dwAttCountryID = 0;
            this->dwAreaID = 0;
            this->byStatus = 0;
        };
    };
    
    // 由会话发往场景，让符合条件的玩家，跳转到边境
    const BYTE PARA_SEL_TRANS_COUNTRY_WAR = 5;
    struct t_selTransCountryWar_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;  // 要跳转的玩家国家
      DWORD dwLevel;     // 玩家等级条件
      
      t_selTransCountryWar_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SEL_TRANS_COUNTRY_WAR) {};
    };

    //国王处罚一个玩家
    const BYTE PARA_COUNTRY_PUNISH_USER = 6;
    struct t_countryPunishUser_SceneSession : t_NullCmd
    {
      char name[MAX_NAMESIZE];
      DWORD method;//处罚方式 1禁言 2关监狱

      t_countryPunishUser_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_COUNTRY_PUNISH_USER)
        {
          bzero(name,sizeof(name));
          method = 0;
        };
    };

    struct _techItem
    {
      DWORD dwType;
      DWORD dwLevel;
    };  
    
    // 更新国家科技到场景
    const BYTE PARA_UPDATE_TECH = 7;
    struct t_updateTech_SceneSession : t_NullCmd
    {
      t_updateTech_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_UPDATE_TECH)
        {
          bzero(data,sizeof(data));
          dwCountryID = 0;
        };
      
      DWORD dwCountryID;
      _techItem data[14];
    };

    // 场景发往会话，进行科技投票的启动与结束
    const BYTE PARA_OP_TECH_VOTE = 8;
    struct t_opTechVote_SceneSession : t_NullCmd
    {

      t_opTechVote_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_OP_TECH_VOTE)
        {
          byOpType = 0;
          dwCountryID = 0;
        };

      DWORD dwCountryID;
      BYTE byOpType; //1为启动，0为结束
    };
    
    // 更新领主帮会到场景
    const BYTE PARA_UPDATE_SCENE_UNION = 9;
    struct t_updateSceneUnion_SceneSession : t_NullCmd
    {

      t_updateSceneUnion_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_UPDATE_SCENE_UNION)
        {
          dwSceneID = 0;
          dwUnionID = 0;
        };
      
      DWORD dwSceneID;
      DWORD dwUnionID;
    };

    // 更新战胜国标志
    const BYTE PARA_WINNER_EXP_SCENE_COUNTRY = 10;
    struct t_updateWinnerExp_SceneSession : t_NullCmd
    {

      t_updateWinnerExp_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_WINNER_EXP_SCENE_COUNTRY)
        {
        };
      DWORD countryID;
      bool type;  //false表示结束,true表示开始
    };
    
    struct _allyItem
    {
      DWORD dwCountryID;
      DWORD dwAllyCountryID;
      DWORD dwFriendDegree;
    };  
    
    // 更新国家同盟信息到场景
    const BYTE PARA_UPDATE_ALLY = 11;
    struct t_updateAlly_SceneSession : t_NullCmd
    {
      t_updateAlly_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_UPDATE_ALLY)
        {
          dwSize = 0;
        };
      
      DWORD dwSize;
      _allyItem data[0];
    };

    // 场景到会话,增加国家联盟友好度
    const BYTE PARA_OP_ALLY_FRIENDDEGREE = 12;
    struct t_opAllyFrienddegree_SceneSession : t_NullCmd
    {
      t_opAllyFrienddegree_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_OP_ALLY_FRIENDDEGREE)
        {
          dwCountryID = 0;
          friendDegree = 0;
        };
      
      DWORD dwCountryID;
      int friendDegree;
    };

    // 会话到场景,触发联盟镖车
    const BYTE PARA_SUMMON_ALLY_NPC = 13;
    struct t_summonAllyNpc_SceneSession : t_NullCmd
    {
      t_summonAllyNpc_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SUMMON_ALLY_NPC)
        {
          dwCountryID = 0;
        };
      
      DWORD dwCountryID;
    };

    // 场景到会话,当外交车队到达时,增加国家联盟友好度
    const BYTE PARA_ALLY_NPC_CLEAR = 14;
    struct t_allyNpcClear_SceneSession : t_NullCmd
    {
      t_allyNpcClear_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_ALLY_NPC_CLEAR)
        {
          dwCountryID = 0;
        };

      DWORD dwCountryID;
    };

    // 设置皇城占领国(会话到场景)
    const BYTE PARA_SET_EMPEROR_HOLD = 15;
    struct t_setEmperorHold_SceneSession : t_NullCmd
    {
      t_setEmperorHold_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SET_EMPEROR_HOLD)
        {
          dwCountryID = 0;
        };

      DWORD dwCountryID;
    };

    // 会话到场景,通知大将军的等级
    const BYTE PARA_REFRESH_GEN = 16;
    struct t_refreshGen_SceneSession : t_NullCmd
    {
      t_refreshGen_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_REFRESH_GEN)
        {
          dwCountryID = 0;
          level = 0;
          exp = 0;
          maxExp = 0;
        };

      DWORD dwCountryID;
      DWORD level;
      DWORD exp;
      DWORD maxExp;
    };

    // 场景到会话,给大将军加经验
    const BYTE PARA_ADD_GEN_EXP = 17;
    struct t_addGenExp_SceneSession : t_NullCmd
    {
      t_addGenExp_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_ADD_GEN_EXP)
        {
          dwCountryID = 0;
          exp = 0;
        };

      DWORD dwCountryID;
      DWORD exp;
    };

    //皇帝处罚一个玩家
    const BYTE PARA_EMPEROR_PUNISH_USER = 18;
    struct t_emperorPunishUser_SceneSession : t_NullCmd
    {
      char name[MAX_NAMESIZE];
      DWORD method;//处罚方式 1禁言 2关监狱

      t_emperorPunishUser_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_EMPEROR_PUNISH_USER)
        {
          bzero(name,sizeof(name));
          method = 0;
        };
    };

    // 检查一个玩家的善恶度
    const BYTE PARA_CHECK_USER = 19;
    struct t_checkUser_SceneSession : t_NullCmd
    {
      t_checkUser_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_CHECK_USER)
        {
          byState   = 0;
          dwCheckID  = 0;
          dwCheckedID = 0;
        };
      
      BYTE byState; // 0,未通过检查,1,通过检查
      DWORD dwCheckID; // 发起检查的玩家ID
      DWORD dwCheckedID; // 待检测玩家的ID
    };

    // 设置外交官状态
    const BYTE PARA_SET_DIPLOMAT_STATE = 20;
    struct t_setDiplomatState_SceneSession : t_NullCmd
    {
      t_setDiplomatState_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SET_DIPLOMAT_STATE)
        {
          byState   = 0;
          dwUserID = 0;
        };
      
      BYTE byState; // 0,取消状态,1,设置状态
      DWORD dwUserID; // 待设置的玩家ID
    };

    // 设置捕头状态
    const BYTE PARA_SET_CATCHER_STATE = 21;
    struct t_setCatcherState_SceneSession : t_NullCmd
    {
      t_setCatcherState_SceneSession()
        : t_NullCmd(CMD_SCENE_COUNTRY,PARA_SET_CATCHER_STATE)
        {
          byState   = 0;
          dwUserID = 0;
        };
      
      BYTE byState; // 0,取消状态,1,设置状态
      DWORD dwUserID; // 待设置的玩家ID
    };


    const BYTE PARA_COUNTRY_POWER_SORT = 22;
    struct t_countryPowerSort_SceneSession : t_NullCmd
    {
      BYTE country[13];
      t_countryPowerSort_SceneSession() : t_NullCmd(CMD_SCENE_COUNTRY,PARA_COUNTRY_POWER_SORT)
      {
        bzero(country,sizeof(country));
      }
    };
    //////////////////////////////////////////////////////////////
    ///  国家指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  对战指令开始
    //////////////////////////////////////////////////////////////
    // 由场景往服务器发送，通知其有关对战的处理是否成功，并不仅限于激活对战斗时
    enum
    {
      SCENE_ACTIVEDARE_SUCCESS,// 场景处理激活战斗成功
      SCENE_ACTIVEDARE_FAIL        // 场景处理激活战斗失败
    };

    const BYTE PARA_ACTIVEDARE = 1;
    struct t_activeDare_SceneSession : t_NullCmd
    {
      DWORD dwWarID;
      DWORD dwStatus;

      t_activeDare_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_ACTIVEDARE) 
        {
          dwWarID = 0;
          dwStatus = SCENE_ACTIVEDARE_FAIL;
        };
    };

    
    // 由会话向场景发送，通知其交战状态，场景收到后，会给角色加上交战记录，并由此计算出是否显示交战标示
    const BYTE PARA_ENTERWAR = 2;
    struct t_enterWar_SceneSession : t_NullCmd
    {
      DWORD dwWarType;        // 交战类型
      DWORD dwUserID;    //
      DWORD dwFromRelationID; // 
      DWORD dwToRelationID;   // 与之交战的社会关系ID,守方(在夺旗类型对战时使用)
      DWORD dwSceneTempID;
      DWORD dwStatus;         // 1,为开始交战的记录，0为结束交战的记录
      bool isAtt;    // false,为守方，true为攻方（夺旗类型对战使用）
      bool isAntiAtt;    // 是否可以反攻

      t_enterWar_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_ENTERWAR)
        {
          dwWarType = 0;
          dwSceneTempID = 0;
          dwUserID = 0;
          dwToRelationID = 0;
          dwFromRelationID = 0;
          dwStatus = 1;
          isAtt = false;
          isAntiAtt = false;
        };
    };

    // 由场景发送给会话，通知社会团体交战结果
    const BYTE PARA_DARE_PK = 3;
    struct t_darePk_SceneSession : t_NullCmd
    {
      DWORD attID;    // 攻击方用户ID
      DWORD defID;    // 防御方用户ID

      t_darePk_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_DARE_PK)
        {
          attID = 0;
          defID = 0;
        };
    };
      
    enum
    {
      DARE_GOLD,// 挑战金
      RETURN_DARE_GOLD,// 返还挑战金
      WINNER_GOLD,// 奖励金
      EMPEROR_GOLD,// 皇帝每日奖励金
    };
    
    // 由会话发向场景，通知其在某玩家上扣钱，或加钱
    const BYTE  PARA_DARE_GOLD = 4;
    struct t_dareGold_SceneSession : t_NullCmd
    {
      DWORD dwUserID;      /// 角色ID
      int   dwNum;      /// 增或减的金钱数
      DWORD dwWarID;      /// 对战ID
      DWORD dwType;                   /// 扣钱类型,扣挑战金0,还挑战金1,对战奖励2
      DWORD dwWarType;    /// 对战类型
        
      t_dareGold_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_DARE_GOLD) 
        {
          dwNum = 0;
          dwUserID = 0;
          dwWarID = 0;
        };
    };
    
    // 新建帮会夺城战(场景发往会话)
    const BYTE PARA_UNION_CITY_DARE = 5;
    struct t_UnionCity_Dare_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;
      DWORD dwCityID;
      DWORD dwFromUserID;  // 发起挑战者
      DWORD dwFromUnionID;  // 
      DWORD dwToCountryID;
        
      t_UnionCity_Dare_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_UNION_CITY_DARE) {}
    };

    // 帮会夺城战结果(场景发往会话)
    const BYTE PARA_UNION_CITY_DARE_RESULT = 6;
    struct t_UnionCity_DareResult_SceneSession : t_NullCmd
    {
      DWORD dwCountryID;
      DWORD dwCityID;
      DWORD dwUserID;  // 赢家帮主
      DWORD dwUnionID; // 对战赢家帮会
        
      t_UnionCity_DareResult_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_UNION_CITY_DARE_RESULT) {}
    };
    
    // GM指令触发帮会夺城战(场景发往会话)
    const BYTE PARA_GM_CREATE_UNION_CITY = 7;
    struct t_GMCreateUnionCity_SceneSession : t_NullCmd
    {
      DWORD dwCityID;
      DWORD dwCountryID;
      BYTE  byOpType;
        
      t_GMCreateUnionCity_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_GM_CREATE_UNION_CITY) {}
    };
    
    // 设置反攻标志(会话发往场景)
    const BYTE PARA_SET_ANTI_ATT_FLAG = 8;
    struct t_setAntiAttFlag_SceneSession : t_NullCmd
    {
      DWORD dwFromRelationID;
      DWORD dwToRelationID;
      DWORD dwType;
        
      t_setAntiAttFlag_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_SET_ANTI_ATT_FLAG) {}
    };
    
    // 设置皇城争夺战开始标志(会话发往场景)
    const BYTE PARA_SET_EMPEROR_DARE = 9;
    struct t_setEmperorDare_SceneSession : t_NullCmd
    {
      t_setEmperorDare_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_SET_EMPEROR_DARE) 
        {
          byState = 0;
          dwDefCountryID = 0;
        }
      
      BYTE byState; // 1,皇城进入争夺战,0,皇城退出争夺战
      DWORD dwDefCountryID; // 目前皇城的拥有者,为0表示,没有
    };

    // 触发皇城争夺战(场景发往会话)
    const BYTE PARA_BEGIN_EMPEROR_DARE = 10;
    struct t_beginEmperorDare_SceneSession : t_NullCmd
    {
      t_beginEmperorDare_SceneSession()
        :  t_NullCmd(CMD_SCENE_DARE,PARA_BEGIN_EMPEROR_DARE) 
        {
        }
    };
    //令牌抓人
    const BYTE PARA_GOTO_LEADER = 11;
    struct t_GoTo_Leader_SceneSession  : t_NullCmd
    {
      t_GoTo_Leader_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_GOTO_LEADER) {};
      BYTE type;          //令牌类型
      DWORD leaderTempID;  
      char mapName[MAX_NAMESIZE]; //地图名称
      WORD x;            //坐标x  
      WORD y;            //坐标y
    };
    //令牌抓人到场景验证
    const BYTE PARA_GOTO_LEADER_CHECK = 12;
    struct t_GoTo_Leader_Check_SceneSession  : t_NullCmd
    {
      t_GoTo_Leader_Check_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_GOTO_LEADER_CHECK) {};
      BYTE type;          //令牌类型
      DWORD leaderTempID;  
      DWORD userTempID;  
      char mapName[MAX_NAMESIZE]; //地图名称
      WORD x;            //坐标x  
      WORD y;            //坐标y
    };

    //令牌抓人次数检查
    const BYTE PARA_CHECK_CALLTIMES_LEADER = 13;
    struct t_Check_CallTimes_SceneSession  : t_NullCmd
    {
      t_Check_CallTimes_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_CHECK_CALLTIMES_LEADER) {};
      BYTE type;          //令牌类型
      DWORD leaderTempID;  
      DWORD qwThisID;        //令牌id
    };
    //返回剩余可用次数
    const BYTE PARA_RETURN_CALLTIMES_LEADER = 14;
    struct t_Return_CallTimes_SceneSession  : t_NullCmd
    {
      t_Return_CallTimes_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_RETURN_CALLTIMES_LEADER) {};
      BYTE type;          //令牌类型
      DWORD leaderTempID;  
      DWORD times;
      DWORD qwThisID;        //令牌id
    };
    //令牌清0GM指令
    const BYTE PARA_RESET_CALLTIMES_LEADER = 15;
    struct t_Reset_CallTimes_SceneSession  : t_NullCmd
    {
      t_Reset_CallTimes_SceneSession()
        : t_NullCmd(CMD_SCENE_DARE,PARA_RESET_CALLTIMES_LEADER) {};
      DWORD leaderTempID;  
    };
    //////////////////////////////////////////////////////////////
    ///  对战指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  帮会指令开始
    //////////////////////////////////////////////////////////////
    // 场景发往会话，修改帮会资金
    const BYTE OP_UNION_MONEY_PARA = 1;
    struct t_OpUnionMoney_SceneSession : t_NullCmd
    {
      DWORD dwUnionID; // 帮会ID
      int dwMoney; //  资金
      
      t_OpUnionMoney_SceneSession()
        : t_NullCmd(CMD_SCENE_UNION,OP_UNION_MONEY_PARA)
        {
          dwUnionID = 0;
          dwMoney = 0;
        }
    };

    // 场景发往会话，修改帮会行动力
    const BYTE OP_UNION_ACTION_PARA = 2;
    struct t_OpUnionAction_SceneSession : t_NullCmd
    {
      DWORD dwUnionID; // 帮会ID
      int dwAction; //  资金
      
      t_OpUnionAction_SceneSession()
        : t_NullCmd(CMD_SCENE_UNION,OP_UNION_ACTION_PARA)
        {
          dwUnionID = 0;
          dwAction = 0;
        }
    };

    // 会话发往场景，更新有关帮会的普通信息，不用存档
    const BYTE SEND_UNION_NORMAL_PARA = 3;
    struct t_SendUnionNormal_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 族长ID
      DWORD dwMana; // 家族声望
      
      t_SendUnionNormal_SceneSession()
        : t_NullCmd(CMD_SCENE_UNION,SEND_UNION_NORMAL_PARA)
        {
          dwUserID = 0;
          dwMana = 0;
        }
    };
    
    // 检查一个玩家的善恶度
    const BYTE PARA_CHECK_USER_CITY = 4;
    struct t_checkUserCity_SceneSession : t_NullCmd
    {
      t_checkUserCity_SceneSession()
        : t_NullCmd(CMD_SCENE_UNION,PARA_CHECK_USER_CITY)
        {
          byState   = 0;
          dwCheckID  = 0;
          dwCheckedID = 0;
        };
      
      BYTE byState; // 0,未通过检查,1,通过检查
      DWORD dwCheckID; // 发起检查的玩家ID
      DWORD dwCheckedID; // 待检测玩家的ID
    };

    //////////////////////////////////////////////////////////////
    ///  帮会指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  军队指令开始
    //////////////////////////////////////////////////////////////
    // 场景发往会话，转发军队列表命令
    const BYTE REQ_ARMY_LIST_SCENE_PARA = 1;
    struct t_ReqArmyList_SceneSession : t_NullCmd
    {
      BYTE byType;
      DWORD dwUserID;
      DWORD dwCityID;
      
      t_ReqArmyList_SceneSession()
        : t_NullCmd(CMD_SCENE_ARMY,REQ_ARMY_LIST_SCENE_PARA)
        {
          byType = 0;
          dwUserID = 0;
          dwCityID = 0;
        }
    };

    const BYTE SEND_USER_ARMY_INFO_PARA = 2;
    struct t_sendUserArmyInfo_SceneSession : t_NullCmd
    {
      char title[MAX_NAMESIZE]; // 所属城市名称
      BYTE byType; // 1为队长，2为将军
      DWORD dwUserID;
      
      t_sendUserArmyInfo_SceneSession()
        : t_NullCmd(CMD_SCENE_ARMY,SEND_USER_ARMY_INFO_PARA)
        {
          bzero(title,MAX_NAMESIZE);
          byType = 0;
          dwUserID = 0;
        }
    };
    //////////////////////////////////////////////////////////////
    ///  军队指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  护宝指令开始
    //////////////////////////////////////////////////////////////
    // 会话发往场景，刷出龙精或虎魄罗汉
    const BYTE SUMMON_GEMNPC_SCENE_PARA = 1;
    struct t_SummonGemNPC_SceneSession : t_NullCmd
    {
      DWORD dwMapID;
      DWORD x;
      DWORD y;
      DWORD dwBossID;

      t_SummonGemNPC_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,SUMMON_GEMNPC_SCENE_PARA)
        {
          dwMapID = 0;
          x = 0;
          y = 0;
          dwBossID = 0;
        }
    };
    
    // 会话发往场景，清除龙精或虎魄罗汉
    const BYTE CLEAR_GEMNPC_SCENE_PARA = 2;
    struct t_ClearGemNPC_SceneSession : t_NullCmd
    {
      DWORD dwMapID;
      DWORD dwBossID;

      t_ClearGemNPC_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,CLEAR_GEMNPC_SCENE_PARA)
        {
          dwMapID = 0;
          dwBossID = 0;
        }
    };

    // 会话发往场景，设置护宝状态（龙精或虎魄）
    const BYTE SET_GEMSTATE_SCENE_PARA = 3;
    struct t_SetGemState_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwState; // 1为龙精，2为虎魄,0为清除这两种状态

      t_SetGemState_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,SET_GEMSTATE_SCENE_PARA)
        {
          dwUserID = 0;
          dwState = 0;
        }
    };
    
    // 会话发往场景，指定龙精或虎魄NPC自暴掉落物品
    const BYTE BLAST_GEMNPC_SCENE_PARA = 4;
    struct t_BlastGemNPC_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 在指定玩家身旁
      DWORD dwBossID; // 为指定NPC的ID: 1002  龙睛  1003  虎魄  

      t_BlastGemNPC_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,BLAST_GEMNPC_SCENE_PARA)
        {
          dwUserID = 0;
          dwBossID = 0;
        }
    };
    
    // 场景发往会话,进行护宝状态转移
    const BYTE CHANGE_GEMSTATE_SCENE_PARA = 5;
    struct t_ChangeGemState_SceneSession : t_NullCmd
    {
      DWORD fromUserID; // 从某玩家
      DWORD toUserID; // 转移到某玩家

      DWORD dwState; // 1,龙精，2,虎魄

      t_ChangeGemState_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,CHANGE_GEMSTATE_SCENE_PARA)
        {
          fromUserID = 0;
          toUserID = 0;
          dwState = 0;
        }
    };

    // 场景发往会话,取消并重置某护宝状态
    const BYTE CANCEL_GEMSTATE_SCENE_PARA = 6;
    struct t_CancelGemState_SceneSession : t_NullCmd
    {
      DWORD dwUserID; // 要取消的玩家
      DWORD dwState; // 待取消的状态1,龙精，2,虎魄,0所有状态取消

      t_CancelGemState_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,CANCEL_GEMSTATE_SCENE_PARA)
        {
          dwUserID = 0;
          dwState = 0;
        }
    };

    // 场景发往会话,设置护宝任务开始和结束
    const BYTE OP_GEMSTATE_SCENE_PARA = 7;
    struct t_OpGemState_SceneSession : t_NullCmd
    {
      DWORD dwState; // 1为开始，0为结束

      t_OpGemState_SceneSession()
        : t_NullCmd(CMD_SCENE_GEM,OP_GEMSTATE_SCENE_PARA)
        {
          dwState = 0;
        }
    };

    //////////////////////////////////////////////////////////////
    ///  护宝指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    ///  推荐系统指令开始
    //////////////////////////////////////////////////////////////
    // 会话发往场景，进行奖励
    const BYTE PICKUP_RECOMMEND_SCENE_PARA = 1;
    struct t_PickupRecommend_SceneSession : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwMoney;
      BYTE  byType; // 0,推荐人提取奖励,1被推荐人提取奖励

      t_PickupRecommend_SceneSession()
        : t_NullCmd(CMD_SCENE_RECOMMEND,PICKUP_RECOMMEND_SCENE_PARA)
        {
          dwUserID = 0;
          dwMoney = 0;
          byType = 0;
        }
    };
    //////////////////////////////////////////////////////////////
    ///  推荐系统指令结束
    //////////////////////////////////////////////////////////////
  };
};

/**
 * \brief 用户信息服务类命令
 */

namespace Cmd
{
  namespace UserServer
  {
    const int SEQ_MAX_LENGTH = 32;    //交易序列号长度
    const int ID_MAX_LENGTH = 64;    //帐号长度
    const int REMARK_LENGTH = 200;    //备注长度
    const int CARDID_LENGTH = 32;
    const int PCARD_NO_LENGTH = 20;    //道具卡号长度

    const BYTE CMD_USER_LOGON = 1;     //登陆服务器命令
    const BYTE CMD_USER_CONSUME = 2;   //玩家扣费命令
    const BYTE CMD_USER_FILLIN = 3;   //玩家充值命令
    const BYTE CMD_USER_QBALANCE = 4;   //帐号余额查询
    const BYTE CMD_USER_MCARD = 5;     //玩家冲值月卡
    const BYTE CMD_USER_PCARD = 6;     //玩家道具卡
    const BYTE CMD_USER_SCARD = 7;    //专区卡
    struct t_logon : public Cmd::t_NullCmd
    {
      t_logon() 
        : t_NullCmd(CMD_USER_LOGON) { }
    };
    struct t_logon_OK : t_NullCmd//服务器同步命令
    {
      t_logon_OK()
        : t_NullCmd(CMD_USER_LOGON) {};
      GameZone_t   gameZone;      //游戏区
      char     name[MAX_NAMESIZE];  //区名字
      BYTE     netType;      //网络类型
    };

    struct t_cmd_consume : public Cmd::t_NullCmd
    {
      t_cmd_consume() 
        : t_NullCmd(CMD_USER_CONSUME) 
      { 
        bzero(tid,SEQ_MAX_LENGTH +1);
        bzero(remark,REMARK_LENGTH +1);
      }
      DWORD   uid;                  //UID
      int        point;                    //扣费点数  
      int       source;                    //来源
      char      tid[SEQ_MAX_LENGTH +1];    //交易序列号
      char      remark[REMARK_LENGTH +1];  //备注
      char       ip[MAX_IP_LENGTH +1];     //客户请求ip
    };

    struct t_cmd_fillin : public Cmd::t_NullCmd
    {
      t_cmd_fillin() 
        : t_NullCmd(CMD_USER_FILLIN) 
      { 
        bzero(account,ID_MAX_LENGTH +1);
        bzero(tid,SEQ_MAX_LENGTH +1);
        bzero(cardid,CARDID_LENGTH +1);
        bzero(remark,REMARK_LENGTH +1);
      }
      DWORD uid;                      //uid
      int        point;                      //充值点数  
      int       source;                      //来源
      char      account[ID_MAX_LENGTH +1];  //玩家帐号
      char      tid[SEQ_MAX_LENGTH +1];      //交易序列号
      char      cardid[CARDID_LENGTH +1];    //充值卡号
      char      remark[REMARK_LENGTH +1];    //备注
    };

    struct t_cmd_qbalance : public Cmd::t_NullCmd
    {
      t_cmd_qbalance() 
        : t_NullCmd(CMD_USER_QBALANCE) { }
      DWORD  uid;            //UID
      char      account[ID_MAX_LENGTH +1];  //玩家帐号
      char      tid[SEQ_MAX_LENGTH +1];    //交易序列号
    };

    struct t_cmd_mcard : public Cmd::t_NullCmd
    {
      t_cmd_mcard() 
        : t_NullCmd(CMD_USER_MCARD) 
      { 
        bzero(account,ID_MAX_LENGTH +1);
        bzero(tid,SEQ_MAX_LENGTH +1);
        bzero(remark,REMARK_LENGTH +1);
      }
      DWORD   uid;                    //UID
      int        point;                      //扣费点数  
      int       source;                      //来源
      char      account[ID_MAX_LENGTH +1];  //玩家帐号
      char      tid[SEQ_MAX_LENGTH +1];      //交易序列号
      char      remark[REMARK_LENGTH +1];    //备注
      char       ip[MAX_IP_LENGTH +1];       //客户请求ip
    };

    struct t_cmd_pcard : public Cmd::t_NullCmd
    {
      t_cmd_pcard() 
        : t_NullCmd(CMD_USER_PCARD) 
      { 
        bzero(tid,SEQ_MAX_LENGTH + 1);
        bzero(pcardid,sizeof(pcardid));
      }
      DWORD   uid;                  //UID
      int       source;                    //来源
      char      tid[SEQ_MAX_LENGTH +1];    //交易序列号
      char      pcardid[CARDID_LENGTH +1];//充值卡号
      char       ip[MAX_IP_LENGTH +1];     //客户请求ip
    };

    enum  //billclient与userserver通信操作码返回值
    {
      RET_OK = 0,             //成功
      RET_FAIL = -1,         //失败
      RET_ID_NOT_EXIST = -2, //用户不存在
      RET_BALANCE_NOT_ENOUGH = -3,//余额不足
      RET_PCARD_NOT_EXIST = -4,//道具卡不存在
      RET_NOTUSE_GAMEZONE = -5,//本道具卡不能在该区使用
      RET_PCARD_NOT_REUSE = -6,//道具卡不能重复使用
      RET_SCARD_ERR = -7,     //专区卡卡号错误
      RET_SCARD_PASSWD_ERR          //专区卡密码错误
    };
    
    //billclient请求类型
    enum
    {
      AT_FILLIN = 0,//充值
      AT_CONSUME = 1,//扣费
      AT_SCARD = 2, //专区卡
      AT_QBALANCE = 3,//查询
      AT_MCARD = 4, //月卡冲值
      AT_PCARD = 5, //道具卡
    };

    //回复billclient子类型
    enum
    {
      SUBAT_INVALID = -1,//billclient请求子类型
      SUBAT_GOLD = 4      //专区卡充值返回子类型//道具卡的子类型不能于该值重复
    };

    enum
    {
      KEEP = 0,     //保留
      ESALES_FILLIN = 1,//电子商城充卡
      ESALES_CONSUME = -1  //电子商城消费
    };

    const BYTE CMD_USER_RET = 5; //服务器端的返回命令
    struct t_cmd_ret : public Cmd::t_NullCmd
    {
      t_cmd_ret() 
        : t_NullCmd(CMD_USER_RET) 
      {
        balance = 0;
        bonus = 0;
        hadfilled = 0;
        ret = RET_FAIL;
        subat = SUBAT_INVALID;
      }
      char    tid[SEQ_MAX_LENGTH + 1];  //交易序列号
      int     balance;        //余额
      int     bonus;          //积分
      int     hadfilled;      //曾经充值的标志,1=曾经充值,0=没有
      int     ret;            //命令返回代码
      int      subat;          //子类型
    };
  };
};

/**
 * \brief 定义计费服务器相关指令
 */

namespace Cmd
{

  namespace Bill
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_GATE = 2;
    const BYTE CMD_FORWARD = 3;
    const BYTE CMD_REDEEM = 4;
    const BYTE CMD_STOCK = 5;


    //////////////////////////////////////////////////////////////
    /// 登陆计费服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginBill : t_NullCmd
    {
      WORD wdServerID;
      WORD wdServerType;
      t_LoginBill()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆计费服务器指令
    //////////////////////////////////////////////////////////////


    //////////////////////////////////////////////////////////////
    /// 计费服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_GATE_NEWSESSION = 1;
    struct t_NewSession_Gateway : t_NullCmd
    {
      t_NewLoginSession session;

      t_NewSession_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_NEWSESSION) {};
    };

    const BYTE PARA_GATE_LOGINVERIFY = 2;
    struct t_LoginVerify_Gateway : t_NullCmd
    {
      DWORD accid;
      DWORD loginTempID;

      t_LoginVerify_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_LOGINVERIFY) {};
    };

    const BYTE PARA_GATE_LOGINVERIFY_RETURN = 3;
    struct t_LoginVerify_Gateway_Return : t_NullCmd
    {
      DWORD accid;
      DWORD loginTempID;
      BYTE retcode;

      t_LoginVerify_Gateway_Return()
        : t_NullCmd(CMD_GATE,PARA_GATE_LOGINVERIFY_RETURN) {};
    };

    const BYTE PARA_GATE_LOGOUT = 4;
    struct t_Logout_Gateway : t_NullCmd
    {
      DWORD accid;
      DWORD loginTempID;

      t_Logout_Gateway()
        : t_NullCmd(CMD_GATE,PARA_GATE_LOGOUT) {};
    };

    /// 请求兑换金币
    const BYTE PARA_REQUEST_GATE_REDEEM_GOLD = 5;
    struct t_Request_Redeem_Gold_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD point;        /// 需兑换的点数
      
      t_Request_Redeem_Gold_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_REQUEST_GATE_REDEEM_GOLD) 
        {
          bzero(account,sizeof(account));
        };
    };

    /// 兑换金币
    const BYTE PARA_GATE_REDEEM_GOLD = 6;
    struct t_Redeem_Gold_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD dwGold;        ///   当前拥有金币数
      DWORD dwBalance;      /// 点卡余额
      BYTE byReturn;  //返回类型
      
      t_Redeem_Gold_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_REDEEM_GOLD) 
        {
          bzero(account,sizeof(account));
          charid=0;
          dwGold=0;
          dwBalance=0;
          byReturn=0;
        };
    };
    /// 请求兑换月卡
    const BYTE PARA_REQUEST_GATE_REDEEM_MONTH_CARD = 7;
    struct t_Request_Redeem_MonthCard_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      t_Request_Redeem_MonthCard_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_REQUEST_GATE_REDEEM_MONTH_CARD)
        {
          bzero(account,sizeof(account));
        };
    };
    /// 兑换月卡
    const BYTE PARA_GATE_REDEEM_MONTH_CARD = 8;
    struct t_Redeem_MonthCard_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD dwNum;  //冲值后的到期时间(time_t)
      DWORD dwBalance;      /// 点卡余额
      BYTE byReturn;  //返回类型
      t_Redeem_MonthCard_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_REDEEM_MONTH_CARD)
        {
          bzero(account,sizeof(account));
        };
    };

    /// 查询月卡和金币
    const BYTE PARA_GATE_REQUECT_CARD_GOLD = 9;
    struct t_Request_Card_Gold_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      t_Request_Card_Gold_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_REQUECT_CARD_GOLD)
        {
          bzero(account,sizeof(account));
        };
    };
     
    /// 查询返回
    const BYTE PARA_GATE_RETURN_CARD_GOLD = 10;
    struct t_Return_Card_Gold : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD dwMonthCard;  //月卡
      DWORD dwGold;  //金币
      BYTE byReturn;  //返回类型
      t_Return_Card_Gold()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_RETURN_CARD_GOLD)
        {
          bzero(account,sizeof(account));
        };
    };

    /// 查询点数
    const BYTE PARA_GATE_REQUECT_POINT = 10;
    struct t_Request_Point_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      t_Request_Point_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_REQUECT_POINT)
        {
          bzero(account,sizeof(account));
        };
    };
     
    /// 查询返回
    const BYTE PARA_GATE_RETURN_POINT = 11;
    struct t_Return_Point : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD dwPoint;  //剩余点数
      BYTE byReturn;  //返回类型
      t_Return_Point()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_RETURN_POINT)
        {
          bzero(account,sizeof(account));
        };
    };
     
    /// 消费道具卡
    const BYTE PARA_GATE_CONSUME_CARD = 12;
    struct stConSumeCardCard_Gateway : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      char cardid[CARDID_LENGTH_PARA];
      DWORD type;            ///卡类型
      stConSumeCardCard_Gateway()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_CONSUME_CARD)
        {
          bzero(account,sizeof(account));
          bzero(cardid,sizeof(cardid));
        };
    };
    /// 消费道具卡返回 
    const BYTE PARA_GATE_RETURN_CARD = 13;
    struct t_Return_ObjCard : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD subatt;  //消费子类型
      DWORD type;            ///卡类型
      DWORD balance;            ///专区卡点数
      BYTE byReturn;  //返回类型
      t_Return_ObjCard()
        : t_NullCmd(CMD_REDEEM,PARA_GATE_RETURN_CARD)
        {
          bzero(account,sizeof(account));
        };
    };
    /*
    const BYTE PARA_GATE_QUERY_GOLD = 6;
    struct t_Query_Gold_GateMoney : t_NullCmd
    {
      char account[Cmd::UserServer::ID_MAX_LENGTH+1];          /// 帐号     
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      DWORD dwNum;  //到期时间(time_t,4字节结构)
      BYTE byReturn;  //返回类型

      t_Query_Gold_GateMoney()
        : t_NullCmd(CMD_GATE,PARA_GATE_QUERY_GOLD) {};
    };
  
    enum
    {
      QUERY_SUCCESS,// 查询成功
      QUERY_BUSY,// 服务器忙
      QUERY_FAIL,// 查询失败
      QUERY_EMPTY,// 该帐号，没有记录
    };
        
    const BYTE PARA_GATE_RETURN_QUERY_GOLD = 7;
    struct t_Return_Query_Gold_GateMoney : t_NullCmd
    {
      DWORD accid;              /// 账号编号
      DWORD charid;        /// 角色ID
      double gold;        /// 帐户余额
      BYTE  state;                            /// 查询状态

      t_Return_Query_Gold_GateMoney()
        : t_NullCmd(CMD_GATE,PARA_GATE_CHANGE_GOLD) {
        gold = 0;
        accid = 0;
        };
    };
    
    const BYTE PARA_GATE_TRADE_GOLD = 8;
    struct t_Trade_Gold_GateMoney : t_NullCmd
    {
      DWORD accid;                  /// 账号编号
      DWORD charid;            /// 角色ID
      double gold;            /// 交易的金额，为正为要减少的金币数，为负为要增加的
                    /// 金币数
      DWORD object_id;          /// 交易物品的ID
      DWORD object_num;          /// 交易物品的数量

      t_Trade_Gold_GateMoney()
        : t_NullCmd(CMD_GATE,PARA_GATE_TRADE_GOLD) {
        accid = 0;
        gold = 0;
        object_id = 0;
        };
    };

    
    const BYTE PARA_RETURN_GATE_TRADE_GOLD = 9;
    struct t_Return_Trade_Gold_GateMoney : t_NullCmd
    {
      DWORD accid;                  /// 账号编号
      DWORD charid;            /// 角色ID
      double gold;            /// 金币余额
      DWORD object_id;          /// 交易物品的ID
      DWORD object_num;          /// 交易物品的数量
      BYTE  state;            /// 交易结果状态

      t_Return_Trade_Gold_GateMoney()
        : t_NullCmd(CMD_GATE,PARA_GATE_TRADE_GOLD) {
        accid = 0;
        gold = 0;
        object_id = 0;
        };
    };
    // */

    //////////////////////////////////////////////////////////////
    /// 股票指令
    //////////////////////////////////////////////////////////////
    //CMD_BILL_GATE_SCENE
    /// 股票套现
    const BYTE PARA_STOCK_FETCH = 1;
    struct t_Stock_Fetch: t_NullCmd
    {
      DWORD dwGold;          /// 套现金币数量
      DWORD dwMoney;          /// 套现银币数量
      t_Stock_Fetch()
        : t_NullCmd(CMD_STOCK,PARA_STOCK_FETCH)
        {
          dwGold=0;
          dwMoney=0;
        };
    };
    /// 股票冲值
    const BYTE PARA_STOCK_SAVE = 2;
    struct t_Stock_Save: t_NullCmd
    {
      DWORD dwGold;          /// 冲入金币数量
      DWORD dwMoney;          /// 冲入银币数量
      t_Stock_Save()
        : t_NullCmd(CMD_STOCK,PARA_STOCK_SAVE)
        {
          dwGold=0;
          dwMoney=0;
        };
    };
    /// 密码登陆成功
    const BYTE PARA_STOCK_LOGIN = 2;
    struct t_Stock_Login: t_NullCmd
    {
      t_Stock_Login()
        : t_NullCmd(CMD_STOCK,PARA_STOCK_LOGIN)
        {
        };
    };
    /// 密码登陆成功
    const BYTE PARA_STOCK_LOGOUT = 2;
    struct t_Stock_Logout: t_NullCmd
    {
      t_Stock_Logout()
        : t_NullCmd(CMD_STOCK,PARA_STOCK_LOGOUT)
        {
        };
    };
    //////////////////////////////////////////////////////////////
    /// 股票指令结束
    //////////////////////////////////////////////////////////////
    //////////////////////////////////////////////////////////////
    /// 计费服务器与网关服务器交互的指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    /// 会话服务器转发指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_FORWARD_USER = 1;
    struct t_Bill_ForwardUser : t_NullCmd
    {
      DWORD dwAccid;
      WORD  size;
      BYTE  data[0];
      t_Bill_ForwardUser()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_USER) {};
    };
    const BYTE PARA_FORWARD_BILL = 2;
    struct t_Bill_ForwardBill : t_NullCmd
    {
      DWORD dwAccid;
      WORD  size;
      BYTE  data[0];
      t_Bill_ForwardBill()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_BILL) {};
    };
    const BYTE PARA_FORWARD_BILL_TO_SCENE = 3;
    struct t_Bill_ForwardBillToScene : t_NullCmd
    {
      DWORD id;
      WORD  size;
      BYTE  data[0];
      t_Bill_ForwardBillToScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_BILL_TO_SCENE) {};
    };
    const BYTE PARA_SCENE_FORWARD_BILL = 4;
    struct t_Scene_ForwardBill : t_NullCmd
    {
      DWORD dwAccid;
      WORD  size;
      BYTE  data[0];
      t_Scene_ForwardBill()
        : t_NullCmd(CMD_FORWARD,PARA_SCENE_FORWARD_BILL) {};
    };
    // */
  };

};

/**
 * \brief 定义场景服务器相关指令
 */

namespace Cmd
{
  namespace Scene
  {
    const BYTE CMD_LOGIN = 1;
    const BYTE CMD_FORWARD = 2;
    const BYTE CMD_SCENE = 3;
    const BYTE CMD_SCENE_GATE_BILL = 4;
    const BYTE CMD_STOCK = 5;

    //////////////////////////////////////////////////////////////
    /// 登陆场景服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGIN = 1;
    struct t_LoginScene : t_NullCmd
    {
      WORD wdServerID;
      WORD wdServerType;
      t_LoginScene()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN) {};
    };

    const BYTE PARA_LOGIN_REFRESH = 2;
    struct t_Refresh_LoginScene : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      t_Refresh_LoginScene()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN_REFRESH) {};
    };

    const BYTE PARA_LOGIN_UNREG = 3;
    const BYTE UNREGUSER_RET_LOGOUT=0;
    const BYTE UNREGUSER_RET_ERROR=1;
    const BYTE UNREGUSER_RET_CHANGE_SCENE=2;
    const BYTE UNREGUSER_RET_KICKOUT=3;
    const BYTE UNREGUSER_RET_UNLOAD_SCENE=4;
    struct t_Unreg_LoginScene : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      BYTE retcode;
      BYTE map[MAX_NAMESIZE];
	  BYTE mapName[MAX_NAMESIZE];	//sky 地图名
      t_Unreg_LoginScene()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN_UNREG) {};
    };
    const BYTE PARA_LOGIN_UNREG_OK = 4;
    struct t_Unreg_LoginScene_Ok : t_NullCmd
    {
      DWORD type;            /// 卸载类型
      DWORD accid;
      DWORD id;            /// 角色
      t_Unreg_LoginScene_Ok()
        : t_NullCmd(CMD_LOGIN,PARA_LOGIN_UNREG_OK) {};
    };
    enum ChangeCountryOper {
      ENABLE_REGISTER,
      DISABLE_REGISTER,
      ENABLE_LOGIN,
      DISABLE_LOGIN,
      LIST_COUNTRY_INFO
    };
    const BYTE PARA_CHANGE_COUNTRY_STATE = 5;
    struct t_ChangeCountryStatus : t_NullCmd
    {
      BYTE  oper;              /// 操作类型
      WORD  country;            /// 卸载类型
      DWORD dwUserID;            /// 操作者的角色ID
      t_ChangeCountryStatus()
        : t_NullCmd(CMD_LOGIN,PARA_CHANGE_COUNTRY_STATE) {};
    };

    enum ChangeVerifyVersionOper {
      CHANGECODE,
      SHOWCODE
    };
    const BYTE PARA_CHANGE_VERIFY_VERSION = 6;
    struct t_ChangeVerifyVersion : t_NullCmd
    {
      BYTE  oper;              /// 操作类型
      DWORD versionCode;          /// 版本校验码
      DWORD dwUserID;            /// 操作者的角色ID
      t_ChangeVerifyVersion()
        : t_NullCmd(CMD_LOGIN,PARA_CHANGE_VERIFY_VERSION) {};
    };
    //////////////////////////////////////////////////////////////
    /// 登陆场景服务器指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    /// 场景服务器指令
    //////////////////////////////////////////////////////////////
    
    //////////////////////////////////////////////////////////////
    /// 场景服务器指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_QUERY_ACCOUNT = 1;
    struct t_Query_AccountScene : t_NullCmd
    {
      char  dwDestID;      // 被查询者ID
      DWORD dwUserID;                // 查询者ID
      t_Query_AccountScene()
        : t_NullCmd(CMD_SCENE,PARA_QUERY_ACCOUNT) {};
    };

    const BYTE PARA_COUNTRY_AND_SCENE = 2;
    struct t_countryAndScene_GateScene : t_NullCmd
    {
      DWORD userID;//玩家ID
      DWORD countryID;      //国家ID
      DWORD sceneID;                // 场景ID
      t_countryAndScene_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_COUNTRY_AND_SCENE) {};
    };
    /// 用户维护网关屏索引指令
    const BYTE PARA_FRESH_SCREENINDEX = 3;
    struct t_fresh_ScreenIndex : t_NullCmd
    {
      DWORD dwMapTempID;
      DWORD dwScreen;
      DWORD dwUserTempID;                // userID
      t_fresh_ScreenIndex()
        : t_NullCmd(CMD_SCENE,PARA_FRESH_SCREENINDEX) 
        {
          dwMapTempID = 0;
          dwScreen = 0;
          dwUserTempID = 0;
        };
    };
    struct MapIndexXY
    {
      DWORD maptempid;
      DWORD mapx;  // 宽多少屏
      DWORD mapy; // 高多少屏
    };
    /// 添加网关地图索引
    const BYTE PARA_FRESH_MAPINDEX = 4;
    struct t_fresh_MapIndex : t_NullCmd
    {
      DWORD dwSize;
      MapIndexXY mps[0]; 
      t_fresh_MapIndex()
        : t_NullCmd(CMD_SCENE,PARA_FRESH_MAPINDEX) 
        {
        };
    };
    /// 删除网关地图索引
    const BYTE PARA_REMOVE_MAPINDEX = 5;
    struct t_Remove_MapIndex : t_NullCmd
    {
      DWORD dwSize;
      DWORD dwMapTempID[0]; 
      t_Remove_MapIndex()
        : t_NullCmd(CMD_SCENE,PARA_REMOVE_MAPINDEX) 
        {
        };
    };

    ///踢掉网关上的玩家
    const BYTE PARA_KICK_USER = 6;
    struct t_kickUser_GateScene : t_NullCmd
    {
      DWORD userID;
      DWORD accid;
      t_kickUser_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_KICK_USER)
        {
          userID = 0;
          accid = 0;
        }
    };
    const BYTE PARA_SCENE_SYS_SETTING = 7;  //系统设置
    struct t_sysSetting_GateScene : t_NullCmd
    {
      BYTE name[MAX_NAMESIZE];
      DWORD id;
      BYTE sysSetting[20];
      DWORD face;
      t_sysSetting_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_SCENE_SYS_SETTING) {};
    };


    ///服务系统控制指令
    enum
    {
      ZT_SERVICE_STOP,//停止服务
      ZT_SERVICE_START,//启动服务
    };
    //金币系统控制
    const BYTE PARA_SERVICE_GOLD = 8;
    struct t_ServiceGold_GateScene : t_NullCmd
    {
      t_ServiceGold_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_SERVICE_GOLD)
        {
        }
      BYTE byType;
    };
    //股票系统控制指令
    const BYTE PARA_SERVICE_STOCK = 9;
    struct t_ServiceStock_GateScene : t_NullCmd
    {
      t_ServiceStock_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_SERVICE_STOCK)
        {
        }
      BYTE byType;
    };
    //调整网关sleep时间
    const BYTE PARA_USLEEP_TIME = 10;
    struct t_Usleep_GateScene : t_NullCmd
    {
      t_Usleep_GateScene()
        : t_NullCmd(CMD_SCENE,PARA_USLEEP_TIME)
        {
          utask=0;
          uclient=0;
        }
      DWORD utask;
      DWORD uclient;
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器转发指令
    //////////////////////////////////////////////////////////////
    // 网关到9屏用户
    const BYTE PARA_FORWARD_NINE = 1;
    struct t_Nine_ForwardScene : t_NullCmd
    {
	  unsigned short dupIndex;
      DWORD maptempid;
      DWORD screen;
      WORD  size;
      BYTE  data[0];
      t_Nine_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_NINE) {};
    };
    
    // 网关到正向5屏或者3屏用户
    const BYTE PARA_FORWARD_NINE_DIR = 2;
    struct t_Nine_dir_ForwardScene : t_NullCmd
    {
	  unsigned short dupIndex;
      DWORD maptempid;
      DWORD screen;
      WORD dir;
      WORD  size;
      BYTE  data[0];
      t_Nine_dir_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_NINE_DIR) {};
    };
    
    // 网关到反向5屏或者3屏用户
    const BYTE PARA_FORWARD_NINE_RDIR = 3;
    struct t_Nine_rdir_ForwardScene : t_NullCmd
    {
	  unsigned short dupIndex;
      DWORD maptempid;
      DWORD screen;
      WORD dir;
      WORD  size;
      BYTE  data[0];
      t_Nine_rdir_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_NINE_RDIR) {};
    };
    
    //网关到用户
    const BYTE PARA_FORWARD_USER = 4;
    struct t_User_ForwardScene : t_NullCmd
    {
      DWORD dwID;
      WORD  size;
      BYTE  data[0];
      t_User_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_USER) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_USER;};
    };

    const BYTE PARA_FORWARD_SCENE = 5;
    struct t_Scene_ForwardScene : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      WORD  size;
      BYTE  data[0];
      t_Scene_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_SCENE) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_SCENE;};
    };

    //网关到用户
    const BYTE PARA_FORWARD_MAP = 6;
    struct t_User_ForwardMap : t_NullCmd
    {
	  unsigned short dupIndex;
      DWORD maptempid;
      WORD  size;
      BYTE  data[0];
      t_User_ForwardMap()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_MAP) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_USER;};
    };
    const BYTE PARA_BILL_FORWARD_SCENE = 7;
    struct t_Bill_ForwardScene : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      WORD  size;
      BYTE  data[0];
      t_Bill_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_BILL_FORWARD_SCENE) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_SCENE;};
    };

    ///场景模拟用户发送消息到Bill
    const BYTE PARA_FORWARD_SCENE_TO_BILL = 8;
    struct t_Scene_ForwardSceneToBill : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      WORD  size;
      BYTE  data[0];
      t_Scene_ForwardSceneToBill()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_SCENE_TO_BILL) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_SCENE;};
    };
    /// 发送场景用户的消息到Bill
    const BYTE PARA_FORWARD_SCENEUSER_TO_BILL = 9;
    struct t_Scene_ForwardSceneUserToBill : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwSceneTempID;
      WORD  size;
      BYTE  data[0];
      t_Scene_ForwardSceneUserToBill()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_SCENEUSER_TO_BILL) {};
      //void init() { cmd=CMD_FORWARD;para=PARA_FORWARD_SCENE;};
    };
    ///发送到除XX之外的屏用户
    const BYTE PARA_FORWARD_NINE_EXCEPTME = 10;
    struct t_Nine_ExceptMe_ForwardScene : t_NullCmd
    {
      DWORD maptempid;
      DWORD screen;
      DWORD exceptme_id;
      WORD  size;
      BYTE  data[0];
      t_Nine_ExceptMe_ForwardScene()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_NINE_EXCEPTME) {};
    };

    // 通知网关用户更改dupIndex
    const BYTE PARA_FORWARD_DUPCHANGE = 11;
    struct t_ForwardScene_dupChange : t_NullCmd
    {
	  unsigned short dupIndex;
	  DWORD dwID;
      WORD  size;
      t_ForwardScene_dupChange()
        : t_NullCmd(CMD_FORWARD,PARA_FORWARD_DUPCHANGE) {};
    };
    //////////////////////////////////////////////////////////////
    /// 场景服务器转发指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    /// 场景服务器转发到Bill的指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_REQUEST_BILL = 1;
    struct t_Request_Bill : t_NullCmd
    {
      DWORD dwUserID;
      t_Request_Bill()
        : t_NullCmd(CMD_SCENE_GATE_BILL,PARA_REQUEST_BILL) {};
    };
    const BYTE PARA_REQUEST_POINT = 2;
    struct t_Request_Point : t_NullCmd
    {
      DWORD dwUserID;
      t_Request_Point()
        : t_NullCmd(CMD_SCENE_GATE_BILL,PARA_REQUEST_POINT) {};
    };
    const BYTE PARA_REQUEST_REDEEM_GOLD = 3;
    struct t_Request_RedeemGold : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwNum;  //需要兑换的点数
      t_Request_RedeemGold()
        : t_NullCmd(CMD_SCENE_GATE_BILL,PARA_REQUEST_REDEEM_GOLD) {};
    };
    const BYTE PARA_REQUEST_REDEEM_CARD = 4;
    struct t_Request_RedeemCard : t_NullCmd
    {
      DWORD dwUserID;
      t_Request_RedeemCard()
        : t_NullCmd(CMD_SCENE_GATE_BILL,PARA_REQUEST_REDEEM_CARD) {};
    };


    /*
    ///股票套现
    const BYTE PARA_STOCK_FETCH = 5;
    struct t_Stock_Fetch : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwGold;
      DWORD dwMoney;
      t_Stock_Fetch()
        : t_NullCmd(CMD_SOTCK,PARA_STOCK_FETCH) {};
    };
    ///股票冲值
    const BYTE PARA_STOCK_SAVE = 6;
    struct t_Stock_Save : t_NullCmd
    {
      DWORD dwUserID;
      DWORD dwGold;
      DWORD dwMoney;
      t_Stock_Save()
        : t_NullCmd(CMD_SOTCK,PARA_STOCK_FETCH) {};
    };
    // */
    //////////////////////////////////////////////////////////////
    /// 场景服务器转发到Bill的指令
    //////////////////////////////////////////////////////////////
  };

};

namespace Cmd
{
  namespace GmTool
  {
    const BYTE CMD_GMTOOL = 128;

    //聊天消息,Gateway->Super->Info->GmTool
    const BYTE PARA_CHAT_GMTOOL = 1;
    struct t_Chat_GmTool : t_NullCmd
    {
      GameZone_t zone;
      char userName[MAX_NAMESIZE];
      char gmName[MAX_NAMESIZE];
      DWORD countryID;
      DWORD sceneID;
      DWORD dwType;                   /**< 消息类型 */
      char content[256];    /**< 对话内容 */
      char server[MAX_NAMESIZE];
      BYTE size;                              // 物品数量
      stTradeObject tobject_array[0]; // 交易物品列表
      t_Chat_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_CHAT_GMTOOL)
      {
        bzero(userName,sizeof(userName));
        bzero(content,sizeof(content));
        bzero(server,sizeof(server));
        size = 0;
      }       
    };

    //GM定单,Scene->Super->Info
    const BYTE PARA_MSG_GMTOOL = 2;
    struct t_Msg_GmTool : t_NullCmd
    {
      GameZone_t zone;
      char userName[MAX_NAMESIZE];
      DWORD accid;
      char country[MAX_NAMESIZE];
      DWORD type;
      char content[512];
      WORD contact;
      char tele[101];
      int isDeal;
      DWORD startTime;
      char gmName[32];
      t_Msg_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_MSG_GMTOOL)
      {
        bzero(userName,sizeof(userName));
        bzero(country,sizeof(country));
        bzero(content,sizeof(content));
        bzero(tele,sizeof(tele));
        isDeal = 0;
        startTime = 0;
        bzero(gmName,sizeof(gmName));
      }
    };

    //GM定单回复,GmTool->Info->Super->Session
    const BYTE PARA_MSG_REPLY_GMTOOL = 3;
    struct t_Msg_Reply_GmTool : t_NullCmd
    {
      GameZone_t zone;
      char userName[MAX_NAMESIZE];
      char content[32];
      char gmName[32];
      char reply[256-32];
      DWORD userID;
      t_Msg_Reply_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_MSG_REPLY_GMTOOL)
      {
        bzero(userName,sizeof(userName));
        bzero(content,sizeof(content));
        bzero(gmName,sizeof(gmName));
        bzero(reply,sizeof(reply));
        userID = 0;
      }
    };

    //GM处罚，GmTool->Info->Super->Scene->Super->Info
    const BYTE PARA_PUNISH_GMTOOL = 4;
    struct t_Punish_GmTool : t_NullCmd
    {
      GameZone_t zone;
      char userName[MAX_NAMESIZE];
      char country[MAX_NAMESIZE];
      char server[MAX_NAMESIZE];
      char GM[MAX_NAMESIZE];
      char reason[128];
      WORD operation;
      int delay;
      WORD level;
      DWORD accid;
      DWORD startTime;
      t_Punish_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_PUNISH_GMTOOL)
      {
        bzero(userName,sizeof(userName));
        bzero(country,sizeof(country));
        bzero(server,sizeof(server));
        bzero(reason,sizeof(reason));
        operation = 0;
        delay = 0;
        level = 0;
        accid = 0;
        startTime = 0;
      }
    };

    //公告
    const BYTE PARA_BROADCAST_GMTOOL = 5;
    struct t_Broadcast_GmTool : t_NullCmd
    {
      GameZone_t zone;
      DWORD country;
      char content[256];
      DWORD time;
      DWORD interval;
      char GM[MAX_NAMESIZE];
      BYTE id;
      DWORD mapID;
      t_Broadcast_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_BROADCAST_GMTOOL)
      {
        bzero(content,sizeof(content));
        time = 0;
        interval = 0;
        country = 0;
        bzero(GM,sizeof(GM));
        id = 0;
        mapID = 0;
      }
    };

    //新GM定单,Scene->Super->Info
    const BYTE PARA_NEW_MSG_GMTOOL = 6;
    struct t_NewMsg_GmTool : t_NullCmd
    {
      GameZone_t zone;//区
      char userName[MAX_NAMESIZE];//举报者
      DWORD accid;//举报者accid
      char userCountry[MAX_NAMESIZE];//举报者国家
      DWORD type;//定单类型
      char content[512];//主要内容
      BYTE contact;//联系方式
      char tele[101];//地址、电话
      char hisName[MAX_NAMESIZE];//被举报者
      char bugCountry[8];//bug发生国家
      char bugMap[16];//bug发生地图
      char bugPos[8];//bug发生位置
      char bugTime[64];//发生时间
      char progName[64];//宜似外挂名称
      BYTE behavior;//不良游戏现象
      DWORD userID;//举报者ID
      t_NewMsg_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_NEW_MSG_GMTOOL)
      {
        bzero(userName,sizeof(userName));
        bzero(userCountry,sizeof(userCountry));
        bzero(content,sizeof(content));
        bzero(tele,sizeof(tele));
        bzero(hisName,sizeof(hisName));
        bzero(bugCountry,sizeof(bugCountry));
        bzero(bugMap,sizeof(bugMap));
        bzero(bugPos,sizeof(bugPos));
        bzero(bugTime,sizeof(bugTime));
        bzero(progName,sizeof(progName));
        behavior = 0;
        userID = 0;
      }
    };

    //日志
    const BYTE PARA_LOG_GMTOOL = 7;
    struct t_Log_GmTool : t_NullCmd
    {
      GameZone_t zone;//区
      DWORD time;//时间
      DWORD charID;
      DWORD accID;
      char GM[MAX_NAMESIZE];//GM名字
      char pos[MAX_NAMESIZE];//地图名
      char cmd[MAX_NAMESIZE];//指令名
      char content[256];//内容
      t_Log_GmTool() : t_NullCmd(CMD_GMTOOL,PARA_LOG_GMTOOL)
      {
        bzero(pos,sizeof(pos));
        bzero(cmd,sizeof(cmd));
        time = 0;
        charID = 0;
        accID = 0;
        bzero(GM,sizeof(GM));
        bzero(content,sizeof(content));
      }
    };
  };
};

/*
# Host: 192.168.2.35
# Database: RecordServer
# Table: 'GMMESSAGE'
# 
CREATE TABLE `GMMESSAGE` (
    `ID` int(10) unsigned NOT NULL auto_increment,
    `ZONE` int(10) unsigned NOT NULL default '0',
    `NAME` varchar(33) NOT NULL default '',
    `TYPE` smallint(5) unsigned NOT NULL default '0',
    `CONTENT` varchar(255) NOT NULL default '',
    `CONTACT` smallint(5) unsigned NOT NULL default '0',
    `TELE` varchar(100) NOT NULL default '',
    `START_TIME` varchar(100) NOT NULL default '',
    `STATE` int(11) NOT NULL default '0',
    `REPLY` varchar(100) NOT NULL default '',
    `ISDEAL` smallint(6) NOT NULL default '0',
    `ACCNAME` varchar(100) NOT NULL default '',
    `CONTRY` varchar(100) NOT NULL default '',
    `GMNAME` varchar(100) NOT NULL default '',
    `SERVER` varchar(100) NOT NULL default '',
    PRIMARY KEY  (`ID`)
    ) ENGINE=MyISAM DEFAULT CHARSET=latin1; 

# Host: 192.168.2.35
# Database: RecordServer
# Table: 'operator'
# 
CREATE TABLE `operator` (
    `id` int(11) NOT NULL auto_increment,
    `gmname` varchar(100) NOT NULL default '',
    `time` varchar(100) NOT NULL default '',
    `content` varchar(100) NOT NULL default '',
    `recordid` varchar(100) NOT NULL default '',
    PRIMARY KEY  (`id`)
    ) ENGINE=MyISAM DEFAULT CHARSET=latin1; 

struct stTradeObject
{
  DWORD dwObjectID;
  DWORD dwObjectTempID;
  char strName[MAX_NAMESIZE];
  BYTE upgrade;                         // 等级
  BYTE kind;      //物品类型,0普通,1蓝色,2金色,4神圣,8套装
};

*/


namespace Cmd
{
  namespace DBAccess
  {
    const BYTE CMD_LOGON = 1;
    const BYTE CMD_LOGINSERVER = 2;


    //////////////////////////////////////////////////////////////
    // 定义登陆数据库访问中间件指令
    //////////////////////////////////////////////////////////////
    const BYTE PARA_LOGON = 1;
    struct t_LogonDBAccess : t_NullCmd
    {
      t_LogonDBAccess()
        : t_NullCmd(CMD_LOGON,PARA_LOGON) {};
    };
    //////////////////////////////////////////////////////////////
    // 定义登陆数据库访问中间件指令
    //////////////////////////////////////////////////////////////

    //////////////////////////////////////////////////////////////
    // 定义数据库访问中间件与登陆服务器之间的指令
    //////////////////////////////////////////////////////////////
    enum
    {
      SESSIONCHECK_SUCCESS = 0,
      SESSIONCHECK_DB_FAILURE = 1,
      SESSIONCHECK_PWD_FAILURE = 2
    };
    const BYTE PARA_LOGINSERVER_SESSIONCHECK = 1;
    struct t_LoginServer_SessionCheck : t_NullCmd
    {
      t_LoginServer_SessionCheck()
        : t_NullCmd(CMD_LOGINSERVER,PARA_LOGINSERVER_SESSIONCHECK)
        {
          retcode = SESSIONCHECK_DB_FAILURE;
        }

      BYTE retcode;
      t_NewLoginSession session;
    };
    //////////////////////////////////////////////////////////////
    // 定义数据库访问中间件与登陆服务器之间的指令
    //////////////////////////////////////////////////////////////
  };

};

#pragma pack()

#endif //_INC_CSCOMMON_H_
