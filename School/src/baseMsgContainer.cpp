#include "baseMsgContainer.h"
template<>
t_BufferCmdQueue::ByteBuffer():_maxSize(trunkSize),_offPtr(0),_curPtr(0),_buffer(_maxSize)
{
}
template<>
t_StackCmdQueue::ByteBuffer():_maxSize(PACKET_ZIP_BUFFER),_offPtr(0),_curPtr(0)
{
}


