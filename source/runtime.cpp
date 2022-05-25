#include <iostream>

#include <stellar/value.hpp>

#include "runtime.hpp"
#include "debug.hpp"

stellar::vm::Runtime::Runtime(stellar::Chunk& chunk) : chunk(chunk) {}

stellar::vm::InterpretResult stellar::vm::Runtime::interpret() {
    for (;;) {
#ifdef DEBUG_TRACE_EXECUTION
        debugPrintStack();
        chunk.disassembleInstruction(programCounter);
#endif

        uint8_t instruction;
        switch (instruction = readByte()) {
            case stellar::OP_RETURN:
                printValue(valueStack.top());
                std::cout << std::endl;
                valueStack.pop();
                return INTERPRET_OK;
            case stellar::OP_CONSTANT:
                Value constant = readConstant();
                valueStack.push(constant);
                break;
        }
    }
}

uint8_t stellar::vm::Runtime::readByte() {
    return chunk.getCode()[programCounter++];
}

stellar::Value stellar::vm::Runtime::readConstant() {
    return chunk.getConstants()[readByte()];
}

void stellar::vm::Runtime::debugPrintStack() {
    std::stack<Value> tempStack = valueStack;
    std::vector<Value> debugVector = std::vector<Value>();

    while (!tempStack.empty()) {
        Value v = tempStack.top();
        debugVector.push_back(v);
        tempStack.pop();
    }

    // stack, read from top down, is reversed relative to its creation (from bottom to top)
    std::reverse(debugVector.begin(), debugVector.end());

    std::cout << "          ";
    for(Value& it : debugVector) {
        std::cout << "[ ";
        printValue(it);
        std::cout << " ]";
    }
    std::cout << std::endl;
}

