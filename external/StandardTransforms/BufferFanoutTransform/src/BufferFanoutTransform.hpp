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

#include <PhyKnight/Database/DatabaseHelper.hpp>
#include <PhyKnight/Database/Types.hpp>
#include <PhyKnight/Phy/Phy.hpp>
#include <PhyKnight/Transform/PhyTransform.hpp>
#include <cstring>

class BufferFanoutTransform : public phy::PhyTransform
{
private:
    bool isNumber(const std::string& s);

public:
    int buffer(phy::Phy* phy_inst, phy::Database* db, int max_fanout,
               std::string buffer_cell, std::string buffer_in_port,
               std::string buffer_out_port, std::string clock_port_name);

    int              run(phy::Phy* phy_inst, phy::Database* db,
                         std::vector<std::string> args) override;
    std::string      bufferName(int index);
    std::string      bufferNetName(int index);
    std::string      bufferName(std::vector<int> indices);
    std::string      bufferNetName(std::vector<int> indices);
    std::vector<int> nextBuffer(std::vector<int> current_buffer,
                                int              max_fanout);
};

DEFINE_TRANSFORM(BufferFanoutTransform, "buffer_fanout", "1.0.0",
                 "Usage: transform buffer_fanout "
                 "<max_fanout> <buffer_cell> <buffer_in_port> "
                 "<buffer_out_port> <clock_port>")