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

#include "fsm/statemachinemodel.h"
#include "fsm/transitionbuilder.h"

#ifndef FSM_STATEMACHINEMODEL_CC
#define FSM_STATEMACHINEMODEL_CC

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   TransitionBuilder_IF<ST, EVT, CTX>& StateMachineModel<ST, EVT, CTX>::addTransition()
   {
      _transitions.emplace_back(Transition<ST, EVT, CTX>());
      TransitionBuilder<ST, EVT, CTX> *pBuilder = new TransitionBuilder<ST, EVT, CTX>(_transitions.back());
      return *pBuilder;
   }

   template <typename ST, typename EVT, typename CTX>
   StateMachineModel<ST, EVT, CTX> &
   StateMachineModel<ST, EVT, CTX>::withEntryActionOnState(ST istate, void (*act)(const ST &s, CTX &c))
   {
      ST& state = istate;
      if (_states.find(state) == _states.end())
      {
         _states.emplace(state, State<ST, EVT, CTX>(state));
      }
      
      _states[state].entryAction = act;
      
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   StateMachineModel<ST, EVT, CTX> &
   StateMachineModel<ST, EVT, CTX>::withExitActionOnState(ST state, void (*act)(const ST &s, CTX &c))
   {
      if (_states.find(state) == _states.end())
      {
         _states.emplace(state, State<ST, EVT, CTX>(state));
      }

      State<ST, EVT, CTX> &s = _states[state];
      s.exitAction = act;

      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   int StateMachineModel<ST, EVT, CTX>::pack()
   {
      int retcount = 0;
      int tindex = 0;

      for (auto &t : _transitions)
      {
         if (_states.find(t.from) == _states.end())
         {
            _states.emplace(t.from, State<ST, EVT, CTX>(t.from));
         }
         if(_states.find(t.to) == _states.end())
         {
            _states.emplace(t.to, State<ST, EVT, CTX>(t.to));
         }
         State<ST, EVT, CTX> &s = _states[t.from];
         s.addTransition(t);
      }

      _transitions.clear();

      return retcount;
   }

   template <typename ST, typename EVT, typename CTX>
   ST &StateMachineModel<ST, EVT, CTX>::onEvent(const ST& state, const EVT& event, CTX& context)
   {
      if (_states.find(state) == _states.end())
      {
         return const_cast<ST &>(state);
      }

      State<ST, EVT, CTX> &s = _states[state];
      Transition<ST, EVT, CTX> &trans = s.getTransitionOnEvent(event);
      if (!trans.condition.isSatisfied(context)){
         return const_cast<ST &>(state);
      }

      if ((trans.to != state) && s.exitAction)
      {
         s.exitAction(state, context);
      }

      ST &newState = trans.doTransit(state, event, context);

      if (newState != state)
      {
         if(_states[newState].entryAction)
            _states[newState].entryAction (newState, context);
      }

      return newState;
   }

} // namespace fsm

#endif // #ifndef FSM_STATEMACHINEMODEL_CC
