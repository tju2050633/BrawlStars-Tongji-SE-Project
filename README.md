
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
   1.卢嘉霖负责大部分代码设计、开发、合并和调试，以及收集了音频、部分图片素材；
   2.梁馨负责AI状态机的设计和部分代码开发，制作人物动画、部分UI组件所需的素材；
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
- [x] 退出功能
- [x] 四个英雄角色，分别为Nita,Shelly,Primo,Stu
- [x] 支持创建房间和加入房间
- [x] 支持键盘WASD及鼠标左右键操作英雄行为
- [x] 随着时间流逝，游戏出现毒圈
- [x] 最终存活的玩家为吃鸡者
- [x] 奖杯数量根据玩家名次奖励
- [x] 三个随机地图
- [x] 地图支持能量宝箱，能量可给英雄增加生命值
- [x] 支持奖杯数记录
- [x] 支持英雄使用普通攻击及大招攻击，普攻可积攒大招
- [x] 部分英雄大招可以摧毁障碍物
- [x] 支持拖拽轮盘及WAS

##### 进阶功能

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

2. animation类的使用

```
class OpeningAnimation : public Layer
{
public:
	/*创建场景和初始化*/
	static Scene* createScene();
	virtual bool init();
	CREATE_FUNC(OpeningAnimation);

	/*预加载所有图片、音频等资源*/
	void PreloadResource();

	/*切换到游戏菜单*/
	void EnterMenu(float dt);
};

```

3. AI有限状态机的使用

```

class FSMState :public Node {
public:
	virtual void execute(AI* _ai, MsgType _msgType) = 0;
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

