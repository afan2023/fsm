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

#include "fsm/if_statemachine.h"
#include "fsm/statemachinemodel.h"

#ifndef FSM_STATEMACHINE_H
#define FSM_STATEMACHINE_H

namespace fsm
{

    template <typename ST, typename EVT, typename CTX>
    class StateMachine : public StateMachine_IF<ST, EVT, CTX>
    {
    private:
        /**
         * ready?
         */ 
        bool _started;
        /**
         * current state
         */
        ST _state;
        /**
         * context where the state machine is in
         */
        CTX &_context;
        /**
         * model
         */
        StateMachineModel<ST, EVT, CTX> &_model;

    public:
        StateMachine(StateMachineModel<ST, EVT, CTX> &model, CTX &ctx);

        virtual ST &currentState();

        virtual void onEvent(const EVT& event);

        virtual void start(ST initState);

    }; // class StateMachineImpl

} // namespace fsm

#endif // #ifndef FSM_STATEMACHINE_H
