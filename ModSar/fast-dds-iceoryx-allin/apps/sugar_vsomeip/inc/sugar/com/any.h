#ifndef _SUGAR_COM_ANY_H
#define _SUGAR_COM_ANY_H
#include "sugar/com/common.h"
#include "sugar/com/sync.h"
namespace sugar
{
    namespace com
    {
        class AnyValue : public cmd::Object
        {
        public:
            using Binary = std::string;
            void *object = NULL;

            enum VALUE_TYPE
            {
                INVALID_TYPE = -1,
                SYNC_TYPE = 1,
                BINARY_TYPE = 2,
            };
            int type = INVALID_TYPE;

            void __to_msg__record__(unsigned char tag, cmd::Stream *ss);

            SyncObj *createSyncObject();
            SyncObj *attachSyncObject(int sessionid);
            SyncObj *getSyncObject();

            Binary *createBinary(void *stream, int size);
            Binary* getBinary();

            void destroy();

            static std::map<int, SyncObj *> syncObjects;
            static std::set<Binary *> binaries;
            static std::mutex _mutex_bin;
            static std::mutex _mutex_sync;
        };
    } // namespace com

} // namespace sugar

#endif // _SUGAR_COM_ANY_H
