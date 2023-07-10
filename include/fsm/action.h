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
 * @brief Action to execute
 */

#ifndef FSM_ACTION_H
#define FSM_ACTION_H

namespace fsm
{

   template <typename ST, typename EVT, typename CTX>
   class Action
   {
   private:
      /**
       * the execution function
       */
      void (*_fn)(const ST &s, const EVT &e, CTX &c);

   public:
      /**
       * @brief NULL ACTION does nothing
       */
      static Action NULL_ACTION;

      /**
       * @brief default constructor
       */
      Action() : _fn(nullptr){};
      /**
       * @brief constructor with executor (function) passed
       * @param f: the function to execute
       */
      Action(void (*f)(const ST &s, const EVT &e, CTX &c)) : _fn(f){};

      /**
       * @brief the execution function will be changed after this assignment
       */
      Action &operator=(void (*f)(const ST &s, const EVT &e, CTX &c))
      {
         _fn = f;
         return *this;
      }

      /**
       * @brief execute the action
       * @param s: the state
       * @param e: the event received
       * @param c: the context
       */
      void operator()(const ST &s, const EVT &e, CTX &c)
      {
         if (_fn != nullptr)
            _fn(s, e, c);
      }
   };

   template <typename ST, typename EVT, typename CTX>
   Action<ST, EVT, CTX> Action<ST, EVT, CTX>::NULL_ACTION; // = Action<ST,EVT,CTX>();

} // namespace fsm

#endif // #ifndef FSM_ACTION_H
