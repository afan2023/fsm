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

#include "fsm/transitionbuilder.h"

#ifndef FSM_TRANSITIONBUILDER_CC
#define FSM_TRANSITIONBUILDER_CC

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   From<ST, EVT, CTX> &TransitionBuilder<ST, EVT, CTX>::from(ST s)
   {
      _trans.from = s;
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   To<ST, EVT, CTX> &TransitionBuilder<ST, EVT, CTX>::to(ST s)
   {
      _trans.to = s;
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   On<ST, EVT, CTX> &TransitionBuilder<ST, EVT, CTX>::on(EVT e)
   {
      _trans.event = e;
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   Where<ST, EVT, CTX> & TransitionBuilder<ST, EVT, CTX>::where(Condition<CTX> c)
   {
      _trans.condition = c;
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   Where<ST, EVT, CTX> & TransitionBuilder<ST, EVT, CTX>::where(bool (*f)(const CTX&))
   {
      _trans.condition = Condition<CTX>(f);
      return *this;
   }

   template <typename ST, typename EVT, typename CTX>
   void TransitionBuilder<ST, EVT, CTX>::execute(Action<ST, EVT, CTX> a)
   {
      _trans.action = a;
      delete this;
   }

   template <typename ST, typename EVT, typename CTX>
   void TransitionBuilder<ST, EVT, CTX>::execute(void (*f)(const ST &, const EVT &, CTX &))
   {
      _trans.action = Action<ST, EVT, CTX>(f);
      delete this;
   }

} // namespace fsm

#endif // #ifndef FSM_TRANSITIONBUILDER_CC
