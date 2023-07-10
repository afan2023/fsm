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

#include "fsm/transition.h"

#include <map>

#ifndef FSM_STATE_H
#define FSM_STATE_H

namespace fsm
{

    template <typename ST, typename EVT, typename CTX>
    class State
    {
    private:
        ST _literal;
        std::map<EVT, Transition<ST, EVT, CTX>> _transitions;

    public:
        /**
         * @brief action to execute on entering this state
         */
        // StateAction_IF<ST, CTX> entryAction;
        void (*entryAction)(const ST&, CTX&);
        /**
         * @brief action to execute on exiting this state
         */
        void (*exitAction)(const ST&, CTX&);

    public:
        State() = default;
        State(ST s);

        /**
         * @brief get the transition for the specified event from this state
         */
        Transition<ST, EVT, CTX> &getTransitionOnEvent(const EVT &event);

        /**
         * @brief construct and add a transition starting from this state
         * @param trans : reference to a transition with starting state being this state,
         *     (after this call, this trans object no more needed for the state machine to run)
         */
        void addTransition(Transition<ST, EVT, CTX> &trans);
    };

} // namespace fsm

#endif // #ifndef FSM_STATE_H
