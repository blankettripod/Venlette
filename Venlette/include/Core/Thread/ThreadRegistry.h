//
// Created by reece on 06/08/22.
//

#pragma once

#include "Core/common.h"

#include <condition_variable>
#include <mutex>

namespace Venlette::Threading {

enum class ThreadType{
    Engine = 0,
    Application,
    Rendering,
    Physics,
    Network,
    Audio,
    Worker,
};

class ThreadRegistry {
public:
    static VEN_RESULT Init() noexcept;
    static VEN_RESULT Shutdown() noexcept;

    static VEN_RESULT RegisterThread(ThreadType type) noexcept;
    static VEN_RESULT UnregisterThread() noexcept;

    static VEN_RESULT IsThreadOfType(ThreadType type) noexcept;
private:

    static VEN_RESULT _isInitialised() noexcept;

    VEN_RESULT _registerThread(ThreadType type) noexcept;
    VEN_RESULT _unregisterThread() noexcept;
    VEN_RESULT _isThreadOfType(ThreadType type) const noexcept;


    static ThreadRegistry* s_instance;

    std::map<std::thread::id, ThreadType> m_threads;
    std::condition_variable m_conditionVariable;
    std::mutex m_mutex;
};

} // Threading
