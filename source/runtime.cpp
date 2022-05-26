#include <iostream>
#include <sstream>
#include <cmath>

#include <stellar/value.hpp>

#include "runtime.hpp"
#include "debug.hpp"

stellar::vm::Runtime::Runtime(stellar::Chunk& chunk) : chunk(chunk) {}

static std::string multiply_string(std::string& value, int factor) {
    std::stringstream result = std::stringstream();
    for (int i = 0; i < factor; ++i) result << value;
    return result.str();
}

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
            case stellar::OP_ADD: {
                Value b = valueStack.top();
                valueStack.pop();
                Value a = valueStack.top();
                valueStack.pop();

                Value result;
                stellar::ValueType aType = stellar::typeOf(a);
                stellar::ValueType bType = stellar::typeOf(b);

                if (aType == VT_STRING) result = stellar::asString(a) + stellar::asString(b); // asString converts other types automatically for us.
                else if (aType == VT_NUMBER && bType == VT_NUMBER) result = stellar::asNumber(a) + stellar::asNumber(b);
                else {
                    std::cerr
                        << "aType " << stellar::typeString(a)
                        << " and bType " << stellar::typeString(b)
                        << " not applicable to binary operand: +" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }
                valueStack.push(result);
                break;
            }
            case stellar::OP_SUBTRACT: {
                Value b = valueStack.top();
                valueStack.pop();
                Value a = valueStack.top();
                valueStack.pop();

                Value result;
                stellar::ValueType aType = stellar::typeOf(a);
                stellar::ValueType bType = stellar::typeOf(b);

                if (aType == VT_NUMBER && bType == VT_NUMBER) result = stellar::asNumber(a) - stellar::asNumber(b);
                else {
                    std::cerr
                        << "aType " << stellar::typeString(a)
                        << " and bType " << stellar::typeString(b)
                        << " not applicable to binary operand: -" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }

                valueStack.push(result);
                break;
            }
            case stellar::OP_MULTIPLY: {
                Value b = valueStack.top();
                valueStack.pop();
                Value a = valueStack.top();
                valueStack.pop();

                Value result;
                stellar::ValueType aType = stellar::typeOf(a);
                stellar::ValueType bType = stellar::typeOf(b);

                if (aType == VT_NUMBER && bType == VT_NUMBER) result = stellar::asNumber(a) * stellar::asNumber(b);
                else if (aType == VT_NUMBER && bType == VT_STRING) {
                    std::string bString = stellar::asString(b);
                    result = multiply_string(bString, trunc(stellar::asNumber(a)));
                } else if (aType == VT_STRING && bType == VT_NUMBER) {
                    std::string aString = stellar::asString(a);
                    result = multiply_string(aString, trunc(stellar::asNumber(b)));
                } else {
                    std::cerr
                        << "aType " << stellar::typeString(a)
                        << " and bType " << stellar::typeString(b)
                        << " not applicable to binary operand: *" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }

                valueStack.push(result);
                break;
            }
            case stellar::OP_DIVIDE: {
                Value b = valueStack.top();
                valueStack.pop();
                Value a = valueStack.top();
                valueStack.pop();

                Value result;
                stellar::ValueType aType = stellar::typeOf(a);
                stellar::ValueType bType = stellar::typeOf(b);

                if (aType == VT_NUMBER && bType == VT_NUMBER) result = stellar::asNumber(a) / stellar::asNumber(b);
                else {
                    std::cerr
                            << "aType " << stellar::typeString(a)
                            << " and bType " << stellar::typeString(b)
                            << " not applicable to binary operand: /" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }

                valueStack.push(result);
                break;
            }
            case stellar::OP_NEGATE: {
                Value a = valueStack.top();
                valueStack.pop();
                Value result;
                stellar::ValueType aType = stellar::typeOf(a);

                if (aType == VT_NUMBER) result = -(stellar::asNumber(a));
                else {
                    std::cerr
                        << "type " << stellar::typeString(a)
                        << " not applicable to unary operand: -" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }

                valueStack.push(result);
                break;
            }
            case stellar::OP_NOT: {
                Value a = valueStack.top();
                valueStack.pop();
                Value result;
                stellar::ValueType aType = stellar::typeOf(a);

                if (aType == VT_BOOLEAN) result = !(stellar::asBool(a));
                else {
                    std::cerr
                            << "type " << stellar::typeString(a)
                            << " not applicable to unary operand: !" << std::endl;
                    return INTERPRET_RUNTIME_ERROR;
                }

                valueStack.push(result);
                break;
            }
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

