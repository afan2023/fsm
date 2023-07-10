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

/**
 * @brief interface definition for building state machine transitions
 */

#include "fsm/condition.h"
#include "fsm/action.h"

#ifndef FSM_IF_TRANSITIONBUILDER_H
#define FSM_IF_TRANSITIONBUILDER_H

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   class Where
   {
   public:
      /**
       * @brief specify the action to execute in the transition
       * @param act - the action to execute
       */
      virtual void execute(Action<ST, EVT, CTX> act) = 0;
   };

   template <typename ST, typename EVT, typename CTX>
   class On
   {
   public:
      /**
       * @brief specify the condition for the transition
       * @param cond - the condition
       */
      virtual Where<ST, EVT, CTX> &where(Condition<CTX> cond) = 0;
   };

   template <typename ST, typename EVT, typename CTX>
   class To
   {
   public:
      /**
       * @brief specify the event on which the transition may happen
       * @param event - the event
       */
      virtual On<ST, EVT, CTX> &on(EVT event) = 0;
   };

   template <typename ST, typename EVT, typename CTX>
   class From
   {
   public:
      /**
       * @brief specify the state to be if the transition does happen
       * @param state - the state might to be
       */
      virtual To<ST, EVT, CTX> &to(ST state) = 0;
   };

   template <typename ST, typename EVT, typename CTX>
   class TransitionBuilder_IF
   {
   public:
      /**
       * @brief specify the state to start from
       * @param state - the state to start from
       */
      virtual From<ST, EVT, CTX> &from(ST state) = 0;
   };

} // namespace fsm

#endif // #ifndef FSM_IF_TRANSITIONBUILDER_H
