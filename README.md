# BrawlStars项目说明文档
> 同济大学软件学院2022年面向对象程序设计课程大项目
## 项目信息
- 项目选题：荒野乱斗
- 项目成员：卢嘉霖、李佩耘、李恒鑫、梁馨
- Github地址：https://github.com/tju2050633/BrawlStars-Tongji-SE-Project
- 项目进度时间线：

![1](D:\1\second_term\期末项目\1.png)




## 项目开发文档
- 选用引擎：Cocos2d-x 4.0
- 辅助软件：Tiled Map Editor 1.8.4 、Adobe Photoshop CC 2020
- 支持平台：Windows  ，macOS
- 小组分工：
   1.卢嘉霖负责大部分代码设计、开发、合并和调试，收集了音频、部分图片素材，实现macOS平台的运行；
   2.梁馨负责AI状态机的设计和部分代码开发，制作人物动画、部分UI组件所需的素材，打包项目和项目文档撰写；
   3.李佩耘负责了瓦片地图的制作，以及大部分与瓦片地图交互的函数；
   4.李恒鑫负责了设置和菜单场景、音频引擎控制音量。

### 整体架构设计

![first](D:\1\second_term\期末项目\first.png)

![second](D:\1\second_term\期末项目\second.png)

![third](D:\1\second_term\期末项目\third.png)




#### 评分项完成度

```
gantt
    title 进度时间
    dateFormat  MM-DD
    section  配置环境与学习     
    学习 Cocos2d-x              :a1, 05-01, 14d
    section 代码实现
    ebug    :  05-12  , 19d
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


### 实现的功能点+实现思路
 - 功能点0 : 预先加载所需音频、图像等资源文件，减少游戏过程卡顿
实现思路：开场动画的静态画面中预加载了所有资源，加载完毕后跳转进游戏界面。

 - 功能点1:多个场景，可来回切换并保留信息（选择的地图、英雄等）
实现思路：多个Layer类各自独立设计场景，通过场景工具类的静态全局函数实现场景切换和场景信息的保留。

 - 功能点2:音乐和音效控制。
实现思路：设计音乐工具类封装音乐切换、暂停、恢复、音量调节等功能，并绑定为菜单项的回调函数。

 - 功能点3:人物的移动和攻击/技能控制，控制器UI界面、攻击/技能范围指示器随着键鼠输入变化
实现思路：设计控制器类，监听键盘和鼠标事件，在事件回调函数中实现按键后的效果。人物移动通过设置人物实际移速实现（主场景每帧根据移速刷新人物位置，一般状态下移速为0，接受到控制时移速设为对应值实现移动），人物攻击/技能通过读取鼠标事件回调函数呢中调用监听对象（英雄）的成员函数实现。控制器UI的变化同理，为监听事件回调函数的一部分。

 - 功能点4:障碍物阻止移动、阻挡子弹，部分英雄技能可摧毁障碍物
实现思路：主场景设置对象位置时监测新位置是否是障碍物单元格，若是则不更新位置（英雄）、摧毁对象（普通攻击子弹）或摧毁障碍物（部分英雄技能）。

 - 功能点5:子弹碰撞宝箱、英雄、墙体等
实现思路：每帧刷新子弹位置，若监测到子弹进入对象碰撞体积则造成伤害、子弹消失并返回发射者伤害值的能量。

 - 功能点6:人物属性控制，受到伤害、获得能量、获得buff、死亡等
实现思路：全部封装在英雄类中，发生相应事件时调用对应成员函数修改人物属性，且成员函数负责了界面上属性的显示情况更新。

 - 功能点7:毒圈收缩
实现思路：封装为主场景的成员函数，修改毒圈地图层的属性并刷新显示实现。

 - 功能点8:草丛隐藏人物，近处草内人物显示
实现思路：主场景每帧设置人物位置时监测是否进入草丛，若为AI将其隐藏，若为玩家设为半透明。AI定时刷新目标英雄时会监测是否有英雄进入周围视野范围，若是设置其为相应状态。

 - 功能点9:人物移动动画
实现思路：设计动画工具类，人物发生移动、转向、停止等行为时调用工具类的静态成员函数，该函数从缓存中读取英雄移动的动画帧并创建动画。

 - 功能点10:AI自动寻敌、摧毁宝箱、获取buff、避开障碍物等
实现思路：AI类含有英雄对象指针，并定时刷新目的地、目标对象、实际速度等成员变量（在自行设计的update函数中，通过遍历场景所有对象并加上在草丛里、在视野范围外等限制条件，定时获取最佳目标和目的地）。目标进入攻击射程后，调用英雄攻击/技能函数。遇到障碍物时，通过实际速度成员变量识别障碍物情况，并作出调整以避开。

 - 功能点11:游戏结束，暂停游戏并计算名次、奖励等。
实现思路：场景工具类记录剩余英雄数，玩家死亡或英雄数为2时结束游戏，根据英雄数计算名次和奖励，通过导演对象暂停场景并隐藏UI界面、创建显示名次、奖励和返回按钮的界面。

 - 功能点12:奖杯数在程序结束后保留
实现思路：奖杯数通过读取txt文件获得，修改时写入txt文件，确保程序重新启动时奖杯数会保留。

### 项目的技术难点+解决方案+解决过程


 - 技术难点1:人物通过技能出界导致程序崩溃
解决方案：缩小实际可活动范围，禁止人物移动到地图边缘单元格，子弹等物体移出地图范围时销毁

 - 技术难点2:AI自动行为不够智能，时常被障碍物卡住
解决方案：设计AI的速度调节属性，遇到障碍物时向垂直方向尝试避开，延长调节速度时间范围（不是每帧刷新），防止AI被墙体卡住时反复来回转向

 - 技术难点3:子弹监测碰撞时人物碰撞体积与实际贴图面积不符合，出现过人物碰撞体积过大导致明显显示错误的BUG
解决方案：排查发现是plist精灵图集属性问题，修改后碰撞体积与贴图完全符合、






### 代码亮点

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
