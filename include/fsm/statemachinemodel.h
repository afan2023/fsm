//////////////////////////////////////////////////////////////////////////////////////
// BSD 3-Clause License                                                             //
//                                                                                  //
// Copyright (c) 2023, c.fan                                                        //
//                                                                                  //
// Redistribution and use in source and binary forms, with or without               //
// modification, are permitted provided that the following conditions are met:      //
//                                                                                  //
// 1. Redistributions of source code must retain the above copyright notice, this   //
//    list of conditions and the following disclaimer.                              //
//                                                                                  //
// 2. Redistributions in binary form must reproduce the above copyright notice,     //
//    this list of conditions and the following disclaimer in the documentation     //
//    and/or other materials provided with the distribution.                        //
//                                                                                  //
// 3. Neither the name of the copyright holder nor the names of its                 //
//    contributors may be used to endorse or promote products derived from          //
//    this software without specific prior written permission.                      //
//                                                                                  //
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"      //
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE        //
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE   //
// DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE     //
// FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL       //
// DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR       //
// SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER       //
// CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,    //
// OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE    //
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.             //
////////////////////////////////////////////////////////////////////////////////////// 

#include "fsm/state.h"
#include "fsm/transition.h"
#include "fsm/if_transitionbuilder.h"

#include <map>
#include <vector>

#ifndef FSM_STATEMACHINEMODEL_H
#define FSM_STATEMACHINEMODEL_H

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   class StateMachineModel
   {
   private:
      using FsmState = State<ST, EVT, CTX>;
      /**
       * @brief all states of the model
       */
      std::map<ST, FsmState> _states;
      using FsmTransition = Transition<ST, EVT, CTX>;
      // a temporary holder in building phase
      std::vector<FsmTransition> _transitions;

   public:
      virtual ~StateMachineModel() = default;

      /**
       * @brief build transition
       */
      virtual TransitionBuilder_IF<ST, EVT, CTX> &addTransition();

      /**
       * @brief specify the entry action on a state
       * @param state: the state on which the entry action is specified
       * @param act: the action on the state
       * @return reference to the state machine itself
       */
      virtual StateMachineModel<ST, EVT, CTX> &withEntryActionOnState(ST state, void (*act)(const ST &s, CTX &c));

      /**
       * @brief specify the exit action on a state
       * @param state: the state on which the exit action is specified
       * @param act: the action to execute on the state exit
       * @return reference to the state machine
       */
      virtual StateMachineModel<ST, EVT, CTX> &withExitActionOnState(ST state, void (*act)(const ST &s, CTX &c));

      /**
       * @brief make an integral state machine model ready to use
       * @return 0 if OK, otherwise if fail
       */
      virtual int pack();

      /**
       * @brief fire an event on the state machine
       * @param state: the state when the event is received
       * @param event: event on the state machine
       * @param context: the context when this happens
       * @return
       * 	the new state after processing this event
       */
      virtual ST &onEvent(const ST &state, const EVT &event, CTX &context);
   };

}

#endif // #ifndef FSM_STATEMACHINEMODEL_H
