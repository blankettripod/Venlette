//
// Created by reece on 31/07/22.
//

#pragma once

#include "Core/common.h"

namespace Venlette::Core{class Engine;}

namespace Venlette::Threading {
    enum class ThreadType {
        None=0,
        Engine,
        ClientUpdate,
        ClientRender,
        JobQueue,
    };

class ThreadManager {
public:

    static ThreadManager* Get() noexcept;

    VEN_RESULT RegisterThread(ThreadType type=ThreadType::None) noexcept;
    VEN_RESULT UnregisterThread() noexcept;
    [[nodiscard]] ThreadType GetThreadType() const noexcept;
    [[nodiscard]] VEN_RESULT IsThreadOfType(ThreadType type) const noexcept;

protected:
    friend class Venlette::Core::Engine;

    static VEN_RESULT Init() noexcept;
    static VEN_RESULT Shutdown() noexcept;

private:
    static ThreadManager* s_instance;

    std::map<std::thread::id, ThreadType> m_trackedThreads;
};

#define REGISTER_THREAD(TYPE) ::Venlette::Threading::ThreadManager::Get()->RegisterThread(TYPE); END_MACRO
#define UNREGISTERED_THREAD() ::Venlette::Threading::ThreadManager::Get()->UnregisterThread(); END_MACRO
#define GET_THREAD_TYPE() (::Venlette::Threading::ThreadManager::Get()->GetThreadType())
#define IS_THREAD_OF_TYPE(TYPE) (::Venlette::Threading::ThreadManager::Get()->IsThreadOfType(TYPE))

} // Threading
