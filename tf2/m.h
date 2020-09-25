#pragma once

template<typename out, class type>
inline out method(size_t index, type* self) noexcept {
    return reinterpret_cast<out>((*reinterpret_cast<void***>(self))[index]);
}

template<typename FuncType>
__forceinline static FuncType CallVFunction(void* ppClass, int index)
{
    int* pVTable = *(int**)ppClass;
    int dwAddress = pVTable[index];
    return (FuncType)(dwAddress);
}
