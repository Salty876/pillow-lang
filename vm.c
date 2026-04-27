#include <stdarg.h>
#include <stdio.h>
#include <math.h>

#include "vm.h"
#include "debug.h"
#include "compiler.h"

#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

VM vm;

static Value peek(int distance);
static bool is_falsey(Value value);



static void resetStack() {
    vm.stackTop = vm.stack; // Point the thing back to the start of the array to indicate stack is empty
}

static void runtimeError(const char* format, ...) { 
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    fputs("\n", stderr);

    size_t instruction = vm.ip - vm.chunk->code - 1;
    int line = vm.chunk->lines[instruction];
    fprintf(stderr, "[line %d] in script\n", line);
    resetStack();
}

void initVM() {
    resetStack();
}

void freeVM() {

}

static InterpretResult run() {
#define READ_BYTE() (*vm.ip++)
#define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])


#define BINARY_OP(valueType, op) \
    do { \
        if (!IS_NUMBER(peek(0)) || !IS_NUMBER(peek(1))) { \
            runtimeError("Operands must be numbers."); \
            return INTERPRET_RUNTIME_ERROR; \
        } \
        double b = AS_NUMBER(pop()); \
        double a = AS_NUMBER(pop()); \
        push(valueType(a op b)); \
    } while (false)

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

        uint8_t instruction;
        
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
            // Check that it's acc a number
            if (!IS_NUMBER(peek(0))) {
                runtimeError("Operand must be a number.");
                return INTERPRET_RUNTIME_ERROR;
            }
            
            push (NUMBER_VAL(-AS_NUMBER(pop())));
            break;
            }
        
        case OP_EQUAL: {
            Value b = pop();
            Value a = pop();
            push(BOOL_VAL(valuesEqual(a, b)));
            break;
        }

        case OP_NULL: push(NULL_VAL); break;
        case OP_TRUE: push(BOOL_VAL(true)); break;
        case OP_FALSE: push(BOOL_VAL(false)); break;
        case OP_NOT: push(BOOL_VAL(is_falsey(pop()))); break;
        case OP_GREATER: BINARY_OP(BOOL_VAL, >); break;
        case OP_LESS: BINARY_OP(BOOL_VAL, <); break;
        case OP_ADD:      BINARY_OP(NUMBER_VAL, +); break;
        case OP_SUBTRACT: BINARY_OP(NUMBER_VAL, -); break;
        case OP_MULTIPLY: BINARY_OP(NUMBER_VAL, *); break;
        case OP_DIVIDE:   BINARY_OP(NUMBER_VAL, /); break;
        // Modulo doesnt work on doubles so I gotta do sum cooked stuff
        case OP_REMAINDER: {
            Value b = pop();
            Value a = pop();
            push(NUMBER_VAL(fmod(AS_NUMBER(a), AS_NUMBER(b))));
            break;
        }

        }

        
        
        
    }

#undef READ_BYTE
}


InterpretResult interpret(const char* source){
    Chunk chunk;
    initChunk(&chunk);

    if (!compile(source, &chunk)) {
        freeChunk(&chunk);
        return INTERPRET_COMPILE_ERROR;
    }

    vm.chunk = &chunk;
    vm.ip = vm.chunk->code;

    InterpretResult result = run();

    freeChunk(&chunk);
    return result;
}

void push(Value value) {
    // Add to the stacktop and push the stack top one to next empty spot
    *vm.stackTop = value;
    vm.stackTop++;
}

Value pop() {
    // Decrement the stacktop and return the elemt at that spot
    vm.stackTop--;
    return *vm.stackTop;
}

static Value peek(int distance) {
    return vm.stackTop[-1 - distance];
}

static bool is_falsey(Value value) {
    return IS_NULL(value) || (IS_BOOL(value) && !AS_BOOL(value));
}

#undef READ_BYTE
#undef READ_CONSTANT
#undef BINARY_OP