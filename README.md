# fsm
a state machine template library



The APIs are documented within the code. The demo (/demo/demo.cc) shows a way in which this lib is expected to be used. Check & enjoy!



不写C++久矣，写个状态机模板试试。

应用这个库分两个阶段，先构建状态机，后使用之。

构建状态机模型（`StateMachineModel`），主要是规定其状态迁移(Transition)，可以用如下方式

```c++
   model.addTransition()
       .from(ST1)
       .to(ST2)
       .on(EVT1)
       .where(testConditionFunc)
       .execute(fn1);
```

（另外还可以指定状态的进入或退出动作`withEntryActionOnState`、 `withExitActionOnState`，应该相对不常用。）

模型built后可以直接使用，或者象 demo 那样外面包一层 `StateMachine`。使用的话就是调用 `onEvent` 传事件给它。

```
   sm.onEvent(EVT1);
```

代码接口上注释比较详细，这里就不多写了。



算是一种“糖“吧:-)



Jul. 2023

c.fan

