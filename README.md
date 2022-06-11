
# BrawlStars项目说明文档
> 同济大学软件学院2022年面向对象程序设计课程大项目
## 项目信息
- 项目选题：荒野乱斗
- 项目成员：卢嘉霖、李佩耘、李恒鑫、梁馨
- Github地址：https://github.com/tju2050633/BrawlStars-Tongji-SE-Project
- 项目进度时间线：


## 项目开发文档
- 选用引擎：Cocos2d-x 4.0
- 辅助软件：Tiled Map Editor 1.8.4 、Adobe Photoshop CC 2020
- 支持平台：Windows  （此项待定）
- 小组分工：
   1.卢嘉霖负责大部分代码设计、开发、合并和调试，收集了音频、部分图片素材，实现macOS平台的运行；
   2.梁馨负责AI状态机的设计和部分代码开发，制作人物动画、部分UI组件所需的素材，打包项目和项目文档撰写；
   3.李佩耘负责了瓦片地图的制作，以及大部分与瓦片地图交互的函数；
   4.李恒鑫负责了设置和菜单场景、音频引擎控制音量。

### 类的设计及继承关系


#### 评分项完成度

```
gantt
    title 进度时间
    dateFormat  MM-DD
    section  配置环境与学习     
    学习 Cocos2d-x              :a1, 05-01, 14d
    section 代码实现
    Debug    :  05-12  , 19d
    完成Scence架构 :  05-12  , 2d
    完成角色类架构 :   05-14 , 4d
     完成Entity架构 :   05-18 , 2d
     完成TMX地图加载 :   05-20 , 7d
     完成UI组件:   05-28 , 4d
     完成攻击技能:   05-30 , 4d
     完成地图:  05-30, 6d
    section Debug
    Debug    :  05-12  ,27d
 
```


---
##### 基础功能
- [x] 游戏开始动画界面
- [x] 背景音乐及按键音乐音量控制
- [x] 暂停及恢复功能
- [x] 退出功能
- [x] 四个英雄角色，分别为Nita,Shelly,Primo,Stu
- [x] 支持创建房间和加入房间
- [x] 支持键盘WASD及鼠标左右键操作英雄行为
- [x] 随着时间流逝，游戏出现毒圈
- [x] 最终存活的玩家为吃鸡者
- [x] 奖杯数量根据玩家名次奖励
- [x] 三幅单人荒野决斗地图
- [x] 地图支持能量宝箱，能量可给英雄增加生命值
- [x] 支持奖杯数记录
- [x] 支持英雄使用普通攻击及大招攻击，普攻可积攒大招

##### 进阶功能

- [x] 表情系统
- [x] 显示攻击、技能的范围指示器
- [x] UI界面还原原版手游，随着操纵指示变化
- [x] 英雄可与地图交互，如英雄在草丛中隐藏和发现近距离敌人等
- [x] 英雄大招有特殊效果，部分英雄大招可以摧毁障碍物
- [x] AI自动寻找目标、识别敌人、避开障碍、寻找宝箱buff等
- [x] 英雄中毒、击杀敌人、死亡、获胜等有特殊音效
- [x] 支持Windows和MacOS双系统运行

###### C++新特性
- [x] 基于范围的for循环
- [x] 类型推断
- [x] Lambda表达式

###### 基础亮点

###### 代码亮点

1. Const.h头文件的使用

```
/*雪莉Shelly 属性*/

const int SHELLY_HP = 3990;		//血量HealthPoint
const int SHELLY_AD = 345;		//攻击力AttackDamage
const int SHELLY_MS = 50;		//移速MoveSpeed
const int SHELLY_AI = 0.8;		//攻击间隔AttackInterval
const int SHELLY_EB = 3450;		//能量条EnergeBar

const int SHELLY_BULLET_SPEED = 400;//子弹速度
const int SHELLY_BULLET_RANGE = 300;//射程

```

2. 预加载资源的使用

```
class OpeningAnimation : public Layer
{
public:
	...
	
	/*预加载所有图片、音频等资源*/
	void PreloadResource();
	
	...
};

/*预加载所有图片、音频等资源*/
void OpeningAnimation::PreloadResource()
{
	/*音乐音效*/
	SimpleAudioEngine::getInstance()->preloadBackgroundMusic("Music/ButtonEffect.mp3");
	...
	
	/*精灵图*/
	Director::getInstance()->getTextureCache()->addImage("trophy.png");
	...
}

```

3.Utils工具类的使用

```

class SceneUtils
{
public:
	/*枚举所有场景*/
	enum AllScenes
	{
		OpeningAnimation,
		GameMenu,
	};
	...
	
	/*静态成员变量，存储切换场景时用到的信息*/
	static AllMap _map;				
	...

	/*共用，切换场景时使用，参数为该对象内枚举数*/
	static void changeScene(AllScenes targetScene);
	
	...

	/*放置背景图，所有场景类共用，loadWay区分加载背景图方式*/
	static void setBGimage(const char* filename, Layer* layer, setBGimageWith loadWay);
};

```

4. PLIST文件的使用

```
   <key>bear_Attack1.png</key>
            <dict>
                <key>aliases</key>
                <array/>
                <key>spriteOffset</key>
                <string>{-2,0}</string>
                <key>spriteSize</key>
                <string>{117,86}</string>
                <key>spriteSourceSize</key>
                <string>{223,182}</string>
                <key>textureRect</key>
                <string>{{184,156},{117,86}}</string>
                <key>textureRotated</key>
                <false/>
            </dict>
```

5. 接口类的使用

```

 class ControllerListener {
public:
	/*设置、获取位置*/
	virtual void setTargetPosition(Vec2 position) = 0;
	virtual Vec2 getTargetPosition() = 0;
	/*设置和获取目标当前速度（不是英雄固有移速属性）*/
	virtual void setTargetMoveSpeedX(int speedX) = 0;
	virtual void setTargetMoveSpeedY(int speedY) = 0;
	virtual INT32 getTargetMoveSpeedX() = 0;
	virtual INT32 getTargetMoveSpeedY() = 0;
	/*获取英雄*/
	virtual Brawler* getTargetBrawler() = 0;
};

```



