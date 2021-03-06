/*
 * Copyright (c) 2018 University of British Columbia
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are
 * met: redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer;
 * redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution;
 * neither the name of the copyright holders nor the names of its
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Authors: Ayub A. Gubran
 */

#ifndef __GPU_STANDALONE_HH__
#define __GPU_STANDALONE_HH__

#include <thread>
#include "base/statistics.hh"
#include "base/types.hh"
#include "params/GraphicsStandalone.hh"
#include "sim/clocked_object.hh"
#include "sim/eventq.hh"
#include "sim/sim_exit.hh"
#include "sim/process.hh"
#include "sim/sim_object.hh"
#include "sim/stats.hh"

class GraphicsStandalone : public ClockedObject
{
  public:
    typedef GraphicsStandaloneParams Params;
    GraphicsStandalone(const Params *p);
    ~GraphicsStandalone();
    virtual void init();
    // main simulation loop
    void tick();
    //Port to physical memory
    const PortProxy physProxy;

  protected:
    class TickEvent : public Event
   {
      private:
         GraphicsStandalone* gpu;

      public:
         TickEvent(GraphicsStandalone* _gpu) : Event(CPU_Tick_Pri), gpu(_gpu) {}
         void process() { gpu->tick(); }

         virtual const char *description() const
         {
            return "GraphicsStandalone tick";
         }
         friend GraphicsStandalone;
   };

    TickEvent tickEvent;
    bool traceStarted;
    bool traceDone;
    Tick simCycles;
    std::string tracePath;

    std::thread* traceThread;
    void runTrace(const std::string& pTracePath);
};

#endif // __Graphics_STANDALONE_HH__



