#include "sugar/com/sync.h"

namespace sugar
{
    namespace com
    {
        /***
         *
         * 多线程里的同步对象
         */

        void SyncObj::wait()
        {
            promise.get_future().wait();
        }
        void SyncObj::notify()
        {
            promise.set_value();
        }

        void SyncObj::setBinary(const std::string &content)
        {
            this->content = content;
        }
        const std::string *SyncObj::getBinary()
        {
            return &this->content;
        }

        /***
         * sync 对象的管理
         * 创建与销毁
         */

        SyncManager::SyncManager()
        {
        }
        SyncManager::~SyncManager()
        {
        }
        SyncObj *SyncManager::createSyncObject()
        {
            std::lock_guard<std::mutex> autolock(_mutex);
            SyncObj *sync = new SyncObj();
            sync->syncUniqueId = _gloab_sync_id++;
            _syncObjs[sync->syncUniqueId] = sync;
            return sync;
        }
        void SyncManager::deleteSyncObject(SyncObj *obj)
        {
            std::lock_guard<std::mutex> autolock(_mutex);
            auto it = _syncObjs.find(obj->syncUniqueId);
            if (it != _syncObjs.end())
            {
                _syncObjs.erase(it);
                delete it->second;
            }
        }

        SyncObj *SyncManager::findSyncObjectWithId(int syncUniqueId)
        {
            std::lock_guard<std::mutex> autolock(_mutex);
            auto it = _syncObjs.find(syncUniqueId);
            if (it != _syncObjs.end())
            {
                return it->second;
            }
            return NULL;
        }

    } // namespace sync

} // namespace sugar