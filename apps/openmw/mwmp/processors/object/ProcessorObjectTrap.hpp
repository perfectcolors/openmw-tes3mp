#ifndef OPENMW_PROCESSOROBJECTTRAP_HPP
#define OPENMW_PROCESSOROBJECTTRAP_HPP

#include "BaseObjectProcessor.hpp"

namespace mwmp
{
    class ProcessorObjectTrap : public BaseObjectProcessor
    {
    public:
        ProcessorObjectTrap()
        {
            BPP_INIT(ID_OBJECT_TRAP)
        }

        virtual void Do(ObjectPacket &packet, ObjectList &objectList)
        {
            BaseObjectProcessor::Do(packet, objectList);

            objectList.triggerTrapObjects(ptrCellStore);
        }
    };
}

#endif //OPENMW_PROCESSOROBJECTTRAP_HPP
