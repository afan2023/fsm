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

#ifndef FSM_CONDITION_H
#define FSM_CONDITION_H

namespace fsm
{

   template <typename CTX>
   class Condition
   {
   private:
      bool (*_checkFn)(const CTX &);

   public:
      /**
       * constructor
       */
      Condition() : _checkFn(nullptr){};
      /**
       * construct from a check function
       */
      Condition(bool (*fn)(const CTX &)) : _checkFn(fn){};

      /**
       * @brief is the condition satisfied?
       * @param ctx : the context
       */
      bool isSatisfied(const CTX &ctx)
      {
         if (!_checkFn) // NULL condition
            return true;
         else
            return _checkFn(ctx);
      }
      /**
       * @brief null condition (i.e. pass without check)
       */
      static Condition NULL_CONDITION;
      /**
       * @brief False condition (i.e. always not satisfied)
       */
      static Condition FALSE_CONDITION;
   }; // class Condition

   template <typename CTX>
   Condition<CTX> Condition<CTX>::NULL_CONDITION;

   template <typename CTX>
   Condition<CTX> Condition<CTX>::FALSE_CONDITION = Condition<CTX>([](const CTX &c)
                                                                   { return false; });

} // namespace fsm
#endif // #ifndef FSM_CONDITION_H