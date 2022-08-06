//
// Created by reece on 06/08/22.
//

#include "Core/Thread/ThreadRegistry.h"

namespace Venlette::Threading {
    VEN_RESULT ThreadRegistry::Init() noexcept {
        VEN_CORE_INFO("[THREAD REGISTRY] Initialising");

        if (s_instance) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to initialise: Already initialised");
            return VEN_FAILURE;
        }

        try {
            s_instance = new ThreadRegistry();
        } catch (std::bad_alloc& e) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to initialise: failed to allocate memory");
            return VEN_FAILURE;
        } catch (std::exception& e) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to initialise: {}", e.what());
            return VEN_FAILURE;
        } catch (std::string& e) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to initialise: {}", e);
            return VEN_FAILURE;
        } catch (...) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to initialise: Unknown error");
            return VEN_FAILURE;
        }

        VEN_CORE_INFO("[THREAD REGISTRY] Initialised");
        return VEN_SUCCESS;
    }

    ThreadRegistry* ThreadRegistry::s_instance = nullptr;

    VEN_RESULT ThreadRegistry::Shutdown() noexcept {
        VEN_CORE_INFO("[THREAD REGISTRY] Shutting down");

        if (!s_instance) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to shutdown: Not initialised");
            return VEN_FAILURE;
        }

        delete s_instance;
        s_instance = nullptr;

        VEN_CORE_INFO("[THREAD REGISTRY] Shut down");
        return VEN_SUCCESS;
    }

    VEN_RESULT ThreadRegistry::RegisterThread(ThreadType type) noexcept {

        if (!s_instance) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Failed to register thread: Not initialised");
            return VEN_FAILURE;
        }

        return s_instance->_registerThread(type);

    }

    VEN_RESULT ThreadRegistry::_isInitialised() noexcept {
        if (s_instance == nullptr) {
            VEN_CORE_ERROR("[THREAD REGISTRY] Thread Registry is not initialised");
        }
    }
} // Threading