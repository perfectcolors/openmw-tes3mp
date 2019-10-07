#ifndef OPENMW_PROCESSORCELLRESET_HPP
#define OPENMW_PROCESSORCELLRESET_HPP

#include "../WorldstateProcessor.hpp"

namespace mwmp
{
    class ProcessorCellReset : public WorldstateProcessor
    {
    public:
        ProcessorCellReset()
        {
            BPP_INIT(ID_CELL_RESET)
        }

        virtual void Do(WorldstatePacket &packet, Worldstate &worldstate)
        {
            // Placeholder
        }
    };
}

#endif //OPENMW_PROCESSORCELLRESET_HPP
