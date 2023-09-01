#include "sugar/com/any.h"

namespace sugar
{
    namespace com
    {
        void AnyValue::__to_msg__record__(unsigned char tag, cmd::Stream *ss)
        {
            switch (tag)
            {
            case cmd::GET:
            {
                unsigned long long value = 0;
                getRecord(value, ss);
                object = (void*)value;
            }
            break;
            case cmd::ADD:
            {
                unsigned long long xx = (unsigned long long)object;
                addRecord(xx, ss);
            }
            break;
            }
            BIND_MSG(type);
        }
        SyncObj *AnyValue::createSyncObject()
        {
            std::lock_guard<std::mutex> mylock(_mutex_sync);
            SyncObj *obj = SyncManager::getInstance().createSyncObject();
            syncObjects[obj->syncUniqueId] = obj;
            object = obj;
            return obj;
        }
        SyncObj *AnyValue::attachSyncObject(int sessionid)
        {
            std::lock_guard<std::mutex> mylock(_mutex_sync);
            auto sync_iter = syncObjects.find(sessionid);
            if (sync_iter != syncObjects.end())
            {
                object = sync_iter->second;
                return sync_iter->second;
            }
            return NULL;
        }
        SyncObj *AnyValue::getSyncObject()
        {
            return (SyncObj *)object;
        }

        AnyValue::Binary *AnyValue::createBinary(void *stream, int size)
        {
            std::lock_guard<std::mutex> mylock(_mutex_bin);
            Binary *bin = new Binary();
            object = bin;
            bin->resize(size);
            memcpy(&(*bin)[0], stream, size);
            binaries.insert(bin);
            return bin;
        }
        AnyValue::Binary *AnyValue::getBinary()
        {
            return (Binary *)object;
        }

        void AnyValue::destroy()
        {
            if (type == SYNC_TYPE)
            {
                std::lock_guard<std::mutex> mylock(_mutex_sync);
                SyncObj *obj = (SyncObj *)object;
                auto it = syncObjects.find(obj->syncUniqueId);
                if (it != syncObjects.end())
                {
                    syncObjects.erase(it);
                }
                SyncManager::getInstance().deleteSyncObject(obj);
            }
            if (type == BINARY_TYPE)
            {
                std::lock_guard<std::mutex> mylock(_mutex_bin);
                Binary *obj = (Binary *)object;
                auto it = binaries.find(obj);
                if (it != binaries.end())
                {
                    binaries.erase(it);
                }
                delete obj;
            }
        }

        std::map<int, SyncObj *> AnyValue::syncObjects;
        std::set<AnyValue::Binary *> AnyValue::binaries;
        std::mutex AnyValue::_mutex_sync;
        std::mutex AnyValue::_mutex_bin;
    } // namespace com

} // namespace sugar
