#ifndef _SUGAR_COM_SYNC_H
#define _SUGAR_COM_SYNC_H
#include "sugar/com/common.h"
#include <mutex>
namespace sugar
{
    namespace com
    {
        /***
         *
         * 多线程里的同步对象
         */
        class SyncObj : public ExecEnvironment
        {
        public:
            SyncObj(){}
            std::promise<void> promise;
            void wait();
            void notify();

            int syncUniqueId = 0;
            void setBinary(const std::string &content);
            const std::string *getBinary();

        private:
            std::string content;
        };
        /***
         * sync 对象的管理
         * 创建与销毁
         */
        class SyncManager : public Singleton<SyncManager>
        {
        private:
            int _gloab_sync_id = 0;
            std::map<int, SyncObj *> _syncObjs;
            std::mutex _mutex;

        public:
            SyncManager();
            ~SyncManager();
            SyncObj *createSyncObject();
            void deleteSyncObject(SyncObj *obj);
            SyncObj *findSyncObjectWithId(int id);
        };

    } // namespace sync

} // namespace sugar

#endif // _SUGAR_COM_SYNC_H
