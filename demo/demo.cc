/**
 * g++ -std=c++17 -I../include demo.cc -o demo
 */
#include "fsm.h"

#include <iostream>

using namespace std;
using namespace fsm;

enum STATE_ENUM
{
   ST1 = 1,
   ST2,
   ST3,
   ST4,
   ST5
};

enum EVENT_ENUM
{
   EVT1 = 1,
   EVT2,
   EVT3
};

struct TestContext
{
   int data = 0;
   std::string info = "initial.";
};

bool testConditionFunc(const TestContext &ctx)
{
   return ctx.data < 10;
}

int tryStateMachine()
{
   TestContext ctx;

   StateMachineModel<STATE_ENUM, EVENT_ENUM, TestContext> model;
   cout << "Let's start construction......" << endl;
   auto fn1 = [](const STATE_ENUM &s, const EVENT_ENUM &e, TestContext &c)
   {
      c.data += ST1 + ST2;
      c.info = "we're transiting from ST1 to ST2 on EVT1";
   };
   auto acten1 = [](const STATE_ENUM &s, TestContext &c)
   {
      std::cout << "I'm entering ST1" << std::endl;
   };

   cout << "add transitions..." << endl;
   model.addTransition()
       .from(ST1)
       .to(ST2)
       .on(EVT1)
       .where(testConditionFunc)
       .execute(Action<STATE_ENUM, EVENT_ENUM, TestContext>(fn1));
   model.addTransition()
       .from(ST2)
       .to(ST1)
       .on(EVT2)
       .where(NULL_CONDITION<TestContext>)
       .execute([](const STATE_ENUM &s, const EVENT_ENUM &e, TestContext &c){
              c.data += e;
              c.info = "transited from ST2 to ST1";
           });
   cout << "add entry and exit states..." << endl;
   model.withEntryActionOnState(ST1, acten1)
       .withEntryActionOnState(ST2, nullptr)
       .withExitActionOnState(ST2, [](const STATE_ENUM &s, TestContext &c)
                              { std::cout << "I'm leaving ST2" << std::endl; });

   cout << "pack the model..." << endl;
   model.pack();

   cout << "create a state machine..." << endl;
   StateMachine<STATE_ENUM, EVENT_ENUM, TestContext> sm(model, ctx);

   cout << "start the state machine..." << endl;
   sm.start(ST1);

   std::cout << "we start from " << sm.currentState() << std::endl;
   std::cout << "context data = " << ctx.data << "; info = " << ctx.info << std::endl;

   for (int i = 0; i < 3; i++)
   {
      // because of the condition check, once ctx.data >= 10, the state machine won't transit
      sm.onEvent(EVT1);

      std::cout << "on event " << EVT1 << ", we transit to " << sm.currentState() << std::endl;
      std::cout << "context become data = " << ctx.data << "; info = " << ctx.info << std::endl;

      sm.onEvent(EVT2);

      std::cout << "on event " << EVT2 << ", we transit to " << sm.currentState() << std::endl;
      std::cout << "context become data = " << ctx.data << "; info = " << ctx.info << std::endl;
   }

   return 0;
}

int main(int argc, char **argv)
{
   return tryStateMachine();
}
