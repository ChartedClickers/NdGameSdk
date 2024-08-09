#pragma once
#include <cstdint>

namespace NdGameSdk {

    template <typename TReg, class TBaseModel = void>
    class ISdkRegenny : public TBaseModel {
    public:
        __forceinline TReg* Get() const {
            return (TReg*)this;
        }

        __forceinline TReg* operator->() const {
            return Get();
        }
    private:
        uint8_t Regenny_data[sizeof(TReg) - sizeof(TBaseModel)];
    };

    template <typename TReg>
    class ISdkRegenny<TReg, void> {
    public:
        __forceinline TReg* Get() const {
            return (TReg*)this;
        }

        __forceinline TReg* operator->() const {
            return Get();
        }
    private:
        uint8_t Regenny_data[sizeof(TReg)];
    };

}