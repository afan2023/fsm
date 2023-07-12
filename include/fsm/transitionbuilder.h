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

#include "fsm/if_transitionbuilder.h"
#include "fsm/transition.h"
#include "fsm/action.h"

#ifndef FSM_TRANSITIONBUILDER_H
#define FSM_TRANSITIONBUILDER_H
namespace fsm
{
    template <typename ST, typename EVT, typename CTX>
    class TransitionBuilder : public TransitionBuilder_IF<ST, EVT, CTX>,
                              public From<ST, EVT, CTX>,
                              public To<ST, EVT, CTX>,
                              public On<ST, EVT, CTX>,
                              public Where<ST, EVT, CTX>
    {
    public:
        TransitionBuilder(Transition<ST, EVT, CTX> &t) : _trans(t){};
        virtual From<ST, EVT, CTX> &from(ST state);
        virtual To<ST, EVT, CTX> &to(ST state);
        virtual On<ST, EVT, CTX> &on(EVT event);
        virtual Where<ST, EVT, CTX> &where(Condition<CTX> cond);
        virtual Where<ST, EVT, CTX> &where(bool (*f)(const CTX&));
        virtual void execute(Action<ST, EVT, CTX> act);
        virtual void execute(void (*f)(const ST&, const EVT&, CTX&));

    private:
        Transition<ST, EVT, CTX> &_trans;
    };

} // namespace fsm

#endif // #ifndef FSM_TRANSITIONBUILDER_H
