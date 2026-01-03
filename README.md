# mlinc

Machine learning in C - a from-scratch implementation of handwritten digit recognition.

## Overview

This project is a learning exercise to build a neural network for recognizing handwritten digits (MNIST dataset) entirely in C, without using any machine learning libraries. Everything from matrix operations to backpropagation is implemented manually.

## Features

### Implemented

**Memory Management**
- Custom arena allocator for efficient memory allocation
- Platform-specific memory reservation and commit/decommit

**Random Number Generation**
- PCG-based pseudo-random number generator for weight initialization

**Matrix Operations**
- Matrix creation, copy, clear, fill, and scaling
- Element-wise addition and subtraction
- Matrix multiplication with transpose support (4 variants: NN, NT, TN, TT)
- Sum computation

### In Progress

**Activation Functions**
- ReLU (Rectified Linear Unit)
- Softmax

**Loss Functions**
- Cross-entropy loss

**Backpropagation**
- Gradient computation for ReLU
- Gradient computation for softmax
- Gradient computation for cross-entropy

**Neural Network**
- Forward propagation
- Backward propagation
- Training loop
- MNIST data loading

## Project Structure

```
mlinc/
├── include/
│   ├── base.h      # Base types and macros (u32, f32, KiB, etc.)
│   ├── arena.h     # Memory arena allocator interface
│   ├── arena.c     # Memory arena implementation
│   ├── prng.h      # PCG random number generator interface
│   └── prng.c      # PCG random number generator implementation
├── src/
│   └── main.c      # Matrix operations and main entry point
├── build/          # Build artifacts
└── Makefile
```

## Building

Requires GCC and Make:

```bash
make
```

This will:
- Compile source files from `src/` directory
- Place object files in `build/`
- Generate executable at `build/program`

To clean build artifacts:

```bash
make clean
```

## Technical Details

### Matrix Multiplication

The implementation includes optimized matrix multiplication with support for transposed inputs, avoiding unnecessary transpose operations:

- **NN**: Regular A × B
- **NT**: A × B^T
- **TN**: A^T × B
- **TT**: A^T × B^T

Loop ordering is optimized for cache locality in each variant.

### Memory Management

Custom arena allocator that:
- Reserves virtual address space upfront
- Commits pages on-demand as needed
- Supports temporary allocations with automatic cleanup
- Eliminates malloc/free overhead

### Type System

Uses explicit-width types for clarity and portability:
- `u32`, `i64` - unsigned/signed integers
- `f32` - 32-bit floating point
- `b8`, `b32` - boolean types

## Learning Goals

- Understand neural network fundamentals from first principles
- Implement backpropagation without abstractions
- Manage memory efficiently in C
- Optimize matrix operations for performance
- Work with low-level memory and numerical computing

## License

MIT
