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
 * @brief interface definition for state machine
 * 
 * once the model is available, it's kind of wrapper and very simple to implement.
 * you may of course adopt the simple implementation provided in this lib.
 * or you may use the model directly, 
 * otherwise you may write your own, e.g. maybe together with the model.
 */

#ifndef FSM_IF_STATEMACHINE_H
#define FSM_IF_STATEMACHINE_H

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   class StateMachine_IF
   {
   public:
      /**
       * @brief get current state
       */
      virtual ST &currentState() = 0;

      /**
       * @brief fire an event on the state machine
       * @param event: event fired on the state machine
       * @return
       * 	the new state after processing this event
       */
      virtual void onEvent(const EVT& event) = 0;

      /**
       * @brief start running the state machine
       * @param initState: the initial state to start with
       */
      virtual void start(ST initState) = 0;
   };

} // namespace fsm

#endif // #ifndef FSM_IF_STATEMACHINE_H
