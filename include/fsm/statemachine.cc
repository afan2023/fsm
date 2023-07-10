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

#include "fsm/statemachine.h"
#include "fsm/state.h"

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   StateMachine<ST, EVT, CTX>::StateMachine(StateMachineModel<ST, EVT, CTX> &model, CTX &ctx)
       : _model(model), _context(ctx), _started(false)//, _state(_initState) 
       {}

   template <typename ST, typename EVT, typename CTX>
   ST &StateMachine<ST, EVT, CTX>::currentState()
   {
      return _state;
   }

   template <typename ST, typename EVT, typename CTX>
   void StateMachine<ST, EVT, CTX>::onEvent(const EVT& event)
   {
      if (_started)
      {
         _state = _model.onEvent(_state, event, _context);
      }
   }

   template <typename ST, typename EVT, typename CTX>
   void StateMachine<ST, EVT, CTX>::start(ST initState)
   {
      _state = initState;
      _started = true;
   }

} // namespace fsm
