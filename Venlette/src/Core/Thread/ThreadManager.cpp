//
// Created by reece on 31/07/22.
//

#include "Core/Thread/ThreadManager.h"
#include "Core/internal.h"

namespace Venlette::Threading {
    VEN_RESULT ThreadManager::Init() noexcept {
        VEN_CORE_INFO("[THREADS] Initialising");

        if (s_instance) {
            VEN_CORE_ERROR("[THREADS] Failed to initialise: Already initialised");
            goto failed;
        }

        try {
            s_instance = new ThreadManager;
        } catch (std::bad_alloc& e) {
            spdlog::error("[THREADS] Failed to create ThreadManager: Could not allocate memory");
            goto failed;
        } catch (std::runtime_error& e) {
            spdlog::error("[THREADS] Failed to create ThreadManager: {}", e.what());
            goto failed;
        } catch (std::string& e) {
            spdlog::error("[THREADS] Failed to create ThreadManager: {}", e);
            goto failed;
        }

        VEN_CORE_INFO("[THREADS] Initialised");
        return VEN_SUCCESS;
        failed:
        return VEN_FAILURE;
    }

    VEN_RESULT ThreadManager::Shutdown() noexcept {
        VEN_CORE_INFO("[THREADS] Shutting down");
        if (!s_instance) {
            VEN_CORE_ERROR("[THREADS] Failed to shutdown: Not Available");
            goto failed;
        }

        try {
            delete s_instance;
            s_instance = nullptr;
        } catch (std::runtime_error& e) {
            spdlog::error("[THREADS] Failed to destroy ThreadManager: {}", e.what());
            goto failed;
        } catch (std::string& e) {
            spdlog::error("[THREADS] Failed to destroy ThreadManager: {}", e);
            goto failed;
        }

        VEN_CORE_INFO("[THREADS] Shut down");
        return VEN_SUCCESS;
        failed:
        return VEN_FAILURE;
    }

    ThreadManager *ThreadManager::Get() noexcept {
        if (!s_instance) {
            VEN_CORE_ERROR("[THREADS] Failed to get instance: Instance not available");
            return nullptr;
        }

        return s_instance;
    }

VEN_RESULT ThreadManager::RegisterThread(ThreadType type) noexcept {

        // is the thread already registered?
        if (m_trackedThreads.find(std::this_thread::get_id()) != m_trackedThreads.end()) {
            VEN_CORE_ERROR("[THREADS] Failed to register thread: Thread already registered");
            return VEN_FAILURE;
        }

        // register the thread
        m_trackedThreads[std::this_thread::get_id()] = type;

        VEN_CORE_INFO("[THREADS] Registered thread");
        return VEN_SUCCESS;
    }

    VEN_RESULT ThreadManager::UnregisterThread() noexcept {
        // is the thread registered?
        if (m_trackedThreads.find(std::this_thread::get_id()) == m_trackedThreads.end()) {
            VEN_CORE_ERROR("[THREADS] Failed to unregister thread: Thread not registered");
            return VEN_FAILURE;
        }

        // unregister the thread
        m_trackedThreads.erase(std::this_thread::get_id());

        VEN_CORE_INFO("[THREADS] Unregistered thread");
        return VEN_SUCCESS;
    }

    ThreadType ThreadManager::GetThreadType() const noexcept {
        // is the thread registered?
        if (m_trackedThreads.find(std::this_thread::get_id()) == m_trackedThreads.end()) {
            VEN_CORE_WARN("[THREADS] Attempted to get unregistered thread: Returned None type");
            return ThreadType::None;
        }

        // get the thread type
        return m_trackedThreads.at(std::this_thread::get_id());
    }

    VEN_RESULT ThreadManager::IsThreadOfType(ThreadType type) const noexcept {
        // is the thread registered?
        if (m_trackedThreads.find(std::this_thread::get_id()) == m_trackedThreads.end()) {
            VEN_CORE_WARN("[THREADS] Attempted to get unregistered thread: Returned False");
            return VEN_FAILURE;
        }

        // is the thread of the correct type?
        if (m_trackedThreads.at(std::this_thread::get_id()) == type) {
            return VEN_SUCCESS;
        }

        return VEN_FAILURE;
    }

    ThreadManager* ThreadManager::s_instance = nullptr;
} // Threading