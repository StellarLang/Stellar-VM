#pragma once

#include <stellar/chunk.hpp>
#include <stack>

namespace stellar::vm {
    enum InterpretResult {
        INTERPRET_OK,
        INTERPRET_RUNTIME_ERROR,
    };

    class Runtime {
    public:
        explicit Runtime(stellar::Chunk& chunk);
        InterpretResult interpret();

    private:
        void debugPrintStack();
        uint8_t readByte();
        Value readConstant();

        std::stack<Value> valueStack;
        size_t programCounter = 0;
        stellar::Chunk& chunk;
    };
}

