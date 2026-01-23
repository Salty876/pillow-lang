#include <stdio.h>
#include <math.h>

#include "vm.h"
#include "debug.h"
#include "compiler.h"

#define READ_BYTE() (*vm.ip++);
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()]);
#define BINARY_OP(op) \
    do { \
        Value b = pop(); \
        Value a = pop(); \
        push(a op b); \
    } while (false)

VM vm;

static void resetStack() {
    vm.stackTop = vm.stack; // Point the thing back to the start of the array to indicate stack is empty
}

void initVM() {
    resetStack();
}

void freeVM() {

}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)

    for (;;){
        #ifdef DEBUG_TRACE_EXECUTION
            printf("          ");
            for (Value* slot = vm.stack; slot < vm.stackTop; slot++) {
                printf("[ ");
                printValue(*slot);
                printf(" ]");
            
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int)(vm.ip - vm.chunk->code));
        #endif

        u_int8_t instruction;
        
        switch (instruction = READ_BYTE())
        {
            // When we find return ends the vm execution

        case OP_CONSTANT: {
            Value constant = READ_CONSTANT();
            push(constant);
            printValue(constant);
            printf("\n");
            break;
        }


        case OP_RETURN: {
            printValue(pop());
            printf("\n");
            return INTERPRET_OK;
            }

        case OP_NEGATE: {
            push(-pop());
            break;
            }
        
        case OP_ADD:        BINARY_OP(+);        break;
        case OP_SUBTRACT:   BINARY_OP(-);        break;
        case OP_MULTIPLY:   BINARY_OP(*);        break;
        case OP_DIVIDE:     BINARY_OP(/);        break;
        // Modulo doesnt work on doubles so i gotta do sum cooked stuff
        case OP_REMAINDER: {
            Value b = pop();
            Value a = pop();
            push(fmod(a, b));
            break;
        }

        }

        
        
        
    }

#undef READ_BYTE
}


InterpretResult interpret(const char* source){
    compile(source);
    return INTERPRET_OK;
}

void push(Value value) {
    // Add to the stacktop and push the stack top one to next empty spot
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    // Decrement the stacktop and return the elemt at that spot
    *vm.stackTop --;
    return *vm.stackTop;
}

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP