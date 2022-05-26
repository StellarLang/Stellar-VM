#include "runtime.hpp"

using namespace stellar::vm;

int main() {
    stellar::Chunk chunk = stellar::Chunk();
    chunk.writeConstant(1.2, 1);
    chunk.writeInstruction(stellar::OP_NEGATE, 1);
    chunk.writeConstant(7.0, 1);
    chunk.writeInstruction(stellar::OP_ADD, 1);
    chunk.writeConstant(false, 2);
    chunk.writeInstruction(stellar::OP_NOT, 2);
    chunk.writeInstruction(stellar::OP_RETURN, 2);

    Runtime runtime = Runtime(chunk);
    InterpretResult result = runtime.interpret();

    if (result == stellar::vm::INTERPRET_OK) return 0;
    else if (result == stellar::vm::INTERPRET_RUNTIME_ERROR) return 1;
    // todo: later add else for unknown cases.
}