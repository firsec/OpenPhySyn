// BSD 3-Clause License

// Copyright (c) 2019, SCALE Lab, Brown University
// All rights reserved.

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are met:

// * Redistributions of source code must retain the above copyright notice, this
//   list of conditions and the following disclaimer.

// * Redistributions in binary form must reproduce the above copyright notice,
//   this list of conditions and the following disclaimer in the documentation
//   and/or other materials provided with the distribution.

// * Neither the name of the copyright holder nor the names of its
//   contributors may be used to endorse or promote products derived from
//   this software without specific prior written permission.

// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
// ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
// LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
// CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
// SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
// INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
// CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
// ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
// POSSIBILITY OF SUCH DAMAGE.

#include <OpenPhySyn/Database/DatabaseHandler.hpp>
#include <OpenPhySyn/Database/Types.hpp>
#include <OpenPhySyn/Psn/Psn.hpp>
#include <OpenPhySyn/SteinerTree/SteinerTree.hpp>
#include <OpenPhySyn/Transform/PsnTransform.hpp>
#include <cstring>
#include <memory>
#include <unordered_set>
#include "BufferTree.hpp"

namespace psn
{
class TimingBufferTransform : public PsnTransform
{

private:
    int   buffer_count_;
    int   resize_count_;
    int   net_index_;
    int   buff_index_;
    float current_area_;
    void  bufferPin(Psn* psn_inst, InstanceTerm* pin,
                    std::vector<LibraryCell*>& buffer_lib,
                    std::vector<LibraryCell*>& inverter_lib, bool resize_gates,
                    float min_gain, float area_penalty);
    std::shared_ptr<BufferSolution>
         bottomUp(Psn* psn_inst, SteinerPoint pt, SteinerPoint prev,
                  std::vector<LibraryCell*>&   buffer_lib,
                  std::vector<LibraryCell*>&   inverter_lib,
                  std::shared_ptr<SteinerTree> st_tree, bool resize_gates = false);
    void topDown(Psn* psn_inst, Net* net, std::shared_ptr<BufferTree> tree);
    void topDown(Psn* psn_inst, InstanceTerm* pin,
                 std::shared_ptr<BufferTree> tree);

    int timingBuffer(Psn* psn_inst, bool fix_cap = true, bool fix_slew = true,
                     std::unordered_set<std::string> buffer_lib_names =
                         std::unordered_set<std::string>(),
                     std::unordered_set<std::string> inverter_lib_names =
                         std::unordered_set<std::string>(),
                     bool  cluster_buffers         = false,
                     bool  cluster_inverters       = false,
                     bool  minimize_cluster_buffer = false,
                     float cluster_threshold = 0.0, bool resize_gates = false,
                     int max_iterations = 1, float min_gain = 0.0,
                     float area_penalty = 0.0);
    int fixCapacitanceViolations(Psn*                       psn_inst,
                                 std::vector<InstanceTerm*> driver_pins,
                                 std::vector<LibraryCell*>& buffer_lib,
                                 std::vector<LibraryCell*>& inverter_lib,
                                 bool resize_gates, float min_gain,
                                 float area_penalty);
    int fixTransitionViolations(Psn*                       psn_inst,
                                std::vector<InstanceTerm*> driver_pins,
                                std::vector<LibraryCell*>& buffer_lib,
                                std::vector<LibraryCell*>& inverter_lib,
                                bool resize_gates, float min_gain,
                                float area_penalty);

public:
    TimingBufferTransform();

    int run(Psn* psn_inst, std::vector<std::string> args) override;
};

DEFINE_TRANSFORM(
    TimingBufferTransform, "timing_buffer", "1.4",
    "Performs several variations of buffering and resizing to fix timing "
    "violations",
    "Usage: transform timing_buffer [-auto_buffer_library "
    "<single|small|medium|large|all>] [-minimize_buffer_library] "
    "[-use_inverting_buffer_library] [-buffers "
    "<buffer library>] [-inverters "
    "<inverters library>] [-iterations <# iterations=1>] [-min_gain "
    "<gain=0ps>] [-enable_gate_resize] [-area_penalty <penalty=0ps/um>]")

} // namespace psn
